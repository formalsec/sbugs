#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

/* The maximum number of values stored. */
#define MAX 1024

/* Array of values. */
/*int vals[SZ];*/
/* The number of values stored. */
int count;

/*scanf(%[^:\n])*/
typedef struct stru_nodeT { /*struct for team*/
	struct stru_nodeT *next, *previous;
	char *name; /*team name*/
	int *victories; /*number of victories*/
} nodeT;

typedef struct { /*team list*/
	nodeT * head, *last;
} listT;

typedef struct stru_nodeG { 
	struct stru_nodeG *next, *previous;
	char *name;
	char *team1;
	char *team2;
	int *score1;
	int *score2;
} nodeG;

typedef struct {
	nodeG * head, *last;
} listG;


listT* mk_listT(){ /*make listT*/
	listT *l = can_fail_malloc(sizeof(listT)); /*allocate space for listT*/
	l->head = l->last = NULL; /*initialize listT as null*/
	return l;
}

listG* mk_listG(){ /*make listT*/
	listG *l = can_fail_malloc(sizeof(listG)); /*allocate space for listT*/
	l->head = l->last = NULL; /*initialize listT as null*/
	return l;
}

void free_nodeT(nodeT* n){/*free nodeT of listT*/
	free(n->victories);
	free(n->name); 
	free(n);
}

void free_nodeG(nodeG* n){/*free nodeT of listT*/
	free(n->name); 
	free(n->team1);
	free(n->team2);
	free(n->score1);
	free(n->score2);
	free(n);
}


void free_listT(listT *l){
	while(l->head != NULL){/*go through llistT*/
		nodeT* tmp = l->head->next; /*save nodeT after head in tmp*/
		free_nodeT(l->head);/*free nodeT*/
		l->head = tmp;/*define tmp as new head*/
	}
	free(l);
}

void free_listG(listG *l){
	while(l->head != NULL){/*go through llistT*/
		nodeG* tmp = l->head->next; /*save nodeT after head in tmp*/
		free_nodeG(l->head);/*free nodeT*/
		l->head = tmp;/*define tmp as new head*/
	}
	free(l);
}

void rm_nodeG(listG* l, nodeG* n){
	if(n->previous == NULL){ /*if nodeT is the head*/
		l-> head = n->next; /*define next nodeT as new head*/
	}
	else{ 
		n->previous->next = n->next; /*define next of previous as next node*/
	}
	if(n->next == NULL){ /*if node was the last*/
		l->last = n->previous; /*define previous node as new last*/
	}
	else {
		n->next->previous = n->previous; /*define previous of next as previous node*/
	}
	free_nodeG(n);

}

void add_lastT(listT *l, const char*n){
	nodeT *nn = can_fail_malloc(sizeof(nodeT)); /*allocate for node*/
	nn-> previous = l->last; /*define nn as the last node*/
	nn-> next = NULL; /*define next as NULL*/
	nn-> name = can_fail_malloc(sizeof(char)*(strlen(n)+1)); /*allocate, +1 for /0 used by strcpy*/
	nn-> victories = can_fail_malloc(sizeof(int));
	strcpy(nn->name, n);/*intialize values*/
	*nn->victories = 0;
	if(l->last){/*if last exists*/
		l->last->next = nn;/*put node after last*/
	}
	else{/*if it's empty*/
		l->head = nn;/*define node as head*/

	}
	l->last = nn;/*define last node as this node*/

}

