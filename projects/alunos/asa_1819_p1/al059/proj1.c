#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

#define max(A, B) A > B ? A : B
#define min(A, B) A < B ? A : B

enum {
    TRUE = 1,
    FALSE = 0
};

typedef char bool_t;

/* =============================================================================
 * Graph
 * =============================================================================
 */

typedef struct AdjNode {
    unsigned long vertex;
    struct AdjNode *next;
} AdjNode;

typedef struct Graph {
    unsigned long numVertices;
    unsigned long articulationPoints;
    AdjNode **adjLists;
} Graph;

AdjNode* createAdjNode(unsigned long n) {

    AdjNode* newNode = (AdjNode*) can_fail_malloc(sizeof(AdjNode));

    newNode->vertex = n;
    newNode->next = NULL;

    return newNode;
}

Graph* createGraph(unsigned long n) {

    Graph *graph = (Graph*) can_fail_malloc(sizeof(Graph));
    unsigned long i;

    graph->numVertices = n;
    graph->adjLists = (AdjNode**) can_fail_malloc(sizeof(AdjNode*) * n);
    graph->articulationPoints = 0;

    for (i = 0; i < n; i++)
        graph->adjLists[i] = NULL;

    return graph;
}

Graph* addEdge(Graph* graph, unsigned long v1, unsigned long v2) {

    AdjNode* newNode1 = createAdjNode(v1);
    AdjNode* newNode2 = createAdjNode(v2);
    AdjNode* current;

    /* Adds edge to first vertex */
    current = graph->adjLists[v1 - 1];
    if (current != NULL) {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode2;
    }
    else {
        graph->adjLists[v1 - 1] = newNode2;
    }

    /* Adds edge to second vertex */
    current = graph->adjLists[v2 - 1];
    if (current != NULL) {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode1;
    }
    else {
        graph->adjLists[v2 - 1] = newNode1;
    }

    return graph;
}

void freeList(AdjNode *head) {

    AdjNode *current;

    if (head != NULL)
        while (head->next != NULL) {
            current = head->next;
            head->next = current->next;
            free(current);
        }

    free(head);
}

void freeGraph(Graph *graph) {

    unsigned long i, n = graph->numVertices;

    for (i = 0; i < n; i++)
        freeList(graph->adjLists[i]);

    free(graph->adjLists);

    free(graph);
}

/* =============================================================================
 * DFS
 * Ignores articulation points and returns size of biggest sub-network
 * =============================================================================
 */

unsigned long DFS_visit(Graph *graph, unsigned long vertex, bool_t visited[], bool_t ap[]) {

    AdjNode *current;
    unsigned long netSize = 0;

    visited[vertex - 1] = TRUE;

    /*Visits all adjacent unvisited nodes*/
    for (current = graph->adjLists[vertex - 1]; current != NULL; current = current->next) {
        if (visited[current->vertex - 1] == FALSE && ap[current->vertex - 1] == FALSE)
            netSize += DFS_visit(graph, current->vertex, visited, ap);
    }

    return netSize + 1;
}

unsigned long DFS(Graph *graph, bool_t visited[], bool_t ap[]) {

    unsigned long i, n = graph->numVertices, netSize = 0, maxNetSize = 0;

    /*Reset all vertices to unvisited*/
    for (i = 0; i < n; i++)
        visited[i] = FALSE;

    /*Visits all unvisited adjacent nodes*/
    for (i = 0; i < n; i++)
        if (visited[i] == FALSE && ap[i] == FALSE) {
            netSize = DFS_visit(graph, i + 1, visited, ap);
            maxNetSize = max(netSize, maxNetSize);
        }

    return maxNetSize;
}

/* =============================================================================
 * Tarjan
 * Counts articulation points, sub-netowrks and each sub-network's maximum index
 * =============================================================================
 */

