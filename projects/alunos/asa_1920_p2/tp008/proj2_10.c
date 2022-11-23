#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/* Segundo projeto - Analise e Sintese de Algoritmos
 * Antonio Elias: 93690
 * Ruben Inacio:  93755
 * Grupo: tp008
 */

#include <stdio.h>
#include <stdlib.h>

#define MIN(__X, __Y) (__X) < (__Y) ? (__X) : (__Y)
#define MAX(__X, __Y) (__X) > (__Y) ? (__X) : (__Y)
#define DEFAULT -1

#define SOURCE 0
#define SINK (M*N*2+1)


typedef struct edge {
    int origin, destination;
    int capacity;
    int flow;
    struct edge *next;
} edge_t;

typedef struct intersection {
    int id;
    edge_t *roads;
    int visited;
    int pi;
} intersection_t;


int N;          /* Number of streets. */
int M;          /* Number of avenues. */
int S;          /* Supermarket's locations. */
int C;          /* Citizens' locations. */

edge_t** supermarkets;
edge_t** citizens;
edge_t** path;
int path_ptr;

/* Queue */
int *q;
int en_ptr;
int de_ptr;

void enqueue(int value){
    q[en_ptr++] = value;
}

int dequeue(){
    return q[de_ptr++];
}

/* Graph-related and algorithm-related functions */

int getid(int avenue, int street, int in){
    if (in)   
        return ((street-1) * M + avenue);
    return ((street-1) * M + avenue) + N*M;
}

edge_t* create_road(int origin, int destination, intersection_t* city, int capacity){
    edge_t* new_road;
    new_road = (edge_t *) can_fail_malloc(sizeof(edge_t));
    new_road->origin = origin;
    new_road->destination = destination;
    new_road->capacity = capacity;
    new_road->flow = 0;
    new_road->next = city[origin].roads ;
    city[origin].roads = new_road;
    return new_road;
}

edge_t* create_supermarket(int avenue, int street, intersection_t *city){
    create_road(getid(avenue, street, 0), SINK, city, 1);
    return create_road(SINK, getid(avenue, street, 0), city, 0);
}

edge_t* create_citizen(int avenue, int street, intersection_t *city){
    create_road(getid(avenue, street, 1),SOURCE, city, 0);
    return create_road(SOURCE, getid(avenue, street, 1), city, 1);
}

edge_t * find_edge(int origin, int destination, intersection_t* city){
    edge_t * edge;
    if (origin == SOURCE) 
        return citizens[destination];

    else if (origin == SINK)
        return supermarkets[destination];

    for(edge = city[origin].roads; edge; edge = edge -> next)
        if (edge -> destination == destination) 
            return edge;

    return NULL;
}

edge_t * find_inverse(edge_t * edge, intersection_t * city) {
    int u, v;
    u = edge->origin;
    v = edge->destination;
    return find_edge(v, u, city);
}

intersection_t* create_city(int total){
    intersection_t* city = (intersection_t* ) can_fail_malloc((total + 2) * sizeof(intersection_t));
    int i;
    for(i = 0; i < total+2; i++){
        city[i].id = i;
        city[i].roads = NULL;
    }
    for(i = 1; i <= total/2; i++){
        create_road(i, total/2 + i, city, 1);
        create_road(total/2 + i, i, city, 0);
    }
    for(i = total/2 + 1; i <= total; i++){
        if (i % M != 0){ /* Street to the right */
            create_road(i, i - total/2 + 1, city, 1);
            create_road(i - total/2 + 1, i, city, 0);
        }         
        if (i % M != 1 && N != 1){ /* Street to the left */
            create_road(i, i - total/2 - 1, city, 1);
            create_road(i - total/2 - 1, i, city, 0);
        }
        if (i - total/2 - M > 0){ /* Street above */
            create_road(i, i - total/2 - M, city, 1);
            create_road(i - total/2 - M, i, city, 0);
        } 
        if (i - total/2 + M <= total / 2){ /* Street below */
            create_road(i, i - total/2 + M, city, 1);
            create_road(i - total/2 + M, i, city, 0); 
        }
    }
    return city;
}

void destroy_city(intersection_t* city){
    int i;
    edge_t* edge, *aux;
    for(i = 0; i < M*N*2+2; i++){
        for(edge = city[i].roads; edge;){
            aux = edge -> next;
            free(edge);
            edge = aux;
        }
    }
    free(city);
}

edge_t** increase_path(intersection_t* city, edge_t** path){
    int i, v, u;
    edge_t *edge;
    path_ptr = 0;
    en_ptr = 0;
    de_ptr = 0;

    city[SOURCE].visited = 1;
    city[SOURCE].pi = DEFAULT;
    
    for (i = 1; i <= SINK; i++) {
        city[i].visited = 0;
        city[i].pi = DEFAULT;
    }

    enqueue(SOURCE);

    while (de_ptr < en_ptr) {
        u = dequeue();
        for(edge = city[u].roads; edge; edge = edge -> next){
            v = edge->destination;
            if(v == SINK && edge->capacity > edge->flow) {
                while (u >= 0) {
                    path[path_ptr++] = find_edge(u, v, city);
                    v = u;
                    u = city[u].pi;
                }
                path[path_ptr] = find_edge(SOURCE, v, city);
                path[path_ptr + 1] = NULL;
                while (de_ptr < en_ptr)
                    dequeue();
                return path;
            }
            if(city[v].visited == 0 && edge->capacity > edge->flow) {
                city[v].visited = 1;
                city[v].pi = u;
                enqueue(v);
            }
        }
    }
    return NULL;
}

int edmonds_karp(intersection_t * city){
    edge_t** path, *pathinv;
    int i;
    int flow = 0;
    q =  can_fail_malloc(sizeof(int) * (2*M*N+1));
    for(i = 0; i < 2*M*N+1; i++)
        q[i] = DEFAULT;

    path = can_fail_malloc(sizeof(edge_t*) * (2 * N * M +1));
    while ((path = increase_path(city, path))) {
        for (i = 0; path[i]; i++) {
            path[i] -> flow++;
            if ((pathinv = find_inverse(path[i], city)))
                pathinv -> flow = - path[i] -> flow;
        }
        flow++;
    }
    free(path);
    free(q);
    return flow;
}

int main(){
    int i, total, id;
    int avenue, street;

    intersection_t* city;
    scanf("%d %d", &M, &N);
    scanf("%d %d", &S, &C);
    total = 2 * M * N;
    city = create_city(total);

    supermarkets =  can_fail_malloc(sizeof(edge_t*) * (total + 1));
    citizens = can_fail_malloc(sizeof(edge_t*) * (total + 1));
    for (i = 0; i < total; i++) {
        supermarkets[i] = NULL;
        citizens[i] = NULL;
    }

    for (i = 0; i < S ; i++){
        scanf("%d %d", &avenue, &street);
        id = getid(avenue, street, 1);
        if (!supermarkets[id])
            supermarkets[id] = create_supermarket(avenue, street, city);
    }
    for (i = 0; i < C ; i++){
        scanf("%d %d", &avenue, &street);
        id = getid(avenue, street, 1);
        if (!citizens[id]) 
            citizens[id] = create_citizen(avenue, street, city);
    }
    printf("%d\n", edmonds_karp(city));
    free(supermarkets);
    free(citizens);
    destroy_city(city);
    return 0;
}