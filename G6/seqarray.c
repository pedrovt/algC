/*******************************************************************************
 Ficheiro de implementa��o do Tipo de Dados Abstracto SEQ_ARRAY (seqarray.c).
 A estrutura de dados de suporte da sequ�ncia � um registo, constitu�da pelos
 campos de tipo inteiro Dim para indicar a capacidade de armazenamento da
 sequ�ncia e Size para indicar o n�mero de elementos efectivamente armazenados na
 sequ�ncia e o campo de tipo ponteiro Seq, para representar a sequ�ncia (pseq)
 atribu�da dinamicamente onde s�o armazenados os n�meros inteiros.

 Autor : Pedro Veloso Teixeira                                  NMEC : 84715
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "seqarray.h"  /* Ficheiro de interface do TDA - ADT Interface file */

/************ Defini��o da Estrutura de Dados Interna da Sequ�ncia ************/

struct seqarray
{
  unsigned int Dim; /* capacidade de armazenamento - pseq's size */
  int Size; /* n�mero de elementos - sequence's size */
  int *Seq; /* ponteiro para armazenar a sequencia - pseq to store the numbers */
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
                                 "ficheiro inexistente - File does not exist"
                               };

static char *AbnormalErrorMessage = "erro desconhecido - Unknown error";

/************** N�mero de mensagens de erro previstas no m�dulo ***************/

#define N (sizeof (ErrorMessages) / sizeof (char *))

/*************************** Defini��o das Fun��es ****************************/

void SeqArrayClearError (void)
{ Error = OK; }

int SeqArrayError (void)
{ return Error; }

char *SeqArrayErrorMessage (void)
{
  if (Error < N) return ErrorMessages[Error];
  else return AbnormalErrorMessage;  /* sem mensagem de erro - no error message */
}

PtSeqArray SeqArrayCreate (unsigned int pdim)
{
  // Verify if argument is valid
  if (pdim == 0) {
    Error = BAD_SIZE;
    return NULL;
  }

  PtSeqArray pseq = malloc(sizeof (struct seqarray));

  // Error: no available memory
  if (pseq == NULL) {
    Error = NO_MEM;
    return NULL;
  }

  // Available Memory -> Create the pseq
  pseq -> Dim  = pdim;
  pseq -> Size = 0;
  pseq -> Seq  = malloc(sizeof (int) * pdim);

  if (pseq -> Seq == NULL) {
    Error = NO_MEM;
    free(pseq);
    return NULL;
  }

  Error = OK;
  return pseq;
}

void SeqArrayDestroy (PtSeqArray *pseq)
{
  PtSeqArray pointer = *pseq;

  if (pointer == NULL) {
    Error = NO_SEQ;
    return;
  }

  free(pointer);
  Error = OK;
  *pseq = NULL;
}

PtSeqArray SeqArrayCopy (PtSeqArray pseq)
{
  PtSeqArray Copy; int I;

  /* verifica se a sequ�ncia existe - verifies if sequence exists */
  if (pseq == NULL) { Error = NO_SEQ; return NULL; }

  /* cria��o da sequ�ncia copia vazia - creating an empty sequence */
  if ((Copy = SeqArrayCreate (pseq->Dim)) == NULL) return NULL;

  /* fazer a copia dos elementos da sequ�ncia - copying the components */
  for (I = 0; I < pseq->Size; I++) Copy->Seq[I] = pseq->Seq[I];
  Copy->Size = pseq->Size;

  return Copy;  /* devolve a sequ�ncia copia - returning the new sequence */
}

