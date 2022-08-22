/*Trabalho realizado por:*/
/*Telmo Lopes, 89540*/
/*Jose Gomes, 89490*/

#include <stdio.h>
#include <stdlib.h>

#define NOT_DISCOVERED -1
#define FALSE 0
#define TRUE 1

/*=====================Nodes=======================*/

typedef struct Node *node;

struct Node
{
	int number;
	node nextNode;
};

void initList(node* list);
void printAndClearList(node list);
node pushNode(node list, int number);
int isEmpty(node *list);
int popNode(node *list);
void clearList(node list);

/*=====================Graph=======================*/

typedef struct Graph *graph;

struct Graph {
	int V, E, visit, componentsNumber;
	int *d, *d_cut, *low, *low_cut, *parent;
	node *adj, stack;
};

void initVertex(graph g, int v);
graph graphInit(int V);
void graphDestroy(graph g);
graph graphReset(graph g);
graph readLineArguments();

/*=====================Code=======================*/

int max(int u, int v);
int min(int u, int v);
void tarjanVisitCut(graph g, int v, node* maxSCC, int *cutVertexNum);
void tarjanCut(graph g, node* maxSCC, int *cutVertexNum);
void tarjanVisit(graph g, int v, int *maxRouterNumber);
void tarjan(graph g, int *maxRouterNumber);

void initList(node* list)
{
	*list = NULL;
}

void printAndClearList(node list) {
	node prev;
	while (list ->nextNode != NULL) {
		printf("%d ", (list -> number));
		prev = list;
		list = list -> nextNode;
		free(prev);
	}
	printf("%d\n", list -> number);
	free(list);
}

node pushNode(node list, int number) 
{
	node newNode = (node) malloc(sizeof(struct Node));
	newNode->number = number;
	newNode->nextNode = list;
	return newNode;
}

int isEmpty(node *list)
{
	if(*list == NULL)
		return 1;
	else return 0;
}

int popNode(node *list)
{
	int number;
	node aux;
	if(!isEmpty(list))
	{
		number = (*list)->number;
		aux = *list;
		*list = aux->nextNode;
		free(aux);
		return number;
	}
	else return 0;
}

void clearList(node list)
{
	node prev;
	while (list != NULL) {
		prev = list;
		list = list -> nextNode;
		free(prev);
	}
}

void initVertex(graph g, int v)
{
	g -> d[v] = NOT_DISCOVERED;
	g -> parent[v] = NOT_DISCOVERED;
	g -> d_cut[v] = g -> low_cut[v] = 1;
	initList(&g -> adj[v]);
}

graph graphInit(int V) {
	int v;
	graph g = (graph) malloc(sizeof(struct Graph));
	g->V = V;
	g->E = 0;
	g->componentsNumber = 0;
	g->visit = 1;
	g -> d = (int*) malloc(V * sizeof(int));
	g -> d_cut = (int*) malloc(V * sizeof(int));
	g -> low = (int*) malloc(V * sizeof(int));
	g -> low_cut = (int*) malloc(V * sizeof(int));
	g -> parent = (int*) malloc(V * sizeof(int));
	g -> adj = (node*) malloc(V * sizeof(node));
	for (v = 0; v < V; v++) {
		initVertex(g, v);
	}
	return g;
}

void graphInsertE(graph g, int v, int w) {
	g->adj[v] = pushNode(g->adj[v], w);
	g->adj[w] = pushNode(g->adj[w], v);
	g->E++;
}

void graphDestroy(graph g) {
	int v;
	for (v = 0; v < g -> V; v++) {
		if (g -> adj[v] != NULL)
			clearList(g -> adj[v]);
	}
	free(g -> d);
	free(g -> low);
	free(g -> adj);
	free(g);
}

graph graphReset(graph g) {
	int v;
	g->componentsNumber = 0;
	g->visit = 1;
	for (v = 1; v < g -> V; v++) {
		if (g -> adj[v] != NULL)
		{
			g -> d[v] = NOT_DISCOVERED;
			g -> low[v] = NOT_DISCOVERED;
		}
	}
	free(g -> d_cut);
	free(g -> low_cut);
	free(g -> parent);
	return g;
}

