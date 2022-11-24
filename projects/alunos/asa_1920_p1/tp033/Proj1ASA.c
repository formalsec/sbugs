#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/******************************************************************************************************************
 *
 *                                          Projecto 1 ASA
 *
 *                                       Paulo Cabecas,  76358
 *                                       Joana Mendonca, 83597
 *
 *****************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define min(a,b) (a<b ? a:b)

struct Graph{
    int numheads;
    struct router** heads;
};

typedef struct {
  int *array;
  size_t used;
  size_t size;
} Array;

/*struct of a router*/
struct router{
    int routerNumber;
    int scc_id;
    int low;
    int instack;
    int discoveryTime;
    struct edge* adjVertex;
    int root;
    int min;
    int currentGrade;
    int* connectionsSCC;
};

struct Stack{
    int number;
    int top;
    int size;
    int *elements;
};

struct edge{
    int vNumber;
    int flag;
    struct edge* nextEdge;
};

struct tpElement{
    int* next;
};

struct connection{
    int source;
    int destiny;
};

struct Stack *stack_aux;
static struct Graph *graph;
struct tpElement* topologicalSort;

/*Headers*/
void initTP();
void initGraph(int n);
void insertEdge(int source,int destiny);
struct router* newRouter(int number);
void SCC_Tarjan(int size);
void Tarjan_Visit(int n);
int isEmpty();
void initStack(int capacity);
void push(int router);
int pop();
void printGraph();
int testConnections(struct edge* ptr);


struct connection* newConnection(int source,int destiny);
void swap(int num1, int num2);
void initArray(Array *a, size_t initialSize);
void insertArray(Array *a, int element);
void freeArray(Array *a);



int time; /*Variável para o tempo de descoberta*/
int scc; /* numero de scc's*/
int connections;
int idAtual;
int min;
struct connection** connectionsArray;
Array a;
Array grades;
int maxRouter;


/*******************DinamicArray***************************************/

