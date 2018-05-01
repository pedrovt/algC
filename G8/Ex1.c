/*
 * Guide 8, Ex. 1
 * Algorithms And Complexity
 * Author: Pedro Teixeira, 84715, MIECT
 */

# include <stdio.h>

int NUM_MULT;

int schroder(unsigned int n) {
	if (n == 0) {
		return 1;
	}
	
	int topN = n - 1;
	int result = schroder(topN);
	for (int i = 0; i <= topN; i++) {
		result += schroder(i) * schroder(topN - i);
		NUM_MULT++;
	}
	return result;
}

void testSchroder (unsigned int n) {
	NUM_MULT = 0;
	int result = schroder(n);
	printf("i = %2d | Result = %10d | Num Mult = %d\n", n, result, NUM_MULT++);
}

int main (void) {
	printf("Recursive Version\n-----------------------------------------------------\n");
	for (int i = 0; i <= 14; i++) {

		testSchroder(i);
	}
	
}
