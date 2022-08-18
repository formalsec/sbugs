#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define HASH_GAMES_SIZE 1747
#define HASH_TEAMS_SIZE 1009
#define MAX_CHARS 1024


/* STRUCT GAME */

typedef struct game{

    char *name;
    char *team1;
    char *team2;
    int score1;
    int score2;

} game;

/* STRUCT NODE FROM LINKED LIST CONTAINING GAMES */

typedef struct g_node{

    game *pointer_game;
    struct g_node *next;

} g_node;


/* STRUCT TEAM */

typedef struct team{

    char *name;
    int wins;

} team;


/* STRUCT NODE FROM LINKED LIST CONTAINING TEAMS */

typedef struct t_node{

    team *pointer_team;
    struct t_node *next;

} t_node;


/* STRUCT NODE FROM DOUBLY LINKED LIST STORING THE NAMES OF THE GAMES AS THEY ARE INSERTED */

typedef struct game_name_slot{

    char *name;
    struct game_name_slot *next;
    struct game_name_slot *previous;

} game_slot;


/* STRUCT NODE FROM LINKED LIST STORING POINTERS TO TEAMS AS THEY ARE INSERTED */

typedef struct team_name_slot{

    team *pointer_team;
    struct team_name_slot *next;

} team_slot;


/* PROTOTYPES */

game* newGame(char *name, char *team1, char *team2, int score1, int score2);
team* newTeam(char *name);
g_node* insertGameNode(g_node *head, char *name, char *team1, char *team2, int score1, int score2);
t_node* insertTeamNode(t_node *head, char *name);
int hash(char *string, int size);
void addGame(g_node **games, t_node **teams, game_slot **game_storage_head, int NL);
void addWin(t_node **teams, char *name);
void subtractWin(t_node **teams, g_node *pointer_g_node);
void addTeam(t_node **teams, team_slot **team_storage_head, int NL);
void removeGame(g_node **games, t_node **teams, game_slot **game_storage_head, int NL);
void freeAll(g_node **games, t_node **teams, game_slot **game_storage_head, team_slot **team_storage_head);
void deleteGameFromHashTable(g_node **games, g_node *head, char *name, int key);
void deleteGameFromStorage(game_slot **game_storage_head, char *name);
void deleteTeamFromHashTable(t_node **teams, t_node *head, char *name, int key);
void deleteTeamFromStorage(team_slot **team_storage_head, team *pointer_team);
game_slot* findGameInStorage(game_slot *game_storage_head, char *name);
team_slot* findTeamInStorage(team_slot *team_storage_head, team *pointer_team);
team_slot* findPreviousTeamInStorage(team_slot *team_storage_head, team *pointer_team);
g_node* findPreviousGame(g_node *head, char *name);
t_node* findPreviousTeam(t_node *head, char *name);
void listGames(g_node **games, game_slot *game_storage_head, int NL);
g_node* findGame(g_node *head ,char *name);
t_node* findTeam(t_node *head ,char *name);
void lookupGame(g_node **games, int NL);
void lookupTeam(t_node **teams, int NL);
void addGameStorage(game_slot **game_storage_head, char *name);
void addTeamStorage(team_slot **team_storage_head, team *pointer_team);
void changeGameScore(g_node **games, t_node **teams, int NL);
void listWinners(team_slot *team_storage_head, int NL);
void WinsAndWinners(team_slot *team_storage_head, int *max_wins, int *number_winners);
int compare_string(const void *p1, const void *p2);


int main(){

/* hashtables that store pointers to linked lists containing g_nodes/t_nodes
which are nodes containing a game/team and a pointer to the next element */

    g_node **games;
    t_node **teams;

/* initializes pointers to linked lists containing game_slots/team_slots, 
which are nodes containing information about games and teams, by order of insertion */

    game_slot *game_storage_head = NULL;
    team_slot *team_storage_head = NULL;

    char c;

    int NL = 0;                     /* used to show the line in the input that produced the output*/
    int i;

    /* initializes every entry of hashtables games/teams as NULL pointers */
    games = malloc(HASH_GAMES_SIZE * sizeof(g_node*));
    for(i = 0; i < HASH_GAMES_SIZE; i++)
        games[i] = NULL;

    teams = malloc(HASH_TEAMS_SIZE * sizeof(t_node*));
    for(i = 0; i < HASH_TEAMS_SIZE; i++)
        teams[i] = NULL;

    while (1) {

        switch(c = getchar()) {     /* Reads a character from stdin and executes the respective command */
            case 'a':

                addGame(games, teams, &game_storage_head, ++NL);
                break;

            case 'l':

                listGames(games, game_storage_head, ++NL);
                break;

            case 'p':

                lookupGame(games, ++NL);
                break;

            case 'r':

                removeGame(games, teams, &game_storage_head, ++NL);
                break;

            case 's':

                changeGameScore(games, teams, ++NL);
                break;

            case 'A':

                addTeam(teams, &team_storage_head, ++NL);
                break;

            case 'P':

                lookupTeam(teams, ++NL);
                break;

            case 'g':

                listWinners(team_storage_head, ++NL);
                break;

            case 'x':

                freeAll(games, teams, &game_storage_head, &team_storage_head);
                exit(0);
                break;
        }

    }

    return 1;
}



