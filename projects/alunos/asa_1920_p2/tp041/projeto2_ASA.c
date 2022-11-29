#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_LINE_SIZE 100
#define FALSE 0
#define TRUE 1
#define NIL -1



struct QNode { 
    int key; 
    struct QNode* next; 
};

struct Queue { 
    struct QNode *front, *rear; 
}; 


typedef struct AdjListNode
{	
	int dest;
	int capacidade;
	struct AdjListNode* next;
	
}AdjListNode;


typedef struct AdjList
{
	AdjListNode* head;
}AdjList;


typedef struct Graph
{
	int V;
	int* pi;
	int* visited;
	AdjList* array;

}Graph;



AdjListNode* addAdjListNode(int dest, int cap);
Graph* createGraph(int V);
void addEdge(Graph* graph, int orig, int dest, int cap);
void freeGraph(Graph* graph);
int EdmondsKarp(Graph* graph,int s, int t);
int BFS(Graph* graph,int s, int t);
struct QNode* newNode(int k);
struct Queue* createQueue();
void enqueue(struct Queue* q, int k);
int dequeue(struct Queue* q);
int is_Q_empty(struct Queue* q);
int min(int u, int v);



int** matrix;

int main(){

	int i,j,n;
	int v_in;
	int numAvenidas,numRuas;
	int numClientes,numSupermercados;



	n = scanf("%d %d",&numAvenidas,&numRuas);
	if(n<0)perror("Error:scanf");


	n = scanf("%d %d",&numSupermercados,&numClientes);
	if(n<0)perror("Error:scanf");

	

	int V = 2*numAvenidas*numRuas;
	Graph* graph = createGraph(V+2);




	for(v_in = 1;v_in < V;v_in = v_in + 2){
		addEdge(graph,v_in,v_in+1,1);

		addEdge(graph,v_in+1,v_in,0);
	} 


	matrix = (int**)can_fail_malloc(numAvenidas* sizeof(int*));
	for(i = 0;i < numAvenidas;i++){
		matrix[i] = (int*) can_fail_malloc(numRuas * sizeof(int));
	}

	int k = 1;
	for(i = 0;i < numAvenidas;i++){
		for(j = numRuas - 1;j >= 0;j--){
			matrix[i][j] = k;
			k += 2;
		}
	}

	int sumermercado[V];
	for (i = 1; i < V; i+=2)
	{
		sumermercado[i] = FALSE;
	}

	int cliente[V];
	for (i = 1; i < V; i+=2)
	{
		cliente[i] = FALSE;
	}

	j = 0;
	int T = V + 1;
	for(k = 0;k < numSupermercados;k++){	
		n = scanf("%d %d",&i,&j);
		if(n<0)perror("Error:scanf");
		if(sumermercado[matrix[i-1][j-1]] == FALSE){
			addEdge(graph,matrix[i-1][j-1]+1,T,1);

			addEdge(graph,T,matrix[i-1][j-1]+1,0);
			sumermercado[matrix[i-1][j-1]] = TRUE;              /*se houver mais que um supermercado em uma localizacao considerar apenas 1 */
		}
	}

	for(k = 0;k < numClientes;k++){	
		n = scanf("%d %d",&i,&j);
		if(n<0)perror("Error:scanf");
		if(cliente[matrix[i-1][j-1]] == FALSE){
			addEdge(graph,0,matrix[i-1][j-1],1);

			addEdge(graph,matrix[i-1][j-1],0,0);
			cliente[matrix[i-1][j-1]] = TRUE;              /*se houver mais que um cliente numa morada considerar apenas 1 */
		}
	}


	for(i = 0;i < numAvenidas;i++){
		for(j = numRuas - 1;j >= 0;j--){

			if(i == 0 && j == numRuas-1){
				addEdge(graph,matrix[i][j]+1,matrix[i][j-1],1);
				addEdge(graph,matrix[i][j]+1,matrix[i+1][j],1);

				addEdge(graph,matrix[i][j-1],matrix[i][j]+1,0);
				addEdge(graph,matrix[i+1][j],matrix[i][j]+1,0);
				continue;
			}
			else if(i == 0 && j == 0){
				addEdge(graph,matrix[i][j]+1,matrix[i+1][j],1);
				addEdge(graph,matrix[i][j]+1,matrix[i][j+1],1);

				addEdge(graph,matrix[i+1][j],matrix[i][j]+1,0);
				addEdge(graph,matrix[i][j+1],matrix[i][j]+1,0);
				continue;
			}
			else if(j == numRuas-1 && i == numAvenidas-1){
				addEdge(graph,matrix[i][j]+1,matrix[i-1][j],1);
				addEdge(graph,matrix[i][j]+1,matrix[i][j-1],1);

				addEdge(graph,matrix[i-1][j],matrix[i][j]+1,0);
				addEdge(graph,matrix[i][j-1],matrix[i][j]+1,0);
				continue;
			}
			else if(i == numAvenidas-1 && j == 0){
				addEdge(graph,matrix[i][j]+1,matrix[i][j+1],1);
				addEdge(graph,matrix[i][j]+1,matrix[i-1][j],1);

				addEdge(graph,matrix[i][j+1],matrix[i][j]+1,0);
				addEdge(graph,matrix[i-1][j],matrix[i][j]+1,0);
				continue;
			}
			else if(i == 0){
				addEdge(graph,matrix[i][j]+1,matrix[i][j+1],1);
				addEdge(graph,matrix[i][j]+1,matrix[i][j-1],1);
				addEdge(graph,matrix[i][j]+1,matrix[i+1][j],1);

				addEdge(graph,matrix[i][j+1],matrix[i][j]+1,0);
				addEdge(graph,matrix[i][j-1],matrix[i][j]+1,0);
				addEdge(graph,matrix[i+1][j],matrix[i][j]+1,0);
				continue;
			}
			else if(i == numAvenidas-1){
				addEdge(graph,matrix[i][j]+1,matrix[i][j+1],1);
				addEdge(graph,matrix[i][j]+1,matrix[i][j-1],1);
				addEdge(graph,matrix[i][j]+1,matrix[i-1][j],1);

				addEdge(graph,matrix[i][j+1],matrix[i][j]+1,0);
				addEdge(graph,matrix[i][j-1],matrix[i][j]+1,0);
				addEdge(graph,matrix[i-1][j],matrix[i][j]+1,0);
				continue;
			}
			else if(j == numRuas-1){
				addEdge(graph,matrix[i][j]+1,matrix[i-1][j],1);
				addEdge(graph,matrix[i][j]+1,matrix[i+1][j],1);
				addEdge(graph,matrix[i][j]+1,matrix[i][j-1],1);

				addEdge(graph,matrix[i-1][j],matrix[i][j]+1,0);
				addEdge(graph,matrix[i+1][j],matrix[i][j]+1,0);
				addEdge(graph,matrix[i][j-1],matrix[i][j]+1,0);
				continue;
			}
			else if(j == 0){
				addEdge(graph,matrix[i][j]+1,matrix[i-1][j],1);
				addEdge(graph,matrix[i][j]+1,matrix[i+1][j],1);
				addEdge(graph,matrix[i][j]+1,matrix[i][j+1],1);

				addEdge(graph,matrix[i-1][j],matrix[i][j]+1,0);
				addEdge(graph,matrix[i+1][j],matrix[i][j]+1,0);
				addEdge(graph,matrix[i][j+1],matrix[i][j]+1,0);
				continue;
			}
			else{
				addEdge(graph,matrix[i][j]+1,matrix[i-1][j],1);
				addEdge(graph,matrix[i][j]+1,matrix[i+1][j],1);
				addEdge(graph,matrix[i][j]+1,matrix[i][j+1],1);
				addEdge(graph,matrix[i][j]+1,matrix[i][j-1],1);

				addEdge(graph,matrix[i-1][j],matrix[i][j]+1,0);
				addEdge(graph,matrix[i+1][j],matrix[i][j]+1,0);
				addEdge(graph,matrix[i][j+1],matrix[i][j]+1,0);
				addEdge(graph,matrix[i][j-1],matrix[i][j]+1,0);
			}
		}

	}
	for(i = 0;i<numAvenidas;i++){
		free(matrix[i]);
	}

	int max_flow = EdmondsKarp(graph,0,V+1);
	printf("%d\n",max_flow);
	

	for(i = 0;i < V+2;i++){
		AdjListNode* tmp;
		while(graph->array[i].head != NULL){
			tmp = graph->array[i].head;
			graph->array[i].head =  graph->array[i].head->next;
			free(tmp);
		}
	}

	freeGraph(graph);

	return 0;
}



