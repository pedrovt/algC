/*
 * fibonnaci
 * Algorithms And Complexity
 * Author: Pedro Teixeira, 84715, MIECT
 */


# include <stdio.h>
# include <math.h>
# include "elapsedTime.h"

typedef unsigned long long int u64;

// Global Variables
u64    COUNT_SUMS;		// on the recursive version of the algorithm, the sum of sums can be too large to be represented using an integer
double PHI_CONSTANT = (1 + sqrt(5)) / 2;
double C1 = 1 / sqrt(5);
double C2 = 0.48121182505960344750;

// Auxiliar Methods
u64 fibRecursive (int n) {
	if (n < 2)
		return n;
	COUNT_SUMS++;
	return fibRecursive(n-1) + fibRecursive(n-2);
}

u64 fibIterative (int n) {
	if (n < 2)
		return n;

	u64 actual = 0;
	u64 anteriorAoAnterior = 0;
	u64 anterior = 1;

	for (int i = 1; i < n; i++) {
		actual   = anterior + anteriorAoAnterior;
		COUNT_SUMS++;
		anteriorAoAnterior = anterior;
		anterior = actual;
	}

	return actual;
}

u64 fibFormula1 (int n) {
	return (pow(PHI_CONSTANT, n) - pow(1-PHI_CONSTANT, n))/sqrt(5);
}

u64 fibFormula2 (int n) {
	return round(pow(PHI_CONSTANT, n)/sqrt(5));
}

u64 fibFormula3 (int n) {
	return floor(pow(PHI_CONSTANT, n)/sqrt(5) + 0.5);
}

u64 fibFormula4 (int n) {
	return round(C1 *  exp(n*C2));
}

// Runs the program
int main (void) {
	int maxValue = 100;

	/* Uncomment to test (very slow if i > 40...)
	printf("------------------\nFórmula Recursiva\n------------------\n");
	for (int i = 0; i <= maxValue; i++) {
		countSums = 0;

		elapsed_time();
		u64 value   = fibRecursive(i);
		double time = elapsed_time();

		printf("%d -> %llu (sums: %llu)\t(time: %f)\n", i, value, countSums, time);
	}
	*/

	printf("------------------\nFórmula Iterativa\n------------------\n");
	for (int i = 0; i <= maxValue; i++) {
		COUNT_SUMS = 0;

		elapsed_time();
		u64 value   = fibIterative(i);
		double time = elapsed_time();

		printf("%d -> %llu (sums: %llu)\t(time: %f)\n", i, value, COUNT_SUMS, time);
	}

	printf("------------------\nFórmula 1\n------------------\n");
	for (int i = 0; i <= maxValue; i++) {
		elapsed_time();
		u64 value   = fibFormula1(i);
		double time = elapsed_time();

		printf("%d -> %llu \t(time: %f)\n", i, value, time);
	}

	printf("------------------\nFórmula 2\n------------------\n");
	for (int i = 0; i <= maxValue; i++) {
		COUNT_SUMS = 0;

		elapsed_time();
		u64 value   = fibFormula2(i);
		double time = elapsed_time();

		printf("%d -> %llu \t(time: %f)\n", i, value, time);
	}

	printf("------------------\nFórmula 3\n------------------\n");
	for (int i = 0; i <= maxValue; i++) {
		COUNT_SUMS = 0;

		elapsed_time();
		u64 value   = fibFormula3(i);
		double time = elapsed_time();

		printf("%d -> %llu \t(time: %f)\n", i, value, time);
	}

	printf("------------------\nFórmula 4\n------------------\n");
	for (int i = 0; i <= maxValue; i++) {
		COUNT_SUMS = 0;

		elapsed_time();
		u64 value   = fibFormula4(i);
		double time = elapsed_time();

		printf("%d -> %llu \t(time: %f)\n", i, value, time);
	}

	return 0;
}
