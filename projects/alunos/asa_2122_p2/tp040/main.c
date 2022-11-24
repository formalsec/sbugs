#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

enum color { WHITE, GRAY, BLACK, RED };

typedef struct node {
    int vertex;
    struct node* next;
} *Node;

/* Returns head if successful, NULL if node tries inserting a 3rd progenitor */
Node insert(Node head, int vertex) {
    Node child = (Node) can_fail_malloc(sizeof(struct node));
    child->vertex = vertex;
    child->next = NULL;

    if (head == NULL) {
        return child;
    }
    if (head->next != NULL) {
        /* If it has gotten here, list already has 2 vertexes
         * Cannot have 3 as that would mean node has 3 progenitors */
        return NULL;
    }
    if (head->vertex > vertex) {
        child->next = head;
        return child;
    }
    if (head->next == NULL) {
        head->next = child;
        return head;
    }
    return head;
}

void destroy(Node head) {
    if (head != NULL) {
        destroy(head->next);
        free(head);
    }
}

/* Returns 1 if back edge is found, 0 otherwise */
int DFS_visit(int u, int numV, Node adj[], enum color color[]) {
    color[u] = GRAY;

    Node n;
    for (n = adj[u]; n != NULL; n = n->next) {
        /* -1 because vertex will only be used for accessing arrays (index 0) */
        int vertex = n->vertex - 1;
        enum color n_color = color[vertex];
        if (n_color == WHITE) {
            if (DFS_visit(vertex, numV, adj, color))
                return 1;
        }
        else if (n_color == GRAY) {
            /* Back edge found, graph is cyclic */
            return 1;
        }
    }

    color[u] = BLACK;
    return 0;
}

/* Returns 1 if back edge is found, 0 otherwise */
int DFS(int numV, Node adj[]) {
    enum color *color = (enum color*) can_fail_malloc(sizeof(enum color) * numV);

    int u;
    for (u = 0; u < numV; u++) {
        color[u] = WHITE;
    }

    for (u = 0; u < numV; u++) {
        if (color[u] == WHITE)
            if (DFS_visit(u, numV, adj, color)) {
                free(color);
                return 1;
            }
    }
    free(color);
    return 0;
}

/* mode 0 for first vertex, mode 1 for second vertex */
void LCA_visit(int u, int numV, Node adj[], enum color color[], int mode) {
    if (!mode)
        color[u] = GRAY;
    else if (color[u] == GRAY) {
        color[u] = BLACK;
    }

    Node n;
    for (n = adj[u]; n != NULL; n = n->next) {
        int vertex = n->vertex - 1;
        enum color n_color = color[vertex];
        if (n_color == WHITE || mode) {
            LCA_visit(vertex, numV, adj, color, mode);
        }
    }
}

/* void filter_visit(int u, int numV, Node adj[], enum color color[]) {
    Node n;
    for (n = adj[u]; n != NULL; n = n->next) {
        int vertex = n->vertex - 1;
        enum color n_color = color[vertex];
        if (n_color == BLACK) {
            filter_visit(vertex, numV, adj, color);
        }
    }
    color[u] = RED;
} */

/* Lowest Common Ancestor */
void LCA(int vertex1, int vertex2, int numV, Node adj[]) {
    enum color *color = (enum color*) can_fail_malloc(sizeof(enum color) * numV);

    int u;
    for (u = 0; u < numV; u++) {
        color[u] = WHITE;
    }

    LCA_visit(vertex1-1, numV, adj, color, 0);
    LCA_visit(vertex2-1, numV, adj, color, 1);

    for (u = 0; u < numV; u++) {
        Node n;
        if (color[u] == BLACK || color[u] == RED) {
            for (n = adj[u]; n != NULL; n = n->next) {
                int vertex = n->vertex - 1;
                enum color n_color = color[vertex];
                if (n_color == BLACK) {
                    color[vertex] = RED;
                }
            }
        }
    }

    int numLCA = 0;
    for (u = 0; u < numV; u++) {
        if (color[u] == BLACK) {
            printf("%d ", u+1);
            numLCA++;
        }
    }

    if (numLCA == 0) {
        printf("-");
    }
    printf("\n");
    free(color);
}

int main() {
    int vertex1, vertex2, number_vertexes, number_edges, scan, i;

    scan = scanf("%d %d", &vertex1, &vertex2);
    if (scan != 2) {
        printf("0\n");
        return 0;
    }
    scan = scanf("%d %d", &number_vertexes, &number_edges);
    if (scan != 2)  {
        printf("0\n");
        return 0;
    }
    Node *adjList = (Node*) can_fail_malloc(sizeof(Node) * number_vertexes);
    for (i = 0; i < number_vertexes; i++)
        adjList[i] = NULL;

    int temp_vertex1, temp_vertex2;
    for (i = 0; i < number_edges; i++) {
        scan = scanf("%d %d", &temp_vertex1, &temp_vertex2);
        if (scan != 2) {
            printf("0\n");
            return 0;
        }

        adjList[temp_vertex2-1] = insert(adjList[temp_vertex2-1], temp_vertex1);
        if (adjList[temp_vertex2-1] == NULL) {
            printf("0\n");
            return 0;
        }
    }

    if (DFS(number_vertexes, adjList)) {
        printf("0\n");
        return 0;
    }

    LCA(vertex1, vertex2, number_vertexes, adjList);

    for (i = 0; i < number_vertexes; i++)
        destroy(adjList[i]);
    free(adjList);

    return 0;
}
