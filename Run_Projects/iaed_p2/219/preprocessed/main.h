#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#include "hash.h"

/**
 * Adiciona um novo jogo a lista de jogos
 * @param lista_jogos *l_jogos - lista de jogos onde se guarda o jogo
 * @param char *nome - nome do jogo que queremos adicionar
 * @param char *equipa1 - nome da 1 equipa do jogo
 * @param char *equipa2 - nome da 2 equipa do jogo
 * @param char *score1 - pontuacao da 1 equipa
 * @param char *score2 - pontuacao da 2 equipa
 */
void comando_a(lista_jogos *l_jogos, char *nome, char *equipa1, char *equipa2, char* score1, char *score2);

/**
 * Le o comando e encaminha para a funcao correspondente
 * @param lista_equipas *l_equipas - lista de equipas
 * @param lista_jogos *l_jogos - lista de jogos
 * @return char comando
 */
char le_comandos (lista_equipas *l_equipas, lista_jogos *l_jogos);

/**
 * Adiciona uma nova equipa a lista de equipas
 * @param lista_equipas *l_equipas - lista de equipas onde se guarda a equipa
 * @param char *nome - nome da equipa que queremos adicionar
 */
void comando_A(lista_equipas *l_equipas, char *nome);

/**
 * Lista todos os jogos pela ordem em que foram introduzidos
 * @param lista_jogos *l_jogos - lista de jogos
 */
void comando_l(lista_jogos *l_jogos);

/**
 * Procura um jogo dado um nome
 * @param char *nome - nome do jogo que procuramos
 */
void comando_p(char *nome);

/**
 * Altera o score de um jogo 
 * @param char *nome - nome do jogo cujo score vamos alterar
 * @param char *novo_score1 - novo score1
 * @param char *novo_score2 - novo score2
 */
void comando_s(char *nome, char *novo_score1, char *novo_score2);

/**
 * Apaga um jogo dado um nome
 * @param lista_jogos *l_jogos - lista de jogos
 * @param char *nome - nome do jogo que queremos retirar
 */
void comando_r(lista_jogos *l_jogos, char *nome);

/**
 * Procura uma equipa dado um nome
 * @param char *nome - nome da equipa que procuramos
 */
void comando_P(char *nome);

/**
 * Encontra as equipas que venceram mais jogos 
 * @param lista_equipas *l_equipas - lista com equipas
 */
int comando_g(lista_equipas *l_equipas);

/**
 *Funcao auxiliar a funcao comando_g
 * @param lista_equipas *l_equipas - lista com equipas
 * @param int ganhostotal - numero maximo de jogos ganhos
 */
void aux_g(lista_equipas *l_equipas, int ganhostotal);


