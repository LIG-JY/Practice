#include <stdio.h>
#include <string.h>


int* Transpose(int arr[], int target, int length)
{
	int value;
	int i;
	int temp;

	/* 탐색 */
	value = arr[i];
	while (value != target)
	{
		i++;
		value = arr[i];
		if (i >= length)
		{
			printf("cannot find element\n");
			return NULL;
		}
	}
	/* swap */
	temp = arr[i-1];
	arr[i-1] = value;
	arr[i] = temp;

	return &(arr[i-1]);
}