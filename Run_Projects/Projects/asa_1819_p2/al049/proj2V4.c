#include <stdlib.h>
#include <stdio.h>


/*==============================================================================
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Vector >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
==============================================================================*/

typedef struct vector {
    long capacity;
	long size;
	void** elements;
} *Vector;

Vector vectorInit(long initSize);

void vectorFree(Vector vectorPtr);

void* vectorIndexAt(Vector vectorPtr, long index);

void vectorChangeItemAtIndex(Vector vectorPtr, long index,void* newItem);

int vectorPush(Vector vectorPtr, void* element);

void* vectorPop(Vector vectorPtr);

long vectorSize(Vector v);


/*==============================================================================
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< List >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
==============================================================================*/

typedef struct node {
	void *item;
	struct node *next;
} *Node;

typedef struct list {
	int size;
	Node head;
	Node tail;
} *List;



List listInit();

void listFree(List lst);

int listPush(List lst, void *item);

void* listPop(List lst);

Node listHead(List lst);

Node listNext(Node node);

int listSize(List lst);

void* listItem(Node node);


/*==============================================================================
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Edge >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
==============================================================================*/

typedef struct edge {
    int vertexNum;
	int flow;
	int original;
	struct edge *twin;
} *Edge;

Edge edgeInit(int n, int flow);

void edgeFree(Edge e);

Edge edgeTwin(Edge e);

void edgeSetTwin(Edge e, Edge twin);

int edgeOriginal(Edge e);

void edgeSetOriginal(Edge e);

int edgeFlow(Edge e);

int edgeVertex(Edge e);

int edgeTwinVertex(Edge e);

void edgeAddFlow(Edge e, int amount);


/*==============================================================================
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Vertex >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
==============================================================================*/

typedef struct vertex {
	int height;
	int excess;
	int current;
	Vector edges;
} *Vertex;

Vertex vertexInit();

void vertexFree(Vertex v);

void vertexAddEdge(Vertex v, Edge e);

Vector vertexGetEdges(Vertex v);

int vertexExcess(Vertex v);

void vertexAddExcess(Vertex v, int val);

int vertexHeight(Vertex v);

void vertexSetHeight(Vertex v, int h);


/*==============================================================================
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Graph >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
==============================================================================*/

typedef struct graph {
	Vertex *vertices;
	int size;
	int suppl;
	int stations;
} *Graph;

Graph graphInit(int suppl, int stations);

void graphFree(Graph g);

Vertex graphGetVertex(Graph g, int n);

int graphSize(Graph g);

int graphConnect(Graph g, int n1, int n2, int capacity);


/*==============================================================================
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Flow Solver >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
==============================================================================*/

int relabelToFront(Graph g, Vertex s, Vertex t, Vertex* heights);

Graph readInput();

void discharge(Graph g,Vertex u, List queue);

void countSort(Vector edges, int size, int low, int high);

void calculateCut(Graph g, Vertex* heights, Vector upEdges, Vector upStations, int* bottomBound, int* topBound);

void printOutput(Graph g, int flow, Vector upEdges, Vector upStations);













/*==============================================================================
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Vector >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
==============================================================================*/

Vector vectorInit(long initSize) {
	Vector vectorPtr = (Vector) malloc(sizeof(struct vector));
	if (vectorPtr == NULL)
		return NULL;

	vectorPtr->capacity = initSize > 1? initSize : 1;
	vectorPtr->size = 0;
	vectorPtr->elements = (void**) malloc(sizeof(void*)*vectorPtr->capacity);
	if (vectorPtr->elements == NULL) {
		free(vectorPtr);
		return NULL;
	}

	return vectorPtr;
}

void vectorFree(Vector vectorPtr) {
	free(vectorPtr->elements);
	free(vectorPtr);
}

void* vectorIndexAt(Vector vectorPtr, long index) {
	if (index < 0 || index >= vectorPtr->size)
		return NULL;

	return vectorPtr->elements[index];
}

void vectorChangeItemAtIndex(Vector vectorPtr, long index,void* newItem){
	if (index < 0 || index >= vectorPtr->size)
		return;

	vectorPtr->elements[index] = newItem;
} 


