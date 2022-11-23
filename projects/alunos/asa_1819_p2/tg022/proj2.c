#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/* GRUPO 22 - LEIC-T */
/* Monica Alves 90759 */
/* Joao Galamba 90735 */


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NIL -1
/* returns the lowest argument given */
#define min(a, b) (((a) < (b)) ? (a) : (b))
/* returns the absolute value argument given */
#define abs(a) (((a) > (0)) ? (a) : (-a))

typedef enum { false, true } bool;


/* linkList structure: Has a number that identifies the node and a pointer for next linkList structure. */
/* This will be used to mark the begining and end of the graph's queue */
typedef struct linkList{
	int n;
	struct linkList* next;
} linkList;

/* connection structer: Has a number for each node with connection (n), capacity of each node (cap) 
and two pointers for the connections (next and dual) */
typedef struct connection{
	int n;
	int cap;
	int flux;
	struct connection* dual;
	struct connection* next;
} connection;

/* coordinates structure: Has a number for origin and for destination. 
This will be used to see where the graf's minimum cut is */
typedef struct coordinates{
	int origin;
	int destination;
} coordinates;

/* node structure: Has height for each node (height), overflow and connections pointers (next and current). */
/* It also has two boolean in order to see if it's a supplier or not and too see if it's a source or not */
typedef struct node{
	int height;
	int overflow;
	bool suplier;
	bool src;
	struct connection* current; /* ultimo arco por onde passou flow*/
	struct connection* next;
} node;


void freeAll (node* nodes, int numNodes, int* abastecimentos, coordinates* caminhos, int* src_trg, int* heights){
	connection* link;
	connection* aux;
	int i;
	
	for (i = 0; i < numNodes; i++)
	{
		link = nodes[i].next;
		while (link != NULL)
		{
			aux = link;
			link = link->next;
			free(aux);
		}
	}
	free(nodes);
	free(abastecimentos);
	free(caminhos);
	free(src_trg);
	free(heights);
}

/* Auxiliar function used for sorting lists */
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

/* Auxiliar function used for sorting lists of coordinates structures */
int cmpfunc2 (const void * a, const void * b){
	coordinates* pa = (coordinates*)a;
	coordinates* pb = (coordinates*)b;
	if (pa->origin != pb->origin)
	{
		return pa->origin - pb->origin;
	}
	else
	{
		return pa->destination - pb->destination;
	}
}

/* Auxiliar function that adds nodes to queue */
void addToQueue(linkList** init, linkList** fin, int n)
{
	if (*init == NULL)
	{
		*init = (linkList*) can_fail_malloc(sizeof(linkList));
		(*init)->n = n;
		(*init)->next = NULL;
		*fin = *init;
	}
	else
	{
		(*fin)->next = (linkList*) can_fail_malloc(sizeof(linkList));
		*fin = (*fin)->next;
		(*fin)->n = n;
		(*fin)->next = NULL;
	}
}
/* Auxiliar function that removes node from the queue and returns removed number */
int removeFromQueue(linkList** init)
{
	int num;
	linkList* aux = *init;
	(*init) = (*init)->next;
	num = aux->n;
	free(aux);
	return num;
}

/* Auxiliar function that calculates the graf's intial flux */
void fluxoInicial(int s, int V, node* nodes, linkList** init, linkList** fin)
{
	nodes[s].height = V;

	connection* link = nodes[s].next;
	while (link != NULL)
	{
		/* Sends as much flux as the connection's capacity allows to next node */
		link->flux = link->cap;
		/* Saves that sent flux as next node's overflow */
		nodes[link->n].overflow = link->flux;

		/* Saves the negative flux as in the residual graph */
		link->dual->flux = -link->flux;

		/* Adds node to queue in order to take care of its overflow */
		addToQueue(init, fin, link->n);

		link = link->next;
	}
}

/* Auxiliar function that increases node's height if necessary in order to
perform push */
void relabel(node* nodes, int u)
{
	int maxH = INT_MAX;

	connection* link = nodes[u].next;
	while(link != NULL)
	{
		if (((link->flux == link->cap) && (link->cap > 0)) || ((link->flux == 0) && (link->cap < 0)))
		{
			link = link->next;
			continue;
		}

		if (nodes[link->n].height < maxH)
		{
			maxH = nodes[link->n].height;

			nodes[u].height = maxH + 1;
		}

		link = link->next;
	}
}

