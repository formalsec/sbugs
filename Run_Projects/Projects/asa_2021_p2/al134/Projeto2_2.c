#include <stdio.h>
#include <stdlib.h>
#define vertex int

int capacity = 0;

typedef struct edge link;

struct edge{

    vertex v;
    int cr; /*capacidade residual*/
    link *twin;
    link *next;

};

typedef struct graph{

    int V;
    link **adj;

}graph;

graph G;

void readInput(){

    int i, nProcesses, nCosts, costY, costX, node1, node2, cost12;

    if(scanf("%d %d", &nProcesses, &nCosts) != 2)
        exit(EXIT_FAILURE);
    
    G.V = nProcesses + 2; 
    G.adj =  (link**) malloc(sizeof(link) * G.V);

    for(i = 0; i < nProcesses; i++){
        link *edgeXP = malloc(sizeof(link)),*edgeYP = malloc(sizeof(link)),*edgePX = malloc(sizeof(link)),*edgePY = malloc(sizeof(link));
        if(scanf("%d %d", &costX, &costY) != 2)
            exit(EXIT_FAILURE);
        
        edgeXP->v = i; 
        edgeXP->cr = costX;  
        edgeXP->twin = edgePX; 
        edgeXP->next = G.adj[G.V-2]; 
        G.adj[G.V-2] = edgeXP; 

        edgePX->v = G.V-2; 
        edgePX->cr = costX;  
        edgePX->twin = edgeXP; 
        edgePX->next = G.adj[i]; 
        G.adj[i] = edgePX; 

        edgeYP->v = i; 
        edgeYP->cr = costY;  
        edgeYP->twin = edgePY; 
        edgeYP->next = G.adj[G.V-1]; 
        G.adj[G.V-1] = edgeYP; 

        edgePY->v = G.V-1; 
        edgePY->cr = costY;  
        edgePY->twin = edgeYP; 
        edgePY->next = G.adj[i]; 
        G.adj[i] = edgePY; 
    }

    for(i = 0; i < nCosts; i++){
        link *edge1_2 = malloc(sizeof(link)), *edge2_1 = malloc(sizeof(link));
        if(scanf("%d %d %d", &node1, &node2, &cost12) != 3)
            exit(EXIT_FAILURE);

        edge1_2->cr = cost12; 
        edge1_2->v = node2-1; 
        edge1_2->twin = edge2_1; 
        edge1_2->next = G.adj[node1-1]; 
        G.adj[node1-1] = edge1_2;

        edge2_1->cr = cost12; 
        edge2_1->v = node1-1; 
        edge2_1->twin = edge1_2; 
        edge2_1->next = G.adj[node2-1]; 
        G.adj[node2-1] = edge2_1;
    }
}


int findPath(vertex s, vertex t, vertex pa[], link *parc[]){
    vertex v,queue[G.V], lenght = 0, first = 0, last = -1;
    int min_flow = __INT_MAX__, visited[G.V];
    link *edge;

    for(v = 0; v < G.V; v++){
        visited[v] = 0;
    }

    visited[s] = 1;
    queue[(++last)%G.V] = s;
    lenght++;

    while(lenght != 0){
        v = queue[(first++)%G.V];
        lenght--;

        if(v == t) break;
        for(edge = G.adj[v]; edge != NULL; edge = edge->next){
            if(edge->cr > 0 && visited[edge->v] != 1){
                visited[edge->v] = 1;
                pa[edge->v] = v; parc[edge->v] = edge;
                queue[(++last)%G.V] = edge->v;
                lenght++;
            }
        }
    }

    if(visited[t] != 1) return 0;
    for(v = t; v != s; v = pa[v]){
        edge = parc[v];
        if(edge->cr < min_flow)
            min_flow = edge->cr;
    }

    return min_flow;
}

void EdmondsKarp(){

    vertex pa[G.V],v;
    link *parc[G.V], *edge;
    int path_flow;

    while((path_flow = findPath(G.V-2, G.V-1, pa, parc)) != 0){

        for(v = G.V-1; v != G.V-2; v = pa[v]){
            edge = parc[v];
            edge->cr -= path_flow;
            edge->twin->cr += path_flow;
        }

        capacity += path_flow;
    }

}

int main(){

    readInput();
    EdmondsKarp();

    printf("%d\n",capacity);
    return 0;
}