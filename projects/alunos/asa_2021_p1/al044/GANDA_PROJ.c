#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h> 
#include <stdlib.h>
#include <assert.h>

typedef struct{
    int v,w;
}Edge;

typedef struct vertice {
    int value;
    int d;
    int inc_edges;
    int inc_edges1;
}*Vertice;

typedef struct node * link;
typedef struct q_node * q_link;

struct node{
    Vertice v;
    link next;
};

struct q_node{
    int value;
    q_link next;
    
};

typedef struct graph {
    int V;
    link *adj;
}*Graph;

typedef struct queue {
    q_link head;
    q_link tail;
}*Queue;

q_link NewLink(int value, q_link next){
    q_link x = can_fail_malloc(sizeof(struct q_node));
    x->value = value;
    x->next = next;
    return x;
}

Queue Q_init(){
    Queue q = can_fail_malloc(sizeof(struct queue));
    q->head = NULL;
    q->tail = NULL;
    return q;
}

void Q_destroy(Queue q){
    free(q);
}

int Q_empty(Queue q){
    return q->head == NULL;
}

void Q_put(Queue q,int value){
    if (q->head == NULL){
        q->head = (q->tail = NewLink(value, q->head));
        return;
    }
    q->tail->next = NewLink(value, q->tail->next);
    q->tail = q->tail->next;
}

int Q_get(Queue q){
    int value = q->head->value;
    q_link t = q->head->next;
    free(q->head);
    q->head = t;
    return value;
}


Graph GraphInit(int V){
    int i;
    Graph G = can_fail_malloc(sizeof(struct graph));
    G->V = V; 
    G->adj = can_fail_malloc(V * sizeof(link));
    for (i=0; i<V ; i++){
        G->adj[i]= can_fail_malloc(sizeof(struct node));
        link x = G->adj[i];
        x->v = can_fail_malloc(sizeof(struct vertice));
        x->v->value = i+1;
        x->v->d = -1;
        x->v->inc_edges=0;
        x->v->inc_edges1=0;
        x->next = NULL;
    }
    return G;
}

void AddEdge(Vertice vertice ,link previous){
    link x = can_fail_malloc (sizeof(struct node));
    x->v = vertice;
    x->next = previous->next;
    previous->next = x;
}

void GraphInsert(Graph G, Edge e){
    int v = e.v, w=e.w;
    AddEdge(G->adj[w-1]->v, G->adj[v-1]);
    G->adj[w-1]->v->inc_edges++;
    G->adj[w-1]->v->inc_edges1++;
}

void GraphDestroy(Graph G){
    int i;
    link j,aux;
    for (i=0; i<G->V ;i++){
        for (j=G->adj[i]->next; j != NULL; ){
            aux=j->next;
            free(j);
            j=aux;
            if(aux!=NULL){
                aux=aux->next;
            }
        }
        free(G->adj[i]->v);
        free(G->adj[i]);
    }
    
    free(G->adj);
    free(G);
}


int BFS(Graph G, Vertice v){
    int d_max=0,value;
    link j;
    /*q_link aux;*/
    v->d=0;
    Queue Q = Q_init();
    Q_put(Q,v->value);

    while (!Q_empty(Q)){
        value = Q_get(Q);
        for (j=G->adj[value-1]->next ; j!=NULL ; j=j->next){
            j->v->inc_edges1--;

            if(j->v->inc_edges1 == 0){
                Q_put(Q,j->v->value);
            }
            if(j->v->d < G->adj[value-1]->v->d+1){
                j->v->d=G->adj[value-1]->v->d+1;
                if(j->v->d > d_max){
                    d_max = j->v->d;
                }
            }
        }
        /*printf("queue value:\n");
        for(aux=Q->head; aux !=NULL;aux=aux->next){
            printf("value:%d\n",aux->value);
        }*/
    }
    Q_destroy(Q);
    return d_max+1;
}

void DoBFS(Graph G, int * results){
    int aux,i;
    for(i=0; i<G->V ;i++){
        if(G->adj[i]->v->inc_edges == 0){
            results[0]++;
            aux = BFS(G, G->adj[i]->v);
            
            if(aux >results[1]){
                results[1]=aux;
            }   
        }
    }
}



int main(){
    int V,E,i;
    /*link j;*/
    scanf("%d %d", &V, &E);
    assert(V >= 2 && E >= 0);
    Graph G=GraphInit(V);
    Edge e;
    int * results = can_fail_malloc(2*sizeof(int));
    results[0]=0;
    results[1]=0;

    for (i=0; i<E ; i++){
        scanf("%d %d",&e.v, &e.w);
        GraphInsert(G,e);
    }
    
    DoBFS(G,results);
    /*for (i=0; i<G->V ; i++){
        j=G->adj[i];
        printf("i:%d distance:%d\n",i+1, j->v->d);
    }*/
    printf("%d %d\n",results[0], results[1]);
    GraphDestroy(G);
    free(results);
    return 0;
}