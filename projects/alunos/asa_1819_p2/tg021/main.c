#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <signal.h>
#include <unistd.h>

int min(int a, int b) { return a > b ? b : a; }


int compare(const void * a, const void * b)
{
	/*
	if a.source == b.source:
		return a.target - b.target;
	else
		return a.source - b.source;
		*/
	(void)a;
	(void)b;
	return 0;
}



/*A utility function to get maximum value in arr[] */
int getMax(int arr[], int n) 
{ 
	int mx = arr[0], i; 
	for (i = 1; i < n; i++) 
		if (arr[i] > mx) 
			mx = arr[i]; 
	return mx; 
} 
  
/*A function to do counting sort of arr[] according to 
 the digit represented by exp. */
void countSort(int arr[], int n, int exp) 
{ 
	int output[n];
	int i, count[10] = {0}; 
  
	for (i = 0; i < n; i++) 
		count[ (arr[i]/exp)%10 ]++; 
  
	for (i = 1; i < 10; i++) 
		count[i] += count[i - 1]; 
  
	for (i = n - 1; i >= 0; i--) 
	{ 
		output[count[ (arr[i]/exp)%10 ] - 1] = arr[i]; 
		count[ (arr[i]/exp)%10 ]--; 
	} 
  
	for (i = 0; i < n; i++) 
		arr[i] = output[i]; 
} 
  
void radixsort(int arr[], int n) 
{ 
	int m = getMax(arr, n), exp; 
  
	for (exp = 1; m/exp > 0; exp *= 10) 
		countSort(arr, n, exp); 
} 


/* =============================================================================
 *
 * list.c
 *
 * =============================================================================
 */


#define ERR(str) { fprintf(stderr, "%s\n", str); exit(EXIT_FAILURE); }
#define test(str) { printf("%s\n", str); fflush(stdout); }

typedef struct list_node {
	void * data;
	struct list_node * next;
} * list_node_t;


typedef struct list {
	list_node_t head;
	list_node_t tail;
	long size;
	int data_size;
} * list_t;


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

long
list_getSize(list_t list)
{
	return list->size;
}

void
list_iter_reset(list_t list, list_node_t * node)
{
	*node = list->head;
}

int
list_iter_hasNext(list_node_t * node)
{
	return (*node != NULL) ? 1 : 0;
}

void
list_iter_next(list_node_t * node)
{
	if (node != NULL)
		*node = (*node)->next;
}

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

void
list_push(list_t list, void * data)
{
	list_insert_start(list, data);
}

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

void
list_insert_end(list_t list, void * data)
{
	list_insert(list, data);
}

void
list_insert_at(list_t list, void * data, long index)
{
	long i = 1, size = list_getSize(list);

	if (index > size) {
		printf("Index exceeds list size.\n");
		return;
	}

	if (index == 0)
		list_insert_start(list, data);
	else if (index == size)
		list_insert_end(list, data);
	else {
		list_node_t new = list_node_create(data, list->data_size);
		list_node_t temp = list->head->next, prev = list->head;

		while (i != index) {
			list_iter_next(&temp);
			list_iter_next(&prev);
			i++;
		}

		prev->next = new;
		new->next = temp;

		list->size++;
	}
}

void *
list_at(list_t list, long index)
{
	long i = 0, size = list_getSize(list);

	if (index > size - 1) {
		printf("Index exceeds list size.\n");
		return NULL;
	}

	list_node_t temp = NULL;
	list_iter_reset(list, &temp);
	while (i != index) {
		list_iter_next(&temp);
		i++;
	}

	void * egg = temp->data;

	(void)egg;

	return temp->data;
}

/*
static void
list_node_free(list_node_t * node)
{
	if (*node != NULL)  
		list_node_free(&(*node)->next);

	if (*node) {
		if ((*node)->data)
			free((*node)->data);
		free(*node);
	}
} */

void
list_remove_start(list_t list)
{
	list_node_t head = list->head;
	list->head = head->next;
	free(head);
	list->size--;
}

