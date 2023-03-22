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

/* call by reference */
void Swap( int* A, int* B )
{
    int Temp = *A;
    *A = *B;
    *B = Temp;
}

int Findmid(int DataSet[])
{
    int piece[3];
    int value;
    int i = 0;
    int j = 0;

    for (i = 0; i < 3; i++)
    {
        piece[i] = DataSet[i];
    }

    BubbleSort(piece, 3);
    value = piece[1];

    for (j = 0; j < 3; j++)
    {
        if (DataSet[j] == value)
            return j;
    }
    return j;
}

int Partition( int DataSet[], int Left, int Right )
{
    /* 
        left most index, right most index 
        피봇 규칙은 처음 3요소 (index 0, 1, 2)에서 중간값
    */
    int length = Right - Left + 1;
    int P_idx = Left;
    int Pivot = DataSet[P_idx];

    
    if (length > 3)
    {
        P_idx = Findmid(DataSet);

        /* Debug */
        Pivot = DataSet[P_idx];
        printf("Pivot = %d\n", Pivot);

        /* pivot을 가장 앞으로 */
        Swap(&DataSet[P_idx], &DataSet[Left]);
        P_idx = Left;
    }
    /* 투 포인터로 교환 작업하는 준비: Pivot(배열의 첫번째)의 바로 오른쪽 인덱스에서 시작 */
    else
    {
        ++Left;
    }

    /* 종료조건: 두 포인터가 만날 때 */
    while( Left <= Right )
    {
        /* 왼쪽에서 오른쪽으로 이동하면서 pivot보다 큰 요소 찾으면 종료 */
        while( DataSet[Left] <= Pivot && Left < Right )
            ++Left;

        while( DataSet[Right] >= Pivot && Left <= Right )
            --Right;

        if ( Left < Right )
            Swap( &DataSet[Left], &DataSet[Right]);
        else
            break;
    }

    Swap( &DataSet[P_idx], &DataSet[Right] );

    /* right = left */
    return Right;
}

void QuickSort(int DataSet[], int Left, int Right)
{
    if ( Left < Right )
    {
        /* 분할 및 기준 요소 선정 */
        int Index = Partition(DataSet, Left, Right);

        QuickSort( DataSet, Left, Index - 1 );
        QuickSort( DataSet, Index + 1, Right );
    }
}

int main( void )
{
    int DataSet[] = {6, 4, 2, 3, 1, 5};
    int Length = sizeof DataSet / sizeof DataSet[0];    
    int i = 0;

    QuickSort( DataSet, 0, Length-1 );

    for ( i=0; i<Length; i++ )
    {
        printf("%d ", DataSet[i]);
    }

    printf("\n");

    return 0;
}