int vectorPush(Vector vectorPtr, void* element) {
	if (vectorPtr->size == vectorPtr->capacity) {
		void** tmp = (void**) realloc(vectorPtr->elements, sizeof(void*)*2*vectorPtr->capacity);
		if (tmp == NULL)
			return 0;

		vectorPtr->elements = tmp;
		vectorPtr->capacity = vectorPtr->capacity * 2;
	}

	vectorPtr->elements[(vectorPtr->size)++] = element;
	return 1;
}

void* vectorPop(Vector vectorPtr) {
	if (vectorPtr->size == 0)
		return NULL;

	return vectorPtr->elements[--(vectorPtr->size)];
}

long vectorSize(Vector v) {
	return v->size;
}


/*==============================================================================
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< List >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
==============================================================================*/

List listInit() {
	List lst = (List) malloc(sizeof(struct list));
	if (lst == NULL)
		return NULL;
	lst->size = 0;
	lst->head = NULL;
	lst->tail = NULL;

	return lst;
}

void listFree(List lst) {
	Node head;
	while(lst->head != NULL) {
		head = lst->head;
		lst->head = lst->head->next;
		free(head);
	}

	free(lst);
}

int listPush(List lst, void *item) {
	Node new = (Node) malloc(sizeof(struct node));
	if (new == NULL)
		return 0;
	new->item = item;
	new->next = NULL;

	if (lst->head == NULL) {
		lst->head = new;
	} else {
		lst->tail->next = new;
	}

	lst->tail = new;
	(lst->size)++;
	return 1;
}

void* listPop(List lst) {
	if (lst == NULL || lst->head == NULL)
		return NULL;

	Node node = lst->head;
	void *item = node->item;
	lst->head = node->next;
	if (lst->head == NULL) {
		lst->tail = NULL;
	}
	(lst->size)--;
	free(node);
	return item;
}

Node listHead(List lst) {
	if (lst == NULL)
		return NULL;
	return lst->head;
}

Node listNext(Node node) {
	if (node == NULL)
		return NULL;
	return node->next;
}

int listSize(List lst) {
	if (lst == NULL)
		return -1;
	return lst->size;
}

void* listItem(Node node) {
	if (node == NULL)
		return NULL;
	return node->item;
}


/*==============================================================================
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Edge >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
==============================================================================*/

Edge edgeInit(int n, int flow) {
	Edge e = (Edge) malloc(sizeof(struct edge));
	if (e == NULL)
		return NULL;

	e->vertexNum = n;
	e->flow = flow;
	e->twin = NULL;
	e->original = 0;

	return e;
}

void edgeFree(Edge e) {
	free(e);
}

Edge edgeTwin(Edge e){
	return e->twin;
}

void edgeSetTwin(Edge e, Edge twin) {
	e->twin = twin;
}

int edgeOriginal(Edge e){
	if (e != NULL){
		return 0;
	}
	return e->original;
}

void edgeSetOriginal(Edge e){
	if (e == NULL){
		return;
	}
	e->original = 1;
}

int edgeFlow(Edge e) {
	return e->flow;
}

int edgeVertex(Edge e) {
	if (e == NULL){
		return -1;
	}
	return e->vertexNum;
}

int edgeTwinVertex(Edge e){
	if (e == NULL){
		return -1;
	}
	return e->twin->vertexNum;
}

void edgeAddFlow(Edge e, int amount) {
	e->flow -= amount;
	e->twin->flow += amount;
}


/*==============================================================================
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Vertex >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
==============================================================================*/

Vertex vertexInit() {
	Vertex v = (Vertex) malloc(sizeof(struct vertex));
	if (v == NULL)
		return NULL;
	v->edges = vectorInit(-1);
	if (v->edges == NULL) {
		free(v);
		return NULL;
	}
	v->height = 0;
	v->excess = 0;
	v->current = 0;

	return v;
}

void vertexFree(Vertex v) {
	vectorFree(v->edges);
	free(v);
}

void vertexAddEdge(Vertex v, Edge e) {
	if (v == NULL || e == NULL)
		return;

	vectorPush(v->edges, (void*)e);
}

Vector vertexGetEdges(Vertex v) {
	return v->edges;
}

int vertexExcess(Vertex v){
	return v->excess;
}

void vertexAddExcess(Vertex v, int val) {
	v->excess += val;
}

int vertexHeight(Vertex v){
	return v->height;
}

void vertexSetHeight(Vertex v, int h){
	if (v->height >= h){
		return;
	}
	v->height = h;
}


/*==============================================================================
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Graph >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
==============================================================================*/

