#include "CircularQueue.h"
#define ERROR 888

// 용량을 input으로 받는다. 
void  CQ_CreateQueue(CircularQueue** Queue, int Capacity)
{
    //  큐를 Heap에 생성 
    (*Queue) = (CircularQueue*)malloc(sizeof(CircularQueue));

    //  Dummy Node 포함해서 +1개의 Nodes를 생성합니다.
    (*Queue)->Nodes = (Node*)malloc(sizeof(Node)*(Capacity+1));

    (*Queue)->Capacity = Capacity;

    // Empty 상태
    (*Queue)->Front = 0;
    (*Queue)->Rear  = 0;
}

void CQ_DestroyQueue(CircularQueue* Queue)
{
    free(Queue->Nodes);
    free(Queue );
}

void CQ_Enqueue(CircularQueue* Queue, ElementType Data)
{
    if (CQ_IsFull(Queue))
    {
        printf("Queue is FULL\n");
        return ;
    }
    else
    {
        int Position=Queue->Rear;
  
        // Rear가 Capacity와 같다
        if(Queue->Rear==Queue->Capacity)
        {
            // Rear값이 Capacity 다음은 0
            Queue->Rear=0;
        }
        // Rear은 다음 data가 들어갈 위치라고 생각하면 된다. 현재 끝 Node위치에 + 1 값.
        else
            Queue->Rear++; 
        Queue->Nodes[Position].Data=Data;
    }  
}

ElementType CQ_Dequeue(CircularQueue* Queue)
{
    if (CQ_IsEmpty(Queue))
    {
        printf("Queue is EMPTY\n");
        return ERROR;
    }
    else
    {
        int Position = Queue->Front;

        if (Queue->Front == Queue->Capacity)
            Queue->Front = 0;
        else
            Queue->Front++;
        // 빈 큐 예외처리
        return Queue->Nodes[Position].Data;
    }
}

int CQ_GetSize( CircularQueue* Queue )
{
    if ( Queue->Front <= Queue->Rear )
        return Queue->Rear - Queue->Front;
    else
        return Queue->Rear + (Queue->Capacity - Queue->Front) + 1;
}

// Rear 과 Front의 값이 같으면 Empty
int CQ_IsEmpty( CircularQueue* Queue )
{
    return (Queue->Front == Queue->Rear);
}

int CQ_IsFull( CircularQueue* Queue )
{
    // 예를 들어 Front 값이 0, Rear 값이 Capacity인 경우
    if ( Queue->Front < Queue->Rear )
        return ( Queue->Rear - Queue->Front) == Queue->Capacity;
    // Rear가 Dummy위치 일 때 Rear + 1 하면 Front 이다.
    else
        return ( Queue->Rear + 1 ) == Queue->Front;
}
