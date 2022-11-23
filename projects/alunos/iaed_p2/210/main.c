#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include "comandos.h"


int main() {
	char c, string1[MAX_STRINGS], string2[MAX_STRINGS], string3[MAX_STRINGS];
	unsigned int score1, score2;
	int NL = UM;

	/* Inicialization of the hash tables and lists used for the teams and games */
	init();

	while(UM) {
		switch(c = getchar()) {
			case 'a':
				scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%u:%u", string1, string2, string3, &score1, &score2);
				add_game(string1, NL, string2, string3, score1, score2);
				NL++;
				break;
			case 'A':
				scanf(" %[^:\n]", string1);
				add_team(string1, NL);
				NL++;
				break;
			case 'l':
				print_games(NL);
				NL++;
				break;
			case 'p':
				scanf(" %[^:\n]", string1);
				printf("%d ", NL);
				search_game(string1);
				NL++;
				break;
			case 'P':
				scanf(" %[^:\n]", string1);
				printf("%d ", NL);
				search_team(string1);
				NL++;
				break;
			case 'r':
				scanf(" %[^:\n]", string1);
				delete_game(string1, NL);
				NL++;
				break;
			case 's':
				scanf(" %[^:\n]:%u:%u", string1, &score1, &score2);
				change_score(string1, score1, score2, NL);
				NL++;
				break;
			case 'g':
				print_teams(NL);
				NL++;
				break;
			case 'x':
				free_all();
				return EXIT_SUCCESS;
			default:
				printf("Erro: Comando desconhecido\n");
		}
		getchar();
	}
	return EXIT_FAILURE;
}