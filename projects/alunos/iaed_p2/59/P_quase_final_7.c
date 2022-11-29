#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* definicao de constantes*/
#define MAX_NAME 1024
#define MAX_TEAM 1024
#define MAX_COMMAND 100

/* associacao a uma letra*/
typedef enum {
	ADD_MATCH = 'a',
	ADD_TEAM = 'A',
	LIST_MATCH = 'l',
	MATCH_SEARCH = 'p',
	TEAM_SEARCH = 'P',
	CHANGE_SCORE = 's',
	DELETE_MATCH = 'r',
	CHANGE_PRICE = 'p',
	LIST_TEAM = 'g',
	END_PROG = 'x',
	UNKNOWN_COMMAND = '\0'

} Command;

/*lista que contem os nomes das equipes*/

typedef struct team{
	char *team_name;
	struct team *next;
} teamNode;

/*lista que contem os jogos(nome, equipes, pontuacao)*/

typedef struct match{

	char *name;
	char *team_1;
	char *team_2;
	int  score_1;
	int  score_2;
	struct match *next;
} matchNode;

char buffer[MAX_COMMAND];
static teamNode *teamList;
static matchNode *matchList;
int inputCount;

void insertTeam(char* teamData){
		teamNode *n, *aux;
		n = (teamNode*) can_fail_malloc(sizeof(teamNode));

		n->team_name = can_fail_malloc((1+strlen(teamData))*sizeof(char));
		strcpy(n->team_name, teamData);

		if (teamList == NULL){

			n->next = NULL;
			teamList = n;
		}else{

			aux = teamList;
			while(aux->next != NULL){

				aux=aux->next;
			}
			n->next=NULL;
			aux->next=n;
		}

		return;
	}

void insertMatch(char* nameData, char* teamData1, char* teamData2, int score_1, int score_2){
		matchNode *n, *aux;
		n = (matchNode*) can_fail_malloc(sizeof(matchNode));

		n->name = can_fail_malloc((1+strlen(nameData))*sizeof(char));
		strcpy(n->name, nameData);

		n->team_1 = can_fail_malloc((1+strlen(teamData1))*sizeof(char));
		strcpy(n->team_1, teamData1);

		n->team_2 = can_fail_malloc((1+strlen(teamData2))*sizeof(char));
		strcpy(n->team_2, teamData2);

		n->score_1 = score_1;
		n->score_2 = score_2;

		if (matchList == NULL){

			n->next = NULL;
			matchList = n;
		}else{

			aux = matchList;
			while(aux->next != NULL){

				aux=aux->next;
			}
			n->next=NULL;
			aux->next=n;
		}

		return;
	}
	
/* a: adiciona um novo jogo */

void add_match(char* name, char* team_1, char* team_2, int score_1, int score_2) {

	matchNode *aux = matchList;
	teamNode  *aux2 = teamList;

	bool b1 = false;
	bool b2 = false;

/*enquanto estiver elemento ainda na lista, mostre-me*/
	while(aux!=NULL){

		if (!strcmp(aux->name, name)){

			printf("%d Jogo existente.\n", inputCount);
		return;
		}
	/*incrementa o aux, pra percorrer a lista toda*/
		aux=aux->next;
	}

	while(aux2!=NULL){

		if (!strcmp(aux2->team_name, team_1)){
			b1 = true;
		}
		if (!strcmp(aux2->team_name, team_2)){
			b2 = true;
		}
		/*incrementa o aux, pra percorrer a lista toda*/
		aux2=aux2->next;
	}

	if(!b1 || !b2){

		printf("%d Equipa inexistente.\n", inputCount);
		return;

		}
		insertMatch(name, team_1, team_2, score_1, score_2);
	return;

}

/* l: lista todos os jogos introduzidos */

void list_match() {

	matchNode *auxList;
	auxList = matchList;

		
	if (auxList == NULL){
		
		return;
	
	}

	while (auxList != NULL) {

		printf("%d %s %s %s %d %d\n", inputCount, auxList->name, auxList->team_1, auxList->team_2, auxList->score_1, auxList->score_2);
		auxList=auxList->next;

	}

	return;
}

/* p: Procura um jogo com o nome dado*/

