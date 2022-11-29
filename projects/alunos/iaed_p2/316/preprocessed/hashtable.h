#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "equipas.h"
#include "jogos.h"

/* Estrutura que representa uma tabela de dispersao para as equipas e uma para os jogos. */
typedef struct {
    node_jogos **elementos_jogos;     /* Tabela de dispersao para os jogos. */
    node_equipas **elementos_equipas; /* Tabela de dispersao para as equipas. */

    int tamanho_jogos;   /* Tamanho da tabela de dispersao para os jogos. */
    int numero_jogos;    /* Numero de elementos da tabela de dispersao para os jogos. */
    int tamanho_equipas; /* Tamanho da tabela de dispersao para as equipas. */
    int numero_equipas;  /* Numero de elementos da tabela de dispersao para as equipas. */

} hashTable;

hashTable *HTinit(int, int); /* Inicializa a hashtable. */
void HTdestroy(hashTable *); /* Liberta a memoria associada a hashtable. */

void HTinsert_jogo(hashTable *, node_jogos *);  /* Adiciona um jogo. */
void HTdelete_jogo(hashTable *, char *);        /* Remove um jogo. */
node_jogos *HTsearch_jogo(hashTable *, char *); /* Encontra um jogo. */

void HTinsert_equipa(hashTable *, node_equipas *);  /* Adiciona uma equipa. */
node_equipas *HTsearch_equipa(hashTable *, char *); /* Encontra uma equipa. */

#endif
