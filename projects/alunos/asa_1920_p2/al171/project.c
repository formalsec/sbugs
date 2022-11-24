#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/* David Azevedo Escobar de Lima */
/* 92447 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INFINITE_CAPACITY INT_MAX - 100	/* simulates infinite capacity */

enum crossing{Empty, Supermarket, Residence};

enum color{White, Gray, Black};

typedef struct Node {
	int index;
	int crossing;
} Node;

/* node for the adjacency list */
typedef struct AdjNode {
	Node* node;
	int r_capacity;
	struct AdjNode* next;
} AdjNode;

/* M x N grid graph data structure */
typedef struct Graph {
	int numVertices;
	int M;
	int N;
	AdjNode** adjList;
} Graph;

/* returns a node's index, given its street and avenue */
int nodeIndex(int avenue, int street, int numAvenues) {
	return numAvenues * (street - 1) + (avenue - 1);
}

/* classifies a node as empty, supermarket or residence */
void classifyNode(Graph* graph, int classification, int index) {
	graph->adjList[index]->node->crossing = classification;
}

/* creates a new node and adds it to the graph's adjacency list */
void addNode(Graph* graph, int index) {
	Node* node = (Node*)can_fail_malloc(sizeof(Node));
	node->index = index;
	node->crossing = Empty;
	/* add new node to adjacency list */
	AdjNode* adj_node = (AdjNode*)can_fail_malloc(sizeof(AdjNode));
	adj_node->node = node;
	adj_node->r_capacity = -1;
	adj_node->next = NULL;
	graph->adjList[index] = adj_node;
}

void addNodes(Graph* graph) {
	int i;	/* iterator */
	int numVertices = graph->numVertices * 2 + 2;
	for (i = 0; i < numVertices; i++)
		addNode(graph, i);
}

/* adds a new forward edge between the nodes with indexes index1 and index2 with residual capacity capacity*/
void addEdge(Graph* graph, int index1, int index2, int capacity) {
	AdjNode* tmp = graph->adjList[index1];
	/* create new node for adjacency list */
	Node* node = graph->adjList[index2]->node;
	AdjNode* new = (AdjNode*)can_fail_malloc(sizeof(AdjNode));
	new->node = node;
	new->r_capacity = capacity;
	new->next = NULL;
	/* find empty slot */
	while(tmp->next != NULL) {
		tmp = tmp->next;
	}
	tmp->next = new;
}

/* adds all of a node's edges, given its index */
void addEdges(Graph* graph, int index) {
	int M = graph->M;
	int N = graph->N;
	int numVertices = graph->numVertices;
	addEdge(graph, index, index + numVertices, 1);
	addEdge(graph, index + numVertices, index, 0);
	if ( index % N != 0 ) {						/* if second node is on the left */
		addEdge(graph, index + numVertices, index - 1, 1);
		addEdge(graph, index - 1, index + numVertices, 0);
	}
	if ( index % N != (N - 1) )	{				/* if second node is on the right */
		addEdge(graph, index + numVertices, index + 1, 1);
		addEdge(graph, index + 1, index + numVertices, 0);
	}
	if ( index >= N ) {							/* if second node is above */
		addEdge(graph, index + numVertices, index - N, 1);
		addEdge(graph, index - N, index + numVertices, 0);
	}
	if ( index < (N * (M - 1)) ) {				/* if second node is below */
		addEdge(graph, index + numVertices, index + N, 1);
		addEdge(graph, index + N, index + numVertices, 0);
	}
}

/* create new M x N grid graph, where M = numStreets and N = numAvenues */
Graph* newGridGraph(int numAvenues, int numStreets) {
	int i;	/* iterator */
	int M = numStreets;
	int N = numAvenues;
	int numVertices = M * N;
	int rNumVertices = numVertices * 2 + 2;
	/* allocate memory for new graph */
	Graph* graph = (Graph*)can_fail_malloc(sizeof(Graph));
	graph->numVertices = numVertices;
	graph->M = M;
	graph->N = N;
	/* create the graph's adjacency list */
	graph->adjList = (AdjNode**)can_fail_malloc(rNumVertices * sizeof(AdjNode*));
	for(i = 0; i < rNumVertices; i++) {
		graph->adjList[i] = NULL;
	}
	/* add all nodes and edges */
	addNodes(graph);
	for (i = 0; i < numVertices; i++)
		addEdges(graph, i);
	return graph;
}

/* frees a grid graph from memory */
void freeGridGraph(Graph* graph) {
	int i;	/* iterator */
	int vertices = graph->numVertices * 2 + 2;
	/* free adjacency list */
	for(i = 0; i < vertices; i++) {
		free(graph->adjList[i]->node);
		AdjNode* current = graph->adjList[i];
		AdjNode* next;
		while(current != NULL) {
			next = current->next;
			free(current);
			current = next;
		}
	}
	free(graph->adjList);
	free(graph);
}