/* Creates a struct game and returns a pointer to its first address */
game* newGame(char *name, char *team1, char *team2, int score1, int score2){

    game *pointer_game = (game*) malloc(sizeof(struct game));

    pointer_game->name = (char*) malloc((strlen(name)+1) * sizeof(char));
    strcpy(pointer_game->name, name);
    pointer_game->team1 = (char*) malloc((strlen(team1)+1) * sizeof(char));
    strcpy(pointer_game->team1, team1);
    pointer_game->team2 = (char*) malloc((strlen(team2)+1) * sizeof(char));
    strcpy(pointer_game->team2, team2);

    pointer_game->score1 = score1;
    pointer_game->score2 = score2;

    return pointer_game;

}

/* Creates a struct team and returns a pointer to its first address */
team* newTeam(char *name){

    team *pointer_team = (team*) malloc(sizeof(struct team));

    pointer_team->name = (char*) malloc((strlen(name)+1) * sizeof(char));
    strcpy(pointer_team->name, name);

    pointer_team->wins = 0;

    return pointer_team;
}


/* Creates a new game node (g_node) and inserts it at the end of a linked list. This linked list was
found by hashing the name of the game and finding a key which contained the pointer to the head of the
respective linked list. Returns a pointer to the linked lists' head. */
g_node* insertGameNode(g_node *head, char *name, char *team1, char *team2, int score1, int score2){

    g_node *pointer_g_node, *aux, *new_head;

    pointer_g_node = malloc(sizeof(struct g_node));
    /* the new head starts off as the previous head, and will only be changed if the linked list is empty */
    new_head = head;
    /* creates the new game node, and assigns NULL to its next, as it is going to be placed at the end */
    pointer_g_node->pointer_game = newGame(name, team1, team2, score1, score2);
    pointer_g_node->next = NULL;
    /* checks if the linked list is not empty */
    if (head != NULL)
    {
        /* traverses the linked list from the head until the last element */
        for(aux = head; aux->next != NULL; aux = aux->next);
        /* assigns the pointer (to the new node) to the last elements' next, making the new node now the 
        last element */
        aux->next = pointer_g_node;
    }
    /* if the linked list is empty, the new node created will now be its head */
    else
        new_head = pointer_g_node;

    return new_head;
}


/* Creates a new team node (t_node) and inserts it at the end of a linked list. This linked list was
found by hashing the name of the team and finding a key which contained the pointer to the head of the
respective linked list. Returns a pointer to the linked lists' head. */
t_node* insertTeamNode(t_node *head, char *name){

    t_node *pointer_t_node, *aux, *new_head;

    pointer_t_node = malloc(sizeof(struct t_node));
    /* the new head starts off as the previous head, and will only be changed if the linked list is empty */
    new_head = head;
    /* creates the new team node, and assigns NULL to its next, as it is going to be placed at the end */
    pointer_t_node->pointer_team = newTeam(name);
    pointer_t_node->next = NULL;
   /* checks if the linked list is not empty */
    if (head != NULL)
    {
        /* traverses the linked list from the head until the last element */
        for(aux = head; aux->next != NULL; aux = aux->next);
        /* assigns the pointer (to the new node) to the last elements' next, making the new node now the 
        last element */
        aux->next = pointer_t_node;
    }
    /* if the linked list is empty, the new node created will now be its head */
    else
        new_head = pointer_t_node;

    return new_head;
}


/* HASH FUNCTION USED FOR BOTH GAMES AND TEAMS  */
int hash(char *string, int size){

    int h = 0, a = 127;

    for (; *string != '\0'; string++)

        h = (a * h + *string) % size;

    return h;
}


