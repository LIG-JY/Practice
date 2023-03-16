#ifndef DLL_H
#define DLL_H

#include <stdlib.h>
#include <stdio.h>

typedef int ElementType;

typedef struct Node
{
	ElementType Data;
	struct Node* NextNode;
	struct Node* PrevNode;
} Node;

Node* DLL_CreateNode(ElementType NewData);
void DLL_DestroyNode(Node* node);
void DLL_AppendNode(Node** head, Node* node);
Node* DLL_GetNodeAt(Node** head, int location);
void DLL_RemoveNode(Node** head, Node* remove);
void DLL_InsertAfter(Node* current, Node* newnode);
int DLL_GetNodeCount(Node* head);
void PrintReverse(Node* head);

#endif
