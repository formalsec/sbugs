#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* Tamanho da hashtable */
#define SIZE 1013
/* Tamanho de lista de caracteres */
#define MAXIJOGO 1024

/* Estrutura que define um jogo (nome do jogo, nome das equipas, pontuacao de cada equipa) */
typedef struct List
{
        char *key;
        char *eq1;
        char *eq2;
        int score1;
        int score2;
        struct List *next, *previous;
} List;

/* Estrutura que define uma lista duplamente ligada */
typedef struct list2
{
    List *head, *last;
}list2;

/* Estrutura que define uma hastable de jogos */
typedef struct HashTable
{
        unsigned int size;
        List **array;
} HashTable;

list2 *list2_create();
void free_node(List *n);
void free_list2(list2 *l);
void add_list2(list2 *l, List *n);
void list2_handler(list2 *ls, char *nome, int score1, int score2);
HashTable *ht_create();
int ht_get(HashTable *hashtable, const char *key);
void ht_insert(HashTable *hashtable, List *jogo);
List *ht_lookup(HashTable *hashtable, const char *key);
int score_handler(HashTable *hashtable, char *nome, int s1, int s2);
void free_hash_table_j(HashTable *ht);
void a(int NL, HashTable *hashtable, HashTable2 *hash_eq, list2 *ls);
void l(int NL, list2 *ls);
void p(int NL, HashTable *hashtable);
void r(int NL, HashTable *hashtable, list2 *ls, HashTable2 *ht_eq);
void s(int NL, HashTable *hashtable, HashTable2 *hash_eq, list2 *ls);
