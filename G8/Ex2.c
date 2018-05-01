/*
 * Guide 8, Ex. 2
 * Algorithms And Complexity
 * Author: Pedro Teixeira, 84715, MIECT
 */

# include <stdio.h>
# include <stdlib.h>
int NUM_MULT;

int schroderRec(unsigned int n) {
	if (n == 0) {
		return 1;
	}

	int topN = n - 1;
	int result = schroderRec(topN);
	for (int i = 0; i <= topN; i++) {
		result += schroderRec(i) * schroderRec(topN - i);
		NUM_MULT++;
	}
	return result;
}

int schroderIter(unsigned int n) {
	if (n == 0) {
		return 1;
	}

	int array[n+1];
	
	// Base Case
	array[0] = 1;
	
	for (int i = 1; i <= n; i++) {
		array[i] = array[i - 1];
		int sum = 0;		//value of summatory
		for (int j = 0; j <= (i - 1); j++) {
			sum += array[j] * array[i - j - 1]; 
			NUM_MULT += 1;
		}	
		array[i] += sum;
	}
	
	return array[n];
}

void testSchroderIter (unsigned int n) {
	NUM_MULT = 0;
	int result = schroderIter(n);
	printf("N = %2d | Result = %10d | Num Mult = %d\n", n, result, NUM_MULT++);
}

void testSchroderRec (unsigned int n) {
	NUM_MULT = 0;
	int result = schroderRec(n);
	printf("N = %2d | Result = %10d | Num Mult = %d\n", n, result, NUM_MULT++);
}

int main (void) {
	printf("Recursive Version\n-----------------------------------------------------\n");
	for (int i = 0; i <= 12; i++) {
		testSchroderRec(i);
	}
	
	printf("\nIterative (Dynamic Programming) Version\n-----------------------------------------------------\n");
	for (int i = 0; i <= 12; i++) {
		testSchroderIter(i);
	}
}
