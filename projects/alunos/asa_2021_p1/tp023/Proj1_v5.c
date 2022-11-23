#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>


int numeroNodes, numeroDependencias, first = 0, last = 0, k, l = 0, V, E;

typedef struct node{
	int id, indegree, outdegree, d, pi;
} node;

typedef struct grafo{
	int numeroNodes, numeroDependencias;
	int **matrizAdjacencias;
	node *vertices;
} grafo;

node *ordemTopologica;
node *queue;



int** constroiMatriz() {
	int i, j, origem, destino;
	int **matriz = NULL;
	if(scanf("%d %d", &V, &E) == 2) {
		matriz = can_fail_malloc(V * sizeof(int*));
		numeroNodes = V;
		for(i = 0; i < V; i++) {
			matriz[i] = can_fail_malloc(V * sizeof(int));
			for(j = 0; j < V; j++) {
				matriz[i][j] = 0;
			}
		}
	}

	for(i = 0; i < E; i++) {
		if(scanf("%d %d", &origem, &destino) == 2) {
			matriz[origem - 1][destino - 1] = 1;
		}
	}
	return matriz;
}

grafo constroiGrafo(int **matrizAdjacencias) {
	grafo g;
	int i, j;
	g.numeroNodes = V;
	g.numeroDependencias = E;
	g.matrizAdjacencias = matrizAdjacencias;
	g.vertices = can_fail_malloc(numeroNodes * sizeof(node));
	for (i = 0; i < numeroNodes; i++) {
		g.vertices[i].indegree = 0;
		g.vertices[i].outdegree = 0;
	}
	for (i = 0; i < numeroNodes; i++) {
		g.vertices[i].id = i + 1;
		for(j = 0; j < numeroNodes; j++) {
			if(matrizAdjacencias[i][j] == 1) {
				g.vertices[i].outdegree += 1;
				g.vertices[j].indegree += 1;
			}
		}
	}
	return g;
}

void topologicalOrder(grafo g) {
	int i;
	queue = can_fail_malloc(numeroNodes * sizeof(node));
	ordemTopologica = can_fail_malloc(numeroNodes * sizeof(node));
	for(i = 0; i < numeroNodes; i++) {
		if(g.vertices[i].indegree == 0) {
			queue[last] = g.vertices[i];
			last += 1;
		}
	}
	k = last;
	while(first < last) {
		ordemTopologica[first] = queue[first];
		for(i = 0; i < numeroNodes; i++) {
			if(g.matrizAdjacencias[ordemTopologica[first].id - 1][i] == 1) {
				g.vertices[i].indegree -= 1;
				if(g.vertices[i].indegree == 0) {
					queue[last] = g.vertices[i];
					last += 1;
				}
			}
		}
		first += 1;
	}
}

void caminhoMaisLongo(grafo g) {
	int i, j;
	for(i = 0; i < numeroNodes; i++) {
		ordemTopologica[i].d = 0;
	}
	for(i = 0; i < numeroNodes; i++) {
		for(j = 0; j < numeroNodes; j++) {
			if(g.matrizAdjacencias[j][ordemTopologica[i].id - 1] == 1 && g.vertices[j].d >= g.vertices[ordemTopologica[i].id - 1].d) {
				g.vertices[ordemTopologica[i].id - 1].d = g.vertices[j].d;
			}
		}
		g.vertices[ordemTopologica[i].id - 1].d += 1;
	}
}

void liberta(int **matriz, grafo g) {
	int i;
	free(g.vertices);
	for(i = 0; i < numeroNodes; i++) {
		free(matriz[i]);
	}
	free(matriz);
}


int main(){

	int **matriz = constroiMatriz();
	grafo g = constroiGrafo(matriz);
	int i;


	topologicalOrder(g);
	caminhoMaisLongo(g);



	for(i = 0; i < numeroNodes; i++) {
		if(g.vertices[i].outdegree == 0 && g.vertices[i].d > l) {
			l = g.vertices[i].d;
		}
	}


	printf("%d %d\n", k, l);

	liberta(matriz, g);
	free(ordemTopologica);
	free(queue);


	return 0;
} 