#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/*                                                                       */
/*                ANALISE E SINTESE DE ALGORITMOS 2018/19                */
/*                          2o PROJETO – TG003                           */
/*                                                                       */
/*                         GONCALO GUERRA, 83899                         */
/*                         FILIPE COLACO, 84715                          */
/*                                                                       */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 1048576
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define NORMAL 0
#define STORAGE 1
#define MANUF 2
#define BACKWARDS 3
#define B_STORAGE 4
#define B_MANUF 5

typedef struct node {
    long id;
    long cap;
    int type;
    struct node * next;
} *node_t;

typedef struct pair {
    int u;
    int v;
} pair;

/* FUNCTION DECLARATIONS */
void insertNode(int u, int v, int c, int type);
void printAdjacenciesList();
void initPreflow();
void Push(int u, int v);
void Relabel(int u);
int Discharge(int u);
int withExcess();
int PushRelabel();
void DFS();
void DFSvisit(int u);
void getResults();
int cmpfunc(const void *p1, const void *p2);

/* GLOBAL VARIABLES DECLARATIONS */
int numManuf,               /* number of manufacturers */
    numStora,               /* number of storage points */
    numNodes,               /* number of total nodes */
    numLinks,               /* number of edges in the graph */
    DFS_iTree = 0,          /* dictates which DFS tree the node belongs to */
    DFS_time = 1,           /* timer to use for DFS_d */
    *DFS_tree,              /* tells which tree each node belongs to */
    *DFS_color,             /* vertex color for DFS */
    *DFS_d,                 /* start time for DFS */
    *DFS_pi,                /* list of predecessors for DFS */
    *PR_h,                  /* height of each node in push-relabel */
    *PR_e,                  /* flow inside each vertex in push-relabel */
    *storaUp,               /* which storage points should be updated */
    **PR_f,                 /* flow of each edge */
    **PR_c;                 /* capacity of each edge */

node_t* linkList;           /* array of linked lists (adjacencies list) */

int main(int argc, char *argv[]) {
    int i, u, v, c;
    char buffer[BUFF_SIZE], *token;

    /* get all the quantities */
    if (fgets(buffer, BUFF_SIZE-1, stdin) == NULL) exit(1);

    token = strtok(buffer, " ");
    numManuf = atoi(token);

    token = strtok(NULL, " ");
    numStora = atoi(token);

    token = strtok(NULL, " ");
    numLinks = atoi(token);

    numNodes = numManuf + 2 * numStora + 2;

    /* initializing arrays */
    DFS_color = (int*) can_fail_malloc(numNodes * sizeof(int));
    DFS_d = (int*) can_fail_malloc(numNodes * sizeof(int));
    DFS_pi = (int*) can_fail_malloc(numNodes * sizeof(int));
    DFS_tree = (int*) can_fail_malloc(numNodes * sizeof(int));

    PR_h = (int*) can_fail_calloc(numNodes, sizeof(int));
    PR_e = (int*) can_fail_calloc(numNodes, sizeof(int));
    storaUp = (int*) can_fail_calloc(numNodes, sizeof(int));
    linkList = (node_t*) can_fail_malloc(numNodes * sizeof(struct node));

    PR_f = (int**) can_fail_malloc(numNodes * sizeof(int*));
    PR_f[0] = (int*) can_fail_calloc(numNodes * numNodes, sizeof(int));
    for (i = 1; i < numNodes; i++) PR_f[i] = PR_f[0] + i * numNodes;

    PR_c = (int**) can_fail_malloc(numNodes * sizeof(int*));
    PR_c[0] = (int*) can_fail_calloc(numNodes * numNodes, sizeof(int));
    for (i = 1; i < numNodes; i++) PR_c[i] = PR_c[0] + i * numNodes;

    /* initialize the linked list */
    for (i = 0; i <= numNodes; i++) {
        linkList[i] = NULL;
    }

    /* get the manufacturers' capacity */
    if (fgets(buffer, BUFF_SIZE-1, stdin) == NULL) exit(1);
    token = strtok(buffer, " ");

    for (i = 2; i <= numManuf + 1; i++) {
        insertNode(0, i, atoi(token), MANUF);
        insertNode(i, 0, 0, B_MANUF);

        PR_c[0][i] = atoi(token);

        token = strtok(NULL, " ");
    }

    /* get the storage points' capacity */
    if (fgets(buffer, BUFF_SIZE-1, stdin) == NULL) exit(1);
    token = strtok(buffer, " ");

    for (; i < numNodes - numStora; i++) {
        insertNode(i, i + numStora, atoi(token), STORAGE);
        insertNode(i + numStora, i, 0, B_STORAGE);
        PR_c[i][i + numStora] = atoi(token);
        token = strtok(NULL, " ");
    }

    /* gets all the links and inserts tham into linkList */
    for (i = 0; i < numLinks; i++) {
        if (fgets(buffer, BUFF_SIZE-1, stdin) == NULL) exit(1);

        token = strtok(buffer, " ");
        u = atoi(token);
        u = u > numManuf + 1 ? u + numStora : u;

        token = strtok(NULL, " ");
        v = atoi(token);

        token = strtok(NULL, " ");
        c = atoi(token);

        insertNode(u, v, c, NORMAL);
        insertNode(v, u, 0, BACKWARDS);
        PR_c[u][v] = c;
        PR_c[v][u] = 0;
    }

    printf("%d\n", PushRelabel());
    DFS();
    getResults();

    return 0;
}

/* adds a node to the beginning of the linked list */
void insertNode(int u, int v, int c, int type) {
    node_t new = (node_t) can_fail_malloc(sizeof(struct node));
    new->id = v;
    new->cap = c;
    new->type = type;
    new->next = linkList[u];
    linkList[u] = new;
}

