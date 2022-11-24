#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "structures.h"
#include "auxiliary.h"

/* ----------------------------- Team Functions -------------------------------------- */

/* Function that adds a new team to the hashtable. Returns 1 if it succeeds (no team with the same name). */
int new_team(tlink** team_table, char* name)
{
    int key;
    tlink *aux;
    team *new_team = (team*) can_fail_malloc(sizeof(team));

    key = stringhash(name);
    aux = team_table[key];

    new_team->name = strdupl(name);
    new_team->victories = 0;

    if (team_table[key] == NULL) /* Case with no existing external chain */
    {
        team_table[key] = can_fail_malloc(sizeof(tlink));
        team_table[key]->next = NULL;
        team_table[key]->t = new_team;
        return 1;
    }

    else 
    {
        while (aux != NULL)
        {
            if (strcmp(aux->t->name, name) == 0)
            {
                free(new_team->name);
                free(new_team);
                return 0;
            }

            aux = aux->next;
        }
        /* New team will be the first element of the chain in this tab*/
        aux = can_fail_malloc(sizeof(tlink));
        aux->next = team_table[key];
        aux->t = new_team;
        team_table[key] = aux; 

        return 1;
    }
}


/* Function that searches the hashtable for a team given the name.
Returns a pointer to the team if it exists, NULL otherwise. */
team* team_table_search(tlink** team_table, char* name)
{
    team* result = NULL;
    tlink* runthrough;
    int key = stringhash(name);

    for (runthrough = team_table[key]; runthrough != NULL; runthrough = runthrough->next)
    {
        if (strcmp(runthrough->t->name, name) == 0)
        {
            result = runthrough->t;
            return result;
        }
    }
    return result;
}


/* Function that increments the given team's victories. */
void give_victory(tlink** team_table, char* name)
{
    team* winner;
    winner = team_table_search(team_table, name);
    winner->victories++;
}


/* Function that decrements the given team's victories. */
void remove_victory(tlink** team_table, char* name)
{
    team* loser;
    loser = team_table_search(team_table, name);
    loser->victories--;
}


/* Auxiliary compare function used in qsort */
int compare_func(const void *t1, const void *t2)
{
    team *team1 = (team*) t1;
    team *team2 = (team*) t2;
    return strcmp(team1->name,team2->name);
}


/* Frees all the memory used in the team hashtable (both teams and nodes) */
void destroy_ttable(tlink** team_table)
{
    tlink *aux, *next;
    int i;

    for (i = 0; i < HASHSIZE; i++)
    {
        for (aux = team_table[i]; aux != NULL; aux = next)
        {
            next = aux->next;
            free(aux->t->name);
            free(aux->t);
            free(aux);
        }
    }
}



/* ----------------------------- Game Functions -------------------------------------- */

/* Function that adds a new game to the hashtable. Updates the pointers to the edge of the linked chain,
and increment's the winner's victories. */
void new_game(glink** game_table, tlink** team_table, game** first_game, game** last_game, char* name, char* t1, char* t2, int scr1, int scr2)
{
    int key;
    glink *aux;
    game *new_game = (game*) can_fail_malloc(sizeof(game));

    key = stringhash(name);
    aux = game_table[key];

    new_game->name = strdupl(name);
    new_game->team1 = strdupl(t1);
    new_game->team2 = strdupl(t2);
    new_game->score1 = scr1;
    new_game->score2 = scr2;

    if (scr1 > scr2)
        give_victory(team_table, t1);
    else if (scr2 > scr1)
        give_victory(team_table, t2);

    /* Input order is perserved */
    if (*first_game == NULL)
    {
        new_game->previous = NULL;
        new_game->next = NULL;
        *last_game = *first_game = new_game;
    } 
    else if (first_game[0]->next == NULL) /* first_game->next needs an update */
    {
        new_game->previous = *last_game;
        new_game->next = NULL;
        last_game[0]->next = new_game;
        first_game[0]->next = new_game;
        *last_game = new_game;
    }
    else
    {
        new_game->previous = *last_game;
        new_game->next = NULL;
        last_game[0]->next = new_game;
        *last_game = new_game;
    }

    if (game_table[key] == NULL) /* Case with no existing external chain */
    {
        game_table[key] = can_fail_malloc(sizeof(glink));
        game_table[key]->next = NULL;
        game_table[key]->g = new_game;
    }

    else 
    {
        while (aux != NULL)
            aux = aux->next;

        /* New game will be the first element of the chain in this tab */
        aux = can_fail_malloc(sizeof(glink));
        aux->next = game_table[key];
        aux->g = new_game;
        game_table[key] = aux; 
    }
}


