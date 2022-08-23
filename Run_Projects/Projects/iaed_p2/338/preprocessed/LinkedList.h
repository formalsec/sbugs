#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "structs.h"
#include "Hash.h"

node append(char game[],node Head);
void display(int contalinhas,int tblsz_jogo,node Head, jogo*st);
void display2(int contalinhas,int tblsz_jogo,node Head, equipa *eq);
tuplio get_max_vit(node Head,int tblsz, equipa *eq, tuplio tuplo);
node delete_node(char *nome, node Head);
void obtem_equipas_com_max_vit(node Head, int max_vitorias, char**equipa_c_vitorias,int tblsz, equipa *eq);
#endif