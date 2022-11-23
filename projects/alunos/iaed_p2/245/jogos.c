#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "p2.h"             /* Header file que contem as estruturas utilizadas no projeto e os comandos */
#include "auxiliares.h"     /* Header file que contem os defines relativos as funcoes auxiliares */
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

/********************************************************************************/
/*  Ficheiro que contem os comandos relativos aos jogos.                        */
/*                                                                              */
/*  Comandos:                                                                   */
/*                                                                              */
/*  a -> a nome:equipa1:equipa2:score1:score2 ; Adiciona um novo jogo.          */
/*  p -> p nome ; Procura um jogo com o nome dado.                              */
/*  l -> l      ; Lista todos os jogos introduzidos.                            */
/*  r -> r nome ; Apaga um jogo dado um nome.                                   */
/*  s -> s nome:score1:score2   ; Altera o score de um jogo dado o nome.        */
/*                                                                              */
/********************************************************************************/

/*  Funcao a
    Input: a nome:equipa1:equipa2:score1:score2
    Output: Nada (excepto erro)
    Descricao: Esta funcao adiciona um novo jogo. */
Lista_jogos *a(int NL, char s[], hashtable_jogos *ht_jogos, hashtable_equipas *ht_equipa, Lista_jogos *lista_jogo) {
    unsigned int slot; 
    Jogo *novo;
    Equipa *equipa;
    char *separa;

    separa = strtok(s, ":");
    if (ht_jogos_verifica(ht_jogos, separa) != NULL) {
        printf("%d Jogo existente.\n", NL);
        return lista_jogo;
    }
    novo = can_fail_malloc(sizeof(Jogo));
    novo->nome = can_fail_malloc(strlen(separa) + 1);
    strcpy(novo->nome, separa);

    separa = strtok(NULL, ":");
    if (ht_equipas_verifica(ht_equipa, separa) == NULL) {
        printf("%d Equipa inexistente.\n", NL);
        free(novo->nome);
        free(novo);
        return lista_jogo;
    }
    novo->equipa1 = can_fail_malloc(sizeof(Equipa));
    novo->equipa1->nome = can_fail_malloc(strlen(separa) + 1);
    strcpy(novo->equipa1->nome, separa);

    separa = strtok(NULL, ":");
    if (ht_equipas_verifica(ht_equipa, separa) == NULL) {
        printf("%d Equipa inexistente.\n", NL);
        free(novo->nome);
        free(novo);
        return lista_jogo;
    }
    novo->equipa2 = can_fail_malloc(sizeof(Equipa));
    novo->equipa2->nome = can_fail_malloc(strlen(separa) + 1);
    strcpy(novo->equipa2->nome, separa);

    separa = strtok(NULL, ":");
    novo->score1 = atoi(separa);

    separa = strtok(NULL, ":");
    novo->score2 = atoi(separa);

    if (novo->score1 > novo->score2) {
        novo->equipa1->vitorias += 1;
        equipa = ht_equipas_verifica(ht_equipa, novo->equipa1->nome);
        equipa->vitorias += 1;
    }
    if (novo->score2 > novo->score1) {
        novo->equipa2->vitorias += 1;
        equipa = ht_equipas_verifica(ht_equipa, novo->equipa2->nome); 
        equipa->vitorias += 1; 
    } 
    novo->next = NULL;
    novo->prev = lista_jogo->last; 
    slot = hash(novo->nome); 
    if (lista_jogo->head == NULL) {
        lista_jogo->head = novo;
    }
    else {
        lista_jogo->last->next = novo; 
    }
    lista_jogo->last = novo;
    ht_jogos->entradas[slot] = novo; 
    return lista_jogo;
}

/*  Funcao p
    Input: p nome
    Output: NL nome-jogo nome-equipa1 nome-equipa2 score1 score2
    Descricao: Esta funcao procura um jogo com o nome dado. */
void p(int NL, char s[], hashtable_jogos *ht_jogo) {
    Jogo *a = ht_jogos_verifica(ht_jogo, s);
    if (a == NULL) {
        printf("%d Jogo inexistente.\n", NL);
        return;
    }
    printf("%d %s %s %s %d %d\n", NL, a->nome, a->equipa1->nome, a->equipa2->nome,
        a->score1, a->score2);
    return;
}

