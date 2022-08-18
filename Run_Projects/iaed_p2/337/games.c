#include "hash.h"
#include "teams.h"
#include "games.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Este ficheiro (games.c) e a parte do codigo que corresponde as funcoes para os jogos1 */


/* Esta funcao permite a inicializacao de um conjunto de listas ligadas, em que cada lista representa um jogo. */

Games * init_Glist(){
	Games * list = malloc(sizeof(Games));

	list->head = NULL;
	list->tail = NULL;
	return list;
}


/* Esta funcao permite a libertacao de toda a memoria alocada para o conjunto de listas ligadas dos jogos */

void destroy_Glist(Games * games){
	game * game_aux;

	while (games->head){
		game_aux = games->head->next;
		free_game_node(games->head);
		games->head = game_aux;
	}
	free(games);
}


/* Esta funcao permite a libertacao de toda a memoria alocada para a criacao de um jogo - corresponde a um no */

void free_game_node(game * game_x){
	free(game_x->name);
	free(game_x->t1_name);
	free(game_x->t2_name);
	free(game_x->winner);
	free(game_x);
}


/* Esta e uma das funcoes pedidas no projeto e corresponde ao comando 'a'.
E responsavel por criar um jogo novo, com a informacao recebida no input, apos ler o 'a'.
Adicionando esse jogo ao fim da lista ligada de jogos. */

void new_game(Games * games, HashGames * hashtable_games, HashTeams * hashtable_teams, int NL){
	char game_name[MAXCHAR], t1_name[MAXCHAR], t2_name[MAXCHAR];
	int score_t1, score_t2;

	scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", game_name, t1_name, t2_name, &score_t1, &score_t2);

	if (verify_conditions_to_add_game(NL, game_name, t1_name, t2_name, hashtable_games, hashtable_teams) != 0){
		game * new_game = alloc_game(game_name, t1_name, t2_name, score_t1, score_t2);
		add_last_game(games, new_game);
		add_game_to_hash(new_game, hashtable_games);

		if (strcmp(new_game->winner, "NONE") != 0) sum_win_in_team(new_game->winner, hashtable_teams);
	}
}


/* Esta funcao verifica se as condicoes, de acordo com o enunciado do projeto, estao reunidas para um novo jogo ser
 adicionado a lista de jogos. Caso nao se verifiquem retorna False (0) e da print do erro correspondido.
 Claro que caso se verifiquem retorna True (1), e nao printa nada. */

int verify_conditions_to_add_game(int NL, char game_name[MAXCHAR], char t1_name[MAXCHAR], char t2_name[MAXCHAR], 
	HashGames * hashtable_games, HashTeams * hashtable_teams){

	game * game_x = hash_lookfor_game(hashtable_games, game_name);
	team * team1, * team2;
	
	if (game_x != NULL) printf("%d Jogo existente.\n", NL);

	team1 = hash_lookfor_team(hashtable_teams, t1_name);
	team2 = hash_lookfor_team(hashtable_teams, t2_name);

	if (game_x == NULL && (team1 == NULL || team2 == NULL))
		printf("%d Equipa inexistente.\n", NL);

	return team1 != NULL && team2 != NULL && game_x == NULL;
}



/* Esta funcao aloca todo o espaco na memoria necessario para a criacao de um novo jogo, e a sua respetiva insercao
 na lista ligada de jogos. Para alem disso guarda ja os dados do jogo no novo no criado (new_game). */

game * alloc_game(char game_name[MAXCHAR], char t1_name[MAXCHAR], char t2_name[MAXCHAR], int score_t1, int score_t2){
	game * new_game = malloc(sizeof(game));
	char winner[MAXCHAR];
	new_game->next = NULL;
	new_game->previous = NULL;

	new_game->name = malloc(sizeof(char) * (strlen(game_name) + 1));
	strcpy(new_game->name, game_name);

	new_game->t1_name = malloc(sizeof(char) * (strlen(t1_name)+ 1));
	strcpy(new_game->t1_name, t1_name);

	new_game->t2_name = malloc(sizeof(char) * (strlen(t2_name)+ 1));
	strcpy(new_game->t2_name, t2_name);

	new_game->score_t1 = score_t1;
	new_game->score_t2 = score_t2;
	
	strcpy(winner, choose_winner(score_t1, score_t2, t1_name, t2_name));
	new_game->winner = malloc(sizeof(char) * (strlen(winner) + 1));
	strcpy(new_game->winner, winner);

	return new_game;
}


/* Esta funcao e e responsavel por escolher a equipa vencedora e devolver o seu nome. */

char * choose_winner(int score_t1, int score_t2, char * t1_name, char * t2_name){

	if (score_t1 > score_t2)
		return t1_name;
	
	else if (score_t2 > score_t1)
		return t2_name;
	
	else return "NONE";
}


