#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/****************************************************************************/
/*				         		 ASA - PROJETO 2                    		*/
/*																			*/
/* Grupo 33 	   No 92433, 92442  	                                	*/
/****************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CITIZEN -3
#define SUPERMARKET -2
#define NOTHING -1
#define SOURCE -4
#define SINK -5
#define WHITE 1
#define GREY 2
#define BLACK 3
#define INFINITE 1000000

/****************************************************************************/
/*                               STRUCTURES                                 */
/****************************************************************************/

typedef struct adjListNode_t {
	struct crossroads_t *from;
	struct crossroads_t *dest;
	struct adjListNode_t *next;
	struct adjListNode_t *originalEdge;
	struct adjListNode_t *reverseEdge;
	bool isItMain;
	int capacity;
	int flow;
} AdjListNode_t;

typedef struct crossroads_t {
	int index;
	int type; /* CITIZEN, SUPERMARKET, SOURCE, SINK OR NOTHING*/
	bool done;
	AdjListNode_t *head;
	bool revEdge;
	int color;
} Crossroads_t;

typedef struct graph_t {
	Crossroads_t **vertex;
	int size;
} Graph_t;

typedef struct node_t {
	Crossroads_t *crossroad;
	struct node_t *next;
} Node_t;

typedef struct list_t {
	Node_t *head;
	Node_t *last;
} List_t;

/****************************************************************************/
/*                               PROTOTYPES                                 */
/****************************************************************************/
void processInput();
int calculateIndex(int avenue, int street);
Crossroads_t *createNewCrossroads(int index, int type);
Graph_t *createGraph(int m, int n);
void addEdge(Graph_t *g, int from, int dest);
void displayMaxFlow(int flow);
void placeInCrossroad(int index, int type);
int edmondsKarpAlgorithm(Graph_t *graph, Crossroads_t *source, Crossroads_t *sink);
void augmentFlowEdge(AdjListNode_t *edge, int flow);
Node_t *newNode();
void printAdjList(Crossroads_t *u);

/****************************************************************************/
/*                               VARIABLES                                  */
/****************************************************************************/

int numberAvenues;
int numberStreets;
int numberCitizens = 0;
int numberSupermarkets = 0;
int maxFlow = 0;
Graph_t *manhattan;

/****************************************************************************/
/*                               FUNCTIONS                                  */
/****************************************************************************/

void processInput() {
	int i = 0, j = 0, avenue = 0, street = 0, retvalue = 0, index = 0;

	retvalue = scanf("%d %d", &numberAvenues, &numberStreets);
	retvalue = scanf("%d %d", &numberSupermarkets, &numberCitizens);

	manhattan = createGraph(numberAvenues, numberStreets);

	for (i = 0; i < numberSupermarkets; i++) {
		retvalue = scanf("%d %d", &avenue, &street);
		index = calculateIndex(avenue, street);
		placeInCrossroad(index, SUPERMARKET);
		addEdge(manhattan, index, manhattan->size - 1);
	}

	for (j = 0; j < numberCitizens; j++) {
		retvalue = scanf("%d %d", &avenue, &street);
		index = calculateIndex(avenue, street);
		placeInCrossroad(index, CITIZEN);
		addEdge(manhattan, 0, index);
	}
	retvalue++;
}

int calculateIndex(int avenue, int street) {
	avenue--;
	return street + (numberStreets * avenue);
}

/* Initializes a new crossroad */
Crossroads_t *createNewCrossroads(int index, int type) {
	Crossroads_t *newCrossroad = (Crossroads_t *)can_fail_malloc(sizeof(Crossroads_t));

	newCrossroad->index = index;
	newCrossroad->type = type;
	newCrossroad->head = NULL;
	newCrossroad->revEdge = false;
	newCrossroad->color = WHITE;
	newCrossroad->done = false;
	return newCrossroad;
}

/* Changes the type of place of a Crossroad given the index */
void placeInCrossroad(int index, int type) {
	if (manhattan->vertex[index] != NULL)
		manhattan->vertex[index]->type = type;
}

