#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/*Segundo projeto de ASA*/
/*Grupo al054*/
/*Pedro Almeida n 92538*/
/*Tiago Fournigault n 92562*/

#include <stdio.h> 
#include <stdlib.h>

#define CITIZEN 1
#define MARKET 2
#define WHITE 3
#define GRAY 4
#define BLACK 5

typedef struct Node{ 
    int dest; 
    int flux;
    struct Node* next; 
} *VerticeNode; 
  
typedef struct VerticeList{
    VerticeNode head;  
    int type;
    int height;
    int excess;
    int color;
    int d;
    int pi;
} *VerticeList; 
  
typedef struct Graph{ 
    int numverts; 
    int numedges;
    int nummarkets;
    int numcitizens;
    VerticeList vertices; 
} *Graph; 

typedef struct node {
    int val;
} *node_t;

int front;
int tail;
node_t queue;
Graph graph;

void addEdge(int src, int dest){ 

    VerticeNode newNode = (VerticeNode) can_fail_malloc(sizeof(struct Node)); 
    newNode->dest = dest;
    newNode->flux = 0; 
    newNode->next = graph->vertices[src].head; 
    graph->vertices[src].head = newNode;

} 

void createGraph(int M, int N, int S, int C){ 
    int vert = M*N + 2;
    int edge = 2*(M-1)*(N-1)+(M-1)+(N-1);
    int x, y;

    graph = (Graph) can_fail_malloc(sizeof(struct Graph)); 
    graph->numverts = vert;
    graph->numedges = edge;
    graph->nummarkets = S;
    graph->numcitizens = C;
    graph->vertices = (VerticeList) can_fail_malloc(((vert*2) - 2) * sizeof(struct VerticeList)); 

    int i;
    /*Cada vertice contem um vertice auxiliar (excepto source e sink)*/
    for (i = 0; i < (graph->numverts * 2 - 2); ++i){
        graph->vertices[i].head = NULL;
        graph->vertices[i].type = 0;
        graph->vertices[i].height = 0;
        graph->vertices[i].excess = 0;
        graph->vertices[i].color = WHITE;
        graph->vertices[i].d = 0;
        graph->vertices[i].pi = 0;
    }

    /*Ligar os vertices que representam mercados a sink*/
    for(i = 0; i < S; i++){
        scanf("%d %d", &x, &y);
        graph->vertices[M*(y-1) + x].type = MARKET;
        addEdge(M*(y-1)+x+vert-1, vert-1);
        addEdge(vert-1, M*(y-1)+x+vert-1);
    }

    /*Ligar os vertices que representam cidadaos a source*/
    for(i = 0; i < C; i++){
        scanf("%d %d", &x, &y);
        graph->vertices[M*(y-1) + x].type = CITIZEN;
        addEdge(0, M*(y-1)+x);
        addEdge(M*(y-1)+x, 0);
    }

    /*Criacao das arestas entre vertices (excepto entre mercados ou entre cidadaos)*/
    for(i = 1; i < vert - 1; i++){
        if(i <= M*(N - 1) && (graph->vertices[i].type != graph->vertices[i+M].type || graph->vertices[i+M].type == 0 || graph->vertices[i].type == 0)){
            addEdge(i+vert-1, i+M);
            addEdge(i+M, i+vert-1);
        }
        if(i % M != 0 && (graph->vertices[i].type != graph->vertices[i+1].type || graph->vertices[i+1].type == 0 || graph->vertices[i].type == 0)){
            addEdge(i+vert-1, i+1);
            addEdge(i+1, i+vert-1);
        }
        if(i != 1 && (i-1)%M != 0 && (graph->vertices[i].type != graph->vertices[i-1].type || graph->vertices[i-1].type == 0 || graph->vertices[i].type == 0)){
            addEdge(i+vert-1, i-1);
            addEdge(i-1, i+vert-1);
        }
        if(i > M && (graph->vertices[i].type != graph->vertices[i-M].type || graph->vertices[i-M].type == 0 || graph->vertices[i].type == 0)){
            addEdge(i+vert-1, i-M);
            addEdge(i-M, i+vert-1);
        }

        /*Criar aresta entre vertice principal e auxiliar*/
        addEdge(i, i+vert-1);
        addEdge(i+vert-1, i);
    }
}

int deQueue(){
    int u = queue[front].val;
    front++;
    return u;
}

void enQueue(int u){
    queue[tail].val=u;
    tail++;
}

int Bfs(){
    int i;
    graph->vertices[0].d = 0;
    graph->vertices[0].color = GRAY;
    graph->vertices[0].pi = 0;
    for(i = 1; i < (graph->numverts * 2 - 2); ++i){
        graph->vertices[i].d = -1;
        graph->vertices[i].color = WHITE;
        graph->vertices[i].pi = 0;
    }
    
    /*Aplicar bfs ao grafo residual iniciando a procura na source*/
    /*Terminar a procura ao encontar o sink*/
    enQueue(0);
    VerticeNode vizinho;
    while(front != tail){
        int u = deQueue();
        vizinho = graph->vertices[u].head;
        while(vizinho != NULL){
            if(graph->vertices[vizinho->dest].color == WHITE && ((vizinho->flux == 0 && ((u > graph->numverts - 1 && vizinho->dest < graph->numverts)|| vizinho->dest == u+graph->numverts-1 || u == 0)) || (vizinho->flux == -1 && ((u < graph->numverts - 1 && (vizinho->dest > graph->numverts - 1 || vizinho->dest == 0))|| vizinho->dest == u - graph->numverts + 1)))){
                graph->vertices[vizinho->dest].color = GRAY;
                graph->vertices[vizinho->dest].d = graph->vertices[u].d + 1;
                graph->vertices[vizinho->dest].pi = u;
                if(vizinho->dest == graph->numverts-1){
                    tail=0;
                    front=0;
                    return 1;
                }
                enQueue(vizinho->dest);
            }
            vizinho = vizinho->next;
        }
        graph->vertices[u].color = BLACK;
    }
    return 0;
}

int edmondsKarp(){
    int result = 0;

    /*Econtrar caminhos de aumento aplicando uma bfs ao grafo residual*/
    while(Bfs()){
        result++;
        int v;
        int u = graph->numverts-1;
        VerticeNode current;
        while(u != 0){
            /*Percorrer o caminho encontrado desde o sink a source para diminuir a capacidade das arestas*/
            v = graph->vertices[u].pi;
            current = graph->vertices[v].head;
            while(current->dest != u){
                current = current->next;
            }
            current->flux++;
            current = graph->vertices[u].head;
            while(current->dest != v){
                current = current->next;
            }
            current->flux--;
            u = v;
        }
        if(result == graph->numcitizens || result == graph->nummarkets){
            return result;
        }
    }
    return result;
}

int main(){   
    int M, N, S, C, result;
    scanf("%d %d", &M, &N);
    scanf("%d %d", &S, &C);
    createGraph(M, N, S, C);
    queue = (node_t)can_fail_malloc(((graph->numverts*2) - 2) * sizeof(struct node));

    result = edmondsKarp();
    printf("%d\n", result);
    return 0; 
} 