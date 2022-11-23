#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFFER 101

typedef struct{
    int grade;
} Vertex;

typedef struct node Node;

struct node{
    int dst;
    Node* nxt;
};

typedef struct Edge{
    int src;
    int dst;
} Edge;

typedef struct Graph{
    int numVer;
    Vertex *vertices;
    Node** head;
} Graph;

Node* newNode(int dst) {
    Node* newNode = (Node*) can_fail_malloc(sizeof(Node));
    newNode->dst = dst;
    newNode->nxt = NULL;
    return newNode;
}

Graph* newGraph(int vertices, int numOfRelationship);

void print(Graph* graph){
    int x;
    for(x = 0; x < graph->numVer; x++){
        Node* ptr = graph->head[x];
        int grade = graph->vertices[x].grade;
        while(ptr != NULL){
            if(graph->vertices[ptr->dst].grade > grade){
                grade = graph->vertices[ptr->dst].grade;
            }
            ptr = ptr->nxt;
        }
        printf("%d\n", grade);
    }
}

int main(){

    char buffer[MAX_BUFFER];

    Graph* graph;

    char delim1[] = ",";

    char *token;

    int numOfStudents = 0;

    int numOfRelationships = 0;

    fgets(buffer, MAX_BUFFER, stdin);

    token = strtok(buffer, delim1);

    numOfStudents = strtol(token, NULL, 10);

    token = strtok(NULL, delim1);

    numOfRelationships = strtol(token, NULL, 10);

    if(numOfStudents < 2 || numOfRelationships < 1){
        return 1;
    }

    graph = newGraph(numOfStudents, numOfRelationships);

    print(graph);

    return 0;

}

Graph* newGraph(int vertices, int numOfRelationships){
    char buffer[MAX_BUFFER];
    char *token;
    char delim2[] = " ";
    Graph* graph = (Graph*) can_fail_malloc(sizeof(Graph));
    graph->numVer = vertices;
    graph->vertices = (Vertex*) can_fail_malloc(vertices * sizeof(Vertex));
    graph->head = (Node**) can_fail_malloc(vertices * sizeof(Node*));
    int x;
    for(x = 0; x < vertices; x++){
        fgets(buffer, MAX_BUFFER, stdin);
        graph->vertices[x].grade = strtol(buffer, NULL, 10);
        graph->head[x]=NULL;
    }

    for(x = 0; x < numOfRelationships; x++){
        int current, aux;
        fgets(buffer, MAX_BUFFER, stdin);
        token = strtok(buffer, delim2);
        current = strtol(token, NULL, 10)-1;
        token = strtok(NULL, delim2);
        aux = strtol(token, NULL, 10)-1;

        Node* temp = (Node*)can_fail_malloc(sizeof(Node));
        temp->dst = current;
        temp->nxt = graph->head[aux];
        graph->head[aux] = temp;
    }

    return graph;
}

