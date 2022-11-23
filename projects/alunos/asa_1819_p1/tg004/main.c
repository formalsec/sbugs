#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

/* Definicao de Tipos */

/* Tipo No - Corresponde a um no de um grafo */
typedef struct node_s {
	int ignore;		/* flag */
	int parent;		/*pai do no*/
    int index; 		/*num do scc*/
    int low_link;	/*low*/
    int in_stack;	/*0/1=>true/false*/
    int deg;		/*num arcos do no*/
} node;

/*Tipo pilha*/
typedef struct stack_s {
    int top;
    int *items;
} stack;

/*Tipo scComponent */
typedef struct scComponent_s {
	int maxNode;
	int numComponents;
}scComponent;

/* Tipo Lista */
typedef struct list_s{
	scComponent* link;
	struct list_s *next;
}list;

/* List First */
typedef struct liist_s{
	int numSCC;
	list* first;
}listscc;

typedef struct links{
	int start;
	int end;
} input;


/* Variaveis Globais */
node** graph=NULL;
int numNodes=0;
int numLinks=0;
int curr_index=0;
int maxLinksPerNode=0;
stack* sComponent=NULL;
int **adj;

/* Funcoes Auxiliares */

/*Cria e inicializa um no*/
node* createNode(int id, int maxLinks){
	node* out = (node*) can_fail_malloc(sizeof(node));
	out->ignore=0;
	out->parent=-2;
	out->index=0;
	out->low_link=-1;
	out->in_stack=0;
	out->deg=0;
	return out;
}

/*Cria e inicializa um grafo*/
node** createGraph(int numNodes, int numLinks){
	int count;
	node** graph = (node**)can_fail_malloc(sizeof(node)*numNodes);
	for(count=0; count < numNodes;count++){
		graph[count] = createNode(count, numLinks);
	}
	return graph;
}

void resetNodes(){
	int a;
	
	for(a=0;a<numNodes;a++){
		graph[a]->parent=-2;
		graph[a]->index=-1;
		graph[a]->low_link=-1;
		graph[a]->in_stack=0;
	}

}

/*Adiciona arco ao grafo e devolve grafo atualizado*/
void addVertices(input* in){
	int count;
	int node1, node2;
	node *startNode, *endNode;
	/*int *aux, count;*/
	for(count=0;count<numNodes;count++){
		adj[count]=(int*) can_fail_malloc(sizeof(int)*(graph[count]->index+1));
	}
	
	for(count=0;count<numLinks;count++){
		node1 = in[count].start;
		node2 = in[count].end;
		startNode = graph[node1-1];
		endNode = graph[node2-1];
		adj[node1-1][startNode->deg++] = node2;
		adj[node2-1][endNode->deg++] = node1;
	}
	resetNodes();
}

/*Adiciona elemento a pilha*/
void stack_push(int v, stack* s) {
    s->top++;
    if (s->top < numNodes)
		s->items[s->top] = v;
    else {
		printf("Stack is full!\n");
		exit(1);
    }
}

/*Remove elemento da pilha*/
int stack_pop(stack* s) {
    return s->top < 0 ? -1 : s->items[s->top--];
}

/*Cria e inicializa uma stack*/
stack* createStack(int size){
	stack* s;
	s=(stack *) can_fail_malloc(sizeof(stack));
	s->top=-1;
	s->items=(int*) can_fail_malloc(sizeof(int)*size);
	return s;
}

void deleteStack(stack* s){
	free(s->items);
	free(s);
}

/*Cria e inicializa um SCC*/
scComponent* createComponent(int numComponents, stack *s){
	int aux, no;
	scComponent* component;
	component = (scComponent*)can_fail_malloc(sizeof(scComponent));
	component->maxNode=-1;
	component->numComponents=numComponents;
	for(aux=0;aux<numComponents;aux++){
		no = stack_pop(s);
		if(no+1>component->maxNode){
			component->maxNode=no+1;
		}
	}
	return component;
}

