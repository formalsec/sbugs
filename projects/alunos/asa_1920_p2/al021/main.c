#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/*
 * Main file for covid simulator
 * Alexandre Pires nº92414 ; Joao Fonseca nº92497
 * ASA - LEIC-A - 2019/20 - IST
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

#define INFINITE 100
#define NONE -1
#define TRUE 1
#define FALSE 0

typedef int **adj_matrix;

/* 
 * The structure used for the graph.
 */
typedef struct ll_node {
        int i;
        int capacity;
        struct ll_node* reverse; /* Points to the reverse edge*/
        struct ll_node* next;
} *ll_node_ptr;

typedef struct graph {
        int order; /*the order of the graph, i.e., its number of nodes.*/
        ll_node_ptr* llacency_list;
} graph;

/*
 * The structure used for the circular list
 */

typedef struct circ_list_struct{
    int item;                           /*Value stored*/
    struct circ_list_struct *next;          /*Pointer to next node in the circular list*/
    struct circ_list_struct *prev;          /*Pointer to prev node in the circular list*/
} circ_list;


/*
 * Queue functions
 */

/*
 * Checks if list is empty
 */
int c_list_is_empty(circ_list **root){
    return *root == NULL;
}

/*
 * Adds an element to the end of the list
 */
void c_list_add_last(circ_list **root, int item){
    circ_list* new = (circ_list*) can_fail_malloc(sizeof(circ_list));
    circ_list* last = NULL;
    new->item = item;

    if(c_list_is_empty(root)){
        (*root) = new;
        new->prev = new;
        new->next = new;
    }
    else{
        last = (*root)->prev;
        new->item = item;
        last->next = new;
        new->prev = last;
        (*root)->prev = new;
        new->next = *root;
    }
}

/*
 * Takes the first element of the list
 */
int c_list_pop(circ_list **root){
    int item = NONE;
    circ_list *aux = *root;
    struct circ_list_struct *prev = NULL;
    struct circ_list_struct *next = NULL;

    if(!c_list_is_empty(root)) {
        item = (*root)->item;
        if(*root != (*root)->next){
            item = (*root)->item;
            *root = (*root)->next;
            prev = aux->prev;
            next = aux->next;
            prev->next = next;
            next->prev = prev;
            free(aux);
        }
        else{

            free(*root);
            *root = NULL;
        }
        return item;
    }
    else
        return -1;
}

/*
 * Frees all memory from the list
 */
void c_list_free(circ_list **root){
    if(!c_list_is_empty(root)) {
        while(*root != NULL) c_list_pop(root);
    }
}

/*
 * Checks if there is an item i in the list
 */
int c_list_is_in(circ_list *root, int i){
    circ_list *aux = root;
    while(aux->next != root){
        if(aux->item == i)
            return 1;
        aux = aux->next;
    }
    if(aux->item == i)
        return 1;
    else
        return 0;
}

/*
 * Graph functions
 */

/* 
 * Allocates memory for and initializes an adjacency list and returns it.
 * If 'number_of_nodes' is less than or equal to 0, returns NULL. This
 * function can also return NULL if there was a memory allocation error.
 */
ll_node_ptr* ll_adj_init(int number_of_nodes)
{
    int i = 0;
    ll_node_ptr* ll_list = can_fail_malloc(sizeof(ll_node_ptr) * number_of_nodes);

    while (i < number_of_nodes) {
        ll_list[i] = NULL;
        i++;
    }
    return ll_list;
}

/* 
 * Deletes the head node from one of the vertices of an llacency list.
 */
ll_node_ptr ll_delete_node(ll_node_ptr head)
{
    ll_node_ptr new_head = head->next;
    free(head);
    head = new_head;
    return head;
}

/* 
 * Deletes the given llacency list.
 */
void ll_delete_list(ll_node_ptr* list, int number_of_vertices) 
{
    int i = 0;

    while (i < number_of_vertices) {
        while(list[i] != NULL)
            list[i] = ll_delete_node(list[i]);
        i++;
    }

    free(list);
}

ll_node_ptr ll_get_next_node(ll_node_ptr current) 
{
    return current->next;
}

int ll_get_i(ll_node_ptr node) {
    return node->i;
}

