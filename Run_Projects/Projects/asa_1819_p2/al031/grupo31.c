#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NIL -1
#define min(N, X, Y) (X < Y)? (N = X) : (N = Y)

/*=====================priorityList=======================*/
typedef struct PriorityNode *priorityNode;

struct PriorityNode
{
	int number;
	priorityNode nextPriority;
};

void pushPriority(priorityNode *head, priorityNode *tail, int number) 
{
	priorityNode newNode = (priorityNode) malloc(sizeof(struct PriorityNode));
	newNode->number = number;
	newNode -> nextPriority = NULL;
	if (*head == NULL)
	{
		*tail = *head = newNode;
	}
	else
	{
		(*tail)->nextPriority = newNode;
		(*tail) = newNode;
	}
}

int popPriority(priorityNode *head)
{
	int number;
	priorityNode prev;
	if (*head == NULL)
		return NIL;
	number = (*head) -> number;
	prev = *head;
	*head = (*head)->nextPriority;
	free(prev);
	return number;
}

/*=====================Nodes=======================*/
typedef struct Node *node;

struct Node
{
	void* dataPtr;
	node nextNode;
};

void initNode(node* n)
{
	*n = NULL;
}

node pushNode(node list, void* dataPtr) 
{
	node newNode = (node) malloc(sizeof(struct Node));
	newNode->dataPtr = dataPtr;
	newNode->nextNode = list;
	return newNode;
}

/*=====================Link=======================*/
typedef struct Link *link;

struct Link {
	int u, v;
	int fuv, fvu;
};

link initLink(int u, int v, int capacity) {
	link l = (link) malloc(sizeof(struct Link));
	l->u = u;
	l->v = v;
	l->fuv = capacity;
	l->fvu = 0;
	return l;
}

/*=====================Graph=======================*/
typedef struct Graph *graph;

struct Graph {
	int minDealer, minStation, minAux, maxAux, offset;
	int *height, *e;
	node *adj;
	priorityNode head, tail;
};

graph graphInit(int vert, int minStation, int minAux, int offset) {
	graph g = (graph) malloc(sizeof(struct Graph));
	g->height = (int*) malloc(vert * sizeof(int));
	g->e = (int*) malloc(vert * sizeof(int));
	g->adj = (node*) malloc(vert * sizeof(node));
	g->minDealer = 2;
	g->minStation = minStation;
	g->minAux = minAux;
	g->maxAux = vert;
	g->offset = offset;
	g->head = NULL;
	g->tail = NULL;
	return g;
}

/*=====================Code=======================*/
int getAdj(int n, link l)
{
	if (n == l->u)
		return l->v;
	else return l->u;
}

void clearLinks(int i, node list)
{
	node prev;
	link data;
	while (list != NULL) {
		data = list -> dataPtr;
		if (i > getAdj(i, data))
		{
			free(data);
		}
		prev = list;
		list = list -> nextNode;
		free(prev);
	}
}

void clearAdj(graph g)
{
	int i;
	for (i = 0; i < g->maxAux; i++)
	{
		clearLinks(i, g->adj[i]);
	}
}

void graphDestroy(graph g) {
	clearAdj(g);
	free(g->height);
	free(g->adj);
	free(g);
}

