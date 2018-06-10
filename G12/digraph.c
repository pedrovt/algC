// Simão Gomes 84819
// Pedro Teixeira 84715

/************ Implementação do Digrafo Dinâmico - digraph.c ************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "digraph.h"	/* interface do dágrafo */
#include "queue.h"  /* interface da fila */

/************** Definição do Estrutura de Dados do Dágrafo *************/

typedef struct binode *PtBiNode;
typedef struct vertex *PtVertex;
typedef struct edge *PtEdge;

struct binode	/* Definição de um Binó genérico - definition of the generic double linked list node */
{
	unsigned int Number;	/* número do vértice ou da aresta - number od the vertes or edge */
	PtBiNode PtPrev;	/* ponteiro para o nó anterior da lista - pointer to preview list node */
	PtBiNode PtNext;	/* ponteiro para o nó seguinte da lista - pointer to next list node */
	PtBiNode PtAdj;	/* ponteiro para a lista de adjacências - pointer to the adjacency list of edges */
	void *PtElem;	/* ponteiro para o elemento da lista - pointer to the element (vertex or edge) of the list */
	unsigned int Visit;	/* marcação de vértice visitado - field for marquing the visited vertex */
};

struct vertex	/* defini��o de um v�rtice - definition of the vertex */
{
	unsigned int InDeg;	/* semigrau incidente do v�rtice - in degree */
	unsigned int OutDeg;	/* semigrau emergente do v�rtice - out degree */
};

struct edge	/* defini��o de uma aresta - definition of the edge */
{
	int Cost;	/* custo da aresta - edge cost */
};

struct digraph	/* defini��o do d�grafo - definition of the digraph/graph */
{
	PtBiNode Head;	/* ponteiro para a cabe�a do d�grafo - pointer to digraph/graph head of the vertexes list */
	unsigned int NVertexes;	/* n�mero de v�rtices do d�grafo - number of vertexes */
	unsigned int NEdges;	/* n�mero de arestas do d�grafo - number of edges */
	unsigned int Type;	/* tipo d�grafo (1) / grafo (0) - type of digraph (1) / graph (0) */
};

/***************** Prot�tipos dos Subprogramas Internos ****************/

static PtVertex CreateVertex (void);
static PtEdge CreateEdge (int);
static PtBiNode CreateBiNode (unsigned int);
static void DestroyBiNode (PtBiNode *);
static PtBiNode InPosition (PtBiNode, unsigned int);
static PtBiNode OutPosition (PtBiNode, unsigned int);
static int InsertEdge (PtBiNode, PtBiNode, int);
static void DeleteEdge (PtBiNode, PtBiNode);

/********************** Defini��o dos Subprogramas *********************/

PtDigraph Create (unsigned int ptype)
{
	PtDigraph Digraph;

	if ((Digraph = (PtDigraph) malloc (sizeof (struct digraph))) == NULL)
		return NULL;	/* alocar mem�ria para o d�grafo */
	Digraph->Head = NULL;	/* inicializa a cabe�a do d�grafo */
	Digraph->NVertexes = 0;	/* inicializa o n�mero de v�rtices */
	Digraph->NEdges = 0;	/* inicializa o n�mero de arestas */
	Digraph->Type = ptype;	/* inicializa o tipo d�grafo/grafo */

	return Digraph;	/* devolve a refer�ncia do d�grafo criado */
}

int Destroy (PtDigraph *pdig)
{
	PtDigraph TmpDigraph = *pdig; PtBiNode Vertex, Edge;

	if (TmpDigraph == NULL) return NO_DIGRAPH;

	while (TmpDigraph->Head != NULL)	/* libertar a mem�ria dos v�rtices */
	{
		Vertex = TmpDigraph->Head;	/* v�rtice da cabe�a do d�grafo */
		TmpDigraph->Head = TmpDigraph->Head->PtNext;	/* atualizar cabe�a */

		while (Vertex->PtAdj != NULL)	/* libertar a mem�ria das arestas */
		{
			Edge = Vertex->PtAdj;	/* cabe�a da lista das arestas */
			Vertex->PtAdj = Vertex->PtAdj->PtNext;	/* atualizar cabe�a */
			free (Edge->PtElem);	/* libertar a mem�ria da aresta */
			free (Edge);	/* libertar o bin� da lista de arestas */
		}

		free (Vertex->PtElem);	/* libertar a mem�ria do v�rtice */
		free (Vertex);	/* libertar o bin� da lista de v�rtices */
	}

	free (TmpDigraph);	/* libertar a mem�ria ocupada pelo d�grafo */
	*pdig = NULL;	/* colocar a refer�ncia do d�grafo a NULL */

	return OK;
}

