#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>

#define MAX_INT 2147483647;

struct node{
	int id;
	int flow_capacity;
	struct node* next;

};

struct graph{
	struct node** lista_adj;
	int size;
	int sources;
	int storage_points;
};
/*------------------------------------------------*/
typedef struct Node{
	int node_id;
	struct Node* next;
} FIFO_Node;

typedef struct Queue{
	FIFO_Node* head;
	FIFO_Node* tail;
	int size;
} FIFO_Queue;


/*------------------------------------------------*/
struct graph* create_Graph();
void addEdge(struct graph*, int, int, int);
struct node* createNode(int, int);
void printGraph(struct graph*);
int Edmonds_Karp(struct graph*);
int BFS(struct graph*, int**);
int findCapacity(struct node*, int);
void changeCapacity(struct graph*, int, int, int);
int min(int, int);
void Minimum_Cut(struct graph*);
void printEdges(struct graph*);
void freeGraph(struct graph*);
/*------------------------------------------------*/
void init(FIFO_Queue*);
int pop(FIFO_Queue*);
void push(FIFO_Queue*, int);


int main(){
	
	struct graph* graph_ptr = create_Graph();
	printf("%d\n", Edmonds_Karp(graph_ptr));
	Minimum_Cut(graph_ptr);
	printEdges(graph_ptr);
	freeGraph(graph_ptr);
	return EXIT_SUCCESS;
}

struct graph* create_Graph(){
	int i, test ;
	int sources = 0, middle_nodes = 0, edges = 0;
	int capacity_sourcei = 0, capacity_middlenodei = 0, origin = 0, destination = 0, capacity_edgei = 0;
	
	struct graph* flow_graph = can_fail_malloc(sizeof(struct graph));
	test = scanf("%d %d %d", &sources, &middle_nodes, &edges);
	if(test != 3) exit(1);
	
	flow_graph->size = sources + 2*middle_nodes + 2;
	flow_graph->sources = sources;
	flow_graph->storage_points = middle_nodes;
	flow_graph->lista_adj = can_fail_malloc(flow_graph->size * sizeof(struct node));

	for(i=0; i<sources; i++){
		test = scanf("%d", &capacity_sourcei);
		if(test != 1) exit(1);
		addEdge(flow_graph, 0, i+2, capacity_sourcei);
	}

	for(i=0; i<middle_nodes; i++){
		test = scanf("%d", &capacity_middlenodei);
		if(test != 1) exit(1);
		addEdge(flow_graph, sources+2+i, sources+2+i+middle_nodes, capacity_middlenodei);
	}

	for(i=0; i<edges; i++){
		test = scanf("%d %d %d", &origin, &destination, &capacity_edgei);
		if(test != 3) exit(1);
		
		if(origin > sources+1){ 
			origin += middle_nodes;
		}
		addEdge(flow_graph, origin, destination, capacity_edgei);
	}
	
	return flow_graph;
}

void freeGraph(struct graph* flow_graph){
	int i;
	for(i = 0; i<flow_graph->size; i++){
		struct node* temp = flow_graph->lista_adj[i];
		while(temp){
			struct node* aux = temp;
			temp = temp->next;
			free(aux);
		}
	}
	
	free(flow_graph->lista_adj);
	free(flow_graph);
};

void addEdge(struct graph* flow_graph, int NodeA, int NodeB, int FlowAB){
	struct node* newNodeB = createNode(NodeB, FlowAB);
	newNodeB->next = flow_graph->lista_adj[NodeA];
	flow_graph->lista_adj[NodeA] = newNodeB;
};

struct node* createNode(int newNode_id, int Flow){
	struct node* newNode = can_fail_malloc(sizeof(struct node));
	newNode->id = newNode_id;
	newNode->flow_capacity = Flow;
	newNode->next = NULL;
	return newNode;
}

void printGraph(struct graph* graph_ptr){
	int i;
	for(i=0; i<graph_ptr->size; i++){
		printf("\n\nNODE %d:\n",i);
		struct node* temp = graph_ptr->lista_adj[i];
		while(temp){
			printf("-( %d )-> %d\n",temp->flow_capacity, temp->id);
			temp = temp->next;
		}
	}
};

int Edmonds_Karp(struct graph* flow_graph){
	int i;
	int flow = 0, aux;
	int* parent = (int*)can_fail_malloc(flow_graph->size*sizeof(int));
	for(i = 0; i<flow_graph->size; i++)	parent[i] = -1;

	while(BFS(flow_graph,&parent)==1){
		int path_flow = MAX_INT;
		aux = 1;

		while(aux != 0){
			path_flow = min(path_flow,findCapacity(flow_graph->lista_adj[parent[aux]],aux));
			aux = parent[aux];
		}
		flow += path_flow;

		aux = 1;

		while(aux != 0){
			changeCapacity(flow_graph, parent[aux],aux,-path_flow);
			changeCapacity(flow_graph, aux, parent[aux], path_flow);
			aux = parent[aux];
		}
		for(i = 0; i<flow_graph->size; i++)	parent[i] = -1;
	}
	free(parent);
	return flow;
}

