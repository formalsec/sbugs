/* ************************************************************************/
/* *********** Analise e Sintese de Algoritmos - Projeto 2*****************/
/* ************************************************************************/
/* ***************************** Grupo 4 **********************************/
/* ************************************************************************/
/* ********************** 70566 Ricardo Carreira **************************/
/* ********************** 65951 Tiago Fernandes****************************/
/* ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>


/* Structs */

/* lst_iitem_arch - each element of the list points to the next element */
typedef struct lst_iitem_arch {
   int source;
   int destination;
   int capacity;
   int flow;
   struct lst_iitem_arch *reverse;
   struct lst_iitem_arch *next;
} lst_iitem_edge;

/* list_edge */
typedef struct {
   lst_iitem_edge * first;
} list_edge;

/* lst_iitem_node - each node has a list of edges */
typedef struct lst_iitem_node{
	int id;
	int numLinks;
	int inCut;
	int visited;
	list_edge *edges;
} node;

/* stack_n - queue for nodes */
typedef struct stack_s {
    int top;
    int size;
    int *items;
} stack;

/*---------------------------------------------*/

/* Function Declarations */
node* readInput(node *graph, list_edge *edgeList, int* edges, int* links, int* suppliers, int* processors, int* firstPostId, int* originalNodes, int* totalNodes);
lst_iitem_edge* createEdge(int source, int destination, int capacity);
void printEdge(lst_iitem_edge *edge);
list_edge* lst_new();
void lst_print(list_edge *list);
void insert_new_edge(node* graph, int source, int destination, int capacity);
int min(int a, int b);
void edmondsKarp(node* nodes, int totalNodes);
void stack_push(int v, stack* s);
int stack_pop(stack* s);
stack* createStack(int size);
void deleteStack(stack* s);
void add_to_list(list_edge *list, lst_iitem_edge *item);
node* findMinCut(node* nodes, int totalNodes);
void printAugments(node* nodes, int totalNodes, int processors, int suppliers,  int originalNodes);
int isPostLink(int source, int destination, int totalNodes, int originalNodes, int suppliers, int processors);
void bubbleSort(list_edge *edgeList);
void swap(lst_iitem_edge *a, lst_iitem_edge *b);




/* Main */
int main(int argc, const char* argv[]){
	/* Variable Declaration */
	int edges, links, suppliers, processors;
	int firstPostId;
	int originalNodes, totalNodes;
	node* nodes;
	list_edge *edgeList;
	
	/* Variable Initialization */
	edges = links = suppliers = processors = 0;
	originalNodes = totalNodes = 0;
	firstPostId = 0;
	nodes=NULL;
	edgeList = lst_new();
	/*------------------------------*/
	nodes = readInput(nodes, edgeList, &edges, &links, &suppliers, &processors, &firstPostId, &originalNodes, &totalNodes);		

	
	edmondsKarp(nodes, totalNodes);
	
	nodes = findMinCut(nodes, totalNodes);
	
	printAugments(nodes, totalNodes, processors, suppliers, originalNodes);

	return 0;
}


node* readInput(node *graph, list_edge *edgeList, int* edges, int* link, int* suppliers, int* processors, int* firstPostId, int* originalNodes, int* totalNodes) {
	int count, source, destination, src, dst, capacity, firstPostAux;
	if(scanf("%d %d %d", suppliers, processors, link) == 0)
		fprintf(stderr, "Error reading input\n");
	*firstPostId=*suppliers + 2;
	*originalNodes = 1 + *suppliers + *processors;	/* Add 1 for hiper and one for each supplier and processing post */
	*totalNodes = *originalNodes + *processors + 1; /* Add 1 for source and one for each processing post */
	firstPostAux = *originalNodes + 1;
	graph = (node*) malloc(sizeof(node)*(*totalNodes));
	
	for(count=0;count<*totalNodes;count++){
		graph[count].id = count+1;
		graph[count].numLinks = 0;
		graph[count].inCut = 0;
		graph[count].edges = lst_new();
	}
	for(count=0;count<*suppliers; count++){
		source = 2+count;	/* first supplier is always #2 */
		destination = *totalNodes; /* all suppliers connect to last node aka virtual sink */
		if(scanf("%d", &capacity) == 0)
			fprintf(stderr, "Error reading input\n");
		insert_new_edge(graph, source, destination, capacity);
		
	}
	getchar();
	for(count=0;count<*processors;count++){
		source = firstPostAux+count;	/* first processing post created */
		destination = *firstPostId+count; /*first processing post id */
		if(scanf("%d", &capacity) == 0)
			fprintf(stderr, "Error reading input\n");
		insert_new_edge(graph, source, destination,  capacity);
	}
	for(count=0;count<*link;count++){
		if(scanf("%d %d %d", &src, &dst, &capacity) == 0)
			fprintf(stderr, "Error reading input\n");
		source = dst;
		destination = src;
		if(src>=*firstPostId){
			destination = src+(*originalNodes-*firstPostId)+1;
			insert_new_edge(graph, source, destination, capacity);
		} else {
			insert_new_edge(graph, source, destination, capacity);
		}
	}
	return graph;
}

