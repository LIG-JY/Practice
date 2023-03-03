#include "SLL.h"

int main(void)
{
	Node* NewNode = NULL;
	Node* List = NULL;
	Node* current = NULL;
	Node* NewHead = SLL_CreateNode(11);
	Node* target = NULL;

	int count = 0;

	for (int i = 0; i<5 ; i++)
	{
		NewNode = SLL_CreateNode(i);
		SLL_AppendNode(&List, NewNode);
	}

	current = SLL_GetNodeAt(List, 3);
	SSL_InsertBefore(&List, current, NewHead);
	count = SSL_GetNodeCount(List);

	for (int j = 0; j < count; j++)
	{
		target = SLL_GetNodeAt(List, j);
		printf("List[%d} : %d\n", j, target->Data);
	}

	SSL_DestroyAllNodes(&List);

	if (!List)
		printf("clear\n");

}