/**
 * 	A.S.A. - Projeto 1
 *
 * 	Duarte Santos (89438)
 * 	Guilherme Palma (89452)
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 *	|---------------------------------|
 *	|-----------| STRUCTS |-----------|
 *	|---------------------------------|
 */

typedef struct node {
	int value;
	struct node *next;
} *link; 

typedef struct stack {
	link head; 
	int size; 
} *stack_t;

typedef struct data {
	int *discovery, *low, *parent;
	bool *artcVec;
	stack_t artcPoints;
	stack_t subHeads;
	int numSub, subSize;
} *data_t;

typedef struct graph {
	link *adjList;
	int numNodes;
} *graph_t;

/*
 *	|---------------------------------|
 *	|------------| STACK |------------|
 *	|---------------------------------|
 */

link newNode(int value, link head) {
	link x = (link) malloc(sizeof(struct node));
	x->value = value;
	x->next = head;
	return x;
}

void initStack(stack_t stack) {
	stack->head = NULL;
	stack->size = 0;
}

int emptyStack(stack_t stack) {
	return stack->head == NULL;
}

void push(stack_t stack, int value) {
	stack->head = newNode(value, stack->head);
	(stack->size)++;
}

int pop(stack_t stack) {
	int value = stack->head->value;
	link t = stack->head->next;
	free(stack->head);
	stack->head = t;
	(stack->size)--;
	return value;
}

/*
 *	|---------------------------------|
 *	|-------| ADJACENCY LIST |--------|
 *	|---------------------------------|
 */

link insertBegin(link head, int v) {
	link x = (link) malloc(sizeof(struct node));
	x->value = v;
	x->next = head;
	return x;
}

graph_t initGraph(int n) {
	int v;
	graph_t graph = (graph_t) malloc(sizeof(struct graph));
	graph->numNodes = n;
	graph->adjList = (link*) malloc(n * sizeof(link));
	for (v = 0; v < n; v++)
		graph->adjList[v] = NULL;
	return graph;
}

void insertEdge(graph_t graph, int node1, int node2) {
	graph->adjList[node1] = insertBegin(graph->adjList[node1], node2);
	graph->adjList[node2] = insertBegin(graph->adjList[node2], node1);
}

link findPrevious(link head, int v) {
	link prev = head;
	if (prev == NULL) 
		return NULL;
	if (prev->value == v)
		return prev;

	link node = prev->next;

	for (; node != NULL; node = node->next) {
		if (node->value == v){
			return prev;
		}
		prev = node;
	}
	
	return NULL;
}

void deleteNext(link prev, link head) {
	if (prev == NULL) return;

	link node = prev->next;
	if (prev == head && node == NULL){
		free(prev);
		head = NULL;
		return;
	}
	
	prev->next = node->next;
	free(node);
}

void removeNode(graph_t graph, int v) {
	link prev, next, x;

	for (x = graph->adjList[v]; x != NULL; x = next) {
		prev = findPrevious(graph->adjList[x->value], v);
		if (prev->value == v){
			graph->adjList[x->value] = prev->next;
			free(prev);
		}
		else {
			deleteNext(prev, graph->adjList[x->value]);
		}
		next = x->next;
		free(x);
	}
	graph->adjList[v] = NULL;
}

/*
 *	|---------------------------------|
 *	|--------| DFS ALGORITHM |--------|
 *	|---------------------------------|
 */

int min(int x, int y) { return ( (x < y) ? x : y ); }

