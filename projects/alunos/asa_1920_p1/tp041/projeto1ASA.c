#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_LINE_SIZE 100
#define WHITE 0
#define BLACK 1
#define GRAY 2
#define NIL -1

struct node_SCC
{
	int max_grade;

};



typedef struct node_pilha
{	
	int value;
	struct node_pilha* next;
	
}node_pilha;


typedef struct AdjListNode
{	
	int dest;
	struct AdjListNode* next;
	
}AdjListNode;


typedef struct AdjList
{
	AdjListNode* head;
}AdjList;



typedef struct SCC_Node
{	
	int node;
	struct SCC_Node* next;
	
}SCC_Node;


typedef struct SCC_List
{
	SCC_Node* head;
}SCC_List;




typedef struct Graph
{
	int V;
	int* color;
	int* pi;
	int* d;
	int* f;
	int* low;
	int* grade;
	int* scc;
	AdjList* array;

}Graph;


typedef struct SCC_Graph
{
	int V;
	int* color;
	int* pi;
	int* d;
	int* f;
	int* max_grade;
	AdjList* array;

}SCC_Graph;



int time; 
int visited;
int numSCC;
static node_pilha* top;
int* is_in_stack;

SCC_List* scc_array;



AdjListNode* addAdjListNode(int dest);
SCC_Node* addSCC_Node(int node);
Graph* createGraph(int V);
void addEdge(Graph* graph, int orig, int dest);
void addToSCC(int v, int w);
void DFS(Graph* graph);
void DFS_Visit(Graph* graph, int u);
void SCC_Tarjan(Graph* graph);
void Tarjan_Visit(Graph* graph, int u);
void init_pilha();
void push(int value);
int is_empty();
int pop();
int min(int u, int v);
int max_grade(Graph* graph, int i);



int main(){

	int i,v,n,grade,orig,dest;
	int numStudents;
	int numRelationships;
	char line[MAX_LINE_SIZE];

	n = scanf("%s",line);
	if(n<0)perror("Error:scanf");

	sscanf(line,"%d,%d",&numStudents,&numRelationships);

	Graph* graph = createGraph(numStudents);

	for(i = 0;i < numStudents;i++){
		n = scanf("%d",&grade);
		if(n<0)perror("Error:scanf");
		graph->grade[i] = grade;
	}

	for(i = 0;i < numRelationships;i++){	
		n = scanf("%d %d",&orig,&dest);
		if(n<0)perror("Error:scanf");
		addEdge(graph,orig-1,dest-1);
	}

	SCC_Tarjan(graph);


	Graph* scc_graph = createGraph(numSCC);
	for(i = 0;i < numSCC;i++){
		scc_graph->grade[i] = max_grade(graph,i);
	}

	for(i = 0 ;i < numStudents;i++){
		int s = graph->scc[i];
		AdjListNode* adjNode;
		for(adjNode = graph->array[i].head;adjNode != NULL;adjNode = adjNode->next){
			v = adjNode->dest;
			if(graph->scc[v] != s){
				addEdge(scc_graph,s,graph->scc[v]);
			}
		}
	}

	DFS(scc_graph);

	for(i = 0;i < numSCC;i++){
		SCC_Node* sccNode;
		for(sccNode = scc_array[i].head;sccNode != NULL;sccNode = sccNode->next){	
			v = sccNode->node;
			graph->grade[v] = scc_graph->grade[i];
		}
	}

	for(i = 0;i < numStudents;i++){
		printf("%d\n",graph->grade[i]);
	}

	return 0;
}


AdjListNode* addAdjListNode(int dest){
	AdjListNode* newNode = (AdjListNode*) can_fail_malloc(sizeof(AdjListNode));
	newNode->dest = dest;
	newNode->next = NULL; 
	return newNode;
}


SCC_Node* addSCCNode(int node){
	SCC_Node* newNode = (SCC_Node*) can_fail_malloc(sizeof(SCC_Node));
	newNode->node = node;
	newNode->next = NULL; 
	return newNode;
}


Graph* createGraph(int V){

	Graph* graph = (Graph*) can_fail_malloc(sizeof(Graph));
	graph->V = V;

	graph->array = (AdjList*) can_fail_malloc(V * sizeof(AdjList));

	graph->color = (int*) can_fail_malloc(V * sizeof(int));
	graph->pi = (int*) can_fail_malloc(V * sizeof(int));
	graph->d = (int*) can_fail_malloc(V * sizeof(int));
	graph->f = (int*) can_fail_malloc(V * sizeof(int));
	graph->low = (int*) can_fail_malloc(V * sizeof(int));
	graph->grade = (int*) can_fail_malloc(V * sizeof(int));

	graph->scc = (int*) can_fail_malloc(V * sizeof(int));

	int i;
	for(i = 0; i < V;i++){
		graph->array[i].head = NULL;
	}

	return graph;

}

