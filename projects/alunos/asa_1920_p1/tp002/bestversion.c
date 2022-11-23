#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct stack
{
    int maxsize;
    int top;
    int *items;
} Stack;


typedef struct Node{
    int vertexNum;
    int data;
    struct Node *next;
} Node;

typedef struct List{
    Node *head;
} List;

typedef struct Amizade{
    int indiceum;
    int indicedois;
} Amizade;

List **adjlist;

void addNode(int s, int s_data, int d, int d_data){
    Node *dest, *tmp, *src;

    if(adjlist[s]->head == NULL){
        src = (Node *) can_fail_malloc(sizeof(Node));
        src->vertexNum = s;
        src->data = s_data;
        src->next = NULL;
        adjlist[s]->head = src;
    }

    dest = (Node *)can_fail_malloc(sizeof(Node));
    dest->vertexNum = d;
    dest->data = d_data;
    dest->next = NULL;
    tmp = adjlist[s]->head;

    while(tmp->next != NULL)
        tmp = tmp->next;

    tmp->next = dest;
}

struct stack* newStack(int capacity)
{
    struct stack *pt = (struct stack*)can_fail_malloc(sizeof(struct stack));

    pt->maxsize = capacity;
    pt->top = -1;
    pt->items = (int*)can_fail_malloc(sizeof(int) * capacity);

    return pt;
}

int isEmpty(struct stack *pt)
{
    return pt->top == -1;
}

int isFull(struct stack *pt)
{
    return pt->top == pt->maxsize - 1;
}

int size(struct stack *pt)
{
    return pt->top + 1;
}

int min(int a, int b) {
    return (a<b)?a:b;
}

int max(int aa, int b){
    return (aa>b)?aa:b;
}

void push(struct stack *pt, int x)
{
    if (isFull(pt))
    {
        printf("OverFlow\nProgram Terminated\n");
        exit(EXIT_FAILURE);
    }

    pt->items[++pt->top] = x;
}

int peek(struct stack *pt)
{
    if (!isEmpty(pt))
        return pt->items[pt->top];
    else
        exit(EXIT_FAILURE);
}

int pop(struct stack *pt)
{
    if (isEmpty(pt))
    {
        printf("UnderFlow\nProgram Terminated\n");
        exit(EXIT_FAILURE);
    }

    return pt->items[pt->top--];
}

void findComponent(int u, int array_notas[], int disc[], int low[], int length, Stack *stk, bool stkItem[]) {
    static int time = 0;
    int v;
    Node *temp;
    disc[u] = low[u] = ++time;
    push(stk, u);
    stkItem[u] = true;
    if(adjlist[u]->head != NULL) {
        for (v = 0; v < length; v++) {
            temp = adjlist[u]->head->next;
            while (temp != NULL) {
                if (v == temp->vertexNum) {
                    if (disc[v] == -1) {
                        findComponent(v, array_notas, disc, low, length, stk, stkItem);
                        low[u] = min(low[u], low[v]);
                        if(adjlist[v]->head != NULL) {
                            adjlist[u]->head->data = max(adjlist[u]->head->data, adjlist[v]->head->data);
                        } else {
                            adjlist[u]->head->data = max(adjlist[u]->head->data, array_notas[v]);
                        }
                    } else if (stkItem[v]) {
                        low[u] = min(low[u], low[v]);
                        if(adjlist[v]->head != NULL) {
                            adjlist[u]->head->data = max(adjlist[u]->head->data, adjlist[v]->head->data);
                        } else {
                            adjlist[u]->head->data = max(adjlist[u]->head->data, array_notas[v]);
                        }
                    }
                }
                temp = temp->next;
            }
        }
    }
    int poppedItem = 0;
    if(low[u] == disc[u]) {
        while(peek(stk) != u) {
            poppedItem = peek(stk);
            stkItem[poppedItem] = false;
            pop(stk);
        }
        poppedItem = peek(stk);
        stkItem[poppedItem] = false;
        pop(stk);
    }
}

void strongConComponent(int length, int array_notas[]) {
    int disc[length], low[length], i;
    bool stkItem[length];
    Stack *stk = newStack(length);
    for (i = 0; i < length; i++) {
        disc[i] = low[i] = -1;
        stkItem[i] = false;
    }
    for (i = 0; i < length; i++) {
        if (disc[i] == -1)
            findComponent(i, array_notas, disc, low, length, stk, stkItem);
    }
}

int main(){
    char *token, aux[10], auxdois[10], input[10];
    Amizade *array_amizades =  (Amizade *) can_fail_malloc(sizeof(Amizade));
    int *array_notas = (int *) can_fail_malloc(sizeof(int)), nalunos = 0, namizades = 15, contador = -1, contador_aux = 0, i, h;
    while(!(contador_aux >= namizades)){
        scanf("%[^\n]%*c", input);
        if(contador == -1){
            token = strtok(input, ",");
            strcpy(aux, token);
            nalunos = atoi(aux);
            token = strtok(NULL, "\0");
            strcpy(aux,token);
            namizades = atoi(aux);
            array_notas = (int *) can_fail_realloc(array_notas, sizeof(int)*nalunos);
            array_amizades = (Amizade *) can_fail_realloc(array_amizades, sizeof(Amizade)*namizades);
            contador++;
        } else if (contador < nalunos ){
            token = strtok(input, "\0");
            strcpy(aux, token);
            array_notas[contador] = atoi(aux);
            contador++;
        } else if (contador_aux < namizades){
            token = strtok(input, " ");
            strcpy(aux, token);
            token = strtok(NULL, "\0");
            strcpy(auxdois, token);
            array_amizades[contador_aux].indiceum = atoi(aux) - 1;
            array_amizades[contador_aux].indicedois = atoi(auxdois) - 1;
            contador_aux++;
        }
    }

    adjlist = (List **) can_fail_malloc(sizeof(List *)* nalunos);
    for(i = 0; i < nalunos; i++){
        adjlist[i] = (List *) can_fail_malloc(sizeof(List));
        adjlist[i]->head = NULL;
    }

    for(h = 0; h < namizades; h++){
        int index_p = array_amizades[h].indiceum, index_s = array_amizades[h].indicedois;
        addNode(index_p, array_notas[index_p], index_s, array_notas[index_s]);
    }

    strongConComponent(nalunos, array_notas);

    for(i = 0; i < nalunos; i++) {
        if (adjlist[i]->head != NULL) {
            printf("%d\n", adjlist[i]->head->data);
        } else {
            printf("%d\n", array_notas[i]);
        }
    }
    return 0;
}