lst_iitem_edge* createEdge(int source, int destination, int capacity) {
	lst_iitem_edge* newEdge;
	newEdge = (lst_iitem_edge*) malloc(sizeof(lst_iitem_edge));
	newEdge->source = source;
	newEdge->destination = destination;
	newEdge->capacity = capacity;
	newEdge->flow = 0;
	newEdge->reverse = (lst_iitem_edge*) malloc(sizeof(lst_iitem_edge));
	newEdge->reverse->source = destination;
	newEdge->reverse->destination = source;
	newEdge->reverse->capacity = 0;
	newEdge->reverse->reverse = newEdge;
	newEdge->reverse->next = NULL;
	newEdge->next = NULL;
	return newEdge;
}

void printEdge(lst_iitem_edge *edge) {
	int source, destination;
	source = edge->source+1;
	destination = edge->destination+1;
	printf("%d %d\n", source, destination);
	return;
}

void edmondsKarp(node* nodes, int totalNodes) {
	/* Parent array used for storing path */
	/* (parent[i] stores edge position in array used to get to node i) */
	int source = 0;
	int sink = totalNodes-1;
	int dest;
	int count, pushFlow, maxFlow, curr;
	lst_iitem_edge *edge;
	stack *queue;
	lst_iitem_edge **parents;
	
	parents=(lst_iitem_edge**)malloc(sizeof(lst_iitem_edge*)*totalNodes);
	maxFlow = 0;
	curr = -1;
	
	while (1){
		for(count=0;count<totalNodes;count++){
			parents[count]=NULL;
		}
		
		queue = createStack(totalNodes);
		stack_push(source, queue);
		
		/* BFS finding shortest augmenting path */
		while (queue->top != -1){
			curr = stack_pop(queue);
			/* Checks that edge has not yet been visited, and it doesn't */
			/* point to the source, and it is possible to send flow through it. */
			edge = nodes[curr].edges->first;
			for (count=0;count<nodes[curr].numLinks;count++){
				dest = edge->destination;
				if (parents[dest] == NULL && dest != source && edge->capacity > edge->flow) {
					parents[dest] = edge;
					stack_push(dest, queue);
				}
				edge=edge->next;
			}
		}
			
		/* If sink was NOT reached, no augmenting path was found. */
		/* Algorithm terminates and prints out max flow. */
		if (parents[sink] == NULL)
			break;
		
		/* If sink WAS reached, we will push more flow through the path */
		pushFlow = INT_MAX;
		
		/* Finds maximum flow that can be pushed through given path */
		/* by finding the minimum residual flow of every edge in the path */
		edge = parents[sink];
		while (edge != NULL) {
			pushFlow = min(pushFlow , edge->capacity - edge->flow);
			edge = parents[edge->source];
		}
		
		/* Adds to flow values and subtracts from reverse flow values in path */
		edge = parents[sink];
		while (edge != NULL) {
			edge->flow += pushFlow;
			edge->reverse->flow -= pushFlow;
			edge = parents[edge->source];
		}
		
		maxFlow += pushFlow;
		deleteStack(queue);
	}

	printf("%d\n",maxFlow);
}

int min(int a, int b) {
	return a<b?a:b;
}

node* findMinCut(node* nodes, int totalNodes) {
	int count, curr, source, dest;
	stack *queue;
	lst_iitem_edge *edge;
	
	queue = createStack(totalNodes+1);
	
	source = 0;
	curr = -1;
	
	stack_push(source, queue);
	nodes[source].inCut = 1;
	/* BFS finding shortest augmenting path */
	while (queue->top != -1){
		curr = stack_pop(queue);
		
		/* Checks that edge has not yet been visited, and it doesn't */
		/* point to the source, and it is possible to send flow through it. */
		edge = nodes[curr].edges->first;
		for (count=0;count<nodes[curr].numLinks;count++){
			dest = edge->destination;
			if (dest != source && ((edge->capacity)-(edge->flow)) > 0 && nodes[dest].visited==0 && (edge->flow >= 0||edge->reverse->flow != 0)) {
				nodes[dest].inCut = 1;
				nodes[dest].visited = 1;
				stack_push(dest, queue);
			}
			edge=edge->next;
		}
	}
	return nodes;
}


