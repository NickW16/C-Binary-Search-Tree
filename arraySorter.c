#include <stdio.h>
#include <stdlib.h>
#include "arraySorter.h"

int compare(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}

int arraySorter(int* arr, int size) {
	if (size <= 0) return 0; // handle 0 or negative

	qsort(arr, size, sizeof(int), compare);

	int newSize = 1;
	for (int i = 1; i < size; i++) {
		if (arr[i] != arr[i-1]) {
			arr[newSize++] = arr[i];
		}
	}
	return newSize;
}
