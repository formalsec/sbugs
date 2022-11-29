#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct graph *Graph;
typedef struct node *link;

struct node {
int v;
link next;
};

struct graph {
int V;
int E;
link *adj;
};

link NEWnode(int v, link next){
    link a = can_fail_malloc(sizeof(struct node));
    a->v = v;
    a->next = next;
    return a;
}

Graph GRAPHinit(int V, int* markings, int* visited){
    int v;
    Graph G = can_fail_malloc(sizeof *G);
    G->V = V;
    G->E = 0;
    G->adj = can_fail_malloc(V * sizeof(link));
    for (v=0; v < V; v++){
        G->adj[v] =  NULL;
        markings[v] = 0;
        visited[v] = 0;
    }
    return G; 
}

void GRAPHinsertE(Graph G, int v, int w ){
    G->adj[v] = NEWnode(w, G->adj[v]);
    G->E++;
}

void markAncestor(Graph G, int v, int* visited, int* markings){
    link i;
    visited[v] = 1;
    if (markings[v] == 0){
        markings[v] = 1;
    }
    else if (markings[v] == 1){
        markings[v] = 2;
    }
    for (i = G->adj[v]; i != NULL; i = i->next){
        if (visited[i->v] == 0){
            markAncestor(G,i->v,visited,markings);
        }
    }
}

void resetVisited(Graph G,int* visited){
    int v;
    for (v=0;v<G->V;v++){
        visited[v] = 0;
    }
}

int returnInter(Graph G, int *markings, int *candidates){
    int v;
    int i = 0;
    for (v=0;v<G->V;v++){
        if (markings[v] == 2){
            candidates[i] = v;
            i++;
        }
    }
    return i;
}

int partof(Graph G, int *candidates, int v){
    int i;
    for (i=0; i<G->V; i++){
        if (candidates[i] == v){
            return 1;
        }
    }
    return 0;
}

void lowestA(Graph G, int *candidates, int *markings, int size){
    link a;
    int i;
    for (i=0;i<size;i++){
        for (a = G->adj[candidates[i]]; a != NULL;a = a->next){
            if (partof(G,candidates,a->v) == 1){
                markings[a->v] = 0;
            }
        }
    }
}

int main(){
    int node1, node2;
    int V,E;
    int x,y;
    int i = 0;
    int sizec;
    Graph G;
    scanf("%d %d", &node1, &node2);
    scanf("%d %d", &V, &E);
    int* candidates = (int*)can_fail_malloc(V*sizeof(int));
    int* markings = (int*)can_fail_malloc(V*sizeof(int));
    int* visited = (int*)can_fail_malloc(V*sizeof(int));
    G = GRAPHinit(V,markings,visited);
    while (i<E){
        scanf("%d %d", &x, &y);
        GRAPHinsertE(G,y,x);
        i++;
    }
    markAncestor(G,node1,visited,markings);
    resetVisited(G,visited);
    markAncestor(G,node2,visited,markings);
    sizec = returnInter(G,markings,candidates);
    lowestA(G,candidates,markings,sizec);
    sizec = returnInter(G,markings,candidates);
    if (sizec == 0){
        printf("-\n");
    }
    else{
        for(i=0;i<sizec;i++){
            printf("%d ", candidates[i]);
        }
        printf("\n");
    }
    return 0;
}