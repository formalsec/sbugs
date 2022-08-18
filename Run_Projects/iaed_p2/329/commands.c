#include "commands.h"

/* allocates the memmory needed for the System */
void Start_Sytem(System *s){
	s->inputline = 0;
	s->ts = malloc(sizeof(TS));
	s->gs = malloc(sizeof(GS));
	Init_Teams(s->ts);
	Init_Games(s->gs);
}

/* inserts a game in the System when possible */
void command_add_game(System *s){
	char bufferg[MAXGNAME], buffert1[MAXTNAME], buffert2[MAXTNAME];
	char *name_game;
	int  scoret1, scoret2; 
	pTeam t1;
	pTeam t2;
	pGame  game;
	pNode games;
	s->inputline += 1;

	scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", bufferg, buffert1, buffert2, &scoret1, &scoret2);
	games = STsearchG(bufferg, s->gs);
	t1 = STsearch(buffert1, s->ts);
	t2 = STsearch(buffert2, s->ts);

	if (games){
		printf("%d Jogo existente.\n", s->inputline);
	}
	
	else if(!(t1 && t2)){
		printf("%d Equipa inexistente.\n", s->inputline);
	}
	
	else{
		name_game = malloc(sizeof(char)*strlen(bufferg)+1);
		strcpy(name_game, bufferg);
		s->gs->number_games += 1;
		game = malloc(sizeof(struct Game));
		game->name = name_game;
		game->team1 = t1;
		game->scoreteam1 = scoret1;
		game->team2 = t2;
		game->scoreteam2 = scoret2;
		if (scoret1 > scoret2)
			t1->wins += 1;
		else if(scoret1 < scoret2){
			t2->wins += 1;
		}
		STinsertG(s->gs, game);	
		s->gs->number_games += 1; 
	}
}

/* prints all the games in the System in input order */
void command_list_game(System *s){
	pGNode  real_head = s->gs->list->head;
	s->inputline += 1;	
	for(real_head = s->gs->list->head;real_head; real_head = real_head->next)
		printf("%d %s %s %s %d %d\n", s->inputline, real_head->g->name,
												  real_head->g->team1->name,
												  real_head->g->team2->name,
												  real_head->g->scoreteam1,
												  real_head->g->scoreteam2);		
}

/* finds and prints an existing game */
void search_game(System *s){
	char buffer[MAXGNAME];
	pNode gm;
	scanf(" %[^:\n]", buffer);
	s->inputline += 1;	
	gm = STsearchG(buffer, s->gs);
	if (gm)
		printf("%d %s %s %s %d %d\n", s->inputline, gm->gms->g->name, gm->gms->g->team1->name, 
												  gm->gms->g->team2->name, gm->gms->g->scoreteam1,
												  gm->gms->g->scoreteam2);
	else
		printf("%d Jogo inexistente.\n", s->inputline);
}

/* removes a game from the hash table and the double linked list */
void remove_game(char *buffer, System *s){
	int i=hash(buffer, s->gs->HTsize);
	pNode remove;
	remove = STsearchG(buffer, s->gs);
	if (!remove)
		printf("%d Jogo inexistente.\n", s->inputline);		
	else{
		s->gs->number_games -= 1;

		if (remove->gms->g->scoreteam1 > remove->gms->g->scoreteam2 && 
			remove->gms->g->team1->wins > 0)
				remove->gms->g->team1->wins -= 1;

		else if(remove->gms->g->scoreteam1 < remove->gms->g->scoreteam2 && 
			remove->gms->g->team2->wins > 0)
				remove->gms->g->team2->wins -= 1;

		if (remove->gms->prev == NULL)
			s->gs->list->head = remove->gms->next;				 
		else
			remove->gms->prev->next = remove->gms->next;
		if (remove->gms->next == NULL)
			s->gs->list->last = remove->gms->prev;
		else
			remove->gms->next->prev = remove->gms->prev;

		free(remove->gms->g->name);
		s->gs->headsgames[i] = remove_gameaux(s->gs->headsgames[i], remove->gms);
	}
}

/* deleates a specific game from the System */
void deleate_game(System *s){
	char buffer[MAXGNAME];
	scanf(" %[^:\n]", buffer);
	s->inputline += 1;
	remove_game(buffer, s);
}

/* changes the score aof a spefic game */
void change_score(System *s){
	char    buffer[MAXGNAME];
	int     scoret1, scoret2;
	pNode               gm;
	s->inputline += 1;
	scanf(" %[^:\n]:%d:%d", buffer, &scoret1, &scoret2);
	gm = STsearchG(buffer, s->gs);
	if (gm)
		change_wins(gm->gms, scoret1, scoret2);
	
	else
		printf("%d Jogo inexistente.\n", s->inputline);
}

/* inserts a team in the System when possible */
void command_add_team(System *s){
	char buffer[MAXTNAME];
	char *name;
	pTeam t;
	scanf(" %[^:\n]", buffer);
	s->inputline += 1;	
	name = malloc(sizeof(char)*strlen(buffer)+1);
	strcpy(name, buffer);
	if (STsearch(name, s->ts)){
		printf("%d Equipa existente.\n", s->inputline);
		free(name);
	}
	else{
		s->ts->Nteams += 1;
		t = malloc(sizeof(struct Team));
		t->name = name;
		t->wins = 0;
		STinsert(s->ts, t);
	}
}

/* finds and prints an existing team */
void command_search_team(System *s){
	char buffer[MAXTNAME];
	pTeam    t;				
	s->inputline +=1;	
	scanf(" %[^:\n]", buffer);
	t = STsearch(buffer, s->ts);
	!t ? printf("%d Equipa inexistente.\n", s->inputline) : printf("%d %s %d\n", s->inputline, 
																			t->name, t->wins);
}

int cmpfnct(const void * a, const void * b){
	return strcmp(*(char**)a, *(char**)b);  	
}

/* finds and prints the biggest winners */
void command_bggst_wnnrs(System *s){
	int      max_wins = 0, n_winners = 0, count;
	pnode     real_head;
	char                  **biggest_winners;
	s->inputline += 1;

	if (s->ts->Nteams > 0){

		for(real_head = s->ts->list_teams;real_head; real_head = real_head->next){
			if(real_head->t->wins > max_wins){
				max_wins = real_head->t->wins;
				n_winners = 1;
			}
			else if (real_head->t->wins == max_wins)
				n_winners += 1;
		}
		
		/* number of teams that has already been added to the System */
		count = 0;

		biggest_winners = malloc(sizeof(char*) * n_winners);

		for (real_head = s->ts->list_teams;real_head; real_head = real_head->next){
			if(count < n_winners){
				if(real_head->t->wins == max_wins){
					biggest_winners[count] = real_head->t->name;
					count++;
				}
			}
			else break;
		}

		qsort(biggest_winners, n_winners, sizeof(char*), cmpfnct);

		printf("%d Melhores %d\n", s->inputline, max_wins);
		for (count=0; count < n_winners; count++){
			printf("%d * %s\n", s->inputline, biggest_winners[count]);
		}

		free(biggest_winners);
	}
}

/* Frees all the remaining allocated memmory in the system */
void Stop_System(System *s){
	Stop_Games(s->gs);
	Deleteallinfo_T(s->ts);
	free(s->ts->headsteams);
	free(s->gs);
	free(s->ts);
	free(s);
}