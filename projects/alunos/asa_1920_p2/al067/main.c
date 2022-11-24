#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/*
 * File:	main.c
 * 
 * Author:	André Nascimento	92419
 * Author:	Francisco Malveiro	92465	
 * 
 * Serial: 	110520201247
 * 
 * A small algorithm to calculate the maximum ammount of citizens that can go 
 * out shopping without crossing paths with one another.
 */



/*============================================================================*/
/*				Include directives			                                  */
/*============================================================================*/
#include <stdlib.h>
#include <stdio.h>



/*============================================================================*/
/*			File macros and constants			                              */
/*============================================================================*/

/* Allows the usage of the TRUE and FALSE keywords. */
#define TRUE 	1
#define FALSE 	0

/* The source index on the network array. */
#define SOURCE	0

/* Augmenting paths. */
#define PATH_NOT_FOUND -1





/*============================================================================*/
/* 			Linked list declaration		                                      */
/*============================================================================*/

/* Node structure - Each node contains an element of the list. */
typedef struct node {

	void *element;			/* The element stored on each node of the list. */
	struct node *next;		/* The next element of the list. */

} Node;


/* List structure - The list contains the first and the last node. */
typedef struct list {

	Node *head;		/* The first element of the list. */
	Node *tail;		/* The last element of the list. */

} *List;



/*! \brief Creates a new node.
 *
 *  Creates a new node with the specified data and returns its pointer.
 *
 * 	\param 	Element		The element to be stored in the node.
 *	\return 			The node's pointer.
 */
Node *nodeCreate(void *element);


/*! \brief Destroys a node.
 *
 *  Destroys the node given as argument and frees all the memory associated 
 *  with it.
 *
 * 	\param 	node		The node to destroy.
 * 	\return The element previously associated with the node.
 */
void* nodeDestroy(Node *node);


/*! \brief Creates a new list.
 *
 *  Allocates a new list in memory.
 *
 * 	\return A pointer to the created list.
 */
List listCreate();


/*! \brief Destroys a list.
 *
 *  Destroys the list given as argument and frees all the memory associated 
 *  with it.
 *
 * 	\param 	list		The list to be destroyed.
 *  \param  freeElement	A function to delete the element (optional).
 */
void listDestroy(List list, void (*freeElement)(void*));


/*! \brief Inserts a new element at the end of a list.
 *
 *  Creates a new node for the specified element and places it at the end of 
 *  the list. Note: linear time function - the pushFront method should be 
 *  preferred.
 *
 * 	\param 	list 		The list in which to insert the element.
 * 	\param  element		The element to be inserted.
 */
void listPushBack(List list, void *element);


/*! \brief Inserts a new element at the beggining of a list.
 *
 *  Creates a new node for the specified element and places it at the front of 
 *  the list.
 *
 * 	\param  list		The list in which to insert the element. 					
 * 	\param  element		The element to be inserted. 		
 */
void listPushFront(List list, void *element);


/*! \brief Removes the last element of a list.
 *
 *  Removes the last node of a given list, returning the element stored in it.
 *
 * 	\param 	list		The list from which to remove the element.
 * 	\return The element contained in the removed node.
 */
void* listPopBack(List list);


/*! \brief Removes the first element of a list.
 *
 *  Removes the first node of a given list, returning the element stored in it.
 *
 * \param  list			The list from which to remove the element.
 * \return The element contained in the removed node.
 */
void* listPopFront(List list);


/*! \brief Returns an iterator to a list.
 *
 *  Returns the first node of a list that can then be with iterated with the 
 *  «next» pointer.
 *
 * 	\param 	list		The list whose iterator is going to be returned.
 * 	\return The list's iterator.
 */
Node* listIterator(List list);





/*============================================================================*/
/* 			Network's components declaration	         	                  */
/*============================================================================*/

/* A vertex is a list containing its outgoing edges. */
typedef List Vertex;

/* The structure that represents an edge of the graph. */
typedef struct edge {

	Vertex *orig;				/* The vertex where the edge starts. */
	Vertex *dest;				/* The vertex where the edge ends. */
	struct edge *residual;			/* The opposite edge in the residual graph. */
	int capacity;				/* The ammount of flow that can still pass. */

} Edge;


