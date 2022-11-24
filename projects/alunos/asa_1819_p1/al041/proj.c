#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/* Projeto 1 - ASA 2018-19
   Antonio Lopes - 89415
   Joao Goncalves - 93918  */

#include <stdio.h>
#include <stdlib.h>

int N = 0;  /* numero de routers */
int M = 0;  /* numero de ligacoes */

typedef struct {
    int v;
    int w;
} Edge; /* estrutura auxiliar Edge (arco) */

typedef struct graph *Graph;
typedef struct node *link;

struct node {
    int v;  /* cada elemento das listas, guarda um indice de um vertice */
    link next;
};

struct graph {
    int V;  /* numero de vertices */
    int E;  /* numero de arcos */
    link *adj;  /* vetor de listas ligadas de int's */
};

int min(int a, int b) {
    return(a < b ? a : b);
}

/*--------------------------------------------------------------------
| Funcao: insertBegin
| Descricao: adiciona cada elemento ao inicio
---------------------------------------------------------------------*/
link insertBegin(int v, link head) {
    link x = can_fail_malloc(sizeof(struct node));
    x->v = v;
    x->next = head;
    return x;
} 

/*--------------------------------------------------------------------
| Funcao: insertEdge
| Descricao: adiciona um arco ao inicio da lista correspondente
---------------------------------------------------------------------*/
void insertEdge(Graph G, Edge e) {
    int v = e.v, w = e.w;
    G->adj[v] = insertBegin(w, G->adj[v]);
    G->adj[w] = insertBegin(v, G->adj[w]);
    G->E++;
}

/*--------------------------------------------------------------------
| Funcao: createEdge
| Descricao: cria um arco entre x e y
---------------------------------------------------------------------*/
Edge createEdge(int x, int y) {
    Edge e;
    e.v = x;
    e.w = y;
    return e;
}

/*--------------------------------------------------------------------
| Funcao: printGraph
| Descricao: funcao auxiliar para observacao da representacao do grafo
---------------------------------------------------------------------*/
void printGraph(Graph G) {
    int i;
    for (i = 1; i <= N; i++) {
        struct node* temp = G->adj[i];
        printf("Vertice: %d\n ", i);
        while (temp) {
            printf("%d -> ", temp->v);
            temp = temp->next;
        }
        printf("\n");
    }
}

/*--------------------------------------------------------------------
| Funcao: initializeGraph
| Descricao: inicializa o grafo reservando a memoria necessaria
---------------------------------------------------------------------*/
Graph initializeGraph(int V) {
    int v;
    Graph G = can_fail_malloc(sizeof(struct graph));
    G->V = V;
    G->E = 0;
    G->adj = can_fail_malloc((V+1) * sizeof(link));
    for (v = 0; v <= V; v++)
        G->adj[v] = NULL;
    return G;
}

/*--------------------------------------------------------------------
| Funcao: merge
| Descricao: funcao auxiliar do algoritmo de ordenacao Merge Sort
---------------------------------------------------------------------*/
void merge(int low, int mid, int high, int a[], int b[]) {
    int l1, l2, i;

    for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
        if(a[l1] <= a[l2])
            b[i] = a[l1++];
        else
            b[i] = a[l2++];
   }
   
   while(l1 <= mid)    
        b[i++] = a[l1++];

   while(l2 <= high)
        b[i++] = a[l2++];

   for(i = low; i <= high; i++)
        a[i] = b[i];
}


/*--------------------------------------------------------------------
| Funcao: mergeSort
| Descricao: funcao composta pelo algoritmo de ordenacao Merge Sort
---------------------------------------------------------------------*/
void mergeSort(int low, int high, int list[], int listSorted[]) {
    int mid;
   
    if(low < high) {
        mid = (low + high) / 2;
        mergeSort(low, mid, list, listSorted);
        mergeSort(mid+1, high, list, listSorted);
        merge(low, mid, high, list, listSorted);
    }
    else { 
        return;
    }   
}


