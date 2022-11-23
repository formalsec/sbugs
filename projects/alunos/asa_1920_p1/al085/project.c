#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/* Duarte Penalva Boto - n92457 - 085 */

#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 64

#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct node {
    int adj;
    struct node* next;
} node;

node** adjList;

int numV, numE;
int* vertices;

int processInput();
void addNode(node** list, int vertex, int adj);
void freeList(node** list);
void printVertices();

void dfsVisit(node** list, int vertex, int* colors, int* parent, node** update);
void updateVertex(int vertex, int* parent, node** update);

int main() {
    int i;
    processInput();
    
    int colors[numV];
    int parent[numV];
    for (i = 0; i < numV; i++) {
        colors[i] = WHITE;
        parent[i] = -1;
    }

    node** updateList = can_fail_malloc(numV * sizeof(node*));
    for (i = 0; i < numV; i++) {
        updateList[i] = NULL;
    }

    
    for (i = 0; i < numV; i++) {
        if (colors[i] == WHITE) dfsVisit(adjList, i, colors, parent, updateList);
    }

    printVertices();

    free(vertices);
    freeList(adjList);
    freeList(updateList);
    return 0;
}

int processInput() {
    int i;
    char buffer[BUFFER_SIZE];
    fgets(buffer, BUFFER_SIZE, stdin);
    
    sscanf(buffer, "%d,%d", &numV, &numE); 

    vertices = can_fail_malloc(numV * sizeof(int));
    for (i = 0; i < numV; i++) {
        fgets(buffer, BUFFER_SIZE, stdin);
        sscanf(buffer, "%d", &(vertices[i]));
    }

    adjList = can_fail_malloc(numV * sizeof(node*));
    for (i = 0; i < numV; i++) {
        adjList[i] = NULL;
    }
    for (i = 0; i < numE; i++) {
        int vertex, adj;
        fgets(buffer, BUFFER_SIZE, stdin);
        sscanf(buffer, "%d %d", &vertex, &adj);
        addNode(adjList, vertex - 1, adj - 1);
    }

    /* // DEBUG: REMOVE LATER
    printf("V: %d\nE: %d\n", numV, numE);
    for (i = 0; i < numV; i++) {
        printf("%d:N=%d -", i + 1, vertices[i]);
        node* n = adjList[i];
        while (n != NULL) {
            printf(" %d", (n->adj) + 1);
            n = n->next;
        }
        printf("\n");
    }
    printf("\n");
    // END DEBUG */ 
    return 0;
}

void addNode(node** list, int vertex, int adj) {
    if (list[vertex] == NULL) {
        list[vertex] = can_fail_malloc(sizeof(node));
        list[vertex]->adj = adj;
        list[vertex]->next = NULL;
    } else {
        node* n = can_fail_malloc(sizeof(node));

        n->next = list[vertex];
        n->adj = adj;
        list[vertex] = n;
    }
}

void freeList(node** list) {
    int i;
    for (i = 0; i < numV; i++) {
        if (list[i] != NULL) {
            node* n = list[i];
            node* temp = n->next;
            free(n);
            while (temp != NULL) {
                n = temp;
                temp = n->next;
                free(n);
            }
        }
    }

    free(list);
}

void printVertices() {
    int i;
    for (i = 0; i < numV; i++) {
        printf("%d\n", vertices[i]);
    }
}

void dfsVisit(node** list, int vertex, int* colors, int* parent, node** update) {
    colors[vertex] = GRAY;
    node* adj = list[vertex];
    while (adj != NULL) {
        if (colors[adj->adj] == WHITE) {
            parent[adj->adj] = vertex;
            dfsVisit(list, adj->adj, colors, parent, update);
        } else {
            addNode(update, adj->adj, vertex);
        }
        if (vertices[vertex] < vertices[adj->adj]) vertices[vertex] = vertices[adj->adj];
        adj = adj->next;
    }
    node* updtAdj = update[vertex];
    while(updtAdj != NULL) {
        if (vertices[updtAdj->adj] < vertices[vertex]) {
            vertices[updtAdj->adj] = vertices[vertex];
            updateVertex(updtAdj->adj, parent, update);
        }
        updtAdj = updtAdj->next;
    }
    colors[vertex] = BLACK;
}

void updateVertex(int vertex, int* parent, node** update) {
    node* adj = update[vertex];
    while (adj != NULL) {
        if (vertices[adj->adj] < vertices[vertex]) {
            vertices[adj->adj] = vertices[vertex];
            updateVertex(adj->adj, parent, update);
        }
        adj = adj->next;
    }
    if (parent[vertex] >= 0 && vertices[parent[vertex]] < vertices[vertex]) {
        vertices[parent[vertex]] = vertices[vertex];
        updateVertex(parent[vertex], parent, update);
    }
}
