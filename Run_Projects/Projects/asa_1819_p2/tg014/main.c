#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define SIZE 20

/* Queue Structures */

typedef struct item{
	int element;
	struct item *next;
} Item;

typedef struct queue{
	Item *head;
	Item *tail;
} Queue;


/* Edges Structure */

typedef struct cutEdge{
	int from;
	int to;
} CutEdge;

typedef struct edge{
	int from;
	int to;
	int capacity;
	int flow;
	struct edge *next;
} Edge;

typedef struct node{
	int excess;
	int height;
	Edge *firstEdge;
} Node;


/* Global variables */

Node* G = NULL;
Queue *queue = NULL;
int sizeCutEdgesArray = SIZE;
int supliers, refillStations, numberEdges;
int *visited;
int *criticalStation;
int indexCutEdge = 0;
CutEdge *cutEdges;


/* Queue operations */

Queue* allocQueue(){
	Queue *q = malloc(sizeof(struct queue));
	q->tail = NULL;
	q->head = NULL;
	return q;
}


int isEmpty(Queue *q){
	if (q->head == NULL)
		return 1;
	return 0;
}


void push(Queue *q, int element){
	Item *help;
	Item *newItem = malloc(sizeof(struct item));
	
	if (isEmpty(q)){
		newItem->element = element;
		newItem->next = NULL;
		q->tail = newItem;
		q->head = newItem;
		return;
	}

	newItem->element = element;
	newItem->next = NULL;
	help = q->tail;
	help->next = newItem;
	q->tail = newItem;
}


int pop(Queue *q){
	Item *help;
	int element;

	if (q->head == NULL)
		return -1;

	help = q->head;
	element = help->element;

	if (q->head == q->tail){
		q->head = NULL;
		q->tail = NULL;
	}
	else
		q->head = q->head->next;

	free(help);
	return element;
}


void freeQueue(Queue *q){
	Item *help = q->head;
	while (help != NULL){
		
		Item *help2 = help->next;
		
		if (help2 == NULL){
			free(help);
			break;
		}

		free(help);
		help = help2;
		help2 = help->next;
	}
	free(q);
}


/* Main Program */

int residualCapacity(int cap, int flow){
	return cap-flow;
}


int indexGraph(int index){
	return index - 2;
}


int isStation(int index){
	if (index > supliers + 1)
		return 1;
	return 0;
}


void addEdge(int origin, int dest, int capacity){

	Edge *newEdge = malloc(sizeof(struct edge));
	Edge *residualEdge = malloc(sizeof(struct edge));
	
	if (isStation(origin)){
		origin = origin + refillStations;
	}
	
	newEdge->from = origin;
	newEdge->to = dest;
	newEdge->capacity = capacity;
	newEdge->flow = 0;
	newEdge->next = NULL;

	residualEdge->from = dest;
	residualEdge->to = origin;
	residualEdge->capacity = capacity;
	residualEdge->flow = residualCapacity(capacity, 0);
	residualEdge->next = NULL;


	if (G[origin].firstEdge == NULL){
		G[origin].firstEdge = newEdge;
	}
	else {
		newEdge->next = G[origin].firstEdge;
		G[origin].firstEdge = newEdge;
	}

	if (G[dest].firstEdge == NULL){
		G[dest].firstEdge = residualEdge;
	}
	else {
		residualEdge->next = G[dest].firstEdge;
		G[dest].firstEdge = residualEdge;
	}
}


void addStationEdge(int origin, int dest, int capacity){

	Edge *newEdge = malloc(sizeof(struct edge));
	Edge *residualEdge = malloc(sizeof(struct edge));

	newEdge->from = origin;
	newEdge->to = dest;
	newEdge->capacity = capacity;
	newEdge->flow = 0;
	newEdge->next = NULL;

	residualEdge->from = dest;
	residualEdge->to = origin;
	residualEdge->capacity = capacity;
	residualEdge->flow = residualCapacity(capacity, 0);
	residualEdge->next = NULL;


	if (G[origin].firstEdge == NULL){
		G[origin].firstEdge = newEdge;
	}
	else {
		newEdge->next = G[origin].firstEdge;
		G[origin].firstEdge = newEdge;
	}

	if (G[dest].firstEdge == NULL){
		G[dest].firstEdge = residualEdge;
	}
	else {
		residualEdge->next = G[dest].firstEdge;
		G[dest].firstEdge = residualEdge;
	}
}


