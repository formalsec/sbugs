#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct edge{
    int arcoPartida;
    int arcoDestino;
    int capacidade;
    int flow;
}Edge;

typedef struct queuenode{
    int verticeNum;
    struct queuenode *next;
}QueueNode;

typedef struct queuelist{
    QueueNode *head;
    QueueNode *tail;
}QueueList;

Edge *ArrayArcos;
QueueList queue;

int *parent;
bool *visited;

void Queueinit();
int Queueempty();
QueueNode *createQueueNode(int v);
void Queuepush(int vertice);
int Queuegetlast();
void criaArco(int u, int v, int indiceArco);
void iniciaArcos(int vertices);
void freeArcos();
int returnIndiceArcos(int u, int v, int vertices);
void adicionaArcos(int vertices, int edges);
int fordfulkerson(int vertices);
bool bfs_aux(int start, int finish);


int main(){
    int vertices=0, total_edges=0;

    if(scanf("%d %d", &vertices, &total_edges)==1){
        exit(EXIT_FAILURE);
    }else{

        if(vertices<2 || total_edges<0){
            exit(EXIT_FAILURE);
        }

        iniciaArcos(vertices);
        adicionaArcos(vertices,total_edges);
        
        printf("%d\n", fordfulkerson(vertices));
        
        freeArcos();
    }
    return 0;
}

int min(int n, int n1){
    return n < n1 ? n : n1;
}

/*===================QUEUE============*/

void Queueinit(){
    queue.head = NULL;
    queue.tail = NULL;
}

int Queueempty(){
    return queue.head == NULL;
}

QueueNode *createQueueNode(int v){
    QueueNode *newNode;
    newNode = (QueueNode *)can_fail_malloc(sizeof(QueueNode));
    newNode->verticeNum = v;
    newNode->next = NULL;
    return newNode;
}

void Queuepush(int v){
    if (queue.head == NULL) {
        queue.head = (queue.tail = createQueueNode(v));
        return;
    }
    else{
        queue.tail->next = createQueueNode(v);
        queue.tail = queue.tail->next;
 }
}

int Queuegetlast(){
    int v=0;
    QueueNode *previousNode;
    if (!Queueempty()) {
        v = queue.head->verticeNum;
        previousNode = queue.head;
        queue.head = queue.head->next;
        free(previousNode); 
    }else{
        printf("Queue empty.");
    }
    
    return v;
}

/*=====================CREATE AND INICIALIZE THE EDGES====================*/

void criaArco(int u, int v, int indiceArco){
    ArrayArcos[indiceArco].arcoPartida=u;
    ArrayArcos[indiceArco].arcoDestino=v;
    ArrayArcos[indiceArco].capacidade=0;
    ArrayArcos[indiceArco].flow=0;
}

void iniciaArcos(int vertices){
    int u=0, v=0, k=0, indiceArco=0;

    ArrayArcos = (Edge *)can_fail_malloc(sizeof(Edge)*((vertices+2)*(vertices+2)));
    parent = (int *)can_fail_malloc(sizeof(int)*(vertices+2));
    visited = (bool *)can_fail_malloc(sizeof(bool)*(vertices+2));

    for(u=0; u<=(vertices+1);u++){
        for(v=0; v<=vertices+1;v++){
            indiceArco = (u*(vertices+1))+(v+k);
            criaArco(u,v,indiceArco);
        }
        k++;
    }
}

/*====================FREE ALL========================*/

void freeArcos(){

    free(ArrayArcos);
    free(parent);
    free(visited);
}

/*===============RETORNA INDICE ARCOS================*/

int returnIndiceArcos(int u, int v, int vertices){
    int indiceArco=0;
    indiceArco = (u*(vertices))+(v+u);
    return indiceArco;
}

/*=================ADICIONA ARCOS==================*/

void adicionaArcos(int vertices, int edges){
    int vertice=0, next_vertice=0, i=0, weight=0,  cap_x=0, cap_y=0, indiceArco=0;

    for(i=1; i<=vertices; i++){
        if(scanf("%d %d", &cap_x, &cap_y)){
            indiceArco=returnIndiceArcos(0,i,vertices+1);
            ArrayArcos[indiceArco].capacidade=cap_x;
            ArrayArcos[indiceArco].flow=cap_x;

            indiceArco=returnIndiceArcos(i,vertices+1,vertices+1);
            ArrayArcos[indiceArco].capacidade=cap_y;
            ArrayArcos[indiceArco].flow=cap_y;
        }
    }

    for(i=1; i<=edges; i++){
        if(scanf("%d %d %d", &vertice, &next_vertice, &weight)){
            indiceArco=returnIndiceArcos(vertice,next_vertice,vertices+1);
            ArrayArcos[indiceArco].capacidade=weight;
            ArrayArcos[indiceArco].flow=weight;

            indiceArco=returnIndiceArcos(next_vertice,vertice,vertices+1);
            ArrayArcos[indiceArco].capacidade=weight;
            ArrayArcos[indiceArco].flow=weight;
        }
    }
}


/*=================FORD FULKERSON==================*/

int fordfulkerson(int vertices){
    int i=0, j=0, max_flow=0, indiceArco=0, indiceArco2=0;

    while(bfs_aux(0,vertices)){
        int flow_calculated=0;
        for(i=vertices+1; i!=0; i=parent[i]){
            j = parent[i];
            indiceArco = returnIndiceArcos(j,i,vertices+1);
            if(i==vertices+1){
                flow_calculated=ArrayArcos[indiceArco].flow;
            }else{
                flow_calculated= min(flow_calculated, ArrayArcos[indiceArco].flow);
            }
        }

        for(i=vertices+1; i!=0; i=parent[i]){
            j = parent[i];

            indiceArco = returnIndiceArcos(j,i,vertices+1);
            ArrayArcos[indiceArco].flow = ArrayArcos[indiceArco].flow - flow_calculated;

            indiceArco2 = returnIndiceArcos(i,j,vertices+1);
            ArrayArcos[indiceArco2].flow = ArrayArcos[indiceArco2].flow + flow_calculated;
            
        }
        max_flow = max_flow + flow_calculated;
    }
    return max_flow;

}


/*=================BFS==================*/

bool bfs_aux(int start, int finish){
    int v=0, u=0, i=0, indiceArco=0;

    for(i=0; i<=finish+1; i++){
        visited[i]=false;
    }

    Queueinit();
    Queuepush(start);
    visited[start] = true;
    parent[start] = -1;

    while(!Queueempty()){
        u = Queuegetlast();
        for(v=0; v<=finish+1;v++){
            indiceArco= returnIndiceArcos(u,v,finish+1);
            if(!visited[v] && ArrayArcos[indiceArco].flow >0){
                if (v == finish+1){
                    parent[v]= u;
                    return true;
                }
                
                Queuepush(v); 
                parent[v] = u;
                visited[v] = true;
            }
        } 
    }
    return false;
}