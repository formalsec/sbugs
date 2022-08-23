#include "AuxiliaryFunctions.h"

/* Receives an array and two indices, switching those positions.*/
void exch(char ** vetor,int i, int j){
    char * aux = vetor[i];
    vetor[i] = vetor[j];
    vetor[j] = aux;
}

/* Auxiliary function to Quick Sort function.*/
int partition(char ** vetor, int l, int r){
    int i = l-1, j = r;
    char * v = vetor[r];
    while (i < j){
        while (strcmp(vetor[++i],v) < 0);
        while (strcmp(v,vetor[--j]) < 0)
            if (j == l)
                break;
        if (i < j){
            exch(vetor, i, j);
        }
    }
    exch(vetor, i, r);
    
    return i;
}

/* Quick sort function to sort an array of strings using strcmp, by lexicographic order.*/
void Quick_Sort(char ** vetor, int l, int r){
    int i;
    if (r <= l)
        return;
    
    i = partition(vetor, l, r);
    Quick_Sort(vetor, l, i-1);
    Quick_Sort(vetor, i+1, r);
}

/* Receives a List, a hash table of Nodes, a hash table of Teams and the number of Teams. Destroys them all.*/
void Clean(List l, Node * hash_game, Team * hash_team, int * n_teams){
    DestroyList(l);
    DestroyHashGames(hash_game);
    DestroyHashTeams(hash_team, n_teams);
}

/* Receives an array of strings, a hash of Teams, the number of Teams to copy and the best number of goals.
Copies all the Team names with that number of goals to the array "team_names", returning it in the end.*/
char ** CreatesTeamNames(char ** team_names, Team * hash_team, int count, int best){
    int i = 0, n = 0;
    team_names = (char**) malloc(sizeof(char*) * count);
    /* The names of the best Teams are copied to "team_names", always allocating the necessary space.*/
    for (; n < count ; i++)
        if (hash_team[i] != NULL && Wins(hash_team[i]) == best){
            team_names[n] = (char*) malloc(MAX_STR);
            strcpy(team_names[n], TeamName(hash_team[i]));
            n++;
        }
    return team_names;
}

/* Receives a number of Games and the size of the hash table of Nodes. Returns True if there is a need of expansion.*/
int CheckHashGame(int * n_games, int * m_game){
    return *n_games >= *m_game * EXPAND;
}

/* Receives a number of Teams and the size of the hash table of Teams. Returns True if there is a need of expansion.*/
int CheckHashTeam(int * n_teams, int * m_team){
    return *n_teams >= *m_team * EXPAND;
}