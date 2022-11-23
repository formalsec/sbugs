#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define EMPTY 0
#define LINESIZE 30

#define SOURCE_BACK 1
#define SOURCE_FRONT 2

#define STATION_BACK 3
#define STATION_FRONT 4

#define DESTINATION 5

/*

	->AS ESTRUTURAS FORAM MUDADAS DE MODO A SIMPLIFICAR O GRAFO RESIDUAL
	  ONDE SERIA APLICADO O RELABEL

	->TODAS OS FORNECEDORES PARTEM DA MESMA FONTA QUE ESTA NO INDICE 0, SENDO QUE
	  NO INDICE 1 FICA O HIPERMERCADO E NOS RESTANTES OS ABASTECIMENTOS

	->OS TIPOS DEFINIDOS A CIMA NÃO SÃO PRECISOS PARA A IMPLEMENTACAO DO MAX FLOW
	  MAS CREIO QUE FUTURAMENTE PRECISAREMOS DE DISTINGUIR DE ALGUMA FORMA QUAIS SAO
	  AS ARESTAS PARA OS QUAIS OS VERTICES TEM STATION BACK/FRONT DE MODO A SABER QUE
	  ABASTECIMENTOS AUMENTAR

	->AINDA N FOI APLICADA A OTIMIZACAO DE ESCOLHA POR ALTURA POIS AINDA N ME FEZ SENTIDO

*/


/***********************
		TYPEDEFS
************************/
typedef struct node{
	int current;
	struct node *next;
}*Node;

typedef struct vertex{
	int height;
	int excessFlow;
	char visited : 1;
	int* adj;
	int size;
	int current;
}*Vertex;

typedef struct edge{
	int sourceVertex, destVertex;
	int currentFlow;
	int maxFlow;
}*Edge;

typedef Edge* EdgeList;

typedef Vertex* VertexList;

typedef int listSize;

typedef struct queue{
	int size;
	Node first;
	Node last;
}*Queue;

typedef struct graph{
	int numSources;
	int numStations;
	int numEdges;
	listSize edgeL;
	listSize vertexL;
	EdgeList edgeList;
	VertexList vertexList;
	Queue queue;
}*Graph;

typedef struct vpair{
	int source;
	int destination;
}*Vpair;


/************************************
		FUNCOES DE INICIALIZACAO
************************************/

Vpair newVpair(int s, int d){
	Vpair new = (Vpair)can_fail_malloc(sizeof(struct vpair));
	new->source = s;
	new->destination = d;
	return new;
}

Vertex newVertex(){
	Vertex new = (Vertex)can_fail_malloc(sizeof(struct vertex));
	new->height = 0;
	new->excessFlow = EMPTY;
	new->visited = 0;
	new->adj = NULL;
	new->size = 0;
	return new;
}

Edge newEdge(int source, int destination, int maxFlow){
	Edge new = (Edge)can_fail_malloc(sizeof(struct edge));
	new->sourceVertex = source;
	new->destVertex = destination;
	new->currentFlow = EMPTY;
	new->maxFlow = maxFlow;
	return new;
}

Node newNode(int vertex){
	Node new = (Node)can_fail_malloc(sizeof(struct node));
	new->current = vertex;
	new->next = NULL;
	return new;
}

Queue newQueue(){
	Queue new = (Queue)can_fail_malloc(sizeof(struct queue));
	new->first = NULL;
	new->last = NULL;
	new->size = 0;
	return new;
}


void enQueue(Queue queue, int vertex){
	Node node = newNode(vertex);
	if(queue->size == 0){
		queue->first = node;
		queue->last = node;
		queue->size++;
	}
	else{
		queue->last->next = node;
		queue->last = node;
		queue->size++;
	}
}

Node deQueue(Queue queue){
	Node temp = queue->first;
	if(queue->first == NULL){
		return NULL;
	}
	queue->first = queue->first->next;
	queue->size--;
	if(queue->size == 1){
		queue->last = queue->first;
	}
	if(queue->size == 0){
		queue->last = NULL;
	}
	temp->next = NULL;
	return temp;
}

