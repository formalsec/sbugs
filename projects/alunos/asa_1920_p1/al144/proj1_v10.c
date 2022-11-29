#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/*Analise e Sintese de Algoritmos, DEI/IST/ULisboa 2019-2020 */
/*Trabalho realizado por:
 * Pedro Magalhaes e Silva, nº92540
 * Grupo nº144
 */

#include <stdio.h>
#include <stdlib.h>

#define NOT_FOUND -1
#define MAX_INPUT_SIZE 100
#define WHITE -1
#define GREY 0
#define BLACK 1

/*----------------------STRUCTS------------------------*/
typedef struct Edge{    /*The "edge" struct will represent a friendship between two students (in the context of the problem).*/
    int to;
    struct Edge* next;
} edge;

typedef edge* elink;

typedef struct Node{    /*The "node struct shall be required during the application of "Tarjan's Algorithm".*/
    int number;
    struct Node* next;
} node;

typedef node* link;

struct Vertex;

typedef struct SCComp{  /*"sccomp" struct refers to a Strongly Connected Component.*/
    short colour;
    int max_grade;
    struct Vertex* v;  /*Every "SCC" points to a "vertex struct" which shall be the head of the list of vertices that compose this specific "SCC".*/
    struct SCComp* next;
}sccomp;

typedef struct Vertex{  /*The "vertex" struct will represent a student (in the context of the problem).*/
    int number;
    int grade;
    sccomp* scc;    /*Every vertex struct has a pointer to the "SCC" to which it belongs, this facilitates the determination of the final grade of the student.*/
    int d;
    int low;
    struct Vertex* next;    /*Every vertex has a pointer to the next vertex, within the SCC that both share.*/
} vertex;

/*------------------------------------------------------*/
/*------------------ADJACENCY-LISTS---------------------*/
void initialize_edges(elink* edges, int vertices){ /*Inicialization of every adjacency list, of every vertex.*/
    int i;
    for(i = 0; i < vertices; i++){
        *(edges+i) = NULL;
    }
    return;
}

void add_edge(elink* edges, elink new_edge, int from){
    new_edge->next = *(edges+from);
    *(edges+from) = new_edge;
    return;
}

/*------------------------------------------------------*/
/*---------------------NODE-STACK-----------------------*/
link new_node(int n){
    link new = (link)can_fail_malloc(sizeof(node));
    new->number = n;
    new->next = NULL;
    return new;
}

int is_empty(link root){
    if (root == NULL){
        return 1;
    }
    return 0;
}

void push(link* root, int n){
    link new;
    new = new_node(n);
    new->next = *root;
    *root = new;
}

int pop(link* root){
    link l;
    int pop;
    if ( is_empty(*root) ){
        return -1;
    }
    l = *root;
    *root = (*root)->next;
    pop = l->number;
    free(l);
    return pop;
}

int is_element(link root, int n){
    link l;
    l = root;
    while (l != NULL){
        if (l->number == n){
            return 1;
        }
        l=l->next;
    }
    return 0;
}

void free_list(link* L){
    link l, temp;
     l = (*L);
    if (l == NULL){
        free(L);
        return;
    }
    while(l != NULL){
        temp = l->next;
        free(l);
        l = temp;
    }
    free(L);
    return;
}

/*-----------------------------------------------------------*/    
/*------------------INFORMATION-PROCESSING-------------------*/
int readP1(){   /*Reads a number until a ' ' character is found.*/
    int i = 0;
    char c, number[MAX_INPUT_SIZE];
    for (c = getchar(); c!=' '; c = getchar()){
        number[i++] = c;
    }
    number[i] = '\0';
    return atoi(number);
}

int readNumber(){   /*Reads a number until a newline character is found.*/
    int i = 0;
    char c, number[MAX_INPUT_SIZE];
    for (c = getchar(); c!='\n'; c = getchar()){
        number[i++] = c;
    }
    number[i] = '\0';
    return atoi(number);
}

