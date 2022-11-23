#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/******************************************************************************
 *
 * File Name: main.c
 * Authors: André Dias (ist91029) and Gonçalo Duarte (ist92467)
 * Last modified: 12/03/2020
 * Revision:  v1.2.0
 *
 * COMMENTS
 *		Main program
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/******************************************************************************
 * STRUCTURES
 *****************************************************************************/
typedef struct _stack{
	int number;
	struct _stack* next;
}Stack;

typedef struct _node{
	int dest;
	struct _node* next;
}Node;

typedef struct _graph{
	int V;
	int E;
	Node** vertices;
}Graph;

/******************************************************************************
 * GLOBAL VARIABLES
 *****************************************************************************/
Graph* graph;
int* grades;
Stack* stack;
int* scc;

int* dist;
int* low;
int* onStack;
int visited;

int* color;

/******************************************************************************
 * FUNCTIONS
 *****************************************************************************/
void readInput(void);
void writeOutput(void);

void* safeMalloc(int size);

Stack* newStack(void);
int isStackEmpty(void);
void pushStack(int this);
int popStack(void);
void printStack(void);
void freeStack(void);

Graph* newGraph(int v);
void addGraphEdge(int src, int dest);
void printGraph(void);
void freeGraph(void);
Node* newNode(int dest);

void doTarjan(void);
void strongConnect(int vertex);
void reduceSCC(int vertex, int vertex2);

void doDFS(void);
void visitDFS(int vertex);

int min(int a, int b);
int max(int a, int b);

/******************************************************************************
 * MAIN FUNCTIONS
 *****************************************************************************/
void readInput(void)
{
	int v;
	int e;
	int i;
	int aux[2];

	if(fscanf(stdin, "%d,%d", &v, &e) != 2)
	{
		printf("Error: did not read 2 parameters (number of vertices and number of edges).");
		exit(EXIT_FAILURE);
	}

	graph = newGraph(v);
	grades = safeMalloc(v * sizeof(int));

	for(i = 0; i < v; i++)
	{
		if(fscanf(stdin, "%d", &aux[0]) != 1)
		{
			printf("Error: did not read parameters (value of vertex).");
			exit(EXIT_FAILURE);
		}
		grades[i] = aux[0];
	}

	for(i = 0; i < e; i++)
	{
		if(fscanf(stdin, "%d %d", &aux[0], &aux[1]) != 2)
		{
			printf("Error: did not read 2 parameters (edge source and edge destination).");
			exit(EXIT_FAILURE);
		}
		addGraphEdge(aux[0] - 1, aux[1] - 1);
	}

	return;
}

void writeOutput(void){
	int i;
	for(i = 0; i < graph->V; i++)
		printf("%d\n", grades[scc[i]]);
}

int main(void)
{
	readInput();

	stack = newStack();
	scc = safeMalloc(graph->V * sizeof(int));

	dist = safeMalloc(graph->V * sizeof(int));
	low = safeMalloc(graph->V * sizeof(int));
	onStack = safeMalloc(graph->V * sizeof(int));
	visited = 0;

	doTarjan();

	free(dist);
	free(low);
	free(onStack);

	color = safeMalloc(graph->V * sizeof(int));

	doDFS();

	writeOutput();

	freeGraph();
	free(grades);
	freeStack();
	free(scc);
	free(color);

	return 0;
}

/******************************************************************************
 * MALLOC
 *****************************************************************************/
void* safeMalloc(int size)
{
	void* pointer = can_fail_malloc(size);
	if(!pointer)
	{
		perror("Error: ");
		exit(EXIT_FAILURE);
	}
	return pointer;
}

/******************************************************************************
 * STACK
 *****************************************************************************/
Stack* newStack(void){
	return NULL;
}

int isStackEmpty(void){
	if(stack == NULL)
		return 1;
	else
		return 0;
}

void pushStack(int this){
	Stack* new = safeMalloc(sizeof(Stack));
	new->number = this;

	if(stack == NULL)
		new->next = NULL;
	else
		new->next = stack;

	stack = new;
	return;
}

int popStack(void){
	if(stack == NULL)
		return -1;

	Stack* aux;
	int this;

	aux = stack;
	stack = stack->next;
	this = aux->number;

	free(aux);
	return this;
}

