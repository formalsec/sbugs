#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define UNDEFINED -1
#define MIN(a,b) (((a)<(b))?(a):(b))

struct node
{
    int vertex;
    struct node* next;
};

struct node* createNode(int v);

struct Graph
{
    int numVertices;
    int* visited;
    int* disc;
    int* low;
    int* parent;
    int* ap;
    struct node** adjLists; /* we need int** to store a two dimensional array. Similary, we need struct node** to store an array of Linked lists*/
};

typedef struct network_result {
    struct node* network;
    struct network_result* next;
} network_result_t;

struct Graph* createGraph(int);
void addEdge(struct Graph*, int, int);
void printGraph(struct Graph*);
void DFS(struct Graph*, int, int);
struct Graph* read_input_file();
struct node* push(struct node*, int);

void printResults(network_result_t*);
network_result_t* pushNetwork(network_result_t *);
void push_n(struct node**, int);
void insertOrdered(struct node**, int);
void free_results();
void DFS_NORMAL(struct Graph*, int, int);
void removeArticulationPoints(struct Graph*, int);
void printResults2(network_result_t*);
void free_graph(struct Graph*);
network_result_t* results;

int n_vertices;
int M = 0;

int main() {
    int i; 
    int j = 0;
    /*int* articulation_p;*/
    struct Graph* graph;
    results = NULL;
    graph = read_input_file();
    /*results = can_fail_malloc(sizeof(network_result_t));
    results->next = NULL;
    results->network = can_fail_malloc(sizeof(struct node));*/
    
    for (i = 0; i < n_vertices; ++i) {
        if (!graph->visited[i])
            DFS(graph, i, 0);
    }

    printf("%d\n", M);
    printResults(results);
    
    for (i = 0; i < n_vertices; i++) { 
        if (graph->ap[i] == 1){ 
            j++;
            removeArticulationPoints(graph, i);
        }
    }

    printf("%d\n", j);
    /*articulation_p = (int*) can_fail_malloc(sizeof(int)*j);*/
    j = 0;
    
    /*for (i = 0; i < n_vertices; i++) 
        if (graph->ap[i] == 1) 
            articulation_p[j++] = i;        
    
    for (i = 0; i < j; ++i) {
        removeArticulationPoints(graph, articulation_p[i]);
    }*/
    
    for (i = 0; i < n_vertices; ++i) {
        graph->visited[i] = 0;
    }
    /*puts("-------");
    printGraph(graph);*/
    free_results();
    /*free(articulation_p);*/

    free(graph->parent);
    free(graph->disc);
    free(graph->low);
    free(graph->ap);
    /*results = NULL;*/
    
    for (i = 0; i < n_vertices; ++i) {
        if (!graph->visited[i])
            DFS_NORMAL(graph, i, 0);
    }
    
    printResults2(results);
    free_results();
    free_graph(graph);
    return 0;
}

void free_graph(struct Graph* graph) {
    int i;
    struct node* tmp;
    for (i = 0; i < n_vertices; ++i) {
        while (graph->adjLists[i] != NULL) {
            tmp = graph->adjLists[i];
            graph->adjLists[i] = tmp->next;
            free(tmp);
        }
    }
    free(graph->adjLists);
    free(graph->visited);

    free(graph);
}

void insertOrdered(struct node** head, int val) {
    struct node* tmp = *head;
    struct node* prev = NULL;
    struct node* new_node = createNode(val);
    if (tmp == NULL) {
        new_node->next = tmp;
        *head = new_node;
        return;
    }

    while(tmp != NULL && tmp->vertex <= val) {
        prev = tmp;
        tmp = tmp->next;
    }


    if (prev == NULL) {
        new_node->next = tmp;
        (*head) = new_node;
    }
    else {    
        new_node->next = tmp;
        prev->next = new_node;
    }

}


int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void printResults(network_result_t* head) {
    network_result_t* tmp = head;
    int *networks;
    int i = 0;
    int c = 0;
    networks = (int*) can_fail_malloc(sizeof(int)*M);


    while (tmp != NULL) {
        struct node* tmp2 = tmp->network;
        int max = -1;

        while (tmp2 != NULL) {
            if (tmp2->vertex > max)
                max = tmp2->vertex;
            tmp2 = tmp2->next;
        }
        networks[c++] = max+1;


        tmp = tmp->next;
    }
    qsort(networks, M, sizeof(int), cmpfunc);
    for (i = 0; i < M-1; ++i) {
        printf("%d ", networks[i]);
    }
    printf("%d\n", networks[i]);
    free(networks);

}

void printResults2(network_result_t* head) {
    network_result_t* tmp = head;
    int max = -1;   
    /*puts("------------");*/
    while (tmp != NULL) {
        int c = 0;
        struct node* tmp2 = tmp->network;
        
        while (tmp2 != NULL) {
            /*printf("%d ", tmp2->vertex+1);*/
            c += 1;
            tmp2 = tmp2->next;
        }
        /*puts("");*/
        if (c > max) {
            max = c;
        }
        tmp = tmp->next;
    }
    printf("%d\n", max);
    
}

void removeArticulationPoints(struct Graph* graph, int vertex) {
    /* Add edge from src to dest */
    /*struct node* newNode = createNode(dest);
    newNode->next = graph->adjLists[vertex];
    graph->adjLists[vertex] = newNode;*/
    
    struct node* tmp = NULL;
    struct node* tmp2 = NULL;
    struct node* prev = NULL;
    
    while (graph->adjLists[vertex] != NULL) {
        tmp = graph->adjLists[vertex];
        tmp2 =  graph->adjLists[tmp->vertex];
        prev = NULL;
        while(tmp2) {
            if (tmp2->vertex == vertex) {
                if (prev == NULL) {
                    graph->adjLists[tmp->vertex] = tmp2->next;
                    tmp2->next = NULL;
                    free(tmp2);
                    break;
                }
                else {
                    prev->next = tmp2->next;
                    tmp2->next = NULL;
                    free(tmp2);
                    tmp2 = NULL;
                    break;
                }
            }
            prev = tmp2;
            tmp2 = tmp2->next;
        }
        graph->adjLists[vertex] = tmp->next;
        free(tmp);
    }


    /* Add edge from dest to src */
    /*newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;*/

}


