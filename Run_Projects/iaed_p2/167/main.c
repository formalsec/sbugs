#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "hashtable.h"
#include "strdup.h"
/* ============================================================ */
/* boolean values */
#define TRUE 1
#define FALSE 0

/* initial hashtable size */
#define SIZE 100000

/* string size */
#define STRSZ 1024
/* ============================================================ */
node * AddGameLL(node *head, char *name, char *team1, char *team2, int score1, int score2); /* function that adds a new game to the linked list */
p_game * AddGameHT(p_game *p, char *name, char *team1, char *team2, int score1, int score2, int N, int M); /* function that adds a new game to the hash table */
p_team * AddTeamHT(p_team *t, char *team, int N, int M); /* function that adds a new team to the hash table */
void ListsGames(node *head, int NL); /* function that lists all existing games */
void SearchesGame(p_game *games, int M, int NL); /* function that searches and returns a specific game */
void SearchesTeam(p_team *t, int M, int NL); /* function that searches and returns a specific team */
int ChecksNameGame(p_game *p, char *name, int NL, int M); /* function that checks if a certain string corresponds to an existing game */
int ChangesScore(p_team *teams, int score1, int score2, int M_T, char *name, p_game game_test); /* function that retuns the new score of a game */
void ListsWinningTeams(p_team *t, int M, int NL); /* function that lists the teams with the most wins */
/* ============================================================ */
p_game ObtainsGame(); /* function that reads all input necessary and returns the new game */
int ChecksGame(int M1, int M2, char *name, char *team1, char *team2, p_team *t, p_game *p, int NL); /* function that checks if a game is deemed acceptable */ 
int ChecksTeam(p_team *t, char *team, int NL, int M); /* function that checks if a team is deemed acceptable */
int ObtainsArguments(p_game *p, char *name, int M, int NL);  /* function that checks if the arguments are acceptable for the following operations */
int StringCompare(const void *A, const void *B); /* function that compares two strings */
/* ============================================================ */

int main()
{    
    char command, string1[STRSZ], string2[STRSZ], name[STRSZ], team1[STRSZ], team2[STRSZ];
    
    int NL = 1, M_G = SIZE, M_T = SIZE, output = FALSE; /* instruction counter, hash table's size */

    int El_G = 0, El_T = 0, score1i, score2i; /* counters for each hashtable */

    node *head = NULL; /* initial linked list for games */

    p_game game_test, *game_test_p, *games = Init(M_G); /* initial hashtable for games */

    p_team *team_test_p, *teams = Init_T(M_T); /* initial hashtable for teams */

    do
    {
        scanf("%c", &command);

        switch (command)
        {
            case 'a':
            scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", name, team1, team2, &score1i, &score2i);
            if (ChecksGame(M_G, M_T, name, team1, team2, teams, games, NL) == TRUE) /* checks if it is possible to create the required game */
            {
                head = AddGameLL(head, name, team1, team2, score1i, score2i); /* adds game to linked list */
                if ((game_test_p = AddGameHT(games, name, team1, team2, score1i, score2i, El_G, M_G)) == NULL) /* checks if it is necessary to expand the hash table for games */
                {
                    games = Expand(games, El_G, M_G); /* expands hash table */
                    M_G = M_G + M_G;
                    games = AddGameHT(games, name, team1, team2, score1i, score2i, El_G, M_G); /* adds game to hash table of games */
                }
                else
                {
                    games = game_test_p;
                }
                if (score1i > score2i) /* verifies who wins the game in question */
                    { Search_T(teams, team1, M_T)->wins++; }
                    else if (score1i < score2i)
                    { Search_T(teams, team2, M_T)->wins++; }
                El_G++;   
            }
            NL++;
            break;

            case 'A':
            scanf(" %[^:\n]\n", string1);
            if (ChecksTeam(teams, string1, NL, M_T) == TRUE) /* checks if it is possible to create the required team */
            {
                if ((team_test_p = AddTeamHT(teams, string1, El_T, M_T)) == NULL) /* checks if it is necessary to expand the hash table for teams */
                {
                    teams = Expand_T(teams, El_T, M_T); /* expands hash table */
                    M_T = M_T + M_T;
                    teams = AddTeamHT(teams, string1, El_T, M_T); /* adds game to hash table of teams */
                }
                El_T++;
            }
            NL++;
            break;

            case 'l':
            ListsGames(head, NL);
            NL++;
            break;

            case 'p':
            SearchesGame(games, M_G, NL);
            NL++;
            break;

            case 'P':
            SearchesTeam(teams, M_T, NL);
            NL++;
            break;

            case 'r':
            scanf(" %[^:\n]\n", string2);
            if (ChecksNameGame(games, string2, NL, M_G) == TRUE) /* checks if the string is acceptable */
            {
                if (Search(games, string2, M_G)->score1 > Search(games, string2, M_G)->score2) /* checks if it is necessary to change the number of wins of any team */
                {
                    --Search_T(teams, Search(games, string2, M_G)->team1, M_G)->wins;
                }
                else if (Search(games, string2, M_G)->score1 < Search(games, string2, M_G)->score2)
                {
                    --Search_T(teams, Search(games, string2, M_G)->team2, M_G)->wins;
                }
                head = ListDelete(head, string2); /* removes the game from the linked list */
                games = HTRemoveElement(games, string2, El_G, M_G); /* removes the game from the hash table of games */
                El_G--;
            }
            NL++;
            break;

            case 's':
            scanf(" %[^:\n]:%d:%d", string1, &score1i, &score2i);
            if (ObtainsArguments(games, string1, M_G, NL) == TRUE) /* checks if the arguments are acceptable */
            {
                game_test = Search(games, string1, M_G);
                /* changes the number of wins of the game in the hash table of games */
                Search_T(teams, game_test->team1, M_G)->wins = ChangesScore(teams, score1i, score2i, M_T, game_test->team1, game_test);
                Search_T(teams, game_test->team2, M_G)->wins = ChangesScore(teams, score1i, score2i, M_T, game_test->team2, game_test);
                /* changes the score of the game in the hash table of games */
                Search(games, game_test->name, M_G)->score1 = score1i;
                Search(games, game_test->name, M_G)->score2 = score2i;
                /* changes the number of wins of the game in the linked list */
                SearchLL(head, game_test->name)->score1 = score1i;
                SearchLL(head, game_test->name)->score2 = score2i;
            }
            NL++;
            break;

            case 'g':
            ListsWinningTeams(teams, M_T, NL);
            NL++;
            break;

            case 'x':
            output = TRUE;
            break;

            default:
            break;
        }
    } while (output != TRUE);
    /* frees all dynamical allocated memory */
    head = DestroyList(head);
    games = FreeAllHT(games, M_G);
    teams = FreeAllHT_T(teams, M_T);
    free(head);
    free(games);
    free(teams);
    return 0;
}
/* ============================================================ */
/* Command Functions */

