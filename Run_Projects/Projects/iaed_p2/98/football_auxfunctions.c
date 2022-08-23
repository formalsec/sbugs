#include "football_auxfunctions.h"

/* General hash function that returns the index of the
   table in where to put or search for the item.       */
int hash(char* v, int M)
{
    int h = 0, a = 127;

    for (; *v != '\0'; v++)
        h = (a*h + *v) % M;
    
    return h;
}

/* Creates a pointer to a string (array of characters). */
/*char* strdup(char str[])
{ 
    char* name = malloc(sizeof(char)*(strlen(str)+1));

    strcpy(name, str);

    return name;
}*/

/* Creates a pointer to a Game struct with the arguments given. */
Game createGame(char name[], char team1[], char team2[], int score1, int score2)
{
    Game x = malloc(sizeof(struct stru_Game));

    x->name = strdup(name);
    x->team1 = strdup(team1);
    x->team2 = strdup(team2);
    x->score1 = score1;
    x->score2 = score2;

    return x;
}

/* Inserts a Game item at the end of the linked list of Games. */
void insertGameList(Game item, List_Limits headAndTail)
{
    Game_Link x = malloc(sizeof(struct node_G));

    x->item = item;
    x->next = NULL;

    /* If no Games added, x is the new head. */
    if (headAndTail->head == NULL){
        x->prev = NULL;
        headAndTail->head = x;     
    }
    /* At least one Game added. */
    else{
        x->prev = headAndTail->tail;
        headAndTail->tail->next = x;
    }
    
    headAndTail->tail = x;  /* x is always the new Tail. */

}

/* Inserts Game item in the begining of a hashtable index. */
void insertGameTable(Game item, Game_Link* heads)
{   
    Game_Link x;
    int i = hash(item->name, SG); /* Calculates the index to insert the game. */

    x = malloc(sizeof(struct node_G));

    x->item = item;
    x->prev = NULL; /* x is always the new head */

    /* At least one Game added at index i. */
    if (heads[i] != NULL){
        heads[i]->prev = x;
        x->next = heads[i];
    }
    /* No Games added. */
    else
       x->next = NULL;
    
    heads[i] = x;

}

/* Frees memory used for a Game. */
void freeGameAux(Game x)
{
    free(x->name);
    free(x->team1);
    free(x->team2);
    free(x);
}

/* Removes a Game item of the table 'headsG' and linked list 'headAndTail'. */
void freeGame(Game item, int i, Game_Link* headsG, List_Limits headAndTail)
{
    /* t1 and t2 will contain the Game item to remove; s1 and s2
       will if necessary link the rest of the list.  */
    Game_Link t1, t2, s1, s2;

    /* The Game item to remove is the first one at the index i;
       t1 is the Game item to remove and the list is linked.    */
    if (headsG[i]->item == item){
        t1 = headsG[i];
        headsG[i] = t1->next;
        /* More than one Game item at this index. */
        if (headsG[i] != NULL)
            headsG[i]->prev = NULL;
    }
    /* The Game item to remove is not the first one at this index. */
    else
        for (t1 = headsG[i]->next; t1 != NULL; t1 = t1->next){
            /* If t1->item is the item to remove and the list is linked. */
            if (t1->item == item){
                s1 = t1->prev;
                s1->next = t1->next;
                /* The item is not the last one at this index. */
                if (t1->next != NULL){
                    s1 = t1->next;
                    s1->prev = t1->prev;
                }
                /* Exit the for cycle. */
                break;
            }
        }

    /* Only one Game added to the list. */
    if (headAndTail->head == headAndTail->tail){
        t2 = headAndTail->head;
        headAndTail->head = NULL;
        headAndTail->tail = NULL;
    }
    /* The Game item to remove is the first item added. */
    else if (headAndTail->head->item == item){
        t2 = headAndTail->head;
        headAndTail->head = t2->next;
        headAndTail->head->prev = NULL;
    }
    /* The Game item to remove is the last item added. */
    else if (headAndTail->tail->item == item){
        t2 = headAndTail->tail;
        headAndTail->tail = t2->prev;
        headAndTail->tail->next = NULL;
    }
    else
        for (t2 = headAndTail->head->next; t2 != NULL; t2 = t2->next)
            /* If t2->item is the item to remove and the list is linked. */
            if (t2->item == item){
                s2 = t2->prev;
                s2->next = t2->next;
                /* The item is not the last one at this index. */
                if (t2->next != NULL){
                    s2 = t2->next;
                    s2->prev = t2->prev;
                }
                /* Exit the for cycle. */
                break;
            }

    /* Frees the memory associated with the Game item; the t2->item is not freed
       because it is the same as the t1->item, it has already been freed.        */
    freeGameAux(t1->item);
    free(t1);
    free(t2);

}

/* Finds a Game in a index i of the hashtable, by comparing
   each Game item name, to the one given.                   */
Game searchGame(char name[], Game_Link* heads)
{
    Game_Link t;
    char* pname = strdup(name); /* Creates pointer to string. */
    int i = hash(pname, SG); /* Calculates the index in where to search. */

    /* For cycle to traverse the index i of the Games hashtable. */
    for (t = heads[i]; t != NULL; t = t->next)
        /* Compares the item->name with the one given;
           if it is the same the item is returned.     */
        if(strcmp(t->item->name, pname) == 0){
            free(pname);
            return t->item;
        }

    free(pname);

    /* No item found. */
    return NULL;

}

/* Creates a pointer to a Team struct with the arguments given. */
Team createTeam(char name[])
{
    Team x = malloc(sizeof(struct stru_Team));
    
    x->name = strdup(name);
    x->victories = 0; /* Team victories is none. */

    return x;
}

/* Calculates the index in where to insert the Team;
   calls the auxiliar function to insert it.         */
void insertTeam(Team item, Team_Link* heads)
{
    Team_Link x = malloc(sizeof(struct node_G));
    int i = hash(item->name, SG);

    x->item = item;
    x->next = heads[i];
    heads[i] = x;

}

/* Finds a Team in a index i of the hashtable, by comparing
   each Team item name, to the one given.                   */
Team searchTeam(char name[], Team_Link* heads)
{
    Team_Link t;
    char* pname = strdup(name); /* Creates pointer to string. */
    int i = hash(pname, ST); /* Calculates the index in where to search. */

    /* For cycle to traverse the index i of the Games hashtable. */
    for (t = heads[i]; t != NULL; t = t->next)
        /* Compares the item->name with the one given;
           if it is the same the item is returned. */
        if(strcmp(t->item->name, pname) == 0){
            free(pname);
            return t->item;
        }

    free(pname);

    /* No item found. */
    return NULL;
}