/* The structure that represents the city network. */
typedef struct network {
	
	Vertex *vertices;			/* An array with the vertices of the network. */
	int nVertices;				/* The number of vertices of the network. */
	int nAvenues;				/* The number of avenues of the network. */
	int nStreets;				/* The number of streets of the network. */
	int nSupermarkets;			/* The number of supermarkets of the network. */
	int nHouses;				/* The number of houses of the network. */

} Network;


/** \brief Creates a new edge.
 * 
 * 	Allocates in memory and initializes a new edge with the capacity and destiny
 * 	specified.
 * 
 *  \param 	orig
 * 	\param 	dest		The index of the vertex where the edge ends.
 * 	\param 	capacity			The capacity of the edge.
 *  \return A pointer to the edge.
 */
Edge* createEdge(Vertex *orig, Vertex *dest, int capacity);


/** \brief Destroys an edge.
 * 
 * Destroys the specified edge and frees all the memory associated with it.
 * 
 *  \param edge					The edge to be destroyed:
 * 								 - void to be used on the list.
 */
void destroyEdge(void *edge);





/*============================================================================*/
/* 			Linked-list implementation		                                  */
/*============================================================================*/

/* Creates a new node. */
Node* nodeCreate(void *element) {
	Node *node = (Node*) can_fail_malloc(sizeof(Node));
	node->element = element;
	node->next = NULL;
	return node;
}


/* Destroys a node. */
void *nodeDestroy(Node *node) {
	void *element = node->element;
	free(node);
	return element;
}


/* Creates a new list. */
List listCreate() {
	List list = (List) can_fail_malloc(sizeof(struct list));
	list -> head = NULL;
	list -> tail = NULL;
	return list;
}


/* Destroys a list. */
void listDestroy(List list, void (*freeElement)(void*)) {	
	Node *iterator = listIterator(list);
	while ((iterator = list->head) != NULL)	{
		list->head = iterator->next;
		/* destroys the element stored if a function was specified */
		if (freeElement != NULL)
			freeElement(nodeDestroy(iterator));
		else
			nodeDestroy(iterator);
	}
	
	free(list);
}


/* Inserts a new element at the end of the list. */
void listPushBack(List list, void *element) {
	Node *node = nodeCreate(element);
	if (list->head == NULL) 
		list->head = node;
	else
		list->tail->next = node;
	
	list->tail = node;
}


/* Inserts a new element at the beggining of the list. */
void listPushFront(List list, void *element) {
	Node *node = nodeCreate(element);
	if (list->head == NULL) 
		list->tail = node;
	else
		node->next = list->head;

	list->head = node;
}


/* Removes the last element of the list. */
void* listPopBack(List list) {
	Node *temp, *iterator;

	/* empty list */
	if (list->head == NULL)										
		return NULL;
		
	temp = list->tail;
	iterator = listIterator(list);

	/* list empty after the removal of the last element */
	if (iterator->next == NULL)	{
		list->head = NULL;
		list->tail = NULL;
	}
	else {
		/* gets the element before the last (linear time) */
		while (iterator->next != list->tail)	
			iterator = iterator->next;
		
		iterator->next = NULL;
		list->tail = iterator;
	}
	
	return nodeDestroy(temp);
}

/* Removes the first element of the list. */
void* listPopFront(List list) {
	Node *temp;

	/* empty list */
	if (list->head == NULL)										
		return NULL;

	temp = list->head;
	list->head = temp->next;
	list->tail = (list->head == NULL ? NULL : list->tail);
	return nodeDestroy(temp);
}


/* Removes an iterator to the list. */
Node* listIterator(List list) {
	return list->head;
}


int listEmpty(List list)
{
	return list->head == NULL;
}



/*============================================================================*/
/* 			Graph's components implementation         		                  */
/*============================================================================*/