graph readLineArguments() {
	int V, E, i;
	scanf("%d", &V);
	scanf("%d", &E);
	graph g = graphInit(V+1);
	for(i = 0; i < E; i++) {
		int v, w;
		scanf("%d %d", &v, &w);
		graphInsertE(g, v, w);
	}
	return g;
}

int max(int u, int v)
{
	if(u > v)
		return u;
	else return v;
}

int min(int u, int v)
{
	if(u < v)
		return u;
	else return v;
}

void tarjanVisitCut(graph g, int v, node* maxSCC, int *cutVertexNum)
{ 
	int w, isCut = FALSE, children = 0;
	g -> d[v] = g -> low[v] = (g->visit)++;
	if (g -> parent[v] != NOT_DISCOVERED)
		g -> d_cut[v] = g -> low_cut[v] = (g -> d_cut[g -> parent[v]] + 1);
 	node* stack = &g -> stack;
	*stack = pushNode(*stack, v);
	node adj = g -> adj[v];
	for (; adj != NULL; adj = adj -> nextNode) {
		w = adj -> number;
		if (g -> d[w] == NOT_DISCOVERED) {
			children++;
			g -> parent[w] = v;
			tarjanVisitCut(g, w, maxSCC, cutVertexNum);
			g -> low[v] = min(g -> low[v], g -> low[w]);
			g -> low_cut[v] = min(g -> low_cut[v], g -> low_cut[w]);
			if (g -> low_cut[w] >= g -> d_cut[v])
				isCut = TRUE;
		}
		else
			g -> low[v] = min(g -> low[v], g -> d[w]);
		if (g -> d[w] != NOT_DISCOVERED && g -> parent[v] != adj -> number)
			g -> low_cut[v] = min(g -> low_cut[v], g -> d_cut[w]);
	}
	if ((g -> parent[v] != NOT_DISCOVERED && isCut) || (g -> parent[v] == NOT_DISCOVERED && children > 1))
	{
		(*cutVertexNum)++;
		clearList(g -> adj[v]);
		g -> adj[v] = NULL;
	}
	if (g -> d[v] == g -> low[v]) {
		int number, maxNum = 0;
		g -> componentsNumber++;
		do {
			number = popNode(stack);
			maxNum = max(number, maxNum);
		} while (number != v);
		*maxSCC = pushNode(*maxSCC, maxNum);
	}
}

void tarjanCut(graph g, node* maxSCC, int *cutVertexNum)
{
	int i;
	for (i = (g -> V - 1); i > 0; i--)
	{
		if (g -> d[i] == NOT_DISCOVERED)
			tarjanVisitCut(g, i, maxSCC, cutVertexNum);
	}
}

void tarjanVisit(graph g, int v, int *maxRouterNumber)
{ 
	int w;
	g -> d[v] = g -> low[v] = (g->visit)++;
 	node* stack = &g -> stack;
	*stack = pushNode(*stack, v);
	node adj = g -> adj[v];
	for (; adj != NULL; adj = adj -> nextNode) {
		w = adj -> number;
		if (g -> adj[w] != NULL)
		{
			if (g -> d[w] == NOT_DISCOVERED) {
				tarjanVisit(g, w, maxRouterNumber);
				g -> low[v] = min(g -> low[v], g -> low[w]);
			}
			else 
				g -> low[v] = min(g -> low[v], g -> d[w]);
		}
	}
	if (g -> d[v] == g -> low[v]) {
		int number, inc = 0;
		do {
			number = popNode(stack);
			inc++;
		} while (number != v);
		if (inc > *maxRouterNumber)
			*maxRouterNumber = inc;
	}
}

void tarjan(graph g, int *maxRouterNumber)
{
	int i = 1;
	for (;i < g -> V; i++)
	{
		if (g -> d[i] == NOT_DISCOVERED)
			tarjanVisit(g, i, maxRouterNumber);
	}
}

int main()
{
	int cutVertexNum = 0, maxRouterNumber = 0;
	node maxSCC;
	initList(&maxSCC);
	graph g = readLineArguments();
	tarjanCut(g, &maxSCC, &cutVertexNum);
	printf("%d\n", g -> componentsNumber);
	printAndClearList(maxSCC);
	printf("%d\n", cutVertexNum);
	graphReset(g);
	tarjan(g, &maxRouterNumber);
	printf("%d\n", maxRouterNumber);
	graphDestroy(g);
	return 0;
}
