#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <can_fail_malloc.h>


typedef struct Node
{
	int indice;
	int capacity;
	struct Node *next;
}Node;

typedef struct /*Queue*/
{
	int* numbers;
	int inicio;
	int fim;
	int size;
}Queue;


Node **Grafo;
int Avenidas,Ruas,Cidadaos,Supermercados;
int NumVertices=0;
Queue q;



void constroiRedeFluxo();
void addCidadaosSupermercados();
void printGrafo();
void addToList(int index, int cruzamento);
void addToQueue(Queue* tabela, int num);
int removeFromQueue(Queue* tabela);
void initQueue(Queue* tabela, int tamanho);
void freeQueue(Queue* tabela);
int encontraCaminhosDisjuntos();
int bfs(int * parent);
void swap(int index1, int index2);
void destroyList();
void lowerCapacity(int v1, int v2);

int main()
{
	int caminhosPossiveis;
	constroiRedeFluxo();
	addCidadaosSupermercados();
	/*printGrafo();*/
	initQueue(&q,NumVertices-1);
	caminhosPossiveis=encontraCaminhosDisjuntos();
	printf("%d\n", caminhosPossiveis);
	freeQueue(&q);
	destroyList();
	return 0;
}

void constroiRedeFluxo()
{
	scanf("%d %d", &Avenidas, &Ruas);
	NumVertices = (Avenidas * Ruas * 2) + 2;
	Grafo = (Node**)can_fail_calloc(NumVertices, sizeof(Node*));
	int i = 1, r=0, a=0;
	for(r=0 ; r<Ruas ; r++)
		for (a = 0; a < Avenidas; a++)
		{
			addToList(i, i + 1);
			i++;
			if (a!=0)
				addToList(i, i - 3);
			if (a!=Avenidas-1)
				addToList(i, i + 1);
			if (r!=0)
				addToList(i, i - (Avenidas * 2 + 1));
			if (r!=Ruas-1)
				addToList(i, i + (Avenidas * 2 - 1));
			i++;
		}
}

void addCidadaosSupermercados()
{
	int i, avenida, rua;
	scanf("%d %d", &Supermercados, &Cidadaos);
	if (Supermercados > Cidadaos)
	{
		for (i = 0; i < Supermercados; i++)
		{
			scanf("%d %d", &avenida, &rua);
			addToList((rua - 1) * Avenidas * 2 + avenida * 2, NumVertices - 1);
		}
		for (i = 0; i < Cidadaos; i++)
		{
			scanf("%d %d", &avenida, &rua);
			addToList(0, (rua - 1) * Avenidas * 2 + avenida * 2 - 1);
		}
	}
	else {
		for (i = 0; i < Supermercados; i++)
		{
			scanf("%d %d", &avenida, &rua);
			addToList(0, (rua - 1) * Avenidas * 2 + avenida * 2 - 1);
		}
		for (i = 0; i < Cidadaos; i++)
		{
			scanf("%d %d", &avenida, &rua);
			addToList((rua - 1) * Avenidas * 2 + avenida * 2, NumVertices - 1);
		}
	}
}

void addToList(int index, int cruzamento)
{
	Node* n = Grafo[index];
	/*printf("%d %d\n", index, cruzamento);*/
	while (n != NULL)
	{
		if (n->indice == cruzamento)
			return;
		n = n->next;
	}


	Node* novoNo = (Node*)can_fail_malloc(sizeof(Node));
	novoNo->indice = cruzamento;
	novoNo->capacity = 1;
	novoNo->next = Grafo[index];
	Grafo[index] = novoNo;



}

void removeFromList(int index1, int index2)
{
	Node* t1, * t2=NULL;
	for (t1 = Grafo[index1]; t1 != NULL && t1->indice != index2; t2=t1, t1 = t1->next)
		;
	if (t1 == NULL)
		printf("-5 euros");
	else if (t2 == NULL)
	{
		Grafo[index1] = t1->next;

	}
	else {
		t2->next = t1->next;
	}
	free(t1);
}


void destroyList()
{
	Node* t1, * t2;
	int i;
	for (i = 0; i < NumVertices; i++)
	{
		t1 = Grafo[i];
		while (t1 != NULL)
		{
			t2 = t1->next;
			free(t1);
			t1 = t2;
		}
	}
	free(Grafo);
}


void printGrafo()
{
	int i; Node* t;
	for (i = 0; i < NumVertices; i++)
	{
		printf("Indice:%d liga-se a:", i);
		for (t = Grafo[i]; t != NULL; t = t->next)
			printf("[%d] ", t->indice);
		putchar('\n');
	}
}

int bfs(int *parent)
{
	int *visitados,cruzamento;
	Node* t;
	visitados = (int*)can_fail_calloc(NumVertices, sizeof(int));
	addToQueue(&q,0);
	visitados[0] = 1;
	parent[0] = -1;
	while ((cruzamento = removeFromQueue(&q))!=-1)
	{

		for (t=Grafo[cruzamento];t!=NULL;t=t->next)
		{
			if (t->indice== NumVertices - 1)
			{
				parent[t->indice] = cruzamento;
				free(visitados);
				return 1;
			}
			if (visitados[t->indice] == 0 && t->capacity==1)
			{
				addToQueue(&q, t->indice);
				visitados[t->indice] = 1;
				parent[t->indice] = cruzamento;
			}
		}
	}
	free(visitados);
	return 0;
}

int encontraCaminhosDisjuntos()
{
	int *parent= (int*)can_fail_calloc(NumVertices, sizeof(int));
	int max_flow = 0,v1;
	while(bfs(parent) && max_flow<Cidadaos && max_flow < Supermercados)
	{
		for (v1 = NumVertices - 1; v1 != 0; v1 = parent[v1])
		{
			swap(parent[v1],v1);
		}
		q.inicio = 0;
		q.fim = 0;
		max_flow++;
	}
	return max_flow;
}


void lowerCapacity(int v1, int v2)
{
	Node* t;
	t = Grafo[v1];
	while (t->indice != v2)
		t = t->next;
	t->capacity = 0;
}

void initQueue(Queue* tabela, int tamanho)
{
	tabela->size = tamanho;
	tabela->inicio = 0;
	tabela->fim = 0;
	tabela->numbers = (int*)can_fail_malloc(sizeof(int) * tamanho);
}
void freeQueue(Queue* tabela)
{
	free(tabela->numbers);
}

void addToQueue(Queue* tabela, int num)
{
	if ((tabela->inicio - tabela->fim) % tabela->size == 1)
		printf("Erro");
	tabela->numbers[tabela->fim++] = num;
}


int removeFromQueue(Queue* tabela)
{
	if (tabela->inicio == tabela->fim)
		return -1;
	return tabela->numbers[tabela->inicio++];
}

void swap(int index1,int index2)
{
	removeFromList(index1, index2);
	addToList(index2, index1);
}
