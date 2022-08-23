#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define NORMAL 0
#define HOUSE 2
#define MARKET 1
#define BOTH 3
#define SOURCE 4
#define DEST 5
#define VISITED 6

#define WHITE -1
#define GRAY -2
#define BLACK -3

/* Structures for adjacency list representation */
typedef struct Node {
	int dest;
	int capacity;
	struct Node* next;
}Node;

typedef struct AdjList
{
	Node* head;
}AdjList;

typedef struct Graph{
	int v;
    AdjList* array;
}Graph;

typedef struct Stack { 
    int top; 
    int* array; 
}Stack; 

Graph* graph; /* graph of the streets */

int num_av, num_str; /* Number of avenues and streets respectively */
int num_sup, num_prs; /* Number of supermarkets and people respectively */

int num_nodes = 0;		/* Number of nodes */

Stack* create_stack(unsigned capacity) 
{ 
    Stack* stack = (Stack*)malloc(sizeof(struct Stack)); 
    stack->top = -1; 
    stack->array = (int*)malloc(capacity * sizeof(int)); 
    return stack; 
} 

int isEmpty(Stack* stack) 
{ 
    return stack->top == -1; 
}

int pop(Stack* stack) 
{ 
    if (isEmpty(stack)) 
        return 0; 
    return stack->array[stack->top--]; 
} 

void push(Stack* stack, int item) 
{ 
    stack->array[++stack->top] = item;
} 

int getNode(int str, int av){
	return (str-1)*num_av + (av-1);
}

Node* new_node(int dest){
	
	Node* node = (Node*)malloc(sizeof(Node));
	
	node->dest = dest;
	node->next = NULL;

	return node;
}

Graph* create_graph(int v){	

	Graph* graph = (Graph*)malloc(sizeof(Graph));

	graph->v = v;

	graph->array = (AdjList*) malloc(v * sizeof(AdjList));

	int i;
	for (i = 0; i < v; i++){
		graph->array[i].head = NULL;
	}

	return graph;
}

void add_edge(int src, int dest, int capacity){

	Node* node = new_node(dest);
	node->next = graph->array[src].head;
	node->capacity = capacity;
	graph->array[src].head = node;
}

int get_Vin(int v){
	return v * 2;
}

int get_Vout(int v){
	return v * 2 + 1;
}

void parse_input(){
	
	int av = 0, str = 0, node = 0;
	long e;

	scanf("%d %d", &num_av, &num_str);
	scanf("%d %d", &num_sup, &num_prs);

	num_nodes = num_av * num_str; /* Calculating the number of total nodes */

	graph = create_graph(2*num_nodes+2);

	/* Reading input data for the markets location */
	for (e = 0; e < num_sup; e++) {
		scanf("%d %d", &av, &str);
		node = getNode(str, av);
		add_edge(get_Vout(node), 2*num_nodes + 1, 1);
		add_edge(2*num_nodes + 1, get_Vout(node),0);
	}

	/* Reading input data for the peoples residences location */
	for (e = 0; e < num_prs; e++) {
		scanf("%d %d", &av, &str);
		node = getNode(str, av);
		add_edge(2*num_nodes, get_Vin(node), 1);
		add_edge(get_Vin(node), 2*num_nodes, 0);
	}

	for (e = 0; e < num_nodes; e++){
		add_edge(get_Vin(e), get_Vout(e), 1);
		add_edge(get_Vout(e), get_Vin(e), 0);
		if (e % num_av > 0){
			add_edge(get_Vout(e), get_Vin(e - 1), 1);
			add_edge(get_Vin(e - 1), get_Vout(e), 0);
		} 
		if (e % num_av < num_av - 1){
			add_edge(get_Vout(e), get_Vin(e + 1), 1);
			add_edge(get_Vin(e + 1), get_Vout(e), 0);
		}
		if (e / num_av > 0){
			add_edge(get_Vout(e), get_Vin(e - num_av), 1);
			add_edge(get_Vin(e - num_av), get_Vout(e), 0);
		}
		if (e / num_av < num_str - 1){
			add_edge(get_Vout(e), get_Vin(e + num_av), 1);
			add_edge(get_Vin(e + num_av), get_Vout(e), 0);
		}	
	}
}

int bfs(int source, int target, int* parent){

	Node* node;
	
	Stack* stack = create_stack(2*num_nodes + 2);

	memset(parent, -1, (2*num_nodes + 2)*sizeof(int));

	push(stack, source);
	parent[source] = -2;

	while (!isEmpty(stack)){

		int currentNode = pop(stack);

		node = graph->array[currentNode].head;

		while (node != NULL){
			
			if (parent[node->dest] == -1){
				
				if (node->capacity > 0){
					
					parent[node->dest] = currentNode;
					
					if (node->dest == target){
						free(stack->array);
						free(stack);
						return 1;
					}
					
					push(stack, node->dest);
				}
			}
			node = node->next;
		}

	}
	free(stack->array);
	free(stack);
	return 0;
}

int max_capacity(int source, int dest){

	int max_capacity = 0;
	int* parent;
	Node* node;

	parent = (int*)malloc((2*num_nodes + 2)*sizeof(int));

		
	while(1){

		int flow = bfs(source, dest, parent);
		
		if (flow == 0){
			break;
		}

		max_capacity += 1;

		int currentNode = dest;

		while (currentNode != source){
			int previousNode = parent[currentNode];

			node = graph->array[previousNode].head;
			while (node->dest != currentNode){
				node = node->next;
			}
			node->capacity = !node->capacity;

			node = graph->array[currentNode].head;
			while (node->dest != previousNode){
				node = node->next;
			}
			node->capacity = !node->capacity;

			currentNode = previousNode;

		}
	}
	free(parent);
	return max_capacity;
}

int main(){
	
	parse_input(); /* Function call to parse the input from the terminal */ 

	printf("%d\n", max_capacity(2*num_nodes, 2*num_nodes+1));

	return 0;
}

/*
My example:
3 3
2 2
1 1
1 2
3 2
3 3
*/

/*
Exemplo Vertice comum:
8 4
2 6
4 2
6 4
1 1
2 2
1 3
8 1
8 2
4 2
*/

/*
Teste enunciado
Input:
5 5
7 7
1 1
1 3
2 4
1 2
1 4
3 4
3 5
2 1
2 3
2 2
3 2
2 5
4 4
5 3
Output: 6
*/

/*
Teste enunciado
Input:
3 4
3 3
1 4
2 4
3 3
1 1
1 2
2 2
Output: 3
*/
