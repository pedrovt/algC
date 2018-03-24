/*
 * Guide 4, Part 2
 * Algorithms And Complexity
 * Author: Pedro Teixeira, 84715, MIECT
 */


# include <stdio.h>
# include <stdlib.h>
# include <time.h>

int SIZE = 10;
int ARRAY_NUM = 0;

int COUNT_COPIES = 0;
int COUNT_COMPARISONS = 0;

void deleteRepeatedElems (int* array, int* N) {
	 if (*N < 2) return;
	 
	 for(int i = 0; i < *N; i++) {
	 	for (int j = i + 1; j < *N; j++) { 
	 		 COUNT_COMPARISONS++;
	 		 
	 		 // Repeated elements
			 if (array[i] == array[j]) {
				 
				 // Push elements	
				 for (int k = j; k < (*N) - 1; k++) {
				 	array[k] = array[k + 1];
	 			 	COUNT_COPIES++;
				 }
				 
				 // Go back (element in j position is now untested)
				 j--;		
				 
				 // Decrease number of elements
				 (*N)--;		 
				 
			 }
		 }
	 }
}

/*
 * Prints the array
 */
void printArray(int* array, int N) {
	printf("{");
	for(int i = 0; i < N - 1; i++) {
		printf("%d, ", array[i]);
	}
	printf("%d}", array[N - 1]);
}

/*
 * Tests the algorithm with the given array
 */
void testArray(int* array) {
	COUNT_COMPARISONS = 0;
	COUNT_COPIES  	  = 0;
 	int N = SIZE;
 	
    ARRAY_NUM++;
	printf("Array #%2d      : ", ARRAY_NUM);
	printArray(array, N);	

	deleteRepeatedElems(array, &N);
	printf("\n-> Result      : ");
	printArray(array, N);
	
	printf("\n-> Comparisons : %d", COUNT_COMPARISONS);
	printf("\n-> Copies      : %d\n\n", COUNT_COPIES);
	
}

/*
 * Runs the program
 */
int main(void) {
	// -----------------------------------------------------------------------------------------------------
	int array1[10] = { 1, 2, 2, 2, 3, 3, 4, 5, 8, 8 };	// result should be { 1, 2, 3, 4, 5, 8 }
	int array2[10] = { 1, 2, 2, 2, 3, 3, 3, 3, 8, 8 };  // result should be { 1, 2, 3, 8 }
	int array3[10] = { 1, 2, 5, 4, 7, 0, 3, 9, 6, 8 };  // result should be { 1, 2, 5, 4, 7, 0, 3, 9, 6, 8 }
	int array4[10] = { 1, 2, 2, 3, 2, 2, 3, 9, 6, 8 };	// result should be { 1, 2, 3, 9, 6, 8 }
	int array5[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };	// result should be { 1 }
	int array6[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };	// result should be { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 }
	int array7[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };	// result should be { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 }
	int array8[10] = { 1, 1, 3, 2, 4, 3, 2, 2, 5, 3 };	// result should be { 1, 3, 2, 4, 5}
	
	testArray(array1);
	testArray(array2);
	testArray(array3);
	testArray(array4);
	testArray(array5);
	testArray(array6);
	testArray(array7);
	testArray(array8);
	
	exit (EXIT_SUCCESS);
}
