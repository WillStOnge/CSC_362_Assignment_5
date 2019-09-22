// Name: selectionsort.c
// Author: Will St. Onge
// Description: Selection sort algorithm implemented with x86 assembly

#include <stdio.h>

int main()
{
	int data[] = { 5, 8, 9, 4, 2, 1, 3, 6, 10, 7 };
	int lengths = 10;

	int min, minpos, i = 0, j, temp, n;

	/*
	for (i = 0; i < length - 1; i++)
	{
		min = data[i];
		minpos = i;
		for (j = i + 1; j < length; j++)
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
	*/

	__asm {
	outer:
		mov eax, i
		mov dword ptr[minpos], eax
		mov ebx, data[eax]
		mov dword ptr[min], ebx
		add eax, 1
	inner:
		mov dword ptr[j], eax
		mov ebx, data[eax]
		mov ecx, minpos
		cmp ebx, data[ecx]
		jge out1
		mov min, ebx
		mov minpos, eax
	out1:
		add eax, 1
		cmp eax, lengths
		jl inner
		mov edx, i
		mov ecx, data[edx]
		mov dword ptr[temp], ecx
		mov edx, minpos
		mov ecx, data[edx]
		mov edx, i
		mov data[edx], ecx
		mov ecx, temp
		mov edx, minpos
		mov data[edx], ecx
		mov edx, i
		add edx, 1
		mov i, edx
		cmp edx, lengths
		jl outer
	}

	for (n = 0; n < lengths; n++)
		printf("%d ", data[n]);
}