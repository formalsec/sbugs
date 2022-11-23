#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* MACROS */
#define MAX_LEN 8000
#define min(X, Y) (((X) < (Y)) ? (X) : (Y))

/* Structs */

typedef struct connection {
	int id;
	int capacity;
	int flow;
	struct connection *next;
}Connection;

typedef struct vertex {
	int id;
	int excess;
	int height;
	Connection *head,*tail, *current;
	struct vertex *next, *prev;
}Vertex;

typedef struct vertex_list {
	Vertex *head, *tail;
}Vertex_List;

typedef struct cut {
	int source;
	int dest;
}Cut;

typedef struct network {
	int n_suppliers;
	int n_stations;
	int n_connections;
	Vertex *vertices;
}Network;


char * readInput() {
	/* Function used to read only one value at a time from the stdin */
	int c,n=0;
	char * input=can_fail_malloc(sizeof(char)*MAX_LEN);

	while((c=getchar())!=' ' && c!='\n') {
		input[n]=c;
		n++;
	}
	return input;
}

void create_vertex (int id,Network *nw) {
	Vertex v;
	v.id=id;
	v.excess=0;
	v.height=0;
	v.head=NULL;
	v.tail=NULL;

	nw->vertices[id]=v;
}

Connection* create_connection () {
	/* Allocate memory for a list connection */
	Connection *c=(Connection*)can_fail_malloc(sizeof(struct connection));

	return c;
}


void vertex_add_conn(int u, int v,int cap,Network *Nw) {
	/* Add v to u's neighbours list  */

	if (Nw->vertices[u].head==NULL) {
		/* Case 1: List is empty */
		Nw->vertices[u].head=Nw->vertices[u].tail=create_connection();
		Nw->vertices[u].head->id=v;
		Nw->vertices[u].head->flow=0;
		Nw->vertices[u].head->capacity=cap;
		Nw->vertices[u].head->next=NULL;
	}

	else if (Nw->vertices[u].head==Nw->vertices[u].tail) {
		/* Case 2: List only has 1 element */
		Nw->vertices[u].tail=create_connection();
		Nw->vertices[u].head->next=Nw->vertices[u].tail;
		Nw->vertices[u].tail->id=v;
		Nw->vertices[u].tail->flow=0;
		Nw->vertices[u].tail->capacity=cap;
		Nw->vertices[u].tail->next=NULL;
	}

	else {
		Connection *c=create_connection();
		Nw->vertices[u].tail->next=c;
		Nw->vertices[u].tail=c;
		Nw->vertices[u].tail->flow=0;
		Nw->vertices[u].tail->capacity=cap;
		c->id=v;
		c->next=NULL;
	}
}


/*  ----------- RELABEL-TO-FRONT ALGORITHM ----------------------------   */


Vertex_List *create_vertex_list(Network *Nw) {
	/* Creates the vertices list used in the Relabel-To-Front algorithm */

	int i;
	Vertex_List *L=(Vertex_List *)can_fail_malloc((Nw->n_suppliers + 2*Nw->n_stations + 2)*sizeof(struct vertex_list));

	L->head = NULL;
	L->tail = NULL;
	
	for (i=2; i<=Nw->n_suppliers + 2*Nw->n_stations +1;i++) {
		if (L->head==NULL) {
			/* Case 1: List is empty */
			L->head=&Nw->vertices[i];
			L->tail = L->head;
			L->head->next=NULL;
			L->head->prev=NULL;
		}

		else if (L->head==L->tail) {
			/* Case 2: List only has 1 element */
			L->tail=&Nw->vertices[i];
			L->head->next=L->tail;
			L->tail->next=NULL;
			L->tail->prev = L->head;
		}

		else {
			L->tail->next=&Nw->vertices[i];
			Nw->vertices[i].prev = L->tail;
			L->tail=&Nw->vertices[i];
			L->tail->next = NULL;
		}
	}
	return L;
}

void initialize_preflow(Network *Nw) {
	/* Part of the Relabel-To-Front algorithm*/

	Nw->vertices[0].height=Nw->n_suppliers+2*Nw->n_stations+2;

	Connection *c=Nw->vertices[0].head;
	while (c!=NULL) {
		c->flow=c->capacity;
		Nw->vertices[c->id].excess=c->capacity;
		Nw->vertices[0].excess -= c->capacity;

		Connection *d=Nw->vertices[c->id].head;
		while (d!=NULL) {
			if(d->id == 0) {
				d->flow -= c->capacity;
				break;
			}
			d=d->next;
		}
		c=c->next;

	}
}

