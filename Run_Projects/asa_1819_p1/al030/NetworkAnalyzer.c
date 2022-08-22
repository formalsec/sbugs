#include <stdio.h>
#include <stdlib.h>
#define MIN(a,b) (a < b ? a : b)


/*  CHANGELOG
 *  -Read function written(reads input, allocates list array, sets the initial values for ID and calls the savefunc)
 *  -Save to network function written. Network structure: <network> variable, array of nodes, when empty the node in
 *      each entry of the array has it's Id=0. The save function updates that point's Id on the first acces to it, and
 *      adds a new node to it's connection list every time after.
 *   -Fixed pointer inconsistency completely I think, resolved list storage error.
 *   -Merged my pointer fixes (allows use of global array now) with your DFS.
 *   -Added functioning DFS with sub-network counting
 *   -Added highest number in subnetwork finder
 *
 *
 *
 *
 *
 * */



struct Node{
    int Id;
    struct Node* next;
} Node;

/*Declaration of global variables to be used*/
int router_number;
int connections_number;
int subnetworks;
int artic_number;
int root_node;
int child_nodes;
int current_subn_id;
int subnetwork_size;
int dfs_time;

/*Global arrays to be used*/
int *node_depth;
int *node_low;
int *node_parent;
int *network_articulations;
int *subnetwork_identifiers;

/*Global array of nodes to permit the Adjacency List*/
struct Node *network;

/*Function prototypes*/
void read_input();
void save_to_network(int node1, int node2);
void main_art();
void Articulation_recursive(int u);
int subnetwork_dfs();
void sub_finder(int u);
void print_results();

/*Functions*/
int main(int argc, char const *argv[]){
    /*
     * Main function. Only calls all other functions.
     */
    read_input();
    main_art();
    print_results();
    return 0;
}

void read_input(){
    /*
     * Input reception function. Receives the input from stdin and calls the necessary
     * functions to save the data.
     */
    int i, j, node1, node2, k;

    /*Reads the number of routers & connections in the network*/
    k=scanf("%d", &router_number);
    k=scanf("%d", &connections_number);
    k = k+1;
    

    /* Initializes the list vector that will keep records of the connections
     * and sets the first point of each to its Id
     * struct Node lists[router_number];
     */
    network = malloc(sizeof(Node)*router_number);
    for(j=0; j<router_number; j++){
        network[j].Id = j+1;
        network[j].next = NULL;
    }

    /*Reads all of the connection details and stores them accordingly*/
    for(i=1; i<= connections_number; i++) {
        k=scanf("%d %d", &node1, &node2);
        save_to_network(node1, node2);
    }
}

void save_to_network(int node1, int node2){
    /*
     * Receives a pair of points and registers their connection in the appropriate data sites
     * For these, it is used an adjacency list consisting of an array of Node structures,
     * which form between themselves a single-linked list.
     */
    struct Node* newnode1;
    struct Node* newnode2;
    struct Node* network_point;

    network_point = &(network[node1-1]);
    /*Checks if this is the first connection using this router, if not, inserts at list
     * beginning*/
    newnode2 = malloc(sizeof(Node));
    newnode2->Id = node2;
    newnode2->next = network_point->next;
    network_point->next = newnode2;

    /*Saves the correspondent pair to the other point of the pair*/
    network_point = &(network[node2-1]);
    newnode1 = malloc(sizeof(Node));
    newnode1->Id = node1;
    newnode1->next = network_point->next;
    network_point->next = newnode1;
}

void main_art(){
    /*
     * Main DFS-related function. Allocates the vectors necessary to store all the data used
     * by the proper DFS function.
     */
    int i;

    /*Allocates the vectors necessary*/
    node_depth = malloc(sizeof(int)*router_number);
    node_low = malloc(sizeof(int)*router_number);
    node_parent = malloc(sizeof(int)*router_number);
    network_articulations = malloc(sizeof(int)*router_number);
    subnetwork_identifiers = malloc(sizeof(int)*router_number);
    /*Sets the variables to their default values*/
    for(i=0; i<router_number; i++){
        node_depth[i] = -1;
        node_low[i] = 0;
        node_parent[i] = 0;
        network_articulations[i] = 1;
        subnetwork_identifiers[i] = 0;
    }
    dfs_time = 0;
    artic_number = 0;

    /*DFS-calling loop. Iterates through the nodes and calls DFS on an unvisited root-node.*/
    for(i=0; i<router_number;i++){
        if(node_depth[i]==-1){
            subnetworks++;
            current_subn_id=i+1;
            root_node = i;
            child_nodes = 0;
            Articulation_recursive(i);
            subnetwork_identifiers[current_subn_id - 1] = 1;

            /*If the root is an articulation point*/
            network_articulations[root_node] = child_nodes;
        }
    }
}