node * AddGameLL(node *head, char *name, char *team1, char *team2, int score1, int score2)
{
    node *new_head;
    new_head = AddElement(head, name, team1, team2, score1, score2); /* adds game to the linked list */
    return new_head;
}

p_game * AddGameHT(p_game *p, char *name, char *team1, char *team2, int score1, int score2, int N, int M)
{
    p_game *new_game;
    new_game = HTInsertElement(p, name, team1, team2, score1, score2, N, M); /* adds game to the hash table */
    return new_game;
}

p_team * AddTeamHT(p_team *t, char *team, int N, int M)
{
    p_team *new_team;
    new_team = HTInsertElement_T(t, team, 0, N, M); /* adds team to the hash table */
    return new_team;    
}

void ListsGames(node *head, int NL)
{
    if (head == NULL)
    { return; }
    ListsGames(head->next, NL); /* calls it self to reach the end of the linked list */
    printf("%d %s %s %s %d %d\n", NL, head->name, head->team1, head->team2, head->score1, head->score2); /* prints all games from the end of the linked list to the beginning */
}

void SearchesGame(p_game *games, int M, int NL)
{
    char name[STRSZ];
    p_game game;
    scanf("%s", name);
    game = Search(games, name, M);
    if (game != NULL) /* checks if the game exists */
    {
        printf("%d %s %s %s %d %d\n", NL, game->name, game->team1, game->team2, game->score1, game->score2);
    }
    else /* if it doesn't returns an error */
    {
        printf("%d Jogo inexistente.\n", NL);
    }
}

void SearchesTeam(p_team *t, int M, int NL)
{
    char name[STRSZ];
    p_team team;
    scanf(" %[^:\n]", name);
    team = Search_T(t, name, M);
    if (team != NULL) /* checks if the team exists */
    {
        printf("%d %s %d\n", NL, team->name, team->wins);
    }
    else /* if it doesn't returns an error */
    {
        printf("%d Equipa inexistente.\n", NL);
    }
}

int ChecksNameGame(p_game *p, char *name, int NL, int M)
{
    p_game game_aux;
    if ((game_aux = Search(p, name, M)) == NULL) /* checks if the game exists */
    {
        /* if it doesn't returns an error */
        printf("%d Jogo inexistente.\n", NL);
        return FALSE;
    }
    return TRUE;
}


