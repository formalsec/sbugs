#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SINK_AND_SOURCE 2
#define TRUE 1
#define FALSE 0

/*Edges*/
typedef struct edge{
    int to;
    int from;
    int capacity;
    struct edge* backwardEdge;
    struct edge* next_in_ad_list;
}*edgePtr;

/*Edge Functions*/
void add_new_Edge(int from, int to);
void add_Edge_to_Graph(edgePtr edge,int vertex_number);
void add_all_Edges_to_Graph();
void add_down(int i,int j);
void add_right(int i,int j);
void augment_Edge(edgePtr edge);
void init_in_and_out_vertex(int i,int j);

/*Graph functions*/
void Graph_init();
void process_input();
void printGraph();
void add_supermerket_to_graph(int i,int j);
void add_home_to_graph(int i,int j);

/*Ford Fulkerson*/
int ford_fulkerson();
int visit_edges(int vertexnumber, int token);

/*Visited list functions*/
void init_visited();

/*Frees*/
void free_all();
void free_visited();
void free_Graph();
void free_ad_list(edgePtr head);

/*Graph*/
edgePtr* ad_list;
int Avenues;
int Roads;
int numberOfVertices;

/*Visited list*/
int* visited;

/*Visited list functions*/
void init_visited(){
    visited=(int*)calloc(numberOfVertices,sizeof(int));
}

void free_visited(){
    free(visited);
}

/*Graph functions____________________________________________________*/
void Graph_init(){
    int i;
    numberOfVertices= 2*Avenues*Roads+SINK_AND_SOURCE; /*Por cada vertice que nao é a source nem o sink há um vertice in e outro out*/
    ad_list=(edgePtr*)malloc(sizeof(edgePtr)*numberOfVertices);
    for(i=0;i<numberOfVertices;i++){
        ad_list[i]=NULL;
    }
    add_all_Edges_to_Graph();
}

void printGraph()
{
    int v;
    for (v = 0; v <numberOfVertices; v++)
    {
        edgePtr temp = ad_list[v];
        printf("\n Adjacency list of vertex %d\n ", v);
        while (temp)
        {
            printf("           - %d -> %d              ", temp->capacity,temp->to);
            temp = temp->next_in_ad_list;
        }
        printf("\n");
    }
}

void add_supermerket_to_graph(int i,int j){
    int out_vertex_number=(i-1)*Avenues+j+(Avenues*Roads);
    add_new_Edge(out_vertex_number,numberOfVertices-1); /*numberOfVertices-1 is the vertexnumber of the sink*/
}

void add_home_to_graph(int i,int j){
    int in_vertex_number=(i-1)*Avenues+j;
    add_new_Edge(0,in_vertex_number); /*0 is the source*/
}

void free_Graph(){
    int i;
    for(i=0;i<numberOfVertices;i++){
        free_ad_list(ad_list[i]);
    }
    free(ad_list);
}

void free_ad_list(edgePtr head){
    edgePtr cur,next;
    cur=head;
    while(cur!=NULL){
        next=cur->next_in_ad_list;
        free(cur);
        cur=next;
    }
}

/*Edge Functions____________________________________________________________*/

void add_new_Edge(int from, int to){
    edgePtr new_front=(edgePtr)malloc(sizeof(struct edge));
    edgePtr new_backward=(edgePtr)malloc(sizeof(struct edge));
    new_front->to=to;
    new_front->from=from;
    new_front->next_in_ad_list=NULL;
    new_backward->to=from;
    new_backward->from=to;
    new_backward->next_in_ad_list=NULL;
    new_front->capacity=1;
    new_backward->capacity=0;
    new_front->backwardEdge=new_backward;
    new_backward->backwardEdge=new_front;
    add_Edge_to_Graph(new_front,from);
    add_Edge_to_Graph(new_backward,to);
}

void add_Edge_to_Graph(edgePtr edge,int vertex_number){
    edgePtr currEdge,prevEdge;
    if(ad_list[vertex_number]==NULL){
        ad_list[vertex_number]=edge;
    }
    else{
        currEdge=ad_list[vertex_number];
        while(currEdge!=NULL){
            prevEdge=currEdge;
            currEdge=currEdge->next_in_ad_list;
        }
        prevEdge->next_in_ad_list=edge;
    }
}

void add_down(int i,int j){
    int in_vertex_from=(i-1)*Avenues+j;
    int out_vertex_from=in_vertex_from+(Avenues*Roads);
    int in_vertex_to=in_vertex_from+Avenues;
    int out_vertex_to=in_vertex_to+(Avenues*Roads);
    add_new_Edge(out_vertex_from,in_vertex_to);
    add_new_Edge(out_vertex_to,in_vertex_from);
}
void add_right(int i,int j){
    int in_vertex_from=(i-1)*Avenues+j;
    int out_vertex_from=in_vertex_from+(Avenues*Roads);
    int in_vertex_to=in_vertex_from+1;
    int out_vertex_to=in_vertex_to+(Avenues*Roads);
    add_new_Edge(out_vertex_from,in_vertex_to);
    add_new_Edge(out_vertex_to,in_vertex_from);
}

void init_in_and_out_vertex(int i,int j){
    int in=(i-1)*Avenues+j;
    int out=(i-1)*Avenues+j+(Avenues*Roads);
    add_new_Edge(in,out);
}

void add_all_Edges_to_Graph(){
    int i,j;
    for(i=1;i<=Roads;i++){
        for(j=1;j<=Avenues;j++){
            init_in_and_out_vertex(i,j);
            if(j<Avenues && i<Roads){
                 add_down(i,j);
                 add_right(i,j);
            }
            else if (j==Avenues && i==Roads){
                return;
            }
            else if (j==Avenues){
                add_down(i,j);
            }
            else if(i==Roads){
                add_right(i,j);
            }
        }
    }
}

void augment_Edge(edgePtr edge){
    edge->capacity=0;
    edge->backwardEdge->capacity=1;
}


/*Ford Fulkerson_____________________________________________________________*/

int ford_fulkerson(){
    int flow=0;
    int token = -1;
    init_visited();
    while(visit_edges(0,token)){
        flow++;
        token++;
    }
    return flow;
}

int visit_edges(int vertexnumber, int token){
    edgePtr cur=ad_list[vertexnumber];
    while(cur!=NULL){
        if(visited[cur->to]!=token && cur->capacity!=0 && cur->to!=0){
            visited[cur->to]=token;
            if(cur->to==numberOfVertices-1){
                augment_Edge(cur);
                return TRUE;
            }
            else if(visit_edges(cur->to, token)){
                augment_Edge(cur);
                return TRUE;
            }  
        }
        cur=cur->next_in_ad_list;
    }
    return FALSE;
}

/*Process input________________________________________*/
void process_input(){
    int k,i,j,supermarkets,homes;
    scanf("%d %d",&Avenues,&Roads);
    Graph_init();
    scanf("%d %d",&supermarkets,&homes);
    for(k=0;k<supermarkets;k++){
        scanf("%d %d",&j,&i);
        add_supermerket_to_graph(i,j);
    }
    for(k=0;k<homes;k++){
        scanf("%d %d",&j,&i);
        add_home_to_graph(i,j);
    }
}

/*Frees_________________________________________________*/
void free_all(){
    free_Graph();
    free_visited();
}

int main(){
    process_input();
    printf("%d\n",ford_fulkerson());
    free_all();
    return 0;
}