listscc* addToList(listscc* sccList, scComponent *scc){
	list *insert;
	insert = (list*) can_fail_malloc(sizeof(list));
	insert->link = scc;
	insert->next=NULL;
	if(sccList->first==NULL){
		sccList->first = insert;
	} else {
		insert->next=sccList->first;
		sccList->first = insert;
	}
	sccList->numSCC++;
	return sccList;
}

void deleteSCC(scComponent* scc){
	free(scc);
}

void deleteList(listscc* l){
	int aux;
	list *next,*laux;
	next=l->first;
	for(aux=0;aux<l->numSCC;aux++){
		deleteSCC(next->link);
		laux=next->next;
		free(next);
		next=laux;
	}
	free(l);
}

void deleteNode(node* no){
	free(no);
}

void deleteGraph(){
	int aux;
	for(aux=0;aux<numNodes;aux++){
		deleteNode(graph[aux]);
	}
	free(graph);
}





/* Algoritmo TARJAN */
int min(int a, int b) {
    return a < b ? a : b;
}

stack* strongconnect(int v) {
    int i, c, n;
    graph[v]->index = curr_index;
    graph[v]->low_link = curr_index;
    ++curr_index;
    graph[v]->in_stack = 1;
    
    for (i = 0, c = graph[v]->deg; i < c; ++i){
		if (adj[v][i] > 0) {
			n = adj[v][i] - 1;
			if(n+1 != graph[v]->parent){
				if (graph[n]->index == -1) {
					graph[n]->parent=v+1;
					strongconnect(n);
					graph[v]->low_link = min(graph[v]->low_link, graph[n]->low_link);
				} else if (graph[n]->in_stack) {
					graph[v]->low_link = min(graph[v]->low_link, graph[n]->index);
				}
			}
		}
	}
    
	stack_push(v, sComponent);
	return sComponent;
}

listscc* tarjan(listscc* sccList) {
    int i;
    stack *pilha;
    scComponent *scc;
    for (i = 0; i < numNodes; ++i){
	    if (graph[i]->index == -1 && graph[i]->ignore==0){
			pilha=strongconnect(i);
			scc = createComponent(pilha->top+1, pilha);
	        sccList = addToList(sccList, scc);
		}
	}
	return sccList;
}

/* Algoritmo para encontrar nos que quebram redes */
stack* findBridges(){
	int n, a, pos;
	int currIndex, lowSon, sons, parentAdj;
	int parent = -1;
	stack* bridges;
	bridges=createStack(numNodes);
	
	for(n=0; n<numNodes;n++){
		sons=0;
		parent = graph[n]->parent-1;
		if(parent<0){
			for(a=0;a<graph[n]->deg;a++){
				if(graph[adj[n][a]-1]->parent==n+1)
					sons++;
				if(sons>1){
					stack_push(n+1,bridges);
					break;
				}
			}
		} else {
			for(a=0;a<graph[n]->deg;a++){
				pos=adj[n][a]-1;
				parentAdj=graph[pos]->parent;
				currIndex=graph[n]->index;
				if(parentAdj==n+1){
					lowSon = graph[pos]->low_link;
					if(currIndex<=lowSon){
						stack_push(n+1, bridges);
						break;
					}
				}
			}
		}
	}
	return bridges;
}

void removeFromGraph(stack* s){
	int current, a, n, r;
	int *aux;
	int toRemove = s->top+1;
	aux=(int*)can_fail_malloc(sizeof(int)*toRemove);
	a=0;
	while((current=stack_pop(s))!=-1)
		aux[a++]=current;
	
	for(a=0;a<toRemove;a++){
		graph[aux[a]-1]->ignore=1;
	}
	for(a=0;a<numNodes;a++){
		if(graph[a]->ignore==0){
			for(n=0;n<graph[a]->deg;n++){
				for(r=0;r<toRemove;r++){
					if(adj[a][n]==aux[r]){
						adj[a][n]=-1;
					}
				}
			}
		}
	}
	free(aux);
}

