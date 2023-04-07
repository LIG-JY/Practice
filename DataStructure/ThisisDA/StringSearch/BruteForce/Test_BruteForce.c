#include <stdio.h>
#include <string.h>
#include "BruteForce.h"

#define MAX_BUFFER 512

int main(int argc, char** argv)
{
    char* FilePath;
    FILE* fp;

    char  Text[MAX_BUFFER];
    char* Pattern;
    int   PatternSize = 0;
    int   Line        = 0;
    
    if ( argc < 3 ) // command line arguments 로 FilePath, Pattern 입력
    {
        printf("Usage: %s <FilePath> <Pattern>\n", argv[0] );
        return 1;
    }

    FilePath = argv[1];
    Pattern  = argv[2];

    PatternSize = strlen( Pattern );

    if ( (fp = fopen( FilePath, "r"))  == NULL ) // 2번째 인자인 Filepath Open, readmode
    {
        printf("Cannot open file:%s\n", FilePath);
        return 1;
    } 

    while ( fgets( Text, MAX_BUFFER, fp ) != NULL ) // 1줄씩 읽는다. Buffer의 최대값은 512
    {
        int Position = BruteForce( Text, strlen(Text), 0, Pattern, PatternSize ); // 1줄 즉 char Text[512]마다 BruteForce함수를 호출해서 찾는다.
        
        Line++;

        if ( Position >= 0 ) 
        {
            printf("line:%d, column:%d : %s", Line, Position+1, Text); // position이 string의 인덱스라서 0부터 시작합니다.
        }
    }

    fclose( fp );

    return 0;
}
