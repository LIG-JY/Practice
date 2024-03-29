#include "Heap.h"

Heap* HEAP_Create( int IntitialSize )
{
    /* Heap 구조체 만들기 */
    Heap* NewHeap = (Heap*) malloc( sizeof( Heap ) );

    /* 
    Heap 구조체 초기화
    Node의 개수 = InitialSize = Capacity 만큼 malloc을 통해서 메모리 할당받는다.
    배열의 크기를 알고 그 만큼 동적으로 할당받는다. 
    */

    NewHeap->Capacity = IntitialSize;
    NewHeap->UsedSize = 0;
    NewHeap->Nodes = (HeapNode*) malloc( sizeof ( HeapNode ) * NewHeap->Capacity );

    return NewHeap;
}

void  HEAP_Destroy( Heap* H )
{
    /* 배열 초기화 */
    free( H->Nodes );
    
    /* Heap 구조체 초기화 */
    free( H );
}

void  HEAP_Insert( Heap* H, ElementType NewData )
{
    /* Current는 새로 추가할 노드의 인덱스이다. 기존에 Usedsize가 3이라면 배열의 인덱스 3에 추가된다. */
    int CurrentPosition = H->UsedSize;
    int ParentPosition  = HEAP_GetParent( CurrentPosition );

    /* 용량 찬 상태의 경우 -> CurrentPostion에 넣으려면 확장이 필요하다. */
    if ( H->UsedSize == H->Capacity ) 
    {
        if (H->Capacity == 0)
        {
            H->Capacity = 1;
            printf("용량확장 %d -> %d\n",0, H->Capacity );    
        }
        H->Capacity *= 2;
        H->Nodes = (HeapNode*)realloc( H->Nodes, sizeof( HeapNode ) * H->Capacity );
        printf("용량확장 %d -> %d\n",H->Capacity/2, H->Capacity );
    }
    /* 꽉 차던 말던 두 경우 반드시 삽입은 한다. 완전 이진 트리 유지하면서 삽입 */
    H->Nodes[CurrentPosition].Data = NewData;

    /* 
    heap의 속성(부모노드는 자식 노드보다 반드시 작은 값을 가진다.)을 유지하기 위한 후속처리 
    종료조건 1) CurrentPostion이 0인 경우 즉 Root까지 온 경우
    종료조건 2) 부모노드 보다 큰 값을 가지는 경우
    */ 
    while ( CurrentPosition > 0 && H->Nodes[CurrentPosition].Data < H->Nodes[ParentPosition].Data )     
    {
        HEAP_SwapNodes( H, CurrentPosition, ParentPosition );
        
        CurrentPosition = ParentPosition;
        ParentPosition  = HEAP_GetParent( CurrentPosition );
    }

    H->UsedSize++;
}

void      HEAP_SwapNodes( Heap* H, int Index1, int Index2 )
{ 
    int CopySize = sizeof( HeapNode );
    HeapNode* Temp = (HeapNode*)malloc(CopySize);
        
    memcpy( Temp,               &H->Nodes[Index1], CopySize);
    memcpy( &H->Nodes[Index1] , &H->Nodes[Index2], CopySize);
    memcpy( &H->Nodes[Index2] , Temp,              CopySize);

    free(Temp);
}

void      HEAP_DeleteMin( Heap* H, HeapNode* Root )
{
    int ParentPosition = 0;
    int LeftPosition   = 0;    
    int RightPosition  = 0;    
    
    /* 1. 루트를 삭제한다. */
    memcpy(Root, &H->Nodes[0], sizeof(HeapNode));
    memset(&H->Nodes[0], 0, sizeof(HeapNode));

    /* 
    Usedsize를 인덱스로 사용할 것이라 1줄이면 배열의 마지막 인덱스 
    2. 배열의 마지막 노드를 루트로 복사한다.
    */
    H->UsedSize--;
    HEAP_SwapNodes( H, 0, H->UsedSize );

    LeftPosition  = HEAP_GetLeftChild(ParentPosition);
    RightPosition = HEAP_GetRightChild(ParentPosition);

    /* 3. 힙의 속성을 만족하도록 처리한다. */
    while ( 1 )
    {   
        /* 1단계: 자식 중 최소값을 가지는 자식을 찾는다. 교환할 후보를 찾는 과정 */
        int SelectedChild = 0;

        /* 아래의 두 경우 모두 마지막 하위 트리에서 벌어지는 상황. 완전 이진 트리를 유지 */
        /* 
        마지막 하위 트리인데 parent position이 자식이 없는 경우
        LeftChild가 없는 경우, out of index 상태. RightChild도 당연히 없다. 
        */ 
        if ( LeftPosition >= H->UsedSize )
            break;
        /* 
        마지막 하위 트리에서 parent position의 왼쪽 자식만 있는 경우
        RightChild가 없는 경우. 이 배열의 마지막이 Leftchild다. 
        */
        if ( RightPosition >= H->UsedSize )
        {
            SelectedChild = LeftPosition;
        }
        /* 일반적인 경우 parent position이 2개의 자식을 가지고 있는 경우: 두 자식 중 최소 값을 가지는 자식을 찾는다.*/
        else
        {
            if ( H->Nodes[LeftPosition].Data > H->Nodes[RightPosition].Data)
                SelectedChild = RightPosition;
            else
                SelectedChild = LeftPosition;                
        }
        /* 2단계: 교환 후보 검증. 최소값을 가지는 자식과 부모를 비교해서 부모와 자식의 교환을 결정한다. */
        if ( H->Nodes[SelectedChild].Data < H->Nodes[ParentPosition].Data )
        {
            HEAP_SwapNodes(H, ParentPosition, SelectedChild);
            ParentPosition = SelectedChild;
        }
        /* 교환할 필요가 없다면 Heap의 규칙을 만족했다는 것 */
        else
            break;

        LeftPosition  = HEAP_GetLeftChild(ParentPosition);
        RightPosition = HEAP_GetRightChild(ParentPosition);
    }

    if ( H->UsedSize < ( H->Capacity / 2 ) ) 
    {
        H->Capacity /= 2;
        H->Nodes = (HeapNode*) realloc( H->Nodes, sizeof( HeapNode ) * H->Capacity );
    }
}

int HEAP_GetParent( int Index )
{
    return  (int)((Index - 1) / 2);
}

int HEAP_GetLeftChild( int Index )
{
    return (2 * Index) + 1;
}

int HEAP_GetRightChild( int Index )
{
    return (2 * Index) + 2;
}

void      HEAP_PrintNodes(Heap* H )
{
    int i = 0;
    for ( i=0; i < H->UsedSize; i++ )
    {
        printf("%d ", H->Nodes[i].Data);
    }
    printf("\n");
}
