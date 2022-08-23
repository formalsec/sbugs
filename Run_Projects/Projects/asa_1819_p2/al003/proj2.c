/* Grupo 3 - João Fonseca 89476 e Tomás Lopes 89552 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

#define INFINITY INT_MAX

/* Macros for dealing with auxiliary vertices that control supplier capacities */
#define AUX(x) (x + e)
#define INVERTAUX(x) (x - e)

#define MIN(x, y) (x < y ? x : y)


/* === STRUCTS === */

typedef struct edge {
	int u;
	int v;
	int flow;
	int capacity;
}* Edge;

typedef struct node {
	void* data;
	struct node* next;
	struct node* prev;
}* link;

typedef struct graph {
	int V;
	link* adj;
}* Graph;


/* === GLOBAL VARIABLES === */

int f, e;
char* markedVertices;
link edges;
int nedges;
link vertexQueue;
link vertexQueueTail;
Edge* edgeArray;
Edge* edgeArrayAux;


/* === PROTOTYPES === */

int pushRelabel(Graph G);
void initializePreFlow(Graph G, int* h, int* e);
void discharge(Graph G, link* N, link u, int* h, int* e);
void relabel(link* N, link u, int* h);
void pushFront(link u, link v, int* e);
void pushBack(link u, link v, int* e);
void getMinCut(Graph G);
char* DFS(Graph GRT);
void DFS_Visit(Graph GRT, int u, char* color);
void merge_sort(Edge* edgeArray, int l, int r);
void merge(Edge* edgeArray, int l, int m, int r);
int less(Edge x, Edge y);
Graph graph_init(int V);
void graph_insertEdge(Graph G, int u, int v, int cap);
void graph_destroy(Graph G);
link list_newNode(void* data);
link list_insertBegin(void* data, link head, link* tail, char withTail);
link list_insertEnd(void* data, link head, link* tail);
link list_remove(link toRemove, link head, link* tail, char withTail);
void list_free(link head);


/* ===== MAIN ===== */

int main() {

	Graph G;
	int t, i, u, v, cap, prod, supp, maxFlow, isFirst;
	link x;

	scanf("%d %d %d", &f, &e, &t);

	G = graph_init(f + 2*e + 2);

	for (i = 2; i <= f+1; i++) {
		scanf("%d", &prod);
		graph_insertEdge(G, 0, i, prod);
	}

	for (i = f+2; i <= f+e+1; i++) {
		scanf("%d", &supp);
		graph_insertEdge(G, i, AUX(i), supp);
	}

	for (i = 0; i < t; i++) {
		scanf("%d %d %d", &u, &v, &cap);
		if (u >= f+2 && u < f+e+2 && v == 1)
			graph_insertEdge(G, AUX(u), v, cap);
		else {
			/* Checks for edge (v,u) when trying to add edge (u,v) */
			int found = 0;
			for (x = G->adj[v]; x != NULL; x = x->next) { 
				Edge edge = (Edge)(x->data);
				if (edge->v == u) {
					if (edge->capacity > cap) {
						edge->capacity -= cap;
					} else if (edge->capacity == cap) {
						G->adj[v] = list_remove(x, G->adj[v], NULL, 0);
					} else {
						cap -= edge->capacity;
						G->adj[v] = list_remove(x, G->adj[v], NULL, 0);
						if (u >= f+2 && u <= f+e+2 && v >= f+2 && v <= f+e+2)
							graph_insertEdge(G, AUX(u), v, cap);
						else
							graph_insertEdge(G, u, v, cap);
					}
					found = 1;
					break;
				}
			}
			if (!found) {
				if (u >= f+2 && u <= f+e+2 && v >= f+2 && v <= f+e+2)
					graph_insertEdge(G, AUX(u), v, cap);
				else
					graph_insertEdge(G, u, v, cap);
			}
		}
	}

	maxFlow = pushRelabel(G);
	
	printf("%d\n", maxFlow);

	isFirst = 1;
	for (i = 0; i < G->V; i++)
		if (markedVertices[i] && isFirst) {
			printf("%d", i);
			isFirst = 0;
		}
		else if (markedVertices[i])
			printf(" %d", i);
	putchar('\n');

	for (i = 0; i < nedges; i++)
		printf("%d %d\n", edgeArray[i]->u, edgeArray[i]->v);

	graph_destroy(G);
	free(markedVertices);
	while (edges != NULL) {
		x = edges;
		edges = edges->next;
		free(x);
	}

	free(edgeArray);

	return 0;

}


/* === PUSH-RELABEL WITH QUEUE === */

