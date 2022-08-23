#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trees.h"
#include "lists.h"
#include "teams.h"
#include "games.h"

void add_game(t_node *, t_node **, t_node **, list *, int );
void add_team(t_node **, t_node **, int);
void list_games(list *, int);
void search_game(t_node *, int);
void search_team(t_node *, int);
void search_print(t_node *, int, void (*print)(void*, int), int);
void remove_game(t_node **, t_node **, list **, int);
void change_score(t_node *, t_node **, int);
void print_winners(t_node *, int);
//char *strdup(char *);

/* Receives primary input and calls appropriate functions                     */
int main(){
    char cmd;
    int in_line = 1;
    t_node *t_teams_v, *t_teams_n, *t_games;
    list *l_games;

    t_teams_v = t_teams_n = t_games = NULL;
    l_games = list_init();
    
    do {
        cmd = getchar();

        switch (cmd){
            case 'a': add_game(t_teams_n, &t_teams_v, &t_games, l_games, in_line); break;
            case 'A': add_team(&t_teams_n, &t_teams_v, in_line); break;
            case 'l': list_games(l_games, in_line); break;     
            case 'p': search_game(t_games, in_line); break;
            case 'P': search_team(t_teams_n, in_line); break;
            case 'r': remove_game(&t_games, &t_teams_v, &l_games, in_line); break;
            case 's': change_score(t_games, &t_teams_v, in_line); break;
            case 'g': print_winners(t_teams_v, in_line); break;
        }
        in_line++;
    } while(cmd != 'x');

    destroy_tree(t_teams_v, del_team);
    free_tree(t_teams_n);
    free_tree(t_games);
    destroy_list(l_games, del_game);

    return 0;
}

/* Reads input and adds new game to respective structures, updating victories */
void add_game(t_node *t_teams_n, t_node **t_teams_v, t_node **t_games, list *l_games, int i_l){
    char g_name[MAX_GAME_NAME], t1_name[MAX_TEAM_NAME], t2_name[MAX_TEAM_NAME];
    short score1, score2;
    team *t1, *t2;
    lst_node *g_nd;
    game *new_g;

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%hd:%hd", g_name, t1_name, t2_name, &score1, &score2);
    getchar();

    if(tree_lookup(*t_games, cmp_game_str, g_name) != NULL){
        printf("%d Jogo existente.\n", i_l);
        return;
    }
    t1 = tree_lookup(t_teams_n, cmp_team_str, t1_name);
    t2 = tree_lookup(t_teams_n, cmp_team_str, t2_name);

    if(t1 == NULL || t2 == NULL){
        printf("%d Equipa inexistente.\n", i_l);
        return;
    }
    if(score1 > score2)
        *t_teams_v = change_victs(*t_teams_v, t1, 1);
    else if (score2 > score1)
        *t_teams_v = change_victs(*t_teams_v, t2, 1);

    new_g = malloc(sizeof(game));
    new_g->name = strdup(g_name);
    new_g->team1 = t1; new_g->team2 = t2;
    new_g->score1 = score1; new_g->score2 = score2;

    g_nd = list_append(l_games, new_g);
    *t_games = tree_insert(*t_games, cmp_game_nds, g_nd);
    return;
}

/* Reads input and adds new team to respective structures                     */
void add_team(t_node **t_teams_n, t_node **t_teams_v, int in_line){
    char t_name[MAX_TEAM_NAME];
    team *new_t;

    scanf(" %[^:\n]", t_name);
    getchar();
    if(tree_lookup(*t_teams_n, cmp_team_str, t_name) != NULL){
        printf("%d Equipa existente.\n", in_line);
        return;
    }

    new_t = malloc(sizeof(team));
    new_t->name = strdup(t_name);
    new_t->victs = 0;

    *t_teams_n = tree_insert(*t_teams_n, cmp_teams_nme, new_t);
    *t_teams_v = tree_insert(*t_teams_v, cmp_teams_vct, new_t);
    return;
}

