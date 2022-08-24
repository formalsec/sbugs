#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*STRUCTURES*/
typedef struct node {
    int num;
    struct node* next;
}*nodept;

typedef struct vertice {
    int edges;
    int tmp;
    int vis_state;
}*verticept;

typedef struct Graph {
    int size;
    nodept* adj_lists;
    verticept* v_list;
}*Graphpt;

typedef struct Queue {
    int front, back, size, max_size;
    int* array;
}*Queuept;

struct Queue* createQueue(int max_size) {
    Queuept queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->max_size = max_size;
    queue->front = queue->size = 0;
    queue->back = max_size - 1;
    queue->array = (int*)malloc(queue->max_size * sizeof(int));
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

struct node* newNode (int v) {
    
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->num = v;
    newnode->next = NULL;
    return newnode;
}

struct vertice* newVertice() {
    
    verticept v = (struct vertice*)malloc(sizeof(struct vertice));
    v->edges = 0;
    v->tmp = 0;
    v->vis_state = 0;
    return v;
}

struct Graph* newGraph (int size) {
    
    Graphpt graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->size = size;
    graph->adj_lists = (struct node**)malloc(size * sizeof(struct node*));
    graph->v_list = (struct vertice**)malloc(size * sizeof(struct vertice*));
    
    int i;
    
    for (i=0; i<size; i++) {
        graph->v_list[i] = newVertice();
        graph->adj_lists[i] = NULL;
    }
    return graph;
}

void addEdge (Graphpt graph, int root, int dest) {
    
    graph->v_list[dest]->edges++;
    nodept newnode = newNode(dest);
    newnode->next = graph->adj_lists[root];
    graph->adj_lists[root] = newnode; 
    
}

int* topologicalSort (Graphpt graph) {
    
    int* sorted = (int*)malloc(graph->size * sizeof(int));
    int i,j=0;
    Queuept queue = createQueue(graph->size);
    
    /* colocar vertices na queue*/
    for (i=0; i<graph->size; i++) {
        if (graph->v_list[i]->edges == 0) { 
            addQueue(queue, i);
        }
    }    
    /* para cada vertice na queue */
    while (!(isEmpty(queue))) {
        i = removeQueue(queue);
        sorted[j++] = i;
        
        nodept v = graph->adj_lists[i];
        while (v != NULL ) {
            int n = v->num;
            graph->v_list[n]->edges--;
            if (graph->v_list[n]->edges == 0)\
                addQueue(queue, n);
            v = v->next;
        }      
    }    
    return sorted;
}

void longestPath (Graphpt graph, int* sorted) {
    
    int i,j;
    int big_path = 0;
    int num_paths = 0;
    
    /*para cada vertice j na ordem topologica*/
    for (i=0; i<graph->size; i++) {
        j = sorted[i];   
        /* +1 num de v's nao visitados*/
        if (graph->v_list[j]->vis_state == 0) {
            graph->v_list[j]->vis_state = 1;
            num_paths++;
        }
        /*para cada vertice v adjacente a j*/
        nodept v = graph->adj_lists[j];
        while (v != NULL ) {
            int n = v->num;
            graph->v_list[n]->vis_state = 1;
            /*se dist u > dist v + 1   (init dist = 0)*/
            if (graph->v_list[n]->tmp < (graph->v_list[j]->tmp + 1))
                /*ent dist u = dist v + 1*/
                graph->v_list[n]->tmp = (graph->v_list[j]->tmp + 1);
            /*ir guardando maior dist (MAIOR DIST + 1)*/
            if (big_path < (graph->v_list[j]->tmp + 1)) {
                big_path = (graph->v_list[j]->tmp + 1);
            }
            v = v->next;
        }           
    }
    
    printf("%d %d\n",num_paths,big_path+1);
}

struct Graph* processInput () {
    
    int num_ver, num_ligs, a, b;
    
    int num_args = scanf("%d %d", &num_ver, &num_ligs);
    
    if ((num_args != 2) || (num_ver < 2) || (num_ligs < 0)) {
        fprintf(stderr,"bad args in 1st line\n");
        exit(EXIT_FAILURE);
    }
        
    Graphpt graph = newGraph(num_ver);
    
    int i;
    for (i=0; i<num_ligs; i++) {
        
        int num_args = scanf("%d %d", &a, &b);
        
        if ((num_args != 2) || (a > num_ver) || (a < 1) || (b > num_ver) || (b < 1)) {
            fprintf(stderr,"bad args in 2nd+ line\n");
            exit(EXIT_FAILURE);
        }
            
        addEdge (graph, a-1, b-1);
    }
    return graph;
}

void getOutput (Graphpt graph) {
    
    int* sorted = topologicalSort(graph);
    longestPath(graph, sorted);
    
}

int main(int agrc, char* argv[]) {
        
    Graphpt grafo = processInput ();
    
    getOutput (grafo);
    
    return 0;
}