void processInput(int *N, int *M){  /*Determines the ammount of students and friendships that will exist (in the context of the problem), and saves them.*/
    char c, number[MAX_INPUT_SIZE];
    int i = 0;
    for(c = getchar(); c != ','; c = getchar()){
        number[i++] = c;
    }
    number[i] = '\0';
    *N = atoi(number);
    *M = readNumber();
    if ( (*N <= 1) || (*M <= 0) ){  /*As requested, the numbers of students and friendships must respect specific boundaries. If not the program ends it's execution.*/
        free(N);
        free(M);
        exit(0);
    }
    return;
}

void processGrades(vertex *graph, int* N){  /*Initiates every vertex struct that was previously allocated, and attributes a read "grade" to each one.*/
    int i;
    for(i = 0; i < *N; i++){
        (graph+i)->number = i;
        (graph+i)->scc = NULL;
        (graph+i)->grade = readNumber();
        (graph+i)->d = NOT_FOUND;
        (graph+i)->next = NULL;
    }
    return;
}

void processFriendships(elink* edges, int M){   /*Adds an "edge" struct containing the "end-vertex" number to the adjacency list of the "beggining-vertex".*/ 
    int p1, p2, i;
    elink e;
    for(i = 0; i < M; i++){
        p1 = readP1()-1;
        p2 = readNumber()-1;
        e = (elink)can_fail_malloc(sizeof(edge));
        e->to = p2;
        e->next = NULL;
        add_edge(edges, e, p1);
    }
    return;
}
/*--------------------------------------------------------------------*/
/*-----------------------TARJAN'S-ALGORITHM---------------------------*/
int min(int a, int b){ /*Returns the minimum value between both arguments passed.*/
    if (a < b){
        return a;
    }
    return b;
}

int max(int a, int b){ /*Returns the maximum value between both arguments passed.*/
    if (a > b){
        return a;
    }
    return b;
}

void tarjan_visit(vertex *u, int *visited, link *L, elink *edges, int N, vertex *graph, sccomp **sccs){ /*Application of "Tarjan's Algorithm".*/
    int i;
    vertex *v;
    sccomp *n_scc;
    elink e;
    
    u->d = *visited;
    u->low = *visited;
    *visited = (*visited)+1;
    push(L, u->number);
    e = *(edges+(u->number));   /*"e" points to the first edge of "vertex u's" adjacency list.*/
    
    while (e != NULL){ /*We will visit every adjacent vertex that has not been visited, to the "vertex u".*/
        v = graph+(e->to);
        if ( v->d == NOT_FOUND ){ /*If the vertex in question hasn't been visited*/
            tarjan_visit(v, visited, L, edges, N, graph, sccs);
            u->low = min(v->low, u->low);
        }
        else if (is_element(*L, v->number)){    /*If the vertex has already been visited, and it's (student number is) still within the L stack.*/
            u->low = min(u->low, v->d);
        }   /*Otherwise the vertex in question is ignored.*/
        e = e->next;
    }
    if ( (u->low)==(u->d) ){    /*Corresponds to the identification of the "head"/"root" of the SCC.*/
        n_scc = (sccomp*)can_fail_malloc(sizeof(sccomp));
        n_scc->next = *sccs;
        n_scc->v = NULL;
        
        i = (graph+( (*L)->number))->grade; /*The i variable will initially assume the value of the grade of the first student within the L stack; through the "while" cycle, this variable will keep the highest grade found within the SCC.*/
        while ( ((*L)->number) != (u->number) ){
            (graph+((*L)->number))->next = n_scc->v;
            n_scc->v = (graph+((*L)->number));
            (graph+((*L)->number))->scc = n_scc;
            i = max(i, (graph+((*L)->number))->grade);  /*i will be replaced, in case the new grade is higher.*/
            pop(L);
        }
        (graph+((*L)->number))->next = n_scc->v;
        n_scc->v = (graph+((*L)->number));
        (graph+((*L)->number))->scc = n_scc;
        i = max(i, (graph+((*L)->number))->grade);
        pop(L);
        n_scc->max_grade = i;
        n_scc->colour = WHITE;  /*We initiate the SCC's colour as "white", this will prove essential when applying the "scc_maxout" function.*/
        *sccs = n_scc;
    }
    return;
}

