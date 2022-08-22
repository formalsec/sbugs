#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

typedef struct Node{
	int dest;
	int weight;
	int flow;
	struct Node *next;
} Node;

typedef struct QueueN{
	int id;
	struct QueueN *next;
	struct QueueN *prev;
	Node *current;
} QueueN;

typedef struct Vertex{
	Node *head;
	Node *tail;
} Vertex;

typedef struct Queue{
	QueueN *head;
	QueueN *tail;
} Queue;	

typedef struct Graph{
	Vertex *adjency_list;
} Graph;

typedef struct Edge{
	int o;
	int d;
}Edge;
/*qsort auxiliary function*/
int sort(const void * elem1, const void * elem2){
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}
/*qsort auxiliary function*/
int compare(const void *elem1, const void *elem2){
	Edge f = *((Edge*)elem1);
	Edge s = *((Edge*)elem2);
	if(f.o > s.o) 
		return 1;
	if(f.o < s.o) 
		return -1;
	else if(f.o == s.o){
		if(f.d > s.d)
			return 1;
		if(f.d < s.d)
			return -1;
	}
	return 0;
}
/*adds a vertex to the graph*/
void insert(Vertex *vertex, int dest, int weight){
	Node *adj;
		
	adj = (Node*) malloc(sizeof(Node));
	adj->dest = dest;
	adj->weight = weight;
	adj->flow = 0;
	adj->next = NULL;

	if(vertex->head == NULL){
		vertex->head = adj;
		vertex->tail = adj;
	}

	else{
		vertex->tail->next = adj;
		vertex->tail = vertex->tail->next;
	}

}

/*Inserts a back edge*/
void insertBE(Vertex *vertex, int dest, int weight){
	Node *adj;
		
	adj = (Node*) malloc(sizeof(Node));
	adj->dest = dest;
	adj->weight = weight;
	adj->flow = weight;
	adj->next = NULL;

	if(vertex->head == NULL){
		vertex->head = adj;
		vertex->tail = adj;
	}

	else{
		vertex->tail->next = adj;
		vertex->tail = vertex->tail->next;
	}

}
/*Inserts an element on a linked list used in the Relabel-To-Front algorithm*/
void insertQ(Queue *queue, int id, Graph *g){
		QueueN *v;

		v = (QueueN*) malloc(sizeof(QueueN));
		v->id = id;
		v->next = NULL;
		v->prev = NULL;
		v->current = g->adjency_list[id].head;
		
		if(queue->head == NULL){
			queue->head = v;
			queue->tail = v;
		}

		else{
			v->prev = queue->tail;
			queue->tail->next = v;
			queue->tail = queue->tail->next;
		}
}

int getStr(){
	int i = 0, v;
	int c;
	char *tmp_str = malloc(sizeof(char) * 1000);

	while((c = getchar()) != ' ' && c != '\n'){
		tmp_str[i++] = c;
	}

	v = atoi(tmp_str);
	free(tmp_str);
	return v;
}

void relabel(QueueN *u, int *max_height, int *height, Graph *g){
	Node *node;
	int min_height;

	min_height = *max_height;
	for(node = g->adjency_list[u->id].head; node != NULL; node = node->next){ /* Searches for the vertex with the minimum height that is a neighbour of u*/
		if(node->flow != node->weight){ /*If the edge is saturated it's height is ignored*/
			if(height[node->dest] < min_height){
				min_height = height[node->dest];
			}
		}
	}
	height[u->id] = 1 + min_height;
	if(height[u->id] > *max_height){
		*max_height = height[u->id];
	}
}

