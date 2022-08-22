/*Projeto 1 ASA

Grupo 117
Pedro Campos - 83951
Tiago Lopes - 86518
*/

#include <stdio.h>
#include <stdlib.h>

/*Structs*/

struct node{
	int id;
	int parent_node;
	struct node* next;
};

struct Graph{
	int num_nodes;
	int* visited;
	int* parent;
	int* articulationPoints;
	int* low;
	int* disc;
	int* subtree_ids;
	int time;
	int bigger_subtree;
	int num_subtrees;
	struct node** adjLists;
};


/*initializing functions*/

struct Graph* createGraph(int num_nodes);
struct node* createNode(int r);
void add_connection(struct Graph* graph, int r1, int r2);
void DFS(struct Graph* graph);
int DFS_visit(struct Graph* graph, int node_index);	
struct Graph* read_input();	
int min(int x, int y);


/*main*/

int main(){
	struct Graph* graph = read_input();
	DFS(graph);
	printf("%d\n", graph->num_subtrees);
	int i, num_articulationPoints = 0;
	for(i=1; i<=graph->num_nodes; i++){
		if(graph->subtree_ids[i]==1){
			if(i==graph->num_nodes)
				printf("%d",i);
			else
				printf("%d ",i);
		}
		if (graph->articulationPoints[i]==1){
			num_articulationPoints++;
		}
	}
	printf("\n%d\n",num_articulationPoints);
	DFS(graph);
	printf("%d\n", graph->bigger_subtree);
	return 0;
}

/*Graph functions*/

struct Graph* createGraph(int num_nodes){
	int i;
	struct Graph* graph = malloc(sizeof(struct Graph));
	graph -> num_nodes = num_nodes;
	graph -> adjLists = malloc((1+num_nodes)*sizeof(struct node*));
   	graph -> visited = malloc((1+num_nodes) * sizeof(int));
   	graph -> parent = malloc((1+num_nodes) * sizeof(int));
   	graph -> articulationPoints = malloc((1+num_nodes) * sizeof(int));
   	graph -> subtree_ids = malloc((1+num_nodes) * sizeof(int));
   	graph -> low = malloc((1+num_nodes) * sizeof(int));
   	graph -> disc = malloc((1+num_nodes) * sizeof(int));
    for (i = 1; i < num_nodes+1; i++){
        graph -> adjLists[i] = NULL;
        graph -> articulationPoints[i] = 0;
    }
    return graph;
}

struct node* createNode(int r){
	struct node* newNode = malloc(sizeof(struct node));
	newNode -> id = r;
	newNode -> next = NULL;
	return newNode;
}

void add_connection(struct Graph* graph, int r1, int r2){
	struct node* newNode = createNode(r2);
	newNode -> next = graph -> adjLists[r1];
	graph -> adjLists[r1] = newNode;

	newNode = createNode(r1);
	newNode -> next = graph -> adjLists[r2];
	graph -> adjLists[r2] = newNode;
}



/*DFS functions*/

void DFS(struct Graph* graph){
	int num_nodes = graph->num_nodes;
	int i;
	int subtree_id, num_subtrees=0, bigger_subtree_aux=0;
	graph->time=0;

	
	for(i=1; i<=num_nodes; i++){
		graph -> visited[i]=0;
		graph -> parent[i] = 0;
        graph -> low[i] = -1;
        graph -> disc[i] = 0;
	}

	for(i=1; i<= num_nodes; i++){
		graph->time+=1;
		if(graph->visited[i]==0 && graph->articulationPoints[i]==0){
			graph->bigger_subtree=1;
			subtree_id=DFS_visit(graph, i);
			num_subtrees++;
			graph->subtree_ids[subtree_id]=1;
			if(bigger_subtree_aux<graph->bigger_subtree)
				bigger_subtree_aux=graph->bigger_subtree;
		}
	}

	graph->num_subtrees = num_subtrees;
	graph->bigger_subtree=bigger_subtree_aux;
}

int DFS_visit(struct Graph* graph, int node_id){
	struct node* node_next = graph->adjLists[node_id];
	int nr_children=0, max_node=0, max_node_aux=0;
	graph->visited[node_id]=1;
	graph->disc[node_id] = graph->low[node_id] = graph->time++;
	while(node_next){
		if(graph->visited[node_next->id]==0 && graph->articulationPoints[node_next->id]==0){
			graph->parent[node_next->id]=node_id;
			nr_children++;
			max_node_aux = DFS_visit(graph, node_next->id);
			graph->bigger_subtree++;

			graph->low[node_id]= min(graph->low[node_id], graph->low[node_next->id]);
			if((graph->parent[node_id] == 0 && nr_children>1) || (graph->parent[node_id] != 0 && graph->low[node_next->id]>=graph->disc[node_id]))
				graph->articulationPoints[node_id]=1;
		}
		else if(graph->parent[node_id] != node_next->id)
			graph->low[node_id]= min(graph->low[node_id], graph->disc[node_next->id]);

		if(max_node < max_node_aux)
			max_node = max_node_aux;
		if(max_node < node_id)
			max_node = node_id;

		node_next = node_next->next;
	}
	return max_node;
}

/* other functions*/

struct Graph* read_input(){
	int i, r1, r2, num_routers, num_connections;
	scanf("%d\n%d\n", &num_routers, &num_connections);
	struct Graph* graph = createGraph(num_routers);
	for(i=0;i<num_connections;i++){
		scanf("%d %d", &r1, &r2);
		add_connection(graph, r1, r2);
	}
	return graph;
}

int min(int x, int y){ 
	return y ^ ((x ^ y) & -(x < y)); 
} 