Graph newGraph(){	

	char line[LINESIZE];
	int sources, stations, edges, value;
	int src,src_v = 0,dst,dst_v = 0,cap;
	int i, aux = 0, aux_2 = 0;

	Graph graph = (Graph)can_fail_malloc(sizeof(struct graph));
	
	assert(fgets(line, LINESIZE, stdin));
	sscanf(line, "%d %d %d", &sources, &stations, &edges);

	graph->numSources = sources;
	graph->numStations = stations;
	graph->numEdges = edges;
	graph->queue = newQueue();

	/*ESTA PARTE AQUI DO TAMANHO DA LISTA DE VERTICES E DE ARESTAS
	  E UM BOCADO DIFICIL DE EXPLICAR AQUI, MAS SE FIZERES UM DESENHO
	  DO GRAFO NORMAL E ADICIONARES ARESTAS REVERSAS E MUDARES CD
	  ABASTECIMENTO PARA 2VERTICES +1ARESTA VAIS PERCEBER
	 */
	graph->edgeL = edges + stations + sources;
	graph->vertexL = (2*stations)+sources+2;
	graph->edgeList = (EdgeList)can_fail_malloc(sizeof(Edge)*graph->edgeL);
	graph->vertexList = (VertexList)can_fail_malloc(sizeof(Vertex)*graph->vertexL);


	/*COMO EU TINHA DITO ACIMA O HIPER E NO INDEX 1, SENDO QUE A FONTE DE TODOS OS
	  FORNECEDORES FICA NO 0
	 */
	graph->vertexList[0] = newVertex();
	graph->vertexList[1] = newVertex();
	


	/*CASO N SAIBAS BEM O QUE FAZ A VAR AUX, ELA APENAS AJUDA NA ICREMENTACAO DE INDICE,
	  POIS QD ADICIONO UM FORNECEDOR TENHO DE ADICIONAR 2 ARESTAS ENTRE ELE E A FONTE GERAL
	  LOGO, O AUX AJUDA A METER AS ARESTAS NOS INDICES 2,3 4,5 6,7 ETC...
	*/
	for(i = 2; i < sources + 2; i++){
		assert(scanf("%d",&value));
		graph->vertexList[i] = newVertex();
		graph->edgeList[aux] = newEdge(0,i,value);
		graph->vertexList[i]->size++;
		graph->vertexList[0]->size++;
		aux+=1;
	}

	for(i = 0; i < stations; i++){
		assert(scanf("%d",&value));
		graph->vertexList[ 2 + sources + i + aux_2] = newVertex();
		graph->vertexList[3 + sources + i + aux_2] = newVertex();
		graph->edgeList[aux] = newEdge(2 + sources + i + aux_2,3 + sources + i + aux_2,value);
		graph->vertexList[ 2 + sources + i + aux_2]->size++;
		graph->vertexList[3 + sources + i + aux_2]->size++;
		aux+=1;
		aux_2++;
	}
	i = 0;
	while((fgets(line, LINESIZE, stdin)) && (i < edges + 1)){
		sscanf(line, "%d %d %d", &src, &dst, &cap);		
		if(i != 0){	
			src_v = src;
			dst_v = dst;
			if(src > sources + 1) src_v = 2*src - sources - 1;
			if(dst > sources + 1) dst_v = 2*dst - sources - 2;				
			graph->edgeList[aux] = newEdge(src_v,dst_v,cap);
			graph->vertexList[src_v]->size++;
			graph->vertexList[dst_v]->size++;
			aux+=1;
		}
		i++;
	}
	Vertex currentVertex;
	for(i=0; i < graph->vertexL; i++){
		currentVertex = graph->vertexList[i];
		currentVertex->adj = (int*) can_fail_malloc(sizeof(int)*graph->vertexList[i]->size);
		currentVertex->size = 0;
	}
	Edge currentEdge;
	for(i=0; i < graph->edgeL; i++){
		currentEdge = graph->edgeList[i];
		currentVertex = graph->vertexList[currentEdge->sourceVertex];
		currentVertex->adj[currentVertex->size] = i;
		currentVertex->size++;
		currentVertex = graph->vertexList[currentEdge->destVertex];
		currentVertex->adj[currentVertex->size] = i;
		currentVertex->size++;
	}
	return graph;
}

 

int comparator(const void *p, const void *q)  { 
    struct vpair** l = (struct vpair**)p;
    struct vpair** r = (struct vpair**)q;
	if((*l)->source == (*r)->source)
		return (*l)->destination - (*r)->destination;
    return ((*l)->source - (*r)->source); 
}  

 
int compareStations (const void * a, const void * b){
	return ( *(int*)a - *(int*)b );
}

