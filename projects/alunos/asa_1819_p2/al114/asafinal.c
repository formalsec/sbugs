#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/* Henrique Santos 92476 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define min(a,b) a>b?b:a

#define push(q,s) q[++q[0]]=s
#define pop(q) q[--q[0]+1]
#define empty(q) q[0]==0

typedef struct link {
	int node, cap;
	struct link *next;
} Link;

typedef Link* LINK;

static int f, e, t, n, *abast, *parent;
static Link **graph, **rGraph;
static char *visited;

/* adiciona adjacência em 'n' de 'x' para 'y' */
static void add(LINK * n, int x, int y, int cap) {
	register Link *l = can_fail_malloc(sizeof(Link));
	l->cap = cap;
	l->node = y;
	l->next = n[x];
	n[x] = l;
}

/* devolve capacidade da adjacência em 'n' de 'x' para 'y' */
static int get(LINK * n, int x, int y) {
	register Link *l;
	for (l = n[x]; l; l = l->next)
		if (l->node == y)
			return l->cap;
	return 0;
}

/* incrementa capacidade em 'cap' da adjacência em 'n' de 'x' para 'y' */
static void set(LINK * n, int x, int y, int cap) {
	register Link *l;
	for (l = n[x]; l; l = l->next)
		if (l->node == y) {
			l->cap += cap;
			return;
		}
	add(n, x, y, cap); /* ainda não existe a ligação */
}

/* processa o ficheiro de entrada */
static void input() {
	register int i;
	int orig, dest, cap;

	scanf("%d %d %d", &f, &e, &t);
	n = 2 + f + e;
	abast = can_fail_malloc(sizeof(int) * (n + e));
	memset(abast, 0, sizeof(int) * (n + e));
	for (i = 0; i < n + e; i++)
		abast[i] = i;
	parent = can_fail_malloc(sizeof(int) * (n + e));
	memset(parent, 0, sizeof(int) * (n + e));
	visited = can_fail_malloc(sizeof(int) * (n + e));
	memset(visited, 0, sizeof(int) * (n + e));
	graph = can_fail_malloc(sizeof(Link *) * (n + e));
	memset(graph, 0, sizeof(Link *) * (n + e));
	rGraph = can_fail_malloc(sizeof(Link *) * (n + e));
	memset(rGraph, 0, sizeof(Link *) * (n + e));
	for (i = 0; i < f; i++) {	/* fornecedores */
		scanf("%d", &cap);
		add(graph, 0, i + 2, cap);
		add(rGraph, 0, i + 2, cap);
	}
	while (i < f + e) {	/* abastecimento */
		scanf("%d", &cap);
		i++;
		add(graph, i + 1, n, cap);
		add(rGraph, i + 1, n, cap);
		abast[i + 1] = n;
		n++;
	}
	for (i = 0; i < t; i++) {	/* ligações */
		scanf("%d %d %d", &orig, &dest, &cap);
		add(graph, abast[orig], dest, cap);
		add(rGraph, abast[orig], dest, cap);
	}
}

/* liberta o grafo */
static void clean(LINK * v, int n) {
	register int i;
	register Link *l, *next;
	for (i = 0; i < n; i++) {
		for (l = v[i]; l; l = next) {
			next = l->next;
			free(l);
		}
	}
	free(v);
}


static int *q;
/* preenche caminho inverso 'parent' e devolve flow se chegou ao destino */
static int bfs(LINK * rGraph, int n, int s, int t, int *parent, int flow) {
	int ret, qn = 0;

	memset(visited, 0, n);
	visited[s] = 1;
	if (!q) q = can_fail_malloc(sizeof(int)*n);
	q[0] = 0;		/* elementos na pilha */
	q[qn++] = s;
	parent[s] = -1;

	while (qn) {
		int u = q[--qn];
		register Link *l;
		for (l = rGraph[u]; l; l = l->next)
			if (visited[l->node] == 0 && l->cap > 0) {
				if (l->cap < flow) flow = l->cap;
				q[qn++] = l->node;
				parent[l->node] = u;
				visited[l->node] = 1;
			}
	}

	ret = visited[t] == 1;	/* reached sink ? */
	return ret ? flow : 0;
}

