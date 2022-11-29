#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

#define NO_PATH 0
#define PATH 1

#define QUEUE_IS_EMPTY -1
#define QUEUE_IS_NOT_EMPTY 0

typedef struct queue_el{
    int id;
    struct queue_el *next;
}QueueEl;

typedef struct queue{
    QueueEl* first;
    QueueEl* last;
}Queue;

typedef struct destinationNode
{
    int id;
    int from;
    int flow;
    int weight;
    int residualCapacity;
    struct destinationNode *reverseDestinationNode;
    struct destinationNode *nextNode;
} DestinationNode;

typedef struct baseNode
{
    DestinationNode *firstNode;
    DestinationNode *lastNode;
} BaseNode;

typedef struct graph
{
    int dim;
    BaseNode *nodes;
} Graph;

Graph *newGraph(int dim)
{
    int i;
    Graph *g = can_fail_malloc(sizeof(Graph));
    BaseNode *b;
    g->dim = dim;
    g->nodes = can_fail_malloc(g->dim * sizeof(BaseNode));
    b = g->nodes;
    for (i = 0; i < g->dim; i++)
    {
        (b + i)->firstNode = NULL;
        (b + i)->lastNode = NULL;
    }
    return g;
}

void freeGraph(Graph *g){
    int i;
    BaseNode *b;
    DestinationNode *d1, *d2;
    for ( i = 0; i < g->dim; i++)
    {
        b = g->nodes + i;
        d1 = b->firstNode;
        while (d1)
        {
            d2 = d1->nextNode;
            free(d1);
            d1 = d2;
        }
    }
    free(g->nodes);
    free(g);
}

DestinationNode *newNode(Graph *g, int from, int to, int weight)
{
    BaseNode *b = g->nodes + from;
    DestinationNode *d = can_fail_malloc(sizeof(DestinationNode));
    d->id = to;
    d->from = from;
    d->weight = weight;
    d->flow = 0;
    d->residualCapacity = weight;
    d->reverseDestinationNode = NULL;
    d->nextNode = NULL;
    if (b->firstNode == NULL)
    {
        b->firstNode = d;
    }
    else
    {
        b->lastNode->nextNode = d;
    }
    b->lastNode = d;
    return d;
}

void createProcessToProcessor(Graph *g, int id, int cost1, int cost2){
    DestinationNode *tmp1, *tmp2;
    tmp1 = newNode(g, 0, id, cost1);/*s->id*/
    tmp2 = newNode(g, id, 0, 0);/*id->s*/
    tmp1->reverseDestinationNode = tmp2;
    tmp2->reverseDestinationNode = tmp1;
    tmp1 = newNode(g, id, g->dim - 1, cost2);/*id->t*/
    tmp2 = newNode(g, g->dim - 1, id, cost2);/*t->id*/
    tmp1->reverseDestinationNode = tmp2;
    tmp2->reverseDestinationNode = tmp1;
}

void createProcessToProcess(Graph *g, int from, int to, int cost){
    DestinationNode *tmp1, *tmp2;
    tmp1 = newNode(g, from, to, cost);
    tmp2 = newNode(g, to, from, cost);
    tmp1->reverseDestinationNode = tmp2;
    tmp2->reverseDestinationNode = tmp1;
}

QueueEl *newQueueEl(int id)
{
    QueueEl *el = (QueueEl *)can_fail_malloc(sizeof(QueueEl));
    el->id = id;
    el->next = NULL;
    return el;
}

void freeQueueEl(QueueEl *el)
{
    free(el);
}

Queue *newQueue()
{
    Queue *q = (Queue *)can_fail_malloc(sizeof(Queue));
    q->first = NULL;
    q->last = NULL;
    return q;
}

void freeQueue(Queue *q)
{
    QueueEl *aux1, *aux2;
    aux1 = q->first;
    while (aux1)
    {
        aux2 = aux1->next;
        freeQueueEl(aux1);
        aux1 = aux2;
    }
    free(q);
}

int isQueueEmpty(Queue *q)
{
    if (!q->first)
    {
        return QUEUE_IS_EMPTY;
    }
    return QUEUE_IS_NOT_EMPTY;
}

void enQueue(Queue *q, int id)
{
    QueueEl *el = newQueueEl(id);
    if (isQueueEmpty(q))
    {
        /*a queue esta vazia*/
        q->first = el;
    }
    else
    {
        /*a queue nao esta vazia*/
        q->last->next = el;
    }
    q->last = el;
}

