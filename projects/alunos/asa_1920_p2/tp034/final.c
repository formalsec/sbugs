#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>


/*
------------------------------------------------------------
                           STRUCTS
------------------------------------------------------------
*/
/*
Struct of a edge.
    res: oposite edge or "residual" edge (actually holds the edge flow);
    dest: destiny vertex of the edge;
    ccap: current capacity or [total capacity - flow] (actually is the value of the residual edge);
    cap: capacity of the edge (can't be changed!)
*/
typedef struct Edge {
    struct Edge* res;
    int dest;
    int ccap;
    int cap;
}edge;

/*Struct of a node*/
typedef struct Node {
    edge* edge;
    struct Node* next;
}node;

/*Struct of a simple linked list*/
typedef struct List{
    node* head;
}list;

/*Struct of a adjency list*/
typedef struct AdjList {
    int n;
    list* lists;
}adjList;

/*Struct of the graph*/
typedef struct Graph{
    int nClients;
    int nSupers;
    int nVertices;
    int nEdges;
    int m;
    int n;
    adjList* adjList;
}graph;

/*Used to pass data to FFdfs*/
typedef struct Dfsdata{
    adjList* adjList;
    int vertex;
    int flow;
    int* visited;
    int time;
}dfsData;

/*
------------------------------------------------------------
                            EDGE
------------------------------------------------------------
*/
/*
Creates a edge.
    dest: is the destiny of the edge;
    cap: total capacity of said edge
*/
edge* createEdge(int dest, int cap){
    edge* newEdge = (edge*)can_fail_malloc(sizeof(edge));
    newEdge->dest = dest;
    newEdge->cap = cap;
    newEdge->ccap = cap;

    return newEdge;
}


/*
------------------------------------------------------------
                        ADJANCY LIST
------------------------------------------------------------
*/
/*
Creates a new node, used to represent a edge.
    dest: is the destination vertex;
    cap: is the capacity of the edge from origin to destination, where the origin is the index of the list where this node is found
*/
node* createNode(int dest, int cap){
    node* newNode = (node*)can_fail_malloc(sizeof(node));
    edge* newEdge = createEdge(dest, cap);
    newNode->edge = newEdge;
    newNode->next = NULL;
    return newNode;
}

/*
Creates and allocates memory for a adjency list.
    n: is the number os vertices
*/
adjList* createAdjList(int n){
    int i;
    adjList* newAdjList = (adjList*)can_fail_malloc(sizeof(adjList));
    newAdjList->n = n;
    newAdjList->lists = (list*)can_fail_malloc(sizeof(list) * n);

    for(i = 0; i < n; i++){
        newAdjList->lists[i].head = NULL;
    }

    return newAdjList;
}

/*
Adds a edge to the AdjList.
    AdjList: is a pointer to AdjList to add the edge;
    origin: is the vertex where the path starts;
    dest: is the vertex where the path ends;
    cap: is the capacity of the edge
*/
edge* addEdge(adjList* adjList, int origin, int dest, int cap){
    node* newNode = createNode(dest, cap);
    newNode->next = adjList->lists[origin].head;
    adjList->lists[origin].head = newNode;

    return newNode->edge;
}

/*
**DEBUG FUNCTION**
Prints the adjList
*/
void printAdjList(adjList* adjList){
    int v;

    for(v=0; v < adjList->n; v++){
        node* nodep = adjList->lists[v].head;
        while(nodep){
            printf("  > [edge: (%d->%d) | capacity: %d/%d c: %d]\n", v, nodep->edge->dest, nodep->edge->res->ccap, nodep->edge->cap, nodep->edge->ccap);
            nodep = nodep->next;
        }
        printf("\n");
    }
}
/*
**END OF DEBUG FUNCTION**
*/


/*
------------------------------------------------------------
                            GRAPH
------------------------------------------------------------
*/
/*
Creates a new graph, used to store the adjency list of the graph and other information.
    f: is the number of clients                                                  |   > 0
    e: is the number of supermarkets                                             |   >= 0
    m: is the number of collumns                                                 |   > 0
    n: is the number of rows                                                     |   > 0
-----------------------------------------------------------------------------------------------------------------------------------
    nVertices: is the number of vertices in the adjList. It's the collumns (m) times the rows (n);
        It's also added a new vertex to be a general and the only source of the graph (1) and one to be the destination (1);
        Which totals to (m * n) + 2
    nEdges: is the number of edges in the adjList. It's given by (2mn - m - n);
        for each client there's a new edge to connect to the general source (f);
        for each supermarket ithere's a new edge to connect to the general sink (e);
        Making a total of 2*m*n - m - n + f + e
    adjList: is the adjency list of the graph, contains edges and capacity
*/
graph* createGraph(int f, int e, int m, int n){
    graph* newGraph = (graph*)can_fail_malloc(sizeof(graph));

    newGraph->nClients = f;
    newGraph->nSupers = e;
    newGraph->nVertices = (m * n) + 2;
    newGraph->nEdges = (2*m*n) - m - n + f + e;

    return newGraph;
}