PtDigraph Copy (PtDigraph pdig)
{
  PtDigraph Copy; PtBiNode Vert, PEdge; PtEdge Edge;

  if (pdig == NULL) return NULL;

  Copy = Create (pdig->Type);

  /* inserir os v�rtices */
  for (Vert = pdig->Head; Vert != NULL; Vert = Vert->PtNext)
    if (InVertex (Copy, Vert->Number)) { Destroy (&Copy); return NULL; }

  /* inserir as arestas */
  for (Vert = pdig->Head; Vert != NULL; Vert = Vert->PtNext)
    for (PEdge = Vert->PtAdj; PEdge != NULL; PEdge = PEdge->PtNext)
    {
      Edge = (PtEdge) PEdge->PtElem;
      if (InEdge (Copy, Vert->Number, PEdge->Number, Edge->Cost))
      { Destroy (&Copy); return NULL; }
    }

  return Copy;  /* devolver a refer�ncia do Digrafo criado */
}

int InVertex (PtDigraph pdig, unsigned int pv)
{
	PtBiNode Insert, Node;	/* posi��o de inser��o e novo v�rtice */

	if (pdig == NULL) return NO_DIGRAPH;

					/* criar o bin� e o v�rtice */
	if ((Node = CreateBiNode (pv)) == NULL) return NO_MEM;
	if ((Node->PtElem = CreateVertex ()) == NULL)
	{ free (Node); return NO_MEM; }

					/* determinar posi��o de coloca��o e inserir o v�rtice */
	if (pdig->Head == NULL || pdig->Head->Number > pv)
	{				/* inser��o � cabe�a do d�grafo */
		Node->PtNext = pdig->Head; pdig->Head = Node;
		if (Node->PtNext != NULL) Node->PtNext->PtPrev = Node;
	}
	else
	{				/* inser��o � frente do n� de inser��o */
		if ((Insert = InPosition (pdig->Head, pv)) == NULL)
		{			/* inser��o sem sucesso, porque o v�rtice j� existe */
			DestroyBiNode (&Node); return REP_VERTEX;
		}
		Node->PtNext = Insert->PtNext;
		if (Node->PtNext != NULL) Node->PtNext->PtPrev = Node;
		Node->PtPrev = Insert; Insert->PtNext = Node;
	}

	pdig->NVertexes++;	/* atualizar o n�mero de v�rtices */
	return OK;
}