/* Auxiliar function that takes care of a node's overflow by sending it to another node  */
void push(node* nodes, int u, linkList** init, linkList** fin)
{
	int flux;
	if (nodes[u].current == NULL)
	{
		nodes[u].current = nodes[u].next;
	}
	while(nodes[u].current != NULL)
	{
		if ((nodes[u].current->flux == nodes[u].current->cap) && (nodes[u].current->cap > 0))
		{
			nodes[u].current = nodes[u].current->next;
			continue;
		}

		if ((nodes[u].height > nodes[nodes[u].current->n].height) && (nodes[u].current->cap > 0))
		{
			flux = min(nodes[u].current->cap - nodes[u].current->flux, nodes[u].overflow);
			nodes[u].overflow -= flux;
			if ((nodes[nodes[u].current->n].overflow == 0) && (nodes[u].current->n != 1) && (nodes[u].current->n != 0))
			{
				addToQueue(init, fin, nodes[u].current->n);
			}
			nodes[nodes[u].current->n].overflow += flux;
			nodes[u].current->flux += flux;
			nodes[u].current->dual->flux -= flux;
			if (nodes[u].overflow == 0)
			{
				return;
			}
		}
		
		else if (nodes[u].height > nodes[nodes[u].current->n].height)
		{
			flux = min(abs(nodes[u].current->flux), nodes[u].overflow);
			nodes[u].overflow -= flux;
			if ((nodes[nodes[u].current->n].overflow == 0) && (nodes[u].current->n != 1) && (nodes[u].current->n != 0))
			{
				addToQueue(init, fin, nodes[u].current->n);
			}
			nodes[nodes[u].current->n].overflow += flux;
			nodes[u].current->flux += flux;
			nodes[u].current->dual->flux -= flux;
			if (nodes[u].overflow == 0)
			{
				return;
			}
		}

		nodes[u].current = nodes[u].current->next;
	}
	
	return;
}


/* Auxiliar function regarding first's project output: Graph's maximum flow */
void fluxoMaximo(node* nodes, linkList** init, linkList** fin)
{
	while ((*init) != NULL)
	{
		int u = removeFromQueue(init);

		while(1)
		{
			push(nodes, u, init, fin);
			if (nodes[u].overflow != 0)
			{
				relabel(nodes, u);
			}
			else
			{
				break;
			}
		}
	}
}

void calculateAux(node* nodes, int s, int numNodes, int** src_trg, int* vctr_size)
{
	int i;
	for (i = 1; i < numNodes; i++)
	{
		connection* link = nodes[i].next;
		while(link != NULL)
		{
			if ((nodes[i].src == true) && (nodes[link->n].src == false) && (link->cap > 0))
			{
				(*vctr_size) += 2;
				(*src_trg) = (int*) can_fail_realloc((*src_trg), sizeof(int) * (*vctr_size));
				(*src_trg)[(*vctr_size) - 2] = i;
				(*src_trg)[(*vctr_size) - 1] = link->n;
			}
			link = link->next;
		}
	}
}

