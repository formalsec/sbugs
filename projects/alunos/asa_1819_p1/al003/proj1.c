#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/* Grupo 3 - João Fonseca 89476 e Tomás Lopes 89552 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NIL -1
#define INFINITY INT_MAX
#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)

typedef struct node {
	int v;
	struct node *next;
}* link;

typedef struct graph {
	int V;
	int E;
	link* adj;
}* Graph;

link ids;
int C = 0;
int m = 0;


/* ===== LIST ===== */

link list_newNode(int v) {
	link x = (link) can_fail_malloc(sizeof(struct node));
	x->v = v;
	x->next = NULL;
	return x;
}

link list_insertBegin(int v, link head) {
	link x = list_newNode(v);
	x->next = head;
	return x; 
}

void list_free(link head) {
	link x;
	while (head != NULL) {
		x = head;
		head = head->next;
		free(x);
	}
}


/* ===== GRAPH ===== */

Graph graph_init(int V) {
	int v;
	Graph G = (Graph) can_fail_malloc(sizeof(struct graph));
	G->V = V;
	G->E = 0;
	G->adj = (link*) can_fail_malloc((V+1)*sizeof(link));
	for (v = 0; v <= V; v++)
		G->adj[v] = NULL;
	return G; 
}

void graph_insertEdge(Graph G, int u, int v) {
	G->adj[u] = list_insertBegin(v, G->adj[u]);
	G->adj[v] = list_insertBegin(u, G->adj[v]);
	G->E++; 
}

void graph_DFSVisit(Graph G, int i, int* visited, int* d, int* pi,
					   int* low, int* closed, int* unsafe, int* nvertices) {
	link x;
	int suc = 0;
	int maxVertices = 1;
	low[i] = *visited;
	d[i] = *visited;
	(*visited)++;

	for (x = G->adj[i]; x != NULL; x = x->next) {
		if (d[x->v] == INFINITY) {
			suc++;
			pi[x->v] = i;
			graph_DFSVisit(G, x->v, visited, d, pi, low, closed, unsafe, nvertices);
			low[i] = MIN(low[i], low[x->v]);
			if (pi[i] != NIL && low[x->v] >= d[i] && unsafe[i] == 0) {
				C++;
				unsafe[i] = 1;
			}

		} else if (x->v != pi[i])
			low[i] = MIN(low[i], d[x->v]);
	}

	if (pi[i] == NIL && suc > 1 && unsafe[i] == 0) {
		C++;
		unsafe[i] = 1;
	}

	closed[i] = 1;

	if (unsafe[i] == 1)
		nvertices[i] = 0;
	else {
		for (x = G->adj[i]; x != NULL; x = x->next) {
			if (closed[x->v] == 1) {
				maxVertices += nvertices[x->v];
				closed[x->v] = 2;
			}
		}
		nvertices[i] = maxVertices;
	}
}

int graph_DFS(Graph G) {
	int i;
	int R = 0;
	int visited = 0;
	int* d = (int*) can_fail_malloc(((G->V)+1)*sizeof(int));
	int* pi = (int*) can_fail_malloc(((G->V)+1)*sizeof(int));
	int* low = (int*) can_fail_malloc(((G->V)+1)*sizeof(int));
	int* closed = (int*) can_fail_malloc(((G->V)+1)*sizeof(int));
	int* unsafe = (int*) can_fail_malloc(((G->V)+1)*sizeof(int));
	int* nvertices = (int*) can_fail_malloc(((G->V)+1)*sizeof(int));

	for (i = 1; i <= G->V; i++) {
		d[i] = INFINITY;
		pi[i] = NIL;
		low[i] = INFINITY;
		closed[i] = 0;
		unsafe[i] = 0;
		nvertices[i] = 0;
	}

	for (i = G->V; i >= 1; i--) {
		if (d[i] == INFINITY) {
			R++;
			ids = list_insertBegin(i, ids);
			graph_DFSVisit(G, i, &visited, d, pi, low, closed, unsafe, nvertices);
		}
	}

	for (i = 1; i <= G->V; i++)
		m = MAX(m, nvertices[i]);

	free(d);
	free(pi);
	free(low);
	free(closed);
	free(unsafe);
	free(nvertices);
	return R;
}

void graph_destroy(Graph G) {
	int i;
	for (i = 0; i <= G->V; i++)
		list_free(G->adj[i]);
	free(G->adj);
	free(G);
}


/* ===== MAIN ===== */

int main() {
	Graph G;
	int V, E, R, i, u, v;
	link x;

	scanf("%d", &V);
	scanf("%d", &E);
	G = graph_init(V);

	for (i = 0; i < E; i++) {
		scanf("%d %d", &u, &v);
		graph_insertEdge(G, u, v);
	}

	R = graph_DFS(G);

	printf("%d\n", R);

	if (ids != NULL) {
		for (x = ids; x != NULL; x = x->next)
			if (x->next == NULL)
				printf("%d", x->v);
			else
				printf("%d ", x->v);
	}
	putchar('\n');

	printf("%d\n", C);

	printf("%d\n", m);

	list_free(ids);
	graph_destroy(G);

	return 0;
}