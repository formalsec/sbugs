/* Grupo 69
 Guilherme Nunes 89450
 Beatriz Feliciano 89417
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*Inicializacoes*/
typedef struct lista Lista;
typedef struct no No;
typedef struct v Vertice;
typedef struct queue Queue;
typedef struct fila Fila;

/*Variaveis globais*/
Vertice *grafo;

int nfornecedores, nabastecimentos, nligacoes;
int *infila;
int *estacoesaumenta;
int contador = 0;
Fila fila;

Fila *arestas;

/*Estruturas*/
struct lista{
	No *inicio;
	No *fim;

};

struct fila
{
	Queue *inicio;
	Queue *fim;
};

struct queue{
	int vertice;
	Queue *prox;
};

struct no{
	long int capacidade;
	long int fluxo;
	int destino;
	/*serve como identificador no caso de ser usado para queue*/
	No *prox;
};

struct v{
	Lista arestas;
	long int excesso; /*no inicio e' o equivalente 'a producao nos fornecedores*/
	int altura;
};


Queue* NovoQueue(int vertice)
{
	Queue *x = (Queue*)malloc(sizeof(struct queue));
	
	x->vertice = vertice;
	x->prox = NULL;
	
	return x;
}

Queue* insereFimQueue(Queue* fim, int vertice,  Queue **inicio)
{
 if(fim == NULL)/*caso a lista seja vazia o inicio e o fim serao iguais*/
 {
 	*inicio = NovoQueue(vertice);
 	return *inicio;
 }
 /*senao adiciona ao fim da lista e altera o ponteiro do fim da lista */
 fim->prox = NovoQueue(vertice);
 fim = fim->prox;
 return fim;
}

Queue* insereAresta(Queue* fim, int vertice,  Queue **inicio)
{

	Queue *x=(*inicio),*anterior = NULL,*aux;
	if(fim == NULL)/*caso a lista seja vazia o inicio e o fim serao iguais*/
	{

		*inicio = NovoQueue(vertice);

		return *inicio;
	}
	/*senao adiciona ao fim da lista e altera o ponteiro do fim da lista */
	while (x != NULL && x->vertice < vertice)
	{
		
		anterior = x;
		x = x->prox;
	}
	if (x == NULL && anterior != NULL)
	{

		fim->prox = NovoQueue(vertice);
		fim = fim->prox;
		return fim;
	}
	else if (x != NULL && anterior == NULL)
	{
		aux = *inicio;
		*inicio = NovoQueue(vertice);
		(*inicio)->prox = aux;
		return fim;

	}
	else
	{
		anterior->prox = NovoQueue(vertice);
		anterior->prox->prox = x;
		return fim;
	}
	
	
}
/*FUNCOES AUXILIARES LISTAS*/
No* Novo(int destino, long int capacidade, long int fluxo)
{
	No *x = (No *)malloc(sizeof(struct no));
	
	x->capacidade = capacidade;
	x->destino = destino;
	x->fluxo = fluxo;
	x->prox = NULL;
	
	return x;
}


No* insereFim(No* fim, int destino, long int capacidade, long int fluxo,  No **inicio)
{
 if(fim == NULL)/*caso a lista seja vazia o inicio e o fim serao iguais*/
 {
 	*inicio = Novo(destino, capacidade, fluxo);
 	return *inicio;
 }
 /*senao adiciona ao fim da lista e altera o ponteiro do fim da lista */
 fim->prox = Novo(destino, capacidade, fluxo);
 fim = fim->prox;
 return fim;
} 


void Push(int origem, No* destino)
{
	int d = grafo[origem].excesso;
	No *x = grafo[destino->destino].arestas.inicio;

	if (grafo[origem].excesso > (destino->capacidade - destino->fluxo))
		d = destino->capacidade - destino->fluxo;

	
	while (x != NULL && x->destino != origem)
		x=x->prox;
	
	destino->fluxo+=d;

	
	x->fluxo-=d;
					
	grafo[origem].excesso-=d;
	grafo[destino->destino].excesso+=d;

    if((destino->destino > 1) && (!infila[destino->destino]))
	    fila.fim = insereFimQueue(fila.fim, destino->destino, &(fila.inicio));
}

