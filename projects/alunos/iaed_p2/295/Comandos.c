#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Estruturas.h"
#include "Comandos.h"
#define MIL_VINTE_QUATRO 1024   /* Tamanho maximo do nome de uma equipa e jogo */
#define VALOR_HASH 10000        /* Numero utilizado na funcao de hash */

/* Funcao do comando A que vai invocar funcoes auxiliares que resultam na adicao de uma nova equipa */
void comando_A(int nl, lista_equipas *a, lista_equipas_aux *b){
    char nome_equipa[MIL_VINTE_QUATRO];
    Equipa *c, *e;
    scanf(" %[^\n]", nome_equipa);
    c = procura_equipa(nome_equipa, a);
    if (c != NULL) {
        printf("%d Equipa existente.\n", nl);
    }
    else { /* No caso da nao existencia dessa equipa, vai adiciona la */
        e = can_fail_malloc(sizeof(Equipa));
        e->nome_equipa = can_fail_malloc(sizeof(char) * (strlen(nome_equipa) + 1));
        strcpy(e->nome_equipa, nome_equipa);
        e->n_vitorias = 0;
        insere_equipa(a, e);
        insere_equipa_aux(b, e);
    }
}

/* Funcao do comando a que vai invocar funcoes auxiliares que resultam na adicao de um novo jogo */
void comando_a(int nl, lista_equipas *a, lista_jogos *b, lista_jogos_aux *c, lista_equipas *g){
    char nome_jogo[MIL_VINTE_QUATRO], nome_equipa1[MIL_VINTE_QUATRO], nome_equipa2[MIL_VINTE_QUATRO];
    int res_equipa1, res_equipa2;
    Equipa *d, *f;
    Jogo *e, *i;
    Jogo_aux *h;
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome_jogo, nome_equipa1, nome_equipa2, &res_equipa1, &res_equipa2);
    d = procura_equipa(nome_equipa1, a);
    f = procura_equipa(nome_equipa2, a);
    e = procura_jogo(nome_jogo, b);
    if (e != NULL){  /* Verifica a existencia do jogo dado no input */
        printf("%d Jogo existente.\n", nl);
    }
    else if (d == NULL || f == NULL){ /* Verifica a existencia das equipas dadas no input */
        printf("%d Equipa inexistente.\n", nl);
    }
    else {
    
        /* Criacao do no da hash table */

        i = can_fail_malloc(sizeof(Jogo));
        i->nome_jogo = can_fail_malloc(sizeof(char) * (strlen(nome_jogo) + 1));
        strcpy(i->nome_jogo, nome_jogo);
        i->equipa1 = can_fail_malloc(sizeof(char) * (strlen(nome_equipa1) + 1));
        strcpy(i->equipa1, nome_equipa1);
        i->equipa2 = can_fail_malloc(sizeof(char) * (strlen(nome_equipa2) + 1));
        strcpy(i->equipa2, nome_equipa2);
        i->resultado1 = res_equipa1;
        i->resultado2 = res_equipa2;

        /* Criacao do no da lista auxiliar */

        h = can_fail_malloc(sizeof(Jogo_aux));
        h->nome_jogo = can_fail_malloc(sizeof(char) * (strlen(nome_jogo) + 1));
        strcpy(h->nome_jogo, nome_jogo);
        h->equipa1 = can_fail_malloc(sizeof(char) * (strlen(nome_equipa1) + 1));
        strcpy(h->equipa1, nome_equipa1);
        h->equipa2 = can_fail_malloc(sizeof(char) * (strlen(nome_equipa2) + 1));
        strcpy(h->equipa2, nome_equipa2);
        h->resultado1 = res_equipa1;
        h->resultado2 = res_equipa2;

        insere_jogo(b, i, g);
        insere_jogo_aux(c, h);
    }
}

/* Funcao do comando P que vai printar os dados de uma equipa caso ela exista */
void comando_P(int nl, lista_equipas *a){
    char nome_equipa[MIL_VINTE_QUATRO];
    Equipa *b;
    scanf(" %[^\n]", nome_equipa);
    b = procura_equipa(nome_equipa, a);
    if (b != NULL){
        printf("%d %s %d\n", nl, b->nome_equipa, b->n_vitorias);
    }
    else{
        printf("%d Equipa inexistente.\n", nl);
    }
}

