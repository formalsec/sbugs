#include <stdio.h>
#include <stdlib.h>

typedef struct vertice {
	unsigned long id;
	unsigned long height;
	unsigned long overflow;
	struct link *connect;
	struct link *current;
} vertice;

typedef struct edge {
	unsigned long source;
	unsigned long destination;
	unsigned long capacity;
	unsigned long flow;
} edge;

typedef struct link {
	struct edge *edge;
	struct link *next;
} link;

typedef struct v_link{
	unsigned long int id;
	struct v_link *next;
} v_link;

typedef struct queue{
	struct v_link *start;
	struct v_link *end;
} queue;

void addToQueue(queue *queue, unsigned long value){
	v_link *toAdd = (v_link*) malloc(sizeof(v_link));
	toAdd->id = value;
	toAdd->next = NULL;
	if(queue->start == NULL){
		queue->start = toAdd;
		queue->end = queue->start;
	} else{
		queue->end->next = toAdd;
		queue->end = queue->end->next;
	}
}

unsigned long getFromQueue(queue *queue){
	unsigned long value = queue->start->id;
	v_link *temp;
	if(queue->start==queue->end){
		free(queue->start);
		queue->start=NULL;
		queue->end=NULL;
	}
	else{
		temp=queue->start;
		queue->start = queue->start->next;
		free(temp);
	}
	return value;
}

void addLink(link **list, link *toAdd){
	if (*list == NULL) {
		*list = toAdd;
	}
	else {
		link *temp = *list;
		while(temp->next!=NULL){
			temp=temp->next;
		}
		temp->next = toAdd;
	}
}

void associateEdge(vertice *vertices, edge *edge){
	link *link1 = (link*) malloc(sizeof(link));
	link *link2 = (link*) malloc(sizeof(link));
	link1->edge = edge;
	link2->edge = edge;
	link1->next = NULL;
	link2->next = NULL;
	addLink(&(vertices[(edge->source)-1].connect), link1);
	addLink(&(vertices[(edge->destination)-1].connect), link2);
}

void freeList(link *list){
	link *temp = list;
	link *oldTemp;
	while(temp!=NULL){
		oldTemp = temp;
		temp=temp->next;
		free(oldTemp);
	}
}

void startVertices(unsigned long number, vertice *vertices){
	unsigned long i;
	for(i = 0; i<number; i++){
		vertices[i].id = i+1;
		vertices[i].height = 0;
		vertices[i].overflow = 0;
		vertices[i].connect = NULL;
		vertices[i].current = NULL;
	}
}

void startEdges(unsigned long number, edge *edges){
	unsigned long i;
	for(i=0; i<number; i++){
		edges[i].source = 0;
		edges[i].destination = 0;
		edges[i].flow = 0;
		edges[i].capacity = 0;
	}
}

unsigned long min(unsigned long a, unsigned long b) {
	if (a < b)
		return a;
	return b;
}

void pushSrcDest(vertice *vertices, edge *edge){
	vertice *source = &(vertices[(edge->source)-1]);
	vertice *destination = &(vertices[(edge->destination)-1]);
	unsigned long possible = min(source->overflow, edge->capacity - edge->flow);
	edge->flow = edge->flow + possible;
	source->overflow = source->overflow - possible;
	destination->overflow = destination->overflow + possible;
}

void pushDestSrc(vertice *vertices, edge *edge){
	vertice *source = &(vertices[(edge->source)-1]);
	vertice *destination = &(vertices[(edge->destination)-1]);
	unsigned long possible = min(destination->overflow, edge->flow);
	edge->flow = edge->flow - possible;
	source->overflow = source->overflow + possible;
	destination->overflow = destination->overflow - possible;
}

int is_src(unsigned long u, edge *edge){
	if(edge->source == u){
		return 1;
	} else{return 0;}
}

int is_dest(unsigned long u, edge *edge){
	if(edge->destination == u){
		return 1;
	} else{return 0;}
}