void relabel(Vertex *u, Network *Nw) {
	/* Part of the Relabel-To-Front algorithm*/

	Connection *c=Nw->vertices[u->id].head;
	int  min = INT_MAX;
	while (c!=NULL) {
		if(Nw->vertices[c->id].height < min && (c->capacity != c->flow)) {
			min = Nw->vertices[c->id].height;
		}
		c=c->next;
	}
	u->height = min + 1;
}

void push(Vertex *u, Connection *v, Network *Nw) {
	/* Part of the Relabel-To-Front algorithm*/

	int increase;

	increase = min(u->excess, (v->capacity - v->flow));

	if ((v->capacity - v->flow) > 0) {
		v->flow += increase;
		Connection *c=Nw->vertices[v->id].head;
		while (c!=NULL) {
			if(c->id == u->id) {
				c->flow -= increase;
				break;
			}
			c=c->next;
		}
	}
	else {
		Connection *c=Nw->vertices[v->id].head;
		while (c!=NULL) {
			if(c->id == u->id) {
				c->flow -= increase;
				break;
			}
			c=c->next;
		}
		v->flow += increase;
	}

	u->excess -= increase;
	Nw->vertices[v->id].excess += increase;
}

void discharge(Vertex *u, Network *Nw) {
	/* Part of the Relabel-To-Front algorithm*/

	while (u->excess > 0)  {
		Connection *v = u->current;
		if (v == NULL) {
			relabel(u, Nw);
			u->current = u->head;
		}
		else if ((v->capacity - v->flow) > 0 && u->height == Nw->vertices[v->id].height + 1)
			push(u,v, Nw);
		

		else
			u->current = v->next;
	}
}

void relabel_to_front(Network *Nw) {

	int i, old_height;

	initialize_preflow(Nw);

	Vertex_List *L = create_vertex_list(Nw);

	for (i=2;i<=Nw->n_suppliers+2*Nw->n_stations+1;i++) 
		Nw->vertices[i].current = Nw->vertices[i].head;

	Vertex *u = L->head;

	while (u != NULL) {
		old_height = u->height;

		discharge(u, Nw);
		if (u->height > old_height) {

			if (u == L->head);

			else if (L->tail == u) {
				L->head->prev = u;
				u->prev->next = NULL;
				L->tail = u->prev;
				u->prev = NULL;
				u->next = L->head;
				L->head = u;
			}
			else {
				L->head->prev = u;
				u->prev->next = u->next;
				u->next->prev = u->prev;
				u->prev = NULL;
				u->next = L->head;
				L->head = u;
			}
		}

		u = u->next;
	}	
}

/* -----------------------------------------------------------   */


void DFS(int v, int visited[], Network *Nw) {
    visited[v] = 1; 

    Connection *c=Nw->vertices[v].head;

	for (;c!=NULL;c=c->next){

        if(!visited[c->id] && (c->flow + c->capacity) != 0) {	
        	DFS(c->id,visited,Nw);
        }
    } 
}