/*****************************
		PUSH-RELABEL
****************************/
void initializePreflow(Graph graph){
	Vertex source = graph->vertexList[0];
	source->height = graph->vertexL;
	int currentNode, i = 0;
	Edge currentEdge;
	while(i < source->size){
		currentNode = source->adj[i];
		currentEdge = graph->edgeList[currentNode];
		if(currentEdge->sourceVertex == 0){
			currentEdge->currentFlow = currentEdge->maxFlow;
			graph->vertexList[currentEdge->destVertex]->excessFlow = currentEdge->maxFlow;
			source->excessFlow = source->excessFlow - currentEdge->maxFlow;
			enQueue(graph->queue,currentEdge->destVertex);
		}
		i++;
	}
}

void push(Graph graph, int vertex, Edge edge){
	Vertex current = graph->vertexList[vertex];
	Vertex next = NULL;
	int flow = MIN(edge->maxFlow,current->excessFlow);
	if(edge->sourceVertex == vertex){
		edge->currentFlow = edge->currentFlow + flow;
		next = graph->vertexList[edge->destVertex];
		if(edge->destVertex >1 && next->excessFlow == 0){
			enQueue(graph->queue, edge->destVertex);
		}
	}
	else{
		edge->currentFlow = edge->currentFlow - flow;
		next = graph->vertexList[edge->sourceVertex];
		if(edge->sourceVertex > 1 && next->excessFlow == 0){
			enQueue(graph->queue, edge->sourceVertex);
		}
	}
	current->excessFlow = current->excessFlow - flow;
	next->excessFlow = next->excessFlow + flow;
}


void relabel(Graph graph, int vertex){	
	/*Carrega o int maximo, como altura*/
	int minHeight = INT_MAX, currentHeight = 0, i = 0;
	/*Precorre a lista de arestas*/
	Vertex currentVertex = graph->vertexList[vertex];
	int currentNode;
	while(i < currentVertex->size){
		currentNode = currentVertex->adj[i];		
		if((graph->edgeList[currentNode]->sourceVertex != vertex) && (graph->edgeList[currentNode]->currentFlow > 0)){
			currentHeight = graph->vertexList[graph->edgeList[currentNode]->sourceVertex]->height;
			if(currentHeight < minHeight){
				minHeight = currentHeight;
			}
		}
		if((graph->edgeList[currentNode]->destVertex != vertex) && (graph->edgeList[currentNode]->maxFlow-graph->edgeList[currentNode]->currentFlow > 0)){
			currentHeight = graph->vertexList[graph->edgeList[currentNode]->destVertex]->height;	
			if(currentHeight < minHeight){
				minHeight = currentHeight;
			}
		}
		i++;
	}
	currentVertex->height = minHeight + 1;
}

void Discharge(Graph graph, int vertex){
	int i = 0;
	Vertex currentVertex = graph->vertexList[vertex];
	int currentNode;
	Edge currentEdge;
	Vertex newVertex;
	while((currentVertex->excessFlow > 0)){
		if(currentVertex->size == i){	
			relabel(graph, vertex);
			i = 0;
			currentVertex->current = currentVertex->adj[i];
		}
		else if(currentVertex->size > i){
			currentVertex->current = currentVertex->adj[i];
			currentNode = currentVertex->adj[i];
			currentEdge = graph->edgeList[currentNode];
			if(currentEdge->sourceVertex == vertex){
				if((graph->edgeList[currentNode]->maxFlow-graph->edgeList[currentNode]->currentFlow > 0)){
					newVertex = graph->vertexList[currentEdge->destVertex];
					if(currentVertex->height == newVertex->height+1){
						push(graph, vertex, currentEdge);
					}
					else{
						i++;
					}
				} 
				else{
					i++;
				}
			}
			else if(currentEdge->destVertex == vertex){
				if(graph->edgeList[currentNode]->currentFlow > 0){
					newVertex = graph->vertexList[currentEdge->sourceVertex];
					if(currentVertex->height == newVertex->height+1){
						push(graph, vertex, currentEdge);
					}
					else{
						i++;
					}
				}
				else{
					i++;
				}
			}
		}
		else{	
			i++;
		}
	}
}