int listMinHeight(vertice *vertices, link *head, unsigned long u){
	link *current = head;
	unsigned long oldh = vertices[u-1].height;
	long min = -1;
	while(current != NULL){
		if(is_src(u, current->edge)){
			if((vertices[(current->edge->destination)-1].height < min || min==-1) 
				&& vertices[(current->edge->destination)-1].height >= oldh){
				min = vertices[(current->edge->destination)-1].height;
			}
		}
		else if((vertices[(current->edge->source)-1].height < min || min==-1) 
			&& vertices[(current->edge->source)-1].height >= oldh){
			min = vertices[(current->edge->source)-1].height;
		}
		if(min == oldh){
			break;
		}
		current = current->next;
	}
	return min;
}

void relabel(vertice *vertices, unsigned long u){
	vertices[u-1].height = listMinHeight(vertices, vertices[u-1].connect, u) + 1;
}

void newDischarge(vertice *vertices, unsigned long u, queue *queue){
	link *curr_link;
	if(vertices[u-1].current==NULL){
		vertices[u-1].current = vertices[u-1].connect;
	}
	while(vertices[u-1].overflow > 0){
		curr_link = vertices[u-1].current;
		if(curr_link == NULL){
			relabel(vertices, u);
			vertices[u-1].current = vertices[u-1].connect;
		}
		else{
			if(is_src(u, curr_link->edge) 
				&& (vertices[u-1].height == (vertices[(curr_link->edge->destination)-1].height + 1))
				&& (curr_link->edge->flow < curr_link->edge->capacity)){
				if(vertices[curr_link->edge->destination - 1].overflow==0){
					addToQueue(queue, curr_link->edge->destination);
				}
				pushSrcDest(vertices, curr_link->edge);
			}
			else if(is_dest(u, curr_link->edge) 
				&& (vertices[u-1].height == (vertices[(curr_link->edge->source)-1].height + 1))
				&& (curr_link->edge->flow > 0)){
				if(vertices[curr_link->edge->source - 1].overflow==0){
					addToQueue(queue, curr_link->edge->source);
				}
				pushDestSrc(vertices, curr_link->edge);
			}
			else{
				vertices[u-1].current = vertices[u-1].current->next;
			}
		}
	}
}

void queuedPushRelabelStrat(vertice *vertices, unsigned long numVertices){
	unsigned long i, u;
	queue *overflown = (queue*) malloc(sizeof(queue));
	overflown->start=NULL;
	overflown->end=NULL;
	vertices[numVertices-1].height = numVertices;
	for(i=0; i<numVertices; i++){
		if(vertices[i].overflow>0){
			addToQueue(overflown, i+1);
		}
	}
	while(overflown->start != NULL){
		u = getFromQueue(overflown);
		if(u == 1 || u==numVertices){
			continue;
		}
		else{
			newDischarge(vertices, u, overflown);
		}
	}
	free(overflown);
}

int isTraversableEdge(edge *edge, unsigned long u){
	if(is_src(u, edge) && edge->flow == 0){
		return 0;
	}
	else if(is_dest(u, edge) && edge->flow == edge->capacity){
		return 0;
	}
	else{
		return 1;
	}
}

void dfsSplitterVisit(vertice *vertices, unsigned long u, int *isOnFarSide, unsigned long verticeNum){
	isOnFarSide[u-1] = 1;
	link *curr_link = vertices[u-1].connect;
	while(curr_link!=NULL){
		if(curr_link->edge->source != verticeNum){
			if(is_src(u, curr_link->edge)){
				if(isTraversableEdge(curr_link->edge, u) && isOnFarSide[(curr_link->edge->destination)-1] == 0){
					dfsSplitterVisit(vertices, curr_link->edge->destination, isOnFarSide, verticeNum);
				}
			}
			else{
				if(isTraversableEdge(curr_link->edge, u) && isOnFarSide[(curr_link->edge->source)-1] == 0){
					dfsSplitterVisit(vertices, curr_link->edge->source, isOnFarSide, verticeNum);
				}
			}
		}
		curr_link = curr_link->next;
	}
}

