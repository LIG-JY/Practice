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
    Stack->Top++;
    Stack->Nodes[Stack->Top].Data = Data;
}

ElementType AS_Pop(ArrayStack* Stack)
{
    int Position = Stack->Top--;
    return Stack->Nodes[Position].Data;
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
