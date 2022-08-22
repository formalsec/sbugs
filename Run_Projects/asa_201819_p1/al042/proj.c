#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXCARAC 80
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

/*//////////////////////////////////////////
                   Graph
//////////////////////////////////////////*/

typedef struct node *link;

struct node
{
    int v;
    link next;
};

typedef struct graph
{
    int V;
    link *adj;
} * Graph;

link ap = NULL;
Graph g;

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

link NEW(int v)
{ /* cria um novo elemento */
    link x = (link)malloc(sizeof(struct node));
    x->v = v;
    x->next = NULL;
    return x;
}


Graph GRAPHinit(int V)
{
    Graph G = malloc(sizeof(struct graph));
    G->adj = (link *)malloc(sizeof(link) * V);
    G->V = V;
    return G;
}

void GRAPHinsertE(int v1, int v2)
{
    link x;

    if (g->adj[v1] == NULL)
    {
        g->adj[v1] = NEW(v2);
    }
    else
    {
        x = g->adj[v1];
        g->adj[v1] = NEW(v2);
        g->adj[v1]->next = x;
    }
}

/*//////////////////////////////////////////
                OPEN FILE
//////////////////////////////////////////*/

void read_input()
{
    int nRouters;
    int nLigacoes;
    if (scanf("%d", &nRouters) == 0)
    {
        exit(1);
    }
    getchar();
    if (nRouters < 2) /* Erro de input no numero de routers da rede */
    {
        exit(1);
    }
    g = GRAPHinit(nRouters);
    if (scanf("%d", &nLigacoes) == 0)
    {
        exit(1);
    }
    getchar();
    for (; nLigacoes > 0; nLigacoes--)
    {
        int r1, r2;
        if (scanf("%d %d", &r1, &r2) == 0)
        {
            exit(1);
        }
        getchar();
        GRAPHinsertE(r1 - 1, r2 - 1);
        GRAPHinsertE(r2 - 1, r1 - 1);
    }
}

/*//////////////////////////////////////////
            VER SUBREDES
//////////////////////////////////////////*/

void add_ap(int v)
{
    link x;
    bool flag = false;
    if (ap == NULL)
    {
        ap = NEW(v);
    }
    else
    {
        for (x = ap; x->next != NULL; x = x->next)
        {
            if(x->v == v){
                flag = true;
            }
        }
        if(x->v == v){
            flag = true;
        }
        if (!flag){
            x->next = NEW(v);
        }
    }
}


void count_ap() /* Conta quantos aps sao e retira os do grafo */
{
    link x;
    int counter = 0;
    for (x = ap; x != NULL; x = x->next)
    {
        g->adj[x->v] = NULL;
        counter++;
    }
    printf("%d\n", counter);
}

void checkAp_aux(int node, int *visited, int *child, int *parent, int *low, int *maxR)
{
    link aux = NULL;
    static int distance = 0;
    int children = 0;
    aux = g->adj[node];
    visited[node] = 1;
    distance++;
    child[node] = low[node] = distance;
    if (node > *maxR)
        *maxR = node;

    while (aux != NULL)
    {
        if (!visited[aux->v])
        {
            children++;
            parent[aux->v] = node;
            checkAp_aux(aux->v, visited, child, parent, low, maxR);
            low[node] = MIN(low[node], low[aux->v]);
            if (parent[node] == -1 && children > 1)
            {
                add_ap(node);
            }

            if (parent[node] != -1 && child[node] <= low[aux->v])
            {
                add_ap(node);
            }
        }
        else if (aux->v != parent[node])
        {
            low[node] = MIN(low[node], child[aux->v]);
        }
        aux = aux->next;
    }
}


void checkAp(int* subredes, int* maxis)
{
    int i;
    int *child = (int *)malloc(sizeof(int) * g->V);
    int *visited = (int *)malloc(sizeof(int) * g->V);
    int *parent = (int *)malloc(sizeof(int) * g->V);
    int *low = (int *)malloc(sizeof(int) * g->V);
    int maxR, maxcounter = 0;
    for (i = 0; i < g->V; i++)
    {
        visited[i] = 0;
        parent[i] = -1;
    }
    for (i = 0; i < g->V; i++)
    {
        if (visited[i] == 0)
        {
            maxR = 0;
            *subredes = *subredes +1;
            checkAp_aux(i, visited, child, parent, low, &maxR);
            maxis[maxcounter++] = maxR;
        }
    }
}


/*//////////////////////////////////////////////////////////////*/


void checkAp_aux_final(int node, int *visited, int *child, int *parent, int *low, int *maxRoutersSub)
{
    link aux = NULL;
    static int distance = 0;
    int children = 0;
    aux = g->adj[node];
    visited[node] = 1;
    distance++;
    child[node] = low[node] = distance;
    *maxRoutersSub = *maxRoutersSub +1;

    while (aux != NULL)
    {
        if (!visited[aux->v])
        {
            children++;
            parent[aux->v] = node;
            checkAp_aux_final(aux->v, visited, child, parent, low, maxRoutersSub);
            low[node] = MIN(low[node], low[aux->v]);
        }
        else if (aux->v != parent[node])
        {
            low[node] = MIN(low[node], child[aux->v]);
        }
        aux = aux->next;
    }
}


int checkAp_final()
{
    int i;
    int *child = (int *)malloc(sizeof(int) * g->V);
    int *visited = (int *)malloc(sizeof(int) * g->V);
    int *parent = (int *)malloc(sizeof(int) * g->V);
    int *low = (int *)malloc(sizeof(int) * g->V);
    int maxRoutersSub, maxSubRede=0;
    for (i = 0; i < g->V; i++)
    {
        visited[i] = 0;
        parent[i] = -1;
    }
    for (i = 0; i < g->V; i++)
    {
        if (visited[i] == 0)
        {
            maxRoutersSub = 0;
            checkAp_aux_final(i, visited, child, parent, low, &maxRoutersSub);
            if (maxRoutersSub > maxSubRede){
                maxSubRede = maxRoutersSub;
            }
        }
    }
    return maxSubRede;
}


/*//////////////////////////////////////////////////////////////*/

void printMaxis(int* maxis){
    int i;
    qsort(maxis, g->V, sizeof(int), compare);
    for (i=0; i< g->V; i++){
        if(maxis[i] != 0){
            if (maxis[i] == g->V-1){
                printf("%d", maxis[i]+1);
            }
            else{
                printf("%d ", maxis[i]+1);
            }
        }
        if (i == g->V-1){
            printf("\n");
        }
    }
}

int main(int argc, char *argv[])
{
    int subredes = 0;
    read_input();
    int *maxis = (int*) malloc(sizeof(int)*g->V);
    checkAp(&subredes, maxis);
    printf("%d\n", subredes);
    printMaxis(maxis);
    count_ap();
    printf("%d\n", checkAp_final());
    free(maxis);
    return 0;
}