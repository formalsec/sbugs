#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define min(x, y) (x < y ? x : y)

int numSuppliers, numStations, numConnections;

typedef struct edge
{
    int source, destination;
    int flowForward, capacityForward;
    int flowBackward, capacityBackward;
    struct edge *nextSrc, *nextDst;
} * edge_t;

typedef struct vertex
{
    int height, excess;
    bool visited;
    edge_t srcEdgeList;
    edge_t dstEdgeList;
    struct vertex *next;
} * vertex_t;

/*<<<<<<<>>>>>>>>
  < GLOBAL VARS >
  <<<<<<<>>>>>>>>*/

vertex_t *graph = NULL;

vertex_t verticesQueueFront = NULL;
vertex_t verticesQueueRear = NULL;

void *can_fail_mallocAndVerify(size_t size)
{
    void *x = can_fail_malloc(size);

    if (x == NULL)
    {
        printf("Error in can_fail_malloc, exiting...\n");
        exit(EXIT_FAILURE);
    }
    return x;
}

void scanfAndVerify(int *number)
{
    int error = scanf("%d", number);

    if (error < 0)
    {
        printf("Error in scanf, exiting...\n");
        exit(EXIT_FAILURE);
    }
}

void pushQueue(vertex_t v)
{
    if (verticesQueueRear == NULL)
    {
        verticesQueueFront = verticesQueueRear = v;
    }
    else
    {
        verticesQueueRear->next = v;
        verticesQueueRear = v;
    }
}

void popQueue()
{
    if (verticesQueueFront != NULL)
    {
        vertex_t x = verticesQueueFront;
        verticesQueueFront = verticesQueueFront->next;
        x->next = NULL;

        if (verticesQueueFront == NULL)
            verticesQueueRear = NULL;
    }
}

vertex_t newVertex()
{
    vertex_t vertex = can_fail_mallocAndVerify(sizeof(struct vertex));

    vertex->height = 0;
    vertex->excess = 0;
    vertex->srcEdgeList = NULL;
    vertex->dstEdgeList = NULL;
    vertex->next = NULL;
    vertex->visited = false;
    return vertex;
}

edge_t newEdge(int src, int dest, int flowForward, int capForward, int flowBackward, int capBackward)
{
    edge_t x = can_fail_mallocAndVerify(sizeof(struct edge));

    x->source = src;
    x->destination = dest;

    x->flowForward = flowForward;
    x->capacityForward = capForward;

    x->flowBackward = flowBackward;
    x->capacityBackward = capBackward;
    x->nextSrc = NULL;
    x->nextDst = NULL;

    return x;
}

/*Add vertex to sorted list*/
void addToSrcList(edge_t *head, int src, int dest, int flowForward, int capForward, int flowBackward, int capBackward)
{
    edge_t x = newEdge(src, dest, flowForward, capForward, flowBackward, capBackward);
    int d = x->destination;

    if (*head == NULL)
    {
        x->nextSrc = *head;
        *head = x;
        (*head)->nextDst = NULL;
    }
    else
    {
        if (d < (*head)->destination)
        {
            x->nextSrc = *head;
            *head = x;
        }
        else
        {
            edge_t tmp = *head;
            while (tmp->nextSrc != NULL && tmp->nextSrc->destination < x->destination)
                tmp = tmp->nextSrc;

            x->nextSrc = tmp->nextSrc;
            tmp->nextSrc = x;
        }
    }
}

void addToDstList(edge_t *head, edge_t x, int destination)
{
    edge_t tmp;

    for (tmp = x; tmp != NULL; tmp = tmp->nextSrc)
    {
        if (tmp->destination == destination)
        {
            tmp->nextDst = *head;
            (*head) = tmp;
            break;
        }
    }
}

