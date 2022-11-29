#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>

#define FALSE 0
#define TRUE (!FALSE)

typedef struct edge {
    int u, v;
    int c_f;
    int f;
    struct edge *residual;
} * edge;

typedef struct vertex {
    int visited;
    edge pred;
} * vertex;

typedef struct flow_graph {
    vertex *V;
    edge **E;
} flow_graph;

typedef struct queue {
    int *vertexes;
    int front;
    int back;
} queue;

flow_graph *G;
queue *Q;

int M, N, S, C;

void init_queue(int size) {
    Q = (queue *) can_fail_malloc(sizeof(queue));

    Q->vertexes = (int *) can_fail_malloc(sizeof(int) * size);
    Q->front = -1;
    Q->back = -1;
}

void enqueue(int v) {
    if (Q->front == -1) Q->front = 0;

    Q->back++;

    Q->vertexes[Q->back] = v;
}

int dequeue() {
    int v;

    if (Q->back == -1) return -1;

    v = Q->vertexes[Q->front];
    Q->front++;

    if (Q->front > Q->back) { Q->front = -1; Q->back = -1; }

    return v;
}

void add_vertex(int u) {
    vertex v = (vertex) can_fail_malloc (sizeof(struct vertex));

    G->V[u] = v;
}

void add_edge(int u, int v, int c) {
    edge e;
    int pos = 0, i = 0;

    while (G->E[u][pos]) {
        if (G->E[u][pos]->u == u && G->E[u][pos]->v == v) return;

        pos++;
    }

    e = (edge) can_fail_malloc (sizeof(struct edge));

    e->u = u;
    e->v = v;
    e->c_f = c;
    e->f = 0;

    if (c == 0) {
        while(G->E[v][i]->v != u) i++;

        G->E[v][i]->residual = e;
        e->residual = G->E[v][i];
    }

    G->E[u][pos] = e;
}

int read_flow_graph() {
    int i, out, where;
    int x, y;
    int n_V;

    scanf("%d %d\n%d %d", &M, &N, &S, &C);

    n_V = M * N * 2 + 2;

	G->V = (vertex *) can_fail_malloc(sizeof(vertex) * n_V);
    G->E = (edge **) can_fail_malloc(sizeof(edge *) * n_V);

    for (i = 0; i < n_V ; i++) add_vertex(i);

    for (i = 1; i <= N * M; i++) {
        G->E[i + N * M] = (edge *) can_fail_calloc (6, sizeof(edge));
        G->E[i] = (edge *) can_fail_calloc (6, sizeof(edge));
    }

	for (i = 1; i <= N * M; i++) {
        out = i + N * M;

        if ((i - 1) % M > 0) { add_edge(out, i - 1, 1); add_edge(i - 1, out, 0); }
        if (i % M != 0) { add_edge(out, i + 1, 1); add_edge(i + 1, out, 0); }
        if (i + M <= M * N) { add_edge(out, i + M, 1); add_edge(i + M, out, 0); }
        if (i - M > 0)  { add_edge(out, i - M, 1); add_edge(i - M, out, 0); }

        add_edge(i, out, 1);
        add_edge(out, i, 0);
	}

    G->E[n_V - 1] = (edge *) can_fail_calloc (S + 1, sizeof(edge));
    for (i = 0; i < S; i++) {
        scanf("%d %d", &x, &y);

        where = M * (y - 1) + x + M * N;

        add_edge(where, n_V - 1, 1);
        add_edge(n_V - 1, where, 0);
    }

    G->E[0] = (edge *) can_fail_calloc (C + 1, sizeof(edge));
    for(i = 0; i < C; i++) {
        scanf("%d %d",&x,&y);

        where = M * (y - 1) + x;

        add_edge(0, where, 1);
        add_edge(where, 0, 0);
    }

    return n_V;
}

void init_search(int size) {
    int i;

    for (i = 0; i < size; i++) {
            G->V[i]->visited = 0;
            G->V[i]->pred = NULL;
    }
}

int bfs(int s, int t) {
    int v, suc;
    int cur;
    edge path;

    Q->front = -1;
    Q->back = -1;

    enqueue(s);

    G->V[s]->visited = 1;

    while ((v = dequeue()) != -1) {
        G->V[v]->visited = 2;

        cur = 0;
        while (G->E[v][cur]) {
            suc = G->E[v][cur]->v;
	        if (G->E[v][cur]->c_f > G->E[v][cur]->f) {
                if (G->V[suc]->visited == 0) {
                    enqueue(suc);
                    G->V[suc]->visited = 1;
                    G->V[suc]->pred = G->E[v][cur];
                }
	        } cur++;
        } if (G->V[t]->visited != 0) break;
    }

    if (G->V[t]->visited == 0) { return 0; }

    path = G->V[t]->pred;
    while (path != NULL) {
        path->f++;
        path->residual->f--;
        path = G->V[path->u]->pred;
    }

    return 1;
}

int edmonds_karp(int s, int t) {
    int flow, max_flow = 0;
    do {
        init_search(t + 1);
        flow = bfs(0, t);
        max_flow += flow;
    } while (flow != 0);

    return max_flow;
}

int main() {
	int max_flow;

    G = (flow_graph *) can_fail_malloc(sizeof(flow_graph));

    int n_V = read_flow_graph();

    init_queue(n_V);

    max_flow = edmonds_karp(0, n_V - 1);
    printf("%d\n", max_flow);

    return 0;
}
