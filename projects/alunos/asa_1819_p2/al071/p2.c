#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/*
*************************************************
* Grupo 71, Alameda.
* Andre Gaspar, 83429 e Mathieu Correia, 85186.
*
* Correr no terminal
* gcc -O3 -ansi -Wall -lm p2.c
* ./a.out < input1 > res
* diff res output1
*************************************************
*/


#include <stdio.h>
#include <stdlib.h>


/* estruturas */
typedef struct {
	int from;
	int to;
	int flow;
	int capacity;
} Edge;

typedef struct {
	int *edgeID;
	int capacityArray;
	int size;
} List;

typedef struct {
	List *adjList;
	Edge *edges;    
	int *arrayLevel;
	int counterVertex;
	int size;
} Graph;

typedef struct NodeQueue {
	int value;
	struct NodeQueue *pNext;
} NodeQueue;

typedef struct {
	NodeQueue *pStart;
	NodeQueue *pEnd;
	int size;
} Queue;


/* funcoes comparacao */
int compare_abst(const void *p, const void *q) {
    int x = *(const int *)p;
    int y = *(const int *)q;

    if (x < y)
        return -1;
    else if (x > y)
        return 1;
    return 0;
}

int compare_edges(const void *p, const void *q) {
	Edge *e1 = (Edge *)p;
  	Edge *e2 = (Edge *)q;
    int x1 = e1->to;
	int y1 = e1->from;
    int x2 = e2->to;
	int y2 = e2->from;
  
    if (x1 < x2)
        return -1;
    else if (x1 > x2)
        return 1;
	else if (y1 < y2)
		return -1;
	else if (y1 > y2)
		return 1;
    return 0;
}


/* funcoes listas */
void initList(List *pList) {
	pList->capacityArray = 10;
	pList->edgeID = (int*) can_fail_malloc(pList->capacityArray * sizeof(int));
    pList->size = 0;
}

void addEdgeIdToList(List *pList, int item) {
	if (pList->size == pList->capacityArray) {
		pList->capacityArray *= 2;
		pList->edgeID = (int*) can_fail_realloc(pList->edgeID, pList->capacityArray * sizeof(int));
	}
	
	pList->edgeID[pList->size++] = item;
}

void freeList(List *pList) {
	free(pList->edgeID);
}


/* funcoes arestas */
Edge makeEdge (int from, int to, int flow, int capacity) {
	Edge edge;
	edge.from = from;
	edge.to = to;
	edge.flow = flow;
	edge.capacity = capacity;
	
	return edge;
}

void addEdge(Graph *graph, int from, int to, int capacity) {
	Edge forwardEdge = makeEdge(from, to, 0, capacity);	
	Edge backEdge = makeEdge(to, from, 0, 0);
	
	addEdgeIdToList(&graph->adjList[from], graph->counterVertex);
	graph->edges[graph->counterVertex++] = forwardEdge;

	addEdgeIdToList(&graph->adjList[to], graph->counterVertex);
	graph->edges[graph->counterVertex++] = backEdge;
}


/* funcoes grafo */
void initGraph(Graph *graph, int numVertices, int numArestas) {
	graph->size = numVertices;
	graph->counterVertex = 0;
	graph->adjList = (List*) can_fail_malloc(numVertices * sizeof(List));
	graph->arrayLevel = (int*) can_fail_malloc(numVertices * sizeof(int));
	graph->edges = (Edge*) can_fail_malloc(numArestas * 2 * sizeof(Edge));
	
	int i=0;
	List *adjList;
	while (i < numVertices) {
		adjList = &graph->adjList[i];
		initList(adjList);
		i++;
	}
}

void freeGraph(Graph *graph) {
	free(graph->arrayLevel);
	free(graph->edges);
	
	int i=0;
	while(i < graph->size) {
		List adjList = graph->adjList[i];
		freeList(&adjList);
		i++;
	}
	
	free(graph->adjList);
}


/* funcoes fila */
void initQueue(Queue *pQueue) {
    pQueue->pStart = NULL;
    pQueue->size = 0;
}

int isQueueEmpty(Queue *pQueue) {
    return (pQueue->size == 0);
}

void enqueue(Queue *pQueue, int item) {
	NodeQueue *pNodeQueue = (NodeQueue*) can_fail_malloc(sizeof(NodeQueue));
	
	if (isQueueEmpty(pQueue)) {
		pQueue->pStart = pNodeQueue;
	}
	else {
		pQueue->pEnd->pNext = pNodeQueue;
	}
	
	pNodeQueue->value = item;
	pNodeQueue->pNext = NULL;
	pQueue->pEnd = pNodeQueue;
	pQueue->size++;
}

NodeQueue* dequeue(Queue *pQueue) {
    if (isQueueEmpty(pQueue)) {
        return NULL;
    }
    
    NodeQueue *pNodeQueue = pQueue->pStart;
    pQueue->pStart = pNodeQueue->pNext;
    pQueue->size--;
    
    return pNodeQueue;
}

void freeQueue(Queue *pQueue) {
	NodeQueue *pNodeQueue = NULL;
	while ((pNodeQueue = dequeue(pQueue)) != NULL) {
		free(pNodeQueue);
	}
}


