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
	int head;
	int d;
	int low;
};

struct node
{
	item _vertex;
	link next;
};



typedef struct
{
	link* adjacenciesList;
	int verticesNumber;
	int count;
	int biggest_seq;
	item* _vertices;

}Graph;

int time = 0;

int max(int a, int b) {
	if (a >= b) {
		return a;
	}

	return b;
}


int output(Graph graph){
	
	printf("%d %d\n",graph.count, graph.biggest_seq);

	return 0;
}

int visit(Graph* graph, item u){

	u->d = time++;
	u->visited = 1;
	link current = graph->adjacenciesList[u->id];
	while(current != NULL){
		
		if (current->_vertex->visited == 0){
			u->low = max(visit(graph, current->_vertex)+1, u->low);
		}
		else {
			u->low = max(current->_vertex->low+1, u->low);
		}

		current = current->next;
	}

	return u->low;

}

Graph algorithm(Graph graph){

	int i;
	graph.biggest_seq = 0;
	for (i =  0; i < graph.verticesNumber; i++)
	{
		if (graph._vertices[i]->head == 1)
		{
			graph._vertices[i]->low = max(visit(&graph, graph._vertices[i]), graph._vertices[i]->low);

		}
		if (graph.biggest_seq < graph._vertices[i]->low+1) {
			graph.biggest_seq = graph._vertices[i]->low+1;
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
	new->head = 1;
	new->d = -1;
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

	scanf("%d %d", &vertices, &edges);
	graph.adjacenciesList = (link*) can_fail_malloc(sizeof(link)*vertices);
	graph.verticesNumber = vertices;
	graph.count = vertices;
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

		if (graph._vertices[vertexTwo-1]->head == 1) {
			graph._vertices[vertexTwo-1]->head = 0;
			graph.count--;
		}
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