void push(QueueN *u, Node *v, int *excess, Graph *g){
	int f_fluct;
	Node *node;

	f_fluct = MIN(excess[u->id], (v->weight - v->flow));
	for(node = g->adjency_list[v->dest].head; node != NULL; node = node->next){
		if(node->dest == u->id){
			if(node->flow == 0){
				v->flow = v->flow + f_fluct; /*Pushes flow to the edge*/
				node->flow = node->flow - f_fluct; /*The back edge "loses" the flow that is pushed*/
				break;
							}
			else{
				node->flow = node->flow - f_fluct;
				v->flow = v->flow + f_fluct;
				break;
			}
		}
	}
	excess[u->id] = excess[u->id] - f_fluct;
	excess[v->dest] = excess[v->dest] + f_fluct;
}

void discharge(QueueN *u, int *excess, int *height, Graph *g, int *max_height){
	Node *v;

	while(excess[u->id] > 0){
		v = u->current;
		if(v == NULL){ /*If the neighbour list of u reaches it's end u is relabeled*/
			relabel(u, max_height, height, g);
			u->current = g->adjency_list[u->id].head;
		}
		else if(v->weight - v->flow > 0 && height[u->id] == height[v->dest] + 1){ /*If we can push to a neighbour vertex we push the flow to it*/
			push(u, v, excess, g);
		}
		else
			u->current = v->next; /*Goes to the next neighbour of u*/
	}
}



int relabelToFront(Graph *g, int n_prov, int n_stations){
	int *excess;
	int *height;
	int i;
	int old_height;
	int max_height;
	QueueN *u;
	Node *node;
	Queue *q;

	excess = (int*) malloc(sizeof(int) * ((n_prov + 2 * n_stations) + 2));
	height = (int*) malloc(sizeof(int) * ((n_prov + 2 * n_stations) + 2));

	q = (Queue*) malloc(sizeof(Queue));
	q->head = NULL;
	q->tail = NULL;

	/*							INITIALIZE-PREFLOW							*/							
	memset(excess, 0, (sizeof(int) * ((n_prov + 2 * n_stations) + 2)));
	memset(height, 0, (sizeof(int) * ((n_prov + 2 * n_stations) + 2)));
	
	height[0] = n_prov + 2 * n_stations + 2;
	max_height = height[0];
	
	for(node = g->adjency_list[0].head; node != NULL; node = node->next){
		node->flow = node->weight;
		excess[node->dest] = node->weight;
		excess[0] = excess[0] - node->weight;
	}
	/*							INITIALIZE-PREFLOW							*/

	/*							AUXILARY LIST INITIALIZATION				*/			
	for(i = 2; i < ((n_prov + 2 * n_stations) + 2); i ++)
		insertQ(q, i, g);
	/*							AUXILARY LIST INITIALIZATION				*/		


	u = q->head; /* Begins discharging all vertices with excess */
	while(u != NULL){
		old_height = height[u->id];
		discharge(u, excess, height, g, &max_height);
		if(height[u->id] > old_height){
			if(u == q->head)
				u = q->head;
			
			else if(u == q->tail){
				u->prev->next = u->next;
				q->tail = u->prev;
				u->next = q->head;
				u->prev = q->head->prev;
				q->head = u;
			}

			else{
				u->prev->next = u->next;
				u->next->prev = u->prev;
				u->prev = q->head->prev;
				u->next = q->head;
				q->head->prev = u;
				q->head = u;
			}
		}
		u = u->next;

	}
	printf("%d\n", excess[1]);
	return excess[1];

}