/*--------------------------------------------------------------------
| Funcao: DFSAux
| Descricao: funcao auxiliar do algoritmo de procura Depth-First Search
---------------------------------------------------------------------*/
void DFSAux(Graph G, int v, int visited[], int des[], int parent[], int low[], int ap[], int* ID, int* count) {
    struct node* temp = NULL;
    static int time = 0;
    int children = 0;
    temp = G->adj[v];
    visited[v] = 1;
    time++;
    des[v] = low[v] = time;

    if (v > *ID)
        *ID = v;

    if (temp != NULL)
        *count = *count + 1;

    while (temp != NULL) {
        if (!visited[temp->v]) {
            children++;
            parent[temp->v] = v;
            DFSAux(G, temp->v, visited, des, parent, low, ap, ID, count);

            low[v] = min(low[v], low[temp->v]);
        
            if (parent[v] == 0 && children > 1) {
                ap[v] = 1;
            }
            
            if (parent[v] != 0 && des[v] <= low[temp->v]) {
                ap[v] = 1;
            }
        }

        else if (temp->v != parent[v]) {
            low[v] = min(low[v], des[temp->v]);
        }

        temp = temp->next;
    }
}


/*--------------------------------------------------------------------
| Funcao: DFS
| Descricao: funcao composta pelo algoritmo de procura Depth-First Search
---------------------------------------------------------------------*/
void DFS(Graph G) {
    int visited[N+1];
    int ap[N+1];
    int des[N+1];
    int ID = 0;
    int j = 0;
    int k = 0;
    int i;
    int count = 0;
    int biggestSub = 0;
    int articulationPoints = 0;
    int subNetworks = 0;
    int* low = can_fail_malloc(sizeof(int)*(N+1));
    int* parent = can_fail_malloc(sizeof(int)*(N+1));
    int* ids = can_fail_malloc(sizeof(int)*(N+1));
    int* idsSorted = can_fail_malloc(sizeof(int)*(N+1));
    int* aps = can_fail_malloc(sizeof(int)*(N+1));

    for (i = 0; i <= N; i++) {
        parent[i] = 0;
        visited[i] = 0;
        ap[i] = 0;
        ids[i] = 0;
        idsSorted[i] = 0;
        aps[i] = 0;
    }

    for (i = 1; i <= N; i++) {
        if (visited[i] == 0) {
            subNetworks++;
            DFSAux(G, i, visited, des, parent, low, ap, &ID, &count);
            ids[j] = ID;
            j++;
            ID = 0;
        }
    }
    
    for (i = 0; i <= N; i++) {
        if (ap[i] == 1) {
            aps[k] = i;
            k++;
            articulationPoints++;
        }
    }

    printf("%d\n", subNetworks);

    mergeSort(0, N, ids, idsSorted);
        
    for (i = 0; i <= N; i++) {
        if (idsSorted[i] == N)
            printf("%d", idsSorted[i]);
        else if (idsSorted[i] != 0)
            printf("%d ", idsSorted[i]);
    }

    printf("\n%d\n", articulationPoints);
    
    for (i = 0; i <= N; i++) {
        if (aps[i] != 0) {
            G->adj[aps[i]] = NULL;
        }
    }

    for (i = 0; i <= N; i++) {
        parent[i] = 0;
        visited[i] = 0;
    }

    count = 0;
    for (i = 1; i <= N; i++) {
        if (visited[i] == 0) {
            DFSAux(G, i, visited, des, parent, low, ap, &ID, &count);
            if (count > biggestSub)
                biggestSub = count;
            count = 0;
        }
    }
    
    printf("%d\n", biggestSub);

    for (i = 0; i <= N; i++)
        free(G->adj[i]);
    free(G);
    free(low);
    free(parent);
    free(ids);
    free(idsSorted);
    free(aps);
}


/*--------------------------------------------------------------------
| Funcao: main
| Descricao: entrada do programa 
---------------------------------------------------------------------*/
int main() {
    scanf("%d\n%d", &N, &M);
    Graph G = initializeGraph(N);
    int v, w;
    int i;
    for (i = 0; i < M; i++) {
        scanf ("%d %d", &v, &w);
        insertEdge(G, createEdge(v, w));
    }
    DFS(G);
    return 0;
}