#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int n;
    struct node *next;
}node;


typedef struct processo {
    int n;
    int parent;
    int path_capacity;
    int color;
    int *edges;
}processo;


int N, M;
processo *graph;

void initGraph(){
    graph=can_fail_malloc(sizeof(processo)*(N+2));
    int i, e;
    for (i=0; i<N+2; i++){
        graph[i].n=i;
        graph[i].color=0;
        graph[i].path_capacity=0;
        graph[i].edges=can_fail_malloc(sizeof(int)*(N+2));
        for(e=0; e<N+2;e++){
            graph[i].edges[e]=0;
        }
    }
}


void readInput(){
    scanf("%d %d", &N, &M);
    int x, y, z;
    initGraph();
    int i;
    for (i=0; i<N; i++){
        scanf("%d %d", &x, &y);
        graph[0].edges[i+2]=x;
        graph[i+2].edges[1]=y;

    }
    for(i=0; i<M; i++){
        scanf("%d %d %d", &x, &y, &z);
        graph[x+1].edges[y+1]=z;
        graph[y+1].edges[x+1]=z;
    }
}

int bfs(int i){
    node *new= can_fail_malloc(sizeof(node));
    new->n=0;
    new->next=NULL;
    graph[0].color=i;
    node *head=new;
    node *last=new;
    int e;
    while(head!=NULL){
        for (e=0; e<N+2; e++){
            if(graph[e].color!=i && graph[head->n].edges[e]!=0){
                new= can_fail_malloc(sizeof(node));
                new->n=e;
                last->next=new;
                last=new;
                graph[e].parent=head->n;
                graph[e].color=i;
                if(head->n==0){
                    graph[e].path_capacity=graph[head->n].edges[e];
                }
                else if(graph[head->n].path_capacity > graph[head->n].edges[e]){
                    graph[e].path_capacity=graph[head->n].edges[e];
                }
                else{
                    graph[e].path_capacity=graph[head->n].path_capacity;
                }
                if(e==1){
                    while(head!=NULL){
                        node *removed=head;
                        head=head->next;
                        free(removed);
                    }
                    return 1;
                }
            }
        }
        node *removed=head;
        head=head->next;
        free(removed);
    }
    return 0;
}

int edmonds_karp(){
    int custo=0;
    int i=1, e=1;
    while(bfs(e)){
        int path_capacity=graph[i].path_capacity;
        while(i!=0){
            graph[graph[i].parent].edges[i]-=path_capacity;
            graph[i].edges[graph[i].parent]-=path_capacity;
            i=graph[i].parent;
        }
        i=1;
        custo+=path_capacity;
        e++;
    }
    return custo;
}

void freeGraph(){
    int i;
    for (i=0; i<N+2; i++){
        free(graph[i].edges);
    }
    free(graph);
}

int main(){
    readInput();
    int custo=edmonds_karp();
    printf("%d\n", custo);
    freeGraph();
    return 0;
}