/* Creates a new edge. */
Edge* createEdge(Vertex *orig, Vertex *dest, int capacity) {
	Edge *edge = (Edge*) can_fail_malloc(sizeof(Edge));
	edge->orig = orig;
	edge->dest = dest;
	edge->capacity = capacity;
	return edge;
} 


/* Destoys an edge. */
void destroyEdge(void *edge) {
	free(edge);
}





/*============================================================================*/
/*			Program basic functionality			      						  */
/*============================================================================*/


/*! \brief Calculates the index of a building.
 *
 *  Calculates the index of a building (input vertex) from the specified
 * 	intersection between an avenue and street.
 *
 * \param  avenue 				The avenue of the building.
 * \param  street 				The street of the building.
 * \param  nStreets				The number of streets that cross each avenue.
 * \return The input vertex of a building.
 */
int buildingIndex(int avenue, int street, int nStreets) {
	return 2 * ((avenue - 1) * nStreets + street) - 1;
}


/** \brief Returns the position on the network of a supermarket / house.
 * 
 * 	Reads the position (avenue & street) of the supermarket / house from the 
 * 	input file and returns the index of its input vertex on the network.
 * 
 * 	\param 	nStreets			The number of streets on each avenue on the city.
 * 	\return The input vertex's index on the network.
 */
int getBuildingIndex(int nStreets) 
{
	int avenue, street;
	scanf("%d %d", &avenue, &street);
	return buildingIndex(avenue, street, nStreets);
}


/** \brief Creates an edge on the residual network.
 * 
 *  Creates an edge on the residual network and the respective counterpart with
 * 	the capacity set to 0.
 * 
 *  \param 	orig					The starting vertex of the edge.
 * 	\param	dest					The ending vertex of the edge.
 *  \param 	capacity				The capacity of the main edge
 */
void createResidualEdge(Vertex *orig, Vertex *dest, int capacity) {
	Edge *mainEdge = createEdge(orig, dest, capacity);
	Edge *resEdge  = createEdge(dest, orig, 0);
	mainEdge->residual = resEdge;
	resEdge->residual = mainEdge;
	listPushFront(*orig, mainEdge);
	listPushFront(*dest, resEdge);
}


/** \brief Initialises the graph that represents the city.
 * 
 * 	The network is an array of vertices, each containing a list of outgoing 
 * 	edges. Each vertex contains 4 adjacent vertices with the exception of 
 * 	the border ones.
 * 
 * 	\param 	network				The network to be initialised.
 */
void initialiseCityNetwork(Network *network) {
	int i, avenue, street, origI, destI, nVertices, nAvenues, nStreets;
/*	int origIminusTwo, origIplusTwo;*/
	Vertex *v = network->vertices;

	nVertices = network->nVertices;
	nAvenues = network->nAvenues;
	nStreets = network->nStreets;


	/* initialises a list for every vertex of the network */
	for (i = 0; i < nVertices; i++)
		v[i] = listCreate();

	/* initialises the middle vertices */
	for (avenue = 1; avenue <= nAvenues; avenue++)
		for (street = 1; street <= nStreets; street++) {
			origI = buildingIndex(avenue, street, nStreets);
			destI = origI + 1;
/*			origIminusTwo = origI - 2;
			origIplusTwo = origI + 2;*/

			/* initialises the input vertex */
			createResidualEdge(&v[origI], &v[destI], 1);

			/* initialises the output vertex */
			if (avenue > 1)
				createResidualEdge(&v[destI], &v[origI - 2 * nStreets], 1);
/*				createResidualEdge(&v[destI], &v[origIminusTwo* nStreets], 1);*/	
			if (avenue < nAvenues)/* if (avenue < network->nAvenues)*/
				createResidualEdge(&v[destI], &v[origI + 2 * nStreets], 1);
/*				createResidualEdge(&v[destI], &v[origIplusTwo* nStreets], 1);*/
			if (street > 1)
				createResidualEdge(&v[destI], &v[origI - 2], 1);
/*				createResidualEdge(&v[destI], &v[origIminusTwo], 1);*/
			if (street < nStreets)/* if (street < network -> nStreets)*/
				createResidualEdge(&v[destI], &v[origI + 2], 1);
/*				createResidualEdge(&v[destI], &v[origIplusTwo], 1);*/
					
		}
}


