#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/*
primeiro projeto de ASA

nome:   Miguel Leonardo
numero: 92529
curso:  LEIC-A

*/

#include <stdio.h>
#include <stdlib.h>

/*estados possiveis dos N vertices ou nodos*/
enum color{White, Gray, Black};
/*variavel global usada para atribuir a cada vertice um discovery time (d) e um
finishing time (f) */
int time;
/*define o espaco maximo alocado aos vetores de inteiros notas (grades),
parent (p), discovery time (d) e finishing time (f)*/
int grades[10000000], p[10000000], d[10000000], f[10000000];
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
            dfs_visit(G, (a->v));
        }
        /*compara (e modifica) a nota do vertice origem quando o vertice
        destino ja foi visitado*/
        if (color[(a->v)] == Black || color[(a->v)] == Gray)
            if (grades[u]<grades[(a->v)])
                grades[u]=grades[(a->v)];
    }
    /*depois de explorar todos os vertices adjacentes a u, marca-os com f e
    altera o estado para Black*/
    color[u] = Black;
    f[u] = time;
    time++;
}

void dfs(Graph G) {
    int u;
    /*inicializa todos os vertices a White e o vetor p*/
    for (u = 0; u < G->V; u++) {
        color[u] = White;
        p[u] = -1;
    }
    time = 1;
    /*verifica todos os vertices adjacentes a vez e inicia a funcao dfs_visit
    quando encontra um vertice no estado White*/
    for (u = 0; u < G->V; u++) {
        if(color[u] == White) {
            dfs_visit(G, u);
        }
    }
}

/*funcao que estima as N notas dos alunos*/
void predictGrades(Graph G) {
    int u;
    link a;
    /*implementa o algoritmo DFS*/
    dfs(G);
    /*percorre todas as arestas do grafo*/
    for (u = 0; u < G->V; u++) {
        for (a = G->adj[u]; a != NULL; a = a->next) {
            /*compara (e modifica) as notas das backward edges*/
            if ((d[a->v]<=d[u] && d[u]<f[u] && f[u]<=f[a->v]))
                if (grades[u]<grades[(a->v)])
                    grades[u]=grades[(a->v)];
            /*compara (e modifica) as notas das forward edges*/
            if ((d[u]<d[a->v] && d[u]<f[a->v] && f[a->v]<f[u]) && color[a->v]==Black)
                if (grades[u]<grades[(a->v)])
                    grades[u]=grades[(a->v)];
            /*compara (e modifica) as notas das cross edges*/
            if ((d[a->v]<f[a->v] && f[a->v]<d[u] && d[u]<f[u]))
                if (grades[u]<grades[(a->v)])
                    grades[u]=grades[(a->v)];
        }
    }
    /*compara (e modifica) as notas das N-1 arestas da Arvore de Pesquisa
    em Profundidade*/
    for (u=G->V-1;u>-1;u--)
        if (p[u]!=-1)
            if (grades[u]>grades[p[u]])
                grades[p[u]]=grades[u];
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

/*funcao que mostra as N notas no stdo*/
void printGrades(Graph G) {
    int i;
    for (i=0;i<G->V;i++) {
        printf("%d\n", grades[i]);
    }
}

/*funcao que recebe as notas dos alunos*/
void getGrades(int N) {
    int i;
    for (i=0;i<N;i++) {
        scanf("%d", &grades[i]);
    }
}

/*funcao que recebe as relacoes de amizade entre os alunos (arestas do grafo)*/
void getEdges(Graph G, int M) {
    int i, v, w;
    for (i=0;i<M;i++) {
        scanf("%d %d", &v, &w);
        GRAPHinsertE(G, v-1, w-1);
    }
}

/*funcao  principal do programa*/
int main() {
    int N, M;
    scanf("%d,%d", &N, &M);
    if (N >= 2 && M >= 1) {
        Graph G = GRAPHinit(N);
        getGrades(N);
        getEdges(G, M);
        predictGrades(G);
        printGrades(G);
    }
    return 0;
}
