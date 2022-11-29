#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define FAILURE 0
#define MAXLINE 100

typedef struct node {
	int vertex_index;
	struct node *next, *prev;
} node;

typedef node* link;

typedef struct AdjListElement {
	int stackPresence;
	int grade;
	int scc_index;
	link listHead;
	link listTail;
} adj_list_element;

typedef adj_list_element* adj_link;

typedef struct AdjList {
	int size;
	adj_link *head;
} adj_list;

adj_list *adjList;

typedef struct TarjanStack {
	int size;
	int max_size;
	link head;
} Tarjan_stack;

typedef enum color{
	WHITE, GRAY, BLACK
} color;

int time_v = 0;
int *discovery;
int *low;
color *colour;
int *pred;
int *scc_disc;
int *end;

typedef struct SCCListNode {
	int scc_index;
	struct SCCListNode *next;
	struct SCCListNode *prev;
} SCCAdjListNode;

typedef struct SCCListNode* SCC_link;

typedef struct SCCAdjListElement{
	int max;
	SCC_link head;
	SCC_link tail;
} SCCAdjListElement;

typedef SCCAdjListElement* SCC_adj_link;

typedef struct SCCAdjList {
	int size;
	SCC_adj_link *vec;
} SCCAdjList;

SCCAdjList *scc_adj_list;

SCC_link newSCCNode(int index){
	SCC_link t = (SCC_link) can_fail_malloc(sizeof(SCCAdjListNode));
	t->scc_index = index;
	t->prev = t->next = NULL;
	return t;
}

void deleteSCCNode(SCC_link node){

	if(node->prev != NULL)
		node->prev->next = node->next;

	if (node->next != NULL)
		node->next->prev = node->prev;

	free(node);
}

void freeSCCAdjListElemAdjacencies(SCC_link head){
	SCC_link t = head;

	while(head != NULL){
		t = t->next;
		free(head);
		head = t;
	}
}

void freeSCCAdjListElement(SCC_adj_link e){
	freeSCCAdjListElemAdjacencies(e->head);
	free(e);
}

link newNode(int vertex) {
	link t = (link) can_fail_malloc(sizeof(node));
	t->vertex_index = vertex;
	t->next = t->prev = NULL;
	return t;
}

void deleteNode(link node) {

	if (node->prev != NULL)
		node->prev->next = node->next;

	if (node->next != NULL)
		node->next->prev = node->prev;

	free(node);
}

void freeVertexList(link head){
	link t = head;

	while(head != NULL){
		t = t->next;
		free(head);
		head = t;
	}
}

adj_link newAdjListElement(int grade) {
	adj_link t = (adj_link) can_fail_malloc(sizeof(adj_list_element));
	t->grade = grade;
	t->scc_index = -1;
	t->stackPresence = 0;
	t->listHead = NULL;
	t->listTail = NULL;
	return t;
}

void freeAdjListElement(adj_link t){
	freeVertexList(t->listHead);
	free(t);
}

int AdjListInit(int size) {
	int i = 0;

	adjList = (adj_list*) can_fail_malloc(sizeof(adj_list));

	if (adjList == NULL)
		exit(EXIT_FAILURE);

	adjList->size = size;
	adjList->head = (adj_link*) can_fail_malloc(sizeof(adj_link) * size);

	if (adjList->head == NULL)
		exit(EXIT_FAILURE);

	for(i = 0; i < size; i++)
		adjList->head[i] = newAdjListElement(0);

	return SUCCESS;
}

void freeAdjList(){
	int i = 0;

	for(i = 0; i < adjList->size; i++)
		freeAdjListElement(adjList->head[i]);

	free(adjList->head);
	free(adjList);
}

void createEdge(int u, int v) {
	link t;
	if (v >= adjList->size || u >= adjList->size || u < 0 || v < 0) {
		printf("Invalid Vertex\n");
		return;
	}

	t = newNode(v);

	if (adjList->head[u]->listHead == NULL) {
		adjList->head[u]->listHead = t;
		adjList->head[u]->listTail = t;
	}
    else{
        adjList->head[u]->listTail->next = t;
        t->prev = adjList->head[u]->listTail;
        adjList->head[u]->listTail = t;
    }
}

SCC_adj_link newSCCAdjListElement(){
	SCC_adj_link t = (SCC_adj_link) can_fail_malloc(sizeof(SCCAdjListElement));

	t->max = 0;
	t->head = NULL;
	t->tail = NULL;

	return t;
}

