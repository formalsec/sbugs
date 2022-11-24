#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/*@author 57395	Tiago Ferreira tg054 ASA 19/20*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 1000000

#define WHITE 0
#define GRAY 1

typedef struct item{
	int n;					/*id de vertice adjacente*/
	struct item* prox;		/*adjacencia de vertices*/
}Item;

int nV;			/*numero de vertices*/
int nE;			/*numero de arcos*/
int Vorig;		/*vertice de origem de 1 arco*/
int Vdest;		/*vertice de destino de 1 arco*/

Item list[MAX+1];		/*graph*/

int pi[MAX+1];				/*array com parents de cada vertice(DFS*)*/
int d[MAX+1];				/*array com tempo de descoberta de cada vertice (DFS*)*/
int low[MAX+1];				/*array com low de cada vertice (DFS*)*/
int color[MAX+1];			/*array com cores de vertices (DFS*)	*/
int t;						/*DFS* timer*/
int w[MAX+1];				/*array 'peso' de verice*/

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
			nChild++;
			pi[v->n] = u;
			DFSutil(v->n);
			low[u] = min(low[u], low[v->n]);
		} else {
			if(v->n != pi[u])
				low[u] = min(low[u], d[v->n]);
		}
		w[u] = max(w[u], w[v->n]);
	}
}

void DFS(Item l){
	int i;
	for(i=1; i<=nV; i++){
		color[i] = WHITE;
		pi[i] = -1;
	}
	t = 0;

	for(i = 1; i<=nV; i++){
		if(color[i] == WHITE){
			DFSutil(i);
		}
	}
}


int main(int argc, char *argv[]){

	scanf("%d,%d", &nV, &nE);	/*input 1 */

	int i, j, k;
	for(j = 1; j <= nV; j++)	/*input 2 *nV */
		scanf("%d", &w[j]);

	for(i = 1; i <= nV; i++){			/*inicializaçao de list*/
		list[i].n = 0;
		list[i].prox = NULL;
	}

	for(j = 1; j <= nE; j++){				/*input 3 *nE */
		scanf("%d %d", &Vorig, &Vdest);
		addEdge(list, Vorig, Vdest);	/*acrescenta arco entre 2 vertices*/
	}

	DFS(*list);	

	int printed = 0;
	for(k = 1; k <= nV; k++){		/*output*/
		if(printed){
				printf("\n%d", w[k]);
		} else {
			printed++;
			printf("%d",w[k]);
		}
	}
	printf("\n");
	return 0;
}
