#ifndef _AUX_
#define _AUX_

#include <string.h>
#include "Estruturas.h"

/* Funcao que acerta as ligacoes prox e ant do jogo removido,
   bem como os conteudos de cab_j e fim_j */
void compensa_jogos(p_jogo jogo_apag, p_jogo *fim_j, p_jogo *cab_j);

/* Funcao que retorna o ponteiro do jogo chamado "nome" */
p_jogo existe_jogo(char *nome, p_jogo *tab_j);

/* Funcao que da uma vitoria a equipa chamada "nome" */
void aumenta_vitorias(char *nome, p_equipa *tab_e);

/* Funcao que remove uma vitoria da equipa chamda "nome" */
void remove_vitoria(char *nome, p_equipa *tab_e);

/* Funcao que verifica se alguma equipa ganhou o jogo  e adiciona a vitoria */
void ve_vitoria(p_jogo jogo, p_equipa *tab_e);

/* Funcao que verifica se alguma equipa ganhou o jogo e remove a vitoria */
void ve_derrota(p_jogo jogo, p_equipa *tab_e);

/* Funcao que da free a todos os jogos e a tabela que os contem */
void free_tabela_jogos(p_jogo *tab_j, p_jogo *cab_j);

/* Funcao que da free a todas as equipas e a tabela que as contem */
void free_tabela_equipas(p_equipa *tab_e, p_equipa *cab_e);

/* Verifica se a string b vem primeiro na ordem alfabetica do que a */
int alfabetico_equipas(const void *a, const void *b);

/* Funcao que retorna um ponteiro para strings criado com o tamanho necessario */
char* novo_nome(char nome[]);

/* Funcao que acerta as vitorias e ligacoes entre jogos apos a remocao de "jogo" */
void acerta_jogos(p_jogo jogo, p_equipa *tab_e, p_jogo *cab_j, p_jogo *fim_j);


#endif