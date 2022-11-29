#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#define ERR(str) { fprintf(stderr, "%s\n", str); exit(1); }


enum {
    FALSE = 0,
    TRUE  = 1
};

typedef char bool_t;

typedef struct subnetwork {
	int * subnetwork;
	unsigned size;
} * subnetwork_t;

typedef struct list_node {
	void * data;
	struct list_node * next;
} * list_node_t;


typedef struct list {
	list_node_t head;
	list_node_t tail;
	unsigned size;
	unsigned amount;
	short data_size;
} * list_t;


typedef struct graph_node {
	int id;
	unsigned size;
	unsigned amount;
	int * adjacencies;
} graph_node_t;


typedef struct graph {
	int num_nodes;
	struct graph_node * nodes;
} * graph_t;


typedef struct queue queue_t;


struct queue {
    long pop; /* points before element to pop */
    long push;
    long capacity;
    void** elements;
};

enum config {
    QUEUE_GROWTH_FACTOR = 2,
};



subnetwork_t
create_subnetwork(unsigned size)
{
	subnetwork_t new_subnetwork = can_fail_malloc(sizeof(subnetwork_t));
	new_subnetwork->size = size;
	new_subnetwork->subnetwork = can_fail_malloc(sizeof(int) * size);

	return new_subnetwork;

}

void
subnetwork_free(subnetwork_t sub)
{
	free(sub->subnetwork);
}

/* =============================================================================
 * list_node_create
 *
 * Declares and allocates memory for a node that contains a pointer to
 * any type of given data and a pointer to the next element in the linked list.
 *
 * @param data: a pointer to any kind of data, which is stored in the node
 * @return: the created node
 * =============================================================================
 */
static list_node_t
list_node_create(void * data, int data_size)
{
	list_node_t node = can_fail_malloc(sizeof(struct list_node));

	if (!node)
		ERR("Could not allocate memory for node.");

	node->data = can_fail_malloc(data_size);
	memcpy(node->data, data, data_size);
	node->next = NULL;

	return node;
}


/* =============================================================================
 * list_create
 *
 * Declares and allocates memory to an empty linked list.
 * Its head and tail initially point to NULL and the size is set to 0.
 *
 * @return: the created linked list
 * =============================================================================
 */
list_t
list_create(int data_size)
{
	list_t list = can_fail_malloc(sizeof(struct list));

	if (!list) {
		ERR("Could not allocate memory for linked list.");
	}

	list->data_size = data_size;
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;

	return list;
}


/* =============================================================================
 * list_getSize
 *
 * Gets the size of the given linked list.
 *
 * @param list: the linked list of which we want the size
 * @return: a long int with the size of the linked list
 * =============================================================================
 */
long
list_getSize(list_t list)
{
	return list->size;
}


/* =============================================================================
 * list_iter_reset
 *
 * Function used for linked list iteration purposes.
 * Prepares a given node to iterate a given list by making it point to
 * the head of said list.
 *
 * @param list: the linked list which we want to iterate
 * @param node: the node to be used to iterate
 * =============================================================================
 */
void
list_iter_reset(list_t list, list_node_t * node)
{
	*node = list->head;
}


/* =============================================================================
 * list_iter_hasNext
 *
 * Function used for linked list iteration purposes.
 * Despite its name leading into verifying whether the node we're at is not
 * the end of the list we're iterating, this function returns true if the node
 * we're at is not NULL.
 *
 * @param node: the node used for iteration
 * @return: 1 (true) if we're done iterating the list, otherwise 0 (false)
 * =============================================================================
 */
int
list_iter_hasNext(list_node_t * node)
{
	return (*node != NULL) ? 1 : 0;
}


/* =============================================================================
 * list_iter_next
 *
 * Function used for linked list iteration purposes.
 * Given a node being used for list iteration, makes it equal to the next
 * node in the linked list.
 *
 * @param node: the node used for iteration
 * =============================================================================
 */
void
list_iter_next(list_node_t * node)
{
	if (node != NULL)
		*node = (*node)->next;
}