/* Adds a game to the system, both to the hashtable containing games and to the game storage */
void addGame(g_node **games, t_node **teams, game_slot **game_storage_head, int NL){

    g_node *g_head;
    t_node *t1_head, *t2_head;
    char name[MAX_CHARS] = "", team1[MAX_CHARS] = "", team2[MAX_CHARS] = "";
    int score1, score2;
    int key_game, key_team1, key_team2;

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", name, team1, team2, &score1, &score2);
    key_game = hash(name, HASH_GAMES_SIZE);
    g_head = games[key_game];
    /*checks if the game already exists in the games' hashtable */
    if (findGame(g_head, name) != NULL)
    {
        printf("%d Jogo existente.\n", NL);
        return;
    }
    /* finds the hash value for both teams and accesses the indexes of the hashtable of those
    values, finding the heads to two linked lists, each one containing one of the teams. */
    key_team1 = hash(team1, HASH_TEAMS_SIZE);
    t1_head = teams[key_team1];
    key_team2 = hash(team2, HASH_TEAMS_SIZE);
    t2_head = teams[key_team2];
    /* checks if the teams do not exist in the teams' hashtable */
    if (findTeam(t1_head, team1) == NULL || findTeam(t2_head, team2) == NULL)
    {
        printf("%d Equipa inexistente.\n", NL);
        return;
    }
    /* adds the game to the hashtable containing games */
    games[key_game] = insertGameNode(g_head, name, team1, team2, score1, score2);
    /* adds the name of the game to the game_storage and alters the head only if it was NULL. */
    addGameStorage(game_storage_head, name);
    /* if one of the teams won the game, adds one to the teams' wins. */
    if (score1 > score2)
        addWin(teams, team1);
    if (score2 > score1)
        addWin(teams, team2);
}


/* Adds a team to the system, both to the hashtable containing teams and to the team storage */
void addTeam(t_node **teams, team_slot **team_storage_head, int NL){

    t_node *head, *pointer_t_node;
    team *pointer_team;
    char name[MAX_CHARS] = "";
    int key;

    scanf(" %[^:\n]", name);
    key = hash(name, HASH_TEAMS_SIZE);
    head = teams[key];
    /*checks if the team already exists in the teams' hashtable */
    if (findTeam(head, name) != NULL)
    {
        printf("%d Equipa existente.\n", NL);
        return;
    }
    /* adds the team to the hashtable containing teams */
    teams[key] = insertTeamNode(head, name);
    /* adds a pointer to the teams' info to the team_storage and alters the head if it was NULL */
    head = teams[key];
    pointer_t_node = findTeam(head, name);
    pointer_team = pointer_t_node->pointer_team;
    addTeamStorage(team_storage_head, pointer_team);
}


/* removes a game from the system, both from the hashtable containing games and from the game storage */
void removeGame(g_node **games, t_node **teams, game_slot **game_storage_head, int NL){

    g_node *g_head, *pointer_g_node;
    char name[MAX_CHARS] = "";
    int key_game;

    scanf(" %[^:\n]", name);
    key_game = hash(name, HASH_GAMES_SIZE);
    g_head = games[key_game];
    pointer_g_node = findGame(g_head, name);
    /* checks if the game exists in the games' hashtable */
    if (pointer_g_node == NULL)    
    {
        printf("%d Jogo inexistente.\n", NL);
        return;
    }
    /* if the game that was removed had a winner, it deletes one win from its info */
    subtractWin(teams, pointer_g_node);
    /* deletes the game from both places where it was stored */
    deleteGameFromHashTable(games, g_head, name, key_game);
    deleteGameFromStorage(game_storage_head, name);
}


/* adds one to the number of wins a certain team has */
void addWin(t_node **teams, char *name){

    t_node *pointer_t_node, *head;
    team *pointer_team;
    int key;

    key = hash(name, HASH_TEAMS_SIZE);
    head = teams[key];

    pointer_t_node = findTeam(head, name);

    pointer_team = pointer_t_node->pointer_team;

    pointer_team->wins += 1;
}

