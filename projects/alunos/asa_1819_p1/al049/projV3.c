#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

/*==============================================================================
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Vector >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
==============================================================================*/

/*Structure: vector (*Vector) ..................................................
	Stores data for manipulation of vectors of integers.
		> maximum capacity of the vector
		> current size of the vector
		> pointer to the array of elements
..............................................................................*/
typedef struct vector {
    int capacity;
	int size;
	int* elements;
} *Vector;

/*vectorInit: creates new vector with the size given (mininum size = 1).......*/
Vector vectorInit(int initSize);

/*vectorFree: frees the given vector..........................................*/
void vectorFree(Vector vectorPtr);

/*vectorIndexAt: returns the element at the specified index...................*/
int vectorIndexAt(Vector vectorPtr, int index);

/*vectorPush: inserts the new element to the end of the vector................*/
int vectorPush(Vector vectorPtr, int element);

/*vectorPop: removes and returns the last inserted element....................*/
int vectorPop(Vector vectorPtr);

/*vectorSize: returns the size of the vector..................................*/
int vectorSize(Vector v);

/*==============================================================================
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Vertex >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
==============================================================================*/

/*Structure: vertex (*Vertex) ...............................................,..
	Stores data for manipulation of vertices.
		> number of times the vertex was visited
		> time of the Tarjan algorithm
		> low time of the Tarjan algorithm
		> parent of the vertex of the Tarjan algorithm
		> vector of connections to other vertices
..............................................................................*/
typedef struct vertex {
	int visits;
	int time;
	int low;
	struct vertex *parent;
	Vector connections;
} *Vertex;

/*vertexInit: creates new vertex with the given id number.....................*/
Vertex vertexInit(int n);

/*vertexFree: frees a vertex..................................................*/
void vertexFree(Vertex v);

/*vertexAddVisit: adds a visit to a vertex....................................*/
void vertexAddVisit(Vertex v);

/*vertexVisited: returns if the vertex was visited............................*/
int vertexVisited(Vertex v);

/*vertexVisitCount: returns the number of visits of the vertex................*/
int vertexVisitCount(Vertex v);

/*vertexSetTime: sets the given value to the vertex time......................*/
void vertexSetTime(Vertex v, int t);

/*vertexGetTime: returns the time of a vertex.................................*/
int vertexGetTime(Vertex v);

/*vertexGetLow: returns the low of a vertex...................................*/
int vertexGetLow(Vertex v);

/*vertexSetLow: sets the given value to the vertex low........................*/
void vertexSetLow(Vertex v, int t);

/*vertexSetParent: sets the given vertex id as the vertex parent..............*/
void vertexSetParent(Vertex v, Vertex p);

/*vertexGetParent: returns the parent of a vertex.............................*/
Vertex vertexGetParent(Vertex v);

/*vertexHasParent: returns if a vertex has a parent or not....................*/
int vertexHasParent(Vertex v);

/*vertexAddConnection: adds a connection to the vertex........................*/
void vertexAddConnection(Vertex v, int n);

/*vertexGetConnections: returns the connections of a vertex...................*/
Vector vertexGetConnections(Vertex v);

/*==============================================================================
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Graph >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
==============================================================================*/

/*Structure: graph (*Graph) ...............................................,..
	Stores data for manipulation of the graph.
		> vertices of the graph
		> number of vertices of the graph
..............................................................................*/
typedef struct graph {
	Vertex *vertices;
	int size;
} *Graph;

/*graphInit: creates a new graph with the given number of vertices (1 to v)...*/
Graph graphInit(int v);

/*graphFree: frees a graph....................................................*/
void graphFree(Graph g);

/*graphGetVertex: returns the vertex of id n..................................*/
Vertex graphGetVertex(Graph g, int n);

/*graphSize: returns the size (number of vertices) of the graph...............*/
int graphSize(Graph g);

/*graphConnect: adds a bidirectional connection between vertex n1 and n2......*/
int graphConnect(Graph g, int n1, int n2);

/*==============================================================================
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Networks >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
==============================================================================*/

/*errorFound: prints the error message given and exits with error.............*/
void errorFound(const char* message);

/*readInput: reads the input and returns a graph representing the input*/
Graph readInput();

/*calcArtPoints: calculates the articulation points of a graph................*/
void calcArtPoints(Graph g, Vertex v, int *t, int *artPoints);

/*calcSize: calculates the highest size of all the subgraphs..................*/
int calcSize(Graph g, Vertex v);

/*networkAnalysis: analyses the graph given...................................*/
Vector networkAnalysis(Graph g, int *artPoints, int *maxTree);

/*printOutput: prints the output of the program...............................*/
void printOutput(Vector trees, int artPoints, int maxTree);



/*==============================================================================
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Vector >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
==============================================================================*/

