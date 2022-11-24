#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int r_num;
	struct node* next;
} node_t;

typedef struct Graph{
	int n_routers;
	int* visited;
	int* ap;
	node_t** adjLists;
} graph_t;

node_t* createNode(int r);
graph_t* createGraph(int routers);
void addConnection(graph_t* graph, int u, int v);
void DFS(graph_t* graph, int router, int* parent,int* des,int* low);
int DFS_Router(graph_t* graph);
int DFS_Aux(graph_t* graph);
int DFS_Ap(graph_t* graph, int router);

int* ids;

int main(){
	int N, M, u, v;
	int i;
	int subGraphs;
	int Var;
	int conta = 0;

	Var = scanf("%d %d", &N, &M);
	ids = can_fail_malloc(N* sizeof(int));
	graph_t* graph = createGraph(N);
	for(i=0;i<M;i++){
		Var = scanf("%d %d", &u, &v);
		if (Var == -1){
			exit(1);
		}
		addConnection(graph, u, v);
	}
	subGraphs = DFS_Router(graph);
	printf("%d\n", subGraphs);

	for(i=subGraphs-1;i>0;i--)
		printf("%d ", ids[i]);
	printf("%d\n", ids[0]);
	for(i=1;i<N+1;i++){
		if(graph->ap[i]==1){
			conta++;
		}
	}
	printf("%d\n", conta);

	int dimSubr = DFS_Aux(graph);
	printf("%d\n", dimSubr);
	return 0;
}

void DFS(graph_t* graph, int router, int* parent, int* des, int* low){

	static int time=0;
	int children=0;
	node_t* adjList = graph->adjLists[router];
	node_t* t_node = adjList;

	graph->visited[router] = 1;

	time++;
	des[router]=time;
	low[router]=time;

	while(t_node!=NULL){
		int connectedRouter = t_node->r_num;

		if(graph->visited[connectedRouter] == 0){
			children++;
			parent[connectedRouter]=router;
			DFS(graph, connectedRouter, parent, des, low);
			
			if(low[router]>low[t_node->r_num]){
				low[router] = low[t_node->r_num];
			}

			if(parent[router]==-1 && children>1){
				graph->ap[router]=1;
			}
			if(parent[router]!=-1 && des[router]<=low[t_node->r_num]){
				graph->ap[router]=1;
			}
		}
		else if(t_node->r_num != parent[router]){
			if(low[router] > des[t_node->r_num]){
				low[router] = des[t_node->r_num];
			}
		}
		t_node = t_node->next;
	}
}

int DFS_Router(graph_t* graph){
	int i;
	int n = graph->n_routers;
	int cont = 0;

	int* des = (int*)can_fail_malloc(sizeof(int)* (n+1));
	int* parent = (int*)can_fail_malloc(sizeof(int)* (n+1));
	int* low = (int*)can_fail_malloc(sizeof(int)*(n+1));

	for(i=0;i<n+1;i++){
		parent[i] = -1;
	}
	
	for(i=n;i>0;i--){
		if(graph->visited[i]==0){
			ids[cont] = i;
			cont+= 1;
			DFS(graph, i, parent, des, low);
		}
	}
	return cont;
}

node_t* createNode(int r){
	node_t* newNode = can_fail_malloc(sizeof(node_t));
	newNode->r_num = r;
	newNode->next = NULL;
	return newNode;
}

graph_t* createGraph(int routers){
	graph_t* newGraph = can_fail_malloc(sizeof(graph_t));
	newGraph->n_routers = routers;
	newGraph->adjLists = can_fail_malloc((routers + 1) * sizeof(struct node_t*));
	newGraph->visited = can_fail_malloc((routers + 1) * sizeof(int));

	newGraph->ap = can_fail_malloc((routers + 1) * sizeof(int));

	int i;
	for(i=0; i<routers+1; i++){
		newGraph->adjLists[i] = NULL;
		newGraph->visited[i] = 0;
		newGraph->ap[i] = 0;

	}
	return newGraph;
}

void addConnection(graph_t* graph, int u, int v){
	node_t * newNode = createNode(v);
	newNode->next = graph->adjLists[u];
	graph->adjLists[u] = newNode;

	newNode = createNode(u);
	newNode->next = graph->adjLists[v];
	graph->adjLists[v] = newNode; 
}

int DFS_Aux(graph_t* graph){
	int i;
	int n = graph->n_routers;
	int Syze = 0;
	int identifier = 0;

	for(i=n;i>0;i--){
		if(graph->visited[i]==1 && graph->ap[i]!=1){
			Syze = DFS_Ap(graph, i);
			if(identifier < Syze){
				identifier = Syze;
			}
		}
	}
	return identifier;
}

int DFS_Ap(graph_t* graph, int router){

	int contaCenas=1;

	node_t* adjList = graph->adjLists[router];
	node_t* t_node = adjList;

	graph->visited[router] = 0;

	while(t_node!=NULL){
		int connectedRouter = t_node->r_num;

		if(graph->visited[connectedRouter] == 1 && graph->ap[connectedRouter] != 1){	
			contaCenas += DFS_Ap(graph, connectedRouter);	
		}
		t_node = t_node->next;
	}
	return contaCenas;
}
