#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/*  ASA Project 1 - Dominos
    Pedro Lynce Silva ist195656
    Due date - 19 de Abril 2021 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <sys/time.h>

#define SOURCE 1
#define VISITED 1
#define CLOSED 1

/* ############################################################### */

/* Structures */

typedef struct {
    int * values;
    int last;
} TopologicArray;

typedef struct link {
    int value;
    struct link * link;
} Link;

typedef struct domino{
    int value;
    int num_links;
    int source;
    int visited;
    int closed;
    int start_t;
    int end_t;
    long int low;
    Link * cursor;
    struct domino * father; 
    Link * links;
} Domino;

typedef struct {
    Link * head;
} Stack;

typedef struct {
    int V;
    int E;
    long int sources;
    Domino * domino;
} Grafo;

/* ############################################################### */

/* Global Operation */

/* Adapts the index */
int ind(int i){
    return i-1;
}

/* ############################################################### */

/* Topologic Array Operations */

int * getTAValues(TopologicArray * array){
    return array->values;
}
void setTAValues(TopologicArray * array, int * values){
    array->values = values;
}

int getTALast(TopologicArray * array){
    return array->last;
}
void setTALast(TopologicArray * array, int last){
    array->last = last;
}

void decTALast(TopologicArray * array){
    array->last--;
}
void incTALast(TopologicArray * array){
    array->last++;
}

int getTAValue(TopologicArray * array, int index){
    return array->values[index];
}
void setTAValue(TopologicArray * array, int value, int index){
    array->values[index] = value;
}

TopologicArray * topologic_sort_init(int V){
    TopologicArray * array = (TopologicArray*)can_fail_malloc(sizeof(TopologicArray));
    setTAValues(array, (int*)can_fail_malloc(sizeof(int) * V));
    setTALast(array, ind(V));
    return array;
}

void topologic_insert(TopologicArray * array, int value){
    setTAValue(array, value, getTALast(array));
    decTALast(array);
}

void topologic_destroy(TopologicArray * array){
    free(array->values);
    free(array);    
}

/* ############################################################### */

/* Link Operations */

int getLinkValue(Link * link){
    return link->value;
}
void setLinkValue(Link * link, int value){
    link->value = value;
}

Link * getLinkNext(Link * link){
    return link->link;
}
void setLinkNext(Link * link, Link * next){
    link->link = next;
}

Link * new_link(){
    return (Link*)can_fail_malloc(sizeof(Link));
}

void destroy_links(Link * head){
    if (head == NULL)
        return;
    
    Link * next = getLinkNext(head);
    
    while (next != NULL){
        free(head);
        head = next;
        next = getLinkNext(head);
    }

    free(head);
}

/* ############################################################### */

/* Domino Operations */

int getDominoValue(Domino * domino){
    return domino->value;
}
void setDominoValue(Domino * domino, int value){
    domino->value = value;
}

int getDominoNumLinks(Domino * domino){
    return domino->num_links;
}
void setDominoNumLinks(Domino * domino, int num){
    domino->num_links = num;
}

int getDominoSource(Domino * domino){
    return domino->source;
}
void setDominoSource(Domino * domino, int n){
    domino->source = n;
}

int getDominoVisited(Domino * domino){
    return domino->visited;
}
void setDominoVisited(Domino * domino, int n){
	domino->visited = n;
}

int getDominoClosed(Domino * domino){
    return domino->closed;
}
void setDominoClosed(Domino * domino, int n){
	domino->closed = n;
}

int getDominoStartTime(Domino * domino){
    return domino->start_t;
}
void setDominoStartTime(Domino * domino, int time){
    domino->start_t = time;
}

int getDominoEndTime(Domino * domino){
    return domino->end_t;
}
void setDominoEndTime(Domino * domino, int time){
    domino->end_t = time;
}

long int getDominoLow(Domino * domino){
    return domino->low;
}
void setDominoLow(Domino * domino, long int low){
    domino->low = low;
}

Link * getDominoCursor(Domino * domino){
    return domino->cursor;
}
void setDominoCursor(Domino * domino, Link * new_cursor){
    domino->cursor = new_cursor;
}

Domino * getDominoFather(Domino * domino){
    return domino->father;
}
void setDominoFather(Domino * domino, Domino * father){
    domino->father = father;
}

Link * getDominoLinks(Domino * domino){
    return domino->links;
}
void setDominoLinks(Domino * domino, Link * links){
    domino->links = links;
}