void printStack(void){
	Stack* aux = stack;
	while(aux)
	{
		printf("%d->",aux->number);
		aux = aux->next;
	}
	printf("\n");

	return;
}

void freeStack(void)
{
	Stack* aux;
	while(stack)
	{
		aux = stack;
		stack = stack->next;
		free(aux);
	}
	return;
}

/******************************************************************************
 * GRAPH
 *****************************************************************************/
Graph* newGraph(int v){
	int i;
	Graph* graph;

	graph = safeMalloc(sizeof(Graph));

	graph->V = v;
	graph->E = 0;
	graph->vertices = safeMalloc(v * sizeof(Node));

	for(i = 0; i < v; i++)
		graph->vertices[i] = NULL;

	return graph;
}

void addGraphEdge(int src, int dest){
	if(!graph->vertices[src])
		graph->vertices[src] = newNode(dest);
	else
	{
		Node* new = newNode(dest);
	    new->next = graph->vertices[src];
	    graph->vertices[src] = new;
	}
	graph->E++;

	return;
}

Node* newNode(int dest) 
{ 
    Node* new = safeMalloc(sizeof(Node)); 
    new->dest = dest;
    new->next = NULL;
    return new;
}

void printGraph(void){
	int i;
	Node* aux;

	printf("Graph G(V,E) = (%d,%d)\n", graph->V, graph->E);
	for(i = 0; i < graph->V; i++)
	{
		printf("\nAdjacent to %d\n", i + 1);

		for(aux = graph->vertices[i]; aux != NULL; aux = aux->next)
			printf("%d-", aux->dest + 1);
		
		printf("\n");
	}

	return;
}

void freeGraph(void){
	int i;
	Node* aux;
	for(i = 0; i < graph->V; i++)
		while(graph->vertices[scc[i]])
		{
			aux = graph->vertices[scc[i]];
			graph->vertices[scc[i]] = aux->next;
			free(aux);
		}

	free(graph->vertices);
	free(graph);

	return;
}

/******************************************************************************
 * TARJAN
 *****************************************************************************/
void doTarjan(void){
	int i;
	for(i = 0; i < graph->V; i++)
	{
		onStack[i] = 0;
		dist[i] = -1;
	}

	for(i = 0; i < graph->V; i++)
		if(dist[i] == -1)
			strongConnect(i);

	return;
}

void strongConnect(int vertex){
	Node* node;

	dist[vertex] = low[vertex] = visited;
	visited++;

	int aux;
	pushStack(vertex);
	onStack[vertex] = 1;

	for(node = graph->vertices[vertex]; node != NULL; node = node->next)
		if(dist[node->dest] == -1 || onStack[node->dest] == 1)
		{
			if(dist[node->dest] == -1)
				strongConnect(node->dest);
			low[vertex] = min(low[vertex], low[node->dest]);
		}

	if(low[vertex] == dist[vertex])
	{
		do{
			aux = popStack();
			onStack[aux] = 0;
			scc[aux] = vertex;
			if(vertex != aux)
				reduceSCC(vertex, aux);
		}while(vertex != aux);
	}
	return;
}

void reduceSCC(int vertex, int vertex2){
	Node* node = graph->vertices[vertex2]; 

	grades[vertex] = max(grades[vertex], grades[vertex2]);

	if(node != NULL)
	{
		while(node->next != NULL)
			node = node->next;

		node->next = graph->vertices[vertex];
		graph->vertices[vertex] = graph->vertices[vertex2];
	}
	return;
}

/******************************************************************************
 * DFS
 *****************************************************************************/
void doDFS(void){
	int i;
	for(i = 0; i < graph->V; i++)
		color[i] = 0;

	for(i = 0; i < graph->V; i++)
		if(color[scc[i]] == 0)
			visitDFS(scc[i]);

	return;
}

void visitDFS(int vertex){
	Node* node;
	color[vertex] = 1;

	for(node = graph->vertices[vertex]; node != NULL; node = node->next)
	{
		if(color[scc[node->dest]] == 0)
			visitDFS(scc[node->dest]);

		grades[vertex] = max(grades[vertex], grades[scc[node->dest]]);
	}

	return;
}

/******************************************************************************
 * OTHER FUNCTIONS
 *****************************************************************************/
int min(int a, int b){
	return (a < b) ? a : b;
}

int max(int a, int b){
	return (a > b) ? a : b;
}
