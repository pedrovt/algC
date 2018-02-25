/*
 * Ex3_Factorioes
 *
 *  Created on: Feb 20, 2018
 *      Author: Pedro Teixeira, 84715, MIECT
 */

# include <stdio.h>


int main(void) {
	int countMults = 0;

	// Pre-Calculates the factorials of the 10 different digits
	int factorials[10];
	factorials[0] = 1;

	for (int i = 1; i <= 9; i++) {
		factorials[i] = factorials[i-1] * i;
		countMults += 1;
		//printf("%d! = %d\n", i, factorials[i]);
	}

	// Determines the "factorioes"
	for (int i = 0; i <= 1; i++) {
		for (int j = 0; j <= 9; j++) {
			for (int k = 0; k <= 9; k++) {
				//printf("Loop info: %d %d %d\n",i ,j ,k);
				//printf("Factorial: %d %d %d\n",factorials[i] ,factorials[j] ,factorials[k]);
				int num    = i*100 + j*10 + k;
				countMults += 2;

				int sumFactorials = 0;
				if (i != 0) sumFactorials = factorials[i] + factorials[j] + factorials[k];
				else if (j != 0) sumFactorials = factorials[j] + factorials[k];
				else sumFactorials = factorials[k];

				//printf("Conclusions: %d <=> %d : %d\n\n", num, sumFactorials, num == sumFactorials);
				if (num == sumFactorials) printf("%d\n", num);

				if (num == 105) {
					printf("Number of multiplications: %d", countMults);
					return 0;
				}
			}
		}
	}


}