/*  Funcao l
    Input: l
    Output: NL nome-jogo nome-equipa1 nome-equipa2 score1 score2
    Descricao: Esta funcao lista todos os jogos introduzidos. */
void l(int NL, Lista_jogos *lista_jogo) {
    Jogo *t = lista_jogo->head;

    if (t == NULL) {
        return;
    }
    while (t != NULL) {
        printf("%d %s %s %s %d %d\n", NL, t->nome, t->equipa1->nome, t->equipa2->nome,
            t->score1, t->score2);
        t = t->next;
    }
    return;
}

/*  Funcao r
    Input: r nome
    Output: Nada (excepto erro)
    Descricao: Esta funcao apaga um jogo dado um nome. */
Lista_jogos *r(int NL, char s[], hashtable_jogos *ht_jogos, hashtable_equipas *ht_equipa, Lista_jogos *lista_jogo) {
    Equipa *equipa;
    Jogo *a = ht_jogos_verifica(ht_jogos, s);
    if (a == NULL) {
        printf("%d Jogo inexistente.\n", NL);
        return lista_jogo;
    }

    if (a->score1 > a->score2) {
        if (a->equipa1->vitorias > 0) {
            a->equipa1->vitorias -= 1;
            equipa = ht_equipas_verifica(ht_equipa, a->equipa1->nome);
            equipa->vitorias -= 1;
        }
    }
    if (a->score2 > a->score1) {
        if (a->equipa2->vitorias > 0) {
            a->equipa2->vitorias -= 1;
            equipa = ht_equipas_verifica(ht_equipa, a->equipa2->nome);
            equipa->vitorias -= 1;
        }
    }
    if (a->next != NULL) {
        a->next->prev = a->prev;
    }
    if (a->prev != NULL) {
        a->prev->next = a->next;
    }
    if (a == lista_jogo->head) {
        lista_jogo->head = a->next;
    }
    if (a == lista_jogo->last) {
        lista_jogo->last = a->prev;
    }
    free(a->equipa2->nome);
    free(a->equipa2);
    free(a->equipa1->nome);
    free(a->equipa1);
    free(a->nome);
    free(a); 
    return lista_jogo;
} 

/*  Funcao s
    Input: s nome:score1:score2
    Output: Nada (excepto erro)
    Descricao: Esta funcao altera o score de um jogo dado o nome. */
Lista_jogos *s_altera(int NL, char s[], hashtable_jogos *ht_jogos, hashtable_equipas *ht_equipa, Lista_jogos *lista_jogo) {
    Jogo *a;
    Equipa *equipa;
    char *separa = strtok(s, ":");
    a = ht_jogos_verifica(ht_jogos, separa);
    if (a == NULL) {
        printf("%d Jogo inexistente.\n", NL);
        return lista_jogo;
    }
    if (a->score1 > a->score2) {
        if (a->equipa1->vitorias > 0) {
            a->equipa1->vitorias -= 1;
            equipa = ht_equipas_verifica(ht_equipa, a->equipa1->nome);
            equipa->vitorias -= 1;
        }
    }
    if (a->score2 > a->score1) {
        if (a->equipa2->vitorias > 0) {
            a->equipa2->vitorias -= 1;
            equipa = ht_equipas_verifica(ht_equipa, a->equipa2->nome);
            equipa->vitorias -= 1;
        }
    }
    separa = strtok(NULL, ":");
    a->score1 = atoi(separa);

    separa = strtok(NULL, ":");
    a->score2 = atoi(separa);

    if (a->score1 > a->score2) {
        a->equipa1->vitorias += 1;
        equipa = ht_equipas_verifica(ht_equipa, a->equipa1->nome);
        equipa->vitorias += 1;
    }
    if (a->score2 > a->score1) {
        a->equipa2->vitorias += 1;
        equipa = ht_equipas_verifica(ht_equipa, a->equipa2->nome); 
        equipa->vitorias += 1; 
    }
    return lista_jogo; 
} 
 