#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashtableGame.h"
#include "HashtableTeam.h"

/* Prime number defining initial hashtable size */
#define FACTOR 3011

/* Number of elements on the hashtable upon creation */
#define INIT_HT_SIZE 0

/* Maximum string size (including end character) */
#define MAX_STRING 1024

/* Size of the score array */
#define SCORE 2

/* Initial variable values */
#define INIT_VALUES 0


/* Copies the games from an hashtable to another array.
*  @params: src - source array from the hashtable;
*           dest - destination array to copy the games to;
*           size - size of the source array.
*  @returns: void.
*/
static void copyGames(Game **src, Game *dest, int size)
{
    int i, j;

    j = 0;

    for(i = 0; i < size; i++)
    {
        if(src[i] != NULL && !src[i]->isDeleted)
        {
            dest[j++] = *(src[i]);
        }
    }
}

/* Copies the teams from an hashtable to another array.
*  @params: src - source array from the hashtable;
*           dest - destination array to copy the teams to;
*           size - size of the source array.
*  @returns: void.
*/
static void copyTeams(Team **src, Team *dest, int size)
{
    int i, j;

    j = 0;

    for(i = 0; i < size; i++)
    {
        if(src[i] != NULL && !src[i]->isDeleted)
        {
            dest[j++] = *(src[i]);
        }
    }
}

/* Compare function for qsort();
*  Ensures games are sorted by order of insertion.
*/
static int compareGame(const void *a, const void *b)
{
    Game *game1, *game2;

    game1 = (Game*) a;
    game2 = (Game*) b;

    return (game1->id - game2->id);
}

/* Compare function for qsort();
*  Ensures teams are sorted by most won games.
*/
static int compareTeam(const void *a, const void *b)
{
    Team *team1, *team2;

    team1 = (Team*) a;
    team2 = (Team*) b;

    return (team2->nWon - team1->nWon);
}

/* Compare function for qsort();
*  Ensures teams are sorted by lexicographic order.
*/
static int compareTeamName(const void *a, const void *b)
{
    Team *team1, *team2;

    team1 = (Team*) a;
    team2 = (Team*) b;

    return (strcmp(team1->name, team2->name));
}

/* Adds a new game.
*  Command 'a'.
*  @params: htg - hashtable of games;
*           htt - hashtable of teams;
*           cmdCount - command counter;
*           id - unique game identifier;
*           score - array of 2 representing the score of the game;
*           teamStr1 - name of the home team;
*           teamStr2 - name of the away team;
*           name - name of the game.
*  @returns: void.
*/
void addGame(HTG *htg, HTT *htt, int cmdCount, unsigned int id,
                unsigned int score[], char *teamStr1,
                 char *teamStr2, char *name)
{
    Game *game;
    Team *team1, *team2;

    /* Find game and teams */
    game = getGame(htg, name);
    team1 = getTeam(htt, teamStr1);
    team2 = getTeam(htt, teamStr2);

    /* Handle errors in case game already exists or teams do not */
    if(game != NULL)
    {
        printf("%d Jogo existente.\n", cmdCount);
        return;
    }
    else if(team1 == NULL || team2 == NULL)
    {
        printf("%d Equipa inexistente.\n", cmdCount);
        return;
    }
    
    /* Create new game and insert it on the hashtable */
    game = newGame(id, score, team1, team2, name);
    insertHTG(htg, game);
}

/* Adds a new team.
*  Command 'A'.
*  @params: htt - hashtable of teams;
*           id - team unique identifier;
*           cmdCount - command counter;
*           name - name of the team.
*  @returns: void.
*/
void addTeam(HTT *htt, unsigned int id, int cmdCount, char *name)
{
    Team *team;

    /* Find team */
    team = getTeam(htt, name);

    /* Handle error if team already exists */
    if(team != NULL)
    {
        printf("%d Equipa existente.\n", cmdCount);
        return;
    }

    /* Create new team and insert it on the hashtable */
    team = newTeam(id, name);
    insertHTT(htt, team);
}

/* Search for a team given its name.
*  Command 'P'.
*  @params: htt - hashtable of teams;
*           cmdCount - command counter;
*           name - name of the team.
*  @returns: void.
*/
void searchTeam(HTT *htt, int cmdCount, char *name)
{
    Team *team;

    /* Find team */
    team = getTeam(htt, name);

    /* Handle error if team does not exist */
    if(team == NULL)
    {
        printf("%d Equipa inexistente.\n", cmdCount);
        return;
    }

    /* Print the team and its win record */
    printf("%d %s %d\n", cmdCount, team->name, team->nWon);
}