/* Esta funcao e responsavel por adicionar um novo no (jogo) no fim da lista ligada de jogos */
/* Nota: nao coloco no linkedlist.h pois tem que receber um argumento tipo game e seria impossivel a abstracao. */

void add_last_game(Games * games, game * new_game){

	if (games->tail)
		games->tail->next = new_game;

	else games->head = new_game;

	new_game->previous = games->tail;
	new_game->next = NULL;

	games->tail = new_game;
}


/* Esta e uma das funcoes pedidas para desenvolver no projeto, correspondente ao comando 'l'.
 Quando este comando e lido esta funcao e efetuada, com o intuito de listar todos os jogos ja guardados no sistema. */

void show_all_games(Games * games, int NL){
	game * game_x;

	for (game_x = games->head; game_x != NULL; game_x = game_x->next)
		printf("%d %s %s %s %d %d\n", NL, game_x->name, game_x->t1_name, game_x->t2_name, game_x->score_t1, game_x->score_t2);
}


/* Esta e uma das funcoes pedidas para desenvolver no enunciado do projeto, e corresponde ao comando 'p'.
	Quando este comando e lido esta funcao procura um jogo no sistema, e devolve a informacao deste jogo, no caso
 de o encontrar. Caso contrario devolve NULL, de maneira a nao dar erro. */

void lookfor_game(HashGames * hashtable, int NL){
	char game_name[MAXCHAR];
	game * game_x; 

	scanf(" %[^\n]", game_name);

	game_x = hash_lookfor_game(hashtable, game_name);

	if (game_x != NULL)
		printf("%d %s %s %s %d %d\n", NL, game_x->name, game_x->t1_name, game_x->t2_name, game_x->score_t1, game_x->score_t2);

	else printf("%d Jogo inexistente.\n", NL);
}



/* Esta funcao e responsavel por somar 1 vitoria na estutura correspondente a equipa recebida no argumento */

void sum_win_in_team(char * team_name, HashTeams * hashtable_teams){

	team * team_x = hash_lookfor_team(hashtable_teams, team_name);
	team_x->wins += 1;
}



/* Esta funcao e uma das pedidas no desenvolvimento do projeto, e e efetuada quando se recebe o comando 'r'.
	Ela e responsavel por apagar um no da lista ligada dos jogos e tambem libertar o seu slot na hashtable, 
 correspondendo estas acoes ao que e pedido quando se diz para apagar um jogo. */ 

void remove_game(Games * games, HashGames * hashtable, int NL, HashTeams * hashtable_teams){
	char game_name[MAXCHAR];
	game * game_x;
	scanf(" %[^\n]", game_name);
	game_x = hash_lookfor_game(hashtable, game_name);

	if (game_x != NULL){
		int h = hash(game_x->name, hashtable->cap);
		int inc = (1 + 3 * h) % hashtable->cap;
		if (inc == 0) inc++;

		while(hashtable->slots[h].game_slot != NULL || hashtable->slots[h].occ == 1){

			if (hashtable->slots[h].game_slot != NULL && strcmp(hashtable->slots[h].game_slot->name, game_name) == 0){
				if (strcmp(game_x->winner, "NONE") != 0)
					remove_team_win(hashtable_teams, game_x->winner);

				erase_game_node(games, game_x, hashtable, h);
			}
			else h = (h + inc) % hashtable->cap;
		}
	}
	else printf("%d Jogo inexistente.\n", NL);
}


/* Esta funcao e responsavel por apagar o no da lista ligada dos jogos, correspondente ao jogo recebido 
no argumento da funcao, e recolocar o slot na hashtable a NULL. */

void erase_game_node(Games * games, game * game_x, HashGames * hashtable, int h){
	if (game_x->previous == NULL)
		games->head = game_x->next;
	else game_x->previous->next = game_x->next;

	if (game_x->next == NULL)
		games->tail = game_x->previous;
	else game_x->next->previous = game_x->previous;

	free_game_node(game_x);
	hashtable->slots[h].game_slot = NULL;
}



/* Esta funcao pedida no desenvolvimento do projeto, sendo executada quando o comando 's' e lido.
	A funcao e responsavel por alterar o score de um jogo, para o score recebido no input. */

void change_game_score(HashGames * hashtable_games, HashTeams * hashtable_teams, int NL){
	char game_name[MAXCHAR], new_winner[MAXCHAR];
	int score_t1, score_t2;
	game * game_x;

	scanf(" %[^:]:%d:%d", game_name, &score_t1, &score_t2);

	game_x = hash_lookfor_game(hashtable_games, game_name);

	if (game_x != NULL){
		strcpy(new_winner, choose_winner(score_t1, score_t2, game_x->t1_name, game_x->t2_name));

		if (strcmp(new_winner, game_x->winner) != 0)
			change_winner(game_x, new_winner, hashtable_teams);

		game_x->score_t1 = score_t1;
		game_x->score_t2 = score_t2;
	}
	else printf("%d Jogo inexistente.\n", NL);
}