void addTarget(int size){
	size += refillStations + 1;
	
	G[size].excess = 0;
	G[size].height = 0;
	G[size].firstEdge = NULL;
}


void parseGraph(){

	int i, size, origin, dest, capacity;

	scanf("%d %d %d", &supliers, &refillStations, &numberEdges);
	
	size = 1 + supliers + refillStations;

	G = (Node*)malloc(sizeof(Node)*(size + refillStations + 2)); /* with source & target & ignoring 0 (2) */

	addTarget(size);

	for (i = 2; i < size + 1; i++){
		scanf("%d", &capacity);
		G[i].excess = 0;
		G[i].height = 0;
		G[i].firstEdge = NULL;
		if (i < 2 + supliers) {
			addEdge(i, size+refillStations+1, capacity);
		}
		else {
			G[i+refillStations].firstEdge = NULL;
			G[i+refillStations].height = 0;
			G[i+refillStations].excess = 0;
			addStationEdge(i, i+refillStations, capacity);
		}
	}

	for (i = 0; i < numberEdges; i++){
		scanf("%d %d %d", &origin, &dest, &capacity);
		addEdge(dest, origin, capacity);
	}
}


void updateReverseEdgeFlow(int origin, int dest, int flow){

	Edge *edge = G[origin].firstEdge;

	while(edge != NULL){
		if (edge->to == dest){
			edge->flow -= flow;
			return;
		}
		edge = edge->next;
	}
}


int min(int a, int b){
	if (a == -1)
		return b;

	if (b == -1)
		return a;

	if (a < b)
		return a;
	else
		return b;
}


void InitializePreFlow(){

	Edge *sourceEdge = G[1].firstEdge;

	G[1].height = supliers + refillStations*2 + 2;
	G[1].excess = 0;

	while (sourceEdge != NULL){

		sourceEdge->flow = sourceEdge->capacity;
		updateReverseEdgeFlow(sourceEdge->to, sourceEdge->from, sourceEdge->flow);
		G[sourceEdge->to].excess = sourceEdge->flow;
		G[sourceEdge->from].excess -= sourceEdge->flow;
		push(queue, sourceEdge->to);

		sourceEdge = sourceEdge->next;
	}
}


int isOverflowed(Edge *edge){
	if (edge->capacity == edge->flow)
		return 1;

	return 0;
}


int tryPush(int nodeId){

	int flowPushed;
	Edge *edge = G[nodeId].firstEdge;

	while(edge != NULL){

		if (edge->flow == edge->capacity) {
			edge = edge->next;
			continue;
		}

		if (G[nodeId].height > G[edge->to].height){

			flowPushed = min(G[nodeId].excess, residualCapacity(edge->capacity, edge->flow));

			if (G[edge->to].excess == 0 && (edge->to != 2 + supliers + refillStations + refillStations))
				push(queue, edge->to);

			G[nodeId].excess -= flowPushed;
			edge->flow += flowPushed;
			G[edge->to].excess += flowPushed;

			updateReverseEdgeFlow(edge->to, edge->from, flowPushed);
			
			return 1;
		}

		edge = edge->next;
	}

	return 0;
}


void relabel(int nodeId){

	Edge *edge = G[nodeId].firstEdge;
	int minHeight = INT_MAX;

	while (edge != NULL) {
		if (isOverflowed(edge)){
			edge = edge->next;
			continue;
		}

		if (G[edge->to].height < minHeight) {
			minHeight = G[edge->to].height + 1;
		}

		edge = edge->next;
	}

	G[nodeId].height = minHeight;
}