/* subtracts one from the number of wins a certain team has, if it finds that 
one of the given teams had won the game that is being removed */
void subtractWin(t_node **teams, g_node *pointer_g_node){

    t_node *t_head, *pointer_t_node;
    team *pointer_team;
    char *team;
    int key_team, score1, score2;

    score1 = pointer_g_node->pointer_game->score1;
    score2 = pointer_g_node->pointer_game->score2;
    if (score1 > score2 || score2 > score1)
    {
        if(score1 > score2)
            team = pointer_g_node->pointer_game->team1;
        else
            team = pointer_g_node->pointer_game->team2;
        key_team = hash(team, HASH_TEAMS_SIZE);
        t_head = teams[key_team];
        pointer_t_node = findTeam(t_head, team);
        pointer_team = pointer_t_node->pointer_team;
        pointer_team->wins -= 1;
    }
}


/* ends the program, by freeing everything that was dynamically allocated during its execution*/
void freeAll(g_node **games, t_node **teams, game_slot **game_storage_head, team_slot **team_storage_head){

    g_node *g_head;
    t_node *t_head;
    game_slot *g_pointer_slot;
    team_slot *t_pointer_slot;
    team *pointer_team;
    char *name;
    int key;

    /* traverses the game storage, from its head to the last slot */
    while (*game_storage_head != NULL)
    {   
        g_pointer_slot = *game_storage_head;
        name = g_pointer_slot->name;
        key = hash(name, HASH_GAMES_SIZE);
        g_head = games[key];
        /* deletes node (containing a pointer to a game) from the hashtable 
        and the game itself */
        deleteGameFromHashTable(games, g_head, name, key);
        /* deletes slot (containing the name of the game) from storage and alters
        the storage's head to the next slot */
        deleteGameFromStorage(game_storage_head, name);
    }
    /* traverses the team storage, from its head to the last slot */
    while (*team_storage_head != NULL)
    {
        t_pointer_slot = *team_storage_head;
        pointer_team = t_pointer_slot->pointer_team;
        name = pointer_team->name;
        key = hash(name, HASH_TEAMS_SIZE);
        t_head = teams[key];
        /* deletes slot (containing a pointer to a team) from storage and alters
        the storage's head to the next slot */
        deleteTeamFromStorage(team_storage_head, pointer_team);
        /* deletes node (containing a pointer to a team) from the hashtable 
        and the team itself*/
        deleteTeamFromHashTable(teams, t_head, name, key);
    }
}


/* frees a node (containing a pointer to a game) from the hashtable and frees the game structure itself.
the linked lists containing games are doubly linked! */
void deleteGameFromHashTable(g_node **games, g_node *head, char *name, int key){

    g_node *pointer_g_node, *previous;
    game *pointer_game;
    char *team1, *team2, *name_in_hashtable;

    /* finds the node in the hashtable that comes before the one being deleted */
    previous = findPreviousGame(head, name);
    /* if the node being deleted is not the head of the linked list, connects the previous
    node to the next one */
    if(previous != NULL)
    {
        pointer_g_node = previous->next;
        previous->next = pointer_g_node->next;
    }
    /* if the node being deleted is the first one, alters the head of the linked list to 
    the next node, by accessing directly the index of the hashtable that stores the pointer to
    the linked list's head */
    else
    {
        pointer_g_node = head;
        games[key] = pointer_g_node->next;
    }
    /* frees all the memory previously allocated */
    pointer_game = pointer_g_node->pointer_game;
    team1 = pointer_game->team1;
    team2 = pointer_game->team2;
    name_in_hashtable = pointer_game->name;
    free(team1);
    free(team2);
    free(name_in_hashtable);
    free(pointer_game);
    free(pointer_g_node);
}


/* frees a slot (containing the name of a game) from the game storage and frees the name itself */
void deleteGameFromStorage(game_slot **game_storage_head, char *name){

    game_slot *pointer_slot;
    char *name_in_storage;

    /* finds the slot in the storage that contains the game */
    pointer_slot = findGameInStorage(*game_storage_head, name);
    /* if the slot to be deleted is the head of the storage, alters the head
    to the next slot */
    if(*game_storage_head == pointer_slot)
        *game_storage_head = pointer_slot->next;
    /* changes next only if game_slot to be deleted is NOT the last node */
    if (pointer_slot->next != NULL)
        pointer_slot->next->previous = pointer_slot->previous;
    /* changes previous only if game_slot to be deleted is NOT the first node */
    if (pointer_slot->previous != NULL)
        pointer_slot->previous->next = pointer_slot->next;
    name_in_storage = pointer_slot->name;
    /* frees the memory allocated for the name in storage and for the slot containing the name */
    free(name_in_storage);
    free(pointer_slot);
}


