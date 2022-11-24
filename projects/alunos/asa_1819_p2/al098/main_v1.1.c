#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/* 89463 Inês Silva */
/* 89522 Pedro Galhardo */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define max(a, b) ((a > b) ? a: b)
#define min(a, b) ((a < b) ? a: b)

#define N (g->f + 2 * g->e + 2)
#define in(v) g->V[v].in
#define out(v) g->V[v].out
#define discovery(v) g->V[v].discovery
#define aux(v) g->V[g->e + v]

typedef struct vertex * Vertex;

typedef struct node {
	int u;
	struct node * next;
} * Node;

typedef struct queue {
	Node head;
	Node tail;
} * Queue;

typedef struct edge {
	int u, v, capacity_forward;
	int flow_forward, flow_back;
	struct edge * next_in, * next_out;
} * Edge;

typedef struct vertex {
	Edge in;
	Edge out;
} * Vertex;

typedef struct graph {
	Vertex V;
	int f, e, t;
} * Graph;

int isStation(Graph g, int u) {
	return (u >= g->f + 2 && u < N - g->e);
}

void displayOutput(Graph g, char * discovery, int flow) {
	int u, v, print = 0;
	char * upgrade = can_fail_calloc(g->e, sizeof(char));
	Edge adj;

	printf("%d\n", flow);

	for (u = g->f + 2; u < N - g->e; u++) {
		v = u + g->e;

		if (!discovery[u] && discovery[v]) {
			if (print)
				printf(" %d", (v >= N - g->e) ? v - g->e : v);
			else {
				printf("%d", (v >= N - g->e) ? v - g->e : v);
				print = 1;
			}
			upgrade[u - g->f - 2] = 1;
		}
	}	

	printf("\n");
	for (u = 2; u < N; u++) {
		for (adj = out(u); adj != NULL; adj = adj->next_out) {
			v = adj->v;

			if (!u || !v) 
				continue;
			else if (isStation(g, u) && upgrade[u - g->f - 2])
				continue;
			else if (isStation(g, v) && upgrade[v - g->f - 2])
				continue;
			
			if (!discovery[u] && discovery[v]) {
				printf("%d %d\n", 
					(u >= N - g->e) ? u - g->e : u,
					(v >= N - g->e) ? v - g->e : v);
			}
		}
	}

	free(upgrade);
}

void pushNode(Queue queue, int u) {
	Node node = (Node) can_fail_malloc(sizeof(struct node));
	node->u = u;
	node->next = NULL;

	if (!queue->head)
		queue->head = queue->tail = node;
	else {
		queue->tail->next = node;
		queue->tail = node;
	}
}

int selectVertex(Queue overflown) {
	int u;
	Node aux = overflown->head;

	if (!aux) return 0;
	u = aux->u;
	overflown->head = overflown->head->next;
	free(aux);
	return u;
}

void DFS(Graph g, char * discovery, int u) {
	int v;
	Edge adj;
	discovery[u] = 1;

	for (adj = in(u); adj != NULL; adj = adj->next_in) {
		v = adj->u;
		if ((adj->capacity_forward- adj->flow_forward) && !discovery[v])
			DFS(g, discovery, v);
	}

	for (adj = out(u); adj != NULL; adj = adj->next_out) {
		v = adj->v;
		if ((-adj->flow_back) && !discovery[v])
			DFS(g, discovery, v);
	}
}

void insertIn(Graph g, Edge head, Edge new) {
	Edge iter;

	if (!head || head->v >= new->u) {
		new->next_in = in(new->v);
		in(new->v) = new;
		return;
	}

	iter = in(new->v);
	while (iter->next_in && iter->next_in->v < new->u)
		iter = iter->next_in;
	new->next_in = iter->next_in;  
	iter->next_in = new;
}

void insertOut(Graph g, Edge head, Edge new) {
	Edge iter;

	if (!head || head->v >= new->v) {
		new->next_out = out(new->u);
		out(new->u) = new;
		return;
	}

	iter = out(new->u);
	while (iter->next_out && iter->next_out->v < new->v)
		iter = iter->next_out;
	new->next_out = iter->next_out;  
	iter->next_out = new;
}

void link(Graph g, int a, int b, int capacity) {
	Edge new = (Edge) can_fail_malloc(sizeof(struct edge));
	new->u = a;
	new->v = b;
	new->flow_forward = new->flow_back = 0;
	new->capacity_forward = capacity;
	new->next_in = new->next_out = NULL;

	insertOut(g, out(a), new);
	insertIn(g, in(b), new);
}