/* 
 * Creates a new entry for an llacency list with an edge to the vertex of 
 * index 'edge_to'.
 */
ll_node_ptr ll_new_entry(int edge_to, int capacity)
{
    ll_node_ptr new_entry = can_fail_malloc(sizeof(struct ll_node));

    new_entry->i = edge_to;
    new_entry->capacity = capacity;
    new_entry->next = NULL;
    new_entry->reverse = NULL;

    return new_entry;
}

int get_edge_cap(ll_node_ptr node) {
    return node->capacity;
}

void set_edge_cap(ll_node_ptr node, int new_cap) {
    node->capacity = new_cap;
}

ll_node_ptr get_reverse_edge(ll_node_ptr edge) {
    return edge->reverse;
}

/* Sets the reverse edge of edge_1 as edge_2. */
void set_reverse_edge(ll_node_ptr edge_1, ll_node_ptr edge_2) {
    if (edge_1 != NULL && edge_2 != NULL)
        edge_1->reverse = edge_2;
}

graph* graph_create(int number_of_vertices) 
{
    graph* g = can_fail_malloc(sizeof(graph));

    g->order = number_of_vertices;
    g->llacency_list = ll_adj_init(number_of_vertices);
    
    return g;
}

void graph_delete(graph* g) 
{
    ll_delete_list(g->llacency_list, g->order);
    free(g);
}

ll_node_ptr graph_get_node_edges(graph* g, int vertex_index) 
{
    return g->llacency_list[vertex_index];
}

int graph_get_order(graph* g) {
    return g->order;
}

int graph_has_edge(graph* g, int u, int v){
    ll_node_ptr aux = NULL;
    ll_node_ptr *vertex_head = &(g->llacency_list[u]);

    for(aux = *vertex_head; aux != NULL; aux = aux->next){
        if(aux->i == v)
            return TRUE;
    }
    return FALSE;
}

ll_node_ptr graph_get_edge(graph* g, int u, int v){
    ll_node_ptr aux = NULL;
    ll_node_ptr *vertex_head = &(g->llacency_list[u]);

    for(aux = *vertex_head; aux != NULL; aux = aux->next){
        if(aux->i == v)
            return aux;
    }
    return NULL;
}

/* Adds an edge to the graph and returns it. */
ll_node_ptr graph_add_edge(graph* g, int u, int v, int cap) 
{
    if(!graph_has_edge(g, u, v)){
        ll_node_ptr *vertex_head = &(g->llacency_list[u]);
        ll_node_ptr new_edge = ll_new_entry(v, cap);

        if (*vertex_head == NULL){
            *vertex_head = new_edge;
        }
        else{
            ll_node_ptr aux = NULL;
            int found = FALSE;

            /* Keeps list ordered */
            for(aux = *vertex_head; aux->next != NULL; aux = aux->next){
                if(aux->next->i >= new_edge->i){
                    new_edge->next = aux->next;
                    aux->next = new_edge;
                    found = TRUE;
                    break;
                }
            }
            if(!found)
                aux->next = new_edge;
        }
        return new_edge;
    }
    return NULL;
}  

void add_edge_and_reverse(graph* g, int u, int v, int cap) {
    if (g != NULL) {
        if (u >= 0 && u < g->order && v >= 0 && v < g->order) {
            ll_node_ptr uu = graph_add_edge(g, u, v, cap);
            ll_node_ptr vv = graph_add_edge(g, v, u, 0);
            set_reverse_edge(uu, vv);
            set_reverse_edge(vv, uu);
        }
    }
}


/*
 * Flux functions
 */

/*
 * Runs a BFS from source to sink, storing predecessors in pred, and visits in visited
 */
int BFS(graph* g, int source,int sink, int pred[]) 
{ 
    circ_list* queue = NULL;                            /*Saves gray colored edges*/
    int v = -1;                                         /*Current edge being visited*/
    int i = 0;

    ll_node_ptr ll_list = NULL;                         /*Saves list of neighbours*/

    for (i = 0; i < graph_get_order(g); i++) { 
        pred[i] = NONE;
    } 

    c_list_add_last(&queue,source);

    while (!c_list_is_empty(&queue)){ 
        v = c_list_pop(&queue);
        ll_list = graph_get_node_edges(g, v);

        for (; ll_list != NULL; ll_list = ll_get_next_node(ll_list)){ 
            if(pred[ll_list->i] == NONE && ll_list->i != source && get_edge_cap(ll_list) > 0){

                pred[ll_list->i] = v;
                c_list_add_last(&queue,ll_list->i);

                if(ll_list->i == sink){
                    c_list_free(&queue);
                    return 1;
                }
            }
        }
    }
    c_list_free(&queue);
    return -1; 
} 