PtSeqArray SeqArrayFileCreate (char *pfname)
{
  PtSeqArray Seq; FILE *PtF; unsigned int Dim, Size, I;

  /* abertura com validacao do ficheiro para leitura - opening the text file for reading */
  if ( (PtF = fopen (pfname, "r")) == NULL) { Error = NO_FILE; return NULL; }

  /* leitura da dimens�o da sequ�ncia e do n�mero de elementos armazenados */
  /* reading the sequence's dimension and the number of elements */
  fscanf (PtF, "%u %u", &Dim, &Size);
  if (Dim < 1) { Error = BAD_SIZE; fclose (PtF); return NULL; }

  /* cria��o da sequ�ncia com a dimens�o pretendida - creating the sequence */
  if ((Seq = SeqArrayCreate (Dim)) == NULL) { fclose (PtF); return NULL; }

  /* leitura da sequ�ncia do ficheiro - reading the sequence's components from the text file */
  for (I = 0; I < Size; I++) fscanf (PtF, "%d", Seq->Seq+I);
  Seq->Size = Size;

  fclose (PtF);  /* fecho do ficheiro - closing the text file */
  Error = OK;
  return Seq;  /* devolve a sequ�ncia criada - returning the new sequence */
}

void SeqArrayStoreFile (PtSeqArray pseq, char *pfname)
{
  FILE *PtF; unsigned int I;

  /* verifica se a sequ�ncia existe - verifies if sequence exists */
  if (pseq == NULL) { Error = NO_SEQ; return ; }

  /* verifica se a sequ�ncia tem elementos - verifies if sequence has elements */
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return ; }

  /* abertura com validacao do ficheiro para escrita - opening the text file for writing */
  if ((PtF = fopen (pfname, "w")) == NULL) { Error = NO_FILE; return ; }

  /* escrita da dimens�o da sequ�ncia e do n�mero de elementos armazenados na sequ�ncia */
  /* writing the sequence's dimension and the number of elements */
  fprintf (PtF, "%u %u\n", pseq->Dim, pseq->Size);

  /* escrita da sequ�ncia - writing the sequence's components in the text file */
  for (I = 0; I < pseq->Size; I++) fprintf (PtF, "%d\n", pseq->Seq[I]);

  Error = OK;
  fclose (PtF);  /* fecho do ficheiro - closing the text file */
}

int  SeqArrayGetDimension (PtSeqArray pseq)
{
  if (pseq == NULL) {
    Error = NO_SEQ;
    return -1;
  }
  Error = OK;
  return pseq -> Dim;
}

int SeqArrayGetSize (PtSeqArray pseq)
{
  if (pseq == NULL) {
    Error = NO_SEQ;
    return -1;
  }

  Error = OK;
  return pseq -> Size;
}

int SeqArrayGetElement (PtSeqArray pseq, int pindex)
{
  if (pseq == NULL) {
    Error = NO_SEQ;
    return -1;
  }

  int size = pseq -> Size;

  /* a more elegant solution would be using a function
   * to compute the absolute value of the pindex
   * (alternative implemented on the seqlist) */
  if ((pindex <= -1) && (pindex >= -size)) {
    Error = OK;
    return pseq -> Seq[(pindex * -1)];
  }

  else if ((pindex >= 0) && (pindex <= size)) {
    Error = OK;
    return pseq -> Seq[pindex];
  }

  //else
  Error = BAD_INDEX;
  return -1;
}

void SeqArraySetElement (PtSeqArray pseq, int pindex, int pvalue)
{
  if (pseq == NULL) {
    Error = NO_SEQ;
    return;
  }

  int size = pseq -> Size;

  if ((pindex <= -1) && (pindex >= -size)) {
    Error = OK;
    pseq -> Seq[(pindex * -1) - 1] = pvalue;
    return;
  }

  else if ((pindex >= 0) && (pindex < size)) {
    Error = OK;
    pseq -> Seq[pindex - 1] = pvalue;
    return;
  }

  Error = BAD_INDEX;
}

int SeqArrayEquals (PtSeqArray pseq1, PtSeqArray pseq2)
{
  // verify if sequences exists
  if ((pseq1 == NULL) | (pseq2 == NULL)) {
    Error = NO_SEQ;
    return -1;
  }

  if (pseq1 == pseq2) {
    return 1;
  }

  // Two sequences are equal if they have the same Dim, same Size and same Seq
  if (pseq1 -> Dim == pseq2 -> Dim) {
    if (pseq1 -> Size == pseq2 -> Size) {
      int* seq1 = pseq1 -> Seq;
      int* seq2 = pseq2 -> Seq;
      if (seq1 == seq2) {
        return 1;
      }
      int i = 0;
      int size = pseq1 -> Size;
      for (i = 0; i < size; i++) {
        if (seq1[i] != seq2[i]) {
          return 0;
        }
      }
      return 1;
    }
    return 0;
  }
  return 0;
}

