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
	// Smallest number in the to be sorted array and its index in the array.
	int min, minpos;

	__asm {
		mov eax, 0						// Initialize the loop expression to 0 to start the loop.
		mov i, eax
	outer:								
		mov eax, i						// Move the loop expression into eax so we can cmp and add.
		mov minpos, eax					// Set minpos equal to i and min equal to the element at i so we have base values for the inner loop.
		mov ebx, data[eax]				
		mov min, ebx
		add eax, 4						// Increment the array index by 4 (ints are 4 bytes wide) to go to the next integer.
	inner:							
		mov j, eax						// Set j equal to the element after i.
		mov ebx, data[eax]				// Check if the data at j is less then that at minpos to see if we need to modify min and minpos.
		mov ecx, minpos
		cmp ebx, data[ecx]
		jge outer_l						// If the above statement is greater than or equal to, jump past the condition since the next number is not smaller than min.
		mov min, ebx					// Move minpos and min ahead since a new smallest element was found.
		mov minpos, eax					
	outer_l:							
		add eax, 4						// Increment j so we can test the next element.
		cmp eax, lengths				// If j is less than the length of the area, continue the loop.
		jl inner			
		mov edx, i						// Swaps elements at indices i and minpos. Since minpos contains the current smaller element in the range and i is the first unsort element. Uses ecx as a temp variable for the swap.
		mov ebx, data[edx]
		mov edx, minpos					
		mov ecx, data[edx]
		mov edx, i						
		mov data[edx], ecx
		mov edx, minpos				
		mov data[edx], ebx
		mov edx, i						// Increment i by 1 position (integers are 4 bytes wide).
		add edx, 4
		mov i, edx
		add edx, 4						// If i + 4 is less than the length of the array, continue the loop since were still inside of the array.
		cmp edx, lengths				
		jl outer
	}
	// Print out the values of the sorted array.
	for (int n = 0; n < lengths / 4; n++)
		printf("%d ", data[n]);
}