#include "Hash_jogos.h"
#include "Function_Hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Funcao auxiliar da insert_jogo que aloca memoria para a criacao de um novo jogo, e inicializa as
 * variaveis que estao incluidas nesse jogo. */
Jogo_hash NEW(jogo *res) {
    Jogo_hash x = malloc(sizeof(struct str_jogo));
    x->ptr_jogo = res;
    x->next = NULL;
    return x;
}

/* Funcao auxiliar da insert_jogo que inserte um novo jogo no inicio de uma lista ligada na
 * Hashtable. */
Jogo_hash insertBegin(Jogo_hash head, jogo *res) {
    Jogo_hash x = NEW(res);
    /* Se ainda nao existir nenhum elemento na lista. */
    if (head == NULL) {
        head = x;
        x->next = NULL;
    } else {
        x->next = head;
    }
    return x;
}

/* Funcao que inserte um novo jogo na Hashtable. */
void insert_jogo(Jogo_hash *todos_jogos, jogo *ptr_jogo, int M) {
    unsigned long i = hashU(ptr_jogo->nome, M);
    todos_jogos[i] = insertBegin(todos_jogos[i], ptr_jogo);
}

/* Funcao auxiliar da delete_jogo que elimina um certo jogo da Hashtable. */
Jogo_hash delete_node(Jogo_hash head, jogo *res) {
    Jogo_hash t, prev;
    /* Percorre a Hashtable ate encontrar o jogo. */
    for (t = head, prev = NULL; t != NULL; prev = t, t = t->next) {
        if (strcmp(t->ptr_jogo->nome, res->nome) == 0) {
            if (t == head) {
                head = t->next;
            } else {
                prev->next = t->next;
            }
            free(t);
            break;
        }
    }
    return head;
}

/* Funcao que inicializa a Hahstable alocando memoria. */
Jogo_hash *init_j(int M) {
    Jogo_hash *todos_jogos = calloc(M, sizeof(Jogo_hash));
    return todos_jogos;
}

/* Funcao que elimina um certo jogo da Hashtable. */
void delete_jogo(Jogo_hash *todos_jogos, jogo *ptr_jogo, int M) {
    unsigned long i = hashU(ptr_jogo->nome, M);
    todos_jogos[i] = delete_node(todos_jogos[i], ptr_jogo);
}

/* Funcao auxiliar da Search que percorre a Hashtable ate encontrar o jogo pretendido. */
jogo *search_list(Jogo_hash head, char *nome) {
    Jogo_hash new;
    /* Percorre a Hashtable ate encontrar o jogo. */
    for (new = head; new != NULL; new = new->next) {
        if (strcmp(new->ptr_jogo->nome, nome) == 0) {
            return new->ptr_jogo;
        }
    }
    return NULL;
}

/* Funcao que retorna um certo jogo que pertence a Hashtable. */
jogo *Search(Jogo_hash *todos_jogos, char *nome, int M) {
    unsigned long i = hashU(nome, M);
    return search_list(todos_jogos[i], nome);
}

/* Funcao que elimina todos os jogos armazenados na Hashtable,
e liberta toda a memoria que esta ocupava. */
void destroy_jogos(Jogo_hash *j, int M) {
    Jogo_hash old, aux;
    long i = 0;
    while (i < M) {
        old = j[i];
        while (old != NULL) {
            aux = old->next;
            free(old);
            old = aux;
        }
        i++;
    }
    free(j);
}