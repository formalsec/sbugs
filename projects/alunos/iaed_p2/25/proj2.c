#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 1023 /* maximo de 1023 caracteres para nomes*/


/* Estrutura para uma equipa */

typedef struct team {
	char *name; /* string de tamanho arbitrario */
	struct team *next;
} *team_link; /* team_link e um pointer para uma equipa (struct team) */


/* Estrutura para um jogo */

typedef struct game {
	char *name, *team1, *team2; /* strings de tamanho arbitrario */
	int score1, score2;
	struct game *next;
} *game_link; /* game_link e um pointer para um jogo (struct game) */












/*  /\    /\    /\    /\    /\    /\    /\    /\    /\    /\    */
/* /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  /*/
/*/    \/    \/    \/    \/    \/    \/    \/    \/    \/    \/ */
/*//////////////////////////////////////////////////////////////*/
/*//////////////////////adiciona_equipa/////////////////////////*/
/*/////////////////////////////&////////////////////////////////*/
/*//////////////////////procura_equipa//////////////////////////*/
/*/////////////////////////////&////////////////////////////////*/
/*/////////////////////////melhores/////////////////////////////*/
/*//////////////////////////////////////////////////////////////*/




/* Procura na lista de equipas uma equipa na qual o nome da equipa corresponde a 
string passada por argumento. A funcao retorna o pointer da equipa encontrada. 
A funcao retorna NULL se nenhuma equipa for encontrada */

team_link teams_lookup(team_link *teams_head, char* name){
	
	team_link t;
	for(t = *teams_head; t != NULL; t = t->next)
		if(strcmp(t->name, name) == 0)
			return t;
	return NULL;

}

/* Esta funcao retorna um pointer de uma string, que e um duplicado do pointer da 
string passada por argumento. A memoria e obtida dinamicamente usando "can_fail_malloc" */

char *copy_string(char* name){

	char *string = (char *) can_fail_malloc(sizeof(char)*(strlen(name)+1));
	strcpy(string,name);
	return string;

}

/* Responsavel pela alocacao de memoria de tudo o que e necessario para uma nova equipa 
(struct team) e de a inserir no inicio da lista de equipas */

void insertBegin_team(team_link *teams_head, char* name){
	
	team_link t = (team_link) can_fail_malloc(sizeof(struct team));
	t->name = copy_string(name);
	t->next = *teams_head;
	*teams_head = t;

}

/* Calcula o numero de jogos ganhos por uma equipa com nome correspondente a string 
passada por argumento. A funcao retorna o numero de vitorias da equipa */

int games_won(game_link *games_head, char* name){

	int wins = 0;
	game_link g;
	for(g = *games_head; g != NULL; g = g->next){
		if(strcmp(g->team1, name) == 0 && g->score1 > g->score2)
			wins++;

		if(strcmp(g->team2, name) == 0 && g->score1 < g->score2)
			wins++;
	}

	return wins;

}

/* Calcula o maximo de vitorias por uma equipa da lista de equipas. A funcao retorna 
esse valor */

int most_wins(team_link *teams_head, game_link *games_head){

	int wins, max = 0;
	team_link t;
	for(t = *teams_head; t != NULL; t = t->next){
		if((wins = games_won(games_head, t->name)) > max)
			max = wins; 
	}
	return max;

}

/* Funcao copia equipas da lista de equipas para uma lista de equipas auxiliar cujo numero 
de vitorias corresponda ao inteiro passado por argumento */

void teams_copy(team_link *teams_head, game_link *games_head, team_link *teams_head_aux, int *wins){
	
	team_link t;
	for(t = *teams_head; t != NULL; t = t->next)
		if(games_won(games_head, t->name) == *wins)
			insertBegin_team(teams_head_aux, t->name); 
	
}

/* Divivde as equipas da dada lista em metades "front" e "back", e retorna as duas listas 
usando os parametros de referencia. Se o comprimento for impar, a equipa extra deve estar 
na lista da frente. Usa a estrategia do fast/slow pointer.*/