/*Function: vectorInit..........................................................
	Creates a new vector with the size given (0: applies default of 1).
	Input:	> initial size of the vector
	Output: Vector created
..............................................................................*/
Vector vectorInit(int initSize) {
	Vector vectorPtr = (Vector) can_fail_malloc(sizeof(struct vector));
	if (vectorPtr == NULL)
		return NULL;

	vectorPtr->capacity = initSize > 1? initSize : 1;
	vectorPtr->size = 0;
	vectorPtr->elements = (int*) can_fail_malloc(sizeof(int)*vectorPtr->capacity);
	if (vectorPtr->elements == NULL) {
		free(vectorPtr);
		return NULL;
	}

	return vectorPtr;
}

/*Function: vectorFree..........................................................
	Frees the vector given but not its elements.	
	Input:	> vector to be freed
	Output: None
..............................................................................*/
void vectorFree(Vector vectorPtr) {
	free(vectorPtr->elements);
	free(vectorPtr);
}


/*Function: vectorIndexAt.......................................................
	Gets the element at index specified.
	Input:	> vector
			> index of the element wanted
	Output: element of the vector
..............................................................................*/
int vectorIndexAt(Vector vectorPtr, int index) {
	if (index < 0 || index >= vectorPtr->size)
		return 0;

	return vectorPtr->elements[index];
}

/*Function: vectorPush..........................................................
	Inserts a new element in the vector. If the size of the vector is reached
	then the vector is reallocated with two times its current limit.
	Input:	> vector
			> index of the element to be pushed
	Output: 1 in case of success, 0 otherwise
..............................................................................*/
int vectorPush(Vector vectorPtr, int element) {
	if (vectorPtr->size == vectorPtr->capacity) {
		int* tmp = (int*) can_fail_realloc(vectorPtr->elements, sizeof(int)*2*vectorPtr->capacity);
		if (tmp == NULL)
			return 0;

		vectorPtr->elements = tmp;
		vectorPtr->capacity = vectorPtr->capacity * 2;
	}

	vectorPtr->elements[(vectorPtr->size)++] = element;
	return 1;
}

/*Function: vectorPop...........................................................
	Removes and returns the last inserted element.
	Input:	> vector
	Output: number stored at the last position of the vector
..............................................................................*/
int vectorPop(Vector vectorPtr) {
	if (vectorPtr->size == 0)
		return 0;

	return vectorPtr->elements[--(vectorPtr->size)];
}

/*Function: vectorSize..........................................................
	Returns the size of the vector.	
	Input:	> vector
	Output: current size of the vector
..............................................................................*/
int vectorSize(Vector v) {
	return v->size;
}


/*==============================================================================
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Vertex >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
==============================================================================*/


/*Function: vertexInit..........................................................
	Creates a new vertex with the number given.	
	Input:	> number of the vertex
	Output: Vertex created
..............................................................................*/
Vertex vertexInit(int n) {
	Vertex v = (Vertex) can_fail_malloc(sizeof(struct vertex));
	if (v == NULL)
		return NULL;
	v->connections = vectorInit(-1);
	if (v->connections == NULL) {
		free(v);
		return NULL;
	}
	v->visits = 0;
	v->time = 0;
	v->parent = NULL;

	return v;
}

/*Function: vertexFree..........................................................
	Frees a vertex.
	Input:	> Vertex to be freed.
	Output: None
..............................................................................*/
void vertexFree(Vertex v) {
	vectorFree(v->connections);
	free(v);
}

/*Function: vertexAddVisit......................................................
	Adds a visit to a vertex.
	Input:	> Vertex
	Output: None
..............................................................................*/
void vertexAddVisit(Vertex v) {
	(v->visits)++;
}

/*Function: vertexVisited.......................................................
	Adds a visit to a vertex.
	Input:	> Vertex
	Output: True if visited False otherwise
..............................................................................*/
int vertexVisited(Vertex v) {
	return v->visits != 0;
}

/*Function: vertexVisitCount....................................................
	Returns the number of visits of the vertex.
	Input:	> Vertex
	Output: Number of visits
..............................................................................*/
int vertexVisitCount(Vertex v) {
	return v->visits;
}

/*Function: vertexSetTime.......................................................
	Sets a time of a vertex to the time given.
	Input:	> Vertex
			> Time to be set
	Output: None
..............................................................................*/
void vertexSetTime(Vertex v, int t) {
	v->time = t;
}

/*Function: vertexGetTime.......................................................
	Gets the time of a vertex.
	Input:	> Vertex
	Output: Time of the vertex
..............................................................................*/
int vertexGetTime(Vertex v) {
	return v->time;
}

