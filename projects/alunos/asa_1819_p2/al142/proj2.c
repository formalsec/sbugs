#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct alist *alist;
typedef struct queue *queue;
typedef struct node *node;
typedef struct vertice *vertice;
typedef struct aresta *aresta;

void unvisit(vertice *V, int f, int e);
int bfs(vertice *V, int size, int f, int e);
void visit(vertice v);
void dfs(vertice *V, vertice v);
int dfs_1(vertice *V, int at, int flow);

typedef struct alist {
	aresta a;
	alist next;
}*alist;

typedef struct vertice {
	int n;
	int next;
	aresta prev;
	int visited;
	alist out_arest; 
	int out_size;
	alist in_arest;
}*vertice;

typedef struct aresta {
	vertice orig;
	vertice dest;
	int cap_in;
	int cap;
	bool abast;
}*aresta;


alist addlist(alist l1, aresta a){
	alist l2 = (alist) can_fail_malloc(sizeof(struct alist));
	l2->next = l1;
	l2->a = a;
	return l2;
}

int cmpint(const void * a, const void * b){
	return ( *(int*)a - *(int*)b);
}

int cmparesta(const void * a1, const void * b1){
	aresta a = *(aresta*)a1;
	aresta b = *(aresta*)b1;

	if (a->orig->n == b->orig->n)
		return a->dest->n - b->dest->n;
	return a->orig->n - b->orig->n;
}

int main(){
	int f, e, t, i;

	scanf("%d %d %d", &f, &e, &t);

	vertice V[f+2*e+2];
	aresta A[t+e+f];
	aresta A_corte[t];
	int A_abast[e];


	/* SOURCE & HIPER */

	vertice v_orig = (vertice) can_fail_malloc(sizeof(struct vertice));
	vertice v_hiper = (vertice) can_fail_malloc(sizeof(struct vertice));
	v_orig->n = 0;
	v_hiper->n = 1;
	v_orig->out_size = 0;
	v_hiper->out_size = 1;
	V[0] = v_orig;
	V[1] = v_hiper;

	/* SOURCE & HIPER */



	/* TRATAMENTO DE INPUT */

	int flow;
	for(i=0; i<f; i++){
		scanf("%d", &flow);
		vertice v = (vertice) can_fail_malloc(sizeof(struct vertice));
		V[i+2] = v;
		v->n = i+2;
		v->out_size = 0;
		V[0]->out_size++;

		aresta a = (aresta) can_fail_malloc(sizeof(struct aresta));
		a->orig = V[0];
		a->dest = v;
		a->cap = flow;
		a->cap_in = flow;
		a->abast = false;
		A[i]=a;
		V[0]->out_arest = addlist(V[0]->out_arest, a);
		V[i+2]->in_arest = addlist(V[i+2]->in_arest, a);
	}

	for(i=0; i<e; i++){
		scanf("%d", &flow);
		vertice v1 = (vertice) can_fail_malloc(sizeof(struct vertice));
		vertice v2 = (vertice) can_fail_malloc(sizeof(struct vertice));
		v1->n = 2*i + f + 2;
		v1->out_size = 1;
		v2->n = 2*i + f + 3;
		v2->out_size = 0;
		V[2*i + f + 2] = v1;
		V[2*i + f + 3] = v2;

		aresta a = (aresta) can_fail_malloc(sizeof(struct aresta));
		a->orig = v1;
		a->dest = v2;
		a->cap = flow;
		a->cap_in = flow;
		a->abast = true;
		A[i+f]=a;
		v1->out_arest = addlist(v1->out_arest, a);
		v2->in_arest = addlist(v2->in_arest, a);
	}

	int x1, x2, x;
	for(i=0; i<t; i++){
		scanf("%d %d %d", &x1, &x2, &flow);

		if(x1 > f+1){
			x = x1;
			x1=(x-2-f)*2 + 3+f;
		}

		if(x2 > f+1){
			x = x2;
			x2=(x-2-f)*2 + 2+f;
		}

		V[x1]->out_size++;

		aresta a = (aresta) can_fail_malloc(sizeof(struct aresta));
		a->orig = V[x1];
		a->dest = V[x2];
		a->cap = flow;
		a->cap_in = flow;
		a->abast = false;
		A[i+f+e]=a;
		V[x1]->out_arest = addlist(V[x1]->out_arest, a);
		V[x2]->in_arest = addlist(V[x2]->in_arest, a);

	}

	/* TRATAMENTO DE INPUT */



	/* Algoritmo Dinic */


	int maxflow = 0;
	int fl;
	while(bfs(V, f+2*e+2, f, e)){
		for (fl = dfs_1(V, 0, -1); fl != 0; fl = dfs_1(V, 0, -1)){
			maxflow += fl;
		}
	} 

	/* Algoritmo Dinic */



	/* Algoritmo Corte Minimo + Proximo do Hiper */

	unvisit(V, f, e);
	dfs(V, V[1]);


	int c1=0,c2=0;
	for(i=0;i<f+e+t;i++){
		if(A[i]->dest->visited != -1 && A[i]->orig->visited == -1){

			if(A[i]->abast){
				A_abast[c1] = A[i]->orig->n - (A[i]->orig->n -f-1)/2;
				c1++;
			}

			else if(A[i]->orig->n != 0){
				A_corte[c2] = A[i];
				c2++;
			}

		}
	}

	/* Algoritmo Corte Minimo + Proximo do Hiper */



	/* TRATAMENTO DE OUTPUT */

	printf("%d\n", maxflow);

	qsort(A_corte, c2, sizeof(aresta), cmparesta);

	for(i=0;i<c1;i++){
		printf("%d", A_abast[i]);
		if(i+1 != c1)
			printf(" ");
	}
	puts("");

	for(i=0;i<c2;i++){

		int v1 = A_corte[i]->orig->n;
		int v2 = A_corte[i]->dest->n;

		if(A_corte[i]->orig->n > f+1){
			v1 = A_corte[i]->orig->n - (A_corte[i]->orig->n -f-1)/2;
		}

		if(A_corte[i]->dest->n > f+1){
			v2 = A_corte[i]->dest->n - (A_corte[i]->dest->n -f-1)/2;
		}

		printf("%d %d\n", v1, v2);
	}

	/* TRATAMENTO DE OUTPUT */

	

	return 0;

}

