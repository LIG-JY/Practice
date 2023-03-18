#include "LinkedQueue.h"

int main( void )
{
    Node* Popped;
    LinkedQueue* Queue;

    LQ_CreateQueue(&Queue );
    
    LQ_Enqueue( Queue, LQ_CreateNode("abc") );
    LQ_Enqueue( Queue, LQ_CreateNode("def") );
    LQ_Enqueue( Queue, LQ_CreateNode("efg") );
    LQ_Enqueue( Queue, LQ_CreateNode("hij") );

    printf("Queue Size : %d\n", Queue->Count);

    while ( LQ_IsEmpty( Queue ) == 0 )
    {
        Popped = LQ_Dequeue( Queue );

        printf( "Dequeue: %s \n", Popped->Data );
        printf( "Now Queue has %d nodes \n", Queue->Count );

        LQ_DestroyNode( Popped );
    }

    // Empty Test
    Popped = LQ_Dequeue( Queue );

    LQ_DestroyQueue( Queue );

    return 0;
}