/* Funcao do comando p que vai o nome de um jogo caso ele exista */
void comando_p(int nl, lista_jogos *a){
    char nome_jogo[MIL_VINTE_QUATRO];
    Jogo *b;
    scanf(" %[^\n]", nome_jogo);
    b = procura_jogo(nome_jogo, a);
    if (b != NULL){
        printf("%d %s %s %s %d %d\n", nl, b->nome_jogo, b->equipa1, b->equipa2, b->resultado1, b->resultado2);
    }
    else{
        printf("%d Jogo inexistente.\n", nl);
    }
}

/* Funcao do comando r que vai invocar uma funcao auxiliar com o objetivo de remover o jogo dado no input */
void comando_r(int nl, lista_jogos *a, lista_equipas *b){
    int i;
    char nome_jogo[MIL_VINTE_QUATRO];
    Jogo *c;
    scanf(" %[^\n]", nome_jogo);
    c = procura_jogo(nome_jogo, a);
    i = hash(nome_jogo);
    if (c != NULL){
        a->no[i] = remove_jogo(nome_jogo, a, b);
    }
    else{
        printf("%d Jogo inexistente.\n", nl);
    }
}

/* Funcao do comando s que vai invocar uma funcao auxiliar com o objetivo de mudar o resultado do jogo dado \
   no caso de ele existir  */
void comando_s(int nl, lista_jogos *a, lista_equipas *c){
    char nome_jogo[MIL_VINTE_QUATRO];
    int res_equipa1, res_equipa2;
    scanf(" %[^:]:%d:%d", nome_jogo, &res_equipa1, &res_equipa2);
    muda_resultado(nl, nome_jogo, res_equipa1, res_equipa2, a, c);

}

/* Funcao do comando l que vai invocar uma funcao auxiliar com o objetivo de listar os jogos \
   pela ordem que foram introduzidos */
void comando_l(int nl, lista_jogos *a, lista_jogos_aux *b){
    int e = 0;
    no_jogos_aux *c, *g;
    Jogo *d;
    c = b->head;

    while (c){
        g = c->next;
        d = procura_jogo(c->jog->nome_jogo, a);
        if (d != NULL){
            for (; g; g = g->next){ /* Ciclo para evitar o corner case de printar duas vezes o mesmo jogo */
                if (strcmp(d->nome_jogo, g->jog->nome_jogo) == 0){
                    e++;
                }
            }
            if (e == 0){  
                printf("%d %s %s %s %d %d\n", nl, d->nome_jogo, d->equipa1, d->equipa2,
                       d->resultado1, d->resultado2);
                c = c->next;
                e = 0;
            }
            else{
                c = c->next;
                e = 0;
            }
        }
        else{
            c = c->next;
        }
    }
}

/* Funcao do comando g que lista por ordem lexicografica as equipas com o maior numero de vitorias */
void comando_g(int nl, lista_equipas_aux *b){
    int n_vitorias = 0, i = 0, j = 0;
    no_equipas *lista_nos[MIL_VINTE_QUATRO];
    no_equipas *c, *d;
    c = b->head;
    d = b->head;
    while (c){
        if (c->eq->n_vitorias > n_vitorias){
            n_vitorias = c->eq->n_vitorias;
            c = c->next;
        }
        else{
            c = c->next;
        }
    }
    /* Vai criar uma lista com os nos das equipas mais vencedoras */
    while (d){
        if (d->eq->n_vitorias == n_vitorias){
            lista_nos[i] = d;
            d = d->next;
            i++;
            j++;
        }
        else{
            d = d->next;
        }
    }
    mergesort(lista_nos, 0, (i - 1)); /* Vai organizar as equipas por ordem lexicografica */
    if (b->head){
        printf("%d Melhores %d\n", nl, n_vitorias);
        for (i = 0; i < j; i++) {
            printf("%d * %s\n", nl, lista_nos[i]->eq->nome_equipa);
        }
    }
}

/* Funcao responsavel por, verificar qual o comando dado no input e levar o codigo ate a funcao desse comando */
void direciona(char e, int nl, lista_equipas *a, lista_equipas_aux *b, lista_jogos *c, lista_jogos_aux *d){
    switch(e){

        /* Verifica qual o comando pedido */
        case 'a':
            comando_a(nl, a, c, d, a);
            break;

        case 'l':
            comando_l(nl, c, d);
            break;

        case 'p':
            comando_p(nl, c);
            break;

        case 'r':
            comando_r(nl, c, a);
            break;

        case 's':
            comando_s(nl, c, a);
            break;

        case 'A':
            comando_A(nl, a, b);
            break;

        case 'P':
            comando_P(nl, a);
            break;

        case 'g':
            comando_g(nl, b);
            break;
    }
}