void addEdge(Graph* graph, int orig, int dest){

	AdjListNode* newNode = addAdjListNode(dest);
	newNode->next = graph->array[orig].head;
	graph->array[orig].head = newNode;
}

void addToSCC(int v, int w){
	SCC_Node* newNode = addSCCNode(w);
	newNode->next = scc_array[v].head;
	scc_array[v].head = newNode;
}


/*----------------------------------------------------------------------------------------------- Algoritmo DFS---------------------------------------------------------------------------------------*/


void DFS(Graph* graph){

	int V = graph->V;
	int u;
	for(u = 0;u < V;u++){
		graph->color[u] = WHITE;
		graph->d[u] = INT_MAX;
		graph->f[u] = INT_MAX;
		graph->pi[u] = NIL;
	}
	time = 1;
	for(u = 0;u < V;u++){
		if (graph->color[u] == WHITE)
			DFS_Visit(graph,u);
	}

}


void DFS_Visit(Graph* graph, int u){

	int v;
	int max_grade = 0;
	graph->color[u] = GRAY;
	graph->d[u] = time;
	time++;
	AdjListNode* adjNode;
	for(adjNode = graph->array[u].head;adjNode != NULL;adjNode = adjNode->next){
		v = adjNode->dest;
		if(graph->grade[v] > max_grade){
			max_grade = graph->grade[v];
		}
		if(graph->color[v] == WHITE){
			graph->pi[v] = u;
			DFS_Visit(graph,u);
		}
	}
	graph->color[u] = BLACK;
	graph->f[u] = time;
	if(max_grade > graph->grade[u]){
		graph->grade[u] = max_grade;
	}
	time++;
}


/*----------------------------------------------------------------------------------------------- Algoritmo Tarjan------------------------------------------------------------------------------------------*/


void SCC_Tarjan(Graph* graph){

	int V = graph->V;
	int u;
	visited = 0;
	numSCC = 0;
	scc_array = (SCC_List*) can_fail_malloc(V * sizeof(SCC_List));
	for(u = 0; u < V;u++){
		scc_array[u].head = NULL;
	}
	init_pilha();
	is_in_stack = (int*) can_fail_malloc(V * sizeof(int));
	for(u = 0;u < V;u++){
		graph->d[u] = INT_MAX;
		is_in_stack[u] = 0;
	}
	for(u = 0;u < V;u++){
		if (graph->d[u] == INT_MAX){
			Tarjan_Visit(graph,u);
		}
	}

}

void Tarjan_Visit(Graph* graph, int u){

	int v;
	graph->d[u] = visited;
	graph->low[u] = visited;
	visited++;
	push(u);
	is_in_stack[u] = 1;

	AdjListNode* adjNode;
	for(adjNode = graph->array[u].head;adjNode != NULL;adjNode = adjNode->next){
		v = adjNode->dest;

		if(graph->d[v] == INT_MAX || /* V € L */ is_in_stack[v] == 1){
			if(graph->d[v] == INT_MAX){
				Tarjan_Visit(graph,v);
			}
		graph->low[u] = min(graph->low[u],graph->low[v]);
		}
	}
	if (graph->d[u] == graph->low[u]){
		numSCC++;
		do{
			v = pop();
			is_in_stack[v] = 0;
			addToSCC(numSCC-1,v);
			graph->scc[v] = numSCC-1;
		}
		while( u != v);
	}
}



/*----------------------------------------------------------------------------------------------- Pilha------------------------------------------------------------------------------------------*/


void init_pilha(){
	top = NULL;
}

void push(int value){
	node_pilha* new = (node_pilha*) can_fail_malloc(sizeof(node_pilha));

	new->value = value;
	new->next = top;
	top = new;
}

int is_empty(){
	return top == NULL;
}

int pop(){

	if(!is_empty()){
		int value;
		node_pilha* old;
		value = top->value;
		old = top;
		top = top->next;
		free(old);
		return value;
	}
	return -1;
}

/*----------------------------------------------------------------------------------------------- Aux------------------------------------------------------------------------------------------*/

int min(int u, int v){
	if(u < v){
		return u;
	}
	else{
		return v;
	}
}

int max_grade(Graph* graph, int i){
	int max_grade = 0;
	int v;
	SCC_Node* sccNode;
	for(sccNode = scc_array[i].head;sccNode != NULL;sccNode = sccNode->next){	
		v = sccNode->node;
		if(graph->grade[v] > max_grade){
			max_grade = graph->grade[v];
		}
	}
	return max_grade;
}
