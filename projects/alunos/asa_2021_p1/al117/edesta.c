#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

#define NOT_VISITED 0
#define VISITED 1

typedef struct node{
    int vertice;
    struct node* next;
}*Edge;

typedef struct stack{
    int vertice;
    struct stack* next;
    struct stack* prev;
}*Stack;

typedef struct graph{
    int numVertices;
    int* lenght;
    int* history;
    Edge* edges;
    int* inEdges;
}*Graph;

Graph createGraph(int num);
void addEdge(Graph graph, int v1, int v2);
Edge createEdge(int vertice);
void DFS(Graph graph);
void explore(Graph graph, int i);
int max(int a, int b);
void deleteGraph(Graph graph);
void deleteEdges(Edge edge);
Edge pop(Edge edge);
Stack createStack(int v);
Stack pushStack(Stack stack, int v);
Stack popStack(Stack stack);

int largestLength=1, inDegreeVertices=0;

int main(){
    int i, v1, v2, dominoes, dependencies;
    if (scanf("%d %d", &dominoes, &dependencies) <= 0)
        return -1;
    Graph DAG = createGraph(dominoes);
    for (i=1; i<=dependencies;i++){
        if (scanf("%d %d", &v1, &v2) <= 0)
            return -1;
        addEdge(DAG, v1, v2);
    }
    DFS(DAG);
    /*deleteGraph(DAG);*/
    return 0;
}

int max(int a, int b){
    return a>b ? a:b;
}

Graph createGraph(int num){
    int i;
    Graph graph = can_fail_malloc(sizeof(struct graph));
    graph->numVertices = num;
    graph->lenght = can_fail_malloc(sizeof(int)*(num+1));
    graph->history = can_fail_malloc(sizeof(int)*(num+1));
    graph->edges = can_fail_malloc(sizeof(Edge)*(num+1));
    graph->inEdges = can_fail_malloc(sizeof(int)*(num+1));
    for(i=1;i<=num;i++){
        graph->history[i]=NOT_VISITED;
        graph->edges[i]=NULL;
        graph->inEdges[i]=0;
        graph->lenght[i]=1;
    }
    return graph;
}

void addEdge(Graph graph, int v1, int v2){
    Edge newEdge=createEdge(v2);
    newEdge->next=graph->edges[v1];
    graph->edges[v1]=newEdge;
    graph->inEdges[v2]++;
}

Edge createEdge(int vert){
    Edge edge = can_fail_malloc(sizeof(struct node));
    edge->vertice=vert;
    edge->next=NULL;
    return edge;
}

void DFS(Graph graph){
    int i;
    for (i=1;i<=graph->numVertices;i++){
        if (!graph->inEdges[i] && graph->history[i]==NOT_VISITED){
            explore(graph, i);
            inDegreeVertices++;
        }
    }
    printf("%d %d\n",inDegreeVertices, largestLength);
}

void explore(Graph graph, int s){
    Stack stack = NULL;

    stack = pushStack(stack, s);
    while(stack){
        s = stack->vertice;
        stack = popStack(stack);
                  
        graph->history[s]=VISITED;
                  
        Edge edge = graph->edges[s];
                  
        for (;edge;edge=edge->next){
            graph->inEdges[edge->vertice]--;
            if(graph->history[edge->vertice]==NOT_VISITED && graph->inEdges[edge->vertice]==0)
                stack = pushStack(stack, edge->vertice);
            graph->lenght[edge->vertice] = max(graph->lenght[edge->vertice], 1 + graph->lenght[s]);
            largestLength = max(largestLength, graph->lenght[edge->vertice]);
        }
                  
    }
}

void deleteGraph(Graph graph){
    int i;
    free(graph->lenght);
    free(graph->history);
    for(i=1; i<=graph->numVertices;i++){
        deleteEdges(graph->edges[i]);
    }
    free(graph->inEdges);
    free(graph->edges);
    free(graph);
}

void deleteEdges(Edge edge){
    while(edge)
        edge=pop(edge);
}

Edge pop(Edge edge){
    Edge nextEdge=edge->next;
    free(edge);
    return nextEdge;
}

Stack createStack(int v){
    Stack newStack = can_fail_malloc(sizeof(struct stack));
    newStack->vertice = v;
    newStack->next = NULL;
    return newStack;
}

Stack pushStack(Stack stack, int v){
    Stack newStack = createStack(v);
    newStack->prev = stack;
    if (stack)
        stack->next = newStack;
    return newStack;
}

Stack popStack(Stack stack){
    Stack previous = stack->prev;
    free(stack);
    if (previous)
        previous->next=NULL;
    return previous;
}