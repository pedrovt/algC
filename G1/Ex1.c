/*
 * Ex1
 * Algorithms And Complexity
 * Author: Pedro Teixeira, 84715, MIECT
 */

#include <stdio.h>

int f1(int n);
int f2(int n);
int f3(int n);

int COUNT = 0;

int main(void) {

	int num, a = 0;

	do {
		printf ("Número de elementos da tabela: ");
		fflush(stdout);
		a = scanf ("%d", &num);
		scanf ("%*[^\n]");
		scanf ("%*c");
	} while (a == 0);

	printf("N=%d\n", num);

	printf("\n--------------------\nf1: \n");
	for (int i = 1; i <= num; i++) {
		COUNT = 0;
		printf("F1(%d) = %d\t\tem %d adições\n", i, f1(i), COUNT);
	}

	printf("\n--------------------\nf2: \n");
	for (int i = 1; i <= num; i++) {
		COUNT = 0;
		printf("F2(%d) = %d\t\tem %d adições\n", i, f2(i), COUNT);
	}

	printf("\n--------------------\nf3: \n");
	for (int i = 1; i <= num; i++) {
		COUNT = 0;
		printf("F3(%d) = %d\t\tem %d adições\n", i, f3(i), COUNT);
	}

	return 0;
}

int f1 (int n)
{
	int i, j, r = 0;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++) {
			r += 1;
			COUNT += 1;
		}
	return r;
}

int f2 (int n)
{
	int i, j, r = 0;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= i; j++) {
			r += 1;
			COUNT += 1;
		}
	return r;
}

int f3 (int n)
{
	int i, j, r = 0;
	for (i = 1; i <= n; i++)
		for (j = i; j <= n; j++) {
			r += j;
			COUNT += 1;
		}
	return r;
}


