#include <stdio.h>

/* call by reference */
void Swap( int* A, int* B )
{
    int Temp = *A;
    *A = *B;
    *B = Temp;
}

int Partition( int DataSet[], int Left, int Right )
{
    /* 
        left most index, right most index 
        피봇 규칙은 (분할된)그룹에서 가장 왼쪽
    */
    int First = Left;
    int Pivot = DataSet[First];

    /* 투 포인터로 교환 작업하는 준비: Pivot의 바로 오른쪽 인덱스에서 시작 */
    ++Left;

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

    Swap( &DataSet[First], &DataSet[Right] );

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
