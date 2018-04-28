/*
 * Guide 7, Ex. 2
 * Algorithms And Complexity
 * Author: Pedro Teixeira, 84715, MIECT
 */

# include <stdio.h>

int NUM_DIV;

int verifyPower (int a, int b) {
	//a múltiplo de b? ou quociente da divisão inteira de a por b potencia de b?
	if ((a == b) | (a == 1)) return 1; 
	if ((a % b) != 0) 		 return 0;
	
	NUM_DIV++;
	return verifyPower(a/b, b);
}

void testVerifyPower (int x, unsigned int N) {
	NUM_DIV = 0;
	int result = verifyPower(x, N);
	if (result) printf("i = %6d | Result = YES | Num Div = %d\n", x, NUM_DIV);
	else		printf("i = %6d | Result = NO  | Num Div = %d\n", x, NUM_DIV);
}

int main (void) {
	printf("\nb = 2\n--------------------------------------------------\n");
	for (int i = 1; i <= 1024; i*= 2) {
		testVerifyPower(i, 2);				// Result should be YES
		testVerifyPower(i + 1, 2);			// Result should be NO
	}
	
	printf("\nb = 10\n--------------------------------------------------\n");
	for (int i = 1; i <= 10000; i*= 10) {	
		testVerifyPower(i, 10);				// Result should be YES
		testVerifyPower(i + 1, 10);			// Result should be NO
	}
 	
	testVerifyPower(50, 10);
}
