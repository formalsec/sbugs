#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/*Bibliotecas*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*Constantes*/
#define INITIAL_SIZE 16
#define NIL -1

/* Definição de estruturas */
typedef struct Vector {
    int* vector;
    int elems;
    int size;
} Vector;

typedef struct Graph {
    int vertices;
    Vector* adj;
} Graph;

typedef struct subNetworksVector {
    Vector* vector;
    int elems;
    int size;
    int biggestSubNetwork;
} subNetworksVector;


/* Protótipos */
void adjDFS(Graph* g, bool goal);
void adjAux(Graph* g, int u, int* time, bool* visited, int* discovery, int* low, int* parent, bool goal);
void addConnectionToGraph(Graph* g, int v, int u);
void graphInit(Graph* g, int vertices);
void vectorInit(Vector* v, int defSize);
void vectorPushback(Vector* v, int element);
void vectorFree(Vector* v);
void subNetworksInit(subNetworksVector* v, int initSize);
void addSubNetwork(subNetworksVector* v, int initSize);
void freeSubNetwork(subNetworksVector* v);
void freeGraph(Graph* g);


/* Varáveis globais / inicializações */
int subNetworksCount = 0;
int max=0;
subNetworksVector* subNetworks;
Vector subNetworkIds;
int crucialPointCounter = 0;
bool* crucialPoints;


/* Código principal */
int main() {

    int routers, connections;
    if (scanf("%d\n%d", &routers, &connections) < 0)
        perror("error on scanf\n");

    Graph* graph = (Graph*) can_fail_malloc(sizeof(struct Graph));
    graphInit(graph, routers);  
    subNetworks = (subNetworksVector*) can_fail_malloc(sizeof(struct subNetworksVector));
    subNetworksInit(subNetworks, INITIAL_SIZE);
    vectorInit(&subNetworkIds, INITIAL_SIZE);

    int aux1, aux2, i;
    for (i=0; i<connections; i++) {
        if (scanf("%d %d", &aux1, &aux2) < 0)
            perror("error on scanf\n");
        addConnectionToGraph(graph, aux1-1, aux2-1);
    }

    crucialPoints = (bool*) can_fail_malloc(sizeof(bool)*routers);
    adjDFS(graph, false);

    printf("%d\n", subNetworksCount);

    for (i=subNetworksCount-1; i>0; i--)
        printf("%d ", subNetworkIds.vector[i] + 1);
    printf("%d\n", subNetworkIds.vector[0] + 1);

    printf("%d\n", crucialPointCounter);

    /** acessório           *                    
    for (int i=0; i<routers; i++)
        printf("%d ", crucialPoints[i]);
    printf("\n");
                                              */

    /* free subNetworks */
    freeSubNetwork(subNetworks);    
    subNetworksCount = 0;

    subNetworks = (subNetworksVector*) can_fail_malloc(sizeof(struct subNetworksVector));
    subNetworksInit(subNetworks, INITIAL_SIZE);
    adjDFS(graph, true);

    printf("%d\n", subNetworks->biggestSubNetwork);
    
    free(crucialPoints);
    freeSubNetwork(subNetworks);
    freeGraph(graph);
    vectorFree(&subNetworkIds);

    return 0;
}

void adjDFS(Graph* g, bool goal) {
    int routers = g->vertices;
    bool* visited = (bool*) can_fail_malloc(sizeof(bool)*routers);
    int* discovery = (int*) can_fail_malloc(sizeof(int)*routers);
    int* low = (int*) can_fail_malloc(sizeof(int)*routers);
    int* parent = (int*) can_fail_malloc(sizeof(int)*routers);
    int* time = (int*) can_fail_malloc(sizeof(int));
    *time = 0;

    int i;
    for (i=0; i<routers; i++) {
        visited[i] = false;
        parent[i] = NIL;
        if (!goal)
            crucialPoints[i] = false;
    }

    for (i=routers-1; i>=0; i--) {
        if (!visited[i] && !crucialPoints[i]) {
            addSubNetwork(subNetworks, INITIAL_SIZE);
            adjAux(g, i, time, visited, discovery, low, parent, goal);
            vectorPushback(&subNetworkIds, max);
            max=0;
            if (goal && subNetworks->vector[subNetworksCount].elems > subNetworks->biggestSubNetwork)
                subNetworks->biggestSubNetwork = subNetworks->vector[subNetworksCount].elems;  

            subNetworksCount++;
        }
    }

    free(visited);
    free(discovery);
    free(low);
    free(parent);
    free(time);
}