/* =============================================================================
 * list_insert_start
 *
 * Inserts a node containing the given data at the beginning of the given list.
 *
 * @param list: the linked list in which the data is to be inserted
 * @param data: a pointer to the data to be inserted
 * =============================================================================
 */
void
list_insert_start(list_t list, void * data)
{
	list_node_t temp, node = list_node_create(data, list->data_size);

	if (list->size == 0) {
		list->head = node;
		list->tail = node;
	} else {
		temp = list->head;
		node->next = temp;
		list->head = node;
	}

	list->size++;
}


/* =============================================================================
 * list_insert
 * 
 * Inserts a node containing the given data at the end of the given list.
 *
 * @param list: the linked list in which the data is to be inserted
 * @param data: a pointer to the data to be inserted
 * =============================================================================
 */
void
list_insert(list_t list, void * data)
{
	list_node_t node = list_node_create(data, list->data_size);

	if (list->size == 0) {
		list->head = node;
		list->tail = node;
	} else {
		list->tail->next = node;
		list->tail = node;
	}

	list->size++;
}


/* =============================================================================
 * list_node_free
 *
 * Recursive function that frees all the nodes in a linked list.
 *
 * @param node: the node we're traversing; initially the head of the list
 * =============================================================================
 */
static void
list_node_free(list_node_t node)
{
	if (node != NULL)
		list_node_free(node->next);

	if (node != NULL) {
		if (node->data != NULL)
			free(node->data);
		free(node);
	}
}


/* =============================================================================
 * list_remove_start
 *
 * Removes the first node on a given linked list.
 *
 * @param list: the list we want to remove the first node of
 * =============================================================================
 */
void
list_remove_start(list_t list)
{
	list_node_t head = list->head;
	list->head = head->next;
	list_node_free(head);
	list->size--;
}



/* =============================================================================
 * list_remove_end
 *
 * Removes the last node on a given linked list.
 *
 * @param list: the list we want to remove the last node of
 * =============================================================================
 */
void
list_remove_end(list_t list)
{
	list_node_t temp, prev = NULL;
	temp = list->head;

	while (list_iter_hasNext(&temp->next)) {
		prev = temp;
		temp = temp->next;
	}

	list_node_free(temp);

	if (prev) {
		prev->next = NULL;
		list->tail = prev;
	} else {
		list->head = NULL;
		list->tail = NULL;
	}

	if (list->size == 1) {
		list->head = list->tail;
	}

	list->size--;
}


/* =============================================================================
 * list_free
 *
 * Frees the allocated memory for a linked list along with its nodes.
 *
 * @param list: the list we want to free the memory from
 * =============================================================================
 */
void
list_free(list_t list)
{
	list_node_t temp, aux = list->head;
	while (aux != NULL) {
		temp = aux->next;
		free(aux->data);
		free(aux);
		aux = temp;
	}
	free(list);
}


/* =============================================================================
 * graph_create
 * =============================================================================
 */
graph_t
graph_create(int num_nodes)
{
	int i;
	graph_t graph = can_fail_malloc(sizeof(struct graph));

	if (!graph) {
		ERR("Could not allocate memory for linked list.");
	}

	graph->num_nodes = num_nodes;
	graph->nodes = can_fail_malloc(num_nodes * sizeof(struct graph_node));

	for (i = 0; i < num_nodes; i++) {
		graph->nodes[i].id = i + 1;
		graph->nodes[i].size = 15;
		graph->nodes[i].adjacencies = can_fail_malloc(sizeof(int) * 15);
		graph->nodes[i].amount = 0;
	}

	return graph;
}


/* =============================================================================
 * graph_insert
 * =============================================================================
 */
/*
void
graph_insert_connection(graph_t graph, int node1, int node2)
{
	graph_node_t aux;
	list_t adj;

	aux = graph->nodes[node1-1];
	adj = aux.adjacencies;
	list_insert(adj, &node2);

	aux = graph->nodes[node2-1];
	adj = aux.adjacencies;
	list_insert(adj, &node1);
}
*/

int *
graph_get_adjacencies(graph_t graph, int id)
{
	return graph->nodes[id-1].adjacencies;
}


/*
static void
node_destroy(graph_node_t node)
{
	free(node.adjacencies);
}
*/


