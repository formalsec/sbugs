/**
 *	|===============================================|
 *	| A.S.A. - Project 2							|
 *	|===============================================|
 *	| Duarte Santos 						(89438)	|
 *	| Guilherme Palma 						(89452)	|
 *	|===============================================|
 */


/**
 *	|===============================================|
 *	| I N C L U D E 								|
 *	|===============================================|
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>


/**
 *	|===============================================|
 *	| D E F I N E 									|
 *	|===============================================|
 */

#define INFITY (LONG_MAX / 2)
#define SOURCE 0
#define SINK 1

#define MAX(a,b) (a > b) ? (a) : (b);
#define MIN(a,b) (a < b) ? (a) : (b);


/**
 *	|===============================================|
 *	| S T R U C T 									|
 *	|===============================================|
 */

typedef struct Link {
	int data;
	struct Link *next;
} *Link_t;

typedef struct Queue {
	Link_t head, tail;
} *Queue_t;

typedef struct Edge {
	int from_node, to_node;
	long capacity, flow;
	struct Edge *reverse;
} *Edge_t;

typedef struct Vector {
	int size, capacity;
	Edge_t *elements;
} *Vector_t;

typedef struct Graph {
	Vector_t *adj_list;
	int num_nodes;
	long max_flow;
	Vector_t mincut_e, mincut_f;
} *Graph_t;


/**
 *	|===============================================|
 *	| Q U E U E 									|
 *	|===============================================|
 */

Queue_t queue_alloc() {
	Queue_t q = (Queue_t) malloc(sizeof(struct Queue));

	q->head = NULL;
	q->tail = NULL;

	return q;
}

bool queue_isEmpty(Queue_t queue) {
	return queue->head == NULL;
}

Link_t new_node(int data, Link_t next) {
	Link_t x = (Link_t) malloc(sizeof(struct Link));

	x->data = data;
	x->next = next;

	return x;
}

void queue_push(Queue_t queue, int data) {
	if (queue->head == NULL) {
		queue->head = (queue->tail = new_node(data, queue->head));
		return;
	}
	queue->tail->next = new_node(data, queue->tail->next);
	queue->tail = queue->tail->next;
}

int queue_pop(Queue_t queue) {
	int data = queue->head->data;
	Link_t x = queue->head->next;

	free(queue->head);
	queue->head = x;

	return data;
}


/**
 *	|===============================================|
 *	| E D G E 										|
 *	|===============================================|
 */

Edge_t newEdge(int from_node, int to_node, long capacity) {
	Edge_t e = (Edge_t) malloc(sizeof(struct Edge));

	e->from_node = from_node;
	e->to_node = to_node;
	e->capacity = capacity;
	e->flow = 0;

	return e;
}

long excessCapacity(Edge_t edge) {
	return (edge->capacity - edge->flow);
}

void augmentEdge(Edge_t edge, long bottle_neck) {
	edge->flow += bottle_neck;
	edge->reverse->flow -= bottle_neck;
}

int qsort_compare (const void *a, const void *b) {
	Edge_t x = *(Edge_t*) a;
	Edge_t y = *(Edge_t*) b;

	if (x->from_node != y->from_node)
		return x->from_node - y->from_node;

	return x->to_node - y->to_node;
}


/**
 *	|===============================================|
 *	| V E C T O R 									|
 *	|===============================================|
 */

Vector_t vector_alloc(int init_capacity) {
	Vector_t v = (Vector_t) malloc(sizeof(struct Vector));
	int capacity = MAX(init_capacity, 1);

	v->size = 0;
	v->capacity = capacity;
	v->elements = (Edge_t*) malloc(capacity * sizeof(Edge_t));

	return v;
}

Edge_t vector_get(Vector_t vector, int index) {
	if ((index < 0) || (index >= vector->size)) {
		return NULL;
	}

	return (vector->elements[index]);
}

void vector_pushBack(Vector_t vector, Edge_t data) {
	if (vector->size == vector->capacity) {
		int i, new_capacity = vector->capacity * 2;
		Edge_t *new_elements = (Edge_t*) malloc(new_capacity * sizeof(Edge_t));
		vector->capacity = new_capacity;
		for (i = 0; i < vector->size; i++) {
			new_elements[i] = vector->elements[i];
		}
		free(vector->elements);
		vector->elements = new_elements;
	}
	vector->elements[vector->size++] = data;
}

void vector_free(Vector_t vector) {
	free(vector->elements);
	free(vector);
}


/**
 *	|===============================================|
 *	| G R A P H 									|
 *	|===============================================|
 */

