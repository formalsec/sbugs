/*Primeiro projeto de ASA*/
/*Grupo al054*/
/*Pedro Almeida n 92538*/
/*Tiago Fournigault n 92562*/

#include <stdio.h> 
#include <stdlib.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define RED 3

  
typedef struct Node{ 
    int dest; 
    struct Node* next; 
} *VerticeNode; 
  
typedef struct VerticeList{
    int color;
    int circle;
    int expected;
    int real; 
    VerticeNode head;  
} *VerticeList; 
  
typedef struct Graph{ 
    int numverts; 
    int numedges;
    VerticeList vertices; 
} *Graph; 

Graph graph;

void createGraph(int vert, int edge){ 

    graph = (Graph) malloc(sizeof(struct Graph)); 
    graph->numverts = vert;
    graph->numedges = edge;
    graph->vertices = (VerticeList) malloc(vert * sizeof(struct VerticeList)); 

    int i, grade; 
    for (i = 0; i < vert; ++i){
        graph->vertices[i].head = NULL;
        graph->vertices[i].color = WHITE;
        scanf("%d", &grade);
        graph->vertices[i].expected = grade;
        graph->vertices[i].real = grade;
    } 
  
} 
  
void addEdge(int src, int dest){ 

    VerticeNode newNode = (VerticeNode) malloc(sizeof(struct Node)); 
    newNode->dest = dest; 
    newNode->next = graph->vertices[src].head; 
    graph->vertices[src].head = newNode;

} 

void printGraph(){ 

    int i;
    for (i = 0; i < graph->numverts; ++i){
        printf("%d\n", graph->vertices[i].real);
    } 

} 

/*Se o vertice u tem vertices adjacentes brancos, aplicamos lhes dfsVisit*/
/*Se o vertice u tem vertices adjacentes cinzentos ou contornados a vermelho, contornamos u a vermelho*/
/*Se o vertice u tem vertices adjacentes com nota superior, a sua nota e alterada*/
void dfsVisit(int u){

    int max = graph->vertices[u].expected;
    graph->vertices[u].color = GRAY;
    VerticeNode aux = graph->vertices[u].head;
    while(aux){
        int v = aux->dest;
        if(graph->vertices[v].color == WHITE ){
            dfsVisit(v);
        }
        if(graph->vertices[v].color == GRAY || graph->vertices[v].circle == RED){
            graph->vertices[u].circle = RED;
        }
        if(graph->vertices[v].real > max){
            max = graph->vertices[v].real;
        }
        aux = aux->next;
    }
    graph->vertices[u].real = max;
    graph->vertices[u].color = BLACK;

}

/*Primeiramente aplicamos dfsVisit a todos os vertices brancos*/
/*De seguida aplicamos dfsVisit a todos os vertices contornados a vermelho*/
void dfs(){

    int i, j;
    for(i = 0; i < graph->numverts; i++){
        if(graph->vertices[i].color == WHITE){
            dfsVisit(i);
        }
    }
    for(i = 0; i < graph->numverts; i++){
        if(graph->vertices[i].circle == RED){
            for(j = 0; j < graph->numverts; j++){
                if(graph->vertices[j].circle == RED){
                    graph->vertices[j].color = WHITE;
                }
            }
            dfsVisit(i);
        }
    }
}

int main(){   

    int a, b;
    scanf("%d,%d", &a, &b);
    createGraph(a, b);

    int i;
    for(i = 0; i < graph->numedges; i++){
        scanf("%d %d", &a, &b);
        addEdge(--a, --b); 
    }

    dfs();
    printGraph();
    return 0; 

} 