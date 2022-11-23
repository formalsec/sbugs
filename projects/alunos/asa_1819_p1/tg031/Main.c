#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define NIL -1
#define LINESIZE 30
#define TRUE 1
#define FALSE 0

typedef struct node{
	unsigned int value;
	struct node* next;
}* Node;

typedef struct vertex{
	Node adj;
	int parent;
	int startTime;
	int low;
	unsigned char ap : 1;
}* Vertex;

typedef struct graph{
	int numVertexes;
	int numEdges;
	Vertex* vertexList;
	Node idList;
	int C;
	int Max;
}* Graph;

Node newNode(int vertex, Node next);
Graph graphInit();
void addId(Graph g, int i);
void graphInsert(Vertex* vertexList, int vertex1, int vertex2);
void graphDebug(Graph graph);
void DFS(Vertex* vertexList, int numVertexes, Graph g, int* C);
void DFSAlgorythm(Vertex* vertexList, int i, int R, int* D, int* C);
void cutLength(Vertex* vertexLis, int f, int* max);
void deep(Vertex* vertexList, int* length, int node);
void listFree(Node n);
void VertexFree(Vertex v);
void graphFree(Graph g);

Node newNode(int value, Node next){
	Node new = (Node)can_fail_malloc(sizeof(struct node));
	new->value = value;
	new->next = next;
	return new;
}

Vertex newVertex(){
	Vertex new = (Vertex)can_fail_malloc(sizeof(struct vertex));
	new->parent = NIL;
	new->startTime = NIL;
	new->low = 0;
	new->ap = 0;
	new->adj = NULL;
	return new;
}

Graph graphInit(){
	
	char line[LINESIZE];
	int N, M, src, dst, i=0;
	char* c;

	c = fgets(line, LINESIZE, stdin);
	assert(c);
	sscanf(line, "%d", &N);
	c = fgets(line, LINESIZE, stdin);
	assert(c);
	sscanf(line, "%d", &M);
	Graph graph = (Graph)can_fail_malloc(sizeof(struct graph));
	graph->numVertexes = N;
	graph->numEdges = M;
	graph->vertexList = (Vertex*)can_fail_malloc(sizeof(Vertex)*(N+1));
	graph->C = 0;
	graph->Max = 0;
	int v;
	for(v = 1; v < N+1; v++){
		graph->vertexList[v] = newVertex();
	}

	while((fgets(line, LINESIZE, stdin)) && (i<M)){
		sscanf(line, "%d %d", &src, &dst);
		graphInsert(graph->vertexList,src,dst);
		graphInsert(graph->vertexList,dst,src);
		i++;
	}	
	return graph;
}

void graphInsert(Vertex* vertexList, int vertex1, int vertex2){
	vertexList[vertex1]->adj = newNode(vertex2, vertexList[vertex1]->adj);
}

void addId(Graph g, int i){
	g->idList = newNode(i, g->idList);
}

void DFS(Vertex* vertexList, int numVertexes, Graph g, int* C){
	int i, R=0, D=1;
	Node current;
	for(i = numVertexes; i > 0; i--){
		if(vertexList[i]->startTime == NIL){
			DFSAlgorythm(vertexList, i, ++R, &D, C);
			addId(g, i);
		}
	}
	printf("%d\n", R);
	current = g->idList;
	while(current != NULL){
		(current->next == NULL) ? printf("%d\n", current->value) :printf("%d ",current->value);
		current = current->next;
	}
	listFree(g->idList);
	printf("%d\n", (*C));
}

void DFSAlgorythm(Vertex* vertexList, int i, int R, int* D, int* C){
	vertexList[i]->startTime = (*D);
	vertexList[i]->low = (*D);
	(*D)++;
	int childNum = 0;
	Node v;
	for(v = vertexList[i]->adj; v != NULL; v = v->next){
		if(vertexList[v->value]->startTime == NIL){
			vertexList[v->value]->parent = i;
			childNum++;
			DFSAlgorythm(vertexList,v->value, R, D, C);
			vertexList[i]->low = ((vertexList[i]->low) < (vertexList[v->value]->low)) ? vertexList[i]->low : vertexList[v->value]->low;
			if((vertexList[i]->parent == NIL) && (childNum >= 2) &&(vertexList[i]->ap == FALSE)){
				vertexList[i]->ap = TRUE;
				(*C)++;
			}
			else if((vertexList[i]->parent != NIL) && (vertexList[v->value]->low >= vertexList[i]->startTime) &&(vertexList[i]->ap == FALSE)){
				vertexList[i]->ap= TRUE;
				(*C)++;
			}	
		}
		else if(v->value != vertexList[i]->parent){
			vertexList[i]->low = (vertexList[i]->low < vertexList[v->value]->startTime) ? vertexList[i]->low : vertexList[v->value]->startTime;
		}
	}
}

void cutLength(Vertex* vertexList, int f, int* max){
	int length = 0;
	int i;
	for(i = 1; i < f+1; i++){
		if((vertexList[i]->startTime != NIL) && (vertexList[i]->ap != TRUE)){
			deep(vertexList,&length,i);
			if(length > (*max)){
				(*max) = length;
			}
			length = 0;
		}
	}
	printf("%d\n", (*max));
}

void deep(Vertex* vertexList, int* length, int node){
	vertexList[node]->startTime = NIL;
	(*length)++;
	Node i;
	for(i = vertexList[node]->adj; i != NULL; i = i->next)
		if(vertexList[i->value]->startTime != NIL && (vertexList[i->value]->ap != TRUE))
			deep(vertexList,length,i->value);
}

void listFree(Node n){
	Node iter;
	while(n != NULL){
		iter = n;
		n = n->next;
		free(iter);
	}
}

void VertexFree(Vertex v){
	listFree(v->adj);
	free(v);
}

void graphFree(Graph g){
	int i;
	for(i = 1; i <= g->numVertexes; i++){
		VertexFree(g->vertexList[i]);
	}
	free(g);
	free(g->vertexList);
}

int main(int argc, char* argv[]){
	Graph graph = NULL;
	graph = graphInit();
	DFS(graph->vertexList, graph->numVertexes, graph, &graph->C);
	cutLength(graph->vertexList,graph->numVertexes, &graph->Max);
	graphFree(graph);
	return 0;
}