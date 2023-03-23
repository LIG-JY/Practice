#include "BinarySearchTree.h"

BSTNode* BST_CreateNode( ElementType NewData )
{
    BSTNode* NewNode = (BSTNode*)malloc( sizeof(BSTNode) );
    NewNode->Left    = NULL;
    NewNode->Right   = NULL;
    NewNode->Data    = NewData;

    return NewNode;
}

void BST_DestroyNode( BSTNode* Node )
{
    free(Node);
}

void BST_DestroyTree( BSTNode* Tree )
{
    if ( Tree->Right != NULL )
        BST_DestroyTree( Tree->Right );

    if ( Tree->Left != NULL )
        BST_DestroyTree( Tree->Left );

    /* left, right child 중 둘 중하나만 있는 경우 child를 free하고 포인터 NULL로 만들어 준다. */
    Tree->Left = NULL;
    Tree->Right = NULL; 

    BST_DestroyNode( Tree );
}

BSTNode*  BST_SearchNode( BSTNode* Tree, ElementType Target )
{
    /* 종료조건 2가지임 */
    /*  못찾는 경우 */
    if ( Tree == NULL )
        return NULL;
    
    /*  찾는 경우 */
    if ( Tree->Data == Target )
        return Tree;
    /* Node의 데이터와 대소비교를 통해 좌,우 자식으로 탐색 재귀 호출 */
    else if ( Tree->Data > Target )
        return BST_SearchNode ( Tree->Left, Target );
    else
        return BST_SearchNode ( Tree->Right,  Target );
}


BSTNode*  BST_SearchMinNode( BSTNode* Tree )
{
    if ( Tree == NULL )
        return NULL;

    if ( Tree->Left == NULL ) 
        return Tree;
    else
        return BST_SearchMinNode( Tree->Left );
}

/* child가 추가할 노드 */
void BST_InsertNode( BSTNode* Tree, BSTNode *Child)
{
    if ( Tree->Data < Child->Data ) 
    {
        /* 노드 여부를 확인해야 한다. 추가 해야하니까! 탐색과 차이점 */
        if ( Tree->Right == NULL )
            Tree->Right = Child;
        else
            BST_InsertNode( Tree->Right, Child );
    } 
    else if ( Tree->Data > Child->Data ) 
    {
        if ( Tree->Left == NULL )
            Tree->Left = Child;
        else
            BST_InsertNode( Tree->Left, Child );
    }
}

BSTNode* BST_RemoveNode( BSTNode* Tree,BSTNode* Parent, ElementType Target )
{
    BSTNode* Removed = NULL;

    if ( Tree == NULL )
        return NULL;

    if ( Tree->Data > Target )
        Removed = BST_RemoveNode( Tree->Left, Tree, Target );
    else if ( Tree->Data < Target )
        Removed = BST_RemoveNode( Tree->Right, Tree, Target );
    else //  목표 값을 찾은 경우. 
    {
        Removed = Tree;

        //  잎 노드인 경우 바로 삭제 
        if ( Tree->Left == NULL && Tree->Right == NULL )
        {
            if ( Parent->Left == Tree )
                Parent->Left = NULL;
            else 
                Parent->Right = NULL;
        }
        else
        {
            //  자식이 양쪽 다 있는 경우 
            if ( Tree->Left != NULL && Tree->Right != NULL ) 
            {
                //  오른쪽 하위 트리에서 최솟값 노드를 찾아 제거한 뒤 현재의 노드에 위치시킨다. (데이터만 교체)
                BSTNode* MinNode = BST_SearchMinNode( Tree->Right );
                MinNode = BST_RemoveNode( Tree, NULL, MinNode->Data ); // 2번째 parameter가 부모Node인데 NULL말고 뭘 넣든 상관없다. 어차피 자식 방향으로 탐색하는 흐름이기 때문이다.
                Tree->Data = MinNode->Data;
            }
            else
            {
                //  자식이 한쪽만 있는 경우 
                BSTNode* Temp = NULL;
                if ( Tree->Left != NULL )
                    Temp = Tree->Left;
                else 
                    Temp = Tree->Right;

                if ( Parent->Left == Tree )
                    Parent->Left  = Temp;
                else 
                    Parent->Right = Temp;
            }
        }
    }

    return Removed;
}

void BST_InorderPrintTree( BSTNode* Node )
{
    if ( Node == NULL )
        return;

    //  왼쪽 하위 트리 출력 
    BST_InorderPrintTree( Node->Left );

    //  루트 노드 출력 
    printf( "%d ", Node->Data );

    //  오른쪽 하위 트리 출력 
    BST_InorderPrintTree( Node->Right );
}