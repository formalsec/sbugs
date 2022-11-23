#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 1024
#define HT_SIZE 1571
#define MAX_IN 3500

/************************************************************/
/************************************************************/
/*                                                          */
/*                        ESTRUTURAS                        */
/*                                                          */
/************************************************************/
/************************************************************/

/* Estrutura de um jogo: */

typedef struct game{
	char *name, *team1, *team2;
	int score1, score2;
}p_game;

/* Estrutura de um node pertencente a linked list que engloba os jogos com a mesma hash key: */

typedef struct node_game{
	p_game *g;
	struct node_game *prev;
	struct node_game *next;
}link_game;

/*********************************************************************************************************************************/

/* Estrutura de uma equipa: */

typedef struct team{
	char *name;
	int vict;
}p_team;

/* Estrutura de um node pertencente a linked list que engloba as equipas com a mesma hash key: */

typedef struct node_team{
	p_team *t;
	struct node_team *prev;
	struct node_team *next;
}link_team;

/*********************************************************************************************************************************/

/* Estrutura de um node pertencente a linked list usada para obter os jogos ordenados pela ordem de insercao */

typedef struct ordered_games{
	p_game *g;
	struct ordered_games *prev;
	struct ordered_games *next;
}link_ord_games;

/*********************************************************************************************************************************/

/*********************************************************************************************************************************/

/* Estrutura de um node pertencente a linked list usada para obter as equipas ordenadas pela quantidade de vitorias */

typedef struct ordered_teams{
	p_team *t;
	struct ordered_teams *prev;
	struct ordered_teams *next;
}link_ord_teams;

/*********************************************************************************************************************************/

/************************************************************/
/************************************************************/
/*                                                          */
/*                    VARIAVEIS GLOBAIS                     */
/*                                                          */
/************************************************************/
/************************************************************/

static link_game **head_game;
static link_team **head_team;
static link_ord_games *head_ord_games;
static link_ord_teams *head_ord_teams;

/************************************************************/
/************************************************************/
/*                                                          */
/*                   FUNCOES DE ORDENACAO                   */
/*                                                          */
/************************************************************/
/************************************************************/
 
/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves, 
    and return the two lists using the reference parameters. 
    If the length is odd, the extra node should go in the front list. 
    Uses the fast/slow pointer strategy. */

void Partition(link_ord_teams *source, link_ord_teams **frontRef, link_ord_teams **backRef){

    link_ord_teams *fast; 
    link_ord_teams *slow; 
    slow = source; 
    fast = source->next; 
  
    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL) { 
        fast = fast->next; 
        if (fast != NULL) { 
            slow = slow->next; 
            fast = fast->next; 
        } 
    } 
  
    /* 'slow' is before the midpoint in the list, so split it in two 
    at that point. */
    *frontRef = source; 
    *backRef = slow->next; 
    slow->next = NULL; 
}

/* See https:// www.geeksforgeeks.org/?p=3622 for details of this  
function */
link_ord_teams * SortedMerge(link_ord_teams *a, link_ord_teams *b) 
{ 
    link_ord_teams *result = NULL; 
  
    /* Base cases */
    if (a == NULL) 
        return b; 
    else if (b == NULL) 
        return a; 
  
    /* Pick either a or b, and recur */
    if (b->t->vict < a->t->vict || ((b->t->vict == a->t->vict) && (strcmp(a->t->name, b->t->name) < 0))) { 
        result = a; 
        result->next = SortedMerge(a->next, b); 
    } 
    else { 
        result = b; 
        result->next = SortedMerge(a, b->next); 
    } 
    return result; 
} 

/* sorts the linked list by changing next pointers (not data) */
void MergeSort(link_ord_teams **headRef) 
{ 
    link_ord_teams *head = *headRef; 
    link_ord_teams *a; 
    link_ord_teams *b; 
  
    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->next == NULL)) { 
        return; 
    } 
  
    /* Split head into 'a' and 'b' sublists */
    Partition(head, &a, &b); 
  
    /* Recursively sort the sublists */
    MergeSort(&a); 
    MergeSort(&b); 
  
    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b); 
} 

/************************************************************/
/************************************************************/
/*                                                          */
/*                  FUNCOES DA HASH TABLE                   */
/*                                                          */
/************************************************************/
/************************************************************/

/* Hash function que retorna a hash key de um determinado nome */

