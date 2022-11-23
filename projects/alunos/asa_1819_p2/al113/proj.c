#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/*
Analise e Sintese de Algoritmos
Proj 2

Sofia Carvalho ist189539
Miguel Gonçalves ist189507
*/


#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) a < b ? a : b
#define REAL(i, s) i < s+2 ? i : (((i-s-2)/2)+s+2) /* real vertice index (not counting 2 vertices p station) */
#define REP(r, s) r < s+2 ? r : (((r-s-2)*2)+s+2) /* represented vertice index (counting 2 vertices p station) */
#define ADJ(v) g->vertices[v]
#define DESTIN(k) k->destination
#define CAP(k) k->cap
#define FLOW(k) k->flow
#define MAIN(k) k->main


/* LINKED LISTS ASSETS */

typedef struct node {
	int destination;
	int cap;
	int flow;
	int main; /* graph the edge belongs to (1 - main, 0 - residual) */
	struct node* rev; /* corresponding edge on the opposite graph */
	struct node* next;
}* Link;

typedef struct list {
	Link head;
}* List;

List init_list() {
	List l = (List) can_fail_malloc(sizeof(struct list));
	l->head = NULL;
	return l;
}

void insert_list(List l, int d, int c, int m, Link r) {
	Link new = (Link) can_fail_malloc(sizeof(struct node));
	new->destination = d;
	new->cap = c;
	new->flow = 0;
	new->main = m;
	new->rev = r;
	new->next = l->head;
	l->head = new;
}

void clear_list(List l) {
	Link x = l->head, aux;
	while (x != NULL) {
		aux = x;
		x = aux->next;
		free(aux);
	}
	l->head=NULL;
}

/* END OF LINKED LISTS ASSETS */

/* QUEUE ASSETS */

typedef struct Qnode {
	int key;
	struct Qnode *next;
}* QNode;

typedef struct queue {
	QNode front, rear;
}* Queue;


QNode newNode(int k) { 
	QNode new = (QNode) can_fail_malloc(sizeof(struct Qnode));
	new->key = k;
	new->next = NULL;
	return new;
}

Queue init_queue() {
	Queue q = (Queue) can_fail_malloc(sizeof(struct queue));
	q->front = q->rear = NULL;
	return q;
}

void enQueue(Queue q, int k) {
	QNode temp = newNode(k);

	if (q->rear == NULL) {
	   q->front = q->rear = temp;
	   return;
	}

	q->rear->next = temp;
	q->rear = temp;
}

int deQueue(Queue q) {
	QNode temp = q->front;
	q->front = q->front->next;

	if (q->front == NULL)
	   q->rear = NULL;

	int key = temp->key;
	free(temp);

	return key;
}

int queue_empty(Queue q) {
	return (q->front == NULL)? 1 : 0;
}

/* END OF QUEUE ASSETS */

/* GRAPH ASSETS */

typedef struct graph {
	int numVertices;
	int numSuppliers;
	List* vertices;
}* Graph;


Graph init_graph() {
	Graph g = (Graph) can_fail_malloc(sizeof(struct graph));
	g->numVertices = 0;
	g->numSuppliers = 0;
	g->vertices = NULL;
	return g;
}

void free_graph(Graph g) {
	int i;
	for (i=0; i < g->numVertices; i++) {
		if (g->vertices[i] != NULL)
			clear_list(g->vertices[i]);
		free(g->vertices[i]);
	}
	free(g->vertices);
	free(g);
}

/* END OF GRAPH ASSETS */



/* FUNCTIONS DECLARATION */

/*
push: function to push flow from a vertice to another
Arguments: an array with the vertices' excess, the involved vertices and the max flow that is allowed
Return: the amount of flow that was pushed
*/
int push(int* e, int u, int v, int curr_f) {
	int flow = MIN(e[u], curr_f);
	e[u] -= flow;
	e[v] += flow;
	return flow;
}

/*
relabel: function to increase the height of a vertice
Arguments: a struct graph representing a graph, an array with the vertices' heights and the current vertice
Return: nothing
*/
void relabel(Graph g, int* h, int u) {
	Link k;
	int min = -1;
	for (k = ADJ(u)->head; k != NULL; k = k->next) {
		if (CAP(k) - FLOW(k) <= 0) continue;
		min = (min == -1) ? h[DESTIN(k)] : MIN(min, h[DESTIN(k)]); /* finds the lowest adjacent vertice that can receive flow */
	}
	h[u] = min + 1;
}

/*
discharge: function to push the vertice's excess to its adjacent vertices
Arguments: a struct graph representing a graph, a struct queue to store the vertices with excess, an array with the vertices' excess
and one with their heights and the current vertice
Return: nothing
*/
void discharge(Graph g, Queue q, int* e, int* h, int u) {
	int curr_f, prev_e;
	Link k;
	for (k = ADJ(u)->head; k != NULL && e[u] != 0; k = k->next) {
		if ((curr_f = CAP(k) - FLOW(k)) > 0 && h[u] > h[DESTIN(k)]) { /* if 'u' can push to the adjacent vertice */
			prev_e = e[DESTIN(k)];
			curr_f = push(e, u, DESTIN(k), curr_f);
			FLOW(k) += curr_f;
			FLOW(k->rev) = -(FLOW(k));
			if (prev_e == 0 && DESTIN(k) != 1) enQueue(q, DESTIN(k));
		}
	}

	if (e[u] != 0) { /* if 'u' still has excess, it is relabeled and enqueued again */
		relabel(g, h, u);
		enQueue(q, u);
	}
}

