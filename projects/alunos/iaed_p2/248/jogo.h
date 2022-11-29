#ifndef _JOGO_
#define _JOGO_

/*
 * Libraries
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Structures
*/

/* Structure that represents the type Jogo (the games). */
typedef struct jogo {
    char *nome;
    char *equipa_1; 
    char *equipa_2;
    int pontuacao_1;
    int pontuacao_2;
} Jogo;

/* Structure that represents the node of a doubly linked list for games. */
typedef struct node_jogo {
    Jogo *jogo;
    struct node_jogo *next;
    struct node_jogo *previous;
} Node_jogo;

/* Structure that represents the doubly linked lists for games. */
typedef struct lista_jogo {
    Node_jogo *head;
    Node_jogo *tail;
} Lista_jogo;

/* Structure that represents the hash tables with external chaining for games. */
typedef struct hashtable_jogo {
    int tamanho;
    Lista_jogo **tabela;
} Hashtable_jogo;

/*
 * Functions
*/

/* Function that creates a new game. */
Jogo * cria_jogo(char *nome, char *equipa1, char *equipa2, int pontuacao1, 
int pontuacao2);

/* Function that changes the scores of a game. */
void altera_pontucao_jogo(Jogo *jogo, int pontuacao1, int pontuacao2);

/* Function that frees all the memory allocated for a game. */
void liberta_jogo(Jogo *jogo);

/* Function that creates a new empty list for games. */
Lista_jogo * cria_lista_jogo(void);

/* Function that adds a game to a list of games. */
void adiciona_lista_jogo(Lista_jogo *lista, Jogo *jogo);

/* Function that searches for a game in a list of games. */
Node_jogo * procura_lista_jogo(Lista_jogo *lista, char *jogo);

/* Function that removes a game from a list of games. */
void remove_lista_jogo(Lista_jogo *lista, Jogo *jogo);

/* Function that prints the games in a list of games. */
void imprime_lista_jogo(Lista_jogo *lista, int linha_input);

/* Function that frees all the memory allocated for a list of games and its 
games. */
void liberta_lista_jogo(Lista_jogo *lista);

/* Function that creates a new hash table with external chaining for games. */
Hashtable_jogo * cria_hashtable_jogo(int tamanho);

/* Function that adds a game to a hash table of games. */
void adiciona_hashtable_jogo(Hashtable_jogo *hashtable, Jogo *jogo);

/* Function that searches for a game in an hash table of games. */
Jogo * procura_hashtable_jogo(Hashtable_jogo *hashtable, char *chave);

/* Function that removes a game from a hash table of games. */
Jogo * remove_hashtable_jogo(Hashtable_jogo *hashtable, char *chave);

/* Function that frees all the memory allocated only for the hash table. */
void liberta_hashtable_jogo(Hashtable_jogo *hashtable);

/* Hash function used for the hash table. */
int hash_jogo(char *chave, int tamanho);

#endif
