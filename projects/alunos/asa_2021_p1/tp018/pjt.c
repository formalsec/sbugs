#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DIM 50

void doNot(){}

typedef struct node{
    int degree; /*Numero de nos incidentes*/
    int *adj;   /*Lista dos nodos filhos adjacentes*/
    int *adjParent; /*Lista dos nodos pais adjacentes*/
    int nEdj;       /*numero de nodos filhos*/
    int nEdjParent; /*numero de nodos pais*/
    bool vis;   /*flag que indica se o nodo ja foi visitado*/
    int maxSeq; /*caminho mais longo ate este nodo*/
    int listSize; /*dimensao da lista das adjacencias */
    int listSizeParent; /*dimensao da lista das adjacencias dos parents*/
    int maxLen;
    bool inQ;   /*flag que indica se este no esta dentro de queue de exploracao para DFS*/
} Node;

/*Nova Queue*/
struct qNode{
    int data;
    struct qNode *next;
};

struct qNode *first = NULL;
struct qNode *last = NULL;

void add(int item){
    struct qNode *elm = can_fail_malloc(sizeof(struct qNode));
    elm->data = item;
    elm->next = NULL;
    if (last == NULL){
        first = elm;
        last = elm;
    }
    else{
        last->next = elm;
        last = last->next;
    }
}

int rmv(){
        if(first != last){
        struct qNode *temp;
        temp = first;
        int temp2 = first->data;
        first = first->next;
  
        free(temp);
        return temp2;
        }
    struct qNode *temp;
    temp = first;
    int temp2 = first->data;
    first = first->next;

    free(temp);
    first = NULL;
    last = NULL;
    return temp2;        
}

int max(int a, int b){
    if(a<b) return b;
    return a;
}


            /*DFS iterativo*/
void dfSrcIt(Node nodeList[], int node){
    int s, p = 0, child;
    add(node);
    int stackSize = 1;

    while(stackSize > 0){
        s = first->data;
        if(!nodeList[s].vis){
            nodeList[s].vis=true;
            for(p=0; p<nodeList[s].nEdj; p++){
                child = nodeList[s].adj[p];
                if(!nodeList[child].vis){
                    if(!nodeList[child].inQ){

                        add(child);
                        ++stackSize; 
                        nodeList[child].inQ = true; 
                        }
                    }
                }
            }
        --stackSize;
        rmv();
    }
}

    /*Algoritmo para encontrar o caminho mais curto*/               
int longestPath(Node nodeList[], int topSort[],int nNode){
    int i, i2, n, parent, maxLen, x;
    maxLen = 0;
    for(i=0; i<nNode; i++){
        n = topSort[i];
        for(i2=0; i2<nodeList[n].nEdjParent; i2++){
            parent = nodeList[n].adjParent[i2];
            x = (nodeList[parent].maxLen+1);
            if(nodeList[n].maxLen < x) {
                nodeList[n].maxLen = x;
                if(maxLen < x)  maxLen = x;
                }
        }
    }
    return maxLen;
}


/*===========================MAIN=========================*/
int main(){
    int nNodes, nEdjes, node, edge, i, i2, nTouch, lSize, maxSub = 0;
    if(scanf("%d %d", &nNodes, &nEdjes)) doNot();

    int *topSort = (int*)can_fail_malloc((nNodes+1)*sizeof(int)); /*Lista para guardar id dos nodos segundo a sua ordenacao topologica*/
    Node *nodeList = (Node *)can_fail_malloc((nNodes+1) * sizeof(Node)); /*struct array dos nodos*/
    for(i=0; i<=nNodes; i++){
        nodeList[i].adj = can_fail_malloc(sizeof(int)* DIM);
        nodeList[i].adjParent = can_fail_malloc(sizeof(int)* DIM);
        nodeList[i].listSize = DIM;
        nodeList[i].listSizeParent = DIM;
        nodeList[i].nEdj = 0;
        nodeList[i].nEdjParent = 0;
        nodeList[i].degree = 0;
        nodeList[i].maxSeq = 0;
        nodeList[i].maxLen = 0;
        nodeList[i].vis = false;
        nodeList[i].inQ = false;
    }
    i=0;

            /*Leitura das adjacencias do ficheiro*/
    while(i<nEdjes){  
        if(scanf("%d %d", &node, &edge)) doNot();
        if((nodeList[node].listSize-2)<nodeList[node].nEdj){ /*Caso a dimensao do vetor que guarda as adjacencias seja pequena realoca-se a memoria*/
               nodeList[node].adj= can_fail_realloc(nodeList[node].adj, sizeof(int)*(nodeList[node].listSize*1.5));
            nodeList[node].listSize = (1.5*nodeList[node].listSize);
        }

        if((nodeList[edge].listSizeParent-2)<nodeList[edge].nEdjParent){ /*Caso a dimensao do vetor que guarda as adjacencias dos nodos incidentes seja pequena realoca-se a memoria*/
               nodeList[edge].adjParent= can_fail_realloc(nodeList[edge].adjParent, sizeof(int)*(nodeList[edge].listSizeParent*1.5));
            nodeList[edge].listSizeParent = (1.5*+nodeList[edge].listSizeParent);
        }

        nodeList[node].adj[nodeList[node].nEdj] = edge;
        nodeList[edge].adjParent[nodeList[edge].nEdjParent] = node;

        nodeList[node].nEdj+=1;
        nodeList[edge].nEdjParent+=1;
        nodeList[edge].degree+=1;
        i++;
    } 


   /*Inicializa tabela com elementos para topological Sort*/
    for(i2=1; i2<=nNodes; i2++){
        if(nodeList[i2].degree == 0){
                add(i2);
            }
        }

    i = 0; lSize = 0; i2 = 0; 

    /*Ordenacao topologica*/
    int child;
    while(lSize < nNodes){
        i = rmv();
        topSort[lSize] = i;
        lSize++;
        for(i2 = 0; i2 < nodeList[i].nEdj ; i2++){
            child = nodeList[i].adj[i2];
            nodeList[child].degree-=1;
            if(nodeList[child].degree == 0) add(child);
        }
    }

    /*procura DFS sobre ordem topologica dos nodo. Cada vez que for houver chamada
    do DFS incrementa-se o contador que simboliza existencia de mais uma sublista*/
    nTouch = 0;
    for(i=0; i<nNodes; i++){
        if(!nodeList[topSort[i]].vis){
            dfSrcIt(nodeList, topSort[i]);
            nTouch++;
        }
    }

    /*procura  de caminho mas longo seguindo ordenacao topologica*/
    maxSub = longestPath(nodeList, topSort, nNodes);

    printf("%d %d\n", nTouch, (maxSub+1));


    free(topSort);
    for(i=0; i<=nNodes; i++){
        free(nodeList[i].adj);
        free(nodeList[i].adjParent);
    }
    free(nodeList);
    return 0;
}