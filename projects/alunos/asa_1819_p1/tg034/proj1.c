#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#define VISITED 1


typedef struct node{

	unsigned long int id;
	struct node* next_node;

} * Node;



typedef struct router {

	unsigned long int id;
	int visited;
	Node list_of_connections;
	unsigned long int low;
	unsigned long int discovery_time;
	unsigned long int deleted;

} * Router;





Router readInput(unsigned long int number_of_routers);
void addConnection(Router, unsigned long int id1, unsigned long int id2);
Node createConnection(unsigned long int id);
void findSCC(Router routers, unsigned long int number_of_routers);
unsigned long int DFS(Router routers, unsigned long int position, unsigned long int *time, unsigned long int* articulation_points);
Node addSCC(Node list, unsigned long int id);
void printSCC(Node list, unsigned long int number_of_SCC);
unsigned long int min(unsigned long int a, unsigned long int b, unsigned long int c);
void findBiggestSCC(Router routers, unsigned long int number_of_routers);
void newDFS(Router routers, unsigned long int position, unsigned long int *counter);
void MergeSort(Node *headRef);
void FrontBackSplit(Node source, Node* frontRef, Node* backRef);
Node SortedMerge(Node a, Node b);


int main() {


	Router list_of_routers;
	unsigned long int number_of_routers;
	scanf("%lu", &number_of_routers);
	list_of_routers = readInput(number_of_routers);
	findSCC(list_of_routers, number_of_routers);
	findBiggestSCC(list_of_routers, number_of_routers);

	return 0;
}



Router readInput(unsigned long int number_of_routers) {


	unsigned long int router1_id = 0;
	unsigned long int router2_id = 0;
	unsigned long int number_of_connections = 0;
	int i;
	Router routers;
	scanf("%lu", &number_of_connections);
	
	routers = (Router)can_fail_malloc(sizeof(struct router)*number_of_routers);

	for (i = 0; i < number_of_routers; i++) {

		routers[i].id = i + 1;
		routers[i].list_of_connections = NULL;
		routers[i].visited = !VISITED;
		routers[i].discovery_time = 0;
		routers[i].low = 0;
		routers[i].deleted=0;

	}

	for (i = 0; i < number_of_connections; i++) {

		scanf("%lu %lu", &router1_id, &router2_id);
		addConnection(routers, router1_id, router2_id);
		addConnection(routers, router2_id, router1_id);

	}

	return routers;


}

void addConnection(Router routers, unsigned long int id1, unsigned long int id2) {

	Node new = createConnection(id2);
	new->next_node = routers[id1-1].list_of_connections;
	routers[id1-1].list_of_connections = new;

}

Node createConnection(unsigned long int id) {

	Node new = (Node)can_fail_malloc(sizeof(struct node));
	new->id = id;
	return new;
	
}





void findSCC(Router routers, unsigned long int number_of_routers) {

	unsigned long int i;
	unsigned long int number_of_SCC = 0;
	unsigned long int SCC_id;
	Node SCC_list = NULL;
	unsigned long int* time;
	unsigned long int articulation_points = 0;
	unsigned long int aux = 1;


	time = &aux;	

	for (i = 0; i < number_of_routers; i++) {

		SCC_id = 0;

		if (routers[i].visited) {
			continue;
		}

		SCC_id = DFS(routers, i, time, &articulation_points);
		SCC_list = addSCC(SCC_list, SCC_id);
		number_of_SCC++;
		aux = 1;
		time = &aux;


	}

	MergeSort(&SCC_list);
	printSCC(SCC_list, number_of_SCC);
	printf("%lu\n", articulation_points);


}


