#include "BinaryTree.h"

SBTNode* SBT_CreateNode( ElementType NewData )
{
    SBTNode* NewNode = (SBTNode*)malloc( sizeof(SBTNode) );
    NewNode->Left    = NULL;
    NewNode->Right   = NULL;
    NewNode->Data    = NewData;

    return NewNode;
}

void SBT_DestroyNode( SBTNode* Node )
{
    free(Node);
}

void SBT_DestroyTree( SBTNode* Node )
{
    // 종료조건
    if ( Node == NULL )
        return;
    
    // 반드시 뿌리가 마지막에 오는 후위 순회(PostOrder): 

    //  왼쪽 하위 트리 소멸 
    SBT_DestroyTree( Node->Left );

    //  오른쪽 하위 트리 소멸 
    SBT_DestroyTree( Node->Right );

    //  뿌리 노드 소멸 
    SBT_DestroyNode( Node );
}

// 전위순회: 뿌->왼->오
void SBT_PreorderPrintTree( SBTNode* Node )
{
    if ( Node == NULL )
        return;

    //  뿌리 노드 출력 
    printf( " %c", Node->Data );

    //  왼쪽 하위 트리 출력 
    SBT_PreorderPrintTree( Node->Left );

    //  오른쪽 하위 트리 출력 
    SBT_PreorderPrintTree( Node->Right );
}

// 중위: 왼->뿌->오
void SBT_InorderPrintTree( SBTNode* Node )
{
    if ( Node == NULL )
        return;
    
    //  왼쪽 하위 트리 출력 
    SBT_InorderPrintTree( Node->Left );

    //  뿌리 노드 출력 
    printf( " %c", Node->Data );
    
    //  오른쪽 하위 트리 출력 
    SBT_InorderPrintTree( Node->Right );
}

// 후위: 왼->오->뿌
void SBT_PostorderPrintTree( SBTNode* Node )
{
    if ( Node == NULL )
        return;
    
    //  왼쪽 하위 트리 출력 
    SBT_PostorderPrintTree( Node->Left );

    //  오른쪽 하위 트리 출력 
    SBT_PostorderPrintTree( Node->Right );

    //  뿌리 노드 출력 
    printf( " %c", Node->Data );
}