/* frees a node (containing a pointer to a team) from the hashtable and frees the team structure itself */
void deleteTeamFromHashTable(t_node **teams, t_node *head, char *name, int key){

    t_node *pointer_t_node, *previous;
    team *pointer_team;
    char *name_in_hashtable;

    previous = findPreviousTeam(head, name);
    /* if the node being deleted is not the first one, alters the linked list in the hashtable 
    as to have the last element before the one removed pointing to the one that came after the one removed */
    if(previous != NULL)
    {
        pointer_t_node = previous->next;
        previous->next = pointer_t_node->next;
    }   
    /* if the node being deleted is the first one, alters the head of the linked list to the next node, 
    by accessing directly the index of the hashtable that stores the pointer to the linked list's head */
    else
    {
        pointer_t_node = head;
        teams[key] = pointer_t_node->next;
    }
    /* frees all the memory allocated previously */
    pointer_team = pointer_t_node->pointer_team;
    name_in_hashtable = pointer_team->name;
    free(name_in_hashtable);
    free(pointer_team);
    free(pointer_t_node);
}


/* frees a slot (containing a pointer to a team) */
void deleteTeamFromStorage(team_slot **team_storage_head, team *pointer_team){

    team_slot *pointer_slot, *previous_pointer_slot;

    previous_pointer_slot = findPreviousTeamInStorage(*team_storage_head, pointer_team);
    /* if the slot being deleted is not the head, alters the storage as to have the last 
    element before the one removed pointing to the one that came after the one removed */
    if (previous_pointer_slot != NULL)
    {
        pointer_slot = previous_pointer_slot->next;
        previous_pointer_slot->next = pointer_slot->next;
    }
    /* if the slot being deleted is the first one, alters the head of the storage to the next node */
    else
    {
        pointer_slot = *team_storage_head;
        *team_storage_head = pointer_slot->next;
    }
    /* frees the memory allocated for the slot containing the name */
    free(pointer_slot);
}


/* searches for a game in the hashtable, and, if the search is successful, prints its information */
void lookupGame(g_node **games, int NL){

    g_node *head, *pointer_g_node;
    game *pointer_game;
    char name[MAX_CHARS] = "";
    int key;

    scanf(" %[^:\n]", name);
    key = hash(name, HASH_GAMES_SIZE);
    head = games[key];
    pointer_g_node = findGame(head, name);
    if (pointer_g_node == NULL)
    {
        printf("%d Jogo inexistente.\n", NL);
        return;
    }
    pointer_game = pointer_g_node->pointer_game;
    printf("%d %s %s %s %d %d\n", NL, pointer_game->name, pointer_game->team1, pointer_game->team2,
           pointer_game->score1, pointer_game->score2);
}


/* searches for a team in the hashtable, and, if the search is successful, prints its information */
void lookupTeam(t_node **teams, int NL){

    t_node *head, *pointer_t_node;
    team *pointer_team;
    char name[MAX_CHARS] = "";
    int key;

    scanf(" %[^:\n]", name);
    key = hash(name, HASH_TEAMS_SIZE);
    head = teams[key];
    pointer_t_node = findTeam(head, name);
    if (pointer_t_node == NULL)
    {
        printf("%d Equipa inexistente.\n", NL);
        return;
    }
    pointer_team = pointer_t_node->pointer_team;
    printf("%d %s %d\n", NL, pointer_team->name, pointer_team->wins);
}


/* creates a new game_name_slot, inserting it at the beggining of the linked list that stores names of games */
void addGameStorage(game_slot **game_storage_head, char *name){

    game_slot *pointer_slot;

    /* allocates game_slot struct and puts in the data */
    pointer_slot = malloc(sizeof(game_slot));
    pointer_slot->name = (char*) malloc((strlen(name)+1) * sizeof(char));
    strcpy(pointer_slot->name, name);
    /* makes next of new slot as head and previous as NULL */
    pointer_slot->next = *game_storage_head;
    pointer_slot->previous = NULL;
    /* changes previous of head to new slot */
    if (*game_storage_head != NULL)
        (*game_storage_head)->previous = pointer_slot;
    /* new head is the new slot */
    *game_storage_head = pointer_slot;
}


