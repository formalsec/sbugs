/* GRUPO 22 - LEIC-T */
/* Monica Alves 90759 */
/* Joao Galamba 90735 */


#include <stdio.h>
#include <stdlib.h>

#define NIL -1
/* returns the lowest argument given */
#define min(a, b) (((a) < (b)) ? (a) : (b))

typedef enum { false, true } bool;

/* structers */

/* connection structer: Has a number for each node with connection (n) and a pointer for the next connection (next) */
typedef struct connection{
	int n;
	int* next;
} connection;

/* Auxiliar function used for sorting lists */
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

/* Auxiliar function that calculates the articulation points in the graph, number of nodes (size) in a network	*/
/* (or sub-network).																							*/
/* Arguments: u : is the node's index where the function is going to begin the search 							*/
/*			  visited : is a vector of booleans that contains wether each node has been visited before or not   */
/*			  disc : is a vector of integers that contains the time of discovery of each node					*/
/* 			  low : is a vector of integers that contains the lows of each nodes 								*/
/*			  parent : is a vector of integers that contains the parent of each node of the graph 				*/
/* 			  artpoint : is a vector of booleans that contains whether each node is a articulation point or not */
/*			  nodes : is a pointer to a vector of connections for each node of the graph			 			*/
/*			  time : is a pointer to an integer that indicates the time when the node was discovered		 	*/
/* 	 		  size : is a pointer to an integer that indicates the graph's size 								*/
/* Returns an integer (max) that indicates the number of nodes in the network (or sub-network)					*/	
int artPoints(int u, bool visited[], int disc[], int low[], int parent[], bool artpoint[], connection* nodes,int* time,int *size)
{	
	int max = u + 1;
	int children = 0;
	int index;

	(*size)++;
	visited[u] = true;
	disc[u] = low[u] = ++(*time);

	/* goes through each node of the graph searching for the articulation points */
	for (index = 0; index < nodes[u].n; index++)
	{
		int v = nodes[u].next[index];

		if (visited[v] == false && artpoint[v] == false)
		{
			children++;
			parent[v] = u;
			int m = artPoints(v, visited, disc, low, parent, artpoint,nodes,time,size);
			if (m > max)
			{
				max = m;
			}

			low[u] = min(low[u],low[v]);

			if (parent[u] == NIL && children > 1){
				artpoint[u] = true;
			}

			if (parent[u] != NIL && low[v] >= disc[u]){
				artpoint[u] = true;
			}
		}

		else if (v != parent[u])
		{
			low[u] = min(low[u], disc[v]);
		}
	}

	return max;
}  


int main ()
{
	/* initializations */
	connection* nodes;
	int numNodes;
	int numConnec;
	int i, index = 0;
	int origin, dest;
	int time = 0;
	int subs = 0;
	int size = 0;
	int size_aux = 0;
	
	/* error message in case the input is wrongly introduced */
	int err = scanf("%d", &numNodes);
	if (err == -1)
	{
		printf("Error occurred.\n");
	}
	err = scanf("%d", &numConnec);
	if (err == -1)
	{
		printf("Error occurred.\n");
	}
	
	/* allocates spaces for vector of connections */
	nodes = (connection*)malloc(sizeof(connection) * numNodes);
	for (i = 0; i < numNodes; i++)
	{
		nodes[i].n = 0;
		nodes[i].next = (int*) malloc (sizeof(int) * 0);
	}
	
	while (index < numConnec)
	{
		err = scanf("%d %d", &origin, &dest);
		/* error message in case the input is wrongly introduced */
		if (err == -1)
		{
			printf("Error occurred.\n");
		}

		origin--;
		dest--;
		int originConnections = ++(nodes[origin].n);
		nodes[origin].next = (int*) realloc (nodes[origin].next, sizeof(int) * originConnections);
		nodes[origin].next[originConnections - 1] = dest;
		int destConnections = ++(nodes[dest].n);
		nodes[dest].next = (int*) realloc (nodes[dest].next, sizeof(int) * destConnections);
		nodes[dest].next[destConnections - 1] = origin;
		index++;
	}
	
	bool* visited = (bool*) malloc (sizeof(bool) * (numNodes)); 
	int* disc = (int*) malloc (sizeof(int) * (numNodes)); 
	int* low = (int*) malloc (sizeof(int) * (numNodes)); 
	int* parent = (int*) malloc (sizeof(int) * (numNodes)); 
	bool* artpoint = (bool*) malloc(sizeof(bool) * (numNodes));
	int* subnetworks = (int*) malloc(sizeof(int) * 0);

	/* initializes the vectors of each nodes */
	for (i=0; i < numNodes; i++)
	{
		parent[i] = NIL;
		visited[i] = false;
		artpoint[i] = false;
	}
	
	/* goes through the graph and searches the articulation points with the auxiliar function : artPoints*/
	for (i = 0; i < numNodes; i++)
	{
		if (visited[i] == false) 
		{
			int max = artPoints(i,visited,disc,low,parent,artpoint,nodes,&time,&size);
			subs++;
			subnetworks = realloc(subnetworks, sizeof(int) * subs);
			subnetworks[subs - 1] = max;
		}
	}
	
	printf("%d\n", subs); /* Prints the number of subnetworks found in the graph */ 
	
	/* Sorts the numbers returned by the function artPoints and prints them */
	qsort(subnetworks, subs, sizeof(int), cmpfunc); 

	printf("%d", subnetworks[0]);
	for (i = 1; i < subs; i++)
	{
		printf(" %d", subnetworks[i]);
	}
	printf("\n");

	/* Variable that contains number of articulation points in the graph */
	int numAPoints=0;
	/* Using the vector of artpoint counts the number of articulation points in the graph */
	for (i=0; i<numNodes; i++){
		if (artpoint[i]==true){
			numAPoints++;
		}
	}
	printf("%d\n", numAPoints);

	/* re-initializes the vectors of each node in the graphs */
	for (i=0; i < numNodes; i++){
		parent[i] = NIL;
		visited[i] = false;
	}

	/* Goes through the graph ignoring the articulation points in order to search the number
	   of sub-networks created when 'removing' the articulation points					 */
	time = 0;
	for (i=0; i<numNodes; i++)
	{
		if (artpoint[i] == false && visited[i] == false)
		{
			size=0;
			artPoints(i,visited,disc,low,parent,artpoint,nodes,&time, &size);
			if (size_aux < size)
			{
				size_aux = size;
			}
		}
	}
	/* prints last output */
	printf("%d\n",size_aux);

	free(visited);
	free(disc);
	free(low);
	free(parent);
	free(artpoint);
	for (i = 0; i < numNodes; i++)
	{
		free(nodes[i].next);
	}
	free(nodes);

	exit(0);
}