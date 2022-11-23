#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define min(A, B) A < B ? A : B
#define resCap(A) A->capacity - A->flux

enum {
    TRUE = 1,
    FALSE = 0
};

typedef char bool_t;

/* =============================================================================
 * Graph
 * =============================================================================
 */

typedef struct Edge {
    int vertex;
    int capacity;
    int flux;
    struct Edge *next;
    struct Edge *backEdge;
} Edge;

typedef struct Graph {
    int numVertices;
    Edge **adjLists;
} Graph;

Edge* createEdge(int vertex, int capacity) {

    Edge* newEdge = (Edge*) can_fail_malloc(sizeof(Edge));

    newEdge->vertex = vertex;
    newEdge->capacity = capacity;
    newEdge->flux = 0;
    newEdge->next = NULL;

    return newEdge;
}

Graph* createGraph(int size) {

    Graph *graph = (Graph*) can_fail_malloc(sizeof(Graph));

    graph->numVertices = size;
    graph->adjLists = (Edge**) can_fail_malloc(sizeof(Edge*) * size);

    return graph;
}

void addEdge(Graph* graph, int v1, int v2, int capacity2) {

    Edge *ResidualEdge = createEdge(v1, 0);
    Edge *newEdge2 = createEdge(v2, capacity2);
    Edge *current;
    Edge *before;

    /* Sets pointers */
    ResidualEdge->backEdge = newEdge2;
    newEdge2->backEdge = ResidualEdge;

    /* Adds edge to first vertex in order */
    if (graph->adjLists[v1] != NULL) {
        current = graph->adjLists[v1]->next;
        before = graph->adjLists[v1];
        while (current != NULL && current->vertex < newEdge2->vertex) {
            before = current;
            current = current->next;
        }
        newEdge2->next = current;
        before->next = newEdge2;
    } else {
        graph->adjLists[v1] = newEdge2;
    }

    /* Adds Residual Edge in order*/
    if (graph->adjLists[v2] != NULL) {
        current = graph->adjLists[v2]->next;
        before = graph->adjLists[v2];
        while (current != NULL && current->vertex < ResidualEdge->vertex) {
            before = current;
            current = current->next;
        }
        ResidualEdge->next = current;
        before->next = ResidualEdge;
    } else {
        graph->adjLists[v2] = ResidualEdge;
    }

}

void freeList(Edge *node) {

    Edge *current;

    if (node != NULL) {
        while (node->next != NULL) {
            current = node->next;
            node->next = current->next;
            free(current);
        }
        free(node);
    }

}

void freeGraph(Graph *graph) {

    int i, n = graph->numVertices;

    for (i = 0; i < n; i++)
        freeList(graph->adjLists[i]);

    free(graph->adjLists);

    free(graph);

}

/* =============================================================================
 * Queue
 * =============================================================================
 */

typedef struct queueNode {
    int data;
    struct queueNode *next;
} QueueNode;

typedef struct {
    QueueNode *head;
    QueueNode *tail;
} Queue;

Queue *createQueue() {

    Queue *queue = (Queue*) can_fail_malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}

