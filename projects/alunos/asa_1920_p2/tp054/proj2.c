#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/*@author 57395	Tiago Ferreira tg024 ASA 19/20*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 1000000


typedef struct item{
	int n;					/*id de vertice adjacente*/
	struct item* prox;		/*adjacencia de vertices*/
}Item;

struct queue {
	int items[MAX+1];
	int front;
	int rear;
};

struct queue* createQ(){
	struct queue* q = can_fail_malloc(sizeof(struct queue));
	q->front = -1;
	q->rear = -1;
	return q;
}

int isEmpty(struct queue* q){
	if(q->rear == -1)
		return 1;
	else
		return 0;
}

void enQ(struct queue* q, int value){
	if(q->front == -1)
		q->front = 0;
	q->rear++;
	q->items[q->rear] = value;
}

int deQ(struct queue* q){
	int item;
	if(isEmpty(q))
		item = -1;
	else {
		item = q->items[q->front];
		q->front++;
		if(q->front > q->rear)
			q->front = q->rear = -1;
	}
	return item;
}


Item list[MAX+1];	/*graph*/

int M, N;	/*input line1*/

int nS, nC;	/*input line2*/

int Sup[MAX+1];
int Cid[MAX+1];

int color[MAX+1];


int maxC;	/*max number of C with available path(output)*/


void addEdge(Item *list, int u, int v){
	Item *aux;
	Item *tmp;

	aux = (Item*) can_fail_malloc((int)sizeof(Item));
	aux->n = v;
	aux->prox = NULL;

	list[u].n++;
	if(list[u].prox == NULL)			/*se list[u] vazia insere elemento*/
		list[u].prox = aux;
	else {
		tmp = list[u].prox;
		if(tmp->n > v){						/*insere como 1o elemento*/
			aux->prox = tmp;
			list[u].prox = aux;
		}
		else if(tmp->prox == NULL){			/*insere novos vertices ordenados*/
			aux->prox = tmp->prox;
			tmp->prox = aux;
		}
		else {
			while((tmp->prox !=NULL) && (tmp->prox->n < v))
				tmp = tmp->prox;
			aux->prox = tmp->prox;
			tmp->prox = aux;
		}
	}
}

/*function (bfs on matrix)*/
void BFS (Item *list, int startVer){
	struct queue* q = createQ();
	color[startVer] = 1;
	enQ(q, startVer);
	
	while(!isEmpty(q)){
		int currentVer = deQ(q);
		color[currentVer] = 1;
		/*printf("visited %d\n", currentVer);*/		/*clean*/

		if(Sup[currentVer] == 1){
			maxC++;
			break;
		}

		Item *temp;
		temp = (Item*) can_fail_malloc((int)sizeof(Item));

		temp->n = currentVer;
		temp->prox = list[currentVer].prox;

		while(temp->prox != NULL){
			int adjVer;
			adjVer = temp->n;

			if(color[adjVer] == 0){
				color[adjVer] = 1;
				enQ(q, adjVer);
			}
			temp = temp->prox;
		}
	}
}


int main(int argc, char *argv[]){

	int i, j, m, n, v, b;
	int vS, vC;

	scanf("%d %d", &M, &N);

	/*create MxN graph*/
	for (v = 1; v <= M*N; v++){

		addEdge(list, v, v);
		if (v+N <= M*N)		/*arco para este*/
			addEdge(list, v, v+N);
			
		if (v-N > 0)		/*arco para oeste*/
			addEdge(list, v, v-N);

		if (v%N != 0)		/*arco para sul*/
			addEdge(list, v, v+1);

		if (v%N != 1)		/*arco para norte*/
			addEdge(list, v, v-1);

	}

	/*input verification*/		/*clean*/
	/*printf("%d colunas(M)\n%d linhas(N)\n", M, N);	*/
	/*for (v = 1; v <= M*N; v++){	*/
	/*	Item *a;	*/
	/*	a = (Item*) can_fail_malloc((int)sizeof(Item));	*/
	/*	printf("Vertice %d: ", v);	*/
	/*	for(a = list[v].prox; a != NULL; a = a->prox){	*/
	/*		printf("%d ", a->n);	*/
	/*	}	*/
	/*	printf("\n");	*/
	/*}	*/


	scanf("%d %d", &nS, &nC);

	for(i = 1; i <= nS; i++){
		scanf("%d %d", &m, &n);
		/*set S at mxn location on matrix*/
		vS = (m*N)-(N-n);
		Sup[vS] = 1;
	}

	for(j = 1; j <= nC; j++){
		scanf("%d %d", &m, &n);
		/*set C at mxn location on matrix*/
		vC = (m*N)-(N-n);
		Cid[vC] = 1;
	}

	/*input verification*/		/*clean*/
	/*for(v = 1; v <= M*N; v++){	*/
	/*	if(Sup[v]==1)	*/
	/*		printf("Vertice %d tem supermercado\n", v);	*/
	/*}	*/

	/*for(v = 1; v <= M*N; v++){	*/
	/*	if(Cid[v]==1)	*/
	/*		printf("Vertice %d tem cidadao\n", v);	*/
	/*}	*/
	

	/*function call (bfs on matrix)*/
	for(b = 1; b <= M*N; b++){
		if(Cid[b] == 1){
			/*printf("bfs start cid %d\n", b);*/ /*clean*/
			BFS(list, b);
		}
	}

	printf("%d\n", maxC);		/*output*/
	return 0;

}






