#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include<stdlib.h>
#define UNVISITED -1
#define MAX(a,b) (a < b ? b : a)
#define MIN(a,b) (a < b ? a : b)

typedef struct stack{
    int val;
    struct stack *next;
}stack;

typedef struct node{
    struct node *prox;
    int valorProx;
}node;

void inserir(int u,int v);
void DFS(int at, int numAlunos);
int findScc(int numAlunos);
void push();
int pop();

node **adjList;
int *notasAlunos, *tempoDescoberta, *low , *onStack;
int temp = 0;
stack *head;


int main(){
    int numAlunos, numRelacoes, n, m;
    int i = 0;

    scanf ("%d, %d", &numAlunos, &numRelacoes);

    notasAlunos = can_fail_malloc(sizeof(int) * numAlunos);
    adjList = can_fail_malloc(sizeof(node) * numAlunos);
    tempoDescoberta = can_fail_malloc(sizeof(int) * numAlunos);
    low = can_fail_malloc(sizeof(int) * numAlunos);
    onStack = can_fail_malloc(sizeof(int) * numAlunos);

    head = NULL;

    for (i = 0; i < numAlunos; i++){
        adjList[i] = NULL;
        tempoDescoberta[i] = UNVISITED;
        low[i] = -1;
        onStack[i] = 0;
        scanf("%d", &n);
        notasAlunos[i] = n;
      }

    for (i = 0; i < numRelacoes; i++){
        scanf("%d %d", &n, &m);
        inserir(n-1, m-1);  
    } 

    findScc(numAlunos);
    for ( i = 0; i < numAlunos ; i++)
        printf("%d\n", notasAlunos[i]);
    return 0;
}

void inserir(int u,int v){
    node *aux, *new;
    new = (node*)can_fail_malloc(sizeof(node));
    new->valorProx = v;
    new->prox = NULL;
 
    if(adjList[u]==NULL)
        adjList[u]=new;

    else{
        aux = adjList[u];

        while(aux->prox != NULL)
            aux = aux->prox;
        aux->prox = new;
    }
}


int findScc(int numAlunos){
    int i;
    for (i = 0; i < numAlunos; i++){
        if(tempoDescoberta[i] == UNVISITED){
            DFS(i, numAlunos);
        }
    }
    return *low;
}


void DFS(int at, int numAlunos){  /* at - node atual, to - proximo node*/
    int to, varPop, max = 0;
    struct node *n;
    push(at);

    onStack[at] = 1;
    tempoDescoberta[at] = temp;
    low[at] = temp;
    temp++;

    n = adjList[at];
    while(n!=NULL){
        to = n->valorProx;
        if (tempoDescoberta[to] == UNVISITED){
            DFS(to, numAlunos);
        }
        if (onStack[to]){
            low[at] = MIN(low[at], low[to]);
            notasAlunos[at] = MAX(notasAlunos[at], notasAlunos[to]);
        }
        else{
            notasAlunos[at] = MAX(notasAlunos[at], notasAlunos[to]);
        }
        n = n->prox;
    }
    max = notasAlunos[at];
    if(tempoDescoberta[at] == low[at]){
        while (1){
            varPop = pop();
            onStack[varPop] = 0;
            low[varPop] = tempoDescoberta[at];
            notasAlunos[varPop] = max;
            if (varPop == at)
            break;
        }
    }
}

void push(int at){
    stack *aux = can_fail_malloc(sizeof(stack));
    if(head == NULL){
        head = aux;
        head ->next = NULL;
        head ->val =at;
        return;
    }
    aux->next = head;
    aux->val = at;
    head = aux;
}

int pop(){
    int i = head->val;
    head = head->next;
    return i;
}