void Discharge(int vertice)
{
	No *viz = grafo[vertice].arestas.inicio;
	int min = grafo[viz->destino].altura;

	while(grafo[vertice].excesso > 0){

		if (viz == NULL)
		{
			if (grafo[vertice].altura < min+1)
				grafo[vertice].altura=min+1; /*Relable*/
			viz = grafo[vertice].arestas.inicio;
			while(viz->fluxo == viz->capacidade)
				viz = viz->prox;

			min = grafo[viz->destino].altura;
		}

		else if ((viz->fluxo < viz->capacidade) && (grafo[vertice].altura == grafo[viz->destino].altura+1)){
			Push(vertice, viz);

		}
			
		else
		{
			viz = viz->prox;
			if (viz != NULL && min > grafo[viz->destino].altura && (viz->fluxo < viz->capacidade))
				min = grafo[viz->destino].altura;	
		}
	}

}



void DFSvisit(int vertice)
{
	No *x;
	infila[vertice] = true;
	
	for (x = grafo[vertice].arestas.inicio; x!=NULL; x=x->prox)
	{
		if (x->destino > 0)
		{
			if (infila[x->destino] == false)
			{
				if (x->capacidade - x->fluxo != x->capacidade)
				{
					DFSvisit(x->destino);
				}
				else
				{
					if (vertice > nfornecedores+nabastecimentos+1 && x->destino == (vertice-nabastecimentos))
					{
						estacoesaumenta[x->destino-nfornecedores-2] = 1;
					}
					else if (x->destino > nfornecedores+nabastecimentos+1)
					{
						arestas[x->destino-nabastecimentos].fim = insereAresta(arestas[x->destino-nabastecimentos].fim,vertice,&(arestas[x->destino-nabastecimentos].inicio));
					}
					else
						arestas[x->destino].fim = insereAresta(arestas[x->destino].fim,vertice,&(arestas[x->destino].inicio));
				}
			}
		}
	}
}
void DFS()
{
	int i;
	for (i=0;i<nfornecedores+2*nabastecimentos+2;i++)
	{
		infila[i] = false;
	}

	DFSvisit(1);

}

int relabelToFront()
{	
	int fluxo = 0;
	Queue *u = fila.inicio;
	while (u != NULL)
	{

		Discharge(u->vertice);
		infila[u->vertice] = false;
		fila.inicio = fila.inicio->prox;
		free(u);
		u = fila.inicio;
	}
	fluxo = grafo[1].excesso;
	return fluxo;
}

/*PROGRAMA*/

