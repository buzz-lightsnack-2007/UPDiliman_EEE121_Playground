/**
 * @file oddevensel.cpp
 * @author your name (you@domain.com)
 * @version 0.1
 * 
 * Modify the insertion sort / selection such that it is "sped-up" and seperates odd and even. It may either be selection sort or insertion sort. Testcases will only involve even length arrays and won't have repeating numbers. 
 * 
 * @copyright Copyright (c) 2026
 */
#include <iostream>
using namespace std; 

/**
 * Get the lowest number. 
 * 
 * @param original (int[]): the unsorted list of items
 * @param start (int): the starting index
 * @param end (int): the ending index (excluding)
 * @param parity (int): the parity. 1 if odd, 2 if even, any other number otherwise
 * @return (int) the index of the maximum number (start ≤ return value ≤ end), or -1 if not applicable
 */
int get_maximum(int *original, int start, int end, int parity = 0) {
	// Correct any inputs
	parity = abs(parity);
	if (end < start) {int target = start; start = end; end = target; } 
	
	bool found = false; 
	int lowest[2] = {-1, 0}; // The lowest number (index, number)
	for (int index = start; index < end; index++) {
		if (((!found) ||
			(lowest[1] > original[index])) && (
				!parity ||
				(parity % 2 && original[index] % 2) ||
				(!(parity % 2) && !(original[index] % 2))
			)) {    
			lowest[0] = index; 
			lowest[1] = original[index];
			found = true; 
		};
	};

	return lowest[0];
};

/**
 * Selection sort with parity sorting. 
 * 
 * @param original (int[]): the original array
 * @param size (int): the size to sort
 * @param verbose (int)
 */
void selsortp(int *original, int size, int verbose = 1) {
	// Validate the inputs
	size = abs(size); 
	
	int sorted_sizes[2] = {0, 0}; // Determines how many odd (left) and even (right) items have already been sorted

	for (int index = 0; index < size; index++) {
		// Get greatest element in the unsorted region. 
		int largest[2] = {
			get_maximum(original, index, size, 1), // This works!
			get_maximum(original, sorted_sizes[0], size - index, 2)
		};

		// Correct the size bounds if we will be changing the sorted odd region
		if (largest[0] >= 1) {
			largest[1] = get_maximum(original, sorted_sizes[0] + 1, size - sorted_sizes[1], 2);
		};

		// Attempt swapping into the sorted region. 
		if (largest[0] >= 0) {
			swap(original[largest[0]], original[sorted_sizes[0]]);
			sorted_sizes[0]++; 
		};

		if (largest[1] >= 0) {
			swap(original[largest[1]], original[size - sorted_sizes[1] - 1]);
			sorted_sizes[1]++; 
		};

		if (verbose) {
			for (int i = 0; i < size; i++) {cout << original[i]; if (i < size - 1) {cout << ", ";} else {cout << "\t|\t";};}
			for (int i = 0; i < 2 && verbose >= 2; i++) {cout << sorted_sizes[i]; if (i < 1) {cout << ", ";} else {cout << "\t|\t";};}
			for (int i = 0; i < 2 && verbose >= 2; i++) {cout << largest[i]; if (i < 1) {cout << ", ";} else {cout << endl;};};
		};
	};
};

int main(){
	int arr1[] = {20, 7, 2, 9, 8, 6, 5, 3, 4, 33, 34, 35, 99, 124};
	selsortp(arr1, 12, true);
	cout << endl;
};