void SeqArrayInsert (PtSeqArray pseq, int pvalue)
{
  if(pseq == NULL){
    Error = NO_SEQ;
    return;
  }

  int size = pseq -> Size;
  if (size == (pseq -> Dim)) {
    Error = SEQ_FULL;
    return;
  }

  pseq -> Seq[size] = pvalue;
  pseq -> Size = size + 1;
  Error = OK;
}

void SeqArrayDelete (PtSeqArray pseq, int pvalue)
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

  int* array = pseq -> Seq;
  for (int i = 0; i < size; i++) {
    //printf("pvalue = %d, array[%d] = %d", pvalue, i, pseq -> Seq[i]);
    if (array[i] == pvalue) {
      // remove the first occurrence of the element
      for (int j = i; j < size - 1; j++) {
        array[j] = array[j + 1];
      }
      array[size - 1] = 0;    // "NULL" value
      pseq -> Size = size--;
      Error = OK;
      return;
    }
  }

  Error = NO_NUMBER;
}

void SeqArrayDuplicate (PtSeqArray pseq)
{
  int *newSeq;
  /* verifica se a sequ�ncia existe - verifies if sequence exists */
  if (pseq == NULL) { Error = NO_SEQ; return; }

  /* verifica se a sequ�ncia n�o est� vazia - verifies if sequence is not empty */
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return; }

  if ((newSeq = calloc (2*pseq->Size, sizeof (int))) == NULL)
  { Error = NO_MEM; return; }

  pseq->Dim = 2*pseq->Size;  /* armazenamento da nova dimens�o - storing the new dimension */

  /* copiar os elementos - copying the elements */
  for (int I = 0; I < pseq->Size; I++) newSeq[I] = pseq->Seq[I];
  /* guardar o novo pseq e libertar o antigo - storing the new arry and freeing the old */
  int * Tmp = pseq->Seq; pseq->Seq = newSeq; free (Tmp);

  Error = OK;
}

int SeqArrayIsOrdered (PtSeqArray pseq)
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

  int* array = pseq -> Seq;
  for(int i = 0; i < size - 1; i++){
		if(array[i] > array[i+1]){
			Error = OK;
			return 0;
		}
	}

  Error = OK;
  return 1;
}

int SeqArrayIsEvenOdd (PtSeqArray pseq)
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

  int* array = pseq -> Seq;

  int isEven = (array[0] % 2 == 0);   // 1 if even, 0 if odd
  for(int i = 1; i < size; i++){
    int elementIsEven = (array[i] % 2 == 0);
		if (elementIsEven == (isEven)) {
			Error = OK;
			return 0;
    }
    isEven = elementIsEven;
	}

  Error = OK;
	return 1;
}

int SeqArrayNumberOfMultiples (PtSeqArray pseq, int pvalue)
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
  int* array = pseq -> Seq;
  for(int i = 0; i < size - 1; i++){
		if(array[i] % pvalue == 0){
			count++;
		}
	}

  Error = OK;
  return count;
}

void SeqArraySmallerBigger (PtSeqArray pseq, int * psmall, int * pbig)
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

  int* array = pseq -> Seq;
  *psmall = array[0];
  *pbig   = array[0];
  for(int i = 1; i< size; i++){
    if(*psmall > array[i])
      *psmall = array[i];
    if(*pbig < array[i])
      *pbig = array[i];
  }

  Error = OK;
}

int SeqArrayIsPalindromic (PtSeqArray pseq)
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

  int* array = pseq -> Seq;
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
		if(array[i] != array[j]){
			Error = OK;
			return 0;
		}
		i--;
		j++;
	}

	Error = OK;
  return 1;
}

double SeqArrayAverage (PtSeqArray pseq)
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

  int* array = pseq -> Seq;
  int sum;
  for(int i = 0; i < size; i++){
		sum += array[i];
	}

  Error = OK;
  return sum / size;
}
