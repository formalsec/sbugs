#ifndef main_aux_h
#define main_aux_h
#include "estruturas.h"



/* funcoes auxliares da lista por ordem de insercao dos jogos */
void guarda_lista_ord(bloco_hash_jogo *head,bloco_hash_jogo *tail,jogo *j);
void apaga_lista_ord(bloco_hash_jogo *head_ord, bloco_hash_jogo *tail_ord ,char *nome);


/* funcoes auxliares das listas das equipas */
void guarda_lista_e(bloco_hash_equipa *head,equipa *e);
void guarda_ord_alfabetica(bloco_hash_equipa *lista, equipa *e);

#endif