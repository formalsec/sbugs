#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "teams.h"

/* Takes in a hash table size and returns a team hash table struct 
which contains its size, the number of teams the system currently 
hold and a pointer to a linked list implemented using separate 
chaining with linked lists, with their headers initialized as NULL */
TeamHT team_ht_init(int size)
{
    TeamHT team_ht;
    int i;

    team_ht.size = size;
    team_ht.teams_num = 0;
    team_ht.header = (TeamLink *)can_fail_malloc(size * sizeof(TeamLink));

    for (i = 0; i < size; i++)
    {
        team_ht.header[i] = NULL;
    }

    return team_ht;
}

/* Takes in a hash table size and  a team name and returns its hash.
Based upon Strings 2.0 dispersion method shown in class. */
int name_hash(int size, char *c)
{
    int h, a = 31415, b = 27183;
    for (h = 0; *c != '\0'; c++, a = a * b % (size - 1))
    {
        h = (a * h + *c) % size;
    }
    return h;
}

/* Searches the hash table for a given team. 
If found, returns its pointer, else returns NULL */
TeamLink team_ht_search(TeamHT team_ht, char *team)
{
    TeamLink t;
    int team_hash = name_hash(team_ht.size, team);

    for (t = team_ht.header[team_hash]; t != NULL; t = t->next)
    {
        if (!strcmp(t->team, team))
        {
            return t;
        }
    }
    return NULL;
}

/* Searches the hash table for a given team.
If the team isn't found, issues an error */
void team_ht_search_print(TeamHT team_ht, char *team, unsigned long int NL)
{
    TeamLink res = team_ht_search(team_ht, team);

    if (res == NULL)
    {
        printf("%ld Equipa inexistente.\n", NL);
        return;
    }

    else
    {
        printf("%ld %s %d\n", NL, res->team, res->games_won);
    }
}

/* Takes in a team hash table and a new team and inserts that team into 
the table, updating the current number of teams stored */
void team_ht_insert(TeamHT *team_ht_ptr, char *team, unsigned long int NL)
{
    /* If the team already exists, issues an error */
    if (team_ht_search(*team_ht_ptr, team) != NULL)
    {
        printf("%ld Equipa existente.\n", NL);
        return;
    }

    else
    {
        int team_hash = name_hash(team_ht_ptr->size, team);
        /* Creates a new TeamNode */
        TeamLink t = (TeamLink)can_fail_malloc(sizeof(struct TeamNode));

        t->team = (char *)can_fail_malloc((strlen(team) + 1) * sizeof(char));
        strcpy(t->team, team);
        t->games_won = 0;

        /* Updates the header in the hash table line correspondent to
        hashing the team name to the new GameNode */
        t->next = team_ht_ptr->header[team_hash];
        team_ht_ptr->header[team_hash] = t;

        /* Updates the number of teams currently stored */
        team_ht_ptr->teams_num++;
    }
}

/* Function we use to compare two teams alphabetically, used in qsort */
static int team_comp_name(const void *team1, const void *team2)
{
    char *name1, *name2;

    name1 = (*(TeamLink *)team1)->team;
    name2 = (*(TeamLink *)team2)->team;

    return strcmp(name1, name2);
}

/* Copies all items present in the hash table to an array, sorts the
array based on the ammount of games each team has won and prints all the teams
that share the highest score, in alphabetical order */
void team_ht_print_best(TeamHT team_ht, unsigned long int NL)
{
    int i, j = 0;
    TeamLink t;

    /* The biggest number of games won by a single team */
    int best_score = 0;

    /* Number of teams tied at first place */
    int best_teams_num = 0;

    /* Array that will hold the games tied at first place */
    TeamLink *best_teams;

    /* If there are no teams, don't do anything */
    if (team_ht.teams_num == 0)
    {
        return;
    }

    else
    {
        /* Runs through the hash table and finds the best score 
        (biggest number of games won by a single team) and the 
        number of teams that have won that many games */
        for (i = 0; i < team_ht.size; i++)
        {
            for (t = team_ht.header[i]; t != NULL; t = t->next)
            {
                if (t->games_won == best_score)
                {
                    best_teams_num++;
                }
                else if (t->games_won > best_score)
                {
                    best_score = t->games_won;
                    best_teams_num = 1;
                }
            }
        }

        /* Creates a new array and copies the teams with the highest number of
        games won to that array, and sorts the array alphabetically */
        best_teams = (TeamLink *)can_fail_malloc(best_teams_num * sizeof(TeamLink));

        for (i = 0; i < team_ht.size; i++)
        {
            for (t = team_ht.header[i]; t != NULL; t = t->next)
            {
                if (t->games_won == best_score)
                {
                    best_teams[j++] = t;
                }
            }
        }

        qsort(best_teams, best_teams_num, sizeof(TeamLink), team_comp_name);

        /* Prints out the teams in alphabetical order */

        printf("%ld Melhores %d\n", NL, best_score);

        for (i = 0; i < best_teams_num; i++)
        {
            printf("%ld * %s\n", NL, best_teams[i]->team);
        }

        /* Frees the second array */

        free(best_teams);
    }
}

/* Deletes a team hash table, freeing the space it took up */
void team_ht_free(TeamHT team_ht)
{
    int i;
    TeamLink head, next;

    for (i = 0; i < team_ht.size; i++)
    {
        head = team_ht.header[i];
        while (head != NULL)
        {
            next = head->next;
            free(head->team);
            free(head);
            head = next;
        }
    }
    free(team_ht.header);
}