#ifndef _TEAMS_
#define _TEAMS_

/* Node structure that holds a single team's name and the total number 
of games it has won, as well as a pointer to the next node */
struct TeamNode
{
    char *team;
    int games_won;
    struct TeamNode *next;
};
typedef struct TeamNode *TeamLink;

/* Team hash table wich countains a pointer to an array of headers, 
its size (number of headers) and the number of teams currently stored within */
typedef struct TeamHT
{
    TeamLink *header;
    int size, teams_num;
} TeamHT;

/**************************** Function prototypes ****************************/
int name_hash(int size, char *c);
TeamHT team_ht_init(int size);
void team_ht_insert(TeamHT *team_ht_ptr, char *team, unsigned long int NL);
TeamLink team_ht_search(TeamHT team_ht, char *team);
void team_ht_search_print(TeamHT team_ht, char *team, unsigned long int NL);
void team_ht_print_best(TeamHT team_ht, unsigned long int NL);
void team_ht_free(TeamHT team_ht);

#endif