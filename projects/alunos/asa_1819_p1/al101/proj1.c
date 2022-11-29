#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/*
 *	Analise e Sintese de Algoritmos
 *	2018/19
 *	Projeto 1
 *	Grupo 101
 *		87629 - Andre Leitao
 *		87697 - Pedro Bigodinho
 *
 */


#include <stdio.h>
#include <stdlib.h>

#define NIL -1


typedef struct arco* Arco;
typedef struct router* Vertice;
typedef struct ligacao* Ligacao;
typedef struct IdSubRede* IdSCC;

struct ligacao {
	/** Estrutura para a pilha de arcos para o BCC */
	int v, w;
	Ligacao next;
};

struct arco {
	int v;
	Arco next;
};

struct router {
	/** depth corresponde ao valor da profundidade e low o vertice visitado mais cedo (o vertice
	com minimo tempo de pesquisa) que pode ser alcancado na sub-arvore cuja raiz e' o vertice atual */
	int id, low, depth, parent;
	char stackMember, newBCC;	/* Boolean */
	Arco a;
};

struct IdSubRede {
	int id;
	IdSCC next;
};

typedef struct rede {
	int numVert;
	Vertice* adjacencias;
}* Grafo;


IdSCC listSCC = NULL;	/* Linked List dos ID's das sub-redes */
Arco stSCC 	  = NULL;	/* Stack para as Componentes Fortemente Ligadas */
Ligacao stBCC = NULL;	/* Stack para as BiConnected Components */

int numSCC=0,
	numRoutersRobustos=0,
	numMaxRoutersBCC=0,
	currNumComp=0;		/* Numero atual de componentes do grafo */


/* Funcoes-Prototipo */
Grafo readInput();
Grafo GraphInit(int V, int E);
void  InsertEdge(Grafo g, int v, int w);
Arco  InsertBegin(Arco head, int v);
void  SCC(Grafo g);
void  BCC(Grafo g, int router, int profundidade);
void  freeRede(Grafo g);
void  freeArcos(Grafo g);
void  printRede(Grafo g);


int main(int argc, char const *argv[]) {
	
	Grafo G= readInput();

	SCC(G);

	printf("%d\n", numSCC);

	/* Imprime o primeiro e depois os restantes para nao ter um espaco no fim da linha */
	printf("%d", listSCC->id);
	IdSCC aux = listSCC;
	listSCC = listSCC->next;
	free(aux);
	while (listSCC) {
		printf(" %d", listSCC->id);
		IdSCC aux = listSCC;
		listSCC = listSCC->next;
		free(aux);
	}

	printf("\n%d\n%d\n", numRoutersRobustos, numMaxRoutersBCC);

	freeRede(G);
	return 0;
}


/* Leitura e Inicializacao de todas as estruturas do grafo */

Grafo readInput() {

	int v, e, i, j;
	scanf("%d\n%d", &v,&e);

	Grafo G= GraphInit(v, e);

	while (e--) {
		scanf("%d %d", &i,&j);
		InsertEdge(G, i-1, j-1);
	}
	return G;
}


Grafo GraphInit(int V, int E) {
	/** Inicializa o grafo com V vertices e E arcos */

	int i=0;
	Grafo G = can_fail_malloc(sizeof(struct rede));

	G->numVert = V;
	G->adjacencias = can_fail_malloc(V * sizeof(Vertice));

	for (; i<V; i++) {
		G->adjacencias[i] = can_fail_malloc(sizeof(struct router));
		Vertice v = G->adjacencias[i];
		v->id = i+1;
		v->low = -1;
		v->depth = -1;
		v->parent = -1;
		v->stackMember = 'f';
		v->newBCC = 'f';
		v->a = NULL;
	}
	return G;
}


void InsertEdge(Grafo g, int v, int w) {
	/** Por ser adirecional, e' colocado para ambos os sentidos */
	g->adjacencias[v]->a = InsertBegin(g->adjacencias[v]->a, w); 
	g->adjacencias[w]->a = InsertBegin(g->adjacencias[w]->a, v);
} 


Arco InsertBegin(Arco head, int v) {
	Arco x = can_fail_malloc(sizeof(struct arco));
	x->v = v;
	x->next = head;
	return x;
} 


/* Calculo do output aplicando o algoritmo de Tarjan */

void SCC(Grafo g) {

	int i=0, n=g->numVert;

	for (; i<n; i++) {
		if (g->adjacencias[i]->depth == NIL) {
			
			BCC(g, i, 0);

			currNumComp = 0;
			Ligacao aux;
			while (stBCC) {
				currNumComp++;
				aux = stBCC;
				stBCC = stBCC->next;
				free(aux);
			}
			
			if (numRoutersRobustos!=1)
				currNumComp++;
			numMaxRoutersBCC = (numMaxRoutersBCC > currNumComp) ? numMaxRoutersBCC : currNumComp;
			currNumComp = 0;
		}
	}
}

