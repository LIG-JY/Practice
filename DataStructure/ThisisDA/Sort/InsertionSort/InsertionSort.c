#include <stdio.h> 
#include <string.h> 
 
void InsertionSort(int DataSet[], int Length) 
{ 
    int i = 0; 
    int j = 0; 
    int value = 0; 
 
    /* value(key)를 정하는 과정, 반복횟수는 index 1부터 끝까지. */
    for ( i=1; i<Length; i++ ) 
    { 
        /* value가 정렬된 상태인지 확인 */
        if ( DataSet[i-1] <= DataSet[i] ) 
            continue; 
 
        value = DataSet[i]; 

        /* 가장 앞 부터 비교(이미 정렬되어있다는 가정) */
        for ( j=0; j<i; j++ )  
        {             
            if (DataSet[j] > value)  
            {
                /* demonstration */
                int k;
                printf("before\t");
                for (k=0; k<Length; k++)
                {
                    printf("%d", DataSet[k]);
                }
                printf("\n");

                /* i~j(i 제외 j 포함) 변위만큼의 바이트를 복사한다. 결과적으로 배열의 값들을 밀어준다. */
                memmove(&DataSet[j+1], &DataSet[j], sizeof(DataSet[0]) * (i-j)); 
                DataSet[j] = value; 

                /* demonstration */
                printf("after\t");
                for (k=0; k<Length; k++)
                {
                    printf("%d", DataSet[k]);
                }
                printf("\n");
                break;     
            } 
        } 
    } 
}
 
int main( void )
{ 
    int DataSet[] = {6, 4, 2, 3, 1, 5}; 
    int Length = sizeof DataSet / sizeof DataSet[0];     
    int i = 0; 
 
    InsertionSort(DataSet, Length); 
 
    for ( i=0; i<Length; i++ ) 
    { 
        printf("%d ", DataSet[i]); 
    } 
 
    printf("\n"); 
 
    return 0; 
}
