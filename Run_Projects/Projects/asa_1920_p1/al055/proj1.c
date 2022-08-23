/*      1º Projeto - ASA 2019/20
        António Lopes- 89415
        Pedro Galhardo - 89517      */

#include <stdio.h>
#include <stdlib.h>

int N = 0;                                      /* número de alunos */
int M = 0;                                      /* número de relações de amizade */

typedef struct {
    int v;
    int w;
} Edge;

typedef struct graph *Graph;
typedef struct node *link;

struct node {
    int v;                                      /* cada elemento das listas, guarda um índice de um vertice */
    link next;
};

struct graph {
    int V;                                      /* número de vértices (vertexes) */
    int E;                                      /* número de arcos (edges) */
    int* visited;
	int* closed;
	int* grades;
    link* adj;                                  /* vetor de listas ligadas de inteiros */
};

/*--------------------------------------------------------------------
| Função: maximum
| Descrição: função auxiliar para extrair o máximo entre dois inteiros
---------------------------------------------------------------------*/
int maximum(int a, int b) {
    return(a > b ? a : b);
}

/*--------------------------------------------------------------------
| Função: printGraph
| Descrição: função auxiliar para observação da representação do grafo
---------------------------------------------------------------------*/
void printGraph(Graph G) {
    int i;
    for (i = 1; i <= N; i++) {
        struct node* temp = G->adj[i];
        printf("Vertex: %d\n ", i);
        while (temp) {
            printf("%d -> ", temp->v);
            temp = temp->next;
        }
        printf("\n");
    }
}

/*--------------------------------------------------------------------
| Função: insertBegin
| Descrição: adiciona cada elemento ao início
---------------------------------------------------------------------*/
link insertBegin(int v, link head) {
    link x = malloc(sizeof(struct node));
    x->v = v;
    x->next = head;
    return x;
} 

/*--------------------------------------------------------------------
| Função: insertEdge
| Descrição: adiciona um arco ao início da lista correspondente
---------------------------------------------------------------------*/
void insertEdge(Graph G, Edge e) {
    int v = e.v, w = e.w;
    G->adj[v] = insertBegin(w, G->adj[v]);
    G->E++;
}

/*--------------------------------------------------------------------
| Função: createEdge
| Descrição: cria um arco entre x e y
---------------------------------------------------------------------*/
Edge createEdge(int x, int y) {
    Edge e;
    e.v = x;
    e.w = y;
    return e;
}

/*--------------------------------------------------------------------
| Função: initializeGraph
| Descrição: inicializa o grafo reservando a memória necessária
---------------------------------------------------------------------*/
Graph initializeGraph(int V) {
    int v;
    Graph G = malloc(sizeof(struct graph));
    G->V = V;
    G->E = 0;
    G->adj = malloc((V+2) * sizeof(link));
    G->visited = malloc((V+2) * sizeof(int));
    G->closed = malloc((V+2) * sizeof(int));
    G->grades = malloc((V+2) * sizeof(int));
    for (v = 0; v <= V+1; v++) {
        G->adj[v] = NULL;
        G->visited[v] = 0;
		G->closed[v] = 0;
		G->grades[v] = 0;
    }
    return G;
}

/*--------------------------------------------------------------------
| Função: insertGrades
| Descrição: preenchimento da lista de notas (leitura do input)
---------------------------------------------------------------------*/
void insertGrades(Graph G) {
    int i, v;
    for (i = 1; i < N+1; i++) {
        scanf("%d", &v);
        G->grades[i] = v;
    }
}

/*--------------------------------------------------------------------
| Função: insertFriends
| Descrição: inserção das relações de amizade (arcos) no grafo (leitura do input)
---------------------------------------------------------------------*/
void insertFriends(Graph G) {
    int i, v, w;
    for (i = 0; i < M; i++) {
        scanf ("%d %d", &v, &w);
        insertEdge(G, createEdge(v, w));
    }
}

/*--------------------------------------------------------------------
| Função: DFSVisit
| Descrição: utilizada para descobrir a nota máxima de um aluno específico (em caso de loop)
---------------------------------------------------------------------*/
int DFSVisit(Graph G, int v, int *visited) {
	struct node* adjList = G->adj[v];
    struct node* temp = adjList;
    int max;

   	visited[v] = 1;
    max = G->grades[v];
    
    while(temp!=NULL) {
        int connectedVertex = temp->v;
        
        if (G->closed[connectedVertex] == 1) {
        	max = maximum(max, G->grades[connectedVertex]);
        }

		else if (visited[connectedVertex] == 0) {
			max = maximum(max, DFSVisit(G, connectedVertex, visited));
        }

        temp = temp->next;
    }
	
	return max; 
}

/*--------------------------------------------------------------------
| Função: DFS
| Descrição: algoritmo DFS implementado recursivamente
---------------------------------------------------------------------*/
int DFS(Graph G, int v) {
    struct node* adjList = G->adj[v];
    struct node* temp = adjList;
	int i, max;

    G->visited[v] = 1;
    max = G->grades[v];
    
    while(temp!=NULL) {
        int connectedVertex = temp->v;
		if (G->visited[connectedVertex] == 0) {   
			max = maximum(max, DFS(G, connectedVertex));

        }
		else if (G->closed[connectedVertex] == 1) { 
			max = maximum(max, G->grades[connectedVertex]);
		}	
		else { 
			int* visitedAux;
			visitedAux = malloc((N+2) * sizeof(int));
 
			for (i=1; i<N+1;i++) {
				visitedAux[i] = 0;
			}    
			max = DFSVisit(G, v, visitedAux);
			free(visitedAux);
			
		}
        temp = temp->next;
    }
	
	G->grades[v] = max;
	G->closed[v] = 1;
	return max;
}

/*--------------------------------------------------------------------
| Função: printGrades
| Descrição: impressão do output no formato pedido
---------------------------------------------------------------------*/
void printGrades(Graph G) {
	int i;
	for (i = 1; i < N+1; i++) {
        printf("%d\n", G->grades[i]);
    }
}

/*--------------------------------------------------------------------
| Função: freeGraph
| Descrição: limpeza do grafo
---------------------------------------------------------------------*/
void freeGraph(Graph G) {
    free(G->adj);
    free(G->visited);
    free(G->closed);
    free(G->grades);
    free(G);
}

/*--------------------------------------------------------------------
| Funcao: main
| Descricao: entrada do programa 
---------------------------------------------------------------------*/
int main() {
    int i;
    Graph G;

    scanf("%d,%d", &N, &M);
    G = initializeGraph(N);
    insertGrades(G);
    insertFriends(G);

    for (i = 1; i < N+1; i++) {
        if (G->visited[i] == 0)
        	DFS(G, i);
    }

    printGrades(G);
    freeGraph(G);

    return 0;
}