int hash(char *p){
	int key, a = 31415, b = 27183;

	for (key = 0; *p != '\0'; p++, a = a * b % (HT_SIZE - 1)){
		key = (a * key + *p) % HT_SIZE;
	}	
		return key;
}

/***************************************************************/

/* Funcao que inicia as duas hash tables. A dos jogos e a das equipas. */

void Init_ht(){
	int key;
	head_game = can_fail_malloc(HT_SIZE * sizeof(link_game));
	head_team = can_fail_malloc(HT_SIZE * sizeof(link_team));
	head_ord_games = NULL;
	head_ord_teams = NULL;
	for (key = 0; key < HT_SIZE; key++){
		head_game[key] = NULL;
		head_team[key] = NULL;
	}	
}

/********************************************/
/* FUNCOES RELATIVAS A HASH TABLE DOS JOGOS */
/********************************************/

void ht_insert_game(p_game *g, int key){
	link_game *next_game = can_fail_malloc(sizeof(link_game));

	next_game->g = g;
	next_game->next = head_game[key];
	next_game->prev = NULL;
	if (head_game[key] != NULL) head_game[key]->prev = next_game;
	head_game[key] = next_game;
}

/******************************************************************/

link_game * ht_find_game(char *name, int key){
	link_game *ptr = NULL;

	if (head_game[key] != NULL){
		ptr = head_game[key];

		while (ptr != NULL){
			if (strcmp(ptr->g->name, name) == 0)
				return ptr;
			ptr = ptr->next;
		}
	}	
	return NULL;
}

/**********************************************/
/* FUNCOES RELATIVAS A HASH TABLE DAS EQUIPAS */
/**********************************************/

void ht_insert_team(p_team *t, int key){
	link_team *next_team = can_fail_malloc(sizeof(link_team));

	next_team->t = t;
	next_team->next = head_team[key];
	next_team->prev = NULL;
	if (head_team[key] != NULL) head_team[key]->prev = next_team;
	head_team[key] = next_team;
}

/******************************************************************/

link_team * ht_find_team(char *name, int key){
	link_team *ptr = NULL;
	
	if (head_team[key] != NULL){
		ptr = head_team[key];

		while (ptr != NULL){
			if (strcmp(ptr->t->name, name) == 0)
				return ptr;
			ptr = ptr->next;
		}
	}	
	return NULL;
}

/*********************************************************************************************************************************/

void insert_ord_games(p_game *g){
	link_ord_games *ptr = can_fail_malloc(sizeof(link_ord_games));

	ptr->g = g;
	ptr->prev = NULL;

	if (head_ord_games == NULL){
		ptr->next = NULL;
	}
	else{
		ptr->next = head_ord_games;
		head_ord_games->prev = ptr;
	}
	head_ord_games = ptr;
}

void insert_ord_teams(p_team *t){
	link_ord_teams *ptr = can_fail_malloc(sizeof(link_ord_teams));

	ptr->t = t;
	ptr->prev = NULL;

	if (head_ord_teams == NULL){
		ptr->next = NULL;
	}
	else{
		ptr->next = head_ord_teams;
		head_ord_teams->prev = ptr;
	}
	head_ord_teams = ptr;
}


/************************************************************/
/************************************************************/
/*                                                          */
/*               FUNCOES RELATIVAS AOS COMANDOS             */
/*                                                          */
/************************************************************/
/************************************************************/


void add_game(char * input, int nl){
	char game_name[MAX_STRING], team_1[MAX_STRING], team_2[MAX_STRING];
	int score_1 = 0, score_2 = 0;
	int key_game, key_team_1, key_team_2;
	p_game *game = can_fail_malloc(sizeof(p_game));

	sscanf(input, "%[^:\n]:%[^:\n]:%[^:\n]:%d:%d", game_name, team_1, team_2, &score_1, &score_2);
	key_game = hash(game_name);
	key_team_1 = hash(team_1);
	key_team_2 = hash(team_2);

	if (ht_find_game(game_name, key_game) != NULL)
		printf("%d Jogo existente.\n", nl);
	else if (ht_find_team(team_1, key_team_1) == NULL || ht_find_team(team_2, key_team_2) == NULL)
		printf("%d Equipa inexistente.\n", nl);
	else{
		game->name = can_fail_malloc(sizeof(char) * (strlen(game_name) + 1));
		game->team1 = can_fail_malloc(sizeof(char) * (strlen(team_1) + 1));
		game->team2 = can_fail_malloc(sizeof(char) * (strlen(team_2) + 1));
		strcpy(game->name, game_name);
		strcpy(game->team1, team_1);
		strcpy(game->team2, team_2);
		game->score1 = score_1;
		game->score2 = score_2;
		if (score_1 > score_2)
			ht_find_team(team_1, key_team_1)->t->vict++;
		else if (score_2 > score_1)
			ht_find_team(team_2, key_team_2)->t->vict++;
		ht_insert_game(game, key_game);
		insert_ord_games(game);
	}
}