/*
------------------------------------------------------------
                         PARSE INPUT
------------------------------------------------------------
*/
/*
Takes the input and parses it into the graph structure.
    graph: is the graph structure chosen to hold the input given
*/
graph* parseInput(){
    int m, n, c, su, i, e, s, x, y;
    graph* graph;
    adjList* adjList;
    edge* e1;
    edge* e2;

    /*Takes m and n*/
    scanf("%d %d", &m, &n);

    /*Takes su and c*/
    scanf("%d %d", &su, &c);

    graph = createGraph(c, su, m, n);

    adjList = createAdjList(graph->nVertices);

    for(i=1; i<graph->nVertices - 1; i++){
        e = i + 1;
        s = i + m;

        if(i % m){
            e1 = addEdge(adjList, i, e, 1);
            e2 = addEdge(adjList, e, i, 1);
            e1->res = e2;
            e2->res = e1;
        }
        if(s < graph->nVertices - 1){
            e1 = addEdge(adjList, i, s, 1);
            e2 = addEdge(adjList, s, i, 1);
            e1->res = e2;
            e2->res = e1;
        }
    }

    for(i=0; i<su; i++){
        scanf("%d %d", &x, &y);
        e1 = addEdge(adjList, x + ((y - 1) * m), graph->nVertices - 1, 1);
        e2 = addEdge(adjList, graph->nVertices - 1, x + ((y - 1) * m), 0);
        e1->res = e2;
        e2->res = e1;
    }

    for(i=0; i<c; i++){
        scanf("%d %d", &x, &y);
        e1 = addEdge(adjList, 0, x + ((y - 1) * m), 1);
        e2 = addEdge(adjList, x + ((y - 1) * m), 0, 0);
        e1->res = e2;
        e2->res = e1;
    }

    graph->adjList = adjList;

    return graph;
}


/*
------------------------------------------------------------
                  FORD-FULKERSON ALGORITHM
------------------------------------------------------------
*/

/*
DFS modified to serve the Ford-Fulkerson algorith.
    Data: is a struct that contains information needed (adjency list, current vertex, current flow, array of visited vertecies this time, time)
*/
int dfsFF(dfsData* data, int sink){
    adjList* adjList = data->adjList;
    int vertex = data->vertex;
    int flow = data->flow;
    int* visited = data->visited;
    int time = data->time;
    int dfsFlow = 0;
    node* nodep = adjList->lists[vertex].head;

    if(vertex == sink){
        return flow; /*Case where the vertex is the sink*/
    }

    visited[vertex] = time;

    while(nodep){
        edge* edgep = nodep->edge;
        edge* resEdgep = edgep->res;

        if((visited[edgep->dest] != time) && (edgep->ccap > 0) && (visited[edgep->dest] != -1)){
            if(edgep->ccap < flow){
                data->flow = edgep->ccap;

            }
            data->vertex = edgep->dest;
            dfsFlow = dfsFF(data, sink);
            if((dfsFlow > 0)){
                edgep->ccap -= dfsFlow; /*ccap is actually the current capacity left of the edge*/
                resEdgep->ccap += dfsFlow; /*ccap is actually the current capacity of the resEdge left (the original capacity of the edge is going to be edge.ccap[actual residual of edge] + resEdge.ccap[actual flow of edge])*/

                return dfsFlow;
            }
        }
        nodep = nodep->next;
    }
    return 0;
}

/*
Main function of the Ford-Fulkerson algorith.
    graph: is the pointer of the graph to run the algorithm on
*/
void fordFulkerson(graph* graph){
    dfsData* data = (dfsData*)can_fail_malloc(sizeof(dfsData));
    int flow = 0, maxFlow = 0, time = 1; /*time is used to keep the number of times the algorithm is looped*/
    int visited[graph->nVertices];
    data->adjList = graph->adjList;
    data->visited = visited;
    do{
        data->vertex = 0;
        data->flow = INT_MAX;
        data->time = time;
        flow = dfsFF(data, graph->nVertices - 1);
        maxFlow += flow;
        time++;
    }
    while(flow != 0);

    printf("%d\n", maxFlow);
}

int main(){
    graph* graph;

    graph = parseInput();

    fordFulkerson(graph);

    return 0;
}
