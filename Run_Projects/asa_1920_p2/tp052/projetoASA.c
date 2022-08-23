#include <stdio.h>
#include <stdlib.h>
/*Realizado por:
Pedro Gomes
93747*/

struct Node{
    int x;
    int y;
    int capacity;
    struct Node* next;
};

struct AdjList {
    struct Node *head;
};

struct Graph { 
    int V;
    int avenues;        /*equivalente ao y(comeca a 0 em cima)*/
    int streets;        /*equivalente ao x(comeca a 0 a esquerda)*/
    struct AdjList* array;
    struct AdjList* parent; 
};

struct Node* createNode(int y, int x, struct Graph* graph){
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->x = x;
    newNode->y = y;
    newNode->next = NULL;
    newNode->capacity = 1;
    return newNode;
}

struct Graph* createGraph(int av, int str){
    int i, j;
    int V = av * str;
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->avenues = av;
    graph->streets = str;
    graph->array = (struct AdjList*) malloc(((2 * V) + 2) * sizeof(struct AdjList));
    graph->parent = (struct AdjList*) malloc(((2 * V) + 2) * sizeof(struct AdjList));
    for (i = 0;i < 2 * V + 2;i ++) 
        graph->parent[i].head = NULL; 
    for(i = 0;i < (2 * V) + 2; i++)
        graph->array[i].head = NULL;
    graph->array[V].head = (struct Node*) createNode(-1,0,graph);       /*source=(-1,0)*/
    graph->array[V + 1].head = (struct Node*) createNode(0,-1,graph);   /*sink=(0,-1)*/
    for(i = 0;i < av;i ++){
        for(j = 0;j < str;j ++){
                if(i == 0){
                    if(j == 0){
                        struct Node* adjNode1 = createNode(i + 1, j + 2, graph);
                        struct Node* adjNode2 = createNode(i + 2, j + 1, graph);
                        struct Node* outVertex = createNode(i + 1, j + 1, graph);
                        adjNode1->next = adjNode2;
                        graph->array[i*str+j+V].head= adjNode1;
                        graph->array[i*str+j].head = outVertex;
                    }
                    else if(j == str - 1){
                        struct Node* adjNode1 = createNode(i + 1, str - 1, graph);
                        struct Node* adjNode2 = createNode(i + 2, str, graph);
                        struct Node* outVertex = createNode(i + 1, j + 1, graph);
                        adjNode1->next = adjNode2;
                        graph->array[i*str+j+V].head= adjNode1;
                        graph->array[i*str+j].head = outVertex;
                    }
                    else{
                        struct Node* adjNode1 = createNode(i + 1, j, graph);
                        struct Node* adjNode2 = createNode(i + 1, j + 2, graph);
                        struct Node* adjNode3 = createNode(i + 2, j + 1, graph);   
                        struct Node* outVertex = createNode(i + 1, j + 1, graph);
                        adjNode1->next = adjNode2;
                        adjNode2->next = adjNode3;
                        graph->array[i*str+j+V].head= adjNode1;
                        graph->array[i*str+j].head = outVertex;
                    }
                }
                else if(i == av - 1){
                    if(j == 0){
                        struct Node* adjNode1 = createNode(i + 1, j + 2, graph);
                        struct Node* adjNode2 = createNode(i, j + 1, graph);
                        struct Node* outVertex = createNode(i + 1, j + 1, graph);
                        adjNode1->next = adjNode2;
                        graph->array[i*str+j+V].head= adjNode1;
                        graph->array[i*str+j].head = outVertex;
                    }
                    else if(j == str - 1){
                        struct Node* adjNode1 = createNode(i + 1, str - 1, graph);
                        struct Node* adjNode2 = createNode(i, str, graph);
                        struct Node* outVertex = createNode(i + 1, j + 1, graph);
                        adjNode1->next = adjNode2;
                        graph->array[i*str+j+V].head= adjNode1;
                        graph->array[i*str+j].head = outVertex; 
                    }
                    else{
                        struct Node* adjNode1 = createNode(i + 1, j, graph);
                        struct Node* adjNode2 = createNode(i + 1, j + 2, graph);
                        struct Node* adjNode3 = createNode(i, j + 1, graph);
                        struct Node* outVertex = createNode(i + 1, j + 1, graph);   
                        adjNode1->next = adjNode2;
                        adjNode2->next = adjNode3;
                        graph->array[i*str+j+V].head= adjNode1;
                        graph->array[i*str+j].head = outVertex;
                    }
                }
                else{
                    if(j == 0){
                        struct Node* adjNode1 = createNode(i, j + 1, graph);
                        struct Node* adjNode2 = createNode(i + 2, j + 1, graph);
                        struct Node* adjNode3 = createNode(i + 1, j + 2, graph);
                        struct Node* outVertex = createNode(i + 1, j + 1, graph);   
                        adjNode1->next = adjNode2;
                        adjNode2->next = adjNode3;
                        graph->array[i*str+j+V].head= adjNode1;
                        graph->array[i*str+j].head = outVertex;
                    }
                    else if(j == str - 1){
                        struct Node* adjNode1 = createNode(i, j + 1, graph);
                        struct Node* adjNode2 = createNode(i + 2, j + 1, graph);
                        struct Node* adjNode3 = createNode(i + 1, j, graph);
                        struct Node* outVertex = createNode(i + 1, j + 1, graph);   
                        adjNode1->next = adjNode2;
                        adjNode2->next = adjNode3;
                        graph->array[i*str+j+V].head= adjNode1;
                        graph->array[i*str+j].head = outVertex;
                    }
                    else{
                        struct Node* adjNode1 = createNode(i, j + 1, graph);
                        struct Node* adjNode2 = createNode(i + 2, j + 1, graph);
                        struct Node* adjNode3 = createNode(i + 1, j + 2, graph);
                        struct Node* adjNode4 = createNode(i + 1, j, graph);
                        struct Node* outVertex = createNode(i + 1, j + 1, graph);   
                        adjNode1->next = adjNode2;
                        adjNode2->next = adjNode3;
                        adjNode3->next = adjNode4;
                        graph->array[i*str+j+V].head= adjNode1;
                        graph->array[i*str+j].head = outVertex;
                    }
                }
        }
    }
    return graph;
}