void
graph_destroy(graph_t graph)
{
	int i, index = graph->num_nodes;

	for (i = 0; i < index; i++)
		free(graph->nodes[i].adjacencies);

	free(graph->nodes);
	free(graph);
}


/* =============================================================================
 * queue_alloc
 * =============================================================================
 */
queue_t*
queue_alloc (long initCapacity)
{
    queue_t* queuePtr = (queue_t*)can_fail_malloc(sizeof(queue_t));

    if (queuePtr) {
        long capacity = ((initCapacity < 2) ? 2 : initCapacity);
        queuePtr->elements = (void**)can_fail_malloc(capacity * sizeof(void*));
        if (queuePtr->elements == NULL) {
            free(queuePtr);
            return NULL;
        }
        queuePtr->pop      = capacity - 1;
        queuePtr->push     = 0;
        queuePtr->capacity = capacity;
    }

    return queuePtr;
}


/* =============================================================================
 * queue_free
 * =============================================================================
 */
void
queue_free (queue_t* queuePtr)
{
    free(queuePtr->elements);
    free(queuePtr);
}


/* =============================================================================
 * queue_isEmpty
 * =============================================================================
 */
bool_t
queue_isEmpty (queue_t* queuePtr)
{
    long pop      = queuePtr->pop;
    long push     = queuePtr->push;
    long capacity = queuePtr->capacity;

    return (((pop + 1) % capacity == push) ? TRUE : FALSE);
}


/* =============================================================================
 * queue_clear
 * =============================================================================
 */
void
queue_clear (queue_t* queuePtr)
{
    queuePtr->pop  = queuePtr->capacity - 1;
    queuePtr->push = 0;
}


/* =============================================================================
 * queue_push
 * =============================================================================
 */
bool_t
queue_push (queue_t* queuePtr, void* dataPtr)
{
    long pop      = queuePtr->pop;
    long push     = queuePtr->push;
    long capacity = queuePtr->capacity;

    assert(pop != push);

    /* Need to resize */
    long newPush = (push + 1) % capacity;
    if (newPush == pop) {

        long newCapacity = capacity + QUEUE_GROWTH_FACTOR;
        void** newElements = (void**)can_fail_malloc(newCapacity * sizeof(void*));
        if (newElements == NULL) {
            return FALSE;
        }

        long dst = 0;
        void** elements = queuePtr->elements;
        if (pop < push) {
            long src;
            for (src = (pop + 1); src < push; src++, dst++) {
                newElements[dst] = elements[src];
            }
        } else {
            long src;
            for (src = (pop + 1); src < capacity; src++, dst++) {
                newElements[dst] = elements[src];
            }
            for (src = 0; src < push; src++, dst++) {
                newElements[dst] = elements[src];
            }
        }

        free(elements);
        queuePtr->elements = newElements;
        queuePtr->pop      = newCapacity - 1;
        queuePtr->capacity = newCapacity;
        push = dst;
        newPush = push + 1; /* no need modulo */
    }

    queuePtr->elements[push] = dataPtr;
    queuePtr->push = newPush;

    return TRUE;
}


/* =============================================================================
 * queue_pop
 * =============================================================================
 */
void*
queue_pop (queue_t* queuePtr)
{
    long pop      = queuePtr->pop;
    long push     = queuePtr->push;
    long capacity = queuePtr->capacity;

    long newPop = (pop + 1) % capacity;
    if (newPop == push) {
        return NULL;
    }

    void* dataPtr = queuePtr->elements[newPop];
    queuePtr->pop = newPop;

    return dataPtr;
}


int min(int a,int b)
{
	return(a<b?a:b);
}


