#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include<stdio.h>
#include<stdlib.h>

typedef struct edge{
    int indexfromV;   
    int indexToV;     
    int flow;
    int capacity;
}Edge;

typedef struct node{
    Edge e;
    struct node* next;
} Node;

typedef struct list{
	Node *head;
	Node *tail;
} List;

typedef struct graph{
    List listOfAdjEdges;
} Graph;


/*------------------QUEUE-------------------------------------*/

typedef struct queuenode{
	int verticeindex;
	struct queuenode *next;
} QueueNode;

typedef struct queuelist{
	QueueNode *head;
	QueueNode *tail;
} QueueList;


/*-------------------VARIAVEIS GLOBAIS-------------------------*/
int nAvenues=0, nStreets=0, nSuperm=0, nCitiz=0;

int ** MatrixOfverticesCit;
int ** MatrixOfverticesSup;

int *prev;
int *path;

Graph *Manhattan; 

QueueList queue;

/*------------------------QUEUE------------------------------------*/

QueueNode *createQueueNode(int i){
    QueueNode *newNode;
    newNode = (QueueNode *)can_fail_malloc(sizeof(QueueNode));
    newNode->verticeindex = i;
    newNode->next = NULL;
    
    return newNode;
}

int QUEUEempty() {
 return queue.head == NULL;
} 

void QUEUEinit() {
 queue.head = NULL;
 queue.tail = NULL;
} 

void QUEUEput(int i) {
 if (queue.head == NULL) {
    queue.head = (queue.tail = createQueueNode(i) );
    return;
 }
 else{
    queue.tail->next = createQueueNode(i);
    queue.tail = queue.tail->next;
 }
  
} 

int QUEUEget() {
 int i=0;
 QueueNode *previousNode;
 if (!QUEUEempty()) {
        i = queue.head->verticeindex;
        previousNode = queue.head;
        queue.head = queue.head->next;
        free(previousNode); 
    }
    else{
        printf("Queue is empty.");
    }
    return i;
}


/*-------------------------INPUTS & AUX-------------------------------*/

int returnIndexInGraph(int i, int j){  
    return ( (i * nStreets) + j );
}

void inputOfCitizens(int lenght, int id){
    int i;
    int input1,input2;                            

    for(i = 0; i < lenght; i++){
        scanf("%d %d", &input1, &input2);
        MatrixOfverticesCit[input1-1][input2-1] = id;
    }
}

void inputOfSupermarkets(int lenght, int id){
    int i;
    int input1,input2;                            

    for(i = 0; i < lenght; i++){
        scanf("%d %d", &input1, &input2);
        MatrixOfverticesSup[input1-1][input2-1] = id;
    }
}


/*----------------------EDGES & NODES--------------------------------*/

Edge NewEdge(int ToV, int FromV, int c){
    Edge e;
    e.flow=0;
    e.capacity=c;
    e.indexfromV = FromV;
    e.indexToV= ToV;
    return e;
}

Node *createNode(Edge e){
    Node *newNode;
    newNode = (Node *)can_fail_malloc(sizeof(Node));
    newNode->e = e;
    newNode->next = NULL;
    
    return newNode;
}

void insertAtEnd(int n, Edge edge){
    if(Manhattan[n].listOfAdjEdges.head == NULL){
        Manhattan[n].listOfAdjEdges.head = createNode(edge);
        Manhattan[n].listOfAdjEdges.tail = Manhattan[n].listOfAdjEdges.head;
        return;
    }
    Manhattan[n].listOfAdjEdges.tail->next = createNode(edge);
    Manhattan[n].listOfAdjEdges.tail = Manhattan[n].listOfAdjEdges.tail->next;
}


/*---------------------------INITIALIZATION--------------------------*/

void aux_init_ListOfAdjEdgesINtoOUT(int iIN, int jIN, int iOUT, int jOUT, int c){
    int indexIN = returnIndexInGraph(iIN,jIN);
    int indexOUT = returnIndexInGraph(iOUT,jOUT) + (nAvenues*nStreets);
    Edge eAux = NewEdge(indexOUT,indexIN,c);
    insertAtEnd(indexIN,eAux);
}

void aux_init_ListOfAdjEdgesOUTtoIN(int iOUT, int jOUT, int iIN, int jIN, int c){
    int indexIN = returnIndexInGraph(iIN,jIN);
    int indexOUT = returnIndexInGraph(iOUT,jOUT) + (nAvenues*nStreets);
    Edge eAux = NewEdge(indexIN,indexOUT,c);
    insertAtEnd(indexOUT,eAux);
}

