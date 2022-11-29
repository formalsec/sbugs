#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/* 89461 Inês Alves */
/* 89508 Miguel Silva */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a, b) ((a < b) ? a: b)
#define NONE 0
#define HOME 1
#define MARKET 2
#define BOTH 3

typedef struct queue{
	int visitedVertex;
	struct queue * next;
}* Queue;

typedef struct edge{
	int indexVertexList;
	int flow;
	int capacity;
	struct edge * next;
}*Edge;

typedef struct vertex{
	Edge edgesHead;
	int type;
}*Vertex;

typedef struct graph {
	Vertex vertexList;
	int maxFlow;
	int marketsNumber;
	int clientsNumber;
	int vertexNumber;
	int streets;
	int avenues;
	int size;
	int sourceIndex;
	int sinkIndex;
} * Graph;

void edgeInitializer(Graph g, int from, int to, int capacity, int flow){
	Edge aux;
	aux=g->vertexList[from].edgesHead;
	g->vertexList[from].edgesHead = (struct edge *)can_fail_malloc(sizeof(struct edge));
	g->vertexList[from].edgesHead->next = aux;
	g->vertexList[from].edgesHead->indexVertexList = to;
	g->vertexList[from].edgesHead->capacity = capacity;
	g->vertexList[from].edgesHead->flow = flow;
}
void edgesInitializer(Graph g, int from, int to){
	edgeInitializer(g,from,to,1,0);
	edgeInitializer(g,to,from,0,0);
}
void parseInput(Graph g) {
	int i, N, M, S, C, offset, up,down,left,right;
	scanf("%d %d\n", &M, &N);
	g->size = 2*M*N + 2;
	g->vertexList = (struct vertex *)can_fail_malloc(g->size*sizeof(struct vertex));
	g->streets = N;
	g->avenues = M;
	g->maxFlow = 0;
	g->vertexNumber = N*M;
	g->sourceIndex = 2*g->vertexNumber;
	g->sinkIndex = 2*g->vertexNumber + 1;
	g->marketsNumber=0;
	g->clientsNumber=0;
	
	for(i=0; i<g->size; i++){
		g->vertexList[i].edgesHead = NULL;
		g->vertexList[i].type = NONE;
	}

	scanf("%d %d\n", &S, &C);
	for (i = 0; i < S; i++) {
		scanf("%d %d\n", &M, &N);
		offset = (N-1)*(g->avenues)+(M-1);
		if(g->vertexList[offset].type == NONE)
			g->marketsNumber +=1;
		g->vertexList[offset].type=MARKET;
		g->vertexList[offset + g->vertexNumber].type=MARKET;
	}

	for (i = 0; i < C; i++) {
		scanf("%d %d\n", &M, &N);
		offset = (N-1)*(g->avenues)+(M-1);
		if(g->vertexList[offset].type != BOTH && g->vertexList[offset].type != HOME )
			g->clientsNumber +=1;
		if(g->vertexList[offset].type == MARKET || g->vertexList[offset].type == BOTH ){
			g->vertexList[offset].type=BOTH;
			g->vertexList[offset + g->vertexNumber].type=BOTH;
		}
		else{
			g->vertexList[offset].type=HOME;
			g->vertexList[offset + g->vertexNumber].type=HOME;
		}
	}

	for (i = 0; i < g->vertexNumber; i++){
		edgesInitializer(g, i, i + g->vertexNumber);

		if(g->vertexList[i].type == HOME || g->vertexList[i].type == BOTH){
			edgesInitializer(g, g->sourceIndex,i);
		}
		if(g->vertexList[i].type == MARKET || g->vertexList[i].type == BOTH){
			edgesInitializer(g, i + g->vertexNumber,g->sinkIndex);
		}
		if(g->vertexList[i].type == NONE || g->vertexList[i].type == HOME){
			up=i-g->avenues; 
			down=i+g->avenues; 
			left=i-1;
			right=i+1;
			if(up>=0){
				edgesInitializer(g, i + g->vertexNumber,up);
			}
			if(down < g->vertexNumber){
				edgesInitializer(g, i + g->vertexNumber,down);
			}
			if(left/g->avenues == i/g->avenues && left>=0){
				edgesInitializer(g, i + g->vertexNumber,left);
			}
			if(right/g->avenues == i/g->avenues && right< g->vertexNumber){
				edgesInitializer(g, i + g->vertexNumber,right);
			}
		}
	}
}

