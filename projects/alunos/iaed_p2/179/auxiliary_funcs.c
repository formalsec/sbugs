#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "auxiliary_funcs.h"

/* ------ Auxiliar functions ------ */

int length(char str[MAXLEN]){
    int i, cont = 0;
    for(i = 0; str[i] != '\0'; i++)
        cont++;
    return cont;
}

void strCopy(char *str1, char *str2){
    int i;
    for(i = 0; *(str1+i) != '\0'; i++)
        *(str2+i) = *(str1+i);

    *(str2+i) = '\0';
}

char* allocateWrite(char str[MAXLEN]){
    int len = length(str)+1;    /* length + '\0' */
    char *ptr = can_fail_malloc(sizeof(char)*len);
    strCopy(str, ptr);
    return ptr;
}

int compareQsort(const void *a, const void *b){
    const Team *t1 = (Team*) a;
    const Team *t2 = (Team*) b;
    return strcmp((*t1)->name, (*t2)->name);
}

void withdrawVictory(Ht_teams ht, char *name){
    Team t = HTsearchTeam(ht, name);
    t->won--;
    t = NULL;
}

void addVictory(Ht_teams ht, char *name){
    Team t = HTsearchTeam(ht, name);
    t->won++;
    t = NULL;
}

int mostWins(nodeTeam head){
    if(head == NULL)
        return -1;

    else{
        unsigned int w = head->ptr->won;
        nodeTeam aux;

        for(aux = head->next; aux != NULL; aux = aux->next){
            if(aux->ptr->won > w)
                w = aux->ptr->won;
        }

        aux = NULL;
        return w;
    }
}

int countTeams(nodeTeam head, unsigned int w){
    int c;
    nodeTeam aux;

    for(c = 0, aux = head; aux != NULL; aux = aux->next){
        if(aux->ptr->won == w)
            c++;
    }

    aux = NULL;
    return c;
}

Team* nWinsTeams(nodeTeam head, int n, unsigned int w){
    int i;
    nodeTeam aux;
    Team *teams = can_fail_malloc(n*sizeof(Team));

    for(i = 0, aux = head; aux != NULL; aux = aux->next){
        if(aux->ptr->won == w){
            teams[i] = aux->ptr;
            i++;
        }
    }
    
    aux = NULL;
    return teams;
}

void changeWins(Ht_teams ht, Game *game,\
                int score1, int score2, int prev1, int prev2){
/* Winner: team1 */
    if(score1 > score2){
        if(prev2 > prev1){
            addVictory(ht, (*game)->team1);
            withdrawVictory(ht, (*game)->team2);
        }

        else if(prev1 == prev2)
            addVictory(ht, (*game)->team1);
    }

    /* Winner: team2 */
    else if(score2 > score1){
        if(prev1 > prev2){
            addVictory(ht, (*game)->team2);
            withdrawVictory(ht, (*game)->team1);
        }

        else if(prev1 == prev2)
            addVictory(ht, (*game)->team2);
    }

    /* Tie */
    else{
        if(prev1 > prev2)
            withdrawVictory(ht, (*game)->team1);
        else if(prev2 > prev1)
            withdrawVictory(ht, (*game)->team2);
    }
}

void outputGame(Game game, int outL){
    printf("%d %s %s %s %d %d\n", outL, game->name, game->team1,\
            game->team2, game->score1, game->score2);
}

void outputTeam(Team team, int outL){
    printf("%d %s %d\n", outL, team->name, team->won);
}

void freeMemory(Ht_games htg, Ht_teams htt, nodeGame hg, nodeTeam ht){
    freeHTGames(htg);
    freeHTTeams(htt);
    hg = destroyLinkedGames(hg);
    ht = destroyLinkedTeams(ht);
}
