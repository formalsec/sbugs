#ifndef _EQUIPA_
#define _EQUIPA_

/*
 * Libraries
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Structures
*/

/* Structure that represents the type Equipa (the teams). */
typedef struct equipa {
    char *nome;
    int vitorias;
} Equipa;

/* Structure that represents the node of a doubly linked list for teams. */
typedef struct node_equipa {
    Equipa *equipa;
    struct node_equipa *next;
    struct node_equipa *previous;
} Node_equipa;

/* Structure that represents the doubly linked lists for teams. */
typedef struct lista_equipa {
    Node_equipa *head;
    Node_equipa *tail;
} Lista_equipa;

/* Structure that represents the hash tables with external chaining for teams. */
typedef struct hashtable_equipa {
    int tamanho;
    Lista_equipa **tabela;
} Hashtable_equipa;

/* Structure that represents an array for teams with the same number of victories. */
typedef struct tabela_equipas {
    Equipa **equipas;
    int n_equipas, vitorias;
} Tabela_equipas;

/*
 * Functions
*/

/* Function that creates a new team. */
Equipa * cria_equipa(char *nome);

/* Function that changes the number of victories of a team. */
void altera_vitorias_equipas(Equipa *equipa, int vitorias);

/* Function that frees all the memory allocated for a team. */
void liberta_equipa(Equipa *equipa);

/* Function that creates a new empty list for teams. */
Lista_equipa * cria_lista_equipa(void);

/* Function that adds a team to a list of teams. */
void adiciona_lista_equipa(Lista_equipa *lista, Equipa *equipa);

/* Function that searches for a team in a list of teams. */
Equipa * procura_lista_equipa(Lista_equipa *lista, char *equipa);

/* Function that frees all the memory allocated for a list of teams and its 
teams. */
void liberta_lista_equipa(Lista_equipa *lista);

/* Function that creates a new hash table with external chaining for teams. */
Hashtable_equipa * cria_hashtable_equipa(int tamanho);

/* Function that adds a team to a hash table of teams. */
void adiciona_hashtable_equipa(Hashtable_equipa *hashtable, Equipa *equipa);

/* Function that searches for a team in an hash table of teams. */
Equipa * procura_hashtable_equipa(Hashtable_equipa *hashtable, char *chave);

/* Function that searches for the teams with the most amount of wins in an 
hash table of teams. */
Tabela_equipas * maximas_vitorias_equipa(Hashtable_equipa *hashtable);

/* Function that frees all the memory allocated for the hash table and its 
content. */
void liberta_hashtable_equipa(Hashtable_equipa *hashtable);

/* Hash function used for the hash table. */
int hash_equipa(char *chave, int tamanho);

#endif
