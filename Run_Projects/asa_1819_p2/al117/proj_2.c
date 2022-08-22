/*Projeto 2 ASA

Grupo 117
Pedro Campos - 83951
Tiago Lopes - 86518
*/

#include <stdio.h>
#include <stdlib.h>

int mincut_i = 0;

/*Struct*/

struct Node{
	int id;
	int capacity;
	int flow;
	int type;
	int cut;
};


struct Graph{
	int num_nodes;
	int num_edges;
	int num_supliers;
	int num_stations;
	int* bfs_parent;
	int* bfs_level;
	int* dfs_visited;
	int* mincut_visited;
	int* nodes_increment;
	struct Edge** edges_increment;
	struct Node* nodesList;
	struct Edge** edgeList;
};

struct Edge{
	int o;
	int d;
	int capacity;
	int flow;
	int cut;
	struct Edge *next;
};
	
struct Graph* createGraph(int num_supliers, int num_stations, int num_edges);
struct Edge* createEdge(int o, int d, int capacity);
void add_edge(struct Graph* graph, int o, int d, int capacity);
void mincut(struct Graph* graph, int t, int ps);

struct Graph* scanInput();

int bfs(struct Graph* graph, int s, int t);
void dfs_visit(struct Graph *graph, int s);

int Dinic(struct Graph *graph, int s, int t);
int sendFlow(int s, int t, int increment, struct Graph *graph);


void printfgraph(struct Graph* graph);
int min(int x, int y);


int main(){
	int i, j, num_print_nodes=0, num_s_nodes=0;
	struct Graph* graph = scanInput();
	printf("%d\n", Dinic(graph, 0, 1));
	dfs_visit(graph, 1);
	mincut(graph, 1, 1);
	for(i=0; i<graph->num_nodes; i++){
		if(graph->nodes_increment[i]==1)
			num_print_nodes++;
		if(graph->nodes_increment[i]==1 && graph->nodesList[i].type ==1)
			num_s_nodes++;
	}
	if(num_print_nodes==0 || num_print_nodes==num_s_nodes)
		printf("\n");
	if(num_print_nodes!=num_s_nodes || num_s_nodes==0){
		int edge_out[graph->num_nodes][graph->num_nodes];
		for(i=0; i<graph->num_nodes; i++){
			for(j=0; j<graph->num_nodes; j++){
				edge_out[i][j]=0;
			}
		}
		for(i=0; i<graph->num_nodes; i++){
			if(graph->nodesList[i].type !=1 && graph->nodes_increment[i]==1)
				printf("%d\n", i);
		}
		for(i=0; i<mincut_i; i++){
			if(graph->edges_increment[i]){
				edge_out[graph->edges_increment[i]->d][graph->edges_increment[i]->o]=1;
			}
		}
		for(i=0; i<graph->num_nodes; i++){
			for(j=0; j<graph->num_nodes; j++){
				if(edge_out[i][j]==1)
					printf("%d %d\n",i, j );
			}
		}
	}
	return 0;
}

struct Graph* scanInput(){
	int i, j=2, capacity, total_capacity=0, o, d;
	int num_supliers, num_stations, num_edges;
	struct Graph* graph;
	struct Node n;
	scanf("%d %d %d", &num_supliers, &num_stations, &num_edges);
	graph = createGraph(num_supliers, num_stations, num_edges);
	for(i=0; i<num_supliers; i++){
		scanf(" %d", &capacity);
		n.capacity = capacity;
		n.flow = 0;
		n.type = 1;
		graph-> nodesList[j] = n;
		add_edge(graph, 0, j, capacity);
		add_edge(graph, j, 0, capacity);
		j++;
		total_capacity+=capacity;
	}
	graph->nodesList[0].flow=total_capacity;
	graph->nodesList[1].capacity=total_capacity;
	for(i=0; i<num_stations; i++){
		scanf(" %d", &capacity);
		n.type = 2;
		n.capacity = capacity;
		graph-> nodesList[j]= n;
		j++;
	}
	for(i=0; i<num_edges; i++){
		scanf("%d %d %d", &o, &d, &capacity);
		add_edge(graph, o, d, capacity);
		add_edge(graph, d, o, capacity);
		j++;
	}
	return graph;
}




struct Graph* createGraph(int num_supliers, int num_stations, int num_edges){
	int i;
	struct Graph* graph = malloc(sizeof(struct Graph));
	graph -> num_supliers = num_supliers;
	graph -> num_stations = num_stations;
	graph -> num_edges = num_edges;
	graph -> num_nodes = num_stations+num_supliers+2;
	graph -> nodesList = malloc((graph->num_nodes) * sizeof(struct Node));
	graph -> edgeList = malloc((graph->num_nodes) * sizeof(struct Edge));
	graph -> bfs_parent = malloc((graph->num_nodes) * sizeof(struct Node));
	graph -> bfs_level = malloc((graph->num_nodes) * sizeof(struct Node));
	graph -> dfs_visited = malloc((graph->num_nodes) * sizeof(int));
	graph -> mincut_visited = malloc((graph->num_nodes) * sizeof(int));
	graph -> edges_increment = malloc((graph->num_edges) * sizeof(struct Edge));
	graph -> nodes_increment = malloc((graph->num_nodes) * sizeof(int));
	for(i=0; i<graph->num_nodes; i++){
		graph->dfs_visited[i]=-1;
		graph->nodes_increment[i]=0;
		graph -> mincut_visited[i]=0;
	}
	for(i=0; i<graph->num_edges; i++){
		graph -> edges_increment[i] = NULL;
	}
	return graph;
}