void match_search(char* namep) {

	matchNode *auxMatch = matchList;
	bool b1 = false;

	while(auxMatch!=NULL){

		if (!strcmp(auxMatch->name, namep)){
			b1 = true;
			printf("%d %s %s %s %d %d\n", inputCount, namep, auxMatch->team_1, auxMatch->team_2, auxMatch->score_1, auxMatch->score_2);
			return;
		}
		/*incrementa o aux, pra percorrer a lista toda*/
		auxMatch=auxMatch->next;
	}

	if(!b1){

		printf("%d Jogo inexistente.\n", inputCount);
		return;

		}

	return;

}
/* s: Altera o score de um jogo dado o nome*/

void change_score(char* name, int score_1, int score_2) {

	matchNode *auxMatch = matchList;
	matchNode *auxHead = auxMatch;
	bool b1 = false;

	while(auxMatch!=NULL){

		if (!strcmp(auxMatch->name, name)){
			b1 = true;
			auxMatch->score_1=score_1;
			auxMatch->score_2=score_2;
		}
		/*incrementa o aux, pra percorrer a lista toda*/
		auxMatch=auxMatch->next;
	}

		if(!b1){

		printf("%d Jogo inexistente.\n", inputCount);
		return;

		}
		matchList = auxHead;

	return;


}


/* A: Adiciona uma nova equipa*/

void add_team(char* nameA) {

	teamNode *aux = teamList;
	/*enquanto estiver elemento ainda na lista, mostre-me*/
	while(aux!=NULL){

		if (!strcmp(aux->team_name, nameA)){

			printf("%d Equipa existente.\n", inputCount);
			return;
	}
		/*incrementa o aux, pra percorrer a lista toda*/
		aux=aux->next;
	}

	insertTeam(nameA);
	return;
}

/* r: Apaga um jogo dado um nome*/

void delete_match(char* name) {

	matchNode *auxMatch = matchList;
	matchNode *auxPrevious = NULL;

		if (auxMatch != NULL && !strcmp(auxMatch->name,name)){
			matchList = auxMatch->next;
			return;
		}

		while (auxMatch != NULL && strcmp(auxMatch->name,name)){
			auxPrevious = auxMatch;
			auxMatch = auxMatch->next;

		}

		if (auxMatch == NULL){

			printf("%d Jogo inexistente.\n", inputCount);
			return;

		}

		auxPrevious->next = auxMatch->next;
		return;
}

/* P: Procura uma equipa dado um nome*/


void team_search(char* name) {

	matchNode *auxMatch = matchList;
	teamNode  *auxTeam = teamList;
	int winCount = 0;
	bool b1 = false;
	bool b2 = false;

while(auxTeam!=NULL){

		if (!strcmp(auxTeam->team_name, name)){
			b1 = true;
		}
		if (!strcmp(auxTeam->team_name, name)){
			b2 = true;
		}
		/*incrementa o aux, pra percorrer a lista toda*/
		auxTeam=auxTeam->next;
	}

	if(!b1 || !b2){

		printf("%d Equipa inexistente.\n", inputCount);
		return;

		}

	while(auxMatch!=NULL){

		if (!strcmp(auxMatch->team_1, name) & (auxMatch->score_1>auxMatch->score_2)){
				winCount++;
			}

		if (!strcmp(auxMatch->team_2, name) & (auxMatch->score_2>auxMatch->score_1)){
				winCount++;
			}
	/*incrementa o aux, pra percorrer a lista toda*/
		auxMatch=auxMatch->next;
	}


	printf("%d %s %d\n", inputCount, name, winCount);
	return;
}

/* g: Encontra as equipes que ganharam mais jogos e lista por ordem lexicografica*/

