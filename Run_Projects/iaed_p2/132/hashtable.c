#include "hashtable.h"

#define HASH_KEY 911    /* hash key used for the hashtables */


/* strdup: duplicate a string into the heap */
// char *strdup(char *s)
// {
//     char *p;
    
//     p = malloc(strlen(s) + 1);  /* allocate memory */
//     if (p != NULL)
//         strcpy(p, s);           /* copy string to the allocated memory */
//     return p;
// }


/* hash: hash an item based on a string */
/* used both for teams hashtable and games hashtable */
int hash(char *s, int m)
{
    int h = 0, a = 127;

    for (; *s != '\0'; s++)
        h = (a * h + *s) % m;
    return h;
}



/* =============================================================== */
/* **************** Teams' manipulation functions **************** */
/* =============================================================== */

/* init_teams: initialize hashtable to store teams */
tnode **init_teams(tnode **teams_tab)
{
    int i;

    /* allocate lists in the hashtables */
    teams_tab = malloc(HASH_KEY * sizeof(tnode));   
    for (i = 0; i < HASH_KEY; i++)
        teams_tab[i] = NULL;
    return teams_tab;
}


/* destroy_teams: free all memory utilized by nodes of teams */
void destroy_teams(tnode **teams_tab)
{
    int i;

    for (i = 0; i < HASH_KEY; i++)
        destroy_tnode(teams_tab[i]);
    free(teams_tab);
}


/* table_insert_team: insert a team into the hashtable of teams */
void table_insert_team(tnode **teams_tab, team *t)
{
    int i;

    i = hash(t->name, HASH_KEY);
    teams_tab[i] = insert_team_begin(teams_tab[i], t);
}


/* table_search_team: search for a team in the hashtable of teams */
team *table_search_team(tnode **teams_tab, char *name)
{
    int i;

    i = hash(name, HASH_KEY);
    return lookup_team(teams_tab[i], name);
}


/* new_team: create a new team */
team *new_team(char *name)
{
    team *t = malloc(sizeof(team));

    /* set attributes */
    t->name = strdup(name);
    t->wins = 0;

    return t;
}


/* insert_team_begin: insert a team to the beginning of a linked list of teams */
tnode *insert_team_begin(tnode *head, team *t)
{
    tnode *new = malloc(sizeof(tnode));

    new->t = t;
    new->next = head;

    return new;
}


/* lookup_team: search for a team in a linked list of teams */
team *lookup_team(tnode *head, char *name)
{
    tnode *tmp;

    for (tmp = head; tmp != NULL; tmp = tmp->next)
        if (strcmp(tmp->t->name, name) == 0)
            return tmp->t;

    return NULL;
}


/* destroy_tnode: frees all nodes and teams of a linked list of teams */
tnode *destroy_tnode(tnode *head)
{
    tnode *tmp;

    while (head != NULL) {
        tmp = head->next;
        free_tnode(head);
        head = tmp;
    }
    return head;
}


/* free_tnode: free a node and the team that it stores */
void free_tnode(tnode *n)
{
    free(n->t->name);
    free(n->t);
    free(n);
}


/* =============================================================== */
/* *********** List top teams command specific functions ********* */
/* =============================================================== */

/* table_search_higher: search for the higher number of wins
 * in the hashtable of teams */
int table_search_higher(tnode **teams_tab)
{
    int i;
    int higher = -1;    /* init with invalid number */

    for (i = 0; i < HASH_KEY; i++)  /* search through each list of the hashtable */
        higher = lookup_higher(teams_tab[i], higher);

    return higher;
}


/* lookup_higher: search for the higher number of wins
 * in a linked list of teams */
int lookup_higher(tnode *head, int higher)
{
    tnode *tmp;

    for (tmp = head; tmp != NULL; tmp = tmp->next)
        if (tmp->t->wins > higher)
            higher = tmp->t->wins;

    return higher;
}


/* search_top_teams: search for all teams with the higher number of wins 
 * in the hashtable and add them to top_teams */
tnode *table_search_top_teams(tnode **teams_tab, tnode *top_teams, int higher)
{
    int i;

    for (i = 0; i < HASH_KEY; i++)
        top_teams = lookup_top_team(teams_tab[i], top_teams, higher);

    return top_teams;
}


/* lookup_top_team: search all teams with the higher number of wins
 * in a linked list of teams and add them to top_teams */
tnode *lookup_top_team(tnode *head, tnode *top_teams, int higher)
{
    tnode *tmp;

    for (tmp = head; tmp != NULL; tmp = tmp->next)
        if (tmp->t->wins == higher)
            top_teams = insert_team_sorted(top_teams, tmp->t);

    return top_teams;
}


/* insert_team_sorted: insert a team in a linked list of teams 
 * in alphabetical order of names */
