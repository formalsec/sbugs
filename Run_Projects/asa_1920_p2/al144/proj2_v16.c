/* Analise e Sintese de Algoritmos, DEI/IST/ULisboa 2019-2020 */
/* Trabalho realizado por:
 * Pedro Magalhaes e Silva, nº92540
 * Grupo nº144
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NIL -1

#define MAX_CAPACITY 1
#define NO_CAPACITY 0

#define UPPER_BORDER 1
#define LEFT_BORDER 2
#define RIGHT_BORDER 3
#define LOWER_BORDER 4

/* Each vertex is divided into two, an "outward-going" and an "inward-going" vertex.
 * The outward-going vertex will receive/manage all outgoing edges of the original vertex;
 * While the inward-going vertex shall receive/manage all incoming edges;
 * All outward-going vertexes shall have an EVEN number as it's "id" (associated integer), starting with at 0;
 * While the inward-going shall have the following ODD number;
 * After all "sub-vertexes" are defined, the (next) last two "id's" will be the source and target (vertexes), respectively;
 */

int source_id;      /*"id" of the source vertex*/
int target_id;      /*"id" of the target vertex*/
int n_Vertex;       /* total number of vertexes, including "sub-vertexes"*/
short* parents;     /* array including the "parent vertex" of each vertex in a Breadth First Search*/
int* queue;         /* priority queue for the application of Breadth First Searches*/

typedef struct Edge{    /* represents an edge between two vertexes*/
    int to;
    short capacity;
    struct Edge* next;
} edge;

typedef edge* elink;

/*-----------------------ADJACENCY-LISTS------------------------*/

/* "allocAdjLists" allocates the necessary memory for the creation of an individual adjacency lists (for each vertex)*/
void allocAdjLists(elink** e){
    *e = (elink*) malloc(sizeof(elink)*n_Vertex);
    return;
}

/* Inicialization of every adjacency list, for every vertex*/
void initializeEdges(elink* edges){
    int i;
    for(i = 0; i < n_Vertex; i++){
        *(edges+i) = NULL;
    }
    return;
}

/* Adds an edge to the adjacency list of a specific vertex*/
void addEdge(elink* edges, elink new_edge, int from){
    new_edge->next = *(edges+from);
    *(edges+from) = new_edge;
    return;
}

/* Inverts the capacities of a pair of "opposite" edges*/
/* We assume that both vertexes (represented by the "id's" passed as arguments) are connected, and that there is a unitary capacity from v1 to v2*/
void invertCapacities(int v1, int v2, elink* edges){
    elink temp;
    temp = *(edges+v1);
    while( temp->to != v2 ){
        temp = temp->next;
    }
    temp->capacity = NO_CAPACITY;
    
    temp = *(edges+v2);
    while( temp->to != v1 ){
        temp = temp->next;
    }
    temp->capacity = MAX_CAPACITY;
    return;
}
/*----------------------------------------------------------------*/
/*--------------------BASIC-INFO-INITIALIZATION-------------------*/

/* "allocBasic" allocates the necessary memory for all of the basic information (within the context of the problem)*/
void allocBasic(int** M, int** N, int** S, int** C){
    *M = (int*)malloc(sizeof(int));  /*number of avenues*/
    *N = (int*)malloc(sizeof(int));  /*number of streets*/
    *S = (int*)malloc(sizeof(int));  /*number of supermarkets*/
    *C = (int*)malloc(sizeof(int));  /*number of citizens*/
    return;
}  

/* parses all of the basic data towards the resolution of the problem, reading from stdin*/
void parseBasic(int* M, int* N, int* S, int* C){
    scanf("%d %d", M, N);
    scanf("%d %d", S, C);
    source_id = ((*N)*(*M)*2);
    target_id = ((*N)*(*M)*2)+1;
    n_Vertex = ((*N)*(*M)*2)+2;
    parents = (short*)malloc(sizeof(short)*n_Vertex);
    queue = (int*)malloc(sizeof(int)*n_Vertex);         /* allocates the maximum number of elements possible for the priority queue*/
    return;
}