unsigned long tarjanVisit(Graph *graph, unsigned long vertex, unsigned long *d,
                    unsigned long *low, unsigned long *parent, bool_t visited[],
                    bool_t ap[]) {

    AdjNode *current;
    static unsigned long time;
    unsigned long children = 0, currentIndex = 0, maxIndex = vertex;

    visited[vertex - 1] = TRUE;
    d[vertex - 1] = ++time;
    low[vertex - 1] = d[vertex - 1];

    /*Visits all unvisited adjacent nodes*/
    for (current = graph->adjLists[vertex - 1]; current != NULL; current = current->next) {
        if (visited[current->vertex - 1] == FALSE) {
            children++;
            parent[current->vertex - 1] = vertex;

            currentIndex = tarjanVisit(graph, current->vertex, d, low, parent, visited, ap);
            maxIndex = max(maxIndex, currentIndex);

            /*Updates node's low value*/
            low[vertex - 1] = min(low[vertex - 1], low[current->vertex - 1]);

            /*Checks if node is articulation point*/
            if ((parent[vertex - 1] == 0 && children > 1) ||
                (parent[vertex - 1] != 0 && low[current->vertex - 1] >= d[vertex - 1])) {
                if (ap[vertex - 1] == FALSE) {
                    graph->articulationPoints++;
                    ap[vertex - 1] = TRUE;
                }
            }

        /*Updates node's low value*/
        } else if (current->vertex != parent[vertex - 1])
            low[vertex - 1] = min(low[vertex - 1], d[current->vertex - 1]);
    }

    return maxIndex;
}

unsigned long tarjan(Graph *graph, bool_t maxIndexes[], unsigned long *d,
                unsigned long *low, unsigned long *parent, bool_t visited[],
                bool_t ap[]) {

    unsigned long i, maxIndex, n = graph->numVertices, subNetCount = 0;

    /*Resets all nodes and max indexes*/
    for (i = 0; i < n; i++) {
        visited[i] = FALSE;
        parent[i] = 0;
        ap[i] = FALSE;
        maxIndexes[i] = FALSE;
    }

    /*Visits all unvisited nodes*/
    for (i = 0; i < n; i++)
        if (visited[i] == FALSE) {
            maxIndex = tarjanVisit(graph, i + 1, d, low, parent, visited, ap);
            maxIndexes[maxIndex - 1] = TRUE;
            subNetCount++;
        }

    return subNetCount;
}

/* =============================================================================
 * Main
 * =============================================================================
 */

int main() {

    Graph* graph;
    unsigned long n, e;
    unsigned long v1, v2;
    unsigned long i, j;
    unsigned long subNetworks;

    /* Gets number of vertices and edges from stdin */
    scanf("%lu\n%lu", &n, &e);

    /* Sets up graph */
    unsigned long *d = (unsigned long *) can_fail_malloc(sizeof(unsigned long) * n);
    unsigned long *low = (unsigned long *) can_fail_malloc(sizeof(unsigned long) * n);
    unsigned long *parent = (unsigned long *) can_fail_malloc(sizeof(unsigned long) * n);
    bool_t maxIndexes[n];
    bool_t visited[n];
    bool_t ap[n];

    graph = createGraph(n);
    for (i = 0; i < e; i++) {
        scanf("\n%lu %lu", &v1, &v2);
        addEdge(graph, v1, v2);
    }

    subNetworks = tarjan(graph, maxIndexes, d, low, parent, visited, ap);

    printf("%lu\n", subNetworks);
    for (i = 0; i < n; i++)
        if (maxIndexes[i] == TRUE) {
            printf("%lu", i + 1);
            break;
        }
    for (j = i + 1; j < n; j++)
        if (maxIndexes[j] == TRUE)
            printf(" %lu", j + 1);
    printf("\n%lu\n%lu\n", graph->articulationPoints, DFS(graph, visited, ap));

    free(d);
    free(low);
    free(parent);
    freeGraph(graph);

    return 0;
}
