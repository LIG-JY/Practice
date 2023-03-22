#include "stdlib.h"
#include "stdio.h"

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
/* 현재노드의 바로 앞에 삽입하는 함수 */
void DLL_InsertBefore(Node* current, Node* newnode)
{
	newnode->NextNode = current;
	newnode->PrevNode = current->PrevNode;
	
	// 중간에 삽입하는 경우
	if (current->PrevNode != NULL)
	{
		current->PrevNode->NextNode = newnode;
	}
	// 맨 앞의 경우 와 중간에 삽입하는 경우 모두
	current->PrevNode = newnode;
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

void DDL_PrintData(Node* head)
{
	while (head != NULL)
	{
		printf("Node%p, data is %d\n",head, head->Data);
		head = head->NextNode;
	}
}

void InsertionSort(Node* head, int length) 
{  
	Node* temp = NULL;
	Node* target = NULL;
    Node* key = NULL;
	int i = 0;
	int j = 0;
 
    /* 
	Node 탐색과정, value(key)를 정하는 과정, head 바로 다음(배열이라면 index 1)부터 시작 
	*/
	temp = head->NextNode;
    for (i = 1; i < length; i++)
    {
        /* value가 정렬된 상태인지 확인 */
		if ( (temp->PrevNode)->Data > temp->Data )
		{
			key = temp;
			/* 
				가장 앞 부터 비교(이미 정렬되어있다는 가정) 
				노드 탐색 과정
			*/
			target = head;
			while (1)
			{
				if (target->Data > key->Data)
				{
					/* key를 리스트로 부터 제거할 때 연결을 유지시키기 위한 코드 */
					(key->PrevNode)->NextNode = key->NextNode;
					if (key->NextNode != NULL)
					{
						(key->NextNode)->PrevNode = key->PrevNode;
					}
					/* 새로운 위치에서 연결 */
					if (target->PrevNode != NULL)
					{
						(target->PrevNode)->NextNode = key;
					}
					key->PrevNode = target->PrevNode;
					target->PrevNode = key;
					key->NextNode = target;
					break;
				}
				target = target->NextNode;
			}
		}
		/* 헤드 찾기 */
		while (head->PrevNode != NULL)
		{
			head = head->PrevNode;
		}
		/* temp 위치 조정 */
		temp = head->NextNode;
		for (j = 1; j < i; j++)
		{
			temp = temp->NextNode;
		}
    }
}
 
int main( void )
{ 
	/* 노드 생성 */
	Node* Node1 = DLL_CreateNode(6);
	Node* Node2 = DLL_CreateNode(4);
	Node* Node3 = DLL_CreateNode(2);
	Node* Node4 = DLL_CreateNode(3);
	Node* Node5 = DLL_CreateNode(1);
	Node* Node6 = DLL_CreateNode(5);

	/* 링크드 리스트 생성 */
	DLL_AppendNode(&Node1, Node2);
	DLL_AppendNode(&Node1, Node3);
	DLL_AppendNode(&Node1, Node4);
	DLL_AppendNode(&Node1, Node5);
	DLL_AppendNode(&Node1, Node6);

	printf("before--------------------------\n");
	DDL_PrintData(Node1);
	printf("after--------------------------\n");
    InsertionSort(Node1, DLL_GetNodeCount(Node1));
	DDL_PrintData(Node1);

	DLL_DestroyNode(Node1);
	DLL_DestroyNode(Node2);
	DLL_DestroyNode(Node3);
	DLL_DestroyNode(Node4);
	DLL_DestroyNode(Node5);
	DLL_DestroyNode(Node6);
	
    return 0; 
}