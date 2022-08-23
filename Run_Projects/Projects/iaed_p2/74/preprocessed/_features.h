#ifndef features_h
#define features_h

#include <stdio.h>
#include "lists.h"
#include "HashTable.h"

/*------------------------prototipos-------------------------------------*/

/*funcao que adiciona um novo jogo e que devolve o pointer da lista onde ficou,
 recebe o nome do jogo, os nomes da equipa 1 e 2 e o resultado que ficou*/
list *f_addgame(char *game_name,char *t1,char *t2,int s1,int s2,int nl,list *jogos);

/*funcao que imprime todos os jogo adiconados por ordem de introducao, recebe a lista de jogos*/
void print_games(list *jogos,int nl);

/*funcao adiciona equipa, recebe o nome da equipa a ser adicionada*/
void add_team(char *team_name,int nl);

/*funcao que imprime o jogo pedido, recebe o nome do jogo*/
void show_game(char *game_name,int nl);

/*funcao que elimina um jogo, recebe o nome do jogo e a lista do jogo*/
void delete_game(char *game_name,list *jogos, int nl);

/*funcao que altera o resultado de um jogo, recebe o nome do jogo e o novo resultado*/
void change_score(char *game_name,int s1, int s2,int nl);

/*funcao que imprime uma equipa e os seus jogos ganhos, recebe o nome da equipa*/
void search_team(char *equipa,int nl);

/*funcao que imprime as equipas com o maior numero de jogos ganhos*/
void best_teams(int nl);
#endif /* features_h */
