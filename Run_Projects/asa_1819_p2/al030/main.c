#include <stdio.h>
#include <stdlib.h>
#define MIN(a,b) (a < b ? a : b)


/*Structure declarations*/
struct Node{
    int flow_here;
    int back_flow;
    int flow_cap;
    int Id;
    struct Node* next;
} Node;

struct QueueNode{
    int Id;
    struct QueueNode* next;
}QueueNode;


/*Global variables*/
int f, e, t, imaginary_id, max_flow;
struct QueueNode* first_point;
struct QueueNode* last_point;


/*Global arrays*/
int *parent;
int *visited;

/*Global array of nodes that keeps all of the vertices*/
struct Node *network;

/*Function prototypes*/
void collect_input();
void calculate_max_flow();
void print_results();
int flow_here(int u, int v);
int flow_cap(int u, int v);
int subtract_flow(int u, int v, int path_flow);
int add_backflow(int u, int v, int path_flow);
int bfs(int s, int t);
int push_to_queue(int newValue, struct QueueNode* last_point, struct QueueNode* first_point);
int pop_from_queue(struct QueueNode* first_point);
void dfs(int s);



/*
 * Main function. Only calls for other functions.*/
int main() {
    collect_input();
    calculate_max_flow();
    return 0;
}


/*
 * This function collects the input from stdin, saves the necessary network values, and proceeds to
 * construct the delivery network, via the calling of auxiliary functions.
 */
void collect_input(){

    int i, current=2, current_cap, k, o, d, z;
    char temp;
    struct Node* new_link;
    struct Node* network_point;

    /*Scans for the number of suppliers, f; number of stations, e; number of connections, t;*/
    z=scanf("%d %d %d", &f, &e, &t);
    k = f+e;
    imaginary_id = k + k + 2;

    /*Allocates the network array that will keep all of the nodes relative to the adjacency list*/
    network = malloc(sizeof(Node)*(2+f+f+e+e));

    /*Scans and processes the information relative to the supplier vertices of the graph*/
    do{
        z=scanf("%d%c", &current_cap, &temp);

        /*Adds the first vertex of the split vertex*/
        network[current-1].Id=current;
        network[current-1].flow_here = 0;
        network[current-1].back_flow = 0;
        network[current-1].next = NULL;

        /* Adds the second vertex of the split vertex, saving the original vertices capacity on this node. This second
         * vertex possesses an offset equal to the sum of the number of refueling stations and suppliers.*/
        network[current+k-1].Id=current+k;
        network[current+k-1].flow_here = 0;
        network[current+k-1].back_flow = 0;
        network[current+k-1].next = NULL;

        /*Adds a reference to the direction and flow capacity on the linked list*/
        new_link = malloc(sizeof(Node));
        new_link->Id = current+k;
        new_link->next = NULL;
        new_link->flow_here = current_cap;
        new_link->flow_cap = current_cap;
        new_link->back_flow = 0;
        network[current-1].next = new_link;

        current++;

    }while(temp != '\n');

    /*Sets the current counter to start processing supply stations. The same logic as the supplier vertices will be used*/
    current=f+2;
    do{
        z=scanf("%d%c", &current_cap, &temp);

        /*Adds the first vertex of the split vertex*/
        network[current-1].Id=current;
        network[current-1].flow_here = 0;
        network[current-1].back_flow = 0;
        network[current-1].next = NULL;

        /* Adds the second vertex of the split vertex, saving the original vertices capacity on this node. This second
         * vertex possesses an offset equal to the sum of the number of refueling stations and suppliers.*/
        network[current+k-1].Id=current+k;
        network[current+k-1].flow_here = current_cap;
        network[current+k-1].back_flow = 0;
        network[current+k-1].next = NULL;

        /*Adds a reference to the direction and flow capacity on the linked list*/
        new_link = malloc(sizeof(Node));
        new_link->Id = current+k;
        new_link->next = NULL;
        new_link->flow_here = current_cap;
        new_link->back_flow = 0;
        new_link->flow_cap = current_cap;
        network[current-1].next = new_link;

        current++;

    }while(temp != '\n');

    /*Will now scan the connections between nodes and register them to the adjacency list via pointers*/
    for(i=0; i<t; i++){
        z=scanf("%d %d %d", &o, &d, &current_cap);

        /*Saves the connection to the list*/
        /*Adjusts the origin of the connection to be the endpoint of the separated vertex*/
        o = (network[o-1].next)->Id;
        network_point = &(network[o-1]);
        new_link = malloc(sizeof(Node));
        new_link->Id = d;
        new_link->back_flow = 0;
        new_link->flow_here = current_cap;
        new_link->flow_cap = current_cap;
        new_link->next = network_point->next;
        network_point->next = new_link;
    }
    z=z+1;

    /*Sets the imaginary point that flows into all of the suppliers*/
    network[imaginary_id-1].Id = imaginary_id;
    network[imaginary_id-1].flow_here=0;
    network[imaginary_id-1].back_flow=0;
    network[imaginary_id-1].next = NULL;

    /*Makes the connections between that point and said suppliers*/
    network_point = &(network[imaginary_id-1]);
    for(i=2; i<=f+1; i++){
        new_link = malloc(sizeof(Node));
        new_link->Id = i;
        new_link->flow_here = 2147483647;
        new_link->flow_cap = 2147483647;
        new_link->back_flow = 0;
        new_link->next = network_point->next;
        network_point->next = new_link;
    }
}

/*
 * Calculates the maximum flow (max_flow) and allows for the discovery of the minimum cut.
 */
