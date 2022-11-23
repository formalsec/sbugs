#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct node* link;
typedef struct Vertex* item; 



struct Vertex
{
	int id;
	short visited;
	item pi;
	int d;
	int low;
	int articulation;
};

struct node
{
	item _vertex;
	link next;
};



typedef struct
{
	link* adjacenciesList;
	int subNets;
	int verticesNumber;
	int m;
	int count;
	item* _vertices;

}Graph;

int time = 0;


int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int min(int a, int b){
	
	if (a < b)
		return a;
	return b;
}

void DFS(Graph* graph, item u){

	u->visited = 2;
	link current = graph->adjacenciesList[u->id];
	time++;


	while(current != NULL){
		if(current->_vertex->visited == 1){
			DFS(graph, current->_vertex);
		}
		current = current->next;
	}

}


int output(Graph graph){

	int i, j = 0, aux = 0, vec[graph.subNets];	

	for (i =  0; i < graph.verticesNumber; i++){
		if(graph._vertices[i]->articulation > 1){
			vec[j] = graph._vertices[i]->articulation;
			j++;
		}
		if(graph._vertices[i]->visited == 1){
			time = 0;
			DFS(&graph, graph._vertices[i]);
			if(aux <= time){
				aux = time;
			}
		}
		free(graph._vertices[i]);
	}

	if(graph.subNets > 1){
		qsort(vec, graph.subNets, sizeof(int), cmpfunc);
	}

	printf("%d\n", graph.subNets);
	for(i = 0; i < graph.subNets; i++){
		if(i != graph.subNets-1){
			printf("%d ", vec[i]);
		}
		else{
			printf("%d\n", vec[i]);
		}
	}
	printf("%d\n", graph.count);
	printf("%d\n", aux);

	return 0;
}

void visit(Graph* graph, item u){

	int children = 0;
	u->visited = 1;
	link current = graph->adjacenciesList[u->id];
	u->d = u->low = time++;

	if(graph->m <= u->id+1){
		graph->m = u->id+1;
	}

	
	while(current != NULL){
		if (current->_vertex->visited == 0){
			children++;
			current->_vertex->pi = u;
			visit(graph, current->_vertex);
			u->low = min(u->low, current->_vertex->low);

			if ((u->pi == NULL) && (children > 1) && (u->articulation < 1)){
				u->articulation = 1;
				u->visited = 2;
				graph->count++;
			}

			if ((u->pi != NULL) && (current->_vertex->low >= u->d) && (u->articulation < 1)){
				u->articulation = 1;
				u->visited = 2;
				graph->count++;
			}
		}
		else if (u->pi == NULL){
			u->low = min(u->low, current->_vertex->d);
		}

		else if (current->_vertex->id != u->pi->id){
			u->low = min(u->low, current->_vertex->d);
		}
		
		current = current->next;
	}
}

Graph algorithm(Graph graph){
	
	int i;
	for (i =  0; i < graph.verticesNumber; i++)
	{
		if (graph._vertices[i]->visited == 0)
		{
			graph.m = 0;
			graph.subNets++;
			visit(&graph, graph._vertices[i]);
			graph._vertices[i]->articulation = graph.m;
		}
	}
	return graph;
}

item createVertex(int i)
{
	item new = (item)can_fail_malloc(sizeof(struct Vertex));
	new->id = i;
	new->pi = NULL;
	new->visited = 0;
	new->d = -1;
	new->articulation = 0;
	new->low = 0;
	return new;
}


link createNode(item i)
{
	link new = (link) can_fail_malloc(sizeof(struct node));
	new->_vertex = i;
	new->next = NULL;
	return new;
}


link insertLinkedList(item i, link head)
{
	link new = createNode(i);
	if (head == NULL){
		head = new;
	}
	else
	{
		new->next = head;
		head = new;
	}
	return head;
}


Graph builtGraph()
{
	int vertices, edges, vertexOne, vertexTwo, i;

	Graph graph;

	graph.subNets = 0;
	graph.count = 0;
	scanf("%d %d", &vertices, &edges);
	graph.adjacenciesList = (link*) can_fail_malloc(sizeof(link)*vertices);
	graph.verticesNumber = vertices;
	graph._vertices = (item*) can_fail_malloc(sizeof(item)*vertices);

	for (i = 0; i < vertices; i++)
	{
		graph.adjacenciesList[i] = NULL;
		graph._vertices[i] = createVertex(i);
	}

	for (i = 0; i < edges; i++)
	{
		scanf("%d %d", &vertexOne, &vertexTwo);
		graph.adjacenciesList[vertexOne-1] = insertLinkedList(graph._vertices[vertexTwo-1], graph.adjacenciesList[vertexOne-1]);
		graph.adjacenciesList[vertexTwo-1] = insertLinkedList(graph._vertices[vertexOne-1], graph.adjacenciesList[vertexTwo-1]);
	}
	return graph;
}


int main()
{

	Graph graph = builtGraph();
	graph = algorithm(graph);
	output(graph);

	
	return 0;
}

