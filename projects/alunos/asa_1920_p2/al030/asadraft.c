#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/*  2o projecto de ASA 2019/2020
    Miguel Pereira n.92530
    Tomas Sequeira n.92565
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define INFINITO 1000
#define CAPACITY 1


int avenues = 0, streets = 0, nodes = 0;
int maxnodes = 0;

int num_citizens = 0, num_markets = 0;

typedef struct intersectionLink{
    int pos;
    int flow;
    struct intersectionLink* next;
}*link;

typedef struct intersection {
    link connections;
}Intersection;


int *citizens;

int *markets;

int *pred;

int *q;

int *color;

int head = 0, end = 0;

Intersection *intersections;

int min(int v1, int v2) {
    if (v1 < v2) return v1;
    else         return v2;
}

int calcPos(int st, int av) {
    return  st * avenues + av;
}

int repeated(int* list, int len, int v) {
    int i = 0;
    for(i = 0; i < len && list[i] != -1; i++)
        if(list[i] == v) return 1;
    return 0;
}

int getFlow(int s, int t) {
    link aux;
    for(aux = intersections[s].connections; aux != NULL; aux = aux->next) {
        if (aux->pos == t) return aux->flow;
    }
    return 0;
}

void setFlow(int s, int t, int flow) {
    link aux;
    for(aux = intersections[s].connections; aux != NULL; aux = aux->next) {
        if (aux->pos == t) aux->flow -= flow;
    }
    for(aux = intersections[t].connections; aux != NULL; aux = aux->next) {
        if (aux->pos == s) aux->flow += flow;
    }
}

link newLink(int pos, int flow){
    link l = (link)can_fail_malloc(sizeof(struct intersectionLink));
    l->pos = pos;
    l->flow = flow;
    l->next = NULL;
    return l;
}

void insertLink(int v1, int v2, int flow){
    link l = newLink(v2, flow);
    if(intersections[v1].connections == NULL) {
        intersections[v1].connections = l;
    }
    else {
        l->next = intersections[v1].connections;
        intersections[v1].connections = l;
    }
}


void queue(int x) {
    q[end] = x;
    end++;
    color[x] = GRAY;
}

int outqueue() {
    int x = q[head];
    head++;
    color[x] = BLACK;
    return x;
}


int bfs(int source, int sink){
    int i = 0, j = 0, flow = 0;
    link aux;

    memset(color, 0, maxnodes*sizeof(int));
    head = end = 0;
    queue(source);
    pred[source] = -1;
    while(head!=end){
        i = outqueue();
        for(aux = intersections[i].connections; aux != NULL; aux = aux->next){
            j = aux->pos;
            flow = aux->flow;
            if(color[j] == WHITE && flow > 0){
                queue(j);
                pred[j] = i;
                if(j == sink) return 1;
            }
        }
    }
    return color[sink] == BLACK;
}

int fordFulkerson(int source, int sink){
    int maxFlow = 0;
    int flow;
    int i;
    while(bfs(source,sink)){
        flow = CAPACITY;
        for(i = sink; pred[i] >= 0; i = pred[i]){
            flow = min(flow, getFlow(pred[i], i));
        }
        for(i = sink; pred[i] >= 0; i = pred[i]){
            setFlow(pred[i], i, flow);
        }

        maxFlow += flow;
        if (maxFlow == num_citizens) break;
    }

    return maxFlow;

}

void calcLinks(){
    int i = 0, j = 0, k = 0;
    for(i=0; i < 2*streets; i++){
        for(j=0; j < avenues; j++){
            if (i >= streets) {
                k = i - streets;
                if((k-1) >= 0) {            insertLink(calcPos(i,j), calcPos(k-1,j), 1);
                                            insertLink(calcPos(k-1,j), calcPos(i,j), 0);}
                if((k+1) <= (streets-1)) {  insertLink(calcPos(i,j), calcPos(k+1,j), 1);
                                            insertLink(calcPos(k+1,j), calcPos(i,j), 0);}
                if((j+1) <= (avenues-1)) {  insertLink(calcPos(i,j), calcPos(k,j+1), 1);
                                            insertLink(calcPos(k,j+1), calcPos(i,j), 0);}
                if((j-1) >= 0) {            insertLink(calcPos(i,j), calcPos(k,j-1), 1);
                                            insertLink(calcPos(k,j-1), calcPos(i,j), 0);}
            }
            else {
                insertLink(calcPos(i,j), calcPos(i+streets,j), 1);
                insertLink(calcPos(i+streets,j), calcPos(i,j), 0);
            }
        }
    }
}



void createSuper(){
    int i = 0;

    intersections[nodes].connections = NULL;
    intersections[nodes+1].connections = NULL;

    for(i=0; i < num_citizens; i++){
        insertLink(nodes, citizens[i], 1);
        insertLink(citizens[i], nodes, 0);
    }
    for(i=0; i < num_markets; i++){
        insertLink(markets[i], nodes+1, 1);
        insertLink(nodes+1, markets[i], 0);
    }
}

void freeLinks(link head) {
    link item = head;
    link aux = NULL;
    while (item != NULL) {
        aux = item;
        item = item->next;
        free(aux);
    }
}

void freeIntersections(){
    int i;
    for(i = 0; i < maxnodes; i++){
        freeLinks(intersections[i].connections);
    }
    free(intersections);
}


int main() {
    int i = 0, j = 0;
    int av = 0, st = 0;
    int pos = 0;

    scanf("%d %d", &avenues, &streets);
    nodes = 2 * streets * avenues;
    maxnodes = nodes + 2;
    
    intersections = (Intersection*)can_fail_malloc(maxnodes*sizeof(Intersection));
    for(i = 0; i < 2*streets; i++){
        for(j = 0; j < avenues; j++){
                intersections[calcPos(i,j)].connections = NULL;
        }
    }


    pred = (int*)can_fail_malloc(maxnodes*sizeof(int));


    q = (int*)can_fail_malloc(maxnodes*sizeof(int));


    color = (int*)can_fail_malloc(maxnodes*sizeof(int));


    scanf("%d %d", &num_markets, &num_citizens);

    markets = (int*)can_fail_malloc(sizeof(int)*num_markets);
    citizens = (int*)can_fail_malloc(sizeof(int)*num_citizens);
    memset(markets, -1, sizeof(int)*num_markets);
    memset(citizens, -1, sizeof(int)*num_citizens);

    for (i = 0, j = 0; i < num_markets; i++) {
        scanf("%d %d", &av, &st);

        pos = calcPos(st-1 + streets, av-1);

        if(!repeated(markets, num_markets, pos)) {
            markets[j] = pos; 
            j++;
        }
    }
    num_markets = j;

    for (i = 0, j = 0; i < num_citizens; i++) {
        scanf("%d %d", &av, &st);

        pos = calcPos(st-1, av-1);

        if(!repeated(citizens, num_citizens, pos)) {
            citizens[j] = pos; 
            j++;
        }
    }
    num_citizens = j;

    calcLinks();

    createSuper();

    printf("%d\n", fordFulkerson(nodes, nodes+1));

    freeIntersections();
    free(markets);
    free(citizens);
    free(q);
    free(color);
    free(pred);

    return 0;
}