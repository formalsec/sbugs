#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#define VISITED 1


typedef struct node{

	unsigned long int id;
	unsigned long int from;
	unsigned long int capacity;
	unsigned long int flow;
	struct node* next_node;
	int inCut;

} * Node;


typedef struct p_Connection {

	Node node_pointer;
	struct p_Connection* next;
	
} * P_Connection;



typedef struct vertex {

	unsigned long int id;
	int visited;
	int reachable;	
	unsigned long int flow;
	unsigned long int height;
	Node list_of_connections;
	Node c_tail;



	P_Connection list_of_previous;
	
} * Vertex;


typedef struct p_Vertex {

	Vertex v;
	struct p_Vertex* next;

} * P_Vertex;






void readConections(Vertex list_of_vertexes, unsigned long int number_of_connections, unsigned long int number_of_productors, unsigned long int number_of_suppliers);
void addConnection(Vertex, unsigned long int id1, unsigned long int id2, unsigned long int cpct);
Node createConnection(unsigned long int id1, unsigned long int id2, unsigned long int cpct);
void print_List(unsigned long int number_of_vertexes, Vertex vertexs);
Vertex Inicialize(unsigned long int number_of_vertexes);
void GetProductors(Vertex list_of_vertexes,unsigned long int number_of_suppliers);
void Getsuppliers(Vertex list_of_vertexes,unsigned long int f, unsigned long int number_of_suppliers);
void findMaxFLow(Vertex list_of_vertexes, unsigned long int number_of_vertexes);
void findReachable(Vertex list_of_vertexes, unsigned long int position);
void findCut(Vertex list_of_vertexes, unsigned long int id, unsigned long int number_of_productors, unsigned long int number_of_suppliers, P_Vertex *supplier_list, P_Connection *edge_list);
void printSup(P_Vertex supplier_list);
void sortsuppliers(P_Vertex *headRef);
P_Vertex  sortedMergeSup(P_Vertex  a, P_Vertex  b);
void frontBackSplitSup(P_Vertex  source, P_Vertex * frontRef, P_Vertex * backRef);
void printEdge(P_Connection edge_list, unsigned long int number_of_suppliers, unsigned long int number_of_productors);
void sortEdges(P_Connection *headRef);
P_Connection sortedMergeEdge(P_Connection a, P_Connection b);
void frontBackSplitEdge(P_Connection source, P_Connection * frontRef, P_Connection * backRef);







int main() {


	Vertex list_of_vertexes;
	P_Connection edge_list = NULL;
	P_Vertex supplier_list = NULL;
	unsigned long int number_of_productors,number_of_suppliers,number_of_connections,number_of_vertexes;
	scanf("%lu %lu %lu", &number_of_productors,&number_of_suppliers,&number_of_connections);
	number_of_vertexes=number_of_productors + (number_of_suppliers*2) + 2;
	list_of_vertexes = Inicialize(number_of_vertexes);
	GetProductors(list_of_vertexes,number_of_productors);
	Getsuppliers(list_of_vertexes, number_of_productors, number_of_suppliers);
	readConections(list_of_vertexes, number_of_connections, number_of_productors, number_of_suppliers);
	findMaxFLow(list_of_vertexes, number_of_vertexes);
	findReachable(list_of_vertexes,1);
	findCut(list_of_vertexes,0, number_of_productors, number_of_suppliers, &supplier_list, &edge_list);
	printSup(supplier_list);
	printEdge(edge_list, number_of_suppliers, number_of_productors);
	/*print_List(number_of_vertexes, list_of_vertexes);*/



	return 0;
}

Vertex Inicialize(unsigned long int number_of_vertexes){
	int i;
	Vertex vertexes;
	
	vertexes = (Vertex)can_fail_malloc(sizeof(struct vertex)*number_of_vertexes);

	for (i = 0; i < number_of_vertexes; i++) {

		vertexes[i].id = i;
		vertexes[i].list_of_connections = NULL;
		vertexes[i].c_tail = NULL;
		vertexes[i].visited = !VISITED;
		vertexes[i].reachable = 0;
		vertexes[i].height = i != 0? 0: number_of_vertexes;
		vertexes[i].flow = 0;
		vertexes[i].list_of_previous = NULL;

	}

	return vertexes;
}

void GetProductors(Vertex list_of_vertexes,unsigned long int number_of_productors){
	int i=0;
	unsigned long int prodcap;
	while(i < number_of_productors){
		scanf("%lu",&prodcap);
		addConnection(list_of_vertexes, 0, i + 2, prodcap);
		list_of_vertexes[i + 2].flow = prodcap;
		list_of_vertexes[0].c_tail->flow = prodcap;
		i++;
	}
}
	
void Getsuppliers(Vertex list_of_vertexes, unsigned long int f, unsigned long int number_of_suppliers){
	int i = f;
	unsigned long int supcap;
	while(i < number_of_suppliers + f){
		scanf("%lu",&supcap);
		addConnection(list_of_vertexes, i + 2, i + 2 + number_of_suppliers, supcap);
		i++;
	}	
}


