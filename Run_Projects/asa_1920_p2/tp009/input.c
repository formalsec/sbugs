#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define NIL -1

typedef struct Grafo {
    int numVertices;
    int** adjList; 
    int* numArcs;                                                                                    
} grafo;

typedef struct Fila {
    int *list;
    int head, tail;
} fila;

grafo graph;

fila queue;

int qIsEmpty() {
	return (queue.head == queue.tail);
}

void qInit() {
	queue.head = 0;
    queue.tail = 0;
}

void qPush(int n) {
	queue.list[queue.tail++] = n;
}

int qPop() {
	int n = NIL;
	if (!qIsEmpty(queue))
		n = queue.list[queue.head++];
	return n;
}


void insert(int src, int dest) {
    graph.adjList[src] = realloc(graph.adjList[src], ((++graph.numArcs[src]))*sizeof(int));
    graph.adjList[src][graph.numArcs[src]-1] = dest;
}

void delete(int src, int pos) {
    for (; pos < graph.numArcs[src]-1; pos++)
        graph.adjList[src][pos] = graph.adjList[src][pos+1];  
    graph.adjList[src] = realloc(graph.adjList[src], ((--graph.numArcs[src]))*sizeof(int));
}

void processInput() {
    int a,b,i,e,d,c;
    /* read number of streets and avenues */
    scanf("%d %d",&d,&c);
    graph.numVertices = d*c;
    graph.numArcs = malloc(sizeof(int)*(graph.numVertices*2 + 2));
    graph.adjList = (int **)malloc((graph.numVertices*2 + 2) * sizeof(int *));
    /* initialize empty capacity matrix */
    for (i = 0; i < graph.numVertices; i++) {
        graph.adjList[i] = (int *)malloc(sizeof(int));
        graph.numArcs[i] = 0;
        graph.adjList[i + graph.numVertices] = (int *)malloc(sizeof(int));
        graph.numArcs[i + graph.numVertices] = 0;
        /* first numVertices vertices in graph are in
           last numVertices vertices in graph are out
           in connect to out */
        insert(i, i + graph.numVertices);
        if(i - 1 >= 0  && (i-1) % d != d-1) insert(i + graph.numVertices, i - 1);
        if(i + 1 < graph.numVertices && (i+1) % d != 0) insert(i + graph.numVertices, i + 1);
        if(i + d < graph.numVertices) insert(i + graph.numVertices, i + d);
        if(i - d >= 0) insert(i + graph.numVertices, i - d);
    }
    graph.numVertices *= 2;

    /* read number of supermarkets and houses */
    scanf("%d %d", &c, &e);
    graph.adjList[graph.numVertices] = (int *)malloc(sizeof(int));
    graph.numArcs[graph.numVertices] = 0;
    for (i = 0; i < c; i++) {
        scanf("%d %d", &a, &b);
        insert(a-1+(b-1)*d + graph.numVertices/2, graph.numVertices);
    }
    graph.numVertices++;
    graph.adjList[graph.numVertices] = (int *)malloc(sizeof(int));
    graph.numArcs[graph.numVertices] = 0;
    for (i = 0; i < e; i++) {
        scanf("%d %d", &a, &b);
        insert(graph.numVertices, a-1+(b-1)*d);
    }
    graph.numVertices++;
    /* graph.numVertices-1 -> source */
    /* graph.numVertices-2 -> sink */
}


int findFlux(int u, int v) {
    int i;
    for(i = 0; i < graph.numArcs[u]; i++)
        if(graph.adjList[u][i] == v) return i;
    return NIL;
}

int bfs(int parent[], int s, int t) {
    int u, i, visited[graph.numVertices];
     
    qInit();
    memset(visited, 0, sizeof(visited));

    qPush(s);
    
    visited[s] = 1;
    parent[s] = NIL;

    while (!qIsEmpty(&queue)) {
        u = qPop();
        for(i = 0; i < graph.numArcs[u]; i++) {
            if (!visited[graph.adjList[u][i]]) {
                qPush(graph.adjList[u][i]);
                parent[graph.adjList[u][i]] = u;
                visited[graph.adjList[u][i]] = 1;
            }
            if(visited[t]) return 1;
        }
    }
    return 0;
}


int fordFulkerson() {
    int u, v, s, t;
    int parent[graph.numVertices];
    int maxFlow = 0;
    s = graph.numVertices-1;
    t = graph.numVertices-2;

    queue.list = malloc(sizeof(int)*graph.numVertices);

    while(bfs(parent, s, t)) {
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            delete(u, findFlux(u, v));
            insert(v, u);
        }
        maxFlow++;
    }
    return maxFlow;
}

int main () {
    processInput();
    printf("%d\n", fordFulkerson());
    return 0;
}