/* David Azevedo Escobar de Lima */
/* 92447 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Nodes {
	int index;
	int grade;
	int updated;
	int discovered;
	int low;
	int scc;
	int stack;
} Node;

typedef struct AdjNodes {
	Node* node;
	struct AdjNodes* next;
} AdjNode;

typedef struct Graphs {
	int vertices;
	AdjNode** head;
	int* visited;
} Graph;

typedef struct Queues {
	int front, rear, size;
	int capacity;
	AdjNode** array;
} Queue;

typedef struct Stacks {
    int size;
    int capacity;
    AdjNode** array;
} Stack;

Graph* initializeGraph(int vertices) {
	/* malloc for new node */
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->vertices = vertices;
	graph->visited = (int*)malloc(vertices * sizeof(int));
	/* malloc for new adjacency list node */
	graph->head = (AdjNode**)malloc(vertices * sizeof(AdjNode*));
	int i;
	for(i = 0; i < vertices; i++) {
		graph->head[i] = NULL;
	}
	return graph;
}

void addNode(Graph* graph, int index, int grade) {
	/* create new node */
	Node* node = (Node*)malloc(sizeof(Node));
	node->grade = grade;
	node->index = index;
	node->updated = 0;
	node->scc = 0;
	node->stack = 0;
	/* create new adjacency list node */
	AdjNode* adj_node = (AdjNode*)malloc(sizeof(AdjNode));
	adj_node->node = node;
	/* add new node to list */
	graph->head[index - 1] = adj_node;
	adj_node->next = NULL;
}

void addEdge(Graph* graph, int edge1, int edge2) {
	AdjNode* tmp = graph->head[edge1];
	/* create new node for adjacency list */
	Node* node = graph->head[edge2]->node;
	AdjNode* new = (AdjNode*)malloc(sizeof(AdjNode));
	new->node = node;
	new->next = NULL;
	while(tmp->next != NULL) {
		tmp = tmp->next;
	}
	tmp->next = new;
}

void deleteGraph(Graph* graph) {
	int i;
	int vertices = graph->vertices;
	for(i = 0; i < vertices; i++) {
		free(graph->head[i]->node);
		AdjNode* current = graph->head[i];
		AdjNode* next;
		while(current != NULL) {
			next = current->next;
			free(current);
			current = next;
		}
	}
	free(graph->head);
	free(graph->visited);
	free(graph);
}

Queue* createQueue(int capacity) {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->capacity = capacity;
	queue->front = 0;
	queue->size = 0;
	queue->rear = capacity - 1;
	queue->array = (AdjNode**)malloc(queue->capacity * sizeof(AdjNode*));
	return queue;
}

int queueIsFull(Queue* queue) {
	return queue->size == queue->capacity;
}

int queueIsEmpty(Queue* queue) {
	return queue->size == 0;
}

void enqueue(Queue* queue, AdjNode* adj_node) {
	if(queueIsFull(queue))
		return;
	queue->rear = (queue->rear + 1) % queue->capacity;
	queue->array[queue->rear] = adj_node;
	queue->size++;
}

AdjNode* dequeue(Queue* queue) {
	if(queueIsEmpty(queue))
		return NULL;
	AdjNode* adj_node = queue->array[queue->front];
	queue->front = (queue->front + 1) % queue->capacity;
	queue->size--;
	return adj_node;
}

void deleteQueue(Queue* queue) {
	free(queue->array);
	free(queue);
}

Stack* createStack(int capacity)
{
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	stack->size = 0;
	stack->capacity = capacity;
	stack->array = (AdjNode**) malloc(sizeof(AdjNode*) * capacity);
	return stack;
}

void push(Stack* stack, AdjNode* adj_node)
{
	if (stack->capacity > 0)
	{
		stack->array[stack->size] = adj_node;
		adj_node->node->stack = 1;
		stack->capacity--;
		stack->size++;
	}
}

AdjNode* pop(Stack *stack)
{
	if (stack->size > 0)
	{
		AdjNode* top_element = stack->array[stack->size - 1];
		stack->capacity++;
		stack->size--;
		top_element->node->stack = 0;
		return top_element;
	}
	else
	{
		return NULL;
	}
}

void deleteStack(Stack *stack)
{
	free(stack->array);
	free(stack);
}

int min(int a, int b) {
    return a < b ? a : b;
}

void deleteSCCList(AdjNode*** scc_list) {
	int i;
	for(i = 0; scc_list[i] != NULL; i++) {
		free(scc_list[i]);
	}
	free(scc_list);
}

