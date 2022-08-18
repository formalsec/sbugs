#include <stdlib.h>
#include <stdio.h>
#include "hashtables.h"
#include "linked_lists.h"

/*--------funcao de hash para ambas as tables---------*/

/* Retorna uma hash de modulo M para uma string */
int hash(char * head, int M){

    unsigned int h = 0, a = 5839, b = 7883;

    while(*head != '\0'){

        a = a*b % (M-1);
        h = (a*h + *head) % M;
        head++;

    }

    return h;
}





/*-------------funcoes para hashtable de jogos-------------*/
/* Procura um jogo na hashtable respetiva, na posicao dada pela hash */
nodeGame * search_game_ht(nodeGame * array_games[], char * game_name, int M){
    
    int index = hash(game_name, M);
    return _is_game_(array_games[index], game_name);

}

/* Adiciona um jogo a hashtable e armazena a respetiva posicao em index_games */
void add_game_ht(nodeGame * array_games[], indexNode ** index_games, char * game_name, int id, 
                int score1, int score2, char * team1, char * team2, int M){

    int index = hash(game_name, M);
    array_games[index] = _push_game_(array_games[index], game_name, id, 
                                        score1, score2, team1, team2);
    *index_games = _add_index_(*index_games, index);

}

/* Elimina um jogo da hasthtable e guarda a nova head do respetivo encadeamento */
void del_game_ht(nodeGame * array_games[], char * name, int M){

    int index = hash(name, M);
    array_games[index] = _del_game_(array_games[index], name);

}

/* Imprime no ecra a informacao de um jogo */
void print_game(int NL, Game * game_played){

    if(game_played == NULL) return;

    printf("%d %s %s %s %d %d\n", NL, game_played->name, game_played->team1, 
                    game_played->team2, game_played->score1, game_played->score2);

}

/* Destroi e da free de toda a hashtable de jogos */
void destroy_games_ht(nodeGame * games_ht[], indexNode * index_games){

    int i;

    while(index_games != NULL){
        /*posicao da hashtable ocupada*/
        i = index_games->s;

        /*destroi o encadeamento nessa posicao da ht*/
        games_ht[i] = _destroy_game_(games_ht[i]);

        index_games = index_games->next;
    }

}





/*-------------funcoes para hashtable de equipas--------------*/
/* Procura um jogo na hashtable respetiva, na posicao dada pela hash */
nodeTeam * search_team_ht(nodeTeam * array_teams[], char * team_name, int M){
    
    int index = hash(team_name, M);
    return _is_team_(array_teams[index], team_name);
}

/* Adiciona uma nova equipa a respetiva ht, na posicao dada pela hash */
void add_team_ht(nodeTeam * array_teams[], indexNode ** index_teams, char * team_name, int M){

    int index = hash(team_name, M);
    array_teams[index] = _push_team_(array_teams[index], team_name);
    *index_teams = _add_index_(*index_teams, index);

}

/* Dado o endereco de um no de equipa, altera o numero de vitorias dessa */
void change_wins_directly(nodeTeam * address, int change){
    address->team->wins += change;
}

/* Imprime no ecra a informacao de uma equipa */
void print_team(int NL, Team * team_addr){

    printf("%d %s %d\n", NL, team_addr->name, team_addr->wins);
    
}

/* Destroi e free de toda a hashtable de equipas */
void destroy_teams_ht(nodeTeam * teams_ht[], indexNode * index_teams){

    int i;
    while(index_teams != NULL){
        /*posicao da ht ocupada*/
        i = index_teams->s;

        /*destroi o encadeamento nessa posicao da ht*/
        teams_ht[i] = _destroy_team_(teams_ht[i]);

        index_teams = index_teams->next;
    }

}