/*Function: vertexGetLow........................................................
	Gets the low of a vertex.
	Input:	> Vertex
	Output: Low of the vertex
..............................................................................*/
int vertexGetLow(Vertex v){
	return v->low;
}

/*Function: vertexSetLow........................................................
	Sets the low of a vertex to the time given.
	Input:	> Vertex
	Output: None
..............................................................................*/
void vertexSetLow(Vertex v, int t){
	v->low = t;
}

/*Function: vertexSetParent.....................................................
	Sets the parent of a vertex to the vertex given.
	Input:	> Vertex
			> Parent to be set
	Output: None
..............................................................................*/
void vertexSetParent(Vertex v, Vertex p) {
	if (v == p)
		return;
	v->parent = p;
}

/*Function: vertexGetParent.....................................................
	Gets the parent of a vertex.
	Input:	> Vertex
	Output: vertex of the parent
..............................................................................*/
Vertex vertexGetParent(Vertex v) {
	return v->parent;
}

/*Function: vertexHasParent.....................................................
	Checks if a vertex has a parent or not.
		Input:	> Vertex
	Output: True if the vertex has a parent, False if not
..............................................................................*/
int vertexHasParent(Vertex v){
	if (v->parent != NULL)
		return 1;
	return 0;
}

/*Function: vertexAddConnection.................................................
	Adds a connection to the vertex.
		Input:	> Vertex
				> number of the vertex to be connected
	Output: None
..............................................................................*/
void vertexAddConnection(Vertex v, int n) {
	vectorPush(v->connections, n);
}

/*Function: vertexGetConnections................................................
	Gets the connections of a vertex.
		Input:	> Vertex
	Output: Vector of the connections of the vertex
..............................................................................*/
Vector vertexGetConnections(Vertex v) {
	return v->connections;
}


/*==============================================================================
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Graph >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
==============================================================================*/

/*Function: graphInit...........................................................
	Creates a new graph with the number of vertices given.
		Input:	> Number of vertices
	Output: Graph created
..............................................................................*/
Graph graphInit(int v) {
	Graph g;
	int i, j;
	if (v < 2)
		return NULL;

	g = (Graph) can_fail_malloc(sizeof(struct graph));
	if (g == NULL)
		return NULL;

	g->vertices = (Vertex*) can_fail_malloc(sizeof(Vertex)*v);
	if (g->vertices == NULL) {
		free(g);
		return NULL;
	}

	for (i = 0; i < v; ++i) {
		(g->vertices)[i] = vertexInit(i+1);
		if ((g->vertices)[i] == NULL) {
			for (j = 0; j < i; ++j)
				vertexFree((g->vertices)[j]);
			free(g->vertices);
			free(g);
			return NULL;
		}
	}
	g->size = v;
	return g;
}


/*Function: graphFree...........................................................
	Frees a graph.
		Input:	> Graph to be freed
	Output: None
..............................................................................*/
void graphFree(Graph g) {
	int i;
	for (i = 0; i < g->size; ++i)
		vertexFree((g->vertices)[i]);

	free(g->vertices);
	free(g);
}

/*Function: graphGetVertex......................................................
	Gets the vertex of number n.
		Input:	> Graph
				> Number of the vertex
	Output: Vertex wanted
..............................................................................*/
Vertex graphGetVertex(Graph g, int n) {
	if (g == NULL || n < 1 || n > g->size)
		return NULL;

	return (g->vertices)[n-1];
}

/*Function: graphSize...........................................................
	Returns the number of vertices of the graph.
		Input:	> Graph
	Output: Size of the graph
..............................................................................*/
int graphSize(Graph g) {
	return g->size;
}

/*Function: graphConnect........................................................
	Adds a bidirectional connection between vertex n1 and n2.
		Input:	> Graph
				> Number of the first vertex
				> Number of the second vertex
	Output: Returns 1 in case of success, 0 otherwise
..............................................................................*/
int graphConnect(Graph g, int n1, int n2) {
	if (n1 == n2 || n1 < 1 || n2 < 1 || n1 > g->size || n2 > g->size)
		return 0;

	vertexAddConnection((g->vertices)[n1-1], n2);
	vertexAddConnection((g->vertices)[n2-1], n1);

	return 1;
}


/*==============================================================================
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Networks >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
==============================================================================*/


/*Function: errorFound..........................................................
	Prints the error message given and exits with error.
		Input:	> Message to be printed
	Output: None
..............................................................................*/
void errorFound(const char* message) {
	printf("%s", message);
	exit(1);
}