QueueNode *createQueueNode(int data) {

    QueueNode *newNode = (QueueNode*) can_fail_malloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

void queuePop(Queue *queue) {

    /*Removes element from the top of the queue*/
    QueueNode *aux = queue->head;
    queue->head = queue->head->next;
    free(aux);
}

void queueInsert(Queue *queue, int data) {

    /*Inserts element at the end of the queue*/
    if (queue->head == NULL) {
        queue->head = createQueueNode(data);
        queue->tail = queue->head;
    } else {
        queue->tail->next = createQueueNode(data);
        queue->tail = queue->tail->next;
    }
}

void freeQueue(Queue *queue) {

    if (queue->head != NULL) {
        while (queue->head->next != NULL) queuePop(queue);
        free(queue->head);
    }

    free(queue);
}

/* =============================================================================
 * Relabel to front
 * =============================================================================
 */

void push(Edge *u, Edge *v, int excess[]) {

    int diff = min(excess[u->vertex], resCap(v));

    v->flux += diff;
    u->flux = -1 * v->flux;
    excess[u->vertex] -= diff;
    excess[v->vertex] += diff;
}

Edge *relabel(Graph *graph, int u, int height[]) {

    Edge *aux;
    Edge *minNeighbor = NULL;
    int minHeight = INT_MAX;

    for (aux = graph->adjLists[u]; aux != NULL; aux = aux->next) {

        /*Finds minimum height of all neighbors*/
        if (resCap(aux) > 0) {
            int testHeight = height[aux->vertex];

            if (testHeight >= height[u] && testHeight < minHeight) {
                minHeight = testHeight;
                minNeighbor = aux;
            }
        }
    }

    height[u] = minHeight + 1;
    return minNeighbor;
}

void initializePreFlow(Graph *graph, int source, int height[], int excess[]) {

    /*Initiliazes flow on the graph*/
    Edge *aux;

    /*Sets source's height*/
    height[source] = graph->numVertices;

    for (aux = graph->adjLists[source]; aux != NULL; aux = aux->next) {
        /*Updates all of source's neighbors*/
        aux->flux = aux->capacity;
        aux->backEdge->flux = -1 * aux->capacity;
        excess[aux->vertex] = aux->capacity;
        excess[source] -= aux->capacity;
    }
}

void discharge(Graph *graph, Queue *queue, int u, int height[], int excess[]) {

    /*Pushes to all neighbors until there's no excess left*/
    Edge *aux = graph->adjLists[u];
    while (excess[u] > 0) {
        if (aux == NULL) {
            /*If it can´t push to any neighbor, relabels*/
            aux = relabel(graph, u, height);
        } else {
            int resCap = aux->capacity - aux->flux;

            if (resCap > 0 && height[u] == height[aux->vertex] + 1) {
                /*Pushes to neighbor*/
                int oldExcess = excess[aux->vertex];
                push(aux->backEdge, aux, excess);
                if (oldExcess == 0 && aux->vertex > 1)
                    queueInsert(queue, aux->vertex);
            } else {
                aux = aux->next;
            }
        }
    }
}

void relabelToFront(Graph *graph, int source, int f) {

    /*Finds maximum flux through relabel to front algorithm*/
    Queue *queue = createQueue();
    int i, height[graph->numVertices], excess[graph->numVertices];

    /*Initialization*/
    for (i = 0; i < graph->numVertices; i++) {
        height[i] = 0;
        excess[i] = 0;
    }

    initializePreFlow(graph, source, height, excess);
    for (i = 2; i < f + 2; i++) {
        queueInsert(queue, i);
    }

    /*Main loop to discharge all vertices until there's no excess left*/
    while (queue->head != NULL) {
        int u = queue->head->data;
        discharge(graph, queue, u, height, excess);
        queuePop(queue);
    }

    freeQueue(queue);
    printf("%d\n", excess[1]);
}

void printEdges(Graph *graph, bool_t *visited, int e, int f) {

    Edge *aux;
    int i;
    bool_t first = TRUE;

    /* Stations */
    for (i = f + 2; i < f + e + 2; i++) {
        if (!visited[i]) {
            for (aux = graph->adjLists[i]; aux != NULL; aux = aux->next) {
                if (visited[aux->vertex] && aux->capacity > 0) {
                    if (first) {
                        printf("%d", i);
                        first = FALSE;
                    } else
                        printf(" %d", i);
                }
            }
        }
    }
    printf("\n");

    /*Edges before stations*/
    for (i = 2; i < f + 2; i++) {
        if (!visited[i]) {
            for (aux = graph->adjLists[i]; aux != NULL; aux = aux->next) {
                if (visited[aux->vertex] && aux->capacity > 0) {
                    printf("%d %d\n", i, aux->vertex);
                }
            }
        }
    }

    /*Edges after stations*/
    for (i = f + e + 2; i < graph->numVertices; i++) {
        if (!visited[i]) {
            for (aux = graph->adjLists[i]; aux != NULL; aux = aux->next) {
                if (visited[aux->vertex] && aux->capacity > 0) {
                    printf("%d %d\n", i - e, aux->vertex);
                }
            }
        }
    }

}

/* =============================================================================
 * BFS
 * =============================================================================
 */

void bfs(Graph *graph, int s, int e, int f) {

    Queue *queue = createQueue();
    Edge *aux;
    int i;
    bool_t visited[graph->numVertices];

    for (i = 0; i < graph->numVertices; i++)
        visited[i] = FALSE;

    visited[s] = TRUE;
    queueInsert(queue, s);

    while (queue->head != NULL) {

        i = queue->head->data;
        queuePop(queue);

        for (aux = graph->adjLists[i]; aux != NULL; aux = aux->next) {
            if (((aux->capacity == 0 && aux->backEdge->flux < aux->backEdge->capacity) || (aux->capacity > 0 && aux->flux > 0)) && !visited[aux->vertex]) {
                visited[aux->vertex] = TRUE;
                queueInsert(queue, aux->vertex);
            }
        }
    }

    freeQueue(queue);
    printEdges(graph, visited, e, f);
}

/* =============================================================================
 * Main
 * =============================================================================
 */

int main(int argc, const char *argv[]) {

    Graph* graph;
    int f, e, t;
    int size;
    int s, d;
    int i = 2;
    int j;
    int capacity;

    /* Gets number of suppliers, stations and edges from stdin */
    if (scanf("%d %d %d\n", &f, &e, &t) < 0) {
        exit(1);
    }

    /* Creates graph */
    size = f + 2 * e + 2;

    graph = createGraph(size);

    /* Setups source */
    for (j = 0; j < f; j++) {
        if (scanf("%d", &capacity) < 0) {
             exit(1);
        }
        addEdge(graph, 0, i++, capacity);
        getchar();
    }

    /* Setups stations */
    for (j = 0; j < e; j++) {
        if (scanf("%d", &capacity) < 0) {
            exit(1);
        }
        addEdge(graph, i, i + e, capacity);
        i++;
        getchar();
    }

    /* Adds rest of the edges */
    for (j = 0; j < t; j++) {
        if (scanf("%d %d %d", &s, &d, &capacity) < 0) {
            exit(1);
        }
        if (s >= f + 2) {
            addEdge(graph, s + e, d, capacity);
        }
        else {
            addEdge(graph, s, d, capacity);
        }
        getchar();
    }


    /* Finds max flow */
    relabelToFront(graph, 0, f);

    /* Finds minimum cut */
    bfs(graph, 1, e, f);
    freeGraph(graph);
    return 0;
}