void FrontBackSplit(team_link source, team_link *frontRef, team_link *backRef) {

	team_link fast;
	team_link slow;
	slow = source;
	fast = source->next;
  
    while (fast != NULL) { /* avanca 'fast' duas equipas, e avanca 'slow' uma equipa */
        fast = fast->next; 
        if (fast != NULL) { 
            slow = slow->next; 
            fast = fast->next; 
        } 
    } 
  
  	/* 'slow' esta antes do ponto medio da lista, entao divide-se em dois nesse ponto */
    *frontRef = source; 
    *backRef = slow->next; 
    slow->next = NULL; 

}

/* Ver https:// www.geeksforgeeks.org/?p=3622 para os detalhes desta funcao */

team_link SortedMerge(team_link a, team_link b) {

 	team_link result = NULL;
  
    if (a == NULL) /* casos basicos */
        return b; 
    else if (b == NULL) 
        return a; 
  
    /* Escolhe entre a ou b, e recursao */
    if (strcmp(a-> name, b-> name ) < 0) { 
        result = a; 
        result->next = SortedMerge(a->next, b); 
    } 
    else { 
        result = b; 
        result->next = SortedMerge(a, b->next); 
    } 
    return result; 

}

/* Ordena a lista de equipas alterando os next pointers (nao os dados) */

/* *********************** Ver https://www.geeksforgeeks.org/merge-sort-for-linked-list/ 
para os detalhes desta funcao ********************************************************* */

void MergeSort(team_link *teams_head) {

	team_link head = *teams_head;
	team_link a;
	team_link b;
  
    if ((head == NULL) || (head->next == NULL)) /* caso basico -- comprimento 0 ou 1 */
        return; 
  
    FrontBackSplit(head, &a, &b); /* divide head em sublistas 'a' e 'b' */
  
    MergeSort(&a); /* recursivamente ordenar as sublistas */
    MergeSort(&b); 
  

    *teams_head = SortedMerge(a, b); /* resposta = merge as duas listas ordenadas juntas */

}

/* Esta funcao liberta a memoria alocada de uma equipa qualquer. Um pointer para essa 
equipa e passado por argumento */

void FREE_team(team_link t){

	free(t->name);
	free(t);

}

/* Esta funcao liberta a memoria alocada de uma lista de equipas qualquer. Um pointer para 
a primeira equipa dessa lista e passado por argumento */

void free_teams(team_link *teams_head){
	
	team_link t, next_t;
	if (*teams_head != NULL){
		for (t = *teams_head, next_t = t->next; next_t != NULL; t = next_t, next_t = next_t->next)
			FREE_team(t);
		FREE_team(t);
	}
	*teams_head = NULL;

}



/*//////////////////////////////////////////////////////////////*/
/*////////////////////////////main//////////////////////////////*/
/*//////////////////////////////////////////////////////////////*/



/* Adiciona uma dada nova equipa a lista de equipas */

void adiciona_equipa(int *line, team_link *teams_head){
	char name[MAX_CHAR];
	scanf(" %[^\n]", name);

	if (teams_lookup(teams_head, name) == NULL)	
		insertBegin_team(teams_head, name);
	else
		printf("%d Equipa existente.\n", *line);

}

/* Procura uma equipa dado um nome na lista de equipas e faz print da tal */

void procura_equipa(int *line, team_link *teams_head, game_link *games_head){
	char name[MAX_CHAR];
	scanf(" %[^\n]", name);

	if (teams_lookup(teams_head, name) == NULL)
		printf("%d Equipa inexistente.\n", *line);
	else 
		printf("%d %s %d\n", *line, name, games_won(games_head, name));

}

/* Encontra as equipas na lista de equipas que ganharam mais jogos e lista por ordem 
lexicografica */

void melhores(int *line, team_link *teams_head, game_link *games_head){
	int wins = most_wins(teams_head, games_head); /* guarda o numero vitorias da equipa com mais jogos ganhos na lista de equipas */
	team_link teams_head_aux = NULL; /* pointer("head") para a primeira equipa da lista de equipas auxiliar */
	team_link t;

	if (*teams_head == NULL)
		return;

	teams_copy(teams_head, games_head, &teams_head_aux, &wins); /* copia equipas da lista de equipas para a lista de equipas auxilar com "wins" vitorias */
	MergeSort(&teams_head_aux); /* ordena a lista de equipas auxiliares por ordem lexicografica */

	printf("%d Melhores %d\n", *line, wins);
	for(t = teams_head_aux; t != NULL; t = t->next)
		printf("%d * %s\n", *line, t->name);
	free_teams(&teams_head_aux); /* liberta a memoria alocada da lista de equipas auxiliar */

}



