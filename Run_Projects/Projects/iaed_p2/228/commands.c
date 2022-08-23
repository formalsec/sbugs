#include "commands.h"
#include "game.h"
#include "team.h"
int NL = 0;     /* counter for the inputs */


void cmd_a(ht *games,ht *teams) {
	/* buffers for handling user input */
	char name[NAME_DIM],team1name[NAME_DIM],team2name[NAME_DIM];
	int score_team1,score_team2;
	game *new_game;

	NL++;
	scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",name,team1name,team2name,&score_team1,&score_team2);
	if(find_in_ht(games,name)) {
		printf("%d Jogo existente.\n",NL);
		return;
	}
	if(!find_in_ht(teams,team1name)) {
		printf("%d Equipa inexistente.\n",NL);
		return;
	}
	if(!find_in_ht(teams,team2name)) {
		printf("%d Equipa inexistente.\n",NL);
		return;
	}
	
	new_game = create_game(name,team1name,team2name,score_team1,score_team2);
	add_to_ht(games,new_game);
	
	/* if the scores are different update the number of games won */
	if(score_team1 != score_team2){
		update_games_won(teams,team1name,team2name,score_team1,score_team2);
	}
}

void print_game(void *v) {
  game *g = v;

  printf("%d %s %s %s %d %d\n",NL,g->name,g->team1,g->team2,g->score1,g->score2);
}

void cmd_l(ht *games) { 
	NL++;

	apply_all_in_ht(games,print_game);
}

void cmd_A(ht *teams) {
	char name[NAME_DIM];
	team *new_team;

	NL++;
	scanf(" %[^\n]",name);
	if ((new_team = find_in_ht(teams, name)))
    	printf("%d Equipa existente.\n",NL);

  	else { /* if the team does not exist in teams*/
	    new_team = create_team(name);
	    add_to_ht(teams, new_team);
  	}
}

void cmd_p(ht *games) {
	char name[NAME_DIM];
	game *g;

	NL++;
	scanf(" %[^\n]",name);
	if((g =find_in_ht(games,name))!=NULL)
		print_game(g);
	
	else
		printf("%d Jogo inexistente.\n",NL);
}

void cmd_P(ht *teams) {
	char name[NAME_DIM];
	team *t;
	
	NL++;
	scanf(" %[^\n]",name);
	if ((t = find_in_ht(teams,name))!=NULL) 
		printf("%d %s %d\n",NL,t->name,t->games_won);
	else
		printf("%d Equipa inexistente.\n",NL);
}

void cmd_r(ht *games, ht *teams) {
	char name[NAME_DIM];
	game *g;
	team *t;

	NL++;
	scanf(" %[^\n]",name);
	if((g=find_in_ht(games,name)) != NULL) {
		if(g->score1 > g->score2) {
			t = find_in_ht(teams,g->team1);
			t -> games_won--;
		}

		if(g ->score2 > g->score1) {
			t = find_in_ht(teams,g->team2);
			t->games_won--;
		}
		remove_in_ht(games,name);
	}
	else
		printf("%d Jogo inexistente.\n",NL);
}


void cmd_s(ht *games, ht *teams) {
	char name[NAME_DIM];
	int new_score1,new_score2;
	game *g;
	team *t;

	NL++;
	scanf(" %[^:\n]:%d:%d",name,&new_score1,&new_score2);
	if((g=find_in_ht(games,name)) != NULL) {
		
		/* finds the winner of the original game and decreases the parameter 'games_won' */
		if(g->score1 > g->score2) {
			t = find_in_ht(teams,g->team1);
			t -> games_won--;
		}

		if(g ->score2 > g->score1) {
			t = find_in_ht(teams,g->team2);
			t -> games_won--;
		}

		if(new_score1 != new_score2)
			update_games_won(teams,g->team1,g->team2,new_score1,new_score2);
		
		g->score1 = new_score1;
		g->score2 = new_score2;
	}
	else
		printf("%d Jogo inexistente.\n",NL);
}


void cmd_g(ht *teams) {
	team *w;
	node *n;
	int max=0,num_of_winners=0,i,k;
	char **winners;
	char temp[NAME_DIM];

	NL++;
	/* searches in teams for the number of maximum number of wins */
	for (n = teams->dll_head; n; n = n->next) { 
		w = n -> data;
		if(w->games_won > max)
			max = w->games_won;
	}
	
	/* searches in teams for the number of teams which have the maximum number of wins */
	for (n = teams->dll_head; n; n = n->next) {
		w = n->data;
		if((w -> games_won)==max) 
			num_of_winners++;
	}
	
	/* allocs only the necessary memory for a table of chars*/
	if(num_of_winners){
		winners = malloc(num_of_winners*sizeof(char*));
		for (i = 0; i < num_of_winners; ++i)
			winners[i] = malloc(NAME_DIM*sizeof(char));

		
		/* insert the team->name in winners if the team has the maximum number of wins */
		i=0;
		for (n = teams->dll_head; n; n = n->next){
			w = n->data;
			if(w->games_won == max){
				strcpy(winners[i],w->name);
				i++;
			}
		}
		/* sorts lexicographically */
		for (i = 0; i < num_of_winners; ++i) {
    		for (k = i + 1; k < num_of_winners; ++k) {
        		if (strcmp(winners[i], winners[k]) > 0) {
	                strcpy(temp, winners[i]);
	                strcpy(winners[i], winners[k]);
	                strcpy(winners[k], temp);
	            }
    		}
		}
		
		printf("%d Melhores %d\n",NL,max);
		for (i = 0; i < num_of_winners; ++i)
			printf("%d * %s\n",NL,winners[i]);
		
		for (i = 0; i < num_of_winners; ++i)
			free(winners[i]);
		free(winners);
	}
}











