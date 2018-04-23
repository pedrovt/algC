/*******************************************************************************
 Ficheiro de implementa��o do Tipo de Dados Abstracto SEQ_LIST (seqlist.c).
 A estrutura de dados de suporte da sequ�ncia � uma estrutura, constitu�da pelos
 campos de tipo inteiro Size para indicar o n�mero de elementos armazenados na
 sequ�ncia e os campos de tipo ponteiro para n�s de lista biligada Head e Tail,
 para representar, respectivamente, a cabe�a e a cauda da lista biligada onde
 s�o armazenados os n�meros inteiros.

 Autor : Pedro Veloso Teixeira                                   NMEC : 84715
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "seqlist.h"  /* Ficheiro de interface do TDA - ADT Interface file */

/************ Defini��o da Estrutura de Dados Interna da Sequ�ncia ************/

typedef struct binode *PtBiNode;
struct binode /* defini��o do n� da lista biligada */
{
	int Elem; /* o elemento da lista */
	PtBiNode PtPrev, PtNext; /* ponteiros para o n�s anterior e seguinte */
};

struct seqlist
{
  int Size; /* n�mero de elementos - sequence's size */
  PtBiNode Head; /* ponteiro para o in�cio da lista (cabe�a da lista) - list head */
  PtBiNode Tail; /* ponteiro para o fim da lista (cauda da lista) - list tail */
};

/*********************** Controlo Centralizado de Error ************************/

static unsigned int Error = OK;  /* inicializa��o do erro */

static char *ErrorMessages[] = {
                                 "sem erro - Without Error",
                                 "sequencia(s) inexistente(s) - Sequence(s) do not exist",
                                 "memoria esgotada - Out of memory",
                                 "indice errado - Wrong index",
                                 "elemento inexistente - Element does not exist",
                                 "sequencia vazia - Empty sequence",
                                 "sequencia cheia - Full sequence",
                                 "dimensao da sequencia errada - Wrong size",
                                 "ficheiro inexistente - File does not exist",
                                 "ponteiro nulo - Null pointer"
                               };

static char *AbnormalErrorMessage = "erro desconhecido - Unknown error";

/************** N�mero de mensagens de erro previstas no m�dulo ***************/

#define N (sizeof (ErrorMessages) / sizeof (char *))

/******************** Prot�tipos dos Subprogramas Internos ********************/

PtBiNode BiNodeCreate (int);
void BiNodeDestroy (PtBiNode *);
void DoubleListDestroy (PtBiNode *);

/*************************** Defini��o das Fun��es ****************************/

void SeqListClearError (void)
{ Error = OK; }

int SeqListError (void)
{ return Error; }

char *SeqListErrorMessage (void)
{
  if (Error < N) return ErrorMessages[Error];
  else return AbnormalErrorMessage;  /* sem mensagem de erro - no error message */
}

PtSeqList SeqListCreate ()
{
	PtSeqList list = malloc (sizeof (struct seqlist));

	if (list == NULL) {
		Error = NO_MEM;
		return NULL;
	}

	list -> Size = 0;

	list -> Head = BiNodeCreate(0);

	list -> Tail = list -> Head;

	Error = OK;
 	return list;
}

void SeqListDestroy (PtSeqList *pseq)
{
	PtSeqList pointer = *pseq;

	if (pointer == NULL) {
		Error = NO_SEQ;
		return;
	}

	PtBiNode head = pointer -> Head;
	DoubleListDestroy(&head);

	free(pointer);
	Error = OK;
	*pseq = NULL;
}

PtSeqList SeqListCopy (PtSeqList pseq)
{
  PtSeqList Copy;

  /* verifica se a sequ�ncia existe - verifies if sequence exists */
  if (pseq == NULL) { Error = NO_SEQ; return NULL; }

  /* cria��o da sequ�ncia copia nulo - creating an empty sequence */
  if ((Copy = SeqListCreate ()) == NULL) return NULL;

  /* fazer a copia da sequ�ncia - copying the components */
  for (PtBiNode Node = pseq->Head; Node != NULL; Node = Node->PtNext)
  {
    SeqListInsert (Copy, Node->Elem);
    if (Error == NO_MEM) break;
  }

  if (Error == NO_MEM) { SeqListDestroy (&Copy); return NULL; }

  Copy->Size = pseq->Size;
  Error = OK;
  return Copy;  /* devolve a sequ�ncia copia - returning the new sequence */
}