/*//////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////////*/



/*//////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////////*/
/*\    /\    /\    /\    /\    /\    /\    /\    /\    /\    /\ */
/* \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \*/
/*  \/    \/    \/    \/    \/    \/    \/    \/    \/    \/    */












/*  /\    /\    /\    /\    /\    /\    /\    /\    /\    /\    */
/* /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  /*/
/*/    \/    \/    \/    \/    \/    \/    \/    \/    \/    \/ */
/*//////////////////////////////////////////////////////////////*/
/*///////////////////////adiciona_jogo//////////////////////////*/
/*/////////////////////////////&////////////////////////////////*/
/*////////////////////////lista_jogos///////////////////////////*/
/*/////////////////////////////&////////////////////////////////*/
/*///////////////////////procura_jogo///////////////////////////*/
/*/////////////////////////////&////////////////////////////////*/
/*////////////////////////apaga_jogo////////////////////////////*/
/*/////////////////////////////&////////////////////////////////*/
/*///////////////////////altera_score///////////////////////////*/
/*//////////////////////////////////////////////////////////////*/



/* Procura na lista de jogos um jogo no qual o nome do jogo corresponde a string 
passada por argumento. A funcao retorna o pointer do jogo encontrado. 
A funcao retorna NULL se nenhum jogo for encontrado */

game_link games_lookup(game_link *games_head, char* name){
	
	game_link g;
	for(g = *games_head; g != NULL; g = g->next)
		if(strcmp(g->name, name) == 0)
			return g;
	return NULL;

}

/* Funcao auxiliar responsavel pela alocacao de memoria de tudo o que e necessario 
para um novo jogo (struct game) */

game_link NEW_game(char* name, char* team1, char* team2, int score1, int score2){

	game_link g = (game_link) can_fail_malloc(sizeof(struct game));
	g->name = copy_string(name);
	g->team1 = copy_string(team1);
	g->team2 = copy_string(team2);
	g->score1 = score1; 
	g->score2 = score2; 
	g->next = NULL;
	return g;

}

/* Responsavel pela alocacao de memoria de tudo o que e necessario para um novo jogo 
e de o inserir no fim da lista de jogos */

void insertEnd_game(game_link *games_head, char* name, char* team1, char* team2, int score1, int score2){
	
	game_link g;

	if(*games_head == NULL){
		*games_head = NEW_game(name, team1, team2, score1, score2);
		return;
	}

	for(g = *games_head; g->next != NULL; g = g->next);
	g->next = NEW_game(name, team1, team2, score1, score2);

}

/* Esta funcao liberta a memoria alocada de um jogo qualquer. Um pointer para esse 
jogo e passado por argumento */

void FREE_game(game_link g){

	free(g->name);
	free(g->team1);
	free(g->team2);
	free(g);

}

/* Esta funcao remove da lista de jogos um jogo cujo nome corresponde a string 
passada por argumento */


void delete_game(game_link *games_head, char* name){

	game_link g, prev;
	for(g = *games_head, prev = NULL; g != NULL; prev = g, g = g->next){
		if(strcmp(g->name, name) == 0){
			if(g == *games_head)
				*games_head = g->next;
			else
				prev->next = g->next;
			FREE_game(g);	
			return;
		}
	}

}

/* Esta funcao altera os scores de um jogo da lista de jogos cujo nome, novo score1 
e novo score2 correspondem a string e os dois inteiros passados por argumento*/

void game_score(game_link *games_head, char* name, int score1, int score2){
	
	game_link g;
	g = games_lookup(games_head, name);
	g->score1 = score1; 
	g->score2 = score2; 

}



