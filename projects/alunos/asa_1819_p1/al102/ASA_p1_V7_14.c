#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>                                                              
#include <string.h>                                                                                 
#include <stdlib.h>

struct router{
	int id;
	int routerPai;
	int visitado;
	int tempoDesc;
	int menorTempoDesc;
	int C_Router;
	struct router *prox;
};
typedef struct router *ListaRouters;

struct rede{
	int N_routers;
	ListaRouters *adjacencias;
};
typedef struct rede *Rede;

int N_routers;
int nRoutersSubRede = 0;
int max_subRede = 0;

Rede criaRede(int N_routers){
	Rede r = can_fail_malloc (sizeof(struct rede));
	int router;
	r->N_routers = N_routers;
	r->adjacencias = can_fail_malloc (N_routers*sizeof(struct router));
	for (router=0; router<N_routers; router++){
		r->adjacencias[router] = NULL;
	}
	return r;
}

ListaRouters criaRouter(int id, int routerPai, int visitado, int tempoDesc, int menorTempoDesc, int C_Router, ListaRouters prox){
	ListaRouters router = can_fail_malloc (sizeof(struct router));
	router->id = id;
	router->routerPai = routerPai;
	router->visitado = visitado;
	router->tempoDesc = tempoDesc;
	router->menorTempoDesc = menorTempoDesc;
	router->C_Router = C_Router;
	router->prox = prox;
	return router;
}

void libertaRede(Rede r){
	int router;
	if (r->adjacencias != NULL){
		ListaRouters x;
		for (router=0; router<N_routers; router++){
			while (r->adjacencias[router] != NULL){
				x = r->adjacencias[router];
				r->adjacencias[router]=r->adjacencias[router]->prox;
				free(x);
			}
		}
		free(r->adjacencias);
	}
	free(r);
}

int insereLigacao(Rede r, int router1, int router2){
	r->adjacencias[router1-1] = criaRouter(router2, 0, 0, 0, 0, 0, r->adjacencias[router1-1]);
	return 0;
}

void readInput(Rede r){
	int M_ligacoes;
	int i;
	int u, v;
    scanf("%d", &M_ligacoes);
    for (i=0; i<M_ligacoes; i++){
    	scanf("%d", &u);
		getchar();
    	scanf("%d", &v);
    	insereLigacao(r, u, v);
    	insereLigacao(r, v, u);
    }
}

int minimo(int a, int b){
	return a < b ? a : b;
}

void buscaProfundidadeRede(Rede r, int router){
	static int tempo = 1;
	int ligacoes = 0;
	ListaRouters l;
	if (router > max_subRede){
		max_subRede = router;
	}
	r->adjacencias[router-1]->visitado = 1;
	r->adjacencias[router-1]->menorTempoDesc = tempo;
	r->adjacencias[router-1]->tempoDesc = tempo++;
	for (l=r->adjacencias[router-1]; l!=NULL; l=l->prox){
		if (r->adjacencias[l->id-1]->visitado == 0){
			ligacoes++;
			r->adjacencias[l->id-1]->routerPai = router;
			buscaProfundidadeRede(r, l->id);
			r->adjacencias[router-1]->menorTempoDesc = minimo(r->adjacencias[router-1]->menorTempoDesc, 
															  r->adjacencias[l->id-1]->menorTempoDesc);
			if (r->adjacencias[router-1]->routerPai == 0 && ligacoes > 1){
				r->adjacencias[router-1]->C_Router = 1;
			} else if (r->adjacencias[router-1]->routerPai != 0 && 
					   r->adjacencias[l->id-1]->menorTempoDesc >= r->adjacencias[router-1]->tempoDesc){

				r->adjacencias[router-1]->C_Router = 1;
			}
		} else if (l->id != r->adjacencias[router-1]->routerPai){
			r->adjacencias[router-1]->menorTempoDesc = minimo(r->adjacencias[router-1]->menorTempoDesc, 
															  r->adjacencias[l->id-1]->tempoDesc);
		}
	}
}

void insertionSort(int lista[], int n){
	int i, chave, j;
	for (i=1; i<n; i++){
		chave = lista[i];
		j = i-1;
		while (j >= 0 && lista[j] > chave){
			lista[j+1] = lista[j];
			j = j-1;
		}
		lista[j+1] = chave;
	}
}

void buscaProfundidadeRede2(Rede r, int router){
	r->adjacencias[router-1]->visitado = 1;
	ListaRouters l;
	for (l=r->adjacencias[router-1]; l!=NULL; l=l->prox){
		if (r->adjacencias[l->id-1]->visitado == 0 && r->adjacencias[l->id-1]->C_Router == 0){
			nRoutersSubRede++;
			buscaProfundidadeRede2(r, l->id);
		}
	}
}

void printOutput(Rede r){
	int router;
	int R_subRedes = 0;
	int maxSubRedes[N_routers];
	int indice=0;
	int num_C_Routers = 0;
	ListaRouters l;
	int mRoutersSubRede = 0;

	memset(maxSubRedes, 0, sizeof(maxSubRedes));
	for (router=1; router<=N_routers; router++){
		if (r->adjacencias[router-1]->visitado == 0){
			max_subRede = 0;
			buscaProfundidadeRede(r, router);
			R_subRedes++;
			if (max_subRede != 0){
				maxSubRedes[indice++] = max_subRede;
			}
		}
	}
	insertionSort(maxSubRedes, indice);
	printf("%d\n", R_subRedes);
	for (router=0; router<indice-1; router++){
		printf("%d ", maxSubRedes[router]);
	}
	printf("%d\n", maxSubRedes[router]);
	for (router=0; router<N_routers; router++){
 		if (r->adjacencias[router]->C_Router == 1){
 			num_C_Routers++;
 		}
 	}
 	printf("%d\n", num_C_Routers);
 	for (router=0; router<N_routers; router++){
	 	for (l=r->adjacencias[router]; l!=NULL; l=l->prox){
			l->visitado = 0;
		}
	}
 	for (router=1; router<=N_routers; router++){
 		nRoutersSubRede = 1;
		if (r->adjacencias[router-1]->visitado == 0 && r->adjacencias[router-1]->C_Router == 0){
		 	buscaProfundidadeRede2(r, router);
		}
		if (nRoutersSubRede > mRoutersSubRede){
			mRoutersSubRede = nRoutersSubRede;
		}
	}
	printf("%d\n", mRoutersSubRede);
}

int main(){

	scanf("%d", &N_routers);
	Rede r;
	r = criaRede(N_routers);
	readInput(r);
	printOutput(r);
	libertaRede(r);
	return 0;
}