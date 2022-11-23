#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

int custoMinimo;

#define NOT_VISITED 0
#define VISITED 1
#define RED 2
#define BLUE 3

typedef struct node{
    int vertice;
    struct node* prev;
    struct node* next;
}*Node;

typedef struct queue{
    Node head;
    Node tail;
}*Queue;

typedef struct edge{
    int capacidade;
    int max;
}*Edge;

typedef struct graph{
    int numVertices;
    int* color;
    int* previous;
    Edge *edges;
}*Graph;

int min(int a, int b);
Graph createGraph(int num);
void initializeEdges(Graph graph, int index);
void addEdge(Graph graph, int custoX, int custoY, int processo);
void addCom(Graph graph, int ver1, int ver2, int custo);
void ED(Graph graph, int source, int sink);
int isReachable(Graph graph, int source, int sink);
Node createNode(int v);
Queue initQueue();
Queue pushQueue(Queue queue, int v);
Queue popQueue(Queue queue);
void paint(Graph graph, int source, int sink, int color1, int color2);

int main(){
    int i, v1, v2, processos, nCom, custoX, custoY, somaX=0, somaY=0;
    if (scanf("%d %d", &processos, &nCom) <= 0)
        return -1;
    Graph graph = createGraph(processos);
    for (i=1;i<=processos;i++){
        if (scanf("%d %d", &custoX, &custoY) <= 0)
            return -1;
        addEdge(graph, custoX, custoY, i);
        somaX+=custoX;
        somaY+=custoY;
    }
    custoMinimo = min(somaY, somaX);
    for(i=1;i<=nCom;i++){
        if (scanf("%d %d %d",&v1, &v2, &custoX) <= 0)
            return -1;
        addCom(graph,v1,v2,custoX);
    }
    ED(graph, 0, graph->numVertices-1);
    paint(graph, 0, graph->numVertices-1, RED, BLUE);
    paint(graph, graph->numVertices-1, 0, BLUE, RED);
    printf("%d\n", custoMinimo);
    return 0;
}

int min(int a, int b){
    return a<b ? a:b;
}

Graph createGraph(int num){
    int i;
    Graph graph = can_fail_malloc(sizeof(struct graph));
    graph->numVertices = num + 2;
    graph->color = can_fail_malloc(sizeof(int)*(num+2));
    graph->color[0] = RED;
    graph->color[num+1] = BLUE;
    graph->previous = can_fail_malloc(sizeof(int)*(num+2));
    graph->edges = can_fail_malloc(sizeof(Edge)*(num+2));
    for(i=0;i<=num+1;i++){ 
        graph->edges[i] = can_fail_malloc(sizeof(struct edge)*(num+2));
        initializeEdges(graph, i);
    }
    return graph;
}

void initializeEdges(Graph graph, int index){
    int i;
    for(i=0;i<graph->numVertices;i++){
        graph->edges[index][i].max=0;
        graph->edges[index][i].capacidade=0;
    }
}

void addEdge(Graph graph, int custoX, int custoY, int processo){
    graph->edges[processo][0].max=custoX;
    graph->edges[0][processo].max=custoX;
    graph->edges[processo][graph->numVertices-1].max=custoY;
    graph->edges[graph->numVertices-1][processo].max=custoY;
}

void addCom(Graph graph, int ver1, int ver2, int custo){
    graph->edges[ver1][ver2].max=custo;
    graph->edges[ver2][ver1].max=custo;
}

void ED(Graph graph, int source, int sink){

    int u, v;

    while (isReachable(graph, source, sink)) {

        int minFlow = INT_MAX;
        for (v = sink; v != source; v = graph->previous[v]) {
            u = graph->previous[v];
            minFlow = min(minFlow, graph->edges[u][v].max - graph->edges[u][v].capacidade);
        }
 

        for (v = sink; v != source; v = graph->previous[v]) {
            u = graph->previous[v];
            graph->edges[u][v].capacidade += minFlow;
            graph->edges[v][u].capacidade += minFlow;
        }
    }
}

int isReachable(Graph graph, int source, int sink){

    int i, history[graph->numVertices];
    for (i=0;i<graph->numVertices;i++)
        history[i]=NOT_VISITED;
 
    Queue queue = initQueue();

    queue = pushQueue(queue, source);
    history[source] = VISITED;
    graph->previous[source] = -1;
 
    while (queue->head) {
        int s = queue->tail->vertice;
        queue = popQueue(queue);
        for (i = 0; i < graph->numVertices; i++) {
            if (history[i] == NOT_VISITED && (graph->edges[s][i].max - graph->edges[s][i].capacidade) > 0) {

                if (i == sink) {
                    graph->previous[i] = s;
                    return 1;
                }
                queue = pushQueue(queue, i);
                graph->previous[i] = s;
                history[i] = VISITED;
            }
        }
    }
 
    return 0;
}

void paint(Graph graph, int source, int sink, int color1, int color2){

    int i, j, custo=0, history[graph->numVertices];
    for (i=0;i<graph->numVertices;i++){
        graph->color[i]=color2;
        history[i]=NOT_VISITED;
    }
 
    Queue queue = initQueue();

    queue = pushQueue(queue, source);
    history[source] = VISITED;
    graph->color[source] = color1;
 
    while (queue->head != NULL) {
        int s = queue->tail->vertice;
        queue = popQueue(queue);
        for (i = 0; i < graph->numVertices; i++) {
            if ((i!=sink) && history[i] == NOT_VISITED && (graph->edges[s][i].max - graph->edges[s][i].capacidade) > 0) {

                queue = pushQueue(queue, i);
                graph->color[i] = color1;
                history[i] = VISITED;

            }
        }
    }

    for(i=0;i<graph->numVertices;i++){
        for(j=i;j<graph->numVertices;j++){
            if (graph->color[i]!=graph->color[j] && (graph->edges[i][j].max == graph->edges[i][j].capacidade))
                custo+=graph->edges[i][j].max;
        }
    }
    
    custoMinimo=min(custoMinimo,custo);
}

Queue initQueue(){
    Queue q;
    q = can_fail_malloc(sizeof(struct queue));
    q->head=NULL;
    q->tail=NULL;
    return q;
}

Node createNode(int v){
    Node newNode = can_fail_malloc(sizeof(struct node));
    newNode->vertice = v;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

Queue pushQueue(Queue queue, int v){
    Node newNode = createNode(v);
    if (queue->head){
        newNode->next = queue->head;
        queue->head->prev=newNode;
        queue->head=newNode;
        return queue;
    }
    queue->head=newNode;
    queue->tail=newNode;
    return queue;
}

Queue popQueue(Queue queue){
    if (!queue->head)
        return NULL;
    if (queue->tail->prev){
        queue->tail=queue->tail->prev;
        queue->tail->next=NULL;
        free(queue->tail->next);
        return queue;
    }
    free(queue->tail);
    queue->head=NULL;
    queue->tail=NULL;
    return queue;    
}