void Articulation_recursive(int this_node){
    /*
     * The recursive DFS function. Incorporates the Tarjan algorithm for finding articulation
     * points. These are set through two conditions: The number of children of a vertix and
     * the relationship between the low and depth values of a point. Note that the depth array
     * also stores the visitation status of a given node.
     */
    struct Node current;
    int adj_node;

    /*Sets the depth and low values according to the elapsed time of the DFS*/
    node_depth[this_node] = node_low[this_node] = dfs_time++;

    /*Checks if the identifier of the currently traversing subnetwork needs updating*/
    if(current_subn_id<this_node+1)
        current_subn_id = this_node+1;

    /*Traverses the nodes adjacent to the current one*/
    for(current = network[this_node]; current.next != NULL; current = *(current.next )){
        adj_node = (current.next)->Id-1;
        if(node_depth[adj_node] == -1){
            /*If the node has not been visited, saves the node's parent node*/
            node_parent[adj_node] = this_node;
            /* Checks if the parent node is the root of the subnetwork, updates the
             * root-children value accordingly (used for articulation points)
             */
            if(this_node == root_node)
                child_nodes++;

            /*Calls the recursive DFS on this node*/
            Articulation_recursive(adj_node);

            /* Checks if this is an articulation point, saves it and sets the low
             * value of the point
             */
            if(node_low[adj_node] >= node_depth[this_node]) {
                network_articulations[this_node]++;
            }
            node_low[this_node] = MIN(node_low[this_node], node_low[adj_node]);
        }
        else if(adj_node != node_parent[this_node])
            node_low[this_node] = MIN(node_low[this_node], node_depth[adj_node]);
        /*This node has already been visited, updates the low value*/
    }
}

int subnetwork_dfs(){
    /*
     * Main function of the DFS-based function that finds the largest subnetwork size after
     * removal of the articulation points. Sets the necessary values, resets the visitation
     * arrays, and calls the recursive function.
     */
    int i;
    int largest_subnetwork=0;

    for(i=0; i<router_number; i++){
        node_depth[i]=-1;
    }

    for(i=0; i<router_number; i++){
        subnetwork_size=0;
        /* If the node hasn't been visited, analyzes the subnetwork and updates the maximum
         * size if it's needed
         */
        if(node_depth[i]==-1 && network_articulations[i]<=1){
            sub_finder(i);
            if(subnetwork_size > largest_subnetwork){
                largest_subnetwork = subnetwork_size;
            }
        }
    }
    return largest_subnetwork;
}

void sub_finder(int this_node){
    /*
     * Recursive function of the subnetwork-size finding function.
     */
    struct Node current;
    int adj_node;

    node_depth[this_node]=0;
    subnetwork_size++;

    /*Checks if the nodes adjacent are still present and unvisted and calls itself if so*/
    for(current = network[this_node]; current.next != NULL; current = *(current.next )){
        adj_node = (current.next)->Id-1;
        if(node_depth[adj_node]==-1 && network_articulations[adj_node]<=1){
            sub_finder(adj_node);
        }
    }
}

void print_results(){
    /*
     * Prints the results of the program.
     */
    int i;

    /*Line 1: Number of subnetworks*/
    printf("%d\n", subnetworks);

    /*Line 2: Subnetwork Identifiers*/
    for(i=0; i<router_number; i++){
        if(subnetwork_identifiers[i]==1){
            printf("%d", i+1);
            i++;
            break;
        }
    }
    while(i<router_number){
        if(subnetwork_identifiers[i]==1){
            printf(" %d", i+1);
        }
        i++;
    }
    printf("\n");

    /*Line 3: Number of articulation points*/
    for (i=0; i<router_number; i++){
        if(network_articulations[i]>1)
            artic_number++;
    }
    printf("%d\n", artic_number);

    /*Line 4: Size of largest post-removal network*/
    printf("%d\n", subnetwork_dfs());
}