#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "search.h"


/*Estas duas funcoes, ao receberem um nome, verificam se este existe na hashtable
* respetiva, jogos ou equipas, e retorna as informacoes respetivas ao no da hashtable.*/
void searchGame(){

	hashNode *get;
	char name[MAXC];

	scanf(" %[^\n]", name);

	get = getNodeGames(name);

	if(get == NULL){
		printf("%d Jogo inexistente.\n", counter);
		return;
	}

	else
		printf("%d %s %s %s %d %d\n", counter, get->point->name, get->point->team1,
		 get->point->team2, get->point->score1, get->point->score2);

}

void searchTeam(){

	hashNode *get;
	char team[MAXC];

	scanf(" %[^\n]", team);

	get = getNodeTeams(team);

	if(get == NULL){
		printf("%d Equipa inexistente.\n", counter);
		return;
	}

	else
		printf("%d %s %d\n", counter, get->point->name, get->point->won);
	
}