Graph graphInit(int suppl, int stations) {
	Graph g;
	int i, j, size = 2+suppl+2*stations;

	g = (Graph) malloc(sizeof(struct graph));
	if (g == NULL)
		return NULL;

	g->vertices = (Vertex*) malloc(sizeof(Vertex)*size);
	if (g->vertices == NULL) {
		free(g);
		return NULL;
	}

	for (i = 0; i < size; ++i) {
		(g->vertices)[i] = vertexInit();
		/*vertexSetHeight(g->vertices[i], i);-For testing purposes*/
		if ((g->vertices)[i] == NULL) {
			for (j = 0; j < i; ++j)
				vertexFree((g->vertices)[j]);
			free(g->vertices);
			free(g);
			return NULL;
		}
	}
	vertexSetHeight(g->vertices[1], size);
	g->size = size;
	g->suppl = suppl;
	g->stations = stations;

	return g;
}


void graphFree(Graph g) {
	int i;
	for (i = 0; i < g->size; ++i) {
		Vector edges = vertexGetEdges((g->vertices)[i]);
		Edge e;
		while ((e = (Edge) vectorPop(edges)) != NULL)
			edgeFree(e);

		vertexFree((g->vertices)[i]);
	}

	free(g->vertices);
	free(g);
}

Vertex graphGetVertex(Graph g, int n) {
	if (g == NULL || n < 0 || n > g->size)
		return NULL;

	return (g->vertices)[n];
}

int graphSize(Graph g) {
	return g->size;
}

int graphConnect(Graph g, int n1, int n2, int capacity) {
	if (n1 == n2 || n1 < 0 || n2 < 0 || n1 > g->size || n2 > g->size)
		return 0;

	Edge e1 = edgeInit(n2, capacity);
	Edge e2 = edgeInit(n1, 0);

	edgeSetTwin(e1, e2);
	edgeSetTwin(e2, e1);

	edgeSetOriginal(e1);

	vertexAddEdge((g->vertices)[n1], e1);
	vertexAddEdge((g->vertices)[n2], e2);

	return 1;
}



/*==============================================================================
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Flow Solver >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
==============================================================================*/


Graph readInput() {
	int suppl, stations, connects, capacity, u, v, i, scan;
	Graph g;
	scan = scanf("%d %d %d", &suppl, &stations, &connects);
	g = graphInit(suppl, stations);
	for (i = 2; i < suppl+2; ++i) {
		scan = scanf("%d", &capacity);
		graphConnect(g, i, 0, capacity);
	}
	for (i = suppl+2; i < suppl+stations+2; ++i) {
		scan = scanf("%d", &capacity);
		graphConnect(g, i, i+stations, capacity);
	}

	while(scanf("%d %d %d", &u, &v ,&capacity) == 3) {
		if (u != v) {
			/*Need to check if edges between suppliers can be ignored*/
			if (v > 1+suppl)
				v += stations;
			graphConnect(g, v, u, capacity);
		}
	}
	return g;
}

int relabelToFront(Graph g, Vertex s, Vertex t, Vertex* heights){
	Vector edges;
	Vertex v;
	List queue = listInit();
	int i;


	edges = g->vertices[1]->edges;
	for (i = 0; i < vectorSize(edges); ++i){
		Edge e = (Edge)vectorIndexAt(edges,i);
		g->vertices[1]->excess -= edgeFlow(e);
		g->vertices[e->vertexNum]->excess += edgeFlow(e);
		edgeAddFlow(e,edgeFlow(e));
		listPush(queue, (void*)(g->vertices[e->vertexNum]));
	}
	i = 2;
	while(g->vertices[0]->excess != -(g->vertices[1]->excess)){
		v = (Vertex)listPop(queue);
		discharge(g, v, queue);

	}
	listFree(queue);
	return (g->vertices[0])->excess;
}


void discharge(Graph g,Vertex u, List queue){
	Vertex v;
	Edge e;
	int flow;

	while(u->excess > 0){
		e = (Edge)vectorIndexAt(u->edges, u->current);
		v = NULL;
		if (e != NULL){
			v = g->vertices[edgeVertex(e)];
		}

		if(v == NULL){
			u->height += 1;
			u->current = 0;
		} else if(edgeFlow(e) > 0 && u->height > v->height){
			flow = u->excess > edgeFlow(e) ? edgeFlow(e) : u->excess;
			edgeAddFlow(e, flow);
			u->excess -= flow;
			v->excess += flow;
			if (edgeVertex(e) != 0 && edgeVertex(e) != 1) {
				listPush(queue, (void*)v);
			}
		} else {
			u->current++;
		}

	}
}

