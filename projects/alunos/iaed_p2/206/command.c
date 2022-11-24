#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* O tamanho do buffer para escrita e 1023 + \0 = 1024. */
#define MAXSTRINGSIZE 1024

#include "command.h"
#include "game.h"
#include "team.h"

void a_addNewGame(Game_List *GL, Game_Hashtable *GH, Team_Hashtable *TH, int n) {

	char buffer_name[MAXSTRINGSIZE], buffer_team1[MAXSTRINGSIZE], buffer_team2[MAXSTRINGSIZE];
	int score1, score2;

	Game new_game, existed_game;
	Team existed_team1, existed_team2;
	getchar();

	scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d", buffer_name, buffer_team1, buffer_team2, &score1, 
		&score2);

	if ((existed_game = search_game_hashtable(GH, buffer_name)) != NULL) {
		printf("%d Jogo existente.\n", n);
		return;
	}

	if ((existed_team1 = search_team_hashtable(TH, buffer_team1)) == NULL) {
		printf("%d Equipa inexistente.\n", n);
		return;
	}

	if ((existed_team2 = search_team_hashtable(TH, buffer_team2)) == NULL) {
		printf("%d Equipa inexistente.\n", n);
		return;
	}

	new_game = create_game(buffer_name, buffer_team1, buffer_team2, score1, score2);

	/* Apos criar o jogo, a sua referencia e adicionada na lista duplamente ligada e na 
	hashtable referentes a 'game'. */
	insert_game_hashtable(GH, new_game);
	add_last_game_list(GL, new_game);

	/* Atualiza o numero de vitorias da equipa vencedora. */
	if (score1 > score2) {
		existed_team1->winnings++;
	}

	if (score1 < score2) {
		existed_team2->winnings++;
	}
}

void A_addNewTeam(Team_List *TL, Team_Hashtable *TH, int n) {

	char buffer_name[MAXSTRINGSIZE];
	Team new_team, existed_team;
	getchar();

	scanf("%[^\n]", buffer_name);

	if ((existed_team = search_team_hashtable(TH, buffer_name)) != NULL) {
		printf("%d Equipa existente.\n", n);
		return;
	}

	new_team = create_team(buffer_name);

	/* Apos criar a equipa, a sua referencia e adicionada na lista duplamente ligada e na 
	hashtable referentes a 'team'. */
	insert_team_hashtable(TH, new_team);
	add_last_team_list(TL, new_team);
}

void l_printAllGames(Game_List *GL, int n) {

	/* A variavel auxiliar 'aux_game_node' percorre a lista duplamente ligada, do inicio ao fim. */
	Game_Node *aux_game_node = GL->head;

	/* Por cada iteracao, imprime o conteudo dessa posicao. */
	while (aux_game_node != NULL) {
		printf("%d %s %s %s %d %d\n", n, aux_game_node->game->name, aux_game_node->game->team1, 
			aux_game_node->game->team2, aux_game_node->game->score1, aux_game_node->game->score2);

		/* Avanca para o elemento seguinte. */
		aux_game_node = aux_game_node->next;
	}
}

void p_searchGame(Game_Hashtable *GH, int n) {

	char buffer_name[MAXSTRINGSIZE];
	Game existed_game;
	getchar();

	scanf("%[^\n]", buffer_name);

	if ((existed_game = search_game_hashtable(GH, buffer_name)) == NULL) {
		printf("%d Jogo inexistente.\n", n);
		return;
	}
	printf("%d %s %s %s %d %d\n", n, existed_game->name, existed_game->team1, existed_game->team2, 
		existed_game->score1, existed_game->score2);
}

void P_searchTeam(Team_Hashtable *TH, int n) {

	char buffer_name[MAXSTRINGSIZE];
	Team existed_team;
	getchar();

	scanf("%[^\n]", buffer_name);

	if ((existed_team = search_team_hashtable(TH, buffer_name)) == NULL) {
		printf("%d Equipa inexistente.\n", n);
		return;
	}
	printf("%d %s %d\n", n, existed_team->name, existed_team->winnings);
}

void r_deleteGame(Game_List *GL, Game_Hashtable *GH, Team_Hashtable *TH, int n) {

	char buffer_name[MAXSTRINGSIZE];
	int old_score1, old_score2;
	Game existed_game;
	Team existed_team1, existed_team2;
	getchar();

	scanf("%[^\n]", buffer_name);

	if ((existed_game = search_game_hashtable(GH, buffer_name)) == NULL) {
		printf("%d Jogo inexistente.\n", n);
		return;
	}

	old_score1 = existed_game->score1;
	old_score2 = existed_game->score2;

	existed_team1 = search_team_hashtable(TH, existed_game->team1);
	existed_team2 = search_team_hashtable(TH, existed_game->team2);

	if (old_score1 < old_score2) {
		existed_team2->winnings--;
	}

	if (old_score1 > old_score2) {
		existed_team1->winnings--;
	}

	/* A referencia para o 'existed_game' e removida da lista duplamente ligada e da hashtable 
	referentes a 'game'. */

	remove_game_list(GL, existed_game->name);
	remove_game_hashtable(GH, existed_game->name);
}