Graph_t graph_alloc(int num_nodes) {
	int i;
	Graph_t g = (Graph_t) malloc(sizeof(struct Graph));

	g->num_nodes = num_nodes;
	g->max_flow = 0;
	g->adj_list = (Vector_t*) malloc(num_nodes * sizeof(Vector_t));
	g->mincut_e = vector_alloc(10);
	g->mincut_f = vector_alloc(10);

	for (i = 0; i < num_nodes; i++) {
		g->adj_list[i] = vector_alloc(5);
	}

	return g;
}

void insertEdge(Graph_t graph, int from_node, int to_node, long capacity) {
	Edge_t e = newEdge(from_node, to_node, capacity);
	Edge_t r = newEdge(to_node, from_node, 0);

	e->reverse = r;
	r->reverse = e;
	vector_pushBack(graph->adj_list[from_node], e);
	vector_pushBack(graph->adj_list[to_node], r);
}

void graph_free(Graph_t graph) {
	int i, j, size, num_nodes = graph->num_nodes;

	for (i = 0; i < num_nodes; i++) {
		size = graph->adj_list[i]->size;
		for (j = 0; j < size; j++) {
			free(graph->adj_list[i]->elements[j]);
		}
		vector_free(graph->adj_list[i]);
	}

	vector_free(graph->mincut_e);
	vector_free(graph->mincut_f);
	
	free(graph->adj_list);
	free(graph);
}

/**
 *	|===============================================|
 *	| M A X - F L O W 								|
 *	|===============================================|
 */

bool bfs(Graph_t graph, int *level) {
	int i, size, n = graph->num_nodes, node;
	long excess;
	Queue_t queue = queue_alloc();
	Edge_t e;

	for (i = 0; i < n; i++)
		level[i] = -1;

	queue_push(queue, SOURCE);
	level[SOURCE] = 0;

	while (!queue_isEmpty(queue)) {
		node = queue_pop(queue);
		size = graph->adj_list[node]->size;
		for (i = 0; i < size; i++) {
			e = vector_get(graph->adj_list[node], i);
			excess = excessCapacity(e);
			if (excess > 0 && level[e->to_node] == -1) {
				level[e->to_node] = level[node] + 1;
				queue_push(queue, e->to_node);
			}
		}
	}

	free(queue);

	return level[SINK] != -1;
}

long dfs(Graph_t graph, int current_node, int *next, int *level, long flow) {
	int num_edges;
	Edge_t e;
	long excess, bottle_neck, min;

	if (current_node == SINK) 
		return flow;
	
	num_edges = graph->adj_list[current_node]->size;

	for (; next[current_node] < num_edges; next[current_node]++) {
		e = vector_get(graph->adj_list[current_node], next[current_node]);
		excess = excessCapacity(e);
		if (excess > 0 && level[e->to_node] == level[current_node] + 1) {
			min = MIN(flow, excess);
			bottle_neck = dfs(graph, e->to_node, next, level, min);
			if (bottle_neck > 0) {
				augmentEdge(e, bottle_neck);
				return bottle_neck;
			}

		}
	}

	return 0;
}

void dinic(Graph_t graph) {
	int n = graph->num_nodes;
	int *next = (int*) malloc(n * sizeof(int));
	int *level = (int*) malloc(n * sizeof(int));
	long flow;

	memset(next, 0, n * sizeof(int));

	while (bfs(graph, level)) {
		memset(next, 0, n * sizeof(int));

		while ((flow = dfs(graph, SOURCE, next, level, INFITY)) != 0)
			graph->max_flow += flow;
	}

	free(next);
	free(level);
}


/**
 *	|===============================================|
 *	| M I N - C U T 								|
 *	|===============================================|
 */

void reverse_bfs(Graph_t graph, bool *can_reach) {
	int i, size, node;
	long excess;
	Queue_t queue = queue_alloc();
	Edge_t edge, e, r;

	queue_push(queue, SINK);
	can_reach[SINK] = true;

	while (!queue_isEmpty(queue)) {
		node = queue_pop(queue);
		size = graph->adj_list[node]->size;
		for (i = 0; i < size; i++) {
			edge = vector_get(graph->adj_list[node], i);
			if (edge->capacity == 0) { /* if edge is residual */
				e = edge->reverse;
				r = edge;
			} 
			else {
				e = edge;
				r = edge->reverse;
			}

			excess = excessCapacity(e);
			if (edge->capacity == 0 && excess > 0 && !can_reach[r->to_node]) {
				can_reach[r->to_node] = true;
				queue_push(queue, r->to_node);
			}
			else if (edge->capacity != 0 && e->flow > 0 && !can_reach[e->to_node]) {
				can_reach[e->to_node] = true;
				queue_push(queue, e->to_node);
			}
		}
	}

	free(queue);
}