graph readLineArguments()
{
	int i, u, v, cap,  max, dealers, stations, links;
	link l;
	scanf("%d %d %d", &dealers, &stations, &links);
	max = 2 + dealers + 2*stations;
	graph g = graphInit(max, dealers + 2, 2 + dealers + stations, stations);
	g->height[0] = 0;
	g->height[1] = max;
	g->e[0] = 0;
	g->e[1] = 0;
	initNode(&g->adj[0]);
	initNode(&g->adj[1]);
	for (i = 2; i < g->minStation; i++)
	{
		g->height[i] = 0;
		g->e[i] = 0;
		initNode(&g->adj[i]);
		scanf("%d", &cap);
		l = initLink(i, 0, cap);
		g->adj[i] = pushNode(g->adj[i], l);
	}
	for (i = g->minStation; i < g->minAux; i++)
	{
		g->height[i] = 0;
		g->height[i + stations] = 0;
		g->e[i] = 0;
		g->e[i + stations] = 0;
		initNode(&g->adj[i]);
		initNode(&g->adj[i + stations]);
		scanf("%d", &cap);
		l = initLink(i, i + stations, cap);
		g->adj[i] = pushNode(g->adj[i], l);
		g->adj[i + stations] = pushNode(g->adj[i + stations], l);
	}
	for (i = 0; i < links; i++)
	{
		scanf("%d %d %d", &u, &v, &cap);
		if (v == 1)
		{
			l = initLink(1, u, cap);
			g->adj[u] = pushNode(g->adj[u], l);
			g->adj[1] = pushNode(g->adj[1], l);
			l->fvu = l->fuv;
			l->fuv = 0;
			g->e[1] -= l->fvu;
			g->e[u] += l->fvu;
			pushPriority(&g -> head, &g -> tail, u);
		}
		else if (v >= g->minStation && v < g->minAux)
		{
			l = initLink(v + stations, u, cap);
			g->adj[u] = pushNode(g->adj[u], l);
			g->adj[v + stations] = pushNode(g->adj[v + stations], l);
		}
	}
	return g;
}

int getPossibleFlux(int vert, link l)
{
	if (vert == l -> u)
	{
		return l -> fuv;
	}
	else return l -> fvu;
}

void pushFlux(int vert, link l, graph g)
{
	int maxFlux;
	if (vert == l -> u)
	{
		min(maxFlux, g -> e[vert], l -> fuv);
		l -> fuv -= maxFlux;
		l -> fvu += maxFlux;
		g -> e[vert] -= maxFlux;
		g -> e[l -> v] += maxFlux;
	}
	else
	{
		min(maxFlux, g -> e[vert], l -> fvu);
		l -> fvu -= maxFlux;
		l -> fuv += maxFlux;
		g -> e[vert] -= maxFlux;
		g -> e[l -> u] += maxFlux;
	}
}

void discharge(int u, graph g)
{
	int v, newHeight = INT_MAX, possibleFlux;
	node adj = g -> adj[u];
	while (g -> e[u] > 0)
	{
		v = getAdj(u, adj -> dataPtr);
		possibleFlux = getPossibleFlux(u, adj -> dataPtr);
		if ((g -> height[u] == 1 + g -> height[v]) && possibleFlux > 0)
		{
			if (v != 0 && v != 1 && g -> e[v] == 0)
				pushPriority(&g -> head, &g -> tail, v);
			pushFlux(u, adj -> dataPtr, g);
		}
		else if (g -> height[v] >= g ->height[u] && g -> height[v] < newHeight && possibleFlux > 0)
		{
			newHeight = g ->height[v];
		}
		adj = adj -> nextNode;
		if (adj == NULL && g -> e[u] > 0)
		{
			adj = g -> adj[u];
			if (newHeight == INT_MAX)
			{
				while (adj != NULL)
				{
					v = getAdj(u, adj -> dataPtr);
					possibleFlux = getPossibleFlux(u, adj -> dataPtr);
					if (g -> height[v] >= g ->height[u] && g -> height[v] < newHeight && possibleFlux > 0)
						newHeight = g ->height[v];
					adj = adj -> nextNode;
				}
				adj = g -> adj[u];
			}
			g -> height[u] = newHeight + 1;
			newHeight = INT_MAX;
		}
	}
}

void relabelToFront(graph g)
{
	int u;
	u = popPriority(&g -> head);
	while (u != NIL)
	{
		discharge(u, g);
		u = popPriority(&g -> head);
	}
}

