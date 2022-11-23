#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX(a, b) ((a)>(b))?(a):(b)
#define MIN(a, b) ((a)<(b))?(a):(b)

typedef struct edge{
    int v;
    int w;
    struct edge *next;
} Edge;

Edge EDGE(int v, int w) {
    Edge e;
    e.v = v;
    e.w = w;
    return e;
}

typedef struct graph *Graph;
typedef struct node *link;

struct node {
    int v;
    link next;
};

struct graph {
    int V, E;
    link *adj;
};

link InsertBegin(int v, link head) {
    link x = (link) can_fail_malloc(sizeof(struct node));
    x->v = v;
    x->next = head;
    return x;
}

link new, aux2;

link InsertEnd(link head, link tail, int v) {
    new->v = v;
    new->next = NULL;
    aux2 = new;
    if(head == NULL) return new;
    tail->next = new;
    return head;
}

Edge *aux;

Edge *InsertEndEdge(Edge *head, Edge *tail, Edge e) {
    Edge *new = (Edge*)can_fail_malloc(sizeof(Edge));
    new->v = e.v;
    new->w = e.w;
    new->next = NULL;
    aux = new;
    if(head == NULL) return new;
    tail->next = new;
    return head;
}

Graph G;

Graph GRAPHinit(int V) {
    int v;
    G = (Graph) can_fail_malloc(sizeof(struct graph));
    G->V = V;
    G->E = 0;
    G->adj = (link*) can_fail_malloc(V * sizeof(link));
    for (v = 0; v < V; v++)
        G->adj[v] = NULL;
    return G;
}

void GRAPHinsertE(Graph G, Edge e) {
    int v = e.v, w = e.w;
    G->adj[v-1] = InsertBegin(w, G->adj[v-1]);
    G->E++;
}

struct stack_node {
    int value;
    struct stack_node *next;
};

static struct stack_node *top;

void STACKinit() {
    top = NULL;
}

void STACKpush(int value) {
    struct stack_node *new;
    new = (struct stack_node *) can_fail_malloc(sizeof(struct stack_node));
    new->value = value;
    new->next = top;
    top = new;
}

int STACKis_empty() {
    return top == NULL;
}

int STACKpop() {
    int value;
    struct stack_node* old;
    if (!STACKis_empty()){
        value = top->value;
        old = top;
        top = top->next;
        free(old);
        return value;
    } else {
        return -1;
    }
}

struct stack_node *STACKfind_index(int tar) {
    struct stack_node* t = top;
    int f = 0;
    while (t != NULL){
        if (t->value == tar){
            f = 1;
            break;
        }
        t = t->next;
    }
    if(f != 0)
        return t;
    else
        return NULL;
}

int visited = 0, *d, *low;
int *est, highest_est = INT_MIN, scc_counter = 0;
link *scc, scc_highest_est;
Edge *bridges;

void Tarjan_Visit(int u) {
    d[u] = visited;
    low[u] = visited;
    visited += 1;
    
    STACKpush(u+1);
    link i;
    for (i = G->adj[u]; i != NULL ; i = i->next) {
        if (d[i->v - 1] == INT_MAX || STACKfind_index(i->v)!= NULL) {
            if (d[i->v - 1] == INT_MAX)
                Tarjan_Visit(i->v - 1);
            low[u] = MIN(low[u], low[i->v - 1]);
            if (d[u] < low[i->v-1]) 
                bridges = InsertEndEdge(bridges, aux, EDGE(u+1, i->v));
        } else {
            bridges = InsertEndEdge(bridges, aux, EDGE(u+1, i->v));
        }
    }
    if (d[u] == low[u]){
        
        int v = STACKpop();
        new = (link) can_fail_malloc(sizeof(struct node));
        scc[v-1] = new;
        highest_est = MAX(est[v-1], highest_est);

        while ((u+1) != v) {
            v = STACKpop();
            scc[v-1] = new;
            highest_est = MAX(est[v-1], highest_est);
        }

        scc_highest_est = InsertEnd(scc_highest_est, aux2, highest_est);
        scc_counter++;
        highest_est = INT_MIN;
        
        
    }
    
}

void SCC_Tarjan(Graph G) {
    STACKinit();
    int u;
    for (u = 0; u < G->V; u++)
        d[u] = INT_MAX;
    for (u = 0; u < G->V; u++)
        if (d[u] == INT_MAX){
            Tarjan_Visit(u);
        }
            
}

int main() {

    int N, M;

    do {
        scanf("%d, %d", &N, &M);
    } while (N < 2 || M < 1);
    
    Graph G = GRAPHinit(N);
        
    est = (int*) can_fail_malloc(N * sizeof(int));
    scc = (link*) can_fail_malloc(N * sizeof(link));
    int i;
    for (i = 0; i < N; i++) {
        scanf("%d", &est[i]);
    }
      
    int v, w;
    for (i = 0; i < M; i++) {
        scanf("%d %d", &v, &w);
        GRAPHinsertE(G, EDGE(v, w));
    }

    d = (int*) can_fail_malloc(G->V * sizeof(int));
    low = (int*) can_fail_malloc(G->V * sizeof(int));

    SCC_Tarjan(G);

    Edge *e;
    for (e = bridges; e != NULL; e = e->next) {
        scc[e->v-1]->v = MAX(scc[e->v-1]->v, scc[e->w-1]->v);
        
    }

    for (i=0; i<N; i++) {
        printf("%d\n", scc[i]->v);
    }
    
    return 0;
}