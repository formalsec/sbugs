/*
 * File: proj2ASA.c
 * Authors: João Vítor 99246, Rafael Maciel 100671
 * Description: ASA second project 2021/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STRING 100
#define INVALID_TREE "0\n"
#define NO_COMMON_ANCESTORS "-\n"
#define WHITE 0
#define GREY 1
#define BLACK 2

typedef struct {
    int id;
    int color;
    int parent1;
    int parent2;
} node;

node** readInput(int*, int*, int*);
node** initNodeList(int);
bool validTree(node**, int);
bool validNode(node**, int);
int lowestCommonAncestors(node**, int, int);
void paintToRoot(node**, int, int);
int findWhite(node**, int);
void printCommonAncestors(node**, int);


int main() {
    int id1;
    int id2;
    int nNodes;
    
    /*obtains the tree and the ids of the nodes to analyse */
    node** nodeList = readInput(&id1, &id2, &nNodes);
    
    /* checks if the tree is valid */
    if (nodeList == NULL || !validTree(nodeList, nNodes)) {
	printf(INVALID_TREE);
	return 0;
    }
    
    /* sets the color of the lowest common anscestors to GREY */
    if (!lowestCommonAncestors(nodeList, id1, id2)) {
	printf(NO_COMMON_ANCESTORS);
	return 0;
    }

    /* prints the id of GREY nodes */
    printCommonAncestors(nodeList, nNodes);

    return 0;
}


/* Reads a tree from stdin, registers the ids of the nodes to analyze
 * and returns an array of its nodes ordered by id */
node** readInput(int* id1, int* id2, int* nNodes) {
    /* reads the ids of the nodes to analyse */
    char line[MAX_STRING];
    fgets(line, MAX_STRING, stdin);
    if (sscanf(line, "%d %d", id1, id2) == EOF)
	return NULL;

    /* reads the number of nodes and edges in the tree */
    fgets(line, MAX_STRING, stdin);
    int nEdges;
    if (sscanf(line, "%d %d", nNodes, &nEdges) == EOF)
	return NULL;
    
    /* initializes the array of nodes */
    node** nodeList = initNodeList(*nNodes);
    
    /* reads which nodes are connected by edges */ 
    int parent;
    int child;
    for (; 0 < nEdges; nEdges--) {
	fgets(line, MAX_STRING, stdin);
	if (sscanf(line, "%d %d", &parent, &child) == EOF)
	    return NULL;
	node* childNode = nodeList[child - 1];
	if (childNode->parent1 == 0)
	    childNode->parent1 = parent;
	else if (childNode->parent2 == 0)
	    childNode->parent2 = parent;
	else
	    return NULL;
    }

    return nodeList;
}


/* Allocates memory, initializes and returns an array of nNodes nodes */ 
node** initNodeList(int nNodes) {
    node** nodeList = (node**) malloc(sizeof(node*) * nNodes);
    
    int i = 0;
    for (; i < nNodes; i++) {
	node* n = (node*) malloc(sizeof(node));
	n->id = i + 1;
	n->color = WHITE;
	n->parent1 = 0;
	n->parent2 = 0;
	nodeList[i] = n;
    }
    
    return nodeList;
}


/* Checks if the tree is valid by calling validNode for every node */
bool validTree(node** nodeList, int nNodes) {
    int i = 0;
    for (; i < nNodes; i++) {
	if (!validNode(nodeList, i))
	    return false;
    }

    return true;
}


/* Checks if a node is part of a loop returning false if it is
 * WHITE = unvisited
 * GREY = visited
 * BLACK = closed */
bool validNode(node** nodeList, int n) {
    node* currentNode = nodeList[n];
    
    /* sees if the node has already been closed */
    if (currentNode->color == BLACK)
	return true;
    
    /* marks the node as visited */
    currentNode->color = GREY;
    
    bool res = true;
    if (currentNode->parent1 != 0) {
	/* if the parent nodes are unvisited, calls itself for them */ 
	if (nodeList[currentNode->parent1 - 1]->color == WHITE)
	    res = res && validNode(nodeList, currentNode->parent1 - 1);
	/* if they have been visited but not closed, these nodes are part of a loop */
	else if (nodeList[currentNode->parent1 - 1]->color == GREY)
	    return false;
	if (currentNode->parent2 != 0) {
	    if (nodeList[currentNode->parent2 - 1]->color == WHITE)
		res = res && validNode(nodeList, currentNode->parent2 - 1);
	    else if (nodeList[currentNode->parent2 - 1]->color == GREY)
	        return false;
	}
    }
    
    /* marks the node as closed */
    currentNode->color = BLACK;
    
    return res;
}


/* Marks the lowest common ancestors of nodes id1 and id2 as GREY */
int lowestCommonAncestors(node** nodeList, int id1, int id2) {
    /* sets the color of the node with id1 and its ancestors to WHITE */
    nodeList[id1 - 1]->color = WHITE;
    paintToRoot(nodeList, id1, WHITE);

    /* checks the ancestors of the node with id2
     *marking the lowest common ones with id1 */
    return findWhite(nodeList, id2);
}


/* Sets the color of the ancestors of given node to given color */
void paintToRoot(node** nodeList, int id, int color) {
    node* currentNode = nodeList[id - 1];

    if (currentNode->parent1 != 0) {
	nodeList[currentNode->parent1 - 1]->color = color;
	paintToRoot(nodeList, currentNode->parent1, color);
	if (currentNode->parent2 != 0) {
	    nodeList[currentNode->parent2 - 1]->color = color;
	    paintToRoot(nodeList, currentNode->parent2, color);
	}
    }
}


/* Changes the color of the first WHITE node it finds in a path to GREY
 *and all its ancestors to BLACK. Returns the number of nodes it changed to GREY */
int findWhite(node** nodeList, int id) {
    node* currentNode = nodeList[id - 1];

    int res = 0;
    /* if the node is WHITE, changes color to GREY and ancestors to BLACK */
    if (currentNode->color == WHITE) {
	currentNode-> color = GREY;
	res++;
	paintToRoot(nodeList, id, BLACK);
    }
    /* else calls itself for the parent nodes */
    else if (currentNode->color == BLACK) {
	if (currentNode->parent1 != 0) {
	    res += findWhite(nodeList, currentNode->parent1);
	    if (currentNode->parent2 != 0)
		res += findWhite(nodeList, currentNode->parent2);
	}
    }

    return res;
}


/* Prints all GREY nodes. Frees all nodes in nodeList and the array itself */
void printCommonAncestors(node** nodeList, int size) {
    int i = 0;
    for (; i < size; i++) {
	node* currentNode = nodeList[i];
	if (currentNode->color == GREY)
	    printf("%d ", currentNode->id);
	free(currentNode);
    }
    printf("\n");
    free(nodeList);
}