/* (in a map/grid context) determines wether the vertex belongs to the "first" or "last" street/line, or the "first" or "last" avenue/column; and which one
 * returns the integer 0 if the vertex doesn't belong to any of these*/
int borderSide(int i, int A){
    if ( (i >= 0) && (i <= (2*A)-2) ){
        return UPPER_BORDER;
    }
    else if ( (i >= (n_Vertex-2-(2*A))) && (i <= n_Vertex-4) ){
        return LOWER_BORDER;
    }
    else if ( (i%(2*A) == 0) && (i != 0) &&  (i != (n_Vertex-2-(2*A))) ){
        return LEFT_BORDER;
    }
    else if ( ((i+2)%(2*A) == 0) && (i != (2*A)-2) && (i != n_Vertex-4) ){
        return RIGHT_BORDER;
    }
    return 0;
}

int leftHandCorner(int i, int A){
    if ( (i == 0) || (i == n_Vertex-2-(2*A)) ){ /*Possible left hand corner "id's"*/
        return 1;
    }
    return 0;
}

int rightHandCorner(int i, int A){
    if( (i == (2*A)-2) || (i == n_Vertex-4) ){  /*Possible right hand corner "id's"*/
        return 1;
    }
    return 0;
}

/* The following "family" of functions represent the connection (through edges) of a given vertex to another within the context of a grid (in every direction possible, and the connection between "sub-vertexes" belonging to the same vertex)*/
void connectLeft(elink* edges, int i){
    elink e1, e2;
    e1 = (elink)malloc(sizeof(edge));   /*"current-out" to "left-in"*/
    e1->to = i-1;
    e1->capacity = MAX_CAPACITY;
    e1->next = NULL;
    addEdge(edges, e1, i);
    
    e2 = (elink)malloc(sizeof(edge));   /*"current-in" to "left-out"*/
    e2->to = i-2;
    e2->capacity = NO_CAPACITY;
    e2->next = NULL;
    addEdge(edges, e2, i+1);
}

void connectRight(elink* edges, int i){
    elink e1, e2;
    e1 = (elink)malloc(sizeof(edge));   /*"current-out" to "right-in"*/
    e1->to = i+3;
    e1->capacity = MAX_CAPACITY;
    e1->next = NULL;
    addEdge(edges, e1, i);
    
    e2 = (elink)malloc(sizeof(edge));   /*"current-in" to "right-out"*/
    e2->to = i+2;
    e2->capacity = NO_CAPACITY;
    e2->next = NULL;
    addEdge(edges, e2, i+1);
}

void connectAbove(elink* edges, int i, int A){
    elink e1, e2;
    e1 = (elink)malloc(sizeof(edge));   /*"current-out" to "above-in"*/
    e1->to = i-(2*A)+1;
    e1->capacity = MAX_CAPACITY;
    e1->next = NULL;
    addEdge(edges, e1, i);
    
    e2 = (elink)malloc(sizeof(edge));   /*"current-in" to "above-out"*/
    e2->to = i-(2*A);
    e2->capacity = NO_CAPACITY;
    e2->next = NULL;
    addEdge(edges, e2, i+1);
}

void connectBelow(elink* edges, int i, int A){
    elink e1, e2;
    e1 = (elink)malloc(sizeof(edge));   /*"current-out" to "below-in"*/
    e1->to = i+(2*A)+1;
    e1->capacity = MAX_CAPACITY;
    e1->next = NULL;
    addEdge(edges, e1, i);
    
    e2 = (elink)malloc(sizeof(edge));   /*"current-in" to "below-out"*/
    e2->to = i+(2*A);
    e2->capacity = NO_CAPACITY;
    e2->next = NULL;
    addEdge(edges, e2, i+1);
}

