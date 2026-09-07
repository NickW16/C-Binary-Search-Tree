#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "randomArrayCreator.h"

void randomArrayCreator(int* arr, int size) {
	static int seeded = 0;

	if (!seeded) {
		srand(time(NULL));
		seeded = 1;
	}

	for (int i = 0; i < size; i++) arr[i] = rand() % 100;
	// no need to return anything because we got the array from a pointer
}
