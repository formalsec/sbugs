#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "games.h"
#include "list.h"
#include "hash.h"

#define MAX_CHAR 1024 /* Longest possible Team/Game name */

/* Reads Team/Game name from stdin and allocates enough memory to store it
 * Returns pointer to string allocated
*/
char *readName() {
    char *str;
    char buffer[MAX_CHAR];
    
    getchar();

    scanf("%[^:\n]", buffer);

    str = (char *) malloc(sizeof(char) *(strlen(buffer) + 1));

    strcpy(str, buffer);

    return str;
}

/* Clears hash map and linked list
 * Frees all allocated memory
*/
void clean() {
    hashClean();
    cleanList();
}

/* Returns pointer to Game name
*/
char *getName(Game *game) { 
    return game->name;
}

/* Frees Game structure including string allocated in readName function
*/
void freeGame(void *item) {
    Game *game = (Game *) item;
    free(game->name);
    free(game);
}

/* Frees Team structure including string allocated in readName function
*/
void freeTeam(void *item) {
    Team *team = (Team *) item;
    free(team->name);
    free(team);
}


/* Adds Game to hash map and linked list if a Game with the same name does not exist 
*/
void addGame(int lineNumber) {
    int c;
    char *name, *home, *away;
    unsigned int h, a;
    Game *game = (Game *) malloc(sizeof(Game));
    Team *homeT, *awayT;

    name = readName();
    
    /* If Game already exists */
    if(searchGameHash(name) != NULL){
        free(name);
        free(game);
        printf("%d Jogo existente.\n", lineNumber);
        /*Clear stdin*/
        while((c = getchar()) != '\n' && c!=EOF); 
        return;
    }

    home = readName();

    homeT = searchTeamHash(home);
    free(home);

    /* If Team doesn't exist */
    if(homeT == NULL){
        free(name);
        free(game);
        printf("%d Equipa inexistente.\n", lineNumber);
        /*Clear stdin*/
        while((c = getchar()) != '\n' && c!=EOF);
        return;
    }


    away = readName();

    awayT = searchTeamHash(away);
    free(away);

    /* If Team doesn't exist */
    if(awayT == NULL){
        free(name);
        free(game);
        printf("%d Equipa inexistente.\n", lineNumber);
        /*Clear stdin*/
        while((c = getchar()) != '\n' && c!=EOF);
        return;
    }

    
    scanf(":%u:%u", &h, &a);
    

    game->name = name;
    game->home = homeT;
    game->away = awayT;
    game->homeScore = h;
    game->awayScore = a;

    if(h > a)
        homeT->wins++;
    
    else if(a > h)
        awayT->wins++;
    
    /* If all conditions are met insert Game in structures */
    add(game);
}

/* Calls list function in charge of printing all Games chronologically
*/
void listGames(int lineNumber) {
    printList(lineNumber);
}

/* Search Game in hash map
*/
void searchGame(int lineNumber) {
    Game *game;
    char *name;

    name = readName();

    game = searchGameHash(name);
    free(name);
    
    if(game == NULL){
        printf("%d Jogo inexistente.\n", lineNumber);
        return;
    }

    printGame(lineNumber, game);
}

/* Remove Game from hash map and linked list
*/
void deleteGame(int lineNumber) {
    Game *game;
    char *name;

    /* Get name of Game we wish to remove from stdin */
    name = readName();

    game = (Game *) hashRemove(name);

    if(game == NULL) {
        free(name);
        printf("%d Jogo inexistente.\n", lineNumber);
        return;
    }

    /* Deleting Game has an impact on the wins of the Teams that participated in the match 
     * Decrement wins from the Team with the highest score
    */
    if(game->homeScore > game->awayScore) game->home->wins--;
    else if(game->awayScore > game->homeScore) game->away->wins--;

    listRemove(name);
    free(name);

    freeGame((void *) game);
}

