#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "games_struct.h"
#include "teams_struct.h"
#include "comands.h"

#define MAX_STR 1024  /* Tamanho maximo de cada string */

/* Inicializa a base de dados */
d_b* init_data_base(){
    d_b *data_base;
    data_base = can_fail_malloc(sizeof(d_b));
    data_base->game_list = init_game_list();
    data_base->hash_games = init_hash_games();
    data_base->teams_pile = NULL;
    data_base->hash_teams = init_hash_teams();
    data_base->NL = 0;
    return data_base;
}

/* Liberta memoria alocada para a base de dados */
void destroy_data(d_b *data_base){
    destroy_game_list(data_base->game_list);
    destroy_hash_game(data_base->hash_games);
    destroy_pile(data_base->teams_pile);
    destroy_hash_teams(data_base->hash_teams);
    free(data_base);
}

/* Adiciona um novo jogo a base de dados */
void add_new_game(d_b *data_base){
    game_node *game;
    t_node *first_team, *second_team;  /* Ponteiros que iram apontar para a primeira e segunda equipa */
    char name[MAX_STR], team1[MAX_STR], team2[MAX_STR];
    int first_score, second_score;
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", name, team1, team2, &first_score, &second_score);
    game = search_game(data_base->hash_games, name);
    if(!game){
        first_team = search_team(data_base->hash_teams, team1);
        second_team = search_team(data_base->hash_teams, team2);
        if(first_team && second_team){
            game = insert_game(data_base->game_list, name, first_team, second_team, first_score, second_score);
            insert_hash_game(data_base->hash_games, game);
        }
        else
            printf("%d Equipa inexistente.\n", data_base->NL);
    }
    else
        printf("%d Jogo existente.\n", data_base->NL);
}

/* Imprime todos os jogos pela ordem que foram introduzidos na base de dados */
void list_games(d_b *data_base){
    game_node *game = data_base->game_list->head;
    while(game){
        printf("%d %s %s %s %d %d\n", data_base->NL, game->game_name, game->team_one->team_name, game->team_two->team_name, game->score_one, game->score_two);
        game = game->next;
    }
}

/* Procura e printa o nome do jogo */
void search_name_game(d_b *data_base){
    game_node *game;
    char name[MAX_STR];
    scanf(" %[^:\n]", name);
    game = search_game(data_base->hash_games, name);
    if(game)
        printf("%d %s %s %s %d %d\n", data_base->NL, game->game_name, game->team_one->team_name, game->team_two->team_name, game->score_one, game->score_two);
    else
        printf("%d Jogo inexistente.\n", data_base->NL);
}

/* Remove um jogo da base de dados (tanto da hash table como da lista de jogos)*/
void remove_game(d_b *data_base){
    game_node *game;    /* Ponteiro que aponta para o nome da equipa */
    char name[MAX_STR];
    scanf(" %[^:\n]", name);
    game = search_game(data_base->hash_games, name);
    if(game){
        remove_win(game->team_one, game->team_two, game->score_one, game->score_two); 
        delete_game_hash(data_base->hash_games, data_base->game_list, name);
    }
    else
        printf("%d Jogo inexistente.\n", data_base->NL);
}

/* Muda o resultado de um jogo */
void score_change(d_b *data_base){
    game_node *game;	/* Ponteiro que aponta para o nome da equipa */
    char name[MAX_STR];
    int first_score, second_score;
    scanf(" %[^:\n]:%d:%d", name, &first_score, &second_score);
    game = search_game(data_base->hash_games, name);
    if(game){
    	remove_win(game->team_one, game->team_two, game->score_one, game->score_two);
        game->score_one = first_score;
        game->score_two = second_score;
        record_update(game->team_one, game->team_two, game->score_one, game->score_two);
    }
    else
        printf("%d Jogo inexistente.\n", data_base->NL);
}


/* Adiciona uma nova equipa a base de dados */
void add_new_team(d_b *data_base){
    char name[MAX_STR];
    t_node *team; /* Ponteiro que ira apontar para a equipa de input na hash_table */
    scanf(" %[^:\n]", name);
    team = search_team(data_base->hash_teams, name);
    if(!team){
        data_base->teams_pile = push_team(data_base->teams_pile, name);
        insert_hash_team(data_base->hash_teams, data_base->teams_pile);
    }
    else
        printf("%d Equipa existente.\n", data_base->NL);
}

/* Printa o nome da equipa e o seu numero de vitorias */
void search_name_team(d_b *data_base){
    t_node *team; /* Ponteiro para a equipa */
    char name[MAX_STR];
    scanf(" %[^:\n]", name);
    team = search_team(data_base->hash_teams, name);
    if(team)
        printf("%d %s %d\n", data_base->NL, name, team->wins);
    else
        printf("%d Equipa inexistente.\n", data_base->NL);
}

/* Printa as equipas com maior numero de vitorias por ordem alfabetica */
void best_teams(d_b *data_base){
    int max = 0, size = 0; /*max = maximo de vitorias, size = numero de equipas com o numero de vitorias igual a max*/
    t_node *new_pile = NULL, *head = data_base->teams_pile;
    while(head){ /* Determinar maximo */
        if(head->wins > max)
            max = head->wins;
        head = head->next;
    }
    head = data_base->teams_pile;
    while(head){ /* Construir pilha com as equipas com o mesmo numero de vitorias de max*/
        if(head->wins == max){
            new_pile = push_team(new_pile, head->team_name);
            size += 1;
        }
        head = head->next;
    }
    if(new_pile){
        new_pile = sort_teams_pile(new_pile, size);
        head = new_pile;
        printf("%d Melhores %d\n", data_base->NL, max);
        while(head){
            printf("%d * %s\n", data_base->NL, head->team_name);
            head = head->next;
        }
        destroy_pile(new_pile);
    }
}

/* Chama uma funcao segundo o comando de input */
void comand_list(char comand, d_b *data_base){
    data_base->NL += 1;
    switch(comand){
        case 'a': add_new_game(data_base); break;
        case 'l': list_games(data_base); break;
        case 'p': search_name_game(data_base); break;
        case 'r': remove_game(data_base); break;
        case 's': score_change(data_base); break;
        case 'A': add_new_team(data_base); break;
        case 'P': search_name_team(data_base); break;
        case 'g': best_teams(data_base); break;
    }
}