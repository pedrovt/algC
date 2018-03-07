/*
 * part1.c
 * Algorithms And Complexity
 * Author: Pedro Teixeira, 84715, MIECT
 */

# include <stdio.h>			
# include <stdlib.h>

int size = 10;
int COUNT_COMPARISONS = 0;
int ARRAY_NUM = 0;

int countOcurrences(int* array, int size) {
	int count = 0;

	for (int i = 1; i < size; i++) {
		COUNT_COMPARISONS++;
		if(array[i] != array[i-1]) {
			count++;
		}
	}

	return count;
}

void testArray(int* array) {
	COUNT_COMPARISONS = 0;	
	int result = countOcurrences(array, size);
	ARRAY_NUM++;	
	printf("Array #%2d: Result: %d | Num of Comparisons: %d\n", ARRAY_NUM, result, COUNT_COMPARISONS);
	
}

int main(void) {
	
	int array1[10] = {3,3,3,3,3,3,3,3,3,3};
	int array2[10] = {4,3,3,3,3,3,3,3,3,3};
	int array3[10] = {4,5,3,3,3,3,3,3,3,3};
	int array4[10] = {4,5,1,3,3,3,3,3,3,3};
	int array5[10] = {4,5,1,2,3,3,3,3,3,3};
	int array6[10] = {4,5,1,2,6,3,3,3,3,3};
	int array7[10] = {4,5,1,2,6,8,3,3,3,3};
	int array8[10] = {4,5,1,2,6,8,7,3,3,3};
	int array9[10] = {4,5,1,2,6,8,7,9,3,3};
	int array10[10] = {4,5,1,2,6,8,7,9,3,0};

	testArray(array1);
	testArray(array2);
	testArray(array3);
	testArray(array4);
	testArray(array5);
	testArray(array6);
	testArray(array7);
	testArray(array8);
	testArray(array9);
	testArray(array10);
	
    exit (EXIT_SUCCESS);
}