/* Change the score of a Game with the specified name
*/
void changeScore(int lineNumber) {
    char *name;
    unsigned int homeS, awayS;
    Game *game;

    name = readName();
    scanf(":%u:%u", &homeS, &awayS);

    game = searchGameHash(name);
    free(name);
    
    if(game == NULL) {
        printf("%d Jogo inexistente.\n", lineNumber);
        return;
    }

    /* Decrement wins from the Team with previously the highest score
    */
    if(game->homeScore > game->awayScore) game->home->wins--;
    else if(game->awayScore > game->homeScore) game->away->wins--;

    game->homeScore = homeS;
    game->awayScore = awayS;

    /* Increment wins from the Team with the new highest score
    */
    if(game->homeScore > game->awayScore) game->home->wins++;
    else if(game->awayScore > game->homeScore) game->away->wins++;
}

/* Adds Team to hash map if a Team with the same name does not exist 
*/
void addTeam(int lineNumber) {
    char *name;
    Team *team;

    name = readName();

    team = searchTeamHash(name);

    /* If a Team with said name exists */
    if(team != NULL){
        printf("%d Equipa existente.\n", lineNumber);
        free(name);
        return;
    }

    team = (Team *) malloc(sizeof(Team));

    team->wins = 0;
    team->name = name;

    hashInsertTeam(team);
}

/* Search Team in hash map
*/
void searchTeam(int lineNumber) {
    char *name;
    Team *team;

    name = readName();

    team = searchTeamHash(name);

    /* If Team does not exist */
    if(team == NULL) {
        printf("%d Equipa inexistente.\n", lineNumber);
        free(name);
        return;
    }

    printf("%d %s %u\n",lineNumber, team->name, team->wins);
    free(name);
}

/* Print a given Game
*/
void printGame(int lineNumber, Game *game) {
    printf("%d %s %s %s %u %u\n", 
        lineNumber, game->name, game->home->name, game->away->name,
            game->homeScore, game->awayScore);
}

 /* Print all Teams with the highest amount of wins
 */
void mostSuccessfulTeams(int lineNumber) {
    char **list, **aux;
    int length;
    unsigned int wins;

    list = getBestTeams(&length, &wins);
    if(length > 0) {
        printf("%d Melhores %u\n", lineNumber, wins);
        /* Auxiliary array used in mergesort */
        aux = (char **) malloc(sizeof(char *) * length);
        /* Sort list alphabetically */
        mergeSort(list, aux,  0, length - 1);
        free(aux);
        printNames(list, length, lineNumber);
    }
    free(list);
}

/* Print array of Strings
*/
void printNames(char **arr, int len, int lineNumber) {
    int i;

    for(i = 0; i < len; i++) {
        printf("%d * %s\n", lineNumber, arr[i]);
    }
}

/* Sorts array arr in lexicographic order
*/
void mergeSort(char **arr, char **aux, int l, int r) {
    int m;


    if(l < r) {
        m = (r + l) / 2;

        mergeSort(arr, aux, l, m);
        mergeSort(arr, aux, m + 1, r);

        merge(arr, aux, l, m, r);
    }
}

/* Merge two subarrays of arr in alphabetical order
 * First subarray is from position left to position m
 * Second subarray is from position m+1 to position right
*/
void merge(char **arr, char **aux, int left, int m, int right) {
    int i, j, k; 
    
    for(i = m + 1; i > left; i--) 
        aux[i - 1] = arr[i - 1];

    for(j = m; j < right; j++) 
        aux[right + m - j] = arr[j + 1];

    for(k = left; k <= right; k++) {
        if(lower(aux[j], aux[i]) || i > m)
            arr[k] = aux[j--];
        else
            arr[k] = aux[i++];
    }
}

/* Returns 0 if product a preceeds product b lexicographically, otherwise returns "true"
*/
int lower(const char *a, const char *b) {
    int i = 0, j = 0;
    while (a[i] != '\0' && b[j] != '\0') {
        /* Ignore spaces */
        if(a[i] == ' ') i++;
        if(b[j] == ' ') j++;

        if(a[i] == b[j]){
            i++;
            j++;
        }
        else {
            return a[i] < b[j];
        }
    }
    return 0;
}

/* Return amount of wins of a given Team
*/
int amountOfWins(void *team) {
    return ((Team *) team)->wins;
}

/* Returns pointer to name of a given Team
*/
char *nameOfTeam(void *team){
    return ((Team *) team)->name;
}