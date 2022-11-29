#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int fifoSize = 0;

/*Array serve para guardar por ordem elementos que foram retirados*/
int *array;
int narr = 0;

typedef struct node{
    int id;
    int h;
    int e;
    int nViz;  
    int *viz;   

}Node;

typedef struct pipe{
    int act;
    int max;
} Pipe;


/*Nova Queue*/
struct qNode{
    int data;
    struct qNode *next;
};

struct qNode *first = NULL;
struct qNode *last = NULL;


/*add - adiciona elementos no fim da queue eunquanto add2 adiciona no inicio da queue*/
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


void add2(int item){ /*para adicionar no inicio*/

    struct qNode *elm = can_fail_malloc(sizeof(struct qNode));
    elm->data = item;
    elm->next = NULL;
    if (last == NULL){
       
        first = elm;
        last = elm;
    }
    else{
         elm->next = first;
         first = elm;
    }
}


/*remove e retorna primeiro elemento da minha queue*/
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

/*retorna numero de elementos na queue*/
int getSize(){
    return fifoSize;
}

int gmin(int a, int b){
    if(a<b) return a;
    return b;
}

void initPreF(Node *nodes, Pipe ** pipes, int nNodes){
    int x, Sn=0, f; 
    for(x=1;x<=nNodes; x++){
        f=pipes[Sn][x].max;
        pipes[Sn][x].act = f;
        nodes[x].e = f;
        nodes[Sn].e-=f;
        add(x);
    }
}

void Push(Node *nodos, Pipe **pipes, int u, int v){ /* u-de v-para*/

    int flow;
    flow = gmin(nodos[u].e, pipes[u][v].max - pipes[u][v].act);
    nodos[u].e-=flow;
    nodos[v].e+=flow;

    pipes[u][v].act+=flow;
    pipes[v][u].act-=flow;
    
}

void Relabel(Node *nodos, Pipe **pipes, int nodo, int minH){
    nodos[nodo].h+=(minH);
}

/*retorna altura minima possivel para incremento da altura atual do elemento
com excesso de flow*/
int getMinH(Node *nodos, Pipe **pipes, int nodo, int pmh){
    int minH = nodos[0].h;
    int i;
    for(i=0; i < nodos[nodo].nViz; i++){
                if(nodos[nodos[nodo].viz[i]].h < minH && (nodos[nodos[nodo].viz[i]].h+1) > pmh ) {minH = nodos[nodos[nodo].viz[i]].h; 
               
                }
            }
    
    return (minH+1);
}


void Discharge(Node *nodos, Pipe **pipes, int nodo){
    int minH = nodos[0].h, pmh=0; 
    int nViz = 0;
    int viz = nodos[nodo].viz[0]; 
    /*o primeiro vizinho e sempre o sink
    consequentemente iremos verificar se
    da para enviar fluxo para la*/

    while(nodos[nodo].e > 0){

        if(nViz == nodos[nodo].nViz){ 
            minH = getMinH(nodos, pipes, nodo, pmh);
            pmh = minH;
            Relabel(nodos, pipes, nodo, minH);
            nViz = 0;
        }
        
        else if(pipes[nodo][viz].act < pipes[nodo][viz].max && nodos[nodo].h > nodos[viz].h){
            Push(nodos, pipes, nodo, viz);
            ++nViz;

        }
        else{
            ++nViz; 
             }
        viz = nodos[nodo].viz[nViz];
    }

}

/*adiciona elementos que foram removidas da queue*/
void addToArr(int v){
    
    array[narr++]=v;
}

/*remove ultimo elemento da arr e coloca no inicio da queue*/
int rmvFromArr(){
    --narr;
    return array[narr];
}

/*remove todos elementos da arr e coloca na queue*/
void restoreQ(){
    while(narr>0){
        add2(rmvFromArr());
    }
    
}

int main(){
    int nNodes, nEdges, x,y,z, w, nPipes, Sn, sn, np = 0;
    scanf("%d %d", &nNodes, &nEdges);
    array = can_fail_malloc(nNodes*sizeof(int));
    Sn = 0; sn = nNodes+1;
    nPipes = (nNodes+2);
    Node *nodes = can_fail_malloc((nNodes+2)*sizeof(Node));
    for(x=0; x<=nNodes+1; x++){
        nodes[x].viz=can_fail_malloc((nNodes+2)* sizeof(int));
    }
    
    Pipe **pipes = (Pipe**)can_fail_malloc((nPipes)*sizeof(Pipe*));
    for(x=0; x<nPipes; x++){
        pipes[x] = (Pipe*)can_fail_malloc(nPipes*sizeof(Pipe));
    }
    
    nodes[Sn].h=nNodes;
    nodes[sn].h=0;

   /*Inicializacao de piped de Source para Node e de Node para sink*/
    for(x=1; x<=nNodes; x++){
        scanf("%d %d", &y, &z);
        pipes[Sn][x].max = y;
        pipes[x][Sn].max = y;
        ++np;
        ++np;
        pipes[x][sn].max = z;
        ++np;

        nodes[x].h = 0;
        nodes[x].e = 0;
        /*Tanto sn como Sn serao vizinhos dequalequer nodo
        De preferencia queremos qeu sn e Sn sejam primeiros analizados qundo
        enviarmos fluxo*/
        nodes[x].viz[nodes[x].nViz] = sn;
        nodes[x].nViz+=1;
        nodes[x].viz[nodes[x].nViz] = Sn;
        nodes[x].nViz+=1;
    }


/*Inicializacao de pipes entre os Nodes*/
    for(x=0; x<nEdges; x++){
        scanf("%d %d %d",&y, &z, &w);
       
        pipes[y][z].max=w;
        pipes[z][y].max=w;
        pipes[y][z].act=0;
        pipes[z][y].act=0;
        ++np;
        ++np;
       
        nodes[y].viz[nodes[y].nViz]=z;
        nodes[y].nViz+=1;

        nodes[z].viz[nodes[z].nViz]=y;
        nodes[z].nViz+=1;
    }
 

    initPreF(nodes, pipes, nNodes);

   
    x = 0;
    int nodo, oldh; 
    while(nodes[Sn].e != -(nodes[sn].e)){ /*Condicao de de maximo fluxo*/ 
        if(x == nNodes) break;
       
        nodo = rmv();
        
        oldh = nodes[nodo].h;
        if(nodes[nodo].e > 0) Discharge(nodes, pipes, nodo);

        if(oldh < nodes[nodo].h){
            if(narr>0) restoreQ();
            add2(nodo);
            x = 0;
            }
        else {++x; addToArr(nodo);};
    }


    printf("%d\n", nodes[sn].e);


    for(x=0; x<=nNodes+1; x++){
        free(nodes[x].viz);
    }
    for(x=0; x<nPipes; x++){
        free(pipes[x]);
    }
    free(pipes);free(nodes);free(array);


    return 0;
}