int OutVertex (PtDigraph pdig, unsigned int pv)
{
	PtBiNode Vertex, Edge, Delete;	/* posi��o de remo��o do v�rtice */

	if (pdig == NULL) return NO_DIGRAPH;
	if (pdig->NVertexes == 0) return DIGRAPH_EMPTY;

					/* determinar posi��o de remo��o do v�rtice */
	if ((Delete = OutPosition (pdig->Head, pv)) == NULL)
		return NO_VERTEX;

	while (Delete->PtAdj != NULL)	/* remover a lista de adjac�ncias */
	{	/* atualizar semigrau incidente da cabe�a da lista das arestas */
		((PtVertex) Delete->PtAdj->PtAdj->PtElem)->InDeg--;
		Edge = Delete->PtAdj;
		Delete->PtAdj = Delete->PtAdj->PtNext;	/* atualizar cabe�a */
		DestroyBiNode (&Edge);	/* destruir bin� com aresta */
		pdig->NEdges--;	/* atualizar o n�mero de arestas */
	}
					/* remo��o do v�rtice */
	if (Delete == pdig->Head)
	{				/* remo��o do v�rtice da cabe�a do d�grafo */
		if (Delete->PtNext != NULL) Delete->PtNext->PtPrev = NULL;
		pdig->Head = Delete->PtNext;
	}
	else
	{				/* remo��o de outro v�rtice do d�grafo */
		Delete->PtPrev->PtNext = Delete->PtNext;
		if (Delete->PtNext != NULL) Delete->PtNext->PtPrev = Delete->PtPrev;
	}
	DestroyBiNode (&Delete);	/* destruir bin� com v�rtice */
	pdig->NVertexes--;	/* atualizar o n�mero de v�rtices */

					/* remover as arestas incidentes */
	Vertex = pdig->Head;	/* v�rtice da cabe�a do d�grafo */
	while (Vertex != NULL)
	{				/* remover a aresta deste v�rtice para o v�rtice removido */
		if ((Edge = OutPosition (Vertex->PtAdj, pv)) != NULL)
		{
			if (Edge == Vertex->PtAdj)
			{		/* remo��o da aresta da cabe�a da lista das arestas */
				if (Edge->PtNext != NULL) Edge->PtNext->PtPrev = NULL;
				Vertex->PtAdj = Vertex->PtAdj->PtNext;
			}
			else
			{		/* remo��o de outra aresta da lista das arestas */
				Edge->PtPrev->PtNext = Edge->PtNext;
				if (Edge->PtNext != NULL) Edge->PtNext->PtPrev = Edge->PtPrev;
			}
			((PtVertex) Vertex->PtElem)->OutDeg--;	/* atualizar semigrau */
			DestroyBiNode (&Edge);	/* destruir bin� com aresta */
			if (pdig->Type) pdig->NEdges--;	/* atualizar o n�mero de arestas */
		}
		Vertex = Vertex->PtNext;	/* v�rtice seguinte do d�grafo */
	}
	return OK;
}

int InEdge (PtDigraph pdig, unsigned int pv1, unsigned int pv2, int pcost)
{
	PtBiNode V1, V2;	/* posi��o dos v�rtices adjacentes */

	if (pdig == NULL) return NO_DIGRAPH;
	if (pdig->NVertexes == 0) return NO_VERTEX;	/* sem v�rtices */
	if (pv1 == pv2) return REP_EDGE;	/* lacetes proibidos */

			/* verificar se os v�rtices existem e se a aresta j� existe */
	if ((V1 = OutPosition (pdig->Head, pv1)) == NULL)
		return NO_VERTEX;	/* v�rtice emergente inexistente */
	if (V1->PtAdj != NULL && OutPosition (V1->PtAdj, pv2) != NULL)
		return REP_EDGE;	/* aresta existente */
	if ((V2 = OutPosition (pdig->Head, pv2)) == NULL)
		return NO_VERTEX;	/* v�rtice incidente inexistente */

					/* inserir a aresta v1-v2 */
	if (InsertEdge (V1, V2, pcost) != OK) return NO_MEM;
	if (!pdig->Type)	/* se � grafo, inserir tamb�m a aresta v2-v1 */
		if (InsertEdge (V2, V1, pcost) != OK)
		{		/* se a aresta v2-v1 n�o foi inserida, remover a aresta v1-v2 */
			DeleteEdge (V1, V2); return NO_MEM;
		}

	pdig->NEdges++;	/* incrementar o n�mero de arestas */
	return OK;
}

int OutEdge (PtDigraph pdig, unsigned int pv1, unsigned int pv2)
{
	PtBiNode V1, V2;	/* posi��o dos v�rtices adjacentes */

	if (pdig == NULL) return NO_DIGRAPH;
	if (pdig->NVertexes == 0) return NO_VERTEX;
	if (pdig->NEdges == 0 || pv1 == pv2) return NO_EDGE;

			/* verificar se os v�rtices e a aresta existem */
	if ((V1 = OutPosition (pdig->Head, pv1)) == NULL)
		return NO_VERTEX;	/* v�rtice emergente inexistente */
	if (V1->PtAdj == NULL || OutPosition (V1->PtAdj, pv2) == NULL)
		return NO_EDGE;	/* aresta inexistente */
	if ((V2 = OutPosition (pdig->Head, pv2)) == NULL)
		return NO_VERTEX;	/* v�rtice incidente inexistente */

 
	DeleteEdge (V1, V2);	/* remover a aresta v1-v2 */
					/* se � grafo, remover tamb�m a aresta v2-v1 */
	if (!pdig->Type) DeleteEdge (V2, V1);

	pdig->NEdges--;	/* decrementar o n�mero de arestas */
	return OK;
}

