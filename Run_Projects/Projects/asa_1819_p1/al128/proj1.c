#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct router {
	unsigned long id;
	bool ap;
	struct link *connect;
} router;

typedef struct link {
	struct router *content;
	struct link *next;
} link;

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

void addNode(unsigned long router1, unsigned long router2, router *vertices){
	link *oneToTwo = (link *) malloc(sizeof(link));
	link *twoToOne = (link *) malloc(sizeof(link));
	oneToTwo->content = &(vertices[router2-1]);
	twoToOne->content = &(vertices[router1-1]);
	oneToTwo->next = NULL;
	twoToOne->next = NULL;
	addLink(&(vertices[router1-1].connect), oneToTwo);
	addLink(&(vertices[router2-1].connect), twoToOne);
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

unsigned long listSize(link *list){
	if (list == NULL) {
		return 0;
	}
	else {
		unsigned long size = 1;
		link *temp = list;
		while(temp->next!=NULL){
			temp=temp->next;
			size++;
		}
		return size;
	}
}

void startVertices(unsigned long number, router *vertices){
	unsigned long i;
	for(i = 0; i<number; i++){
		vertices[i].id = i+1;
		vertices[i].ap = false;
		vertices[i].connect = NULL;
	}
}

void freeGraph(router *vertices, unsigned long verticeNum){
	unsigned long i;
	for(i = 0; i<verticeNum; i++){
		freeList(vertices[i].connect);
	}
	free(vertices);
}

unsigned long min(unsigned long a, unsigned long b) {
	if (a < b)
		return a;
	return b;
}

unsigned long dfsVisit(router *node, unsigned long *time, unsigned long *discovery, unsigned long *predecessor, unsigned long *low, bool *seen) {
	unsigned long biggestId=node->id;
	unsigned long tempId;
	unsigned long children = 0;
	seen[node->id-1]=true;
	discovery[node->id-1] = *time;
	low[node->id-1] = *time;
	(*time)++;

	link *l = node->connect;
	while (l != NULL) {
		if(seen[l->content->id - 1] == false){
			predecessor[l->content->id-1] = node->id;
			children++;
			tempId = dfsVisit(l->content, time, discovery, predecessor, low, seen);
			if(tempId>biggestId){
				biggestId = tempId;
			}

			low[node->id-1] = min(low[node->id-1], low[l->content->id-1]);

			if(predecessor[node->id -1]==0 && children>1){
				node->ap = true;
			}
			
			if(predecessor[node->id -1]!=0 && low[l->content->id -1] >= discovery[node->id -1]){
				node->ap = true;
			}

		} else if(l->content->id != predecessor[node->id-1]){
			low[node->id-1] = min(low[node->id-1], discovery[l->content->id-1]);
		}
		l = l->next;
	}
	return biggestId;
}

void dfs(router *vertices, unsigned long verticeNum) {

	unsigned long i;
	unsigned long time = 1;
	unsigned long biggestNode;
	unsigned long *dfsDiscovery = (unsigned long*) malloc(sizeof(unsigned long)*verticeNum);
	unsigned long *dfsPredecessor = (unsigned long*) malloc(sizeof(unsigned long)*verticeNum);
	unsigned long *dfsLow = (unsigned long*) malloc(sizeof(unsigned long)*verticeNum);
	bool *dfsSubtree = (bool*) malloc(sizeof(bool)*verticeNum);
	bool *dfsSeen = (bool*) malloc(sizeof(bool)*verticeNum);

	/* STARTING VARS O(V) */
	for(i=0; i<verticeNum; i++){
		dfsDiscovery[i]=0;
		dfsPredecessor[i]=0;
		dfsLow[i]=0;
		dfsSeen[i]=false;
		dfsSubtree[i]=false;
	}

	/* VISIT VERTICES */
	for (i = 0; i < verticeNum; i++) {
		if (dfsSeen[i] == false) {
			biggestNode = dfsVisit(&(vertices[i]), &time, dfsDiscovery, dfsPredecessor, dfsLow, dfsSeen);
			dfsSubtree[biggestNode-1]=true;
		}
	}

	/* OUTPUT (first 3 lines) */
	unsigned long subR = 0, ap = 0;
	for (i = 0; i < verticeNum; i++) {
		if (dfsSubtree[i] == true)
			subR++;
		if (vertices[i].ap == true)
			ap++;
	}
	printf("%lu\n", subR);
	for (i = 0; i < verticeNum; i++) {
		if (dfsSubtree[i] == true) {
			printf("%lu", vertices[i].id);
			if(subR > 1) {
				putchar(' ');
				subR--;
			}
		}
	}
	printf("\n%lu\n", ap);

	free(dfsDiscovery);
	free(dfsPredecessor);
	free(dfsLow);
	free(dfsSubtree);
	free(dfsSeen);
}

void simpleDfsVisit(router *node, unsigned long *time, bool *seen) {
	seen[node->id-1]=true;
	(*time)++;

	link *l = node->connect;
	while (l != NULL) {
		if(seen[l->content->id - 1] == false && l->content->ap == false){
			simpleDfsVisit(l->content, time, seen);
		}
		l = l->next;
	}
}

void simpleDfsCounter(router *vertices, unsigned long verticeNum) {
	unsigned long i, time = 0, timeHigh = 0;
	bool *dfsSeen = (bool*) malloc(sizeof(bool)*verticeNum);

	for(i=0; i<verticeNum; i++) {	
		dfsSeen[i]=false;
	}

	for (i = 0; i < verticeNum; i++) {
		if (dfsSeen[i] == false && vertices[i].ap == false) {
			simpleDfsVisit(&(vertices[i]), &time, dfsSeen);
		}
		if (timeHigh < time)
			timeHigh = time;
		time = 0;
	}
	
	/* OUTPUT (last line) */
	printf("%lu\n", timeHigh);

	free(dfsSeen);
}

int main() {
	unsigned long i, verticeNum, edgeNum, r1, r2;
	if (scanf("%lu", &verticeNum) != 1)
		return EXIT_FAILURE;
	if (scanf("%lu", &edgeNum) != 1)
		return EXIT_FAILURE;


	router *vertices = (router *) malloc(sizeof(router)*verticeNum);
	startVertices(verticeNum, vertices);
	for(i = 0; i < edgeNum; i++) {
		if (scanf("%lu %lu", &r1, &r2) != 2)
			return EXIT_FAILURE;
		addNode(r1, r2, vertices);
	}

	dfs(vertices, verticeNum);
	simpleDfsCounter(vertices, verticeNum);
	freeGraph(vertices, verticeNum);

	return 0;
}