void list_team() {

typedef struct vic_Team{
	char vName[MAX_NAME];
	int vicCount;
	struct vic_Team *next;
} vicNode;

    int maxVict = 0;
    int i,j,k = 0;
    vicNode vicTeam[50];
    char auxVic[MAX_NAME];
	teamNode *aux_team = teamList;
	matchNode *aux_match;
	bool swapped;

	if (aux_team == NULL){
		return;
	}
	
	/*enquanto estiver elemento ainda na lista, mostre-me*/
	while(aux_team!=NULL){

		strcpy(vicTeam[i].vName, aux_team->team_name);
		vicTeam[i].vicCount = 0;
		aux_match = matchList;

		
		while(aux_match!=NULL){

            if (!strcmp (aux_match->team_1,vicTeam[i].vName)&& aux_match->score_1>aux_match->score_2){
            vicTeam[i].vicCount++;
            }
            if (!strcmp (aux_match->team_2,vicTeam[i].vName)&& aux_match->score_2>aux_match->score_1){
            vicTeam[i].vicCount++;
            }

        	aux_match = aux_match->next;

		}
	
	if (vicTeam[i].vicCount >  maxVict ) maxVict = vicTeam[i].vicCount;
 	/*incrementa o aux_team, pra percorrer a lista toda*/
	aux_team=aux_team->next;
	i++;
    strcpy(vicTeam[i].vName,"EOF");
	}
	free(aux_team);
	free(aux_match);

	swapped = true;
    while (swapped){
    	swapped = false;
    	for (j = 0; j<i-1; j++){
    		if (strcmp(vicTeam[j].vName,vicTeam[j+1].vName)>0){
    			
    			strcpy(auxVic, vicTeam[j].vName);
    			k = vicTeam[j].vicCount;

    			strcpy(vicTeam[j].vName, vicTeam[j+1].vName);
                vicTeam[j].vicCount = vicTeam[j+1].vicCount;

    			strcpy(vicTeam[j+1].vName, auxVic);
    			vicTeam[j+1].vicCount = k;

    			swapped = true;
    		}
    	}
    }
    
    printf("%d %s %d\n", inputCount, "Melhores", maxVict);
 
    	for (j=0; j<i; j++){
    		if (vicTeam[j].vicCount == maxVict && strcmp(vicTeam[j].vName,vicTeam[j+1].vName)){
    			printf("%d %s %s\n", inputCount, "*", vicTeam[j].vName);	
    		}
    	}

   return;
}

/* x: termina o programa*/

void end_prog() {

	free(teamList);
	free(matchList);
	exit(0);

}

void run_command(Command com, char* args) {

	char name[MAX_NAME], team_1[MAX_TEAM], team_2[MAX_TEAM], *r_args_1, *r_args_2, *r_args;
	int score_1, score_2;

	switch(com) {

		/* Entrada: a nome:equipa1:equipa2:score_1:score_2*/
		case ADD_MATCH:

			inputCount++;

			r_args   = strchr(args, ':'); /*args eh tudo menos o comando r_args eh o args sem nome*/
			r_args[0]   = '\0';
			r_args++;
			strcpy(name, args);

			r_args_1 = strchr(r_args, ':');/*tira a equipa1*/
			r_args_1[0] = '\0';
			r_args_1++;
			strcpy(team_1, r_args);

			r_args_2 = strchr(r_args_1, ':'); /*tira equipa2*/
			r_args_2[0] = '\0'; r_args_2++;
			strcpy(team_2, r_args_1);
 			sscanf(r_args_2,"%d:%d", &score_1, &score_2);

			add_match(name, team_1, team_2, score_1, score_2);
			break;

		/* Entrada: l*/
		case LIST_MATCH:
			inputCount++;
      		list_match();
			break;

		/* Entrada: p nome */
		case MATCH_SEARCH:
			inputCount++;
			sscanf(args, "%[^\t\n]", name);
			match_search(name);
			break;

		/* Entrada: r nome*/
		case DELETE_MATCH:
			inputCount++;
			sscanf(args, "%[^\t\n]", name);
			delete_match(name);
			break;

    /* Entrada: s nome:score_1:score_2*/
		case CHANGE_SCORE:

			inputCount++;
            r_args = strchr(args, ':'); /*seleciona tudo que vem depois de :*/
			r_args[0] = '\0'; /*tira o :*/
			r_args++; /* continua a ler o resto*/
			strcpy(name, args); /* pega o nome e copia para args*/
			sscanf(r_args, "%d:%d", &score_1, &score_2);
			change_score(name, score_1, score_2);
			break;

		/* Entrada: A nome*/
		case ADD_TEAM:
			inputCount++;
		/*le o comando*/
			sscanf(args,"%[^\t\n]", name);
			add_team(name);
			break;

			/* Entrada:P nome*/
		case TEAM_SEARCH:

			inputCount++;
			sscanf(args,"%[^\t\n]", name);
			team_search(name);
			break;

				/* Entrada: g*/
		case LIST_TEAM:
			inputCount++;
			list_team();
			break;

			/* Entrada: x*/
		case END_PROG:
			end_prog();
			break;

		default:
			break;

	}

}

Command read_command(char** args) {

	if(!fgets(buffer, MAX_COMMAND, stdin))
		return UNKNOWN_COMMAND;

	*args = buffer + 2;

	return (Command)buffer[0];

}

int main () {

	char* args;

	args = NULL;

	/*inicializando lista de times vazia*/

	teamList = NULL;

	inputCount = 0;

	while (1) {

			Command com = read_command(&args);
			run_command(com, args);
	}

}