/* Print the graph */
void printGraph(Graph* graph) {
  int v;
  for (v = 0; v < graph->numVertices * 2 + 2; v++) {
    AdjNode* temp = graph->adjList[v];
    if (temp->node->index == graph->numVertices * 2)
    	printf("\n Adjacency list of Supersource \n ");
    else if (temp->node->index == graph->numVertices * 2 + 1)
    	printf("\n Adjacency list of Superdest \n ");
    else
    	printf("\n Adjacency list of vertex %d\n ", v);
    while (temp) {
   	  if (temp->node->index == graph->numVertices * 2)
   	  	printf("Supersource (%d) -> ", temp->r_capacity);
   	  else if (temp->node->index == graph->numVertices * 2 + 1)
   	  	printf("Superdest (%d) -> \n", temp->r_capacity);
   	  else
      	printf("%d (%d)-> ", temp->node->index, temp->r_capacity);
      temp = temp->next;
    }
    printf("\n");
  }
}

/* queue for BFS algorithm */
int head, tail;
int* queue;

void enqueue(int v)
{
	queue[tail] = v;
	tail++;
}

int dequeue()
{
	int v = queue[head];
	head++;
	return v;
}

/* gives the shortest path from supersource to superdest */
int bfs(Graph* graph, int supersource, int superdest, int* parent) {
	int i;	/* iterator */
	int u, v;
	AdjNode* v_node;
	int numVertices = graph->numVertices * 2 + 2;
	queue = (int*)can_fail_malloc(numVertices * sizeof(int));
	int color[numVertices];
	for (i = 0; i < numVertices; i++)
		color[i] = White;

	head = tail = 0;

	color[supersource] = Gray;
	parent[supersource] = -1;
	enqueue(supersource);

	while(head != tail) {
		u = dequeue();
		v_node = graph->adjList[u]->next;
		while(v_node != NULL) {
			v = v_node->node->index;
			if(color[v] == White && v_node->r_capacity > 0) {
				color[v] = Gray;
				parent[v] = u;
				enqueue(v);
			}
			v_node = v_node->next;
		}
		color[u] = Black;
	}
	free(queue);
	return(color[superdest] == Black);
}

void printPath(int* parent, int source, int dest) {
	int i = parent[dest];
	printf(" Superdest <- ");
	while (i != source) {
		printf("%d <- ", i);
		i = parent[i];
	}
	printf(" Supersource: Path\n");
}

int min(int a, int b) {
    return a < b ? a : b;
}

/* returns the residual capacity of the forward edge from u to v */
int residualCapacity(Graph* graph, int u, int v) {
	AdjNode* node = graph->adjList[u]->next;
	while (node->node->index != v)
		node = node->next;
	return node->r_capacity;
}

/* decrements the capacity of forward edge (u, v) and increments the capacity of backwards edge (v, u) */
void updateCapacity(Graph* graph, int u, int v, int flow) {
	AdjNode* forward_node = graph->adjList[u]->next;
	int supersource = graph->numVertices * 2;
	int superdest = graph->numVertices * 2 + 1;

	while (forward_node->node->index != v)
		forward_node = forward_node->next;
	forward_node->r_capacity -= flow;

	if(v != superdest && u != supersource) {
		AdjNode* backwards_node = graph->adjList[v]->next;
		while (backwards_node->node->index != u)
			backwards_node = backwards_node->next;
		backwards_node->r_capacity += flow;
	}
}

int fordFulkerson(Graph* graph, int supersource, int superdest) {
	int u, v;	/* iterators */
	int max_flow = 0;
	int* parent = (int*)can_fail_malloc((graph->numVertices * 2 + 2) * sizeof(int));

	while(bfs(graph, supersource, superdest, parent)) {
		/* find the minimum residual capacity of the path */
		int path_flow = INFINITE_CAPACITY;
		v = superdest;
		while(v != supersource) {
			u = parent[v];
			path_flow = min(path_flow, residualCapacity(graph, u, v));
			v = parent[v];
		}
		/* update the residual capacity of the forward edges along the path and their respective backward edges */
		v = superdest;
		while(v != supersource) {
			u = parent[v];
			updateCapacity(graph, u, v, path_flow);
			v = parent[v];
		}

		max_flow += path_flow;
	}
	free(parent);
	return max_flow;
}

int main() {
	int i;	/* iterator */
	int numAvenues, numStreets;
	int numSmarkets, numPeople;
	int avenue, street;
	int index, supersource, superdest;
	scanf("%d %d", &numAvenues, &numStreets);
	scanf("%d %d", &numSmarkets, &numPeople);
	Graph* graph = newGridGraph(numAvenues, numStreets);
	int numVertices = graph->numVertices;
	supersource = numVertices * 2;
	superdest = supersource + 1;
	/* add Supermarket classification to certain nodes */
	for (i = 0; i < numSmarkets; i++) {
		scanf("%d %d", &avenue, &street);
		index = nodeIndex(avenue, street, numAvenues);
		classifyNode(graph, Supermarket, index);
		addEdge(graph, index + numVertices, superdest, INFINITE_CAPACITY);	/* add forward edges from the Supermarkets to the superdest */
	}
	/* add Residence classification to certain nodes */
	for (i = 0; i < numPeople; i++) {
		scanf("%d %d", &avenue, &street);
		index = nodeIndex(avenue, street, numAvenues);
		classifyNode(graph, Residence, index);
		addEdge(graph, supersource, index, INFINITE_CAPACITY);	/* add forward edges from the supersource to the Residences */
	}

	printf("%d\n", fordFulkerson(graph, supersource, superdest));

	freeGridGraph(graph);

	return 0;
}