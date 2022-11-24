#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


typedef struct Vertex {
    int id;
    int flow;
    bool visited;
    struct Vertex*next;
} Vertex;


typedef struct Queue {
    int id;
    struct Queue* next;
} Queue;

typedef struct Graph {
    int numVertices;
    int numAvenues;
    Vertex** adjLists;
} Graph;

bool* added;
int* parents;
int head, tail;
int* q;
int* visited;

Graph* createGraph(int numVertices);
void addEdge(Graph* graph, int src, int dest);

Graph* processInput() {
    int* super;
    int* homes;
    char line[20];
    int numAvenues = 0, numStreets = 0, numSuperMarkets = 0, numPeople = 0;
    int numVertices = 0;
    int avenue = 0;
    int street = 0;
    int i = 0;

    fgets(line, sizeof(line)/sizeof(char), stdin);
    numAvenues = atoi(strtok(line, " "));
    numStreets = atoi(strtok(NULL, " "));
    numVertices = numAvenues*numStreets;


    fgets(line, sizeof(line)/sizeof(char), stdin);
    numSuperMarkets = atoi(strtok(line, " "));
    numPeople = atoi(strtok(NULL, " "));

    Graph* graph = createGraph(numVertices);
    
    graph->numVertices = numVertices;
    graph->numAvenues = numAvenues;
    homes = (int*)can_fail_malloc((numPeople+1)*sizeof(int));
    super = (int*)can_fail_malloc((numSuperMarkets+1)*sizeof(int));

    for(i = 1; i <= numSuperMarkets; i++) {
        fgets(line, sizeof(line)/sizeof(char), stdin);
        avenue = atoi(strtok(line, " "));
        street = atoi(strtok(NULL, " "));
        super[i] = avenue + (street - 1)*numAvenues;
        addEdge(graph, super[i]*2, graph->numVertices*2 + 1);
    }

    for(i = 1; i <= numPeople; i++) {
        fgets(line, sizeof(line)/sizeof(char), stdin);
        avenue = atoi(strtok(line, " "));
        street = atoi(strtok(NULL, " "));
        homes[i] = avenue + (street - 1)*numAvenues; 
        addEdge(graph, 0, (homes[i])*2-1); 
    }
    
    free(homes);
    free(super);
    return graph;
}


void addEdge(Graph* graph, int src, int dest) {
    Vertex* aux = (Vertex*)can_fail_malloc(sizeof(Vertex));

    aux->flow = 0;
    aux->id = dest;
    aux->visited = false;

    aux->next = graph->adjLists[src];
    graph->adjLists[src] = aux;    
}


Graph* createGraph(int numVertices) {
    int i;
    Graph* graph = can_fail_malloc(sizeof(struct Graph));
    
    parents = (int*)can_fail_malloc((numVertices*2+2)*sizeof(int));
    q = (int*)can_fail_malloc((numVertices*2+4)*sizeof(int));
    visited = (int*)can_fail_malloc((numVertices*2+2)*sizeof(int));
    added = (bool*)can_fail_malloc((numVertices*2+2)*sizeof(bool));

    graph->adjLists = (Vertex**)can_fail_malloc((numVertices*2 + 2)*sizeof(Vertex*));

    for(i = 0; i <= graph->numVertices*2 + 1; i++) {
        graph->adjLists[i] = NULL;
        added[i] = false;
    }
    return graph;
}

int dequeue() {
    int x = q[head];
    head++;
    return x;
}

void enqueue(int x) {
    q[tail] = x;
    tail++;
}

/* PERCEBER O QUE ESTA ERRADO */
int bfs(Graph* graph) {
    int i;

    for(i = 0; i <= graph->numVertices*2 + 1; i++) {
        visited[i] = false;
        parents[i] = -1;
    }

    head = tail = 0;
    visited[0] = true;
    enqueue(0);

    while(head != tail) {
        int u = dequeue();

        if(added[u] == false && u != 0 && u != graph->numVertices*2 + 1) {
            added[u] = true;
            if(u%2 == 1) {
                addEdge(graph, u, u + 1);
            }
            
            if(u%2 == 0) {
                if(u%(graph->numAvenues*2) != 0) {   
                    addEdge(graph, u, u + 1);
                }

                if(u%(graph->numAvenues*2) != 2) {
                    addEdge(graph, u, u - 3);
                }

                if(u + graph->numAvenues*2 <= graph->numVertices*2) {
                    addEdge(graph, u, u + graph->numAvenues*2 - 1);
                }

                if(u - graph->numAvenues*2 > 0) {
                    addEdge(graph, u, u - graph->numAvenues*2 - 1);
                } 
            }
        }
         
        Vertex* v = graph->adjLists[u];

        for(;v != NULL; v = v->next) {
            if(visited[v->id] == false && 1 - v->flow > 0) {
                enqueue(v->id);
                parents[v->id] = u;
                visited[v->id] =true;   
            }  
        }  
    }      
    return visited[graph->numVertices*2 + 1];
}  

int edmondsKarp(Graph* graph) {
    int maxFlow = 0;
    int u;
    while(bfs(graph)) {
        for (u = graph->numVertices*2 + 1; parents[u] >= 0; u = parents[u]) {

            Vertex* temp = graph->adjLists[parents[u]];

            for(; temp != NULL; temp = temp->next) {
                if(temp->id == u) {
                    temp->flow += 1;
                    break;
                }
            }
            
            Vertex* aux = graph->adjLists[u];
            for(; aux != NULL; aux = aux->next) {
                if(aux->id == parents[u]) {
                    aux->flow -= 1;
                    break;              
                }
            }

            addEdge(graph, u, parents[u]);
        }
        maxFlow++;
    }
    return maxFlow; 
}

int main() {
    
    Graph* graph = processInput();
    

    printf("%d\n", edmondsKarp(graph));

    int i;
    for(i = 0; i <= graph->numVertices*2 + 1; i++) {
        Vertex* vertexAux = graph->adjLists[i];
        while(vertexAux != NULL) {
            Vertex* vextexNext = vertexAux->next;
            free(vertexAux);
            vertexAux = vextexNext;
        }
    }
    free(graph->adjLists);
    free(graph);

    return 0;
}
    
    