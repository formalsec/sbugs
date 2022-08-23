#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comandos.h"
#include "jogos.h"
#include "equipas.h"

#define MAX 1023 /* tamanho maximo dos nomes de jogos e equipas */
#define M 1049


/* Esta funcao retorna a equipa vencedora tendo em conta os scores de 2 equipas. */

char* vencedor_f(char* equipa1, char* equipa2, unsigned int score1,  unsigned int score2) {
    char *empate = "empate";
    if (score1 > score2) 
        return equipa1;
    else if (score1 < score2)
        return equipa2;
    else
        return empate;
}

 
/* Esta funcao adiciona um novo jogo ao sistema. */

void a(unsigned long contador, link *heads_jogos, link_e *heads_equipas, lst_ptr lista) {   
    char nome[MAX], equipa1[MAX], equipa2[MAX];
    unsigned int score1, score2;
    getchar(); /* pois existe um espaco entre a letra do comando e o resto */
    scanf("%[^:\n]:%[^:\n]:%[^:\n]:%u:%u", nome, equipa1, equipa2, &score1, &score2); 

    /* As funcoes de search retornam NULL se o jogo ou equipa nao existem no sistema */

    if (hash_search_jogo(nome, heads_jogos) != NULL)  { 
        printf("%ld Jogo existente.\n", contador);
        return;
    }

    else if ((hash_search_equipa(equipa1, heads_equipas) == NULL) || (hash_search_equipa(equipa2, heads_equipas) == NULL)) {
        printf("%ld Equipa inexistente.\n", contador);
        return;
    }

    else {
        char* vencedor;
        char *empate = "empate";
        equipa_ptr e;
        jogo_ptr x = (jogo_ptr) malloc(sizeof(jogo)); /* x eh ponteiro para o novo jogo criado */
        x->nome = (char*) malloc(sizeof(char)*(strlen(nome)+1));
        x->equipa1 = (char*) malloc(sizeof(char)*(strlen(equipa1)+1));
        x->equipa2 = (char*) malloc(sizeof(char)*(strlen(equipa2)+1));
        strcpy(x->nome, nome); 
        strcpy(x->equipa1, equipa1); 
        strcpy(x->equipa2, equipa2); 
        x->score1 = score1;
        x->score2 = score2;
        hash_insert_jogo(x, heads_jogos); /* guardar na hashtable */
        insertEnd_lista(lista, x); /* guardar na lista com todos os jogos por ordem de introducao */
        vencedor = vencedor_f(x->equipa1, x->equipa2, x->score1, x->score2); /* obter o vencedor do jogo */
        if (strcmp(vencedor, empate) == 0)
            return;
        else {
            e = hash_search_equipa(vencedor, heads_equipas); 
            e->vitorias++; /* se nao houve empate, incrementar as vitorias do vencedor */
            return;    
        }
    }
}

/* Esta funcao lista todos os jogos por ordem de introducao. */

/* Como temos uma lista ligada com todos os jogos por ordem de introducao, basta percorre-la. */

void l(unsigned long contador, lst_ptr lista) {  
    link t, head = lista->head;
    jogo_ptr j;
    for(t = head; t != NULL; t = t->next) {
        j = t->j;
        printf("%ld %s %s %s %u %u\n", contador, j->nome, j->equipa1, j->equipa2, j->score1, j->score2);
    }
    return;
}


/* Esta funcao procura o jogo com o nome dado. */ 
    
void p(unsigned long contador, link *heads_jogos) {  
    char nome[MAX];
    jogo_ptr j;
    getchar();
    scanf("%[^:\n]", nome);
    j = hash_search_jogo(nome, heads_jogos); /* procura o jogo no sistema */
    if (j != NULL) { /* se j eh NULL, o jogo eh inexistente */
            printf("%ld %s %s %s %u %u\n", contador, j->nome, j->equipa1, j->equipa2, j->score1, j->score2);
        return;
    }
    else {
        printf("%ld Jogo inexistente.\n", contador);
        return;
    }
}

/* Esta funcao apaga um jogo dado um nome. */

void r(unsigned long contador, link *heads_jogos, link_e *heads_equipas, lst_ptr lista) {
    char nome[MAX];
    char* vencedor;
    char* empate = "empate";
    jogo_ptr j;
    equipa_ptr e;
    getchar();
    scanf("%[^:\n]", nome);
    j = hash_search_jogo(nome, heads_jogos);
    if (j == NULL) {
        printf("%ld Jogo inexistente.\n", contador);
        return;
    }

    else {

        /* Se o jogo a ser apagado tinha um vencedor, retirar-lhe a vitoria */

        vencedor = vencedor_f(j->equipa1, j->equipa2, j->score1, j->score2);
        if (strcmp(vencedor, empate) != 0) { 
                e = hash_search_equipa(vencedor, heads_equipas);
                e->vitorias--;
        }
        hash_delete_jogo(nome, heads_jogos, lista); /* eliminar o jogo da hashtable e lista */
        return;
    }
}

