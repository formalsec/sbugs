#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "item.h"


/* adiciona os dados de um novo jogo ao sistema */
void a_adicionaNovoJogo(lista_jogo * lst_jogo, Item ** hashtable_jogo, Item ** hashtable_equipa, int contador);

/* adicina uma nova equipa ao sistema */
Item * A_adicionaNovaEquipa(Item * head_equipa, Item ** hashtable, int contador);

/* lista todos os jogos existentes no sistema por ordem de introducao */
void l_listaTodosJogosPorOrdem(lista_jogo * lst_jogo, int contador);

/* procura um jogo no sistema dado um nome e dispoe todas as informacoes relativas ao mesmo */
void p_procuraJogo(Item ** hashtable, int contador);

/* procura uma equipa no sistema dado um nome e dispoe todas as informacoes relativas 'a mesma */
void P_procuraEquipa(Item ** hashtable, int contador);

/* remove um jogo do sistema dado um nome */
void r_apagaJogo(lista_jogo * lst_jogo, Item ** hashtable_jogo, Item ** hashtable_equipa, int contador);

/* altera a pontuacao de um jogo existente dado um nome e uma nova pontuacao */
void s_alteraPontuacao(Item ** hashtable_jogo, Item ** hashtable_equipa, int contador);

/* lista as equipas existentes no sistema com o maior numero de vitorias por ordem lexicografica */
void g_encontraEquipasMaisVitorias(Item * head_equipa, int contador);