void scc_tarjan(vertex *graph, int N, elink *edges, sccomp **sccs){ /*Application of "Tarjan's Algorithm".*/
    link* L;
    int i, *visited;
    visited = (int*)can_fail_malloc(sizeof(int));
    *visited = 0;
    L = (link*)can_fail_malloc(sizeof(link));
    for(i = 0; i < N; i++){
        if( (graph+i)->d == NOT_FOUND ){
            tarjan_visit(graph+i, visited, L, edges, N, graph, sccs);
        }
    }
    free_list(L);
    free(visited);
    return;
}

/*---------------------------------------------------------------------------------*/
/*----------------------------------SCC-MAXOUT-------------------------------------*/

/*The following functions visit every "adjcent SCC" of a specific SCC, attributing the maximum value found to the initial SCC. If the adjacent SCC hasn't been visited (has the colour WHITE), then we shall "visit" it, and repeat the process, until:
 * -> The SCC has no adjacent SCC's to visit, by which we know that it already has the maximum grade, and it's colour becomes BLACK;
 * -> Or the SCC has no more adjcent SCC's to visit,  and we've visited every single one, having already saved the maximum grade of an adjacent SCC;
 (This function uses the property that a graph of SCC's is acyclic, so we know that eventually one of the previous conditions will be verified).*/
void maxout_visit(elink* edges, sccomp** sccs, sccomp* to_visit, vertex* graph){
    elink e;
    vertex* w;
    to_visit->colour = GREY;
    w = to_visit->v;
    while(w != NULL){
        e = *(edges+(w->number));
        while(e != NULL){
            if( w->scc != (graph+(e->to))->scc ){
                if ( (graph+(e->to))->scc->colour == WHITE ){
                    maxout_visit(edges, sccs, (graph+(e->to))->scc, graph);
                }
                w->scc->max_grade = max( w->scc->max_grade, (graph+(e->to))->scc->max_grade );
            }
            e = e->next;
        }
        w = w->next;
    }
    to_visit->colour = BLACK;
}

void scc_maxout(elink* edges, sccomp** sccs, vertex* graph){
    sccomp* scc_tovisit;
    scc_tovisit = *sccs;
    while(scc_tovisit != NULL){
        if( scc_tovisit->colour == WHITE ){
            maxout_visit(edges, sccs, scc_tovisit, graph);
        }
        scc_tovisit = scc_tovisit->next;
    }
}
/*------------------------------------------------------------------------------*/
/*------------------------------------MAIN--------------------------------------*/
void free_all(vertex* graph, elink* edges, sccomp** sccs, int* M, int* N){  /*Freeing all the allocated memory that is used by the "main" function.*/
    int i;
    elink e, temp;
    sccomp *scc_temp, *scc_free;
    
    scc_free = *sccs;
    while(scc_free != NULL){
        scc_temp = scc_free->next;
        free(scc_free);
        scc_free = scc_temp;
    }
    free(sccs);
    
    for(i = 0;i < (*N);i++){
        e = *(edges+i);
        while(e != NULL){
            temp = e->next;
            free(e);
            e = temp;
        }
        continue;
    }
    free(edges);
    free(graph);
    free(M);
    free(N);
    return;
}

int main(){
    int i, *N, *M; /* N: number of students; M: number of friendships*/
    vertex *v, *graph; /*"graph" will always point to the "first" vertex of the (real) graph, which will facilitate the access to a vertex (through the student number).*/
    elink *edges;
    sccomp **sccs;
    sccs = NULL;
    N = (int*)can_fail_malloc(sizeof(int));
    M = (int*)can_fail_malloc(sizeof(int));
    
    processInput(N, M);
    graph = (vertex*)can_fail_malloc(sizeof(vertex)*(*N));
    processGrades(graph, N);
    edges = (elink*) can_fail_malloc(sizeof(elink)*(*N));    /*Initiation of every adjacency list (one for each of the allocated vertices).*/
    initialize_edges(edges, *N);
    processFriendships(edges, *M);
    
    sccs = (sccomp**)can_fail_malloc(sizeof(sccomp*));
    *sccs = NULL;
    scc_tarjan(graph, *N, edges, sccs);
    scc_maxout(edges,sccs, graph);
    
    for(i=0;i<*N;i++){  /*Prints the value of the maxgrade of an SCC, that is associated with each of the vertices.*/
        v = (graph+i);
        printf("%d\n", v->scc->max_grade);
    }
    free_all(graph, edges, sccs, M, N);
    return 0;
}
