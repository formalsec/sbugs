#include <stdio.h>
#include <stdlib.h>

#define MAX(x, y) (((x)>(y))?(x):(y))
#define MIN(x, y) (((x)<(y))?(x):(y))

/* ESTRUTURAS */

typedef struct neighbour {
    int id;
    struct neighbour* next;
} *neighbour_ptr;

typedef struct edge {
    int u;
    int v;
    int f;
    int w;
    struct edge* next;
} *edge_ptr;

typedef struct node {
    neighbour_ptr neighbours;
    edge_ptr edges;
} *node_ptr;

/* FUNCOES AUXILIARES */

void addEdge(node_ptr n, edge_ptr e) {
    e -> next = n -> edges;
    n -> edges = e;
}

void addNeighbour(node_ptr nd, neighbour_ptr nb) {
    nb -> next = nd -> neighbours;
    nd -> neighbours = nb;
}

neighbour_ptr newNeighbour(int num) {
    neighbour_ptr aux = malloc(sizeof(struct neighbour));
    aux -> id = num;
    return aux;
}

int main() {

    int f, e, t, u, v, w, i;
    edge_ptr aux_edge;
    scanf("%d %d %d", &f, &e, &t);
    int aux = f+e+2;
    node_ptr g = malloc(aux * sizeof(struct node));
    int *pc = malloc(aux * sizeof(int));
    int *height = malloc(aux * sizeof(int));
    int *excess = malloc(aux * sizeof(int));
    
    /* Inicializacao Nodes */
    for (i=1; i<aux; i++) {
        g[i].neighbours = NULL;
        g[i].edges = NULL;
    }
    
    /* Inicializacao PreFlow */
    for (i=2; i<aux; i++) {
        height[i] = 0;
        excess[i] = 0;
    }
    
    /* Leitura da producao de cada fornecedor */
    for (i=2; i<=f+1; i++) {
        scanf("%d", &pc[i]);
    }
    
    /* Leitura da capacidade para cada estacao de abastecimento */
    for (i=f+2; i<=f+e+1; i++) {
        scanf("%d", &pc[i]);
    }
    
    /* Construcao do grafo transposto */
    for (i=0; i<t; i++) {
        scanf("%d %d %d", &u, &v, &w);
        aux_edge = malloc(sizeof(struct edge));
        aux_edge -> u = v;
        aux_edge -> v = u;
        aux_edge -> f = 0;
        aux_edge -> w = w;
        addEdge(&g[v], aux_edge);
        addNeighbour(&g[u], newNeighbour(v));
        addNeighbour(&g[v], newNeighbour(u));
    }
    
    /* Algoritmo Relabel-To-front */
    

    return 0;
}