void s_changeGameScore(Game_Hashtable *GH, Team_Hashtable *TH, int n) {

	char buffer_name[MAXSTRINGSIZE];
	int new_score1, new_score2, old_score1, old_score2;
	Game existed_game;
	Team existed_team1, existed_team2;
	getchar();

	scanf("%[^:\n]:%d:%d", buffer_name, &new_score1, &new_score2);

	if ((existed_game = search_game_hashtable(GH, buffer_name)) == NULL) {
		printf("%d Jogo inexistente.\n", n);
		return;
	}

	existed_team1 = search_team_hashtable(TH, existed_game->team1);
	existed_team2 = search_team_hashtable(TH, existed_game->team2);

	old_score1 = existed_game->score1;
	old_score2 = existed_game->score2;

	if ((old_score1 < old_score2) && (new_score1 > new_score2)) {

		existed_team1->winnings++;
		existed_team2->winnings--;

	} else if ((old_score1 > old_score2) && (new_score1 < new_score2)) {

		existed_team1->winnings--;
		existed_team2->winnings++;

	} else if ((old_score1 == old_score2) && (new_score1 > new_score2)) {

		existed_team1->winnings++;

	} else if ((old_score1 == old_score2) && (new_score1 < new_score2)) {

		existed_team2->winnings++;

	} else if ((old_score1 < old_score2) && (new_score1 == new_score2)) {

		existed_team2->winnings--;

	} else if ((old_score1 > old_score2) && (new_score1 == new_score2)) {

		existed_team1->winnings--;
	}

	existed_game->score1 = new_score1;
	existed_game->score2 = new_score2;
}

void g_findWinners(Team_List *TL, int n) {

	int i = 0, k, j, number_of_teams, more_winnings = 0, team_count = length_team_list(TL);
	Team *winners, aux_team;
	Team_Node *aux_team_node, *aux_team_node2;

	/* A variavel 'winners' representa um vetor que armazenara ponteiros para estruturas do tipo 
	'team' em cada posicao. */
	winners = can_fail_malloc(sizeof(int) * team_count);
	aux_team_node = TL->head;
	aux_team_node2 = TL->head;

	/* Procura a equipa que tem mais vitorias, e guarda esse valor na variavel 'more_winnings'. */
	while (aux_team_node != NULL) {

		if (aux_team_node->team->winnings >= more_winnings) {
			more_winnings = aux_team_node->team->winnings;
			aux_team_node = aux_team_node->next;

		} else {
			aux_team_node = aux_team_node->next;
		}
	}

	/* Adiciona em cada posicao de 'winners' a referencia para a equipa que tiver esse numero de 
	vitorias.*/
	while (aux_team_node2 != NULL) {

		if (aux_team_node2->team->winnings == more_winnings) {

			winners[i] = aux_team_node2->team;
			i++;
			aux_team_node2 = aux_team_node2->next;

		} else {
			aux_team_node2 = aux_team_node2->next;
		}
	}

	/* A variavel 'number_of_teams' contabiliza o numero total de equipas que estao em 'winners'. 
	*/
	number_of_teams = i;

	/* Organiza o vetor 'winners' por ordem lexicografica do nome da equipa. */
	for (j = 0; j < number_of_teams; j++) {
		for (k = j; k < number_of_teams; k++) {
			if (strcmp(winners[j]->name, winners[k]->name) > 0) {
				aux_team = winners[j];
				winners[j] = winners[k];
				winners[k] = aux_team;
			}
		}
	}

	if (number_of_teams != 0) {
		printf("%d Melhores %d\n", n, more_winnings);

		for (j = 0; j < number_of_teams; j++) {
			printf("%d * %s\n", n, winners[j]->name);
		}
	}

	/* Liberta o espaco da memoria ocupada pelo vetor, uma vez utilizado. */
	free(winners);

	return;
}

void x_exitApp(Team_List *TL, Team_Hashtable *TH, Game_List *GL, Game_Hashtable *GH) {

	free_teams_list(TL);
	free_games_list(GL);
	free_teams_hashtable(TH);
	free_games_hashtable(GH);
	return;
}