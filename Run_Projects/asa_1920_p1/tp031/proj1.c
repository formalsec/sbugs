/*tp93748
  tp93746*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 10

struct aluno{
	int i;
	struct aluno *next;
};

struct graph{
	int tamanho;
	struct aluno *turma;
};

struct stack{
	int topo;
	int tamanho;
	int *array;
};

struct fila{
	int *array;
	int topo;
	int fim;
};

int nr_alunos; 
struct graph *grafo;
int *notas;
int *visBfs;
int *d;
int *low;
int *visDfs;
struct stack *stack;
int sccCount = 0;
int sccIndex = 0;
struct fila *fila;

void createGraph(){
	int i;
	grafo = (struct graph*)malloc(sizeof(struct graph));
	grafo->tamanho = nr_alunos;
	grafo->turma = (struct aluno*)malloc(sizeof(struct aluno)*nr_alunos);
	d = (int*)malloc(sizeof(int)*nr_alunos);
	low = (int*)malloc(sizeof(int)*nr_alunos);
	visDfs = (int*)malloc(sizeof(int)*nr_alunos);
	visBfs = (int*)malloc(sizeof(int)*nr_alunos);
	for (i = 0; i < nr_alunos; i++){
		grafo->turma[i].i = i;
        grafo->turma[i].next = NULL;
        d[i] = -1;
        low[i] = -1;
        visDfs[i] = 1;
        visBfs[i] = 1;
	}
}

void destroyGraph(){
	free(visBfs);
	free(grafo->turma);
	free(grafo);
}

void connect(int src, int amigos){
	struct aluno *aux = &grafo->turma[src];
	while(aux->next != NULL){
		aux = aux->next;
	}
	aux->next = (struct aluno*)malloc(sizeof(struct aluno));
	aux->next->i = amigos;
	aux->next->next = NULL;
}

void printGraph(){
	int i;
	struct aluno *aux;
	for(i = 0; i < nr_alunos; i++){
		aux = &grafo->turma[i];
		while(aux != NULL){
			printf("%d -> ", aux->i);
			aux = aux->next;
		}
		printf("\n");
		printf("%d\n", low[i]);
	}
}

void printNotas(){
	int i;
	for(i = 0; i < nr_alunos; i++){
		printf("%d\n", notas[i]);
	}
}

void createStack(){
	stack = (struct stack*)malloc(sizeof(struct stack));
	stack->topo = -1;
	stack->tamanho = nr_alunos;
	stack->array = (int*)malloc(sizeof(int)*nr_alunos);
}

int stackEmpty(){
	if(stack->topo == -1){
		return 1;
	}
	else{
		return 0;
	}
}

int stackFull(){
	if(stack->topo == (stack->tamanho - 1)){
		return 1;
	}
	else{
		return 0;
	}
}

int pop(){
	if(!stackEmpty()){
		stack->topo--;
		return stack->array[stack->topo + 1];
	}
	else{
		printf("stack vazio\n");
		return -1;
	}
}

void push(int V){
	if(!stackFull()){
		stack->array[++stack->topo] = V;
	}
	else{
		printf("stack cheio\n");
	}
}

int inStack(int V){
	int i;
	for(i = 0; i <= stack->topo; i++){
		if(stack->array[i] == V){
			return 1;
		}
	}
	return 0;
}

void printStack(){
	int i;
	if(!stackEmpty()){
		for(i = 0; i <= stack->topo; i++){
			printf("%d", stack->array[i]);
		}
		printf("\n");
	}
}

void destroyStack(){
	free(stack->array);
	free(stack);
}

void createFila(){
	fila = (struct fila*)malloc(sizeof(struct fila));
	fila->array = (int*)malloc(sizeof(int)*nr_alunos);
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
	if(fila->fim == nr_alunos - 1){
		printf("fila cheia\n");
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

void printFila(){
	int i;
	for(i = fila->topo;i < fila->fim + 1;i++){
		printf("%d ", fila->array[i]);
	}
	printf("\n");
}

int min(int i, int e){
	if(i < e){
		return i;
	}
	else{
		return e;
	}
}

int max(int i, int e){
	if(i < e){
		return e;
	}
	else{
		return i;
	}
}

int bfs(int V){
	int i, maxl = notas[V];
	struct aluno *aux;
	visBfs[V] = 0;
	insert(V);
	while(!filaEmpty()){
		int topo = removeFila();
		aux = &grafo->turma[topo];
		while(aux->next != NULL){
			if(visBfs[aux->next->i]){
				visBfs[aux->next->i] = 0;
				insert(aux->next->i);
				maxl = max(maxl, notas[aux->next->i]);
			}
			aux = aux->next;
		}
	}
	for(i = 0; i < nr_alunos; i++){
		visBfs[i] = 1;
	}
	return maxl;
}

void dfs(int V){
	int i, node, maxl = 0;
	struct aluno *aux = &grafo->turma[V];
	push(V);
	d[V] = sccIndex;
	low[V] = sccIndex;
	sccIndex++;
	visDfs[V] = 0;

	while(aux->next != NULL){
		if(visDfs[aux->next->i]){
			dfs(aux->next->i);
		}
		if(inStack(aux->next->i)){
			low[V] = min(low[V], low[aux->next->i]);
		}
		aux = aux->next;
	}
	if(d[V] == low[V]){
		maxl = bfs(V);
		for(i = 0; i < nr_alunos; i++){
			node = pop();
			notas[node] = maxl;
			low[node] = d[V];
			if(node == V){
				break;
			}
		}
		sccCount++;
	}
}

void findScc(){
	int i;
	for(i = 0; i < nr_alunos; i++){
		if(visDfs[i]){
			dfs(i);
		}
	}
}

void processInput(){
	int amizades, i, nota, src, amigos;
	if(scanf("%d,%d", &nr_alunos, &amizades) != 2){
		perror("error reading number of students and friendships");
	}
	createGraph();
	createStack();
	createFila();
	notas = (int*)malloc(sizeof(int)*nr_alunos);
	for(i = 0; i < nr_alunos; i++){
		if(scanf("%d", &nota) != 1){
            perror("error reading grades");
        }
		notas[i] = nota;
	}
	for(i = 0; i < amizades; i++){
		if(scanf("%d %d", &src, &amigos) != 2){
            perror("error reading friendship");
        }
		connect(--src, --amigos);
	}	
}

int main(int argc, char const *argv[]){
	processInput();
	findScc();
	printNotas();
	destroyGraph();
	destroyStack();
	free(notas);
	return 0;
}