int bfs(Graph g, int * parentList, int * patchCapacity){
	int u,v;
	Edge auxEdge;
	Queue queueRoot = (struct queue *)can_fail_malloc(sizeof(struct queue)), queueTail, queueAux;
	memset(parentList, -1, g->size * sizeof(int));
	memset(patchCapacity, 0, g->size * sizeof(int));
	parentList[g->sourceIndex] = g->sourceIndex;
	patchCapacity[g->sourceIndex]=999;
	queueRoot->visitedVertex = g->sourceIndex;
	queueRoot->next=NULL;
	queueTail=queueRoot;
    while(queueRoot != NULL){
		u = queueRoot->visitedVertex;
		queueAux = queueRoot;
		queueRoot = queueRoot->next;
		free(queueAux);
		if(queueRoot == NULL)
			queueTail = queueRoot;

		auxEdge = g->vertexList[u].edgesHead;
		while(auxEdge != NULL){
			v=auxEdge->indexVertexList;
			if( parentList[v]==-1 && (auxEdge->capacity - auxEdge->flow) >0 ){
				parentList[v]=u;
				patchCapacity[v] = min(patchCapacity[u], (auxEdge->capacity - auxEdge->flow));

				if(queueRoot == NULL){
					queueRoot = (struct queue *)can_fail_malloc(sizeof(struct queue));
					queueRoot->visitedVertex=v;
					queueRoot->next=NULL;
					queueTail=queueRoot;
				}
				else{
					queueTail->next = (struct queue *)can_fail_malloc(sizeof(struct queue));
					queueTail = queueTail->next;
					queueTail->visitedVertex = v;
					queueTail->next = NULL;
				}

				if(v == g->sinkIndex){
					while(queueRoot != NULL){
						queueAux=queueRoot;
						queueRoot=queueRoot->next;
						free(queueAux);
					}
					return patchCapacity[v];
				}
			}
			auxEdge=auxEdge->next;
		}
	}
	return 0;
}

void edmondsKarp(Graph g){
	int currentVertex,previousVertex,path;
	int parentList[g->size];
	int patchCapacity[g->size];
	Edge auxEdge;
	path=bfs(g,parentList,patchCapacity);
	while(path != 0){
		g->maxFlow = g->maxFlow + path;
		if(g->maxFlow == min(g->marketsNumber, g->clientsNumber))
			break;
		currentVertex = g->sinkIndex;
		while(currentVertex != g->sourceIndex){
			previousVertex = parentList[currentVertex];
			auxEdge = g->vertexList[previousVertex].edgesHead;
			while(auxEdge != NULL){
				if(auxEdge->indexVertexList == currentVertex){
					auxEdge->flow = auxEdge->flow + 1;
					auxEdge = g->vertexList[currentVertex].edgesHead;
					while(auxEdge != NULL){
						if(auxEdge->indexVertexList == previousVertex){
							auxEdge->flow = auxEdge->flow -1;
							break;
						}
						auxEdge = auxEdge->next;
					}
					break;
				}
				auxEdge = auxEdge->next;
			}
			currentVertex = previousVertex;
		}
		path=bfs(g,parentList,patchCapacity);
	}
	
}

void freeGraph(Graph g){
	int i;
	Edge auxEdge,terminateEdge;
	for(i=0; i<g->size; i++){
		auxEdge = g->vertexList[i].edgesHead;
		while(auxEdge != NULL){
			terminateEdge = auxEdge;
			auxEdge = auxEdge->next;
			free(terminateEdge);
		}
		free(&g->vertexList[i]);
	}
	free(g->vertexList);
	free(g);
}

int main (void) {
	Graph g = can_fail_malloc(sizeof(struct graph));
	parseInput(g);
	edmondsKarp(g);
	printf("%d\n",g->maxFlow);
	free(g);
	return 0;
}
