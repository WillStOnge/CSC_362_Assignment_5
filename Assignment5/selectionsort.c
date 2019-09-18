// Name: selectionsort.c
// Author: Will St. Onge
// Description: Selection sort algorithm implemented with x86 assembly

#include <stdio.h>

int main()
{
	int data[] = { 5, 8, 9, 4, 2, 1, 3, 6, 10, 7 };
	int length = 10;

	int min, minpos, i, j, temp, n;

	for (i = 0; i < length - 1; i++)
	{
		min = data[i];
		minpos = i;
		for (j = i + 1; j < length; i++)
		{
			if (data[j] < data[minpos])
			{
				min = data[j];
				minpos = j;
			}
		}
		temp = data[i];
		data[i] = data[minpos];
		data[minpos] = temp;
	}

	for (n = 0; n < length; n++)
		printf("%d ", data[n]);

	return 1;
}