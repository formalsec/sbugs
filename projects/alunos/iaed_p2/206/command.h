#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "game_double_linked_list.h"
#include "game_hashtable.h"
#include "team_double_linked_list.h"
#include "team_hashtable.h"

/* As seguintes funcoes representam um comando diferente. Em cada funcao serao recebidos os 
parametros de  acordo com a sua especificacao, uma vez que nao e viavel o uso de variaveis 
globais. */

/* 
Comando a: adiciona um novo jogo.
Cria um jogo apos verificar as condicoes de existencia para o jogo e a cada uma das equipas, i.e. 
nao haver nenhum jogo com o mesmo nome e o nome das duas equipas ja existir no sistema 
simultaneamente. 
Posteriormente, a referencia para o jogo e adicionado a lista duplamente ligada e a hashtable 
relativas a 'game'.
Retorno: vazio.
*/
void a_addNewGame(Game_List *GL, Game_Hashtable *GH, Team_Hashtable *TH, int n);


/*
Comando A: adiciona uma nova equipa.
A equipa e criada caso satisfaca as condicoes de existencia, i.e, nao haver ainda nenhuma equipa
no sistema com o mesmo nome. De seguida, a sua referencia e adicionada a lista duplamente ligada
e a hashtable relativas a 'team'.
Retorno: vazio.
*/
void A_addNewTeam(Team_List *TL, Team_Hashtable *TH, int n);


/*
Comando l: lista todos os jogos pela ordem em que foram introduzidos.
Os jogos sao listados por ordem de insercao. Esta ordem e preservada na lista duplamente ligada
relativa a 'game'. A informacao apresentada tem a forma: game:team1:team2:score1:score2.
Retorno: vazio.
*/
void l_printAllGames(Game_List *GL, int n);


/*
Comando p: procura um jogo com o nome dado.
Procura o nome do jogo na hashtable relativa a este. 
A informacao apresentada tem a forma: game:team1:team2:score1:score2.
Apresenta um erro caso o jogo nao existir.
Retorno: vazio.
*/
void p_searchGame(Game_Hashtable *GH, int n);


/*
Comando P: procura uma equipa com o nome dado.
Procura o nome da equipa na hashtable relativa a esta. 
A informacao apresentada tem a forma: team:numero_de_jogos_ganhos.
Apresenta um erro caso a equipa nao existir.
Retorno: vazio.
*/
void P_searchTeam(Team_Hashtable *TH, int n);


/*
Comando r: apaga um jogo com o nome dado.
Apos verificar a existencia do jogo, a referencia para o jogo e removido da lista duplamente ligada
e da hashtable relativas a 'game'. As equipas envolventes nesse jogo sao atualizadas quanto ao
numero de jogos ganhos.
Retorno: vazio.
*/
void r_deleteGame(Game_List *GL, Game_Hashtable *GH, Team_Hashtable *TH, int n);


/*
Comando s: altera a pontuacao do jogo com o nome dado.
Verifica se o jogo dado pelo nome existe no sistema. De seguida, atualiza o numero de jogos ganhos
das equipas envolvidas no jogo de acordo com a nova pontuacao e substitui a pontuacao antiga do
jogo pela nova.
Retorno: vazio.
*/
void s_changeGameScore(Game_Hashtable *GH, Team_Hashtable *TH, int n);


/*
Comando g: encontra as equipas que ganharam mais jogos e lista por ordem lexicografica do nome da 
equipa.
A equipa que tem mais vitorias e procurada na lista duplamente ligada relativa a 'team', guardando
este valor numa variavel e comparando com as vitorias das demais equipas. As equipas com o mesmo
numero de vitorias sao organizadas por ordem lexicofrafica do seu nome.
A informacao apresentada tem a forma: 
Melhores numero-de-jogos-ganhos
* team1
* team2
* team3
* ...
Retorno: vazio.
*/
void g_findWinners(Team_List *TL, int n);


/*
Comando x: termina o programa.
O programa e terminado libertando a memoria previamente alocada para as hashtables e listas 
duplamente ligadas relativas a 'team' e 'game'.
Retorno: vazio.
*/
void x_exitApp(Team_List *TL, Team_Hashtable *TH, Game_List *GL, Game_Hashtable *GH);

#endif