void incDominoNumLinks(Domino * domino){
    domino->num_links++;
}

void close(Domino * domino, TopologicArray * array, int * time){
    topologic_insert(array, getDominoValue(domino));
    setDominoClosed(domino, CLOSED);
    setDominoEndTime(domino, *time);
    (*time)++;
}

void visit(Domino * domino, int * time){
    setDominoVisited(domino, VISITED);
    setDominoStartTime(domino, *time); 
    (*time)++; 
}

int dominoSink(Domino * domino){
    return getDominoNumLinks(domino) == 0;
}

/* ############################################################### */

/* Stack Operations */

Link * getStackHead(Stack * stack){
    return stack->head;
}
void setStackHead(Stack * stack, Link * head){
    stack->head = head;
}

int getStackFirst(Stack * stack){
    return stack->head->value;
}

Stack * stack_init(){
    Stack * stack = (Stack*)can_fail_malloc(sizeof(Stack));
    setStackHead(stack, NULL);
    return stack;
}

int emptyStack(Stack * stack){
    return getStackHead(stack) == NULL;
}

void popStack(Stack * stack){
    Link * temp = stack->head;
    stack->head = stack->head->link;
    free(temp);
}

void stack_destroy(Stack * stack){
    free(stack);
}

void stack_insert(Stack * stack ,int value){
    Link * new = new_link();
    
    setLinkValue(new, value);
    if (emptyStack(stack))
        setLinkNext(new, NULL);
    else 
        setLinkNext(new, getStackHead(stack));

    setStackHead(stack, new);
}

/* ############################################################### */

/* Grafo Operations */

int getGrafoV(Grafo * grafo){
    return grafo->V;
}
void setGrafoV(Grafo * grafo, int V){
    grafo->V = V;
}

int getGrafoE(Grafo * grafo){
    return grafo->E;
}
void setGrafoE(Grafo * grafo, int E){
    grafo->E = E;
}

long int getGrafoSources(Grafo * grafo){
    return grafo->sources;
}
void setGrafoSources(Grafo * grafo, int sources){
    grafo->sources = sources;
}

Domino * getGrafoDomino(Grafo * grafo){
    return grafo->domino;
}
void setGrafoDomino(Grafo * grafo, Domino * domino){
    grafo->domino = domino;
}

Domino * get_domino(Grafo * grafo, int index){
    return &grafo->domino[index];
}

void decrementSources(Grafo * grafo){
    grafo->sources--;
}

Grafo * new_grafo(int V, int E){
    int i = 0;

    Grafo * grafo = (Grafo*)can_fail_malloc(sizeof(Grafo));

    setGrafoV(grafo, V);
    setGrafoE(grafo, E);
    setGrafoSources(grafo, V);

    setGrafoDomino(grafo, (Domino*)can_fail_malloc(sizeof(Domino) * V));

    for (; i < V; i++){
        setDominoFather(get_domino(grafo, i), NULL);
        setDominoLinks(get_domino(grafo, i), NULL);
        setDominoNumLinks(get_domino(grafo, i), 0);
        setDominoSource(get_domino(grafo, i), SOURCE);
        setDominoVisited(get_domino(grafo, i), !VISITED);
        setDominoClosed(get_domino(grafo, i), !CLOSED);

        setDominoValue(get_domino(grafo, i), i+1);
    }

    return grafo;
}

void destroy_grafo(Grafo * grafo){
    int i = 0;
    for (; i < grafo->V; i++)
        destroy_links(getDominoLinks(get_domino(grafo, i)));

    free(getGrafoDomino(grafo));
    free(grafo);
}

void add_domino(Grafo * grafo, int V, int E){
    Link * new = new_link();
    
    setLinkValue(new, E);

    setLinkNext(new, getDominoLinks(get_domino(grafo, ind(V))));
    setDominoLinks(get_domino(grafo, ind(V)), new);
    setDominoCursor(get_domino(grafo, ind(V)), new);

    if (getDominoSource(get_domino(grafo, ind(E)))){
        decrementSources(grafo);
        setDominoSource(get_domino(grafo, ind(E)), !SOURCE);
    }

    incDominoNumLinks(get_domino(grafo, ind(V)));
}

Domino * get_child(Grafo * grafo, Domino * domino){
    Link * result = getDominoCursor(domino);
    setDominoCursor(domino, getLinkNext(result));
    return get_domino(grafo, ind(getLinkValue(result)));
}

