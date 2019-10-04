// Name: selectionsort.c
// Author: Will St. Onge
// Description: Selection sort algorithm implemented with x86 inline assembly

#include <stdio.h>

int main()
{
	int data[] = { 8, -1, 7, -8, 6, 3, -4, 4, 1, -2, 9, -5, 0, 2};
	int lengths = sizeof(data);

	int min, minpos, i = 0, j;

	__asm {
	outer:							; Outer loop 

		mov eax, i					; Initialize the loop

		mov minpos, eax				; Setup min and minpos
		mov ebx, data[eax]				
		mov min, ebx

		add eax, 4					; Increment the array index by 4 (int is 4b wide)

	inner:							; Inner loop

		mov j, eax					; Set j equal to the element after i

		mov ebx, data[eax]				; Check if the data at j is less then that at minpos
		mov ecx, minpos
		cmp ebx, data[ecx]
		jge outer_l					; If it is greater than or equal to, jump to past the condition 

		mov min, ebx					; Move minpos and min ahead since a new smallest element was found
		mov minpos, eax					

	outer_l:						; Swapping and continuing or stopping the loop if the sort is complete

		add eax, 4					; Increment j

		cmp eax, lengths				; If j is less than the length of the area, continue the loop
		jl inner

		mov edx, i					; Swap data at indices min and i
		mov ecx, data[edx]
		mov ebx, ecx
		mov edx, minpos					
		mov ecx, data[edx]
		mov edx, i
		mov data[edx], ecx
		mov ecx, ebx					
		mov edx, minpos
		mov data[edx], ecx

		mov edx, i				; Increment i by 4
		add edx, 4
		mov i, edx

		add edx, 4				; If i is less than the length of the array, continue the loop until it isn't
		cmp edx, lengths				
		jl outer
	}


	// Print out the values of the array
	for (int n = 0; n < lengths / 4; n++)
		printf("%d ", data[n]);
}


// Run 1 Output: 12 29 31 39 43 44 50 63 69 74 77 81 83 86 87 90 95 97 99 100
// Run 2 Output: -8 -5 -4 -2 -1 0 1 2 3 4 6 7 8 9