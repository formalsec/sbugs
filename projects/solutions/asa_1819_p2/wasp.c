#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <wasp.h>

#define FALSE 0
#define TRUE 1

#define TARGET 0
#define HIPER 1

typedef struct arc arc;

struct arc {
    int destination;
    int capacity;
    int flow;

    arc* dual;
};

int f; /* Numero de fornecedores */
int e; /* Numero de estacoes de abastecimento */
int t; /* Numero de ligacoes */
int V; /* Numero total de Nos */

int f_start, f_end;
int e_start, e_end;

/* LIST DEFINITION SECTION */

#define LIST_ALLOC_STEP 1000

typedef struct arcList {
    int alloc_size;
    int size;
    arc* l;
} arcList;

int abs(int x) {
    if (x < 0) return -x;
    return x;
}

void addArc(int source, int destination, int capacity);

typedef struct pArcList {
    int alloc_size;
    int size;
    arc** l;
} pArcList;

void pArcList_add(pArcList* list, arc* arc1);

arcList* adj;

/* END LIST DEFINITION SECTION*/

/*DFS*/

#define WHITE 0
#define GREY 1

#define NONE -1

int* dfs_nodes;

/* END DFS*/

void Sort_Quick_Vector(int* v, int size);

void FordFulkersonAndCut();

void PrintAdjGraph();

void PrintAdjGraphErrors();

void printCut(const int* cut);

int main() {

    int i;

    f = __WASP_symb_int("f");
    e = __WASP_symb_int("e");
    t = __WASP_symb_int("t");

    V = 2 + f + (e * 2);
    adj = calloc((size_t) V, sizeof(arcList));
    dfs_nodes = calloc((size_t) V, sizeof(int));
    for (i = 0; i < V; ++i) {
        adj[i].l = calloc(LIST_ALLOC_STEP, sizeof(arc));
        adj[i].alloc_size = LIST_ALLOC_STEP;
        adj[i].size = 0;
    }

    f_start = 2;
    f_end = e_start = f_start + f;
    e_end = e_start + (e * 2);

    for (i = f_start; i < f_end; ++i) {
        int producao = 0;
        producao = __WASP_symb_int("producao");

        addArc(i, TARGET, producao);
    }

    for (i = e_start; i < e_start + e; ++i) {
        int capacidade = 0;
        capacidade = __WASP_symb_int("capacidade");

        addArc(i + e, i, capacidade);
    }

    for (i = 0; i < t; ++i) {
        int o; /* Origem */
        int d; /* Destino */
        int c; /* Capacidade */

        o = __WASP_symb_int("o");
        d = __WASP_symb_int("d");
        c = __WASP_symb_int("c");

        if (o >= e_start && o < e_start + e) {
            o += e;
        }
        addArc(d, o, c);
    }

    FordFulkersonAndCut();

    for (i = 0; i < V; ++i) {
        free(adj[i].l);
    }
    free(adj);

    return 0;
}

void pArcList_add(pArcList* list, arc* arc1) {
    int alloc_size;

    list->size = list->size + 1;
    alloc_size = list->alloc_size;
    if (list->size > alloc_size) {
        list->alloc_size = alloc_size * 2;
        list->l = realloc(list->l,
                          (size_t) list->alloc_size * sizeof(arc*));
    }

    list->l[list->size - 1] = arc1;
}

arc* addArcSingle(int source, int destination, int capacity, arc* dual) {
    int alloc_size;
    arc* arc1;

    adj[source].size = adj[source].size + 1;
    alloc_size = adj[source].alloc_size;
    if (adj[source].size > alloc_size) {
        adj[source].alloc_size = alloc_size * 2;
        adj[source].l = realloc(adj[source].l,
                                (size_t) adj[source].alloc_size * sizeof(arc));
    }

    arc1 = &(adj[source].l[adj[source].size - 1]);
    arc1->destination = destination;
    arc1->capacity = capacity;
    arc1->flow = 0;
    if (dual == NULL) {
        arc1->dual = NULL;
    } else {
        arc1->dual = dual;
        dual->dual = arc1;
    }
    return arc1;
}

