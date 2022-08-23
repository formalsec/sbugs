#include "change.h"


/*Funcao que recebe uma lista, um nome e os novos resultados de modo
* a poder efetuar a troca e apresentar o novo resultado do jogo.*/
void altScore(list *ls, char *name, int n_score1, int n_score2){

	node *ptr = ls->head;

	while(ptr != NULL){

		ptr = ptr->next;
	}

	while(ptr){
		if(strcmp(ptr->name, name) == 0){
			ptr->score1 = n_score1;
			ptr->score2 = n_score2;
			break;
		}
		ptr = ptr->next;
	}
}


/*Funcao verifica os resultados anteriores e os novos resultados,
* recebidos do input, e procede as alteracoes do contador de jogos
vencidos por cada equipa respetivamente ao jogo em questao.*/
void changeScore(list *ls, list *tms){

	hashNode *n_res, *team1, *team2;
	char name[MAXC];
	int n_score1, n_score2, p_scr1, p_scr2;

	scanf(" %[^:\n]:%d:%d", name, &n_score1, &n_score2);

	n_res = getNodeGames(name);

	if(n_res == NULL){
		printf("%d Jogo inexistente.\n", counter);
		return;
	}

	else{
		p_scr1 = n_res->point->score1;
		p_scr2 = n_res->point->score2;
		
		altScore(ls, name, n_score1, n_score2);

		n_res->point->score1 = n_score1;
		n_res->point->score2 = n_score2;
		
		team1 = getNodeTeams(n_res->point->team1);
		team2 = getNodeTeams(n_res->point->team2);

		
		if(p_scr1 > p_scr2){
			if(n_score1 < n_score2){
				addWin(tms, team2->point->name);
				(team2->point->won)++;
				rmvWin(tms, team1->point->name);
				(team1->point->won)--;
			}

			else if(n_score1 == n_score2){
				rmvWin(tms, team1->point->name);
				(team1->point->won)--;
			}
		}

		else if(p_scr1 < p_scr2){
			if(n_score1 > n_score2){
				addWin(tms, team1->point->name);
				(team1->point->won)++;
				rmvWin(tms, team2->point->name);
				(team2->point->won)--;
			}

			else if(n_score1 == n_score2){
				rmvWin(tms, team2->point->name);
				(team2->point->won)--;
			}
		}

		else{
			if(n_score1 > n_score2){
				addWin(tms, team1->point->name);
				(team1->point->won)++;
			}

			else if(n_score1 < n_score2){
				addWin(tms, team2->point->name);
				(team2->point->won)++;
			}
		}
	}
}