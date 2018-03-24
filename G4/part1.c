/*
 * Guide 4, Part 1
 * Algorithms And Complexity
 * Author: Pedro Teixeira, 84715, MIECT
 */

/* Seja uma dada sequ�ncia (array) de n�meros inteiros ordenada por ordem n�o decrescente. Pretende-se
 * determinar se a sequ�ncia � uma sequ�ncia cont�nua de n�meros.
 *
 *
 * Implemente uma fun��o inteira eficiente (utilize um algoritmo em l�gica negativa) e eficaz que
 * determinar se a sequ�ncia � uma sequ�ncia cont�nua de n�meros.
 * verifica se uma sequ�ncia com n elementos (sendo n > 1) define uma sequ�ncia cont�nua de
 * n�meros. Considere o resultado da fun��o do tipo: 1 para verdadeiro e 0 para falso.
 * Depois de validar o algoritmo apresente-o no verso da folha
 *
 *
 * � Determine experimentalmente a ordem de complexidade do n�mero de adi��es envolvendo os
 * elementos da sequ�ncia. Considere as seguintes dez sequ�ncias de dez inteiros, todas diferentes e
 * que cobrem todas as distintas situa��es poss�veis de execu��o do algoritmo. Calcule para cada uma
 * delas se se verifica a condi��o pretendida e o n�mero de opera��es de adi��o efectuadas.
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



