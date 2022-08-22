/***********************************************************************************************
*                                                                                              *
*                                         Grupo: 146                                           *
*                                                                                              *
*                                     Marco Ruben, 78934                                       *
*                                                                                              *
*              		   Copyright (c) 2019 Marco Ruben. All rights reserved.  	               *
*                                                                                              *
***********************************************************************************************/

/*
// Projeto ASA - Projecto 1
// Analise e Sintese de Algoritmos, DEI/IST/ULisboa 2018-19
*/


/* Diretivas de pre-compilador -> inclusao das bibliotecas e ficheiros necessarios ao programa */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/* Definicao de macros */
#define	max(x, y) x > y ? x : y /* Retorna o maior entre x e y */
#define min(x, y) x < y ? x : y /* Retorna o menor entre x e y */


/* Definicao de estruturas de dados */
typedef struct connection {
	int vertex;
	struct connection *next;
} *Connection;

typedef struct vertexs {
	int vertex;
	int d;
	int low;
	int parent;
	bool is_articulation;
	bool visited;
	bool is_max_vertex;
	Connection head;
} *Vertexs;

typedef struct data {
	int nr_vertexs;
	int nr_connections;
	int nr_graphs;
	int nr_vertexs_bigger_graph;
	Vertexs vertexs;
} *Data;


/* =============================================================================
 * printResults
 * =============================================================================
*/

void printResults(Data data) {
    printf("%d\n", data->nr_graphs); /* Imprime o numero de sub-redes */
	int i, j = data->nr_graphs, count_cut_vertexs = 0;
	for (i = 0; i < data->nr_vertexs; i++) {
		if (data->vertexs[i].is_max_vertex == true) {
			printf("%d", data->vertexs[i].vertex); /* Imprime o identificador de cada sub-rede em ordem crescente */
			j--;
			if (j > 0)
				printf(" ");
		}
        if (data->vertexs[i].is_articulation == true)
            count_cut_vertexs++; /* Conta o numero de routers que quebram uma sub-rede */
    }
	printf("\n%d\n%d\n", count_cut_vertexs, data->nr_vertexs_bigger_graph); /* Imprime o numero de routers que quebram uma sub-rede e o numero de routers da maior sub-rede resultante da remoção de todos destes routers */
}


/* =============================================================================
 * DFS Algorithm
 *
 * 	Referencia:
 * 		-> Slides das aulas teoricas: Alg. Elementares (cap. 22)
 * 		-> DFS pseudocode (recursive implementation):
 * 			https://www.programiz.com/dsa/graph-dfs
 *		-> https://www.geeksforgeeks.org/articulation-points-or-cut-vertices-in-a-graph/
 *
 *
 * dfs and dfsVisit
 * =============================================================================
*/

void dfsVisit(Data data, int u, int *variable, int mode) {
	data->vertexs[u].visited = true;
	if (mode == 0) {
		static int time = 0;
		int children = 0;
		data->vertexs[u].d = data->vertexs[u].low = ++time;
		Connection pointer;
		for (pointer = data->vertexs[u].head; pointer != NULL; pointer = pointer->next) {
			if (data->vertexs[pointer->vertex - 1].visited == false) {
				*variable = max(*variable, pointer->vertex);
				children++;
				data->vertexs[pointer->vertex - 1].parent = u + 1;
				dfsVisit(data, pointer->vertex - 1, variable, mode);
				data->vertexs[u].low = min(data->vertexs[u].low, data->vertexs[pointer->vertex - 1].low);
				if ((data->vertexs[u].parent == 0 && children > 1) || (data->vertexs[u].parent != 0 && data->vertexs[pointer->vertex - 1].low >= data->vertexs[u].d))
					data->vertexs[u].is_articulation = true;
			}
			else if (pointer->vertex != data->vertexs[u].parent)
				data->vertexs[u].low = min(data->vertexs[u].low, data->vertexs[pointer->vertex - 1].d);
		}
	}
	else {
		Connection pointer;
		for (pointer = data->vertexs[u].head; pointer != NULL; pointer = pointer->next)
			if (data->vertexs[pointer->vertex - 1].visited == false && data->vertexs[pointer->vertex - 1].is_articulation == false) {
				(*variable)++;
				dfsVisit(data, pointer->vertex - 1, variable, mode);
			}
	}
}