int Type (PtDigraph pdig, unsigned int *pty)
{
	if (pdig == NULL) return NO_DIGRAPH;
	if (pty == NULL) return NULL_PTR;

	*pty = pdig->Type;
	return OK;
}

int VertexNumber (PtDigraph pdig, unsigned int *pnv)
{
	if (pdig == NULL) return NO_DIGRAPH;
	if (pnv == NULL) return NULL_PTR;

	*pnv = pdig->NVertexes;
	return OK;
}

int EdgeNumber (PtDigraph pdig, unsigned int *pne)
{
	if (pdig == NULL) return NO_DIGRAPH;
	if (pne == NULL) return NULL_PTR;

	*pne = pdig->NEdges;
	return OK;
}

int GetVertexList (PtDigraph pdig, unsigned int ppos, char *pvlist)
{
	PtBiNode PVert, PEdge; PtEdge Edge; char NodeList[20];

	if (pdig == NULL) return NO_DIGRAPH;
	if (ppos > pdig->NVertexes) return NO_VERTEX;
	if (pvlist == NULL) return NULL_PTR;

	ppos--;
	for (PVert = pdig->Head; ppos > 0; ppos--) PVert = PVert->PtNext;

	sprintf (NodeList, "Vertice %2d > ", PVert->Number);
	strcpy (pvlist, NodeList);

	for (PEdge = PVert->PtAdj; PEdge != NULL; PEdge = PEdge->PtNext)
	{
		sprintf (NodeList, "%2d (", PEdge->Number);
		strcat (pvlist, NodeList);
		Edge = (PtEdge) PEdge->PtElem;
		sprintf (NodeList, "%2d) ", Edge->Cost);
		strcat (pvlist, NodeList);
	}

	return OK;
}

PtDigraph CreateFile (char *pfilename)
{
  PtDigraph Digraph; FILE *PtF;
  unsigned int Type, NVertexes, NEdges, V, E, Vert1, Vert2; int Status, Cost;

  /* abertura com valida��o do ficheiro para leitura */
  if ( (PtF = fopen (pfilename, "r")) == NULL) return NULL;

  /* leitura do tipo de digrafo/grafo e cria��o do vazio */
  fscanf (PtF, "%d", &Type); fscanf (PtF, "%*c");

  /* leitura do n�mero de v�rtices e de arestas do ficheiro e cria��o do digrafo vazio */
  fscanf (PtF, "%d %d", &NVertexes, &NEdges); fscanf (PtF, "%*c");

  if ((Digraph = Create (Type)) == NULL) { fclose (PtF); return NULL; }

  /* leitura dos v�rtices do ficheiro */
  for (V = 0; V < NVertexes ; V++)
    {
      fscanf (PtF, "%d", &Vert1); fscanf (PtF, "%*c");
      if (InVertex (Digraph, Vert1))
      { Destroy (&Digraph); fclose (PtF); return NULL; }
    }

  /* leitura das arestas do ficheiro */
  for (E = 0; E < NEdges ; E++)
    {
      Status = fscanf (PtF, "%d %d %d", &Vert1, &Vert2, &Cost); fscanf (PtF, "%*c");
      if (Status != 3)
      { Destroy (&Digraph); fclose (PtF); return NULL; }

      if (InEdge (Digraph, Vert1, Vert2, Cost))
      { Destroy (&Digraph); fclose (PtF); return NULL; }
    }

  fclose (PtF);  /* fecho do ficheiro */

  return Digraph;  /* devolve o digrafo criado */
}

