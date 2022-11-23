#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"
#include "teams.h"
#include "games.h"

/* Este ficheiro (teams.c) e a parte do codigo que corresponde as funcoes para as equipas */


/* Esta funcao permite a inicializacao de um conjunto de listas ligadas, em que cada lista representa uma equipa. */

Teams * init_Tlist(){
	Teams * list = can_fail_malloc(sizeof(Teams));

	list->head = NULL;
	list->tail = NULL;
	return list;
}


/* Esta funcao permite a libertacao de toda a memoria alocada para o conjunto de listas ligadas das equipas. */

void destroy_Tlist(Teams * teams){
	team * team_aux;

	while (teams->head){
		team_aux = teams->head->next;
		free_team_node(teams->head);
		teams->head = team_aux;
	}
	free(teams);
}


/* Esta funcao permite a libertacao de toda a memoria alocada para a criacao de uma equipa (um no da lista ligada). */

void free_team_node(team * team_x){
	free(team_x->name);
	free(team_x);
}


/* Esta e uma das funcoes pedidas no projeto e corresponde ao comando 'A'.
	E responsavel por criar uma nova equipa no sistema, com a informacao recebida no input, apos ler o 'A'.
	Adiciona essa equipa no fim da lista ligada de equipas. */

void new_team(Teams * teams, HashTeams * hashtable, int NL){
	char team_name[MAXCHAR];
	scanf(" %[^\n]", team_name);

	if (hash_lookfor_team(hashtable, team_name) != NULL)
		printf("%d Equipa existente.\n", NL);
	
	else{
		team * new_team = alloc_team(team_name);
		add_last_team(teams, new_team);
		add_team_to_hash(new_team, hashtable);
	}
}

/* Esta e a funcao responsavel por alocar todoo espaco em memoria necessario para a criacao de uma nova equipa */

team * alloc_team(char team_name[MAXCHAR]){
	team * new_team = can_fail_malloc(sizeof(team));
	new_team->next = NULL;
	new_team->previous = NULL;

	new_team->name = can_fail_malloc(sizeof(char) * strlen(team_name)+1);
	strcpy(new_team->name, team_name);
	new_team->wins = 0;

	return new_team;
}


/* Esta e a funcao responsavel por adicionar uma nova equipa, no fim da lista ligada de equipas do sistema. */

void add_last_team(Teams * teams, team * new_team){

	if (teams->tail)
		teams->tail->next = new_team;
	else teams->head = new_team;

	new_team->previous = teams->tail;
	new_team->next = NULL;

	teams->tail = new_team;
}


/* Esta e uma das funcoes pedidas para desenvolver no enunciado do projeto, e corresponde ao comando 'P'.
	Quando este comando e lido esta funcao procura uma equipa no sistema, e devolve a informacao desta equipa, no
 caso de o encontrar. Caso contrario devolve NULL, de maneira a nao dar erro. */

void lookfor_team(HashTeams * hashtable, int NL){
	char team_name[MAXCHAR];
	team * team_x; 

	scanf(" %[^\n]", team_name);
	team_x = hash_lookfor_team(hashtable, team_name);

	if (team_x != NULL)
		printf("%d %s %d\n", NL, team_x->name, team_x->wins);

	else printf("%d Equipa inexistente.\n", NL);
}



/* Esta funcao e uma das pedidas para desenvolver no enunciado do projeto e corresponde ao comando 'g'.
	E responsavel por listar todas as equipas com o maior numero de vitorias. */

void find_most_winning_teams(Teams * teams, int NL){
	team * team_x;
	int max_wins = 0, init_size = 100, i = 0;
	team ** W_teams = can_fail_malloc(sizeof(team *) * init_size);

	for (team_x = teams->head ; team_x != NULL ; team_x = team_x->next){

		if (team_x->wins > max_wins){
			max_wins = team_x->wins;

			clean_winning_teams(W_teams, i);
			i = 0;

			W_teams[i] = team_x;
			i++;
		}
		else if (team_x->wins == max_wins){
			W_teams[i] = team_x;
			i++;
		}
	}

	quicksort_teams(W_teams, 0, i-1);
	print_winning_teams(W_teams, i, NL, max_wins);
	free(W_teams);
}


/* Esta funcao e responsavel por ordenar as equipas por ordem alfabetica ou lexicografica do seu nome. */

void quicksort_teams(team ** W_teams, int l, int r){
	int i;
	if (r <= l) return;

	i = partition(W_teams, l, r);
	quicksort_teams(W_teams, l, i-1);
	quicksort_teams(W_teams, i+1, r);
}

/* Esta funcao faz parte da funcao quicksort */

int partition(team ** W_teams, int l, int r){
	int i = l-1;
	int j = r;
	team * v = W_teams[r];

	while (i < j){

		while(less(W_teams[++i]->name, v->name));
		while(less(v->name, W_teams[--j]->name)){
			if (j == l)
				break;
		}
		if (i < j)
			exch(W_teams[i], W_teams[j]);
	}
	exch(W_teams[i], W_teams[r]);
	return i;
}


