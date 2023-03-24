#include "Heap.h"

void PrintNode( HeapNode* Minnode )
{
    printf("방금 뽑은 최소 데이터 : %d\n", Minnode->Data);
}

int main( void )
{
    Heap* H = HEAP_Create( 0 );
    HeapNode MinNode;
    
    HEAP_Insert( H, 12 );
    HEAP_Insert( H, 87 );
    HEAP_Insert( H, 111 );
    HEAP_Insert( H, 34 );
    HEAP_Insert( H, 16 );
    HEAP_Insert( H, 75 );
    HEAP_PrintNodes( H );
    
    HEAP_DeleteMin( H, &MinNode );
    PrintNode(&MinNode);
    HEAP_PrintNodes( H );

    HEAP_DeleteMin( H, &MinNode );
    PrintNode(&MinNode);
    HEAP_PrintNodes( H );

    HEAP_DeleteMin( H, &MinNode );
    PrintNode(&MinNode);
    HEAP_PrintNodes( H );

    HEAP_DeleteMin( H, &MinNode );
    PrintNode(&MinNode);
    HEAP_PrintNodes( H );

    HEAP_DeleteMin( H, &MinNode );
    PrintNode(&MinNode);
    HEAP_PrintNodes( H );

    HEAP_DeleteMin( H, &MinNode );
    PrintNode(&MinNode);
    HEAP_PrintNodes( H );

    return 0;
}