/* Esta funcao altera o score de um jogo dado um nome. */

void s(unsigned long contador, link *heads_jogos, link_e *heads_equipas) {
    char nome[MAX];
    char *empate = "empate";
    unsigned int score1, score2;
    char* vencedor_ant, *vencedor_dep;
    jogo_ptr j;
    equipa_ptr e_ant, e_dep;
    getchar();
    scanf("%[^:\n]:%u:%u", nome, &score1, &score2);
    j = hash_search_jogo(nome, heads_jogos);
    if (j == NULL) {
        printf("%ld Jogo inexistente.\n", contador);
        return;
    }

    else {
        vencedor_ant = vencedor_f(j->equipa1, j->equipa2, j->score1, j->score2); /* saber vencedor antigo */
        vencedor_dep = vencedor_f(j->equipa1, j->equipa2, score1, score2); /* saber vencedor novo */
        j->score1 = score1; /* atualizar os scores */
        j->score2 = score2;
        if (strcmp(vencedor_ant, vencedor_dep) == 0) /* o vencedor nao se alterou */
            return;
        else {

            /* se o vencedor se alterou e antes nao havia empate, retirar vitoria */

            if (strcmp(vencedor_ant, empate) != 0) {
                e_ant = hash_search_equipa(vencedor_ant, heads_equipas);
                e_ant->vitorias--;
            }

            /* se agora temos empate, nao eh preciso incrementar vitorias */

            if (strcmp(vencedor_dep, empate) == 0)
                return;
            
            /* se temos vencedor novo, incrementar vitorias */ 

            else {
                e_dep = hash_search_equipa(vencedor_dep, heads_equipas);
                e_dep->vitorias++;
                return;
            }
        }
    }
}

        

/* Esta funcao adiciona uma nova equipa ao sistema. */
    
void A(unsigned long contador, link_e *heads_equipas) {   
    char nome[MAX];
    getchar();
    scanf("%[^:\n]", nome); 

    if (hash_search_equipa(nome, heads_equipas) != NULL) {
        printf("%ld Equipa existente.\n", contador);
        return;
    }

    else {
        equipa_ptr e = (equipa_ptr) malloc(sizeof(equipa)); /* x eh ponteiro para o novo jogo criado */
        e->nome = (char*) malloc(sizeof(char)*(strlen(nome)+1));
        strcpy(e->nome, nome); 
        e->vitorias = 0;
        hash_insert_equipa(e, heads_equipas); /* guardar a nova equipa na hashtable */
        return;
    }
}

/* Esta funcao procura uma equipa dado um nome. */

void P(unsigned long contador, link_e *heads_equipas) {
    char nome[MAX];
    equipa_ptr e;
    getchar();
    scanf("%[^:\n]", nome);
    e = hash_search_equipa(nome, heads_equipas);


    if (e == NULL) {
        printf("%ld Equipa inexistente.\n", contador);
        return;
    }

    else {
        printf("%ld %s %u\n", contador, nome, e->vitorias);
        return;
    }
}

/* Esta funcao faz a comparacao entre duas strings, necessaria para o qsort no comando g. */

int compare(const void *x, const void *y) {
    char **v_x, **v_y;
    v_x = (char **) x;
    v_y = (char **) y;
    return strcmp(*v_x, *v_y);
}

/* Esta funcao encontra as equipas que ganharam mais jogos e lista por ordem lexicografica. */

void g(unsigned long contador, link_e *heads_equipas) {
    char* vec[150]; /* inicializacao de vetor que vai guardar os ponteiros para nomes de equipas com mais vitorias */
    int i, n_equipas = 0;
    unsigned int max_vit = 0;
    link_e t;
    equipa_ptr e;
    for(i = 0; i < M; i++) { /* percorrer todas as listas da hashtable de equipas */
        for(t = heads_equipas[i]; t != NULL; t = t->next) {
            e = t->e;
            if (e->vitorias == max_vit) { /* se tem tantas vitorias como o maximo ate agora, adicionar ao vetor */
                vec[n_equipas] = e->nome;
                n_equipas++;
                
            }
            else if (e->vitorias > max_vit) { /* se tem mais vitorias, comecar a escrever no inicio do vetor */
                vec[0] = e->nome;
                n_equipas = 1; /* numero de equipas com maximo de vitorias passa a ser 1 */
                max_vit = e->vitorias; /* atualizar maximo de vitorias */          
            }
        }
    }
    if (n_equipas > 0) { /* se nao existem equipas, nao se faz nada */
        printf ("%ld Melhores %d\n", contador, max_vit);
        qsort(vec, n_equipas, sizeof(char*), compare); /* ordenar por ordem lexicografica */
        for (i = 0; i < n_equipas; i++) /* i < n_equipas garante que apenas le os indices desejados */
            printf("%ld * %s\n", contador, vec[i]);
    }
    return;
}




    


            










        