void
list_remove_end(list_t list)
{
	list_node_t temp, prev = NULL;
	temp = list->head;

	while (list_iter_hasNext(&temp->next)) {
		prev = temp;
		temp = temp->next;
	}

	free(temp);

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

void
list_pop(list_t list)
{
	list_remove_end(list);
}

void
list_remove(list_t list, void * data)
{
	list_node_t head = list->head;
	list_node_t tail = list->tail;
	int found = 0;

	if (list->size == 0) {
		printf("Could not remove: list is empty.\n");
		return;
	}

	if (head->data == data) {
		found = 1;
		list_remove_start(list);
	} else if (tail->data == data) {
		found = 1;
		list_remove_end(list);
	} else {
		list_node_t temp = list->head->next, prev = list->head;

		while (list_iter_hasNext(&temp)) {
			if (temp->data == data) {
				prev->next = temp->next;
				free(temp);
				found = 1;
				list->size--;
				break;
			}
			temp = temp->next;
			prev = prev->next;
		}
	}

	if (!found)
		printf("Could not remove: data was not found in list.\n");
}

void
list_remove_at(list_t list, long index)
{
	long i = 0, size = list_getSize(list);

	if (index > size - 1) {
		printf("Index exceeds list size.\n");
		return;
	}

	if (index == 0)
		list_remove_start(list);
	else if (index == size - 1)
		list_remove_end(list);
	else {
		list_node_t temp = list->head->next, prev = list->head;
		i++;
		while (i != index) {
			list_iter_next(&temp);
			list_iter_next(&prev);
			i++;
		}

		prev->next = temp->next;

		free(temp);

		list->size--;
	}
}

int
list_isEmpty(list_t list)
{
	return !list->size;
}

void
list_free(list_t list)
{
	list_node_t current;
  	while(list->head != NULL) {
		current = list->head;
		list->head = current->next;

		free(current->data);
		free(current);
	}

	free(list);
}

/* ============================ END OF LIST.C ============================ */

typedef unsigned long ulong_t;

enum {
	FALSE = 0,
	TRUE  = 1
};

typedef long bool_t;

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
		queuePtr->pop	  = capacity - 1;
		queuePtr->push	 = 0;
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
	long pop	  = queuePtr->pop;
	long push	 = queuePtr->push;
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
	long pop	  = queuePtr->pop;
	long push	 = queuePtr->push;
	long capacity = queuePtr->capacity;

	assert(pop != push);

	/* Need to resize */
	long newPush = (push + 1) % capacity;
	if (newPush == pop) {

		long newCapacity = capacity * QUEUE_GROWTH_FACTOR;
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
		queuePtr->pop	  = newCapacity - 1;
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
	long pop	  = queuePtr->pop;
	long push	 = queuePtr->push;
	long capacity = queuePtr->capacity;

	long newPop = (pop + 1) % capacity;
	if (newPop == push) {
		return NULL;
	}

	void* dataPtr = queuePtr->elements[newPop];
	queuePtr->pop = newPop;

	return dataPtr;
}

/* ============================ END OF QUEUE.C ============================

 gcc -Wall -Wextra -ggdb3 -o main main.c
 valgrind -v --leak-check=full --show-leak-kinds=all --track-origins=yes ./main */


typedef struct edge {
	int target_id;
	int capacity;
	int flow;
} edge_t;

typedef struct node {
	int excess;
	int height;
	int current;
	int id;
	edge_t * adj;
} node_t;

typedef struct queueItem {
	int id;
	int type; 
} queueItem_t;

node_t * stations_in;
node_t * stations_out;
node_t * producers;

int num_suppliers = 0;
int num_stations = 0;
int num_edges = 0;

int total_production;

int * amount_edges;

list_t queue;

typedef struct connection {
    int origin_id;
    int target_id;
} connection_t;

/*
void
find_chicken_nuggets()
{
    queue_t * stack = queue_alloc(-1);
    char * discovered = can_fail_calloc(num_suppliers + num_stations + 20, sizeof(char));
    int amount_neighbours, i;

    queue_push(stack, producers[0]);

    while (!queue_isEmpty(stack)) {
        node_t v = (node_t)queue_pop(stack);

        amount_neighbours = amount_edges[v.id];
        for (i = 0; i < amount_neighbours; i++) {
            if ()
        }
    }

    // get the hombres

    free(discovered);
}
*/

void
add_edge(int source_id, int target_id, int capacity)
{
	node_t source;
	int num_edges;

	if (source_id == target_id) {
		source = stations_in[source_id-num_suppliers-2];
		if (!source.adj)
			source.adj = can_fail_calloc(1, sizeof(edge_t));
		source.adj[0].target_id = target_id;
		source.adj[0].capacity += capacity;		
		stations_in[source_id-num_suppliers-2] = source;
		return;
	}

	if (source_id > num_suppliers + 1)
		source = stations_out[source_id-num_suppliers-2];
	else
		source = producers[source_id];

	num_edges = amount_edges[source_id];

	if (num_edges != 0) {
		source.adj = can_fail_realloc(source.adj, (num_edges+1) * sizeof(edge_t));
	} else {
		edge_t * mcnubbwe = can_fail_calloc(1, sizeof(edge_t));
		source.adj = mcnubbwe;
		source.id = source_id;
	}

	source.adj[num_edges].target_id = target_id;
	source.adj[num_edges].capacity += capacity;
	amount_edges[source_id]++;

	if (source_id > num_suppliers + 1)
		stations_out[source_id-num_suppliers-2] = source;
	else
		producers[source_id] = source;
		
	if (source_id == 0)
		producers[0].excess += capacity;
}


void
get_input()
{
	int i = 0;
	char buffer[10000];
	char * token;
	const char * delim = " \n";
	queue = list_create(sizeof(node_t));

	if (scanf("%d %d %d\n", &num_suppliers, &num_stations, &num_edges) == 3);

	amount_edges = can_fail_calloc(num_suppliers + num_stations + 20, sizeof(int));
	stations_in = can_fail_calloc(num_stations, sizeof(node_t));
	stations_out = can_fail_calloc(num_stations, sizeof(node_t));
	producers = can_fail_calloc(num_suppliers+2, sizeof(node_t));

	if (fgets(buffer, 9999, stdin) != NULL);
	token = strtok(buffer, delim);
	i = 2;
	while (token != NULL) {
		add_edge(0, i, atoi(token));
		i++;
		token = strtok(NULL, delim);
	}

	i = num_suppliers+2;
	if (fgets(buffer, 9999, stdin) != NULL);
	token = strtok(buffer, delim);
	while (token != NULL) {
		add_edge(i, i, atoi(token));
		i++;
		token = strtok(NULL, delim);
	}

	for (i = 0; i < num_edges; i++) {
		int origin_id, target_id, capacity;
		if(scanf("%d %d %d", &origin_id, &target_id, &capacity) == 3);

		add_edge(origin_id, target_id, capacity);
		add_edge(target_id, origin_id, capacity);
	}

	producers[0].height = num_suppliers + num_stations;

	list_insert(queue, &producers[0]);

}

void
push(node_t * u, node_t * v, int u_edge_id, int v_edge_id)
{
	int current_flow = u->adj[u_edge_id].capacity - u->adj[u_edge_id].flow;
	int residual_flow = min(u->excess, current_flow);
	
	if (residual_flow)
		u->adj[u_edge_id].flow += residual_flow;
	else
		v->adj[v_edge_id].flow += residual_flow;

	u->excess -= residual_flow;
	v->excess += residual_flow;

	if (v->id < num_suppliers + 2) {
		list_insert_end(queue, &producers[v->id]);
	}
	else if(u->id == v->id)
		list_insert_end(queue, &stations_out[v->id-num_suppliers-2]);
	else
		list_insert_end(queue, &stations_in[v->id-num_suppliers-2]);
	
}

void
relabel(node_t * u) { u->height += 1; }

void
discharge(node_t * u)
{
	int counter = 0;
	while(u->excess != 0) {
		int v = u->current;
		node_t * vertex = can_fail_malloc(sizeof(struct node));
		if(v) {
			if (v < num_suppliers + 2) {
				vertex = &producers[v];
			}
			else if(u->id == v)
				vertex = &stations_out[v-num_suppliers-2];
			else
				vertex = &stations_in[v-num_suppliers-2];
				
		}
		int current_flow = 0, j = 0;
		int size = amount_edges[u->id], i = 0;
		for (; i < size; i++) {
			if (u->adj[i].target_id == vertex->id) {
				current_flow = u->adj[i].capacity - u->adj[i].flow;
				if (current_flow > 0) {
					break;
				}
			}
		}
		if(!v) {
			relabel(u);
			u->current = u->adj[counter++].target_id;
		}
		else if(u->height > vertex->height && current_flow > 0) {
			for (; j < size; j++)
				if (vertex->adj[j].target_id == u->id)
					break;		
			push(u, vertex, i, j);
	
		}		
		else {
			u->current = u->adj[counter++].target_id;
		}
	}
}


void
relabel_to_front()
{
	int counter  = 0, old_h;
	while(!list_isEmpty(queue) && counter < list_getSize(queue)) {
		fflush(stdout);
		node_t * vertex = list_at(queue, counter);
		old_h = vertex->height;
		
		discharge(vertex);
		if (old_h > vertex->height) {
			counter = 1;
			list_remove(queue, vertex);
			list_insert_start(queue, vertex);
		}
		else {
			list_remove(queue, vertex);
			counter++;
		}

	}
}




int
main()
{
	int i;

	get_input();
	relabel_to_front();

	/*
	 print le graph
	for (i = 0; i < num_suppliers; i++)
		printf("Producer %d produces %d\n", i + 1, producers[0].adj[i].target_id);

	for (i = 0; i < num_stations; i++)
		printf("Station %d with capacity %d\n", num_suppliers + i + 1, stations_in[i].adj[0].capacity);

	*/
	free(amount_edges);

	for (i = 0; i < num_stations; i++) {
		free(stations_in[i].adj);
	}
	free(stations_in);

	for (i = 0; i < num_stations; i++) {
		free(stations_out[i].adj);
	}
	free(stations_out);

	for (i = 0; i < num_suppliers+2; i++) {
		free(producers[i].adj);
	}
	free(producers);

	exit(0);
}
