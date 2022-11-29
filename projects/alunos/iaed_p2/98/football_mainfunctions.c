#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "football_mainfunctions.h"

/* Creates the Games hashtable, by alocating memory 
   and initializing each index of it to NULL.       */
Game_Link* initGameTable()
{
    int i;
    Game_Link* heads = can_fail_malloc(SG*sizeof(Game_Link));

    for (i = 0; i < SG; i++)
        heads[i] = NULL;

    return heads;
}

/* Creates the Teams hashtable, by alocating memory 
   and initializing each index of it to NULL.       */
Team_Link* initTeamTable()
{
    int i;
    Team_Link* heads = can_fail_malloc((ST)*sizeof(Team_Link));

    for (i = 0; i < ST; i++)
        heads[i] = NULL;

    return heads;
}

/* Finds winner of the Game item given as argument, returning
   it; if it's a draw, function returns NULL.                 */
Team findWinner(Game item, Team_Link* heads)
{
    Team x = NULL;

    /* First Team wins. */
    if (item->score1 > item->score2){
        x = searchTeam(item->team1, heads);
        return x;
    }
    /* Second Team wins. */
    else if (item->score2 > item->score1){
        x = searchTeam(item->team2, heads);
        return x;
    }

    /* Draw. */
    return x;
}

/* Reads the necessary information to add a Game to the database; it must
   be a new name and the Teams should also exist in the database.         */
void addGame(int l, Game_Link* headsG, 
List_Limits headAndTail, Team_Link* headsT)
{
    char name[MAX_STR], team1[MAX_STR], team2[MAX_STR];
    int score1, score2;
    Game x;
    Team t;

    /* Reads from standard input the information. */
    scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d", name,
    team1, team2,
    &score1, &score2);

    /* Checks if no game added previously has already this name. */
    if (searchGame(name, headsG) != NULL)
        printf("%d Jogo existente.\n", l);

    /* Checks if the two Teams exist. */
    else if ((searchTeam(team1, headsT) == NULL) ||
            (searchTeam(team2, headsT) == NULL))
        printf("%d Equipa inexistente.\n", l);

    /* The Game can be added, as it has been validated. */
    else{
        /* Creates Game and inserts it in the hash and the linked list. */
        x = createGame(name, team1, team2, score1, score2);
        insertGameTable(x, headsG);
        insertGameList(x, headAndTail);

        /* Finds the winner and adds a victory to
           the winning team, if not draw.         */
        t = findWinner(x, headsT);
        if (t != NULL)
            t->victories++;
    }
}

/* Prints Game item given. */
void printGame(int l, Game x)
{
    printf("%d %s %s %s %d %d\n", l, x->name,
        x->team1, x->team2, x->score1, x->score2);
}

/* Lists all the games added, by insertion order;
   it is used the auxiliar linked list. */
void listGames(int l, List_Limits headAndTail)
{
    Game_Link x;
    
    for (x = headAndTail->head; x != NULL; x = x->next)
        printGame(l, x->item);

}

/* Reads the name given from the standard input and finds the Game with
   that name in the hash, printing its information in case it exists.   */
void findGame(int l, Game_Link* heads)
{
    char name[MAX_STR];
    Game x;

    /* Reads from standard input the name. */
    scanf("%[^:\n]", name);

    /* Checks if it exists. */
    x = searchGame(name, heads);

    /* If it exists, the information is printed. */
    if (x != NULL)
        printGame(l, x);
    /* No game with that name. */
    else
        printf("%d Jogo inexistente.\n", l);

}

/* Removes Game from the hash and linked list, in case it exists. */
void removeGame(int l, Game_Link* headsG,
List_Limits headAndTail, Team_Link* headsT)
{
    char name[MAX_STR];
    char* pname;
    Game x;
    Team t;
    int i;

    /* Reads from the standard input the name. */
    scanf("%[^:\n]", name);

    /* Checks if it exists. */
    x = searchGame(name, headsG);
    pname = strdup(name);

    /* If it exists, finds winner and removes one victory to the winning Team */
    if (x != NULL){
        i = hash(pname, SG);
        t = findWinner(x, headsT);
        if (t != NULL)
            t->victories--;

        /* Removes the Game from the database. */
        freeGame(x, i, headsG, headAndTail);
    }
    /* No game with this name in the database. */
    else
        printf("%d Jogo inexistente.\n", l);

    free(pname);

}

/* Reads a name of a Game and the score to be changed;
   if it exists, changes the score from the Game.      */
void changeScore(int l, Game_Link* headsG, Team_Link* headsT)
{
    Game x;
    Team t, s;
    char name[MAX_STR];
    int score1, score2;

    /* Reads from the standard input the name and the new score. */
    scanf("%[^:\n]:%d:%d", name, &score1, &score2);

    /* Checks if the Game exists. */
    x = searchGame(name, headsG);

    /* If no Game has this name. */   
    if (x == NULL)
        printf("%d Jogo inexistente.\n", l);
    /* The Game exists. */
    else{
        /* The score is changed and it is stored in variables t
           and s the winners before and after the replacement.  */
        t = findWinner(x, headsT);
        x->score1 = score1;
        x->score2 = score2;
        s = findWinner(x, headsT);

        /* If the winning Team has changed, it removes the victory
           from the first winner and adds one to the new winner.   */
        if ((t != s) && (s != NULL) && (t != NULL)){
            s->victories++;
            t->victories--;
        }
        /* If after the replacement there were no winners. */
        else if ((t != s) && (t != NULL))
            t->victories--;
        /* If there were no winners and now there is */
        else if ((t != s) && (s != NULL))
            s->victories++;
    }
}