int main(){
	int producao=0, capacidade=0, origem, destino, capacidadelig=0,fluxomaximo;
	int pos_source = 0, i = 0,flaglinda = 0;
	Queue *x;
	fila.fim = NULL;
	fila.inicio = NULL;
	if(scanf("%d %d %d", &nfornecedores, &nabastecimentos, &nligacoes))
	{
		if( (nfornecedores > 0) && (nabastecimentos >= 0) && (nligacoes >= 0))
		{

			grafo = (Vertice *)malloc(sizeof(Vertice)*(nfornecedores+2*nabastecimentos+2));
			infila = (int *)malloc(sizeof(int)*(nfornecedores+2*nabastecimentos+2));
			
			grafo[pos_source].altura = nfornecedores+2*nabastecimentos+2; 

			/*target -- hipermercado*/
			grafo[1].excesso = 0;
			grafo[1].altura = 0;

			for (i=0; i<nfornecedores+nabastecimentos*2+2;i++)
			{
				grafo[i].arestas.fim = NULL;
				grafo[i].arestas.inicio = NULL;
				infila[i] = false;
			}

			for(i = 2; i <=nfornecedores+1;i++){
				if( scanf("%d",&producao) && (producao >= 0) ){
					grafo[i].excesso = producao;
					grafo[i].altura = 0;
					grafo[pos_source].excesso -= producao;
					grafo[i].arestas.fim = insereFim(grafo[i].arestas.fim,pos_source,producao,0,&(grafo[i].arestas.inicio));
					grafo[pos_source].arestas.fim = insereFim(grafo[pos_source].arestas.fim, i, producao, producao, &(grafo[pos_source].arestas.inicio));
					/*adiciona fornecedor 'a queue*/
					fila.fim = insereFimQueue(fila.fim, i, &(fila.inicio));
					infila[i] = true;
				}
			}

			for(; i < (nfornecedores+nabastecimentos+2); i++){
				if( scanf("%d",&capacidade) && (capacidade >= 0) ){
					grafo[i].arestas.fim = insereFim(grafo[i].arestas.fim, i+nabastecimentos, capacidade, 0, &(grafo[i].arestas.inicio));
					grafo[i+nabastecimentos].arestas.fim = insereFim(grafo[i+nabastecimentos].arestas.fim,i,capacidade,capacidade,&(grafo[i+nabastecimentos].arestas.inicio));

					grafo[i+nabastecimentos].excesso = 0;
					grafo[i+nabastecimentos].altura = 0;
					grafo[i].excesso = 0;
					grafo[i].altura = 0;
				}
			}


			for(i=0; i < nligacoes; i++){
				if(scanf("%d %d %d", &origem, &destino, &capacidadelig)){

					if (origem > nfornecedores+1) 
						origem += nabastecimentos;/*ligar copia dos abastecimentos*/

                    grafo[origem].arestas.fim = insereFim(grafo[origem].arestas.fim, destino, capacidadelig, 0, &(grafo[origem].arestas.inicio));

						grafo[destino].arestas.fim = insereFim(grafo[destino].arestas.fim, origem, capacidadelig, capacidadelig, &(grafo[destino].arestas.inicio));
				}
			}

		}

		fluxomaximo = relabelToFront();
		printf("%d\n",fluxomaximo);
		estacoesaumenta = (int *)malloc(sizeof(int)*(nabastecimentos));
		arestas = (Fila*)malloc(sizeof(Fila)*(nabastecimentos+nfornecedores+2));
		for(i=0;i<nabastecimentos+nfornecedores+2;i++)
		{
			arestas[i].inicio = NULL;
			arestas[i].fim = NULL;
		}

		DFS();
		for(i=0;i<nabastecimentos;i++)
		{
			if (infila[nfornecedores+2+i] == false && estacoesaumenta[i] == 1)
			{
				if (flaglinda == 0)
				{
					flaglinda = 1;
				}
				else
				{
					printf(" ");
				}
				printf("%d",nfornecedores+2+i);
			}
		}
		printf("\n");/*
		for (i=1;i<2*nabastecimentos+nfornecedores+2;i++)
		{
			if (infila[i])
			{
				for (x2 = grafo[i].arestas.inicio; x2!=NULL;x2 = x2->prox)
				{
					if((x2->capacidade - x2->fluxo) == x2->capacidade && !infila[x2->destino] && x2->destino != i-nabastecimentos && x2->destino!= 0 )
						arestas[i].fim = insereAresta(arestas[i].fim,x2->destino,&(arestas[i].inicio));

				}

			}
		}
		for (i=1;i<nabastecimentos+nfornecedores+2;i++)
			for(x=arestas[i].inicio;x!=NULL;x=x->prox)
				printf("%d %d\n",i,x->vertice);
		*/
		for (i=0;i<nabastecimentos+nfornecedores+2;i++)
		{
			if (infila[i] == false && arestas[i].inicio != NULL)
			{
				for (x = arestas[i].inicio; x != NULL; x=x->prox)
				{
					printf("%d %d\n",i, x->vertice);
				}
			}
		}
	}
	return 0;
}
