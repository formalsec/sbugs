#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Node node;
struct Node {
	int id;
	struct Node *next;
};

typedef struct Router router;
struct Router {
	int d;
	int d2;
	int low;
	int FLAG_CUT;
	node *head;
};

router *routers;

void delete_linked_list(node *p) {
	node *aux;
	if(p == NULL) return;
	while(p != NULL) {
		aux = p->next;
		free(p);
		p = aux;
	}
}

void clean_memory(int N) {
	int i;
	for(i = 0; i < N; i++) {
		delete_linked_list(routers[i].head);
	}
}

int DFS_Visit(int index,int time,int predecessor,int *subnet_id,int *number_of_cut_vertices) {
	int l = -1, FLAG_CV = 0, root_vertex_counter = 0;
	node *n = routers[index].head;
	routers[index].d = routers[index].low = time;
	time++;
	while(n != NULL) {
		if(routers[n->id - 1].d == 0 || n->id != predecessor) {
			if(routers[n->id - 1].d == 0) {
				time = DFS_Visit(n->id - 1,time,index + 1,subnet_id,number_of_cut_vertices);
				if(predecessor != 0 && routers[index].d <= routers[n->id - 1].low && FLAG_CV == 0) {
					FLAG_CV = 1;
					(*number_of_cut_vertices)++;
					routers[index].FLAG_CUT = 1;
				}
				if(predecessor == 0 && FLAG_CV == 0) {
					root_vertex_counter++;
					if(root_vertex_counter == 2) {
						FLAG_CV = 1;
						(*number_of_cut_vertices)++;
						routers[index].FLAG_CUT = 1;
					}
				}
			}
			if(l == -1) l = routers[n->id - 1].low;
			else if(routers[n->id - 1].low < l) l = routers[n->id - 1].low;
		}
		n = n->next;
	}
	if(l < routers[index].low && l != -1) routers[index].low = l;
	if(index + 1 > *(subnet_id)) *(subnet_id) = index + 1;

	return time;
}

int DFS_Visit_2(int index,int time,int *number_of_subnet_elements) {
	node *n = routers[index].head;
	routers[index].d2 = time;
	time++;
	(*number_of_subnet_elements)++;
	while(n != NULL) {
		if(routers[n->id - 1].d2 == 0 && routers[n->id - 1].FLAG_CUT == 0) {
			time = DFS_Visit_2(n->id - 1,time,number_of_subnet_elements);
		}
		n = n->next;
	}
	return time;
}

void print_ordered_subnet_ids(int *v, int size) {
	int i;
	for(i = 0; i < size; i++) {
		if(v[i] != 0) {
			printf("%d",v[i]);
			break;
		}
	}
	i++;
	for(; i < size; i++) {
		if(v[i] != 0) printf(" %d",v[i]);
	}
	puts("");
}

int main(int argc, char const *argv[])
{
	int i,N,M;
	int *ordered_subnet_ids;

	scanf("%d",&N);

	routers = (router *) can_fail_malloc(sizeof(router)*N);
	ordered_subnet_ids = (int *) can_fail_malloc(sizeof(int)*N);
	for(i = 0; i < N; i++) {
		ordered_subnet_ids[i] = 0;
		routers[i].d = 0;
		routers[i].d2 = 0;
		routers[i].FLAG_CUT = 0;
		routers[i].head = NULL;
	}

	scanf("%d",&M);

	/* INICIALIZACAO DAS LISTAS DE ADJACENCIAS */

	while(M != 0) {
		int u,v;
		node *aux;
		scanf("%d",&u);
		scanf("%d",&v);

		if(routers[u-1].head == NULL) {
			routers[u-1].head = (node *) can_fail_malloc(sizeof(node));
			routers[u-1].head->id = v;
			routers[u-1].head->next = NULL;
		}
		else {
			aux = routers[u-1].head;
			routers[u-1].head = (node *) can_fail_malloc(sizeof(node));
			routers[u-1].head->id = v;
			routers[u-1].head->next = aux;
		}

		if(routers[v-1].head == NULL) {
			routers[v-1].head = (node *) can_fail_malloc(sizeof(node));
			routers[v-1].head->id = u;
			routers[v-1].head->next = NULL;
		}
		else {
			aux = routers[v-1].head;
			routers[v-1].head = (node *) can_fail_malloc(sizeof(node));
			routers[v-1].head->id = u;
			routers[v-1].head->next = aux;
		}

		M--;
	}

	/* PRIMEIRA DFS */

	int R = 0, time = 1, subnet_id = 0, number_of_cut_vertices = 0;
	for(i = 0; i < N; i++) {
		if(routers[i].d == 0) {
			time = DFS_Visit(i,time,0,&subnet_id,&number_of_cut_vertices);
			ordered_subnet_ids[subnet_id - 1] = subnet_id;
			subnet_id = 0;
			R++;
		}
	}

	/* SEGUNDA DFS */

	int number_of_subnet_elements = 0, max = 0;
	time = 1;
	for(i = 0; i < N; i++) {
		if(routers[i].d2 == 0 && routers[i].FLAG_CUT == 0) {
			time = DFS_Visit_2(i,time,&number_of_subnet_elements);
			if(number_of_subnet_elements > max) max = number_of_subnet_elements;
			number_of_subnet_elements = 0;
		}
	}

	printf("%d\n",R);
	print_ordered_subnet_ids(ordered_subnet_ids,N);
	printf("%d\n%d\n",number_of_cut_vertices,max);

	clean_memory(N);
	free(routers);
	free(ordered_subnet_ids);

	return 0;
}