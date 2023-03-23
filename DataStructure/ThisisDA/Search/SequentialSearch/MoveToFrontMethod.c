#include <stdio.h>
#include <string.h>

int* Array_MoveToFront(int arr[], int Target, int lenght)
{
	int value = 0;
	int i = 0;

	value = arr[i];
	while (value != Target)
	{
		i++;
		value = arr[i];
		if (i >= lenght)
		{
			printf("cannot find element\n");
			return NULL;
		}	
	}
	if (i > 0)
	{
		memmove(&arr[1], &arr[0], sizeof(arr[0]) * i);
	}
	arr[0] = Target;
	return (&arr[0]);
}