/* Esta e a funcao responsavel por alterar o vencedor de um jogo na estrutura da sua equipa.
	Sendo que se hovuer um empate nao altera nada. */

void change_winner(game * game_x, char * new_winner, HashTeams * hashtable_teams){

	if (strcmp(game_x->winner, "NONE") != 0)
		remove_team_win(hashtable_teams, game_x->winner);

	if (strcmp(new_winner, "NONE") != 0)
		add_team_win(hashtable_teams, new_winner);

	free(game_x->winner);
	game_x->winner = malloc(sizeof(char) * (strlen(new_winner) + 1));
	strcpy(game_x->winner, new_winner);
}



/* %%%%%%%%%%%%%%%%%%% Espaco correspondente as funcoes da hashtable dos jogos. %%%%%%%%%%%%%%%%%%%%% */


/* Esta funcao inicializa uma hashtable para os jogos com todos os slots vazios, 
 	capacidade (numero maximo de elementos) recebida no argumento e tamanho 0. */

HashGames * init_HGtable(int size){
	int i;
	HashGames * hashtable = malloc(sizeof(HashGames));
	hashtable->slots = malloc(sizeof(Slot) * size);
	hashtable->size = 0;
	hashtable->cap = size;
	for (i = 0; i < hashtable->cap; i++){
		hashtable->slots[i].occ = 0;
		hashtable->slots[i].game_slot = NULL;
	}

	return hashtable;
}


/* Esta funcao permite a libertacao de toda a memoria alocada para a criacao de uma hashtable para jogos. */

void destroy_HGtable(HashGames * hashtable){
	free(hashtable->slots);
	free(hashtable);
}


/* Esta funcao permite que seja inserido um jogo na hashtable. */
/* h representa o index na hashtable, inc o incremento quando a posicao h ja esta ocupada */

void add_game_to_hash(game * game_x, HashGames * hashtable){

	int h = hash(game_x->name, hashtable->cap);
	int inc = (1 + 3 * h) % hashtable->cap;
	if (inc == 0) inc++;

	while(hashtable->slots[h].game_slot != NULL)
		h = (h + inc) % hashtable->cap;

	hashtable->slots[h].game_slot = game_x;
	hashtable->slots[h].occ = 1;
	hashtable->size++;

	if (hashtable->size > hashtable->cap/2)
		resize_hashtable_games(hashtable);
}


/* Esta e a funcao responsavel por procurar um jogo na hashtable. */

game * hash_lookfor_game(HashGames * hashtable, char * name){
	int h = hash(name, hashtable->cap);
	int inc = (1 + 3 * h) % hashtable->cap;
	if (inc == 0) inc++;

	while(hashtable->slots[h].game_slot != NULL || hashtable->slots[h].occ == 1){
	
		if (hashtable->slots[h].game_slot != NULL && strcmp(hashtable->slots[h].game_slot->name, name) == 0)
			return hashtable->slots[h].game_slot;

		else h = (h + inc) % hashtable->cap;
	}
	return NULL;
}


/* Esta funcao e responsavel por aumentar o tamanho da hashtable dos jogos de maneira a haver sempre slots livres.*/

void resize_hashtable_games(HashGames * hashtable){
	int new_cap, new_size = 0;
	Slot * new_slots;
	Slot * old_slots = hashtable->slots;

	new_cap = (hashtable->cap * 2);
	while (eh_primo(new_cap) != 1)
 		new_cap++;

 	new_slots = malloc(sizeof(Slot) * new_cap);

 	init_new_slots(new_slots, new_cap);

	rehash_games(hashtable, new_slots, old_slots, new_cap, new_size);

	hashtable->slots = new_slots;
	hashtable->cap = new_cap;
	hashtable->size = new_size;
	free(old_slots);
}


/* Esta funcao inicializa todos os slots a null e occ a 0, na nova hashtable dos jogos */ 

void init_new_slots(Slot * new_slots, int new_cap){
	int i;

	for (i = 0; i < new_cap; i++){
		new_slots[i].occ = 0;
		new_slots[i].game_slot = NULL;
	}
}


/* Esta funcao e responsavel por colocar os elementos da antiga hashtable dos jogos na nova, com o novo hashcode */

void rehash_games(HashGames * hashtable, Slot * new_slots, Slot * old_slots, int new_cap, int new_size){
	int i, h, inc;

	for(i = 0; i < hashtable->cap; i++){
		if (old_slots[i].game_slot != NULL){
			new_size++;

			h = hash(old_slots[i].game_slot->name, new_cap);
			inc = (1 + 3 * h) % new_cap;
			if (inc == 0) inc++;

			while(new_slots[h].game_slot != NULL)
				h = (h + inc) % new_cap;

			new_slots[h].game_slot = old_slots[i].game_slot;
			new_slots[h].occ = 1;
		}
	}
}