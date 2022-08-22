
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define FALSE 0
#define TRUE 1
#define WHITE 2
#define GREY 3
#define BLACK 4

#define INDEX(id) (id - 1)

typedef struct tarjanArgs tarjanArgs;
typedef struct dfsArgs dfsArgs;
typedef struct router router;
typedef struct node *node;

struct tarjanArgs {

    router *graph;

    int tim;
    int networkId;
};

struct dfsArgs {

    router *graph;

    int nVertex;
};

struct router {
    
    char isNetworkId;
    char isBridge;

    int visitTime;
    int lowTime;
    int Pid;
    char color;

    struct node *head;
};

struct node {

    int id;
    
    struct node *next;
};

node insertList(node head, int id);
void freeList(node head);

int Tarjan(router *graph, int N);
void TarjanVisit(tarjanArgs *args, int id);
int DFS(router *graph, int N);
void DFSVisit(dfsArgs *args, int id);


int main() {

    router *network;

    int N, M, R, C, m;
    int u, v;
    int i;
    char firstCh;

    if (scanf("%d", &N) != 1) perror("scanf");
    if (scanf("%d", &M) != 1) perror("scanf");

    network = (router *)(malloc(sizeof(router) * N));

    for (i = 0; i < N; i++) {
        network[i].head = NULL;
    }

    for (i = 0; i < M; i++) {
        if (scanf("%d %d", &u, &v) != 2) perror("scanf");

        network[INDEX(u)].head = insertList(network[INDEX(u)].head, v);
        network[INDEX(v)].head = insertList(network[INDEX(v)].head, u);
    }

    R = Tarjan(network, N);

    printf("%d\n", R);

    C = 0;
    firstCh = TRUE;
    
    for (i = 0; i < N; i++) {

        if (network[i].isNetworkId) {

            if (firstCh) {
                printf("%d", i + 1);
                firstCh = !firstCh;

            } else {
                printf(" %d", i + 1);
            }
        }
        
        if (network[i].isBridge) {
            C++;
        }
    }

    m = DFS(network, N);

    printf("\n%d\n%d\n", C, m);

    for (i = 0; i < N; i++) {
        freeList(network[i].head);
    }

    free(network);

    exit(0);
}


node insertList(node head, int id) {

    node new = (node)(malloc(sizeof(struct node)));
    assert(new);

    new->id = id;
    new->next = head;

    return new;
}


void freeList(node head) {

    node i, next;
    i = head;

    while (i != NULL) {
        next = i->next;
        free(i);
        i = next;
    }
}


int Tarjan(router *graph, int N) {

    tarjanArgs args;

    int i;
    int R = 0;

    args.graph = graph;

    for (i = 0; i < N; i++) {
        graph[i].color = WHITE;
        graph[i].Pid = 0;
        graph[i].isNetworkId = FALSE;
        graph[i].isBridge = FALSE;
    }

    args.tim = 0;

    for (i = 0; i < N; i++) {

        if (graph[i].color == WHITE) {

            args.networkId = i + 1;

            TarjanVisit(&args, i + 1);

            graph[(INDEX(args.networkId))].isNetworkId = TRUE;
            R++;
        }
    }

    return R;
}


void TarjanVisit(tarjanArgs *args, int id) {
    
    node i;
    router *vertex, *adjacency;
    int nrChild = 0;

    if (id > args->networkId) {
        args->networkId = id;
    }

    vertex = &args->graph[INDEX(id)];

    args->tim++;
    vertex->color = GREY;
    vertex->visitTime = args->tim;
    vertex->lowTime = args->tim;

    for (i = vertex->head; i != NULL; i = i->next) {

        if (vertex->Pid == i->id) continue;

        adjacency = &args->graph[INDEX(i->id)];
        
        if (adjacency->color == WHITE) {

            adjacency->Pid = id;
            TarjanVisit(args, i->id);

            if (adjacency->lowTime < vertex->lowTime) {
                /* MIN */
                vertex->lowTime = adjacency->lowTime;
            }

            if (!vertex->Pid) {
                /* Independent branch */
                nrChild++;

            } else if (vertex->visitTime <= adjacency->lowTime) {
                /* Articulation Point */
                vertex->isBridge = TRUE;
            }

        } else if (adjacency->visitTime < vertex->lowTime) {
            /* MIN */
            vertex->lowTime = adjacency->visitTime;
        }
    }

    if ((!vertex->Pid) && (nrChild > 1)) {
        /* Articulation Point */
        vertex->isBridge = TRUE;
    }
}


int DFS(router *graph, int N) {

    dfsArgs args;

    int i;
    int m = 0;

    args.graph = graph;

    for (i = 0; i < N; i++) {
        graph[i].color = graph[i].isBridge ? BLACK : WHITE;
    }

    for (i = 0; i < N; i++) {

        if (graph[i].color == WHITE) {

            args.nVertex = 0;

            DFSVisit(&args, i + 1);

            if (args.nVertex > m) m = args.nVertex;
        }
    }

    return m;
}


void DFSVisit(dfsArgs *args, int id) {
    
    node i;
    router *vertex;
    
    vertex = &args->graph[INDEX(id)];

    args->nVertex++;
    vertex->color = GREY;

    for (i = vertex->head; i != NULL; i = i->next) {
        
        if (args->graph[INDEX(i->id)].color == WHITE) {

            DFSVisit(args, i->id);
        }
    }
}
