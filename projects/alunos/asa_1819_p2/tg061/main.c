#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER 10000

typedef struct node
{
    int dado;
    struct node* prox;
}node_t;

typedef struct
{
    node_t* inicio;
    node_t* fim;
    int size;
}list_t;

typedef list_t queue_t;

queue_t* initQueue();
void pushQueue(queue_t *queue, int data);
int popQueue(queue_t *queue);

/*Lista*/
list_t *iniciaLista(){
    list_t *newList = (list_t*) can_fail_malloc(sizeof(list_t));
    newList->inicio = NULL;
    newList->fim = NULL;
    newList->size = 0;

    return newList;
}

void addLista(list_t *lista, int dado){
    node_t *novoNode = (node_t *)can_fail_malloc(sizeof(node_t));
    novoNode->dado = dado;
    novoNode->prox = NULL;
    
    if(lista->inicio == NULL){
        lista->inicio = novoNode;
        lista->fim = novoNode;
    }
    else{
     lista->fim->prox = novoNode;
     lista->fim = novoNode;   
    }
    
    lista->size += 1;
}

node_t *encontrarLista(list_t *lista, int index)
{
    int i = 0;
    node_t *node = lista->inicio;

    if (index >= lista->size || index < 0)
        return NULL;

    while(i<index){
        node = node->prox;
        i++;
    }
    
    return node;
}

int encontrarIndice(list_t *lista, int dado){
    int sucesso = -1, i=0;
    node_t *node = lista->inicio;
    
    while(i < lista->size)
    {
        if(node->dado == dado)
            return i;
        node = node->prox;
        i++;
    }
    return sucesso;
}

int obterLista(list_t *lista, int index){
    node_t* node = encontrarLista(lista, index);

    if(node == NULL)
        return -1;

    return node->dado;
}

void mudarLista(list_t *lista, int index, int novoDado){
    node_t *node = encontrarLista(lista, index);
    node->dado = novoDado;
}

int removeLista(list_t *lista, int index)
{
    int sucesso = 1;
    node_t *currNode = encontrarLista(lista, index);
    node_t* preNode = encontrarLista(lista, index - 1);
    if(currNode==NULL)
        return 0;
    if(index == 0){
        lista->inicio = currNode->prox;
    }
    else{
        preNode->prox = currNode->prox;
    }
    
    free(currNode);
    return sucesso;
}

void imprimLista(list_t *lista)
{
    node_t *node = lista->inicio;

    for (int i = 0; i < lista->size; i++)
    {
        printf("%d ", node->dado);
        node = node->prox;
    }
}
/*queue*/
queue_t* initQueue(){
    queue_t* queue = (queue_t*) iniciaLista();
    return queue;
}

void pushQueue(queue_t* queue, int dado){
    addLista((list_t*)queue, dado);
}

int popQueue(queue_t* queue){
    list_t* lista = (list_t*) queue;
    int dado = obterLista(lista, 0);
	
    removeLista(lista, 0);
    return dado;
}




/*PRINCIPAL*/

int numConexoes;
int numProviders;
int numDistribuicoes;
int numVertices;
int *currentVertice,*excesso,*altura;
queue_t *verticesQueue;
list_t **fluxo, **capacidade,**listAdj;

list_t **initMatrix(){
    list_t **lista = (list_t **)can_fail_malloc(numVertices * sizeof(list_t*));
	int i = 0;
	while(i<numVertices)
	{
		lista[i] = iniciaLista();
		i++;
	}
    return lista;
}

int *initArray(){
    int *array = (int *)can_fail_malloc(numVertices * sizeof(int));
    return array;
}
void addListaAdj(int u, int v){
	addLista(listAdj[u], v);
    addLista(listAdj[v], u);
}
void addListaFluxo(int u, int v, int c){
	addLista(fluxo[u], 0);
    addLista(fluxo[v], c);
}
void addListaCapacidade(int u, int v, int c){
	addLista(capacidade[u], c);
    addLista(capacidade[v], c);
}
void addCapacidade(int u, int v, int numeroCapacidade){
	addListaAdj(u,v);
	addListaFluxo(u,v, numeroCapacidade);
	addListaCapacidade(u,v, numeroCapacidade);
}
void mudarFluxo(int u, int v, int fluxo_number){
    int index = encontrarIndice(listAdj[u], v);
    mudarLista(fluxo[u], index, fluxo_number);
}
		
int obterFluxo(int u, int v){
    int index;
	index = encontrarIndice(listAdj[u], v);
    return obterLista(fluxo[u], index);
}

