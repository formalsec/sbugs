#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define NIL -1

struct AdjListNode {
	int dest, nota;
	struct AdjListNode* next;
};

struct AdjList {
	struct AdjListNode* head;
};

struct Graph {
	int V;
	struct AdjList* array;
};

struct AdjListNode* NewAdjListNode(int dest) {
	struct AdjListNode* newNode = (struct AdjListNode*) can_fail_malloc(sizeof(struct AdjListNode));
	newNode->dest = dest;
	newNode->next = NULL;
	return newNode;
}

struct Graph* createGraph(int V) {
	struct Graph* graph = (struct Graph*) can_fail_malloc(sizeof(struct Graph));
	graph->V = V;
	graph->array = 
		(struct AdjList*) can_fail_malloc((V + 1) * sizeof(struct AdjList));
	int i;
	for(i = 0; i <= V; i++) {
		graph->array[i].head = NULL;
	}
	return graph;
}

void FREEgraph(struct Graph* g) {
	struct AdjListNode* t;
	struct AdjListNode* prev;
	int i;
	for(i = 0; i < g->V; i++) {
		for(t = g->array[i].head, prev = NULL; t != NULL; prev = t, t = t->next) {
			if(prev != NULL) 
				free(prev);
		}
	}
	free(g->array);
	free(g);
}

void addEdge(struct Graph* graph, int src, int dest) {
	struct AdjListNode* newNode = NewAdjListNode(dest);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;
}

void printGraph(struct Graph *g, int* alunos) {
	int i;
	for(i = 0; i < g->V; i++) {
		struct AdjListNode* adj = g->array[i].head;
		printf("Vertices adjacentes ao vertice %d\n", i);
		while(adj != NULL) {
			printf(" (%d -> %d)\n",i ,adj->dest);
			adj = adj->next;
		}
		printf("\n");
	}
	printf("==========Fim==========\n\n");
}

/*void DFS(struct Graph* g, int u, int visited[], int* alunos) {
	struct AdjListNode* t;
	visited[u] = 1;
	for(t = g->array[u].head; t != NULL; t = t->next) {
		int v = t->dest;
		if(visited[v] == 0) {
			DFS(g, v, visited, alunos);
		}
		if(alunos[v] > alunos[u]) {
				alunos[u] = alunos[v];
		}
	}
}*/

void DFS(struct Graph* g, int u, int visited[], int disc[], 
			int low[], int parent[], int ap[], int alunos[], int time) {
	struct AdjListNode* t;
	visited[u] = 1;
	int children = 0;
	disc[u] = time + 1;
	low[u] = disc[u];
	for(t = g->array[u].head; t != NULL; t = t->next) {
		int v = t->dest;
		children++;
		if(visited[v] == 0) {
			parent[v] = u;
			DFS(g, v, visited, disc, low, parent, ap, alunos, time + 1);
			if(low[u] > low[v]) {
				low[u] = low[v];
			}
			if(parent[u] == NIL && children > 1)
				ap[u] = 1;
			if(parent[u] != NIL && low[v] >= disc[u])
				ap[u] = 1;
		}
		else if(v != parent[u]) {
			if(low[u] > disc[v]) {
				low[u] = disc[v];
			}
		}
		if(alunos[v] > alunos[u]) {
				alunos[u] = alunos[v];
		}
	}
}

int main() {
	int Nalunos = 0, Nfriends = 0, foo = 0, i = 0, r = 0;
	int *alunos, *visited, *disc, *low, *parent, *ap;
	r = scanf("%i,%i", &Nalunos, &Nfriends);
	struct Graph *g = createGraph(Nalunos);
	alunos = (int*) can_fail_malloc((1 + Nalunos)*sizeof(int));
	visited = (int*) can_fail_malloc((1 + Nalunos)*sizeof(int));
	disc = (int*) can_fail_malloc((1 + Nalunos)*sizeof(int));
	low = (int*) can_fail_malloc((1 + Nalunos)*sizeof(int));
	parent = (int*) can_fail_malloc((1 + Nalunos)*sizeof(int));
	ap = (int*) can_fail_malloc((1 + Nalunos)*sizeof(int));
	memset(alunos, 0, 1+ Nalunos);
	memset(visited, 0, 1+ Nalunos);
	memset(disc, 0, 1+ Nalunos);
	memset(parent, 0, 1+ Nalunos);
	memset(low, 0, 1+ Nalunos);
	memset(ap, 0, 1+ Nalunos);
	for(i = 1; i < Nalunos + 1; i++) {
		r = scanf("%i", &foo);
		alunos[i] = foo;
	}
	for(i = 0; i < Nfriends; i++) {
		int u = 0, v = 0;
		r = scanf("%d %d", &u, &v);
		addEdge(g, u, v);
	}
	DFS(g, 1, visited, disc, low, parent, ap, alunos, 0);

	for(r = 1; r != Nalunos + 1; r++) {
		printf("%d\n", alunos[r]);
	}
	return 0;
}