void aux_init_ListOfAdjEdgesOUTtoINandINtoOUT(int iOUT, int jOUT, int iIN, int jIN){
    aux_init_ListOfAdjEdgesOUTtoIN(iOUT, jOUT, iIN, jIN,1);
    aux_init_ListOfAdjEdgesINtoOUT(iIN, jIN, iOUT, jOUT,0);  /*residual*/
}

void init_ListOfAdjEdges(){
    int i,j;

    for(i=0;i<nAvenues;i++){
        for(j=0;j<nStreets;j++){
            
            aux_init_ListOfAdjEdgesINtoOUT(i,j,i,j,1);
            aux_init_ListOfAdjEdgesOUTtoIN(i,j,i,j,0);       /*residual*/

            if(i==0){
                aux_init_ListOfAdjEdgesOUTtoINandINtoOUT(i,j,i+1,j);

                if(j==0)
                    aux_init_ListOfAdjEdgesOUTtoINandINtoOUT(i,j,i,j+1);
                else if(j>0 && j<(nStreets-1)){
                    aux_init_ListOfAdjEdgesOUTtoINandINtoOUT(i,j,i,j-1);
                    aux_init_ListOfAdjEdgesOUTtoINandINtoOUT(i,j,i,j+1);
                }
                else if(j==(nStreets-1))
                    aux_init_ListOfAdjEdgesOUTtoINandINtoOUT(i,j,i,j-1);
            }

            else if(i>0 && i<(nAvenues-1)){

                aux_init_ListOfAdjEdgesOUTtoINandINtoOUT(i,j,i+1,j);
                aux_init_ListOfAdjEdgesOUTtoINandINtoOUT(i,j,i-1,j);

                if(j==0)
                    aux_init_ListOfAdjEdgesOUTtoINandINtoOUT(i,j,i,j+1);
                else if(j>0 && j<(nStreets-1)){
                    aux_init_ListOfAdjEdgesOUTtoINandINtoOUT(i,j,i,j+1);
                    aux_init_ListOfAdjEdgesOUTtoINandINtoOUT(i,j,i,j-1);
                }
                else if(j==(nStreets-1))
                    aux_init_ListOfAdjEdgesOUTtoINandINtoOUT(i,j,i,j-1);

            }
            else if(i==nAvenues-1){

                aux_init_ListOfAdjEdgesOUTtoINandINtoOUT(i,j,i-1,j);

                if(j==0)
                    aux_init_ListOfAdjEdgesOUTtoINandINtoOUT(i,j,i,j+1);
                else if(j>0 && j<(nStreets-1)){
                    aux_init_ListOfAdjEdgesOUTtoINandINtoOUT(i,j,i,j+1);
                    aux_init_ListOfAdjEdgesOUTtoINandINtoOUT(i,j,i,j-1);
                }
                else if(j==(nStreets-1))
                    aux_init_ListOfAdjEdgesOUTtoINandINtoOUT(i,j,i,j-1);

            }

        }
    }
}

void init_SourceAndSink(){
    int SourceIndex = 2*(nAvenues*nStreets);
    int SinkIndex = 2*(nAvenues*nStreets)+1;
    int i,j,indexIN=0, indexOUT=0;
    for(i=0;i<nAvenues;i++){
        for(j=0;j<nStreets;j++){
            if(MatrixOfverticesCit[i][j]== 1){
                indexIN = returnIndexInGraph(i,j);
                insertAtEnd(SourceIndex, NewEdge(indexIN,SourceIndex,1));
                insertAtEnd(indexIN, NewEdge(SourceIndex, indexIN, 0));
            }
            if(MatrixOfverticesSup[i][j]== 2){
                indexOUT = returnIndexInGraph(i,j) + (nAvenues*nStreets);
                insertAtEnd(indexOUT, NewEdge(SinkIndex, indexOUT,1));
                insertAtEnd(SinkIndex, NewEdge(indexOUT,SinkIndex,0));
            }
        }
    }
}

void init_graph(){
    int i;
    Manhattan=(Graph *)can_fail_malloc((2*(nAvenues*nStreets) + 2) * sizeof(Graph));
    for(i=0; i< 2*(nAvenues*nStreets) + 2 ;i++){
        Manhattan[i].listOfAdjEdges.head=NULL;
        Manhattan[i].listOfAdjEdges.tail=NULL;
    }

    init_ListOfAdjEdges();
    init_SourceAndSink();
}

void init_MatrixOfVerticesBoth(){
    int i,j;
    MatrixOfverticesCit = (int **)can_fail_malloc(nAvenues * sizeof(int *));
    MatrixOfverticesSup = (int **)can_fail_malloc(nAvenues * sizeof(int *));
    for(i=0; i<nAvenues ;i++){
        MatrixOfverticesCit[i] = (int *)can_fail_malloc(nStreets * sizeof(int));  
        MatrixOfverticesSup[i] = (int *)can_fail_malloc(nStreets * sizeof(int)); 
        for(j=0;j<nStreets;j++){
            MatrixOfverticesCit[i][j]=0;
            MatrixOfverticesSup[i][j]=0;
        }
    }                      
}

