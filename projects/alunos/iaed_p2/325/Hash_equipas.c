#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "Hash_equipas.h"
#include "Function_Hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Funcao auxiliar da insert_equipa que aloca memoria para a criacao de uma nova equipa, e
 * inicializa as variaveis que estao incluidas nessa equipa. */
Equipas_hash NEWE(char *buffer) {
    Equipas_hash x = can_fail_malloc(sizeof(struct str_equipa));
    x->nome_equipa = can_fail_malloc(sizeof(char) * (strlen(buffer) + 1));
    x->jogos_ganhos = 0;
    strcpy(x->nome_equipa, buffer);
    x->next = NULL;
    return x;
}

/* Funcao auxiliar da insert_equipa que inserte uma nova equipa no inicio de uma lista ligada na
 * Hashtable. */
Equipas_hash insertBeginE(Equipas_hash head, char *buffer) {
    Equipas_hash x = NEWE(buffer);
    /* Se ainda nao existir nenhum elemento na lista. */
    if (head == NULL) {
        head = x;
        x->next = NULL;
    } else {
        x->next = head;
    }
    return x;
}

/* Funcao que inserte uma nova equipa na Hashtable. */
void insert_equipa(Equipas_hash *todas_equipas, char *nome, int E) {
    unsigned long i = hashU(nome, E);
    todas_equipas[i] = insertBeginE(todas_equipas[i], nome);
}

/* Funcao que inicializa a Hahstable alocando memoria. */
Equipas_hash *init_e(int E) {
    Equipas_hash *todas_equipas = can_fail_calloc(E, sizeof(Equipas_hash));
    return todas_equipas;
}

/* Funcao auxiliar da Search que percorre a Hashtable ate encontrar a equipa pretendida. */
Equipas_hash search_listE(Equipas_hash head, char *n) {
    Equipas_hash new = NULL;
    /* Percorre a Hashtable ate encontrar a equipa. */
    for (new = head; new != NULL; new = new->next) {
        if (strcmp(new->nome_equipa, n) == 0) {
            return new;
        }
    }
    return NULL;
}

/* Funcao que retorna uma certa equipa que pertence a Hashtable. */
Equipas_hash SearchE(Equipas_hash *todas_equipas, char *nome, int E) {
    unsigned long i = hashU(nome, E);
    return search_listE(todas_equipas[i], nome);
}

/* Funcao que elimina todos as equipas armazenadas na Hashtable,
e liberta toda a memoria que esta ocupava. */
void destroy_equipas(Equipas_hash *e, int E) {
    Equipas_hash old, aux;
    long i = 0;
    while (i < E) {
        aux = e[i];
        while (aux != NULL) {
            old = aux;
            aux = aux->next;
            free(old->nome_equipa);
            free(old);
        }
        i++;
    }
    free(e);
}