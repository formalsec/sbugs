#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/*@author 57395	Tiago Ferreira tg024 ASA 18/19*/

#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

#define MAX 1000000

typedef struct item{
	int n;							/*id de vertice adjacente*/
	struct item* prox;	/*adjacencia de vertices*/
}Item;

int nV;			/*numero de vertices*/
int nE;			/*numero de arcos*/
int Vorig;	/*vertice de origem de 1 arco*/
int Vdest;	/*vertice de destino de 1 arco*/

Item list[MAX+1];

int pi[MAX+1];				/*array com parents de cada vertice(DFS*)*/
int d[MAX+1];					/*array com tempo de descoberta de cada vertice (DFS*)*/
int low[MAX+1];				/*array com low de cada vertice (DFS*)*/
int color[MAX+1];			/*array com cores de vertices (DFS*)	*/
int t;								/*DFS* timer*/
int artpoint[MAX+1];	/*array de verificacao se e vertice de articulacao*/
int maxVtree[MAX+1];	/*array com vertice maior de cada tree (DFS*)*/
int maxV = 0;					/*vertice maior de cada tree*/
int r = 0;						/*numero de redes do grafo (output 1)*/
int m = 1;						/*maior numero de ligacoes de rede#2 (output4)*/
int mT = 1;


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

int min(int a, int b){
	if(a < b)
		return a;
	return b;
}

int max(int a, int b){
	if(a > b)
		return a;
	return b;
}


void DFSutil(int u){
	Item *v;
	v = (Item*) can_fail_malloc((int)sizeof(Item));
	color[u] = GRAY;
	int nChild = 0;
	d[u] = low[u] = ++t;
	
	for(v = list[u].prox; v != NULL; v = v->prox){
		if(color[v->n] == WHITE ){
			mT++;
			nChild++;
			pi[v->n] = u;
			DFSutil(v->n);
			low[u] = min(low[u], low[v->n]);

			if(pi[u] == -1 && nChild > 1)								/*se vertice tem mais q 1 filho*/
				artpoint[u] = 1;													/*u ponto de articulacao*/
			else if(pi[u] != -1 && low[v->n] >= d[u])		/*se filhos teem arco q liga ao seu antecedente na arvore*/
							artpoint[u] = 1;										/*u ponto de articulacao*/
		} else if(v->n != pi[u])
						low[u] = min(low[u], d[v->n]);
	}
	maxV = max(maxV, u);
	maxVtree[r] = maxV;
}


void DFS(Item l){

	int i;	

	for(i=1; i<=nV; i++){
		color[i] = WHITE;
		pi[i] = -1;
	}
	t = 1;
	
	int j;
	for(j = 1; j <= nV; j++){		/*DFS* #2 excluding artpoint	*/		
		m = 1;										/*restart de profundidade de arvore*/
		if(artpoint[j] == 1){
			color[j] = BLACK;
		}
	}

	for(i = 1; i<=nV; i++){
		if(color[i] == WHITE){
			mT = 1;
			maxV = 0;
			DFSutil(i);
			r++;
			m = max(m, mT);			/*verificacao de maior rede#2 output4*/
		}
	}
}


void merge(int arr[], int l, int m, int r){
	int i, j, k;
	int n1 = m - l + 1;
	int n2 =  r - m;

	int L[n1], R[n2];

	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1+ j];
 
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2){
		if (L[i] <= R[j]){
			arr[k] = L[i];
			i++;
		} else {
			arr[k] = R[j];
			j++;
			}
		k++;
	}

	while (i < n1){
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2){
		arr[k] = R[j];
		j++;
		k++;
	}
}


void mergeSort(int arr[], int l, int r){
	if (l < r){
		int m = l+(r-l)/2;
		mergeSort(arr, l, m);
		mergeSort(arr, m+1, r);
		merge(arr, l, m, r);
	}
}


int main(int argc, char *argv[]){

	scanf("%d %d", &nV, &nE);

	int i, j, k, l;
	for(i=1; i<=nV; i++){			/*inicializaçao de list*/
		list[i].n = 0;
		list[i].prox = NULL;
	}

	for(j=1; j<=nE; j++){
		scanf("%d %d", &Vorig, &Vdest);
		addEdge(list, Vorig, Vdest);	/*acrescenta arco entre 2 vertices*/
		addEdge(list, Vdest, Vorig);
	}


	DFS(*list);


	int artcounter = 0;

	/*output*/

	printf("%d\n", r);		/*output 1*/

	mergeSort(maxVtree, 0, r-1);

	int printed = 0;
	for(k = 0; k < r; k++){		/*output 2*/
		if(printed){
				printf(" %d", maxVtree[k]);
		} else {
			printed++;
			printf("%d", maxVtree[k]);
		}
	}

	for(l = 1; l <= nV; l++){
		if(artpoint[l]==1)
			artcounter++;
	}

	printf("\n%d\n", artcounter);		/*output 3*/

	DFS(*list);

	printf("%d\n", m);			/*output4*/

	return 0;
}