void add_lastG(listG *l, const char*n, const char*T1, const char*T2, int* s1, int* s2){
	nodeG *nn = can_fail_malloc(sizeof(nodeG)); /*allocate for node*/
	nn-> previous = l->last; /*define nn as the last node*/
	nn-> next = NULL; /*define next as NULL*/
	nn-> name = can_fail_malloc(sizeof(char)*(strlen(n)+1)); /*allocate, +1 for /0 used by strcpy*/
	nn-> team1 = can_fail_malloc(sizeof(char)*(strlen(T1)+1));
	nn-> team2 = can_fail_malloc(sizeof(char)*(strlen(T2)+1));
	nn-> score1 = can_fail_malloc(sizeof(int));
	nn-> score2 = can_fail_malloc(sizeof(int));
	strcpy(nn->name, n); /*intialize values*/
	strcpy(nn->team1, T1);
	strcpy(nn->team2, T2);
	*nn-> score1 = *s1;
	*nn-> score2 = *s2;
	if(l->last){ /*if last exists*/
		l->last->next = nn; /*put node after last*/
	}
	else{/*if it's empty*/
		l->head = nn; /*define node as head*/
		
	}
	l->last = nn; /*define last node as this node*/

}


char* scan_and_allocate(){/*alocate memory and read from stdin*/
	char *buffer = can_fail_malloc(MAX);
	scanf("%[^:\n]%*c", buffer); /*read string and discard next character, either /n or :*/
	return buffer;
}

int* scan_int(){
	int *s = can_fail_malloc(sizeof(int)); /*auxiliar for score*/
	scanf("%d%*c", s); /*read score and discard next character, etiehr /n or :*/
	return s;
}

bool checkGame(listG *games, char *name){
	nodeG *tmp; /*save head in tmp*/
	for(tmp = games->head; tmp; tmp = tmp->next){ /*go through games*/
		if(strcmp(tmp->name, name)==0){ /*if game name already exists*/
			return true; /*exit fucntion*/
		}
	}
	return false;
}
bool checkTeam(listT *teams, char *name){
	
	nodeT *tmp; /*save head in tmp*/
	for(tmp = teams->head; tmp; tmp = tmp->next){ /*go through teams*/
		if(strcmp(tmp->name, name)==0){ /*if team name already exists*/
			return true; /*exit fucntion*/
		}
	}

	return false;
}

void addTeam(listT *teams){/*add team to listT of teams*/

	char *name = scan_and_allocate(); /*read and allocate*/
	if(!checkTeam(teams, name)){
		add_lastT(teams, name); /*add team name to listT*/
	}
	else{
		printf("%d Equipa existente.\n", count);
	}
	free(name); /*free buffer*/
}


void victory(listT *teams, char *T1, char *T2, int* s1, int *s2){
	char *name;
	nodeT *tmp; /*save head in tmp*/
	if(*s1>*s2){ /*if team 1 won*/
		name = T1; 
	}
	else if(*s1<*s2){ /*if team 2 won*/
		name = T2;
	}	
	else{ /*if it was a draw*/
		return; /*do nothing, no one won*/
	}
	

	for(tmp = teams->head; tmp; tmp = tmp->next){ /*go through teams*/
		if(strcmp(tmp->name, name)==0){ /*if team name macthes winning team*/
			tmp->victories++; /*add victory to that team*/
		}
	}
			
}

void addGame(listG *games, listT *teams){
	char *name, *team1, *team2;
	int *s1, *s2;
	name = scan_and_allocate(); /*read and allocate*/
	team1 = scan_and_allocate(); /*read and allocate*/
	team2 = scan_and_allocate(); /*read and allocate*/
	s1= scan_int(); /*read and allocate int*/
	s2 = scan_int(); /*read and allocate int*/
	if(!checkGame(games, name)){/*if game doesn't exist*/

	
		if(checkTeam(teams, team1) && checkTeam(teams, team2)){ /*if teams exist*/
			add_lastG(games, name, team1, team2, s1, s2);/*add game*/
			victory(teams, team1, team2, s1, s2); /*add victory*/
			
		}
		else{ /*if one or both teams don't exist*/
			printf("%d Equipa inexistente.\n", count);
		}
		
	}
	else{/*if game exists*/
		printf("%d Jogo existente.\n", count);
	}
	free(s2);
	free(s1);
	free(team2);
	free(team1);
	free(name);

	
}