/* funcao verifica se é possível passar mais fluxo da source à sink */
int moreFlow(Graph *graph, int source, int sink) {
	int *level = graph->arrayLevel, i;
	for (i = 0; i < graph->size; i++) {
		level[i] = -1;
	}
	level[source] = 0;
	
	Queue queue;
	initQueue(&queue);
	enqueue(&queue, source);
	
	while (!isQueueEmpty(&queue)) {
		NodeQueue *pNodeQueue = dequeue(&queue);
		int id = pNodeQueue->value;
		free(pNodeQueue);
		
		for (i = 0; i < graph->adjList[id].size; i++) {
			Edge *edge = &graph->edges[graph->adjList[id].edgeID[i]];
			
			if (level[edge->to] < 0 && edge->flow < edge->capacity) {
				level[edge->to] = level[id] + 1;
				enqueue(&queue, edge->to);
			}
		}
	}
	
	freeQueue(&queue);
	
	return (level[sink] != -1);
}


/* funcao envia múltiplos fluxos ao longo do grafo */
int sendFlow(Graph *graph, int counterVertex, int currentFlow, int sink, int *visited) {
	if (counterVertex == sink) {
		return currentFlow;
	}
	
	int sizeAdjList = (&graph->adjList[counterVertex])->size;
	int *level = graph->arrayLevel;
	
	while (visited[counterVertex] < sizeAdjList) {
		int v = graph->adjList[counterVertex].edgeID[visited[counterVertex]];
		Edge *edge = &graph->edges[v];
		
		if (level[edge->to] == level[counterVertex] + 1 && edge->flow < edge->capacity) {
			
			int minFlow = currentFlow;
			if (edge->capacity - edge->flow < minFlow) {
				minFlow = edge->capacity - edge->flow;
			}
			
			int tempFlow = sendFlow(graph, edge->to, minFlow, sink, visited);
			
			if (tempFlow > 0) {	
				edge->flow += tempFlow; 
				graph->edges[v+1].flow -= tempFlow;
				
				return tempFlow;
			}
		}

		visited[counterVertex]++;
	}
	
	return 0;
}


/* funcao retorna maxflow */
int getMaxFlow(Graph *graph, int source, int sink) {
	if (source == sink) {
		return -1;
	}
	
	int i, flow, maxFlow = 0;
	int visited[graph->size + 1];
	
	while (moreFlow(graph, source, sink)) {
		i = 0;
		while (i <= graph->size) {
			visited[i] = 0;
			i++;
		}
		
		while ((flow = sendFlow(graph, source, 2147483647, sink, visited)) != 0) {
			maxFlow += flow;
		}
	}
	
	return maxFlow;
}


/* funcao imprime corte minimo */
void getMinCut(Graph *graph, int forn, int abst, int arestas) {
	int i, j, cont1 = 0, cont2 = 0;
	int *res1 = (int*) can_fail_malloc(abst * sizeof(int));
	Edge *res2 = (Edge*) can_fail_malloc(arestas * sizeof(Edge));
	
	int visited[graph->size + 1];
	for (i = 0; i <= graph->size; i++) {
		visited[i] = 0;
	}
	visited[1] = 1;
	
	Queue queue;
	initQueue(&queue);
	enqueue(&queue, 1);

	while (!isQueueEmpty(&queue)) {
		NodeQueue *pNodeQueue = dequeue(&queue);
		int u = pNodeQueue->value;
		free(pNodeQueue);
		
		for (i = 0;i < graph->adjList[u].size; i++) {
			Edge *edge = &graph->edges[graph->adjList[u].edgeID[i]];
			
			if (visited[edge->to] == 0 && edge->flow < edge->capacity) {
				visited[edge->to] = 1;
				enqueue(&queue, edge->to);
			}
		}
	}
	
	freeQueue(&queue);

	for (i = 1; i < graph->size; i++) {

		if(visited[i] == 1) {
			
			j = 0;
			for (j = 0; j < graph->adjList[i].size; j++) {
				Edge *edge = &graph->edges[graph->adjList[i].edgeID[j]];
				
				if (visited[edge->to] == 0  && edge->to != 0 && edge->flow > 0) {

					if (edge->from > forn + 1 + abst && edge->to == edge->from - abst){
						res1[cont1++] = edge->to;
					}

					else {
						if (edge -> from > forn + abst + 1) {
							edge -> from -= abst;
						}

						if (edge -> to > forn + abst + 1) {
							edge -> to -= abst;
						}

						res2[cont2++] = *edge;
					}
				}
			}
		}
	}

	qsort(res1, cont1, sizeof *res1, &compare_abst);
	qsort(res2, cont2, sizeof *res2, &compare_edges);

	if (cont1 > 0) {
		printf("%d", res1[0]);
		for (i = 1; i < cont1; i++) {
			printf(" %d", res1[i]);
		}
	}

	printf("\n");
	
	if(cont2 > 0) {
		for (i = 0; i < cont2; i++) {
			printf("%d %d\n", res2[i].to, res2[i].from);
		}
	}
}


/* main */
int main(int argc, const char * argv[]) {
    int forn, abst, arestas;

    scanf("%d", &forn);
    scanf("%d", &abst);
    scanf("%d", &arestas);

	Graph grafo;
	initGraph(&grafo, forn + 2*abst + 2, arestas + forn + abst);

    int forn_val, abst_value, i = 0;
    while (i < forn) {
        scanf("%d", &forn_val);
        addEdge(&grafo, i + 2, 0, forn_val);
		i++;
    }

	i = 0;
    while (i < abst) {
        scanf("%d", &abst_value);
        addEdge(&grafo, forn + i + 2 + abst, forn + i + 2, abst_value);
		i++;
	}

    int o, d, c;
	i = 0;
    while (i < arestas) {
        scanf("%d %d %d", &o, &d, &c);
        if (o>forn + 1) {
  			o = o + abst;
        }
        addEdge(&grafo, d, o, c);
		i++;
    }

    printf("%d\n", getMaxFlow(&grafo, 1, 0));

	getMinCut(&grafo, forn, abst, arestas);

	freeGraph(&grafo);

    return 0;
}