void addArc(int source, int destination, int capacity) {
    arc* dual = addArcSingle(source, destination, capacity, NULL);
    addArcSingle(destination, source, -capacity, dual);
}

void addFlowSingle(arc* arc, int flow) {
    arc->flow += flow;
}

void addFlow(arc* arc, int flow) {
    addFlowSingle(arc, flow);
    if (arc->dual != NULL) {
        addFlowSingle(arc->dual, -flow);
    }
}

char calculateCut = FALSE;

char dfs_visit(int u, pArcList* path, int* maxFlow) {
    int i, v, flow;

    if (u == TARGET) {
        return TRUE;
    }

    dfs_nodes[u] = GREY;
    for (i = 0; i < adj[u].size; ++i) {
        arc* arc1 = &adj[u].l[i];


        if (arc1->capacity < 0) {
            if (arc1->flow == 0) {
                continue;
            }
            flow = abs(arc1->flow);
        } else {
            flow = abs(arc1->capacity - arc1->flow);
            if (flow == 0) {
                continue;
            }
        }

        v = adj[u].l[i].destination;

        if (calculateCut) pArcList_add(path, arc1);

        if (dfs_nodes[v] == WHITE) {

            if (dfs_visit(v, path, maxFlow)) {
                if (*maxFlow > flow) *maxFlow = flow;
                if (!calculateCut) pArcList_add(path, arc1);
                return TRUE;
            }
        }
    }
    return FALSE;
}

char dfs(pArcList* path, int* maxFlow) {
    int i;
    *maxFlow = INT_MAX;
    path->size = 0;

    for (i = 0; i < V; ++i) {
        dfs_nodes[i] = WHITE;
    }

    return dfs_visit(HIPER, path, maxFlow);
}

int FordFulkerson(pArcList* path) {
    int i;
    int maxFlow = 0, totalMaxFlow = 0;
    while (dfs(path, &maxFlow)) {
        for (i = 0; i < path->size; ++i) {
            addFlow(path->l[i], maxFlow);
        }
        totalMaxFlow += maxFlow;
    }

    return totalMaxFlow;
}

void FordFulkersonAndCut() {
    int i, j, l, maxFlow, tempFlow, * cut, * arcAdj, arcAdj_count, dest, source;
    char addSpace;

    pArcList path;
    path.alloc_size = LIST_ALLOC_STEP;
    path.size = 0;
    path.l = calloc(path.alloc_size, sizeof(arc*));

    maxFlow = FordFulkerson(&path);

    /* Run an extra DFS to see what nodes are reached*/
    /*they path traveled is stored in `path`*/
    tempFlow = maxFlow;
    calculateCut = TRUE;
    dfs(&path, &tempFlow);

    /*Build an boolean array that tells what nodes belong to the cut*/
    /*Travel each arc and toggle the nodes visited.*/
    cut = calloc(V, sizeof(int));
    for (i = 0; i < V; ++i) {
        cut[i] = FALSE;
    }
    cut[HIPER] = TRUE;
    for (i = 0; i < path.size; ++i) {
        arc* arc1 = path.l[i];
        cut[arc1->destination] = TRUE;
    }

/*###############   PRINT   ##################*/
    printf("%d\n", maxFlow);

    addSpace = FALSE;
    for (i = e_start; i < e_start + e; ++i) {
        if ((cut[i] && !cut[i + e]) || (!cut[i] && cut[i + e])) {
            if (addSpace) printf(" ");
            printf("%d", i);
            addSpace = TRUE;
        }
    }
    printf("\n");

    /* For each node in the cut, check arc going out of the cut, those are the one that should be improved
     i = 1 - ignore the end node 0
     i < e_start + e - this makes the algorithm ignore the nodes connecting the stations (optimization) */
    for (i = 1; i < e_end; ++i) {
        if (cut[i]) continue;

        arcAdj = calloc(adj[i].size, sizeof(int));
        arcAdj_count = 0;

        for (j = 0; j < adj[i].size; ++j) {
            arc* adj1 = &adj[i].l[j];
            dest = adj1->destination;

            if (!cut[dest]) continue;
            if (dest == TARGET) continue;
            if (adj1->capacity > 0) continue;
            if (adj1->capacity != adj1->flow) continue;

            if (dest >= e_start + e && dest < e_end &&
                i >= e_start && i < e_start + e)
                continue;

            if (dest >= e_start + e && dest < e_end) dest -= e;
            arcAdj[arcAdj_count++] = dest;
        }

        Sort_Quick_Vector(arcAdj, arcAdj_count);
        source = i;
        if (source >= e_start + e && source < e_end) source -= e;
        for (l = 0; l < arcAdj_count; ++l) {
            printf("%d %d\n", source, arcAdj[l]);
        }

        free(arcAdj);
    }

    free(path.l);
    free(cut);
}

