#ifndef PROJ2_H
#define PROJ2_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "linked_list.h"
#include "hash_table.h"
#include "qsort.h"

#define FALSE 0
#define TRUE 1
#define MAX_NAME_SIZE 1024
#define IBUFFER_SIZE 8192
#define UNINITIALIZED -1
#define UNUSED(var) (void)(var)

typedef struct team
{
    char *name;
    int games_won;
} team;

typedef struct game
{
    char *name,*team1,*team2;
    int score1,score2;

} game;

typedef struct list_hash_info
{
    hash_table *ht_teams,*ht_games;
    l_list *l_teams,*l_games;

}l_ht_info;

void free_team(void *ptr);
void free_game(void *ptr);
int commands_loop(l_ht_info *info);
int add_game_proc(char *io_buffer, l_ht_info *info, int cmd_ctr);
int add_team_proc(char *io_buffer, l_ht_info *info, int cmd_ctr);
int list_games_proc(l_ht_info *info, int cmd_ctr);
int search_game_proc(char *io_buffer, l_ht_info *info, int cmd_ctr);
int search_team_proc(char *io_buffer, l_ht_info *info, int cmd_ctr);
int delete_game_proc(char *io_buffer, l_ht_info *info, int cmd_ctr);
int change_game_score_proc(char *io_buffer, l_ht_info *info, int cmd_ctr);
int teams_most_wins_proc(l_ht_info *info, int cmd_ctr);
int search_game_by_name(char *name, l_ht_info *info,game **p_game);
int search_team_by_name(char *name, l_ht_info *info,team **p_team);
void add_game(l_ht_info *info,char *name,char *tm1, char *tm2,int score1, int score2);
void add_team(l_ht_info *info,char *name);
void swap_char(int idx_1, int idx_2, char **chr_arr, void *info_struct);
void cgsp_update_games_won(l_ht_info *info, game *p_game,int scr1,int scr2);
void dgp_update_games_won(l_ht_info *info, game *p_game);
void tmwp_sort_print(l_list* l_winners, int n_winners, int max_wins, int cmd_ctr);
#endif
