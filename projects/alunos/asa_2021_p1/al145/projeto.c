#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/*
primeiro projeto de ASA

nome:   Miguel Leonardo
numero: 92529
curso:  LEIC-A

*/

#include <stdio.h>
#include <stdlib.h>

int K, L, current_node;
/*estados possiveis dos N vertices ou nodos*/
enum color{White, Gray, Black};
/*variavel global usada para atribuir a cada vertice um discovery time (d) e um
finishing time (f) */
int time;
/*define o espaco maximo alocado aos vetores de inteiros notas (grades),
parent (p), discovery time (d) e finishing time (f)*/
int p[10000000], d[10000000], f[10000000], netedges[10000000], orphans[10000000];
/*define o espaco maximo alocado ao vetor color*/
enum color color[10000000];

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

void dfs_visit(Graph G, int u) {
    link a;
    /*atribui o estado Gray ao vertice visitado pela primeira vez e marca o
    tempo de descoberta d*/
    color[u] = Gray;d[u] = time;
    time++;
    /*explora os vetores v adjacentes a u e visita-os se forem White*/
    for (a = G->adj[u]; a != NULL; a = a->next) {
        if (color[(a->v)] == White) {
            p[(a->v)] = u;
            netedges[current_node] = netedges[current_node] + 1;
            dfs_visit(G, (a->v));
        }
    }
    /*depois de explorar todos os vertices adjacentes a u, marca-os com f e
    altera o estado para Black*/
    color[u] = Black;
    f[u] = time;
    time++;
}

void dfs(Graph G, int Array[]) {
    int u;
    /*inicializa todos os vertices a White e o vetor p*/
    for (u = 0; u < G->V; u++) {
        color[u] = White;
        p[u] = -1;
    }
    time = 1;
    /*verifica todos os vertices adjacentes a vez e inicia a funcao dfs_visit
    quando encontra um vertice sem pai*/
    for (u = 0; u < G->V; u++) {
        if(orphans[u]==1) {
            current_node=u;
            netedges[current_node] = netedges[current_node] + 1;
            dfs_visit(G, u);
        }
    }
}

/*funcao que cria e inicializa o grafo*/
Graph GRAPHinit(int V) {
    int v;
    Graph G = can_fail_malloc(sizeof(struct graph));
    G->V = V;
    G->E = 0;
    G->adj = can_fail_malloc(V * sizeof(link));
    for (v = 0; v < V; v++)
        G->adj[v] = NULL;
    return G;
}

/*funcao que insere um nodo/vertice no grafo*/
void insertE(link *head, int v) {
    link  a = (link)can_fail_malloc(sizeof(struct node));
    link last = *head;
    a->v = v;
    a->next = NULL;
    if (*head == NULL) {
       *head = a;
       return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = a;
    return;
}

/*funcao que insere uma aresta no grafo*/
void GRAPHinsertE(Graph G, int v, int w) {
   link a;
   for (a = G->adj[v]; a != NULL; a = a->next)
      if (a->v == w) return;
    insertE(&G->adj[v], w);
   G->E++;
}

void predictK(Graph G) {
    int u;
    for (u=0;u<G->V;u++)
        if (p[u]==-1)
            K = K + 1;
}

void predictL(Graph G) {
    int u;
    int max=0;
    for (u=0;u<G->V;u++)
        if(netedges[u] > max)
            max = netedges[u];
    L = max-1;
}

/*funcao que recebe as relacoes de amizade entre os alunos (arestas do grafo)*/
void getEdges(Graph G, Graph GT, int M) {
    int i, v, w;
    for (i=0;i<M;i++) {
        scanf("%d %d", &v, &w);
        GRAPHinsertE(G, v-1, w-1);
        GRAPHinsertE(GT, w-1, v-1);
    }
}

void findOrphans(Graph G) {
    int u;
    for(u=0; u<G->V; u++){
        orphans[u]=0;
    }
    for(u=0; u<G->V; u++)
        if(G->adj[u]==NULL)
            orphans[u]=1;
}

/*funcao  principal do programa*/
int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    if (N >= 2 && M >= 0) {
        /*cria grafo*/
        Graph G = GRAPHinit(N);
        /*cria grafo transposto*/
        Graph GT = GRAPHinit(N);
        getEdges(G, GT, M);
        findOrphans(GT);
        dfs(G, orphans);
        predictK(G);
        predictL(G);
        printf("%d %d\n", K, L);
    }
    return 0;
}


