#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "MATCH.h"
#include "TEAM.h"
#include "TEAMHTABLE.h"

/*Apaga o jogo m*/
void freeMatch(Match m){
	free(m->name);
	free(m);
}

/*Retorna a equipa vencedora do jogo match, devolve NULL em caso de empate*/
Team getWinTeam(Match match){
	if (match->score1 > match->score2){
		return match->team1;
	}
	else if (match->score1 < match->score2){
		return match->team2;
	}
	return NULL;
}

/*Retorna a equipa perdedora do jogo match, devolve NULL em caso de empate*/
Team getLoserTeam(Match match){
	if (match->score1 < match->score2){
		return match->team1;
	}
	else if (match->score1 > match->score2){
		return match->team2;
	}
	return NULL;
}

/*Funcao auxiliar que decrementa o score da equipa vencedora do jogo match*/
void removeScores(Match match){
  if (match->score1 > match->score2){
		match->team1->score--;
	}
	else if (match->score1 < match->score2){
		match->team2->score--;
	}
}

/*Funcao que altera os scores de um jogo match, corrigindo tambem os scores das equipas*/
void changeScores(Match match, int s1, int s2){
	removeScores(match);
	match->score1 = s1;
	match->score2 = s2;

	updateTeamScore(match);
}

/*Funcao auxiliar que incrementa o score da equipa vencedora do jogo*/
void updateTeamScore(Match match){
	if (match->score1 > match->score2){
		match->team1->score++;
	}
	else if (match->score1 < match->score2){
		match->team2->score++;
	}
}

/*Cria um novo match com as informacoes recebidas como argumento*/
Match newMatch(char* name, char* team1, char* team2, int score1, int score2){
  teamNode t1, t2;
  Match new = (Match)can_fail_malloc(sizeof(struct match));
  size_t size = strlen(name) + 1;
  t1 = teamSearch(team1);
  t2 = teamSearch(team2);
  new->name = (char*) can_fail_malloc(sizeof(char) * size);
	strncpy(new->name, name, size);
	new->team1 = t1->team;
	new->team2 = t2->team;
	new->score1 = score1;
	new->score2 = score2;
  updateTeamScore(new);
	return new;
}
