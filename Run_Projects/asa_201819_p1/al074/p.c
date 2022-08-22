#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define NIL -1

struct AdjListNode {
	int dest;
	struct AdjListNode* next;
};

struct EdgesNode {
	int u, v, check;
	struct EdgesNode* next;
};

struct AdjList {
	struct AdjListNode* head;
};

struct Graph {
	int V;
	struct AdjList* array;
};

struct Node {
	int data;
	struct Node* link;
};

struct EdgesNode* InsertEdge(struct EdgesNode* head, int u, int v) {
	struct EdgesNode* e = (struct EdgesNode*) malloc(sizeof(struct EdgesNode));
	e->u = u;
	e->v = v;
	e->check = 0;
	e->next = head;
	return e;
}

void FREEedges(struct EdgesNode* head) {
	struct EdgesNode* e;
	while(head != NULL) {
		e = head;
		head = head->next;
		free(e);
	}
}

struct EdgesNode* delete(struct EdgesNode* head, int u, int v) {
	struct EdgesNode* t, *prev;
	for(t = head, prev = NULL; t != NULL; prev = t, t = t->next) {
		if((t->u == u && t->v == v )||( t->u == v && t->v == u)) {
			if(t == head)
				head = t->next;
			else
				prev->next = t->next;
			if(t->check == 1)
				free(t);
			else
				t->check += 1;
		}
	}
	return head;
}

struct Node* top;

void push(int data) {
	struct Node* temp;
	temp = (struct Node*) malloc(sizeof(struct Node));
	temp->data = data;
	temp->link = top;
	top = temp;
}

int isEmpty() {
	return top == NULL;
}

void pop() {
	struct Node* temp;
	if(top != NULL) {
		temp = top;
		top = top->link;
		temp->link = NULL;
		free(temp);
	}
}

int peek() {
	if(!isEmpty(top))
		return top->data;
	else {
		exit(EXIT_FAILURE);
	}
}

int find(int parent[], int i) {
	if(parent[i] <= -1) 
		return i;
	if(parent[parent[i]] >= 0)
		parent[i] = parent[parent[i]];
	return find(parent, parent[i]);
}

void Union(int parent[], int x, int y) {
	int xset = find(parent, x);
	int yset = find(parent, y);
	if(xset > yset) {
		parent[xset] += parent[yset];
		parent[yset] = xset;
	}
	else if(xset < yset) {
		parent[yset] += parent[xset];
		parent[xset] = yset; 
	}
	else {/* DO NOTHING */}
}

struct AdjListNode* NewAdjListNode(int dest) {
	struct AdjListNode* newNode =
		(struct AdjListNode*) malloc(sizeof(struct AdjListNode));
	newNode->dest = dest;
	newNode->next = NULL;
	return newNode;
}	

struct Graph* createGraph(int V) {
	struct Graph* graph = 
		(struct Graph*) malloc(sizeof(struct Graph));
	graph->V = V;
	graph->array = 
		(struct AdjList*) malloc((V + 1) * sizeof(struct AdjList));
	int i;
	for(i = 0; i <= V; i++) {
		graph->array[i].head = NULL;
	}
	return graph;
}

void FREEgraph(struct Graph* g) {
	struct AdjListNode* t;
	struct AdjListNode* prev;
	int i;
	for(i = 0; i < g->V; i++) {
		for(t = g->array[i].head, prev = NULL; t != NULL; prev = t, t = t->next) {
			if(prev != NULL) 
				free(prev);
		}
	}
	free(g->array);
	free(g);
}

void addEdge(struct Graph* graph, int src, int dest) {
	struct AdjListNode* newNode = NewAdjListNode(dest);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;
	newNode = NewAdjListNode(src);
	newNode->next = graph->array[dest].head;
	graph->array[dest].head = newNode;
}

struct EdgesNode* head;

void DFS(struct Graph* g, int u, int visited[], int disc[], 
			int low[], int parent[], int ap[], int time) {
	struct AdjListNode* t;
	int children = 0;
	visited[u] = 1;
	disc[u] = time + 1;
	low[u] = disc[u];
	for(t = g->array[u].head; t != NULL; t = t->next) {
		int v = t->dest;
		if(visited[v] == 0) {
			children++;
			parent[v] = u;
			DFS(g, v, visited, disc, low, parent, ap, time + 1);
			if(low[u] > low[v]) {
				low[u] = low[v];
			}
			if(parent[u] == NIL && children > 1)
				ap[u] = 1;
			if(parent[u] != NIL && low[v] >= disc[u])
				ap[u] = 1;

		}
		else if(v != parent[u]) {
			if(low[u] > disc[v]) {
				low[u] = disc[v];
			}
		}
	}
}

void EXE(struct Graph* g, int E) {
	int i, V = g->V;
	int visited[V + 1];
	int disc[V + 1];
	int low[V + 1];
	int parent[V + 1];
	int ap[V + 1];
	struct AdjListNode* e;

	for(i = 0; i <= V; i++) {
		parent[i] = NIL;
		visited[i] = 0;
		ap[i] = 0;
	}

	for(i = 0; i <= V; i++) {
		DFS(g, i, visited, disc, low, parent, ap, 0);
	}

	int* list = (int*) malloc((V + 1) * sizeof(int));
	memset(list, -1, (V + 1) * sizeof(int));
	int C = 0;
	for(i = 1; i <= V; i++) {
		if(ap[i] == 1) 
			C++;
		else {
			for(e = g->array[i].head; e != NULL; e = e->next) {
				if(ap[e->dest] == 0)
				Union(list, i, e->dest);
			}
		}
	}
	printf("%d\n", C);


	int min = 0;
	for(i = 0; i < (V + 1); i++) {
		if(list[i] < min) 
			min = list[i];
	}
	printf("%d\n", (-1)*min);
	free(list);
}

int main() {
	int V = 0, E = 0, i, u, v, ret, Sub;
	char aux[500];
	char result[10000];
	strcpy(result, "");
	ret = scanf("%d", &V);
	ret = scanf("%d", &E);
	int* list = (int*) malloc((V + 1) * sizeof(int));
	memset(list, -1, (V + 1) * sizeof(int));

	struct Graph* g = createGraph(V);
	for(i = 0; i < E; i++) {
		ret = scanf("%d %d", &u, &v);
		addEdge(g, u, v);
		Union(list, u, v);
	}
	for(i = 1, Sub = 0; i < (V + 1); i++) {
		if(list[i] < 0) {
			Sub++;
			if(i == V)
				sprintf(aux, "%d", i);
			else
				sprintf(aux, "%d ", i);
			strcat(result, aux);
		}
	}
	printf("%d\n%s\n", Sub, result);
	free(list);
	EXE(g, E);
	FREEedges(head);
	FREEgraph(g);
	return (ret = 0);
}