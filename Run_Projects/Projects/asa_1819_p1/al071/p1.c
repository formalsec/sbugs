/**
* ********************************************
* Grupo 71, Alameda.
* Andre Gaspar, 83429 e Mathieu Correia, 85186.
* ********************************************
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))



/**
* No de uma lista de adjacencias
*/
typedef struct node {
    int destino; /* Representa a aresta do current no */
    struct node* next;
} *No;


/* Lista de adjacencias com referencia para o primeiro no*/
typedef struct list {
    No head;
} *List;


/**
* Grafo com todas as listas de adjacencias
*/
typedef struct graph {
    int vertices;
    List listas;
} *Graph;


/**
* Inicializacao de Funcoes
*/
No criaNo(int destino);
Graph criaGrafo(int vertices);
void addAresta(Graph grafo, int fonte, int destino);
void removeNo(Graph grafo, int *ap);
void DFS(Graph grafo);
int APUtil(Graph grafo, int vertice);
void DFS2(Graph grafo);
void APUtil2(Graph grafo, int vertice);
void libertar(Graph grafo);
void sort_array(int *a, size_t n);
int compare_ints(const void *p, const void *q);


/*---------------------------------------------------------GLOBAL VARIABLES--------------------------------------------------------*/
int i, j, *disc, *parent, *low, *ap, *visited, counterSubR, *ListAPConca, *listAux, counterAP, max, counterApHelper, counterVertex, maxCounterVertex, countings;


/*-----------------------------------------------------CONSTRUIR GRAFO-------------------------------------------------------------*/
/*Funcao que cria no*/
No criaNo(int destino) {
    No novoNo = (No) malloc(sizeof(struct node));
    novoNo->destino = destino;
    novoNo->next = NULL;
    return novoNo;
}


/* Funcao que cria um grafo*/
Graph criaGrafo(int vertices) {
    Graph novoGraph = (Graph) malloc(sizeof(struct graph));
    novoGraph->vertices = vertices;

    /* Aloca memoria para as listas de adjacencia do grafo */
    novoGraph->listas = (List) malloc(vertices * sizeof(struct list));

    /*  Inicializa cada lista de adjacencias como vazia */
    for (i=0; i<vertices; i++) {
        novoGraph->listas[i].head = NULL;
    }

    return novoGraph;
}


/* Funcao que adiciona uma aresta entre dois vertices*/
void addAresta(Graph grafo, int fonte, int destino) {
    destino--;
    No novoNo = criaNo(destino);

    /* Adiciona a aresta a lista de adjacencia */
    fonte--;
    novoNo->next = grafo->listas[fonte].head;
    grafo->listas[fonte].head = novoNo;
}


/*-------------------------------------------------------------QSORT------------------------------------------------------------------*/
/* Comparison function. Receives two generic (void) pointers to the items under comparison. */
int compare_ints(const void *p, const void *q) {
    int x = *(const int *)p;
    int y = *(const int *)q;

    if (x < y)
        return -1;
    else if (x > y)
        return 1;

    return 0;
}


/* Sort an array of n integers, pointed to by a. */
void sort_array(int *a, size_t n) {
    qsort(a, n, sizeof *a, &compare_ints);
}


/*-------------------------------------------------------------DFS------------------------------------------------------------------*/
void DFS(Graph grafo) { 
    int vertices = grafo->vertices;
    countings = 0;
    counterSubR = 0;
    counterAP = 0;

    ListAPConca = (int*) malloc(vertices * sizeof(int));
    visited = (int*) malloc(vertices * sizeof(int));
    disc = (int*) malloc(vertices * sizeof(int));
    low = (int*) malloc(vertices * sizeof(int));
    parent = (int*) malloc(vertices * sizeof(int));
    ap = (int*) malloc(vertices * sizeof(int));
    listAux = (int*) malloc(vertices * sizeof(int));


    /* Initializar arrays */
    for (i = 0; i < vertices; i++) 
    { 
        parent[i] = -1;
        visited[i] = 0;
        ap[i] = 0;
    } 

    /*Chama a funcao recursiva que vai achar os AP*/
    for (i = 0; i < vertices; i++){ 
        if (visited[i] == 0){
        	++counterSubR;
        	max = i;
            int id = APUtil(grafo, i);
            listAux[counterSubR - 1] = id;

        }
    }

    if(counterSubR>1) {
        sort_array(listAux, counterSubR);
	}

    sort_array(ListAPConca, counterAP);

}


