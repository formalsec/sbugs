#include "team.h"
#include "game.h"
#include "hashTable.h"
#include "messages.h"
#include <stdio.h>
#include <string.h>

/*The universal Hash Table Size*/
#define HASH_TABLE_LENGTH 10000

/*
 * Check if the team exists by searching in the Hash Table using the function 'hashTableSearch'.
 * Requires: char Array with the name and the Teams Hash Table.
 * Returns: 0 if the team doesn't exists 1 otherwise.
 */
int teamExists(char *name, HashTable *teamsHashTable) {
    link *link = hashTableSearch(teamsHashTable, name, compareTeamFunction);
    if (link == NULL) {
        return 0;
    }
    return 1;
}

/*
 * Check if the game exists by searching in the Hash Table using the function 'hashTableSearch'.
 * Requires: char Array with the name and the Games Hash Table.
 * Returns: 0 if the game doesn't exists 1 otherwise.
 */
int gameExists(char *name, HashTable *gameHashMap) {
    link *link = hashTableSearch(gameHashMap, name, compareTeamFunction);
    if (link == NULL) {
        return 0;
    }
    return 1;
}

/*
 * Updates the Victories of the a team depending on the scores.
 * Requires: int Array with scores, Teams Array and a int with the value to update
 */
void newVictories(int *scores, Team **teams, int scoreToUpdate) {
    if (scores[0] > scores[1]) {
        updateVictories(teams[0], scoreToUpdate);
    } else if (scores[0] < scores[1]) {
        updateVictories(teams[1], scoreToUpdate);
    }
}

/*
 * Checks the conditions to create a new game.
 * Requires: char array with game's name, char array with team1's name, char array with team2's name,
 * the games Hash Table, the Teams Hash Table.
 * Returns: 1 if the game all ready exists or 2 if one of the teams doesn't exists.
 */
int canCreateGame(char *name, char *team1, char *team2, HashTable *gamesHashTable, HashTable *teamsHashTable) {
    if (gameExists(name, gamesHashTable) == 1) {
        return 1;
    }

    if (teamExists(team1, teamsHashTable) == 0 || teamExists(team2, teamsHashTable) == 0) {
        return 2;
    }
    return 0;
}

/*
 * Auxiliary function to execute 'a' command.
 * Checks if its possible to create a new game with the 'canCreateGame' function.
 * If possible creates the game and inserts in games Hash Table.
 * Requires: char array with game's name, char array with team1's name, char array with team2's name,
 * int array with the scores, the games Hash Table, the Teams Hash Table and the Order List.
 * Return 1 if the game all ready exists, 2 if one of the teams doesn't exists otherwise returns 0.
 */
int createNewGame(char *name, char *team1, char *team2, int *scores, HashTable *gamesHashTable,
                  HashTable *teamsHashTable, List *orderList) {
    Team *teams[2];
    Game *game;
    link *link;
    int value = canCreateGame(name, team1, team2, gamesHashTable, teamsHashTable);
    if (value == 1 || value == 2) {
        return value;
    }

    link = hashTableSearch(teamsHashTable, team1, compareTeamFunction);
    teams[0] = link->dataPointer;

    link = hashTableSearch(teamsHashTable, team2, compareTeamFunction);
    teams[1] = link->dataPointer;

    game = createGame(name, teams, scores);
    hashTableInsert(gamesHashTable, name, game);
    listInsertEnd(orderList, game);
    newVictories(scores, game->teams, 1);
    return 0;
}

/*
 * Reads the game's name, teams and scores.
 * Calls the function 'createNewGame' with the given information.
 * If there is any errors it prints the correspondent messages.
 * Requires: the Games Hash Table, the Teams HashTable, the Order List and a int pointer to the command counter.
 */
void execute_a(HashTable *gamesHashTable, HashTable *teamsHashTable, List *orderList, int *cmdCounter) {
    char gameName[1023];
    char team1[1023];
    char team2[1023];
    int scores[2];
    int value;
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", gameName, team1, team2, &scores[0], &scores[1]);

    value = createNewGame(gameName, team1, team2, scores, gamesHashTable, teamsHashTable, orderList);
    if (value == 1) {
        printf(GAME_EXISTS_ERROR, *cmdCounter);
    } else if (value == 2) {
        printf(TEAM_NOT_FOUND_ERROR, *cmdCounter);
    }
}

/*
 * Prints the games by the insertion order using the 'listPrint' function.
 * Requires: the Order List and a int pointer to the command counter.
 */
void execute_l(List *orderList, int *cmdCounter) {
    listPrint(orderList, cmdCounter, printGame);
}

/*
 * Searches for a game with the given name.
 * If the game doesn't exists it prints an error otherwise prints the game's information.
 * Requires: the games Hash Table and a int pointer to the command counter.
 */
