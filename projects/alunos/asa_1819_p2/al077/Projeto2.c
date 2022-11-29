#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INITIAL_SIZE 20
#define NIL -1;

typedef struct vector {
    int* capacity;
    int* destination;
    int elems;
    int size;
} Vector;

typedef struct normalVector {
    int* data;
    int elems;
    int size;
}   NormalVector;

typedef struct edge {
    int source;
    int destination;
} Edge;

typedef struct edgeVector {
    Edge* minCut;
    int elems;
    int size;
} EdgeVector;


typedef struct graph {
    int vertexes;
    Vector* origin;
} Graph;

typedef struct node {
    int data;
    int priority;
    struct node* next;
} QueueNode;

void graphInit (Graph* g, int v);
void addConnectionToGraph(Graph* g, int o, int d, int c);
void vectorInit(Vector* v);
void vectorPushback(Vector* v, int d, int c);
int queueGetValue(QueueNode** head);
void queuePop(QueueNode** head);
QueueNode* newQueueNode(int d, int p);
void queuePush(QueueNode**head, int d, int p);
bool bfs(Graph* g, int s, int d, int* parents);
int searchConnectionGraph(Graph* g, int u, int v);
int edmondsKarp(Graph* g, int s, int d);
void findExpandingPoints(Graph* g, int supCount, int staCount);
void getMinCut(Graph* g, int s, int d, bool* visited);
void normalVectorInit(NormalVector* v);
void normalVectorPushback(NormalVector* v, int d);
void edgeVectorInit(EdgeVector* v);
void edgeVectorPushback(EdgeVector* v, int s, int d);
void insertionSort(EdgeVector* minCut, int n);
void freeVector(Vector* head);
void freeEdgeVector(EdgeVector* v);
void freeGraph(Graph* g);
void freeNormalVector(NormalVector* v);



int main() {

    int supplierCount, stationCount, connectionCount, i, origin, destination, c, j, maxFlow, vertexCount;
    Graph* g = (Graph*)can_fail_malloc(sizeof(Graph));
    Graph* gRes = (Graph*)can_fail_malloc(sizeof(Graph));
    if(scanf("%d %d %d", &supplierCount, &stationCount, &connectionCount)<0)
        perror("erro no scanf\n");
    vertexCount = 2+supplierCount+2*stationCount;

    graphInit(g,vertexCount);
    graphInit(gRes, vertexCount);

    for (i=0; i<supplierCount; i++) {
        if(scanf("%d", &c) < 0)
            perror("erro no scanf\n");
        addConnectionToGraph(g, 0, i+2, c);
        addConnectionToGraph(gRes, 0, i+2, c);
        addConnectionToGraph(gRes, i+2, 0, 0);
    }

    for (i=0; i<stationCount; i++) {
        if(scanf("%d", &c) < 0)
            perror("erro no scanf\n");
        addConnectionToGraph(g,i+supplierCount+2,i+supplierCount+2+stationCount,c);
        addConnectionToGraph(gRes,i+supplierCount+2,i+supplierCount+2+stationCount,c);
        addConnectionToGraph(gRes,i+supplierCount+2+stationCount,i+supplierCount+2,0);
    }
    
    for(i=0; i<connectionCount; i++) {
        if(scanf("%d %d %d", &origin, &destination, &c) < 0)
            perror("erro no scanf\n");
        if(origin >= supplierCount+2) {
            origin += stationCount;
        }
        addConnectionToGraph(g,origin,destination,c);
        addConnectionToGraph(gRes,origin,destination,c);
        addConnectionToGraph(gRes,destination,origin,0);
    }

    maxFlow = edmondsKarp(gRes,0,1);
    printf("%d\n",maxFlow);

    bool* visited = (bool*)can_fail_malloc(sizeof(bool)*vertexCount);

    Graph* gT = (Graph*)can_fail_malloc(sizeof(Graph));
    graphInit(gT,vertexCount);

    for (i=0;i<vertexCount;i++) {
        for (j=0;j<gRes->origin[i].elems;j++) {
            addConnectionToGraph(gT,gRes->origin[i].destination[j],i,gRes->origin[i].capacity[j]);
        }
    }
    getMinCut(gT,1,0,visited);

    NormalVector expandingStations;
    normalVectorInit(&expandingStations);
    EdgeVector cut; 
    edgeVectorInit(&cut);


    for(i=0;i<vertexCount;i++) {
        for(j=0;j<g->origin[i].elems;j++) {
            if(visited[g->origin[i].destination[j]] && !visited[i]) {
                if(i >= supplierCount+2 && (g->origin[i].destination[j] == i+stationCount))
                    normalVectorPushback(&expandingStations,i);

                else if(i) {
                    if(i>=supplierCount+2)
                        edgeVectorPushback(&cut,i-stationCount,g->origin[i].destination[j]);
                    else    
                        edgeVectorPushback(&cut,i,g->origin[i].destination[j]);
                }
            }
        }
    }

    if (expandingStations.elems > 0) {
        for(i=0;i<expandingStations.elems-1;i++) {
            printf("%d ",expandingStations.data[i]);
        }
        printf("%d\n",expandingStations.data[i]);
    }
    else printf("\n");
    insertionSort(&cut, cut.elems);
    for (i=0;i<cut.elems;i++) {
        printf("%d %d\n",cut.minCut[i].source, cut.minCut[i].destination);
    }

    free(visited);
    freeGraph(g);
    freeGraph(gRes);
    freeGraph(gT);
    freeEdgeVector(&cut);
    freeNormalVector(&expandingStations);

    
    return 0;
}


