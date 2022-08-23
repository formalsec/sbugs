/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/*                                                                       */
/*                ANALISE E SINTESE DE ALGORITMOS 2018/19                */
/*                          1o PROJETO – TG003                           */
/*                                                                       */
/*                         GONCALO GUERRA, 83899                         */
/*                         FILIPE COLACO, 84715                          */
/*                                                                       */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 128
#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct node {
    long id;
    struct node * next;
} *node_t;

/* FUNCTION DECLARATIONS */
void insertNode(int u, int v);
void DFS();
void DFSvisit(int u);
void results();

/* GLOBAL VARIABLES DECLARATIONS */
int numRouters,             /* number of routers in the network */
    numLinks,               /* number of links between routers */
    numSubNetworks = 0,     /* number of sub-networks (output A) */
    numBreaks = 0,          /* number of critical vertices (output D) */
    mostVertices = 0,       /* number of vertices in the biggest sub-network */
    mostVerticesAux = 0,    /* auxiliary variable for mostVertices */
    DFS_time = 1,           /* timer to use for DFS_d and DFS_l */
    *DFS_c,                 /* if each vertex breaks a sub-network, its index will be <0 */
    *DFS_color,             /* vertex color for DFS */
    *DFS_d,                 /* start time for DFS */
    *DFS_l,                 /* low values for DFS */
    *DFS_child,             /* number of children for each vertex */
    *DFS_pi;                /* list of predecessors for DFS */

long DFS_biggestAux = 0,    /* biggest vertex id in DFS's current sub-network */
    *DFS_biggest;           /* list of biggest id in each sub-network (output B) */

node_t *linkList;           /* array of linked lists for the adjacencies list */

/* MAIN */
int main(int argc, char *argv[]) {
    int i, u, v;
    char buffer[BUFF_SIZE], *token;

    fgets(buffer, BUFF_SIZE-1, stdin);
    numRouters = atoi(buffer);

    fgets(buffer, BUFF_SIZE-1, stdin);
    numLinks = atoi(buffer);

    DFS_c = (int*) calloc((numRouters + 1), sizeof(int));
    DFS_color = (int*) malloc((numRouters + 1) * sizeof(int));
    DFS_d = (int*) malloc((numRouters + 1) * sizeof(int));
    DFS_l = (int*) malloc((numRouters + 1) * sizeof(int));
    DFS_pi = (int*) malloc((numRouters + 1) * sizeof(int));
    DFS_child = (int*) malloc((numRouters + 1) * sizeof(int));

    DFS_biggest = (long*) calloc((numRouters + 1), sizeof(long));
    
    linkList = (node_t*) malloc((numRouters + 1) * sizeof(node_t));
    for (i = 1; i <= numRouters; i++) linkList[i] = NULL;

    /* gets all the links and inserts tham into linkList */
    for (i = 1; i <= numLinks; i++) {
        fgets(buffer, BUFF_SIZE-1, stdin);

        token = strtok(buffer, " ");
        u = atoi(token);

        token = strtok(NULL, " ");
        v = atoi(token);

        insertNode(u, v);
        insertNode(v, u);
    }

    DFS();
    results();

    free(DFS_biggest);
    free(DFS_color);
    free(DFS_d);
    free(DFS_l);
    free(DFS_pi);
    free(DFS_child);
    free(DFS_c);
    free(linkList);

    return 0;
}

/* AUXILIARY FUNCTIONS */
/* inserts a new node with id = v at the start of linkList[u] */
void insertNode(int u, int v) {
    node_t new = (node_t) malloc(sizeof(struct node));
    new->id = v;
    new->next = linkList[u];
    linkList[u] = new;
}

/* executes Depth-First Search over the adjacencies list */
void DFS() {
    int i;

    /* initializes all the necessary lists to 0 */
    for (i = 1; i <= numRouters; i++) {
        DFS_color[i] = DFS_d[i] = DFS_l[i] = DFS_child[i] = 0;
        DFS_pi[i] = -1;
    }

    for (i = 1; i <= numRouters; i++) {
        if (DFS_color[i] == WHITE && DFS_c[i] != 1) DFSvisit(i);

        /* if DFSvisit returned, it didn't find another vertex to visit
           this means a tree is over, therefore a sub-network was found */
        if (DFS_pi[i] == -1) {
            /* updates the biggest number of vertices if necessary (output D) */
            mostVertices = mostVertices < mostVerticesAux ? mostVerticesAux : mostVertices;
            mostVerticesAux = 0;

            /* increments thye number of sub-networks found */
            numSubNetworks++;

            /* stores the sub-network's biggest id */
            DFS_biggest[DFS_biggestAux] = DFS_biggestAux;
            DFS_biggestAux = 0;
        }
    }
}

/* visits each node of a certain linked list */
void DFSvisit(int u) {
    int v;
    node_t node_i = linkList[u];
    DFS_biggestAux = u > DFS_biggestAux ? u : DFS_biggestAux;
    DFS_color[u] = GRAY;
    DFS_d[u] = DFS_l[u] = DFS_time++;
    DFS_child[u] = 0;
    mostVerticesAux++;

    while (node_i != NULL) {
        v = node_i->id;
        if (DFS_color[v] == WHITE) {
            DFS_pi[v] = u;
            DFS_child[u]++;

            if (DFS_c[v] != 1) DFSvisit(v);
            DFS_l[u] = DFS_l[u] < DFS_l[v] ? DFS_l[u] : DFS_l[v];

            /* tries to find out of the current vertex is critical */
            if (DFS_pi[u] == -1 && DFS_child[u] > 1) {
                if (!DFS_c[u]) numBreaks++;
                DFS_c[u] = 1;
            }

            if (DFS_pi[u] != -1 && DFS_l[v] >= DFS_d[u]) {
                if (!DFS_c[u]) numBreaks++;
                DFS_c[u] = 1;
            }
        }

        else if (DFS_pi[u] != v)
            DFS_l[u] = DFS_l[u] < DFS_d[v] ? DFS_l[u] : DFS_d[v];

        node_i = node_i->next;
    }
    DFS_color[u] = BLACK;
}

/* processes the results of the DFS and prints the output */
void results() {
    int i = 0;

    /* output A: number of sub-network */
    printf("%d\n", numSubNetworks);

    /* output B: biggert vertex index in each sub-network */
    while (!DFS_biggest[++i]);
    printf("%ld", DFS_biggest[i++]);
    for (; i<= numRouters; i++) {
        if (DFS_biggest[i]) printf(" %ld", DFS_biggest[i]);
    } printf("\n");

    /* output C: number of vertices that break the sub-network */
    printf("%d\n", numBreaks);

    /* output D: number of vertices in the biggest sub-network */
    mostVertices = 0;
    mostVerticesAux = 0;
    DFS();

    printf("%d\n", mostVertices);
}