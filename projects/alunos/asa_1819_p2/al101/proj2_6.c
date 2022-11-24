#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"

/*
 *	Analise e Sintese de Algoritmos
 *	2018/19
 *	Projeto 2
 *	Grupo 101
 *		87629 - Andre Leitao
 *		87697 - Pedro Bigodinho
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INT_MAX 2147483647

typedef struct arco* Arco;
typedef struct vertice* Vertice;
typedef struct ligacao* Ligacao;

struct ligacao {
	/* Estrutura para a lista FIFO de vertices para o bfs */
	int v;
	Ligacao next;
};

struct arco {
	int capacity;
	Vertice v;
	/* Arco back para alteracao constante de pesos dos arcos */
	Arco next, back;
};

struct vertice {
	int id ;
		
	Arco a, parent;
};

typedef struct rede {
	int numVert, numForn, numAbast;
	Vertice* adjacencias;
}* Grafo;

int V;

/* Funcoes-Prototipo */
Grafo ReadInput();
Grafo GraphInit(int f, int e);
void  InsertEdge(Grafo g, int v, int w,int c);
Arco  InsertBegin(Arco head, Vertice v, int c);
Arco  InsertSorted (Vertice h, Vertice v, int c);
void  FreeRede(Grafo g);
void  FreeArcos(Grafo g);
void  PrintRede(Grafo g);
void  FordFulkerson(Grafo G, int s, int t);


int main(int argc, char const **argv) {
	
	Grafo G= ReadInput();

	FordFulkerson(G, 1, 0);

	FreeRede(G);
	return 0;
}


/* Leitura e Inicializacao de todas as estruturas do grafo */

Grafo ReadInput() {
	/** f- #fornecedores, e- #estacoes de abastecimento, t- #ligacoes na rede */
	
	int f, e, t, i=2, j, c; 
	scanf("%d %d %d", &f, &e, &t);

	Grafo G= GraphInit(f, e);

	/* Insere fornecedores */
	while (i < f+2) {
		scanf("%d", &c);
		InsertEdge(G , i++, 0, c);		
	}

	/* Insere estacoes */
	int m = f+e+2;
	while (i < m) {
		scanf("%d", &c);
		InsertEdge(G, i+e, i, c);
		i++;
	}

	while (t--) {
		scanf("%d %d %d", &i,&j,&c);

		if (i >= f+2) InsertEdge(G, j, i+e, c);

		else InsertEdge(G, j, i, c);
	}
	return G;
}

Grafo GraphInit(int f, int e) {
	/** Inicializa o grafo com V vertices */

	int i=0, v = f+2*e+2;
	/* +2 corresponde a sink/hiper e super source para todos fornecedores, 
 	2*e dado que a cada abstecimento tem-se dois vertices,
 	em que o vertice e tem arco para e' com a capacidade da estacao */

	Grafo G = can_fail_malloc(sizeof(struct rede));

	G->numVert = v;
	G->numForn = f;
	G->numAbast = e;

	G->adjacencias = can_fail_malloc(v * sizeof(Vertice));
	V = v;

	for (; i<v; i++) {
		G->adjacencias[i] = can_fail_malloc(sizeof(struct vertice));
		Vertice new = G->adjacencias[i];
		new->id = i;
		new->a = NULL;
		new->parent = NULL;
	}
	return G;
}

void InsertEdge(Grafo g, int v, int w, int c) {
	/** A funcao cria arco de sentido oposto para gerar grafo transposto */

	/* Arcos original */
	Arco a = InsertSorted(g->adjacencias[v], g->adjacencias[w], c); 
	
	/* Arco da rede residual */
	Arco b = InsertSorted(g->adjacencias[w], g->adjacencias[v], 0);

	/* Ponteiros diretos para os arcos correspondentes, para rede residual */
	a->back = b;
	b->back = a;
} 

Arco InsertSorted (Vertice h, Vertice v, int c) {
	Arco head = h->a;
	Arco x = can_fail_malloc(sizeof(struct arco));
	x->v = v;
	x->capacity = c;
	x->next = NULL;

	
	if (head == NULL) {
		x->next =  NULL;
		h->a = x;
	}
	else if (head->v->id > v->id) {
		x->next = head;
		h->a = x;
	}
	else {
		while (head->next) {
			if (head->next->v->id > v->id) {
				x->next = head->next;
				head->next = x;
				break;
			}
			head = head->next;
		}
		head->next = x;	
	}

	
	return x;
}


/* Aplicacao Ford-Fulkerson */ 