PtSeqList SeqListFileCreate (char *pfname)
{
  PtSeqList Seq; FILE *PtF; unsigned int Size, I; int Elem;

  /* abertura com validacao do ficheiro para leitura - opening the text file for reading */
  if ( (PtF = fopen (pfname, "r")) == NULL) { Error = NO_FILE; return NULL; }

  /* leitura da dimens�o da sequ�ncia e do n�mero de elementos */
  /* reading the sequence's dimension and the number of elements */
  fscanf (PtF, "%u", &Size);
  if (Size < 1) { Error = BAD_SIZE; fclose (PtF); return NULL; }

  /* cria��o da sequ�ncia vazia - creating an empty sequence */
  if ((Seq = SeqListCreate ()) == NULL) { fclose (PtF); return NULL; }

  Error = OK;
  /* leitura da sequ�ncia do ficheiro - reading the sequence's components from the text file */
  for (I = 0; I < Size; I++)
  {
    fscanf (PtF, "%d", &Elem);
    SeqListInsert (Seq, Elem);
    if (Error == NO_MEM) break;
  }

  if (Error == NO_MEM) { SeqListDestroy (&Seq); return NULL; }

  fclose (PtF);  /* fecho do ficheiro - closing the text file */
  return Seq;  /* devolve a sequ�ncia criada - returning the new sequence */
}

void SeqListStoreFile (PtSeqList pseq, char *pfname)
{
  FILE *PtF;

  /* verifica se a sequ�ncia existe - verifies if sequence exists */
  if (pseq == NULL) { Error = NO_SEQ; return ; }

  /* verifica se a sequ�ncia tem elementos - verifies if sequence has elements */
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return ; }

  /* abertura com validacao do ficheiro para escrita - opening the text file for writing */
  if ((PtF = fopen (pfname, "w")) == NULL) { Error = NO_FILE; return ; }

  /* escrita do n�mero de elementos armazenados na sequ�ncia */
  /* writing the number of elements */
  fprintf (PtF, "%u\n", pseq->Size);

  /* escrita da sequ�ncia - writing the sequence's components in the text file */
  for (PtBiNode Node = pseq->Head; Node != NULL; Node = Node->PtNext)
	fprintf (PtF, "%d\n", Node->Elem);

  Error = OK;
  fclose (PtF);  /* fecho do ficheiro - closing the text file */
}

int SeqListGetSize (PtSeqList pseq)
{
	if (pseq == NULL) {
    Error = NO_SEQ;
    return -1;
  }

  Error = OK;
  return pseq -> Size;
}

int SeqListGetElement (PtSeqList pseq, int pindex)
{
	if (pseq == NULL) {
		Error = NO_SEQ;
		return -1;
	}

	pindex = abs(pindex) + 1;
	int size = pseq -> Size;

	if (pindex > size) {
		Error = BAD_INDEX;
		return 0;
	}

	Error = OK;

	// element is in the first half of the sequence --> more effient to start the search from the beginning of the list
	int centerOfTheList = size/2;
	if(pindex < centerOfTheList) {
		PtBiNode pnode = pseq -> Head;
		for (int i = 1; i < pindex; i++) {		// recursive version is possible too
			pnode = pnode -> PtNext;
		}
		return pnode -> Elem;
	}

	// element is in the second half of the sequence --> more effient to start the search from the end of the list
	else {
		PtBiNode pnode = pseq -> Tail;
		for (int j = size; j > pindex; j--) {		// recursive version is possible too
			pnode = pnode -> PtPrev;
		}
		return pnode -> Elem;
	}

}

void SeqListSetElement (PtSeqList pseq, int pindex, int pvalue)
{
	if (pseq == NULL) {
		Error = NO_SEQ;
		return;
	}

	pindex = abs(pindex) + 1;
	int size = pseq -> Size;


	if (pindex > size) {
		Error = BAD_INDEX;
		return;
	}
	Error = OK;

	// element is in the first half of the sequence --> more effient to start the search from the beginning of the list
	int centerOfTheList = size/2;
	if(pindex < centerOfTheList) {
		PtBiNode pnode = pseq -> Head;
		for (int i = 1; i < pindex; i++) {		// recursive version is possible too
			pnode = pnode -> PtNext;
		}
		pnode -> Elem = pvalue;
		return;
	}

	// element is in the second half of the sequence --> more effient to start the search from the end of the list
	else {
		PtBiNode pnode = pseq -> Tail;
		for (int j = size; j > pindex; j--) {		// recursive version is possible too
			pnode = pnode -> PtPrev;
		}
		pnode -> Elem = pvalue;
	}
}