void find_game(char input[MAX_IN], int nl){
	char game_name[MAX_STRING];
	int key;
	link_game *node = NULL;

	sscanf(input, "%[^:\n]", game_name);
	key = hash(game_name);
	node = ht_find_game(game_name, key);
	if (node == NULL) printf("%d Jogo inexistente.\n", nl);
	else{
		printf("%d %s %s %s %d %d\n", nl, node->g->name, node->g->team1, node->g->team2, node->g->score1, node->g->score2);
	}	
}

void list_games(int nl){
	link_ord_games *ptr = NULL;

	ptr = head_ord_games;
	if (ptr != NULL){
		while (ptr->next != NULL) ptr = ptr->next;
		while (ptr != NULL){
			printf("%d %s %s %s %d %d\n", nl, ptr->g->name, ptr->g->team1, ptr->g->team2, ptr->g->score1, ptr->g->score2);
			ptr = ptr->prev;
		}
	}	
}

void remove_game(char input[MAX_IN], int nl){
	char game_name[MAX_STRING];
	int key, key_t1, key_t2;
	link_game *node = NULL;
	link_ord_games *node_ord = NULL;
	link_team *node_t1 = NULL;
	link_team *node_t2 = NULL;	

	sscanf(input, "%[^:\n]", game_name);
	key = hash(game_name);
	if (ht_find_game(game_name, key) == NULL) printf("%d Jogo inexistente.\n", nl);
	else{
		node = ht_find_game(game_name, key);
		node_ord = head_ord_games;
		key_t1 = hash(node->g->team1);
		key_t2 = hash(node->g->team2);
		node_t1 = head_team[key_t1];
		node_t2 = head_team[key_t2];

		if (node->g->score1 > node->g->score2) node_t1->t->vict--;
		else if (node->g->score1 < node->g->score2) node_t2->t->vict--;

		while (strcmp(node_ord->g->name, game_name) != 0) node_ord = node_ord->next;
		if (node_ord->prev != NULL && node_ord->next != NULL){
			node_ord->prev->next = node_ord->next;
			node_ord->next->prev = node_ord->prev;
		}
		else if (node_ord->prev == NULL && node_ord->next != NULL){
			head_ord_games = node_ord->next;
			head_ord_games->prev = NULL;
		}
		else if (node_ord->prev == NULL && node_ord->next == NULL) head_ord_games = NULL;
		else node_ord->prev->next = NULL;

		if (node->prev != NULL && node->next != NULL){
			node->prev->next = node->next;
			node->next->prev = node->prev;
		}
		else if (node == head_game[key] && node->next != NULL){
			head_game[key] = node->next;
			head_game[key] = NULL;
		}
		else if (node == head_game[key] && node->next == NULL) head_game[key] = NULL;
		else node->prev->next = NULL;

		free(node->g->name);
		free(node->g->team1);
		free(node->g->team2);
		free(node->g);

		free(node);
		node = NULL;

		free(node_ord);
		node_ord = NULL;
	}
}	

