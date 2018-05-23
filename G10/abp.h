
/*******************************************************************************

 Ficheiro de interface do Tipo de Dados Abstrato Arvore Binaria de Pesquisa (ABP)
 (abp.h). A implementa��o tem capacidade de m�ltipla instancia��o, sendo
 providenciado um construtor para criar uma arvore vazia. � da responsabilidade
 da aplica��o, invocar o destructor, para libertar a mem�ria atribu�da ao objecto.
 O m�dulo providencia um controlo centralizado de erro, disponibilizando uma fun��o
 para obter o �ltimo erro ocorrido e uma fun��o para obter uma mensagem de erro
 elucidativa.

 Autor : Ant�nio Manuel Adrego da Rocha    Data : Maio de 2018

 Interface file of the abstract data type Binary Search Tree ABP (abp.h). The 
 implementation provides a constructor for creating an empty tree. The application
 has the responsibility of calling the destructor to release the dynamic memory 
 allocated to the tree. The data-type has a central control error mechanism, 
 providing operations for obtaining the last error occurred and for obtaining the 
 correspondent message. The data-type has also operations to store and retrieve
 trees from text files. The tree is simply represented by a pointer to its root.

*******************************************************************************/

#ifndef _ABP
#define _ABP

# include "queue.h"

/****************** Defini��o do Tipo Ponteiro para uma ABP *******************/

typedef struct abpnode *PtABPNode;

/************************ Defini��o de C�digos de Erro ************************/

#define	OK		0	/* opera��o realizada com sucesso - operation with success */
#define	NO_ABP		1	/* a ABP n�o existe - tree does not exist */
#define	NO_MEM		2	/* mem�ria esgotada - out of memory */
#define	NULL_PTR	3	/* ponteiro nulo - null pointer */
#define	ABP_EMPTY	4	/* ABP vazia - empty tree */
#define	REP_ELEM	5	/* j� existe o elemento - element already exists in the tree */
#define	NO_ELEM		6	/* o elemento n�o existe - element does not exist in the tree */
#define	NO_FILE		7	/* o ficheiro n�o existe - file does not exist */
#define INVALID		8	/* par�metros inv�lidos - incorrect parameters */

/*************************** Prot�tipos das Fun��es ***************************/

int ABPErrorCode (void);
/*******************************************************************************
 Fun��o que devolve o c�digo do �ltimo erro ocorrido.Returns the error code.
*******************************************************************************/

char *ABPErrorMessage (void);
/*******************************************************************************
 Fun��o que devolve uma mensagem esclarecedora da causa do �ltimo erro ocorrido.
 Returns an error message.
*******************************************************************************/

PtABPNode ABPCreate (void);
/*******************************************************************************
 Cria uma arvore vazia. Devolve um ponteiro a NULL.

 Creates the empty tree returning a NULL reference.
*******************************************************************************/

void ABPDestroy (PtABPNode *proot);
/*******************************************************************************
 Destr�i a arvore e coloca a refer�ncia a NULL. Valores de erro: OK ou ABP_EMPTY.
 
 Destroys the tree and releases the memory. Error codes: OK or ABP_EMPTY.
*******************************************************************************/

int ABPEmpty (PtABPNode proot);
/*******************************************************************************
 Verifica se a arvore esta ou nao vazia. Devolve 1 em caso afirmativo e 0 em caso 
 contr�rio. Valores de erro: OK.

 Verifies if the tree pointed by proot is empty or not. Returns 1 in affirmative
 case and 0 otherwise. Error code: OK.
*******************************************************************************/

void ABPInsertRec (PtABPNode *proot, int pelem);  /* vers�o recursiva */
void ABPInsertRep (PtABPNode *proot, int pelem);  /* vers�o repetitiva */
/*******************************************************************************
 Coloca pelem na arvore. N�o insere elementos repetidos.
 Valores de erro: OK, NO_MEM ou REP_ELE.

 Inserts pelem in the tree pointed by proot. Error codes: OK, NO_MEM or REP_ELE.
*******************************************************************************/

void ABPDeleteRec (PtABPNode *proot, int pelem);  /* vers�o recursiva */
void ABPDeleteRep (PtABPNode *proot, int pelem);  /* vers�o repetitiva */
/*******************************************************************************
 Retira pelem da arvore. Valores de erro: OK ou NO_ELEM.

 Deletes pelem from the tree pointed by proot. Error codes: OK or NO_ELEM.
*******************************************************************************/