void connectWithin(elink* edges, int i){
    elink e1, e2;
    e1 = (elink)malloc(sizeof(edge));   /*"current-out" to "current-in"*/
    e1->to = i+1;
    e1->capacity = NO_CAPACITY;
    e1->next = NULL;
    addEdge(edges, e1, i);
    
    e2 = (elink)malloc(sizeof(edge));   /*"current-in" to "current-out"*/
    e2->to = i;
    e2->capacity = MAX_CAPACITY;
    e2->next = NULL;
    addEdge(edges, e2, i+1);
}

void prepAdj(elink* edges, int* A){
    int i, effec, border, l_corner, r_corner;
    effec = n_Vertex-2;                     /* The effective number of "sub-vertexes" in the graph. Doesn't account for the source and target vertexes, since these have no "sub-vertexes"*/
    
    for(i = 0; i < effec; i = i+2){
        border = borderSide(i, *A);         /* Flag allerting if a vertex belongs to the border of the grid, and if so which one*/
        l_corner = leftHandCorner(i, *A);   /* Flag allerting if a vertex is a left-hand corner of the grid*/
        r_corner = rightHandCorner(i, *A);  /* Flag allerting if a vertex is a right-hand corner of the grid*/
        
        if( (border == UPPER_BORDER) && (l_corner != 0) ){
            connectWithin(edges, i);
            connectRight(edges, i);
            connectBelow(edges, i, *A);
        }
        else if( (border == UPPER_BORDER) && (r_corner != 0) ){
            connectWithin(edges, i);
            connectLeft(edges, i);
            connectBelow(edges, i, *A);
        }
        else if( (border == LOWER_BORDER) && (l_corner != 0) ){
            connectWithin(edges, i);
            connectRight(edges, i);
            connectAbove(edges, i, *A);
        }
        else if( (border == LOWER_BORDER) && (r_corner != 0) ){
            connectWithin(edges, i);
            connectLeft(edges, i);
            connectAbove(edges, i, *A);
        }
        else if( (border == UPPER_BORDER) && (r_corner == 0) && (l_corner == 0)){
            connectWithin(edges, i);
            connectLeft(edges, i);
            connectRight(edges, i);
            connectBelow(edges, i, *A);
        }
        else if( (border == LOWER_BORDER) && (r_corner == 0) && (l_corner == 0)){
            connectWithin(edges, i);
            connectLeft(edges, i);
            connectRight(edges, i);
            connectAbove(edges, i, *A);
        }
        else if( border == LEFT_BORDER ){
            connectWithin(edges, i);
            connectAbove(edges, i, *A);
            connectBelow(edges, i, *A);
            connectRight(edges, i);
        }
        else if( border == RIGHT_BORDER ){
            connectWithin(edges, i);
            connectAbove(edges, i, *A);
            connectBelow(edges, i, *A);
            connectLeft(edges, i);
        }
        else{
            connectWithin(edges, i);
            connectAbove(edges, i, *A);
            connectBelow(edges, i, *A);
            connectLeft(edges, i);
            connectRight(edges, i);
        }
    }
}

/* edges: adjacency lists;
 * SMerc: the number of supermarket coordinates to analyze;
 * Av: the number of avenues;
 * Connects the target to all of the vertexes representative of supermarkets, whose coordinates are given from stdin, and "id's" are later calculated
 */
void connectTarget(elink* edges, int SMerc, int Av){
    int i, a, s, orig;
    elink e1, e2;
    for(i = 0; i < SMerc; i++){
        scanf("%d %d", &a, &s);
        orig = (2*(a-1))+((s-1)*2*Av);  /*"current-out" calculation*/
        
        e1 = (elink)malloc(sizeof(edge));
        e1->to = target_id;
        e1->capacity = MAX_CAPACITY;
        e1->next = NULL;
        addEdge(edges, e1, orig);       /*"current-out" to target*/
        
        e2 = (elink)malloc(sizeof(edge));
        e2->to = orig;
        e2->capacity = NO_CAPACITY;
        e2->next = NULL;
        addEdge(edges, e2, target_id);  /*target to "current-out"*/
    }
}

