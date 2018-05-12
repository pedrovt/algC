/*
 * Guide 9
 * Usage Examples of Stack & Queue Structures
 * Algorithms And Complexity
 * Author: Pedro Teixeira, 84715, MIECT
 */

# include <stdio.h>
# include "stack.h"
# include "queue.h"

# define size  5
# define true  1
# define false 0

int main (void) {
	// Detectar uma capicua

	char word[size];
	char *str = word;

	printf("--> ");
	fgets(word, size, stdin);
	printf("\nResult: É capicua?");

	PtStack stack = StackCreate(sizeof(char));
	PtQueue queue = QueueCreate(sizeof(char));

	if (stack && queue) {
		// push str to stack
		// enqueue str to queue
		while (*str != '\0') {
			StackPush(stack, str);
			QueueEnqueue(queue, str);
			str++;
			//printf("DEBUG");
		}

		
		// pop from stack
		// dequeue from queue
		char isCapicua = true;

		while (!StackIsEmpty(stack) && !QueueIsEmpty(queue))
		{
			char elemFromStack;
			StackPop(stack, &elemFromStack);

			char elemFromQueue;
			QueueDequeue(queue, &elemFromQueue);

			isCapicua = (elemFromStack == elemFromQueue);
			if (!isCapicua) {
				printf(" NO");
				break;
			}
		}

		if (isCapicua) {
			printf(" YES");
		}
		printf("\n");			
		
	}

	StackDestroy(&stack);
	QueueDestroy(&queue);

	return 0;
}