void unvisit(vertice *V, int f, int e){
	int i;
	for(i=0; i<f+2*e+2; i++){
		V[i]->visited = -1;
	}
}

int bfs(vertice *V, int size, int f, int e){

	unvisit(V, f, e);
	int in=0, fim=1;
	int q[size];
	q[0] = V[0]->n;
	V[0]->visited = 0;


	while(1){
		int v1 = q[in];
		in++;
		vertice v = V[v1];
		alist l = v->out_arest;

		if (l == NULL){
			if(v1 == 1) break;
			continue;
		} 
		while(1){
			aresta a = l->a;
			int cap = a->cap;
			vertice v_to = a->dest;
			if(cap > 0 && v_to->visited == -1){
				v_to->visited = v->visited + 1;
				q[fim] = v_to->n;
				fim++;
			}

			if (l->next == NULL) break;
			l = l->next;
		}
		if (in == fim) break;
	}


	return V[1]->visited != -1;

}


int dfs_1(vertice *V, int at, int flow){
	if (at == V[1]->n) return flow;

	alist l = V[at]->out_arest;
	if(l == NULL) return flow;

	for(;;){

		vertice v = l->a->dest;
		int cap = l->a->cap;

		if(cap > 0 && v->visited == V[at]->visited +1){

			if(flow == -1)
				flow = cap;
			else if(cap < flow)
				flow = cap;


			int min = dfs_1(V, v->n, flow);
			if(min > 0){
				l->a->cap = cap - min;
				return min;
			}
		}
		if(l->next == NULL) break;
		l=l->next;
	}
	return 0;

}

void visit(vertice v){
	v->visited = 1;
}

void dfs(vertice *V, vertice v){

	visit(v);
	alist in = v->in_arest;
	alist out = v->out_arest;
	if(in != NULL){
		while(1){
			if(in->a->cap > 0 && in->a->orig->visited == -1)
				dfs(V, in->a->orig);
			if(in->next == NULL) break;
			in = in->next;
		}
	}

	if(out != NULL){
		while(1){
			if(out->a->cap != out->a->cap_in && out->a->dest->visited == -1)
				dfs(V, out->a->dest);
			if(out->next == NULL) break;
			out = out->next;
		}
	}


}