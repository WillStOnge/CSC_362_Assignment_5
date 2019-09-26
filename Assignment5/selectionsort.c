// Name: selectionsort.c
// Author: Will St. Onge
// Description: Selection sort algorithm implemented with x86 assembly

#include <stdio.h>

int main()
{
	int data[] = { 5, 8, 9, 4, 2, 1, 3, 6, 10, 7 };
	int lengths = 40;

	int min, minpos, i = 0, j, temp;

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
	outer:								; Outer for loop (first part)
		mov eax, i						; eax = i
		mov dword ptr[minpos], eax		; minpos = i
		mov ebx, data[eax]				; min = data[i]
		mov dword ptr[min], ebx
		add eax, 4						; eax += 4

	inner:								; Inner for loop
		mov dword ptr[j], eax			; j = eax (next element in array)
		mov ebx, data[eax]				; ebx = data[j]
		mov ecx, minpos					; ecx = minpos
		cmp ebx, data[ecx]				; data[j] < data[minpos]
		jge outer_l						; if this above condition is true, skip the stuff in the if condition
		mov min, ebx					; min = data[j]
		mov minpos, eax					; minpos = j

	outer_l:							; Swapping and continuing the loop or breaking
		add eax, 4						; j++ (for loop increment)
		cmp eax, lengths				; Make sure j is less than the length of the array
		jl inner
		mov edx, i						; temp = data[i]
		mov ecx, data[edx]
		mov dword ptr[temp], ecx
		mov edx, minpos					; data[i] = data[minpos]
		mov ecx, data[edx]
		mov edx, i
		mov data[edx], ecx
		mov ecx, temp					; data[minpos] = temp
		mov edx, minpos
		mov data[edx], ecx
		mov edx, i						; i++ (for loop increment)
		add edx, 4
		mov i, edx
		cmp edx, lengths				; Make sure i is less than the length of the array
		jl outer
	}

	for (int n = 0; n < 10; n++)
		printf("%d ", data[n]);
}