/* Search for a game given its name.
*  Command 'p'.
*  @params: htg - hashtable of games;
*           cmdCount - command counter;
*           name - name of the game.
*  @returns: void.
*/
void searchGame(HTG *htg, int cmdCount, char *name)
{
    Game *game;

    /* Find game */
    game = getGame(htg, name);

    /* Handle error if game does not exist */
    if(game == NULL)
    {
        printf("%d Jogo inexistente.\n", cmdCount);
        return;
    }

    /* Print the game and all its details */
    printf("%d %s %s %s %u %u\n", cmdCount, game->name,
             game->team1->name, game->team2->name,
              game->score[0], game->score[1]);
}

/* Lists all games.
*  Command 'l'.
*  @params: htg - hashtable of games;
*           cmdCount - command counter.
*  @returns: void.
*/
void listGames(HTG *htg, int cmdCount)
{
    Game *games, **vector;
    int size, factor, i;

    size = htg->size;
    factor = htg->factor;
    vector = htg->items;

    /* Return if there are no games to list */
    if(size == 0)
    {
        return;
    }

    /* Sort games to new array by insertion order */
    games = (Game*) malloc(sizeof(Game)*size);
    copyGames(vector, games, factor);
    qsort(games, size, sizeof(Game), compareGame);

    /* Print games */
    for(i = 0; i < size; i++)
    {
        printf("%d %s %s %s %u %u\n", cmdCount, games[i].name,
                games[i].team1->name, games[i].team2->name,
                 games[i].score[0], games[i].score[1]);
    }

    /* Free the allocated memory for the sorted array */
    free(games);
}

/* Changes the score on an existing game.
*  Command 's'.
*  @params: htg - hashtable of games;
*           cmdCount - command counter;
*           name - name of the game;
*           score - new score to update.
*  @returns: void.
*/
void changeScore(HTG *htg, int cmdCount, char *name,
                 unsigned int score[])
{
    Game *game;

    game = getGame(htg, name);

    /* Handle error if game does not exist */
    if(game == NULL)
    {
        printf("%d Jogo inexistente.\n", cmdCount);
        return;
    }

    /* Update number of wins for teams considering new score */
    if(game->score[0] > game->score[1])
    {
        if(score[0] < score[1])
        {
            game->team1->nWon--;
            game->team2->nWon++;
        }
        else if(score[0] == score[1])
        {
            game->team1->nWon--;   
        }
    }
    else if(game->score[0] < game->score[1])
    {
        if(score[0] > score[1])
        {
            game->team1->nWon++;
            game->team2->nWon--;
        }
        else if(score[0] == score[1])
        {
            game->team2->nWon--;    
        }
    }
    else if(game->score[0] == game->score[1])
    {
        if(score[0] > score[1])
        {
            game->team1->nWon++;
        }
        else if(score[0] < score[1])
        {
            game->team2->nWon++;
        }
    }

    /* Update the score of the game */
    game->score[0] = score[0];
    game->score[1] = score[1];
}

/* Lists teams with the most wins.
*  Command 'g'.
*  @params: htt - hashtable of teams;
*           cmdCount - command counter.
*  @returns: void.
*/
void listMostWon(HTT *htt, int cmdCount)
{
    Team *teams, **vector;
    char **temp;
    int i, size, factor;

    size = htt->size;
    factor = htt->factor;
    vector = htt->items;

    /* Return if no teams exist */
    if(size == 0)
    {
        return;
    }

    /* Sort teams by most wins to new array */
    teams = (Team*) malloc(sizeof(Team)*size);
    copyTeams(vector, teams, factor);
    qsort(teams, size, sizeof(Team), compareTeam);

    /* Count how many teams have the most wins */
    for(i = 0; i < size; i++)
    {
        if(teams[i].nWon != teams[0].nWon)
        {
            break;
        }
    }

    size = i;

    /* Sort teams with most wins in lexicographic order */
    temp = (char**) malloc(sizeof(char*)*size);

    for(i = 0; i < size; i++)
    {
        temp[i] = teams[i].name;
    }

    qsort(temp, size, sizeof(char*), compareTeamName);

    /* Print teams with most wins by lexicographic order */
    printf("%d Melhores %d\n", cmdCount, teams[0].nWon);

    for(i = 0; i < size; i++)
    {
        printf("%d * %s\n", cmdCount, temp[i]);
    }

    /* Free the allocated memory for the sorted arrays */
    free(teams);
    free(temp);
}

