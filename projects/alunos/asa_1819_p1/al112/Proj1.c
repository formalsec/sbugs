#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"


#include <stdio.h>
#include <stdlib.h>

#define TAG_U 0
#define TAG_V 1

#define FALSE 0
#define TRUE 1;

#define minimum(a, b) a <= b ? a : b;


/******** ESTRUTURAS *******/
typedef struct node {
	int value;
	struct node *next;
} *link;

typedef struct {
	int u;
	int v;
} Edge;

typedef struct graph {
	int V;
	int E;
	link *adj;
} *Graph;

typedef struct {
	int d;
	int low;
	int tag;
} Info;


/******** DECLARACOES *******/

Edge createEdge(int u, int v);
Graph initGraph(int v, int e);
link insertBegin(int value, link head);
link removeBegin(link head);
void insertEdge(Graph graph, Edge edge);

link pop(int last, link head);
void tarjanVisit(int u);
void Tarjan();
void formatEdges();
void radixSort();
int isEqual(Edge a, Edge b);
Edge* removeRepeated();

void printResults();


/******** VARIAVEIS GLOBAIS *******/

int V, E, u, v, i = 0;
int idIndex = 0;
static Graph graph;
Edge edge, edge1;

Info *info; 
int *IDs, *SubNetIds; /* ID do representante do SCC */
Edge *edges, *edges1;

int visited = 0;
link L = NULL;

Edge *res;
int lenght_res = 0;

int nr_SCC = 0;
int nr_connections = 0;
int nr_Subnet=0;



/********** MAIN **********/
int main() {
	scanf("%d", &V);
	scanf("%d", &E);

	/* Inicializacao */
	graph = initGraph(V, E);
	info = can_fail_malloc(V * sizeof(Info));
	IDs = can_fail_malloc(V * sizeof(int));
	SubNetIds = can_fail_malloc(V * sizeof(int));
	edges = can_fail_malloc(E * sizeof(Edge));
	edges1 = can_fail_malloc(E * sizeof(Edge));
	/* Criar arestas do grafo */
	while (i < E) {
		scanf("%d %d", &u, &v);
		edge = createEdge(u - 1, v - 1);
		edge1 = createEdge(v - 1, u - 1);
		insertEdge(graph, edge);
		insertEdge(graph, edge1);
		edges[i] = edge;
		edges1[i] = edge1;
		i++;
	}

	Tarjan();
	printResults();
	return EXIT_SUCCESS;
}


/*********Funcoes Principais********/

/*cria a aresta*/
Edge createEdge(int u, int v){
	Edge edge;
	edge.u=u;
	edge.v=v;
	return edge;
}

/*cria o grafo*/
Graph initGraph(int v, int e) {
	int i;
	Graph graph = can_fail_malloc(sizeof(struct graph));
	graph->V = v;
	graph->E = e;
	graph->adj = can_fail_malloc(v * sizeof(link));
	for (i = 0; i < v; i++)
		graph->adj[i] = NULL;
	return graph;
}

/*coloca no inicio da lista de adj*/
link insertBegin(int value, link head){
	link x = can_fail_malloc(sizeof(struct node));
	x->value = value;
	x->next = head;
	return x;
}

/*remove do inicio da lista de adj*/
link removeBegin(link head){
	link x = head;
	head = x->next;
	free(x);
	return head;
}

/*coloca o vertice no grafo*/
void insertEdge(Graph graph, Edge edge){
	int u = edge.u;
	int v = edge.v;
	graph->adj[u] = insertBegin(v, graph->adj[u]);
}



/************************Algoritmos********************************/
/* Remove do inicio de uma lista ate ao 'last' */
link pop(int last, link head) {
	link x = head;
	int min = x->value;

	while (x != NULL && x->value != last) {
		if (x->value < min) min = x->value;
		info[x->value].tag = nr_SCC;
		x = removeBegin(x);
	}

	if (x->value < min) min = x->value;
	info[x->value].tag = nr_SCC;
	x = removeBegin(x);

	IDs[nr_SCC] = min;
	return x;
}

/* Auxiliar ao Alg. Tarjan - visitar vertice */
void tarjanVisit(int u) {
	link x;

	info[u].d = info[u].low = visited;
	visited++;
	L = insertBegin(u, L);

	for (x = graph->adj[u]; x != NULL; x = x->next) {
		int v = x->value;
		if (info[v].d == -1 || info[v].tag == -1) {
			if (info[v].d == -1)
				tarjanVisit(v);
			info[u].low = minimum(info[u].low, info[v].low);
		}
	}

	if (info[u].d == info[u].low) { /* raiz do SCC */
		L = pop(u, L);
		nr_SCC++;
	}
}

/* Algoritmo de Tarjan - encontrar SCC */
void Tarjan() {
	for (i = 0; i < V; i++) {
		info[i].d = -1;
		info[i].tag = -1;
	}

	for (i = 0; i < V; i++) {
		if (info[i].d == -1){
			tarjanVisit(i);
			SubNetIds[idIndex]=i;
			idIndex++;
		}
	}
	SubNetIds[idIndex]=V;
}


void printResults(){
	int j;
	/*printf("===========OUTPUT============\n");*/
	printf("%d\n", nr_SCC);
	for(j=1; j<idIndex+1; j++)
		printf("%d ", SubNetIds[j]);
	printf("\n");
}