int ABPSearch (PtABPNode proot, int pelem);
/*******************************************************************************
 Pesquisa se pelem existe na arvore. Devolve 1 em caso afirmativo e 0 em caso 
 contr�rio. Valores de erro: OK, ABP_EMPTY ou NO_ELEM.

 Searchs pelem in the tree pointed by proot. Returns 1 if it exists and 0 otherwise.
 Error codes: OK, ABP_EMPTY or NO_ELEM.
*******************************************************************************/

PtABPNode ABPMinRec (PtABPNode proot);  /* pesquisa de m�nimo recursiva - minimum recursive search */
PtABPNode ABPMinRep (PtABPNode proot);  /* pesquisa de m�nimo repetitiva - minimum repetitive search */
/*******************************************************************************
 Pesquisa o menor elemento da arvore. Valores de erro: OK ou ABP_EMPTY.

 Returns a pointer to the minimum element of the tree pointed by proot.
 Error codes: OK or ABP_EMPTY.
*******************************************************************************/

PtABPNode ABPMaxRec (PtABPNode proot);  /* pesquisa de m�ximo recursiva - maximum recursive search */
PtABPNode ABPMaxRep (PtABPNode proot); /* pesquisa de m�ximo repetitiva - maximum repetitive search */
/*******************************************************************************
 Pesquisa o maior elemento da arvore. Valores de erro: OK ou ABP_EMPTY.

 Returns a pointer to the maximum element of the tree pointed by proot.
 Error codes: OK or ABP_EMPTY.
*******************************************************************************/

int ABPElement (PtABPNode pnode);
/*******************************************************************************
 Devolve o elemento armazenado em pnode. Valores de erro: OK ou NULL_PTR.

 Returns the element pointed by pnode. Error codes: OK or NULL_PTR.
*******************************************************************************/

PtABPNode ABPKMin (PtABPNode proot, unsigned int pk);  /* pesquisa de K-m�nimo */
/*******************************************************************************
 Pesquisa o K-menor elemento da arvore. Valores de erro: OK, ABP_EMPTY ou NO_ELEM.

 Searchs the Kth minimal element of the tree pointed by proot returning a pointer
 to its node. Error codes: OK, ABP_EMPTY or NO_ELEM.
*******************************************************************************/

unsigned int ABPSize (PtABPNode proot);
/*******************************************************************************
 Calcula o numero de nos da arvore. Valores de erro: OK.

 Calculates the number of elements stores in the tree pointed by proot. Error code: OK.
*******************************************************************************/

unsigned int ABPHeight (PtABPNode proot);
/*******************************************************************************
 Calcula a altura da arvore. Valores de erro: OK.

 Calculates the height of the tree pointed by proot. Error code: OK.
*******************************************************************************/

PtABPNode ABPCreateFile (char *pnomef);
/*******************************************************************************
 Cria uma arvore a partir do ficheiro pnomef. Devolve a refer�ncia da arvore criada
 ou NULL, caso n�o consiga criar a arvore por falta de mem�ria. Valores de erro: 
 OK, NO_MEM ou NO_FILE.

 Creates a tree from a text file. Returns a reference to the new tree or NULL if
 there isn't enough memory. Error codes: OK, NO_MEM or NO_FILE.
*******************************************************************************/

void ABPStoreFile (PtABPNode proot, char *nomef);
/*******************************************************************************
 Armazena a arvore, caso ela exista, no ficheiro pnomef. O ficheiro tem na
 primeira linha o n�mero de elementos da arvore, seguido dos elementos, um por
 linha. Valores de erro: OK, ABP_EMPTY ou NO_FILE.

 Stores the tree pointed by proot in text file pfname. The first line of the file
 constains the number of elements of the tree, followed by the emenets one per line.
 Error codes: OK, ABP_EMPTY or NO_FILE. 
*******************************************************************************/

void ABPPreOrderRec (PtABPNode proot);  /* travessia recursiva - recursive traversal */
void ABPPreOrderRep (PtABPNode proot);  /* travessia repetitiva - repetitive traversal */
/*******************************************************************************
 Lista a arvore em pre-ordem. Valores de erro: OK ou ABP_EMPTY.

 Lists the tree using a pre-order traversal. Error codes: OK or ABP_EMPTY.
*******************************************************************************/

void ABPInOrderRec (PtABPNode proot);  /* travessia recursiva - recursive traversal */
void ABPInOrderRep (PtABPNode proot);  /* travessia repetitiva - repetitive traversal */
/*******************************************************************************
 Lista a arvore em ordem (vers�o recursiva). Valores de erro: OK ou ABP_EMPTY.

 Lists the tree using a in-order traversal. Error codes: OK or ABP_EMPTY.
*******************************************************************************/