int pushRelabel(Graph G) {
	link x;
	int i;
	link* N;
	link u;
	int flow = 0;

	int* h = (int*) malloc(G->V * sizeof(int));
	int* e = (int*) malloc(G->V * sizeof(int));

	for (i = 0; i < G->V; i++) {
		h[i] = 0;
		e[i] = 0;
	}

	initializePreFlow(G, h, e);

	/* Neighbour lists are pointers to edges to improve
	   time efficiency when accessing a vertex's adjacencies */
	N = (link*) malloc(G->V * sizeof(link));
	for (i = 0; i < G->V; i++)
		N[i] = NULL;
	for (i = 0; i < G->V; i++) {
		for (x = G->adj[i]; x != NULL; x = x->next) {
			Edge edge = (Edge)(x->data);
			N[edge->u] = list_insertBegin(edge, N[edge->u], NULL, 0);
			N[edge->v] = list_insertBegin(edge, N[edge->v], NULL, 0);
		}
	}

	u = vertexQueue;

	while (u != NULL) {
		discharge(G, N, u, h, e);
		u = u->next;
		vertexQueue = list_remove(vertexQueue, vertexQueue, &vertexQueueTail, 1);
	}

	flow = e[1];

	for (i = 0; i < G->V; i++) {
		while (N[i] != NULL) {
			x = N[i];
			N[i] = N[i]->next;
			free(x);
		}
	}
	
	free(N);
	free(h);
	free(e);

	markedVertices = (char*) malloc(G->V * sizeof(char));
	for (i = 0; i < G->V; i++)
		markedVertices[i] = 0;

	getMinCut(G);

	list_free(vertexQueue);

	return flow;
}

void initializePreFlow(Graph G, int* h, int* e) {
	link x;
	h[0] = G->V;
	for (x = G->adj[0]; x != NULL; x = x->next) {
		int* vertex = (int*) malloc(sizeof(int));
		Edge edge = (Edge)(x->data);
		edge->flow = edge->capacity;
		e[edge->v] = edge->capacity;
		*vertex = edge->v;
		vertexQueue = list_insertBegin(vertex, vertexQueue, &vertexQueueTail, 1);
		e[0] -= edge->capacity; 
	}
}

void discharge(Graph G, link* N, link u, int* h, int* e) {
	int from = *((int*)(u->data));
	link v = N[from];
	Edge edge;

	while (e[from] > 0) {
		if (v == NULL) {
			relabel(N, u, h);
			v = N[from];
		}
		else {
			edge = (Edge)(v->data);
			/* Differentiates between admissible edges starting from u and edges ending in u */
			if (from == edge->u && edge->capacity - edge->flow > 0 && h[from] == h[edge->v] + 1) {
				pushFront(u, v, e);
			} else if (from == edge->v && edge->flow > 0 && h[from] == h[edge->u] + 1) {
				pushBack(u, v, e);
			} else {
				v = v->next;
			}
		}
	}
}

void relabel(link* N, link u, int* h) {
	link x;
	int minh = INFINITY;
	int from = *((int*)(u->data));
	Edge edge;

	for (x = N[from]; x != NULL; x = x->next) {
		edge = (Edge)(x->data);
		if (from == edge->u && edge->capacity - edge->flow > 0)
			minh = MIN(minh, h[edge->v]);
		else if (from != edge->u && edge->flow > 0)
			minh = MIN(minh, h[edge->u]);
	}

	h[from] = 1 + minh;
}

void pushFront(link u, link v, int* e) {
	int from = *((int*)(u->data));
	Edge edge = (Edge)(v->data);
	int to = edge->v;
	int cf = edge->capacity - edge->flow;
	int f = MIN(e[from], cf);
	int olde = e[to];
	edge->flow += f;
	e[from] -= f;
	e[to] += f;
	if (olde == 0 && e[to] > 0 && to != 0 && to != 1) {
		int* vertex = (int*) malloc(sizeof(int));
		*vertex = to;
		vertexQueue = list_insertEnd(vertex, vertexQueue, &vertexQueueTail);
	}

}

void pushBack(link u, link v, int* e) {
	int from = *((int*)(u->data));
	Edge edge = (Edge)(v->data);
	int to = edge->u;
	int f = MIN(e[from], edge->flow);
	int olde = e[to];
	edge->flow -= f;
	e[from] -= f;
	e[to] += f;
	if (olde == 0 && e[to] > 0 && to != 0 && to != 1) {
		int* vertex = (int*) malloc(sizeof(int));
		*vertex = to;
		vertexQueue = list_insertEnd(vertex, vertexQueue, &vertexQueueTail);
	}
}


/* === MINIMUM CUT === */