void execute_p(HashTable *gamesHashTable, int *cmdCounter) {
    char gameName[1023];
    link *link;
    scanf(" %[^:\n]", gameName);
    link = hashTableSearch(gamesHashTable, gameName, compareGameFunction);
    if (link != NULL) {
        printGame(link->dataPointer, cmdCounter);
    } else {
        printf(GAME_NOT_FOUND_ERROR, *cmdCounter);
    }
}

/*
 * Checks if the game exists and deletes it using the needed functions.
 * Requires: a char array with the game's name, the games Hash Table and the Order List.
 * Returns: 0 if the game doesn't exist 1 otherwise.
 */
int delGame(char *name, HashTable *gamesHashTable, List *orderList) {
    link *link;
    if (gameExists(name, gamesHashTable) == 0) {
        return 0;
    }

    link = hashTableSearch(gamesHashTable, name, compareGameFunction);
    newVictories(((Game *) link->dataPointer)->scores, ((Game *) link->dataPointer)->teams, -1);
    listRemoveElement(orderList, name, compareGameFunction, NULL);
    hashTableRemove(gamesHashTable, name, compareGameFunction, deleteGame);
    return 1;
}

/*
 * Reads the game's name from stdin. Uses the 'delGame' function to delete the game.
 * Prints and error if the game doesn't exist.
 * Requires: the games Hash Table, the Order List and a int pointer for command counter.
 */
void execute_r(HashTable *gamesHashTable, List *orderList, int *cmdCounter) {
    char gameName[1023];
    scanf(" %[^:\n]", gameName);
    if (delGame(gameName, gamesHashTable, orderList) == 0) {
        printf(GAME_NOT_FOUND_ERROR, *cmdCounter);
    }
}

/*
 * Changes the victories of the game's teams by the new scores.
 * Requires: the int array for the newScores and the Game pointer.
 */
void evaluateScores(int *newScores, Game *game) {
    if (newScores[0] == newScores[1]) {
        if (game->scores[0] > game->scores[1]) {
            updateVictories(game->teams[0], -1);
        } else if (game->scores[0] < game->scores[1]) {
            updateVictories(game->teams[1], -1);
        }
    } else if (game->scores[0] > game->scores[1] && newScores[0] < newScores[1]) {
        updateVictories(game->teams[0], -1);
        updateVictories(game->teams[1], 1);
    } else if (game->scores[0] < game->scores[1] && newScores[0] > newScores[1]) {
        updateVictories(game->teams[1], -1);
        updateVictories(game->teams[0], 1);
    } else if (game->scores[0] == game->scores[1]) {
        if (newScores[0] > newScores[1]) {
            updateVictories(game->teams[0], 1);
        } else if (newScores[0] < newScores[1]) {
            updateVictories(game->teams[1], 1);
        }
    }
}

/*
 * Finds the game if it exists and changes the game's scores with the new one.
 * Requires: a char array with the game's name, an int array with the new scores and the games Hash Table.
 * Return: 0 if the game doesn't exists 1 otherwise.
 */
int changeGameScores(char *name, int *newScores, HashTable *gamesHashTable) {
    link *gameLink;
    Game *game;
    if (gameExists(name, gamesHashTable) == 0) {
        return 0;
    }
    gameLink = hashTableSearch(gamesHashTable, name, compareGameFunction);
    game = gameLink->dataPointer;

    evaluateScores(newScores, game);

    game->scores[0] = newScores[0];
    game->scores[1] = newScores[1];
    return 1;
}

/*
 * Reads the game name and the new scores. Uses the 'changeGameScores' function.
 * Prints and error if the game doesn't exist.
 * Requires: the game Hash Table and a int pointer to the command counter.
 */
void execute_s(HashTable *gamesHashTable, int *cmdCounter) {
    char gameName[1023];
    int scores[2];
    scanf(" %[^:\n]:%d:%d", gameName, &scores[0], &scores[1]);
    if (changeGameScores(gameName, scores, gamesHashTable) == 0) {
        printf(GAME_NOT_FOUND_ERROR, *cmdCounter);
    }
}

/*
 * First checks if there is no team with that name by using the 'teamExists' function.
 * If not, create the new team and inserts it in the teams Hash Table using the appropriated functions.
 * Requires: a char array with the team name and the teams Hash Table.
 * Returns: 0 if there is a team with that name 1 otherwise.
 */
int createNewTeam(char *name, HashTable *teamsHashTable) {
    Team *team;
    if (teamExists(name, teamsHashTable) == 1) {
        return 0;
    }
    team = createTeam(name);
    hashTableInsert(teamsHashTable, name, team);
    return 1;
}

/*
 * Reads the team name from stdin and calls the function 'createNewTeam'.
 * If the team already exists then prints and error.
 * Requires: the team Hash Table and a int pointer for the command counter.
 */
void execute_A(HashTable *teamsHashTable, int *cmdCounter) {
    char name[1023];
    scanf(" %[^:\n]", name);
    if (createNewTeam(name, teamsHashTable) == 0) {
        printf(TEAM_EXISTS_ERROR, *cmdCounter);
    }
}

