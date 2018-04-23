/* --------------------------------
 * Aditional Tests for Seq List
 * Algorithms And Complexity
 * Author: Pedro Teixeira, 84715, MIECT
 * --------------------------------
 */

# include "seqlist.c"
# include <stdio.h>

int main (void) {
  PtSeqList list = SeqListCreate();

  // Can be changed by the user
  int NUM_ELEMS = 10;
  int NUM_ELEMENTS_TO_DELETE = 4;
  int ITEMS_TO_REMOVE[] = {9, 1, 2, 5};

  // --------------------------------------
  // Test SeqListInsert
  printf("\n--------------------------------------\nTest SeqListInsert\n");
  for (int i = 0; i < NUM_ELEMS; i++) {
    SeqListInsert(list, i);
    printf("Inserted elem %d \n", i);
  }

  // --------------------------------------
  // Test SeqListGetElement
  printf("\n--------------------------------------\nTest SeqListGetElement\n");
  for (int j = 0; j < NUM_ELEMS; j++) {
    printf("Element on Index %d: %d \n", j, SeqListGetElement (list, j));
  }

  // --------------------------------------
  // Test SeqListSetElement
  printf("\n--------------------------------------\nTest SeqListSetElement\n");
  for (int k = 0; k < NUM_ELEMS; k++) {
      printf("Setting element of index %d to %d \n", k, (NUM_ELEMS - k));
      SeqListSetElement (list, k, NUM_ELEMS - k);
  }

  for (int l = 0; l < NUM_ELEMS; l++) {
    printf("New Index %d: %d ", l, SeqListGetElement (list, l));
    if (SeqListGetElement (list, l) == NUM_ELEMS-l) printf("  : OK\n");
    else                                      printf("  : ERROR\n");
  }

  // --------------------------------------
  // Test SeqListDelete
  printf("\n--------------------------------------\nTest SeqListDelete\n");
  int l = 0;
  for (; l < NUM_ELEMENTS_TO_DELETE; l++) {
    printf("\n------------------------\nRemoving Element %d\n", ITEMS_TO_REMOVE[l]);
    printf("\nBefore Removing Element %d: \n", ITEMS_TO_REMOVE[l]);
    int size = SeqListGetSize(list);
    for (int j = 0; j < size; j++) {
      printf("Index %d: %d \n", j, SeqListGetElement (list, j));
    }

    printf("\nRemoving Element %d...", ITEMS_TO_REMOVE[l]);
    SeqListDelete(list, ITEMS_TO_REMOVE[l]);
    printf("\nResult: %s\n" , SeqListErrorMessage());
  }

  printf("\n------------------------\n");
  printf("\nAfter Removing Element %d: \n", ITEMS_TO_REMOVE[l - 1]);
  int size = SeqListGetSize(list);
  for (int j = 0; j < size; j++) {
    printf("Index %d: %d \n", j, SeqListGetElement (list, j));
  }

  return 0;
}
