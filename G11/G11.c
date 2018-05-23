/*
 * Guide 11
 * Algorithms And Complexity
 * Author: Pedro Teixeira, 84715, MIECT
 */

# include <stdio.h>
# include "pqueue.h"

void testHeapSort(int* array, int size) {
	PtPQueue priorityQueue = PQueueCreate(size);

	// Print original array
	// Create Priority Queue
	printf("Original: \n");
	for (int i = 0; i < size; i++) {
		printf("\t %d", array[i]);
		PQueueInsert(priorityQueue, array[i]);
	}

	printf("\n\nOrdered: \n");
	int value[size];
	for (int j = size - 1; j >= 0; j--) {
		PQueueDeleteMax(priorityQueue, &value[j]);
	}

	for (int i = 0; i < size; i++) {
		printf("\t %d", value[i]);
	}

	printf("\n\n-----------------------------\n");
}

void testSelectKSmallerValues(int *array, int size, int k) {
	PtPQueue priorityQueue = PQueueCreate(k);

	// Print original array
	// Create Priority Queue
	printf("Original: \n");

	int value[k];
	for (int i = 0; i < size; i++) {
		printf("\n\nInserting %2d...", array[i]);
		if (PQueueInsert(priorityQueue, array[i]) == PQUEUE_FULL) {
			PQueueDeleteMax(priorityQueue, &value[0]);
			printf("\tInserted %d but queue is full. Deleting %d", array[i], value[0]);
		}
	}

	printf("\n\nResult (%d smaller values): \n", k);
	for (int j = k - 1; j >= 0; j--) {
		PQueueDeleteMax(priorityQueue, &value[j]);
		printf("\t %d", value[j]);
	}

	printf("\n\n-----------------------------\n");
}

int main (void) {
	int size = 6;
	int k 	 = 2;

	int seq[6] = {10, 20, 20, 3, 1, 2};
	
	testHeapSort(seq, size);
	testSelectKSmallerValues(seq, size, k);

	return 0;
}