void merge(int* a, int* b, int *aux, int *aux2, int l, int m, int r) {
	int i, j, k;
	for (i = m+1; i > l; i--) {
		aux[i-1] = a[i-1];
		aux2[i-1] = b[i-1];
	}
	for(j = m; j < r; j++) {
		aux[r+m-j] = a[j+1];
		aux2[r+m-j] = b[j+1];
	}
	for(k = l; k <= r; k++) {
		if(aux[j] == aux[i] && aux2[j] < aux2[i]) {
			a[k] = aux[j];
			b[k] = aux2[j--];
		}
		else if(aux[j] < aux[i]) {
			a[k] = aux[j];
			b[k] = aux2[j--];
		}
		else {
			a[k] = aux[i];
			b[k] = aux2[i++];
		}
	}
}

void mergeSort(int* a, int* b, int *aux, int *aux2, int l, int r) {
	int m = (l+r) / 2;
	if(r <= l) {
		return;
	}
	mergeSort(a, b, aux, aux2, l, m);
	mergeSort(a, b, aux, aux2, m+1, r);
	merge(a, b, aux, aux2, l, m, r);
}

void printCut(graph g)
{
	int sourceHeight = g -> height[1];
	short heights[sourceHeight];
	int vert, cutHeight = NIL, i, j = 0, minVertexNumber, u[g -> maxAux/2], v[g -> maxAux/2];
	int *aux, *aux2;
	node adj = g -> adj[1];
	for (i = 0; i < sourceHeight; i++)
	{
		heights[i] = NIL;
	}
	for (i = 0; i < g -> maxAux; i++)
	{
		if (g -> height[i] < sourceHeight)
			heights[g -> height[i]] = 1;
	}
	for (i = sourceHeight - 1; i >= 0 && cutHeight == NIL; i--)
	{
		if (heights[i] == NIL)
		{
			cutHeight = i;
		}
	}
	if (cutHeight == NIL)
		return;
	while (adj != NULL)
	{
		vert = ((link) adj -> dataPtr)-> v;
		if (g -> height[vert] < cutHeight && ((link) adj -> dataPtr) -> fuv == 0)
		{
			v[j] = 1;
			u[j++] = vert;
		}
		adj = adj -> nextNode;
	}
	minVertexNumber = j;
	for (i = g -> minStation; i < g -> minAux ; i++)
	{
		if (g -> height[i] > cutHeight && g -> height[i + g -> offset] < cutHeight)
		{
			adj = g -> adj[i];
			while (adj != NULL)
			{
				vert = ((link) adj -> dataPtr) -> v;
				if (vert == i + g -> offset && ((link) adj -> dataPtr) -> fuv == 0)
				{
					v[j] = i;
					u[j++] = vert;
				}
				adj = adj -> nextNode;
			}
		}
	}
	for (i = g -> minAux; i < g -> maxAux ; i++)
	{
		if (g -> height[i] > cutHeight)
		{
			adj = g -> adj[i];
			while (adj != NULL)
			{
				vert = ((link) adj -> dataPtr) -> v;
				if (g -> height[vert] < cutHeight && ((link) adj -> dataPtr) -> fuv == 0)
				{
					v[j] = i - g -> offset;
					u[j++] = vert;
					minVertexNumber++;
				}
				adj = adj -> nextNode;
			}
		}
	}
	graphDestroy(g);
	aux = (int*) malloc(j * sizeof(int));
	aux2 = (int*) malloc(j * sizeof(int));
	mergeSort(u, v, aux, aux2, 0, j-1);
	i = j;
	if (minVertexNumber == j)
		printf("\n");
	else
	{
		for (j = minVertexNumber; j < i-1; j++)
		{
			printf("%d ", v[j]);
		}
		printf("%d\n", v[j]);
	}
	for (j = 0; j < minVertexNumber; j++)
	{
		printf("%d %d\n", u[j], v[j]);
	}
	free(aux);
	free(aux2);
}

int main()
{
	graph g = readLineArguments();
	relabelToFront(g);
	printf("%d\n", g -> e[0]);
	if (g -> e[0] == 0)
	{
		free(g->e);
		graphDestroy(g);
	}
	else
	{
		free(g->e);
		printCut(g);
	}
	return 0;
}
