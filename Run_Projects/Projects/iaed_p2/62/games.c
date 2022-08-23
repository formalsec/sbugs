#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "teams.h"
#include "games.h"

/* Takes a game's information and returns a pointer to a GameNode object */
static GameLink game_create(char *game_name, char *team1, char *team2, int score1, int score2)
{
    GameLink game = (GameLink)malloc(sizeof(struct GameNode));

    /* Copies the game name and both team names */
    game->game_name = (char *)malloc((strlen(game_name) + 1) * sizeof(char));
    strcpy(game->game_name, game_name);

    game->team1 = (char *)malloc((strlen(team1) + 1) * sizeof(char));
    strcpy(game->team1, team1);

    game->team2 = (char *)malloc((strlen(team2) + 1) * sizeof(char));
    strcpy(game->team2, team2);

    /* Copies both teams scores */
    game->score1 = score1;
    game->score2 = score2;

    /* Initializes the node's previous and next pointers in the game hash table */
    game->ht_next = NULL;
    game->ht_previous = NULL;

    /* Initializes the pointers in the ordered table according to order of entry */
    game->table_previous = NULL;
    game->table_next = NULL;

    return game;
}

/* Takes in a hash table size and returns a game struct which 
contains a hash table size, a pointer to that hash table implemented using 
separate chaining with doubly linked lists, with its headers set as NULL,
a pointer to its companion team hash table and two pointers to a doubly
linked list, ordered by the order the games were inserted in the system, 
its head and its tail */
GameHT game_ht_init(TeamHT *team_ht, int size)
{
    GameHT game_ht;
    int i;

    game_ht.team_ht_ptr = team_ht;
    game_ht.size = size;
    game_ht.items_num = 0;
    game_ht.ht_header = (GameLink *)malloc(size * sizeof(GameLink));
    game_ht.table_head = NULL;
    game_ht.table_tail = NULL;

    for (i = 0; i < size; i++)
    {
        game_ht.ht_header[i] = NULL;
    }

    return game_ht;
}

/* Searches the hash table for a given game name. 
If found, returns the pointer to its node, else returns NULL */
GameLink game_ht_search(GameHT game_ht, char *game_name)
{
    GameLink g;
    int game_hash = name_hash(game_ht.size, game_name);

    for (g = game_ht.ht_header[game_hash]; g != NULL; g = g->ht_next)
    {
        if (!strcmp(g->game_name, game_name))
        {
            return g;
        }
    }
    return NULL;
}

/* Searches the hash table for a given game.
If the game isn't found, issues an error */
void game_ht_search_print(GameHT game_ht, char *game_name, unsigned long int NL)
{
    GameLink res = game_ht_search(game_ht, game_name);

    if (res == NULL)
    {
        printf("%ld Jogo inexistente.\n", NL);
        return;
    }

    else
    {
        printf("%ld %s %s %s %d %d\n", NL, res->game_name, res->team1,
               res->team2, res->score1, res->score2);
    }
}

/* Takes a game and returns the pointer to the 
team who won or NULL in case it's a draw */
static TeamLink game_winner(TeamHT team_ht, GameLink game)
{
    char *winner_name;

    if (game->score1 == game->score2)
    {
        return NULL;
    }
    else if (game->score1 > game->score2)
    {
        winner_name = game->team1;
    }
    else
    {
        winner_name = game->team2;
    }
    return team_ht_search(team_ht, winner_name);
}

/* Takes in a pointer to a team hash table and a new team and inserts 
that team into the table, updating the current number of items stored */
void game_ht_insert(GameHT *game_ht_ptr, char *game_name, char *team1, char *team2,
                    int score1, int score2, unsigned long int NL)
{
    /* If the game already exists, issues an error */
    if (game_ht_search(*game_ht_ptr, game_name) != NULL)
    {
        printf("%ld Jogo existente.\n", NL);
        return;
    }

    /* If either team isn't in the associated team_ht, issues an error */
    else if (team_ht_search(*game_ht_ptr->team_ht_ptr, team1) == NULL ||
             team_ht_search(*game_ht_ptr->team_ht_ptr, team2) == NULL)
    {
        printf("%ld Equipa inexistente.\n", NL);
        return;
    }

    else
    {
        GameLink game;
        int hash;
        TeamLink winner;

        game = game_create(game_name, team1, team2, score1, score2);

        hash = name_hash(game_ht_ptr->size, game_name);

        /**** Hash table part ****/
        /* Updates the hash table line corresponding to the game hash's header */
        game->ht_next = game_ht_ptr->ht_header[hash];

        /* If that line wasn't empty, update the current header */
        if (game->ht_next != NULL)
        {
            game->ht_next->ht_previous = game;
        }

        /* Make the new game the new header */
        game_ht_ptr->ht_header[hash] = game;

        /**** Ordered list part ****/

        /* If the table was previously empty, 
        set its head and tail as the new game */
        if (game_ht_ptr->table_head == NULL)
        {
            game_ht_ptr->table_head = game;
            game_ht_ptr->table_tail = game;
        }

        /* Set the game as its new tail */
        else
        {
            game_ht_ptr->table_tail->table_next = game;
            game->table_previous = game_ht_ptr->table_tail;
            game_ht_ptr->table_tail = game;
        }

        /* If either team won the game, updates the number of games that team 
        has won */
        winner = game_winner(*game_ht_ptr->team_ht_ptr, game);

        if (winner != NULL)
        {
            winner->games_won++;
        }

        /* Update the total number of games currently stored */
        game_ht_ptr->items_num++;
    }
}