void change_score(char input[MAX_IN], int nl){
	char game_name[MAX_STRING];
	int key, score_1 = 0, score_2 = 0, key_t1, key_t2;
	link_game *node = NULL;
	link_team *node_t1 = NULL;
	link_team *node_t2 = NULL;

	sscanf(input, "%[^:\n]:%d:%d", game_name, &score_1, &score_2);
	key = hash(game_name);

	if (ht_find_game(game_name, key) == NULL) printf("%d Jogo inexistente.\n", nl);

	else{
		node = head_game[key];
		key_t1 = hash(node->g->team1);
		key_t2 = hash(node->g->team2);
		node_t1 = head_team[key_t1];
		node_t2 = head_team[key_t2];
		while(strcmp(node_t1->t->name, node->g->team1) != 0) node_t1 = node_t1->next;
		while(strcmp(node_t2->t->name, node->g->team2) != 0) node_t2 = node_t2->next;

		if (node->g->score1 > node->g->score2 && score_1 < score_2){
			node_t1->t->vict--;
			node_t2->t->vict++;
		}
		else if (node->g->score1 < node->g->score2 && score_1 > score_2){
			node_t1->t->vict++;
			node_t2->t->vict--;			
		}
		else if (node->g->score1 > node->g->score2 && score_1 == score_2) node_t1->t->vict--;
		else if (node->g->score1 < node->g->score2 && score_1 == score_2) node_t2->t->vict--;
		else if (node->g->score1 == node->g->score2 && score_1 > score_2) node_t1->t->vict++;
		else if (node->g->score1 == node->g->score2 && score_1 < score_2) node_t2->t->vict++;

		while (strcmp(node->g->name, game_name) != 0) node = node->next;
		node->g->score1 = score_1;
		node->g->score2 = score_2;
	}	
}

void add_team(char input[MAX_IN], int nl){
	char team_name[MAX_STRING];
	int key;
	p_team *team = can_fail_malloc(sizeof(p_team));

	sscanf(input, "%[^:\n]", team_name);
	key = hash(team_name);
	if (ht_find_team(team_name, key) != NULL)
		printf("%d Equipa existente.\n", nl);
	else{
		team->name = can_fail_malloc(sizeof(char) * (strlen(team_name) + 1));
		strcpy(team->name, team_name);
		team->vict = 0;
		ht_insert_team(team, key);
		insert_ord_teams(team);
	}
}

void find_team(char input[MAX_IN], int nl){
	char team_name[MAX_STRING];
	int key;
	link_team *node = NULL;

	sscanf(input, "%[^:\n]", team_name);
	key = hash(team_name);
	node = ht_find_team(team_name, key);
	if (node == NULL) printf("%d Equipa inexistente.\n", nl);
	else{
		printf("%d %s %d\n", nl, node->t->name, node->t->vict);
	}	
}

void list_teams(int nl){
	link_ord_teams *ptr = NULL;
	int score_max;

	if (head_ord_teams != NULL){
		MergeSort(&head_ord_teams);
		ptr = head_ord_teams;
		printf("%d Melhores %d\n", nl, ptr->t->vict);
		score_max = ptr->t->vict;
		while (ptr != NULL && ptr->t->vict == score_max){
			printf("%d * %s\n", nl, ptr->t->name);
			ptr = ptr->next;
		}
	}
}

void delete_all(){
	int key;
	link_game *ptr_g;
	link_team *ptr_t;

	for (key = 0; key < HT_SIZE; key++){
		ptr_g = head_game[key];
		while(ptr_g != NULL){
			free(ptr_g->g->name);
			free(ptr_g->g->team1);
			free(ptr_g->g->team2);
			free(ptr_g->g);
			ptr_g = ptr_g->next;
		}
		free(head_game[key]);
	}
	free(head_game);
	for (key = 0; key < HT_SIZE; key++){
		ptr_t = head_team[key];
		while(ptr_t != NULL){
			free(ptr_t->t->name);
			free(ptr_t->t);
			ptr_t = ptr_t->next;
		}
		free(head_team[key]);
	}
	free(head_team);
}

/************************************************************/
/*                                                          */
/*                        FUNCAO MAIN                       */
/*                                                          */
/************************************************************/

int main(){
	char input[MAX_IN];
	int nl = 1;

	Init_ht();

	
	while(1){
		/* Ciclo que aguarda o input do utilizador */
		fgets(input, MAX_IN, stdin);
		switch(input[0]){
			/* Comando switch que contem todas as opcoes possiveis de interacao do programa */

			case 'a':
				add_game(&input[2], nl);
				nl++;
				break;
				
			case 'l':
				list_games(nl);
				nl++;
				break;

			case 'p':
				find_game(&input[2], nl);
				nl++;
				break;

			case 'r':
				remove_game(&input[2], nl);
				nl++;
				break;

			case 's':
				change_score(&input[2], nl);
				nl++;
				break;

			case 'A':
				add_team(&input[2], nl);
				nl++;
				break;	

			case 'P':
				find_team(&input[2], nl);
				nl++;
				break;				

			case 'g':
				list_teams(nl);
				nl++;
				break;

			case 'x':
				delete_all();
				return 0;

			default:
				break;
		}		
	}
	return 0;												
}
