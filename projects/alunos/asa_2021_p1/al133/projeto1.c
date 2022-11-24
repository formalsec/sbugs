#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct linked_ints {
	int n;
	int level;
	struct linked_ints * next;
} linked_ints;

typedef struct node {
	linked_ints * connections;
	int incoming;
	int chain;
} node;

int get_node(linked_ints * head) {
	return head->n;
}

int get_level(linked_ints * head) {
	return head->level;
}

linked_ints * push(linked_ints * head, int n) {
	linked_ints * new_head = (linked_ints *) can_fail_malloc(sizeof(linked_ints));
	new_head->n = n;
	new_head->level = 1;
	new_head->next = head;
	return new_head;
}

linked_ints * push_both(linked_ints * head, int n, int level) {
	linked_ints * new_head = (linked_ints *) can_fail_malloc(sizeof(linked_ints));
	new_head->n = n;
	new_head->level = level;
	new_head->next = head;
	return new_head;
}

linked_ints * pop(linked_ints * head) {
	linked_ints * new_head = head->next;
	free(head);
	return new_head;
}

void destroy(linked_ints * head) {
	while (head != NULL) {
		head = pop(head);
	}	
}

void print(linked_ints * head) {
	linked_ints * printing = head;
	while (printing != NULL) {
		printf("N: %d\n", printing->n + 1);
		printing = printing->next;
	}
}

void propagate(node * graph, linked_ints * path, int start) {
	int chain = start;
	linked_ints * iterator = path;
	while (iterator != NULL) {
		if (chain > graph[iterator->n].chain) {
			graph[iterator->n].chain = chain;
		} else {
			return;
		}
		chain++;
		iterator = iterator->next;
	}
}

int longest_chain(node * graph, linked_ints * queue) {

	int max_chain = 0;
	int i;
	linked_ints * path = NULL;

	while (queue != NULL) {
		int node = get_node(queue);
		int level = get_level(queue);
		queue = pop(queue);

		if (graph[node].chain != -1) {
			int new_chain = level + graph[node].chain - 1;
			if (new_chain > max_chain)
				max_chain = new_chain;
			propagate(graph, path, graph[node].chain + 1);
			
			if (queue == NULL) break;

			int step = level - get_level(queue);
			for (i = 0; i < step; i++)
				path = pop(path);
			
			continue;
		}
		path = push(path, node);
		linked_ints * iterator = graph[node].connections;

		if (iterator == NULL) { /* Doesn't have any childs, reached the end of the graph */
			propagate(graph, path, 1);
			if (level > max_chain)
				max_chain = level;
			
			if (queue == NULL) break;
			int step = level - get_level(queue);
			for (i = 0; i < step + 1; i++) {
				path = pop(path);
			}
		}

		while (iterator != NULL) {
			int end = get_node(iterator);
			iterator = iterator->next;
			queue = push_both(queue, end, level + 1);
		}
				
	}

	destroy(queue);
	return max_chain;

}


int main() {
	int n_dependencies, v;
	int i;
	node * graph;

	if (scanf("%d %d", &v, &n_dependencies) <= 0) {
		perror("Error reading arguments");
	}
	graph = (node *) can_fail_malloc(sizeof(node) * v);

	for (i = 0; i < v; i++) {
		graph[i].incoming = 0;
		graph[i].connections = NULL;
		graph[i].chain = -1;
	}

	for (i = 0; i < n_dependencies; i++) {
		int source, end;
		if (scanf("%d %d", &source, &end) <= 0) {
			perror("Error reading arguments");
		}
		graph[source - 1].connections = push(graph[source - 1].connections, end - 1);
		graph[end - 1].incoming++;
	}

	linked_ints * queue = NULL;
	int n_sources = 0;

	for (i = 0; i < v; i++) {
		if (graph[i].incoming == 0) {
			n_sources++;
			queue = push(queue, i);

		}
	}

	printf("%d %d\n", n_sources, longest_chain(graph, queue));

	for (i = 0; i < v; i++) {
		destroy(graph[i].connections);
	}
	free(graph);
	
	return 0;
}