struct Edge* createEdge(int o, int d, int capacity){
	struct Edge* edge= malloc(sizeof(struct Edge));
	edge -> o = o;
	edge -> d = d;
	edge -> flow = 0;
	edge -> capacity = capacity;
	edge -> next = NULL;
	return edge;
}

void add_edge(struct Graph* graph, int o, int d, int capacity){
	struct Edge* aux = createEdge(o, d, capacity);
	aux -> next = graph -> edgeList[o];
	graph -> edgeList[o] = aux;
}



int bfs(struct Graph *graph, int s, int t){
	struct Edge *edge_aux = malloc(sizeof(struct Edge));
	int i, par, lev, flag=1;

	for(i=0; i<=graph->num_nodes; i++){
		graph->bfs_parent[i]=-1;
		graph->bfs_level[i]=-1;
	}

	int *level = graph->bfs_level;
	int *parent = graph->bfs_parent;

	lev=0;
	level[s]=lev;

	while(flag){
		flag=0;
		for(i=0; i<graph->num_nodes; i++){
			if(level[i]==lev){

				flag=1;
				edge_aux = graph->edgeList[i];
				par = i;

				while(edge_aux!= NULL){
					if(level[edge_aux->d]!=-1 || edge_aux->capacity - edge_aux->flow <= 0 || graph->nodesList[edge_aux->d].capacity- graph->nodesList[edge_aux->d].flow<=0){
						edge_aux=edge_aux->next; 	
					}
					else{
						level[edge_aux->d]=lev+1;
						parent[edge_aux->d]=par;
						edge_aux=edge_aux->next;
					}
				}
			}
		}
		++lev;
	}
	graph->bfs_level=level;
	graph->bfs_parent=parent;
	return level[t]!=-1;
}


int Dinic(struct Graph *graph, int s, int t){
	int max_flow=0;
	int flow;
	int increment = 100000000;
	while(bfs(graph, s, t)){
		while((flow=sendFlow(s, t, increment, graph)))
			max_flow+=flow;
	}
	return max_flow;
}

int sendFlow(int s, int t, int flow, struct Graph *graph){
	struct Edge *edge_aux = malloc(sizeof(struct Edge));
	struct Edge *edge_aux_2 = malloc(sizeof(struct Edge));
	if(s == t){
		return flow;
	}
	edge_aux = graph->edgeList[s];
	while(edge_aux){
		if(graph->bfs_level[edge_aux->d]==graph->bfs_level[s]+1 && edge_aux->capacity>edge_aux->flow && graph->nodesList[edge_aux->d].capacity>graph->nodesList[edge_aux->d].flow){
			int current_flow=min(flow, edge_aux->capacity-edge_aux->flow);
			current_flow=min(current_flow, graph->nodesList[edge_aux->d].capacity-graph->nodesList[edge_aux->d].flow);
			int temp_flow = sendFlow(edge_aux->d, t, current_flow, graph);

			if(temp_flow>0){
				edge_aux->flow+=temp_flow;
				graph->nodesList[edge_aux->d].flow+=temp_flow;
				edge_aux_2=graph->edgeList[edge_aux->d];
				while(edge_aux_2->d != s)
					edge_aux_2=edge_aux_2->next;
				edge_aux_2->flow+=temp_flow;
				return temp_flow;
			}
		}
		edge_aux=edge_aux->next;
	}
	return 0;
}

void dfs_visit(struct Graph *graph, int s){
	struct Edge *edge_aux = malloc(sizeof(struct Edge));
	graph->dfs_visited[s]=1;
	edge_aux = graph->edgeList[s];
	while(edge_aux){
		if(graph->dfs_visited[edge_aux->d]==-1 && edge_aux->capacity > edge_aux->flow){
			if(graph->nodesList[edge_aux->o].capacity > graph->nodesList[edge_aux->o].flow || edge_aux->o == 1){
				graph->dfs_visited[edge_aux->d]=1;
				dfs_visit(graph, edge_aux->d);
			}
		}
		edge_aux=edge_aux->next;
	}
}

void mincut(struct Graph *graph, int s, int ps){
	int j;
	int flag = 1;
	struct Edge *edge_aux = malloc(sizeof(struct Edge));
	edge_aux=graph->edgeList[s];
	graph->mincut_visited[s]=1;

	while(edge_aux){

		if(graph->dfs_visited[edge_aux->d]==1 && edge_aux->d != 0 && edge_aux->d != ps){
			flag=0;
			if(graph->mincut_visited[edge_aux->d]!=1)
				mincut(graph, edge_aux->d, s);
		}
		if(graph->dfs_visited[edge_aux->d]!=1 && edge_aux->d != 0){
			graph->edges_increment[mincut_i]=edge_aux;
			mincut_i++;
		}
		edge_aux=edge_aux->next;
	}
	if(flag==1 && s!=1){
		graph->nodes_increment[s] = 1;
		for(j=0; j<mincut_i; j++){
			if(graph->edges_increment[j] && graph->edges_increment[j]->o == s)
				graph->edges_increment[j]=NULL;
		}
	}
}


int min(int x, int y){ 
	return y ^ ((x ^ y) & -(x < y)); 
} 
