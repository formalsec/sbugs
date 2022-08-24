#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
    int verticeNum;
    struct node* next;
}Node;

typedef struct list{
    Node *head;
}List;

typedef struct queuenode{
    int verticeNum;
    struct queuenode *next;
}QueueNode;

typedef struct queuelist{
    QueueNode *head;
    QueueNode *tail;
}QueueList;

List *ArrayAdjLists;
QueueList queue;

bool *visited;
int *order_topol;
int *indegree;

void createGraph(int vertices);
Node *createNode(int verticeNum);
void addEdges(int edges);
void freeList(int vertices);
void Queueinit();
int Queueempty();
QueueNode *createQueueNode(int v);
void Queuepush(int vertice);
int Queuegetlast();
void khansalgorithm(int vertices);
void bfs();
int dagLongestPath(int vertices);
void bfs_aux(int start);

int main(){
    int vertices=0, edges=0, clicks_dominos=0, l=0, i=0;

    if(scanf("%d %d", &vertices, &edges)==1){
        exit(EXIT_FAILURE);
    }else{

        if(vertices<2 || edges<0){
            exit(EXIT_FAILURE);
        }

        createGraph(vertices);
        addEdges(edges);
        Queueinit();
        khansalgorithm(vertices);

        l = dagLongestPath(vertices);

        for(i=0; i<vertices; i++){
            visited[i]=false;
        }
        
        for(i=0; i<vertices; i++){
            if(visited[order_topol[i]]== false){
                bfs_aux(order_topol[i]);
                clicks_dominos++;
            }
        }
    
        /*-------------------------------------*/
        printf("%d %d\n", clicks_dominos, l);
        freeList(vertices);
    }
    return 0;
}

/*===============Create and Initialize graph===============*/

void createGraph(int vertices){
    int i=0;

    ArrayAdjLists = (List *)malloc(sizeof(List)*vertices);

    for(i=0; i<vertices; i++){
        ArrayAdjLists[i].head = NULL;
    }

    order_topol = (int *)malloc(sizeof(int)*vertices);
    visited = (bool *)malloc(sizeof(bool)*vertices);
    indegree = (int *)malloc(sizeof(int)*vertices);
}

Node *createNode(int vertice){
    Node *newNode;
    newNode = (Node *)malloc(sizeof(Node));
    newNode->verticeNum = vertice-1;
    newNode->next = NULL;
    return newNode;
}

/*===============Input(list of vertices and thiir edges)===============*/

void addEdges(int edges){
    int vertice=0, next_vertice=0, i=0;

    for(i=0; i<edges; i++){
        if(scanf("%d %d", &vertice, &next_vertice)){
            Node *newNode;
            newNode = createNode(next_vertice);
            newNode->next = ArrayAdjLists[vertice-1].head;
            ArrayAdjLists[vertice-1].head = newNode;
        }
    }
}

void freeList(int vertices){
    int i;
    Node *aux;
    Node *aux2;
    for (i = 0; i < vertices; i++) {
        for(aux = ArrayAdjLists[i].head; aux != NULL;){
            aux2 = aux;
            aux = aux->next;
            free(aux2);
        }
        ArrayAdjLists[i].head = NULL;
    }
    free(ArrayAdjLists);
    free(order_topol);
    free(visited);
    free(indegree);
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
    newNode = (QueueNode *)malloc(sizeof(QueueNode));
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

/*===================================================*/

void khansalgorithm(int vertices){
    int i=0;
    Node *aux;
    for(i=0; i<vertices; i++){
        indegree[i] =0;  
    }
    
    /*se conter arestas entao aumenta indegree do vertice*/
    for(i=0; i<vertices; i++){
        for(aux = ArrayAdjLists[i].head; aux!=NULL; aux=aux->next){
            indegree[aux->verticeNum]++;
        }
    }
    
    /*os vertices que estao com indegree 0 sao pushados para queue*/
    for(i=0; i<vertices; i++){
        if(indegree[i] == 0){
            Queuepush(i);
        }
    }
    bfs();

}

/*==============================================*/
void bfs(){
    int v=0,pos=0;
    Node *aux;
    
    while(!Queueempty()){
        v = Queuegetlast();
        order_topol[pos++]=v;
        
        for(aux = ArrayAdjLists[v].head; aux!=NULL; aux=aux->next){
            indegree[aux->verticeNum]--;
            if(indegree[aux->verticeNum]==0){
                Queuepush(aux->verticeNum);
            }
        } 
    }
}

void bfs_aux(int start){
    int v=0;
    Node *aux;

    Queuepush(start);
    visited[start] = true;

    while(!Queueempty()){
        v = Queuegetlast();
        for(aux = ArrayAdjLists[v].head; aux!=NULL; aux=aux->next){
            if(!visited[aux->verticeNum]){
                visited[aux->verticeNum] = true;
                Queuepush(aux->verticeNum); 
            }
        } 
    }
}


int dagLongestPath(int vertices){
    int i=0, value=0, newDist=0, max=0;
    int dist[vertices];
    Node *aux;

    for(i=0; i<vertices; i++){
        dist[i] = 0;
    }

    for(i=0; i<vertices; i++){
        value = order_topol[i];
        for(aux = ArrayAdjLists[value].head; aux!=NULL; aux=aux->next){
            newDist = dist[value] + 1;
            if (dist[aux->verticeNum] < newDist){
                dist[aux->verticeNum] = newDist;
            }
        }
    }

    max = dist[0];
    for(i=1; i<vertices; i++){
        if(max < dist[i]){
            max = dist[i];
        }
    }
    return max+1;
}
