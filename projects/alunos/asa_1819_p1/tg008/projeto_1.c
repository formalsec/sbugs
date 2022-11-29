#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/* Projeto 1 ASA
Grupo tp008
Francisco Almeida n81995
Andre Silva n84700
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define minimum(A,B) (A < B? A : B)

/*Stack do Tarjan*/
typedef struct st stack;
struct st{
    int top;
    int* items; 
};

/*Informacao do Router*/
typedef struct info infoRouter;
struct info{
	int index;
	int head;
	int lowLink;
	bool onStack;
	int scc;
	int rID;
	bool removed;
};

typedef struct r router;
struct r{
    int id;
    router *next;
};


typedef struct l list;
struct l{
    router* head;
};

typedef struct g graph;
struct g {
    list* gList;
};

graph* network;
stack* tarjanStack;
infoRouter* routerInfoVec; 

/*Variaveis Globais*/
int N, M, totalIndex = 1, sccSize = 0;
int currentSCC = 0;
int nAP = 0;
int* sccHeadID;
int totalHeads=1;


void graphInit();
void stackInit();
void routerInfoInit();
router* newRou(int id, int dest);
void newLink(int c1, int c2);
void tarjanAlgorithm();
void scc(int currentRouter);
void push(int routerID);
int pop();
void apUtil(int router, int* isVisited, int* des, int* parent, int* low, int* ap);
void AP();
void printHeads();
void removeRouter(int id);
void printG();
void freeGraph();
void freeGList();
int cmpfunc(const void *a, const void *b);

int main(){
	int i;
	scanf("%d", &N);
	scanf("%d", &M);
	int c1, c2;

	sccHeadID =(int*)can_fail_malloc(totalHeads*sizeof(int));
	graphInit();
	stackInit();
	routerInfoInit();

	for(i=0; i < M; ++i){
		scanf("%d %d", &c1, &c2);
		newLink(c1, c2);
	} 
	tarjanAlgorithm();
	printf("%d\n", currentSCC);
	printHeads();
	AP();
	sccSize = 0;
	totalIndex = 1;
	tarjanAlgorithm();
	printf("%d\n", nAP);
	printf("%d\n", sccSize);

	freeGraph();
	free(routerInfoVec);
	free(tarjanStack->items);
	free(tarjanStack);
	free(sccHeadID);

	return 0;
}

/*Inicializa a infromacao do grafo*/
void graphInit(){
    int i;

    network = (graph*)can_fail_malloc(sizeof(struct g));

    network -> gList = (list*)can_fail_malloc((N + 1) * sizeof(struct l));

    for (i = 1; i <= N; ++i) {
        network -> gList[i].head = NULL;

    }
}

/*Inicializa a informacao da stack*/
void stackInit(){
    /* MALLOC para um ponteiro para stack*/
    tarjanStack = (stack*)can_fail_malloc(sizeof(struct st));

    /*MALLOC para um vector de posicoes da stack que tem o numero de nodos que existem*/
    tarjanStack -> items = (int*)can_fail_malloc(N * sizeof(int));
    tarjanStack -> top = -1;
}

/*Inicializa a infirmacao do router*/
void routerInfoInit(){
	int i;
	routerInfoVec = (infoRouter*)can_fail_malloc((N+1) * sizeof(struct info));
	for(i=1; i <= N; ++i){
    	routerInfoVec[i].index = -1;
    	routerInfoVec[i].head = -1;
    	routerInfoVec[i].lowLink = -1;
    	routerInfoVec[i].onStack = false;
    	routerInfoVec[i].scc = -1;
    	routerInfoVec[i].rID = -1;
    	routerInfoVec[i].removed = false;
	}
}

router* newRou(int id, int dest){
	router* newr = (router*) can_fail_malloc(sizeof(struct r));
	newr->id = id;
	newr->next = NULL;
	return newr;
}

/*Cria uma ligacao entre dois routers*/
void newLink(int c1, int c2){
	router* newRouter = newRou(c1,c2);
	router* newRouter2 = newRou(c2,c1);
    newRouter->next = network->gList[c2].head;
    newRouter2->next = network->gList[c1].head;
    network->gList[c2].head = newRouter;
    network->gList[c1].head = newRouter2;
    routerInfoVec[c1].rID = c1;
    routerInfoVec[c2].rID = c2;

}

/*Algoritmo Tarjan*/
void tarjanAlgorithm(){
	int j,i;
	for(j=1; j <= N; ++j){
		if(routerInfoVec[j].index == -1 && !routerInfoVec[j].removed){
			scc(j);
		}
	}
	for(i=1; i<=N; ++i){
		routerInfoVec[i].index = -1;
    	routerInfoVec[i].head = -1;
    	routerInfoVec[i].lowLink = -1;
    	routerInfoVec[i].scc = -1;
	}
}

/*Imprime os identificadores dos SCCs*/
void printHeads(){
	int i;
	qsort(sccHeadID, currentSCC+1, sizeof(int), cmpfunc);
	for(i = 1; i<=currentSCC; i++){
		printf("%d",sccHeadID[i]);
		if(i!=currentSCC){
			printf(" ");
		}
	}
	printf("\n");
}