int *verticeSplitter(vertice *vertices, unsigned long verticeNum){
	unsigned long i;
	int *isOnFarSide = (int*) malloc(sizeof(int)*verticeNum);
	for(i=0; i<verticeNum; i++){
		isOnFarSide[i]=0;
	}
	dfsSplitterVisit(vertices, 1, isOnFarSide, verticeNum);
	return isOnFarSide;
}

void mergeSource(edge *edges, unsigned long start, unsigned long mid, unsigned long end){
	unsigned long leftNum = mid-start+1;
	unsigned long rightNum = end-mid;
	unsigned long i, j, k;
	edge *left = (edge*) malloc(sizeof(edge)*leftNum);
	edge *right = (edge*) malloc(sizeof(edge)*rightNum);
	for (i = 0; i < leftNum; i++)
		left[i] = edges[start+i];
	for (j = 0; j < rightNum; j++)
		right[j] = edges[mid+1+j];
	
	i=0, j=0, k=start;
	while(i<leftNum && j<rightNum){
		if(left[i].source <= right[j].source){
			edges[k] = left[i];
			i++;
		}
		else{
			edges[k] = right[j];
			j++;
		}
		k++;
	}
	while(i<leftNum){
		edges[k] = left[i];
		i++;
		k++;
	}
	while(j<rightNum){
		edges[k] = right[j];
		j++;
		k++;
	}
	free(left);
	free(right);
}

void sortEdgesSource(edge *edges, unsigned long start, unsigned long end){
	unsigned long mid = (start+end)/2;
	if (start < end){
		sortEdgesSource(edges, start, mid);
		sortEdgesSource(edges, mid+1, end);
		mergeSource(edges, start, mid, end);
	}
}

void mergeDestination(edge *edges, unsigned long start, unsigned long mid, unsigned long end){
	unsigned long leftNum = mid-start+1;
	unsigned long rightNum = end-mid;
	unsigned long i, j, k;
	edge *left = (edge*) malloc(sizeof(edge)*leftNum);
	edge *right = (edge*) malloc(sizeof(edge)*rightNum);
	for (i = 0; i < leftNum; i++)
		left[i] = edges[start+i];
	for (j = 0; j < rightNum; j++)
		right[j] = edges[mid+1+j];
	
	i=0, j=0, k=start;
	while(i<leftNum && j<rightNum){
		if(left[i].destination <= right[j].destination){
			edges[k] = left[i];
			i++;
		}
		else{
			edges[k] = right[j];
			j++;
		}
		k++;
	}
	while(i<leftNum){
		edges[k] = left[i];
		i++;
		k++;
	}
	while(j<rightNum){
		edges[k] = right[j];
		j++;
		k++;
	}
	free(left);
	free(right);
}

void sortEdgesDestination(edge *edges, unsigned long start, unsigned long end){
	unsigned long mid = (start+end)/2;
	if (start < end){
		sortEdgesDestination(edges, start, mid);
		sortEdgesDestination(edges, mid+1, end);
		mergeDestination(edges, start, mid, end);
	}
}