void readConections(Vertex list_of_vertexes, unsigned long int number_of_connections, unsigned long int number_of_productors, unsigned long int number_of_suppliers) {


	unsigned long int vertex1_id = 0;
	unsigned long int vertex2_id = 0;
	unsigned long int capacity = 0;
	int i;

	for (i = 0; i < number_of_connections; i++) {

		scanf("%lu %lu %lu", &vertex1_id, &vertex2_id, &capacity);
		if (vertex1_id < (number_of_productors + 2))
			addConnection(list_of_vertexes, vertex1_id, vertex2_id, capacity);
		else 
			addConnection(list_of_vertexes, vertex1_id + number_of_suppliers, vertex2_id,capacity);
	}

}

void addConnection(Vertex vertexes, unsigned long int id1, unsigned long int id2, unsigned long int cpct) {

	Node new = createConnection(id1,id2, cpct);
	P_Connection new_previous = (P_Connection)can_fail_malloc(sizeof(struct p_Connection));


	if (vertexes[id1].list_of_connections == NULL){

		vertexes[id1].list_of_connections = new;
		

	}else {
		vertexes[id1].c_tail->next_node = new;
	}


	vertexes[id1].c_tail = new;
	new_previous->node_pointer = new;
	new_previous->next = vertexes[id2].list_of_previous;
	vertexes[id2].list_of_previous = new_previous;

	

}

Node createConnection(unsigned long int id1, unsigned long int id2, unsigned long int cpct) {

	Node new = (Node)can_fail_malloc(sizeof(struct node));
	new->id = id2;
	new->from = id1;
	new->capacity = cpct;
	new->next_node = NULL;
	new->inCut = 0;
	return new;
	
}


void findMaxFLow(Vertex list_of_vertexes, unsigned long int number_of_vertexes) {
	int i;
	int done = 0;
	unsigned long int x;
	Node c;
	P_Connection p;
	while (!done) {
		done = 1;
		for (i = 2; i < number_of_vertexes; i++) {
			
			while (list_of_vertexes[i].flow != 0) {
				done = 0;
				for (c = list_of_vertexes[i].list_of_connections; c != NULL; c = c->next_node) {
					
					x = c->capacity - c->flow;
					
					
					if (list_of_vertexes[i].height > list_of_vertexes[c->id].height) {
						
						if (list_of_vertexes[i].flow <= x) {
						
							
							c->flow = c->flow + list_of_vertexes[i].flow;
							list_of_vertexes[c->id].flow = list_of_vertexes[c->id].flow + list_of_vertexes[i].flow;
							list_of_vertexes[i].flow = 0;
							

						}else {	
							
							list_of_vertexes[i].flow = list_of_vertexes[i].flow - (c->capacity - c->flow);
							list_of_vertexes[c->id].flow = list_of_vertexes[c->id].flow + (c->capacity - c->flow);
							c->flow = c->capacity;
							
						}
					}
				}

			

				if (list_of_vertexes[i].flow != 0) {

					for (p = list_of_vertexes[i].list_of_previous; p != NULL; p = p->next) {
						if (list_of_vertexes[i].height > list_of_vertexes[p->node_pointer->from].height && p->node_pointer->capacity != 0) {
						
							if (list_of_vertexes[i].flow >= p->node_pointer->flow) {
								
								list_of_vertexes[i].flow = (list_of_vertexes[i].flow - p->node_pointer->flow);
								list_of_vertexes[p->node_pointer->from].flow = list_of_vertexes[p->node_pointer->from].flow + p->node_pointer->flow;
								p->node_pointer->flow = 0;
								
								
		
							} else {
								
								list_of_vertexes[p->node_pointer->from].flow = list_of_vertexes[p->node_pointer->from].flow + list_of_vertexes[i].flow;
								p->node_pointer->flow = p->node_pointer->flow - list_of_vertexes[i].flow;
								list_of_vertexes[i].flow = 0;

							}
						}
					}

				}


				
				if (list_of_vertexes[i].flow != 0){
					list_of_vertexes[i].height++;
				}

				
			}

		}


	}

	printf("%lu\n", list_of_vertexes[1].flow);


}



void findReachable(Vertex list_of_vertexes, unsigned long int id) {

	P_Connection p;
	Node c;
	list_of_vertexes[id].reachable = VISITED;
	for (p = list_of_vertexes[id].list_of_previous; p !=  NULL; p = p->next) {

		if (p->node_pointer->flow != p->node_pointer->capacity) {
		
			if (!list_of_vertexes[p->node_pointer->from].reachable)
				findReachable(list_of_vertexes, p->node_pointer->from);

		}
	}

	for (c = list_of_vertexes[id].list_of_connections; c != NULL; c = c->next_node) {
		if (c->flow == c->capacity && !list_of_vertexes[c->id].reachable) 
			findReachable(list_of_vertexes, c->id);
	}
}