/* procura em profundidade dos vértices acessíveis da origem 's' */
static void dfs(LINK * rGraph, int n, int s, char *visited) {
	register int i;
	register Link *l;

	visited[s] = 1;
	for (i = 0; i < n; i++)
		for (l = rGraph[i]; l; l = l->next)
			if (l->node == s && l->cap && !visited[i])
				dfs(rGraph, n, i, visited);
}

/* comparador para vetor de inteiros */
static int cmpab(const void *a, const void *b) {
	return *((int *) a) - *((int *) b);
}

/* comparador para vetor de pares de inteiros */
static int cmpno(const void *a, const void *b) {
	register int **x = (int **) a, **y = (int **) b;
	if (x[0][0] != y[0][0])
		return x[0][0] - y[0][0];
	return x[0][1] - y[0][1];
}

/* procura corte mínimo mais próximo do destino */
static void minCut(LINK * graph, int n, int s, int d, int *abast) {
	register Link *l;
	register int u, v;
	int path_flow, max_flow = 0;
	int *ab = can_fail_malloc(sizeof(int) * e), abn = 0;
	int **no = can_fail_malloc(sizeof(int *) * t), non = 0;

	/* aumenta o flow do caminho da origem para o destino */
	while ((path_flow = bfs(rGraph, n, s, d, parent, INT_MAX))) {
		/* calcula o fluxo do caminho */
		int path_flow = INT_MAX;
		for (v = d; v != s; v = parent[v]) {
			int cap;
			u = parent[v];
			cap = get(rGraph, u, v);
			path_flow = min(path_flow, cap);
		}

		/* atualiza as capacidades no caminho */
		for (v = d; v != s; v = parent[v]) {
			u = parent[v];
			set(rGraph, u, v, -path_flow);
			set(rGraph, v, u, path_flow);
		}
		max_flow += path_flow;
	}
	/* procura os vértices acessíveis do destino */
	memset(visited, 0, sizeof(int) * n);
	dfs(rGraph, n, d, visited);

	/* constrói listas com elementos do corte mínmo encontrado */
	for (v = 0; v < n; v++)
		for (l = graph[v]; l; l = l->next) {
			u = l->node;
			if (visited[u] && !visited[v] && l->cap) {
				int i, x = u, y = v;
				if (x > f+e)	/* abastecimento na origem */
					for (i = f; i < x; i++)
						if (abast[i] == x) {
							x = i;
							break;
						}
				if (y > f+e)	/* abastecimento no destino */
					for (i = f; i < y; i++)
						if (abast[i] == y) {
							y = i;
							break;
						}
				if (y == 0) ;
				else if (x == y)
					ab[abn++] = x;
				else {
					no[non] = can_fail_malloc(2 * sizeof(int));
					no[non][0] = y;
					no[non++][1] = x;
				}
			}
		}
	/* ordena as listas: abastecimentos e ligações */
	qsort(ab, abn, sizeof(int), cmpab);
	qsort(no, non, sizeof(int *), cmpno);

	/* imprime no formato pretendido */
	printf("%d\n", max_flow);
	for (u = 0; u < abn; u++)
		printf("%s%d", u ? " " : "", ab[u]);
	printf("\n");
	for (u = 0; u < non; u++)
		printf("%d %d\n", no[u][0], no[u][1]);

	/* valgrind! */
	free(ab);
	for (u = 0; u < non; u++)
		free(no[u]);
	free(no);
}

int main() {
	input();
	minCut(graph, n, 0, 1, abast);

	/* valgrind! */
	free(abast);
	free(parent);
	free(visited);
	clean(graph, n);
	clean(rGraph, n);
	free(q);
	return 0;
}
