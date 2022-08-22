#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Struct of a node in the adjency list*/
typedef struct Node {
    long unsigned int id;
    struct Node* next;
}node;

/*Struct that points to the first node of an adjency list*/
typedef struct List{
    node* head;
}list;

/*Struct for the graph composed by adjency lists*/
typedef struct Graph {
    long unsigned int n;
    list* lists;
}graph;

/*
Creates a new node, used to represent a vertex.
    id is the id of the vertex
*/
node* createNode(long unsigned int id){
    node* newNode = (node*)malloc(sizeof(node*));
    newNode->id = id;
    newNode->next = NULL;
    return newNode;
}

/*
Creates and allocates memory for a graph.
    n is the number os vertices
*/
graph* createGraph(long unsigned int n){
    long unsigned int i;
    n++;
    graph* newGraph = (graph*)malloc(sizeof(graph));
    newGraph->n = n;
    newGraph->lists = (list*)malloc(sizeof(list) * (n+1));

    for(i = 1; i <= n; i++){
        newGraph->lists[i].head = NULL;
    }

    return newGraph;
}

/*
Adds a edge to the graph.
    graph is a pointer to graph to add the edge
    v1 is the first vertex of the edge
    v2 is the second vertex of the edge
*/
void addEdge(graph* graph, long unsigned int v1, long unsigned int v2){
    /*Makes edge from v1 to v2*/
    node* newNode = createNode(v2);
    newNode->next = graph->lists[v1].head;
    graph->lists[v1].head = newNode;

    /*Makes edge from v2 to v1*/
    newNode = createNode(v1);
    newNode->next = graph->lists[v2].head;
    graph->lists[v2].head = newNode;
}

/*
**DEBUG FUNCTION**
Prints the graph
*/
void printGraph(graph* graph){
    long unsigned int v;

    for(v=1; v <= graph->n; v++){
        node* nodep = graph->lists[v].head;
        printf("Vertex %lu\n head", v);
        while(nodep){
            printf(" > %lu", nodep->id);
            nodep = nodep->next;
        }
        printf("\n\n");
    }
}
/*
**END OF DEBUG FUNCTION**
*/

void removeArticulationPoints(graph* routers, long unsigned int articulations[], long unsigned int nArticulations){
    long unsigned int v, i;

    for(i=0; i < nArticulations; i++){
        routers->lists[articulations[i]].head = NULL;
    }

    for(v=1; v <= routers->n; v++){
        node* prevNode = NULL;
        node* nodep = routers->lists[v].head;
        while(nodep){
            for (i=0; i < nArticulations; i++){
                if(articulations[i] == nodep->id){
                    if(!prevNode){
                        routers->lists[v].head = nodep->next;
                    }
                    else{
                        prevNode->next = nodep->next;
                    }
                }
            }
            prevNode = nodep;
            nodep = nodep->next;
        }
    }

}

void biggestSubNetLoop(graph* routers, long unsigned int id, long unsigned int* size, int visited[]){
    node* nodep = routers->lists[id].head;
    long unsigned int nid;

    visited[id] = 1;

    while(nodep){
        nid = nodep->id;
        if(!visited[nid]){
            biggestSubNetLoop(routers, nid, size, visited);
        }

        nodep = nodep->next;
    }
    (*size)++;
}

void biggestSubNet(graph* routers){
    long unsigned int i, maxSize = 0, size, n = routers->n;
    int visited[n+1];

    memset(visited, 0, sizeof(visited));

    for(i=1;i<=n;i++){
        if(!visited[i]){
            size = 0;
            biggestSubNetLoop(routers, i, &size, visited);

            if(size > maxSize){
                maxSize = size;
            }
        }
    }
    printf("%lu\n", maxSize);
}

long unsigned int min(long unsigned int a, long unsigned int b){
    if(a < b){
        return a;
    }
    return b;
}

int compare( const void* a, const void* b){
     return ( *(int*)a - *(int*)b );
}

void dfsLoop(graph* routers, long unsigned int id, long unsigned int time, int visited[], long unsigned int depth[], long unsigned int low[], long unsigned int parent[], long unsigned int articulations[], long unsigned int* nArticulations, long unsigned int* subredeId){
    long unsigned int nid = 0;
    long unsigned int childs = 0;
    int isArticulation = 0;
    node* nodep = routers->lists[id].head;

    visited[id] = 1;
    depth[id] = time;
    low[id] = time;
    if(id > *subredeId){
        *subredeId = id;
    }

    while(nodep){
        nid = nodep->id;
        if(!visited[nid]){
            parent[nid] = id;
            dfsLoop(routers, nid, time + 1, visited, depth, low, parent, articulations, nArticulations, subredeId);
            childs++;
            if(low[nid] >= depth[id]){
                isArticulation = 1;
            }
            low[id] = min(low[id], low[nid]);
        }
        else if (nid != parent[id]){
            low[id] = min(low[id], depth[nid]);
        }

        nodep = nodep->next;
    }

    if((parent[id] != 0 && isArticulation) || (parent[id] == 0 && childs > 1)){
        articulations[(*nArticulations)++] = id;
    }
}

void dfs(graph* routers, long unsigned int n){
    int i, nSubRedes = 0;
    int visited[n+1];
    long unsigned int nArticulations = 0, subredeId;
    long unsigned int depth[n+1];
    long unsigned int low[n+1];
    long unsigned int parent[n+1];
    long unsigned int articulations[n];
    long unsigned int subRedes[n];

    memset(articulations, 0, sizeof(articulations));
    memset(visited, 0, sizeof(visited));
    memset(parent, 0, sizeof(parent));
    memset(subRedes, 0, sizeof(subRedes));

    for(i=1;i<=n;i++){
        if(!visited[i]){
            subredeId = 0;
            dfsLoop(routers, i, 0, visited, depth, low, parent, articulations, &nArticulations, &subredeId);
            subRedes[nSubRedes++] = subredeId;
        }
    }

    printf("%d\n", nSubRedes);
    qsort(subRedes, nSubRedes, sizeof(long unsigned int), compare);
    for(i=0;i<nSubRedes;i++){
        printf("%lu", subRedes[i]);
        if(i+1 < nSubRedes){
            printf(" ");
        }
    }
    printf("\n%lu\n", nArticulations);

    removeArticulationPoints(routers, articulations, nArticulations);
    biggestSubNet(routers);
}


/*
Reads from input all the router links (edges) and "draws" them on the graph.
    routers is the graph to be populated
    m is the number of links (edges)
*/
void parseInput(graph* routers,long unsigned int m){
    long unsigned int i, r1, r2;

    for(i=0; i<m; i++){
        if(scanf("%lu %lu", &r1, &r2));
        addEdge(routers, r1, r2);
    }
}

int main (int argc, char** argv){
    /*
    n is number of vertices and m is number of edges (defined on the project paper)
    routers is the graph of all the routers (vertices) and their connections (edges)
    */
    long unsigned int n;
    long unsigned int m;
    graph* routers;

    /*Reads number of vertices and number of edges*/
    if(scanf("%lu\n%lu", &n, &m));

    /*Creates router graph and populates with given links (edges)*/
    routers = createGraph(n);
    parseInput(routers, m);

    dfs(routers, n);

    return 0;
}
