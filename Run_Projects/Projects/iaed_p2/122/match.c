#include <stdlib.h>
#include "match.h"
#include "strdup.h"

/* duplicates a match*/
MATCH matchdup(MATCH original) {
    MATCH dup;
    dup = malloc(sizeof(struct match));
    dup->name = _strdup(original->name);
    dup->team1 = _strdup(original->team1);
    dup->team2 = _strdup(original->team2);
    dup->score.score_team1 = original->score.score_team1;
    dup->score.score_team2 = original->score.score_team2;
    return dup;
}