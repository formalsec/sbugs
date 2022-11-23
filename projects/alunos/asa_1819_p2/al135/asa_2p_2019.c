#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct List{
	struct Link* head;
}* list;

typedef struct Link{
	struct Vertice* vertice;
	struct Link* next;
	struct Link* prev;
}* link;

typedef struct adjList{
	struct adjLink* head;
}* adjlist;

typedef struct adjLink{
	struct Aresta* aresta;
	struct adjLink* next;
}* adjlink;

typedef struct Aresta{
	struct Vertice* orig;
	struct Vertice* dest;
	int cap;
	int flux;
	struct Aresta* opp;
	struct Aresta* next;
}* aresta;

typedef struct Vertice{
	int id;
	int h;
	int e;
	struct adjLink* current;
	int visited;
	int is_estacao;
	struct adjList* adj;
}* vertice;

typedef struct Grafo{
	struct Vertice** vertices;
	struct List* list_RtF;
}* grafo;

grafo newGrafo(int n_vertices);
vertice newVertice(int id);
aresta newAresta(vertice o, vertice d, int c);
void newArestas(vertice orig, vertice dest, int c);
void addVert(list l, vertice v);
void addAresta(vertice v, aresta a);
int min(int n, int m);
void updateList(list lst, link l);
void push(aresta a);
void relabel(vertice v);
void discharge(vertice u);
void relabelToFront(grafo redeC);

grafo newGrafo(int n_vertices){
	grafo new = (grafo) can_fail_malloc(sizeof(struct Grafo));
	new->vertices = (vertice*) can_fail_malloc(sizeof(vertice) * n_vertices);
	new->list_RtF = (list) can_fail_malloc(sizeof(struct List));
	new->list_RtF->head = NULL;
	return new;
}

vertice newVertice(int id){
	vertice new = (vertice) can_fail_malloc(sizeof(struct Vertice));
	new->adj = (adjlist) can_fail_malloc(sizeof(struct adjList));
	new->adj->head = NULL;
	new->id = id;
	new->h = 0;
	new->e = 0;
	new->visited = 0;
	new->is_estacao = 0;
	return new;
}

aresta newAresta(vertice o, vertice d, int c){
	aresta new = (aresta) can_fail_malloc(sizeof(struct Aresta));
	new->orig = o;
	new->dest = d;
	new->cap = c;
	new->flux = 0;
	return new;
}

void newArestas(vertice orig, vertice dest, int c){
	printf("newArestas\n");
	aresta a1, a2;
	adjlink ax;

	a1 = newAresta(orig, dest , c);
	a2 = newAresta(dest, orig, 0);
	a1->opp = a2;
	a2->opp = a1;
	addAresta(orig, a1);
	addAresta(orig, a2);
	
	addAresta(dest, a1);
	addAresta(dest, a2);

	

	if(orig->id == 0){
		a1->flux = c;
		a2->flux = 0 - c;
		dest->e = c;
		orig->e = orig->e - c;
	}
}

void addVert(list l, vertice v){
	link newLink = (link) can_fail_malloc(sizeof(struct Link));
	newLink->prev = NULL;
	newLink->next = NULL;
	newLink->vertice = v;
	if(l->head == NULL){
		l->head = newLink;
	}
	else{
		newLink->next = l->head;
		l->head->prev = newLink;
		l->head = newLink;
	}
}

void addAresta(vertice v, aresta a){
	adjlink adjlnk = (adjlink) can_fail_malloc(sizeof(struct adjLink));
	adjlnk->aresta = a;
	if(v->adj == NULL){
		v->current = adjlnk;
	}
	adjlnk->next = v->adj->head;
	v->adj->head = adjlnk;
}

int min(int n, int m){
	if (n < m)
		return n;
	else
		return m;
}