void printAdjList(Crossroads_t *u) {
	AdjListNode_t *aux = NULL;
	for (aux = u->head; aux != NULL; aux = aux->next) {
		printf("dest: %d\n ", aux->dest->index);
		printf("->\n");
	}
}

/* Initiates a new graph representing the city of Manhattan */
Graph_t *createGraph(int m, int n) {
	int i = 1;
	int size = (m * n) + 2;
	Graph_t *manhattan = (Graph_t *)can_fail_malloc(sizeof(Graph_t));

	manhattan->size = size;

	manhattan->vertex = (Crossroads_t **)can_fail_malloc(size * sizeof(Crossroads_t) + 1);

	Crossroads_t *source = createNewCrossroads(0, SOURCE);
	Crossroads_t *sink = createNewCrossroads(size - 1, SINK);

	manhattan->vertex[0] = source;
	manhattan->vertex[size - 1] = sink;

	for (i = 0; i < size - 1; i++) {
		manhattan->vertex[i] = createNewCrossroads(i, NOTHING);
	}

	for (i = 2; i < size - 1; i++) {
		if ((i - 1) % n == 0)
			i++;
		addEdge(manhattan, i, i - 1);
		addEdge(manhattan, i - 1, i);
	}
	for (i = 1; i + n < size - 1; i++) {
		addEdge(manhattan, i, i + n);
		addEdge(manhattan, i + n, i);
	}
	return manhattan;
}

void addEdge(Graph_t *g, int from, int dest) {
	AdjListNode_t *newEdge = (AdjListNode_t *)can_fail_malloc(sizeof(AdjListNode_t));
	newEdge->from = g->vertex[from];
	newEdge->dest = g->vertex[dest];
	newEdge->next = NULL;
	newEdge->capacity = 1;
	newEdge->flow = 0;
	newEdge->isItMain = true;
	newEdge->originalEdge = newEdge;
	newEdge->reverseEdge = NULL;
	if (g->vertex[from]->head == NULL) {
		g->vertex[from]->head = newEdge;
		return;
	}
	AdjListNode_t *aux = g->vertex[from]->head;
	while (aux->next != NULL)
		aux = aux->next;
	aux->next = newEdge;
}

void addReverseEdge(Graph_t *g, AdjListNode_t *original, int capacity) {
	AdjListNode_t *newEdge = (AdjListNode_t *)can_fail_malloc(sizeof(AdjListNode_t));
	newEdge->from = original->dest;
	newEdge->dest = original->from;
	newEdge->next = NULL;
	newEdge->capacity = capacity;
	newEdge->flow = 0;
	newEdge->isItMain = false;
	newEdge->originalEdge = original;
	newEdge->reverseEdge = NULL;
	original->reverseEdge = newEdge;
	int index = original->dest->index;
	if (!g->vertex[index]->revEdge) {
		g->vertex[index]->revEdge = true;
		return;
	}
}

List_t *newList() {
	List_t *l = (List_t *)can_fail_malloc(sizeof(List_t));
	l->head = NULL;
	l->last = NULL;
	return l;
}

Node_t *newNode() {
	Node_t *l = (Node_t *)can_fail_malloc(sizeof(Node_t));
	l->next = NULL;
	l->crossroad = NULL;
	return l;
}

void printlist(Node_t *u) {
	Node_t *aux = NULL;
	for (aux = u; aux != NULL; aux = aux->next) {
		printf("dest: %d\n", aux->crossroad->index);
	}
}

List_t *pushFirst(List_t *l, Crossroads_t *c) {
	Node_t *node = newNode(), *aux = l->last;
	node->crossroad = c;
	node->next = NULL;
	if (l->head == NULL && l->last == NULL) {
		l->head = node;
		l->last = NULL;
		l->head->next = l->last;
		return l;
	} else if (l->head != NULL && l->last == NULL) {
		l->last = node;
		l->head->next = l->last;
		return l;
	} else if (aux != NULL && aux->next == NULL) {
		aux->next = node;
		l->last = aux->next;
		return l;
	}
	return NULL;
}

