/*******************************************************************************
 Ficheiro de interface do Tipo de Dados Abstracto SEQ_LIST (seqlist.h). Este
 tipo de dados serve para armazenar e processar sequ�ncias de n�meros inteiros.
 A sequ�ncia � armazenada numa lista biligada e tem associado o n�mero de elementos
 efectivamente armazenados. A implementa��o providencia um construtor para criar
 uma sequ�ncia vazia. � da responsabilidade da aplica��o, invocar o destrutor,
 para libertar a mem�ria atribu�da ao objecto. O m�dulo providencia um controlo
 centralizado de erro, disponibilizando fun��es para: consultar o �ltimo erro
 ocorrido; obter uma mensagem de erro elucidativa; e limpar o erro. Tamb�m s�o
 disponibilizadas fun��es para: criar uma sequ�ncia a partir de um ficheiro de
 texto e armazenar uma sequ�ncia num ficheiro de texto. Este ficheiro tem na
 primeira linha o n�mero de elementos armazenados na sequ�ncia, seguido dos
 elementos, um por linha.
 
 Autor : Ant�nio Manuel Adrego da Rocha    Data : Mar�o de 2018
*******************************************************************************/

#ifndef _SEQ_LIST
#define _SEQ_LIST

/*********** Defini��o do Tipo Ponteiro para a sequ�ncia de N�meros ***********/

typedef struct seqlist *PtSeqList;

/************************ Defini��o de C�digos de Erro ************************/

#define	OK                0         /* opera��o realizada com sucesso */
#define	NO_SEQ            1         /* a(s) sequ�ncia(s) n�o existe(m) */
#define	NO_MEM            2         /* mem�ria esgotada */
#define BAD_INDEX         3         /* posi��o incorrecta */
#define NO_NUMBER         4         /* elemento inexistente */
#define	SEQ_EMPTY         5         /* sequ�ncia vazia */
#define	SEQ_FULL          6         /* sequ�ncia cheia */
#define BAD_SIZE          7         /* dimens�o da sequ�ncia errada - wrong size */
#define	NO_FILE           8         /* ficheiro inexistente */
#define	NULL_PTR          9         /* ponteiro nulo */

/************************* Prot�tipos dos Subprogramas ************************/

void SeqListClearError (void);
/*******************************************************************************
 Inicializa��o do erro.
*******************************************************************************/

int SeqListError (void);
/*******************************************************************************
 Indica��o do c�digo de erro ocorrido na �ltima opera��o.
*******************************************************************************/

char *SeqListErrorMessage (void);
/*******************************************************************************
 Obten��o da mensagem esclarecedora da causa do erro ocorrido.
*******************************************************************************/

PtSeqList SeqListCreate ();
/*******************************************************************************
 Cria��o de uma sequ�ncia vazia. Devolve a refer�ncia da sequ�ncia criada ou NULL,
 caso n�o exista mem�ria. Valores de erro: OK ou NO_MEM.
*******************************************************************************/

void SeqListDestroy (PtSeqList *pseq);
/*******************************************************************************
 Destrui��o de uma sequ�ncia. Valores de erro: OK ou NO_SEQ.
*******************************************************************************/

PtSeqList SeqListCopy (PtSeqList pseq);
/*******************************************************************************
 C�pia de uma sequ�ncia. Valores de erro: OK, NO_SEQ ou NO_MEM.
*******************************************************************************/

PtSeqList SeqListFileCreate (char * pfname);
/*******************************************************************************
 Cria��o de uma sequ�ncia a partir do ficheiro de texto pfname. Devolve a
 refer�ncia da sequ�ncia criada ou NULL, caso n�o consiga criar a sequ�ncia.
 Valores de erro: OK, NO_FILE, BAD_SIZE ou NO_MEM.
*******************************************************************************/

void SeqListStoreFile (PtSeqList pseq, char *pfname);
/*******************************************************************************
 Armazena a sequ�ncia pseq, caso ela exista, no ficheiro pfname.
 Valores de erro: OK, NO_SEQ, SEQ_EMPTY ou NO_FILE.
*******************************************************************************/

