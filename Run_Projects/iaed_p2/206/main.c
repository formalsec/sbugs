#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "command.h"
#include "function_hashtable.h"
#include "game_double_linked_list.h"
#include "game_hashtable.h"
#include "team_double_linked_list.h"
#include "team_hashtable.h"

int main() {

	/* A variavel 'n' auxulia na visualizacao dos outputs do programa. A variavel e incrementada de 
	1 aquando da chamada de alguma funcao. */
	int n = 1;
	/* A variavel 'command' faz corresponder a letra que correspondera a funcao a ser executada. */
	char command;
	/* Declaracao das listas duplamente ligadas e hashtables, que servirao para guardar os dados
	inseridos no programa. */
	Team_List *TL;
	Team_Hashtable *TH;
	Game_List *GL;
	Game_Hashtable *GH;

	/* Tanto as listas duplamente ligadas quanto as hashtables sao inicializadas aqui. */
	TL = init_team_list();
	TH = init_team_hashtable(HASHTABLE_STARTING_SIZE);
	GL = init_game_list();
	GH = init_game_hashtable(HASHTABLE_STARTING_SIZE);

	while (1) {

		command = getchar();
		switch(command) {

			case 'a':
				a_addNewGame(GL, GH, TH, n);
				n++;
				break;

			case 'A':
				A_addNewTeam(TL, TH, n);
				n++;
				break;

			case 'l':
				l_printAllGames(GL, n);
				n++;
				break;

			case 'p':
				p_searchGame(GH, n);
				n++;
				break;

			case 'P':
				P_searchTeam(TH, n);
				n++;
				break;

			case 'r':
				r_deleteGame(GL, GH, TH, n);
				n++;
				break;

			case 's':
				s_changeGameScore(GH, TH, n);
				n++;
				break;

			case 'g':
				g_findWinners(TL, n);
				n++;
				break;

			case 'x':
				x_exitApp(TL, TH, GL, GH);
				n++;
				return 0;

			default:
				printf("%c\n", command);
				puts ("Error: Invalid command.");
		}
		getchar();
	}
	return 1; /* O programa nao foi executado corretamente. */
}