/* MAIN FUNCTION */
int main ()
{
	/* initializations */
	int vctr_size = 0;
	int* src_trg = (int*) can_fail_malloc(sizeof(int) * vctr_size);
	node* nodes;
	linkList* init = NULL;
	linkList* fin = NULL;
	int numFornecedores, numAbastecimento, numLigacoes, numNodes;
	int index = 0;
	int i, j;
	int abastecimentos_size;
	int* abastecimentos;
	int cut, err;
	int max, maxi;
	int* heights;
	int origin, dest, cap;

	/* error message in case the input is wrongly introduced */
	err = scanf("%d %d %d", &numFornecedores, &numAbastecimento, &numLigacoes);
	if (err == -1)
	{
		printf("Error occurred.\n");
	}

	/* numAbastecimento * 2 because of their complementery nodes */
	/* numFornecedores + (numAbastecimento * 2) + 2 because of start and target node */
	numNodes = (numFornecedores + (numAbastecimento * 2) + 2);
	nodes = (node*)can_fail_malloc(sizeof(node) * numNodes);

	for (i = 0; i < numNodes; i++)
	{
		nodes[i].height = 0;
		nodes[i].overflow = 0;
		nodes[i].current = NULL;
		nodes[i].next = NULL;
		nodes[i].suplier = false;
	}
	
	nodes[1].height = numNodes;
	nodes[0].next = (connection*) can_fail_malloc(sizeof(connection));
	nodes[0].next->n = 0;
	nodes[0].next->cap = 0;
	nodes[0].next->flux = 0;

	/* 2nd line input */
	/* For cicle that takes care of supplier's capacity */
	for (index = 2; index < (numFornecedores + 2); index++)
	{
		err = scanf("%d", &cap);
		if (err == -1)
		{
			printf("Error occurred.\n");
		}
		nodes[index].suplier = true;
		nodes[index].next = (connection*) can_fail_malloc(sizeof(connection));
		connection* link = nodes[index].next;
		link->n = 0;
		link->cap = cap;
		link->flux = 0;
		link->next = NULL;
		link->dual = nodes[0].next;
		
	}

	/* 3rd line input */
	/* For cicle that takes care of abastecimento's node  */
	for (index = numFornecedores + 2; index < (numNodes - numAbastecimento); index++)
	{
		err = scanf("%d", &cap);
		if (err == -1)
		{
			printf("Error occurred.\n");
		}
		nodes[index].suplier = false;
		nodes[index].next = (connection*) can_fail_malloc(sizeof(connection));
		connection* link = nodes[index].next;
		link->n = (index + numAbastecimento);
		link->cap = cap;
		link->flux = 0;
		link->next = NULL;
		nodes[(index + numAbastecimento)].suplier = false;
		nodes[(index + numAbastecimento)].next = (connection*) can_fail_malloc(sizeof(connection));
		connection* link2 = nodes[(index + numAbastecimento)].next;
		link2->n = index;
		link2->cap = -cap;
		link2->flux = 0;
		link2->next = NULL;
		link->dual = link2;
		link2->dual = link;
	}

	/* while cicle that creates connections between nodes */
	index = 0;
	while (index < numLigacoes)
	{
		err = scanf("%d %d %d", &origin, &dest, &cap);
		/* error message in case the input is wrongly introduced */
		if (err == -1)
		{
			printf("Error occurred.\n");
		}

		/* if it's an 'abastecimento' node then origin node is connected with abastecimento's complementary node */
		if (nodes[dest].suplier == false && dest >= (2 + numFornecedores))
		{
			dest += numAbastecimento;
		}

		connection* previous = nodes[origin].next;
		nodes[origin].next = (connection*) can_fail_malloc(sizeof(connection));
		nodes[origin].next->n = dest;
		nodes[origin].next->cap = -cap;
		nodes[origin].next->flux = 0;
		nodes[origin].next->next = previous;
		
		previous = nodes[dest].next;
		nodes[dest].next = (connection*) can_fail_malloc(sizeof(connection));
		nodes[dest].next->n = origin;
		nodes[dest].next->cap = cap;
		nodes[dest].next->flux = 0;
		nodes[dest].next->next = previous;
		
		nodes[origin].next->dual = nodes[dest].next;
		nodes[dest].next->dual = nodes[origin].next;

		index++;
	}

	/* Preflow */
	fluxoInicial(1, numNodes, nodes, &init, &fin);

	fluxoMaximo(nodes, &init, &fin);
	
	max = nodes[0].overflow;

	/* 1st asked output */
	printf("%d\n", max);

	maxi = numNodes + 1;
	heights = (int*) can_fail_malloc(sizeof(int) * (maxi + 1));
	for (i = 0; i < maxi; i++) heights[i] = 0;
	for (i = 0; i < numNodes; i++)
	{
		/* Saves nodes which have higher hight than number of nodes in the graph + 1 in 'heights' vector */
		if (nodes[i].height >= (numNodes + 1))
		{
			heights[maxi]++;
		}

		else
		{
			heights[nodes[i].height]++;
		}
	}
	
	cut = numNodes;
	while (heights[cut] != 0)
	{
		cut--;
	}

	nodes[1].src = true;
	nodes[0].src = false;

	for (i = 2; i < numNodes; i++)
	{
		if (nodes[i].height > cut)
		{
			nodes[i].src = true;
		}
		else
		{
			nodes[i].src = false;
		}
	}

	calculateAux(nodes, 1, numNodes, &src_trg, &vctr_size);
													 

	abastecimentos_size = 0;
	abastecimentos = (int*) can_fail_malloc(sizeof(int) * numAbastecimento);

	coordinates* caminhos = (coordinates*) can_fail_malloc(sizeof(coordinates) * (vctr_size/2));
	j=0;
	for (i = 0; i < vctr_size; i+=2)
	{
		if (src_trg[i] >= (numNodes - numAbastecimento))
		{
			src_trg[i] -= numAbastecimento;
		}
		else if (src_trg[i + 1] >= (numNodes - numAbastecimento))
		{
			src_trg[i + 1] -= numAbastecimento;
		}
		if ((src_trg[i] == 1) || (src_trg[i+1] == 1))
		{
			caminhos[j].origin = src_trg[i + 1];
			caminhos[j++].destination = src_trg[i];
		}
		else if ((nodes[src_trg[i]].suplier == false) && (nodes[src_trg[i+1]].suplier == false) && (src_trg[i + 1] == src_trg[i]))
		{
			abastecimentos_size = abastecimentos_size + 1;
			abastecimentos[abastecimentos_size-1] =src_trg[i];
		}
		else if (nodes[src_trg[i]].suplier == false)
		{
			caminhos[j].origin = src_trg[i + 1];
			caminhos[j++].destination = src_trg[i];
		}
	}

	/* sorts list of 'abastecimentos' as asked for first output*/
	qsort(abastecimentos, abastecimentos_size, sizeof(int), cmpfunc);
	if (abastecimentos_size >= 1){
		printf("%d", abastecimentos[0]);
		for (i=1; i<=abastecimentos_size - 1; i++){
			printf(" %d", abastecimentos[i]);
		}
	}
	printf("\n");

	/* sorts list of coordinates as asked for last output */
	qsort(caminhos, j, sizeof(coordinates), cmpfunc2);
	for (i=0; i<j; i++){
		printf("%d %d\n",caminhos[i].origin, caminhos[i].destination);
	}
		
	freeAll(nodes, numNodes, abastecimentos, caminhos, src_trg, heights);

	return 0;
}
