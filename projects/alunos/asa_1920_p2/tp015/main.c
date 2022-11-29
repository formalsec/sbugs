#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    int id;
    int flag_super;
    int flag_person;
    int source;
    int sink;
    struct Node **adjs;
    int numberAdj;
    int *cap;
}node;

typedef struct List{
    struct Node *current;
    struct List *next;
    struct List *previous;
}list;

node **nodes = NULL;
list *queue = NULL;
int *color,*pi;
node *source=NULL,*sink=NULL;
int M, N,s,c;

void addList(node* nodeAdd){
    if (queue==NULL){
        queue = can_fail_malloc(sizeof(list));
        queue->current = nodeAdd;
        queue->previous = queue;
        queue->next = NULL;
    }else{
        list *toAdd = can_fail_malloc(sizeof(list));
        list *last = queue->previous;

        toAdd->current = nodeAdd;
        toAdd->next = NULL;
        toAdd->previous = last;
        last->next = toAdd;

        queue->previous = toAdd;
    }
}

void remove_list(){
    list *aux = NULL;
    if (queue->next != NULL) {
        queue->next->previous = queue->previous;
        aux = queue->next;
        queue->next = NULL;
        queue->previous = NULL;
        free(queue);
        queue = aux;
    }else {
        free(queue);
        queue = NULL;
    }
}

void initBfs(){
    list *aux;
    memset(color,0, (N*M*2+2)*sizeof(int));
    memset(pi,0, (N*M*2+2)*sizeof(int));
    while (queue!=NULL){
        aux = queue->next;
        free(queue);
        queue=aux;
    }
    queue=NULL;
    addList(source);
}



int bfs() {
    int i;
    initBfs();
    while (queue!=NULL){
        node *aux = queue->current;
        remove_list();

        for(i=0;i<aux->numberAdj;i++){
            if(color[aux->adjs[i]->id] == 0 && aux->cap[i] > 0){
                color[aux->adjs[i]->id] = 1;
                pi[aux->adjs[i]->id] = aux->id;
                if (aux->adjs[i] == sink){
                    return 1;
                }
                addList(aux->adjs[i]);
            }
        }
    }
    return 0;
}

int which_adj(node* current,node* adj){
    int i;
    for (i=0;i<current->numberAdj;i++){
        if (current->adjs[i]->id==adj->id){
            return  i;
        }
    }
    return -1;
}

int edmondsKarp()
{
    int maxFlow = 0,last_pi=0;
    while(1)
    {
        int flow = bfs();
        if (flow == 0 || flow+maxFlow == s)
        {
            maxFlow+=flow;
            break;
        }
        maxFlow += flow;
        node* currentNode = sink;
        node* previousNode=NULL;
        while(currentNode != source){
            if(pi[currentNode->id]==M*N*2){
                previousNode=source;
            }else{
                previousNode = nodes[pi[currentNode->id]];
                last_pi = pi[currentNode->id];
            }
            int adj = which_adj(currentNode, previousNode);
            if (adj==-1){
                adj=currentNode->numberAdj;
                currentNode->adjs = can_fail_realloc(currentNode->adjs, sizeof(node*)*(adj+1));
                currentNode->cap = can_fail_realloc(currentNode->cap, sizeof(int)*(adj+1));
                currentNode->adjs[adj] = previousNode;
                currentNode->cap[adj] = 0;
                currentNode->numberAdj++;
            }
            currentNode->cap[adj] = !currentNode->cap[adj];
            adj=which_adj(previousNode,currentNode);
            previousNode->cap[adj] = !previousNode->cap[adj];
            currentNode = previousNode;
        }
        int adj = which_adj(source,nodes[last_pi]);
        source->cap[adj] = !source->cap[adj];
    }
    return maxFlow;
}