void min_cut(Graph_t graph, int out_min) {
	int i, size, n = graph->num_nodes, node;
	bool *can_reach = (bool*) malloc(n * sizeof(bool));
	bool *visited = (bool*) malloc(n * sizeof(bool));
	Queue_t queue = queue_alloc();
	Edge_t edge, e, r;

	memset(can_reach, false, n * sizeof(bool));
	reverse_bfs(graph, can_reach);

	/* bfs */
	memset(visited, false, n * sizeof(bool));
	visited[SINK] = true;
	queue_push(queue, SINK);

	while (!queue_isEmpty(queue)) {
		node = queue_pop(queue);
		size = graph->adj_list[node]->size;
		for (i = 0; i < size; i++) {
			edge = vector_get(graph->adj_list[node], i);
			if (edge->capacity == 0) { /* if edge is residual */
				e = edge->reverse;
				r = edge;
			} 
			else {
				e = edge;
				r = edge->reverse;
			}
			if (edge->capacity == 0) {
				if (can_reach[r->from_node] && !can_reach[r->to_node]) {
					if (e->from_node != 0) {
						if (e->to_node >= out_min)
							vector_pushBack(graph->mincut_e, e);
						else
							vector_pushBack(graph->mincut_f, e);
					}
				}
				else if (!visited[edge->to_node] && can_reach[r->from_node] && can_reach[r->to_node]) {
					visited[edge->to_node] = true;
					queue_push(queue, r->to_node);
				}
			}
		}
	}

	free(queue);
	free(can_reach);
	free(visited);
}


/**
 *	|===============================================|
 *	| M A I N 										|
 *	|===============================================|
 */

int main(int argc, char** argv) {
	int i, size, num_nodes, num_f, f_min, f_max, num_e, e_min, e_max, out_min, out, num_t, from_node, to_node;
	long capacity;
	Graph_t graph;

	scanf("%d %d %d\n", &num_f, &num_e, &num_t);
	num_nodes = 1 + num_f + 2 * num_e + 1; /* source + f + e_in + e_out + sink */
	graph = graph_alloc(num_nodes); 

	/* e input */
	f_min = 2;
	f_max = f_min + num_f - 1;
	for (i = f_min; i <= f_max; i++) {
		scanf("%ld ", &capacity);
		insertEdge(graph, SOURCE, i, capacity);
	}

	/* e input */
	e_min = f_max + 1;
	e_max = e_min + num_e - 1;
	out_min = e_max + 1;
	out = out_min;
	for (i = e_min; i <= e_max; i++) {
		scanf("%ld ", &capacity);
		insertEdge(graph, i, out++, capacity); /* e_in connects to e_out */
	}

	/* t input */
	for (i = 1; i <= num_t; i++) {
		scanf("%d %d %ld\n", &from_node, &to_node, &capacity);
		if (from_node >= e_min) /* from e = from e_out */
			insertEdge(graph, from_node + num_e, to_node, capacity); /* e_in to e_out = e_in + num_e */
		else
			insertEdge(graph, from_node, to_node, capacity);
	}

	dinic(graph);

	/* output 1 */
	printf("%ld\n", graph->max_flow);

	min_cut(graph, out_min);

	/* output 2 */
	size = graph->mincut_e->size;
	qsort(graph->mincut_e->elements, size, sizeof(Edge_t), qsort_compare);
	if (size > 0)
		printf("%d", graph->mincut_e->elements[0]->from_node);
	for (i = 1; i < size; i++) {
		printf(" %d", graph->mincut_e->elements[i]->from_node);
	}
	printf("\n");
	
	/* output 3 */
	size = graph->mincut_f->size;
	qsort(graph->mincut_f->elements, size, sizeof(Edge_t), qsort_compare);
	for (i = 0; i < size; i++) {
		if (graph->mincut_f->elements[i]->from_node >= out_min) { /* from e_out = from e */
			printf("%d %d\n", graph->mincut_f->elements[i]->from_node - num_e, graph->mincut_f->elements[i]->to_node);
		}
		else {
			printf("%d %d\n", graph->mincut_f->elements[i]->from_node, graph->mincut_f->elements[i]->to_node);
		}
	}

	graph_free(graph);

	return 0;
}
