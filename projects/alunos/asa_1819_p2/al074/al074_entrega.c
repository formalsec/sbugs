#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/**
* ********************************************
* Grupo 074, Alameda.
* Rafael Pereira, 83554, e João Lopes, 89479.
* ********************************************
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct AdjListNode {
	int dest;
	int cap;
	int flow;
	struct AdjListNode* next;
} *AdjListNode;

typedef struct AdjList {
	AdjListNode head;
} *AdjList;

typedef struct Vertex {
	int e_flow;
	int h;
} *Vertex;

typedef struct Graph {
	int V;
	Vertex ver;
	AdjList array;
} *Graph;

struct node {
	int v;
	struct node* next;
	struct node* prev;
};

int h(Graph g, int u) {
	return g->ver[u].h;
}

int e(Graph g, int u) {
	return g->ver[u].e_flow;
}

struct node* addNode(struct node* l, int v) {
	struct node* n = (struct node*) can_fail_malloc(sizeof(struct node));
	n->v = v;
	n->next = l;
	n->prev = NULL;
	if(l != NULL)
		l->prev = n;
	return n;
}

void swapNodes(struct node **head, struct node **n) {
	struct node *prevX = (*n)->prev, *currX = *n;
	struct node *prevY = NULL, *currY = *head;
	struct node *temp;
	if((*head)->v == (*n)->v) return;

	if(prevX != NULL)
		prevX->next = currY;
	else
		*head = currY;

	if(prevY != NULL)
		prevY->next = currX;
	else
		*head = currX;

	temp = currY->next;
	currY->next = currX->next;
	currX->next = temp;

}

void freeList(struct node* l) {
	struct node* n;
	while(l != NULL) {
		n = l;
		l = l->next;
		free(n);
	}
}

AdjListNode newAdjListNode(int dest, int cap) {
	AdjListNode newNode = 
		(AdjListNode) can_fail_malloc(sizeof(struct AdjListNode));
	newNode->dest = dest;
	newNode->cap = cap;
	newNode->flow = 0;
	newNode->next = NULL;
	return newNode;
}

Graph newGraph(int V) {
	Graph g = 
		(Graph) can_fail_malloc(sizeof(struct Graph));
	g->V = V;
	g->ver = (Vertex) can_fail_malloc(V * sizeof(struct Vertex));
	g->array =
		(AdjList) can_fail_malloc(V * sizeof(struct AdjList));
	int i;
	for(i = 0; i < V; i++) {
		g->array[i].head = NULL;
		g->ver[i].h = 0;
		g->ver[i].e_flow = 0;
	}
	return g;
}

void freeGraph(Graph g) {
	int i;
	for(i = 0; i < g->V; i++) {
		AdjListNode adj = g->array[i].head;
		while(adj != NULL) {
			AdjListNode aux = adj->next;
			free(adj);
			adj = aux;
		}
	}
	free(g->array);
	free(g->ver);
	free(g);
}

void addEdge(Graph g, int src, int dest, int cap) {
	AdjListNode newNode = newAdjListNode(dest, cap);
	newNode->next = g->array[src].head;
	g->array[src].head = newNode;

	newNode = newAdjListNode(src, cap);
	newNode->next = g->array[dest].head;
	g->array[dest].head = newNode;
}

void printGraph(Graph g) {
	int i;
	for(i = 0; i < g->V; i++) {
		AdjListNode adj = g->array[i].head;
		/*printf("vertice %d h= %d, e_flow= %d\n",i , h(g, i), e(g, i));
		printf("Vertices adjacentes ao vertice %d\n", i);*/
		while(adj != NULL) {
			/*printf(" (%d -> %d, flow= %d, cap= %d)\n",i ,adj->dest, adj->flow, adj->cap);*/
			adj = adj->next;
		}/**/
		printf("\n");
	}
}

int capacity(Graph g, int u, int v) {
	AdjListNode adj = g->array[u].head;
	while(adj != NULL) {
		if(adj->dest == v)
			return adj->cap;
		adj = adj->next;
	}
	return 0;
}

int residualCapacity(Graph g, int u, int v) {
	int c=0, f=0;
	AdjListNode adj = g->array[u].head;
	while(adj != NULL) {
		if(adj->dest == v) {
			c = adj->cap;
			f = adj->flow;
			break;
		}
		adj = adj->next;		
	}
	return c - f;
}

int flow(Graph g, int u, int v) {
	AdjListNode adj = g->array[u].head;
	while(adj != NULL) {
		if(adj->dest == v)
			return adj->flow;
		adj = adj->next;
	}
	return 0;
}

void changeFlow(Graph g, int u, int v, int flow) {
	AdjListNode adj = g->array[u].head;
	while(adj != NULL) {
		if(adj->dest == v)
			adj->flow = flow;
		adj = adj->next;
	}
}


int PUSH(Graph g, int u, int v) {
	int aux = residualCapacity(g, u, v);
	if(e(g, u) > 0 && aux > 0 && h(g, u) == h(g, v) + 1) {
		int f = flow(g, u, v);
		if(aux > e(g, u)) 
			aux = e(g, u);

		changeFlow(g, u, v, aux + f);
		changeFlow(g, v, u, -1*f);

		g->ver[u].e_flow -= aux;
		g->ver[v].e_flow += aux;

		return 1;
	}
	return 0;
}