/* Esta funcao e responsavel por limpar todos os slots com os nomes das equipas que tinham o maior numero de vitorias,
	para dar lugar as novas equipas com numero maior de vitorias , pois max_wins e maior que anteriormente. */

void clean_winning_teams(team ** W_teams, int i){
	int aux;
	for (aux = 0; aux < i; aux++)
		W_teams[aux] = NULL;
}


/* Esta funcao e responsavel por devolver a lista de todas as equipas com maior numero de vitorias. */

void print_winning_teams(team ** W_teams, int i, int NL, int max_wins){
	int aux;
	if (i > 0){
		printf("%d Melhores %d\n", NL, max_wins);
		for (aux = 0; aux < i; aux++)
			printf("%d * %s\n", NL, W_teams[aux]->name);
	}
}



/* Esta funcao e responsavel por remover as vitoria respetiva ao vencedor desse jogo, quando se apaga um jogo. */

void remove_team_win(HashTeams * hashtable_teams, char * winner){
	team * team_x = hash_lookfor_team(hashtable_teams, winner);
	team_x->wins -= 1;
}


/* Esta funcao e responsavel por adicionar uma vitoria ao vencedor de um jogo, quando se altera o score. */

void add_team_win(HashTeams * hashtable_teams, char * new_winner){
	team * team_x = hash_lookfor_team(hashtable_teams, new_winner);
	team_x->wins += 1;
}




/* %%%%%%%%%%%%%%%%%%% Espaco correspondente as funcoes da hashtable das equipas %%%%%%%%%%%%%%%%%%%%% */


/* Esta funcao inicializa uma hashtable para as equipas com todos os slots vazios, 
 	capacidade (numero maximo de elementos) recebida no argumento e tamanho 0. */

HashTeams * init_HTtable(int size){
	int i;
	HashTeams * hashtable = can_fail_malloc(sizeof(HashTeams));
	hashtable->slots = can_fail_malloc(sizeof(team *) * size);
	hashtable->size = 0;
	hashtable->cap = size;
	for (i = 0; i < hashtable->cap; i++)
		hashtable->slots[i] = NULL;

	return hashtable;
}


/* Esta funcao permite a libertacao de toda a memoria alocada para a criacao de uma hashtable para equipas. */

void destroy_HTtable(HashTeams * hashtable){
	free(hashtable->slots);
	free(hashtable);
}


/* Esta funcao permite que seja inserido uma equipa na hashtable. */
/* h representa o index na hashtable, inc o incremento quando a posicao h ja esta ocupada */

void add_team_to_hash(team * team_x, HashTeams * hashtable){

	int h = hash(team_x->name, hashtable->cap);
	int inc = (1 + 3 * h) % hashtable->cap;
	if (inc == 0) inc++;

	while(hashtable->slots[h] != NULL)
		h = (h + inc) % hashtable->cap;

	hashtable->slots[h] = team_x;
	hashtable->size++;
	
	if (hashtable->size > hashtable->cap/2)
		resize_hashtable_teams(hashtable);
}


/* Esta e a funcao responsavel por procurar um jogo na hashtable. */

team * hash_lookfor_team(HashTeams * hashtable, char * name){
	int h = hash(name, hashtable->cap);
	int inc = (1 + 3 * h) % hashtable->cap;
	if (inc == 0) inc++;

	while(hashtable->slots[h] != NULL){

		if (strcmp((hashtable->slots[h])->name, name) == 0)
			return hashtable->slots[h];

		else h = (h + inc) % hashtable->cap;
	}
	return NULL;
}


/* Esta funcao e responsavel por aumentar o tamanho da hashtable equipas de maneira a haver sempre slots livres. */

void resize_hashtable_teams(HashTeams * hashtable){
	int new_cap;
	team ** new_slots;
	team ** old_slots = hashtable->slots;

	new_cap = (hashtable->cap * 2);
	while (eh_primo(new_cap) != 1)
 		new_cap++;

 	new_slots = can_fail_malloc(sizeof(team *) * new_cap);

 	init_new_team_slots(new_slots, new_cap);

 	rehash_teams(hashtable, new_slots, old_slots, new_cap);

	hashtable->slots = new_slots;
	hashtable->cap = new_cap;
	free(old_slots);
}



/* Esta funcao inicializa todos os slots a null, na nova hashtable das equipas */ 

void init_new_team_slots(team ** new_slots, int new_cap){
	int i;
	for (i = 0; i < new_cap; i++)
		new_slots[i] = NULL;
}



/* Esta funcao e responsavel por colocar os elementos da antiga hashtable das equipas na nova, com o novo hashcode */

void rehash_teams(HashTeams * hashtable, team ** new_slots, team ** old_slots, int new_cap){
	int i, inc, h;

	for(i = 0; i < hashtable->cap; i++){
		if (old_slots[i] != NULL){

			h = hash(old_slots[i]->name, new_cap);
			inc = (1 + 3 * h) % new_cap;
			if (inc == 0) inc++;

			while(new_slots[h] != NULL)
				h = (h + inc) % new_cap;

			new_slots[h] = old_slots[i];
		}
	}
}