#include "LCRSTree.h"

LCRSNode* LCRS_CreateNode( ElementType NewData )
{
    LCRSNode* NewNode = (LCRSNode*)malloc( sizeof(LCRSNode) );
    NewNode->LeftChild    = NULL;
    NewNode->RightSibling = NULL;
    NewNode->Data = NewData;

    return NewNode;
}

void LCRS_DestroyNode( LCRSNode* Node )
{
    free(Node);
}

void LCRS_DestroyTree( LCRSNode* Root )
{
    if ( Root->RightSibling != NULL )
        LCRS_DestroyTree( Root->RightSibling );

    if ( Root->LeftChild != NULL )
        LCRS_DestroyTree( Root->LeftChild );

    Root->LeftChild = NULL;
    Root->RightSibling = NULL;

    LCRS_DestroyNode( Root );
}

void LCRS_AddChildNode( LCRSNode* Parent, LCRSNode *Child)
{
    // 자식이 없는 경우 부모노드의 Left Pointer에 바로 연결
    if ( Parent->LeftChild == NULL )
    {
        Parent->LeftChild = Child;
    }
    // 자식이 있는 경오 부모노드의 Left Pointer로 자식을 찾아서, 자식의 형제노드(Right Pointer)로 탐색
    else 
    {
        LCRSNode* TempNode = Parent->LeftChild;
        while ( TempNode->RightSibling != NULL )
            TempNode = TempNode->RightSibling;

        TempNode->RightSibling = Child;        
    }
}

void LCRS_PrintTree( LCRSNode* RootNode, int Depth )
{
    // 들여쓰기
    int i=0; 
    for ( i=0; i<Depth-1; i++ )
        printf("   "); // 공백 3칸

    if (Depth > 0) // 자식 노드 여부 표시
        printf("*--");
    
    // 노드 데이터 출력
    printf("%c\n", RootNode->Data); 

    // 각 노드 포인터에 대해서 할 일 재귀로
    if ( RootNode->LeftChild != NULL )
        LCRS_PrintTree(RootNode->LeftChild, Depth+1);

    // 각 노드 포인터에 대해서 할 일 재귀로
    if ( RootNode->RightSibling != NULL )
        LCRS_PrintTree(RootNode->RightSibling, Depth);
}

void LCRS_PrintNodesAtLevel( LCRSNode* RootNode, int Level, int Depth)
{ 
    // 노드 데이터 출력
    if (Depth == Level)
    {
        if (Level == 0)
            printf("Root : %c\n", RootNode->Data);
        else
            printf("Level %d: %c\n", Level, RootNode->Data);
    }
    // 각 노드 포인터에 대해서 할 일 재귀로
    if ( RootNode->LeftChild != NULL )
        LCRS_PrintNodesAtLevel(RootNode->LeftChild, Level, Depth+1);

    // 각 노드 포인터에 대해서 할 일 재귀로
    if ( RootNode->RightSibling != NULL )
        LCRS_PrintNodesAtLevel(RootNode->RightSibling, Level, Depth);
}