void DFS(struct Graph* graph, int vertex, int flag) {
        struct node* adjList = graph->adjLists[vertex];
        struct node* temp = adjList;
        
        static int time = 0;
        int children = 0;

        if (!graph->visited[vertex] && !flag) {
            results = pushNetwork(results);
            /*results->size += 1;*/
            push_n(&results->network, vertex);
            
            M += 1;
        }

        graph->visited[vertex] = 1;
        graph->disc[vertex] = graph->low[vertex] = ++time;
        
        while(temp!=NULL) {
            int connectedVertex = temp->vertex;
        
            if (graph->visited[connectedVertex] == 0) {

                children++;
                graph->parent[connectedVertex] = vertex;


                push_n(&results->network, connectedVertex);
                
                DFS(graph, connectedVertex, 1);
                
                graph->low[vertex]  = MIN(graph->low[vertex], graph->low[connectedVertex]);

                if (graph->parent[vertex] == UNDEFINED && children > 1){
                    graph->ap[vertex] = 1;
                }

                if (graph->parent[vertex] != UNDEFINED && graph->low[connectedVertex] >= graph->disc[vertex]){   
                    graph->ap[vertex] = 1;
                }
                

                /*subrede[M] = */

            }
            else if (connectedVertex != graph->parent[vertex])
                graph->low[vertex] = MIN(graph->low[vertex],graph->disc[connectedVertex]);
            temp = temp->next;
        }       
}

void DFS_NORMAL(struct Graph* graph, int vertex, int flag) {    
        struct node* adjList = graph->adjLists[vertex];
        struct node* temp = adjList;

        if (!graph->visited[vertex] && !flag) {
            results = pushNetwork(results);
            results->network = NULL;
            push_n(&results->network, vertex);
        }

        graph->visited[vertex] = 1;
        
        while(temp!=NULL) {
            int connectedVertex = temp->vertex;
        
            if (graph->visited[connectedVertex] == 0) {
                push_n(&results->network, connectedVertex);
                /*results->size += 1;*/
                DFS_NORMAL(graph, connectedVertex, 1);

            }
            temp = temp->next;
        }       
}

void free_results() {
    network_result_t* tmp = NULL;
    struct node* tmp2= NULL;
    while (results != NULL) {
        tmp = results;
        while(tmp->network != NULL) {
            tmp2 = tmp->network;
            tmp->network = tmp2->next;
            free(tmp2);
            tmp2 = NULL;
        }
        results = tmp->next;
        free(tmp);
        tmp = NULL;
    }
    results = NULL;
}

void push_n(struct node ** head, int val) {
    /*if (head == NULL) {
        head = createNode(val);
        return head;
    }
    else {
        struct node* new_node = createNode(val);
        new_node->next = head;
        head = new_node;
        return head;
    }*/
    struct node *new_node = (struct node*) can_fail_malloc (sizeof (struct node));
    new_node->vertex = val;
    new_node->next = *head;
    *head = new_node;
}

network_result_t * pushNetwork(network_result_t * head) {
    if (head == NULL) {
        network_result_t* new_node = can_fail_malloc(sizeof(network_result_t));
        head = new_node;
        head->network = NULL;
        head->next = NULL;
        return head;    
    }
    else {
        network_result_t* new_node = can_fail_malloc(sizeof(network_result_t));
        new_node->next = head;
        head = new_node;
        return head;
    }
}

 
struct node* createNode(int v) {
    struct node* newNode = can_fail_malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices) {
    int i;
    struct Graph* graph = can_fail_malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    
    graph->adjLists = can_fail_calloc(vertices, sizeof(struct node*));
     
    graph->visited = can_fail_calloc(vertices, sizeof(int));
 
    graph->parent = can_fail_malloc(vertices * sizeof(int));    
    
    graph->disc =  can_fail_calloc(vertices, sizeof(int));
    
    graph->low =  can_fail_calloc(vertices, sizeof(int));

    graph->ap =  can_fail_calloc(vertices, sizeof(int));

    for (i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
        graph->parent[i] = UNDEFINED;
    }
    return graph;
}
 
void addEdge(struct Graph* graph, int src, int dest) {
    /* Add edge from src to dest */
    struct node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
 
    /* Add edge from dest to src */
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}
 
void printGraph(struct Graph* graph) {
    int v;
    for (v = 0; v < graph->numVertices; v++) {
        struct node* temp = graph->adjLists[v];
        printf("\n Adjacency list of vertex %d\n ", v);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

struct Graph* read_input_file() {
	struct Graph* g;
    int a, b, i, n, e;
    if(!scanf("%d %d", &n, &e))
        exit(0);
    n_vertices = n;
    g = createGraph(n);
    for (i = 0; i < e; i++) {
        if(!scanf("%d %d", &a, &b))
            exit(0);
        if ((a-1) < 0 || (a-1) >= n || (b-1) < 0 || (b-1) >= n) {
            printf("Invalid input %d %d at %d \n", a, b, __LINE__);
            exit(0);
        }
        else{
        	addEdge(g, a-1,b-1);
        }
    }
    return g;
}