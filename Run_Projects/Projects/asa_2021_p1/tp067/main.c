#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Definitions */

typedef struct node *link;
struct node {
	int connection;
	link next;
};

typedef struct {
    int degree;
    link listOfAdj;
    link lastOfAdj;
} Domino;

int hits;
int sequence;

Domino** graph;

void dominoCracker(int vertexs, int arcs) {
    link adj = NULL;
    int i = 0, pointer = -1, topoPointer = 0;
    int currDomi = 0;
    int* stack = (int*)malloc((arcs > 0 ? arcs+1 : 1)*sizeof(int));
    int* topoOrder = (int*)malloc((arcs > 0 ? arcs+1 : 1)*sizeof(int));

    for( i = 0; i < vertexs; i++ ) {
        if( graph[i]->degree == 0 ) {
            hits++;
            pointer++;
            stack[pointer] = i;
        }
    }

    /* topological sort */
    for( ; pointer > -1; ) {
        currDomi = stack[pointer];
        topoOrder[topoPointer] = currDomi;
        topoPointer++;

        for( adj = graph[currDomi]->listOfAdj; adj != NULL; adj = adj->next ) {

            graph[adj->connection]->degree--;

            if( graph[adj->connection]->degree == 0 ) {
                stack[pointer] = adj->connection;
                pointer++;
            }
        }

        pointer--;
    }

    /* longest path */
    for( i = 0; i < topoPointer; i++ ) {
        currDomi = topoOrder[i];
        adj = graph[currDomi]->listOfAdj;

        if( adj != NULL && graph[currDomi]->degree+1 > sequence ) sequence = graph[currDomi]->degree+1;

        for( ; adj != NULL; adj = adj->next ) {
            if( graph[currDomi]->degree+1 > graph[adj->connection]->degree ) {
                graph[adj->connection]->degree = graph[currDomi]->degree + 1;
            }
        }
    }
    free(stack);
    free(topoOrder);
}

/** inserts a new connection */
void insertLink(int rela, int relb) {
    link newAdj = malloc(sizeof(struct node));

    if( graph[rela-1]->listOfAdj == NULL ) graph[rela-1]->listOfAdj = newAdj;
    else graph[rela-1]->lastOfAdj->next = newAdj;

    newAdj->next = NULL;
    newAdj->connection = relb-1;

    graph[rela-1]->lastOfAdj = newAdj;
    graph[relb-1]->degree++;
}

/* main */
int main(int argc, char** argv) {
    int N = 0, M = 0;
    int rela = 0, relb = 0;
    int i = 0;
    hits = 0;
    sequence = 0;
    
    scanf("%d %d", &N, &M);
    
    if( M > 0 && N > 0 ) {
        graph = (Domino**)malloc(N*sizeof(Domino*));

        while( i < N ) {
            graph[i] = (Domino*)malloc(sizeof(Domino));
            graph[i]->degree = 0;
            graph[i]->listOfAdj = NULL;
            graph[i]->lastOfAdj = NULL;
            i++;
        }
        i = 0;

        while( i < M ) {
            /** scan arcs **/
            scanf("%d %d", &rela, &relb);
            
            if( rela > 0 && relb > 0 && rela != relb && rela <= N && relb <= N ) insertLink(rela, relb);
            i++;
        }
        dominoCracker(N, M);
    }
    
    /** print output **/
    printf("%d %d\n", M == 0 ? N : hits, N == 0 ? 0 : sequence+1);

    return 0;
}