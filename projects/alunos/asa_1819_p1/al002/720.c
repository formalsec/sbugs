#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>



/* Sistema de cores - Algoritmo DFS */
#define WHITE 0
#define GREY  1

#define NIL -1


int *topology_order,total_vertices,scc = 0,biggest_scc =0,*scc_ids,counter_c=0,counter_max=1,max_counter=0,*topology;

typedef struct graph *Graph;
typedef struct node *link;

struct node {
    int v;
    link next;
};

struct graph {
    int n_vertices, n_edges;
    link *array;
};


typedef  struct {
    int colour,disc,low,parent;
}node_components;


typedef struct{
    int colour,v;
    int car_articulation_point;
}vertex;


vertex *ap;
node_components *node_aux_components;


Graph createGraph();
link insertBegin(int v, link head);
void addEdge(Graph graph,int router1,int router2);
int min(int a, int b);
void DFS(Graph graph);
void DFSvisit(Graph graph, int index,int transpose);
void resetVisited(Graph graph);
void printSccIds();
void sortSccIds();
void findScc(Graph graph);
void articulationsPoints(Graph graph);
void maxScc(Graph graph);
void DFST(Graph graph,int index,int transpose);



int main(){
    int r1,r2,inter;

    Graph graph = createGraph();


    for(inter = 0; inter < graph->n_edges; inter ++){
        if(fscanf(stdin, "%d %d", &r1, &r2)){}
        addEdge(graph, r1, r2);
    }

    DFS(graph);

    resetVisited(graph);
    findScc(graph);

    articulationsPoints(graph);

    maxScc(graph);
    return 0;
}


Graph createGraph(){
    int index;
    Graph graph = can_fail_malloc(sizeof(struct graph));

    if(scanf("%d",&graph->n_vertices)){}
    if(scanf("%d",&graph->n_edges)){}

    total_vertices = graph ->n_vertices;

    graph->array = can_fail_malloc((graph->n_vertices+1) * sizeof(link));

    for(index =0; index < graph->n_vertices;index ++){
        graph->array[index] = NULL;
    }

    scc_ids = can_fail_malloc(sizeof(int));
    scc_ids[0] = 0;
    return graph;
}


link insertBegin(int v, link old_head) {
    link new_head = can_fail_malloc(sizeof(struct node)+1);
    new_head ->next = old_head;
    new_head ->v = v;
    return new_head;
}


void addEdge(Graph graph,int router1,int router2){
    graph->array[router1] = insertBegin(router2,graph->array[router1]);
    graph->array[router2] = insertBegin(router1,graph->array[router2]);
}


int min(int a, int b){
    return(a <b ? a:b);
}


void DFS(Graph graph){
    int index;
    node_aux_components =can_fail_malloc((graph->n_vertices) * sizeof(node_components));
    topology_order = (int*)can_fail_malloc((graph->n_vertices+1) * sizeof(int));

    for (index = 1; index <= graph->n_vertices; index++) {
        node_aux_components[index].colour = WHITE;
    }

    for (index = 1; index <= graph->n_vertices; index++) {
        if (node_aux_components[index].colour == WHITE) {
            DFSvisit(graph, index,1);
        }
    }
}


void DFSvisit(Graph graph, int value, int transpose) {
    static int time = 0;
    int children =0,flag =0;
    node_aux_components[value].colour = GREY;

    if(transpose == -2){
        time++;
        node_aux_components[value].disc = node_aux_components[value].low = time;
    }
    link node = graph->array[value];
    while (node != NULL) {

        if (transpose !=-2 && node_aux_components[node->v].colour == WHITE) {
            if(transpose == -1 && node->v > biggest_scc ){
                biggest_scc = node->v;
            }
            DFSvisit(graph, node->v,transpose);
        }
        if(transpose == -2 && node_aux_components[node->v].colour == WHITE){
            children++;
            node_aux_components[node->v].parent = value;
            DFSvisit(graph,node->v,transpose);
            node_aux_components[value].low  = min(node_aux_components[value].low, node_aux_components[node->v].low);

            if (node_aux_components[value].parent == NIL && children > 1) {
                ap[value].car_articulation_point = 1;
                flag = 1;
            }
            if (node_aux_components[value].parent != NIL && node_aux_components[value].disc<=node_aux_components[node->v].low) {
                ap[value].car_articulation_point = 1;
                flag = 1;
            }
        }

        else if(transpose == -2 && node->v != node_aux_components[value].parent ){
            node_aux_components[value].low  = min(node_aux_components[value].low, node_aux_components[node->v].disc);
        }

        node = node->next;
    }
    if(flag == 1){
        counter_c++;
        flag = 0;
    }
    if(transpose == 1) {
        topology_order[total_vertices] = value;
        total_vertices--;
    }
}


