#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "teamHTable.h"
#include "gameHTable.h"

#define NOT_SUCESSFUL 0/*se o comando nao e executado*/
#define SUCESSFUL 1	   /*se o comando e executado*/

int cmd_a(int NL, glink ** HTgame, tlink ** HTteams, glink ** STgame, int counter_game);
int cmd_A(int NL, tlink ** HTteams);
void cmd_p(int NL, glink **HTgame);
void cmd_P(int NL, tlink **HTteams);
void cmd_l(glink ** STgame, int NL, int counter_game);
int cmd_r(int NL, glink ** STgame, glink ** HTgame, int counter_game);
void cmd_s(int NL, glink ** HTgame, tlink ** HTteams);
pTeam ** cmd_g(int NL, pTeam ** STteams, int counter_team, tlink ** HTteams);

/*-------------------------------------------------------------------\
| Comando a													   
| Le nome, duas equipas e dois scores de um novo jogo.
| Insere o jogo na hashtable, bem como na lista p/ordem insercao 
| Se o jogo existir, ou a equipa nao existir no sistema, reporta erro.
\--------------------------------------------------------------------*/
int cmd_a(int NL, glink ** HTgame, tlink ** HTteams, glink ** STgame, int counter_game){

	char buffer0[MAX], buffer1[MAX], buffer2[MAX];
	int res1, res2;
	glink * link = can_fail_malloc(sizeof(struct node_game));

	if (scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",
			buffer0, buffer1, buffer2, &res1, &res2) != 5){
		printf("argumentos invalidos a.\n");
		return NOT_SUCESSFUL;
	}
	if(verifica_jogo(buffer0, buffer1, buffer2, HTgame, HTteams) 
		== EXISTE_JOGO){
		printf("%d Jogo existente.\n", NL);
		return NOT_SUCESSFUL;
	}
	if(verifica_jogo(buffer0, buffer1, buffer2, HTgame, HTteams) 
		== NAO_EXISTE_EQUIPA){
		printf("%d Equipa inexistente.\n", NL);
		return NOT_SUCESSFUL;
	}
	else if( verifica_jogo(buffer0, buffer1, buffer2, HTgame, HTteams) 
		== INPUT_OK){
			link = glinkInsert(buffer0, buffer1, buffer2, res1, res2, link, HTgame, 
								HTteams);
			gorderInsert(&link, STgame, counter_game);
		return SUCESSFUL;
		/*printGame(linkord->g);
		printf("main a -> %s\n", link->g->name);*/
	}
	return SUCESSFUL;
}

/*-------------------------------------------------------------------\
| Comando A													   
| Le nome de uma nova equipa.
| Insere a equipa na hashtable, bem como na lista p/ordem insercao 
| Se a equipa ja existir no sistema, reporta erro.
\--------------------------------------------------------------------*/
int cmd_A(int NL, tlink ** HTteams){

	char buffer0[MAX];
	tlink * link = can_fail_malloc(sizeof(struct node_team));
	
	if (scanf(" %[^:\n]",buffer0) != 1){
		printf("argumentos invalidos A.\n");
		return NOT_SUCESSFUL;
	}
	else if(tLinkInsert(buffer0,link, HTteams) == NULL){
		printf("%d Equipa existente.\n", NL); 
		return NOT_SUCESSFUL;
	}
	else{
		link = tLinkInsert(buffer0,link, HTteams);
		return SUCESSFUL;
	}
}

/*-------------------------------------------------------------------\
| Comando p													   
| Le nome, e procura o jogo correspondente.
| Se o jogo nao existir no sistema, reporta erro.
\--------------------------------------------------------------------*/
void cmd_p(int NL, glink **HTgame){
	char buffer0[MAX], *name;
	pGame * jogo = can_fail_malloc(sizeof(struct game));

	if(scanf(" %[^:\n]", buffer0) != 1){
		err("Argumentos invalidos.");
	}
	else if((search_game(HTgame, buffer0)) == NULL){
		printf("%d Jogo inexistente.\n", NL);
	}
	else{
		name = my_strdup(buffer0);
		jogo = search_game(HTgame, name)->g;
		printf("%d %s %s %s %d %d\n", NL, jogo->name, jogo->team1->name, 
		jogo->team2->name, jogo->score1, jogo->score2);
	}
}

/*-------------------------------------------------------------------\
| Comando P													   
| Le nome, e procura a equipa correspondente..
| Se a equipa nao existir no sistema, reporta erro.
\--------------------------------------------------------------------*/
void cmd_P(int NL, tlink **HTteams){
	char buffer0[MAX], *name;
	pTeam * equipa = can_fail_malloc(sizeof(struct team));
	
	if(scanf(" %[^:\n]", buffer0) != 1){
		err("Argumentos invalidos");
	}
	else if((search_team(HTteams, buffer0)) == NULL){
		printf("%d Equipa inexistente.\n", NL);
	}
	else{
		name = my_strdup(buffer0);
		equipa = search_team(HTteams, name)->t;
		printf("%d %s %d\n", NL, equipa->name, equipa->wins);
	}
}

/*-------------------------------------------------------------------\
| Comando l													   
| Lista todos os jogos no sistema, pela sua ordem de insercao.
| Se nenhum jogo existir, nao imprime nada.
\--------------------------------------------------------------------*/
void cmd_l(glink ** STgame, int NL, int counter_game){
	int i=0;
	for(i=0; i < counter_game; i++){
		if(STgame[i] != NULL){
		printf("%d %s %s %s %d %d\n", NL, 
			STgame[i]->g->name, STgame[i]->g->team1->name, 
			STgame[i]->g->team2->name, STgame[i]->g->score1, STgame[i]->g->score2);
		}
	}
}