int findCapacity(struct node* node_list, int node_id){
	struct node* temp = node_list;
	
	while(temp){
		if(temp->id == node_id)
			return temp->flow_capacity;
			
		temp = temp->next;
	}	
	
	return -1;
}

void changeCapacity(struct graph* flow_graph, int parent_node_id, int node_id, int path_flow){
	struct node* temp = flow_graph->lista_adj[parent_node_id];
	while(temp){
		if(temp->id == node_id){
			temp->flow_capacity+=path_flow;
			return;
		}
		temp = temp->next;
	}
	
	addEdge(flow_graph, parent_node_id, node_id, path_flow);
}

int min(int X, int Y){
	if(X > Y) return Y;
	return X;
}

int BFS(struct graph* flow_graph, int** parent){
	int parent_id,i;
	FIFO_Queue q;

	int* visited = (int*)can_fail_malloc(flow_graph->size*sizeof(int));
	for(i = 0; i<flow_graph->size; i++)	visited[i] = 0;

	init(&q);
	push(&q,0);
	visited[0] = 1;
	while(q.size!=0){
		parent_id = pop(&q);
		struct node* temp = flow_graph->lista_adj[parent_id];
		while(temp){
			if(temp->flow_capacity > 0 && visited[temp->id]==0){
				push(&q,temp->id);
				visited[temp->id] = 1;
				(*parent)[temp->id] = parent_id;
			}
			temp = temp->next;
		}
	}

	if(visited[1] == 1){ 
		free(visited);
		return 1;
	}
	free(visited);
	return 0;
}

void Minimum_Cut(struct graph* flow_graph){
	int son_id, i, temp_cap;
	FIFO_Queue q;

	int* visited = (int*)can_fail_malloc(flow_graph->size*sizeof(int));
	for(i = 0; i<flow_graph->size; i++)	visited[i] = 0;
	
	
	init(&q);
	push(&q,1);
	visited[1] = 1;
	while(q.size!=0){
		son_id = pop(&q);
		for(i = 2; i<flow_graph->size; i++){
			temp_cap = findCapacity(flow_graph->lista_adj[i], son_id);
			if(temp_cap > 0 && visited[i]==0){
				push(&q,i);
				visited[i] = 1;
			}
			else if(temp_cap == 0){
				changeCapacity(flow_graph,i, son_id,-1);
			}
		}
	}
	free(visited);
}

void printEdges(struct graph* flow_graph){
	int i, flag = 0;
	
	for(i = 2+flow_graph->sources; i < 2+flow_graph->sources+flow_graph->storage_points; i++){
		struct node* temp = flow_graph->lista_adj[i];
		while(temp){
			if(temp->flow_capacity == -1){
				if(flag == 1) printf(" %d",i);
				else{
					printf("%d", i);
					flag=1;
				}
			}
			temp = temp->next;
		}
	}
	
	printf("\n");	
	
	for(i = 2; i<2+flow_graph->sources; i++){
		struct node* temp = flow_graph->lista_adj[i];
		while(temp){
			if(temp->flow_capacity == -1){
				printf("%d %d\n", i, temp->id);
			}
			temp = temp->next;
		}
	}	
	
	for(i = 2+flow_graph->sources+flow_graph->storage_points; i < flow_graph->size; i++){
		struct node* temp = flow_graph->lista_adj[i];
		while(temp){
			if(temp->flow_capacity == -1){
				printf("%d %d\n", i-flow_graph->storage_points, temp->id);
			}
			temp = temp->next;
		}
	}	
}

void init(FIFO_Queue* q){
	q->head = NULL;
	q->tail = NULL;
	q->size = 0;
}

int pop(FIFO_Queue* q){
	int node_id = q->head->node_id;
	q->size--;

	FIFO_Node* temp = q->head;
	q->head = q->head->next;
	free(temp);

	return node_id;
}

void push(FIFO_Queue* q, int node_id){
	q->size++;

	if(q->head == NULL){
		q->head = (FIFO_Node*)can_fail_malloc(sizeof(FIFO_Node));
		q->head->node_id = node_id;
		q->head->next = NULL;
		q->tail = q->head;
	}
	else{
		q->tail->next = (FIFO_Node*)can_fail_malloc(sizeof(FIFO_Node));
		q->tail->next->node_id = node_id;
		q->tail->next->next = NULL;
		q->tail = q->tail->next;
	}
}