unsigned long int DFS(Router routers, unsigned long int position, unsigned long int *time, unsigned long int *articulation_points) {

	Node c;
	unsigned long int biggest = 0;
	unsigned long int x;
	unsigned long int aux = 0;
	int found_articulation = 0;
	int children = 0;

	routers[position].visited = VISITED;

	routers[position].discovery_time = (*time)++;
	for (c = routers[position].list_of_connections; c != NULL; c = c->next_node) {

		if (!(routers[c->id - 1].visited)) {

			x = DFS(routers, c->id - 1, time, articulation_points);
			biggest = x > biggest? x : biggest;
			(*time)++;
			children++;
			aux = min(routers[position].discovery_time, routers[c->id - 1].low, aux);

			if (routers[c->id -1].low >= routers[position].discovery_time && !(found_articulation) && routers[position].discovery_time != 1) {
				
				(*articulation_points)++;
				found_articulation = 1;
				routers[position].deleted=1;
			}

			if (routers[position].discovery_time == 1 && children > 1 && !found_articulation) {

				 (*articulation_points)++;
				 found_articulation = 1;
				 routers[position].deleted=1;
			} 

		}

		else {

			aux = min(routers[position].discovery_time, routers[c->id - 1].discovery_time, aux);
			
		}

		
		
	}

	routers[position].low = aux;



	if (biggest > routers[position].id) 
		return biggest;

	return routers[position].id;

}



unsigned long int min(unsigned long int a, unsigned long int b, unsigned long int c) {

	unsigned long int smallest;

	if (a > b)
		smallest = b;
	else
		smallest = a;

	if (c < smallest && c != 0)
		return c;

 	return smallest;

}

Node addSCC(Node list, unsigned long int id) {


	Node new = (Node)can_fail_malloc(sizeof(struct node));
	new->id = id;
	new->next_node = list;
	return new;


}


void printSCC(Node list, unsigned long int number_of_SCC) {

	Node n;

	printf("%lu\n", number_of_SCC);

	for (n = list; n != NULL; n = n->next_node) {

		if (n->next_node != NULL)
			printf("%lu ", n->id);
		else
			printf("%lu",n->id);

	}

	printf("\n");
}



void findBiggestSCC(Router routers, unsigned long int number_of_routers) {

	int i;
	unsigned long int biggest = 0;
	unsigned long int counter = 0;


	for (i = 0; i < number_of_routers; i++) {


		if (!(routers[i].visited) || routers[i].deleted) {

			continue;
		}

		newDFS(routers, i, &counter);
	
		if (counter > biggest)
			biggest = counter;

		counter = 0;


	}
	printf("%lu\n", biggest);

}	

void newDFS(Router routers, unsigned long int position, unsigned long int *counter) {


	Node c;
	routers[position].visited = !VISITED;
	(*counter)++;

	for (c = routers[position].list_of_connections; c != NULL; c = c->next_node) {

		if (routers[c->id - 1].visited && !(routers[c->id - 1].deleted)) {

			newDFS(routers, c->id - 1, counter);

		}
	}
}



void MergeSort(Node *headRef) {

	Node head = *headRef; 
	Node a; 
	Node b; 
	  
	
	if ((head == NULL) || (head->next_node == NULL))
	    return; 
	 
	  
	
	FrontBackSplit(head, &a, &b);  
	  
	
	MergeSort(&a); 
	MergeSort(&b); 
	  
	
	*headRef = SortedMerge(a, b); 
} 
 

Node SortedMerge(Node a, Node b) { 
	Node result = NULL; 
	  
	
	if (a == NULL) 
	    return(b); 

	else if (b==NULL) 
	    return(a); 
	  
	
	if (a->id <= b->id) { 

	    result = a; 
	    result->next_node = SortedMerge(a->next_node, b); 

	}else { 

	    result = b; 
	    result->next_node = SortedMerge(a, b->next_node); 

	} 

	return(result); 
} 


void FrontBackSplit(Node source, Node* frontRef, Node* backRef) { 

    Node fast; 
    Node slow; 
    slow = source; 
    fast = source->next_node; 
  
    while (fast != NULL) { 

	    fast = fast->next_node; 
	    if (fast != NULL) { 

	        slow = slow->next_node; 
	        fast = fast->next_node; 

	    } 

    } 
  
    *frontRef = source; 
    *backRef = slow->next_node; 
    slow->next_node = NULL; 
} 