int* sccToArray(listscc *l){
	int a;
	int* out = (int*)can_fail_malloc(sizeof(int)*l->numSCC);
	list *current;
	current=l->first;
	for(a=0;a<l->numSCC;a++){
		out[a]=current->link->maxNode;
		current=current->next;
	}
	
	return out;
}

int getMaxSize(listscc *l){
	int a;
	int out = -1;
	list *current;
	current=l->first;
	for(a=0;a<l->numSCC;a++){
		if(current->link->numComponents>out)
			out=current->link->numComponents;
		current=current->next;
	}
	
	return out;
}

/* QuickSort Algorithm */

void swap(int *a, int *b)
{
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}


/* the aim of the partition is to return the subscript of the exact */
/* position of the pivot when it is sorted */
/*the low variable is used to point to the position of the next lowest element*/
int partition(int arr[], int first, int last)
{
    int pivot = arr[last]; /*changed the pivot*/  
    int low = first;
    int i = first; /*changed*/
    while(i <= last-1 ){/* or you can do for(i=first;i<last;i++)*/
        if(arr[i] < pivot){
            swap(&arr[i], &arr[low]);
            low++; 
        }
        i++;
    }
    swap(&arr[last], &arr[low]);
    /*after finishing putting all the lower element than the pivot 
      It's time to put the pivot into its place and return its position*/
    return low;
}



void quick_sort(int arr[], int first, int last)
{
    int pivot_pos;
    if(first < last){
        pivot_pos = partition(arr, first, last);
        quick_sort(arr, first, pivot_pos-1);
        quick_sort(arr, pivot_pos+1, last);
    }
}

/*************************************************************************/
				

int main(int argc, char** argv){
	int i;
	listscc *sccList1, *sccList2;
	stack* bridges;
	int* sccID;
	input* inputArray;
	
	
	sccList1=(listscc*)can_fail_malloc(sizeof(listscc));
	sccList1->numSCC=0;
	sccList2=(listscc*)can_fail_malloc(sizeof(listscc));
	sccList2->numSCC=0;
	
	
	if(scanf("%d", &numNodes)<=0) exit(1);
	if(scanf("%d", &numLinks)<=0) exit(1);
	
	adj=(int**) can_fail_malloc(sizeof(int*)*numNodes);
	
	inputArray=(input*) can_fail_malloc(sizeof(input)*numLinks);
	
	sComponent=createStack(numNodes);
	
	graph = createGraph(numNodes,numLinks);
	
	
	for(i=0;i<numLinks;i++){
		if(scanf("%d %d", &inputArray[i].start, &inputArray[i].end)<=0) exit(1);
		graph[inputArray[i].start-1]->index++;
		graph[inputArray[i].end-1]->index++;
	}
	
	addVertices(inputArray);
	
	free(inputArray);
	
	
	sccList1=tarjan(sccList1); /*get sccs from tarjan*/
	
	sccID = sccToArray(sccList1); 	/*convert scc list to array*/
	printf("%d\n", sccList1->numSCC);
	quick_sort(sccID, 0, sccList1->numSCC-1);			/*sort scc array*/
	for(i=0;i<sccList1->numSCC;i++){
		if(i+1==sccList1->numSCC){
			printf("%d\n", sccID[i]);
		} else {
			printf("%d ", sccID[i]);
		}
	}
	deleteList(sccList1);			/*delete scc list*/
	bridges=findBridges();			/*find bridge nodes, store in stack*/
	printf("%d\n", bridges->top+1);
	removeFromGraph(bridges);		/*remove bridges from graph*/
	resetNodes();					/*reset graph values for tarjan*/
	sccList2=tarjan(sccList2);		/*run tarjan without bridges*/
	printf("%d\n", getMaxSize(sccList2));
	
	
	
	
	/* Cleanup */
	free(sccID);
	deleteList(sccList2);
	
	deleteStack(sComponent);
	deleteStack(bridges);
	deleteGraph();
	
	return 0;
	
	
}