void getMinCut(Graph G) {
	int i;
	char* color;
	link x;

	/* Creates transpose residual graph
	   Edge capacities are irrelevant: initialized at 0 arbitrarily */
	Graph GRT = graph_init(G->V); 
	nedges = 0;
	for (i = 0; i < G->V; i++) {
		for (x = G->adj[i]; x != NULL; x = x->next) {
			Edge edge = (Edge)(x->data);
			if (edge->flow == 0)
				graph_insertEdge(GRT, edge->v, edge->u, 0);
			else if (edge->flow == edge->capacity)
				graph_insertEdge(GRT, edge->u, edge->v, 0);
			else {
				graph_insertEdge(GRT, edge->v, edge->u, 0);
				graph_insertEdge(GRT, edge->u, edge->v, 0);
			}
		}
	}

	color = DFS(GRT);
	graph_destroy(GRT);

	/* Marks edges and vertices for output */
	for (i = 0; i < G->V; i++)
		for (x = G->adj[i]; x != NULL; x = x->next) {
			Edge edge = (Edge)(x->data);
			if (color[edge->u] == WHITE && color[edge->v] != WHITE) {
				if (edge->u >= f+2 && edge->u <= f+e+1 && edge->v == AUX(edge->u))
					markedVertices[i] = 1;
				else if (edge->v < 2 || edge->v > f+1) {
					nedges++;
					edges = list_insertBegin(edge, edges, NULL, 0);
				}
			}
		}

	free(color);

	/* Changes edge notation for edges stemming from auxiliary vertices to show correct number */
	for (x = edges; x != NULL; x = x->next) {
		Edge edge = (Edge)(x->data);
		if ((edge->u >= f+e+2 && edge->v == 1) || (edge->u >= f+e+2 && edge->v >= f+2 && edge->v <= f+e+2))
			edge->u = INVERTAUX(edge->u);
	}

	edgeArray = (Edge*) malloc(nedges * sizeof(Edge));
	edgeArrayAux = (Edge*) malloc(nedges * sizeof(Edge));
	for (i = 0, x = edges; i < nedges; i++, x = x->next)
		edgeArray[i] = x->data;
	merge_sort(edgeArray, 0, nedges-1);

	free(edgeArrayAux);
}


/* === DFS === */

char* DFS(Graph GRT) {
	int i;
	char* color = (char*) malloc(GRT->V * sizeof(char));
	for (i = 0; i < GRT->V; i++) {
		markedVertices[i] = 0;
		color[i] = WHITE;
	}
	DFS_Visit(GRT, 1, color);

	return color;
}

void DFS_Visit(Graph GRT, int u, char* color) {
	link x;
	color[u] = GRAY;
	for (x = GRT->adj[u]; x != NULL; x = x->next) {
		Edge edge = (Edge)(x->data);
		int v = edge->v;
		if (color[v] == WHITE)
			DFS_Visit(GRT, v, color);
	}
	color[u] = BLACK;
}


/* === MERGE SORT === */

void merge_sort(Edge* edgeArray, int l, int r) { 
  int m = (r+l)/2;

  if (r <= l)
    return;

  merge_sort(edgeArray, l, m);
  merge_sort(edgeArray, m+1, r);
  merge(edgeArray, l, m, r);
}

void merge(Edge* edgeArray, int l, int m, int r) {
  int i, j, k;
  for (i = m+1; i > l; i--) 
    edgeArrayAux[i-1] = edgeArray[i-1];
  for (j = m; j < r; j++)
    edgeArrayAux[r+m-j] = edgeArray[j+1];
  for (k = l; k <= r; k++)
    if (less(edgeArrayAux[j], edgeArrayAux[i]))
      edgeArray[k] = edgeArrayAux[j--];
    else
      edgeArray[k] = edgeArrayAux[i++];
}

int less(Edge x, Edge y) {
	if (x->u < y->u || (x->u == y->u && x->v < y->v))
		return 1;
	else
		return 0;
}


/* ===== GRAPH ===== */

Graph graph_init(int V) {
	int i;
	Graph G = (Graph) malloc(sizeof(struct graph));
	G->V = V;
	G->adj = (link*) malloc(V * sizeof(link));
	for (i = 0; i < V; i++)
		G->adj[i] = NULL;
	return G; 
}

void graph_insertEdge(Graph G, int u, int v, int cap) {
	Edge data = (Edge) malloc(sizeof(struct edge));
	data->u = u;
	data->v = v;
	data->flow = 0;
	data->capacity = cap;
	G->adj[u] = list_insertBegin(data, G->adj[u], NULL, 0);
}

void graph_destroy(Graph G) {
	int i;
	for (i = 0; i < G->V; i++)
		list_free(G->adj[i]);
	free(G->adj);
	free(G);
}


/* ===== DOUBLY LINKED LIST WITH HEAD AND TAIL ===== */

link list_newNode(void* data) {
	link x = (link) malloc(sizeof(struct node));
	x->data = data;
	x->next = NULL;
	x->prev = NULL;
	return x;
}

link list_insertBegin(void* data, link head, link* tail, char withTail) {
	link x = list_newNode(data);
	if (head == NULL && withTail)
		*tail = x;
	x->next = head;
	x->prev = NULL;
	if (head != NULL)
		head->prev = x;
	return x; 
}

link list_insertEnd(void* data, link head, link* tail) {
	link x = list_newNode(data);
	x->next = NULL;
	x->prev = *tail;
	if (head == NULL)
		head = x;
	*tail = x;
	if (x->prev != NULL)
		x->prev->next = x;
	return head; 
}

link list_remove(link toRemove, link head, link* tail, char withTail) {
	if (toRemove == head)
		head = head->next;
	if (toRemove->next != NULL)
		toRemove->next->prev = toRemove->prev;
	if (toRemove->prev != NULL)
		toRemove->prev->next = toRemove->next;
	if (toRemove->next == NULL && withTail)
		*tail = toRemove->prev;
	free(toRemove->data);
	free(toRemove);
	return head;
}

void list_free(link head) {
	link x;
	while (head != NULL) {
		x = head;
		head = head->next;
		free(x->data);
		free(x);
	}
}