void discharge(int nodeId){
	
	while (G[nodeId].excess > 0) {
		if (!tryPush(nodeId)){
			relabel(nodeId);
		}
	}
}


void pushRelabel(){

	int nodeId;

	queue = allocQueue();

	InitializePreFlow();

	while(!isEmpty(queue)){
		nodeId = pop(queue);
		discharge(nodeId);
	}

	freeQueue(queue);

	/* Print max flow */
	printf("%d\n", G[2+refillStations*2+supliers].excess);
}


void DFS(int nodeId){
	
	visited[nodeId] = 1;
	Edge *edge = G[nodeId].firstEdge;

	while (edge != NULL){
		if ((!visited[edge->to]) && (residualCapacity(edge->capacity, edge->flow) > 0)){
			DFS(edge->to);
		}

		edge = edge->next;
	}
}


void addCutEdge(int from, int to){
	
	CutEdge edge;
	edge.from = from;
	edge.to = to;

	cutEdges[indexCutEdge++] = edge;

	sizeCutEdgesArray += SIZE;

	if (indexCutEdge % SIZE > 18)
		cutEdges = realloc(cutEdges, sizeof(struct cutEdge)*sizeCutEdgesArray);
}


void findMinCutEdges(int nodeId){

	Edge *edge = G[nodeId].firstEdge;
	int size = 2 + supliers + 2*refillStations;

	while (edge != NULL){
		if (edge->to == size || edge->from == size){
			edge = edge->next;
			continue;
		}

		if (visited[nodeId] && !visited[edge->to]){
			if (nodeId >= supliers + refillStations + 2) {
				addCutEdge(edge->to, nodeId-refillStations);
			}
			else {
				addCutEdge(edge->to, nodeId);
			}

		}

		edge = edge->next;
	}
}


int compare(const void *edge1, const void *edge2){
	if (((struct cutEdge *)edge1)->from == ((struct cutEdge *)edge2)->from)
		return (((struct cutEdge *)edge1)->to - ((struct cutEdge *)edge2)->to);

	return ((struct cutEdge *)edge1)->from - ((struct cutEdge *)edge2)->from;
}


void findMinCut(){

	int i, size = 2 + supliers + refillStations + refillStations;
	int first = 1;

	visited = malloc(sizeof(int)*(size));
	criticalStation = malloc(sizeof(int)*(size+2));
	cutEdges = malloc(sizeof(struct cutEdge)*(SIZE));

	memset(criticalStation, 0, sizeof(int)*(size+2));
	
	DFS(1);

	for (i = 1; i < size+1; i++){
		if ((i > 1 + supliers) && (i <= supliers + refillStations + 1)){
			if (visited[i] != visited[i+refillStations]){
				criticalStation[i] = 1;
				continue;
			}
		}

		findMinCutEdges(i);
	}

	/* Print critical stations */

	for (i = 0; i < size+1; i++){
		if (criticalStation[i] == 1){
			if (first){
				printf("%d", i);
				first = 0;
			}
			else
				printf(" %d", i);
		}
	}
	printf("\n");

	/* Print critical edges */

	qsort((void*)cutEdges, indexCutEdge, sizeof(struct cutEdge), compare);

	for (i = 0; i < indexCutEdge; i++){
		printf("%d %d\n", cutEdges[i].from, cutEdges[i].to);
	}

	free(criticalStation);
	free(visited);
	free(cutEdges);
}


void freeGraph(Node *G){

	int i;
	int size = 2 + supliers + refillStations*2;
	Edge *edge, *help;

	for (i = 1; i < size + 1; i++){
		edge = G[i].firstEdge;
		while(edge != NULL){
			help = edge;
			edge = edge->next;
			free(help);
		}
	}

	free(G);
}


int main(){

	parseGraph();

	pushRelabel();

	findMinCut();

	freeGraph(G);

	return 0;
}