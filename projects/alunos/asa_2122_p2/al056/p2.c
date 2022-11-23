#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define ERROR 1

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define RED 2

#define QUEUE_IS_EMPTY -1
#define QUEUE_IS_NOT_EMPTY 0

typedef struct queue_el
{
    int id;
    struct queue_el *next;
} QueueEl;

typedef struct queue
{
    QueueEl *first;
    QueueEl *last;
} Queue;

typedef struct associationNode
{
    int id;
    struct associationNode *nextNode;
} AssociationNode;

typedef struct Basenode
{
    int color;
    int colorPredecessor;
    int count;
    int inDegree;
    AssociationNode *firstNode;
    AssociationNode *lastNode;
} BaseNode;

typedef struct graph
{
    int dim;
    BaseNode *nodes;
} Graph;

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
        return QUEUE_IS_NOT_EMPTY; /*queue esta vazia*/
    el = q->first;
    if (!q->first->next)
    { /*e o unico elemento da queue*/
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
        (b + i)->color = WHITE;
        (b + i)->colorPredecessor = WHITE;
        (b + i)->count = 0;
        (b + i)->inDegree = 0;
        (b + i)->firstNode = NULL;
        (b + i)->lastNode = NULL;
    }
    return g;
}

void freeGraph(Graph *g)
{
    int i;
    BaseNode *b;
    AssociationNode *a1, *a2;
    for (i = 0; i < g->dim; i++)
    {
        b = g->nodes + i;
        a1 = b->firstNode;
        while (a1)
        {
            a2 = a1->nextNode;
            free(a1);
            a1 = a2;
        }
    }
    free(g->nodes);
    free(g);
}

void newNode(Graph *g, int from, int to)
{
    BaseNode *b1 = g->nodes + from;
    BaseNode *b2 = g->nodes + to - 1;
    AssociationNode *a = can_fail_malloc(sizeof(AssociationNode));
    a->id = to;
    a->nextNode = NULL;
    b2->inDegree = b2->inDegree + 1;
    if (b1->firstNode == NULL)
    {
        b1->firstNode = a;
    }
    else
    {
        b1->lastNode->nextNode = a;
    }
    b1->lastNode = a;
}

int isGraphAcyclic(Graph *g)
{
    int i, actual_node, visited_nodes = 0;
    BaseNode *b = g->nodes;
    AssociationNode *a;
    Queue *q = newQueue();
    for (i = 0; i < g->dim; i++)
    {
        if ((b + i)->inDegree == 0)
        {
            enQueue(q, i + 1);
        }
    }

    while (isQueueEmpty(q) != QUEUE_IS_EMPTY)
    {
        actual_node = deQueue(q);
        visited_nodes = visited_nodes + 1;
        a = (b + actual_node - 1)->firstNode;
        while (a != NULL)
        {
            (b + a->id - 1)->inDegree = (b + a->id - 1)->inDegree - 1;
            if ((b + a->id - 1)->inDegree == 0)
            {
                enQueue(q, a->id);
            }
            a = a->nextNode;
        }
    }

    freeQueue(q);
    if (visited_nodes == g->dim)
    {
        return TRUE;
    }

    return FALSE;
}

void bfs(Graph *g, int root)
{
    int actual_node;
    BaseNode *b = g->nodes;
    AssociationNode *a;
    Queue *q = newQueue();
    enQueue(q, root);
    (b + root - 1)->color = GRAY;
    (b + root - 1)->colorPredecessor = (b + root - 1)->colorPredecessor + 1;

    while (isQueueEmpty(q) != QUEUE_IS_EMPTY)
    {
        actual_node = deQueue(q);
        (b + actual_node - 1)->color = BLACK;
        a = (b + actual_node - 1)->firstNode;
        while (a != NULL)
        {
            if ((b + a->id - 1)->color == WHITE)
            {
                enQueue(q, a->id);
                (b + a->id - 1)->color = GRAY;
                (b + a->id - 1)->colorPredecessor = (b + a->id - 1)->colorPredecessor + 1;
            }
            a = a->nextNode;
        }
    }
    freeQueue(q);
}

void lca(Graph *g, int v1, int v2)
{
    int i, nodes_in_common = 0, len_str = 1;
    char *string = (char *)can_fail_malloc(len_str);
    BaseNode *b = g->nodes;
    AssociationNode *a;

    memset(string, '\0', len_str);

    bfs(g, v1);
    for (i = 0; i < g->dim; i++)
    {
        (b + i)->color = WHITE;
    }

    bfs(g, v2);
    for (i = 0; i < g->dim; i++)
    {
        if ((b + i)->colorPredecessor == RED)
        {
            a = (b + i)->firstNode;
            while (a != NULL)
            {
                (b + a->id - 1)->count = (b + a->id - 1)->count + 1;
                a = a->nextNode;
            }
        }
    }

    for (i = 0; i < g->dim; i++)
    {
        if ((b + i)->colorPredecessor == RED)
        {
            if ((b + i)->count == 0)
            {
                nodes_in_common = nodes_in_common + 1;
                len_str = len_str + log10(i + 1) + 3;
                string = (char *)can_fail_realloc(string, len_str);
                char *aux = (char *)can_fail_malloc(log10(i + 1) + 3);
                sprintf(aux, "%d ", i + 1);
                strcat(string, aux);
                free(aux);
            }
        }
    }

    if (nodes_in_common != 0)
    {
        printf("%s\n", string);
    }
    else
    {
        printf("-\n");
    }

    free(string);
}


int main()
{
    int i, v1, v2, num_persons, num_associations, tmp1, tmp2, graphic_is_acyclic;
    if (scanf("%d %d", &v1, &v2))
    {
        if (scanf("%d %d", &num_persons, &num_associations))
        {
            Graph *g = newGraph(num_persons);
            for (i = 0; i < num_associations; i++)
            {
                if (scanf("%d %d", &tmp1, &tmp2))
                {
                    newNode(g, tmp2 - 1, tmp1);
                }
            }

            graphic_is_acyclic = isGraphAcyclic(g);

            if (graphic_is_acyclic == TRUE)
            {
                lca(g, v1, v2);
            }
            else
            {
                printf("0\n");
            }

            freeGraph(g);
        }
    }
    return SUCCESS;
}