void initArray(Array *a, size_t initialSize) {
  a->array = (int *)can_fail_malloc(initialSize * sizeof(int));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(Array *a, int element) {

  if (a->used == a->size) {
    a->size *= 2;
    a->array = (int *)can_fail_realloc(a->array, a->size * sizeof(int));
  }
  a->array[a->used++] = element;
}

void freeArray(Array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

/*******************Stack***************************************/
int isEmpty(){
    return stack_aux->number == 0;
}

/*Initialization of the auxiliary stack for Tarjan*/
void initStack(int capacity){
    stack_aux= (struct Stack*) can_fail_malloc(sizeof(struct Stack));
    stack_aux->top=-1;
    stack_aux->number=0;
    stack_aux->size=capacity;
    stack_aux->elements=(int*)can_fail_malloc(sizeof(int)*capacity);
}

/*Push operation for stack*/
void push(int router){
    stack_aux->top=router;
    stack_aux->elements[stack_aux->number]=router;
    stack_aux->number++;
}

int pop(){

    int valueRouterNumber;

    if (isEmpty()) {
        printf("isEMPTY!\n");
        return EXIT_FAILURE;
    }
    valueRouterNumber = graph->heads[stack_aux->top - 1]->routerNumber;
    if (stack_aux->number-2 >= 0)
        stack_aux->top=stack_aux->elements[stack_aux->number-2];
    stack_aux->number--;
    return valueRouterNumber;
}
/****************************************************************/
/*Initialization of the graph*/
void initGraph(int n){
    int i;
    graph=(struct Graph*)can_fail_malloc(sizeof(struct Graph));
    graph->heads=(struct router**)can_fail_malloc(sizeof(struct router*)*n);

    for(i=0;i<n;i++){
        graph->heads[i]=newRouter(i+1);
    }
}

struct connection* newConnection(int source, int destiny){
    struct connection* new=(struct connection*)can_fail_malloc(sizeof(struct connection));
    new->source=source;
    new->destiny=destiny;
    return new;
}
/*Router creation*/
struct router* newRouter(int number){
    struct router* new=(struct router*)can_fail_malloc(sizeof(struct router));
    new->routerNumber=number;
    new->currentGrade=-1;
    new->scc_id=-1;
    new->adjVertex=NULL;
    new->discoveryTime=-1;
    new->instack=0;
    new->low=-1;
    new->root=-1;
    new->min=-1;
    return new;
}

struct edge* newEdge(int number){
    struct edge* new=(struct edge*)can_fail_malloc(sizeof(struct edge));
    new->vNumber=number;
    new->nextEdge=NULL;
    new->flag=0;

    return new;
}

void insertEdge(int source, int destiny){
    struct edge* newNode=newEdge(destiny);
    newNode->nextEdge=graph->heads[source-1]->adjVertex;
    graph->heads[source-1]->adjVertex=newNode;
}

void SCC_Tarjan(int size){
    int i;

    for(i=0;i<size;i++){

        if(graph->heads[i]->discoveryTime==-1){

            Tarjan_Visit(i);
            insertArray(&a, maxRouter);

            maxRouter = 0;

        }
    }
}

void Tarjan_Visit(int n){
    graph->heads[n]->discoveryTime=time;
    graph->heads[n]->low=time;
    time++;
    push(graph->heads[n]->routerNumber);
    graph->heads[n]->instack=1;
    graph->heads[n]->currentGrade=grades.array[n];

    struct edge* ptr=graph->heads[n]->adjVertex;

    while(ptr!=NULL){

        int number = ptr->vNumber;


        if(graph->heads[number-1]->discoveryTime==-1||graph->heads[number-1]->instack==1){
            if(graph->heads[number-1]->discoveryTime==-1 ){
                Tarjan_Visit(number-1);

            }
            graph->heads[n]->low=min(graph->heads[n]->low,graph->heads[number- 1]->low);

        }

        ptr=ptr->nextEdge;

    }


    int popValue;
    if(graph->heads[n]->discoveryTime==graph->heads[n]->low){
        scc++;
        int minTemp=graph->heads[n]->routerNumber;
        do {

            graph->heads[stack_aux->top-1]->instack=0;
            popValue = pop();
            
            if(maxRouter<popValue){
                maxRouter=popValue;
            }
            if(popValue<minTemp){
                minTemp=popValue;
            }
            graph->heads[popValue- 1]->scc_id=idAtual;
            graph->heads[popValue- 1]->root=graph->heads[n]->routerNumber;
        }
        while (popValue != graph->heads[n]->routerNumber);

        graph->heads[n]->min=minTemp;
        idAtual++;
    } 	
}


int main(){
    int nNode,nConnections,i,source,destiny,j,currentGrade,k;
    int maxGrade=0;
    int unused __attribute__((unused));
    scc=0,time=0,connections=0,min=0,maxRouter = 0;
    unused = scanf("%d,%d\n",&nNode, &nConnections);
    initGraph(nNode);
    initStack(nNode);
    initArray(&a, 5);
    initArray(&grades, 5);

    graph->numheads=nNode;

    for(i = 0; i < nNode; i++){
    	unused = scanf("%d\n", &currentGrade);
    	insertArray(&grades, currentGrade);
    }


    for(i=0;i < nConnections;i++){
        unused = scanf("%d %d\n", &source, &destiny);
        insertEdge(source, destiny);
    }

    SCC_Tarjan(nNode);

    for(i = 0; i < scc; i++) {
    	maxGrade = graph->heads[0]->currentGrade;
    	for(j = 0; j < nNode; j++) {
    		if(graph->heads[j]->scc_id == i) {
    			if(graph->heads[j]->currentGrade > maxGrade) {
    				maxGrade = graph->heads[j]->currentGrade;
    			}
    		}
    	}
    	for(k=0; k < nNode; k++){
    		if(graph->heads[k]->scc_id == i) {
				graph->heads[k]->currentGrade = maxGrade;
			}
		}
    }
      
    for(j = 0; j < nNode; j++){
        printf("%d\n", graph->heads[j]->currentGrade);
    }
    
    freeArray(&a);
    freeArray(&grades);
    return EXIT_SUCCESS;
}