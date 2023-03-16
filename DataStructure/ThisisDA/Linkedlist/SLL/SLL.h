#ifndef SLL_H
#define SLL_H

#include <stdlib.h>
#include <stdio.h>

typedef int ElementType;

typedef struct Node
{
	ElementType Data;
	struct Node* NextNode;
} Node;

/* Node 생성 */
Node* SLL_CreateNode(ElementType NewData);
/* Node 소멸 */
void SLL_DestroyNode(Node* NewNode);
/* Tail Node 뒤에 새로운 노드를 만들어서 연결 */
void SLL_AppendNode(Node** Head, Node* NewNode);
/* 노드 탐색 연산 */
Node* SLL_GetNodeAt(Node* Head, int Location);
/* 노드 삭제 연산 */
void SSL_RemoveNode(Node** Head, Node* Remove);
/* 노드 삽입 연산 */
void SSL_InsertAfter(Node* current, Node* NewNode);
void SSL_InsertNewHead(Node** head, Node* NewHead);
/* 노드 개수 세기 연산 */
int SSL_GetNodeCount(Node* Head);
/* 특정 노드 앞에 새로운 노드를 삽입 */
void SSL_InsertBefore(Node** Head, Node* current, Node* NewHead);
/* 리스트의 모든 노드를 한번에 제거 */
void SSL_DestroyAllNodes(Node** List);


#endif







