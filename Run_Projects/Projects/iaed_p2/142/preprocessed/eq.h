#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* Tamanho da hashtable */
#define SIZE 1013
/* Tamanho de lista de caracteres */
#define MAXIJOGO 1024

/* Estrutura que define uma equipa (nome da equipa, numero de vitorias) */
typedef struct equipa
{
    char *nome;
    int vitoria;
    struct equipa *next;
}equipa;

/* Estrutura que define uma hastable de equipas */
typedef struct HashTable2
{
        unsigned int size;
        equipa **array;
} HashTable2;

unsigned int hash(const char *key, unsigned int size);
HashTable2 *ht_create_eq();
int vit_handler_aux(HashTable2 *hashtable, char *nome);
int vit_handler(HashTable2 *hashtable, char *nome);
equipa *ht_lookup_eq(HashTable2 *hashtable, const char *key);
int ht_insert_eq(HashTable2 *hashtable, equipa *eq);
int check_eq(HashTable2 *hashtable, const char *nome);
void free_eq(equipa *eq);
void free_hash_table_e(HashTable2 *ht);
void A(int NL, HashTable2 *hashtable);
void P(int NL, HashTable2 *hashtable);
void g(int NL, HashTable2 *hashtable);
