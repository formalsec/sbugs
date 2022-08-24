#include<stdio.h>
#include<stdlib.h>

typedef struct adj_domino{
    int n;
    struct adj_domino *next;
}adj_domino;

typedef struct node{
    int n;
    struct node *next, *previous;
}node;

typedef struct domino {
    int n;
    int source;
    int color;
    int fallen;
    struct adj_domino *next, *last_adj;
}domino;


int N, M;
domino *graph;

void initGraph(){
    graph=malloc(sizeof(domino)*N);
    int i;
    for (i=0; i<N; i++){
        graph[i].n=i;
        graph[i].source=1;
        graph[i].color=0;
        graph[i].fallen=0;
        graph[i].next=NULL;
        graph[i].last_adj=NULL;
    }
}

void insert_end(int x, int y){
    adj_domino *new=malloc(sizeof(adj_domino));
    new->n=y-1;
    new->next=NULL;
    if(graph[x-1].last_adj==NULL){
        graph[x-1].next=new;
        graph[x-1].last_adj=new;
        return ;
    }
    adj_domino *last=graph[x-1].last_adj;
    last->next=new;
    graph[x-1].last_adj=new;
}

int readInput(){
    scanf("%d %d", &N, &M);
    int nsources=N;
    int x, y;
    initGraph();
    int i;
    for(i=0; i<M; i++){
        scanf("%d %d", &x, &y);
        if(graph[y-1].source){
            graph[y-1].source=0;
            nsources--;
        }
        insert_end(x,y);
    }
    return nsources;
}

int dfsVisit(int i){
    graph[i].color=1;
    int fallen;
    node *head=malloc(sizeof(node));
    head->n=graph[i].n;
    head->next=NULL;
    head->previous=NULL;
    while(head!=NULL){
        fallen=1;
        adj_domino *adj=graph[head->n].next;
        while(adj!=NULL){
            if(graph[adj->n].color==2){
                if(fallen<graph[adj->n].fallen+1){
                    fallen=graph[adj->n].fallen+1;
                }
            }
            else if(graph[adj->n].color==0){
                graph[adj->n].color=1;
                node *new_node=malloc(sizeof(node));
                new_node->n=adj->n;
                new_node->next=NULL;
                new_node->previous=head;
                head->next=new_node;
                head=new_node;
                break;
            }
            adj=adj->next;
        }
        if(adj==NULL){
            graph[head->n].color=2;
            graph[head->n].fallen=fallen;
            if(head->previous==NULL){
                free(head);
                return fallen;
            }
            node *removed=head;
            head=head->previous;
            head->next=NULL;
            removed->previous=NULL;
            free(removed);
        }
    }
    return fallen;
}

int dfs(){
    int fallen=1, new;
    int i;
    for (i=0; i<N; i++){
        if(graph[i].color==0){
            new=dfsVisit(i);
            if(fallen<new){
                fallen=new;
            }
        }
    }
    return fallen;
}

void freeGraph(){
    int i;
    adj_domino *head, *removed;
    for (i=0; i<N; i++){
        head=graph[i].next;
        while(head!=NULL){
            removed=head;
            head=head->next;
            free(removed);
        }
    }
    free(graph);
}

int main(){
    int k=readInput();
    int l=dfs();
    printf("%d %d\n", k, l);
    freeGraph();
    return 0;
}