struct Graph* getStreets(){
    int avenues ,streets;
    scanf("%d %d", &avenues, &streets);
    struct Graph* graph = createGraph(avenues, streets);
    return graph;
}

void addSupermarket(int x, int y, struct Graph* graph){
    struct Node* sink = createNode(0,-1,graph);
    sink->next = graph->array[(x - 1) + graph->streets * (y - 1)].head;
    graph->array[(x - 1) + graph->streets * (y - 1)].head = sink;
    
}

void addCitizen(int x, int y, struct Graph* graph){
    struct Node* source = createNode(-1,0,graph);
    source->next = graph->array[(x - 1) + graph->streets * (y - 1)].head;
    graph->array[(x - 1) + graph->streets * (y - 1)].head = source;
}

void getCitizenSupermarket(struct Graph* graph){
    int citizens, supermarkets, i, x, y;
    scanf("%d %d", &supermarkets, &citizens);
    for(i = 0;i < supermarkets; i++){
        scanf("%d %d",&y, &x);
        addSupermarket(x, y, graph);
    }
    for(i = 0;i < citizens;i ++){
        scanf("%d %d",&y, &x);
        addCitizen(x, y, graph);
    }
}
int getShortestPaths(struct Graph* graph, struct Node* source, struct Node* sink){
    int v,index0 = 0,indexf = 0;
    int visited[2 * graph->V + 2];
    struct Node* queue[2 * graph->V + 2];
    struct Node* tmp,*u;
    for(v = 0;v < 2 * graph->V + 2;v ++){
        visited[v]=0;
    }
    queue[0] = source;
    indexf++;
    visited[0] = 1;
    graph->parent[graph->V].head = NULL;
    while(queue[index0]){
        u = queue[index0];
        queue[index0] = NULL;
        index0++;
        tmp = u;
        while(tmp){
            if(tmp->capacity > 0){
                queue[indexf] = graph->array[((tmp->x - 1) + (tmp->y - 1) * graph->streets)].head;
                indexf++;
                graph->parent[((tmp->x - 1) + (tmp->y - 1) * graph->streets)].head = u;
                visited[((tmp->x - 1) + (tmp->y - 1) * graph->streets)]=1;
            }
        }
        tmp = tmp ->next;
    }
    return visited[graph->V + 1];
}
    

int runFlow(struct Graph* graph, struct Node* source, struct Node* sink){
    int max_flow = 0;
    struct Node* v;
    struct Node* u;
    struct Node* tmp;
    while(getShortestPaths(graph, source, sink)){ 
        for (v = sink; v != source; v = graph->parent[((v->x - 1) + (v->y - 1) * graph->streets)].head){ 
            u = graph->parent[((v->x - 1) + (v->y - 1) * graph->streets)].head;
            u = graph->array[((u->x - 1) + (u->y - 1) * graph->streets)].head;
            while(u){
                if(u->x == v->x && u->y == v->y){
                    u->capacity--;
                }
                u = u->next;
            } 
            u = graph->parent[((v->x - 1) + (v->y - 1) * graph->streets)].head;
            tmp = graph->array[((v->x - 1) + (v->y - 1) * graph->streets)].head;
            while(tmp){
               if(u->x == tmp->x && u->y == tmp->y){
                    tmp->capacity++;
                }
                tmp = tmp->next; 
            } 
        } 
        max_flow++;
    }
    return max_flow;
}

int main(){
    struct Graph* graph = getStreets();
    getCitizenSupermarket(graph);
    int maxFlow = runFlow(graph,graph->array[graph->V].head,graph->array[graph->V + 1].head);
    printf("%d",maxFlow);
    return 0;
}