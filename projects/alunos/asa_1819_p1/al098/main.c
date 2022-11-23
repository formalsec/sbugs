#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/* 89463 Inês Silva */
/* 89522 Pedro Galhardo */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ((a > b) ? a: b)
#define min(a, b) ((a < b) ? a: b)

typedef struct key_list {
	int i;
	struct key_list * next;
} * KeyList;

typedef struct answer {
	int R, C, m;
	KeyList Keys;
} * Answer;

typedef struct vertex * Vertex;

typedef struct adj_vertex {
	Vertex vertex;
	struct adj_vertex * next;
} * AdjVertex;

struct vertex {
	int id, discovery, parent, critical, low;
	AdjVertex head;
};

typedef struct graph {
	Vertex array;
	int N;
} * Graph;

int DFS(Graph g, Answer a, int v, int depth, int update) {
	int w, i = 0, critical = 0;
	AdjVertex adj;
	g->array[v].discovery = g->array[v].low = depth;

	if (g->array[v].id == -1) return --depth;

	for (adj = g->array[v].head; adj != NULL; adj = adj->next) {
		w = adj->vertex->id;

		/* tagged vertex to be ignored */
		if (w == -1) { continue; }

		if (!g->array[w].discovery) {
			g->array[w].parent = v + 1; i++;
			depth = DFS(g, a, w, ++depth, update);

			if (g->array[w].low >= g->array[v].discovery)
				critical = 1;
			g->array[v].low = min(g->array[v].low, g->array[w].low);
		}
	
        /* back edge */
		else if (g->array[v].parent != (w + 1))
			g->array[v].low = min(g->array[v].low, g->array[w].discovery);
	}

	/* case #1 : DFS tree root with 2+ children
	 * case #2 : !(DFS tree root or leaf) & low(this) >= discovery(parent) */
	if (update && ((!g->array[v].parent && i > 1) || (g->array[v].parent && critical))) {
		g->array[v].critical = 1;
		a->C++;
	}
	
	return ++depth;
}

void removeCritical(Graph g) {
	int i;

	for (i = 0; i < g->N; i++) {
		g->array[i].discovery = 0;
		if (g->array[i].critical)
			g->array[i].id = -1;
	}
}

void link(Graph g, int a, int b) {
	Vertex v = &g->array[a-1];
	AdjVertex new = can_fail_malloc(sizeof(struct adj_vertex));
	
	new->vertex = &g->array[b-1];
	new->next = v->head;
	v->head = new;
}

void parseInput(Graph g) {
	int a, b, i, M;
	assert(scanf("%d\n%d", &g->N, &M));

	g->array = can_fail_calloc(g->N, sizeof(struct vertex));
	for (i = 0; i < g->N; i++) {
		g->array[i].head = NULL;
		g->array[i].id = i;
	}

	for (i = 0; i < M; i++) {
		assert(scanf("%d %d", &a, &b));
		link(g, a, b);
		link(g, b, a); /* bidirectional */
	}
}

void displayResults(Answer a) {
	KeyList aux = a->Keys;
	
	printf("%d\n%d", a->R, a->Keys->i);
	a->Keys = a->Keys->next;
	free(aux);

	while (a->Keys) {
		printf(" %d", a->Keys->i);
		aux = a->Keys; a->Keys = a->Keys->next;
		free(aux);
	}
	
	printf("\n%d\n%d\n", a->C, a->m);
}

void freeGraph(Graph g) {
	int i, N = g->N;
	AdjVertex aux;

	for (i = 0; i < N; i++) {
		while (g->array[i].head) {
			aux = g->array[i].head;
			g->array[i].head = g->array[i].head->next;
			free(aux);
		}
	}
	free(g->array);
	free(g);
}

int main (void) {
	int i, prev, processed;
	Graph g = can_fail_malloc(sizeof(struct graph));
	Answer a = can_fail_malloc(sizeof(struct answer));
	prev = processed = a->R = a->C = a->m = 0; a->Keys = NULL;

	parseInput(g);

	for (i = g->N - 1; i >= 0; i--) {
		if (!g->array[i].discovery) {
			KeyList new = can_fail_malloc(sizeof(struct key_list));
			new->i = i + 1; new->next = a->Keys; a->Keys = new;
			processed = DFS(g, a, i, ++processed, 1);
			a->R++;
		}
	}

	removeCritical(g);

	processed = 0;
	for (i = 0; i < g->N; i++) {
		if (!g->array[i].discovery) {
			processed = DFS(g, a, i, ++processed, 0);
			a->m = max(a->m, (processed - prev) / 2);
			prev = processed;
		}
	}

	displayResults(a);
	freeGraph(g);
	free(a);
	return 0;
}