void merge(Cut arr[], int l, int m, int r) { 

    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    Cut L[n1], R[n2]; 
  
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    i = 0;  
    j = 0;  
    k = l; 

    /* Sorts by the source id and if tied, uses the destination id */
    while (i < n1 && j < n2) { 
        if (L[i].source < R[j].source) { 
            arr[k] = L[i]; 
            i++; 
        } 
        else if (L[i].source == R[j].source) {
        	if (L[i].dest < R[j].dest) {
        		arr[k] = L[i]; 
            	i++; 
        	}
        	else {
        		arr[k] = R[j]; 
            	j++;
            }
        }
        else {
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    while (i < n1) { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    while (j < n2) { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  

void mergeSort(Cut arr[], int p, int r) {

    if (p < r) { 
        int q = p+(r-p)/2; 
        mergeSort(arr, p, q); 
        mergeSort(arr, q+1, r); 
        merge(arr, p, q, r); 
    } 
} 



void get_minimum_cut(Network *Nw) {

	int i,n_conn=Nw->n_connections,n_sup=Nw->n_suppliers,n_sta=Nw->n_stations;

	int *visited=(int *)can_fail_malloc((n_sup+2*n_sta+1)*sizeof(int));
    memset(visited,0,(n_sup+2*n_sta+1)*sizeof(int));

    Cut *cut_list=(Cut *)can_fail_malloc((n_conn)*sizeof(struct cut));
    memset(cut_list, -1, (n_conn)*sizeof(struct cut));

    Connection *c=Nw->vertices[1].head;

    visited[1] = 1;

    int j = 0;

    /* DFS to get the reachable vertices */
	for (;c!=NULL;c=c->next) {
		if(!visited[c->id] && (c->flow + c->capacity) != 0) {	
        	DFS(c->id,visited,Nw);
        	visited[c->id] = 1;
        }
	}


	/* Goes through the entire graph to get the edges that satisfy the conditions to be part of the minimum cut */
    for (i=0;i<=n_sup+2*n_sta+1;i++) {
    	Connection *c=Nw->vertices[i].head;
		while(c!=NULL) {
			if (visited[i] && !visited[c->id] && c->flow != 0) {
            	cut_list[j].source = c->id;
            	cut_list[j].dest = i;
            	j++;
			}
			c=c->next;
		}
    }

    /* Sorts the list of edges that are part of the minimum cut */
    mergeSort(cut_list, 0, n_conn-1);
  
   	
 	/* Looks for the first station to be augmented and prints it */
    for (i=0; i<n_conn; i++)
  		if ((cut_list[i].source + n_sta) == cut_list[i].dest && cut_list[i].source > n_sup + 1) {
  			printf("%d", cut_list[i].source);
  			cut_list[i].source = -1;
  			break;
  		}

  	/* Prints the rest of the stations that need to be augmented */
  	for (i=0; i<n_conn; i++)
  		if ((cut_list[i].source + n_sta) == cut_list[i].dest && cut_list[i].source > n_sup + 1) {
  			printf(" %d", cut_list[i].source);
  			cut_list[i].source = -1;
  		}

  	printf("\n");


  	/* Prints the edges that need to be augmented , excluding the ones that are connected to the source (s) */
  	for (i=0; i<n_conn; i++) {
  		if (cut_list[i].source != 0 && cut_list[i].source >= (n_sup + n_sta + 2) && cut_list[i].source != -1) {
  			printf("%d %d\n", cut_list[i].source - n_sta, cut_list[i].dest);
  		}
  		else if(cut_list[i].source != 0 && cut_list[i].source <= (n_sup + n_sta) && cut_list[i].source != -1)
  			printf("%d %d\n", cut_list[i].source, cut_list[i].dest);
  	}
}

int main(){

	int i,n_sup,n_conn,n_sta,input;
	int source,dest,cap;
	char *input_str;

	if (scanf("%d %d %d", &n_sup, &n_sta, &n_conn) < 0)
		exit(-1);

	Network *Nw=(Network *)can_fail_malloc(sizeof(struct network));

	Nw->n_suppliers=n_sup;
	Nw->n_stations=n_sta;
    Nw->n_connections=n_conn;

	Vertex *V=(Vertex *)can_fail_malloc((n_sup+n_sta*2 + 2)*sizeof(struct vertex));

	Nw->vertices=V;

	create_vertex(0,Nw); /* creates source */

	create_vertex(1,Nw); /* Hiper */

	getchar(); /*clears buffer*/


	for (i=2;i<=n_sup+1;i++) { /* stores each supplier's id and capacity */
		input_str=readInput();
		input=atoi(input_str);
		free(input_str);
		create_vertex(i,Nw); /* creates vertex with id "i" and capacity "input" */
		vertex_add_conn(0,i,input,Nw); /* creates edge between the source and the supplier */
		vertex_add_conn(i,0,input,Nw); /* creates corresponding back edge */
	}

	for (i=n_sup+2;i<=n_sup+n_sta+1;i++) { /* stores each station's id and capacity */
		input_str=readInput();
		input=atoi(input_str);
		free(input_str);
		create_vertex(i,Nw); /* creates vertex with id "i" and capacity "input" */
		create_vertex(i+n_sta,Nw); /* creates duplicated vertex */
		vertex_add_conn(i,i+n_sta,input,Nw); /* creates edge between them with capacity = vertex capcity */
		vertex_add_conn(i+n_sta,i,input,Nw); /* creates corresponding back edge */
	}

	for (i=0;i<n_conn;i++) {
		if (scanf("%d %d %d", &source, &dest, &cap) < 0)
			exit(-1);
		if (source >= n_sup+2 && source <= n_sup+n_sta+2) {
			/*  Vertex is a station */
			vertex_add_conn(source+n_sta,dest,cap,Nw);
			vertex_add_conn(dest,source+n_sta,cap,Nw); /* creates corresponding back edge */
		}
		else {
			vertex_add_conn(source,dest,cap,Nw);
			vertex_add_conn(dest,source,cap,Nw); /* creates corresponding back edge */
		}
	}


	relabel_to_front(Nw);


	printf("%d\n", Nw->vertices[1].excess); /* Maximum capacity of the network*/


	get_minimum_cut(Nw);

	
	return 0;
}