int deQueue(Queue *q)
{
    QueueEl *el;
    int id;
    if (isQueueEmpty(q))
        return QUEUE_IS_NOT_EMPTY;/*queue esta vazia*/
    el = q->first;
    if (!q->first->next)
    {/*e o unico elemento da queue*/
        q->first = NULL;
        q->last = NULL;
    }
    else
    {
        q->first = el->next;
    }
    id = el->id;
    freeQueueEl(el);
    return id;
}

void clearQueue(Queue *q){
    QueueEl *aux1, *aux2;
    aux1 = q->first;
    while (aux1)
    {
        aux2 = aux1->next;
        freeQueueEl(aux1);
        aux1 = aux2;
    }
    q->first = NULL;
    q->last = NULL;
}

Queue *q;

int *visited;
int bfs(Graph *g, int from, DestinationNode *path[], int to)
{
    /*variáveis auxiliares*/
    int actual_node, i;
    BaseNode *b;
    DestinationNode* d = NULL;
    /* Inicializa array visitados*/
    for (i = 0; i < g->dim; i++)
        visited[i] = WHITE;

    /*enqueue origem*/
    enQueue(q, from);
    visited[from] = GRAY;
    while (isQueueEmpty(q) == QUEUE_IS_NOT_EMPTY)
    {
        actual_node = deQueue(q);
        visited[actual_node] = BLACK;
        b = g->nodes + actual_node;
        d = b->firstNode;
        while (d)
        {
            if (visited[d->id] == WHITE && d->residualCapacity > 0)
                {
                    enQueue(q, d->id);
                    visited[d->id] = GRAY;
                    path[d->id] = d;
                    if (d->id == g->dim - 1)
                    {
                        clearQueue(q);
                        return PATH;
                    }
                    
                }
            d = d->nextNode;
        }
    }
    return NO_PATH;
}

int incrementFlow(Graph *g, DestinationNode *d, int increment)
{
    d->flow += increment;
    d->residualCapacity = d->weight - d->flow;
    return d->from;
}

int maxFlowPath(Graph *g, DestinationNode *path[]){
    int pathFlow = 0;
    int pos = g->dim - 1;
    DestinationNode *d = path[pos];
    do
    {
        if (pathFlow == 0)
        {
            pathFlow = d->residualCapacity;
        }
        else if (pathFlow > d->residualCapacity)
        {
            pathFlow = d->residualCapacity;
        }
        pos = d->from;
        d = path[pos];
    } while (pos != 0);
    return pathFlow;
}

int maxFlow(Graph *g, DestinationNode *path[])
{
    int pos;
    int flow = 0;
    int pathFlow = 0;
    DestinationNode *d1, *d2;
    /*Enquanto houver um caminho aumentador*/
    while (bfs(g, 0, path, g->dim - 1))
    {  
        pos = g->dim - 1;
        pathFlow = maxFlowPath(g, path);
        flow += pathFlow;
        do
        {
            d1 = path[pos];
            pos = incrementFlow(g, d1, pathFlow);
            d2 = d1->reverseDestinationNode;
            incrementFlow(g, d2, -pathFlow);

        } while (pos != 0);
    }

    /* Não existem mais caminhos aumentadores de fluxo*/
    return flow;
}


int main()
{
    int num_tasks, num_cost_com, tmp1, tmp2, tmp3, i;
    if (scanf("%d %d", &num_tasks, &num_cost_com))
    {
        Graph *g = newGraph(num_tasks + 2);
        visited = (int *)can_fail_malloc(g->dim * sizeof(int));
        DestinationNode *path[g->dim];
        q = newQueue();
        for (i = 0; i < num_tasks; i++)
        {
            if (scanf("%d %d", &tmp1, &tmp2))
            {
                createProcessToProcessor(g, i + 1, tmp1, tmp2);
            }
        }
        for (i = 0; i < num_cost_com; i++)
        {
            if (scanf("%d %d %d", &tmp1, &tmp2, &tmp3))
            {
                createProcessToProcess(g, tmp1, tmp2, tmp3);
            }
        }
        printf("%d\n", maxFlow(g, path));
        free(visited);
        freeQueue(q);
        freeGraph(g);
    }

    return 0;
}