void printAugments(node* nodes, int totalNodes, int processors, int suppliers, int originalNodes) {
	lst_iitem_edge *item;
	stack *postsToAugment;
	list_edge *edgeList;
	int count, isPost, sourcePos, destinationPos;
	
	
	postsToAugment = createStack(suppliers+1);
	edgeList = lst_new();
	
	for(count=totalNodes-1;count>=0;count--){
		item = nodes[count].edges->first;
		while (item != NULL){
			if(nodes[item->source].inCut != nodes[item->destination].inCut && item->destination != count && item->capacity > 0 && item->capacity-item->flow == 0){
				/*add edge to augment list */
				sourcePos = item->destination;
				destinationPos = item->source;
				isPost = isPostLink(sourcePos, destinationPos, totalNodes, originalNodes, suppliers, processors);
				if(sourcePos+1!=totalNodes && destinationPos+1!=totalNodes){
					if(isPost == 1){
						stack_push(sourcePos+1, postsToAugment);
						item = item->next;
						isPost=0;
						continue;
					}
					if(isPost == -1){
						stack_push(destinationPos+1, postsToAugment);
						item = item->next;
						isPost=0;
						continue;
					}		
					if(sourcePos >= originalNodes && sourcePos+1 != totalNodes){
						add_to_list(edgeList, createEdge(sourcePos-processors, destinationPos,0));
						item = item->next;
						continue;
					}					
					if(destinationPos >= originalNodes && destinationPos+1 != totalNodes) {
						add_to_list(edgeList, createEdge(sourcePos, destinationPos-processors,0));
						item = item->next;
						continue;
					}
					add_to_list(edgeList, createEdge(sourcePos, destinationPos,0));
				}
			}
			item = item->next;
		}
	}
	
	if(postsToAugment->top > 0){
		printf("%d", stack_pop(postsToAugment));
		while(postsToAugment->top > 0){
			printf(" %d", stack_pop(postsToAugment));
		}
		printf(" %d", stack_pop(postsToAugment));	
	}
	if(postsToAugment->top==0){
		printf("%d", stack_pop(postsToAugment));
	}
		
	printf("\n");
	deleteStack(postsToAugment);
	bubbleSort(edgeList);
	lst_print(edgeList);
}


/* Bubble sort the given linked list */
void bubbleSort(list_edge *edgeList) { 
    int swapped; 
    lst_iitem_edge *start = edgeList->first;
    lst_iitem_edge  *ptr1; 
    lst_iitem_edge *lptr = NULL; 
  
    /* Checking for empty list */
    if (start == NULL) {
        return; 
	}
  
    do { 
        swapped = 0; 
        ptr1 = start; 
  
        while (ptr1->next != lptr) { 
            if (ptr1->source > ptr1->next->source || 
				((ptr1->source == ptr1->next->source) && (ptr1->destination > ptr1->next->destination))) {  
                swap(ptr1, ptr1->next); 
                swapped = 1; 
            } 
            ptr1 = ptr1->next; 
        } 
        lptr = ptr1; 
    } while (swapped); 
} 

/* function to swap data of two nodes a and b*/
void swap(lst_iitem_edge *a, lst_iitem_edge *b) { 
    int sourceAux, destinationAux;
    sourceAux = a->source;
    destinationAux = a->destination;
    a->source = b->source; 
    a->destination = b->destination; 
    b->source = sourceAux;
    b->destination = destinationAux;
    
} 

int isPostLink(int source, int destination, int totalNodes, int originalNodes, int suppliers, int processors){
	if(source==0||destination==0||source+1==totalNodes||destination+1==totalNodes){
		return 0;
	} else {
		if(source <= originalNodes && destination == source+processors && source>=suppliers){
			return 1;
		}
		if(destination <= originalNodes && source == destination+processors && destination>=suppliers){
			return -1;
		}
	}
	return 0;
}

list_edge* lst_new() {
	list_edge *list;
	list = (list_edge*) malloc(sizeof(list_edge));
	list->first = NULL;
	return list;
}

void lst_destroy(list_edge *list) {
  struct lst_iitem_arch *item, *nextitem;

  item = list->first;
  while (item != NULL){
    nextitem = item->next;
    free(item);
    item = nextitem;
  }
  free(list);
}

void lst_print(list_edge *list) {
	lst_iitem_edge *item;

	item = list->first;
	while (item != NULL){
		printEdge(item);
		item = item->next;
	}
}

void insert_new_edge(node* graph, int source, int destination, int capacity) {
	lst_iitem_edge *item;
	item = createEdge(source-1, destination-1, capacity);
	add_to_list(graph[source-1].edges, item);
	add_to_list(graph[destination-1].edges, item->reverse);
	graph[source-1].numLinks++;
	graph[destination-1].numLinks++;
}

void add_to_list(list_edge *list, lst_iitem_edge *item) {
	if(list->first != NULL){
		item->next = list->first;
	}
	list->first = item;
}

void stack_push(int v, stack* s) {
    s->top++;
    if (s->top < s->size)
		s->items[s->top] = v;
    else {
		printf("Stack is full!\n");
		exit(1);
    }
}

int stack_pop(stack* s) {
    return s->top < 0 ? -1 : s->items[s->top--];
}

stack* createStack(int size) {
	stack* s;
	s=(stack *) malloc(sizeof(stack));
	s->top=-1;
	s->size=size;
	s->items=(int*) malloc(sizeof(int)*size);
	return s;
}

void deleteStack(stack* s) {
	free(s->items);
	free(s);
}


