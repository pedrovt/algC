/*
 * Ex2_Armstrong
 *
 *  Created on: Feb 20, 2018
 *      Author: Pedro Teixeira, 84715, MIECT
 */

#include <stdio.h>


int maindds(void) {
	int countMults = 0;

	// Pre-Calculates the cubes of the 10 different digits
	int powers[10];
	powers[0] = 0;
	powers[1] = 1;

	for (int i = 2; i <= 9; i++) {
		powers[i] = i * i * i;
		countMults += 3;
		//printf("%d\n", powers[i]);
	}

	// Determines the Armstrong numbers with 3 digits
	for (int i = 1; i <= 9; i++) {			// starts at i = 1 because only numbers with 3 digits are asked
		for (int j = 0; j <= 9; j++) {
			for (int k = 0; k <= 9; k++) {
				 int num    = i*100 + j*10 + k;
				 countMults += 2;
				 int sumCubes = powers[i] + powers[j] + powers[k];
				 if (num == sumCubes) printf("%d\n", num);
			}
		}
	}

	printf("Number of multiplications: %d", countMults);
	return 0;
}