/*DFS used to search all the reachable vertices in the residual graph*/
void dfs(Graph *g, int visits, int *visited){
	Node *node;

	visited[visits] = 1;

	for(node = g->adjency_list[visits].head; node != NULL; node = node->next){
		if(node->flow != 0 && !visited[node->dest]){
			dfs(g, node->dest, visited);
		}
	}

}
/*Encouters the minimum cut in the graph that was given in the output*/
void findMinCut(Graph *g, int n_prov, int n_stations, int max_cap){
	int *visited;
	int i, j = 0, k = 0;
	int cut_cap = 0;
	int *stations;
	Node *node;
	Edge *edges;

	visited = (int*) malloc(sizeof(int) * ((n_prov + 2 * n_stations) + 2));
	memset(visited, 0, (sizeof(int) * ((n_prov + 2 * n_stations) + 2)));
	stations = (int*) malloc(sizeof(int));
	edges = (Edge*) malloc(sizeof(Edge));
	dfs(g, 1, visited);

	for(i = 0; i < (n_prov + 2 * n_stations) + 2; i++){
		for(node = g->adjency_list[i].head; node != NULL; node = node->next){
			if(visited[i]  ==  !(visited[node->dest]) && node->flow && cut_cap + node->flow <= max_cap){
				if(node->dest > n_stations + n_prov + 1){
					j = j + 1;
					stations = realloc(stations, j * sizeof(int));
					stations[j - 1] = node->dest;
					cut_cap = cut_cap + node->flow;
				}
				else if(i > n_stations + n_prov + 1){
					k = k + 1;
					edges = realloc(edges, k * sizeof(Edge));
					edges[k - 1].o = i - n_stations;
					edges[k - 1].d = node->dest;
					cut_cap = cut_cap + node->flow;
				}
				else if(i > (n_stations + n_prov + 1) && node->dest > (n_stations + n_prov + 1)){
					k = k + 1;
					edges = realloc(edges, k * sizeof(Edge));
					edges[k - 1].o = i - n_stations;
					edges[k - 1].d = node->dest - n_stations;
					cut_cap = cut_cap + node->flow;
				}
				else if(i == 0){
					cut_cap = cut_cap + node->flow;
				}
				else{
					k = k + 1;
					edges = realloc(edges, k * sizeof(Edge));
					edges[k - 1].o = i;
					edges[k - 1].d = node->dest;
					cut_cap = cut_cap + node->flow;
				}
			}
		}
	}

	if(j != 0){
		qsort(stations, j, sizeof(int), sort);
		for(i = 0; i < j; i++){
			if(i != j - 1){
				printf("%d ", stations[i] - n_stations);
			}
			else{
				printf("%d", stations[i] - n_stations);
			}
		}
		printf("\n");
	}
	else{
		printf("\n");
	}

	if(k !=0){
		qsort(edges, k, sizeof(Edge), compare);
		for(i = 0; i < k; i++){
			printf("%d %d\n", edges[i].o, edges[i].d);
		}
	}
}


int main(){
	Graph *g = (Graph*) malloc(sizeof(Graph));
	int n_prov, n_stations, n_connections, o, d, t, i, j = 2, c, max_flow;

	if (scanf("%d %d %d", &n_prov, &n_stations, &n_connections) != 3){
		exit(0);
	}
	getchar();
	
	g->adjency_list = (Vertex*) malloc(sizeof(Vertex) * ((n_prov + 2 * n_stations) + 2));
	
	for (i = 0; i < n_prov + 2 * n_stations + 2; i++){
		g->adjency_list[i].head = NULL;
		g->adjency_list[i].tail = NULL;
	}
	
	for(i = 0; i < n_prov; i++){
		insert(&g->adjency_list[0], j, c = getStr());
		insert(&g->adjency_list[j], 0, c);
		j++;
	}

	for(i = 0; i < n_stations; i++){
		insert(&g->adjency_list[j], j + n_stations, c = getStr());
		insertBE(&g->adjency_list[j + n_stations], j, c);
		j++;
	}


	i = 0;	

	while (i < n_connections){
		if (scanf("%d %d %d", &o, &d, &t) != 3)
			exit(0);
		if(o >= n_prov + 2){
			insert(&g->adjency_list[o + n_stations], d, t);
			insertBE(&g->adjency_list[d], o + n_stations, t);
		}

		else{
			insert(&g->adjency_list[o], d, t);
			insertBE(&g->adjency_list[d], o, t);
		}

		i++;
	}

	max_flow = relabelToFront(g, n_prov, n_stations);
	
	findMinCut(g, n_prov, n_stations, max_flow);

	return 0;
	
}