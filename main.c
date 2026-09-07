#include <stdio.h>
#include "randomArrayCreator.h"
#include "node.h"

int main() {

	// generate array and fill with rdm numbers
	int array[10];
	randomArrayCreator(array, 10);

	printf("[ ");
	for (int i = 0; i < 10; i++) {
		printf("%d", array[i]);
		if (i < 9) printf(", ");
	}
	printf(" ]\n");

	return 0;

}