/* Frees a game node */
void game_node_free(GameLink game)
{
    free(game->game_name);
    free(game->team1);
    free(game->team2);
    free(game);
}

/* Deletes a game from the game hash table, updating 
all variables that were affected by it */
void game_ht_delete(GameHT *game_ht_ptr, char *game_name, unsigned long int NL)
{
    GameLink game = game_ht_search(*game_ht_ptr, game_name);

    if (game == NULL)
    {
        printf("%ld Jogo inexistente.\n", NL);
        return;
    }

    else
    {
        /* Before we delete our game, we have to decrement our counters.
        We start by decrementing the ammount of games the winner team won,
        as long as the game wasn't a draw. */

        int hash = name_hash(game_ht_ptr->size, game_name);

        TeamLink winner = game_winner(*game_ht_ptr->team_ht_ptr, game);
        if (winner != NULL)
        {
            winner->games_won--;
        }

        /* After that, we decrement the ammount of games 
        currently in the hash table */
        game_ht_ptr->items_num--;

        /* Finally, we delete the node from the hash table
        and free the memory it once occupied */

        /**** Hash table part ****/

        /* If the game was a header, update the header */
        if (game_ht_ptr->ht_header[hash] == game)
        {
            game_ht_ptr->ht_header[hash] = game->ht_next;
        }

        /* As long as the nodes adjacent to the game we want to delete weren't 
        NULL, update their pointers */
        if (game->ht_previous != NULL)
        {
            game->ht_previous->ht_next = game->ht_next;
        }

        if (game->ht_next != NULL)
        {
            game->ht_next->ht_previous = game->ht_previous;
        }

        /**** Ordered list part ****/

        /* If game was the only element in the list, 
        set the head and tail as NULL */
        if (game_ht_ptr->table_head == game && game_ht_ptr->table_tail == game)
        {
            game_ht_ptr->table_head = NULL;
            game_ht_ptr->table_tail = NULL;
        }

        /* If it was only the head, update the next node and the table head */
        else if (game_ht_ptr->table_head == game)
        {
            game_ht_ptr->table_head = game->table_next;
            game->table_next->table_previous = NULL;
        }

        /* Same but for the tail */
        else if (game_ht_ptr->table_tail == game)
        {
            game_ht_ptr->table_tail = game->table_previous;
            game->table_previous->table_next = NULL;
        }

        /* Else, update both the adjacent nodes */
        else
        {
            game->table_previous->table_next = game->table_next;
            game->table_next->table_previous = game->table_previous;
        }

        game_node_free(game);
    }
}

/* Changes the score of a given game */
void game_ht_change_score(GameHT game_ht, char *game_name, int score1,
                          int score2, unsigned long int NL)
{
    GameLink game = game_ht_search(game_ht, game_name);

    /* If the game isn't present in the system, issue a warning */
    if (game == NULL)
    {
        printf("%ld Jogo inexistente.\n", NL);
        return;
    }

    else
    {
        /* Since the score will change, the winner might also change.
        Therefore, we save the current winner, change the score then 
        calculate the new winner */
        TeamLink winner_before, winner_after;

        /* Gets the winner before any changes to the scores */
        winner_before = game_winner(*(game_ht.team_ht_ptr), game);

        /* Updates the scores */
        game->score1 = score1;
        game->score2 = score2;

        /* Gets the new winner */
        winner_after = game_winner(*(game_ht.team_ht_ptr), game);

        /* If the winner is the same before and after 
        the changes, don't do anything */
        if (winner_before == winner_after)
        {
            return;
        }

        else
        {
            /* If the winner changed, the ht_previous winner either lost or tied. 
            Since they didn't win, we have to subtract the games they won */
            if (winner_before != NULL)
            {
                winner_before->games_won--;
            }

            /* If the winner wasn't NULL, then the other team won, in which
            case we need to add to the games they won */
            if (winner_after != NULL)
            {
                winner_after->games_won++;
            }
        }
    }
}

/* Prints all of the games, according to when they were first added 
to the system by going through each node in the ordered list */
void game_ht_print_order(GameHT game_ht, unsigned long int NL)
{
    GameLink t;

    /* If there are no teams, don't do anything */
    if (game_ht.items_num == 0)
    {
        return;
    }

    else
    {
        for (t = game_ht.table_head; t != NULL; t = t->table_next)
        {
            printf("%ld %s %s %s %d %d\n", NL, t->game_name, t->team1, t->team2, t->score1, t->score2);
        }
    }
}

/* Frees the memory used by the game hash table */
void game_ht_free(GameHT game_ht)
{
    int i;
    GameLink head, ht_next;

    for (i = 0; i < game_ht.size; i++)
    {
        head = game_ht.ht_header[i];
        while (head != NULL)
        {
            ht_next = head->ht_next;
            game_node_free(head);
            head = ht_next;
        }
    }
    free(game_ht.ht_header);
}