/*-------------------------------------------------------------------\
| Comando r													   
| Le nome, e remove o jogo correspondente.
| Se o jogo nao existir no sistema, reporta erro.
\--------------------------------------------------------------------*/
int cmd_r(int NL, glink ** STgame, glink ** HTgame, int counter_game){
	char buffer0[MAX];
	if(scanf(" %[^:\n]", buffer0) != 1){
		err("Argumentos invalidos.");
		return NOT_SUCESSFUL;
	}
	else if((search_game(HTgame, buffer0)) == NULL){
		printf("%d Jogo inexistente.\n", NL);
		return NOT_SUCESSFUL;
	}
	else{
		
		STgame = gorderRemove(buffer0, STgame, counter_game);
		/*printf("r - %d contador de jogos.\n", contador);*/
		glinkRemove(buffer0, HTgame);
		/*removo o jogo da lista ordenada, pois esta lista aponta para o jogo da hash*/
		
		/*removo o jogo da minha hashtable*/
		return SUCESSFUL;
	}

}

/*-------------------------------------------------------------------\
| Comando s													   
| Le nome e dois scores, e altera a pontuacao do jogo correspondente.
| Se o jogo nao existir no sistema, reporta erro.
\--------------------------------------------------------------------*/
void cmd_s(int NL, glink ** HTgame, tlink ** HTteams){
	char buffer0[MAX];
	int res1, res2;
	if(scanf(" %[^:\n]:%d:%d", buffer0, &res1, &res2) != 3){
		err("Argumentos invalidos.");
	}
	else if((search_game(HTgame, buffer0)) == NULL){
		printf("%d Jogo inexistente.\n", NL);
	}
	else{
		gchangeScore(buffer0, res1, res2, HTgame, HTteams);
	}
}

/*-------------------------------------------------------------------\
| Comando g													   
| Encontra as equipas no sistema que ganharam mais jogos e lista por 
| ordem lexicografica - do nome da equipa.
| Se nao existir nenhuma equipa no sistema, nao retorna nada.
\--------------------------------------------------------------------*/
pTeam ** cmd_g(int NL, pTeam ** STteams, int counter_team, tlink ** HTteams){
	int i, soma=0;
	if(teamisEmpty(HTteams)){
		return NULL;
	}
	else{
		/*crio uma lista de equipas, com o tamanho do numero de equipas
		que existem no sistema*/
		if(counter_team == 1)
			STteams = team_array(counter_team);
		STteams = search_el(STteams, HTteams, counter_team);
		

		/*reorganizo wins por ordem lexicografica
		final = abc_winners(wins, counter_team);*/
		for(i = 0; i < counter_team; i++){
			if(STteams[i]!= NULL){
				if(STteams[i]->wins > soma)
					soma = STteams[i]->wins;
			}
		}
		printf("%d Melhores %d\n", NL, soma);
		STteams = abc_winners(STteams, counter_team);
		for(i = 0; i < counter_team; i++){
			if(STteams[i]!= NULL){
				if(counter_team > 1){
					if(STteams[i]->wins >= soma)
						printf("%d * %s\n", NL, STteams[i]->name);
				}
				else{
					printf("%d * %s\n", NL, STteams[i]->name);
				}
			}


		}
	}
	return STteams;
}

int main(){
	char command;
	int counter_game=0;/*contador de jogos*/
	int counter_team=0;/*contador equipas*/
	int NL = 0; 	   /*numero do input*/
	glink ** HTgame=NULL;
	tlink ** HTteams=NULL;
	glink ** STgame=NULL;
	pTeam ** STteams = NULL;

	/*inicializo as minhas hashtables dos jogos e equipas*/
	HTgame = init_HTgame(SIZE*2);
	HTteams = init_HTteams(SIZE*2);
	/*inicializo a lista de ordem dos jogos*/
	STgame = init_STgame(SIZE*2);

	while(1){
		command = getchar();
		switch(command){
			case'a':/*adiciona um novo jogo*/
				++NL;
				if (cmd_a(NL, HTgame, HTteams, STgame, counter_game) == SUCESSFUL)
					++counter_game;
				if(counter_game > SIZE/2)
					HTgame = expand(HTgame, SIZE*4);
				if(counter_game > SIZE*2)
					STgame = simplexpand(STgame, SIZE*4);
				break;
			case'A':/*adicona uma nova equipa*/
				++NL;
				if (cmd_A(NL, HTteams) == SUCESSFUL)
					++counter_team;
				if(counter_team > SIZE/2)
					HTteams = texpand(HTteams, SIZE*4);
				break;
			case'l':/*lista todos os jogos introduzidos*/
				++NL; cmd_l(STgame, NL, counter_game); break;
			case'p':/*procura um jogo*/
				++NL; cmd_p(NL, HTgame); break;
			case'P':/*procura uma equipa*/
				++NL; cmd_P(NL, HTteams); break;
			
			case 'r':/*apaga um jogo dado um nome*/
				++NL;
				if (cmd_r(NL, STgame, HTgame, counter_game) == SUCESSFUL)
					--counter_game;
				break;	
			case 's':/*altera o score de um jogo dado o nome*/
				++NL; cmd_s(NL, HTgame, HTteams); break;
			case 'g':/*encontra as equipas que venceram mais jogos*/
				++NL;
				cmd_g(NL, STteams, counter_team, HTteams);
				break;
			case 'x':/*termina o programa*/
				return EXIT_SUCCESS;
			default:
				err("comando desconhecido");
			}	
			getchar();
		}
		free_gTable(*HTgame);
		free_gTable(*STgame);
		free(STteams);
		free(STgame);
		free(HTgame);
		free(HTteams);
	return EXIT_SUCCESS;
}
