/*
Analise e Sintese de Algoritmos
Projeto 1

Sofia Carvalho ist189539
Miguel Gonçalves ist189507
*/


#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) a < b ? a : b
#define MAX(a, b) a > b ? a : b
#define ROOT (predecessor == -1)
#define VISITED(v) (d[v] != -1)
#define TRUE 1
#define FALSE 0

/* LINKED LISTS ASSETS */

typedef struct node {
	int value;
	struct node* next;
}* Link;

typedef struct list {
	Link head;
}* List;


List init_list() {
	List l = (List) malloc(sizeof(struct list));
	l->head = NULL;
	return l;
}

void insert_list(List l, int v) {
	Link new = (Link) malloc(sizeof(struct node));
	new->value = v;
	new->next = l->head;
	l->head = new;
}

void remove_from_list(List l, int v) {
	Link x, aux;
	if (l->head == NULL) return;

	if (l->head->value == v) {
		x = l->head;
		l->head = x->next;
	}

	else {
		for (aux = l->head; aux->next != NULL && aux->next->value != v ; aux = aux->next);
		if ((x=aux->next) == NULL) return;
		aux->next = x->next;
	}
	free(x);
}

void clear_list(List l) {
	Link x = l->head, aux;
	while (x != NULL) {
		aux = x;
		x = aux->next;
		free(aux);
	}
	l->head=NULL;
}

/* END OF LINKED LISTS ASSETS */


/*
Quicksort comparator
*/
int comparator(const void* a, const void* b) {
	return *(int*)a > *(int*)b;
}

/*
aux_findBiggestSubgraph: an auxiliar function to "findBiggestSubgraph" to visit a vertice
Arguments:  a linked list representing a graph,
			the number of vertices,
			the current vertice,
			an array of visited vertices,
			the current count of vertices
Return: nothing
*/
void aux_findBiggestSubgraph(List* graph, int numVertices, int v, int* visited, int* size) {
	Link aux;
	visited[v] = 1;

	for (aux = graph[v]->head; aux != NULL; aux = aux->next)
        if (!visited[aux->value]) 
        	aux_findBiggestSubgraph(graph, numVertices, aux->value, visited, size);

	(*size)++; /* counts all the "reachable" vertices */
}	


/*
findBiggestSubgraph: an auxiliar function to "performAlgorithm" to find the biggest subgraph if all the critical points were removed
Arguments:  a linked list representing a graph,
			the number of vertices,
Return: the number of vertices in the biggest subgraph
*/
int findBiggestSubgraph(List* graph, int numVertices) {
	int i, maxSize = 0, size;
	int* visited = (int*) malloc(sizeof(int)*(numVertices));		/* 0 = not visited, 1 = visited */

	/* INITIALIZATION */
	for (i=0; i < numVertices; i++) {
		if (graph[i]->head != NULL && graph[i]->head->value == -1) /* if i is marked as "deleted" */
			visited[i]=1; /* marks "deleted" vertices as visited */
		else visited[i] = 0;
	}

	/* PROCESSING */
	for (i=0; i < numVertices; i++)
		if (!visited[i]) {
			size = 0;
			aux_findBiggestSubgraph(graph, numVertices, i, visited, &size);
			maxSize = MAX(size, maxSize);
		}

	free(visited);
	return maxSize;
}


/*
visit: an auxiliar function to "performAlgorithm" to visit a vertice in a dfs
Arguments:  a linked list representing a graph,
			the number of vertices,
			the index of the vertice in which to apply the algorithm,
			information arrays (d, low),
			the time counter,
			the number of critical vertices
Return: the highest vertice index of all the successors of the visited vertice
*/
int visit(List* graph, int numVertices, int v, int predecessor, int* d, int* low, int* t, int* numCriticals) {
    int u, id, subGraphId = v, children = 0, critical = FALSE;
    Link aux;
    
    d[v] = (*t)++;
    low[v] = d[v];

	for (aux = graph[v]->head; aux != NULL; aux = aux->next) {
    	u = aux->value;
    	if (!VISITED(u)) {
            children++;
            id = visit(graph, numVertices, u, v, d, low, t, numCriticals);
            low[v] = MIN(low[u], low[v]);
            subGraphId = MAX(id, subGraphId);
            if (!ROOT && low[u] >= d[v]) critical = TRUE;
        }
        else if (u != predecessor) low[v] = MIN(d[u], low[v]);
    }
    if (ROOT && children > 1) critical = TRUE;

    if (critical) {
    	(*numCriticals)++;
		clear_list(graph[v]);	/* List of v's adjacencies won't be needed anymore */
		insert_list(graph[v], -1); /* Marks v as deleted */
    }

    return subGraphId;
}


/*
performAlgorithm: function to solve the project's problem
Arguments: 	a linked list representing a graph,
			the number of vertices
Return: nothing
*/
void performAlgorithm(List* graph, int numVertices) {
	int i, t = 1, maxVertices = 0, numCriticals = 0;			/* t - time */
	Link aux;

	/* DECLARATION */	
	int* d = (int*) malloc(sizeof(int)*(numVertices));		/* d - discovery time */
	int* low = (int*) malloc(sizeof(int)*(numVertices));
	int numSubGraphs = 0;
	List subGraphs = init_list();	/* subGraphs list will store the ids of the subGraphs */

	/* INITIALIZATION */
	for (i=0; i < numVertices; i++) {
		d[i] = -1;
		low[i] = -1;
	}

	/* PROCESSING */
	for (i=0; i < numVertices; i++)
		if (!VISITED(i)) {
			numSubGraphs++;
			insert_list(subGraphs, visit(graph, numVertices, i, -1, d, low, &t, &numCriticals));
		}
	free(d);
	free(low);

	/* SORTING SUBGRAFS ID */
   	int* subAux = (int*) malloc(sizeof(int)*numSubGraphs);		/* subAux array is used to sort the ids */
	for (i=0, aux = subGraphs->head; aux != NULL; aux = aux->next, i++)
		subAux[i] = aux->value;
    qsort(subAux, numSubGraphs, sizeof(int), comparator);

    /* PRINT OUTPUT */
	printf("%d\n", numSubGraphs);
	for (i=0; i < numSubGraphs-1; i++)
		printf("%d ", subAux[i]+1);
	printf("%d\n", subAux[i]+1);
	printf("%d\n", numCriticals);

	/* FREE ALLOCATED MEMORY */
	clear_list(subGraphs);
	free(subGraphs);
	free(subAux);
	
	/* FIND AND PRINT BIGGEST SUBGRAPH */
	maxVertices = findBiggestSubgraph(graph, numVertices);
	printf("%d\n", maxVertices);
}


int main(int argc, char* argv[]) {
	int i, v1, v2, numRouters, numConnections;
	
	/* INPUT PROCESSING */
	scanf("%d\n %d", &numRouters, &numConnections);

	List* network = (List*) malloc(sizeof(List)*(numRouters));
	for (i=0; i<numRouters; i++)
		network[i] = init_list();

	for (i=0; i<numConnections; i++) {
		scanf("%d %d", &v1, &v2);
		insert_list(network[v1-1], v2-1);
		insert_list(network[v2-1], v1-1);
	}

	/* PERFORM ALGORITHM */
	performAlgorithm(network, numRouters);

	/* FREE NETWORK */
	for (i=0; i<numRouters; i++) {
		if (network[i] != NULL)
			clear_list(network[i]);
		free(network[i]);
	}
	free(network);

	return 0;
}