/*! \brief Destoys the network representing the city.
 *
 *	Destoys the network and frees all the memory associated with it.
 *
 * 	\param  network 			The network to be destroyed.
 */
void destroyCityNetwork(Network *network)
{
	int i, nVertices;
	Vertex *vertices;

	nVertices = network->nVertices;
	vertices = network->vertices;

	for (i = 0; i < nVertices; i++) {
/*		listDestroy(network->vertices[i], destroyEdge);*/
		listDestroy(vertices[i], destroyEdge);
	}
	free(vertices);
/*	free(network->vertices);*/
}


/* the source/target is always added on top */
int connected(Vertex *reference, Vertex *v)
{
	Node *iterator = listIterator(*v);
	Edge* edge;
	if (iterator != NULL)	{	
		edge = (Edge*) iterator->element;
		return reference == edge->dest;
	} else {
		return 0;
	}
}




/*! \brief Reads the input file.
 *
 *  The input file is read and its data is stored on a graph representing a flow
 * 	network.
 * 
 * 	\param network				The network that will represent the problem
 */
void processInput(Network *network)
{
	int i, nSupermarkets, nHouses, nStreets, nAvenues, nVertices;
	Vertex* v;

	Vertex *source, *target, *current;


	/* initialises the main network */
	scanf("%d %d", &network->nAvenues, &network->nStreets);
	scanf("%d %d", &network->nSupermarkets, &network->nHouses);	
	/*scanf("%d %d", &nAvenues, &nStreets);
	scanf("%d %d", &nSupermarkets, &nHouses);*/

	nAvenues = network->nAvenues;
	nStreets = network->nStreets;
/*	network->nVertices = 2 * (network->nAvenues * network->nStreets) + 2;*/

	/* v -> in and v -> out for each grid vertex + source + target */
	network->nVertices = 2 * (nAvenues * nStreets) + 2;
	network->vertices = (Vertex*) can_fail_malloc(network->nVertices * sizeof(Vertex));

	/*network->nAvenues = nAvenues;
	network->nStreets = nStreets;*/

	nVertices = network->nVertices;

	initialiseCityNetwork(network);
/*	v = network->vertices;*/


	source = v = network->vertices;
	target = &v[nVertices-1];

	nSupermarkets = network->nSupermarkets;
	nHouses = network -> nHouses;


	/* adds the supermarkets to the network */
	for (i = 0; i < nSupermarkets; i++) {
/*	attempt1	createResidualEdge(&v[getBuildingIndex(network->nStreets) + 1], 
						   &v[network->nVertices - 1], 1);*/

/*	attempt2	createResidualEdge(&v[getBuildingIndex(nStreets) + 1], 
				&v[nVertices - 1], 1);*/



/* working	createResidualEdge(&v[getBuildingIndex(nStreets) + 1], 
				target, 1);*/
	


	current = &v[getBuildingIndex(nStreets) + 1];
	if (!connected(target, current)) {
		
		createResidualEdge(current, 
				target, 1);
	}

	}

	/* adds the houses to the network */
	for (i = 0; i < nHouses; i++) {
		/*attempt1createResidualEdge(v, &v[getBuildingIndex(network->nStreets)], 1);*/
/* attempt2		createResidualEdge(v, &v[getBuildingIndex(nStreets)], 1);*/

/*	working		createResidualEdge(source, &v[getBuildingIndex(nStreets)], 1);*/


		current = &v[getBuildingIndex(nStreets)];
		if (!connected(source, current)) {
			createResidualEdge(source, current, 1);
			
		}
	}
}






/** \brief Calculates the index of a vertex of the network.
 * 
 * 	Uses the value of the pointer of a vertex to calculate its index on the 
 * 	vertices array of the network.
 * 
 * 	\param 	network				The network where the vertex is stored.
 * 	\param 	vertex				The pointer to the vertex.
 * 	\return The index of the vertex in the network's vertices array.
 */
