/*
 main.c
 Grafos
 
 criado by Marc Jelkic n 84741 and Andre Santos n 84699 on 09/03/2019.
 Grupo tg009
 */

#include <stdio.h>
#include <stdlib.h>

int vertMax = 0;
int contNumSub;


/* ESTRUTURAS */
struct AdjListVertice {
    int vertice;
    struct AdjListVertice* next;
};

struct AdjListHead {
    struct AdjListVertice* head;
};

struct Grafo {
    int numVertices;
    int numLigacoes;
    int numMaxSub;
    int* vertMaxArray;
    int* visited;
    int* ap;
    int numAP;
    struct AdjListHead* array;
};

struct AdjListVertice* newAdjListVertice(int vertice) {
    
    struct AdjListVertice* new = (struct AdjListVertice*)malloc(sizeof(struct AdjListVertice));
    
    new->vertice = vertice;
    new->next = NULL;
    
    return new;
}


/* Funcoes Grafo */
struct Grafo* criaGrafo(int v, int t) {
    
    struct Grafo* Grafo = (struct Grafo*)malloc(sizeof(struct Grafo));
    Grafo -> array = (struct AdjListHead*)malloc(sizeof(struct AdjListHead)*v);
    Grafo -> visited = (int*) malloc(sizeof(int) * v);
    Grafo -> ap = (int*) malloc(sizeof(int) * v);
    Grafo -> numVertices = v;
    Grafo -> numLigacoes = t;
    Grafo -> numAP = 0;
    Grafo -> numMaxSub = 0;
    
    int i;
    for(i = 0; i < v; i++) {
        Grafo -> array[i].head = NULL;
        Grafo -> visited[i] = 0;
    }
    
    return Grafo;
}

void addArco(struct Grafo* Grafo, int src, int vertice)
{
    struct AdjListVertice* newNode = newAdjListVertice(vertice);
    newNode->next = Grafo->array[src].head;
    Grafo->array[src].head = newNode;
    
    newNode = newAdjListVertice(src);
    newNode->next = Grafo->array[vertice].head;
    Grafo->array[vertice].head = newNode;
}


/* PRINT PARA TESTES */
void printGrafo(struct Grafo* Grafo)
{
    int v;
    for(v = 0; v < Grafo->numVertices; v++)
    {
        /* Teste */
        printf("Grafo -> visited[%d] = %d\n", v, Grafo -> visited[v]);
        
        struct AdjListVertice* head = Grafo->array[v].head;
        printf("Lista de adjacencias do vertice %d\nhead",v);
        while(head)
        {
            printf("-> %d",head->vertice);
            head = head->next;
        }
        printf("\n");
    }
}


/* FUNCOES AUXILIARES */
int min(int a,int b) {
    return(a<b?a:b);
}


/* Tarjan Algorithm */
void apUtil(struct Grafo* grafo, int vertice, int* visitado, int* des, int* pai, int* low) {
    
    static int time=0;
    int children=0;
    
    struct AdjListVertice* node = NULL;
    node = grafo->array[vertice].head;
    
    visitado[vertice] = 1;
    time++;
    des[vertice]=low[vertice]=time;
    
    while(node!=NULL) {
        
        
        if(!visitado[node->vertice]) {
            
            children++;
            pai[node->vertice]=vertice;
            apUtil(grafo, node->vertice, visitado, des, pai, low);
            
            low[vertice]= min(low[vertice],low[node->vertice]);
            
            if(pai[vertice]==-1 && children>1)
                grafo->ap[vertice]=1;
            
            if(pai[vertice]!=-1 && des[vertice]<=low[node->vertice])
                grafo->ap[vertice]=1;
        }
        
        else if(node->vertice!=pai[vertice]) {
            
            low[vertice]=min(low[vertice],des[node->vertice]);
        }
        
        node = node->next;
        
    }
}