/* Removes a given game.
*  Command 'r'.
*  @params: htg - hashtable of games;
*           cmdCount - command counter;
*           name - name of the game to be removed.
*  @returns: void.
*/
void removeGame(HTG *htg, int cmdCount, char *name)
{
    Game *game;

    /* Find game */
    game = getGame(htg, name);

    /* Handle error if game does not exist */
    if(game == NULL)
    {
        printf("%d Jogo inexistente.\n", cmdCount);
        return;
    }

    /* Update number of wins for the related teams */
    if(game->score[0] > game->score[1])
    {
        game->team1->nWon--;
    }
    else if(game->score[0] < game->score[1])
    {
        game->team2->nWon--;
    }

    /* Remove the game */
    deleteHTG(htg, game);
}

/* Free the allocated memory of the hashtables.
*  @params: htg - hashtable of games;
*           htt - hashtable of teams.
*  @returns: void.
*/
void freeTables(HTG *htg, HTT *htt)
{
    freeHTT(htt);
    freeHTG(htg);
}

/* Menu to choose action given a command.
*  @params: htg - hashtable of games;
*           htt - hashtable of teams;
*           cmdCount - command counter;
*           teamID - team unique identifier;
*           gameID - game unique identifier;
*           score - array of 2 representing the score of the game;
*           command - given by the user to perform a given action;
*           name - name of the game or team;
*           teamStr1 - name of the home team;
*           teamStr2 - name of the away team.
*  @returns: void.
*/
void menu(HTG *htg, HTT *htt, int cmdCount, unsigned int teamID,
             unsigned int gameID, unsigned int score[],
              char command, char name[], char teamStr1[], char teamStr2[])
{
    while(command != 'x')
    {
        switch (command)
        {
        case 'a':
            getchar();
            scanf("%[^:\n]:", name);
            scanf("%[^:\n]:", teamStr1);
            scanf("%[^:\n]:", teamStr2);
            scanf("%u:", &score[0]);
            scanf("%u", &score[1]);

            addGame(htg, htt, ++cmdCount, gameID++, score, teamStr1,
                     teamStr2, name);
            break;

        case 'l':
            listGames(htg, ++cmdCount);
            break;

        case 'p':
            getchar();
            scanf("%[^:\n]", name);

            searchGame(htg, ++cmdCount, name);
            break;

        case 'r':
            getchar();
            scanf("%[^:\n]", name);

            removeGame(htg, ++cmdCount, name);
            break;

        case 's':
            getchar();
            scanf("%[^:\n]:", name);
            scanf("%u:", &score[0]);
            scanf("%u", &score[1]);

            changeScore(htg, ++cmdCount, name, score);
            break;

        case 'A':
            getchar();
            scanf("%[^:\n]", name);

            addTeam(htt, teamID++, ++cmdCount, name);
            break;

        case 'P':
            getchar();
            scanf("%[^:\n]", name);

            searchTeam(htt, ++cmdCount, name);
            break;

        case 'g':
            listMostWon(htt, ++cmdCount);
            break;
        
        default:
            break;
        }

        /* Read new command until 'x' is given */
        command = getchar();
    }
}

/* Main function
*/
int main()
{
    int cmdCount;
    unsigned int teamID, gameID;
    unsigned int score[SCORE];

    char command;
    char name[MAX_STRING];
    char teamStr1[MAX_STRING];
    char teamStr2[MAX_STRING];

    HTG *htg;
    HTT *htt;

    /* Create two new hashtables for games and teams */
    htg = newHTG(FACTOR, INIT_HT_SIZE);
    htt = newHTT(FACTOR, INIT_HT_SIZE);

    /* Initialize values */
    cmdCount = INIT_VALUES;
    teamID = INIT_VALUES;
    gameID = INIT_VALUES;

    /* Read command */
    command = getchar();

    /* Choose action given the read command */
    menu(htg, htt, cmdCount, teamID, gameID, score, command,
         name, teamStr1, teamStr2);

    /* Free the allocated memory of teams and games hashtables */
    freeTables(htg, htt);

    return 0;
}