/*
push relable: function to determine the max amount of flow that can go through a weighted directed graph
Arguments: a struct graph representing a graph
Return: the maximum flow of the graph
*/
int pushRelabel(Graph g) {
	int i, flow;
	Link k;
	int* e = (int*) can_fail_malloc(sizeof(int)*(g->numVertices)); /* vertices' excess */
	int* h = (int*) can_fail_malloc(sizeof(int)*(g->numVertices)); /* vertices' heights */
	Queue q = init_queue();  /* stores the vertices that have (positive) excess */

	/* INITIALIZATION */
	for (i = 0; i < g->numVertices; i++) {
		h[i] = 0;
		e[i] = 0;
	}
	
	h[0] = g->numVertices;
	
	for (k = ADJ(0)->head; k != NULL; k = k->next) { /* pushes flow to the source's adjacent vertices */
		if (MAIN(k) != 0) {
			FLOW(k) = CAP(k);
			FLOW(k->rev) = -CAP(k);
			e[DESTIN(k)] = CAP(k);
			e[0] -= CAP(k);
			enQueue(q, DESTIN(k));
		}
	}

	/* FIND MAXIMUM FLOW */
	while (!queue_empty(q)) {
		i = deQueue(q);
		discharge(g, q, e, h, i);
	}
	flow = e[1];

	/* FREE ALLOCATED MEMORY */
	free(e);
	free(h);
	free(q);

	return flow;
}

/*
getReach: function to determine which vertices are reachable from the one at cause (using available edges)
Arguments: a struct graph representing a graph, the vertice at cause and an array to store the vertices' reach
Return: nothing
*/
void getReach(Graph g, int v, int* reach) {
	Link k;

	for (k = ADJ(v)->head; k != NULL; k = k->next) {
		if ((CAP(k->rev) - FLOW(k->rev)) != 0 && reach[DESTIN(k)] == 0) {
			reach[DESTIN(k)] = 1;
			getReach(g, DESTIN(k), reach);
		}
	}
}

/*
performAlgorithm: function to solve the project's problem and print the output
Arguments: a struct graph representing a graph
Return: nothing
*/
void performAlgorithm(Graph g) {
	int i, j, maxFlow;
	Link k;
	int* reach = (int*) can_fail_malloc(sizeof(int)*(g->numVertices)); /* vertices' reach (1 - can reach sink, 0 - can't reach sink) */
	int* critical = (int*) can_fail_malloc(sizeof(int)*(g->numVertices)); /* stores the destination of the min cut edges */
	
	/* INITIALIZATION */
	for (i = 0; i < g->numVertices; i++) {
		critical[i] = 0;
		reach[i] = 0;
	}

	/* FIND MAX FLOW */
	maxFlow = pushRelabel(g);

	/* FIND MIN CUT */
	reach[1] = 1;
	getReach(g, 1, reach);

	/* PRINT OUTPUT */
	printf("%d\n", maxFlow);

	int space = 0;
	for (i = g->numSuppliers + 2; i < g->numVertices; i+=2) {
		if (reach[i] == 0 && reach[i+1] == 1) {
			if (space) printf(" ");
			else space = 1;
			printf("%d", REAL(i, g->numSuppliers));
		}
	}
	printf("\n");

	for (i = 2; i < g->numVertices; i++) {
		if (i >= (g->numSuppliers)+2) i++;
		if (reach[i] == 0) {
			for (k = ADJ(i)->head; k != NULL; k = k->next) {
				if (MAIN(k) != 0 && reach[DESTIN(k)] == 1)
					critical[REAL(DESTIN(k), g->numSuppliers)] = 1;
			}

			for (j = 0; j < g->numVertices; j++) {
				if (critical[j])	{
					printf("%d %d\n", REAL(i, g->numSuppliers), j);
					critical[j] = 0;
				}
			}
		}
	}

	/* FREE ALLOCATED MEMORY */
	free(critical);
	free(reach);
}


int main(int argc, char* argv[]) {
	int suppliers, stations, connections, numV, i, o, d, c;
	Link k;
	
	/* NETWORK INITIALIZATION */
	Graph network = init_graph();

	/* INPUT PROCESSING */
	scanf("%d %d %d", &suppliers, &stations, &connections);
	numV = suppliers + (stations*2) + 2;
	network->numVertices = numV;
	network->numSuppliers = suppliers;

	network->vertices = (List*) can_fail_malloc(sizeof(List)*(numV));
	for (i=0; i<numV; i++)
		network->vertices[i] = init_list();

	for (i=2; i<suppliers+2; i++) {
		scanf("%d", &c);
		insert_list(network->vertices[0], i, c, 1, NULL); /* suppliers are connected to a source s with the index 0 */
	}

	for (; i<numV; i+=2) {
		scanf("%d", &c);
		insert_list(network->vertices[i], i+1, c, 1, NULL); /* stations are represented by 2 vertices each - in and out */
	}

	for (i=0; i<connections; i++) {
		scanf("%d %d %d", &o, &d, &c);

		if (o <= suppliers+1)
			insert_list(network->vertices[o], REP(d, suppliers), c, 1, NULL); 
		else
			insert_list(network->vertices[REP(o, suppliers)+1], REP(d, suppliers), c, 1, NULL); /* if the edge comes out of a station, it is added to the corresp out vertice */
	}

	/* RESIDUAL GRAPH INITIALIZATION */
	for (i=0; i<numV; i++) {
		for (k = network->vertices[i]->head; k != NULL; k = k->next) {
			if (MAIN(k) != 0) {
				insert_list(network->vertices[DESTIN(k)], i, 0, 0, k);
				k->rev = network->vertices[DESTIN(k)]->head; /* sets the reverse of the main graph's edge */
			}
		}
	}

	/* PERFORM ALGORITHM */
	performAlgorithm(network);

	/* FREE NETWORK */
	free_graph(network);

	return 0;
}