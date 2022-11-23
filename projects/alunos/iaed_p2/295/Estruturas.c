#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Estruturas.h"
#define MIL_VINTE_QUATRO 1024   /* Tamanho maximo do nome de uma equipa e jogo */
#define VALOR_HASH 10000        /* Numero utilizado na funcao de hash */

/* Funcao de hash responsavel por calcular o indice de insercao na hash table */
int hash(char *v) {
    int h, a = 31415, b = 27183;
    for (h = 0; *v != '\0'; v++, a = a*b % (VALOR_HASH-1)) {
        h = (a * h + *v) % VALOR_HASH;
    }
    return h;
}

/* Funcao responsavel pela inicializacao da hash table de equipas */
void inicia_lista_equipas(lista_equipas * a) {
    int i;
    for (i = 0; i < VALOR_HASH; i++) {
        a->no[i] = NULL;
    }
}

/* Funcao responsavel pela inicializacao da lista ligada auxiliar de equipas */
void inicia_lista_equipas_aux(lista_equipas_aux *a){
    a->head = NULL;
}

/* Funcao responsavel pela inicializacao da hash table de jogos */
void inicia_lista_jogos(lista_jogos *a){
    int i;
    for (i = 0; i < VALOR_HASH; i++) {
        a->no[i] = NULL;
    }
}

/* Funcao responsavel pela inicializacao da lista duplamente ligada de jogos */
void inicia_lista_jogos_aux(lista_jogos_aux *a){
    a->head = NULL;
    a->last = NULL;
}

/* Funcao responsavel por verificar a existencia de uma equipa */
Equipa* procura_equipa(char nome_equipa[], lista_equipas *a){
    int i = hash(nome_equipa);
    no_equipas *c;
    c = a->no[i];
    while (c != NULL) {
        if (strcmp(c->eq->nome_equipa, nome_equipa) == 0) {
            return c->eq; /* No caso de existir retorna o ponteiro para a estrutura da equipa dada */
        }
        else {
            c = c->next;
        }
    }
    return NULL; /* No caso de nao existir retorna NULL */
}

/* Funcao responsavel por inserir uma nova equipa na hash table de equipas */
void insere_equipa(lista_equipas *a, Equipa *b){
    int i = hash(b->nome_equipa);
    no_equipas *atual = can_fail_malloc(sizeof(no_equipas));
    atual->eq = b;
    atual->next = a->no[i];
    a->no[i] = atual;
}

/* Funcao responsavel por inserir uma nova equipa na lista ligada auxiliar de equipas */
void insere_equipa_aux(lista_equipas_aux *a, Equipa *b){
    no_equipas *atual = can_fail_malloc(sizeof(no_equipas));
    atual->eq = b;
    atual->next = a->head;
    a->head = atual;
}

/* Funcao responsavel por verificar a existencia de um jogo */
Jogo* procura_jogo(char nome_jogo[], lista_jogos *a){
    int i = hash(nome_jogo);
    no_jogos *c;
    c = a->no[i];
    while (c != NULL){
        if (strcmp(c->jog->nome_jogo, nome_jogo) == 0){
            return c->jog; /* No caso de existir retorna o ponteiro para a estrutura do jogo dado */
        }
        else{
            c = c->next;
        }
    }
    return NULL; /* No caso de nao existir retorna NULL */
}

/* Funcao responsavel por inserir um novo jogo na hash table */
void insere_jogo(lista_jogos *a, Jogo *b, lista_equipas *c){
    int i, j;
    no_equipas *d;
    no_jogos *atual;
    i = hash(b->nome_jogo);
    atual = can_fail_malloc(sizeof(no_jogos));
    atual->jog = b;
    atual->next = a->no[i];
    if (a->no[i] != NULL){
        a->no[i] = atual;
        a->no[i]->previous = NULL;
        a->no[i]->next->previous = atual;
    }
    else{
        a->no[i] = atual;
        a->no[i]->previous = NULL;
    }

    /* Os proximos dois if s sao relativos ao aumento do numero de vitorias dado o resultado do jogo */
    if (b->resultado1 > b->resultado2) {
        j = hash(b->equipa1);
        d = c->no[j];
        while (strcmp(d->eq->nome_equipa, b->equipa1) != 0) {
            d = d->next;
        }
        d->eq->n_vitorias++;
    }
    if (b->resultado1 < b->resultado2){
        j = hash(b->equipa2);
        d = c->no[j];
        while (strcmp(d->eq->nome_equipa, b->equipa2) != 0) {
            d = d->next;
        }
        d->eq->n_vitorias++;
    }
}

/* Funcao responsavel por inserir um novo jogo na lista duplamente ligada auxiliar dos jogos */
void insere_jogo_aux(lista_jogos_aux *a, Jogo_aux *b){
    no_jogos_aux *atual = can_fail_malloc(sizeof(no_jogos_aux));
    atual->jog = b;
    atual->next = a->head;
    if (a->head == NULL){
        a->head = atual;
    }
    atual->next = NULL;
    atual->previous = a->last;
    if (a->last){
        a->last->next = atual;
    }
    a->last = atual;
}