/*----------------------------------------------------------------------------------------------- Edmonds-Karp------------------------------------------------------------------------------------------*/


int EdmondsKarp(Graph* graph,int s, int t){

	int v,u;
	int cap_r = INT_MAX;
	int max_flow = 0;

	while(BFS(graph,s,t) == TRUE){

		int path_flow = INT_MAX;
		for(v = t;v!=s;v = graph->pi[v]){
			u = graph->pi[v];

			AdjListNode* adjNode;
			for(adjNode = graph->array[u].head;adjNode != NULL;adjNode = adjNode->next){
				if(adjNode->dest == v){
					cap_r = adjNode->capacidade;
					break;
				}
			}
			path_flow = min(path_flow,cap_r);
		}
		
		for(v = t;v!=s;v = graph->pi[v]){
			u = graph->pi[v];
	
			AdjListNode* adjNode;
			for(adjNode = graph->array[u].head;adjNode != NULL;adjNode = adjNode->next){        
				if(adjNode->dest == v){
					(adjNode->capacidade)-= path_flow;
					break;
				}
			}
			
			for(adjNode = graph->array[v].head;adjNode != NULL;adjNode = adjNode->next){       
				if(adjNode->dest == u){
					(adjNode->capacidade)+= path_flow;
					break;
				}
			}
			
					
		}
		max_flow+= path_flow;
	}
	return max_flow;
}


