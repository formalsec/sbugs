#include "utils.h"

typedef struct Matches {
    char match_name[MAX_BUFF];
    char team1[MAX_BUFF];
    char team2[MAX_BUFF];
    int score1;
    int score2;
    int winner;
    struct Matches * next;
} Matches;

Matches * add_match_to_list(Matches ** head, char *m_name, char *m_team1, char *m_team2, int m_score1, int m_score2);
bool match_exists(Matches ** head, char* name);
bool team_exists_match(Matches ** head, char* name);
Matches * delete_match_from_list(Matches ** head, char* m_name);
void print_match_found(Matches ** head, char* name);
void free_matches(Matches * head);