void calculate_max_flow(){

    int u, v, i;
    int path_flow = 2147483647;
    /*int parent[imaginary_id];
    int visited[imaginary_id];*/

    visited = malloc(sizeof(int)*imaginary_id);
    parent = malloc(sizeof(int)*imaginary_id);

    for(i=0; i<imaginary_id; i++)
        parent[i]=1;
    for(i=0; i<imaginary_id; i++)
        visited[i]=0;

    while (bfs(imaginary_id, 1)==1){

        path_flow = 2147483647;

        for (v=1; v!=imaginary_id; v=parent[v-1])
        {
            u = parent[v-1];
            path_flow = MIN(path_flow, flow_here(u, v));
        }


        for (v=1; v != imaginary_id; v=parent[v-1])
        {
            u = parent[v-1];
            subtract_flow(u, v, path_flow);
            add_backflow(u, v, path_flow);
        }
        max_flow += path_flow;
    }

    for(i=0; i<imaginary_id; i++)
        visited[i]=0;
    dfs(imaginary_id);

    /*Print all edges that are from a reachable vertex to
     non-reachable vertex in the original graph
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            if (visited[i] && !visited[j] && graph[i][j])
                cout << i << " - " << j << endl;*/

    print_results();
}

/*
 * Returns the current flow capacity of the edge described by u and v (u->v).
 */
int flow_here(int u, int v){
    struct Node* current;
    current = &(network[u-1]);
    current = current->next;
    while(current!=NULL){
        if(current->Id == v)
            return current->flow_here;
        current = current->next;
    }
    return 0;
}

int flow_cap(int u, int v){
    struct Node* current;
    current = &(network[u-1]);
    current = current->next;
    while(current!=NULL){
        if(current->Id == v)
            return current->flow_cap;
        current = current->next;
    }
    return 0;
}

/*
 * Subtracts the flow from the capacity of the edge described by the u and v vertices (u->v).
 */
int subtract_flow(int u, int v, int path_flow){
    struct Node* current;
    current = &(network[u-1]);
    current = current->next;
    while(current!=NULL){
        if(current->Id == v){
            current->flow_here = current->flow_here - path_flow;
            return 0;
        }
        current = current->next;
    }
    return 0;
}

/*
 * Adds backflow to the edge of the graph described by the vertices (u->v);
 */
int add_backflow(int u, int v, int path_flow){
    struct Node* current;
    current = &(network[u-1]);
    current = current->next;
    while(current!=NULL){
        if(current->Id == v){
            current->back_flow = current->back_flow + path_flow;
            return 0;
        }
        current = current->next;
    }
    return 0;
}

/* Returns true if there is a path from source 's' to sink 't' in
  residual graph. Also fills parent[] to store the path */
int bfs(int s, int t){

    int visited[imaginary_id];
    int u;
    struct Node* current;
    struct QueueNode *newNode;


    /*Initializes the queue by creating an entry, this being simultaneously first and last point*/
    newNode = malloc(sizeof(QueueNode));
    newNode->next = NULL;
    newNode->Id = s;
    first_point = newNode;
    last_point = newNode;

    visited[s-1] = 1;
    parent[s-1] = -1;

    while(first_point->Id != -1){
        u = first_point->Id;
        pop_from_queue(first_point);
        current = &(network[u - 1]);
        current = current->next;
        while(current!=NULL){
            if(visited[current->Id-1]==0){
                push_to_queue(current->Id, last_point, first_point);
                parent[current->Id -1] = u;
                visited[current->Id -1] = 1;
            }
            current = current->next;
        }
    }



    if(visited[t-1] == 1)
        return 1;
    else
        return 0;
}

int push_to_queue(int newValue, struct QueueNode* last_point, struct QueueNode* first_point){

    struct QueueNode *newNode;

    if(first_point->Id == -1){
        first_point->Id = newValue;
        return 0;
    }

    /*Allocates the new node*/
    newNode = malloc(sizeof(QueueNode));

    last_point->next = newNode;
    newNode->next = NULL;
    newNode->Id = newValue;

    last_point = newNode;

    return 0;
}

int pop_from_queue(struct QueueNode* first_point){

    struct QueueNode* temp;

    if(first_point->next == NULL){
        first_point->Id = -1;
        return 0;
    }
    else {
        temp = first_point;
        first_point = temp->next;
        free(temp);
        return 0;
    }
}

void dfs(int s){
    struct Node* current;

    visited[s-1] = 1;
    if(s!=1){
        current = &(network[s-1]);
        current = current->next;
        while(current!=NULL){
            if(visited[current->Id -1] == 0 && flow_here(s, current->Id)!=0)
                dfs(current->Id);
            current = current->next;
        }
    }
}

void print_results(){

    int i, j, space=0;

    /*Prints the maximum capacity of the network*/
    printf("%d\n", max_flow);

    /*Iterates through the supply stations and sees if any of them meet the minimum cut*/
    for(i=f+2; i<f+e+2; i++){
        for(j=f+e+2; j<imaginary_id; j++){
            if(visited[i-1]!=0 && visited[j-1]==0 && flow_cap(i, j)!=0){
                if(space){
                    printf(" ");
                }
                printf("%d", i);
                space=1;
            }
        }
    }
    printf("\n");

    /*Iterates through the other connections and sees if any need augmenting*/
    space =0;
    for(i=f+e+2; i<imaginary_id; i++){
        for(j=f+2; j<imaginary_id; j++){
            if(visited[i-1]!=0 && visited[j-1]==0 && flow_cap(i, j)!=0){
                if(space){
                    printf("\n");
                }
                printf("%d %d", i-f-e, j);
                space=1;
            }
        }
    }
}