#include "CircularQueue.h"

int main( void )
{
    int i;
    CircularQueue* Queue;

    CQ_CreateQueue(&Queue, 10);
    
    CQ_Enqueue( Queue, 1 );
    CQ_Enqueue( Queue, 2 );
    CQ_Enqueue( Queue, 3 );
    CQ_Enqueue( Queue, 4 );

    for ( i=0; i<3; i++)
    {
        printf( "Dequeue: %d, ",       CQ_Dequeue( Queue ) );
        printf( "Front:%d, Rear:%d\n", Queue->Front, Queue->Rear );
    }
    
    i = 100;
    while ( CQ_IsFull( Queue ) == 0 )
    {
        CQ_Enqueue( Queue, i);
        printf( "Enqueue: %d, ", i++);
        printf( "Front:%d, Rear:%d\n", Queue->Front, Queue->Rear );
    }

    printf( "Capacity: %d, Size: %d\n\n", Queue->Capacity, CQ_GetSize(Queue ) );
    printf( "Front:%d, Rear:%d\n", Queue->Front, Queue->Rear );
    // Enqueue 꽉 찼을 때 예외처리 확인
    CQ_Enqueue( Queue, 500 );

    while ( CQ_IsEmpty( Queue ) == 0)
    {        
        printf( "Dequeue: %d, ",       CQ_Dequeue( Queue ) );
        printf( "Front:%d, Rear:%d\n", Queue->Front, Queue->Rear );
    }

    // Dequeue 비었을 때 예외처리 확인 
    CQ_Dequeue( Queue );

    CQ_DestroyQueue( Queue );

    return 0;
}