graph_t 
get_input()
{
	graph_t router_graph;
	int N, M, i, u, v;

	if (!scanf("%d", &N))
		exit(1);
	if (!scanf("%d", &M))
		exit(1);

	router_graph = graph_create(N);

	for (i = 0; i < M; i++) {
		if (!scanf("%d %d", &u, &v))
			exit(1);

		if (router_graph->nodes[u-1].amount == router_graph->nodes[u-1].size) {
			int * new = can_fail_realloc(router_graph->nodes[u-1].adjacencies, sizeof(int) * (router_graph->nodes[u-1].amount + 1));
			/*free(router_graph->nodes[u-1].adjacencies);*/
			router_graph->nodes[u-1].adjacencies = new;
			/*free(new);*/
			router_graph->nodes[u-1].amount++;
			router_graph->nodes[u-1].size = router_graph->nodes[u-1].amount + 1;
		}
		

		router_graph->nodes[u-1].adjacencies[router_graph->nodes[u-1].amount++] = v;
		
		if (router_graph->nodes[v-1].amount == router_graph->nodes[v-1].size) {
			int * new = can_fail_realloc(router_graph->nodes[v-1].adjacencies, sizeof(int) * (router_graph->nodes[v-1].amount + 1));
			/*free(router_graph->nodes[v-1].adjacencies);*/
			router_graph->nodes[v-1].adjacencies = new;
			/*free(new);*/
			router_graph->nodes[v-1].amount++;
			router_graph->nodes[v-1].size = router_graph->nodes[v-1].amount + 1;
		}
		router_graph->nodes[v-1].adjacencies[router_graph->nodes[v-1].amount++] = u;
	}

	return router_graph;
}


int
compare_int(const void * a, const void * b)
{
	return *(int*)a - *(int*)b;
}


void 
apUtil(graph_t router_graph,int node,char* isVisited,int* discovery_time,int* parent,int* low_time,char* articulation_points)
{
	int * adjacencies = graph_get_adjacencies(router_graph, node + 1);
	static int time=0;
	int children=0, length = router_graph->nodes[node].amount, i;
	isVisited[node]=1;
	time++;
	discovery_time[node]=low_time[node]=time;

	for (i = 0; i < length; i++) {
		int adjacency = adjacencies[i];
		adjacency--;

		if (!isVisited[adjacency]) {
			children++;
		 	parent[adjacency]=node;
		  	apUtil(router_graph , adjacency, isVisited, discovery_time, parent, low_time, articulation_points);
		  	low_time[node]= min(low_time[node],low_time[adjacency]);

		  	if(parent[node]==-1 && children>1)
				articulation_points[node]=1;
		  	
			if(parent[node]!=-1 && discovery_time[node]<=low_time[adjacency])
				articulation_points[node]=1;  

		}

		else if (adjacency != parent[node])
			low_time[node] = min(low_time[node], discovery_time[adjacency]);
	}
}


char * 
find_articulation_points(graph_t router_graph)
{
	int i, amount_nodes = router_graph->num_nodes, counter = 0;
	int* discovery_time = (int*)can_fail_malloc(sizeof(int)*amount_nodes);
	char * isVisited = can_fail_calloc(amount_nodes, sizeof(char));
	int* parent = (int*)can_fail_malloc(sizeof(int)*amount_nodes);
	int* low_time = (int*)can_fail_malloc(sizeof(int)*amount_nodes);
	char* articulation_points = can_fail_calloc(amount_nodes, sizeof(char));

	for (i = 0; i < amount_nodes; i++) {
		parent[i]=-1;
		articulation_points[i]=0;
	}

	for (i = 0; i < amount_nodes; i++) {
		if (isVisited[i] == 0)
			apUtil(router_graph , i, isVisited, discovery_time, parent, low_time, articulation_points);
	}

	for (i = 0; i < amount_nodes; i++) {
		if (articulation_points[i]==1)
	  		counter++;
	}

	free(discovery_time);
	free(isVisited);
	free(parent);
	free(low_time);

	printf("%d\n", counter);

	return articulation_points;
}

