#include "constants.h"
#include "all.h"
#include "List.h"

#include <stdio.h>

/* funcao para calcular colisoes de uma dada tabela */
void collisions(link** h);

int main() {
	long int NL = 0;
	char c;
	list* game_list = create_list();		/* lista de todos os jogos */
	list* team_list = create_list();		/* lista de todas as equipas */

	while ((c = getchar()) != 'x') {
		NL++;
		switch (c) {

		case 'a':
			add_game(NL, game_list, team_list);
			break;

		case 'A':
			add_team(NL, team_list);
			break;

		case 'l':
			list_games(NL, game_list);
			break;

		case 'p':
			find_game(NL, game_list);
			break;

		case 'P':
			find_team(NL, team_list);
			break;

		case 'r':
			remove_game(NL, game_list);
			break;

		case 's':
			change_game(NL, game_list);
			break;

		case 'g':
			get_winners(NL, team_list);
			break;

		default:
			NL--;
			break;
		}
	}

	/*collisions(team_list->table);
	collisions(game_list->table);*/

	free_list(team_list);
	free_list(game_list);

	return 0;
}

void collisions(link** h) {
	int count = 0;
	int i;
	int max = 0;
	link* head;

	for (i = 0; i < HASH_SIZE; i++)

		/* se houver um elemento na posicao i,
		conta quantos mais elementos estao nessa posicao */

		if (h[i]) {
			int j = 0;
			head = h[i]->next;

			while (head) {
				count++; j++;
				head = head->next;
			}
			if (j > max) max = j;
		}

	printf("%d - %d\n", count, max);
}