int gradeAlgorithmBFS(Graph* graph, int index) {
	int vertices = graph->vertices;
	Queue* queue = createQueue(vertices);
	AdjNode* u;
	AdjNode* v;

	int biggest_grade = -1;

	int i;
	for(i = 0; i < vertices; i++) {
		graph->visited[i] = 0;
	}
	graph->visited[index - 1] = 1;
	enqueue(queue, graph->head[index - 1]);

	while(!queueIsEmpty(queue)) {
		u = dequeue(queue);
		if(u->node->grade > biggest_grade)
			biggest_grade = u->node->grade;
		for(v = u->next; v != NULL; v = v->next) {

			if(!graph->visited[v->node->index - 1]) {

				graph->visited[v->node->index - 1] = 1;

				if(!v->node->updated) {
					enqueue(queue, graph->head[v->node->index - 1]);
				}

				else {
					if(v->node->grade > biggest_grade)
						biggest_grade = v->node->grade;
				}
			}
		}
	}

	deleteQueue(queue);
	return biggest_grade;
}

void tarjanVisit(Graph* graph, AdjNode* u, int* visited, Stack* stack, AdjNode*** scc_list, int* n_scc) {
	AdjNode** new_scc;
	u->node->discovered = *visited;
	u->node->low = *visited;
	AdjNode* v;
	(*visited)++;
	push(stack, u);
	for(v = u->next; v != NULL; v = v->next) {
		if(v->node->discovered == -1 || v->node->stack) {
			if(v->node->discovered == -1)
				tarjanVisit(graph, graph->head[v->node->index - 1], visited, stack, scc_list, n_scc);
			if(!v->node->scc)
				u->node->low = min(u->node->low, v->node->low);
		}
	}
	if(u->node->discovered == u->node->low) {
		int counter_scc = 0;
		new_scc = (AdjNode**)malloc((stack->size + 1) * sizeof(AdjNode*));
		int i;
		for(i = 0; i < (stack->size + 1); i++)
			new_scc[i] = NULL;
		v = pop(stack);
		while(v != u) {
			new_scc[counter_scc] = v;
			v->node->scc = 1;
			counter_scc++;
			v = pop(stack);
		}
		new_scc[counter_scc] = u;
		u->node->scc = 1;
		scc_list[*n_scc] = new_scc;
		(*n_scc)++;
	}
}

AdjNode*** tarjanAlgorithm(Graph* graph) {
	int vertices = graph->vertices;
	AdjNode*** scc_list = (AdjNode***)malloc((vertices + 1) * sizeof(AdjNode**));		/* list with SCCs */
	int i;
	for(i = 0; i < (vertices + 1); i++)
		scc_list[i] = NULL;
	int visited = 0;
	int n_scc = 0;																		/* number of SCCs discovered */
	Stack* stack = createStack(vertices);
	for(i = 0; i < vertices; i++)
		graph->head[i]->node->discovered = -1;
	for(i = 0; i < vertices; i++)
		if(graph->head[i]->node->discovered == -1)
			tarjanVisit(graph, graph->head[i], &visited, stack, scc_list, &n_scc);
	deleteStack(stack);
	return scc_list;
}

int main() {
	int enrolled, relationships;
	int grade;
	int student1, student2;
	int biggest_grade;
	AdjNode*** scc_list;
	/* initialize graph */
	Graph* graph;
	scanf("%d %*c %d", &enrolled, &relationships);
	graph = initializeGraph(enrolled);						/* O(V) */
	/* create nodes */
	int i, j;
	for(i = 0; i < enrolled; i++) {							/* O(V) */
		scanf("%d", &grade);
		addNode(graph, i + 1, grade);
	}
	/* create edges */
	for(i = 0; i < relationships; i++) {				
		scanf("%d %d", &student1, &student2);				/* O(E) */
		addEdge(graph, student1 - 1, student2 - 1);			/* pior: O(V), melhor: O(1) */
	}
	/* find SCCs */
	scc_list = tarjanAlgorithm(graph);
	/* apply algorithm to first vertex of each SCC */
	for(i = 0; scc_list[i] != NULL; i++) {
		biggest_grade = gradeAlgorithmBFS(graph, scc_list[i][0]->node->index);
		for(j = 0; scc_list[i][j] != NULL; j++) {
			scc_list[i][j]->node->grade = biggest_grade;
			scc_list[i][j]->node->updated = 1;
		}
	}
	for(i = 0; i < enrolled; i++)
		printf("%d\n", graph->head[i]->node->grade);		/* O(V) */
	deleteSCCList(scc_list);
	deleteGraph(graph);										/* pior: O(V^2), melhor: O(V) */
	return 0;
}
