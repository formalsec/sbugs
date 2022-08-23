#include "Item.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Prototipos funcoes principais da hash que armazena os jogos. */
pHash ht_init(int m);
void ht_destroy(pHash h);
void ht_insert(pHash h, pJogo j);
void ht_delete(pHash h, char *nome);
pJogo ht_search(pHash h, char *nome);

/* Prototipos funcoes principais da hash que armazena as equipa. */
pHash_e ht_init_e(int m);
void ht_e_destroy(pHash_e h_e);
void ht_insert_e(pHash_e h_e, pEquipa e);
pEquipa ht_search_e(pHash_e h_e,char *nome_e);