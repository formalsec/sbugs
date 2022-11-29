#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "commands.h"
#include "auxiliary.h"

/* A - Function that creates a new team and adds it to the system. */
void add_team(unsigned int NL, tlink** team_table)
{
    char name[STRMAX];

    scanf("%[^:\n]", name); getchar();

    if (!new_team(team_table, name))
        printf("%u Equipa existente.\n", NL);

}


/* a - Function that creates a new game and updates the game structures. */
void add_game(unsigned int NL, game** first_game, game** last_game, glink** game_table, tlink** team_table)
{
    char name[STRMAX], team1[STRMAX], team2[STRMAX];
    int score1, score2;

    scanf("%[^:\n]", name); getchar();
    scanf("%[^:\n]", team1); getchar();
    scanf("%[^:\n]", team2); getchar();
    scanf("%d", &score1); getchar();
    scanf("%d", &score2); getchar();

    if (game_table_search(game_table, name) != NULL)
    {
        printf("%u Jogo existente.\n", NL);
        return;
    }
    else if (team_table_search(team_table, team1) == NULL || team_table_search(team_table, team2) == NULL)
    {
        printf("%u Equipa inexistente.\n", NL);
        return;
    } 
    else
        new_game(game_table, team_table, first_game, last_game, name, team1, team2, score1, score2);
}


/* l - Function that lists all games by input order. */
void list_games(unsigned int NL, game** first_game)
{
    game *runthrough;

    for (runthrough = *first_game; runthrough != NULL; runthrough = runthrough->next)
        printf("%u %s %s %s %d %d\n", NL, runthrough->name, runthrough->team1, runthrough->team2, runthrough->score1, runthrough->score2);
        
}


/* P - Function that prints a team's name and the amount of games they won */
void search_team(unsigned int NL, tlink** team_table)
{
    char name[STRMAX];
    team *wanted;

    scanf("%[^:\n]", name); getchar();

    wanted = team_table_search(team_table, name);

    if (wanted == NULL)
        printf("%u Equipa inexistente.\n", NL);
    else
        printf("%u %s %d\n", NL, wanted->name, wanted->victories);
}


/* p - Function that prints a game's info when given it's name. */
void search_game(unsigned int NL, glink** game_table)
{
    char name[STRMAX];
    game *wanted;

    scanf("%[^:\n]", name); getchar();

    wanted = game_table_search(game_table, name);

    if (wanted == NULL)
        printf("%u Jogo inexistente.\n", NL);
    else
        printf("%u %s %s %s %d %d\n", NL, wanted->name, wanted->team1, wanted->team2,
        wanted->score1, wanted->score2);
}


/* r - Function that removes the game with the corresponding name from the system. */
void remove_game(unsigned int NL, game** first_game, game** last_game, glink** game_table, tlink** team_table)
{
    char name[STRMAX];

    scanf("%[^:\n]", name); getchar();

    if (game_table_search(game_table, name) == NULL)
        printf("%u Jogo inexistente.\n", NL);

    else
        delete_game(first_game, last_game, game_table, team_table, name);
}


/* s - Function that changes the scores of the game with the corresponding name. */
void change_score(unsigned int NL, glink** game_table, tlink** team_table)
{
    int new_tie = 0, old_tie = 0, new_scr1, new_scr2;
    char new_winner[STRMAX], old_winner[STRMAX];
    char name[STRMAX];
    game *match;

    scanf("%[^:\n]", name); getchar();
    scanf("%d", &new_scr1); getchar();
    scanf("%d", &new_scr2); getchar();

    match = game_table_search(game_table, name);

    if (match == NULL)
    {
        printf("%u Jogo inexistente.\n", NL);
        return;
    }
    
    if (new_scr1 > new_scr2)
        strcpy(new_winner, match->team1);
    else if (new_scr2 > new_scr1)
        strcpy(new_winner, match->team2);
    else
        new_tie = 1;
    

    if (match->score1 > match->score2)
        strcpy(old_winner, match->team1);
    else if (match->score2 > match->score1)
        strcpy(old_winner, match->team2);
    else
        old_tie = 1;


    match->score1 = new_scr1;
    match->score2 = new_scr2;

    if (old_tie && new_tie)
        return;

    else if (old_tie  && !new_tie)
        give_victory(team_table, new_winner);

    else if (!old_tie && new_tie)
        remove_victory(team_table, old_winner);

    else if (strcmp(new_winner, old_winner) == 0)
        return;

    else
    {
        remove_victory(team_table, old_winner);
        give_victory(team_table, new_winner);
    }
}


/* g - Prints out the teams that have won the most games by lexicographic order. */
void best_teams(unsigned int NL, tlink** team_table)
{
    int i, total = 1, most = -1;
    tlink *node;
    team *list = (team*) can_fail_malloc(total * sizeof(team));
    team *orig_list = list;
    
    for (i = 0; i < HASHSIZE; i++)
    {
        for (node = team_table[i]; node != NULL; node = node->next)
        {
            if (node->t->victories > most)
            {
                most = node->t->victories;
                free(list); total = 1; /* Reset */
                list = (team*) can_fail_malloc(total * sizeof(team));
                list[0] = *node->t;
            }
            else if (node->t->victories == most)
            {
                total++;
                list = (team*) can_fail_realloc(list, (total * sizeof(team)));
                list[total-1] = *node->t;
            }
        }
    }

    if (most == -1)
    {
        free(orig_list);
        return;
    }
    else
    {
        qsort(list, total, sizeof(team), compare_func);
        printf("%u Melhores %d\n", NL, most);

        for (i = 0; i < total; i++)
        {
            printf("%u * %s\n", NL, list[i].name);
        }

        free(list);
    }
}


/* Auxiliary - x - Free's all the structures that allocate memory in the heap in this project. */
void free_memory(glink** game_table, tlink** team_table, game** first_game, game** last_game)
{
    destroy_gtable(game_table);
    destroy_ttable(team_table);
    free(game_table);
    free(team_table);
    free(first_game);
    free(last_game);
}