int SeqListGetSize (PtSeqList pseq);
/*******************************************************************************
 Determinar o n�mero de elementos da sequ�ncia. Valores de erro: OK ou NO_SEQ.
*******************************************************************************/

int SeqListGetElement (PtSeqList pseq, int pindex);
/*******************************************************************************
 Consultar o elemento armazenado na posi��o pindex da sequ�ncia. A posi��o tanto pode
 ser indicada por um valor: positivo (0<=pindex<size) para acesso do in�cio para o
 fim da sequ�ncia; ou negativo (-1<=pindex<=-size) para acesso do fim para o in�cio
 da sequ�ncia. Valores de erro: OK ou BAD_INDEX.
*******************************************************************************/

void SeqListSetElement (PtSeqList pseq, int pindex, int pvalue);
/*******************************************************************************
 Modificar o elemento armazenado na posi��o pindex da sequ�ncia. A posi��o tanto
 pode ser indicada por um valor: positivo (0<=pindex<size) para acesso do in�cio
 para o fim da sequ�ncia; ou negativo (-1<=pindex<=-size) para acesso do fim para
 o in�cio da sequ�ncia. Valores de erro: OK ou BAD_INDEX.
*******************************************************************************/

int SeqListEquals (PtSeqList pseq1, PtSeqList pseq2);
/*******************************************************************************
 Compara��o de igualdade de duas sequ�ncias, considerando sequ�ncias iguais quando
 elas t�m os mesmos elementos pela mesma ordem. Devolve 1 em caso afirmativo e 0
 em caso contr�rio. Valores de erro: OK ou NO_SEQ.
*******************************************************************************/

void SeqListInsert (PtSeqList pseq, int pvalue);
/*******************************************************************************
 Inserir o elemento pvalue no fim da sequ�ncia. Valores de erro: OK, NO_SEQ ou NO_MEM.
*******************************************************************************/

void SeqListDelete (PtSeqList pseq, int pvalue);
/*******************************************************************************
 Eliminar o elemento pvalue da sequ�ncia. Valores de erro: OK, NO_SEQ, SEQ_EMPTY
 ou NO_NUMBER.
*******************************************************************************/

int SeqListIsOrdered (PtSeqList pseq);
/*******************************************************************************
 Verificar se a sequ�ncia est� ordenada por ordem n�o decrescente. Devolve 1 em
 caso afirmativo e 0 em caso contr�rio. Valores de erro: OK, NO_SEQ ou SEQ_EMPTY.
*******************************************************************************/

int SeqListIsEvenOdd (PtSeqList pseq);
/*******************************************************************************
 Verificar se a sequ�ncia � uma sequ�ncia alternativamente composta por n�meros
 pares e �mpares ou �mpares e pares. Devolve 1 em caso afirmativo e 0 em caso
 contr�rio. Valores de erro: OK, NO_SEQ ou SEQ_EMPTY.
*******************************************************************************/

int SeqListNumberOfMultiples (PtSeqList pseq, int pvalue);
/*******************************************************************************
 Determinar quantos elementos da sequ�ncia s�o m�ltiplos de pvalue. Valores de
 erro: OK, NO_SEQ ou SEQ_EMPTY.
*******************************************************************************/

void SeqListSmallerBigger (PtSeqList pseq, int * psmall, int * pbig);
/*******************************************************************************
 Determinar o menor e o maior elementos da sequ�ncia, que s�o devolvidos pelos,
 par�metros de sa�da, respectivamente, psmall e pbig. Valores de erro: OK,
 NO_SEQ ou SEQ_EMPTY.
*******************************************************************************/

int SeqListIsPalindromic (PtSeqList pseq);
/*******************************************************************************
 Verificar se a sequ�ncia � a mesma quando se percorre em ambos os sentidos, ou
 seja, uma "capicua". Devolve 1 em caso afirmativo e 0 em caso contr�rio.
 Valores de erro: OK, NO_SEQ ou SEQ_EMPTY.
*******************************************************************************/

double SeqListAverage (PtSeqList pseq);
/*******************************************************************************
 Determinar a m�dia dos elementos da sequ�ncia. Valores de erro: OK, NO_SEQ ou SEQ_EMPTY.
*******************************************************************************/

#endif
