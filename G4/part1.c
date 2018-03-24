/*
 * Guide 4, Part 1
 * Algorithms And Complexity
 * Author: Pedro Teixeira, 84715, MIECT
 */

/* Seja uma dada sequência (array) de números inteiros ordenada por ordem não decrescente. Pretende-se
 * determinar se a sequência é uma sequência contínua de números.
 *
 *
 * Implemente uma função inteira eficiente (utilize um algoritmo em lógica negativa) e eficaz que
 * determinar se a sequência é uma sequência contínua de números.
 * verifica se uma sequência com n elementos (sendo n > 1) define uma sequência contínua de
 * números. Considere o resultado da função do tipo: 1 para verdadeiro e 0 para falso.
 * Depois de validar o algoritmo apresente-o no verso da folha
 *
 *
 * • Determine experimentalmente a ordem de complexidade do número de adições envolvendo os
 * elementos da sequência. Considere as seguintes dez sequências de dez inteiros, todas diferentes e
 * que cobrem todas as distintas situações possíveis de execução do algoritmo. Calcule para cada uma
 * delas se se verifica a condição pretendida e o número de operações de adição efectuadas.
*/

# include <stdio.h>			
# include <stdlib.h>
# define TRUE 1
# define FALSE 0

int size = 10;
int COUNT_OPERATIONS = 0;
int ARRAY_NUM = 0;

int isContinuous(int* array, int size) {
	if (size < 2) {
	   return FALSE;
    }	
	   
	for (int i = 1; i < size; i++) {
		COUNT_OPERATIONS++;
        if (array[i] - array[i-1] != 1) {		// negative logic
           return FALSE;	
		}
	}

	return TRUE;
}

void testArray(int* array) {
	COUNT_OPERATIONS = 0;	
	int result = isContinuous(array, size);
	ARRAY_NUM++;	
	printf("Array #%2d: Result: %d | Num of Comparisons: %d\n", ARRAY_NUM, result, COUNT_OPERATIONS);
	
}

int main(void) {
	
	int array1[10]  = {1,3,4,5,5,6,7,7,8,9};
	int array2[10]  = {1,2,4,5,5,6,7,8,8,9};
	int array3[10]  = {1,2,3,6,8,8,8,9,9,9};
	int array4[10]  = {1,2,3,4,6,7,7,8,8,9};
	int array5[10]  = {1,2,3,4,5,7,7,8,8,9};
	int array6[10]  = {1,2,3,4,5,6,8,8,9,9};
	int array7[10]  = {1,2,3,4,5,6,7,9,9,9};
	int array8[10]  = {1,2,3,4,5,6,7,8,8,9};
	int array9[10]  = {1,2,3,4,5,6,7,8,9,9};
	int array10[10] = {1,2,3,4,5,6,7,8,9,10};
	
	
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