/* edges: adjacency lists;
 * Citiz: the number of citizen coordinates to analyze;
 * Av: the number of Avenues;
 * Connects the source to all of the vertexes representative of citizens, whose coordinates are given from stdin, and "id's" are later calculated
 */
void connectSource(elink* edges, int Citiz, int Av){
    int i, a, s, orig;
    elink e1, e2;
    for(i = 0; i < Citiz; i++){
        scanf("%d %d", &a, &s);
        orig = (2*(a-1))+((s-1)*2*Av);  /*"current-out" calculation*/
        
        e1 = (elink)malloc(sizeof(edge));
        e1->to = orig+1;
        e1->capacity = MAX_CAPACITY;
        e1->next = NULL;
        addEdge(edges, e1, source_id);  /*source to "current-in"*/
        
        e2 = (elink)malloc(sizeof(edge));
        e2->to = source_id;
        e2->capacity = NO_CAPACITY;
        e2->next = NULL;
        addEdge(edges, e2, orig+1);     /*"current-in" to source*/
    }
}

/*---------------------------------------------------------------*/
/*------------------------EDMONDS-KARP---------------------------*/

/* Applies a Breadth First Search to the graph in order to find the shortest augmenting path from the source vertex towards the target. If this path exists, then applies the flux accordingly and returns the integer 1. If it doesn't, returns the integer 0, and the application of the algorithm shall end.*/
int bfsMinPath(elink* edges){
    int i, v, p, f, l;
    elink e;
    f = 0;                                          /*Pointer to the next position/index to be read (vertex to be expanded)*/
    l = 0;                                          /*Pointer to the last free position/index in the array*/
    memset(parents, NIL, n_Vertex*sizeof(short));   /*Initialize the parents of all vertices as NIL (non-existent)*/
    memset(queue, NIL, n_Vertex*sizeof(int));
    
    *(queue+f) = source_id;                         /*Adding the source vertex to the priority queue*/
    l++;
    
    while(*(queue+f) != NIL){
        v = *(queue+f);
        e = *(edges+v);
        while(e != NULL){
            if ( (e->capacity == MAX_CAPACITY) && (*(parents+(e->to)) == NIL) && (e->to != source_id) ){
                *(parents+(e->to)) = v;
                if (e->to == target_id){
                    i = e->to;
                    p = *(parents+i);
                    while(p != NIL){
                        invertCapacities(p, i, edges);
                        i = p;
                        p = *(parents+i);
                    }
                    return 1;
                }
                *(queue+l) = e->to;
                l++;
            }
            e = e->next;
        }
        f++;
    }
    return 0;
}

/* Application of the Edmonds-Karp algorithm, returns the value of the maximum-flux within the given flux network*/
int edmondsKarp(elink* edges){
    int maxFlow, f;
    maxFlow = 0;
    while(1){
        f = bfsMinPath(edges);
        if (f == 0){
            break;
        }
        maxFlow++;
    }
    return maxFlow;
}
/*---------------------------------------------------------------*/
/*----------------------------MAIN-------------------------------*/

/* Freeing of all allocated memory*/
void freeAll(int* M, int* N, int* S, int* C, elink* edges){
    int i;
    elink e, temp;
    free(M);
    free(N);
    free(S);
    free(C);
    free(parents);
    free(queue);
    for(i = 0; i < n_Vertex; i++){
        e = *(edges+i);
        while(e != NULL){
            temp = e->next;
            free(e);
            e = temp;
        }
        continue;
    }
    free(edges);
    return;
}

int main(){
    int *M, *N, *S, *C;
    elink *edges;               /*Adjacency lists for the residual capacities of the flux network*/
    allocBasic(&M, &N, &S, &C);
    parseBasic(M, N, S, C);
    allocAdjLists(&edges);
    initializeEdges(edges);
    connectTarget(edges, *S, *M);
    connectSource(edges, *C, *M);
    prepAdj(edges, M);
    
    printf("%d\n", edmondsKarp(edges));
    
    freeAll(M, N, S, C, edges);
    return 0;
}
