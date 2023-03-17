#include "ArrayStack.h"

void  AS_CreateStack(ArrayStack** Stack, int Capacity)
{
    //  스택을 자유 저장소에 생성 
    (*Stack) = (ArrayStack*)malloc(sizeof(ArrayStack));

    //  입력된 Capacity만큼의 노드를 자유 저장소에 생성 
    (*Stack)->Nodes = (Node*)malloc(sizeof(Node)*Capacity);

    //  Capacity 및 Top 초기화 
    (*Stack)->Capacity = Capacity;
    (*Stack)->Top = -1;
}

// 이중 포인터가 필요 없는 이유: stack 포인터가 가진 값을 복사해도 free할 때 문제가 되지 않는다.
void AS_DestroyStack(ArrayStack* Stack)
{
    //  노드를 Heap에서 해제 
    free(Stack->Nodes);

    //  스택을 Heap에서 해제 
    free(Stack);
}

void AS_Push(ArrayStack* Stack, ElementType Data)
{
    if (AS_IsFull(Stack)) // Stack이 Full 이라면 용량 3개 증가
    {
        // 기존의 값들 새로운 Node의 배열(Stack)에 복사
        Node* NewNodes = (Node*)malloc(sizeof(Node)*(Stack->Capacity + 3));
        for (int i = 0; i < Stack->Capacity; i++)
        {
            NewNodes[i].Data = Stack->Nodes[i].Data;
        }

        // 새로운 값 Stack에 추가
        Stack->Top++;
        NewNodes[Stack->Top].Data = Data;
        
        // 기존의 Nodes의 배열 삭제
        free(Stack->Nodes);

        // 새로운 Nodes의 배열 연결
        Stack->Nodes = NewNodes;

        // Capacity 갱신
        Stack->Capacity += 3;

        // debug
        printf("\n Capacity has increased! before: %d after : %d\n", Stack->Capacity - 3, Stack->Capacity);
    }
    else
    {
        Stack->Top++;
        Stack->Nodes[Stack->Top].Data = Data;
    }
}

ElementType AS_Pop(ArrayStack* Stack)
{
    if (Stack->Top < 0)
    {
        printf("\nthis Stack does not have node\n");
    }

    int Position = Stack->Top--;
    ElementType popped = Stack->Nodes[Position].Data;

    if (Position < (Stack->Capacity - 2))
    {
        // 기존의 값들 새로운 Node의 배열(Stack)에 복사
        Node* NewNodes = (Node*)malloc(sizeof(Node)*(Stack->Capacity - 3));
        for (int i = Stack->Top; i > -1; i--)
        {
            NewNodes[i].Data = Stack->Nodes[i].Data;
        }

        // 기존 Stack free
        free(Stack->Nodes);

        // 새로운 Stack 연결
        Stack->Nodes = NewNodes;

        // Capacity 갱신
        Stack->Capacity -= 3;

        // debug
        printf("\n Capacity has decreased! before: %d after : %d\n", Stack->Capacity + 3, Stack->Capacity);
    }
    return popped;
}

// 최상위 노드의 데이터를 제거하지 않고 반환(보여주기)
ElementType AS_Top(ArrayStack* Stack)
{
    return Stack->Nodes[Stack->Top].Data;
}

int AS_GetSize(ArrayStack* Stack)
{
    return Stack->Top+1;
}

int AS_IsEmpty(ArrayStack* Stack)
{
    return (Stack->Top == -1);
}

int AS_IsFull(ArrayStack* Stack)
{
    return (Stack->Top == (Stack->Capacity) - 1);
}
