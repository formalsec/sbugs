#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define UNVISITED -1
#define min(X, Y) ((X) < (Y) ? (X) : (Y))

typedef struct node *link;
typedef struct graph *Graph;

struct node {
    int v;
    link next;
};

struct graph {
    int V;
    int E;
    link *adj;
};

struct Stack {
    int top;
    unsigned capacity;
    int *array;
};

/* VARIABLES ********************************************/

Graph graph;
int numberStudents, numberRelations;
int *grades;
int visited;
int *d;
int *low;
int *onStack;
struct Stack *stack;
int sccCount;
int *countArray;

/* FUNCTIONS ********************************************/

void processInput();
int findMax(int *array, int size);
link createLink(int v, link next);
Graph graphInit(int);
void graphInsertE(Graph G, int v, int w);
struct Stack *createStack(unsigned capacity);
int isFull(struct Stack *stack);
int isEmpty(struct Stack *stack);
void push(struct Stack *stack, int item);
int pop(struct Stack *stack);
int peek(struct Stack *stack);
void tarjan();
void tarjanVisit(int u);
void sccUpdateGrades();
void reUpdateGrades();

/* MAIN *************************************************/

int main() 
{
    processInput();

    tarjan();
    sccUpdateGrades();
    reUpdateGrades();

    int i;
    for (i = 0; i < numberStudents; i++)
    {
        printf("%d\n", grades[i]);
    }
    return 0;
}

void processInput() {
    int v, w;
    int i;

    scanf("%d,%d", &numberStudents, &numberRelations);
    graph = graphInit(numberStudents);

    grades = can_fail_malloc(sizeof(int) * numberStudents);
    for (i = 0; i < numberStudents; i++) {
        scanf("%d", &grades[i]);
    }

    for (i = 0; i < (numberRelations); i++) {
        scanf("%d %d", &v, &w);
        graphInsertE(graph, v, w);
    }

}

link createLink(int v, link next) {
    link x = can_fail_malloc(sizeof(struct node));
    x->v = v;
    x->next = next;
    return x;
}

Graph graphInit(int V) {
    int v;
    Graph G = can_fail_malloc(sizeof(struct graph));
    G->V = V;
    G->E = 0;
    G->adj = can_fail_malloc(V * sizeof(link));
    for (v = 0; v < V; v++)
        G->adj[v] = NULL;
    return G;
}

void graphInsertE(Graph G, int v, int w) {
    v--;  
    w--;
    G->adj[v] = createLink(w, G->adj[v]); 
    G->E++;
}


struct Stack* createStack(unsigned capacity) { 
    struct Stack* stack = (struct Stack*)can_fail_malloc(sizeof(struct Stack)); 
    stack->capacity = capacity; 
    stack->top = -1; 
    stack->array = (int*)can_fail_malloc(stack->capacity * sizeof(int)); 
    return stack; 
} 
  
int isFull(struct Stack* stack) { 
    return stack->top == stack->capacity - 1; 
} 
  
int isEmpty(struct Stack* stack) { 
    return stack->top == -1; 
} 
  
void push(struct Stack* stack, int item) { 
    if (isFull(stack)) 
        return; 
    stack->array[++stack->top] = item; 
} 
  
int pop(struct Stack* stack) { 
    if (isEmpty(stack)) 
        return INT_MIN; 
    return stack->array[stack->top--];
} 


int findMax(int *array, int size) {
    int t = 0;
    int i;
    for (i = 0; i<size; i++) {
        if (grades[array[i]] > t)
            t = grades[array[i]];
    }
    return t;
}

void tarjanVisit(int u) {
    link v;
    
    push(stack, u);
    onStack[u] = true;
    d[u] = low[u] = visited++;

    
    for (v = graph->adj[u]; v != NULL; v = v->next) {
        if (d[v->v] == UNVISITED){
            tarjanVisit(v->v);
        }
        if (onStack[v->v]) {
            low[u] = min(low[u], low[v->v]);
        }
    }

    if (d[u] == low[u]) {
        int w;
        for (w = pop(stack);; w = pop(stack))
        {
            onStack[w] = false;
            low[w] = d[u];
            if (w == u) {
                break;
            }
        }
        sccCount++;
    }
    
}

void tarjan() {
    int u;
    visited = 0;

    d = can_fail_malloc(sizeof(int) * graph->V);
    low = can_fail_malloc(sizeof(int) * graph->V);
    stack = createStack(graph->V);
    onStack = can_fail_malloc(sizeof(int) * graph->V);

    for (u=0; u < graph->V; u++) {
        d[u] = UNVISITED;
        onStack[u] = false;
    }
    for (u = 0; u < graph->V; u++) {
        if(d[u] == UNVISITED){
            tarjanVisit(u);
        }
    }
}


void sccUpdateGrades() {
    int i, j;

    int maxScc;

    countArray = can_fail_malloc(sizeof(int) * sccCount);
    for (i = 0; i < sccCount; i++)
        countArray[i] = 1;

    int i_countArray = 0;
    for (i = 1; i < (stack->capacity) + 1; i++) {
        if (low[stack->array[i]] == low[stack->array[i-1]]) {
            (countArray[i_countArray])++;
        }
        else {
            i_countArray++;
        }
    }

    int i_stack = 0;
    int j_stack = 0;
    for (i = 0; i < sccCount; i++) {
        int *compareArray = can_fail_malloc(sizeof(int) * countArray[i]);
        for (j = 0; j < countArray[i]; j++) {
            compareArray[j] = stack->array[i_stack];
            i_stack++;
        }

        maxScc = findMax(compareArray, countArray[i]);
        for (j = 0; j < countArray[i]; j++) {
            grades[stack->array[j_stack]] = maxScc;
            j_stack++;
        }
    }
}

void reUpdateGrades() {
    int i,u;
    link t;

    for (i = numberStudents - 1; i >= 0; i--) {
        u = stack->array[i];
        for (t = graph->adj[u]; t != NULL; t = t->next) {
            if (grades[u] < grades[t->v]) {
                grades[u] = grades[t->v];
            }
        }
    }

}