/*
 * Reads the team name from stdin and prints its information, prints an error if the team doesn't exists.
 * Requires: the teams Hash Table and the command counter pointer.
 */
void execute_P(HashTable *teamsHashTable, int *cmdCounter) {
    char name[1023];
    link *link;
    scanf(" %[^:\n]", name);
    link = hashTableSearch(teamsHashTable, name, compareTeamFunction);
    if (link != NULL) {
        printTeam(link->dataPointer, cmdCounter);
    } else {
        printf(TEAM_NOT_FOUND_ERROR, *cmdCounter);
    }
}

/*
 * Creates the best teams list by finding which teams have the most victories and inserting in a new list
 * by alphabetic order.
 * Requires: The teams Hash Table and a int pointer for the most victories.
 * Returns: the created list.
 */
List *createBestTeamsList(HashTable *teamsHashTable, int *mostVictories) {
    link *listNode;
    link *node;
    List *list = creatList();
    int i;
    for (i = 0; i < teamsHashTable->buckets; i++) {
        for (node = teamsHashTable->lists[i]->head; node != NULL; node = node->next) {
            if (((Team *) node->dataPointer)->victories == *mostVictories) {
                if (isListEmpty(list)) {
                    listInsertEnd(list, node->dataPointer);
                    continue;
                }
                for (listNode = list->head; listNode != NULL; listNode = listNode->next) {
                    if (strcmp(((Team *) node->dataPointer)->name, ((Team *) listNode->dataPointer)->name) < 0) {
                        listInsertBefore(list, listNode, node->dataPointer);
                        break;
                    } else if (listNode == list->tail) {
                        listInsertEnd(list, node->dataPointer);
                        break;
                    }
                }
            }
        }
    }
    return list;
}

/*
 * Function used to find the biggest games won by any team.
 * Requires: the teams Hash Table and a int pointer for the games won.
 * Returns: the result of the createBestTeamsList which is a List.
 */
List *buildListByGames(HashTable *teamsHashTable, int *victories) {
    int i;
    link *node;
    int mostVictories = 0;
    for (i = 0; i < teamsHashTable->buckets; i++) {
        for (node = teamsHashTable->lists[i]->head; node != NULL; node = node->next) {
            if (mostVictories < ((Team *) node->dataPointer)->victories) {
                mostVictories = ((Team *) node->dataPointer)->victories;
            }
        }
    }

    *victories = mostVictories;

    return createBestTeamsList(teamsHashTable, &mostVictories);
}

/*
 * Function used to print the teams with the most victories.
 * Uses an auxiliary function to create the best Teams list.
 * After that prints it.
 * Requires: the teams Hash Table and the command counter.
 */
void execute_g(HashTable *teamsHashTable, int *counter) {
    int victories = 0;
    List *teams = buildListByGames(teamsHashTable, &victories);
    if (isListEmpty(teams) == 0) {
        printf(BEAST_TEAMS_MESSAGE_HEADER, *counter, victories);
        listPrint(teams, counter, bestTeamsFunction);
    }
    deleteList(teams, NULL);
}

/*
 * A switch case function that will determine which command was inserted by the user.
 * Requires: the command's char for identification, the game and teams Hash Tables, the orders List
 * and the command counter.
 * Returns: 1 if the programs will continue after this function 0 otherwise.
 */
int readCommands(char command, HashTable *gamesHashTable, HashTable *teamsHashTable, List *orderList, int *counter) {
    switch (command) {
        case 'a':
            execute_a(gamesHashTable, teamsHashTable, orderList, counter);
            break;
        case 'l' :
            execute_l(orderList, counter);
            break;
        case 'p':
            execute_p(gamesHashTable, counter);
            break;
        case 'r':
            execute_r(gamesHashTable, orderList, counter);
            break;
        case 's':
            execute_s(gamesHashTable, counter);
            break;
        case 'A':
            execute_A(teamsHashTable, counter);
            break;
        case 'P':
            execute_P(teamsHashTable, counter);
            break;
        case 'g':
            execute_g(teamsHashTable, counter);
            break;
        case 'x':
            return 0;
        default:
            break;
    }
    return 1;
}

/* Program's main function. Creates both Hash Tables and the order list.
 * After that reads all the user inputs from stdin.
 * finally does the final memory clean up right before the program end.
 */
int main() {
    int running = 1;
    int counter = 10;
    char command;
    HashTable *teamsHashTable = createHashTable(HASH_TABLE_LENGTH);
    HashTable *gamesHashTable = createHashTable(HASH_TABLE_LENGTH);
    List *orderList = creatList();

    for (counter = 1; running == 1; counter++) {
        scanf(" %c", &command);
        running = readCommands(command, gamesHashTable, teamsHashTable, orderList, &counter);
    }

    deleteHashTable(teamsHashTable, deleteTeam);
    deleteHashTable(gamesHashTable, deleteGame);
    deleteList(orderList, NULL);

    return 0;
}
