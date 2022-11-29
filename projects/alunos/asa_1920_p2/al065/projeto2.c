#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/* Francisco Lisboa 92464 /
/ Freddy De Lima 92466 */
#include <stdio.h>
#include <stdlib.h>
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define NUMVIZ 6
/*									+-------------------+
									|        Fila       |
									+-------------------+
*/


typedef struct stack {
    int id;
    struct stack *next;
} Stack; 

Stack *first;
Stack *last;

void stack_init(){
    first = NULL;
    last = NULL;
}

void push(int id){
    Stack *new_elem = can_fail_malloc(sizeof(Stack));
    new_elem->id = id;
    new_elem->next = NULL;
    if(first == NULL){
        first = new_elem;
        last = first;
    }
    else{
        Stack *elem_aux = last;
        elem_aux->next = new_elem;
        last = last->next;
    }
}

int pop(){
    int id;
    id = -1;
    if(first==NULL) return id; /* ERROR*/
    if(last == first){
        last = NULL;
    }
    id = first->id;
    Stack *d = first;
    first = first->next;
    free(d);
    return id;
}
/*                                  +--------------------------+
                                    |        Cruzamento        |
                                    +--------------------------+
*/

typedef struct arco{
    int to;
    int capacidade;
    int fluxo;
    struct arco *next;
}Arco;



typedef struct {
    int pi;
    Arco *vizinhos;

} Cruzamento;

Cruzamento *cruzamentos;
int num_avenidas, num_ruas, num_super, num_cidadaos;



void ad_vizinho_aux(int from, int to, int capacidade){
    if(cruzamentos[from].vizinhos == NULL){
        cruzamentos[from].vizinhos = (Arco *)can_fail_malloc(sizeof(Arco));
        cruzamentos[from].vizinhos->capacidade = capacidade;
        cruzamentos[from].vizinhos->fluxo = 0;
        cruzamentos[from].vizinhos->to = to;
        cruzamentos[from].vizinhos->next = NULL;

    } 
    else{
        Arco *iter;
        for(iter = cruzamentos[from].vizinhos; iter->next != NULL; iter = iter->next);
        iter->next = (Arco *)can_fail_malloc(sizeof(Arco));
        iter->next->capacidade = capacidade;
        iter->next->fluxo = 0;
        iter->next->to = to;
        iter->next->next = NULL;
    }
}

void ad_vizinho(int from, int to){
    ad_vizinho_aux(from, to, 1);
    ad_vizinho_aux(to, from, 0);
}


int BFS(){
    int i, atual, to;
    Arco *iter;
    for(i = 0; i < num_avenidas*num_ruas*2 + 2; i++){
        cruzamentos[i].pi = -1; 
    }
    push(num_ruas*num_avenidas*2);
    cruzamentos[num_ruas*num_avenidas*2].pi = -2;


    while((atual = pop()) != -1){
        for(iter = cruzamentos[atual].vizinhos; iter != NULL; iter = iter->next){
            to = iter->to;
            if(cruzamentos[to].pi == -1){
                if(iter->capacidade - iter->fluxo > 0){
                    cruzamentos[to].pi = atual;
                    if(to == num_avenidas*num_ruas*2 +1){
                      while(pop() != -1);
                      return 1;  
                    }
                    push(to);
                }
            }
        }
    }
    return 0;
}

int Karp(){
    int fluxo_max = 0, atual, anterior;
    Arco *iter;
    while(BFS()){ /*flow = 1*/
        fluxo_max++;
        atual = num_ruas*num_avenidas*2 + 1;
        while(atual != num_avenidas*num_ruas*2){
            anterior = cruzamentos[atual].pi;
            for(iter = cruzamentos[anterior].vizinhos; iter->to != atual; iter = iter->next);
            iter->fluxo++;
            for(iter = cruzamentos[atual].vizinhos; iter->to != anterior; iter = iter->next);
            iter->fluxo--;
            atual = anterior;
        }
    }
    return fluxo_max;
}



void init_cuzamentos(){
    int i, from;
    cruzamentos = (Cruzamento *)can_fail_malloc((num_ruas * num_avenidas * 2 + 2) * sizeof(Cruzamento));
    for(i = 0; i < num_ruas * num_avenidas * 2 + 2; i++){
        cruzamentos[i].vizinhos = NULL;
    }
    
    for(from = 0; from < (num_ruas * num_avenidas); from++){
        ad_vizinho(from, from + (num_ruas * num_avenidas));
    }

    for(from = (num_ruas * num_avenidas); from < (num_ruas * num_avenidas * 2); from++){

        /*arco da direita*/
        if(from % num_avenidas != num_avenidas - 1){
            ad_vizinho(from, from - (num_ruas * num_avenidas) + 1);
        }

        /*arco da esquerda*/
        if(from % num_avenidas != 0){
            ad_vizinho(from, from - (num_ruas * num_avenidas) - 1);
        }
        /*arco de cima*/
        if(from >= (num_ruas * num_avenidas) + num_avenidas){
            ad_vizinho(from, from - (num_ruas * num_avenidas) - num_avenidas);
        }

        /*arco de baixo*/
        if(from < (num_ruas * num_avenidas * 2) - num_avenidas){
            ad_vizinho(from, from - (num_ruas * num_avenidas) + num_avenidas);
        }
    }

}

void criar_super(int ave, int rua){
    ad_vizinho((num_avenidas * num_ruas) + rua * num_avenidas + ave, num_avenidas * num_ruas * 2 + 1);
}

void ad_cidadao(int ave, int rua){
    ad_vizinho(num_avenidas * num_ruas * 2, rua * num_avenidas + ave);
}

void free_allocs(){
    Arco *iter;
    int i;
    for(i = 0; i < num_ruas*num_avenidas*2 + 2; i++){
        while(cruzamentos[i].vizinhos){
            iter = cruzamentos[i].vizinhos;
            cruzamentos[i].vizinhos = iter->next;
            free(iter);
        }
    }
    free(cruzamentos);
}

/*                                  +--------------------+
                                    |        Main        |
                                    +--------------------+
*/


int main(){

    int ave, rua;
    int i;

    scanf("%d %d", &num_avenidas, &num_ruas);

    scanf("%d %d", &num_super, &num_cidadaos);

    init_cuzamentos();
    stack_init();

    for(i = 0; i < num_super; i++){
        scanf("%d %d", &ave, &rua);
        criar_super(ave-1, rua-1);
    }

    for(i = 0; i < num_cidadaos; i++){
        scanf("%d %d", &ave, &rua);
        ad_cidadao(ave-1, rua-1);
    }

    int val = Karp();
    printf("%d\n", val);
    free_allocs();
    
    return 0;
}