/* Funcao responsavel por alterar o numero de vitorias de uma equipa quando e removido um jogo */
void muda_n_vitorias (lista_equipas *a, lista_jogos *b, char nome_jogo[]){
    int i, j;
    no_jogos *c;
    no_equipas *d;
    i = hash(nome_jogo);
    c = b->no[i];
    while (strcmp(c->jog->nome_jogo, nome_jogo) != 0){
        c = c->next;
    }
    /* No caso da equipa 1 ser a vencedora do jogo em questao */
    if (c->jog->resultado1 > c->jog->resultado2){ 
        j = hash(c->jog->equipa1);
        d = a->no[j];
        while (strcmp(d->eq->nome_equipa, c->jog->equipa1) != 0){
            d = d->next;
        }
        /* Diminui o numero de vitorias no caso da equipa 1 ter vencido o jogo removido */
        d->eq->n_vitorias--; 
    }
    else if (c->jog->resultado1 < c->jog->resultado2){
        j = hash(c->jog->equipa2);
        d = a->no[j];
        while (strcmp(d->eq->nome_equipa, c->jog->equipa2) != 0){
            d = d->next;
        }
        /* Diminui o numero de vitorias no caso da equipa 2 ter vencido o jogo removido */
        d->eq->n_vitorias--; 
    }
}

/* Funcao responsavel por remover um jogo dado da hash table dos jogos */
no_jogos  * remove_jogo(char nome_jogo[], lista_jogos *a, lista_equipas *c) {
    Jogo *b; 
    no_jogos *d, *f, *g, *h, *j;
    int i;
    b = procura_jogo(nome_jogo, a); 
    muda_n_vitorias(c, a, nome_jogo);
    i = hash(nome_jogo);
    d = a->no[i];
    f = a->no[i];
    for (; f; f = f->next) {
        if (strcmp(f->jog->nome_jogo, b->nome_jogo) == 0) {
            /* No caso de ser o primeiro e unico */
            if (f->next == NULL && f->previous == NULL) {
                free(f->jog->nome_jogo);
                free(f->jog->equipa1);
                free(f->jog->equipa2);
                free(f->jog);
                free(f);
                f = NULL;
                return f;
            } 
            /* No caso de ser o primeiro mas nao unico */
            else if (f->previous == NULL) {
                g = f->next;
                g->previous = NULL;
                free(f->jog->nome_jogo);
                free(f->jog->equipa1);
                free(f->jog->equipa2);
                free(f->jog);
                free(f);
                return g;
            } 
            /* Nos restantes casos */
            else {
                h = f->next;
                j = f->previous;
                if (h != NULL) {
                    h->previous = j;
                }
                j->next = h;
                free(f->jog->nome_jogo);
                free(f->jog->equipa1);
                free(f->jog->equipa2);
                free(f->jog);
                free(f);
                return d;
            }
        }
    }
    return 0;
}


/* Funcao responsavel por alterar o resultado de um jogo e consequentemente o numero de vitorias das equipas */
void muda_resultado(int nl, char nome_jogo[], int res_equipa1, int res_equipa2, lista_jogos *a, lista_equipas *d){
    int c, f, g;
    Jogo *b;
    no_equipas *h;
    b = procura_jogo(nome_jogo, a);
    if (b != NULL){
        if (b->resultado1 > b->resultado2){
            c = 1; /* Variavel c a 1 no caso da equipa 1 ter vencido o jogo antes da alteracao do resultado */
        }
        else if (b->resultado1 < b->resultado2){
            c = 2; /* Variavel c a 2 no caso da equipa 2 ter vencido o jogo antes da alteracao do resultado */
        }
        else{
            c = 0; /* Variavel c a 0 no caso de empate antes da alteracao do resultado */
        }
        b->resultado1 = res_equipa1;
        b->resultado2 = res_equipa2;

        /* Os proximos if s servem para se proceder a alteracao do numero de vitoria dado o novo resultado */
        if (c == 1 && (res_equipa1 < res_equipa2)){
            f = hash(b->equipa1);
            h = d->no[f];
            while (strcmp(h->eq->nome_equipa, b->equipa1) != 0){
                h = h->next;
            }
            h->eq->n_vitorias--;
            g = hash(b->equipa2);
            h = d->no[g];
            while (strcmp(h->eq->nome_equipa, b->equipa2) != 0){
                h = h->next;
            }
            h->eq->n_vitorias++;
        }
        else if (c == 1 && (res_equipa1 == res_equipa2)){
            f = hash(b->equipa1);
            h = d->no[f];
            while (strcmp(h->eq->nome_equipa, b->equipa1) != 0){
                h = h->next;
            }
            h->eq->n_vitorias--;
        }
        else if (c == 2 && (res_equipa1 > res_equipa2)){
            f = hash(b->equipa1);
            h = d->no[f];
            while (strcmp(h->eq->nome_equipa, b->equipa1) != 0){
                h = h->next;
            }
            h->eq->n_vitorias++;
            g = hash(b->equipa2);
            h = d->no[g];
            while (strcmp(h->eq->nome_equipa, b->equipa2) != 0){
                h = h->next;
            }
            h->eq->n_vitorias--;
        }
        else if (c == 2 && (res_equipa1 == res_equipa2)){
            g = hash(b->equipa2);
            h = d->no[g];
            while (strcmp(h->eq->nome_equipa, b->equipa2) != 0){
                h = h->next;
            }
            h->eq->n_vitorias--;
        }
        else if (c == 0 && (res_equipa1 > res_equipa2)){
            f = hash(b->equipa1);
            h = d->no[f];
            while (strcmp(h->eq->nome_equipa, b->equipa1) != 0){
                h = h->next;
            }
            h->eq->n_vitorias++;
        }
        else if (c == 0 && (res_equipa1 < res_equipa2)){
            g = hash(b->equipa2);
            h = d->no[g];
            while (strcmp(h->eq->nome_equipa, b->equipa2) != 0){
                h = h->next;
            }
            h->eq->n_vitorias++;
        }
    }
    else {
        printf("%d Jogo inexistente.\n", nl);
    }
}