void dfs_visit(graph_t graph, int u, int *discovery, int *low, int *parent, stack_t artcPoints, bool *artcVec, int *time) {

	int children = 0;
	(*time)++;
	discovery[u] = *time;
	low[u] = *time;

	link i;
	for (i = graph->adjList[u]; i != NULL; i = i->next) {
		if (discovery[i->value] == -1) {
			children++;
			parent[i->value] = u;
			dfs_visit(graph, i->value, discovery, low, parent, artcPoints, artcVec, time);

			low[u] = min(low[u], low[i->value]);

			if (!artcVec[u]) {
				if ( (parent[u] == -1 && children > 1) ||
					 (parent[u] != -1 && low[i->value] >= discovery[u]) ) {
					artcVec[u] = true;
					push(artcPoints, u);
				}
			}
		}
		else if (i->value != parent[u]) {
			low[u] = min(low[u], discovery[i->value]);
		}
	}
}

data_t dfs(graph_t graph) {
	int size = graph->numNodes;
	int time = 0, numSub = 0, subSize = 0;

	int *discovery = (int*) malloc(size * sizeof(int));
	int *low = (int*) malloc(size * sizeof(int));
	int *parent = (int*) malloc(size * sizeof(int));
	bool *artcVec = (bool*) malloc(size * sizeof(bool));

	stack_t artcPoints = (stack_t) malloc(sizeof(struct stack));
	stack_t subHeads = (stack_t) malloc(sizeof(struct stack));
	initStack(subHeads);
	initStack(artcPoints);

	int i;
	for (i = 0; i < size; i++) {
		discovery[i] = -1;
		parent[i] = -1;
		artcVec[i] = false;
	}

	int startTime, finishTime, dif, u;
	for (u = size - 1; u >= 0; u--) {
		if (discovery[u] == -1) {
			numSub++;
			push(subHeads, u);
			startTime = time;
			dfs_visit(graph, u, discovery, low, parent, artcPoints, artcVec, &time);
			finishTime = time;
			dif = finishTime - startTime;
			if(dif > subSize)
				subSize = dif;
		}
	}

	data_t data = (data_t) malloc (sizeof(struct data));
	data->discovery = discovery;
	data->low = low;
	data->parent = parent;
	data->artcVec = artcVec;
	data->artcPoints = artcPoints;
	data->subHeads = subHeads;
	data->numSub = numSub;
	data->subSize = subSize;

	return data;
}

/*
 *	|---------------------------------|
 *	|------------| MAIN |-------------|
 *	|---------------------------------|
 */

void freeData(data_t data) {
	free(data->discovery);
	free(data->low);
	free(data->parent);
	free(data->artcVec);

	while (!emptyStack(data->artcPoints)) {
		pop(data->artcPoints);
	}
	while (!emptyStack(data->subHeads)) {
		pop(data->subHeads);
	}

	free(data->artcPoints);
	free(data->subHeads);

	free(data);
}

int main(int argc, char** argv) {
	int numNodes, numEdges, node1, node2;
	graph_t graph;

	scanf("%d", &numNodes);
	graph = initGraph(numNodes);

	scanf("%d", &numEdges);
	int i;
	for(i = 0; i < numEdges; i++) {
		scanf("%d %d", &node1, &node2);
		insertEdge(graph, node1-1, node2-1);
	}

	/* output 1 */
	data_t data = dfs(graph);
	printf("%d\n", data->numSub);

	/* output 2 */
	int node;
	if(!emptyStack(data->subHeads)) {
		node = pop(data->subHeads);
		printf("%d", node+1); 
	} 
	while (!emptyStack(data->subHeads)) {
		node = pop(data->subHeads);
		printf(" %d", node+1);
	}
	
	/* output 3 */
	printf("\n%d\n", data->artcPoints->size); 

	/* output 4 */
	while (!emptyStack(data->artcPoints)) {
		node = pop(data->artcPoints);
		removeNode(graph, node);
	}

	freeData(data);

	data = dfs(graph);
	printf("%d\n", data->subSize);

	freeData(data);

	link x, next;
	for(i = 0; i < graph->numNodes; i++) {
		for(x = graph->adjList[i]; x != NULL; x = next) {
			next = x->next;
			free(x);
		}
	}

	free(graph->adjList);
	free(graph);

	return 0;
}