void init_prev_and_path(){
    int n=0;
    prev = (int *)can_fail_malloc((2*(nAvenues*nStreets)+2)*sizeof(int));
    for(n=0; n < (2*(nAvenues*nStreets)+2);n++){
          prev[n]=-1;
    }
    path = (int *)can_fail_malloc((2*(nAvenues*nStreets)+2)*sizeof(int));
    for(n=0; n < (2*(nAvenues*nStreets)+2);n++){
          path[n]=0;
    }

}


/*--------------------EDMONDS-KARP ALGORITHM-----------------------*/

void set_prev_and_path(){
    int n=0;
    for(n=0; n < (2*(nAvenues*nStreets)+2);n++){
          prev[n]=-1;
    }
    for(n=0; n < (2*(nAvenues*nStreets)+2);n++){
          path[n]=0;
    }
}

int min(int u, int v){
    if(v<u){
        return v;
    }
    return u;
}

int bfs(int SourceIndex, int SinkIndex){
    int flow =0, indexPoped=0;
    Node *aux;

    set_prev_and_path();

    QUEUEinit();
    QUEUEput(SourceIndex);
    prev[SourceIndex] = 11;
    path[SourceIndex] = 333;

    while(!QUEUEempty()){
        indexPoped = QUEUEget();
        for(aux = Manhattan[indexPoped].listOfAdjEdges.head; aux!=NULL; aux = aux->next ){
            if(prev[aux->e.indexToV] == -1){
                if(aux->e.capacity - aux->e.flow > 0){
                    prev[aux->e.indexToV] = indexPoped;
                    path[aux->e.indexToV] = min(path[indexPoped],aux->e.capacity - aux->e.flow);
                    if(aux->e.indexToV == SinkIndex){
                        flow = path[aux->e.indexToV];
                    }
                
                QUEUEput(aux->e.indexToV);
                }
                
            }
            
        }
    }

    return flow;
}

int edmondsKarp(){
    int SourceIndex = 2*(nAvenues*nStreets);
    int SinkIndex = 2*(nAvenues*nStreets)+1;
    int maxFlow=0, flow=0;
    int aux=0, beforeAux=0;
    Node * auxNode= NULL;

    while(1){
        flow = bfs(SourceIndex,SinkIndex);
        if(flow==0)
            break;

        maxFlow+=flow;

        aux = SinkIndex;
        while(aux != SourceIndex){
            beforeAux = prev[aux];
            for(auxNode = Manhattan[beforeAux].listOfAdjEdges.head; auxNode->e.indexToV!= aux; auxNode = auxNode->next);
            auxNode->e.flow += flow; 
            
            for(auxNode = Manhattan[aux].listOfAdjEdges.head; auxNode->e.indexToV!= beforeAux; auxNode = auxNode->next );
            auxNode->e.flow -= flow;
            
            aux = beforeAux;
        }

    }
    return maxFlow;
}


/*-------------------------FREE-----------------------------------*/

void free_all(){
    int n,i;
    Node *aux;
    Node *auxBefore;
    for(n = 0; n < 2*(nAvenues*nStreets)+2; n++){
        for(aux = Manhattan[n].listOfAdjEdges.head; aux != NULL;){
            auxBefore = aux;
            aux = aux->next;
            free(auxBefore);
        }
        Manhattan[n].listOfAdjEdges.head = NULL;
        Manhattan[n].listOfAdjEdges.tail = NULL;
    }
    
    free(Manhattan);

    for (i = 0; i < nAvenues; i++) {
        free(MatrixOfverticesCit[i]);
        free(MatrixOfverticesSup[i]);
    }
    free(MatrixOfverticesCit);
    free(MatrixOfverticesSup);
    free(prev);
    free(path);

}



int main(){
    int maxFlow=0;
    
    scanf("%d %d\n", &nAvenues, &nStreets);

    if(nAvenues < 1 || nStreets < 1){
		exit(EXIT_FAILURE);
    }
    scanf("%d %d\n", &nSuperm, &nCitiz);

    init_MatrixOfVerticesBoth();

    inputOfSupermarkets(nSuperm,2);
    inputOfCitizens(nCitiz,1);

    init_graph();

    /*---------------------Edmonds–Karp--------------------*/

    init_prev_and_path();

    maxFlow = edmondsKarp();

    /*------------------------------------------------*/

    free_all();

    printf("%d\n",maxFlow);

    return 0;
}