void updateList(list lst, link l){
	if(l->vertice->id != lst->head->vertice->id){
		l->prev->next = l->next;
		if(l->next != NULL){
			l->next->prev = l->prev;
		}
		l->prev = NULL;
		l->next = lst->head;
		lst->head->prev = l;
		lst->head = l;
	}
}

void push(aresta a){
	int d = min(a->orig->e, a->cap - a->flux);
	a->flux = a->flux + d;
	a->opp->flux = 0 - a->flux;
	a->orig->e = a->orig->e - d;
	a->dest->e = a->dest->e + d;
}

void relabel(vertice v){
	printf("relabel\n");
	int min;
	adjlink aux = v->adj->head;
	while(aux->aresta->orig->id != v->id || (aux->aresta->cap - aux->aresta->flux <= 0)){
		printf("1\n");
		aux = aux->next;
	}
	min = aux->aresta->dest->h;
	while(aux != NULL){
		printf("2\n");
		if(aux->aresta->orig->id == v->id && (aux->aresta->cap - aux->aresta->flux <= 0) && (aux->aresta->dest->h < min)){
			min = aux->aresta->dest->h;
		}
		aux = aux->next;
	}
	v->h = min + 1;
}

void discharge(vertice u){
	printf("discharge\n");
	aresta a;
	while(u->e > 0){
		a = u->current;
		if(a == NULL){
			relabel(u);
			u->current = u->adj->head;
		}
		else if((a->orig->id == u->id) && (a->cap - a->flux > 0) && (u->h == a->dest->h + 1)){
			push(a);
		}
		else{
			u->current = a->next;
		}
	}
}

void relabelToFront(grafo redeC){
	int oldh;
	link u_link = redeC->list_RtF->head;
	vertice u;

	while(u_link != NULL){
		u = u_link->vertice;
		oldh = u->h;
		discharge(u);
		if(u->h > oldh){
			updateList(redeC->list_RtF, u_link);
		}
		u_link = u_link->next;
	}
}


int main(int argc,char *argv[]){
	int n_vert, n_forn, n_est, n_lig, i, c, i1, i2, o, d, flux_max = 0;
	vertice s, t;
	grafo redeCaracol;
	adjlink a3;

	scanf("%d %d %d", &n_forn, &n_est, &n_lig);
	n_vert = n_forn + 2*n_est + 2;
	redeCaracol = newGrafo(n_vert);

	s = newVertice(0);
	t = newVertice(1);
	redeCaracol->vertices[0] = s;
	redeCaracol->vertices[1] = t;

	for(i=2;i<n_vert;i++){
		redeCaracol->vertices[i] = newVertice(i);
		addVert(redeCaracol->list_RtF, redeCaracol->vertices[i]);

	}

	s->h = n_vert;

	for(i=0;i<n_forn;i++){
		scanf("%d", &c);
		newArestas(s, redeCaracol->vertices[i+2] , c);
	}
	
	for(i=0;i<n_est;i++){
		scanf("%d", &c);
		i1 = i + n_forn + 2;
		i2 = i1 + n_est;

		redeCaracol->vertices[i1]->is_estacao = 1;
		redeCaracol->vertices[i2]->is_estacao = 1;

		newArestas(redeCaracol->vertices[i1], redeCaracol->vertices[i2] , c);

	}
	printf("MAIN 3\n");

	for(i=0;i<n_lig;i++){
		scanf("%d %d %d", &o, &d, &c);
		if(redeCaracol->vertices[o]->is_estacao){
			o+=n_est;
		}
		newArestas(redeCaracol->vertices[o], redeCaracol->vertices[d] , c);
	}

	relabelToFront(redeCaracol); 

	a3 = s->adj->head;
	while(a3 != NULL){
		if((a3->aresta->orig->id == s->id) && (a3->aresta->cap > 0)){
			flux_max += a3->aresta->flux;
		}
		a3 = a3->next;
	}

	printf("fluxo max: %d \n", flux_max);

	return 0;
}