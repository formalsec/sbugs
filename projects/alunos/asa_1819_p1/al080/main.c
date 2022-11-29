#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct vertex {
	int index;
	struct vertex * next;
	struct vertex * prev;
} Vertex;

typedef struct tarjan_info {
	int d;
	int low;
	int * scc;
	unsigned int out : 1;
} TarjanInfo;

typedef struct tarjan {
	int next_d;
	int Q_count;
	int * Q;
	int scc_count;
	int scc_arch_count;
	TarjanInfo * info;
} Tarjan;

void add_next_arch(Vertex *, int);
void add_prev_arch(Vertex *, int);
int add_unique_arch(Vertex *, int);
void Tarjan_Visit(int);
void scc_arch_count();

int N;
Vertex * graph;
Tarjan tarjan;

int main(void) {
	int M, src, dest, i;

	/* Read number of nodes. */
	if (scanf("%d", &N) == EOF) {
		return 0;
	}

	/* Start vertex list. */
	graph = (Vertex *)can_fail_malloc(sizeof(struct vertex) * N);
	tarjan.next_d = 0;
	tarjan.Q_count = 0;
	tarjan.Q = (int *)can_fail_malloc(sizeof(int) * N);
	tarjan.info = (TarjanInfo *)can_fail_malloc(sizeof(struct tarjan_info) * N);
	tarjan.scc_count = 0;
	tarjan.scc_arch_count = 0;
	for (i = 0; i < N; i++) {
		graph[i].index = i;
		graph[i].next = NULL;
		graph[i].prev = NULL;
		tarjan.info[i].d = -1;
		tarjan.info[i].low = -1;
		tarjan.info[i].scc = &i;
		tarjan.info[i].out = 0;
	}

	/* Read number or arches. */
	if (scanf("%d", &M) == EOF) {
		return 0;
	}

	/* Read specified arches. */
	i = 0;
	while (i < M && scanf("%d %d", &src, &dest) != EOF) {
		add_next_arch(&graph[src - 1], dest - 1);
		i++;
	}

	/* Travel through the graph. */
	for (i = 0; i < N; i++) {
		if (tarjan.info[i].out == 1) continue;
		Tarjan_Visit(i);
	}

	/* Calculate arches in SCC DAG. */
	scc_arch_count();

	/* Print SCC count. */
	printf("%d\n", tarjan.scc_count);

	/* Print arch count. */
	printf("%d\n", tarjan.scc_arch_count);

	/* Print arches. */
	for (i = 0; i < N; i++) {
		Vertex * adj = graph[i].next;
		Vertex * prev_adj = NULL;

		while (adj != NULL) {
			printf("%d %d\n", i + 1, adj->index + 1);

			/* Free previous adjacent memory. */
			prev_adj = adj;
			adj = adj->next;
			free(prev_adj);
		}
	}

	/* Free data structures. */
	free(graph);
	free(tarjan.Q);
	free(tarjan.info);

	return 0;
}

/**
 * Add arch to adjacent list, while checking for self references.
 */
void add_next_arch(Vertex * node, int dest) {

	/* Prevent adding self references. */
	if (node->index == dest) {
		return;
	}

	Vertex * adj = (Vertex *)can_fail_malloc(sizeof(struct vertex));
	adj->index = dest;
	adj->next = node->next;
	adj->prev = NULL;
	node->next = adj;
}

/**
 * Add an arch to the parent list.
 */
void add_prev_arch(Vertex * node, int dest) {
	Vertex * parent = (Vertex *)can_fail_malloc(sizeof(struct vertex));
	parent->index = dest;
	parent->next = NULL;
	parent->prev = node->prev;
	node->prev = parent;
}

/**
 * Add an arch that isn't in the adjacency list yet.
 */
int add_unique_arch(Vertex * node, int dest) {

	/* Prevent adding self references. */
	if (node->index == dest) {
		return 0;
	}

	Vertex * adj = (Vertex *)can_fail_malloc(sizeof(struct vertex));
	adj->index = dest;
	adj->next = NULL;
	adj->prev = NULL;

	while(node->next != NULL) {
		node = node->next;

		/* Don't double add an adjacent. */
		if (node->index == dest) {
			free(adj);
			return 0;
		}
	}

	node->next = adj;
	return 1;
}

/**
 * Visit vertex and follow arches recursively.
 */
void Tarjan_Visit(int index) {
	tarjan.info[index].d = tarjan.info[index].low = tarjan.next_d;
	tarjan.next_d++;
	tarjan.Q[tarjan.Q_count] = index;
	tarjan.Q_count++;

	Vertex * prev_adj = NULL;
	Vertex * adj = graph[index].next;
	graph[index].next = NULL;

	while (adj != NULL) {
		if (tarjan.info[adj->index].out == 0 || tarjan.info[adj->index].d == -1) {
			if (tarjan.info[adj->index].d == -1) {
				Tarjan_Visit(adj->index);
			}

			if (tarjan.info[index].low > tarjan.info[adj->index].low) {
				tarjan.info[index].low = tarjan.info[adj->index].low;
			}
		}

		/* Register cross-edge arches. */
		if (tarjan.info[adj->index].out == 1) {
			add_prev_arch(&graph[*tarjan.info[adj->index].scc], index);
		}

		/* Select next adjacent and free previous. */
		prev_adj = adj;
		adj = adj->next;
		free(prev_adj);
	}

	/* Pop SCC vertices. */
	if (tarjan.info[index].d == tarjan.info[index].low) {
		int * min = (int *)can_fail_malloc(sizeof(int));
		*min = index;
		tarjan.Q_count--;
		int pop_id = tarjan.Q[tarjan.Q_count];
		tarjan.info[pop_id].scc = min;
		tarjan.info[pop_id].out = 1;
		while (pop_id != index) {

			/* Update minimum identifier of SCC. */
			if (pop_id < *min) {
				*min = pop_id;
			}

			/* Get next vertex. */
			tarjan.Q_count--;
			pop_id = tarjan.Q[tarjan.Q_count];
			tarjan.info[pop_id].scc = min;
			tarjan.info[pop_id].out = 1;
		}

		/* Increment number of SCCs found. */
		tarjan.scc_count++;
	}
}

/**
 * Count result arches between SCCs, excluding duplicates.
 * 
 * Uses the parent list on each SCC identifying vertex (the minimum).
 */
void scc_arch_count() {
	int i;
	Vertex * parent, * prev_parent = NULL;

	for (i = 0; i < N; i++) {
		parent = graph[i].prev;

		while (parent != NULL) {
			tarjan.scc_arch_count += add_unique_arch(
				&graph[*tarjan.info[parent->index].scc],
				i
			);

			/* Select next parent and free previous. */
			prev_parent = parent;
			parent = parent->prev;
			free(prev_parent);
		}
	}
}
