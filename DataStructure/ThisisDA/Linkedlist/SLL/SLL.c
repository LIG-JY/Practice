#include "SLL.h"

/* Node 생성 */
Node* SLL_CreateNode(ElementType NewData)
{
	Node* NewNode = (Node*)malloc(sizeof(Node));
	NewNode->Data = NewData;
	NewNode->NextNode = NULL;

	return NewNode;
}

/* Node 소멸 */
void SLL_DestroyNode(Node* NewNode)
{
	free(NewNode);
}

/* Tail Node 뒤에 새로운 노드를 만들어서 연결 */

void SLL_AppendNode(Node** Head, Node* NewNode)
{
	if (*Head == NULL)
	{
		*Head = NewNode;
	}
	else
	{
		Node* Tail = *Head;
		while (Tail -> NextNode != NULL)
		{
			Tail = Tail -> NextNode;
		}
		Tail -> NextNode = NewNode;
	}
}

/* 노드 탐색 연산 */

Node* SLL_GetNodeAt(Node* Head, int Location)
{
	Node* current = Head;

	while (current != NULL & Location > 0)
	{
		current = current -> NextNode;
		Location--;
	}
	return current;
}

/* 노드 삭제 연산 */
void SSL_RemoveNode(Node** Head, Node* Remove)
{
	if (*Head == Remove)
	{
		*Head = Remove -> NextNode;
	}
	else
	{
		Node* current = *Head;
		while (current != NULL & current->NextNode != Remove)
		{
			current = current->NextNode;
		}
		current->NextNode = Remove->NextNode; 
	}
	SLL_DestroyNode(Remove);
}

/* 노드 삽입 연산 */
void SSL_InsertAfter(Node* current, Node* NewNode)
{
	NewNode->NextNode = current->NextNode;
	current->NextNode = NewNode;
}

void SSL_InsertNewHead(Node** head, Node* NewNode)
{
	if (*head == NULL)
	{
		*head = NewNode;
	}
	else
	{
		NewNode->NextNode = *head;
		*head = NewNode;
	}
}

/* 노드 개수 세기 연산 */
int SSL_GetNodeCount(Node* Head)
{
	int count = 0;
	Node* current = Head;
	while (current != NULL)
	{
		count++;
		current = current->NextNode;
	}
	return count;
}

/* 특정 노드 앞에 새로운 노드를 삽입 */
void SSL_InsertBefore(Node** Head, Node* current, Node* NewHead)
{
	if (current == *Head)
	{
		NewHead->NextNode = current;
		*Head = NewHead;
	}
	else
	{
		Node* find = *Head;
		while (find->NextNode != current)
		{
			find = find->NextNode;
		}
		find->NextNode = NewHead;
		NewHead->NextNode = current;
	}
}
/* 리스트의 모든 노드를 한번에 제거 */
void SSL_DestroyAllNodes(Node** List)
{
	Node* current = *List;
	
	while (current != NULL)
	{
		Node* temp_ptr = current;
		current = current->NextNode;
		SLL_DestroyNode(temp_ptr);
	}
	*List = NULL;
}