int StoreFile (PtDigraph pdig, char *pfilename)
{
  FILE *PtF; PtBiNode Vert, PEdge; PtEdge Edge;

  if (pdig == NULL) return NO_DIGRAPH;

  /* abertura com valida��o do ficheiro para escrita */
  if ((PtF = fopen (pfilename, "w")) == NULL) return NO_FILE;

  /* escrita do tipo do digrafo no ficheiro */
  fprintf (PtF, "%u\n", pdig->Type);

  /* escrita do n�mero de v�rtices e de arestas do digrafo no ficheiro */
  fprintf (PtF, "%u\t%u\n", pdig->NVertexes, pdig->NEdges);

  /* escrita dos v�rtices do digrafo no ficheiro */
  for (Vert = pdig->Head; Vert != NULL; Vert = Vert->PtNext)
    fprintf (PtF, "%u\n", Vert->Number);

  /* escrita das arestas do digrafo no ficheiro */
  for (Vert = pdig->Head; Vert != NULL; Vert = Vert->PtNext)
    for (PEdge = Vert->PtAdj; PEdge != NULL; PEdge = PEdge->PtNext)
    {
      Edge = (PtEdge) PEdge->PtElem;
      fprintf (PtF, "%u\t%u\t%d\n", Vert->Number, PEdge->Number, Edge->Cost);
    }

  fclose (PtF);  /* fecho do ficheiro */

  return OK;
}

/**************************** Aulas 12 e 13 ****************************/

// Function to Obtain Vertex Type
int VertexType (PtDigraph pdig, unsigned int pv)
{ 
	if (pdig == NULL) return NO_DIGRAPH;					// Verify if Digraph Exists!
	if ((pdig->NVertexes == 0)) return DIGRAPH_EMPTY;	 	// Verify if Digraph is Empty!

	PtBiNode node = OutPosition(pdig->Head, pv);			// Select Vertex
	if (node -> Number != pv) return NO_VERTEX;				// Verify if selected Vertex Exists!

	PtVertex vertex = (PtVertex)(node->PtElem);
	
	//Verifications

	if (vertex -> InDeg == 0) {
		if (vertex -> OutDeg == 0) return DISC;				// Return SOURCE if (InDeg == 0 and OutDeg != 0) -> Origem
		return SOURCE;										
	}

	if (vertex -> OutDeg == 0) return SINK;					// Return SINK if (InDeg != 0 and OutDeg == 0) -> Dissipador

	return OK;												// Returns OK if Common Vertex! (None of the above)
}

// Function to Obtain OutDegree Centrality for a Specific Vertex
int VertexOutDegreeCentrality (PtDigraph pdig, unsigned int pv, double *pcent)
{ 
	if (pdig == NULL) return NO_DIGRAPH;									// Verify if Digraph Exists!
	if ((pdig->NVertexes == 0)) return DIGRAPH_EMPTY;						// Verify if Digraph is Empty!

	PtBiNode node = OutPosition (pdig->Head, pv);							// Obtains Referred Node
	if (node == NULL) return NO_VERTEX;										// Break/Return Error if Obtained Node is NULL
	
	PtVertex vertex = (PtVertex)node->PtElem;								// Cast of Node VERTEX for Data Access
	
	*pcent = (((double)vertex->OutDeg) / ((double)(pdig->NVertexes-1)));	// % Calc
	
	if(pcent == NULL) return NULL_PTR;										// Verification IF any NULL before OK Return

	return OK;
}

// Function to Obtain Max OutDegree Centrality Value and respective Node
int MaxOutDegreeCentrality (PtDigraph pdig, unsigned int *pv, double *pmax)
{ 
	if (pdig == NULL) return NO_DIGRAPH; 									// Verify if Digraph Exists!
	if ((pdig->NVertexes == 0)) return DIGRAPH_EMPTY;						// Verify if Digraph is Empty!
	
	*pmax = -1.0; 															// Init at -1 to ensure acurate Max Gathering
	
	PtBiNode temp = pdig->Head;												// Obtains Head Node
	
	//Iterates until last Node (NULL PTR) *
	while(temp != NULL){
		PtVertex pvertex = (PtVertex)temp->PtElem;							// Casted access to Node's VERTEX
		double cent = (double)pvertex->OutDeg / (double)(pdig->NVertexes-1);
		
		//If Bigger -> promote Node as (MaxOutDegreeCentrality)
		if(*pmax < cent){
			*pmax = cent;													// Change (Max..) Value by pointer
			*pv = temp->Number;												// Change (Max..) Node by Pointer
		} 
		temp = temp->PtNext;												// Next Possition on the Iteration *
	}
	
	if(pv==NULL || pmax==NULL || *pmax==-1) return NULL_PTR;				// Verification IF any NULL before OK Return

	return OK;
}

