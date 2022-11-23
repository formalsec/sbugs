#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
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

typedef struct queue {
	link head;
	link tail;
	int size; 
} *queue_t;

typedef struct graph {
	link *adjList;
	int numNodes;
} *graph_t;

/*
 *	|---------------------------------|
 *	|------------| QUEUE |------------|
 *	|---------------------------------|
 */

link newNode(int value, link head) {
	link x = (link) can_fail_malloc(sizeof(struct node));
	x->value = value;
	x->next = head;
	return x;
}

void initQueue(queue_t queue) {
	queue->head = NULL;
	queue->tail = NULL;
	queue->size = 0;
}

int emptyQueue(queue_t queue) {
	return queue->head == NULL;
}

void push(queue_t queue, int value) {
	if (queue->head == NULL){
		queue->head = (queue->tail = newNode(value, queue->head));
		return;
	}
	queue->tail->next = newNode( value, queue->tail->next);
	queue->tail = queue->tail->next;
	(queue->size)++;
}

int pop(queue_t queue) {
	link x;
	int value;

	value = queue->head->value;

	x = queue->head->next;
	free(queue->head);
	queue->head = x;

	(queue->size)--;
	return value;
}

/*
 *	|---------------------------------|
 *	|-------| ADJACENCY LIST |--------|
 *	|---------------------------------|
 */

link insertBegin(link head, int v) {
	link x = (link) can_fail_malloc(sizeof(struct node));
	x->value = v;
	x->next = head;
	return x;
}

graph_t initGraph(int n) {
	int v;
	graph_t graph = (graph_t) can_fail_malloc(sizeof(struct graph));
	graph->numNodes = n;
	graph->adjList = (link*) can_fail_malloc(n * sizeof(link));
	for (v = 0; v < n; v++)
		graph->adjList[v] = NULL;
	return graph;
}

void insertEdge(graph_t graph, int node1, int node2) {
	graph->adjList[node1] = insertBegin(graph->adjList[node1], node2);
}


/*
 *	|---------------------------------|
 *	|--------| BFS ALGORITHM |--------|
 *	|---------------------------------|
 */


void bfs(graph_t G, int* gradeList, int numNodes){

	int i, node, friend_index, max;
	link friend;

	bool* visited = (bool*) can_fail_malloc(numNodes * sizeof(bool));
	

	queue_t queue = (queue_t) can_fail_malloc(sizeof(struct queue));
	initQueue(queue);

	numNodes = G->numNodes;
	link* adjList = G->adjList;

	for(i = 0; i < numNodes; i++){

		memset(visited, 0, numNodes);
		visited[i] = true;
		push(queue,i);
		max = gradeList[i];
		
		while (!emptyQueue(queue)){
			node = pop(queue);
			for(friend = adjList[node]; friend != NULL; friend = friend->next){
				friend_index = friend->value;
				if( !visited[friend_index] ){
					if ( gradeList[friend_index] > max )
						max = gradeList[friend_index];

					visited[friend_index] = true;
					push(queue,friend_index);
				}
			}
		}
		gradeList[i] = max;
	}

	while (!emptyQueue(queue)) { /*should't be needed*/
		perror("qq not empty");
		pop(queue);
	}
	free(queue);
	free(visited);
}

 /*
 *	|---------------------------------|
 *	|------------| MAIN |-------------|
 *	|---------------------------------|
 */

int main(int argc, char** argv) {
	int numNodes, numEdges, node1, node2;
	graph_t graph;

	if (scanf("%d,%d", &numNodes, &numEdges) != 2){
		perror("error reading file");
		return 1;
	}
	graph = initGraph(numNodes);

	int gradeList[numNodes];

	int i;
	for(i = 0; i < numNodes; i++) {
		if (scanf("%d", &gradeList[i]) != 1){
			perror("error reading file");
			return 1;
		}
	}

	for(i = 0; i < numEdges; i++) {
		if(scanf("%d %d", &node1, &node2) != 2){
			perror("error reading file");
			return 1;
		}

		insertEdge(graph, node1-1, node2-1);
	}

	bfs(graph, gradeList, numNodes);

	link x, next;

	for(i = 0; i<numNodes; i++){
		printf("%d\n", gradeList[i]); /* output */
		for(x = graph->adjList[i]; x != NULL; x = next) {
			next = x->next;
			free(x);
		}
	}

	free(graph->adjList);
	free(graph);
	return 0;
}