/*DEBUG PRINTING*/

void PrintAdjGraph() {
    int i, j;
    for (i = 0; i < V; ++i) {
        printf("Node %d Connects to %d other nodes\n", i, adj[i].size);
        for (j = 0; j < adj[i].size; ++j) {
            arc* arc1 = &(adj[i].l[j]);
            printf("\t(%d) -- [%d/%d] --> (%d)", i, arc1->flow,
                   arc1->capacity, arc1->destination);
        }
        printf("\n");
    }
}

void printCut(const int* cut) {
    int i;
    for (i = 0; i < V; ++i) {
        printf("%d ", i);
    }
    printf("\n");
    for (i = 0; i < V; ++i) {
        printf("%d ", cut[i]);
    }
    printf("\n");
}

void PrintAdjGraphErrors() {
    int i, j;
    for (i = 0; i < V; ++i) {
        for (j = 0; j < adj[i].size; ++j) {
            arc* arc1 = &(adj[i].l[j]);

            if (arc1->capacity < 0 && arc1->flow > 0) {
                printf("\t(%d) -- [%d/%d] --> (%d) - Negative Capacity but Positive Flow\n", i,
                       arc1->flow,
                       arc1->capacity, arc1->destination);
            }
            if (arc1->capacity > 0 && arc1->flow < 0) {
                printf("\t(%d) -- [%d/%d] --> (%d) - Positive Capacity but Negative Flow\n", i,
                       arc1->flow,
                       arc1->capacity, arc1->destination);
            }
            if (arc1->capacity < arc1->flow && arc1->capacity > 0) {
                printf("\t(%d) -- [%d/%d] --> (%d) - Flow Overflow with Positive Capacity\n", i,
                       arc1->flow,
                       arc1->capacity, arc1->destination);
            }
            if (arc1->capacity > arc1->flow && arc1->capacity < 0) {
                printf("\t(%d) -- [%d/%d] --> (%d) - Flow Overflow with Negative Capacity\n", i,
                       arc1->flow,
                       arc1->capacity, arc1->destination);
            }

        }
    }
}

/*SORTING*/

int
Quick_Partition(int* v, int l, int r) {
    int i = (int) l - 1, t;
    int j = r;
    int value = v[r];
    while (i < (int) j) {
        while (v[++i] < value);
        while (value < v[--j])
            if (j == l)
                break;
        if (i < (int) j) {
            t = v[i];
            v[i] = v[j];
            v[j] = t;
        }
    }
    t = v[i];
    v[i] = v[r];
    v[r] = t;

    return i;
}

void Sort_Quick_Vector_Range(int* v, int l, int r) {
    int i;
    if (l > r) return;
    if (r <= l) return;
    i = Quick_Partition(v, l, r);
    Sort_Quick_Vector_Range(v, l, i - 1);
    Sort_Quick_Vector_Range(v, i + 1, r);
}

void Sort_Quick_Vector(int* v, int size) {
    if (size <= 0) return;
    Sort_Quick_Vector_Range(v, 0, size - 1);
}