// Function that Returns the Average OutDegree of specific Node Successors
int AverageSucessorOutDegree (PtDigraph pdig, unsigned int pv, double *pmsuc)
{ 
	if (pdig == NULL) return NO_DIGRAPH;	 								// Verify if Digraph Exists!
	if ((pdig->NVertexes == 0)) return DIGRAPH_EMPTY;	 					// Verify if Digraph is Empty!
	
	PtBiNode pvert = OutPosition(pdig->Head, pv);							// Obtains Referred Node
	if (pvert == NULL) return NO_VERTEX;									// If not NULL -> proceed...

	PtBiNode psuc = pvert->PtAdj;											// Obtains Referred Node's first Adjecent
	if (psuc == NULL) return NO_EDGE;										// If not NULL -> proceed...
	
	double sum = 0;	
	 
	//Iterates until last Node (NULL PTR) *
	while(psuc != NULL){
		PtVertex pvertex = (PtVertex)psuc->PtAdj->PtElem;					// Casted access to Node's VERTEX 
		sum = sum + ((double) pvertex->OutDeg);								// Agregate respective OutDegree Values
		psuc = psuc->PtNext;												// Next Possition on the Iteration *
	}

	// Compute average with the obtained values 
	*pmsuc = sum / ((double)((PtVertex) pvert->PtElem)->OutDeg);			// Average calculation and update Result by Pointer

	if(pmsuc == NULL) return NULL_PTR;										// Verification IF any NULL before OK Retur

	return OK;
}

// Function to populate a List with Isolated Nodes
int AllIsolates (PtDigraph pdig, PtQueue *pqueue)
{ 
	if (pdig == NULL) return NO_DIGRAPH;						// Verify if Digraph Exists!
	if (pdig->NVertexes == 0) return DIGRAPH_EMPTY;				// Verify if Digraph is Empty!

	// Vai ser criada uma nova fila logo não há necessidade de verificar 
	//if (*pqueue == NULL) { return NULL_PTR; }
	
	// Queue creation / memory alocation
	PtQueue queue = QueueCreate(sizeof(unsigned int));			// Queue creation
	*pqueue = queue;											// Update pointer
	if (queue == NULL) {										// Check if creation 
		return NO_MEM;
	}

	int NVertexes = pdig -> NVertexes;
	PtBiNode node = pdig -> Head;

	// iterate over the vertexes
	for (int i = 0; i < NVertexes; i++) {
		int elem = node -> Number;
		PtVertex vertex = (PtVertex)(node-> PtElem);

		// analyze the vertex
		if ((vertex-> InDeg == 0) && (vertex-> OutDeg == 0)) {
			if (QueueEnqueue(queue, &elem) != OK) {
				QueueDestroy(&queue);
				return NO_MEM;
			}
		}

		node = node -> PtNext;
	}	

	return OK;
}

int AllPredecessors (PtDigraph pdig, unsigned int pv, PtQueue *pqueue)
{ 
	if (pdig == NULL) { return NO_DIGRAPH; } 				//verify if Digraph Exists!
	if ((pdig->NVertexes == 0)) { return DIGRAPH_EMPTY; } 	//Verify if Digraph is Empty!
	
	// Queue creation / memory alocation
	PtQueue queue = QueueCreate (sizeof (unsigned int));	//Queue creation
	*pqueue = queue;										//Update pointer 
	if (queue == NULL) { return NO_MEM; }					//Check if creation was successfulls

	PtBiNode pvert = pdig->Head;							//First Node

	// Predecessors Number Find using InDegree of Node Vertex
	PtBiNode target = OutPosition(pvert, pv);				//Get target Node
	int predCount = ((PtVertex)(target->PtElem))->InDeg;	//Find InDegree of target Node

	if(predCount == 0) { return OK; }						//If NO predecessors Return NOW!

	int found = 0;											//Hold Queue size

	// Find Predecessors
	for (; pvert != NULL; pvert = pvert->PtNext)
	{
		//At each node iterates thru each adjecent ones
		PtBiNode aux = pvert->PtAdj;
		for (; aux != NULL; aux = aux->PtNext){
			if(found == predCount) { return OK; }		//Break iteration if all Predecessors already Found!

			if(aux->Number == pv){
				if (QueueEnqueue(queue, &pvert->Number) != OK) { //Add to the Queue the Predecessor Node if it's one!
					QueueDestroy(&queue);
					return NO_MEM;
				} 
				found++;
				break;
			}
		}
	}
	
	return OK;
}