/* Reads the name of the Team to add and adds it
   o the hashtable, if it doesn't exist.         */
void addTeam(int l, Team_Link* heads)
{
    char name[MAX_STR];
    Team x;

    /* Reads from the standard input the name of the Team. */
    scanf("%[^:\n]", name);

    /* Checks if the Team doesn't exist. */
    if (searchTeam(name, heads) == NULL){
        /* Creates the Team and inserts it in the hash. */
        x = createTeam(name);
        insertTeam(x, heads);
    }
    /* Unable to add Team; it already exists. */
    else
        printf("%d Equipa existente.\n", l);

}

/* Reads the name given from the standard input and finds the Team with
   that name in the hash, printing its information in case it exists.   */
void findTeam(int l, Team_Link* heads)
{
    char name[MAX_STR];
    Team x;

    /* Reads the name from the standard input. */
    scanf("%[^:\n]", name);

    /* Checks if the Team exists. */
    x = searchTeam(name, heads);

    /* If it exists, prints it. */
    if (x != NULL)
        printf("%d %s %d\n", l, x->name, x->victories);
    /* No Team with this name. */
    else
        printf("%d Equipa inexistente.\n", l);

}

/* Auxiliar function that is used as an argument to qsort; it compares two
   strings, to order a list of Teams alfabetically by their names.         */
int compareTeamNames(const void* a, const void* b) 
{ 
    Team ia = *(Team*)a;
    Team ib = *(Team*)b;

    return strcmp(ia->name, ib->name);
}

/* Auxiliar function that prints a list of Teams alfabetically by their names. */
void printWinningTeams(int l, int M, int nTeams, Team_Link* heads)
{
    Team_Link x;
    Team* p;    /* Pointer to an array of Teams.  */
    int i = 0, j = 0;

    p = can_fail_malloc(sizeof(Team)*nTeams);

    /* while cycle to find the Teams with the same number
       of victories as max, until all of them are added.  */
    while (j < nTeams){
        /* for cycle to traverse all the Team_Links
           at each index i from the hashtable.      */
        for (x = heads[i]; x != NULL; x = x->next)
            /* If the x->item has the same number of victories
               as M, adds the Team x->item to the array.       */
            if (x->item->victories == M){
                p[j++] = x->item;
                /* Exit condition. */
                if (j >= nTeams)
                    break;
            }
        i++;
    }

    /* Order the array p of Teams by Team names. */
    qsort(p, nTeams, sizeof(Team), compareTeamNames);

    /* Prints the information of the Teams. */
    printf("%d Melhores %d\n", l, M);
    for (i = 0; i < nTeams; i++)
        printf("%d * %s\n", l, p[i]->name);

    free(p);

}

/* Finds Teams with more wins in the hashtable and prints their information. */
void findWinningTeams(int l, Team_Link* heads)
{
    Team_Link x;
    /* max is the maximum number of victories in the hash; nTeams
       is the number of Teams with that number of wins.           */
    int i = 0, max = 0, nTeams = 0;

    /* while cycle to traverse all the index of the hashtable. */
    while (i < ST){
        /* for cycle to traverse all Team_Links in each index. */
        for (x = heads[i]; x != NULL; x = x->next){
            /* If the x->item has more victories than the max, re-sets
               the max variable and the number of Teams.               */
            if (x->item->victories > max){
                max = x->item->victories;
                nTeams = 1;
            }
            /* If the x->item has the same victories as the max,
               adds one victory to the nTeams variable. */
            else if (x->item->victories == max)
                nTeams++;
        }
        i++;
    }

    /* If there are Teams added to the
       database, they are printed.     */
    if (nTeams != 0)
        printWinningTeams(l, max, nTeams, heads);

}

/*----------------------- Free functions ---------------------*/
/* Frees the memory used by a Team_Link
   given (pointer to a node of a list). */
Team_Link freeTeamsLink(Team_Link head)
{
    Team_Link x;

    x = head->next;
    free(head->item->name);
    free(head->item);
    free(head);

    return x;
}

/* Frees the memory used by an index of the Teams hashtable. */
void freeTeamsIndex(Team_Link head)
{
    Team_Link x;

    for(x = head; x != NULL; x = freeTeamsLink(x));

}

/* Frees all memory used by the Teams hashtable */
void freeTeams(Team_Link* heads)
{
    int i;

    for (i = 0; i < ST; i++)
        freeTeamsIndex(heads[i]);
    
    free(heads);

}

/* Frees the memory used by a Game_Link
   given (pointer to a node of a list). */
Game_Link freeGamesListLink(Game_Link head)
{
    Game_Link x;

    x = head->next;
    freeGameAux(head->item);
    free(head);

    return x;
}

/* Frees all memory used by the linked list of Games. */
void freeGamesList(List_Limits headAndTail)
{
    Game_Link x;

    for(x = headAndTail->head; x != NULL; x = freeGamesListLink(x));
    
    free(headAndTail);

}

/* Frees the memory used by a Game_Link given (pointer to a
   node of a list); the head->item is not freed because
   it has already been freed previously from the list.      */
Game_Link freeGamesTableLink(Game_Link head)
{
    Game_Link x;

    x = head->next;
    free(head);

    return x;

}

/* Frees the memory used by an index of the Games hashtable. */
void freeGamesTableIndex(Game_Link head)
{
    Game_Link x;

    for(x = head; x != NULL; x = freeGamesTableLink(x));

}

/* Frees all memory used by the Games hashtable */
void freeGamesTable(Game_Link* heads)
{
    int i;

    for (i = 0; i < SG; i++)
        freeGamesTableIndex(heads[i]);

    free(heads);
}
