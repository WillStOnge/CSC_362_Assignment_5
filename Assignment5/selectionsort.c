// Name: selectionsort.c
// Author: Will St. Onge
// Description: Selection sort algorithm implemented with x86 inline assembly

#include <stdio.h>

int main()
{
	int data[] = { 5, 8, 9, 4, 2, 1, 3, 6, 10, 7 };
	int lengths = 40;

	int min, minpos, i = 0, j, temp;

	__asm {
	outer:								; Outer for loop (first part)
		mov eax, i						; eax = i
		mov dword ptr[minpos], eax		; minpos = i
		mov ebx, data[eax]				; min = data[i]
		mov dword ptr[min], ebx
		add eax, 4						; eax += 4

	inner:								; Inner for loop
		mov dword ptr[j], eax			; j = eax (next element in array)
		mov ebx, data[eax]				; if(data[j] < data[minpos])
		mov ecx, minpos
		cmp ebx, data[ecx]
		jge outer_l						; if this above condition is true, skip the stuff in the if condition
		mov min, ebx					; min = data[j]
		mov minpos, eax					; minpos = j

	outer_l:							; Swapping and continuing or stopping the loop if the sort is complete
		add eax, 4						; j++ (for loop increment)
		cmp eax, lengths				; Make sure j is less than the length of the array
		jl inner
										; Swapping indices min and i's values
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
		add edx, 4
		cmp edx, lengths				; Make sure i is less than the length of the array
		jl outer
	}


	// Print out the values of the array
	for (int n = 0; n < lengths / 4; n++)
		printf("%d ", data[n]);
}