// [Thanks to our colleague Luis Moura for the help on this function]
int AllNonEdges (PtDigraph pdig, PtQueue *pqueue)
{ 
	if (pdig == NULL) { return NO_DIGRAPH; } 				//verify if Digraph Exists!
	if ((pdig->NVertexes == 0)) { return DIGRAPH_EMPTY; } 	//Verify if Digraph is Empty!

	PtQueue queue;
	if ((queue = QueueCreate (sizeof (unsigned int))) == NULL) { return NO_MEM; }
	
	// get number of missing edges
	int totalEdges = pdig->NEdges;
	int totalVertexes = pdig->NVertexes;
	int completeEdges = totalVertexes*(totalVertexes - 1);
	int noEdges = completeEdges - totalEdges;
	
	// initial vertex
	PtBiNode vertex = pdig->Head;
	
	while (noEdges > 0){
		// mark all adjacents of the vertex as visited
		vertex->Visit = 1;
		PtBiNode adj;
		if (vertex->PtAdj != NULL) {
			adj = vertex->PtAdj;
			while (adj != NULL){
				adj->PtAdj->Visit = 1;
				adj = adj->PtNext;
			}
		}
		
		// verify non visited vertexes and add them to the queue
		PtBiNode binode = pdig->Head;
		while(binode != NULL){
			if (binode->Visit == 0){
				QueueEnqueue(queue, &(vertex->Number));
				QueueEnqueue (queue, &(binode->Number));
				noEdges--;
			}
			else {
				binode->Visit = 0;
			}
			binode = binode->PtNext;
		}

		vertex = vertex->PtNext;
	}
		
	
	*pqueue = queue;		
	
	if (pqueue == NULL) return NULL_PTR;

	return OK;
}

/***************** Definição dos Subprogramas Internos *****************/

/* Função que insere, de facto, uma aresta no digrafo/grafo. Em caso de sucesso devolve OK, senão devolve NO_MEM para assinalar falta de mem�ria. */

static int InsertEdge (PtBiNode pv1, PtBiNode pv2, int pcost)
{
	PtBiNode Insert, Node;	/* posi��o de inser��o e nova aresta */

					/* criar o bin� e a aresta */
	if ((Node = CreateBiNode (pv2->Number)) == NULL) return NO_MEM;
	if ((Node->PtElem = CreateEdge (pcost)) == NULL)
	{ free (Node); return NO_MEM; }

					/* determinar posi��o de coloca��o e inserir a aresta */
	if (pv1->PtAdj == NULL || pv1->PtAdj->Number > pv2->Number)
	{				/* inser��o � cabe�a da lista das arestas */
		Node->PtNext = pv1->PtAdj; pv1->PtAdj = Node;
		if (Node->PtNext != NULL) Node->PtNext->PtPrev = Node;
	}
	else
	{				/* inser��o � frente do n� de inser��o */
		Insert = InPosition (pv1->PtAdj, pv2->Number);
		Node->PtNext = Insert->PtNext;
		if (Node->PtNext != NULL) Node->PtNext->PtPrev = Node;
		Node->PtPrev = Insert; Insert->PtNext = Node;
	}

	Node->PtAdj = pv2;	/* ligar o v�rtice 1 ao v�rtice 2 */
	/* incrementar semigraus dos v�rtices emergente do 1 e incidente do 2 */
	((PtVertex) pv1->PtElem)->OutDeg++;
	((PtVertex) pv2->PtElem)->InDeg++;

	return OK;
}

/* Fun��o que remove, de facto, uma aresta do d�grafo/grafo. */