void freeLinkedList(Node head){
	Node tmp;
	while(head != NULL){
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

void freeQueue(Queue q){
	freeLinkedList(q->first);
	if(q->last != NULL){
		free(q->last);
	}
	free(q);
}

int FIFOPushRelable(Graph graph){
	/*Faz a primeira descarga*/
	int i;
	initializePreflow(graph);
	Node vertex = NULL;
	for(i = 2; i <graph->vertexL ;i++){
		graph->vertexList[i]->current = graph->vertexList[i]->adj[0];
	}
	/*Enquanto tem vertices no queue*/
	while(graph->queue->size != 0){	
		/*Retira um vertice do queue*/
		vertex = deQueue(graph->queue);
		/*Enquanto esse vertice tiver excesso de fluxo*/
		Discharge(graph, vertex->current);
		free(vertex);
	}
	freeQueue(graph->queue);
	return graph->vertexList[1]->excessFlow;
}

void DFSAlgorytm(Graph graph,int vertex){
	int count,flow;

	graph->vertexList[vertex]->visited = 1;
	
	for(count = 0; count < graph->edgeL; count++)
	{	
		
		if((graph->edgeList[count]->sourceVertex == vertex) && (graph->vertexList[graph->edgeList[count]->destVertex]->visited == 0) ){	
			/*printf("Tou na aresta(%d,%d)\n",graph->edgeList[count]->sourceVertex,graph->edgeList[count]->destVertex);*/
			if(graph->edgeList[count]->currentFlow > 0)					
					DFSAlgorytm(graph,graph->edgeList[count]->destVertex);
				
		} else if((graph->edgeList[count]->destVertex == vertex) && (graph->vertexList[graph->edgeList[count]->sourceVertex]->visited == 0)){	
			/*printf("Tou na aresta(%d,%d)\n",graph->edgeList[count]->sourceVertex,graph->edgeList[count]->destVertex);*/
			flow = graph->edgeList[count]->maxFlow - graph->edgeList[count]->currentFlow;
			if(flow > 0)
				DFSAlgorytm(graph,graph->edgeList[count]->sourceVertex);

		}
	}
}



void freeVertex(Vertex v){
	free(v->adj);
	free(v);
}

void mincut(Graph graph, int* st, Vpair* edg){
	int st_count = 0;
	int edg_count = 0;
	int i, esrc, edst;
	Vertex src, dst; 
	int numSources = graph->numSources;
	for(i = 0; i < graph->edgeL; i++){
		src = graph->vertexList[graph->edgeList[i]->sourceVertex];
		dst = graph->vertexList[graph->edgeList[i]->destVertex];
		esrc = graph->edgeList[i]->sourceVertex;
		edst = graph->edgeList[i]->destVertex;
		if(src->visited != dst->visited && esrc != 0 && edst != 0 && graph->edgeList[i]->currentFlow > 0){		
			if((esrc - (numSources+2))%2 == 1 && esrc > numSources + 1){				
				if((edst - (numSources+2))%2 == 0 && edst > numSources +1)
					edg[edg_count++] = newVpair( ((graph->numSources + esrc+1)/2) ,(graph->numSources + edst+2)/2);
				else edg[edg_count++] = newVpair( ((graph->numSources + esrc+1)/2) ,edst);				
			}
			else if(edst == esrc+1 && edst > graph->numSources+1){
				st[st_count++] = ((graph->numSources + esrc + +2)/2);			
			}
			else if((edst - (numSources+2))%2 == 0 && edst > numSources +1){	
				edg[edg_count++] = newVpair(esrc,((graph->numSources + edst + 2)/2));			
			}
			else{		
				edg[edg_count++] = newVpair(esrc,edst);		
			}
		}
		free(graph->edgeList[i]);
	}

	free(graph->edgeList);

	for(i = 0; i < graph->vertexL; i++){
		freeVertex(graph->vertexList[i]);
	}
	
	free(graph->vertexList);
	
	st = (int*)can_fail_realloc(st,st_count*sizeof(int));
	edg = (Vpair*)can_fail_realloc(edg,edg_count*sizeof(Vpair));
	
	qsort(edg,edg_count,sizeof(Vpair),comparator);
	
	qsort(st,st_count,sizeof(int),compareStations);
	
	
	for(i = 0;i < st_count; i++){
		if( i ==(st_count - 1))
			printf("%d",st[i]);
		else printf("%d ",st[i]);
	}
	printf("\n");
	
	
	for(i = 0;i < edg_count; i++)
		printf("%d %d\n",edg[i]->source,edg[i]->destination);
	
	
	free(st);
	for(i = 0; i < edg_count; i++){
		free(edg[i]);
	}
	free(edg);
}

void DFS(Graph graph){
	
	int* stations = (int*)can_fail_malloc(sizeof(int)*graph->numStations);
	Vpair* edges = (Vpair*)can_fail_malloc(sizeof(Vpair)*graph->numEdges);
	
	DFSAlgorytm(graph, 1);
	mincut(graph,stations,edges);
	
}


int main(int argc, char* argv[]){
	Graph graph = NULL;
	graph = newGraph();
	printf("%d\n",FIFOPushRelable(graph));
	DFS(graph);
	free(graph);
	return 0;
}