/*Verifica qual dos inteiros e maior*/
int cmpfunc(const void *a, const void *b){
	return ( *(int*)a - *(int*)b);
}

/*Coloca um id de um router na stack do Tarjan*/
void push(int routerID){
	tarjanStack->top += 1;
	if((tarjanStack->top) < N){
		tarjanStack->items[tarjanStack->top] = routerID;
	}
	else{
		printf("Tarjan stack is full\n");
		exit(1);
	}
}

/*remove um id de um router da stack do Tarjan*/
int pop(){
	if(tarjanStack->top < 0){
		printf("Tarjan stack is empty\n");
		exit(1);
	}
	return tarjanStack->items[tarjanStack->top--];
}

/*cria e identifica os SCCs*/
void scc(int currentRouter){
	int size = 0;
	int auxRouter = -1;
	router* adjacent= network->gList[currentRouter].head;

	routerInfoVec[currentRouter].index = totalIndex;
	routerInfoVec[currentRouter].lowLink = totalIndex;
	totalIndex += 1;
	push(currentRouter);
	routerInfoVec[currentRouter].onStack = true;

	while(adjacent != NULL){
		if(routerInfoVec[adjacent->id].index == -1 && !routerInfoVec[adjacent->id].removed){
			scc(adjacent->id);
			routerInfoVec[currentRouter].lowLink = minimum(routerInfoVec[currentRouter].lowLink, routerInfoVec[adjacent->id].lowLink);
		}
		else if(routerInfoVec[adjacent->id].onStack){
			routerInfoVec[currentRouter].lowLink = minimum(routerInfoVec[currentRouter].lowLink, routerInfoVec[adjacent->id].lowLink);
		}
		adjacent = adjacent->next;
	}

	if(routerInfoVec[currentRouter].index == routerInfoVec[currentRouter].lowLink){
		currentSCC += 1;
		routerInfoVec[currentRouter].scc = currentSCC;
		routerInfoVec[currentRouter].head = currentRouter;
		totalHeads++;
		sccHeadID =(int*)can_fail_realloc(sccHeadID, totalHeads*sizeof(int));
		sccHeadID[currentSCC] = routerInfoVec[currentRouter].rID;

		while(auxRouter != currentRouter){
			auxRouter = pop();
			routerInfoVec[auxRouter].scc = currentSCC;
			routerInfoVec[auxRouter].onStack = false;
			routerInfoVec[auxRouter].head = currentRouter;
			size+=1;
			if(sccHeadID[currentSCC] < routerInfoVec[auxRouter].rID){
				sccHeadID[currentSCC] = routerInfoVec[auxRouter].rID;
			}
		}
		if(size > sccSize){
			sccSize = size;
		}
		size = 0;
	}
}

void apUtil(int routerID,int* isVisited,int* des,int* parent,int* low,int* ap) {

    static int time=0;
    int children=0;
    router* temp = network->gList[routerID].head;
    isVisited[routerID]=1;
    time++;
    des[routerID]=low[routerID]=time;

    while(temp!=NULL)
    {       
       if(!isVisited[temp->id])
        {
          children++;
          parent[temp->id]=routerID;
          apUtil(temp->id,isVisited,des,parent,low,ap);

      low[routerID]= minimum(low[routerID],low[temp->id]);

          if(parent[routerID]==-1 && children>1)
             ap[routerID]=1;

      if(parent[routerID]!=-1 && des[routerID]<=low[temp->id])
            ap[routerID]=1;           
        }    
        else if(temp->id!=parent[routerID])
        {
            low[routerID]= minimum(low[routerID],des[temp->id]);
        }
       temp= temp->next;
      }
}

/*Procura e cria os Articulated Points*/
void AP() {
    int i;
    int* des = (int*)can_fail_malloc(sizeof(int)*N+4);
    int* isVisited = (int*)can_fail_malloc(sizeof(int)*N+4);
    int* parent = (int*)can_fail_malloc(sizeof(int)*N+4);
    int* low = (int*)can_fail_malloc(sizeof(int)*N+4);
    int* ap = (int*)can_fail_malloc(sizeof(int)*N+4);
 

    for(i=1;i<=N;i++)
    {
        isVisited[i]=0;
        parent[i]=-1;
        ap[i]=0;
    }

    for(i=1;i<=N;i++)
    {
        if(isVisited[i]==0)
        {
            apUtil(i,isVisited,des,parent,low,ap);
        }
    }
    int flag=0;
    for(i=1;i<=N;i++) {
       
        if(ap[i]==1) {
	  		flag=1;
	  		nAP++;
	  		routerInfoVec[i].removed = true;
		}
    }

    if(flag==0){
	}
	free(des);
	free(isVisited);
	free(parent);
	free(low);
	free(ap);
}

/*Liberta a informacao do grafo*/
void freeGraph(){
	int i;
	for(i=1; i<=N; ++i){
		freeGList(network->gList[i].head);
	}
	free(network->gList);
	free(network);
}

/*Liberta a informacao da lista*/
void freeGList(router* head){
	router* auxiliar = NULL;
	while(head){
		auxiliar = head->next;
		free(head);
		head = auxiliar;
	}
}

