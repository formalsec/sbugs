/*93748 - Rafael Candeias
  93746 - Pedro Marques*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct edge{
	int v;/*onde vai*/
	int cap;
	struct edge *next;
}edge;

typedef struct{
	int tamanho;
	edge **matriz;
}graph;

typedef struct{
	int *array;
	int topo;
	int fim;
}queue;

int maxflow = 0;
graph *grafo;
queue *fila;
int *vis;
int *pi;
int avenidas;
int ruas;
int nr_cruzamentos;

void connect(int i1, int i2, int c){
	if(grafo->matriz[i1] == NULL){
		grafo->matriz[i1] = malloc(sizeof(edge));
		grafo->matriz[i1]->v = i2;
		grafo->matriz[i1]->cap = c;
		grafo->matriz[i1]->next = NULL;
	}
	else{
		edge *aux = grafo->matriz[i1];
		while(aux->next != NULL){
			aux = aux->next;
		}
		aux->next = malloc(sizeof(edge));
		aux->next->v = i2;
		aux->next->cap = c;
		aux->next->next = NULL;
	}
}

int findCruzamento(int m, int n){
	if(m > 0 && m <= avenidas && n > 0 && n <= ruas){
		return (m - 1)*ruas*2 + (n - 1)*2;
	}
	return -1;
}

void createGraph(){
	int i, aux, auxc, m = 1, n = 1;
	grafo = malloc(sizeof(graph));
	grafo->tamanho = nr_cruzamentos*2 + 2;
	grafo->matriz = malloc(sizeof(edge*) * grafo->tamanho);
	vis = malloc(sizeof(int)*grafo->tamanho);
	pi = malloc(sizeof(int)*grafo->tamanho);
	for(i = 0; i < grafo->tamanho; i++){
		grafo->matriz[i] = NULL;
		vis[i] = 1;
	}
	for(i = 0; i < nr_cruzamentos; i++){
		aux = findCruzamento(m,n);
		connect(aux, aux+1, 1);/*vin -> vout(cap = 1)*/
		connect(aux+1,aux, 0);/*vout -> vin(cap = 0)*/
		auxc = findCruzamento(m, n - 1);/*ligacao com o de cima*/
		if(auxc != -1){
			connect(aux+1, auxc, 1);
			connect(auxc, aux+1, 0);
		}
		auxc = findCruzamento(m, n + 1);/*ligacao com o de baixo*/
		if(auxc != -1){
			connect(aux+1, auxc, 1);
			connect(auxc, aux+1, 0);
		}
		auxc = findCruzamento(m - 1, n);/*ligacao com o de esquerda*/
		if(auxc != -1){
			connect(aux+1, auxc, 1);
			connect(auxc, aux+1, 0);
		}
		auxc = findCruzamento(m + 1, n);/*ligacao com o de direita*/
		if(auxc != -1){
			connect(aux+1, auxc, 1);
			connect(auxc, aux+1, 0);
		}
		if(n == ruas){
			m++;
			n = 0;
		}
		n++;
	}
}

void printGraph(){
	int i;
	edge *aux;
	for(i = 0; i < grafo->tamanho; i++){
		aux = grafo->matriz[i];
		printf("%d -> ", i);
		while(aux != NULL){
			printf("%d(%d) -> ", aux->v, aux->cap);
			aux = aux->next;
		}
		printf("\n");
	}
}

void createFila(){
	fila = malloc(sizeof(queue));
	fila->array = malloc(sizeof(int)*grafo->tamanho);
	fila->topo = -1;
	fila->fim = -1;
}

void cleanFila(){
	fila->topo = -1;
	fila->fim = -1;
}

int filaEmpty(){
	if(fila->fim == -1){
		return 1;
	}
	else{
		return 0;
	}
}

void insert(int i){
	if(fila->fim == grafo->tamanho - 1){
		/*printf("fila cheia\n");*/
	}
	else{
		if(fila->topo == -1){
			fila->topo = 0;
		}
		fila->fim++;
		fila->array[fila->fim] = i;
	}
}

int removeFila(){
	int i;
	if(filaEmpty()){
		printf("fila vazia");
		i = -1;
	}
	else{
		i = fila->array[fila->topo];
		fila->topo++;
		if(fila->topo > fila->fim){
			fila->topo = -1;
			fila->fim = -1;
		}
	}
	return i;
}

int inFila(int V){
	int i;
	for(i = fila->topo; i <= fila->fim; i++){
		if(fila->array[i] == V){
			return 1;
		}
	}
	return 0;
}

void printFila(){
	int i;
	for(i = fila->topo; i < fila->fim + 1; i++){
		printf("%d ", fila->array[i]);
	}
	printf("\n");
}

int bfs(int V){
	edge *aux;
	vis[V] = 0;
	insert(V);
	while(!filaEmpty()){
		int topo = removeFila();
		aux = grafo->matriz[topo];
		while(aux != NULL){
			if(vis[aux->v] && aux->cap != 0){
				insert(aux->v);
				vis[aux->v] = 0;
				pi[aux->v] = topo;
				if(aux->v == grafo->tamanho - 1){
					maxflow++;
					return 1;
				}
			}
			aux = aux->next;
		}
	}
	return 0;
}

void caminho(int i1, int i2, int c){
	edge *aux;
	aux = grafo->matriz[i1];
	while(aux != NULL){
		if(aux->v == i2){
			aux->cap = c;
		}
		aux = aux->next;
	}
}

void edmundsKarp(){
	int i;
	edge *aux;
	aux = grafo->matriz[grafo->tamanho - 2];
	while(bfs(grafo->tamanho - 2)){
		cleanFila();
		for(i = 0; i < grafo->tamanho; i++){
			vis[i] = 1;
		}
		i = pi[grafo->tamanho - 1];
		caminho(i, grafo->tamanho - 1, 0);
		caminho(grafo->tamanho - 1, i, 1);
		while(i != grafo->tamanho - 2){
			caminho(pi[i], i, 0);
			caminho(i, pi[i], 1);
			i = pi[i];
		}
		aux = aux->next;
	}
}

void processInput(){
	int i, M = 0, N = 0, S = 0, C = 0;
	if(scanf("%d %d", &M, &N) != 2){
		perror("invalid input");
	}
	nr_cruzamentos = M*N;
	avenidas = M;
	ruas = N;
	createGraph();
	createFila();
	if(scanf("%d %d", &S, &C) != 2){
		perror("invalid input");
	}
	for(i = 0; i < S; i++){
		if(scanf("%d %d", &M, &N) != 2){
			perror("invalid input");
		}
		connect(findCruzamento(M, N) + 1, grafo->tamanho - 1, 1);/*vout->end*/
	}
	for(i = 0; i < C; i++){
		if(scanf("%d %d", &M, &N) != 2){
			perror("invalid input");
		}
		connect(grafo->tamanho - 2, findCruzamento(M, N), 1);/*start->vin*/
	}
}

int main(int argc, char const *argv[]){
	processInput();
	edmundsKarp();
	printf("%d\n", maxflow);
	return 0;
}