/* ############################################################### */

/* MAIN FUNCTIONS */

long int w(){
    return 1;
}

void iterate(Grafo * grafo, Stack * stack, Domino * root, TopologicArray * array, int * time){
    int i;
    Domino * current;
    Domino * child;
    stack_insert(stack, getDominoValue(root));
    while (!emptyStack(stack)){
        current = get_domino(grafo, ind(getStackFirst(stack)));
        if (getDominoVisited(current) && !getDominoClosed(current)){
            close(current, array, time);
            popStack(stack);
        }
        else if (getDominoVisited(current) && getDominoClosed(current))
            popStack(stack);
        else {
            visit(current, time);
            for (i = 0; i < getDominoNumLinks(current); i++){
                child = get_child(grafo, current);
                if (!getDominoVisited(child))
                    stack_insert(stack, getDominoValue(child));
            }
        }
    }
    
}

TopologicArray * DFS(Grafo * grafo){
    TopologicArray * array = topologic_sort_init(getGrafoV(grafo));
    Stack * stack = stack_init();
    int i = 0, sources = 0;
    int * time = (int*)can_fail_malloc(sizeof(int));
    *time = 1;

    for (; i < getGrafoV(grafo); i++){
        if (getDominoSource(get_domino(grafo, i))){
            iterate(grafo, stack, get_domino(grafo, i), array, time);
            sources++;
            if (sources == getGrafoSources(grafo))
                break;
        }
    }
    stack_destroy(stack);
    free(time);
    
    return array;
}

int extractMin(TopologicArray * array){
    int min;

    incTALast(array);
    min = getTAValue(array, getTALast(array));
    return min;
}

void InitializeSingleSource(Grafo * grafo, int source){
    int i = 0;
    for (; i < getGrafoV(grafo); i++){
        if (i == ind(source))
            setDominoLow(get_domino(grafo, ind(source)), 0);
        else
            setDominoLow(get_domino(grafo, i), 0);

        setDominoFather(get_domino(grafo, i), NULL);
    }
}

void Relax(Grafo * grafo, Domino * u, Domino * v){
    if (getDominoLow(v) < getDominoLow(u) + w()){
        setDominoLow(v, getDominoLow(u) + w());
        setDominoFather(v, u);
    }
}

void DAGLongestPaths(Grafo * grafo, int source, TopologicArray * priority_queue, long int * best_path){
    int i, min, j;
    Link * next;
    
    InitializeSingleSource(grafo, source);  

    for (j = 0; j < getGrafoV(grafo); j++){
        min = extractMin(priority_queue);
        if (dominoSink(get_domino(grafo, ind(min))) && *best_path < getDominoLow(get_domino(grafo, ind(min)))){
            *best_path = getDominoLow(get_domino(grafo, ind(min)));
        }
        else {
            next = getDominoLinks(get_domino(grafo, ind(min)));
            for (i = 0; i < getDominoNumLinks(get_domino(grafo, ind(min))); i++){
                Relax(grafo, get_domino(grafo, ind(min)), get_domino(grafo, ind(getLinkValue(next))));
                next = getLinkNext(next);
            }
        }    
    }
    setTALast(priority_queue, -1);
}

long int longest_path(Grafo * DAG){
    TopologicArray * priority_queue = DFS(DAG);
    int i = 0;
    long int res;
    long int * best_path = (long int*)can_fail_malloc(sizeof(long int));

    *best_path = 0;
    for (; i < getGrafoV(DAG); i++){
        if (getDominoSource(get_domino(DAG, i))  && getDominoNumLinks(get_domino(DAG, i)) > 0)
            DAGLongestPaths(DAG, getDominoValue(get_domino(DAG, i)), priority_queue, best_path);
    }
    topologic_destroy(priority_queue);

    res = (*best_path) + 1;

    free(best_path);

    return res;
}

/* ############################################################### */

/* MAIN */

int main(){
    int V, E, dom, link, i = 0;
    
    if (scanf("%d %d", &V, &E) < 0)
        perror("Error reading input\n");

    Grafo * domino = new_grafo(V, E);
    
    for (; i < E; i++){
        if (scanf("%d %d", &dom, &link) < 0)
            perror("Error reading input\n");
        add_domino(domino, dom, link);
    }

    printf("%ld %ld\n", getGrafoSources(domino), longest_path(domino));    

    destroy_grafo(domino);
    
    return 0;
}
