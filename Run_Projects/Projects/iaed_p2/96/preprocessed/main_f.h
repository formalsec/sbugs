#ifndef main_f_h
#define main_f_h
#include "main_aux.h"
#define Tamanho_max_letras 1043






/* funcoes do programa */
void A(bloco_hash_equipa *table_e,bloco_hash_equipa *lista_e, int NL);
void a(bloco_hash_jogo *table_j,bloco_hash_equipa *table_e,bloco_hash_jogo *lista_ord_h,
bloco_hash_jogo *lista_ord_t,int NL);
void P(bloco_hash_equipa *table_e, int NL);
void p(bloco_hash_jogo *table_j, int NL);
void s(bloco_hash_jogo *table_j, bloco_hash_equipa *table_e,int NL);
void r(bloco_hash_jogo *table_j,bloco_hash_jogo *lista_ord_h,bloco_hash_jogo *lista_ord_t,int NL);
void l(bloco_hash_jogo *head,int NL);
void g(bloco_hash_equipa *lista_e, int NL);
void x(bloco_hash_equipa *h_e, bloco_hash_equipa *l_e, bloco_hash_jogo *h_j, bloco_hash_jogo *l_j_h,
bloco_hash_jogo *l_j_t);

#endif