/* Function that searches the hashtable for a game given the name.
Returns a pointer to the game if it exists, NULL otherwise. */
game* game_table_search(glink** game_table, char* name)
{
    game* result = NULL;
    glink* runthrough;
    int key = stringhash(name);

    for (runthrough = game_table[key]; runthrough != NULL; runthrough = runthrough->next)
    {
        if (strcmp(runthrough->g->name, name) == 0)
        {
            result = runthrough->g;
            return result;
        }
    }
    return result;
}

/* Function that removes a game from both the corresponding hashtable and the linked chain.
Also updates team victories. */
void delete_game(game** first_game, game** last_game, glink** game_table, tlink** team_table, char* name)
{
    glink *table_aux;
    game *runthrough, *game_aux;
    int key;

    key = stringhash(name);

    table_aux = game_table[key];

    /* Hashtable removal only frees the node, game is removed in the ordered chain segment */

    if (strcmp(table_aux->g->name,name) == 0)
    {
        if (table_aux->g->score1 < table_aux->g->score2)
            remove_victory(team_table, table_aux->g->team2);
        
        else if (table_aux->g->score2 < table_aux->g->score1)
            remove_victory(team_table, table_aux->g->team1); 
                
        game_table[key] = game_table[key]->next;
        free(table_aux);
    }
    else
    {
        glink *table_prev = NULL;
        while (table_aux != NULL)
        {
            if (strcmp(table_aux->g->name, name) == 0)
            {
                table_prev->next = table_aux->next;

                if (table_aux->g->score1 < table_aux->g->score2)
                    remove_victory(team_table, table_aux->g->team2);
                
                else if (table_aux->g->score2 < table_aux->g->score1)
                    remove_victory(team_table, table_aux->g->team1); 
                
                table_prev->next = table_aux->next;
                free(table_aux);
                break;
            }
            table_prev = table_aux;
            table_aux = table_aux->next;

        }
    }

    runthrough = *first_game;

    /* Input order needs to be perserved */
    if (strcmp(first_game[0]->name, name) == 0)
    {
        if (first_game == last_game)
        {
            *first_game = *last_game = NULL;
            destroy_game(runthrough);
        }
        else
        {
            *first_game = first_game[0]->next;
            destroy_game(runthrough);
        }
    }
    else
    {
        while (runthrough != NULL)
        {
            if (strcmp(runthrough->name, name) == 0)
            {
                if (runthrough == *last_game)
                {
                    *last_game = runthrough->previous;
                    last_game[0]->next = NULL;
                    
                    destroy_game(runthrough);
                    break;
                }
                else
                {
                    game_aux = runthrough->previous;
                    game_aux->next = runthrough->next;
                    runthrough->next->previous = game_aux;

                    destroy_game(runthrough);
                    break;   
                }
            }
            runthrough = runthrough->next;
        }
    }
}


/* Frees the memory occupied by a game and it's elements */
void destroy_game(game* match)
{
    free(match->name);
    free(match->team1);
    free(match->team2);
    free(match);
}


/* Frees all the memory used in the game hashtable (both games and nodes) */
void destroy_gtable(glink** game_table)
{
    glink *aux, *next;
    int i;

    for (i = 0; i < HASHSIZE; i++)
    {
        for (aux = game_table[i]; aux != NULL; aux = next)
        {
            next = aux->next;
            destroy_game(aux->g);
            free(aux);
        }
    }
}
