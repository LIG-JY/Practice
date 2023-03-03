#include <stdlib.h>
#include <stdio.h>

typedef int ElementType;

typedef struct Node
{
	ElementType Data;
	struct Node* NextNode;
	struct Node* PrevNode;
} Node;

Node* DLL_CreateNode(ElementType NewData)
{
	Node* NewNode = (Node*)malloc(sizeof(Node));
	NewNode->Data = NewData;
	NewNode->NextNode = NULL;
	NewNode->PrevNode = NULL;

	return NewNode;
}

void DLL_DestroyNode(Node* node)
{
	free(node);
}

void DLL_AppendNode(Node** head, Node* node)
{
	if (*head == NULL)
	{
		*head = node;
	}
	else
	{
		Node* current = *head;
		while (current->NextNode != NULL)
		{
			current = current->NextNode;
		}
		current->NextNode = node;
		node->PrevNode = current;
	}
}

Node* DLL_GetNodeAt(Node** head, int location)
{
	Node* current = *head;
	while (current != NULL && (--location) >= 0)
	{
		current = current->NextNode;
	}
	return current;
}

void DLL_RemoveNode(Node** head, Node* remove)
{
	if (*head == remove)
	{
		*head = remove->NextNode; // head 포인터 옮기기
		remove->NextNode = NULL;
		if ((*head) != NULL)  // 총 길이가 1인경우 remove->NextNode가 NULL이다
			(*head)->PrevNode = NULL; 
	}
	else
	{
		remove->PrevNode->NextNode = remove->NextNode;
		if (remove->NextNode != NULL)  // 맨 끝의 경우 NextNode가 없다.
			remove->NextNode->PrevNode = remove->PrevNode;
		remove->NextNode = NULL;
		remove->PrevNode = NULL;
	}
}
/* 현재노드의 바로 뒤에 삽입하는 함수 */
void DLL_InsertAfter(Node* current, Node* newnode)
{
	newnode->NextNode = current->NextNode;
	newnode->PrevNode = current;
	// 중간에 삽입하는 경우
	if (current->NextNode != NULL)
	{
		current->NextNode->PrevNode = newnode;
	}
	// 맨 끝의 경우 와 중간에 삽입하는 경우 모두
	current->NextNode = newnode;
}

int DLL_GetNodeCount(Node* head)
{
	int count = 0;
	while (head != NULL)
	{
		count++;
		head = head->NextNode;
	}
	return count;
}

void PrintReverse(Node* head)
{
	Node* tail = head;
	int count = 0;
	if (tail == NULL)
		printf("There is no node");
	while(tail->NextNode != NULL)
	{
		tail = tail->NextNode;
		count++;
	}
	printf("ReverePrint start!\n");
	while(tail != NULL)
	{
		printf("List[%d] : %d\n",count, tail->Data);
		tail = tail->PrevNode;
		count--;
	}
}