int ChangesScore(p_team *teams, int score1, int score2, int M_T, char *name, p_game game_test)
{
    int final_value;
    /* checks who had previously won */
    if (game_test->score1 > game_test->score2)
    {
        /* checks who wins with the new score */ 
        if (score1 < score2) 
        {
            if (strcmp(name, game_test->team1) == 0)
            {
                final_value = Search_T(teams, game_test->team1, M_T)->wins - 1;
                return final_value;
            }
            else
            {
                final_value = Search_T(teams, game_test->team2, M_T)->wins + 1;
                return final_value;
            }
        }
        else if (score1 == score2)
        {
            if (strcmp(name, game_test->team1) == 0)
            {
                final_value = Search_T(teams, game_test->team1, M_T)->wins - 1;
                return final_value;
            }
            else
            {
                final_value = Search_T(teams, game_test->team2, M_T)->wins;
                return final_value;
            }
        }
        else
        {
            if (strcmp(name, game_test->team1) == 0)
            {
                final_value = Search_T(teams, game_test->team1, M_T)->wins;
                return final_value;
            }
            else
            {
                final_value = Search_T(teams, game_test->team2, M_T)->wins;
                return final_value;
            }
        }                   
    }

    else if (game_test->score1 < game_test->score2)
    {
        if (score1 > score2)
        {
            if (strcmp(name, game_test->team1) == 0)
            {
                final_value = Search_T(teams, game_test->team1, M_T)->wins + 1;
                return final_value;
            }
            else
            {
                final_value = Search_T(teams, game_test->team2, M_T)->wins - 1;
                return final_value;
            }
        }
        else if (score1 == score2)
        {
            if (strcmp(name, game_test->team1) == 0)
            {
                final_value = Search_T(teams, game_test->team1, M_T)->wins;
                return final_value;
            }
            else
            {
                final_value = Search_T(teams, game_test->team2, M_T)->wins - 1;
                return final_value;
            }
        }
        else
        {
            if (strcmp(name, game_test->team1) == 0)
            {
                final_value = Search_T(teams, game_test->team1, M_T)->wins;
                return final_value;
            }
            else
            {
                final_value = Search_T(teams, game_test->team2, M_T)->wins;
                return final_value;
            }
        }
    }

    else
    {
        if (score1 > score2)
        {
            if (strcmp(name, game_test->team1) == 0)
            {
                final_value = Search_T(teams, game_test->team1, M_T)->wins + 1;
                return final_value;
            }
            else
            {
                final_value = Search_T(teams, game_test->team2, M_T)->wins;
                return final_value;
            }
        }
        else if (score1 < score2)
        {
            if (strcmp(name, game_test->team1) == 0)
            {
                final_value = Search_T(teams, game_test->team1, M_T)->wins;
                return final_value;
            }
            else
            {
                final_value = Search_T(teams, game_test->team2, M_T)->wins + 1;
                return final_value;
            }
        }
        else
        {
            if (strcmp(name, game_test->team1) == 0)
            {
                final_value = Search_T(teams, game_test->team1, M_T)->wins;
                return final_value;
            }
            else
            {
                final_value = Search_T(teams, game_test->team2, M_T)->wins;
                return final_value;
            }    
        }
    }
    return 0;
}

void ListsWinningTeams(p_team *t, int M, int NL)
{
    int i, j = 0, max = -1;
    char *vector[STRSZ];

    for (i = 0; i < M; i++) /* iterates the hash table */
    {
        if (t[i] != NULL && t[i]->wins > max)
        {
            max = t[i]->wins; /* if it finds a new max saves the value */
        } 
    }
    
    if (max == -1) /* if there are no games ends function */
    {
        return;
    }
    
    for (i = 0; i < M; i++)
    {
        if (t[i] != NULL && t[i]->wins == max)
        {
            vector[j] = d_strdup(t[i]->name); /* creates an array of strings that have the highest number of wins */
            j++;
        }
    }

    qsort(vector, j, sizeof(char *), StringCompare); /* sorts the array */

    printf("%d Melhores %d\n", NL, max);

    for (i = 0; i < j; i++)
    {
        printf("%d * %s\n", NL, vector[i]); /* prints the elements of the array */
        free(vector[i]);
    }
    return;    
}

/* ============================================================ */
/* Auxiliary Functions */

int ChecksGame(int M1, int M2, char *name, char *team1, char *team2, p_team *t, p_game *p, int NL)
{
    if (Search(p, name, M1) != NULL) /* checks if the name of the game is in the hash table of games */
    {
        printf("%d Jogo existente.\n", NL);
        return FALSE;
    }
    else if (Search_T(t, team1, M2) == NULL) /* checks if the name of the first team is in th hash table of teams */
    {
        printf("%d Equipa inexistente.\n", NL);
        return FALSE;
    }
    else if (Search_T(t, team2, M2) == NULL) /* checks if the name of the second team is in th hash table of teams */
    {
        printf("%d Equipa inexistente.\n", NL);
        return FALSE;
    }
    return TRUE;
}

int ChecksTeam(p_team *t, char *team, int NL, int M)
{
    if (Search_T(t, team, M) != NULL) /* checks if the name of the team is in th hash table of teams */
    {
        printf("%d Equipa existente.\n", NL);
        return FALSE;
    }
    return TRUE;
}

int ObtainsArguments(p_game *p, char *name, int M, int NL)
{
    if (Search(p, name, M) != NULL) /* checks if the name of the game is in the hash table of games */
    {
        return TRUE;
    }
    else
    {
        printf("%d Jogo inexistente.\n", NL);
        return FALSE;
    }
}

int StringCompare(const void *A, const void *B)
{
    char **s_1, **s_2;
    s_1 = (char **) A;
    s_2 = (char **) B;
    return strcmp(*s_1, *s_2);
}