void listGames(listG *games){
	nodeG *tmp; 
	for(tmp = games->head; tmp; tmp = tmp->next){ /*go through games*/
		printf("%d %s %s %s %d %d\n", count, tmp->name, tmp->team1, tmp->team2, *tmp->score1, *tmp->score2);
	}


}



void removeGame(listG *games){
	char *name = scan_and_allocate(); /*read and allocate*/
	if(checkGame(games,name)){ /*if game exists*/
		nodeG *tmp;
		for(tmp = games->head; tmp; tmp = tmp->next){ /*go through games*/
			if(strcmp(tmp->name, name)==0){ /*if name correponds to given game name*/
				rm_nodeG(games, tmp); /*remove game*/
			}
		}	
		
	}
	else{ /*if game doesn't exist*/
		printf("%d Jogo inexistente.\n", count);
	}
	free(name);
}

void changeScore(listG *games){
	char *name = scan_and_allocate(); /*read and allocate*/
	int *s1 = scan_int();
	int *s2 = scan_int();
	if(checkGame(games,name)){/*if game exists*/
		nodeG *tmp;
		for(tmp = games->head; tmp; tmp = tmp->next){/*go through games*/
			if(strcmp(tmp->name, name)==0){/*if name correponds to given game name*/
				*tmp->score1 = *s1; /*change score*/
				*tmp->score2 = *s2;
			}
		}
	}
	else{
		printf("%d Jogo inexistente.\n", count);
	}
	
	free(name);
}

void searchGame(listG *games){
	char *name = scan_and_allocate(); /*read and allocate*/
	if(checkGame(games,name)){/*if game exists*/
		nodeG *tmp;
		for(tmp = games->head; tmp; tmp = tmp->next){/*go through games*/
			if(strcmp(tmp->name, name)==0){/*if name correponds to given game name*/
				printf("%d %s %s %s %d %d\n", count, tmp->name, tmp->team1, tmp->team2, *tmp->score1, *tmp->score2);
			}
		}
	}
	else{
		printf("%d Jogo inexistente.\n", count);
	}
	
	free(name);
}
void searchTeam(listT *teams){
	char *name = scan_and_allocate(); /*read and allocate*/
	if(checkTeam(teams,name)){/*if team exists*/
		nodeT *tmp; /*save head in tmp*/
		for(tmp = teams->head; tmp; tmp = tmp->next){/*go through teams*/
			if(strcmp(tmp->name, name)==0){/*if name correponds to given team name*/
				printf("%d %s %d\n", count, tmp->name, *tmp->victories);
			}
			
		}

	}
	else{
		printf("%d Equipa inexistente.\n", count);
	}
	free(name);

}
int main() {
	listT *teams = mk_listT(); /*initialize team list*/
	listG *games = mk_listG(); /*initialize game list*/
	count = 0; /*initialize input line counter*/
	while(1)
	{	
		
		char c = getchar(); /*read command from stdin*/
		
		switch(c){
			/*exit*/
			case'x':
				free_listT(teams); /*free team list*/
				free_listG(games);/*free game list*/
			 	exit(EXIT_SUCCESS);	
			/*add game*/
 			case'a': 
 				count++;
				getchar(); /*read extra space from stdin*/
 				addGame(games, teams);
				break;
			/*listT games*/
			case'l':
				count++;
				listGames(games);
				break;
			/*search game*/
			case'p':
				count++;
				getchar(); /*read extra space from stdin*/
				searchGame(games);
				break;
			/*remove game*/
			case'r':
				count++;
				getchar(); /*read extra space from stdin*/
				removeGame(games);
				break;
			/*change score*/
			case's':
				count++;
				getchar(); /*read extra space from stdin*/
				changeScore(games);
				break;
			/*add team*/
			case'A':
				count++;
				getchar(); /*read extra space from stdin*/
				addTeam(teams);
				break;
			/*search team*/
			case'P':
				count++;
				getchar(); /*read extra space from stdin*/
				searchTeam(teams);
				break;
			/*Teams that won the most games in alphabetical order*/
			case'g':
				count++;
				break;	
			
		}
	}
	return 0;
}
