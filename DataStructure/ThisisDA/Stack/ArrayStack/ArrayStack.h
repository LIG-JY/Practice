#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct tagNode
{
    ElementType Data;
} Node;

typedef struct tagArrayStack
{
    int   Capacity;
    int   Top;  // 최상위 노드 위치
    Node* Nodes; // 노드 배열
} ArrayStack;

void        AS_CreateStack(ArrayStack** Stack, int Capacity);
void        AS_DestroyStack(ArrayStack* Stack);
void        AS_Push(ArrayStack* Stack, ElementType Data);
ElementType AS_Pop(ArrayStack* Stack);
ElementType AS_Top(ArrayStack* Stack);
int         AS_GetSize(ArrayStack* Stack);
int         AS_IsEmpty(ArrayStack* Stack);
int         AS_IsFull(ArrayStack* Stack);

#endif
