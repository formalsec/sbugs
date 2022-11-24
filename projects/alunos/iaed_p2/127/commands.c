#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "games.h"
#include "teams.h"
#include "commands.h"
#define MAX_STR_LEN 1024 /*strings maximum length*/

/*Command a name:team1:team2:score1:score2 - add new game to the system*/
link *command_a(link *game_list, link *game_tab,
               team **teams, long int *cont, long int *max_len){
    int score1, score2;
    /*new game link */
    link node;
    /*pointer to the new game*/
    game *new_game;
    link ptr_game;
    team *ptr_team1, *ptr_team2;
    char name[MAX_STR_LEN], team1[MAX_STR_LEN], team2[MAX_STR_LEN];

    (*cont)++;
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", name, team1, team2,
          &score1, &score2);
    ptr_game = search_g(name, game_tab, *max_len);
    ptr_team1 = search_t(team1, teams, *(max_len + 2));
    ptr_team2 = search_t(team2, teams, *(max_len + 2));

    if(ptr_game != NULL){
        printf("%ld Jogo existente.\n", *cont);
        return game_tab;
    }
    else if((ptr_team1 == NULL) || (ptr_team2 == NULL)){
        printf("%ld Equipa inexistente.\n", *cont);
        return game_tab;
    }
    else{

        if (score1 > score2){
            ptr_team1 -> nr_wins ++;
        }
        else if(score2 > score1){
            ptr_team2 -> nr_wins ++;
        }

        new_game = create_game(name, ptr_team1 -> name,
                             ptr_team2 -> name, score1, score2);
        node = push(game_list, new_game);
        return add_game_to_table(game_tab, node, max_len);
    }
}

/*Command A name - add new team to the system*/
team **command_A(team **teams, team **last_team,
                 long int *cont, long int *max_len){
    char name[MAX_STR_LEN];
    /*pointer to the new_team*/
    team *new_team;
    scanf(" %[^:\n]", name);
    (*cont)++;
    if (search_t(name, teams, *(max_len + 2)) == NULL){
        new_team = create_team(name);
        /*make the new team as the last team*/
        new_team -> next = *(last_team);
        *(last_team) = new_team;
        return add_team_to_table(teams, new_team, max_len);
    }
    else{
        printf("%ld Equipa existente.\n", *cont);
        return teams;
    }

}

/*Command l - list all games in the system by is insertion order*/
void command_l(link *game_list, long int *cont){
    link list;
    (*cont)++;
    for (list = *(game_list + 1); list != NULL; list = list -> prev){
        game *game = list -> game;
        printf("%ld %s %s %s %d %d\n",
               *cont,
               game -> name,
               game -> team1,
               game -> team2,
               game -> score_t1,
               game -> score_t2);
    }
}

/*Command p name - search for the game with the given name in the system*/
void command_p(link *game_tab, long int *cont, long int m){
    char name[MAX_STR_LEN];
    link game_node;
    game *game;
    (*cont)++;
    scanf(" %[^:\n]", name);
    game_node = search_g(name, game_tab, m);
    if(game_node == NULL)
        printf("%ld Jogo inexistente.\n", *cont);
    else{
        game = game_node -> game;
        printf("%ld %s %s %s %d %d\n",
               *cont,
               name,
               game -> team1,
               game -> team2,
               game -> score_t1,
               game -> score_t2);
    }
}

/*Command P name - search for a team in the system with the given name*/
void command_P(team **teams_tab, long int *cont, long int m){
    char name[MAX_STR_LEN];
    team *team;
    (*cont)++;
    scanf(" %[^:\n]", name);
    team = search_t(name, teams_tab, m);
    if (team == NULL)
        printf("%ld Equipa inexistente.\n", *cont);
    else
        printf("%ld %s %ld\n",
               *cont,
               name,
               team -> nr_wins);
}

