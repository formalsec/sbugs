#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "hashtable.h"

#define MAX_STR 1024    /* max size of the buffer */


/* Function prototypes */
void add_team(tnode **teams_tab, unsigned int line);
void search_team(tnode **teams_tab, unsigned int line);
void top_teams(tnode **teams_tab, unsigned int line);

/* command functions */
void add_game(tnode **teams_tab, gnode **games_tab, gnode **games_list, unsigned int line);
void remove_game(tnode **teams_tab, gnode **games_tab, gnode **games_list, unsigned int line);
void search_game(gnode **games_tab, unsigned int line);
void change_score(tnode **teams_tab, gnode **games_tab, unsigned int line);
void list_games(gnode *games_list, unsigned int line);

/* auxiliary functions */
void decide_winner(tnode **teams_tab, game *g);
void remove_win(tnode **teams_tab, game *g);
void list_top_teams(tnode *teams_list, unsigned int line);



/* =============================================================== */
/* ***************************** MAIN **************************** */
/* =============================================================== */

int main()
{
    int cmd;
    unsigned int line = 1;

    tnode **teams_tab = NULL;
    gnode **games_tab = NULL;
    gnode *games_list = NULL;
    
    /* initialize hashtables */
    teams_tab = init_teams(teams_tab);
    games_tab = init_games(games_tab);

    /* ask for command */
    while ((cmd = getchar()) != EOF && cmd != 'x') {

        getchar();  /* ignore blank space */

        switch(cmd) {
            case 'a':
                add_game(teams_tab, games_tab, &games_list, line);
                break;
            case 'l':
                list_games(games_list, line);
                break;
            case 'p':
                search_game(games_tab, line);
                break;
            case 'r':
                remove_game(teams_tab, games_tab, &games_list, line);
                break;
            case 's':
                change_score(teams_tab, games_tab, line);
                break;
            case 'A':
                add_team(teams_tab, line);
                break;
            case 'P':
                search_team(teams_tab, line);
                break;
            case 'g':
                top_teams(teams_tab, line);
                break;
        }

        line++;   /* increment number of the input line */
    }

    /* free all team related allocations on the hashtable */
    destroy_teams(teams_tab);

    /* free all game related allocations on the hashtable */
    destroy_games(games_tab);

    /* free list of games */
    destroy_games_list(games_list);

    return 0;
}


/* =============================================================== */
/* ********************** Command functions ********************** */
/* =============================================================== */

/* add_team: add a team to the system */
/* INPUT FORMAT: A name */
void add_team(tnode **teams_tab, unsigned int line)
{
    char name[MAX_STR];         /* buffer for the name of the game */
    team *t;

    scanf("%1023[^:\n]\n", name);

    /* team won't be added if it already exists one with the same name */
    if (table_search_team(teams_tab, name) != NULL) {
        printf("%u Equipa existente.\n", line);
        return;
    }

    t = new_team(name);                 /* create new team */

    table_insert_team(teams_tab, t);    /* insert team into the hashtable */
}


/* search_team: search for a team in the system */
/* INPUT FORMAT: P name */
void search_team(tnode **teams_tab, unsigned int line)
{
    char name[MAX_STR];
    team *t;
    
    scanf("%1023[^:\n]\n", name);

    /* search for the team in the hashtable */
    if ((t = table_search_team(teams_tab, name)) == NULL) {
        printf("%u Equipa inexistente.\n", line);
        return;
    }
    
    printf("%u %s %d\n", line, t->name, t->wins);
}


/* add_game: add a game to the system */
/* INPUT FORMAT: a name:team1:team2:score1:score2 */
void add_game(tnode **teams_tab, gnode **games_tab, gnode **games_list, unsigned int line)
{
    char name[MAX_STR];
    char team1[MAX_STR], team2[MAX_STR];
    int score1, score2;
    game *g;

    scanf("%1023[^:\n]:%1023[^:\n]:%1023[^:\n]:%d:%d\n", 
            name, 
            team1, 
            team2, 
            &score1, 
            &score2);

    /* game won't be added if it already exists one with the same name */
    if (table_search_game(games_tab, name) != NULL) {
        printf("%u Jogo existente.\n", line);
        return;
    }

    /* game won't be added if a one of the provided teams doesn't exist */
    if (table_search_team(teams_tab, team1) == NULL || 
            table_search_team(teams_tab, team2) == NULL) {
        printf("%u Equipa inexistente.\n", line);
        return;
    }

    /* create new game */
    g = new_game(name, team1, team2, score1, score2);
    
    /* insert new game into the hashtable */
    table_insert_game(games_tab, g);

    /* increment the number of wins of the winner team */
    decide_winner(teams_tab, g);
    
    /* update list of games */
    *games_list = insert_game_begin(*games_list, g);
}