/*//////////////////////////////////////////////////////////////*/
/*////////////////////////////main//////////////////////////////*/
/*//////////////////////////////////////////////////////////////*/



/* Adiciona um dado novo jogo a lista de jogos */

void adiciona_jogo(int *line, team_link *teams_head, game_link *games_head){
	char name[MAX_CHAR], team1[MAX_CHAR], team2[MAX_CHAR];
	int score1, score2;
	scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", name, team1, team2, &score1, &score2);

	if (games_lookup(games_head, name) != NULL){
		printf("%d Jogo existente.\n", *line);
		return;
	}

	if (teams_lookup(teams_head, team1) == NULL || teams_lookup(teams_head, team2) == NULL){
		printf("%d Equipa inexistente.\n", *line);
		return;
	}
	
	insertEnd_game(games_head, name, team1, team2, score1, score2);

}

/* Lista todos os jogos na lista de jogos pela ordem em que foram introduzidos */

void lista_jogos(int *line, game_link *games_head){

	game_link g;
	for(g = *games_head; g != NULL; g = g->next)
		printf("%d %s %s %s %d %d\n", *line, g->name, g->team1 , g->team2, g->score1, g->score2);

}

/* Procura um jogo dado um nome na lista de jogos e faz print do tal */

void procura_jogo(int *line, game_link *games_head){
	char name[MAX_CHAR];
	game_link g;
	scanf(" %[^:\n]",name);

	if ((g = games_lookup(games_head, name)) == NULL)
		printf("%d Jogo inexistente.\n", *line);
	else 
		printf("%d %s %s %s %d %d\n", *line, g->name, g->team1 , g->team2, g->score1, g->score2);

}

/* Apaga um jogo da lista de jogos dado um nome */

void apaga_jogo(int *line, game_link *games_head){
	char name[MAX_CHAR];
	scanf(" %[^:\n]",name);

	if (games_lookup(games_head, name) == NULL)
		printf("%d Jogo inexistente.\n", *line);
	else 
		delete_game(games_head, name);

}

/* Altera o score de um jogo da lista de jogos dado o nome. */

void altera_score(int *line, game_link *games_head){
	char name[MAX_CHAR];
	int score1, score2;
	scanf(" %[^:\n]:%d:%d", name, &score1, &score2);

	if (games_lookup(games_head, name) == NULL)
		printf("%d Jogo inexistente.\n", *line);
	else 
		game_score(games_head, name, score1, score2);

}



/*//////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////////*/



/*//////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////////*/
/*\    /\    /\    /\    /\    /\    /\    /\    /\    /\    /\ */
/* \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \*/
/*  \/    \/    \/    \/    \/    \/    \/    \/    \/    \/    */












int main(){

	int line = 0; /* variavel para contabilizar as linhas */
	char comando;
	team_link teams_head = NULL; /* pointer("head") para a primeira equipa (struct team) da lista de equipas */
	game_link games_head = NULL; /* pointer("head") para o primeiro jogo (struct game) da lista de jogos */

	while(1){

		comando = getchar(); /* Le o comando. */

		switch(comando){

			case 'a':
				line++; /* atualiza o numero das linhas */
				adiciona_jogo(&line, &teams_head, &games_head);
				break;	
			case 'l':
				line++; /* atualiza o numero das linhas */
				lista_jogos(&line, &games_head);
				break;	
			case 'p':
				line++; /* atualiza o numero das linhas */
				procura_jogo(&line, &games_head);
				break;	
			case 'r':
				line++; /* atualiza o numero das linhas */
				apaga_jogo(&line, &games_head);
				break;	
			case 's':
				line++; /* atualiza o numero das linhas */
				altera_score(&line, &games_head);
				break;	
			case 'A':
				line++; /* atualiza o numero das linhas */
				adiciona_equipa(&line, &teams_head);
				break;
			case 'P':
				line++; /* atualiza o numero das linhas */
				procura_equipa(&line, &teams_head, &games_head);
				break;
			case 'g':
				line++; /* atualiza o numero das linhas */
				melhores(&line, &teams_head, &games_head);
				break;
			case 'x':
				return 0;
		}
	}

	return 1;
}