/* creates a new team_name node, inserting it at the beginning of the linked list that stores names of teams */
void addTeamStorage(team_slot **team_storage_head, team *pointer_team){

    team_slot *pointer_slot;

    /* allocates team_slot struct and puts in the data */
    pointer_slot = malloc(sizeof(team_slot));
    pointer_slot->pointer_team = pointer_team;
    /* if it is the first slot, the next is made NULL */
    if (*team_storage_head == NULL)
        pointer_slot->next = NULL;
    /* if it is not, the next is made the current head */
    else
        pointer_slot->next = *team_storage_head;
    /* new head is the new slot */
    *team_storage_head = pointer_slot;
}


/* alters the score of a given game */
void changeGameScore(g_node **games, t_node **teams, int NL){

    g_node *g_head, *pointer_g_node;
    t_node *t_head, *pointer_t_node1, *pointer_t_node2;
    game *pointer_game;
    team *pointer_team1, *pointer_team2;
    char name[MAX_CHARS] = "", *team1, *team2;
    int key, score1, score2, previous_score1, previous_score2;

    scanf(" %[^:\n]:%d:%d", name, &score1, &score2);
    key = hash(name, HASH_GAMES_SIZE);
    g_head = games[key];
    pointer_g_node = findGame(g_head, name);
    /*checks if the game exists */
    if (pointer_g_node == NULL)
    {
        printf("%d Jogo inexistente.\n", NL);
        return;
    }
    /* reads the previous scores the teams had on those games */
    pointer_game = pointer_g_node->pointer_game;
    team1 = pointer_game->team1;
    team2 = pointer_game->team2;
    previous_score1 = pointer_game->score1;
    previous_score2 = pointer_game->score2;
    /* finds the pointer to both team structures */
    key = hash(team1, HASH_TEAMS_SIZE);
    t_head = teams[key];
    pointer_t_node1 = findTeam(t_head, team1);
    pointer_team1 = pointer_t_node1->pointer_team;
    key = hash(team2, HASH_TEAMS_SIZE);
    t_head = teams[key];
    pointer_t_node2 = findTeam(t_head, team2);
    pointer_team2 = pointer_t_node2->pointer_team;
    /*alters the wins of the teams, if necessary */
    if ((previous_score1 <= previous_score2) && (score1 > score2)) pointer_team1->wins += 1;
    if ((previous_score1 > previous_score2) && (score1 <= score2)) pointer_team1->wins -=1;
    if ((previous_score2 <= previous_score1) && (score2 > score1)) pointer_team2->wins += 1;
    if ((previous_score2 > previous_score1) && (score2 <= score1)) pointer_team2->wins -=1;
    /* changes the score */
    pointer_game->score1 = score1;
    pointer_game->score2 = score2;
}


/* prints the teams that have the maximum number of wins between all of them */
void listWinners(team_slot *team_storage_head, int NL){

    team *pointer_team;
    team_slot *pointer_slot;
    int max_wins = -1, number_winners = 0, i = 0;  /* i is a counter for the number of names that have been allocated already */

    char **array;

    if(team_storage_head != NULL)
    {   
        /*finds the maximum number of victories and the number of teams that had that value */
        WinsAndWinners(team_storage_head, &max_wins, &number_winners);
        /*allocates memory for the array containing pointers to the names of the winners */
        array = malloc(number_winners * sizeof(char*));
        printf("%d Melhores %d\n", NL, max_wins);
        /* adds to the array a pointer to the name of every team that is a winner */
        for(pointer_slot = team_storage_head; pointer_slot != NULL; pointer_slot = pointer_slot->next){
            pointer_team = pointer_slot->pointer_team;
            if (pointer_team->wins == max_wins)
            {
                array[i] = pointer_team->name;
                ++i;
            }
        }
        /* sorts the array (of pointers to the names of the teams) alfabetically, and prints it */
        qsort(array, number_winners, sizeof(char*), compare_string);
        for (i = 0; i < number_winners; ++i)
            printf("%d * %s\n",NL, array[i]);
        /* frees the memory allocated for the array containing pointers to the names of the winners */
        free(array);
    }
}


/*finds the maximum number of victories and the number of teams that had that value */
void WinsAndWinners(team_slot *team_storage_head, int *max_wins, int *number_winners){

    team *pointer_team;
    team_slot *pointer_slot;

    for(pointer_slot = team_storage_head; pointer_slot != NULL; pointer_slot = pointer_slot->next)
    {
        pointer_team = pointer_slot->pointer_team;
        if (pointer_team->wins == *max_wins)
            *number_winners = *number_winners + 1;
        if (pointer_team->wins > *max_wins)
        {
            *max_wins = pointer_team->wins;
            *number_winners = 1;
        }
    }
}