/* Lists all games by insertion order                                         */
void list_games(list *lst, int in_line){
    lst_node *cursor = lst->head;
    getchar();

    while(cursor != NULL){
        print_game(cursor->value, in_line);
        cursor = cursor->next;
    }
    return;
}

/* Reads input and searches for that game in the games tree                   */
void search_game(t_node *t_games, int in_line){
    char g_name[MAX_GAME_NAME];
    lst_node *g_nd;

    scanf(" %[^:\n]", g_name);
    getchar();
    g_nd = tree_lookup(t_games, cmp_game_str, g_name);

    if(g_nd == NULL){
        printf("%d Jogo inexistente.\n", in_line);
        return;
    }
    print_game(g_nd->value, in_line);
    return;
}

/* Reads input and searches for that team in the teams tree                   */
void search_team(t_node *t_teams_n, int in_line){
    char t_name[MAX_TEAM_NAME];
    team *t;

    scanf(" %[^:\n]", t_name);
    getchar();
    t = tree_lookup(t_teams_n, cmp_team_str, t_name);

    if(t == NULL){
        printf("%d Equipa inexistente.\n", in_line);
        return;
    }
    print_team(t, in_line);
    return;
}

/* Reads input and removes game from respective structures, updating victories*/
void remove_game(t_node **t_games, t_node **t_teams_v, list **l, int in_line){
    char g_name[MAX_GAME_NAME];
    lst_node *g_nd;
    game *g;

    scanf(" %[^:\n]", g_name);
    getchar();
    g_nd = tree_lookup(*t_games, cmp_game_str, g_name);

    if(g_nd == NULL){
        printf("%d Jogo inexistente.\n", in_line);
        return;
    }
    g = g_nd->value;

    if (g->score1 > g->score2)
        *t_teams_v = change_victs(*t_teams_v, g->team1, -1);
    else if(g->score1 < g->score2)
        *t_teams_v = change_victs(*t_teams_v, g->team2, -1);

    *t_games = tree_remove(*t_games, cmp_game_nds, g_nd);
    del_game(g);
    *l = remove_node(*l, g_nd);
    
    return;
}

/* Reads input and changes game result from structures, updating victories    */
void change_score(t_node *t_games, t_node **t_teams_v, int in_line){
    char g_name[MAX_GAME_NAME];
    short n_scr1, n_scr2;
    lst_node *g_nd;
    game *g;

    scanf(" %[^:\n]:%hd:%hd", g_name, &n_scr1, &n_scr2);
    getchar();
    g_nd = tree_lookup(t_games, cmp_game_str, g_name);

    if (g_nd == NULL){
        printf("%d Jogo inexistente.\n", in_line);
        return;
    }
    g = g_nd->value;

    if (g->score1 > g->score2 && n_scr1 <= n_scr2)
        *t_teams_v = change_victs(*t_teams_v, g->team1, -1);
    else if (g->score1 <= g->score2 && n_scr1 > n_scr2)
        *t_teams_v = change_victs(*t_teams_v, g->team1, 1);

    if (g->score1 < g->score2 && n_scr1 >= n_scr2)
        *t_teams_v = change_victs(*t_teams_v, g->team2, -1);
    else if (g->score1 >= g->score2 && n_scr1 < n_scr2)
        *t_teams_v = change_victs(*t_teams_v, g->team2, 1);

    g->score1 = n_scr1;
    g->score2 = n_scr2;
    
    return;
}

/* Lists all teams with the most victories, alphabetically                    */
void print_winners(t_node *t_teams_v, int in_line){
    t_node *max;
    short max_victs;
    getchar();

    if (t_teams_v == NULL)
        return;

    max = max_node(t_teams_v);
    max_victs = ((team*)max->value)->victs;

    printf("%d Melhores %hd\n", in_line, max_victs);    
    print_targets(t_teams_v, max_victs, in_line);
    return;
}

/* Creates a duplicate of a given string and returns pointer to it            */
/*char *strdup(char *s){
    char *new_s;
    new_s = malloc(sizeof(char) * (strlen(s) + 1));
    strcpy(new_s, s);
    return new_s;
}*/