int canRELABEL(Graph g, int u) {
	AdjListNode n = g->array[u].head;
	while(n != NULL) {
		if(g->ver[n->dest].h >= h(g, u))
			return 1;
		n = n->next;
	}
	return g->ver[u].e_flow > 0;
}

void RELABEL(Graph g, int u) {
	if(canRELABEL(g, u)) {
		int min;
		AdjListNode adj = g->array[u].head;
		min = g->ver[adj->dest].h;
		while(adj != NULL) {
			if(min > g->ver[adj->dest].h)
				min = g->ver[adj->dest].h;
			adj = adj->next;
		}
		g->ver[u].h = 1 + min;
	}
}

void PREFLOW(Graph g, int s) {
	g->ver[s].h = g->V;
	AdjListNode adj = g->array[s].head;
	while(adj != NULL) {
		int cap = capacity(g, s, adj->dest);
		changeFlow(g, s, adj->dest, cap);
		changeFlow(g, adj->dest, s, -1* cap);
		g->ver[adj->dest].e_flow = cap;
		g->ver[s].e_flow -= cap;
		adj = adj->next;
	}
}

void DISCHARGE(Graph g, int u) {
	AdjListNode v = g->array[u].head;
	while(e(g, u) > 0) {
		if(v == NULL) {
			RELABEL(g, u);
			v = g->array[u].head;
			/*printf("%d, h= %d\n", u, h(g, u));*/
		}
		else 
			PUSH(g, u, v->dest);
		v = v->next;
	}
}

int maxFlow(Graph g) {
	AdjListNode adj = g->array[0].head;
	int fluxo_max = 0;
	while(adj != NULL) {
		AdjListNode inv= g->array[adj->dest].head;
		fluxo_max += adj->flow - inv->flow;
		adj = adj->next;
	}
	return fluxo_max;
}

int RELABEL_TO_FRONT(Graph g,int s,int t) {
	int old_h, i;
	struct node* L = NULL, *u;
	for(i = g->V; i > 1; i--) {
		L = addNode(L, i);
	}
	PREFLOW(g, s);
	u = L;
	while(u != NULL) {
		/*printf(" v %d, h= %d, e= %d\n\n", u->v, h(g, u->v), e(g, u->v));*/
		old_h = h(g, u->v);
		DISCHARGE(g, u->v);
		if(h(g, u->v) > old_h) {
			swapNodes(&L, &u);
		}
		u = u->next;
		printf("\n");
	}
	freeList(L);
	return maxFlow(g);
}


int main(int argc, const char * argv[]) {
    int fornecedores, estacoes_abastecimento, ligacoes;
    int producao_fornecedor, capacidade_estacao;
    int origem, destino, capacidade_ligacao;
    int total_vertices;
    int i, nova_estacao;

    scanf("%d %d %d", &fornecedores, &estacoes_abastecimento, &ligacoes);
   
   	/*total de vertices = fornecedor + 2*estacoes + vertice de origem a adicionar + hipermercado*/
    total_vertices = fornecedores + 2*estacoes_abastecimento +2; 
    /*uma vez que ligamos os fornecedoras a uma origem e vamos adicionar uma ligacao entre a estacao 
    de abastecimento e uma nova estacao de abastecimento*/

    
    Graph grafo = newGraph(total_vertices);

	for(i=0; i < fornecedores; i++){
    	scanf("%d", &producao_fornecedor);
    	/*adiciona um edge do source(0) para todos os fornecedores, com a capacidade dos mesmos*/
		addEdge(grafo, 0, i+2, producao_fornecedor);
		/*printf("edge: 0 --->%d, prod= %d\n", i+2, producao_fornecedor);*/
	}
  
	for(i=0; i < estacoes_abastecimento; i++){
		nova_estacao = i + estacoes_abastecimento + fornecedores+2;
    	scanf("%d", &capacidade_estacao);
    	/*adiciona um edge da estacao a uma nova estacao(que sera i+numero de estacoes) tendo este edge a capacidade
    	desta estacao*/
		addEdge(grafo, i+2+fornecedores, nova_estacao, capacidade_estacao);
		/*printf("edge: %d ---> %d\n", i+2+fornecedores, nova_estacao);*/
	}

	for(i=0; i < ligacoes; i++){
		scanf("%d %d %d", &origem, &destino, &capacidade_ligacao);
		/*caso o ponto de partida de um edge seja uma estacao temos de adicionar um edge mas nao com este ponto de 
		partida, sera o nova_estacao*/
		if(origem >= fornecedores+2 /*&& origem < fornecedores+estacoes_abastecimento+2*/){
			addEdge(grafo, origem + estacoes_abastecimento, destino, capacidade_ligacao);
			/*printf("edge nova_estacao: %d ---> %d\n", origem+estacoes_abastecimento, destino);*/
		}
		else if (destino){
			addEdge(grafo, origem, destino, capacidade_ligacao);
			/*printf("edge: %d ---> %d\n", origem, destino);*/
		}
	}
	/*ADICIONA TODAS AS ARESTAS CORRETAMENTE*/
	/*printGraph(grafo);*/
	printf("fluxo maximo= %d\n", RELABEL_TO_FRONT(grafo, 0, 1));
	return 0;
}