#include <string.h>
#include <stdlib.h>

typedef struct team{
    char *name;
    int gameswon;
} TEAM;

typedef struct nodeteam{
    struct team* team;
    struct nodeteam* next;
} entry_team;

typedef struct {
    entry_team **entries;
} ht_team;

TEAM aux[100000];

ht_team *ht_create_hteam(void);
entry_team *ht_pair_team(TEAM *team);
unsigned int hash_team(char *team);
void ht_set_team(int line, ht_team *hashtable, TEAM* team);
TEAM *ht_get_team(ht_team *hashtable, char *team);
void ht_dump_team(ht_team *hashtable);
TEAM* getTeam(char *name);
void find_max(ht_team *hashtable, int line);
void order_array(ht_team * hashtable,int max, int maxTeamNumber, int line);
void merge_alphabet(TEAM a[], int left, int m, int right);
void mergesort_alphabet(TEAM a[], int l, int r);
