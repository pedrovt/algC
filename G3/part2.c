/*
 * part2.c
 * Algorithms And Complexity
 * Author: Pedro Teixeira, 84715, MIECT
 */

# include <stdio.h>
# include <stdlib.h>
# include <time.h>

int SIZE = 10;
int COUNT_COMPARISONS = 0;
int ARRAY_NUM = 0;
int NUM_RANDOM_TESTS = 15;

int getIndex (int* array, int SIZE) {
	int index = -1;
	int count = 0;
	int currentCount = 0;

	for (int i = 0; i < SIZE; i++) {
		count = 0;
		for (int j = i; j > 0; j--) {
			COUNT_COMPARISONS++;
			if (array[j] < array[i]) {
				count++;
			}
		}
		if (count > currentCount) {
			currentCount = count;
			index = i;
		}
	}

	return index;
}

/*
 * Prints the array
 */
void printArray(int* array, int SIZE) {
	printf("{");
	for(int i = 0; i < SIZE - 1; i++) {
		printf("%d, ", array[i]);
	}
	printf("%d}", array[SIZE - 1]);
}

/*
 * Tests the algorithm with the given array
 */
void testArray(int* array) {
	COUNT_COMPARISONS = 0;
	int result = getIndex(array, SIZE);
	ARRAY_NUM++;
	printf("Array #%2d: Result: %d | Num of Comparisons: %d\n", ARRAY_NUM, result, COUNT_COMPARISONS);
	//printArray(array, SIZE);
	//printf("\n\n");
}

/*
 * Creates an array of SIZE random integers
 */
int* createTestArray (int SIZE) {
	int* randomArray = (int*) malloc(SIZE * sizeof(int));

	for(int i = 0; i < SIZE; i++) {
		randomArray[i] = rand();
	}
	
	//printArray(randomArray, SIZE);
	
	return randomArray;
}

/*
 * Runs the program
 */
int main(void) {
	// --------------------------------------------------------------------------
	int array1[10] = { 1, 9, 2, 8, 3, 4, 5, 3, 7, 2 };	// result should be 8
	int array2[10] = { 1, 7, 4, 6, 5, 2, 3, 2, 1, 0 };  // result should be 3
	int array3[10] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };  // result should be -1

	int array4[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };  // result should be -1
	int array5[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};  // result should be 9

	testArray(array1);
	testArray(array2);
	testArray(array3);
	testArray(array4);
	testArray(array5);

	// --------------------------------------------------------------------------
	// Test with arrays with length != 10
	SIZE = 6;
	int array6[10] = { 1, 2, 9, 4, 6, 5};  				// result should be 4
	testArray(array6);

	SIZE = 1;
	int array7[1] = { 2 };  							// result should be -1
	testArray(array7);
	
	SIZE = 10;

	// --------------------------------------------------------------------------
	// Tests with random arrays
	printf("-------------------------------\nRandom Arrays: \n");
	ARRAY_NUM = 0;
	SIZE = 0;
	srand(time(NULL));
	for (int i = 0; i < NUM_RANDOM_TESTS; i++) {
		SIZE++;
		int* array = createTestArray(SIZE);
		printf("Number of Elements = %d | ", SIZE);
		testArray(array);
	}

	// --------------------------------------------------------------------------
	exit (EXIT_SUCCESS);
}