void AP(struct Grafo* grafo)
{
    int i;
    int* des = (int*) malloc(sizeof(int) * grafo->numVertices);
    int* visitado = (int*) malloc(sizeof(int) * grafo->numVertices);
    int* pai = (int*) malloc(sizeof(int) * grafo->numVertices);
    int* low = (int*) malloc(sizeof(int) * grafo->numVertices);
    
    for(i=0; i<grafo->numVertices; i++){
        visitado[i]=0;
        pai[i]=-1;
        grafo->ap[i]=0;
    }
    for(i=0; i<grafo->numVertices; i++)
    {
        if(visitado[i]==0)
        {
            apUtil(grafo, i, visitado, des, pai, low);
        }
    }
    
    for(i=0; i < grafo->numVertices; i++) {
        if(grafo->ap[i]==1) {
            grafo->numAP++;
        }
    }
}


/* DFS */
void DFS (struct Grafo* grafo, int v, int contSub) {
    grafo->visited[v] = 1;
    
    if(grafo -> array[v].head == NULL) {
        grafo->vertMaxArray[contSub-1] = v+1;
    }
    
    struct AdjListVertice* AdjListAux = grafo -> array[v].head;
    
    while(AdjListAux != NULL) {
        int verticeAux = AdjListAux -> vertice;
        if (grafo -> visited[verticeAux] == 0) {
            if(grafo->ap[verticeAux]!=1){
                if(vertMax<verticeAux+1){
                    grafo->vertMaxArray[contSub-1] = verticeAux+1;
                    vertMax = verticeAux+1;
                }
                contNumSub++;
                DFS(grafo, verticeAux, contSub);
            }
            else
                break;
        }
        AdjListAux = AdjListAux -> next;
    }
}


/* QuickSort */
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int* arr, int low, int high){
    int j;
    int pivot = arr[high];
    int i = (low - 1);
    
    for (j = low; j <= high- 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int* arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


/* inputs */
int getnVertices(){
    int v;
    scanf("%d", &v);
    if(v<2){
        exit(1);
    }
    return v;
}

int getnLigacoes(){
    int l;
    scanf("%d", &l);
    if(l<1){
        exit(1);
    }
    return l;
}

void vertLigados(struct Grafo* newGrafo){
    int v1, v2;
    scanf("%d%d", &v1, &v2);
    v1--;
    v2--;
    addArco(newGrafo, v1, v2);
}


/* MAIN */
int main(int argc, const char * argv[]) {
    int i, j, k;
    int contSub = 0; /* Numero de subgrafos */
    int nVertices = getnVertices();
    int nLigacoes = getnLigacoes();
    
    struct Grafo* newGrafo = criaGrafo(nVertices, nLigacoes);
    
    for(i=0; i<nLigacoes; i++){
        vertLigados(newGrafo);
    }
    
    /* DFS para cada subgrafo */
    for (i = 0; i < nVertices; i++) {
        if (newGrafo -> visited[i] == 0) {
            contSub++;
            newGrafo -> vertMaxArray = realloc(newGrafo->vertMaxArray, contSub*(sizeof(int)));
            DFS(newGrafo, i, contSub);
            vertMax=0;
        }
    }
    printf("%d\n", contSub);
    
    quickSort(newGrafo->vertMaxArray, 0, contSub-1);
    
    for(j=0; j<contSub-1; j++){
        printf("%d ", newGrafo->vertMaxArray[j]);
    }
    printf("%d\n", newGrafo->vertMaxArray[contSub-1]);
    AP(newGrafo);
    printf("%d\n", newGrafo->numAP);
    
    contSub = 0;
    for(j=0; j < nVertices; j++) {
        newGrafo -> visited[j] = 0;
    }
    
    for (k = 0; k < nVertices; k++) {
        if (newGrafo -> visited[k] == 0) {
            contNumSub = 0;
            contSub++;
            DFS(newGrafo, k, contSub);
        }
        if(newGrafo->numMaxSub<contNumSub){
            newGrafo->numMaxSub = contNumSub;
        }
    }
    printf("%d\n", newGrafo->numMaxSub+1);
    return 0;
}
