#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "team.h"

/*Creates a team with the given name and returns a pointer to that team*/
Team_ptr NewTeam(char *name)
{
    Team_ptr new_team = (Team_ptr)can_fail_malloc(sizeof(struct Team));

    name(new_team) = StringDup(name);
    wins(new_team) = INITIAL_WINS;
    return new_team;
}

/*Prints the elements of a team*/
void PrintTeam(Team_ptr team)
{
    printf("%s %d\n", name(team), wins(team));
}

/*Frees the team name and the team pointer*/
void FreeTeam(Team_ptr team)
{
    free(name(team));
    free(team);
}

/*Creates a struct TeamHash with a hash_table of size max and returns a pointer to it*/
TeamHash_ptr TeamHashInit(int max)
{
    int i;
    TeamHash_ptr team_hash = (TeamHash_ptr)can_fail_malloc(sizeof(struct TeamHash));

    item_count(team_hash) = INITIAL_ITEM_COUNT;
    hash_size(team_hash) = max;
    team_hash->hash_table = (Team_ptr *)can_fail_malloc(hash_size(team_hash) * sizeof(Team_ptr));

    /*Initialize every pointer with NULL*/
    for (i = 0; i < hash_size(team_hash); i++)
        team_hash->hash_table[i] = NULL;

    return team_hash;
}

/*Inserts a team in the team_hash*/
TeamHash_ptr TeamHashInsert(TeamHash_ptr *team_hash, Team_ptr team)
{
    int i = HashU(name(team), hash_size((*team_hash)));

    /*Search for the first available space*/
    while ((*team_hash)->hash_table[i] != NULL)
        i = (i + 1) % hash_size((*team_hash));

    (*team_hash)->hash_table[i] = team; /*Insert the pointer in the available space*/
    item_count((*team_hash))++;         /*Increment the item_count of the TeamHash*/

    /*If the occupancy is equal or over than 50%, expand the hash*/
    if (item_count((*team_hash)) >= hash_size((*team_hash)) / 2)
    {
        TeamHash_ptr new_hash = TeamHashExpand(*team_hash);
        return new_hash;
    }
    return *team_hash;
}

/*Creates a new struct TeamHash with double the size of the previous hash and with every team from the previous hash.
Returns a pointer to the new struct TeamHash*/
TeamHash_ptr TeamHashExpand(TeamHash_ptr team_hash)
{
    int i;
    Team_ptr *aux = team_hash->hash_table;
    TeamHash_ptr new_hash = TeamHashInit(hash_size(team_hash) * 2);

    /*Inserts every team of the previous hash in the new hash*/
    for (i = 0; i < hash_size(team_hash); i++)
        if (team_hash->hash_table[i] != NULL)
            TeamHashInsert(&new_hash, team_hash->hash_table[i]);

    free(aux);
    free(team_hash);
    return new_hash;
}

/*Returns a pointer to the team with the name equal to the one given*/
Team_ptr TeamHashSearch(TeamHash_ptr team_hash, char *name)
{
    int i = HashU(name, hash_size(team_hash));

    /*Iterates through the hashtable until it finds NULL or the wanted team*/
    while (team_hash->hash_table[i] != NULL)

        if (strcmp(name, name(team_hash->hash_table[i])) == 0)
            return team_hash->hash_table[i];

        else
            i = (i + 1) % hash_size(team_hash);

    return NULL;
}

/*Inserts a Team_ptr in the array*/
void ArrayInsert(Team_ptr best_teams[], Team_ptr team, int *N)
{
    best_teams[(*N)++] = team;
}

/*Given an array of Team_ptr, returns that same array sorted in lexicographal order*/
void mergesort(Team_ptr arr[], int left, int right, TeamHash_ptr team_hash)
{
    int m = (right + left) / 2;

    if (right <= left)
        return;

    mergesort(arr, left, m, team_hash);
    mergesort(arr, m + 1, right, team_hash);
    merge(arr, left, m, right, team_hash);
}

/*Auxiliar function to mergesort*/
void merge(Team_ptr arr[], int left, int m, int right, TeamHash_ptr team_hash)
{
    Team_ptr *aux = (Team_ptr *)can_fail_malloc(sizeof(Team_ptr) * hash_size(team_hash));

    int i, j, k;

    for (i = m + 1; i > left; i--)
        aux[i - 1] = arr[i - 1];

    for (j = m; j < right; j++)
        aux[right + m - j] = arr[j + 1];

    for (k = left; k <= right; k++)
    {
        if (strcmp(name(aux[j]), name(aux[i])) < 0)
            arr[k] = aux[j--];
        else
            arr[k] = aux[i++];
    }
    free(aux);
}

/*Frees the team_hash*/
void DeleteTeamHash(TeamHash_ptr team_hash)
{
    int i;

    /*Free every team*/
    for (i = 0; i < hash_size(team_hash); i++)
        if (team_hash->hash_table[i] != NULL)
            FreeTeam(team_hash->hash_table[i]);

    free(team_hash->hash_table);
    free(team_hash);
}