int bfs(Grafo g, int s, int t) { 
	/** Retorna true se houver um caminho desde a source 's' ate a sink 't'
	no grafo residual, e preenche o array 'parent' guardar o valor do caminho */

	/* Cria um array onde marca inicialmente todos os vertices como nao visitados */
	char visited[g->numVert];
    int i=0;
    while (i<g->numVert) {
    	visited[i++] = 'f';
    }

    /* Cria uma fila FIFO, onde guarda o vertice source e marca a source como visitado */
	Ligacao l = can_fail_malloc(sizeof(struct ligacao));
	Ligacao aux=NULL, end=NULL;

	l->v = s;
	l->next = NULL; 
	visited[s] = 't';
	end = l;

	/* Standard BFS Loop */
	Arco curr = NULL;

	while(l) {
		int u = l->v;
		aux = l;				
		l = l->next;

		free(aux);

		curr=g->adjacencias[u]->a;

		while (curr) {
			if(visited[curr->v->id] == 'f' && curr->capacity > 0) {
				
				/* Acede diretamente ao pai de v */
				curr->v->parent = curr->back;
				visited[curr->v->id] = 't';
				Ligacao new = can_fail_malloc(sizeof(struct ligacao));
				new->v = curr->v->id;
				new->next = NULL;

				/* Insere na fila */
				if (l==NULL){
					l = new;
					end = new;
				}
				else {
					aux = end;
					aux->next = new;
					end = new;
				}
			}
			curr = curr->next;
		}
	}
	/* Retorna true se e so se for possivel alcancar a sink na BFS comecando pela source */
	return (visited[t] == 't'); 
} 

void dfs(Grafo g, int s, char visited[]) {
	/** DFS para procurar para encontrar todos os vertices alcancaveis desde 's'. Os valores
	iniciais de visited sao false, marcando visited[i] se i for acancavel desde 's' */
	visited[s] = 't';
	Arco curr = g->adjacencias[s]->a;

	while(curr) {
		if (curr->capacity && visited[curr->v->id] == 'f')
			dfs(g, curr->v->id, visited);
		curr = curr->next;
	}
}

void FordFulkerson(Grafo g, int s, int t)  { 
    int u, V = g->numVert;
    int max_flow = 0;
  
  	/* Aumenta o fluxo enquanto houver um caminho desde a source ate a sink */
    while (bfs(g, s, t)) {

    	/* Determina a capacidade residual minima dos arcos ao longo do caminho
    	completado pela BFS, isto e, determina o fluxo maximo atraves do caminho encontrado */
        int path_flow = INT_MAX;

        Vertice v= g->adjacencias[t];
        Arco u = NULL;

        while(v != g->adjacencias[s]){

            u = v->parent;
            path_flow = (path_flow <= u->back->capacity) ? path_flow : u->back->capacity;
            v = v->parent->v;
        } 
  
  		/* Faz update das capacidades residuais dos arcos e arcos invertidos
  		ao longo do caminho */
        v=g->adjacencias[t];
        u = NULL; 
        while (v != g->adjacencias[s]) {
            u = v->parent; 

            u->back->capacity -= path_flow; 
            u->capacity += path_flow; 

            v = v->parent->v;
        }
        max_flow += path_flow;
    }
 
    /*Calcula fluxo maximo a partir de s*/
    char visited[V];
    int i=0;
	char first = 't';
    while (i<V)
    	visited[i++] = 'f';
    dfs(g, s, visited);

    printf("%d\n", max_flow);

    /* Abastecimentos que devem ser aumentados */
    for(u=g->numForn+2; u<V-g->numAbast; u++) {
		Arco curr = g->adjacencias[u]->a;

		while (curr) {
			if(curr->v->id == u+g->numAbast) {
				if (visited[u]=='f' && visited[curr->v->id]=='t' && curr->capacity) {
					
					/* Se for primeiro abastecimento a ser escrito no output */
					if (first == 'f')
						printf(" ");
					else
						first = 'f';
					printf("%d", u);
				}
			}
		curr = curr->next;
		}
	}
	puts("");

	/* Ve ligacoes para fornecedores */
	for(u=2; u<g->numForn+2; u++) {
		Arco curr=g->adjacencias[u]->a;
		while (curr) {
			if(curr->v->id != 0 && visited[u]=='f' && visited[curr->v->id]=='t' && curr->capacity)
				printf("%d %d\n", u, curr->v->id);
			
			curr = curr->next;
		}
	}

	/* Ve ligacos de abastecimento para hiper */
	for(u=g->numVert-g->numAbast; u<V; u++) {
		Arco curr=g->adjacencias[u]->a;
		while (curr) {
			if (visited[u]=='f' && visited[curr->v->id]=='t' && curr->capacity)
				printf("%d %d\n", u-g->numAbast, curr->v->id);
			
			curr = curr->next;
		}
	}
} 


/* Libertacao dos blocos de memoria alocados pelo programa aquando o seu termino */

void FreeRede(Grafo g) {
	FreeArcos(g);
	free(g->adjacencias);
	free(g);
}

void FreeArcos(Grafo g) {
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


/* Imprime rede/grafo para debugging */

void PrintRede(Grafo g) {

	puts("debug3:print rede");
	printf("v: %d\n", g->numVert);

	int i=0;
	for(; i<g->numVert ; i++) {
		Arco prev=NULL, curr=g->adjacencias[i]->a;
		printf("Adjacencias de%3d:->", g->adjacencias[i]->id);
		
		while (curr != NULL) {
			prev = curr;
			curr = curr->next;
			/*printf("||next:id:%3d,cap:%3d , back:id:%d,cap:%d->", prev->v, prev->capacity, prev->back->v,prev->back->capacity);*/
			printf("next:id:%2d,cap:%3d|| ->", prev->v->id, prev->capacity);
		}
		puts("NIL");
	}
}