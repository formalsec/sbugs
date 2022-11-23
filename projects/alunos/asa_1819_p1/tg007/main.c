#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WHITE -1
#define GRAY 0
#define BLACK 1

typedef struct router
{
    struct router *next;
    int id;
}router;

router** G = NULL;
int* d = NULL;
int* f = NULL;
int* color = NULL;
int n;
int time_clock = 0;
int scc = 0;
int tmp_id = -1;

int* low = NULL;
int* low_tarjan = NULL;
int visited;
int* parent;
int* ap;
int* sccs;


/* typedef struct node
{
    struct node** links;
    int color;
    int d;
    int f;
}; */

int index_g(int u) {
    return u-1;
}

void DFS_Visit(int u) {
    router* v;
    tmp_id++;
    color[u] = GRAY;
    d[u] = time_clock;
    time_clock++;

    v = G[u];
    while (v != NULL) {
        if (color[index_g(v->id)] == WHITE) {
            DFS_Visit(index_g(v->id));
        }
        v = v->next;
    }
    
    color[u] = BLACK;
    f[u] = time_clock;
    time_clock++;
}

void DFS() {
    int i;  
    scc = 0;

    for (i = 0; i < n; i++) {
        if (ap[i]) color[i] = BLACK;
        else color[i] = WHITE;
        f[i] = -1;
    }

    time_clock = 1;
    for (i = 0; i < n; i++) {
        if (color[i] == WHITE) {
            tmp_id = 0;
            DFS_Visit(i);
            if (tmp_id > scc) scc = tmp_id; 
        }
    }
}

int min(int u, int v) {
    return (u < v ? u : v);
}

void Tarjan_Visit(int u) {
    router* v;
    int children = 0;
    d[index_g(u)] = low[index_g(u)] = low_tarjan[index_g(u)] = visited;
    visited++;

    v = G[index_g(u)];
    while (v != NULL) {
        if (d[index_g(v->id)] == -1) {
            parent[index_g(v->id)] = u;
            children++;
            Tarjan_Visit(v->id);
            low[index_g(u)]= min(low[index_g(u)],low[index_g(v->id)]);

            /* Checks conditions for being an articulation point */
            if (parent[index_g(u)] == -1 && children > 1) {
                ap[index_g(u)] = 1;
            }
            else if (parent[index_g(u)] != -1 && low[index_g(v->id)] >= d[index_g(u)]) {
                ap[index_g(u)] = 1;
            }
        }
        else if (v->id != parent[index_g(u)]) {
            low[index_g(u)] = min(low[index_g(u)], d[index_g(v->id)]);
        }
        low_tarjan[index_g(u)]= min(low_tarjan[index_g(u)],low_tarjan[index_g(v->id)]);

        v = v->next;
    }

    /* Gets ID of scc */
    if (u > tmp_id)
        tmp_id = u;

    if (d[index_g(u)] == low_tarjan[index_g(u)]) {
        scc++;
        sccs[index_g(tmp_id)] = tmp_id;
        tmp_id = -1;
    }
}

void SCC_Tarjan() {
    int i;
    visited = 1;

    for (i = 0; i < n; i++) {
        d[i] = -1;
        parent[i] = -1;
        ap[i] = 0;
        sccs[i] = -1;
    }

    for (i = 1; i <= n; i++) {
        if (d[index_g(i)] == -1) {
            Tarjan_Visit(i);
        }
    }
}

void insert(int u, int v) {
    router *v_router, *q;
    v_router = (router*)can_fail_malloc(sizeof(router));
    v_router->id = v;
    v_router->next = NULL;
    q = (router*)can_fail_malloc(sizeof(router));
    q->id = u;
    q->next = NULL;

    if (G[index_g(u)] == NULL) {
        G[index_g(u)] = v_router;
    } else {
        v_router->next = G[index_g(u)];
        G[index_g(u)] = v_router; 
    }

    if (G[index_g(v)] == NULL) {
        G[index_g(v)] = q;
    } else {
        q->next = G[index_g(v)];
        G[index_g(v)] = q;
    }
}

void parse_graph() {
    int i, n_edges, u, v;
    scanf("%d", &n);

    G = (router**)can_fail_malloc(sizeof(router*) * n);
    for (i = 0; i < n; i++) G[i] = NULL;

    scanf("%d", &n_edges);
    for (i = 0; i < n_edges; i++) {
        scanf("%d%d", &u, &v);
        insert(u, v);
    }
}

void free_graph() {
    int i;
    router *tmp, *head;

    for (i = 0; i < n; i++) {
        head = G[i];
        while (head != NULL){
            tmp = head;
            head = head->next;
            free(tmp);
        }
    }
    free(G);
}

int main() {
    int i, tmp;
    tmp = 0;

    parse_graph();

    d = (int*)can_fail_malloc(n * sizeof(int));
    f = (int*)can_fail_malloc(n * sizeof(int));
    low = (int*)can_fail_malloc(n * sizeof(int));
    low_tarjan = (int*)can_fail_malloc(n * sizeof(int));
    parent = (int*)can_fail_malloc(n * sizeof(int));
    ap = (int*)can_fail_malloc(n * sizeof(int));
    sccs = (int*)can_fail_malloc(n * sizeof(int));
    color = (int*)can_fail_malloc(n * sizeof(int));

    SCC_Tarjan();

    printf("%d\n", scc);

    int first = 1;
    for (i = 0; i < n; i++) {
        /* Prints ID of each scc */
        if (sccs[i] != -1) {
            printf(first ? "%d" : " %d", sccs[i]); 
            first = 0;
        }
        /* Counts number of articulation points found */ 
        if (ap[i]) 
            tmp++;
    }
    printf("\n");
    printf("%d\n", tmp);

    DFS();
    printf("%d\n", scc);
    free(d);
    free(f);
    free(low);
    free(low_tarjan);
    free(parent);
    free(ap);
    free(sccs);
    free(color);
    free_graph();

    return 0;
}


