#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFINITY -50
#define DEBUG 0
#define TRUE 1

typedef struct queue_element {
    int n;
    int max_capacity;
    struct queue_element * next;
    struct queue_element * pi;
} queue_element;

typedef struct edge {
    int capacity;
    struct edge * next;
    int v;
} edge;

typedef struct node {
    int visited;
    edge * capacities;
    edge * connections;
} node;

static int SOURCE = 0;
static int SINK;

int get(queue_element * queue) {
    return queue->n;
}

int min(int a, int b) {
    if (a == INFINITY) return b;
    if (b == INFINITY) return a;
    return (a < b) ? a : b;
}

void destroy_queue(queue_element * head) {
	while (head != NULL) {
		queue_element * new_head = head->next;
        free(head);
        head = new_head;
	}	
}

void destroy_graph(node * graph) {
    int i;

    for (i = 0; i <= SINK; i++) {
        free(graph[i].capacities);
    }
    free(graph);
}

queue_element * push_queue(queue_element * head, int n, int max_capacity) {
	queue_element * new_next = (queue_element *) can_fail_malloc(sizeof(queue_element));
	new_next->n = n;
    new_next->max_capacity = max_capacity;
    new_next->pi = head;

    if (head) {
        new_next->next = head->next;
        head->next = new_next;
        return head;
    } else {
        new_next->next = NULL;
        return new_next;
    }
}

void push_flow(node * graph, int u, int v, int flow) {
    graph[u].capacities[v].capacity -= flow;
    graph[v].capacities[u].capacity += flow;
}

edge * push_edge(node * graph, int u, int v) {
    edge * new_head = &graph[u].capacities[v];
    new_head->next = graph[u].connections;
    new_head->v = v;

    return new_head;
}

void addEdge(node * graph, int u, int v, int capacity) {
    if ((capacity > 0) && (graph[u].capacities[v].capacity == 0)) {
        graph[u].connections = push_edge(graph, u, v);
    }

    graph[u].capacities[v].capacity = capacity;
}

void print(queue_element * head) {
	queue_element * printing = head;
    if (!head) return;
	while (printing->next != NULL) {
		printf("%d, ", get(printing));
		printing = printing->next;
	}
    printf("%d\n", get(printing));
}

char * to_string(int u) {
    if (u == SINK)
        return "SINK";
    if (u == SOURCE)
        return "SOURCE";
    
    static char temp[50];
    sprintf(temp, "node %d", u);
    return temp;
}

queue_element * dfs_search(node * graph, queue_element * queue) {
    int been_visited = ++graph[get(queue)].visited;
    while (queue) {
        int u = get(queue);
        if (DEBUG) printf("Exploring node %d\n", u);
        if (u == SINK) return queue;

        edge * visiting = graph[u].connections;
        while(visiting) {
            int v = visiting->v;
            int capacity = visiting->capacity;
            if ((capacity > 0) && (graph[v].visited != been_visited)) {
                graph[v].visited = been_visited;
                queue = push_queue(queue, v, min(queue->max_capacity, capacity));
                if (DEBUG) printf("Added node %d with max capacity %d\n", v, min(queue->max_capacity, capacity));
            }
            visiting = visiting->next;
        }
        queue = queue->next;
    }

    return NULL;
}

int maximize_flow(node * graph, queue_element * path) {
    int flow = path->max_capacity;
    char res[500];
    strcpy(res, to_string(get(path)));
    while(path->pi) {
        queue_element * pi = path->pi;
        push_flow(graph, get(pi), get(path), flow);
        path = path->pi;
        char temp[500];
        strcpy(temp, res);
        strcpy(res, to_string(get(path)));
        strcat(res, " to ");
        strcat(res, temp);
    }
    if (DEBUG) printf("%s\nFlow: %d\n", res, flow);
    return flow;
}

int edmonds_karp(node * graph) {
    int max_flow = 0;
    while (TRUE) {
        queue_element * origin = push_queue(NULL, SOURCE, INFINITY);
        queue_element * path = dfs_search(graph, origin);

        if (!path) break;
        max_flow += maximize_flow(graph, path);
        destroy_queue(origin);
    }
    return max_flow;
}

int main() {

    int V, n_edges, n_processes;
    node *graph;
    int i;

    if (scanf("%d %d", &n_processes, &n_edges) <= 0) {
		perror("Error reading arguments");
	}
    V = n_processes + 2;
    SINK = V - 1;

    graph = can_fail_malloc(sizeof(node) * V);

    /* Initializing source */
    graph[SOURCE].capacities = can_fail_malloc(sizeof(edge) * V);
    graph[SOURCE].visited = 0;

    /* Initializing sink */
    graph[SINK].capacities = can_fail_malloc(sizeof(edge) * V);
    graph[SINK].visited = 0;
    
    /* Initializing all vertexes and edges */
    for (i = 1; i < SINK; i++) {
        int cost1, cost2, j;
        if (scanf("%d %d", &cost1, &cost2) <= 0) {
            perror("Error reading arguments");
        }
        graph[i].capacities = can_fail_malloc(sizeof(edge) * V);
        graph[i].visited = 0;

        for (j = 0; j < V; j++) {
            graph[i].capacities[j].capacity = 0;
        }

        addEdge(graph, i, SINK, cost2);
        addEdge(graph, SOURCE, i, cost1);
        addEdge(graph, i, SOURCE, 0);
        addEdge(graph, SINK, i, 0);
    }


    /* Initializing links between processes */
    for (i = 0; i < n_edges; i++) {
        int from, to, capacity;
        if (scanf("%d %d %d", &from, &to, &capacity) <= 0) {
            perror("Error reading arguments");
        }

        addEdge(graph, from, to, capacity);
        addEdge(graph, to, from, capacity);
    }

    printf("%d\n", edmonds_karp(graph));
    destroy_graph(graph);

    return 0;
}