void adjAux(Graph* g, int u, int* time, bool* visited, int* discovery, int* low, int* parent, bool goal) {
    int children = 0;
    visited[u] = true;
    discovery[u] = low[u] = ++(*time);

    vectorPushback(&subNetworks->vector[subNetworksCount], u);

    if (u > max)
        max = u;

    int i;
    for (i=0; i<g->adj[u].elems; i++) {
        int v = g->adj[u].vector[i];

        if ((goal && !crucialPoints[v]) || (!goal)) {

            if (!visited[v]) {

                children++;
                parent[v] = u;
                adjAux(g, v, time, visited, discovery, low, parent, goal);

                low[u] = low[u]<low[v] ? low[u] : low[v];
                
                if (!goal && (((children > 1 && parent[u] == NIL) || (low[v] >= discovery[u] && parent[u] != NIL)) && !crucialPoints[u])) {
                    crucialPoints[u] = true;
                    crucialPointCounter++;
                }

            } else if (v != parent[u])
                low[u] = low[u] < discovery[v] ? low[u] : discovery[v];
        }
    }
}

void addConnectionToGraph(Graph* g, int v, int u) {
    vectorPushback(&g->adj[v], u);
    vectorPushback(&g->adj[u], v);
}

void graphInit(Graph* g, int vertices) {
    g->vertices = vertices;
    g->adj = (Vector*) can_fail_malloc(sizeof(struct Vector)*vertices);
    int i;
    for (i=0; i<vertices; i++)
        vectorInit(&g->adj[i], INITIAL_SIZE);
}

void vectorInit(Vector* v, int initSize) {
    v->vector = (int*) can_fail_calloc(initSize ,sizeof(int));
    v->elems = 0;
    v->size = initSize;
}

void vectorPushback(Vector* v, int element) {
    if (v->elems == v->size) {
        v->size *= 2;
        v->vector = can_fail_realloc(v->vector, sizeof(int)*v->size);
    }
    v->vector[v->elems++] = element;
}

void vectorFree(Vector* v) {
    free(v->vector);
    v->vector = NULL;
    v->size = v->elems = 0;
}

void subNetworksInit(subNetworksVector* v, int initSize) {
    v->vector = (Vector*) can_fail_malloc(sizeof(struct subNetworksVector)*initSize);
    int i;
    for (i=0; i<initSize; i++) {
        vectorInit(&v->vector[i], initSize);
    }
    v->elems = 0;
    v->size = initSize;
    v->biggestSubNetwork = 0;
}

void addSubNetwork(subNetworksVector* v, int initSize) {
    if (v->elems == v->size) {
        v->size *= 2;
        v->vector = can_fail_realloc(v->vector, sizeof(struct Vector)*v->size);
        int i;
        for (i=v->elems; i<v->size; i++) {
            vectorInit(&v->vector[i], INITIAL_SIZE);
        }
    }
    v->elems++;
}

void freeSubNetwork(subNetworksVector* v) {
    int i=0;
    for (; i<v->size; i++) {
        vectorFree(&v->vector[i]);
    }

    free(v->vector);
    free(v);
}

void freeGraph(Graph* g) {
    int i=0;
    for (; i<g->vertices; i++) {
        vectorFree(&g->adj[i]);
    }

    free(g->adj);
    free(g);
}