/*
 * Gets the maximum flow from a graph
 */
int max_flow(graph* g,int source, int sink){
    int pred[graph_get_order(g)];       /*Stores predecessors*/
    int max_flow = 0;                                           /*Stores maximum flow possible*/
    int parent = sink;
    ll_node_ptr edge = NULL;

    /*
     * Will run bfs until no path from source to sink exists
     */
    while(BFS(g,source,sink,pred) != -1){

        /* Sets path capacity as 0 and reverse as 1*/
        for(parent = sink; pred[parent] != NONE; parent = pred[parent]){
            edge  = graph_get_edge(g,pred[parent],parent);
            set_edge_cap(edge,0);
            set_edge_cap(get_reverse_edge(edge),1);
        }

        max_flow++;
    }

    return max_flow;
}


/*
 * Main
 */

int main(){

	int n_avenues = 0;								    /*Number of avenues, lines*/
	int n_streets = 0;									/*Number of streets, columns*/

    int n_people = 0;                                   /*Number of citizens*/
    int n_markets = 0;                                  /*Number of supermarkets*/

	graph* city = NULL;

    int max_people = 0;                                 /*Stores the max number of people allowed*/

    /* Optimization variables */
    int cord = 0;
    int totalv = 0;

    /* iterators */
    int i = 0;
    int j = 0;

	/*
	 * Gets and processes input and initializes flux graph
	 */

	scanf("%d %d", &n_avenues, &n_streets);				/*Gets number of avenues and streets*/

    totalv = n_streets*n_avenues;

    /*Initializes flux matrix, with super sink and super source*/
	city = graph_create(totalv*2 + 2);

    /* Adds edges in every direction for each vertex */ 
    for(i = 0; i < n_avenues; i++){
        for(j = 0; j < n_streets; j++){
            cord = i*n_streets + j;

            if(j != 0){
                /* Exit IJ to Entry I(J-1), aka right to left*/
                add_edge_and_reverse(city, cord + totalv, cord - 1, 1);

                /* Exit I(J-1) to entry IJ, aka from left to right*/
                add_edge_and_reverse(city, cord + totalv - 1, cord, 1);
            }
            if(i != 0){
                /* Exit IJ to Entry (I-1)J, aka from bottom to top*/
                add_edge_and_reverse(city, cord + totalv, (i - 1) * n_streets + j, 1);

                /* Exit (I-1)J to Entry IJ, aka from top to bottom*/
                add_edge_and_reverse(city, (i - 1) * n_streets + j + totalv, cord, 1);
            }
            /* Adds edge from Entry IJ to Exit IJ */
            add_edge_and_reverse(city, cord, cord + totalv, 1);
        }
    }

	scanf("%d %d", &n_markets, &n_people);				/*Gets number of supermarkets and citizens*/
    
    /* Adds edges from supermarkets to sinks */
    for(i = 0; i < n_markets; i++){
        int avenue = 0;
        int street = 0;
        scanf("%d %d", &avenue,&street);    /*gets location of each supermarket*/
        add_edge_and_reverse(city, (avenue-1)*n_streets+(street-1)+totalv, totalv*2+1, 1);
    }
    /* Adds edges from sources to citizens */
    for(i = 0; i < n_people; i++){
        int avenue = 0;
        int street = 0;
        scanf("%d %d", &avenue,&street);    /*gets location of each supermarket*/
        add_edge_and_reverse(city, totalv*2, (avenue-1)*n_streets+(street-1), 1);
    }

    /*
     * Calculates max flow possible
     */

    max_people = max_flow(city,totalv*2,totalv*2 + 1);

    /*
     * Prints final result
     */
    printf("%d\n",max_people);

	/*
	 * Frees memory
	 */
	graph_delete(city);

	return 0;
}