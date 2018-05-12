/*
 * Guide 9
 * Usage Examples of Stack & Queue Structures
 * Algorithms And Complexity
 * Author: Pedro Teixeira, 84715, MIECT
 */

# include <stdio.h>
# include "stack.h"
# include "queue.h"

# define size 5

int main (void) {
	// Reverse a String using a Stack
	// Stack is LIFO structure...

	char word[size];
	char *str = word;

	printf("--> ");
	fgets(word, size, stdin);
	printf("\nResult: ");

	PtStack stack = StackCreate(sizeof(char));
	if (stack) {
		// push str
		while (*str != '\0') {
			StackPush(stack, str);
			//printf("DEBUG");
			str++;
		}
		// pop str & print in reverse order
		while (!StackIsEmpty(stack)) {
			char elem;
			StackPop(stack, &elem);
			printf("%c", elem);
		}			
		
		printf("\n");			
		
	}

	StackDestroy(&stack);

	return 0;
}
