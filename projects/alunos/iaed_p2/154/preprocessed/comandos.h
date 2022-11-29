#ifndef COMANDOS_H
#define COMANDOS_H

/* inclusao do header file necessario */
#include "structs.h"

/* comando a */
int existe_equipa(team_n **, char *);
void altera_numero_vitorias(team_n **, char *, bool);
game_n *a_adiciona_jogo(game_n **, team_n **, game_n *, int);

/* comando A */
team_n *A_adiciona_equipa(team_n **, team_n *, int);

/* comando l */
void l_lista_jogos(game_n *, int);

/* comando p */
void p_procura_jogo(game_n **, int);

/* comando P */
void P_procura_equipa(team_n **, int);

/* comando r */
game_n *apaga (game_n *, char *);
game_n *r_apaga_jogo(game_n **, team_n **, game_n *, int);

/* comando s */
void muda_scores(int, int, team_n **, game_n *, bool); 
void s_altera_score(game_n **, team_n **, int);

/* comando g */
int encontrar_maximo(team_n *);
int encontrar_numero_maximos(team_n *, int);
int comparar_strings(const void *, const void *);
void g_equipas_vencedoras(team_n *, int, int, int);

#endif