void BCC(Grafo g, int router, int profundidade) {

	static int time = 0;
	Vertice v = g->adjacencias[router];
    v->low = ++time;
    v->depth = profundidade;

    /* Adiciona o vertice a' pilha */
    Arco new = can_fail_malloc(sizeof(struct arco));
    new->v = v->id;
    new->next = stSCC;
    stSCC = new;
    v->stackMember = 't';

    int numFilhos = 0;
    Arco a = v->a;
    char check = 't';

	while (a) {
		Vertice curr = g->adjacencias[a->v];
		if (curr->depth == NIL) {
			curr->parent = router;
			numFilhos++;

			if (curr->newBCC == 'f') {
				currNumComp++;
				curr->newBCC = 't';

				/* Adiciona o arco a' pilha para o BCC */
			    Ligacao new = can_fail_malloc(sizeof(struct ligacao));
			    new->v = v->id;
			    new->w = curr->id;
			    new->next = stBCC;
			    stBCC = new;
			}
			BCC(g, a->v, profundidade+1);

			if (check=='t' && ((v->parent == NIL && numFilhos > 1)
				|| (v->parent != NIL && curr->low >= v->depth))) {
				
				numRoutersRobustos++;	/* Articulation Point */
				check = 'f';

				Ligacao aux;
				while (stBCC->v != v->id || stBCC->w != curr->id) {
					if (curr->newBCC == 't') {
						curr->newBCC = 'f';
						if (currNumComp)
							currNumComp--;
					}
					aux = stBCC;
					stBCC = stBCC->next;
					free(aux);
				}
				if(stBCC)  {
					aux = stBCC;
					stBCC = stBCC->next;
					currNumComp--;
					free(aux);
				}

				if (numRoutersRobustos!=1)
					currNumComp++;
				numMaxRoutersBCC = (numMaxRoutersBCC > currNumComp) ? numMaxRoutersBCC : currNumComp;
				currNumComp = 0;
			}
			v->low = (v->low < curr->low) ? v->low : curr->low;
		}
		else if (curr->stackMember == 't')
			v->low = (v->low < curr->depth) ? v->low : curr->depth;
		a = a->next;
	}

	if (v->low == v->depth) {
		numSCC++;

		/* Identificador da Sub-Rede */
		int max = v->id;
		while (stSCC->v != v->id) {
			g->adjacencias[stSCC->v-1]->stackMember = 'f';
			Arco aux = stSCC;
			stSCC = stSCC->next;

			max = (max > aux->v) ? max : aux->v;
			free(aux);	
		} 
		g->adjacencias[stSCC->v-1]->stackMember = 'f';
		Arco aux = stSCC;
		stSCC = stSCC->next;

		max = (max > aux->v) ? max : aux->v;
		free(aux);


		/* Adiciona a' Linked List dos identificadores ordenados das R sub-redes */
		IdSCC new = can_fail_malloc(sizeof(struct IdSubRede));
    	new->id = max;
    	new->next = NULL;

    	if (listSCC == NULL)
    		listSCC = new;

    	else if (listSCC->id > max) {
    		new->next = listSCC;
    		listSCC = new;
    	}

    	else {
    		IdSCC temp = listSCC;
	    	for (; temp->next; temp = temp->next) {
	    		if (temp->next->id > max) {
	    			new->next = temp->next;
	    			temp->next = new;
	    			return;
	    		}
	    	}
	    	temp->next = new;
		}
	}
}


/* Libertacao blocos de memoria alocados pelo programa aquando o seu termino */

void freeRede(Grafo g) {
	freeArcos(g);
	free(g->adjacencias);
	free(g);
}

void freeArcos(Grafo g) {
	int numVert = g->numVert, i=0;

	for(; i<numVert; i++) {
		Arco prev=NULL, curr=g->adjacencias[i]->a;

		while (curr != NULL) {
			prev = curr;
			curr = curr->next;
			free(prev);
		}
		free(g->adjacencias[i]);
	}
}


/* Imprime rede/garfo para debugging */

void printRede(Grafo g){

	printf("v: %d\n", g->numVert);

	int i=0;
	for(; i<g->numVert ; i++) {
		Arco prev=NULL, curr=g->adjacencias[i]->a;
		printf("Adjacencias de %d: ", g->adjacencias[i]->id);
		
		while (curr != NULL) {
			prev = curr;
			curr = curr->next;
			printf(" %d", prev->v);
		}
		puts("");
	}
}