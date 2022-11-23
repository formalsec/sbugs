#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "team.h"
#include "match.h"
#include "hashtable.h"
#include "auxiliar.h"

/* Function declarations */
Link addMatch(int nl, Hash matches, Hash teams, char *name, char *team1, char *team2, int score1,
              int score2);
void listMatches(int nl, Link head);
void searchMatch(int nl, Hash matches, char *name);
Link removeMatch(int nl, Hash matches, Hash teams, char *name);
void changeScore(int nl, Hash matches, Hash teams, char *name, int score1, int score2);
Link addTeam(int nl, Hash teams, char *name);
void searchTeam(int nl, Hash teams, char *name);
void findWinners(int nl, Link firstTeam);
void freeData(Link firstMatch, Link firstTeam);

/*------------------------------------------------------------------------------------------------*/

/* Read the commands from stdin and execute them */
int main()
{
    char command, name[MAX_INPUT], team1[MAX_INPUT], team2[MAX_INPUT];
    int nl = 0, score1, score2;
    Hash matches = initHash(), teams = initHash();
    Link temp = NULL, firstMatch = NULL, lastMatch = NULL, /* Lists to save the */
        firstTeam = NULL, lastTeam = NULL;                 /* introduction order*/

    while ((command = getchar()) != 'x' && command != EOF)
    {
        getchar(); /* Clean space or '\n' */

        nl++;

        switch (command)
        {
        case 'a':
            scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d\n", name, team1, team2, &score1, &score2);
            temp = addMatch(nl, matches, teams, name, team1, team2, score1, score2);
            if (temp != NULL) insertDLL(&firstMatch, &lastMatch, temp);
            break;
        case 'l':
            listMatches(nl, firstMatch);
            break;
        case 'p':
            scanf("%[^:\n]\n", name);
            searchMatch(nl, matches, name);
            break;
        case 'r':
            scanf("%[^:\n]\n", name);
            temp = removeMatch(nl, matches, teams, name);
            if (temp != NULL) removeDLL(&firstMatch, &lastMatch, temp);
            break;
        case 's':
            scanf("%[^:\n]:%d:%d\n", name, &score1, &score2);
            changeScore(nl, matches, teams, name, score1, score2);
            break;
        case 'A':
            scanf("%[^:\n]\n", name);
            temp = addTeam(nl, teams, name);
            if (temp != NULL) insertDLL(&firstTeam, &lastTeam, temp);
            break;
        case 'P':
            scanf("%[^:\n]\n", name);
            searchTeam(nl, teams, name);
            break;
        case 'g':
            findWinners(nl, firstTeam);
            break;
        }
    }

    freeData(firstMatch, firstTeam);
    free(matches);
    free(teams);

    return 0;
}

/*------------------------------------------------------------------------------------------------*/

/* Main Functions */

/* Command a: Add a new match */
Link addMatch(int nl, Hash matches, Hash teams, char *name, char *team1, char *team2, int score1,
              int score2)
{
    Link new = NULL, teamNode = NULL;
    Team team;
    Match match;

    if (searchHash(matches, name) == NULL)
    {
        if (searchHash(teams, team1) != NULL && searchHash(teams, team2) != NULL)
        {
            match = newMatch(name, team1, team2, score1, score2);
            new = newNode(name, match);
            insertHash(matches, name, new);

            if (score1 != score2)
            {
                if (score1 > score2)
                    teamNode = searchHash(teams, team1);
                else if (score1 < score2)
                    teamNode = searchHash(teams, team2);

                team = (Team)teamNode->data;
                team->victories++;
            }
        }
        else
        {
            printf("%d Equipa inexistente.\n", nl);
        }
    }
    else
    {
        printf("%d Jogo existente.\n", nl);
    }
    return new;
}

/* Command l: List the matches by introduction order */
void listMatches(int nl, Link head)
{
    for (; head != NULL; head = head->next_order)
    {
        Match match = (Match)head->data;
        printf("%d ", nl);
        printMatch(match);
    }
}