void dfs(Data data, int mode) {
	int u;
	for (u = 0; u < data->nr_vertexs; u++)
		data->vertexs[u].visited = false;
	if (mode == 0) {
		int max_vertex;
		for (u = 0; u < data->nr_vertexs; u++)
			if (data->vertexs[u].visited == false) {
				data->nr_graphs++;
				max_vertex = data->vertexs[u].vertex;
				dfsVisit(data, u, &max_vertex, mode);
                data->vertexs[max_vertex - 1].is_max_vertex = true;
			}
	}
	else {
		int nr_vertexs_bigger_graph;
		for (u = 0; u < data->nr_vertexs; u++)
	        if (data->vertexs[u].visited == false && data->vertexs[u].is_articulation == false) {
				nr_vertexs_bigger_graph = 1;
	            dfsVisit(data, u, &nr_vertexs_bigger_graph, mode);
				data->nr_vertexs_bigger_graph = max(data->nr_vertexs_bigger_graph, nr_vertexs_bigger_graph);
			}
	}
}


/* =============================================================================
 * deleteInput
 * =============================================================================
*/

void deleteData(Data data) {
	int i;
	for (i = 0; i < data->nr_vertexs; i++) {
		Connection pointer;
		for (pointer = data->vertexs[i].head; pointer != NULL; ) {
			Connection pointer_delete = pointer;
			pointer = pointer->next;
			free(pointer_delete);
		}
	}
	free(data->vertexs);
	free(data);
}


/* =============================================================================
 * createDataAux
 * =============================================================================
*/

void createDataAux(Data data, int vertex_1, int vertex_2) {
	Connection current;
	if ((current = (Connection) malloc(sizeof(struct connection))) == NULL) {
		perror("Error in malloc in createDataAux (current)");
		exit(EXIT_FAILURE);
	}
	current->vertex = vertex_2;
	Connection pointer_backup = data->vertexs[vertex_1 - 1].head;
	data->vertexs[vertex_1 - 1].head = current;
	data->vertexs[vertex_1 - 1].head->next = pointer_backup;
}


/* =============================================================================
 * createData
 * =============================================================================
*/

Data createData() {
    Data data;
	if ((data = (Data) malloc(sizeof(struct data))) == NULL) {
    	perror("Error in malloc in createData (data)");
      	exit(EXIT_FAILURE);
    }
	if (scanf("%d\n%d", &data->nr_vertexs, &data->nr_connections) == 0) {
		perror("Error in scanf in createData");
   		exit(EXIT_FAILURE);
	}
	data->nr_graphs = 0;
	data->nr_vertexs_bigger_graph = 0;
   	if ((data->vertexs = (Vertexs) malloc(data->nr_vertexs * sizeof(struct vertexs))) == NULL) {
   		perror("Error in malloc in createData (data->vertexs)");
   		exit(EXIT_FAILURE);
   	}
	int i;
   	for (i = 0; i < data->nr_vertexs; i++) {
		data->vertexs[i].vertex = i + 1;
		data->vertexs[i].parent = 0;
		data->vertexs[i].is_articulation = false;
		data->vertexs[i].is_max_vertex = false;
		data->vertexs[i].head = NULL;
	}
	for (i = 0; i < data->nr_connections; i++) {
		int vertex_s, vertex_d;
		if (scanf("%d %d", &vertex_s, &vertex_d) == 0) {
			perror("Error in scanf in createData");
   			exit(EXIT_FAILURE);
   		}
		createDataAux(data, vertex_s, vertex_d);
		createDataAux(data, vertex_d, vertex_s);
	}
    return data;
}


/* =============================================================================
 * main
 * =============================================================================
*/

int main () {
	Data data;
	data = createData();
	dfs(data, 0);
	dfs(data, 1);
	printResults(data);
	deleteData(data);
	return 0;
}