void insertionSort(EdgeVector* minCut, int n) { 
    int i, j;
    Edge key;

    for (i = 1; i < n; i++) { 
        key = minCut->minCut[i]; 
        j = i - 1; 
  
        /* Move elements of arr[0..i-1], that are 
          greater than key, to one position ahead 
          of their current position */
        while (j >= 0 && minCut->minCut[j].destination > key.destination && minCut->minCut[j].source == key.source) { 
            minCut->minCut[j + 1] = minCut->minCut[j]; 
            j--; 
        } 
        minCut->minCut[j + 1] = key; 
    } 
} 


int edmondsKarp(Graph* g, int s, int d) {
    int *parents= (int*)can_fail_malloc(sizeof(int)*g->vertexes);
    int u, v, i, maxFlow=0;
    while(bfs(g,s,d,parents)) {
        int pFlow = __INT_MAX__;
        for(v=d;v!=s;v=parents[v]) {
            u = parents[v];
            i = searchConnectionGraph(g,u,v);
            pFlow = pFlow < g->origin[u].capacity[i] ? pFlow : g->origin[u].capacity[i];
        }
        for(v=d; v!=s; v=parents[v]) {
            u = parents[v];
            i = searchConnectionGraph(g,u,v);
            g->origin[u].capacity[i] -= pFlow;
            i = searchConnectionGraph(g,v,u);
            g->origin[v].capacity[i] += pFlow;
        }
        maxFlow += pFlow;
    }
    free(parents);
    return maxFlow;
}

bool bfs(Graph* g, int s, int d, int* parents) {
    int p=0, i;
    QueueNode* head = newQueueNode(s,p);
    parents[s] = NIL;
    bool result;
    bool* visited = (bool*)can_fail_malloc(sizeof(bool)*g->vertexes);
    memset(visited, 0, sizeof(bool)*g->vertexes);
    visited[s] = true;
    while(head != NULL) {
        int var = queueGetValue(&head);
        queuePop(&head);
        p++;
        for(i=0; i<g->origin[var].elems; i++) {
            if(!visited[g->origin[var].destination[i]] &&  g->origin[var].capacity[i] > 0) {

                queuePush(&head, g->origin[var].destination[i],p);
                parents[g->origin[var].destination[i]] = var;
                visited[g->origin[var].destination[i]] = true;
            }
        }
    }
    result = visited[d];
    free(visited);
    return result == true;

}