/* Funcao recursiva que encontra os pontos de articulacao do grafo
	visited[] --> vertices visitados
	disc[] --> tempo de descoberta dos vertices
	parent[] --> pai do vertice 
	ap[] --> articulation points */
int APUtil(Graph grafo, int vertice) 
{ 
    static int time = 0;
  
    /* Filhos numa DFS */
    int children = 0; 
  
    visited[vertice] = 1; 
  
    disc[vertice] = low[vertice] = ++time;

    No current = grafo->listas[vertice].head;

    int destino;

    /* Percorrer todos os vertices adjacentes a este */
    while(current != NULL) {
        
        destino = current->destino; 

        if (!visited[destino]) 
        {   
            children++; 
            parent[destino] = vertice;

            max = MAX(destino, max);

            APUtil(grafo, destino);
            
  			low[vertice]  = MIN(low[vertice], low[destino]);

            /* Dois casos para vertice ser um Ap */
  
            /* vertice tem mais de um filhos e e root da DFS */
            if (parent[vertice] == -1 && children > 1 && ap[vertice]==0){
               	ap[vertice] = 1;
               	counterAP++;
                ListAPConca[countings]=vertice;
			    countings++;
  			}
            /* Caso nao seja root, entao e caso low value de um dos filhos seja menor do tempo de descoberta do vertice */
            if (parent[vertice] != -1 && low[destino] >= disc[vertice] && ap[vertice]==0){
               	ap[vertice] = 1;
                counterAP++;
                ListAPConca[countings]=vertice;
			    countings++;
            }
        } 
          
        else if (destino != parent[vertice]){
            low[vertice]  = MIN(low[vertice], disc[destino]); 
        }

		current = current->next;

    }
    return max;
} 


void DFS2(Graph grafo) { 
    int vertices = grafo->vertices;
    maxCounterVertex = 0;
    visited = (int*) malloc(vertices * sizeof(int));
    int counter_ap_aux = 0;

    /* Initializar arrays*/
    for (i = 0; i < vertices; i++) {
        if(ListAPConca[counter_ap_aux]==i) {
            visited[i] = 1;
            counter_ap_aux++;
            continue;
        }
        visited[i] = 0; 
    } 

	for (i = 0; i < vertices; i++){
	    if (visited[i] == 0){
	       	counterVertex = 0;
	        APUtil2(grafo, i);
	    }
   	}
}


void APUtil2(Graph grafo, int vertice) 
{ 
    visited[vertice] = 1; 
  
    No current = grafo->listas[vertice].head;
    counterVertex++;

    int destino;

    while(current != NULL) {        
        destino = current->destino;
        if (!visited[destino]){
            APUtil2(grafo, destino);
        }
		current = current->next;

    }
    maxCounterVertex = MAX(counterVertex, maxCounterVertex);
}


/*-------------------------------------------------LIBERTAR MEMORIA-----------------------------------------------------------*/
void libertar(Graph grafo) {
    No head;
    free(visited);
    free(disc);
    free(low);
    free(parent);
    free(ap);
    free(listAux);
    for (i=0; i<grafo->vertices; i++) {
        head = grafo->listas[i].head;
        while(head != NULL) {
            No temp = head;
            head = head->next;
            free(temp);
        }
    }
    free(grafo->listas);
    free(grafo);

}


/*-------------------------------------------------------MAIN----------------------------------------------------------------*/
int main(int argc, const char * argv[]) {
    int vertices, arestas;

    scanf("%d", &vertices);
    Graph grafo = criaGrafo(vertices);

    scanf("%d", &arestas);

    int ligacoes[arestas][2];
    for (i = 0; i < arestas; i++) {
        if (scanf("%d %d", &ligacoes[i][0], &ligacoes[i][1]) == EOF) {
            printf("Incoerente\n");
            libertar(grafo);
            exit(0);
        }
        addAresta(grafo,ligacoes[i][0],ligacoes[i][1]);
        addAresta(grafo,ligacoes[i][1],ligacoes[i][0]);
    }

  	DFS(grafo);

  	printf("%d\n", counterSubR);
	for (i = 0; i < counterSubR - 1; i++) 
        printf("%d ", listAux[i] + 1);
   	printf("%d\n", listAux[i]+1);
    printf("%d\n", counterAP);

  	DFS2(grafo);

  	printf("%d\n", maxCounterVertex);
    
    libertar(grafo);

    return 0;
}
