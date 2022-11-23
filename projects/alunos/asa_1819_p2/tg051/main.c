#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
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
    int nProviders;
    int nStations;
    int nVertices;
    int nEdges;
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

/*Pair struct. Used only to sort*/
typedef struct Pair{
    int o;
    int d;
}pair;


/*
------------------------------------------------------------
                            EDGE
------------------------------------------------------------
*/
/*
Creates a edge.
    dest: is the desteny of the edge;
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
    f: is the number of providers                                                |   > 0
    e: is the number of stations                                                 |   >= 0
    t: is the number of paths (directed edges)                                   |   >= 0
-----------------------------------------------------------------------------------------------------------------------------------
    nVertices: is the number of vertices in the adjList. It's the providers (f), the stations (e) and the hiper (1);
        Since the capacity of each stations is converted in a new edge and vertex it's added one more per station (e);
        And it's added a new vertex to be a general and the only source of the graph (1);
        Which totals to f + e + 1 + e + 1 (f + 2e + 2)
    nEdges: is the number of edges in the adjList. It's the total given in the input (t);
        for each provider there's a new edge to connect to the general source (f);
        for each station is added two new edges, but it's removed one. (2e-1e);
        Making a total of t + f + 2e - 1e (t + f + e)
    adjList: is the adjency list of the graph, contains edges and capacity
*/
graph* createGraph(int f, int e, int t){
    graph* newGraph = (graph*)can_fail_malloc(sizeof(graph));

    newGraph->nProviders = f;
    newGraph->nStations = e;
    newGraph->nVertices = f + (2 * e) + 2;
    newGraph->nEdges = t + f + e;

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
    int f, e, t, i, k, o, d, el;
    graph* graph;
    adjList* adjList;
    edge* e1;
    edge* e2;

    /*Takes f, e and t*/
    scanf("%d %d %d", &f, &e, &t);

    graph = createGraph(f, e, t);
    f++; /*Last id of providers*/
    el = f+e; /*Last id of station*/

    adjList = createAdjList(graph->nVertices);

    /*Parses all the production values of each provider*/
    for(i = 2;i<=f;i++){
        scanf("%d", &k);
        e1 = addEdge(adjList, 0, i, k); /*0 represents the general source, {i} is one of the providers and {k} is the capacity of said provider, which ends up being translated in the capacity of a edge from the general source*/
        e2 = addEdge(adjList, i, 0, 0); /*Creates the back edge*/
        e1->res = e2;
        e2->res = e1; /*Easy acess to the edge oposite edge*/
    }
    /*Parses all the capacity values of each station*/
    for(i = ++f;i<=el;i++){

        scanf("%d", &k);
        e1 = addEdge(adjList, i, i+e, k); /*Adds new edge from the station {i} to a new vertex {i+e} (+e so it doesn't use an allready given id) with the capacity of the station*/
        e2 = addEdge(adjList, i+e, i, 0); /*Adds a back edge*/
        e1->res = e2;
        e2->res = e1;
    }
    /*Reads all the edges and capacity to add it to the adjency list*/
    for(i = 0;i<t;i++){
        scanf("%d %d %d", &o, &d, &k);
        if(o >= f){
            e1 = addEdge(adjList, o+e, d, k); /*In the case of it being a station the edge instead of coming from the station itself comes from i+e, the "sub-edge" created to have in account the station capacity*/
            e2 = addEdge(adjList, d, o+e, 0);
            e1->res = e2;
            e2->res = e1;
        }
        else{
            e1 = addEdge(adjList, o, d, k);
            e2 = addEdge(adjList, d, o, 0);
            e1->res = e2;
            e2->res = e1;
        }
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
DFS to find the mincut of the graph.
    list: is the adjency list;
    source: is the current vertex;
    visited: is a array that holds 0 and 1 to represent which side of the cut the vertex ends (0 - source side; 1 - sink side)
*/
void minCutDFS(adjList* list, int source, int* visited) {
    if(source == 0){
        return;
    }

    visited[source] = 1;

    node* nodep = list->lists[source].head;
    while(nodep){
        if((nodep->edge->res->ccap) && !visited[nodep->edge->dest]){
            minCutDFS(list, nodep->edge->dest, visited);
        }
        nodep = nodep->next;
    }
}

/*
DFS modified to serve the Ford-Fulkerson algorith.
    Data: is a truct that contains information needed (adjency list, current vertex, current flow, array of visited vertecies this time, time)
*/
int dfsFF(dfsData* data){
    adjList* adjList = data->adjList;
    int vertex = data->vertex;
    int flow = data->flow;
    int* visited = data->visited;
    int time = data->time;
    int dfsFlow = 0;
    node* nodep = adjList->lists[vertex].head;

    if(vertex == 1){
        return flow; /*Case where the vertex is the sink*/
    }

    visited[vertex] = time;

    while(nodep){
        edge* edgep = nodep->edge;
        edge* resEdgep = edgep->res;

        if((visited[edgep->dest] != time) && (edgep->ccap > 0)){
            if(edgep->ccap < flow){
                data->flow = edgep->ccap;

            }
            data->vertex = edgep->dest;
            dfsFlow = dfsFF(data);
            if(dfsFlow > 0){
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
int* fordFulkerson(graph* graph){
    dfsData* data = (dfsData*)can_fail_malloc(sizeof(dfsData));
    int flow = 0, maxFlow = 0, time = 1; /*time is used to keep the number of times the algorithm is looped*/
    int visited[graph->nVertices];
    int* minCut = (int*)can_fail_calloc(graph->nVertices,sizeof(int));
    data->adjList = graph->adjList;
    data->visited = visited;
    do{
        data->vertex = 0;
        data->flow = INT_MAX;
        data->time = time;
        flow = dfsFF(data);
        maxFlow += flow;
        time++;
    }
    while(flow != 0);

    minCutDFS(graph->adjList, 1, minCut);

    printf("%d\n", maxFlow);

    return minCut;
}


/*
------------------------------------------------------------
                            EDGE
------------------------------------------------------------
*/
/*
Used for qsort().
*/
int cmpint(const void* a, const void* b) {
    return ( *(int*)a - *(int*)b );
}

/*
Orders the pairs in terms of origin first (o), and destiny secound (d).
*/
void pairInsertSort(pair* edges, int n) {
    int i, j;
    pair key;
    for(i = 1; i < n; i++){
        key = edges[i];
        j = i - 1;
        while(j >= 0 && edges[j].d > key.d){
            edges[j + 1] = edges[j];
            j = j - 1;
        }
        edges[j + 1] = key;
    }
    for(i = 1; i < n; i++){
        key = edges[i];
        j = i - 1;
        while(j >= 0 && edges[j].o > key.o){
            edges[j + 1] = edges[j];
            j = j - 1;
        }
        edges[j + 1] = key;
    }
}

int main(){
    int i, stationStart, si=0, se=0;
    int* stationBN;
    pair* edgeBN;
    adjList* adjList;
    graph* graph;
    int* minCut;

    graph = parseInput();
    minCut = fordFulkerson(graph);

    /*printAll(graph, minCut);*/

    adjList = graph->adjList;
    stationStart = (graph->nProviders + graph->nStations + 1);
    stationBN = (int*)can_fail_calloc(graph->nStations, sizeof(int));
    edgeBN = (pair*)can_fail_calloc(graph->nEdges, sizeof(pair));

    for(i = 1; i < adjList->n; i++){
        node* nodep = adjList->lists[i].head;
        while(nodep){
            edge* edge = nodep->edge;
            if((minCut[i] != minCut[edge->dest]) && (edge->cap)){
                if(edge->dest > stationStart){
                    stationBN[si++] = (edge->dest - graph->nStations);
                }
                else{
                    edgeBN[se].o = i;
                    edgeBN[se++].d = edge->dest;
                }
            }
            nodep = nodep->next;
        }
    }

    qsort(stationBN, si, sizeof(int), cmpint);
    pairInsertSort(edgeBN, se);

    for(i=0;i<si;i++){
        if(i){
            printf(" ");
        }
        printf("%d", stationBN[i]);
    }
    printf("\n");
    for(i=0;i<se;i++){
        if(edgeBN[i].o > stationStart){
            printf("%d ", edgeBN[i].o - graph->nStations);
        }
        else{
            printf("%d ", edgeBN[i].o);
        }
        printf("%d\n", edgeBN[i].d);
    }
    return 0;
}