void parseInput(Graph g) {
	int a, b, i, capacity;
	assert(scanf("%d %d %d", &g->f, &g->e, &g->t));
	g->V = (Vertex) can_fail_malloc(sizeof(struct vertex) * N);

	for (i = 0; i < N; i++) {
		in(i) = NULL;
		out(i) = NULL;
	}

	/* Fornecedores */
	for (i = 2; i <= g->f + 1; i++) {
		assert(scanf("%d", &capacity));
		link(g, 0, i, capacity);
	}

	/* Abastecimento */
	for (i = g->f + 2; i < N - g->e; i++) {
		assert(scanf("%d", &capacity));
		link(g, i, i + g->e, capacity);
	}

	/* Ligações */
	for (i = 0; i < g->t; i++) {
		assert(scanf("%d %d %d", &a, &b, &capacity));

		/* Vértice entre Auxiliar -> Hiper */
		if ((g->f + 1 < a) && b == 1)
			link(g, a + g->e, 1, capacity);

		/* Ligação entre abastecimentos */
		else if ((g->f + 1 < a))
			link(g, a + g->e, b, capacity);	

		/* Ligação entre vértices originais */
		else
			link(g, a, b, capacity);
	}
}

void freeGraph(Graph g) {
	int i;
	Edge aux;

	for (i = 0; i < N; i++)
		while (out(i)) {
			aux = out(i);
			out(i) = out(i)->next_out;
			free(aux);
		}

	free(g->V);
	free(g);
}

int push(Graph g, Edge edge, int u, int v, int * e, Queue overflown, char back) {
	int df;

	if (!back) {
		df = min(e[u], edge->capacity_forward - edge->flow_forward);
		edge->flow_forward += df;
		edge->flow_back -= df;
		e[u] -= df;
		e[v] += df;
	}
	else {
		df = min(e[u], - edge->flow_back);
		edge->flow_forward -= df;
		edge->flow_back += df;
		e[u] -= df;
		e[v] += df;
	}
	
	if (v && v != 1)
		pushNode(overflown, edge->v);
	return 1;
}

void relabel(Graph g, int u, int * h) {
    int min = INT_MAX;
    Edge adj;

    for (adj = out(u); adj != NULL; adj = adj->next_out) {
       	if (!(adj->capacity_forward - adj->flow_forward)) continue;
        min = min(min, h[adj->v]);
    }

    for (adj = in(u); adj != NULL; adj = adj->next_in) {
       	if (!(-adj->flow_back)) continue;
        min = min(min, h[adj->u]);
    }

    h[u] = 1 + min;
}

void discharge(Graph g, int u, int * h, int * e, Queue overflown) {
	char pushed;
	Edge adj;

	while (e[u]) {
		pushed = 0;

		for (adj = out(u); adj != NULL; adj = adj->next_out)
			if ((adj->capacity_forward - adj->flow_forward) && (h[u] == h[adj->v] + 1))
				pushed = push(g, adj, adj->u, adj->v, e, overflown, 0);

		for (adj = in(u); adj != NULL; adj = adj->next_in) {
			if ((-adj->flow_back) && (h[u] == h[adj->u] + 1))
				pushed = push(g, adj, adj->v, adj->u, e, overflown, 1);
		}

		if (!pushed)
			relabel(g, u, h);
	}
}

void initializePreflow(Graph g, int * h, int * e, Queue overflown) {
	int v;
	Edge adj;
			
	h[0] = N;
	for (adj = out(0); adj != NULL; adj = adj->next_out) {
		v = adj->v;
		adj->flow_forward = adj->capacity_forward;
		adj->flow_back = -adj->capacity_forward;
		e[v] += adj->flow_forward;
		pushNode(overflown, v);
	}
}

int pushRelabel(Graph g) {
	int u;
	int * h = (int *) can_fail_calloc(N, sizeof(int));
	int * e = (int *) can_fail_calloc(N, sizeof(int));
	Queue overflown = (Queue) can_fail_malloc(sizeof(struct queue));
	overflown->head = overflown->tail = NULL;

	initializePreflow(g, h, e, overflown);
	while ((u = selectVertex(overflown)))
		discharge(g, u, h, e, overflown);

	u = e[1];
	free(h);
	free(e);
	free(overflown);
	return u;
}

int main (void) {
	int flow;
	char * discovery;
	Graph g = (Graph) can_fail_malloc(sizeof(struct graph));
	parseInput(g);

	flow = pushRelabel(g);

	discovery = (char *) can_fail_calloc(N, sizeof(char));
	DFS(g, discovery, 1);
	displayOutput(g, discovery, flow);

	free(discovery);
	freeGraph(g);
	return 0;
}