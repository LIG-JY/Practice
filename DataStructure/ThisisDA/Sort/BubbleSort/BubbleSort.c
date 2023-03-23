#include <stdio.h> 
 
void BubbleSort(int DataSet[], int Length) 
{ 
    int i = 0; 
    int j = 0; 
    int temp = 0;
    int iteration = 0;
 
    // Length는 총 반복 횟수 input의 크기(자료구조의 크기)와 비례한다. i 값과 이미 정렬된 값의 수가 비례한다.
    for ( i=0; i<Length-1; i++ ) 
    { 
        iteration++;
        int Swapcount = 0;
        // 이웃과 비교, Swap -> 결과적으로 (i+1)순위 값이 정렬된다. ex) i = 0 이면 1순위(가장 큰 값)이 정렬 완료
        for ( j=0; j<Length-(i+1); j++ )  
        { 
            if ( DataSet[j] > DataSet[j+1] ) 
            { 
                temp = DataSet[j+1]; 
                DataSet[j+1] = DataSet[j]; 
                DataSet[j] = temp;
                Swapcount++;
            } 
        }
        if (Swapcount == 0)
        {
            // debug
            printf("iteration: %d, Break!\n", iteration);
            break;
        }
            
    } 
}
 
int main( void ) 
{ 
    // int DataSet[] = {6, 4, 2, 3, 1, 5};
    // int DataSet[] = {5, 1, 6, 4, 2, 3};
    // int DataSet[] = {5, 6, 1, 2, 3, 4};
    // int DataSet[] = {5, 6, 1, 2, 3, 4, 5};
    // int DataSet[] = {5, 1, 2, 3, 4, 5, 6};
    int DataSet[] = {1, 2, 3, 4, 5, 6}; 

    int Length = sizeof(DataSet) / sizeof(DataSet[0]);   
    int i = 0; 
 
    BubbleSort(DataSet, Length);
 
    for ( i=0; i<Length; i++ ) 
    { 
        printf("%d ", DataSet[i]); 
    } 
 
    printf("\n"); 
 
    return 0; 
}