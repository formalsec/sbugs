#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VALUE 10000

typedef struct EDGE {
    int dest;
    int weight;
} EDGE;

typedef struct NODE {
    int color;
    int n_edges;
    struct EDGE *edges;
} NODE;

typedef struct GRAPH {
    int size;
    struct NODE *nodes;
} GRAPH;

GRAPH *createGraph(int num_processes) {
    int i = 0;
    GRAPH *graph = (GRAPH*) malloc(sizeof(GRAPH));
    graph->size = num_processes + 2;
    graph->nodes = (NODE*) malloc(graph->size * sizeof(NODE));
    for (i = 0; i < graph->size; i++) {
        graph->nodes[i].color = 0;
        graph->nodes[i].n_edges = 0;
        graph->nodes[i].edges = (EDGE*) malloc(sizeof(EDGE));
    }
    return graph;
}

void addEdge(GRAPH *graph, int source, int dest, int weight) {
    int n_edges_f = 0, n_edges_b = 0;
    n_edges_f = graph->nodes[source].n_edges;
    n_edges_b = graph->nodes[dest].n_edges;
    graph->nodes[source].edges[n_edges_f].dest = dest;
    graph->nodes[source].edges[n_edges_f].weight = weight;
    graph->nodes[source].n_edges += 1;
    graph->nodes[source].edges = (EDGE*) realloc(graph->nodes[source].edges, sizeof(EDGE) * (n_edges_f + 2));
    graph->nodes[dest].edges[n_edges_b].dest = source;
    graph->nodes[dest].edges[n_edges_b].weight = weight;
    graph->nodes[dest].n_edges += 1;
    graph->nodes[dest].edges = (EDGE*) realloc(graph->nodes[dest].edges, sizeof(EDGE) * (n_edges_b + 2));
}

void initGraph(GRAPH *graph, int num_processes, int num_communications) {
    int i = 0, weight_X = -1, weight_Y = -1, source = 0, dest = 0;
    for (i = 1; i <= num_processes; i++) {
        scanf("%d %d", &weight_X, &weight_Y);
        addEdge(graph, 0, i, weight_X);
        addEdge(graph, i, graph->size - 1, weight_Y);
    }
    for (i = 0; i < num_communications; i++) {
        scanf("%d %d %d", &source, &dest, &weight_X);
        addEdge(graph, source, dest, weight_X);
    }

}

void addToQueue(int *queue, int v, int *end) {
    queue[*end] = v;
    *end += 1;
}

int removeFromQueue(int *queue, int *begin) {
    int v = 0;
    v = queue[*begin];
    *begin += 1;
    return v;
}

int bfs(GRAPH *graph, int source, int dest, int *parent, int *queue) {
    int i = 0, v = 0, w = 0, begin = 0, end = 0;
    for (i = 1; i < graph->size; i++) {
        graph->nodes[i].color = 0;
    }
    graph->nodes[source].color = 1;
    addToQueue(queue, source, &end);
    while (begin != end) {
        v = removeFromQueue(queue, &begin);
        for (i = 0; i < graph->nodes[v].n_edges; i++) {
            w = graph->nodes[v].edges[i].dest;
            if (graph->nodes[w].color == 0 && graph->nodes[v].edges[i].weight > 0) {
                if (w == dest) {
                    parent[w] = v;
                    return 1;
                }
                addToQueue(queue, w, &end);
                graph->nodes[w].color = 1;
                parent[w] = v;
            }
        }
    }
    return 0;
}

int min(int a, int b) {
    int min = 0;
    min = (a < b) ? a : b;
    return min;
}

int fordfulkerson(GRAPH *graph, int s, int t) {
    int i = 0, v = 0, w = 0, flow = 0, max_flow = 0;
    int *parent = (int*) malloc(graph->size * sizeof(int));
    int *queue = (int *) malloc(graph->size * sizeof(int));
    while (bfs(graph, s, t, parent, queue)) {
        flow = MAX_VALUE;
        for (w = t; w != s; w = parent[w]) {
            v = parent[w];
            for (i = 0; i < graph->nodes[v].n_edges; i++) {
                if (graph->nodes[v].edges[i].dest == w)
                    flow = min(flow, graph->nodes[v].edges[i].weight);
            }
        }
        for (w = t; w != s; w = parent[w]) {
            v = parent[w];
            for (i = 0; i < graph->nodes[v].n_edges; i++) {
                if (graph->nodes[v].edges[i].dest == w)
                    graph->nodes[v].edges[i].weight -= flow;
            }
            for (i = 0; i < graph->nodes[w].n_edges; i++) {
                if (graph->nodes[w].edges[i].dest == v)
                    graph->nodes[w].edges[i].weight += flow;
            }
        }
        max_flow += flow;
    }
    return max_flow;
}

int main() {
    int num_processes = 0, num_communications = 0;
    scanf("%d %d", &num_processes, &num_communications);
    GRAPH *graph = createGraph(num_processes);
    initGraph(graph, num_processes, num_communications);
    printf("%d\n", fordfulkerson(graph, 0, graph->size - 1));
    return 0;
}