/* remove_game: remove a games from the system */
/* INPUT FORMAT: r name */
void remove_game(tnode **teams_tab, gnode **games_tab, gnode **games_list, unsigned int line)
{
    game *g;
    char name[MAX_STR];

    scanf("%1023[^:\n]\n", name);

    if ((g = table_search_game(games_tab, name)) == NULL) {
        printf("%u Jogo inexistente.\n", line);
        return;
    }


    /* decrement the number of wins of the winner team*/
    remove_win(teams_tab, g);
    
    /* delete the game from the hashtable */
    table_delete_game(games_tab, name);

    /* update the list of games */
    *games_list = del_from_glist(*games_list, name);
}


/* search_game: search for a game in the system */
/* INPUT FORMAT: p name */
void search_game(gnode **games_tab, unsigned int line)
{
    char name[MAX_STR];
    game *g;

    scanf("%1023[^:\n]\n", name);

    /* search for game in the hashtable */
    if ((g = table_search_game(games_tab, name)) == NULL) {
        printf("%u Jogo inexistente.\n", line);
        return;
    }
   
    printf("%u %s %s %s %u %u\n", line, 
                                    g->name, 
                                    g->t1,
                                    g->t2,
                                    g->score1,
                                    g->score2);
}


/* change_score: change the score of game in the system */
/* INPUT FORMAT: s name:score1:score2 */
void change_score(tnode **teams_tab, gnode **games_tab, unsigned int line)
{
    game *g;
    char name[MAX_STR];
    int score1, score2;

    scanf("%1023[^:\n]:%d:%d\n", name, &score1, &score2);

    /* searches for the game in the hashtable */
    if ((g = table_search_game(games_tab, name)) == NULL) {
        printf("%u Jogo inexistente.\n", line);
        return;
    }

    /* decrements the number of wins of the winner team */
    remove_win(teams_tab, g);

    /* set new scores */
    g->score1 = score1;
    g->score2 = score2;

    /* decide new winner */
    decide_winner(teams_tab, g);
}


/* list_games: list all the games in the system by insertion order */
/* INPUT FORMAT: l */
void list_games(gnode *games_list, unsigned int line)
{
    if (games_list == NULL)
        return;

    /* recursive call to list_games */
    list_games(games_list->next, line);
    printf("%u %s %s %s %u %u\n", line, 
                                    games_list->g->name, 
                                    games_list->g->t1, 
                                    games_list->g->t2, 
                                    games_list->g->score1, 
                                    games_list->g->score2);
}


/* top_teams: search for the top teams in the system and list them */
/* INPUT FORMAT: g */
void top_teams(tnode **teams_tab, unsigned int line)
{
    int higher;
    tnode *top_teams = NULL;    /* temporary list of teams to store pointers to teams */
    
    /* search for the higher score */
    higher = table_search_higher(teams_tab);

    /* search for teams with the higher score */
    top_teams = table_search_top_teams(teams_tab, top_teams, higher);

    /* if at least a team was found */
    if (top_teams != NULL) {
        printf("%u Melhores %d\n", line, higher);
        /* list top teams */
        list_top_teams(top_teams, line);
    }

    /* free all nodes of the list created for top_teams */
    destroy_teams_list(top_teams);
}



/* =============================================================== */
/* ********************* AUXILIARY FUNCTIONS ********************* */
/* =============================================================== */

/* decide_winner: increment the number of wins of the winner team */
void decide_winner(tnode **teams_tab, game *g)
{
    team *t;

    if (g->score1 > g->score2) {            /* team1 wins */
            t = table_search_team(teams_tab, g->t1);
        t->wins++;
    
    } else if (g->score1 < g->score2) {     /* team2 wins */
        t = table_search_team(teams_tab, g->t2);
        t->wins++;
    }
    /* tie do nothing */
}


/* remove_win: decrement the number of wins of the winner team */
void remove_win(tnode **teams_tab, game *g)
{
    team *t;

    if (g->score1 > g->score2) {            /* team1 won */
        t = table_search_team(teams_tab, g->t1);
        t->wins--;
    
    } else if (g->score1 < g->score2) {     /* team2 won */
        t = table_search_team(teams_tab, g->t2);
        t->wins--;
    }
    /* tie do nothing */
}


/* list_top_teams: list teams in top teams' format */
void list_top_teams(tnode *head, unsigned int line)
{
    if (head == NULL)
        return;

    /* recursive call to list_top_teams */
    list_top_teams(head->next, line);
    printf("%u * %s\n", line, head->t->name);
}