void sccAdjList_init(){

	scc_adj_list = (SCCAdjList*) can_fail_malloc(sizeof(SCCAdjList));
	scc_adj_list->vec = NULL;
	scc_adj_list->size = 0;
}

void freeSCCAdjList(){
	int i = 0;

	for(i = 0; i < scc_adj_list->size; i++){
		freeSCCAdjListElement(scc_adj_list->vec[i]);
	}
	free(scc_adj_list->vec);
	free(scc_adj_list);
}

void stack_init(Tarjan_stack* stack){
    stack->size = 0;
    stack->max_size = adjList->size;
    stack->head = NULL;
}

void freeStack(Tarjan_stack* stack){
	freeVertexList(stack->head);
	free(stack);
}

void push_st(int ind, Tarjan_stack* stack){
	link t;

    if(stack->max_size < stack->size+1){
        exit(EXIT_FAILURE);
    }

    t = newNode(ind);
    adjList->head[ind]->stackPresence = 1;
	if (stack->head == NULL){
    	stack->head = t;
			stack->size++;
    	return;
    }
    t->next = stack->head;
    stack->head->prev = t;
    stack->head = t;
		stack->size++;

}

link pop_stack(Tarjan_stack* stack){
    link t;
	
    if(stack->size == 0){
        exit(EXIT_FAILURE);
    }

    t = stack->head;

    if(stack->head->next != NULL){
    	stack->head = stack->head->next;
		t->next = NULL;
	    stack->head->prev = NULL;
		stack->size--;
	}
	else{
		stack->head = NULL;
		stack->size--;
	}
	adjList->head[t->vertex_index]->stackPresence = 0;
    return t;
}

int isOnStack(link v){
	return adjList->head[v->vertex_index]->stackPresence;
}

void sccAdd(SCC_adj_link scc){

	scc_adj_list->vec = (SCC_adj_link*) can_fail_realloc(scc_adj_list->vec, scc_adj_list->size * sizeof(SCC_adj_link) + sizeof(SCC_adj_link));
	scc_adj_list->vec[scc_adj_list->size] = scc;
	scc_adj_list->size++;
}

void Tarjan_Visit(int u, Tarjan_stack* stack){
	link v;

	discovery[u] = time_v;
    low[u] = time_v;
    time_v++;
    push_st(u, stack);

	v = adjList->head[u]->listHead;

    while(v != NULL){
        if((discovery[v->vertex_index] == -1) || (isOnStack(v) == 1)){
            if((discovery[v->vertex_index] == -1)){
                Tarjan_Visit(v->vertex_index, stack);
            }
            low[u]>low[v->vertex_index] ? low[u]=low[v->vertex_index] : low[u];
        }
        v = v->next;
    }
    if(discovery[u]==low[u]){
        SCC_adj_link scc = newSCCAdjListElement();

		v = pop_stack(stack);
        while(u != v->vertex_index){
            adjList->head[v->vertex_index]->scc_index = scc_adj_list->size;

			if(adjList->head[v->vertex_index]->grade > scc->max)
				scc->max = adjList->head[v->vertex_index]->grade;

            deleteNode(v);
			v = pop_stack(stack);
        }
		adjList->head[v->vertex_index]->scc_index = scc_adj_list->size;

		if(adjList->head[v->vertex_index]->grade > scc->max)
			scc->max = adjList->head[v->vertex_index]->grade;

        deleteNode(v);

        sccAdd(scc);
    }
}

void SCC_Tarjan(){
	int vertex = 0;
    Tarjan_stack* stack = (Tarjan_stack*) can_fail_malloc(sizeof(Tarjan_stack));

    stack_init(stack);
	sccAdjList_init();
    discovery = (int*) can_fail_malloc(sizeof(int)*adjList->size);
    low = (int*) can_fail_malloc(sizeof(int)*adjList->size);

    for(vertex = 0; vertex < adjList->size; vertex++){
        discovery[vertex] = -1;
    }
    for(vertex = 0; vertex < adjList->size; vertex++){
        if(discovery[vertex] == -1){
            Tarjan_Visit(vertex, stack);
        }
    }
	
    freeStack(stack);
    free(discovery);
    free(low);
}

int searchSCCAdj(int scc_u, int scc_v){
	SCC_link t = scc_adj_list->vec[scc_u]->head;

	while(t != NULL){
		if(t->scc_index == scc_v){
			return 1;
		}
		t = t->next;
	}

	return 0;
}

