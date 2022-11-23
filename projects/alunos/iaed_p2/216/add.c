#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "add.h"


/*Esta funcao vai aceder a lista de equipas e alterar o contador de
* jogos ganhos apenas na equipa que ganhou um jogo*/
void addWin(list *tms, char *name){

	node *ptr = tms->head;

	while(ptr != NULL){

		ptr = ptr->next;
	}

	while(ptr){
		if(strcmp(ptr->name, name) == 0){
			(ptr->won)++;
			break;
		}
		ptr = ptr->next;
	}
}


/*Funcao que vai colocar um no com a informacao de jogo ou equipa
* na respetiva hashTable, controlado pela flag recebida.*/
void push(int idx, node *n_node, int flag){

	hashNode *info = (hashNode*)can_fail_malloc(sizeof(hashNode));
	info->point = n_node;
	
	if(flag == 0){
		info->next = games[idx].head;
		games[idx].head = info;
	}

	else{
		info->next = teams[idx].head;
		teams[idx].head = info;
	}
}


/*Funcao que vai adicionar um jogo ao sistema, isto e, a lista
* recebida, jogos, e ainda enviar o no para ser colocado na hashtable.
* Caso o jogo ja exista ou uma equipa referida nao exista e levantado um erro*/
void addGame(list *ls, list *tms){

	node *n_game;
	hashNode *testName, *testTeam1, *testTeam2;
	int idx, score1, score2;
	char name[MAXC], team1[MAXC], team2[MAXC];

	n_game = (node*)can_fail_malloc(sizeof(node));

	scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", name, team1, team2, &score1, &score2);


	testName = getNodeGames(name);
	testTeam1 = getNodeTeams(team1);
	testTeam2 = getNodeTeams(team2);

	if(testName != NULL){
		printf("%d Jogo existente.\n", counter);
		free(n_game);
		return;
	}

	else if(testTeam1 == NULL || testTeam2 == NULL){
		printf("%d Equipa inexistente.\n", counter);
		free(n_game);
		return;
	}
	
	else{

		n_game->name = (char*)can_fail_malloc(sizeof(char) * (strlen(name) + 1));
		n_game->team1 = (char*)can_fail_malloc(sizeof(char) * (strlen(team1) + 1));
		n_game->team2 = (char*)can_fail_malloc(sizeof(char) * (strlen(team2) + 1));

		strcpy(n_game->name, name);
		strcpy(n_game->team1, team1);
		strcpy(n_game->team2, team2);
		n_game->score1 = score1;
		n_game->score2 = score2;

		n_game->next = n_game->previous = NULL;

		if(ls->head == NULL){
			ls->head = n_game;
			idx = getHashKey(n_game->name);
			push(idx, n_game, 0);
		}

		else{
			n_game->previous = ls->end;
			ls->end->next = n_game;
			idx = getHashKey(n_game->name);
			push(idx, n_game, 0);
		}

		if(score1 > score2){
			addWin(tms, team1);
			(testTeam1->point->won)++;
		}

		else if(score1 < score2){
			addWin(tms, team2);
			(testTeam2->point->won)++;
		}

		ls->end = n_game;
	}
}


/*Funcao que vai adicionar uma equipa ao sistema, isto e, a lista
* recebida, equipas, e ainda enviar o no para ser colocado na hashtable.
* Caso a equipa ja exista e levantado um erro*/
void addTeam(list *ls){

	node *n_team;
	hashNode *testTeam;
	int idx;
	char name[MAXC];

	n_team = (node*)can_fail_malloc(sizeof(node));

	scanf(" %[^\n]", name);

	n_team->name = (char*)can_fail_malloc(sizeof(char) * (strlen(name) + 1));
	
	strcpy(n_team->name, name);
	n_team->won = 0;	

	n_team->next = n_team->previous = NULL;

	testTeam = getNodeTeams(n_team->name);

	if(testTeam != NULL){
		printf("%d Equipa existente.\n", counter);
		free(n_team->name);
		free(n_team);
		return;
	}

	else{
		if(ls->head == NULL){
			ls->head = n_team;
			idx = getHashKey(n_team->name);
			push(idx, n_team, 1);
		}

		else{
			n_team->previous = ls->end;
			ls->end->next = n_team;
			idx = getHashKey(n_team->name);
			push(idx, n_team, 1);
		}

		ls->end = n_team;
	}
}