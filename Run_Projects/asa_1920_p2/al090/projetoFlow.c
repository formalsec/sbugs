#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h>

#define UNVISITED -1

struct node {
    int w;
    struct node *next;
};
typedef struct node* link;

struct edge {
    int from;
    int to;
    int capacity;
    bool hasReverse;
    struct edge* next;
};
typedef struct edge Edge;

struct adjList { 
    Edge *head;  
};
typedef struct adjList AdjList;

struct graph {
    int V;          /* number of vertices */
    int E;          /* number of edges */
    AdjList *adj;      /* pointer to an array of adjacency lists * O(V+E) */
};
typedef struct graph *Graph;

struct queue { 
    link head, tail;
}; 
typedef struct queue *Queue;

int vertices;
int source;
int sink;
int avenues;
int streets;
int markets;
int citizens;
int increment;
int maxFlow = 0;
int *currentC;
int *prev;
Graph G;
Queue queue;

int min(int a, int b) {
    return a < b ? a : b;
}

link newNode (int v) {
    link a = malloc (sizeof (struct node));
    a->w = v;
    a->next = NULL;
    return a;
}

void newEdge(Graph graph, int v, int w, int weight, bool hasReverse) {

    Edge* new = malloc (sizeof (struct edge));
    new->from = v;
    new->to = w;
    new->capacity = weight;
    new->hasReverse = hasReverse;

    new->next = graph->adj[v].head;
    graph->adj[v].head = new;
    graph->E++;
}

int intFromCoordinates(int x, int y, bool inc) {

    if(inc) return ((y-1)*avenues + (x-1)) + increment;

    return ((y-1)*avenues + (x-1));

}

Graph initGraph() { 
    /* building a graph with V vertices */
    int i, j, k, v_in, v_out;
    int da[4] = {0, 0, 1, -1};
    int ds[4] = {-1, 1, 0, 0};
    Graph G = malloc(sizeof (struct graph));

    G->V = avenues*streets;
    G->E = 0;
    G->adj = malloc ((avenues*streets*2+2) * sizeof(AdjList));

    for(i = 0; i < avenues*streets; i++)
        G->adj[i].head = NULL;

    for(i = 1; i <= avenues; i++) {
        for(j = 1; j <= streets; j++) {

            v_in = intFromCoordinates(i, j, false);
            v_out = intFromCoordinates(i, j, true);
            G->adj[v_out].head = NULL;

            newEdge(G, v_in, v_out, 1, false);

            for(k = 0; k < 4; k++) {
                int aa = i + da[k];
                int ss = j + ds[k];

                if(ss >= 1 && aa >= 1 && ss <= streets && aa <= avenues)
                    newEdge(G, v_out, intFromCoordinates(aa, ss, false), 1, false);

            }
        }
    }

    G->adj[source].head = NULL;
    G->adj[sink].head = NULL;

    return G;
}

Queue createQueue() {
    Queue s = (Queue)malloc(sizeof(struct queue));
    s->head = s->tail = NULL;
    return s;
}

int emptyQueue() {
    if(queue->head == NULL)
        return 1;
    return 0;
}

void pop() {

    if(queue->head == NULL)
        return;

    link temp = queue->head;
    queue->head = queue->head->next;

    if(queue->head == NULL)
        queue->tail = NULL;

    free(temp);
}

void push(int v) {

    link temp = newNode(v);

    if(queue->tail == NULL) {
        queue->head = queue->tail = temp;
        return;
    }

    queue->tail->next = temp;
    queue->tail = temp;
}

int bfs(int start, int end) {

    Edge* a;

    memset(prev, UNVISITED, vertices * sizeof(int));
    memset(currentC, 0, vertices * sizeof(int));

    push(start);

    prev[start] = -2;
    currentC[start] = 999;

    while(emptyQueue() == 0) {

        int u = queue->head->w;
        pop();

        for(a = G->adj[u].head; a != NULL; a = a->next) {

            if(prev[a->to] == -1) {
                if(a->capacity > 0) {

                    prev[a->to] = u;
                    currentC[a->to] = min(currentC[u], a->capacity);

                    if(a->to == end) {

                        while(emptyQueue() == 0) {

                            pop();
                        }

                        return currentC[end];
                    }

                    push(a->to);
                }
            }
        }
    }

    return 0;

}

void treatPath(int start, int end, int flow) {

    Edge* a;
    int current = end;

    while(current != start) {

        int previous = prev[current];

        for(a = G->adj[previous].head; a != NULL; a = a->next) {

            if(a->to == current) {

                a->capacity -= flow;
                break;
            }

        }

        if(a->hasReverse) {

            for(a = G->adj[current].head; a != NULL; a = a->next) {

                if(a->to == previous){

                    a->capacity += flow;
                    break;
                }

            }

        }   

        else {
            
            a->hasReverse = true;
            newEdge(G, a->to, a->from, 1, true);

        }

        current = previous;
    }

}

void edmondsKarp() {

    while(true) {

        int flow = 0;

        flow = bfs(source, sink);

        if(flow == 0) break;

        maxFlow += flow;

        if(maxFlow == min(citizens, markets)) break;

        treatPath(source, sink, flow);

    }
}

int main() {

    int i = 0;
    int x, y;

    scanf("%d %d", &avenues, &streets);
    scanf("%d %d", &markets, &citizens);

    increment = avenues*streets;
    source = 2*avenues*streets;
    sink = 2*avenues*streets+1;
    vertices = 2*avenues*streets+2;

    G = initGraph();
    queue = createQueue();

    prev = (int*)malloc(vertices * sizeof(int));
    currentC = (int*)malloc(vertices * sizeof(int));

    for(i = 0; i < markets; i++) {
        scanf("%d %d", &x, &y);
        newEdge(G, intFromCoordinates(x, y, true), sink, 1, false);
    }

    for(i = 0; i < citizens; i++) {
        scanf("%d %d", &x, &y);
        newEdge(G, source, intFromCoordinates(x, y, false), 1, false);
    }

    edmondsKarp();

    printf("%d\n", maxFlow);

    free(G);
    free(queue);
    free(prev);
    free(currentC);

    return 0;

}