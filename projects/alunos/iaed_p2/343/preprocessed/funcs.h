#include "jogos.h"
#include "nodes.h"
#include "hash.h"

#ifndef FUNCS_H
#define FUNCS_H
#define MDES 1024

void sub_score(jg *jogo);
void acommand(int nl, node_jg *table_jg, node_eq *table_eq, link *lista);
void Acommand(int nl, node_eq *table_eq, node_eq *lista_eq);
void gcommand(int nl, node_eq *lista_eq);
void lcommand(int nl, link *lista);
void pcommand(int nl, node_jg *table_jg);
void Pcommand(int nl, node_eq *table_eq);
void rcommand(int nl, node_jg *table_jg, link *lista);
void scommand(int nl, node_jg *table_jg);
void xcommand(node_eq *table_eq, node_eq *lista_eq, node_jg *table_jg, link *lista);

#endif