#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Goncalo Correia 83897 grupo al146*/

typedef struct {
	int npais;
	int* pais;
} Node;

typedef struct {
	int npais;
	int* pais;
	int depth;

} NodeButCooler;

struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};

void graph_builder(int first, int second);
void init_graph();
void khan(struct Queue* s, int l[]);
void longest_path(int l[]);
 
struct Queue* createQueue(unsigned capacity)
{
    struct Queue* queue = (struct Queue*)can_fail_malloc(
        sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
 
   
    queue->rear = capacity - 1;
    queue->array = (int*)can_fail_malloc(
        queue->capacity * sizeof(int));
    return queue;
}
 
int isEmpty(struct Queue* queue)
{
    return (queue->size == 0);
}
 

void enqueue(struct Queue* queue, int item)
{
    queue->rear = (queue->rear + 1)
                  % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
  
}
 

int dequeue(struct Queue* queue)
{
    if (isEmpty(queue))
        return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1)
                   % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

Node* graph;
NodeButCooler* graph2;
int nodes = 1;
int edges = 1;

int main() {

	int i;
	/*int j;*/
	int pai;
	int filho;

	scanf("%d %d", &nodes, &edges);
	nodes++;
	/*printf("%d", nodes);*/

	struct Queue* s = createQueue(nodes);
	/*struct Queue* s2 = createQueue(nodes);*/

	graph = can_fail_malloc(sizeof(Node)*nodes);
	graph2 = can_fail_malloc(sizeof(NodeButCooler)*nodes);

	init_graph();

	for(i = 0; i < edges; i++) {
		scanf("%d %d", &pai, &filho);
		graph_builder(pai, filho);
	}

	int l[nodes-1]; /*ordem topologica*/

	for(i=0; i<nodes; i++) {
		l[i] = 0;
	}


	for(i=1; i< nodes; i++) {
		/*printf("%d tem %d pais\n", i, graph[i].npais);*/
		if(graph[i].npais==0)
			enqueue(s, i);
		/*for(j=0; j < graph[i].npais; j++)
			//printf("%d ", graph[i].pais[j]);
		printf("\n");*/
	}

	/*while(!isEmpty(s)) {

		printf("%d dequeued from queue \n\n", dequeue(s));
	}*/

	int out1 = s->size;
	printf("%d ", out1);

	/*memcpy(graph2, graph, sizeof(*graph2));*/

	khan(s,l);

	free(graph);

	/*for(i=1; i< nodes; i++) {
		printf("%d tem %d pais\n", i, graph2[i].npais);
		if(graph2[i].npais==0)
			enqueue(s2, i);
		for(j=0; j < graph2[i].npais; j++)
			printf("%d ", graph2[i].pais[j]);
		printf("\n");
	}*/

	longest_path(l);

	free(graph2);

	return 0;
}

void init_graph() {
	int i;

	for (i=1; i<nodes; i++) {
		graph[i].npais = 0;
		graph[i].pais = NULL;
		graph2[i].npais = 0;
		graph2[i].pais = NULL;
		graph2[i].depth = 1;
	}
}

void graph_builder(int pai, int filho) {
	
	if(graph[filho].npais == 0){
		graph[filho].npais = 1;
		graph[filho].pais = can_fail_malloc(sizeof(int));
		graph[filho].pais[0] = pai;
		graph2[filho].npais = 1;
		graph2[filho].pais = can_fail_malloc(sizeof(int));
		graph2[filho].pais[0] = pai;
	}
	else {
		graph[filho].npais++;
		graph2[filho].npais++;
		int*carry = can_fail_malloc(sizeof(int)*graph[filho].npais);
		int*carry2 = can_fail_malloc(sizeof(int)*graph2[filho].npais);
		int i;
		
		for (i=0; i<(graph[filho].npais-1); i++){
			carry[i] = graph[filho].pais[i];
			carry2[i] = graph2[filho].pais[i];
		}

		carry[graph[filho].npais-1] = pai;
		graph[filho].pais = carry;
		carry2[graph2[filho].npais-1] = pai;
		graph2[filho].pais = carry2;

	}
}

void khan(struct Queue* s, int l[]) {

	int i, j;
	int x=0;

	while(!isEmpty(s)) {
		
		int n = dequeue(s);
		/*printf("%d bazou\n", n);*/
		l[x] = n;
		x++;

		for(i=1; i<nodes; i++) {
			for(j=0; j<graph[i].npais; j++) {
				while(graph[i].pais[j] == 0) {
					j++;
				}
				if(graph[i].pais[j] == n) {
					graph[i].pais[j] = 0;
					graph[i].npais--;
					if(graph[i].npais == 0)
						enqueue(s, i);
				}

			}
		}
	}

	/*for(i=0; i<nodes-1; i++) {
		printf("%d ", l[i]);
	}
	printf("\n");*/
}

void longest_path(int l[]) {
	
	int i;
	int j;
	int max = 0;

	for(i=0; i<nodes-1; i++) {
		/*printf("%d ", l[i]);*/
		
		int bestpai = 0;

		for(j=0; j<graph2[l[i]].npais; j++) {
			int pai = graph2[l[i]].pais[j];
			if(bestpai == 0)
				bestpai = pai;
			if(graph2[pai].depth > graph2[bestpai].depth)
				bestpai = pai;
		}

		graph2[l[i]].depth = graph2[bestpai].depth + 1;
		if(graph2[l[i]].depth > max)
			max = graph2[l[i]].depth;
	}

	printf("%d\n", max);
}
