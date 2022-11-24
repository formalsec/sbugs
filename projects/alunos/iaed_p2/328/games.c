#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "games.h"

/******************************************************
*------------------AUXILIAR FUNCTIONS-----------------*
******************************************************/

/*Initializes the list that saves the games by order of input*/
h_t_ordered_list *init_list(){

    h_t_ordered_list *lst = can_fail_malloc(sizeof(h_t_ordered_list));

    lst->head = NULL;
    lst->tail = NULL;

    return lst;
}

/*Initializes the games hash table*/
hash_table_games *create_ht_game(int size){
	
	int i;
	hash_table_games *new;
	
	if(size < 1)
		return NULL;

	if((new = can_fail_malloc(sizeof(hash_table_games))) == NULL)
		return NULL;

	if((new->table = can_fail_malloc(sizeof(list_games*)*size)) == NULL)
		return NULL;

	for(i = 0; i < size; i++)
		new->table[i] = NULL;

	new->size = size;
	
	return new;
}

int hash_games(hash_table_games *game_ht, char *v) {

    int h, a = 31415, b = 27183;

    /* iterates through the letters of the name and uses 
    a hashing algorithm to find a position for game */
    for (h = 0; *v != '\0'; v++, a = a*b % (game_ht->size - 1)){
        h = (a*h + *v) % game_ht->size;
	}
	
    return h;
}

/*Insert a game at the end of the list, this way, that same list is
ordered by the order of input*/
void insertEnd_list(h_t_ordered_list *lst, list_games *g){

    ordered_list_g y, z;

    /*If the list is empty, the head and the tail of the list is the 
    game that is being inserted*/
    if(lst->head == NULL){

        y = can_fail_malloc(sizeof(struct OL_G));

        y->game = g;
        y->next = NULL;
        y ->prev = NULL;
        lst->head = y;
        lst->tail = y;

        return;
    }

    z = can_fail_malloc(sizeof(struct OL_G));

    z->game = g;
    z->next = NULL;
    z->prev = lst->tail;
    lst->tail->next = z;
    lst->tail = z;
}

/*Removes the game with a certain name from the list*/
void remove_list(h_t_ordered_list *lst, char *token){

    ordered_list_g head_aux = lst->head;

    while(head_aux != NULL){
        
		if(strcmp(head_aux->game->name, token) == 0){

            if((head_aux == lst->head) && (head_aux == lst->tail)){

                free(head_aux);
                lst->head = NULL;
                lst->tail = NULL;
                return;
            }

            if(head_aux == lst->head){

                lst->head->next->prev = NULL;
                lst->head = head_aux->next;
                free(head_aux);
                return;
            }

            if(head_aux == lst->tail){

                lst->tail->prev->next = NULL;
                lst->tail = head_aux->prev;
                free(head_aux);
                return;
            }

            head_aux->prev->next = head_aux->next;
            head_aux->next->prev = head_aux->prev;
            free(head_aux);
            return;
        }

        head_aux = head_aux->next;
	}
}

/*Prints all the games (characteristics) of the list*/
void print_list(h_t_ordered_list *lst, int NL){

    ordered_list_g t;

    for(t = lst->head; t != NULL; t = t->next)
        printf("%d %s %s %s %d %d\n",NL, t->game->name, t->game->team1, t->game->team2, t->game->score1, t->game->score2);
}

/*Inserts a game in the hash table*/
list_games *insertBegin_games(hash_table_games *game_ht, char *name, char *team1, char *team2, int score1, int score2){
    
    list_games *new;
    int i = hash_games(game_ht, name);

    new = can_fail_malloc(sizeof(list_games));
    new->name = can_fail_malloc(sizeof(char)*(strlen(name)+1));
    new->team1 = can_fail_malloc(sizeof(char)*(strlen(team1)+1));
    new->team2 = can_fail_malloc(sizeof(char)*(strlen(team2)+1));

    strcpy(new->name, name);
    strcpy(new->team1, team1);
    strcpy(new->team2, team2);
    new->score1 = score1;
    new->score2 = score2;

    new->next = game_ht->table[i];
    game_ht->table[i] = new;

    return new;
}

/*Searches for a game in the hash table, if it finds it returns the game, if not returns NULL*/
list_games *search_game_aux(hash_table_games *game_ht, char *v){

    list_games *g;
    int i = hash_games(game_ht, v);

    for(g = game_ht->table[i]; g != NULL; g = g->next){
        if(strcmp(v, g->name) == 0)
            return g;
    }

    return NULL;
}

/*Deletes the game from the hash table*/
void delete_game_aux(hash_table_games *game_ht, char *token){

    int h = hash_games(game_ht, token);
    int i = 0;
    list_games *temp = game_ht->table[h];
    list_games *aux;

    while(temp != NULL){

        if(strcmp(temp->name, token) == 0){

            if((i == 0) && (temp->next == NULL))
                game_ht->table[h] = NULL;

            if((i == 0) && (temp->next != NULL))
                game_ht->table[h] = temp->next;

            if((i != 0) && (temp->next == NULL))
                aux->next = NULL;

            if((i != 0) && (temp->next != NULL))
                aux->next = temp->next;

            free(temp->name);
            free(temp->team1);
            free(temp->team2);
            free(temp);
            return;
        }

        i++;
        aux = temp;
        temp = aux->next;
    }
}

/*Changes the score of a certain game*/
void change_score_aux(list_games *g, hash_table_teams *team_ht, int score1, int score2){
    
    int old_score1, old_score2;
    list_teams *t1, *t2;

	old_score1 = g->score1;
	old_score2 = g->score2;
	
	g->score1 = score1;
	g->score2 = score2;

	t1 = search_team_aux(team_ht, g->team1);
	t2 = search_team_aux(team_ht, g->team2);

	if((score1 > score2) && (old_score1 < old_score2)){
		t1->victories++;
		t2->victories--;
		return;
	}

	if((score1 < score2) && (old_score1 > old_score2)){
		t1->victories--;
		t2->victories++;
		return;
	}

	if((score1 == score2) && (old_score1 > old_score2)){
		t1->victories--;
		return;
	}

	if((score1 == score2) && (old_score1 < old_score2)){
		t2->victories--;
		return;
	}

    if((score1 > score2) && (old_score1 == old_score2)){
        t1->victories++;
        return;
    }

    if((score1 < score2) && (old_score1 == old_score2)){
        t2->victories++;
    }
}