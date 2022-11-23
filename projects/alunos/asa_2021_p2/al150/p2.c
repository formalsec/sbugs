#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VALUE 1000000
/* STRUCTURES */
int n_v;
typedef struct Queue {
    int front, back, size, max_size;
    int* array;
}*Queue;

/* QUEUE */
struct Queue* createQueue(int max_size) {
    Queue queue = can_fail_malloc(sizeof(struct Queue));
    queue->max_size = max_size;
    queue->front = queue->size = 0;
    queue->back = max_size - 1;
    queue->array = (int*)can_fail_malloc(
        queue->max_size * sizeof(int));
    return queue;
}

int isFull(struct Queue* queue) { return (queue->size == queue->max_size); }

int isEmpty(struct Queue* queue) { return (queue->size == 0); }

void addQueue(struct Queue* queue, int item) {
    if (isFull(queue)) {
        fprintf(stderr,"cant add, queue full\n");
        exit(EXIT_FAILURE);
    }
    queue->back = ((queue->back + 1) % queue->max_size);
    queue->array[queue->back] = item;
    queue->size = queue->size + 1;
}

int removeQueue(struct Queue* queue) {
    if (isEmpty(queue)) {
        fprintf(stderr,"cant remove, queue empty\n");
        exit(EXIT_FAILURE);
    }
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1)
                   % queue->max_size;
    queue->size = queue->size - 1;
    return item;
}

/* GRAPH AND MIN FNC */

int ** newGraph (int num_v) {
    
    int i;    
    int **graph = can_fail_malloc(sizeof(int*)*num_v);
    
    for (i=0; i<num_v; i++) {
        graph[i] = (int *)can_fail_calloc(num_v,sizeof(int));      
    }
    return graph;
}

void addEdge (int ** graph, int v2, int v1, int capacity) {
    
    graph[v2][v1] = capacity;
    graph[v1][v2] = capacity;
    
}

int min (int a, int b) {
    if (a > b)
        return b;
    else
        return a;
}

/* PROG FUNCS */
int** processInput () {
    
    int num_proc, num_coms, c_X, c_Y, v1, v2, cap;
    
    /*1st line*/
    int num_args = scanf("%d %d", &num_proc, &num_coms);
    if ((num_args != 2) || (num_proc < 2) || (num_coms < 0)) {
        printf("bad args 1\n");
        exit(EXIT_FAILURE);
    }
    
    n_v = num_proc +2;
    int** graph = newGraph(n_v);
    
    int i;
    /*next n lines*/
    for (i=0; i<num_proc; i++) {
        int num_args = scanf("%d %d", &c_X, &c_Y);
        if (num_args != 2) {
            printf("bad args 2\n");
            exit(EXIT_FAILURE);
        }
        
        addEdge (graph, 0, i+1, c_X);
        addEdge (graph, n_v-1, i+1, c_Y);
    }
    /*next k lines*/
    for (i=0; i<num_coms; i++) {
        int num_args = scanf("%d %d %d", &v1, &v2, &cap);
        if (num_args != 3) {
            printf("bad args 3\n");
            exit(EXIT_FAILURE);
        }
        
        addEdge (graph, v1, v2, cap);
    }
    return graph;
}

int bfs(int** res_graph, int s, int t, int* p_list) {
    
    /* create vis list */
    int* visited_list = (int *)can_fail_calloc(n_v,sizeof(int));
    /* create queue */
    Queue queue = createQueue(n_v);
    /* colocar source na queue */
    addQueue(queue, s);                                 
    visited_list[s] = 1;
    p_list[s] = -1;
    /* bfs */
    while (!(isEmpty(queue))) {
        int u = removeQueue(queue);
        int v;
 
        for (v=0; v<n_v; v++) {
            if ((visited_list[v]==0) && (res_graph[u][v] > 0)) {
                if (v == t) {
                    p_list[v] = u;
                    return 1;
                }
                addQueue(queue, v);
                p_list[v] = u;
                visited_list[v] = 1;
            }
        }
    }
    return 0;
}

void fordFulkerson (int** graph, int s, int t) {

    int u, v;
    
    int** res_graph = newGraph(n_v);
    
    for (u=0; u<n_v; u++)
        for(v=0; v<n_v; v++) {
            res_graph[u][v] = graph[u][v];
            res_graph[v][u] = graph[u][v];
        }
    
    int* p_list = (int *)can_fail_calloc(n_v,sizeof(int));
    int max_flux = 0;
    
    while(bfs(res_graph, s, t, p_list)) {
        int path_flux = MAX_VALUE;
        for (v = t; v != s; v = p_list[v]) {
            u = p_list[v];
            path_flux = min(path_flux, res_graph[u][v]);
        }
        for (v = t; v != s; v = p_list[v]) {
            u = p_list[v];
            res_graph[u][v] -= path_flux;
            res_graph[v][u] += path_flux;
        }
        max_flux += path_flux;
    }
    
    printf("%d\n",max_flux);
}

int main(int agrc, char* argv[]) {
        
    int** grafo = processInput ();
    
    fordFulkerson(grafo,0, n_v-1);
    
    return 0;
}