int getVertexIndex(const Network *network, const Vertex *vertex) {
	return vertex - network->vertices;
}


/** \brief Finds the shortest path between 2 vertices.
 * 
 * 	Applies a Breath First Search to a graph (array of vertexes each containing 
 * 	a list of edges), to find the shortes path between the specified vertices.
 * 
 * 	\param 	network				The graph where the BFS will be applied:
 * 								 - struct contains the size of the graph.
 *  \param 	orig				The starting vertex of the search.
 * 	\param	dest				The ending vertex of the search.
 * 	\param 	path				The array containing the paths of the BFS.
 * 	\return True if the the destination was reach, false otherwise.
 */
int bfsPath(Network *network, Vertex *orig, Vertex *dest, Edge **path) {
	int i, nVertices;
 	List queue = listCreate();				/* queue implemented as a list */
	Vertex *currentVertex;
	Node *iterator;
	Edge *edge;
	
	nVertices = network->nVertices;


	for (i = 0; i < nVertices; i++)
		path[i] = NULL;

	/* enqueue source */
 	listPushBack(queue, orig);
 	
	while (!listEmpty(queue)) { 	
 		currentVertex = (Vertex*) listPopFront(queue);
		
		/* checks if we reached the last vertex */
		if (currentVertex == dest)
			break;

		/* iterates through the adjancent edges and enqueues them */	
		iterator = listIterator(*currentVertex);
		while (iterator != NULL) {
			edge = (Edge*) iterator->element;
			i = getVertexIndex(network, edge->dest);
			if (edge->capacity != 0 && path[i] == NULL && i != SOURCE) {
				path[i] = edge;
				listPushBack(queue, edge->dest);
			}
			iterator = iterator->next;
		}
	}
	
	
	/* stores the size of the shortest path and returns it to the user */	
	listDestroy(queue, NULL);
 	return (path[nVertices - 1] != NULL ? TRUE : FALSE);
}


/** \brief Increases the flow of an augmenting path.
 * 
 * 	Increases the flow on the specified path by 1 (maximum allowed by the 
 * 	problem)
 * 
 * 	\param 	network				The network where the flow will be calculated.
 * 	\param 	path				The array containing the paths.
 */
void increaseFlow(Network *network, Edge **pi) {
	Edge *edge = pi[network->nVertices - 1];
	while (edge != NULL) {
		edge->capacity = 0;
		edge->residual->capacity = 1;
		edge = pi[getVertexIndex(network, edge->orig)];
	}
}


/** \brief Finds one augmenting path on the residual network.
 * 
 * 	The path is found using a BFS in order to find the shortest path from the
 * 	source to the sink of the residual network.
 * 	The memory for the outpath will be allocated by BFS and it should be freed
 * 	by the user after being used.
 * 
 * 	\param 	network				The residual network.
 * 	\param 	path				The array containing the paths of the BFS.
 * 	\return True if the the destination was reach, false otherwise.
 */
int findAugmentingPath(Network *network, Edge **pi) {
 	return bfsPath(network, network->vertices, 
	 	&network->vertices[network->nVertices - 1], pi);
}


/** \brief Calculates the maximum flow of a network.
 * 
 * 	Calculates the maximum flow of a network and returns it.
 * 
 * 	\param 	network				The network where the flow will be calculated.
 *  \return The maximum flow of the network.
 * 
*/
int edmondsKarp(Network *network) {
	int maxFlow = 0, nSupermarkets, nHouses;
	Edge **path = (Edge **) can_fail_malloc(network->nVertices * sizeof(Edge*));
	
	nSupermarkets = network->nSupermarkets, nHouses = network->nHouses;

	while (maxFlow < nSupermarkets && maxFlow < nHouses && 
		findAugmentingPath(network, path)) {

		increaseFlow(network, path);		
		maxFlow++;
	}
	
	free(path);
	return maxFlow;
}





/*============================================================================*/
/*				main function				      							  */
/*============================================================================*/

int main() {
	Network network;
	processInput(&network);
	printf("%d\n", edmondsKarp(&network));
	destroyCityNetwork(&network);
	return 0;
}
