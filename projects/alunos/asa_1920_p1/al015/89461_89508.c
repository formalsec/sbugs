#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/* 89461 Inês Alves */
/* 89508 Miguel Silva */

#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ((a > b) ? a: b)
#define min(a, b) ((a < b) ? a: b)

int * stack;
int top=0;
int scc=0;

typedef struct stack {
	int key;
	struct stack * next;
} * Stack;

typedef struct vertex * Vertex;

typedef struct adj_vertex {
	Vertex vertex;
	struct adj_vertex * next;
} * AdjVertex;

struct vertex {
	int id, grade, discovery, parent, low;
	AdjVertex head;
};

typedef struct graph {
	Vertex array;
	int N;
} * Graph;

void push(int i){
	stack[top]=i;
	top++;
}
int pop(){
	if(top > 0){
		top--;
		return stack[top];
	}
	return -1;
}
int stackTop(){
	if(top>0)
		return stack[top-1];
	return -1;
}

int tarjan(Graph g, int v, int time) {
	int w, i = 0,j, vertex_index, max_grade=-1, maxStackIndex=-1;
	AdjVertex adj;
	time++;
	g->array[v].discovery = g->array[v].low = time;
	push(v);

	for (adj = g->array[v].head; adj != NULL; adj = adj->next) {
		w = adj->vertex->id;

		if (g->array[w].discovery == -1) {
			g->array[v].grade = max(g->array[v].grade, g->array[w].grade);
			g->array[w].parent = v; i++;
			time = tarjan(g, w, time);
			g->array[v].low = min(g->array[v].low, g->array[w].low);
		}
	
		else if (g->array[v].parent != (w))
			g->array[v].low = min(g->array[v].low, g->array[w].discovery);

		else if (g->array[v].parent == w)
			g->array[v].low = min(g->array[v].low, g->array[w].low);

		g->array[v].grade = max(g->array[v].grade, g->array[w].grade);
	}

	if (g->array[v].discovery == g->array[v].low) {
		while ((vertex_index = pop()) != -1) {
	    	if (vertex_index == v) {
				maxStackIndex = max(maxStackIndex,top);
				max_grade = max(max_grade, g->array[vertex_index].grade);
				for(j=top;j<=maxStackIndex;j++){
					g->array[stack[j]].grade = max(g->array[stack[j]].grade,max_grade);
				}
				break;
	    	}
			else{
				maxStackIndex = max(maxStackIndex,top);
				max_grade = max(max_grade, g->array[vertex_index].grade);
			}
		}
    }
	return ++time;
}


void link(Graph g, int a, int b) {
	Vertex v = &g->array[a-1];
	AdjVertex new = can_fail_malloc(sizeof(struct adj_vertex));
	
	new->vertex = &g->array[b-1];
	new->next = v->head;
	v->head = new;
}

void parseInput(Graph g) {
	int u, v, i, M;

	fscanf(stdin, "%d,%d\n", &g->N, &M);
	stack = can_fail_calloc(g->N,sizeof(int));

	g->array = can_fail_calloc(g->N, sizeof(struct vertex));
	for (i = 0; i < g->N; i++) {
		fscanf(stdin, "%d\n", &g->array[i].grade);
		g->array[i].id = i;
		g->array[i].discovery = -1;
		g->array[i].parent = -1;
		g->array[i].head = NULL;
	}

	for (i = 0; i < M; i++) {
		fscanf(stdin, "%d %d\n", &u, &v);
		link(g, u, v);
	}
}

void displayResults(Graph g) {
	int i;
	for (i = 0; i < g->N; i++) 
		printf("%d\n", g->array[i].grade);
}

void freeGraph(Graph g) {
	int i, N = g->N;
	AdjVertex aux;

	for (i = 0; i < N; i++) {
		while (g->array[i].head) {
			aux = g->array[i].head;
			g->array[i].head = g->array[i].head->next;
			free(aux);
		}
	}
	free(g->array);
	free(g);
}

int main (void) {
	int i, time=0;
	Graph g = can_fail_malloc(sizeof(struct graph));

	parseInput(g);

	for (i = g->N - 1; i >= 0; i--) {
		if ((g->array[i].discovery) == -1) {
			time = tarjan(g, i, time);
		}
	}

	displayResults(g);
	freeGraph(g);
	return 0;
}