int main(){
	unsigned long verticeNum, edgeNum, edgeCounter=0;

	/*
	INPUT:
	f - número de fornecedores
	e - número de estações de abastecimento
	t - número de ligações na rede

	verticeNum será f + 2e + 1(source imaginária) + 1(hipermercado)
	edgeNum será e + t + f(cada edge de source para fornecedor)
	*/

	unsigned long supplierNum, stationNum, connectNum;
	if(scanf("%lu %lu %lu\n", &supplierNum, &stationNum, &connectNum)!=3)
		return EXIT_FAILURE;

	verticeNum = supplierNum + 2*stationNum + 1 + 1;
	edgeNum = stationNum + connectNum + supplierNum;

	vertice *vertices=(vertice*) malloc(sizeof(vertice)*verticeNum);
	edge *edges=(edge*) malloc(sizeof(edge)*edgeNum);
	startVertices(verticeNum, vertices);
	startEdges(edgeNum, edges);
	
	/*
	ESTRUTURA:
	Para conveniência, serão criadas as seguintes variáveis:
	hiper = 0
	forn = 1
	abast_in = f+1
	abast_out = f+e+1
	source = f+2e+1
	vertices[0] é o Hipermercado
	vertices[forn] a vertices[forn + (f-1)] são os fornecedores
	vertices[abast_in] a vertices[abast_in + (e-1)] são o input das estações de abastecimento
	vertices[abast_out] a vertices[abast_out + (e-1)] são output das estações de abastecimento
	vertices[source] é a source imaginária
	*/

	unsigned long forn = 1;
	unsigned long abast_in = supplierNum +1;
	unsigned long abast_out = supplierNum + stationNum + 1;
	unsigned long i;

	/* RECEBENDO FORNECEDORES (FAZ PRE-FLOW)*/
	for(i = forn; i < forn+supplierNum; i++){
		if(scanf("%lu", &(vertices[i].overflow))!=1)
			return EXIT_FAILURE;
		edges[edgeCounter].source = verticeNum;
		edges[edgeCounter].destination = i+1;
		edges[edgeCounter].capacity = vertices[i].overflow;
		edges[edgeCounter].flow = vertices[i].overflow;
		associateEdge(vertices, &edges[edgeCounter]);
		edgeCounter++;
	}

	/*RECEBENDO ESTAÇÕES DE ABASTECIMENTO*/
	for(i=0; i<stationNum; i++){
		if (scanf("%lu", &(edges[edgeCounter].capacity))!=1)
			return EXIT_FAILURE;
		edges[edgeCounter].source = abast_in+i+1;
		edges[edgeCounter].destination = abast_out+i+1;
		associateEdge(vertices, &edges[edgeCounter]);
		edgeCounter++;
	}

	/*RECEBENDO LIGAÇÕES RESTANTES*/
	for(i=0; i < connectNum; i++){
		if(scanf("%lu %lu %lu", &(edges[edgeCounter].source), &(edges[edgeCounter].destination), &(edges[edgeCounter].capacity))!=3)
			return EXIT_FAILURE;
		if(edges[edgeCounter].source >=abast_in+1){
			edges[edgeCounter].source = edges[edgeCounter].source + stationNum;
		}
		associateEdge(vertices, &edges[edgeCounter]);
		edgeCounter++;
	}


	/*relabelToFront(vertices, verticeNum);*/
	queuedPushRelabelStrat(vertices, verticeNum);

	edge *edges_copy=(edge*) malloc(sizeof(edge)*edgeNum);
	for(i=0; i<edgeNum; i++){
		edges_copy[i] = edges[i];
	}

	sortEdgesDestination(edges_copy, 0, edgeNum-1);
	sortEdgesSource(edges_copy, 0, edgeNum-1);

	int *isOnFarSide = verticeSplitter(vertices, verticeNum);

	/* PRINT DOS RESULTADOS */

	printf("%lu\n", vertices[0].overflow);

	int isFirst=1;
	for(i=0; i < edgeNum; i++){
		if(isOnFarSide[edges_copy[i].source - 1] != isOnFarSide[edges_copy[i].destination - 1]){
			if(edges_copy[i].source > abast_in && edges_copy[i].source <= abast_out){
				if(!isFirst)
					putchar(' ');
				printf("%lu", edges_copy[i].source);
				isFirst=0;
			}
		}
	}

	printf("\n");

	for(i=0; i < edgeNum; i++){
		if(isOnFarSide[edges_copy[i].source - 1] != isOnFarSide[edges_copy[i].destination - 1] && edges_copy[i].flow != 0){
			if(edges_copy[i].source <= abast_in){
				printf("%lu %lu\n", edges_copy[i].source, edges_copy[i].destination);
			}
			if(edges_copy[i].source > abast_out && edges_copy[i].source != verticeNum){
				printf("%lu %lu\n", edges_copy[i].source - stationNum, edges_copy[i].destination);
			}
		}
	}

	for(i=0; i < verticeNum; i++){
		freeList(vertices[i].connect);
	}

	free(vertices);
	free(edges);
	free(edges_copy);
	free(isOnFarSide);

	return EXIT_SUCCESS;
}
