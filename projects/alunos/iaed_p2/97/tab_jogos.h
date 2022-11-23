#ifndef TAB_JOGOS
#define TAB_JOGOS

#include "LDL_jogos.h"

/* Tamanho da tabela de dispersao para os jogos */
#define TAB_JOGO 1049

/* Cria a tabela de dispersao para os jogos */
lista** incializa_tabela_jogo();

/* Corresponde a funcao encontra_jogo_lista, para a tabela de dispersao */
elem_j* encontra_jogo_tabela(lista **tab_jogos, char *nome);

/* Insere o Item_j el na tabela de dispersao */
lista** insere_jogo_tabela(lista **tab_jogos, Item_j *el);

/* Apaga o elem_j el (onde esta o jogo) da tabela de dispersao */
lista** remove_jogo_tabela(lista **tab_jogos, elem_j *el);

/* Apaga toda a tabela de dispersao e memoria associada */
void apaga_tabela_jogos(lista **tab_jogos);

#endif