void ABPPostOrderRec (PtABPNode proot);  /* travessia recursiva - recursive traversal */
void ABPPostOrderRep (PtABPNode proot);  /* travessia repetitiva - repetitive traversal */
/*******************************************************************************
 Lista a arvore em pos-ordem. Valores de erro: OK ou ABP_EMPTY.

 Lists the tree using a post-order traversal. Error codes: OK or ABP_EMPTY.
*******************************************************************************/

void ABPByLevel (PtABPNode proot);
/*******************************************************************************
 Lista a arvore por niveis. Valores de erro: OK, ABP_EMPTY ou NO_MEM.

 Lists the tree by levels. Error codes: OK, ABP_EMPTY or NO_MEM.
*******************************************************************************/

PtABPNode ABPBalance (PtABPNode proot);
/*******************************************************************************
 Cria uma uma nova arvore balanceada. Devolve a refer�ncia da ABP criada ou NULL
 em caso de inexist�ncia de mem�ria. Valores de erro: OK, ABP_EMPTY ou NO_MEM.

 Creates a new balanced tree from the tree pointed by proot. Returns a reference
 to the new tree or NULL if there isn't enough memory. Error codes: OK, ABP_EMPTY or NO_MEM.
*******************************************************************************/

void ABPDisplay (PtABPNode proot);
/*******************************************************************************
 Imprime no monitor os elementos da arvore de forma hier�rquica.
 Valores de erro: OK ou ABP_EMPTY.

 Display hierarchically the tree pointed by proot. Error codes: OK or ABP_EMPTY.
*******************************************************************************/

PtABPNode ABPCopy (PtABPNode proot);
/*******************************************************************************
 Copia a arvore. Devolve a refer�ncia da ABP criada ou NULL em caso de
 inexist�ncia de mem�ria. Valores de erro: OK ou NO_MEM.

 Creates a copy tree of the tree pointed by proot. Returns a reference to the new
 tree or NULL if there isn't enough memory. Error codes: OK or NO_MEM.
*******************************************************************************/

/* trabalho da aula 9 */

void ABPDeleteMin (PtABPNode *proot);
/*******************************************************************************
 Elimina o menor elemento da arvore. Valores de erro: OK ou ABP_EMPTY.
*******************************************************************************/

void ABPDeleteMax (PtABPNode *proot);
/*******************************************************************************
 Elimina o maior elemento da arvore. Valores de erro: OK ou ABP_EMPTY.
*******************************************************************************/

PtABPNode ABPFloorValue (PtABPNode proot, int pvalue);
/*******************************************************************************
 Obtem um ponteiro para o n� do elemento pvalue ou, caso ele n�o exista, para o 
 n� do maior dos elementos menores do que ele. Se esse n� n�o existir, devolve o
 ponteiro nulo. Valores de erro: OK, ABP_EMPTY ou NO_ELEM.
*******************************************************************************/

PtABPNode ABPCeilValue (PtABPNode proot, int pvalue);
/*******************************************************************************
 Obtem um ponteiro para o n� do elemento pvalue ou, caso ele n�o exista, para o 
 n� do menor dos elementos maiores do que ele. Se esse n� n�o existir, devolve o
 ponteiro nulo. Valores de erro: OK, ABP_EMPTY ou NO_ELEM.
*******************************************************************************/

int ABPRank (PtABPNode proot, int pvalue);
/*******************************************************************************
 Determina o n�mero de elementos inferiores a pvalue. Valores de erro: OK ou 
 ABP_EMPTY.
*******************************************************************************/

void ABPElements (PtABPNode proot, PtQueue pqueue, int plow, int phigh);
/*******************************************************************************
 Regista ordenadamente, numa fila de inteiros j� existente e referenciada pelo 
 ponteiro pqueue, os elementos da �rvore pertencentes ao intervalo fechado
 [plow, phigh]. Valores de erro: OK, ABP_EMPTY, NULL_PTR, INVALID ou NO_MEM.
*******************************************************************************/

int ABPIsEvenOdd (PtABPNode proot);
/*******************************************************************************
 Verifica se a arvore � alternadamente composta por n�meros pares e �mpares ou
 �mpares e pares. Devolve 1 em caso afirmativo e 0 em caso contr�rio. Valores de
 erro: OK ou ABP_EMPTY.
*******************************************************************************/

#endif
