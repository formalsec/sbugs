#ifndef STRUCTURES_H
#define STRUCTURES_H

#define TABLE_SIZE 1997
#define MAX_INPUT 1024

/****************************************************************************************/
/*	stru_team e uma estrutura do tipo team, que contem a informacao de cada equipa.  	*/
/*  Esta estrutura possui os seguintes componentes:        								*/
/*		name 		(nome da equipa);													*/
/*      wins        (numero de vitorias da equipa)                                      */
/*		next 		(aponta para a proxima equipa);         							*/
/****************************************************************************************/
typedef struct stru_team{
    char *name;
    int wins;
    struct stru_team *next;
} team;


/****************************************************************************************/
/*	stru_game e uma estrutura do tipo game, que contem a informacao de cada jogo.   	*/
/*  Esta estrutura possui os seguintes componentes:										*/
/*		name 		(nome do jogo);			    										*/
/*		t1 		    (nome da primeira equipa);											*/
/*		t2 	        (nome da seguna equipa);    										*/
/*		g_t1        (golos da primeira equipa);	                            			*/
/*		g_t2        (golos da segunda equipa);                              			*/
/*		next        (aponta para o proximo jogo);       								*/
/****************************************************************************************/
typedef struct stru_game{
    char *name;
    char *t1;
    char *t2;
    int g_t1;
    int g_t2;
    struct stru_game *next;
} game;


/****************************************************************************************/
/*	node_game e uma lista duplamente ligada que guarda ponteiros para jogos a medida    */
/*  que estes sao introduzidos.	                                                        */
/*	Esta estrutura possui os seguintes componentes:										*/
/*		Game		(ponteiro que aponta para um jogo);								    */
/*		next		(aponta para o proximo jogo);                               		*/
/*		prev 		(aponta para o jogo anterior);                              		*/
/****************************************************************************************/
typedef struct node_game{
    game* Game;
    struct node_game *next, *prev;
} nodeGame;

#endif