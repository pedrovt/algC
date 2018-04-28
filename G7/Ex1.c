/*
 * Guide 7, Ex. 1
 * Algorithms And Complexity
 * Author: Pedro Teixeira, 84715, MIECT
 */

# include <stdio.h>

int NUM_MULT;

double powerN_v1 (double x, unsigned int N) {
	if (N == 0) return 1;
	NUM_MULT++;
	return x * powerN_v1 (x, N - 1);
}

void testPowerN_v1 (double x, unsigned int N) {
	NUM_MULT = 0;
	double result = powerN_v1(x, N);
	printf("N = %2d | Result v1 = %f | Num Mult v1 = %d\n", N, result, NUM_MULT);
	//printf("%f\n", result);
	//printf("%d\n", NUM_MULT);
}

double powerN_v2 (double x, unsigned int N) {
	if (N == 0) return 1;
	
	double value 	  = powerN_v2(x, N/2);
	double valueValue = value * value;
 	NUM_MULT++;
 	
	if (N % 2 == 0) 
 	return valueValue;
	
	//else
	NUM_MULT++;
	return x * valueValue;
}

void testPowerN_v2 (double x, unsigned int N) {
	NUM_MULT = 0;
	double result = powerN_v2(x, N);
	printf("N = %2d | Result v2 = %f | Num Mult v2 = %d\n", N, result, NUM_MULT);
	//printf("%f\n", result);
	//printf("%d\n", NUM_MULT);
}

int main (void) {
	double x = 0.5;
	int N_MAX = 16;
	printf("Value of the Power Of N of the number %f\nV1\n--------------------------------------------------\n", x);
	for (int i = 0; i <= N_MAX; i++) {
		testPowerN_v1(x, i);
	}
	
	printf("\nV2\n--------------------------------------------------\n");
	for (int i = 0; i <= N_MAX; i++) {
		testPowerN_v2(x, i);
	}
	
}