tnode *insert_team_sorted(tnode *top_teams, team *t)
{
    tnode *tmp, *next;
    tnode *new = malloc(sizeof(tnode));
    
    /* if list is empty or new team should be the firt element of the list */
    if (top_teams == NULL || strcmp(top_teams->t->name, t->name) < 0) {
        new->t = t;
        new->next = top_teams;
    
        return new;
    }

    /* find the correct place to link the new team */
    for (tmp = top_teams, next = tmp->next; next != NULL; tmp = tmp->next, next = tmp->next) {
        if (strcmp(tmp->t->name, t->name) > 0 && strcmp(next->t->name, t->name) < 0)
            break;
    }

    /* update links */
    new->t = t;
    tmp->next = new;
    new->next = next;

    return top_teams;
}


/* destroy_teams_list: free all nodes in a linked list of teams */
tnode *destroy_teams_list(tnode *head)
{
    tnode *tmp;

    while (head != NULL) {
        tmp = head->next;
        free(head);
        head = tmp;
    }

    return head;
}



/* =============================================================== */
/* **************** Games' manipulation functions **************** */
/* =============================================================== */

/* init_games: initialize hashtable to store games */
gnode **init_games(gnode **games_tab)
{
    int i;

    games_tab = malloc(HASH_KEY * sizeof(gnode));
    for (i = 0; i < HASH_KEY; i++)
        games_tab[i] = NULL;
    return games_tab;
}


/* destroy_games: free all memory utilized by gnodes */
void destroy_games(gnode **games_tab)
{
    int i;

    for (i = 0; i < HASH_KEY; i++)
        destroy_gnode(games_tab[i]);
    free(games_tab);
}


/* table_insert_game: inserts a game into the hashtable of games */
void table_insert_game(gnode **games_tab, game *g)
{
    int i;

    i = hash(g->name, HASH_KEY);
    games_tab[i] = insert_game_begin(games_tab[i], g);
}


/* table_delete_game: deletes a game from the hashtable of games */
void table_delete_game(gnode **games_tab, char *name)
{
    int i;

    i = hash(name, HASH_KEY);
    games_tab[i] = delete_game(games_tab[i], name);
}


/* table_search_game: search for game in the hashtable of games */
game *table_search_game(gnode **games_tab, char *name)
{
    int i;

    i = hash(name, HASH_KEY);
    return lookup_game(games_tab[i], name);
}


/* new_game: create new game */
game *new_game(char *name, char *team1, char *team2, int score1, int score2)
{
    game *g = malloc(sizeof(game));

    /* set attributes */
    g->name = strdup(name);
    g->t1 = strdup(team1);
    g->t2 = strdup(team2);
    g->score1 = score1;
    g->score2 = score2;

    return g;
}


/* insert_game_begin: insert a game to the beginning of a linked list of games */
gnode *insert_game_begin(gnode *head, game *g)
{
    gnode *new = malloc(sizeof(gnode));

    new->g = g;
    new->next = head;

    return new;
}


/* delete_game: delete and free a node in a linked list of games */
gnode *delete_game(gnode *head, char *name)
{
    gnode *tmp, *prev;

    for (tmp = head, prev = NULL; tmp != NULL; prev = tmp, tmp = tmp->next) {
        if (!strcmp(tmp->g->name, name)) {

            if (tmp == head)
                head = tmp->next;
            else 
                prev->next = tmp->next;
            
            free(tmp);
            break;
        }
    }
    return head;
}


/* lookup_game: search for a game in a linked list of games */
game *lookup_game(gnode *head, char *name)
{
    gnode *tmp;

    for (tmp = head; tmp != NULL; tmp = tmp->next)
        if (!strcmp(tmp->g->name, name))
            return tmp->g;

    return NULL;
}


/* destroy_gnode: free all nodes of a linked list of games */
gnode *destroy_gnode(gnode *head)
{
    gnode *tmp;

    while (head != NULL) {
        tmp = head->next;
        free(head);
        head = tmp;
    }
    return head;
}


/* =============================================================== */
/* ************ List with all games specific functions *********** */
/* =============================================================== */

/* del_from_glist: delete and free a node and a game 
    from a linked list of games */
gnode *del_from_glist(gnode *head, char *name)
{
    gnode *tmp, *prev;

    for (tmp = head, prev = NULL; tmp != NULL;  prev = tmp, tmp = tmp->next) {
        if (!strcmp(tmp->g->name, name)) {
            if (tmp == head)
                head = tmp->next;
            else
                prev->next = tmp->next;
            free_gnode(tmp);
            return head;
        }
    }
    return head;
}


/* destroy_glist: free all nodes and games of a linked list of games */
gnode *destroy_games_list(gnode *games_list)
{
    gnode *tmp;

    while (games_list != NULL) {
        tmp = games_list->next;
        free_gnode(games_list);
        games_list = tmp;
    }
    return NULL;
}


/* free_gnode: free a node and the game that it stores */
void free_gnode(gnode *n)
{
    free(n->g->name);
    free(n->g->t1);
    free(n->g->t2);
    free(n->g);
    free(n);
}
