#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int x;
	int y;
} Par;

typedef struct node *link;
struct node { 
   	int w; 
   	link next; 
};


typedef struct graph {
   	int V; 
   	int A; 
   	link *adj; 
} *Graph;
/*typedef struct graph *Graph;*/



static link NEWnode(int w, link next) { 
   	link a = can_fail_malloc( sizeof (struct node));
   	a->w = w; 
   	a->next = next;     
   	return a;                         
}


Graph GRAPHinit(int V) { 
	int v;
   	Graph G = can_fail_malloc(sizeof(G));
   	G->V = V; 
   	G->A = 0;
   	G->adj = can_fail_malloc((V + 1) * sizeof(link));
   	for (v = 1; v <= V; v++) {
      	G->adj[v] = NULL;
   	}
   	return G;
}


void GRAPHinsertArc(Graph G, int v, int w) { 
	link a;
   	for (a = G->adj[v]; a != NULL; a = a->next) {
    	if (a->w == w) return;
   	}
   	G->adj[v] = NEWnode(w, G->adj[v]);
   	G->A++;
}


void GRAPHListshow(Graph G) { 
	int v;
  	for (v = 1; v <= G->V; ++v) {
   		printf( "%2d:", v);
   		link a;
	 	for (a = G->adj[v]; a != NULL; a = a->next){ 
		 	printf(" %2d", a->w);
		}
      	printf( "\n");
   	}
}


static void dfsRcc(Graph G, int *cc, int v, int id) { 
	cc[v] = id;
/*	printf("v: %d\nID: %d\n", v, id);*/
	link a;
	for (a = G->adj[v]; a != NULL; a = a->next){  
/*		printf("cc[%d] : %d\n", a->w, cc[a->w]);*/
		if ((cc[a->w] == -1) && (a->w != -1)) { 
         	dfsRcc(G, &cc[0], a->w, id); 
		}
	}
}

int GRAPHcc(Graph G, int *cc) { 
   	int n = 0, v;
   	for (v = 0; v <= G->V; ++v) {
  		cc[v] = -1;
    }
   	for (v = 0; v <= G->V; ++v) {
   	/*	printf("cc[%d] : %d\n",  v,n);*/
		if (cc[v] == -1) {
         	dfsRcc(G, &cc[0], v, n++);
      	}
/*      	printf("N : %d\n",  n);*/
   	}
   	return n - 1;
}


int *newList(int n) {
	int *v;
	v = (int *)can_fail_malloc (n * sizeof(int));
	return v;
}


void idSubRedes(Graph G, int *cc, int nsr, int *mR) { 
	int x = 0, i;
	int k=1;
	int j=0;
	while (k <= nsr) {
		for (i = 0; i <= G->V; i++){
			if (cc[i] == k) {
 				x = i;
			}
		}
		mR[j] = x;
		j++;
		k++;
	}
}

void orderVector(int *v, int n){
	int i, j;
	for ( i = 0; i < n - 1; i++){
		for (j = i + 1; j < n; j++){
			if (v[i] > v[j]){
				int aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
}

static void reachR(Graph G, int i, int *visit, int v) { 
   	visit[i] = 1;
   	link a;
   	for (a = G->adj[i]; a != NULL; a = a->next)
      	if (visit[a->w] == 0 && a->w != v) {
         	reachR(G, a->w, &visit[0], v);
      	}
}

int GRAPHreach(Graph G, int s, int t, int v) { 
	int i;
   	int *visit = newList(G->V+1);
   	for (i = 0; i <= G->V; i++) {
      	visit[i] = 0;
   	}
   	reachR(G, s, &visit[0], v);
   	if (visit[t] == 0) return 0;
   	else return 1;
}

int nBreaks(Graph G, int *cc, int n_subRedes, int *breaks) {
	int v, n = 0, i, cond = 0;
	for (v = 1; v <= G->V; v++) {
/*		printf("VVV  CC[%d] ---- %d\n", v, cc[v]);
*/		link a = G->adj[v];
		while (a != NULL && cond == 0) {
			i = 1;
			if (v == i) i++;
			while (cc[i] != cc[v] && i <= G->V && cond == 0) {
				if (i < G->V) {
					i++;
					if (v == i || a->w == i) i++;
				}
				else cond++;
			}
/*			printf("IIIIII ----- %d\n", i);

			printf("REACH ----- %d\nA  W  ---  %d\n", GRAPHreach(G, i, a->w, v), a->w);
*/			if (GRAPHreach(G, i, a->w, v) == 0) {
				cond++;
				breaks[n] = v;
				n++;
			}
			else a = a->next;	
		}
/*		printf("NNNNNN ------ %d\n", n);
*/		cond = 0;
	}
	return n;
}

int moreRouters(Graph G, int *breaks, int n_breaks) {
	int i, j, big = 0;
	for (i = 0; i < n_breaks; i++) {
		G->adj[breaks[i]] = NULL;
	}
	link a;
	for (i = 1; i <= G->V; i++) {
		a = G->adj[i];
		while (a != NULL) {
			for (j = 0; j < n_breaks; j++) {
				if (a->w == breaks[j]) {
					a->w = -1;
				}
			}
			a = a->next;
		}
	}

/*
	GRAPHListshow(G);
*/
	int *cc = newList(G->V + 1);
	int n_subRedes = GRAPHcc(G, cc);
	int cont = 0;
	for (i = 1; i <= n_subRedes; i++) {
		for (j = 1; j <= G->V; j++) {
			if (cc[j] == i) cont++;
		}
		if (cont > big) big = cont;
		cont = 0;
	}
	return big;
 }





int main(int argc, char *argv[]) {

	int n_routers, n_connects;
	Par* list;
	int i, x, y;

	scanf("%d", &n_routers); 
	scanf("%d", &n_connects);

	list = (Par*)can_fail_malloc((n_connects + 1) * sizeof(Par));
	for (i = 0; i < n_connects; i++) {
		scanf("%d %d", &x, &y);
		if (x > y){
			int aux = x;
			x = y;
			y = aux;
		}
		(list+i)->x = x;
		(list+i)->y = y;
	}

	Graph g = GRAPHinit(n_routers);

	for (i = 0; i < n_connects; i++) {		
		GRAPHinsertArc(g, list[i].x, list[i].y); 
	}
/*
	GRAPHListshow(g);
	printf("------DEPOIS-------\n");
*/
	int *cc = newList(g->V + 1);
	int n_subRedes = GRAPHcc(g, cc);
	int *id_subRedes = newList(n_subRedes);
	idSubRedes(g, cc, n_subRedes, id_subRedes);
	orderVector(id_subRedes, n_subRedes);
	int *breaks = newList(n_routers);;
	int n_breaks = nBreaks(g, cc, n_subRedes, breaks);

	int big = moreRouters(g, breaks, n_breaks);

	printf("%d\n", n_subRedes);
	for (i = 0; i < n_subRedes - 1; i++){
		printf("%d ", id_subRedes[i]);
	}
	printf("%d\n", id_subRedes[i]);
	printf("%d\n", n_breaks);
	printf("%d", big);

/*	for (i = 0; i < n_breaks; i++) {
		printf("BREAK[%d] ---- %d\n", i, breaks[i]);
	}
*/


/*	for (i = 1; i <= n_routers; i++) printf("CC[%d]  -------  %d\n", i, cc[i]);
*/


	return 0;

}