void resetVisited(Graph graph) {
    int index;
    for (index = 1; index <= graph->n_vertices; index++){
        node_aux_components[index].colour = WHITE;
    }
    total_vertices = graph->n_vertices;
}


void printSccIds(){
    int index;
    for(index =0; index < scc-1;index++){
        printf("%d ",scc_ids[index]);
    }
    printf("%d\n",scc_ids[scc-1]);
}


void sortSccIds(){
    int aux,index;
    for(index = scc-1; index>=0 && scc_ids[index]<scc_ids[index-1]; index--){
        aux=scc_ids[index];
        scc_ids[index]=scc_ids[index-1];
        scc_ids[index-1]=aux;
    }
}


void findScc(Graph graph){
    int flag = 0,index;
    for(index = 1; index<=graph->n_vertices;index++) {
        int vertice_colour = node_aux_components[topology_order[index]].colour;
        if (vertice_colour == WHITE) {
            scc++;
            flag =1;
            biggest_scc = 0;
            DFSvisit(graph,topology_order[index],-1);
        }
        if(flag == 1) {
            scc_ids[scc - 1] = biggest_scc;
            sortSccIds();
            scc_ids = (int *) can_fail_realloc(scc_ids, sizeof(int) * (scc + 1));
            flag = 0;
        }
    }
    printf("%d\n",scc);
    printSccIds();
}


void articulationsPoints(Graph graph) {
    int index;
    ap = can_fail_malloc((graph->n_vertices) * sizeof(vertex));
    topology = can_fail_malloc((graph->n_vertices) * sizeof(vertex));

    for (index = 1; index <= graph->n_vertices; index++) {
        node_aux_components[index].parent = -1;
        node_aux_components[index].colour = WHITE;
        ap[index].colour = WHITE;
        ap[index].car_articulation_point = 0;
        ap[index].v = index;
    }

    for (index = 1; index <= graph->n_vertices; index++) {
        if (node_aux_components[index].colour == WHITE) {
            DFSvisit(graph, index,-2);
        }
    }
    printf("%d\n",counter_c);
}


void DFST(Graph graph,int index,int transpose){
    ap[index].colour = GREY;
    link node = graph->array[index];

    while(node != NULL) {
        if (ap[node->v].car_articulation_point == 0 && ap[node->v].colour == WHITE) {
            if(transpose == -1 ){
                counter_max++;
            }
            DFST(graph, node->v,transpose);
        }
        node= node-> next;
    }
    if(transpose == 1){
        topology[total_vertices] = index;
        total_vertices--;
    }
}

void maxScc(Graph graph) {
    int index;
    total_vertices = graph->n_vertices;
    for (index = 1; index <= graph->n_vertices; index++) {
        if (ap[index].car_articulation_point == 0 && ap[index].colour == WHITE) {
            DFST(graph, index, 1);
        }
    }

    for (index = 1; index <= graph->n_vertices; index++) {
        ap[index].colour = WHITE;
    }
    total_vertices = graph->n_vertices;

    for (index = counter_c + 1; index <= graph->n_vertices; index++) {
        int vertice_colour = ap[topology[index]].colour;
        if (vertice_colour == WHITE) {
            DFST(graph, topology[index], -1);
        }
        if (counter_max > max_counter) {
            max_counter = counter_max;
        }
        counter_max = 1;
    }
    printf("%d\n", max_counter);
}









