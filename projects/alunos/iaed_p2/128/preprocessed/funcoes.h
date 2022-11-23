#ifndef _FUNCOES_
#define _FUNCOES_

#define MAX_LETRAS 1024
#include "equipas.h"
#include "lista_char.h"
#include "jogos.h"

void adiciona_equipa(link* heads,int n_linha);
void devolve_equipa(link*heads,int n_linha);
void equipas_mais_vitorias(link*heads,int M,int n_linha);
void adiciona_jogo(limites_lista* lista,link_jogo* heads_jogos,link*heads,int n_linha);
void print_jogos(limites_lista* lista,int n_linha);
void devolve_jogo(link_jogo*heads,int n_linha);
void altera_score(link_jogo* heads_jogos,int n_linha);
void destroi_tudo(link_jogo* head_jogos,limites_lista* lista, link*heads,int M,int n);
void apaga_jogo(link_jogo* head_jogos,limites_lista* lista,int n_linha);




#endif