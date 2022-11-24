#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "match.h"

/* Creates a new match */
Match newMatch(char *name, char *team1, char *team2, int score1, int score2)
{
    Match match = (Match)can_fail_malloc(sizeof(struct match));

    match->name = copyString(name);
    match->team1 = copyString(team1);
    match->team2 = copyString(team2);
    match->score1 = score1;
    match->score2 = score2;

    return match;
}

/* Print a match */
void printMatch(Match match)
{
    printf("%s %s %s %d %d\n", match->name, match->team1, match->team2, match->score1, 
                               match->score2);
}

/* Free the data of a match */
void freeMatch(Match match)
{
    free(match->name);
    free(match->team1);
    free(match->team2);
    free(match);
}