void Preflow()
{
    int i = 0, j = 0, srcTmp = 0, destTmp = 0, pathCapTmp = 0;
    int capacityTmp = 0, total = 0;
    scanfAndVerify(&numSuppliers);
    scanfAndVerify(&numStations);
    scanfAndVerify(&numConnections);

    total = numSuppliers + numStations * 2 + 2;

    graph = can_fail_mallocAndVerify(sizeof(vertex_t) * total);

    graph[0] = newVertex(); /* Source */
    graph[0]->height = total;

    graph[1] = newVertex(); /* Supermarket*/

    for (i = 2; i < (numSuppliers + 2); i++) /* Suppliers */
    {
        graph[i] = newVertex();

        scanfAndVerify(&capacityTmp);

        graph[i]->excess = capacityTmp;
        graph[0]->excess -= capacityTmp;
        addToSrcList(&graph[0]->srcEdgeList, 0, i, capacityTmp, capacityTmp, -capacityTmp, 0);
        addToDstList(&graph[i]->dstEdgeList, graph[0]->srcEdgeList, i);
        pushQueue(graph[i]);
    }

    for (j = i; j < (numSuppliers + numStations + 2); j++) /* Stations */
    {
        graph[j] = newVertex();
        graph[j + numStations] = newVertex();

        scanfAndVerify(&capacityTmp);
        addToSrcList(&graph[j]->srcEdgeList, j, j + numStations, 0, capacityTmp, 0, 0);
        addToDstList(&graph[j + numStations]->dstEdgeList, graph[j]->srcEdgeList, j + numStations);
    }

    for (i = 1; i <= numConnections; i++) /*Connections*/
    {
        scanfAndVerify(&srcTmp);
        scanfAndVerify(&destTmp);
        scanfAndVerify(&pathCapTmp);

        if (srcTmp > numSuppliers + 1) /*Source is station */
        {
            addToSrcList(&graph[srcTmp + numStations]->srcEdgeList, srcTmp + numStations, destTmp, 0, pathCapTmp, 0, 0);
            addToDstList(&graph[destTmp]->dstEdgeList, graph[srcTmp + numStations]->srcEdgeList, destTmp);
        }

        else /*Source is others*/
        {
            addToSrcList(&graph[srcTmp]->srcEdgeList, srcTmp, destTmp, 0, pathCapTmp, 0, 0);
            addToDstList(&graph[destTmp]->dstEdgeList, graph[srcTmp]->srcEdgeList, destTmp);
        }
    }
}

void Push(vertex_t u, vertex_t v, bool uIsSource)
{
    edge_t uv;
    int add = 0, oldexcess = v->excess;

    if (uIsSource)
        for (uv = u->srcEdgeList; uv != NULL; uv = uv->nextSrc)
        {
            if ((v->srcEdgeList != NULL && uv->destination == v->srcEdgeList->source) ||
                uv->destination == v->dstEdgeList->destination)              /*checks if uv edge destination == v*/
            {                                                                /*uv edge exists and uv = uv edge*/
                add = min(u->excess, uv->capacityForward - uv->flowForward); /*vu edge exists and vu = vu edge*/
                uv->flowForward += add;
                uv->flowBackward = -uv->flowForward;
                break;
            }
        }
    else
        for (uv = u->dstEdgeList; uv != NULL; uv = uv->nextDst)
        {
            if (uv->source == v->srcEdgeList->source)                          /*checks if uv edge destination == v*/
            {                                                                  /*uv edge exists and uv = uv edge*/
                add = min(u->excess, uv->capacityBackward - uv->flowBackward); /*vu edge exists and vu = vu edge*/
                uv->flowBackward += add;
                uv->flowForward = -uv->flowBackward;
                break;
            }
        }

    u->excess -= add;
    v->excess += add;

    if ((v->srcEdgeList != NULL && oldexcess == 0 && v->srcEdgeList->source != 1 && v->srcEdgeList->source != 0) ||
        (v->dstEdgeList != NULL && oldexcess == 0 && v->dstEdgeList->destination != 1 && v->dstEdgeList->destination != 0))
        pushQueue(v);
}

void Relabel(vertex_t u)
{
    int minHeight = -1;
    edge_t edge;

    for (edge = u->srcEdgeList; edge != NULL; edge = edge->nextSrc)
    {
        if (graph[edge->destination]->height >= u->height && edge->capacityForward - edge->flowForward > 0)
        {
            if (minHeight == -1)
                minHeight = graph[edge->destination]->height;
            else
                minHeight = min(graph[edge->destination]->height, minHeight);
        }
    }

    for (edge = u->dstEdgeList; edge != NULL; edge = edge->nextDst)
    {
        if (graph[edge->source]->height >= u->height && edge->capacityBackward - edge->flowBackward > 0)
        {
            if (minHeight == -1)
                minHeight = graph[edge->source]->height;
            else
                minHeight = min(graph[edge->source]->height, minHeight);
        }
    }
    if (minHeight != -1)
        u->height = 1 + minHeight;
}