Crossroads_t *popLast(List_t *l) {
	Node_t *aux = l->head;
	if (aux != NULL) {
		l->head = l->head->next;
		aux->next = NULL;
		Crossroads_t *c = aux->crossroad;
		aux->crossroad = NULL;
		return c;
	}
	return NULL;
}

int min(int a, int b) {
	if (a < b)
		return a;
	return b;
}

void augmentFlowEdge(AdjListNode_t *edge, int flow) {
	if (edge->isItMain) {
		edge->flow += flow;
	} else {
		edge->originalEdge->flow -= flow;
	}
}

int residualCap(AdjListNode_t *edge) {
	int residualCap = 0;
	residualCap = edge->capacity - edge->flow;
	return residualCap;
}

int bfs(Crossroads_t *start, AdjListNode_t **parents) {
	int i = 0, flow = 1, vIx = 0, startIx = 0;
	List_t *queue = newList();
	List_t *nonWhites = newList();
	Node_t *aux = NULL;
	AdjListNode_t *v = NULL;
	Crossroads_t *u = NULL;

	parents[startIx] = NULL;

	for (i = 0; i < manhattan->size; i++) {
		parents[i] = NULL;
	}

	start->color = GREY;
	start->done = false;
	manhattan->vertex[manhattan->size - 1]->done = false;

	nonWhites = pushFirst(nonWhites, start);
	queue = pushFirst(queue, start);
	while (queue->head != NULL) {
		u = popLast(queue);

		for (v = u->head; v != NULL; v = v->next) {
			if (v->dest->color == WHITE && residualCap(v) > 0 && v->from->type != SINK && !v->dest->done) {
				vIx = v->dest->index;
				v->dest->color = GREY;
				parents[vIx] = v;
				flow = residualCap(v);
				queue = pushFirst(queue, v->dest);
				nonWhites = pushFirst(nonWhites, v->dest);
			}
			if (v->reverseEdge != NULL && v->reverseEdge->dest->color == WHITE && !v->dest->done) {
				vIx = v->reverseEdge->from->index;
				v->reverseEdge->from->color = GREY;
				parents[vIx] = v->reverseEdge;
				flow = residualCap(v->reverseEdge);
				queue = pushFirst(queue, v->reverseEdge->from);
				nonWhites = pushFirst(nonWhites, v->reverseEdge->from);
			}
			if (v->dest->type == SINK) {
				parents[manhattan->size - 1] = v;
				for (aux = nonWhites->head; aux->next != NULL; aux = aux->next) {
					aux->crossroad->color = WHITE;
				}
				return flow;
			}

			u->color = BLACK;
		}
	}

	return 0;
}

int edmondsKarpAlgorithm(Graph_t *graph, Crossroads_t *source, Crossroads_t *sink) {
	int moreFlow = -1, current = 0, i = 0;

	AdjListNode_t **parents = (AdjListNode_t **)can_fail_malloc(manhattan->size * sizeof(AdjListNode_t *));
	AdjListNode_t *previous = NULL;

	for (i = 0; i < manhattan->size; i++) {
		parents[i] = NULL;
	}

	while (moreFlow != 0) {
		moreFlow = bfs(source, parents);
		if (!moreFlow) break;
		maxFlow += moreFlow;
		current = manhattan->size - 1; /*sink*/

		while (current > 0) /*!= source*/
		{
			previous = parents[current];
			if (previous != NULL) {
				if (previous->isItMain && previous->reverseEdge == NULL) {
					addReverseEdge(manhattan, previous, moreFlow);
				}
				augmentFlowEdge(previous, moreFlow);
				if (previous->dest->type == CITIZEN)
					previous->dest->done = true;
				current = previous->from->index;
			}
		}
	}
	return maxFlow;
}

void displayMaxFlow(int flow) {
	printf("%d\n", flow);
}

int main() {
	processInput();
	displayMaxFlow(edmondsKarpAlgorithm(manhattan, manhattan->vertex[0], manhattan->vertex[manhattan->size - 1]));
	return 0;
}
