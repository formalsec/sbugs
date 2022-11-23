#include "utils.h"
#include "teams.h"
#include "matches.h"

Teams * add_new_team(Teams * teams, char* buffer);
Matches * add_new_match(Matches * matches, char* buffer);

struct Teams *teams;
struct Matches *matches;

int nl = 0;