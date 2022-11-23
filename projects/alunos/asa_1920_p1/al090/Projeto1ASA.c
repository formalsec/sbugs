#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define UNVISITED -1
#define VISITED 1

struct node {
    int w;
    struct node *next;
};
typedef struct node* link;

struct adjList { 
    link head;  
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

int *dsc;
int *low;
int *grades;
int *onStack;
Queue queue;
Graph G;

int time = 0;
int sccCount = 0;

link newNode (int v) {
    link a = can_fail_malloc (sizeof (struct node));
    a->w = v;
    a->next = NULL;
    return a;
}

Queue createQueue() {
    Queue s = (Queue)can_fail_malloc(sizeof(struct queue));
    s->head = s->tail = NULL;
    return s;
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

void newEdge(int v, int w) {
    link new = newNode(w);
    new->next = G->adj[v].head;
    G->adj[v].head = new;
    G->E++;
}

Graph initGraph (int V) { 
    /* building a graph with V vertices */
    int v;
    Graph G = can_fail_malloc(sizeof (struct graph));
    G->V = V;
    G->E = 0;
    G->adj = can_fail_malloc (V * sizeof(AdjList));
    for(v = 0; v < V; v++)
        G->adj[v].head = NULL;
    return G;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int visit(int v) {
    link a;
    push(v);
    onStack[v] = 1;
    dsc[v] = time;
    low[v] = time;
    time++;

    int maxGrade = grades[v];


    for (a = G->adj[v].head; a != NULL; a = a->next) {
        if(dsc[a->w] == UNVISITED) {
            maxGrade = max(maxGrade, visit(a->w));
            low[v] = min(low[v], low[a->w]);
        }
        else if(onStack[a->w] == 1) {
            maxGrade = max(maxGrade, grades[a->w]);
            low[v] = min(low[v], dsc[a->w]);
        }
        else {
            maxGrade = max(maxGrade, grades[a->w]);
        }
    }

    if(dsc[v] == low[v]) {
        for(a = queue->head; a != NULL; a = a->next) {
            grades[a->w] = max(maxGrade, grades[a->w]);
            onStack[a->w] = 0;
            pop();
        }
        sccCount++;
    }

    grades[v] = maxGrade;  
    return maxGrade;
}

int main() {

    int i = 0;
    int students, friendships, s1, s2;
    scanf("%d,%d", &students, &friendships);

    G = initGraph(students);
    queue = createQueue();
    dsc = (int*)can_fail_malloc(students*sizeof(int));
    low = (int*)can_fail_malloc(students*sizeof(int));
    grades = (int*)can_fail_malloc(students*sizeof(int));
    onStack = (int*)can_fail_malloc(students*sizeof(int));

    memset(onStack, 0, students * sizeof(int));
    memset(dsc, UNVISITED, students * sizeof(int));
    memset(low, UNVISITED, students * sizeof(int));

    for(i = 0; i < students; i++) {
        scanf("%d", &grades[i]);
    }

    for(i = 0; i < friendships; i++) {
        scanf("%d %d", &s1, &s2);
        newEdge(s1-1, s2-1);                    /* s2 gives information to s1 */
    }

    for(i = 0; i < students; i++) {
        visit(i);
        printf("%d\n", grades[i]);
    }

    free(G);
    free(dsc);
    free(low);
    free(grades);
    free(onStack);
    free(queue);

    return 0;

}