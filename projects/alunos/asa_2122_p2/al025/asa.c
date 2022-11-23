#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

struct node {
    int vertex;
    struct node* next;
};
struct node* createNode(int);

struct Graph {
    int nvertices;
    int *visited;
    int *color;
    struct node** adjLists;
};

struct node* createNode(int v) {
    struct node* newNode = can_fail_malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createAGraph(int vertices) {
    struct Graph* graph = can_fail_malloc(sizeof(struct Graph));
    graph->nvertices = vertices;

    graph->adjLists = can_fail_malloc(vertices * sizeof(struct node*));
    graph->visited = can_fail_malloc(vertices * sizeof(int));
    graph->color = can_fail_malloc(vertices * sizeof(int));

    int i;
    for (i = 0; i < vertices; i++){
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
        graph->color[i] = 0;
    }

    return graph;
}

void addEdge(struct Graph* graph, int s, int d) {

    struct node* newNode = createNode(s);
    newNode->next = graph->adjLists[d];
    graph->adjLists[d] = newNode;
}

void DFS(struct Graph* graph, int vertex) {

    struct node* temp = graph->adjLists[vertex];

    graph->visited[vertex] = 1;

    graph->color[vertex] += 1;

    while (temp != NULL) {

        if (graph->visited[temp->vertex] == 0) {

            DFS(graph, temp->vertex);
        }
        temp = temp->next;
    }
}

void DFS_cycle(struct Graph* graph, int vertex) {

    struct node* temp = graph->adjLists[vertex];

    if(graph->color[vertex] == 0)
        graph->color[vertex] = 1;

    while (temp != NULL) {

        if(graph->color[vertex] == 1 && graph->color[temp->vertex] == 1){
            printf("0\n");            
            exit(0);
        }

        if(graph->color[temp->vertex] != 2){

            DFS_cycle(graph, temp->vertex);
        }
            
        temp = temp->next;
    }

    graph->color[vertex] = 2;    
}

void getLCA(struct Graph* graph, int n){

    int i, *lca, flag = -1;

    lca = can_fail_malloc(n * sizeof(int));

    for(i = 0; i < n; i++){
        lca[i] = 0;
    }

    for(i = 0; i < graph->nvertices; i++){
        struct node* temp = graph->adjLists[i];
        while (temp)
        {
            if(graph->color[i] == 2 && graph->color[temp->vertex] == 2)
                lca[temp->vertex] = 1;
            temp = temp->next;
        }
    }

    for(i = 0; i < n; i++){
        if(lca[i] != 1 && graph->color[i] == 2){
            printf("%d ", i+1);
            flag = 1;
        }
    }

    if(flag == -1)
        printf("-");

    printf("\n");
}

int main(int argc, char *argv[])
{
    int n, e, u, v;

    if(scanf("%d %d", &u, &v) != 2)
        exit(0);

    u--;
    v--;
    
    if(scanf("%d %d", &n, &e)!= 2)
        exit(0);

    int i = 0, j = 0, l = 0;
    
    struct Graph* graph = createAGraph(n);

    for(l = 0; l < e; l++){
        if(scanf("%d %d", &i, &j)!= 2)
            exit(0);
        addEdge(graph, i-1, j-1);
    }

    for(i = 0; i < n; i++){
        if(graph->color[i] == 0){
            DFS_cycle(graph, i);
        }
    }

    for(i = 0; i < n; i++){
        graph->color[i] = 0;
    }

    DFS(graph, u);

    for(i = 0; i < n; i++){
        graph->visited[i] = 0;
    }

    DFS(graph, v);


    getLCA(graph, n);


    return 0;
}