void processInput() {
    int i, S, C, j, m, n;
    if (!scanf("%d %d", &m, &n)) {
        printf("Error");
    }

    M = m;
    N = n;
    if (!scanf("%d %d", &S, &C)) {
        printf("Error");
    }
    s=S;
    c=C;

    source = can_fail_malloc(sizeof(node));
    source->flag_super = 0;
    source->flag_person = 0;
    source->numberAdj = 0;
    source->source = 1;
    source->sink = 0;
    source->id = M*N*2;

    sink = can_fail_malloc(sizeof(node));
    sink->flag_super = 0;
    sink->flag_person = 0;
    sink->numberAdj = 0;
    sink->source = 0;
    sink->sink = 1;
    sink->id = M*N*2+1;

    nodes = can_fail_malloc(sizeof(node *) * (N * M * 2));

    int id = 0;

    for (i = 0; i < N * M * 2; i += 2) {
        for (j = 0; j < 2; j++) {
            nodes[i + j] = can_fail_malloc(sizeof(node));
            nodes[i + j]->id = id++;
            nodes[i + j]->flag_super = 0;
            nodes[i + j]->flag_person = 0;
            nodes[i + j]->numberAdj = 0;
            nodes[i + j]->source = 0;
            nodes[i + j]->sink = 0;
        }
        nodes[i]->cap = can_fail_malloc(sizeof(int));
        nodes[i]->adjs = can_fail_malloc(sizeof(node *));


        nodes[i]->adjs[nodes[i]->numberAdj] = nodes[i + 1];
        nodes[i]->cap[0] = 1;

        nodes[i]->numberAdj++;
    }

    for (i=1; i < N*M*2; i+=2){
        if (i%(2*M) - 3 >=0){
            nodes[i]->adjs=can_fail_realloc(nodes[i]->adjs,sizeof(node*)*(nodes[i]->numberAdj+1));
            nodes[i]->cap = can_fail_realloc(nodes[i]->cap,sizeof(int)*(nodes[i]->numberAdj+1));
            nodes[i]->adjs[nodes[i]->numberAdj] = nodes[i-3];
            nodes[i]->cap[nodes[i]->numberAdj] = 1;
            nodes[i]->numberAdj++;
        }

        if (i%(2*M) + 1 < 2*M){
            nodes[i]->adjs=can_fail_realloc(nodes[i]->adjs,sizeof(node*)*(nodes[i]->numberAdj+1));
            nodes[i]->cap = can_fail_realloc(nodes[i]->cap,sizeof(int)*(nodes[i]->numberAdj+1));
            nodes[i]->adjs[nodes[i]->numberAdj] = nodes[i+1];
            nodes[i]->cap[nodes[i]->numberAdj] = 1;
            nodes[i]->numberAdj++;
        }

        if (i-2*M-1>=0){
            nodes[i]->adjs=can_fail_realloc(nodes[i]->adjs,sizeof(node*)*(nodes[i]->numberAdj+1));
            nodes[i]->cap = can_fail_realloc(nodes[i]->cap,sizeof(int)*(nodes[i]->numberAdj+1));
            nodes[i]->adjs[nodes[i]->numberAdj] = nodes[i-2*M-1];
            nodes[i]->cap[nodes[i]->numberAdj] = 1;
            nodes[i]->numberAdj++;
        }
        if(i+2*M-1 < M*N*2){
            nodes[i]->adjs=can_fail_realloc(nodes[i]->adjs,sizeof(node*)*(nodes[i]->numberAdj+1));
            nodes[i]->cap = can_fail_realloc(nodes[i]->cap,sizeof(int)*(nodes[i]->numberAdj+1));
            nodes[i]->adjs[nodes[i]->numberAdj] = nodes[i+2*M-1];
            nodes[i]->cap[nodes[i]->numberAdj] = 1;
            nodes[i]->numberAdj++;
        }


    }

    for (i=0;i<S;i++){
        int line,column;
        if (!scanf("%d %d", &column, &line)) {
            printf("Error");
        }
        int pos = --line * M * 2 + --column * 2;
        if (!nodes[pos+1]->flag_super){
            nodes[pos+1]->flag_super = 1;
            nodes[pos+1]->adjs=can_fail_realloc(nodes[pos+1]->adjs,sizeof(node*) * (nodes[pos+1]->numberAdj+1));
            nodes[pos+1]->cap = can_fail_realloc(nodes[pos+1]->cap,sizeof(int)*(nodes[pos+1]->numberAdj+1));
            nodes[pos+1]->adjs[nodes[pos+1]->numberAdj]=sink;
            nodes[pos+1]->cap[nodes[pos+1]->numberAdj] = 1;
            nodes[pos+1]->numberAdj++;

        }
    }

    for (i=0;i<C;i++){
        int line,column;
        if (!scanf("%d %d", &column, &line)) {
            printf("Error");
        }
        int pos = --line * M * 2 + --column * 2;
        if (!nodes[pos]->flag_person){
            nodes[pos]->flag_person = 1;
            if (source->numberAdj==0){
                source->adjs = can_fail_malloc(sizeof(node*));
                source->cap = can_fail_malloc(sizeof(int));
            }else{
                source->adjs = can_fail_realloc(source->adjs, sizeof(node*) * (source->numberAdj+1));
                source->cap = can_fail_realloc(source->cap,sizeof(int)*(source->numberAdj+1));
            }
            source->adjs[source->numberAdj] = nodes[pos];
            source->cap[source->numberAdj] = 1;
            source->numberAdj++;

        }
    }

}


int main(){
    processInput();
    color=can_fail_malloc(sizeof(int)*(M*N*2+2));
    pi=can_fail_malloc(sizeof(int)*(M*N*2+2));
    int i = edmondsKarp();
    printf("%d\n", i);
    return 0;
}