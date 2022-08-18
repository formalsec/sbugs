#ifndef _HASH_TABLE_EQUIPA_
#define _HASH_TABLE_EQUIPA_

#define MAX_STRING 1024
#define HASH_SIZE 2000

#include <stdio.h>

typedef struct equipa
{
    struct equipa* next;
    char *nome_equipa;
    int vitorias;
}equipa;

equipa * init_hash_table_equipa(equipa * hash[HASH_SIZE]);

equipa * hash_table_equipa_insert(equipa *e, equipa *hash[HASH_SIZE]);

equipa * hash_table_equipa_lookup(char *nome, equipa *hash[HASH_SIZE]);

equipa * hash_table_equipa_delete(char *nome, equipa *hash[HASH_SIZE]);



#endif