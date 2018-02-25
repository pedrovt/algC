/*
 * exemplo2.c
 *
 *  Created on: Feb 20, 2018
 *      Author: Pedro
 */

# include <stdio.h>

int mainn(void) {
	char name[10];

	puts("What is your name?");

	scanf("%s", name);
	printf("Hello %s !!\n", name);

	return 0;
}


