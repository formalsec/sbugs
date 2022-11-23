#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 30

typedef struct VERTEX {
	int vertex;
	int visited;
	int count;
	int *adj;
	int max_path_size;
} VERTEX;

VERTEX *initGraph(int *dominos, int *dependencies) {
	int i = 0;
	char buff[MAX_SIZE];
	if (fgets(buff, MAX_SIZE, stdin) == NULL) return NULL;
	*dominos = atoi(strtok(buff, " "));
	*dependencies = atoi(strtok(NULL, "\n"));
	VERTEX *graph = (VERTEX *) can_fail_malloc(*dominos * sizeof(VERTEX));
	for(i = 0; i < *dominos; i++) {
		graph[i].vertex = i+1;
		graph[i].visited = 0;
		graph[i].count = 0;
		graph[i].adj = (int *) can_fail_malloc(1 * sizeof(int));
		graph[i].max_path_size = 0;
	}
	return graph;
}

void readDependencies(VERTEX *graph, int dependencies) {
	int i = 0, u = 0, v = 0;
	char buff[MAX_SIZE];
	for (i = 0; i < dependencies; i++) {
		if (fgets(buff, MAX_SIZE, stdin) == NULL) return;
		u = atoi(strtok(buff, " "));
		v = atoi(strtok(NULL, "\n"));
		graph[u-1].adj[graph[u-1].count] = v;
		graph[u-1].count++;
		graph[u-1].adj = (int *) can_fail_realloc(graph[u-1].adj, (graph[u-1].count + 1) * sizeof(int));
	}
}

void DFS(VERTEX *graph, int u, int path_size, int vertex) {
	int i = 0, v = 0;
	graph[u-1].visited = 1;
	path_size++;
	if (graph[u-1].count == 0) {
		if (path_size > graph[vertex-1].max_path_size)
			graph[vertex-1].max_path_size = path_size;	
	}
	for (i = 0; i < graph[u-1].count; i++) {
		v = graph[u-1].adj[i];
		if (graph[v-1].visited == 0) {
			DFS(graph, v, path_size, vertex);
		}
	}
	graph[u-1].visited = 0;
}

void result(VERTEX *graph, int dominos) {
	int i = 0, j = 0, n = 0, biggest_path = 0;
	int vertices[dominos];
	for (i = 0; i < dominos; i++) {
		vertices[i] = i+1;
	}
	for (i = 0; i < dominos; i++) {
		for (j = 0; j < graph[i].count; j++) {
			vertices[graph[i].adj[j]-1] = 0;
		}
	}
	for (i = 0; i < dominos; i++) {
		if (vertices[i] != 0) {
			n++;
		}
		if (graph[i].max_path_size > biggest_path) {
			biggest_path = graph[i].max_path_size;
		}
	}
	printf("%d %d\n", n, biggest_path);
}

void run(VERTEX *graph, int dominos) {
	int i = 0, path_size = 0;
	for (i = 0; i < dominos; i++) {
		DFS(graph, graph[i].vertex, path_size, graph[i].vertex);
	}
	result(graph, dominos);
}

void freeMem(VERTEX *graph, int dominos) {
	int i = 0;
	for (i = 0; i < dominos; i++) {
		free(graph[i].adj);
	}
	free(graph);
}

int main() {
	int dominos = 0, dependencies = 0;
	VERTEX *graph = initGraph(&dominos, &dependencies);
	readDependencies(graph, dependencies);
	run(graph, dominos);
	freeMem(graph, dominos);
	return 0;
}