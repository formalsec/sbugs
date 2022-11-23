#ifndef GAMEHTTABLE_H
#define GAMEHTTABLE_H
#define SIZE 9677 		/*numero primo - tamanho da hashtable*/

#define Key(a) (a->name)
#define NULLitem (NULL)
#define EXISTE_JOGO 1
#define EXISTE_EQUIPA 2
#define NAO_EXISTE_JOGO 3
#define NAO_EXISTE_EQUIPA 4
#define INPUT_OK 5

#include "teamHTable.h"

/*------------------------------------------------------------------------
| Estrutura 		game 												  
|																		  
| caracterizada por|													  
| 	.name          |string nao vazia, max 1023 caracteres
| 	.pTeam 1 e 2   |estruturas team - as equipas que participam no jogo
|				   |par de strings nao vazias, max 1023 caracteres cada
| 	.score 1 e 2   |par de inteiros > 0, representam o resultado do jogo					  		   
--------------------------------------------------------------------------*/
typedef struct game{
	char * name;
	pTeam * team1;
	pTeam * team2;
	int score1;
	int score2;
}pGame; /*pGame e um pointer para uma struct game*/

/*------------------------------------------------------------------------
| Estrutura 		node_gome												  
|				   |no da minha hashtable de jogos- game											  
| caracterizada por|													  
| 	.g       	   |ponteiro pGame para o jogo g - estrutura game				  		   
--------------------------------------------------------------------------*/
typedef struct node_game{
	pGame * g;
}glink; /*glink e um pointer para uma struct node_game*/


glink ** init_HTgame(int number);
glink ** init_STgame(int number);
glink**  expand(glink ** HTgame, int number);
glink ** simplexpand(glink ** STgame, int number);
pGame * create_game(char * buffer0, char* buffer1, char * buffer2, int res1, int res2,
	tlink ** HTteams);
glink ** gorderInsert(glink ** link, glink ** STgame, int count);
glink ** gorderRemove(char * buffer0, glink ** STgame,int counter_game);
glink * glinkInsert(char * buffer0, char* buffer1, char * buffer2, int res1, int res2,
	glink * link, glink ** HTgame, tlink ** HTteams);
glink * gsimplyInsert(glink * link, glink ** HTgame);
void glinkRemove(char * buffer0, glink ** HTgame);
glink * search_game(glink ** HTgame, char *nome);
glink * gchangeScore(char * buffer0, int res1, int res2, glink ** HTgame, tlink ** HTteams);
int verifica_jogo(char * buffer0, char* buffer1, char * buffer2,
	glink ** HTgame, tlink **HTteams);
bool isEmpty(glink ** HTgame);
void gameFree(pGame * g);
void free_gTable(glink * gtable);


#endif
