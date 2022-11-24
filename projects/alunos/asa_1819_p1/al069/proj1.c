#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
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


/*Estruturas*/
struct lista{
	No *inicio;
	No *fim;

};

struct no{
	int vertice;
	No *prox;
};

/*VARIAVEIS GLOBAIS*/
int nrouters = 0, *low, n_scc = 0,*maxscc, descTemp = 1, *d, *parente,n_ptoart=0,
max_aux = 0,max_art=0;
bool *ptoart;
Lista *adj;

/*FUNCOES AUXILIARES LISTAS*/
No* Novo(int vertice)
{
	No *x = (No *)can_fail_malloc(sizeof(struct no));
	
	x->vertice = vertice;
	x->prox = NULL;
	
	return x;
}

No* insereFim(No* fim, int vertice ,No **inicio)
{
 if(fim == NULL)/*caso a lista seja vazia o inicio e o fim serao iguais*/
 {
 	*inicio = Novo(vertice);
 	return *inicio;
 }
 /*senao adiciona ao fim da lista e altera o ponteiro do fim da lista */
 fim->prox = Novo(vertice);
 fim = fim->prox;
 return fim;
} 

void eliminartudo()
{	
	int i;
	No *t;
	No *aux;
	for (i = 0; i<nrouters;i++)
	{
		for(t = adj[i].inicio; t != NULL;)
		{
			adj[i].inicio = t->prox;
			aux = t;
			t = t->prox;
			free(aux);
		}
		adj[i].fim = adj[i].inicio;
		
	}
	free(adj);
	free(maxscc);
	free(d);
	free(low);
	free(parente);
	free(ptoart);
}


void mergesort(int a[],int l,int m, int r)
{
	int i,j,k,*aux;
	aux = (int *)can_fail_malloc(sizeof(int)*n_scc);
	for (i=m+1;i > l; i--)
		aux[i-1] = a[i-1];
	for (j=m; j<r;j++)
		aux[r+m-j] = a[j+1];
	for (k = l; k <=r; k++)
		if (aux[j] < aux[i])
			a[k] = aux[j--];
		else
			a[k] = aux[i++];
	free(aux);
}
void merge(int a[],int l,int r)
{
	int m = (r+l)/2;
	if (r <= l) return;
	merge(a,l,m);
	merge(a,m+1,r);
	mergesort(a,l,m,r);
}

void Inicializacoes(int flag)
{
	int i;
	for(i = 0; i < nrouters; i++) {
		d[i] = -1;
		low[i] = 0;
		parente[i] = 0;
		if (flag == 1){
			adj[i].inicio = NULL;
			adj[i].fim = NULL;
			ptoart[i] = false;
		}
	}
}
int min(int atual, int posterior)
{
	if (atual < posterior)
		return atual;
	return posterior;
}
/* ------------------------- tarjan ---------------------------------
| Aplica o algoritmo Tarjan ao grafo que foi dado pelo utilizador
------------------------------------------------------------------ */
void tarjan(int atual,int flag) {
	No *i;
	int filhos = 0;
	if ((!ptoart[atual] && flag == 2 )|| flag == 1)
	{
		if (d[atual] == -1) {
			if (flag == 2 )
				max_aux++;
			d[atual] = low[atual] = descTemp++;
			if (max_aux < (atual+1) && flag == 1)
				max_aux = atual+1;
		}

		

		for (i = adj[atual].inicio;i!=NULL; i = i->prox) {
			if(d[i->vertice - 1] == -1){
				filhos++;
				parente[i->vertice-1] = atual+1;
				tarjan(i->vertice - 1,flag);
				low[atual] = min(low[atual], low[i->vertice - 1]);
				if (flag == 1 && ptoart[atual] == false && ((parente[atual] == 0 && filhos >1) ||(parente[atual] != 0 &&  
					low[i->vertice-1] >= d[atual] )))
				{
					ptoart[atual] = true;
					n_ptoart++;
				}	
				
			}
			else if (i->vertice != parente[atual])
				low[atual]  = min(low[atual], d[i->vertice-1]);
		}
	}
}
/*PROGRAMA*/

int main(){
	int nligacoes = 0,i,origem,destino;	
	if (!scanf("%d",&nrouters)){
		printf("Tem de colocar um número de routers e tem de ser igual ou");
		printf(" superior a 2\n");
		exit(EXIT_FAILURE);
	}

	if (!scanf("%d",&nligacoes)){
		printf("Tem de colocar um número de ligações e tem de ser igual ou");
		printf(" superior a 1\n");
		exit(EXIT_FAILURE);
	}



	adj = (Lista *)can_fail_malloc(sizeof(Lista)*nrouters);
	low = (int *)can_fail_malloc(sizeof(int)*nrouters);
	d = (int *)can_fail_malloc(sizeof(int)*nrouters);
	maxscc = (int *)can_fail_malloc(sizeof(int)*nrouters);
	parente = (int *)can_fail_malloc(sizeof(int)*nrouters); 
	ptoart = (bool *)can_fail_malloc(sizeof(bool)*nrouters); 
	Inicializacoes(1);
	for (i = 0; i < nligacoes; i++){
		if ((!scanf("%d %d",&origem,&destino)) || origem < 1 || 
			origem > nrouters || destino < 1 || destino > nrouters)
		{
			printf("O identificador do router tem de estar entre 1 e %d",
				nrouters);
			exit(EXIT_FAILURE);
		}
		adj[origem-1].fim = insereFim(adj[origem-1].fim,destino,
			&(adj[origem-1].inicio));
		adj[destino-1].fim = insereFim(adj[destino-1].fim,origem,
			&(adj[destino-1].inicio));
	}



	for(i = 0; i < nrouters; i++) {
		if (d[i] == -1){
			max_aux = 0;
			n_scc++;
			tarjan(i,1);
			maxscc[n_scc-1]=max_aux;
		}
	}
	Inicializacoes(2);
	for(i=0;i < nrouters;i++)
	{
		if (d[i] == -1){
			max_aux = 0;
			tarjan(i,2);
			if (max_aux > max_art)
				max_art = max_aux;

		}
	}
	merge(maxscc,0,n_scc-1);
	printf("%d\n",n_scc);
	for (i=0;i<n_scc-1;i++)
		printf("%d ",maxscc[i]);
	printf("%d\n",maxscc[n_scc-1]);
	printf("%d\n",n_ptoart);
	printf("%d\n",max_art);
	eliminartudo();
	return 0;
}