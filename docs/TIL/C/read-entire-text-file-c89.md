# 크기를 알 수 없는 텍스트 파일을 읽어오는 방법

## 1. 반복문을 통해 버퍼 사이즈를 늘려나가는 방법

```c++
#include <stdio.h>
#include <stdlib.h>

char *readFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return NULL;
    }

    // Initialize buffer
    size_t bufferSize = 1024;
    char *buffer = (char *)malloc(bufferSize);
    if (buffer == NULL) {
        perror("Failed to allocate initial buffer");
        fclose(file);
        return NULL;
    }

    size_t length = 0;
    size_t n;

    // Read the file in chunks
    while ((n = fread(buffer + length, 1, bufferSize - length, file)) > 0) {
        length += n;
        if (length == bufferSize) {
            bufferSize *= 2;
            char *newBuffer = (char *)realloc(buffer, bufferSize);
            if (newBuffer == NULL) {
                perror("Failed to reallocate buffer");
                free(buffer);
                fclose(file);
                return NULL;
            }
            buffer = newBuffer;
        }
    }

    if (ferror(file)) {
        perror("Error reading file");
        free(buffer);
        fclose(file);
        return NULL;
    }

    // Null-terminate the buffer
    buffer[length] = '\0';

    fclose(file);
    return buffer;
}

int main() {
    const char *filename = "example.txt";
    char *fileContents = readFile(filename);

    if (fileContents != NULL) {
        printf("File contents:\n%s\n", fileContents);
        free(fileContents);
    }

    return 0;
}
```

- length: 파일의 크기(바이트 단위)
- n: 한 번에 읽어온 바이트 수

- case1: 버퍼 사이즈 > 파일의 크기
    - while문 1번만 실행
    - n == 파일의 크기
    - 두번째 while의 조건문에서 fread 결과값이 0이므로 while문 종료
- case2: 버퍼 사이즈 < 파일의 크기
    - while문 여러번 실행
    - n == bufferSize
    - length == bufferSize를 만족함. 따라서 realloc으로 버퍼 사이즈 증가
    - 두번째 while의 조건문에서 fread는 bufferSize - length만큼 읽어옴
        - bufferSize == length + (늘어난 버퍼 사이즈)
        - 즉 늘어난 버퍼 사이즈 만큼 추가로 파일을 읽음
        - ... 반복, 반복하다가 case1이 될 가능성이 높음
    - 파일을 모두 읽은 경우 fread는 0을 반환하므로 while문 종료

## 2. fseek와 ftell을 이용하는 방법

```c++
FILE *fp;
long lSize;
char *buffer;

fp = fopen ( "blah.txt" , "rb" );
if( !fp ) perror("blah.txt"),exit(1);

fseek( fp , 0L , SEEK_END);
lSize = ftell( fp );
rewind( fp );

/* allocate memory for entire content */
buffer = calloc( 1, lSize+1 );
if( !buffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

/* copy the file into the buffer */
if( 1!=fread( buffer , lSize, 1 , fp) )
  fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);

/* do your work here, buffer is a string contains the whole text */

fclose(fp);
free(buffer);
```

```c++
int main(int argc, char** argv)
{
   FILE* fpInputFile = NULL; 
   unsigned long ulSize = 0;  // Input File size
   unsigned long ulIteration = 0; 
   unsigned char* ucBuffer; // Buffer data

  if(argc != 2)
  {
   printf("Enter ihe file name \n");
   return -1;
  }
  fpInputFile = fopen(argv[1],"r"); // file open

  if(!fpInputFile){
    fprintf(stderr,"File opening failed");
  }
  fseek(fpInputFile,0,SEEK_END);
  ulSize = ftell(fpInputFile); //current file position
  fseek(fpInputFile,0,SEEK_SET);
  ucBuffer = (unsigned char*)malloc(ulSize); // memory allocation for ucBuffer var
  fread(ucBuffer,1,ulSize,fpInputFile); // Read file
  fclose(fpInputFile); // close the  file
 }
```

- fseek(fp, 0, SEEK_END): 파일의 끝으로 이동
- lSize = ftell(fp): SEEK_SET에서 부터 파일의 끝까지의 바이트 수를 반환하므로 크기를 알 수 있음
- rewind(fp): 파일의 처음으로 이동
    - fseek(fp, 0, SEEK_SET)과 동일
- 파일의 크기를 동적으로 알아내면, 그 크기만큼 동적할당을 해주고 fread로 파일을 읽어옴