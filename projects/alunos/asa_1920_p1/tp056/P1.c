#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node
{
	int dest;
	int studentNumber;
	int averageGrade;
	struct Node* next;
}Node;

typedef struct Graph
{
	Node ** head;
}Graph;

typedef struct Edge
{
	int src, dest;
}Edge;

Node ** nodes;

long int numberOfStudents = 0;
long int numberOfEdges = 0;
int *visited;
int *stack;
int top = 0;

int * grades;
Edge * edges;

/* receive and separate the input */
void parseInput(){

	long int e = 0;

	/* divide the first line into the number of students and the number of edges (friendships between students) */
	scanf("%ld,%ld", &numberOfStudents, &numberOfEdges);

	/* allocate memory for the following variables */
	grades = can_fail_malloc(sizeof(int) * numberOfStudents);
	edges = can_fail_malloc(sizeof(Edge) * numberOfEdges);
	visited = can_fail_malloc(sizeof(int) * numberOfStudents);
	stack = can_fail_malloc(sizeof(int) * numberOfStudents);

	/* gets the grades of each student */
	while (e < numberOfStudents) {
        scanf("%d", &grades[e]);
        e++;
    }
    e = 0;

	/* gest the friendships between the students */
  while (e < numberOfEdges) {
    scanf("%d %d", &edges[e].src, &edges[e].dest);
    e++;
  }
}

/* crate an adjacency list from specified edges */
Graph* createGraph()
{
	long int e;

	/* allocate memory for graph data structure */
	Graph* graph = (Graph*)can_fail_malloc(sizeof(Graph));
	graph->head = can_fail_malloc(sizeof(Node*) * numberOfStudents);

	/* initiate head pointer for all values */
	for (e = 0; e < numberOfStudents; e++){
		graph->head[e] = NULL;
	}

	/* add edges to the directed graph one by one */
	for (e = 0; e < numberOfEdges; e++){
		/* get source and destination */
		int src = edges[e].src - 1;
		int dest = edges[e].dest - 1;

		/* allocate new node of adjacency list from src to dest */
		Node *newNode = can_fail_malloc(sizeof(Node));

		/* point new node to head */
		newNode->next = graph->head[src];
		newNode->averageGrade = grades[src];
		newNode->studentNumber = src;
		newNode->dest = dest;

		/* point head to new node */
		graph->head[src] = newNode;
	}
	return graph;
}

/* create the tranpose of the graph */
Graph* createTransposeGraph()
{
	long int e;
	 /* allocate memoru for graph data structure */
	Graph* graph = (Graph*)can_fail_malloc(sizeof(Graph));
	graph->head = can_fail_malloc(sizeof(Node*) * numberOfStudents);

	/* initiate head pointer for all values */
	for (e = 0; e < numberOfStudents; e++){
		graph->head[e] = NULL;
	}

	/* add edges to the directed graph one by one */
	/* where source and destination get switched */
	for (e = 0; e < numberOfEdges; e++){
		int src = edges[e].dest - 1;
		int dest = edges[e].src - 1;

		/* allocate new node of adjacency list from src to dest */
		Node *newNode = can_fail_malloc(sizeof(Node));

		/* point new node to head */
		newNode->next = graph->head[src];
		newNode->averageGrade = grades[src];
		newNode->studentNumber = src;
		newNode->dest = dest;

		/* point head to new node */
		graph->head[src] = newNode;
	}
	return graph;
}

void DFS(Graph* graph, int i)
{
    Node *p;
		/* points the node p to the head pointer of i */
    p = graph->head[i];
		/* marks the current node as visited */
    visited[i]=1;
    while(p!=NULL)
    {
		 /* point i to the destination of the current node */
		 i=p->dest;
		 /* if i hasnt been visited */
	   if(!visited[i])
		 			/* repeats the cycle */
            DFS(graph, i);
				/* else point to the next student */
       	i = p->studentNumber;
        p=p->next;
    }
    stack[top++] = i;
}

void DFS1(Graph* graph, int i)
{

    Node *p;
		/* points the node p to the head pointer of i */
    p = graph->head[i];
		/* marks the current node as visited */
    visited[i]=1;

    while(p!=NULL)
    {
		/* point i to the destination of the current node */
		i=p->dest;
		/* if the grade is lower change it */
		if (grades[i] < grades[p->studentNumber]){
			grades[i] = grades[p->studentNumber];
			visited[i] = 0;
		}
		/* if it hasnt been visited repeat */
		if(!visited[i])
			DFS1(graph, i);
		p=p->next;
    }
}

/* print the final grades of all the students */
void printGrades(){

	int e = 0;
	while(e < numberOfStudents){
		printf("%d\n", grades[e]);
		e++;
	}
}

/* free the allocated memory */
void freeMemory(Graph *graph, Graph *graphTransposed){

	int e;

	Node *p;
	Node *pAux;

	free(grades);
	free(edges);
	free(stack);
	free(visited);

	for (e = 0; e < numberOfStudents; e++){
			p = graph->head[e];
			while (p != NULL){
				pAux = p;
				free(pAux);
				p = p->next;
			}
		}
		free(graph->head);
		free(graph);
		for (e = 0; e < numberOfStudents; e++){
			p = graphTransposed->head[e];
			while (p != NULL){
				pAux = p;
				free(pAux);
				p = p->next;
			}
		}
		free(graphTransposed->head);
		free(graphTransposed);
}

int main(){

	int e = 0;

	parseInput();

	Graph *graph = createGraph();
	Graph *graphTransposed = createTransposeGraph();

	/*Initialize the visisted list*/
	for (e = 0; e < numberOfStudents; e++){
		visited[e] = 0;
	}

	e = 0;
	/*Perform dfs on every node and getting the stack of finishing times*/
	while (e < numberOfStudents){
		if (!visited[e]){
			DFS(graph, e);
		}
		e++;
	}

	for (e = 0; e < numberOfStudents; e++){
		visited[e] = 0;
	}

	e = 0;
	top--;
	/*Performing dfs on every node starting with the highest finishing time
	and propagating grades as you go*/
	while (e < numberOfStudents){
		if (!visited[stack[top]]){
			DFS1(graphTransposed, stack[top]);
		}
		e++;
		top--;
	}

	printGrades();
	freeMemory(graph, graphTransposed);
	return 0;
}