int obterCapacidade(int u, int v){
    return obterLista(capacidade[u], encontrarIndice(listAdj[u], v));
}
			
int eDistribuicao(int v){
    int inicio=2;
    int fim;
	
	inicio = inicio + numProviders;
	fim	= inicio + numDistribuicoes;
	
    return (v <= fim) && (v >= inicio);
}

int obterDistribuOut(int v){
    return v + numDistribuicoes;
}

int minimo(int a, int b)
{
    if(a < b){
        return a;
    }
    else { 
        return b;
    } 
}

void fazerGrafico()
{
	char input_line[BUFFER], input_line2[BUFFER];
    char *chave, *chave2;
	int u, v, numeroCapacidade;
    int capProvider;
    int provider = 2;
	int distributor_capacidade;
    int in = numProviders + 2;
    int out = in + numDistribuicoes;
    scanf("%d %d %d",&numProviders,&numDistribuicoes,&numConexoes);
    numVertices = 2 + numProviders + 2 * numDistribuicoes;
	
    currentVertice = initArray();
    altura = initArray();
    excesso = initArray();
    listAdj = initMatrix();
    capacidade = initMatrix();
    fluxo = initMatrix();
    verticesQueue = initQueue();
	
	fgets(input_line, BUFFER, stdin);
    chave = strtok(input_line, " ");

    while (chave != NULL){
        capProvider = atoi(chave);
        addCapacidade(0, provider, capProvider);
        chave = strtok(NULL, " ");
        provider += 1;
	}	
    fgets(input_line2, BUFFER, stdin);
	for(chave2 = strtok(input_line2, " ");chave2 != NULL;in+=1){
        distributor_capacidade = atoi(chave2);
        addCapacidade(in, out, distributor_capacidade);
        out += 1;
		chave2 = strtok(NULL, " ");
    }
	
    for (int i = 0; i < numConexoes; i++){
        scanf("%d %d %d", &u, &v, &numeroCapacidade);
        if(u == 1 && eDistribuicao(v)){
            addCapacidade(u, obterDistribuOut(v), numeroCapacidade);
        }
        else if(v == 1 && eDistribuicao(u)){
            addCapacidade(obterDistribuOut(u), v, numeroCapacidade);
        }
        else{
            addCapacidade(u, v, numeroCapacidade);
        } 
    }
}
void push(int u, int v)
{
    int d = minimo(excesso[u], obterCapacidade(u,v) - obterFluxo(u,v));
    int d1 = obterCapacidade(u,v) + d;
    int d2 = obterCapacidade(v,u) - d;
    
    mudarFluxo(u,v,d1);
    mudarFluxo(v,u,d2);
    excesso[u] -= d;
    excesso[v] += d;
    if (d && excesso[v] == d)
        pushQueue(verticesQueue,v);
}

void relabel(int u){
    int d = 1000000000;
    for(int i = 0;i<numVertices;i++){
        if(obterCapacidade(u,i) - obterFluxo(u,i) > 0)
            d = minimo(d,altura[i]);
    }
    if(d < 1000000000)
        altura[u] = d+1;
}

void discharge(int v)
{
    while(excesso[v]>0)
    {
        int v = currentVertice[v];
        if(v == 0){
            relabel(v);
            currentVertice[v]=0;
        }
        else
        {
            if(obterCapacidade(v,v) - obterFluxo(v,v) > 0 && altura[v] > altura[v])
                push(v,v);
            else
                currentVertice[v]++;
        }
    }
}

void preencherQueue()
{	int v = 1;
	while(v<numVertices){
		pushQueue(verticesQueue, v);
		v++;
	}
}

void prefluxo()
{
    int v, numeroCapacidade, i=0;
	while(i<numVertices){
		altura[i] = 0;
		currentVertice[i] = 0;
		excesso[i] = 0;
	}
    altura[0] = numVertices;
    for(int i = 0; i < listAdj[0]->size; i++){
        v = obterLista(listAdj[0], i);
        numeroCapacidade = obterLista(listAdj[0], i);
        mudarFluxo(0, v, numeroCapacidade);
        mudarFluxo(v, 0, 0);
    }
}

void relabeltofront()
{
    int v, old_altura;
    prefluxo();
    preencherQueue();
    v = popQueue(verticesQueue);
    while(v != 0){
        old_altura = altura[v];
        discharge(v);

        if(altura[v] > old_altura){
            pushQueue(verticesQueue, v);
        }
        v = popQueue(verticesQueue);
    }
}

int main()
{
    fazerGrafico();
    relabeltofront();
}