void findCut(Vertex list_of_vertexes, unsigned long int id, unsigned long int number_of_productors, unsigned long int number_of_suppliers, P_Vertex *supplier_list, P_Connection *edge_list) {

	Node c;
	
	list_of_vertexes[id].visited = VISITED;




	for (c = list_of_vertexes[id].list_of_connections; c != NULL; c = c->next_node) {
		

		if (!c->inCut){	
			
			if (!list_of_vertexes[c->from].reachable && list_of_vertexes[c->id].reachable && c->capacity == c->flow){
				if (c->from != 0){
					if (c->from < number_of_productors + 2 || (c->from >= number_of_productors + 2 && c->id != c->from + number_of_suppliers)){



						P_Connection new_edge = (P_Connection)can_fail_malloc(sizeof(struct p_Connection));
						new_edge->node_pointer = c;
						new_edge->next = (*edge_list);
						(*edge_list) = new_edge;

						c->inCut = 1;

					}else {

						P_Vertex new = (P_Vertex)can_fail_malloc(sizeof(struct p_Vertex));
						new->v = &list_of_vertexes[c->from];
						new->next = (*supplier_list);
						(*supplier_list) = new;

					}
				}
			}else {
				if (!list_of_vertexes[c->id].visited)
					findCut(list_of_vertexes, c->id, number_of_productors, number_of_suppliers, supplier_list, edge_list);
			}



		}
	}


	
	
}




void printSup(P_Vertex supplier_list) {

	P_Vertex p;
	sortsuppliers(&supplier_list);
	for (p = supplier_list; p != NULL; p = p->next) {
		if (p->next != NULL)
			printf("%lu ",p->v->id);
		else 
			printf("%lu",p->v->id);
	}

	printf("\n"	);
}

void printEdge(P_Connection edge_list, unsigned long int number_of_suppliers, unsigned long int number_of_productors) {
	P_Connection p;
	sortEdges(&edge_list);
	for (p = edge_list; p != NULL; p = p->next) {
		if (p->node_pointer->from >= number_of_productors + 2)
			printf("%lu %lu\n", p->node_pointer->from - number_of_suppliers, p->node_pointer->id);
		else 
			printf("%lu %lu\n", p->node_pointer->from, p->node_pointer->id);
	}




}
void sortsuppliers(P_Vertex *headRef) {

	P_Vertex  head = *headRef; 
	P_Vertex  a; 
	P_Vertex  b; 
	  
	
	if ((head == NULL) || (head->next == NULL))
	    return; 
	 
	  
	
	frontBackSplitSup(head, &a, &b);  
	  
	
	sortsuppliers(&a); 
	sortsuppliers(&b); 
	  
	
	*headRef = sortedMergeSup(a, b); 
} 
 




P_Vertex  sortedMergeSup(P_Vertex  a, P_Vertex  b) { 
	P_Vertex  result = NULL; 
	  
	
	if (a == NULL) 
	    return(b); 

	else if (b==NULL) 
	    return(a); 
	  
	
	if (a->v->id <= b->v->id) { 

	    result = a; 
	    result->next = sortedMergeSup(a->next, b); 

	}else { 

	    result = b; 
	    result->next = sortedMergeSup(a, b->next); 

	} 

	return(result); 
} 


void frontBackSplitSup(P_Vertex  source, P_Vertex * frontRef, P_Vertex * backRef) { 

    P_Vertex  fast; 
    P_Vertex  slow; 
    slow = source; 
    fast = source->next; 
  
    while (fast != NULL) { 

	    fast = fast->next; 
	    if (fast != NULL) { 

	        slow = slow->next; 
	        fast = fast->next; 

	    } 

    } 
  
    *frontRef = source; 
    *backRef = slow->next; 
    slow->next = NULL; 
} 




void sortEdges(P_Connection *headRef) {
	P_Connection  head = *headRef; 
	P_Connection a; 
	P_Connection b; 
	  
	
	if ((head == NULL) || (head->next == NULL))
	    return; 
	 
	  
	
	frontBackSplitEdge(head, &a, &b);  
	  
	
	sortEdges(&a); 
	sortEdges(&b); 
	  
	
	*headRef = sortedMergeEdge(a, b); 
}

P_Connection sortedMergeEdge(P_Connection a, P_Connection b) {
	P_Connection result = NULL; 
	  
	
	if (a == NULL) 
	    return(b); 

	else if (b==NULL) 
	    return(a); 
	  
	
	if ((a->node_pointer->from < b->node_pointer->from) || ((a->node_pointer->from == b->node_pointer->from) && (a->node_pointer->id < b->node_pointer->id))) { 

	    result = a; 
	    result->next = sortedMergeEdge(a->next, b); 

	}else { 

	    result = b; 
	    result->next = sortedMergeEdge(a, b->next); 

	} 

	return(result); 
}

void frontBackSplitEdge(P_Connection source, P_Connection * frontRef, P_Connection * backRef) {

	P_Connection fast; 
    P_Connection  slow; 
    slow = source; 
    fast = source->next; 
  
    while (fast != NULL) { 

	    fast = fast->next; 
	    if (fast != NULL) { 

	        slow = slow->next; 
	        fast = fast->next; 

	    } 

    } 
  
    *frontRef = source; 
    *backRef = slow->next; 
    slow->next = NULL; 
}