#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "main.h"

/*
 * Adiciona uma nova equipa "A"
 */
Teams * add_new_team(Teams * teams, char* buffer) {
	if(team_exists(&teams, buffer)) {
		printf("%d Equipa existente.\n", nl);
	} else {
		teams = add_team_to_list(&teams, buffer);
	}
	return teams;
}

/*
 * Adiciona um jogo novo "a"
 */
Matches * add_new_match(Matches * matches, char* buffer) {
	char *m_name, *team1, *team2;
	int score1, score2;

	m_name = can_fail_malloc(MAX_BUFF);
	team1 = can_fail_malloc(MAX_BUFF);
	team2 = can_fail_malloc(MAX_BUFF);

	strcpy(m_name, strtok(buffer, ":"));
	strcpy(team1, strtok(NULL, ":"));
	strcpy(team2, strtok(NULL, ":"));
	score1 = atoi(strtok(NULL, ":"));
	score2 = atoi(strtok(NULL, ":"));

	if (match_exists(&matches, m_name))	{
		printf("%d Jogo existente.\n", nl);
	} else if (!team_exists(&teams, team1) || !team_exists(&teams, team2)) {
		printf("%d Equipa inexistente.\n", nl);
	} else {
		matches = add_match_to_list(&matches, m_name, team1, team2, score1, score2);
		if (score1 > score2) {
			teams = increment_matches_won(&teams, team1);
		} else if (score2 > score1) {
			teams = increment_matches_won(&teams, team2);
		}
	}

	free(m_name);
	free(team1);
	free(team2);
	return matches;
}

/*
 *  Lista todos os jogos introduzidos "l"
 */
void list_matches() {
	Matches * current = matches;

	while (current != NULL) {
    	printf("%d %s %s %s %d %d\n", nl,
    		current->match_name, 
    		current->team1, current->team2,
    		current->score1, current->score2);
        current = current->next;
    }
}

/*
 * Procura um jogo com o nome dado "p"
 */
void find_match(char* buffer) {
	if (match_exists(&matches, buffer))	{
		printf("%d", nl);
		print_match_found(&matches, buffer);
	} else {
		printf("%d Jogo inexistente.\n", nl);
	}
}

/*
 * Procura uma equipa dado um nome "P"
 */
void matches_won_team(char* buffer) {
	if (team_exists(&teams, buffer)) {
		printf("%d ", nl);
		print_matches_won(&teams, buffer);
	} else {
		printf("%d Equipa inexistente.\n", nl);
	}
}

/*
 * Altera o score de um jogo dado o nome "s"
 */
void change_match_score(char* buffer) {
	char *m_name = can_fail_malloc(MAX_BUFF);
	int new_s1, new_s2;

	strcpy(m_name, strtok(buffer, ":"));
	new_s1 = atoi(strtok(NULL, ":"));
	new_s2 = atoi(strtok(NULL, ":"));

	if (match_exists(&matches, buffer))	{
		Matches ** head = &matches;
		Matches * current;

	    for (current = *head; current != NULL; current = current->next) {
	        if (strcmp(current->match_name, m_name) == 0) {
	            current->score1 = new_s1;
            	current->score2 = new_s2;

            	if (new_s2 > new_s1 && current->winner == 1) { 
            		teams = increment_matches_won(&teams, current->team2);
					teams = decrement_matches_won(&teams, current->team1);
					current->winner = 2;
				}
	            if (new_s2 > new_s1 && current->winner == 0) { 
	            	teams = increment_matches_won(&teams, current->team2);
	            	current->winner = 2;
	            }
	            if (new_s2 < new_s1 && current->winner == 2) { 
	            	teams = increment_matches_won(&teams, current->team1);
					teams = decrement_matches_won(&teams, current->team2);
					current->winner = 1;
				}
	            if (new_s2 < new_s1 && current->winner == 0) { 
	            	teams = increment_matches_won(&teams, current->team1);
	            	current->winner = 1;
	            }
	            if (new_s2 == new_s1 && current->winner == 1) { 
	            	teams = decrement_matches_won(&teams, current->team1);
	            	current->winner = 0; 
	            }
	            if (new_s2 == new_s1 && current->winner == 2) { 
	            	teams = decrement_matches_won(&teams, current->team2);
	            	current->winner = 0; 
	            }
	        }
	    }
	} else {
		printf("%d Jogo inexistente.\n", nl);
	}
	free(m_name);
}

/*
 * Apaga um jogo dado um nome "r"
 */
void remove_match(char* buffer) {
	if (match_exists(&matches, buffer))	{
		Matches ** head = &matches;
		Matches * current;

		for (current = *head; current != NULL; current = current->next) {
	        if (strcmp(current->match_name, buffer) == 0) {
            	if (current->winner == 1) { 
					teams = decrement_matches_won(&teams, current->team1);
				}
	            if (current->winner == 2) { 
	            	teams = decrement_matches_won(&teams, current->team2);
	            }
	        }
	    }
		matches = delete_match_from_list(&matches, buffer);
	} else {
		printf("%d Jogo inexistente.\n", nl);
	}
}

/*
 * Encontra as equipas que ganharam mais jogos e lista por ordem lexicografica "g"
 */
void matches_won_highest() {
	if (teams) {
		struct Teams *teams_highest = NULL;
		Teams ** head;
		Teams * temp;
		int highest_won = max_won(&teams);
		int list_size, i;
		teams_highest = add_team_highest(&teams_highest, &teams, highest_won);
		list_size = get_list_size(teams_highest);

		for (i = 0; i < list_size; i++)		{
			sort_teams_alpha(&teams_highest);
		}
			
		head = &teams_highest;

	    for (temp = *head; temp != NULL; temp = temp->next) {
	        if (team_exists_match(&matches, temp->team_name)) {
	        	teams_highest = delete_team_from_list(&teams_highest, temp->team_name);
	        }
	    }

	    printf("%d Melhores %d\n", nl, highest_won);
		print_team_list(nl, teams_highest);
		free_teams(teams_highest);
	} else {
		return;
	}

}

int main() {
	char* tmp;
	char* scan = (char *)can_fail_malloc(MAX_TOTAL_BUFF*sizeof(char));
	teams = NULL;
	matches = NULL;

	while (1) {
		nl++;
		memset(scan, 0, MAX_TOTAL_BUFF);
		scanf(" %[^\n]", scan);
		/*printf("\t%d %s\n", nl, scan);*/
		switch (scan[0]) {
			case 'A':
				tmp = scan + 2;
				teams = add_new_team(teams, tmp);
				break;

			case 'a':
				tmp = scan + 2;
				matches = add_new_match(matches, tmp);
				break;

			case 'l':
				list_matches();
				break;

			case 'p':
				tmp = scan + 2;
				find_match(tmp);
				break;

			case 'P':
				tmp = scan + 2;
				matches_won_team(tmp);
				break;

			case 's':
				tmp = scan + 2;
				change_match_score(tmp);
				break;

			case 'g':
				matches_won_highest();
				break;

			case 'r':
				tmp = scan + 2;
				remove_match(tmp);
				break;

			case 'x':
				free_teams(teams);
				free_matches(matches);
				free(scan);
				return 0;

			default:
				break;
		}
	}
	return 0;
}
