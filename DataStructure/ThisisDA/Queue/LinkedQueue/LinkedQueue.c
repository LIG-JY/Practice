#include "LinkedQueue.h"

void  LQ_CreateQueue( LinkedQueue** Queue )
{
    //  큐를 자유 저장소에 생성 
    (*Queue ) = ( LinkedQueue*)malloc(sizeof( LinkedQueue ) );
    (*Queue )->Front = NULL;
    (*Queue )->Rear  = NULL;
    (*Queue )->Count = 0;
}

void LQ_DestroyQueue( LinkedQueue* Queue )
{
    while ( !LQ_IsEmpty( Queue ) )
    {
        Node* Popped = LQ_Dequeue( Queue );
        // 각 Node Dequeue 해서 Free
        LQ_DestroyNode(Popped);    
    }
    // Queue 구조체 free
    free( Queue );
}

Node* LQ_CreateNode( char* NewData )
{
    Node* NewNode = (Node*)malloc( sizeof( Node ) );
    NewNode->Data = (char*)malloc( strlen( NewData) + 1);

    //  문자열 복사 
    strcpy(NewNode->Data, NewData);  

    //  다음 노드에 대한 포인터는 NULL로 초기화한다. 
    NewNode->NextNode = NULL; 

    //  Queue 구조체의 멤버 Front, Rear의 자료형이 Node의 포인터이다. 호완을 위해
    return NewNode;
}

void  LQ_DestroyNode(Node* _Node )
{
    free(_Node->Data);
    free(_Node );
}

void LQ_Enqueue( LinkedQueue* Queue, Node* NewNode )
{
    // 큐가 빈 경우
    if ( Queue->Front == NULL ) 
    {        
        Queue->Front = NewNode;
        Queue->Rear  = NewNode;
        Queue->Count++;
    }
    else
    {
        // Queue특 Rear에 넣음
        Queue->Rear->NextNode = NewNode;
        Queue->Rear = NewNode;
        Queue->Count++;
    }
}

Node* LQ_Dequeue( LinkedQueue* Queue )
{
    if (LQ_IsEmpty(Queue) == 0)
    {
        Node* Front = Queue->Front;

        // Queue에 오직 Node가 1개 뿐일 때
        if ( Queue->Front->NextNode == NULL )
        {
            Queue->Front = NULL;
            Queue->Rear  = NULL;
        }
        else
            Queue->Front = Queue->Front->NextNode;

        Queue->Count--;
        return Front;
    }
    else
    {
        printf("This Queue is EMPTY!\n");
        return NULL;
    }
}

int LQ_IsEmpty( LinkedQueue* Queue )
{
    return ( Queue->Front == NULL);
}