/* prints the adjacencies list (debug only) */
void printAdjacenciesList() {
    int i;
    node_t node_i;

    for (i = 0; i < numNodes; i++) {
        printf("%d: ", i);
        node_i = linkList[i];
        while (node_i != NULL) {
            printf("%ld:%ld - ", node_i->id, node_i->cap);
            node_i = node_i->next;
        }
        printf("\n");
    }
}

/* initializes the push-relabel preflow */
void initPreflow() {
    int c, u;
    node_t node_i = linkList[0];

    PR_h[0] = numNodes;

    /* 0 initialization of h, e, f, and c done with can_fail_calloc */
    /* pushes the maximum flow through the edges flowing from the source */
    while (node_i != NULL) {
        c = node_i->cap;
        u = node_i->id;

        PR_c[u][0] = c;

        PR_f[0][u] = c;
        PR_f[u][0] = c * (-1);
        PR_e[u] = c;

        node_i = node_i->next;
    }
}

/* does the Push operation of Push-Relabel */
void Push(int u, int v) {
    int c = PR_c[u][v] - PR_f[u][v];
    int d = PR_e[u] < c ? PR_e[u] : c;

    PR_f[u][v] += d;
    PR_f[v][u] = PR_f[u][v] * (-1);

    PR_e[u] -= d;
    PR_e[v] += d;
}

/* does the Relabel operation of Push-Relabel */
void Relabel(int u) {
    int v, minH = 2 * numNodes;
    node_t node_i = linkList[u];

    while (node_i != NULL) {
        v = node_i->id;

        if (PR_h[v] < minH && PR_h[u] <= PR_h[v]) {
            minH = PR_h[v];
        }

        node_i = node_i->next;
    }

    PR_h[u] = minH + 1;
}

/* does the Discharge operation of Relabel-to-Front */
int Discharge(int u) {
    int v;
    node_t node_i = linkList[u];

    while (PR_e[u] > 0) {
        if (node_i == NULL) return -1;
        v = node_i->id;

        if (PR_h[u] > PR_h[v] && PR_c[u][v] - PR_f[u][v] > 0)  {
            Push(u, v);
        }

        node_i = node_i->next;
    }

    return 0;
}

/* searches for the next vertex with excess flow */
int withExcess() {
    int i;

    for (i = 2; i < numNodes; i++) {
        if (PR_e[i] > 0) return i;
    }

    return -1;
}

/* executes the Push-Relabel algorithm over linkList */
int PushRelabel() {
    int u;

    initPreflow();

    while ((u = withExcess()) != -1) {
        while (Discharge(u) == -1) {
            Relabel(u);
        }
    }

    return PR_e[1];
}

/* executes Depth-First Search over the adjacencies list */
void DFS() {
    int i;

    for (i = 0; i < numNodes; i++) {
        DFS_color[i] = DFS_d[i] = 0;
        DFS_pi[i] = -1;
    }

    DFSvisit(1); DFS_iTree++;

    for (i = numNodes - 1; i >= 0; i--) {
        if (DFS_color[i] == WHITE) DFSvisit(i);

        if (DFS_pi[i] == -1 && i != 1) DFS_iTree++;
    }
}

/* visits each node of a certain linked list */
void DFSvisit(int u) {
    int v;
    node_t node_i = linkList[u];

    DFS_tree[u] = DFS_iTree;
    DFS_color[u] = GRAY;
    DFS_d[u] = DFS_time++;

    while (node_i != NULL) {
        v = node_i->id;
        if (DFS_color[v] == WHITE) {

            if (PR_c[v][u] - PR_f[v][u] != 0 ) {
                DFS_pi[v] = u;
                DFSvisit(v);
            }
        }
        node_i = node_i->next;
    }

    DFS_color[u] = BLACK;
}

/* calculates all the necessary outputs */
void getResults() {
    int i = 2 + numManuf, iPair = 0;
    node_t node_i;

    pair *pairs = (pair*) can_fail_malloc(numLinks * sizeof(pair));

    for (i = 2 + numManuf; i < 2 + numManuf + numStora; i++) {
        if (DFS_tree[i + numStora] == 0 && DFS_tree[i] != 0) storaUp[i] = 1;
    }

    for (i = 0; i < numNodes; i++) {
        /* if this node belongs to the sink's DFS tree... */
        if (!DFS_tree[i]) {
            node_i = linkList[i];

            while (node_i != NULL) {
                if (DFS_tree[node_i->id] &&
                    storaUp[i] != 1 &&
                    storaUp[node_i->id] != 1 &&
                    node_i->type != MANUF &&
                    node_i->type != STORAGE &&
                    node_i->type != B_MANUF &&
                    node_i->type != B_STORAGE) {
                    pairs[iPair].u = (int) node_i->id > 1 + numManuf + numStora ? node_i->id - numStora : node_i->id;
                    pairs[iPair].v = i;
                    iPair++;
                }

                node_i = node_i->next;
            }
        }
    }

    for (i = 1; i < numNodes; i++) {
        if (storaUp[i] == 1) {
            printf("%d", i);
            break;
        }
    }

    for (i++; i < numNodes; i++) {
        if (storaUp[i] == 1) printf(" %d", i);
    }
    printf("\n");

    qsort(pairs, numLinks, sizeof(pair), cmpfunc);

    for (i = numLinks - iPair; i < numLinks; i++) printf("%d %d\n", pairs[i].u, pairs[i].v);
}

/* compare function to be used by qsort */
int cmpfunc(const void *p1, const void *p2) {
    pair a = *((pair*)p1);
    pair b = *((pair*)p2);

    if (a.u != b.u) return a.u - b.u;
    return a.v - b.v;
}