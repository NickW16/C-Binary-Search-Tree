#include <stdio.h>
#include "randomArrayCreator.h"
#include "arraySorter.h"

int main() {

	// generate array and fill with rdm numbers
	int array[10];
	randomArrayCreator(array, 10);

	printf("Original array (10): [ ");
	for (int i = 0; i < 10; i++) {
		printf("%d", array[i]);
		if (i < 9) printf(", ");
	}
	printf(" ]\n");

	// sort and remove duplicates:
	int newSize = arraySorter(array, 10);

	// print sorted
	printf("Sorted (%d): [ ", newSize);
	for (int i = 0; i < newSize; i++) {
		printf("%d", array[i]);
		if (i < newSize - 1) printf(", ");
	}
	printf(" ]\n");

	return 0;

}