/*Command s name:new_score1:new_score2 - change the score of the game
with the given name*/
void command_s(link *game_t, team **teams_t,
               long int *cont, long int *max_len){
    char name[MAX_STR_LEN];
    int sc1, sc2;
    link game_node;
    game *game;
    team *t1, *t2;

    (*cont)++;
    scanf(" %[^:\n]:%d:%d", name, &sc1, &sc2);
    game_node = search_g(name, game_t, *max_len);

    if(game_node == NULL)
        printf("%ld Jogo inexistente.\n", *cont);
    else{
        game = game_node -> game;
        t1 = search_t(game -> team1, teams_t, *(max_len + 2));
        t2 = search_t(game -> team2, teams_t, *(max_len + 2));

        /*change the number of wins of each team if needed*/
        if (sc1 > sc2){
            if (game -> score_t1 < game -> score_t2){
                t1 -> nr_wins ++;
                t2 -> nr_wins --;
            }
            else if (game -> score_t1 == game -> score_t2)
                t1 -> nr_wins ++;
        }
        else if (sc1 < sc2){
            if (game -> score_t1 > game -> score_t2){
                t1 -> nr_wins --;
                t2 -> nr_wins ++;
            }
            else if (game -> score_t1 == game -> score_t2)
                t2 -> nr_wins ++;
        }
        else{
            if(game -> score_t1 > game -> score_t2)
                t1 -> nr_wins --;
            else if(game -> score_t1 < game -> score_t2)
                t2 -> nr_wins --;

        }
        game -> score_t1 = sc1;
        game -> score_t2 = sc2;

    }
}

/*Function to delete the game in node_ptr from both game_list and game_tab*/
void delete_game(link *game_list, link *game_tab, team **teams_tab,
                 long int node_ptr, long int *max_len){
    link *game_ptr;
    game *game;
    team *ptr_team1, *ptr_team2;
    game_ptr = game_tab + node_ptr;
    game = (*game_ptr) -> game;

    if ((game -> score_t1) > (game -> score_t2)){
        ptr_team1 = search_t(game -> team1,
                             teams_tab, *(max_len + 2));
        ptr_team1 -> nr_wins --;
    }
    else if((game -> score_t1) < (game -> score_t2)){
        ptr_team2 = search_t(game -> team2,
                    teams_tab, *(max_len + 2));
        ptr_team2 -> nr_wins --;
    }

    delete_el(game_list, *game_ptr);
    *game_ptr = NULL;
    (*(max_len + 1))--;
    /*rearrange all elements after node_ptr in order of organization*/
    rearrange_tab_g(game_tab, node_ptr, max_len);
}

/*Command r name - delete the game with the given name from the system*/
void command_r(link *game_list, link *game_tab, team **teams_tab,
                long int *cont, long int *max_len){
    char name[MAX_STR_LEN];
    long int node_ptr;

    (*cont)++;
    scanf(" %[^:\n]", name);
    node_ptr = search_aux(name, game_tab, *max_len);
    if(node_ptr == -1)
        printf("%ld Jogo inexistente.\n", *cont);
    else{
        delete_game(game_list, game_tab, teams_tab, node_ptr, max_len);
    }

}

/*Function to compare two strings(used in qsort())*/
int comp_strings(const void *str1, const void *str2){
    const char **p_str1 = (const char **)str1,
    **p_str2 = (const char **)str2;

    return strcmp(*p_str1,*p_str2);
}

/*Function to print all elements of strs*/
void print_list(char **strs, long int len,
                long int nr_wins, long int cont){
    long int i;
    printf("%ld Melhores %ld\n", cont, nr_wins);
    for (i = 0; i < len; i++){
        printf("%ld * %s\n", cont, *(strs + i));
    }
}

/*Function that selects from the system all teams with the biggest
number of wins*/
long int winner_list(char **win_list, team *last_team,
                long int *max_wins){
    long int c = 0;
    team *t, *prev;
    prev = last_team;
    *(max_wins) = last_team -> nr_wins;
    for (t = last_team; t != NULL; t = t -> next){
        /*start a new list if the number of wins from t is bigger
        then the one from the last element in the new list*/
        if (t -> nr_wins > prev -> nr_wins){
            *(win_list) = t -> name;
            *(max_wins) = t -> nr_wins;
            prev = t;
            c = 1;
        }
        else if(t -> nr_wins == prev -> nr_wins){
            *(win_list + c) = t -> name;
            prev = t;
            c++;
        }
    }
    free(t);
    return c;
}

/*Command g - find the teams with the max number of wins and prints
them by lexicographic order*/
void command_g(team *last_team, long int *cont, long int *max_len){
    long int c, max_wins = 0;
    /*auxiliary table to contain the winner teams*/
    char **aux_tab = can_fail_malloc(sizeof(char*) * (*(max_len + 3)));
    (*cont)++;
    if (*(max_len + 3) != 0){
        c = winner_list(aux_tab, last_team, &max_wins);
        qsort(aux_tab, c, sizeof(char *), comp_strings);
        print_list(aux_tab, c, max_wins, *cont);
    }
    free(aux_tab);
}