void getMinCut(Graph* g, int s, int d, bool* visited) {
    int p=0, i;
    QueueNode* head = newQueueNode(s,p);
    memset(visited, 0,sizeof(bool)*g->vertexes);
    visited[s] = true;
    while(head != NULL) {
        int var = queueGetValue(&head);
        queuePop(&head);
        p++;
        for(i=0; i<g->origin[var].elems; i++) {
            if(!visited[g->origin[var].destination[i]] &&  g->origin[var].capacity[i] > 0) {
                queuePush(&head, g->origin[var].destination[i],p);
                visited[g->origin[var].destination[i]] = true;
            }
        }
    }
}


int searchConnectionGraph(Graph* g, int u, int v) {
    int i;
    for (i=0; i<g->origin[u].elems; i++) {
        if (g->origin[u].destination[i] == v) {
            return i;
        }
    }
    return 0;
}

void graphInit (Graph* g, int v) {
    g->vertexes = v;
    g->origin = (Vector*)can_fail_malloc(sizeof(Vector)*v);
    int i;
    for (i=0; i<v; i++) {
        vectorInit(&g->origin[i]);
    }
}

void addConnectionToGraph(Graph* g, int o, int d, int c) {
    vectorPushback(&g->origin[o], d, c);
}

void edgeVectorInit(EdgeVector* v) {
    v->elems = 0;
    v->size = INITIAL_SIZE;
    v->minCut = (Edge*)can_fail_malloc(sizeof(Edge)*INITIAL_SIZE);
}

void edgeVectorPushback(EdgeVector* v, int s, int d) {
    if (v->elems == v->size) {
        v->size *= 2;
        v->minCut = can_fail_realloc(v->minCut, sizeof(Edge)*v->size);
    }
    Edge newEdge;
    newEdge.source = s;
    newEdge.destination = d;
    v->minCut[v->elems++] = newEdge;
}

void normalVectorInit(NormalVector* v) {
    v->elems = 0;
    v->size = INITIAL_SIZE;
    v->data = (int*)can_fail_malloc(sizeof(int)*INITIAL_SIZE);
}

void normalVectorPushback(NormalVector* v, int d) {
    if (v->elems == v->size) {
        v->size *= 2;
        v->data = can_fail_realloc(v->data, sizeof(int)*v->size);
    }
    v->data[v->elems++] = d;
}


void vectorInit(Vector* v) {
    v->elems = 0;
    v->size = INITIAL_SIZE;
    v->capacity = (int*)can_fail_malloc(sizeof(int)*INITIAL_SIZE);
    v->destination = (int*)can_fail_malloc(sizeof(int)*INITIAL_SIZE);
}

void vectorPushback(Vector* v, int d, int c) {
    if (v->elems == v->size) {
        v->size *= 2;
        v->capacity = can_fail_realloc(v->capacity, sizeof(int)*v->size);
        v->destination = can_fail_realloc(v->destination, sizeof(int)*v->size);    
    }
    v->destination[v->elems] = d;
    v->capacity[v->elems++] = c;
}

QueueNode* newQueueNode(int d, int p) {
    QueueNode* n = (QueueNode*)can_fail_malloc(sizeof(QueueNode));
    n->data = d;
    n->priority = p;
    n->next = NULL;
    return n;
} 

void queuePop(QueueNode** head) {
    QueueNode* n = *head;
    (*head) = (*head)->next;
    free(n);
}

int queueGetValue(QueueNode** head) {
    return (*head)->data;
}

void queuePush(QueueNode** head, int d, int p) {
    QueueNode* n = newQueueNode(d,p);
    QueueNode* i = (*head);
    
    if((*head)==NULL) {
        (*head) = n;
    }

    else if((*head)->priority > p) {
        n->next = (*head);
        (*head) = n; 
    }
    else {
        while(i->next != NULL && i->priority < p) {
            i = i->next;
        }
        n->next = i->next;
        i->next = n;
    }
}

void freeVector(Vector* v) {
    free(v->capacity);
    free(v->destination);
}

void freeGraph(Graph* g) {
    int i;
    for(i=0;i<g->vertexes;i++)
        freeVector(&g->origin[i]);
    free(g->origin);
    free(g);
}

void freeEdgeVector(EdgeVector* v) {
    free(v->minCut);
}

void freeNormalVector(NormalVector* v) {
    free(v->data);
}