/* Command p: Search a match */
void searchMatch(int nl, Hash matches, char *name)
{
    Link matchNode = searchHash(matches, name);
    if (matchNode != NULL)
    {
        Match match = (Match)matchNode->data;
        printf("%d ", nl);
        printMatch(match);
    }
    else
    {
        printf("%d Jogo inexistente.\n", nl);
    }
}

/* Command r: Remove a match */
Link removeMatch(int nl, Hash matches, Hash teams, char *name)
{
    Link matchNode, teamNode;
    Match match;
    Team team;

    matchNode = searchHash(matches, name);
    if (matchNode != NULL)
    {
        match = (Match)matchNode->data;
        removeHash(matches, name);

        if (match->score1 != match->score2)
        {
            if (match->score1 > match->score2)
                teamNode = searchHash(teams, match->team1);
            else if (match->score1 < match->score2)
                teamNode = searchHash(teams, match->team2);

            team = (Team)teamNode->data;
            team->victories--;
        }
        freeMatch((Match)matchNode->data);
    }
    else
    {
        printf("%d Jogo inexistente.\n", nl);
    }
    return matchNode;
}

/* Command s: Change the score of a match */
void changeScore(int nl, Hash matches, Hash teams, char *name, int score1, int score2)
{
    Link matchNode, teamNode;
    Match match;
    Team team;

    matchNode = searchHash(matches, name);
    if (matchNode != NULL)
    {
        match = (Match)matchNode->data;

        if (match->score1 != match->score2)
        {
            if (match->score1 > match->score2)
                teamNode = searchHash(teams, match->team1);
            else if (match->score1 < match->score2)
                teamNode = searchHash(teams, match->team2);

            team = (Team)teamNode->data;
            team->victories--;
        }

        if (score1 != score2)
        {
            if (score1 > score2)
                teamNode = searchHash(teams, match->team1);
            else if (score1 < score2)
                teamNode = searchHash(teams, match->team2);

            team = (Team)teamNode->data;
            team->victories++;
        }

        match->score1 = score1;
        match->score2 = score2;
    }
    else
    {
        printf("%d Jogo inexistente.\n", nl);
    }
}

/* Command A: Add a new team */
Link addTeam(int nl, Hash teams, char *name)
{
    Link new = NULL;
    if (searchHash(teams, name) == NULL)
    {
        Team team = newTeam(name);
        new = newNode(name, team);
        insertHash(teams, name, new);
    }
    else
    {
        printf("%d Equipa existente.\n", nl);
    }
    return new;
}

/* Command P: Search a team */
void searchTeam(int nl, Hash teams, char *name)
{
    Link teamNode = searchHash(teams, name);
    if (teamNode != NULL)
    {
        Team team = (Team)teamNode->data;
        printf("%d ", nl);
        printTeam(team);
    }
    else
    {
        printf("%d Equipa inexistente.\n", nl);
    }
}

/* Command g: Find the teams with the  most wins */
void findWinners(int nl, Link firstTeam)
{
    Link temp;
    Team team;
    int victories, mostVictories = 0, count = 0, i;
    char **teams = (char **)can_fail_malloc(sizeof(char *));

    while (firstTeam != NULL)
    {
        temp = firstTeam;
        firstTeam = firstTeam->next_order;
        team = (Team)temp->data;
        victories = team->victories;

        if (victories > mostVictories)
        {
            mostVictories = victories;
            count = 0;
        }

        if (victories == mostVictories)
        {
            count++;
            teams = (char **)can_fail_realloc(teams, sizeof(char *) * count);
            *(teams + count - 1) = team->name;
        }
    }

    sort(teams, count);

    if (count > 0)
    {
        printf("%d Melhores %d\n", nl, mostVictories);
        for (i = 0; i < count; i++)
        {
            printf("%d * %s\n", nl, teams[i]);
        }
    }

    free(teams);
}

/* Free the data of the matches and teams */
void freeData(Link firstMatch, Link firstTeam)
{
    Link temp;

    while (firstMatch != NULL)
    {
        temp = firstMatch;
        firstMatch = firstMatch->next_order;
        freeMatch((Match)temp->data);
        freeNode(temp);
    }

    while (firstTeam != NULL)
    {
        temp = firstTeam;
        firstTeam = firstTeam->next_order;
        freeTeam((Team)temp->data);
        freeNode(temp);
    }
}