/*Function: readInput...........................................................
	Reads the input and returns a graph of the input on success.
		Input:	> None
	Output: Graph representing the input
..............................................................................*/
Graph readInput() {
	int nrouters, nconnects, u, v, i=0;
	Graph g;

	if (scanf("%d", &nrouters) < 0)
		errorFound("error reading input\n");
	if (nrouters < 2)
		errorFound("Number of routers needs to be at least 2\n");
	if (scanf("%d", &nconnects) < 0)
		errorFound("error reading input\n");
	if (nconnects < 1)
		errorFound("Number of connections needs to be at least 1\n");

	g = graphInit(nrouters);
	if (g == NULL)
		errorFound("Error creating graph\n");

	for (i = 0; i < nconnects; ++i) {
		if (scanf("%d %d", &u, &v) < 0)
			errorFound("error reading input\n");
		if (graphConnect(g, u, v) == 0)
			errorFound("Invalid connection\n");
	}
	return g;
}


/*Function: calcArtPoints.......................................................
	Calculates the articulation points of a graph.
		Input:	> Graph
				> Current vertex
				> Pointer to current time
				> Pointer to counter of articulation points
	Output: None
..............................................................................*/
void calcArtPoints(Graph g, Vertex v, int *t, int *artPoints) {
	int n, i, children = 0;
	Vertex u;
	Vector vertices = vertexGetConnections(v);
	vertexSetTime(v,(*t));
	vertexSetLow(v,(*t)++);
	vertexAddVisit(v);

	for (i = 0; i < vectorSize(vertices); ++i) {
		n = vectorIndexAt(vertices, i);
		u = graphGetVertex(g, n);
		if (!vertexVisited(u)) {
			children++;
			vertexSetParent(u,v);
			calcArtPoints(g, u, t, artPoints);

			if (vertexGetLow(v) > vertexGetLow(u))
				vertexSetLow(v, vertexGetLow(u));

			if ( vertexVisitCount(v) == 1 && ((!vertexHasParent(v) && children > 1) ||
				(vertexHasParent(v) && vertexGetLow(u) >= vertexGetTime(v))) ) {
					(*artPoints)++;
					vertexAddVisit(v);
			}

		} else if(u != vertexGetParent(v)){
			if (vertexGetLow(v) > vertexGetTime(u))
				vertexSetLow(v, vertexGetTime(u));
		}
	}
}


/*Function: calcSize............................................................
	Calculates the size of a subgraph.
		Input:	> Graph
				> Current vertex
	Output: Size of the subgraph
..............................................................................*/
int calcSize(Graph g, Vertex v) {
	int n, i, size=1;
	Vertex u;
	Vector vertices = vertexGetConnections(v);
	vertexAddVisit(v);
	for (i = 0; i < vectorSize(vertices); ++i) {
		n = vectorIndexAt(vertices, i);
		u = graphGetVertex(g, n);
		if (vertexVisitCount(u) == 1) {
			/*is not articulation point and is the first visit by calcSize*/
			size += calcSize(g, u);
		}
	}

	return size;
}


/*Function: networkAnalysis.....................................................
	Analyses the graph given.
		Input:	> Graph
				> Pointer to number of articulation points
				> Pointer to number of vertices of the highest subgraph
	Output: Vector of the roots of the graph
..............................................................................*/
Vector networkAnalysis(Graph g, int *artPoints, int *maxTree) {
	int n, t = 1, size;
	Vertex v;
	Vector trees = vectorInit(-1);
	if (trees == NULL)
		errorFound("Error creating vector\n");

	/*identify trees and articulation points*/
	for (n = graphSize(g); n > 0; --n) {
		v = graphGetVertex(g, n);
		if (!vertexVisited(v)) {
			vectorPush(trees, n);
			calcArtPoints(g, v, &t, artPoints);
		}
	}

	/*calculate biggest tree after removing all articulation points*/
	for (n = graphSize(g); n > 0; --n) {
		v = graphGetVertex(g, n);
		if (vertexVisitCount(v) == 1) {
			/*is not articulation point and is the first visit by calcSize*/
			size = calcSize(g, v);
			if (size > *maxTree)
				*maxTree = size;
		}
	}

	return trees;
}

/*Function: printOutput.........................................................
	Prints the output of the program.
		Input:	> Vector of the roots of the subgraphs
				> Number of articulation points of the graph
				> Number of the size of the highest subgraph without 
					articulation
	Output: None
..............................................................................*/
void printOutput(Vector trees, int artPoints, int maxTree) {

	printf("%d\n", vectorSize(trees));

	printf("%d", vectorPop(trees));
	while(vectorSize(trees) != 0) {
		printf(" %d", vectorPop(trees));
	}
	printf("\n%d\n%d\n", artPoints, maxTree);
}


int main(int argc, char const *argv[]) {
	Graph g = readInput();
	int artPoints=0, maxTree=0;
	Vector trees = networkAnalysis(g, &artPoints, &maxTree);
	
	printOutput(trees, artPoints, maxTree);

	vectorFree(trees);
	graphFree(g);

	return 0;
}