void findSCCEdges(){
	int u = 0;

	for(u = 0; u < adjList->size; u++){
		int scc_u = adjList->head[u]->scc_index;
		int scc_v;
		link t = adjList->head[u]->listHead;

		while(t != NULL){
			scc_v = adjList->head[t->vertex_index]->scc_index;
			if(scc_u != scc_v){
				if(scc_adj_list->vec[scc_u]->head == NULL){
					scc_adj_list->vec[scc_u]->head = scc_adj_list->vec[scc_u]->tail = newSCCNode(scc_v);
				}
				else{
					if(!searchSCCAdj(scc_u, scc_v)){
						SCC_link w = newSCCNode(scc_v);
						w->prev = scc_adj_list->vec[scc_u]->tail;
						scc_adj_list->vec[scc_u]->tail->next = w;
						scc_adj_list->vec[scc_u]->tail = w;
					}
				}
			}
			t = t->next;
		}
	}
}

void setVertexGrade(int vertex, int val){
	if(val > adjList->head[vertex]->grade)
		adjList->head[vertex]->grade = val;
}

void DFS_Visit(int u){
    SCC_link v = scc_adj_list->vec[u]->head;

	colour[u] = GRAY;
	scc_disc[u] = time_v;
	time_v++;

	while(v != NULL){
		if(colour[v->scc_index] == WHITE){
			pred[v->scc_index] = u;
			DFS_Visit(v->scc_index);
		}
		if(scc_adj_list->vec[v->scc_index]->max > scc_adj_list->vec[u]->max){
			scc_adj_list->vec[u]->max = scc_adj_list->vec[v->scc_index]->max;
		}
		v = v->next;
	}

	if(pred[u] != -1){
		if(scc_adj_list->vec[u]->max > scc_adj_list->vec[pred[u]]->max){
			scc_adj_list->vec[pred[u]]->max = scc_adj_list->vec[u]->max;
		}
	}

	colour[u] = BLACK;
	end[u] = time_v;
	time_v++;
}

void DFS(){
	int u = 0;

	colour = (color*) can_fail_malloc(sizeof(color)*scc_adj_list->size);
	pred = (int*) can_fail_malloc(sizeof(int)*scc_adj_list->size);
	end = (int*) can_fail_malloc(sizeof(int)*scc_adj_list->size);
	scc_disc = (int*) can_fail_malloc(sizeof(int)*scc_adj_list->size);

	for(u = 0; u < scc_adj_list->size; u++){
		colour[u] = WHITE;
		pred[u] = -1;
	}

	time_v = 1;

	for(u = 0; u < scc_adj_list->size; u++){
		if(colour[u] == WHITE){            
			DFS_Visit(u);
		}
	}

	free(colour);
	free(pred);
	free(end); 
	free(scc_disc);
}

void propagateSCCGrades(){

	DFS();
}

void printVertexGrades(){
	int i = 0;

	for(i = 0; i < adjList->size; i++){
		printf("%d\n", scc_adj_list->vec[adjList->head[i]->scc_index]->max);
	}
}

void processInput(){
	char line[MAXLINE];
	int line_index = 1;
	int n_vertex = 0, n_edges = 0;

	while(fgets(line, MAXLINE, stdin)){
		if(line_index == 1){
			int n;

			sscanf(line, "%d,%d", &n_vertex, &n_edges);
			
			line_index++;

			if(n_vertex < 2){
				exit(EXIT_FAILURE);
			}
			if(n_edges < 1){
				exit(EXIT_FAILURE);
			}
			n = AdjListInit(n_vertex);
			if (n != 1)
				exit(EXIT_FAILURE);

		}
		else if(line_index <= (n_vertex + 1)){
			int grade = atoi(line);
			setVertexGrade(line_index - 2, grade);
			line_index++;
		}
		else if(line_index <= (n_vertex + n_edges +1)){
			int u = 0, v = 0;

			sscanf(line, "%d %d", &u, &v);

			line_index++;
			
			if(u > n_vertex || v > n_vertex){
				exit(EXIT_FAILURE);
			}
			
			createEdge(u-1, v-1);
		}
	}
}

void free_all(){
	freeSCCAdjList();
	freeAdjList();
}

int main() {
    
	processInput();

	SCC_Tarjan();

	findSCCEdges();

	propagateSCCGrades();

	printVertexGrades();

	free_all();

	return 0;
}