int SeqListEquals (PtSeqList pseq1, PtSeqList pseq2)
{
	// verify if sequences exists
  if ((pseq1 == NULL) | (pseq2 == NULL)) {
    Error = NO_SEQ;
    return -1;
  }

  if (pseq1 == pseq2) {
    return 1;
  }

	Error = OK;
	int size = pseq1 -> Size;

	// Two sequences are equal if they have the same Size and the same elements
	if (size == pseq2 -> Size) {
		for (int i = 0; i < size; i++) {
			int elem1 = SeqListGetElement (pseq1, i);
			int elem2 = SeqListGetElement (pseq2, i);
			if (elem1 != elem2) {
				return 0;
			}
		}
	}
	else {
		return 0;
	}
	return 1;
}

void SeqListInsert (PtSeqList pseq, int pvalue)
{
	//printf("Inserting %d\n", pvalue);

	if (pseq == NULL) {
		Error = NO_SEQ;
		return;
	}

	// Node not needed if the list has 0 elements. (the "CTOR" of the list
	// creates a node upon the creation of the said list)
	int size = pseq -> Size;
	if (size == 0) {
		pseq -> Head -> Elem = pvalue;
		pseq -> Size = pseq -> Size + 1;
		return;
	}

	// Create Node
	PtBiNode newNode = BiNodeCreate(pvalue);

	PtBiNode currentTail = pseq -> Tail;
	newNode -> PtPrev = currentTail;
	newNode -> PtNext = NULL;

	// Change Tail Node
	currentTail -> PtNext = newNode;

	// Change Tail of the list
	pseq -> Tail = newNode;

	// Update Size of the list
	pseq -> Size = pseq -> Size + 1;

	Error = OK;
}

void SeqListDelete (PtSeqList pseq, int pvalue)
{
	if (pseq == NULL) {
		Error = NO_SEQ;
		return;
	}

	int size = pseq -> Size;
	if (size == 0) {
		Error = SEQ_EMPTY;
		return;
	}

	//printf("\n\nREMOVE %d\n", pvalue);

	// Search Node
	PtBiNode nodeToDelete = pseq -> Head;
	for (int i = 0; i < size; i++) {		// recursive version is possible too
		//printf("%d -> %d\n", i, nodeToDelete -> Elem);
		if ((nodeToDelete -> Elem == pvalue)) {
			pseq -> Size = size - 1;			 // Update Size of the list
			Error = OK;

			// Case 1: node to remove is the first
			if (nodeToDelete == pseq -> Head) {
				//printf("REMOVE FIRST\n");

				PtBiNode oldHead = pseq -> Head;
				pseq -> Head = oldHead -> PtNext;
				//pseq -> Head -> PtPrev == NULL;

				BiNodeDestroy(&nodeToDelete);
				//printf("REMOVED FIRST\n");
				return;
			}

			// Case 2: node to remove is the last
			if (nodeToDelete == pseq -> Tail) {
				//printf("REMOVE LAST\n");

				PtBiNode oldTail = pseq -> Tail;
				pseq -> Tail = oldTail -> PtPrev;
				//pseq -> Tail -> PtNext == NULL;

				BiNodeDestroy(&nodeToDelete);
				//printf("REMOVED LAST\n");
				return;
			}

			// Case 3: node to remove is the between the first and the last
			//printf("REMOVE BETWEEN FIRST AND LAST\n");
			PtBiNode prev = nodeToDelete -> PtPrev;
			PtBiNode next = nodeToDelete -> PtNext;
			prev -> PtNext = next;
			next -> PtPrev = prev;

			BiNodeDestroy(&nodeToDelete);
			//printf("REMOVED BETWEEN FIRST AND LAST\n");
			return;
		}
		nodeToDelete = nodeToDelete -> PtNext;
	}

	Error = NO_NUMBER;
}

int SeqListIsOrdered (PtSeqList pseq)
{
	if (pseq == NULL) {
		Error = NO_SEQ;
		return -1;
	}

	int size = pseq -> Size;
	if (size < 1) {
		Error = SEQ_EMPTY;
		return -1;
	}

	for(int i = 0; i < size - 1; i++){
		if(SeqListGetElement(pseq,i) > SeqListGetElement(pseq,i+1)){
			Error = OK;
			return 0;
		}
	}

	Error = OK;
	return 1;
}

int SeqListIsEvenOdd (PtSeqList pseq)
{
	if (pseq == NULL) {
    Error = NO_SEQ;
    return -1;
  }

  int size = pseq -> Size;
  if (size < 1) {
    Error = SEQ_EMPTY;
    return -1;
  }

  int isEven = (SeqListGetElement(pseq,0) % 2 == 0);   // 1 if even, 0 if odd
  for(int i = 1; i < size; i++){
    int elementIsEven = (SeqListGetElement(pseq,i) % 2 == 0);
		if (elementIsEven == (isEven)) {
			Error = OK;
			return 0;
    }
    isEven = elementIsEven;
	}

  Error = OK;
	return 1;
}