/*low and high represent upper and bottom bounderies of vertex' numbers in edge array*/
void countSort(Vector edges, int size, int low, int high){ 
    Edge output[size];
    int range = high - low; 
    int count[range + 1], i;

    for (i = 0; i < range+1; ++i){
     	count[i] = 0;
    } 

    for(i = 0; i < size; ++i) 
        ++count[((Edge)vectorIndexAt(edges,i))->vertexNum - low]; 
  
    for (i = 1; i <= range; ++i) 
        count[i] += count[i-1]; 

    for (i = size-1; i >= 0; --i){ 
        output[count[((Edge)vectorIndexAt(edges,i))->vertexNum - low]-1] = (Edge)vectorIndexAt(edges,i); 
        --count[((Edge)vectorIndexAt(edges,i))->vertexNum - low]; 
    } 

    for (i = 0; i < size; ++i) 
        vectorChangeItemAtIndex(edges, i,(void*) output[i]); 
} 

void calculateCut(Graph g, Vertex* heights, Vector upEdges, Vector upStations, int* bottomBound, int* topBound){
	int i, j, mincut=0;
	Vertex v;
	Edge e;
	Vector edges;

	for (i = 0; i < g->size; ++i){
		v = g->vertices[i];
		if (heights[v->height] == NULL){
			heights[v->height] = v;
		}
	}

	for (i = g->size; i > 0; --i){
		if (heights[i] == NULL){
			mincut = i;
			break;
		}
	}

	for (i = 1; i < g->size; ++i){
		if (((g->vertices)[i])->height > mincut){
			/* Belongs to cut then search edges and add them */
			edges = g->vertices[i]->edges;
			for (j = 0; j < vectorSize(edges); ++j){
				e = (Edge)vectorIndexAt(edges, j);
				v = g->vertices[edgeVertex(e)];
				if (e->original && v->height < mincut && g->vertices[0] != v){		
					if (i == edgeVertex(e) - g->stations && edgeVertex(e) > g->suppl +g->stations + 1 ){
						vectorPush(upStations,edgeTwin(e));/*need to sort by vertexNum*/
					} else {
						vectorPush(upEdges,e);/*need to sort by vertexNum then change to twin and sort by vertexNum again*/
						*topBound = *topBound > edgeVertex(e) ? *topBound : edgeVertex(e);
						*bottomBound = *bottomBound < edgeVertex(e) ? *bottomBound : edgeVertex(e);
					}
				}
			}
		}
	}
}

void printOutput(Graph g, int flow, Vector upEdges, Vector upStations){
	int i, j;
	printf("%d\n", flow);
	for (i = 0; i < vectorSize(upStations); ++i){
		if (i == vectorSize(upStations) - 1){
			printf("%d", edgeVertex(vectorIndexAt(upStations, i)));
		}
		else printf("%d ", edgeVertex(vectorIndexAt(upStations, i)));
	}

	printf("\n");

	for (i = 0; i < vectorSize(upEdges); ++i){
		j = edgeVertex(edgeTwin(vectorIndexAt(upEdges, i)));
		printf("%d ", edgeVertex(vectorIndexAt(upEdges, i)));	
		printf("%d\n", j > (g->suppl + g->stations + 1) ? j - g->stations : j);
	}
}

int main(int argc, char const *argv[]) {
	/*graph: [ (0:sink) (1:hiper) (suppl) (stations in) (stations out) ]*/
	int flow, topBound, bottomBound;
	Graph g = readInput();
	Vertex heights[g->size + 1];
	Vector upStations = vectorInit(0), upEdges = vectorInit(0);
	heights[0] = NULL;
	heights[1] = NULL;
	flow = relabelToFront(g, (g->vertices)[1], (g->vertices)[0], heights);


	heights[g->size] = g->vertices[1];

	topBound = 0;
	bottomBound = g->size;

	calculateCut(g, heights, upEdges, upStations, &bottomBound, &topBound);

	countSort(upEdges, vectorSize(upEdges), bottomBound, topBound);

	printOutput(g, flow, upEdges, upStations);

	vectorFree(upStations);
	vectorFree(upEdges);
	graphFree(g);
	return 0;
}