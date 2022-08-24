/*  
    grupo al111
    Aldo Cachudo ist189402 
    Projeto 1 ASA 2020-2021 2o. Semestre
*/

#include <stdio.h>
#include <stdlib.h>
 
/*  estrutura para no' de uma lista de adjacencias*/
struct AdjListNode
{
    int dest;
    struct AdjListNode* next;
};
 
/*  estrutura para lista de adjacencias*/
struct AdjList
{
    struct AdjListNode *head;
};
 
/*  
    estrutur para grafo. um grafo e' um array
    de listas de adjacencias
    tamanho do array e' V - nr. de vertices do
    grafo
*/
struct Graph
{
    int V;
    struct AdjList* array;
};
 
/*  cria novo no' para uma lista de adjacencia*/
struct AdjListNode* newAdjListNode(int dest)
{
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}
 
/* cria grafo com V vertices*/
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
 
    /*
        cria array de listas de adjacencias.
        tamanho do array e' V
    */
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
 
    /*  inicializa cada lista*/
    int i;
    for (i = 1; i < V; ++i)
        graph->array[i].head = NULL;
 
    return graph;
}
 
/*  adiciona aresta ao grafo*/
void addEdge(struct Graph* graph, int src, int dest)
{
    /*
        adiciona aresta de src para dest
        adiciona novo no' ao inicio
        da lista de adjacencias de src.
    */
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

int main()
{
    int i;
    int v = 0;
    int e = 0;
    int outD = 0;
    int inD = 0;
    int minTouchesReq = 0;
    int * discovery;
    struct Graph* graph;
    struct AdjListNode* pCrawl;

    if(scanf("%d %d", &v, &e)){
        graph = createGraph(++v);
        discovery = malloc(sizeof(int)*(v));
        for (i=1; i < v; i++)
            discovery[i] = 0;
    }
    else return 1;

    while(e){
        if(scanf("%d %d", &outD, &inD)){
            addEdge(graph, outD, inD);
            discovery[inD] = 1;
            e--;
        }
        else return 1;
    }

    int time, maxTime;
    for (time = 0; time < v-1; time++){
        for( i= 1; i < v; i++){
            if(discovery[i] == time){
                pCrawl = graph->array[i].head;
                while (pCrawl){
                    if(discovery[pCrawl->dest] < time+1) discovery[pCrawl->dest] = time + 1;
                    pCrawl = pCrawl->next;
                }
            }
        }
    }

    maxTime = 0;
    for (i = 1; i < v; i++){
        if(discovery[i] == 0) minTouchesReq++;
        if(discovery[i] > maxTime) maxTime = discovery[i];
    }

    printf("%d %d\n", minTouchesReq, maxTime+1);

    free(discovery);

    return 0;
}