static void DeleteEdge (PtBiNode pv1, PtBiNode pv2)
{
	PtBiNode Delete;	/* posi��o de remo��o da aresta */

					/* determinar posi��o de remo��o da aresta */
	Delete = OutPosition (pv1->PtAdj, pv2->Number);

	if (Delete == pv1->PtAdj)	/* remo��o da aresta */
	{				/* remo��o da aresta da cabe�a da lista das arestas */
		if (Delete->PtNext != NULL) Delete->PtNext->PtPrev = NULL;
		pv1->PtAdj = Delete->PtNext;
	}
	else
	{				/* remo��o de outra aresta do v�rtice */
		Delete->PtPrev->PtNext = Delete->PtNext;
		if (Delete->PtNext != NULL) Delete->PtNext->PtPrev = Delete->PtPrev;
	}

	DestroyBiNode (&Delete);	/* destruir bin� com aresta */

	/* decrementar semigraus dos v�rtices emergente do 1 e incidente do 2 */
	((PtVertex) pv1->PtElem)->OutDeg--;
	((PtVertex) pv2->PtElem)->InDeg--;
}

/* Fun��o que cria o v�rtice do d�grafo/grafo. Devolve a refer�ncia do v�rtice criado ou NULL, caso n�o consiga cri�-lo por falta de mem�ria. */
 
static PtVertex CreateVertex (void)
{
	PtVertex Vertex;

	if ((Vertex = (PtVertex) malloc (sizeof (struct vertex))) == NULL)
		return NULL;

	Vertex->InDeg = 0;	/* inicializa o semigrau incidente */
	Vertex->OutDeg = 0;	/* inicializa o semigrau emergente */
	return Vertex;	/* devolve o v�rtice criado */
}

/* Fun��o que cria a aresta do d�grafo/grafo. Devolve a refer�ncia da aresta criada ou NULL, caso n�o consiga cri�-la por falta de mem�ria. */

static PtEdge CreateEdge (int pcost)
{
	PtEdge Edge;

	if ((Edge = (PtEdge) malloc (sizeof (struct edge))) == NULL)
		return NULL;

	Edge->Cost = pcost;	/* armazena o custo da aresta */
	return Edge;	/* devolve a aresta criada */
}

/* Fun��o que cria o bin� da lista de v�rtices ou da lista de arestas. Devolve a refer�ncia do bin� criado ou NULL, caso n�o consiga cri�-lo por falta de mem�ria. */

static PtBiNode CreateBiNode (unsigned int pnumber)
{
	PtBiNode Node;

	if ((Node = (PtBiNode) malloc (sizeof (struct binode))) == NULL)
		return NULL;

	Node->PtNext = NULL;	/* bin� aponta para a frente para NULL */
	Node->PtPrev = NULL;	/* bin� aponta para a tr�s para NULL */
	Node->PtAdj = NULL;	/* lista de adjac�ncias nula */
	Node->Number = pnumber;	/* armazena o identificador do bin� */
	return Node;	/* devolve o bin� criado */
}

/* Fun��o que liberta a mem�ria ocupada pelo bin� e pelo seu elemento. */

static void DestroyBiNode (PtBiNode *pbinode)
{
	if (*pbinode == NULL) return;

	free ((*pbinode)->PtElem);
	free (*pbinode);
	*pbinode = NULL;
}

/* Fun��o de pesquisa para inser��o. Devolve um ponteiro para o bin� � frente do qual deve ser feita a inser��o do novo v�rtice (nova aresta) ou NULL, caso o v�rtice (a aresta) j� exista. */
 
static PtBiNode InPosition (PtBiNode phead, unsigned int pnumber)
{
	PtBiNode Node, Prev;

	for (Node = phead; Node != NULL; Node = Node->PtNext)
	{
		if (Node->Number >= pnumber) break;
		Prev = Node;
	}

	if (Node == NULL || Node->Number > pnumber) return Prev;
	else return NULL;	/* o elemento j� existe */
}

/* Fun��o de pesquisa para remo��o. Devolve um ponteiro para o bin� onde se encontra o v�rtice (a aresta) ou NULL, caso o v�rtice (a aresta) n�o exista. */

static PtBiNode OutPosition (PtBiNode phead, unsigned int pnumber)
{
	PtBiNode Node;

	for (Node = phead; Node != NULL; Node = Node->PtNext)
		if (Node->Number == pnumber) break;
	return Node;
}