int SeqListNumberOfMultiples (PtSeqList pseq, int pvalue)
{
	if (pseq == NULL) {
		Error = NO_SEQ;
		return -1;
	}

	int size = pseq -> Size;
	if (size < 1) {
		Error = SEQ_EMPTY;
		return -1;
	}

	int count = 0;
	for(int i = 0; i < size - 1; i++){
		if(SeqListGetElement(pseq,i) % pvalue == 0){
			count++;
		}
	}

	Error = OK;
	return count;
}

void SeqListSmallerBigger (PtSeqList pseq, int * psmall, int * pbig)
{
	if (pseq == NULL) {
		Error = NO_SEQ;
		return;
	}

	int size = pseq -> Size;
	if (size < 1) {
		Error = SEQ_EMPTY;
		return;
	}

	*psmall = SeqListGetElement(pseq,0);
	*pbig   = SeqListGetElement(pseq,0);
	for(int i = 1; i< size; i++){
		int elem = SeqListGetElement(pseq,i);
		if(*psmall > elem)
			*psmall = elem;
		if(*pbig < elem)
			*pbig = elem;
	}

	Error = OK;
}

int SeqListIsPalindromic (PtSeqList pseq)
{
	if (pseq == NULL) {
    Error = NO_SEQ;
    return -1;
  }

  int size = pseq -> Size;
  if (size < 1) {
    Error = SEQ_EMPTY;
    return -1;
  }

  int i, j;
	if(size % 2 == 0) {    //sequencia com numero par de elementos
		i = (size - 1)/2;
		j = size/2;
	}
	else {                 //sequencia com numero impar de elementos
		i = size/2;
		j = size/2;
	}

	while(j < size){
		if(SeqListGetElement(pseq,i) != SeqListGetElement(pseq,j)){
			Error = OK;
			return 0;
		}
		i--;
		j++;
	}

	Error = OK;
  return 1;
}

double SeqListAverage (PtSeqList pseq)
{
	if (pseq == NULL) {
    Error = NO_SEQ;
    return -1;
  }

  int size = pseq -> Size;
  if (size < 1) {
    Error = SEQ_EMPTY;
    return -1;
  }

  int sum;
  for(int i = 0; i < size; i++){
		sum += SeqListGetElement(pseq,i);
	}

  Error = OK;
  return sum / size;
}

/*******************************************************************************
 Fun��o auxiliar para criar um n� da lista biligada. Valores de erro: OK ou NO_MEM.

 Auxiliary function to create a binode. Error codes: OK or NO_MEM.
*******************************************************************************/

PtBiNode BiNodeCreate (int pelem)	/* aloca��o do n� */
{
	PtBiNode Node;

	if ((Node = (PtBiNode) malloc (sizeof (struct binode))) == NULL)
	{ Error = NO_MEM; return NULL; }

	Node->Elem = pelem;	/* copiar a informa��o */
	Node->PtPrev = NULL;	/* apontar para detr�s para NULL */
	Node->PtNext = NULL;	/* apontar para a frente para NULL */

	Error = OK;
	return Node;
}

/*******************************************************************************
 Fun��o auxiliar para libertar um n� da lista biligada. Valores de erro: OK ou NULL_PTR.

 Auxiliary function to free a binode. Error codes: OK or NULL_PTR.
*******************************************************************************/
void BiNodeDestroy (PtBiNode *pnode)	/* liberta��o do n� */
{
	if (*pnode == NULL) { Error = NULL_PTR; return; }
	free (*pnode);	/* liberta��o do n� */
	*pnode = NULL;	/* colocar o ponteiro a nulo */
	Error = OK;
}

/*******************************************************************************
 Fun��o auxiliar para destruir uma lista biligada. Valores de erro: OK ou NULL_PTR.

 Auxiliary function to destroy a double link list. Error codes: OK or NULL_PTR.
*******************************************************************************/
void DoubleListDestroy (PtBiNode *phead)
{
	PtBiNode TmpHead = *phead; PtBiNode Node;

	if (TmpHead == NULL) { Error = NULL_PTR; return; }
	while (TmpHead != NULL)
	{
		Node = TmpHead; TmpHead = TmpHead->PtNext;
		BiNodeDestroy (&Node);
	}
	Error = OK;
}
