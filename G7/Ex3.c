/*
 * Guide 7, Ex. 3
 * Algorithms And Complexity
 * Author: Pedro Teixeira, 84715, MIECT
 */

# include <stdio.h>
# include <stdlib.h>

int NUM_MULT;

int fibonnaciRec (int N) {
	if (N < 2) return N;
	NUM_MULT += 2;
	return 3 * fibonnaciRec (N-1) + 2 * fibonnaciRec (N-2);
}

void testVerifyFibonnaciRec (int N) {
	NUM_MULT = 0;
	int result = fibonnaciRec(N);
	printf("N = %2d | Result = %9d | Num Div = %d\n", N, result, NUM_MULT);
}

/* calcular os valores de baixo para cima, ou seja, de P(0) para P(n) e 
 * utilizar um array para manter os valores entretanto calculados. 
 * Este método designa-se por programação dinâmica e reduz o tempo de cálculo à 
 * custa da utilização de mais memória para armazenar valores intermédios.
*/

int fibonnaciDynamic (int N) {
	if (N < 2) return N;
	
	int* array = malloc(sizeof(int) * N);
	if (array == NULL) return -1;
	
	array[0] = 0;
	array[1] = 1;
	
	for (int i = 2; i <= N; i++) {
		array[i] = 3 * array[i - 1] + 2 * array[i - 2];	
		NUM_MULT += 2;
	}
	
	return array[N];
}	

void testVerifyFibonnaciDynamic (int N) {
	NUM_MULT = 0;
	int result = fibonnaciDynamic(N);
	printf("N = %2d | Result = %9d | Num Div = %d\n", N, result, NUM_MULT);
}

int main (void) {
	printf("Recursive Version\n--------------------------------------------------\n");
	for (int i = 0; i <= 16; i++) {
		testVerifyFibonnaciRec(i);
	}
	
	printf("\nDynamic Version\n--------------------------------------------------\n");
	for (int i = 0; i <= 16; i++) {
		testVerifyFibonnaciDynamic(i);
	}
}
