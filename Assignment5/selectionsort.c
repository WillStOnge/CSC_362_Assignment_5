/*	Name: selectionsort.c

	Author: Will St. Onge

	Description: Selection sort algorithm. Finds the smaller number between i and the end of the array which is store in min with its index is stored in minpos. Once the current index (j) reaches the last element, it swaps the minpos-th and i-th element and increments i. Once i is equal to length - 1, the array is sorted and it will be printed out to the console.
*/
#include <stdio.h>

int main()
{
	// Array with the data that will be sorted.
	int data[] = { 8, -1, 7, -8, 6, 3, -4, 4, 1, -2, 9, -5, 0, 2};
	// Size of the array.
	int lengths = sizeof(data);
	// Loop expressions (inner and outer).
	int i, j;
	// Smallest number in the to be sorted array
	int min;
	// Index in the array for swapping.
	int minpos;

	__asm {
		mov eax, 0						; Set i equal to 0
		mov i, eax

	outer:								; Outer loop.

		mov eax, i						; Initialize the loop expression.

		mov minpos, eax					; Set minpos equal to i and min equal to the element at i.
		mov ebx, data[eax]				
		mov min, ebx

		add eax, 4						; Increment the array index by 4 (int is 4b wide).

	inner:								; Inner loop.

		mov j, eax						; Set j equal to the element after i.

		mov ebx, data[eax]				; Check if the data at j is less then that at minpos.
		mov ecx, minpos
		cmp ebx, data[ecx]
		jge outer_l						; If it is greater than or equal to, jump past the condition.

		mov min, ebx					; Move minpos and min ahead since a new smallest element was found.
		mov minpos, eax					

	outer_l:							; Swapping and continuing or stopping the loop if the sort is complete.

		add eax, 4						; Increment j.

		cmp eax, lengths				; If j is less than the length of the area, continue the loop.
		jl inner

										; Swaps elements at indices i and minpos.
		mov edx, i						; Move the index into edx, get the edx-th array element, then put the result into ebx.
		mov ebx, data[edx]

		mov edx, minpos					; Move the minpos index into edx, get the edx-th array element, then put it into ecx.
		mov ecx, data[edx]

		mov edx, i						; Move the index into edx, move ecx to the edx-th position in the array.
		mov data[edx], ecx

		mov edx, minpos					; Move the minpos index into edx, move ebx to the edx-th position in the array.
		mov data[edx], ebx

		mov edx, i						; Increment i by 1 position (integers are 4 bytes wide).
		add edx, 4
		mov i, edx

		add edx, 4						; If i + 4 is less than the length of the array, continue the loop. If not, leave the inline assembly.
		cmp edx, lengths				
		jl outer
	}


	// Print out the values of the array
	for (int n = 0; n < lengths / 4; n++)
		printf("%d ", data[n]);
}