/* Funcao responsavel por dar free na hash table das equipas quando solicitado o fim do programa */
void free_hash_equipas (lista_equipas *a){
    int i;
    lista_equipas *b = a;
    no_equipas *c, *d;
    for (i = 0; i < VALOR_HASH; i++){
        c = b->no[i];
        while (c){
            d = c->next;
            free(c->eq->nome_equipa);
            free(c->eq);
            free(c);
            c = d;
        }
    }
    free(a);
}

/* Funcao responsavel por dar free na lista ligada auxiliar das equipas quando solicitado o fim do programa */
void free_lista_equipas (lista_equipas_aux *a){
    lista_equipas_aux *b = a;
    no_equipas *c, *d;
    c = b->head;
    while (c){
        if (c->next != NULL) {
            d = c->next;
            /*free(c->eq);*/
            free(c);
            c = d;
        }
        else {
            free(c);
            break;
        }
    }
    free(a);
}

/* Funcao responsavel por dar free na hash table dos jogos quando solicitado o fim do programa */
void free_hash_jogos (lista_jogos * a){
    int i;
    lista_jogos *b = a;
    no_jogos *c, *d;
    for (i = 0; i < VALOR_HASH; i++){
        c = b->no[i];
        while (c){
            d = c->next;
            free(c->jog->nome_jogo);
            free(c->jog->equipa1);
            free(c->jog->equipa2);
            free(c->jog);
            free(c);
            c = d;
        }
    }
    free(a);
}

/* Funcao responsavel por dar free na lista duplamente ligada dos jogos quando solicitado o fim do programa */
void free_lista_jogos (lista_jogos_aux *a){
    lista_jogos_aux *b = a;
    no_jogos_aux *c, *d;
    c = b->head;
    while (c){
        if (c->next != NULL) {
            d = c->next;
            free(c->jog->nome_jogo);
            free(c->jog->equipa1);
            free(c->jog->equipa2);
            free(c->jog);
            free(c);
            c = d;
        }
        else {
            free(c->jog->nome_jogo);
            free(c->jog->equipa1);
            free(c->jog->equipa2);
            free(c->jog);
            free(c);
            break;
        }
    }
    free(a);
}

/* Funcao que convoca as funcoes que dao free as hash tables e listas auxiliares */
void free_geral (lista_equipas *a, lista_equipas_aux *b, lista_jogos *c, lista_jogos_aux *d){
    free_hash_equipas(a);
    free_lista_equipas(b);
    free_hash_jogos(c);
    free_lista_jogos(d);
}

/* Funcao auxiliar a funcao merge relativa ao comando g */
int aux_merge(no_equipas *a, no_equipas *b) {
    int j;
    for (j = 0; j < MIL_VINTE_QUATRO; j++) {
        /* Verifica se a primeira letra de a e maior que a de b ou se b chega ao fim primeiro e retorna 1 */
        if (a->eq->nome_equipa[j] > b->eq->nome_equipa[j] || b->eq->nome_equipa[j] == '\0')         
            return 1;
            /* Se a primeira letra de a for menor que a de b ou se a for chegar ao fim primeiro retorna 0 */
        else if (a->eq->nome_equipa[j] < b->eq->nome_equipa[j] || a->eq->nome_equipa[j] == '\0')    
            return 0;
    }
    return 0;
}

/* Funcao merge relativa ao comando g */
void merge(no_equipas **a, int l, int m, int r){
    no_equipas *aux[MIL_VINTE_QUATRO];
    int i, j ,k;
    for (i = m + 1; i > l; i--)
        aux[i - 1] = a[i - 1];
    for (j = m; j < r; j++)
        aux[r + m - j] = a[j + 1];
    for (k = l; k <= r; k++)

        /* No caso da funcao auxiliar retornar 1 , esta condicao e feita */
        if (aux_merge(aux[i],aux[j]))
            a[k] = aux[j--];
        else
            a[k] = aux[i++];
}

/* Funcao mergesort relativa ao comando g */
void mergesort(no_equipas **a,int l,int r) {
    int m = (r + l) / 2;
    if (r <= l)
        return;
    mergesort(a, l, m);
    mergesort(a, m + 1, r);
    merge(a, l, m, r);
}