void Discharge(vertex_t u)
{
    edge_t edgeToNeighborSrc = u->srcEdgeList; /*edge to first neighbor*/
    edge_t edgeToNeighborDst = u->dstEdgeList; /*edge to first neighbor*/
    vertex_t v1 = NULL, v2 = NULL;

    while (u->excess > 0)
    {

        if (edgeToNeighborSrc == NULL && edgeToNeighborDst == NULL)
        {
            Relabel(u);
            edgeToNeighborSrc = u->srcEdgeList; /*edge to first neighbor*/
            edgeToNeighborDst = u->dstEdgeList; /*edge to first neighbor*/
        }
        else
        {
            if (edgeToNeighborSrc != NULL)
                v1 = graph[edgeToNeighborSrc->destination]; /*neighbor*/
            if (edgeToNeighborDst != NULL)
                v2 = graph[edgeToNeighborDst->source]; /*neighbor*/

            if (edgeToNeighborSrc != NULL && edgeToNeighborSrc->capacityForward - edgeToNeighborSrc->flowForward > 0 &&
                u->height == (v1->height + 1))
                Push(u, v1, true);

            else if (edgeToNeighborDst != NULL && edgeToNeighborDst->capacityBackward - edgeToNeighborDst->flowBackward > 0 &&
                     u->height == (v2->height + 1))
                Push(u, v2, false);

            else
            {
                if (edgeToNeighborDst != NULL)
                    edgeToNeighborDst = edgeToNeighborDst->nextDst; /*edge to next neighbor*/
                if (edgeToNeighborSrc != NULL)
                    edgeToNeighborSrc = edgeToNeighborSrc->nextSrc; /*edge to next neighbor*/
            }
        }
    }
}
void DFSVisit(vertex_t u)
{
    edge_t edge;
    u->visited = true;
    for (edge = u->srcEdgeList; edge != NULL; edge = edge->nextSrc)
    {
        if (!graph[edge->destination]->visited &&
            edge->capacityBackward - edge->flowBackward != 0)
            DFSVisit(graph[edge->destination]);
    }
    for (edge = u->dstEdgeList; edge != NULL; edge = edge->nextDst)
    {
        if (!graph[edge->source]->visited &&
            edge->capacityForward - edge->flowForward != 0)
            DFSVisit(graph[edge->source]);
    }
}

void minimumCut()
{
    int i;
    edge_t edge;
    bool firstChar = true;

    printf("%d\n", graph[1]->excess);

    for (i = numSuppliers + 2; i < numSuppliers + 2 + numStations; i++)
    {
        for (edge = graph[i]->srcEdgeList; edge != NULL; edge = edge->nextSrc)
        {
            if (((graph[edge->source]->visited && !graph[edge->destination]->visited) ||
                 (!graph[edge->source]->visited && graph[edge->destination]->visited)) &&
                edge->source < edge->destination && edge->source + numStations == edge->destination)
            {
                if (firstChar)
                {
                    printf("%d", edge->source);
                    firstChar = false;
                }
                else
                    printf(" %d", edge->source);
            }
        }
    }
    printf("\n");
    for (i = 0; i < numSuppliers + 2; i++)
    {
        for (edge = graph[i]->srcEdgeList; edge != NULL; edge = edge->nextSrc)
        {
            if (((graph[edge->source]->visited && !graph[edge->destination]->visited) ||
                 (!graph[edge->source]->visited && graph[edge->destination]->visited)) &&
                edge->source != 0 && edge->destination != 0)
                printf("%d %d\n", edge->source, edge->destination);
        }
    }

    for (i = numSuppliers + 2 + numStations; i < numSuppliers + numStations * 2 + 2; i++)
    {
        for (edge = graph[i]->srcEdgeList; edge != NULL; edge = edge->nextSrc)
        {
            if (((graph[edge->source]->visited && !graph[edge->destination]->visited) ||
                 (!graph[edge->source]->visited && graph[edge->destination]->visited)) &&
                edge->source != 0 && edge->destination != 0 && edge->capacityForward - edge->flowForward == 0)
                printf("%d %d\n", edge->source - numStations, edge->destination);
        }
    }
}

void PushRelabel()
{
    Preflow();
    while (verticesQueueFront != NULL)
    {
        Discharge(verticesQueueFront);
        popQueue();
    }
}

int main()
{
    PushRelabel();
    DFSVisit(graph[1]);
    minimumCut();
    return EXIT_SUCCESS;
}