/* compare function used for qsort */
int compare_string(const void *p1, const void *p2){

    return strcmp(*(char**) p1 , *(char**) p2);
}


/* traverses the game storage searching for a specific slot */
game_slot* findGameInStorage(game_slot *game_storage_head ,char *name){

    game_slot *pointer_slot;

    for(pointer_slot = game_storage_head; pointer_slot != NULL; pointer_slot = pointer_slot->next) 
    {
        if (strcmp(pointer_slot->name, name) == 0)
            return pointer_slot;
    }

    return NULL;
}


/* traverses the team storage searching for a specific slot */
team_slot* findTeamInStorage(team_slot *team_storage_head, team *pointer_team){

    team_slot *pointer_slot;

    for(pointer_slot = team_storage_head; pointer_slot != NULL; pointer_slot = pointer_slot->next)
    {
        if (pointer_slot->pointer_team == pointer_team)
            return pointer_slot;
    }

    return NULL;
}


/* traverses the team storage searching for the slot that comes before a specific one */
team_slot* findPreviousTeamInStorage(team_slot *team_storage_head, team *pointer_team){

    team_slot *pointer_slot;

    for(pointer_slot = team_storage_head; pointer_slot->next != NULL; pointer_slot = pointer_slot->next)
    {
        if (pointer_slot->next->pointer_team == pointer_team)
            return pointer_slot;
    }

    return NULL;
}


/* traverses a linked list searching for a specific game */
g_node* findGame(g_node *head ,char *name){

    g_node *pointer_g_node;
    game *pointer_game;

    for(pointer_g_node = head; pointer_g_node != NULL; pointer_g_node = pointer_g_node->next) 
    {
        pointer_game = pointer_g_node->pointer_game;
        if (strcmp(pointer_game->name,name) == 0)
            return pointer_g_node;
    }

    return NULL;
}


/* traverses a linked list searching for a specific team */
t_node* findTeam(t_node *head ,char *name){

    t_node *pointer_t_node;
    team *pointer_team;

    for(pointer_t_node = head; pointer_t_node != NULL; pointer_t_node = pointer_t_node->next) 
    {
        pointer_team = pointer_t_node->pointer_team;
        if (strcmp(pointer_team->name,name) == 0)
            return pointer_t_node;
    }

    return NULL;
}


/* traverses a linked list searching for the game that comes before a specific one */
g_node* findPreviousGame(g_node *head , char *name){

    g_node *previous_pointer;

    for(previous_pointer = head; previous_pointer->next != NULL; previous_pointer = previous_pointer->next) 
    {
        if (strcmp(previous_pointer->next->pointer_game->name, name) == 0)
            return previous_pointer;
    }

    return NULL;
}


/* traverses a linked list searching for the team that comes before a specific one */
t_node* findPreviousTeam(t_node *head , char *name){

    t_node *previous_pointer;

    for(previous_pointer = head; previous_pointer->next != NULL; previous_pointer = previous_pointer->next) 
    {
        if (strcmp(previous_pointer->next->pointer_team->name, name) == 0)
            return previous_pointer;
    }

    return NULL;
}


/* prints all the existing games, in the same order that they were inserted in */
void listGames(g_node **games, game_slot *game_storage_head, int NL){

    game_slot *pointer_slot, *aux_last;
    g_node *head, *pointer_g_node;
    game *pointer_game;
    char *name;
    int key;

    if (game_storage_head != NULL)
    {   
        /* goes through the storage until the last element */
        for(aux_last = game_storage_head; aux_last->next != NULL; aux_last = aux_last->next);
        /* goes backwards from the last element (firstly inserted) to the first one (lastly inserted) */    
        for(pointer_slot = aux_last; pointer_slot != NULL; pointer_slot = pointer_slot->previous){
            name = pointer_slot->name;
            key = hash(name, HASH_GAMES_SIZE);
            head = games[key];
            pointer_g_node = findGame(head, name);
            pointer_game = pointer_g_node->pointer_game;
            printf("%d %s %s %s %d %d\n", NL, pointer_game->name, pointer_game->team1, pointer_game->team2,
                   pointer_game->score1, pointer_game->score2);
        }
    }
}


