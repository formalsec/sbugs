/*
 * Main file for student grade simulator
 * Alexandre Pires nº92414 ; Joao Fonseca nº92497
 * ASA - LEIC-A - 2019/20 - IST
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

#define INFINITE 100

typedef struct adj_node {
        int edge_to;
        /* Possibly have more attributes? We can use arrays if that's better.*/
        struct adj_node* next;
} *adj_node_ptr;

/* 
 * The structure used for the graph.
 */
typedef struct graph {
        int order; /*the order of the graph, i.e., its number of nodes.*/
        adj_node_ptr* adjacency_list;
} graph;

/* 
 * Allocates memory for and initializes an adjacency list and returns it.
 * If 'number_of_nodes' is less than or equal to 0, returns NULL. This
 * function can also return NULL if there was a memory allocation error.
 */
adj_node_ptr* adj_init(int number_of_nodes)
{
    if (number_of_nodes > 0) {
        int i = 0;
        adj_node_ptr* adj_list = malloc(sizeof(adj_node_ptr) * number_of_nodes);

        if (adj_list != NULL) {
            while (i < number_of_nodes) {
                adj_list[i] = NULL;
                i++;
            }
        }

        return adj_list;
    }

    return NULL;
}

/* 
 * Deletes the head node from one of the vertices of an adjacency list.
 */
adj_node_ptr adj_delete_node(adj_node_ptr head)
{
    if (head != NULL) {
        adj_node_ptr new_head = head->next;
        free(head);
        head = new_head;
    }

    return head;
}

/* 
 * Deletes the given adjacency list.
 */
void adj_delete_list(adj_node_ptr* list, int number_of_vertices) 
{
    if (list != NULL && number_of_vertices > 0) {
        int i = 0;

        while (i < number_of_vertices) {
            while(list[i] != NULL)
                    list[i] = adj_delete_node(list[i]);
            i++;
        }

        free(list);
}
}

adj_node_ptr adj_get_next_edge(adj_node_ptr current) 
{
    if (current != NULL)
        return current->next;
    return NULL;
}

/* 
 * Creates a new entry for an adjacency list with an edge to the vertex of 
 * index 'edge_to'.
 */
adj_node_ptr adj_new_entry(int edge_to)
{
    adj_node_ptr new_entry = malloc(sizeof(struct adj_node));

    if (new_entry != NULL) {
        new_entry->edge_to = edge_to;
        new_entry->next = NULL;
    }

    return new_entry;
}

/* 
 * Adds an edge between the vertex given by 'head' and the vertex with the index
 * 'edge_to'. If 'head' is NULL or 'edge_to' is less than 0, returns 'head'
 * without any kind of change.
 */
adj_node_ptr adj_add_edge(adj_node_ptr head, int edge_to)
{
    if (edge_to >= 0) {
        adj_node_ptr new_edge = adj_new_entry(edge_to);
        new_edge->next = head;
        return new_edge;
    }
    return NULL;
}

graph* graph_create(int number_of_vertices) 
{
    if (number_of_vertices > 0) {
        graph* g = malloc(sizeof(graph));

        if (g != NULL) {
            g->order = number_of_vertices;
            g->adjacency_list = adj_init(number_of_vertices);
        }

        return g;
    }

    return NULL;
}

void graph_delete(graph* g) 
{
    if (g != NULL) {
        adj_delete_list(g->adjacency_list, g->order);
        free(g);
    }
}

adj_node_ptr graph_get_node_edges(graph* g, int vertex_index) 
{
    return (g != NULL && vertex_index < g->order) ? 
            g->adjacency_list[vertex_index] : NULL;
}

int graph_get_order(graph* g) {
    if (g != NULL)
        return g->order;
    return -1;
}

void graph_add_edge(graph* g, int u, int v) 
{
    if (g != NULL && u < g->order && v < g->order && v >= 0 && u >= 0) {
        adj_node_ptr *vertex_head = &(g->adjacency_list[u]);
        *vertex_head = adj_add_edge(*vertex_head, v);
    }
}  

int tarjan_visit(int i, graph* relations, int *grades,int *ids){
	ids[i] = 1;
    adj_node_ptr adj_list = NULL;

	for(adj_list = graph_get_node_edges(relations, i); adj_list != NULL; adj_list = adj_get_next_edge(adj_list)){
		if (ids[adj_list->edge_to] == INFINITE){
			grades[i] = MAX(grades[i], tarjan_visit(adj_list->edge_to, relations, grades, ids));
		}
		grades[i] = MAX(grades[i], grades[adj_list->edge_to]);
	}

    return grades[i];
}

void tarjan(graph* relations, int *grades, int n_students)
{
	int *ids = (int*) malloc(sizeof(int)* n_students);	/*initializes ids array;*/
    adj_node_ptr adj_list = NULL;

    int i = 0;
    
	for (i = 0; i < n_students; i++) {
		ids[i] = INFINITE;
	}
	for (i = 0; i < n_students; i++){
		tarjan_visit(i, relations, grades, ids);
	}

    for (i = 0; i < n_students; i++) {
		ids[i] = INFINITE;
	}
	for (i = n_students -1; i >= 0; i--){
		tarjan_visit(i, relations, grades, ids);
	}

    for(i = 0; i < n_students; i++){
        for(adj_list = graph_get_node_edges(relations, i); adj_list != NULL; adj_list = adj_get_next_edge(adj_list)){
	        grades[i] = MAX(grades[i], grades[adj_list->edge_to]);
        }
    }

    for(i = n_students -1; i >= 0; i--){
        for(adj_list = graph_get_node_edges(relations, i); adj_list != NULL; adj_list = adj_get_next_edge(adj_list)){
	        grades[i] = MAX(grades[i], grades[adj_list->edge_to]);
        }
    }

	free(ids);
}


int main(){

	int n_students = 0;										/*Number of students*/
	int n_relations = 0;									/*Number of relations between students*/

	int *grades = NULL;											/*Array to store student grades*/
	graph *relations = NULL;	
    int i = 0;

	/*
	 * Processes input and initializes grade array and relations matrix
	 */

	scanf("%d,%d", &n_students, &n_relations);				/*Gets n_students and n_relations values*/

	grades = (int*) malloc(sizeof(int)* n_students);		/*initializes grade array*/

	/*Gets input values for grade array*/
	for (i = 0; i < n_students; i++){
		scanf("%d", &grades[i]);
	}

	/*Initializes relations matrix*/
	relations = graph_create(n_students);

	/*Gets input values for each relation*/
	for(i = 0; i < n_relations; i++){
		int student, friend;
		scanf("%d %d", &student, &friend);
		graph_add_edge(relations, student - 1, friend - 1);
	}

	/*
	 * Calculates grade changes based on students' relations
	 */
	tarjan(relations, grades, n_students);

	/*
	 * Prints final grades
	 */
	for (i = 0; i < n_students; i++){
		printf("%d\n", grades[i]);
	}

	/*
	 * Frees memory
	 */
	free(grades);
	graph_delete(relations);

	return 0;
}