void
find_subnetwork_info(graph_t router_graph)
{
	int i, amount_nodes = router_graph->num_nodes, counter = 0;
	list_t subnetworks = list_create(sizeof(struct subnetwork));
	char * visited = can_fail_calloc(amount_nodes, sizeof(char));
	queue_t * stack = queue_alloc(2);


	for (i = 0; i < amount_nodes; i++) {
		if (visited[i] != 0)
			continue;

		list_t new_subnetwork = list_create(sizeof(int));


		queue_push(stack, &i);


		while (!queue_isEmpty(stack)) {
			int current_node_idx = *(int*)queue_pop(stack);

			int * adjacencies = router_graph->nodes[current_node_idx].adjacencies;
			int j, length = router_graph->nodes[current_node_idx].amount;

			for (j = 0; j < length; j++) {
				int adjacency = adjacencies[j];
				adjacency--;

				if (visited[adjacency] != 0) {
					continue;
				}
			
				queue_push(stack, &router_graph->nodes[adjacency-1].id);
			}
	
			list_insert(new_subnetwork, &router_graph->nodes[current_node_idx].id);
			visited[current_node_idx] = 1;
		}

		subnetwork_t _subnetwork = create_subnetwork(list_getSize(new_subnetwork));
		list_node_t iter = NULL;
		list_iter_reset(new_subnetwork, &iter);
		int index = 0;
		while(list_iter_hasNext(&iter)) {
			int num = (*(int*)iter->data)+1;
			_subnetwork->subnetwork[index++] = num;
			list_iter_next(&iter);
		}
		list_free(new_subnetwork);
		list_insert(subnetworks, _subnetwork);
		counter++;
		queue_clear(stack);
	}

	free(visited);

	queue_free(stack);

	printf("%d\n", counter);

	list_node_t iter = NULL;
	list_iter_reset(subnetworks, &iter);
	int max = 0, _counter = 0;
	int * max_subnetwork = can_fail_malloc(sizeof(int) * list_getSize(subnetworks));
	unsigned j;
	while (list_iter_hasNext(&iter)) {
		subnetwork_t sn = (subnetwork_t)iter->data;
		max = 0;
		for (j = 0; j < sn->size; j++)
			if (sn->subnetwork[j] > max)
				max = sn->subnetwork[j];

		subnetwork_free(sn);
		max_subnetwork[_counter++] = max-1;
		list_iter_next(&iter);
	}

	list_node_t temp, aux = subnetworks->head;
	while (aux != NULL) {
		temp = aux->next;
		free(aux->data);
		free(aux);
		aux = temp;
	}
	free(subnetworks);
	

	qsort(max_subnetwork, counter, sizeof(int), compare_int);

	for (i = 0; i < counter-1; i++) {
		printf("%d ", max_subnetwork[i]);
	}
	printf("%d\n", max_subnetwork[counter-1]);

	free(max_subnetwork);

}


void
find_max_router(graph_t router_graph, char * articulation_points)
{

	int i, amount_nodes = router_graph->num_nodes, max = 0, counter = 0;
	char * visited = can_fail_calloc(amount_nodes, sizeof(char));
	queue_t * stack = queue_alloc(2);

	for (i = 0; i < amount_nodes; i++)
		if (articulation_points[i] != 0) {
			visited[i] = 1;
		}

	free(articulation_points);

	for (i = 0; i < amount_nodes; i++) {
		if (visited[i] != 0)
			continue;

		queue_push(stack, &i);

		counter = 0;

		while (!queue_isEmpty(stack)) {
			int current_node_idx = *(int*)queue_pop(stack);

			int * adjacencies = graph_get_adjacencies(router_graph, current_node_idx + 1);
			int length = router_graph->nodes[current_node_idx].amount;

			int j;
			for (j = 0; j < length; j++) {
				int adjacency = adjacencies[j];
				adjacency--;

				if (visited[adjacency] != 0)
					continue;

				queue_push(stack, &router_graph->nodes[adjacency-1].id);
			}

			if(visited[current_node_idx] != 0)
				continue;

			counter++;
			visited[current_node_idx] = 1;
		}

		if (counter > max)
			max = counter;
	}

	queue_free(stack);

	free(visited);

	printf("%d\n", max);

}


/* gcc -O3 -ansi -Wall -ggdb3 -o main main.c -lm */
/* valgrind --tool=massif ./main */
/* ms_print massif.out.pid */


int main()
{
	graph_t router_graph = get_input();

	find_subnetwork_info(router_graph);

	char * articulation_points = find_articulation_points(router_graph);

	find_max_router(router_graph, articulation_points);

	graph_destroy(router_graph);

	exit(0);
}