int BFS(Graph* graph,int s, int t){

	int w,i,v;
	for(i = 0;i < graph->V;i++){
		graph->visited[i] = FALSE;
	}
	struct Queue* q = createQueue();
	enqueue(q,s);
	graph->visited[s] = TRUE;
	graph->pi[s] = NIL;

	while(!is_Q_empty(q)){
		v = dequeue(q);
		if(v == t){
			graph->visited[v] = TRUE;
			return TRUE;
		}

		AdjListNode* adjNode;
		for(adjNode = graph->array[v].head;adjNode != NULL;adjNode = adjNode->next){
			w = adjNode->dest;
			if(graph->visited[w] == FALSE && adjNode->capacidade > 0){
				graph->visited[w] = TRUE;
				graph->pi[w] = v;
				enqueue(q,w);
			}
		}
	}
	return FALSE;
}



/*----------------------------------------------------------------------------------------------- Graph------------------------------------------------------------------------------------------*/




Graph* createGraph(int V){

	Graph* graph = (Graph*) can_fail_malloc(sizeof(Graph));
	graph->V = V;

	graph->array = (AdjList*) can_fail_malloc(V * sizeof(AdjList));

	graph->pi = (int*) can_fail_malloc(V * sizeof(int));
	graph->visited = (int*) can_fail_malloc(V * sizeof(int));

	int i;
	for(i = 0; i < V;i++){
		graph->array[i].head = NULL;
	}

	return graph;

}


void freeGraph(Graph* graph){
	free(graph->array);
	free(graph->pi);
	free(graph->visited);

}





AdjListNode* addAdjListNode(int dest, int cap){
	AdjListNode* newNode = (AdjListNode*) can_fail_malloc(sizeof(AdjListNode));
	newNode->dest = dest;
	newNode->capacidade = cap;
	newNode->next = NULL; 
	return newNode;
}


void addEdge(Graph* graph, int orig, int dest, int cap){

	AdjListNode* newNode = addAdjListNode(dest,cap);
	newNode->next = graph->array[orig].head;
	graph->array[orig].head = newNode;
}




/*----------------------------------------------------------------------------------------------- Queue------------------------------------------------------------------------------------------*/


struct QNode* newNode(int k) 
{ 
    struct QNode* temp = (struct QNode*)can_fail_malloc(sizeof(struct QNode)); 
    temp->key = k; 
    temp->next = NULL; 
    return temp; 
} 


struct Queue* createQueue() 
{ 
    struct Queue* q = (struct Queue*)can_fail_malloc(sizeof(struct Queue)); 
    q->front = q->rear = NULL; 
    return q; 
} 


void enqueue(struct Queue* q, int k) 
{ 
    
    struct QNode* temp = newNode(k); 
  
    if (q->rear == NULL) { 
        q->front = q->rear = temp; 
        return; 
    } 
    q->rear->next = temp; 
    q->rear = temp; 
} 

int dequeue(struct Queue* q) 
{ 
 	int x;
    if (q->front == NULL){ 
        return -1;
    }     

    struct QNode* temp = q->front; 
  
    q->front = q->front->next; 
  
    if (q->front == NULL){ 
        q->rear = NULL; 
  	}

  	x = temp->key;
  	free(temp);
  	return x;
} 

int is_Q_empty(struct Queue* q){
	return q->front == NULL;
}



/*----------------------------------------------------------------------------------------------- Aux------------------------------------------------------------------------------------------*/

int min(int u, int v){
	if(u < v){
		return u;
	}
	else{
		return v;
	}
}
