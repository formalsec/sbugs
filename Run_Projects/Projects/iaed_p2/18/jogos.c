#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "jogos.h"

char **separate(char *string, int separator){
  int i, j, x, len;
  char **temp;
  temp = malloc(separator*sizeof(char *));
  if(!temp){
    perror("separate Failed malloc");
  }
  for(j = 0; j < separator; j++){
    temp[j] = malloc(MAX_STRING_SIZE * sizeof(char));
    if(!temp[j]){
      perror("separate Failed malloc");
    }
  }
  j = 0;
  len = strlen(string);
  for(i = 0; i < separator; i++){
    x = 0;
    while (string[j] != ':' && string[j] != '\0' && j < len && string[j] != '\n') {
      temp[i][x] = string[j];
      j++;
      x++;
    }
    temp[i][x] = '\0';
    j++;
  }
  return temp;
}

int test(char *n1, char*n2){
  int comp = 0, i;
  int len = strlen(n1);
  for(i = 0; i < len; i++){
    if(n1[i] == n2[i]){
      comp++;
    }
  }
  if(comp == len){
    return 1;
  }
  return 0;
}

int isGame(Game *game, char *name){
  if(game == NULL){
    return 0;
  }
  while (game->nextGame != NULL) {
    if(strcmp(game->name, name) == 0 && test(name, game->name) == 1){
      return 1;
    }
    game = game->nextGame;
  }
  if(strcmp(game->name, name) == 0 && test(name, game->name) == 1){
    return 1;
  }
  return 0;
}


Game *createGame(char* gameName, Team team1, Team team2, int scoreTeam1, int scoreTeam2){
  int len;
  Game *newGame = malloc(sizeof(Game));
  len = strlen(gameName);
  newGame->name = malloc((len + 1) *sizeof(char));
  newGame->teams = malloc(2*sizeof(Team));
  newGame->teamsScores = malloc(2*sizeof(int));
  if(!newGame || !newGame->name || !newGame->teams || !newGame->teamsScores){
    perror("createGame Failed malloc");
  }
  strcpy(newGame->name, gameName);
  newGame->teams[0] = team1;
  newGame->teams[1] = team2;
  newGame->teamsScores[0] = scoreTeam1;
  newGame->teamsScores[1] = scoreTeam2;
  newGame->nextGame = NULL;
  return newGame;
}

int addGame(Game *game, char* gameName, Team team1, Team team2, int scoreTeam1, int scoreTeam2){
  Game *new;
  if(isGame(game, gameName) == 1){
    return 0;
  }
  while (game->nextGame != NULL) {
    game = game->nextGame;
  }
  new = createGame(gameName, team1, team2, scoreTeam1, scoreTeam2);
  game->nextGame = new;
  return 1;
}

void prepareGame(Game **gameList, Teams *teamsList, char* string, int commandNumber){
  int i, test = 1;
  Team t1, t2;
  char **temp = separate(string, 5);
  t1 = searchTeam(teamsList, temp[1]);
  t2 = searchTeam(teamsList, temp[2]);
  if(isGame(*gameList, temp[0]) == 1){
    fprintf(outputFile ,"%d Jogo existente.\n", commandNumber);
    test = 0;
  }
  else if(isTeam(FALSE_TEAM, t1) == 1 || isTeam(FALSE_TEAM, t2) == 1){
    fprintf(outputFile ,"%d Equipa inexistente.\n", commandNumber);
    test = 0;
  }
  else if(*gameList == NULL){
    *gameList = createGame(temp[0], t1, t2, atoi(temp[3]), atoi(temp[4]));
  }
  else{
    addGame(*gameList, temp[0], t1, t2, atoi(temp[3]), atoi(temp[4]));
  }
  if(test == 1){
    if(atoi(temp[3]) > atoi(temp[4])){
      addVictory(teamsList, temp[1]);
    }
    else if (atoi(temp[3]) < atoi(temp[4])){
      addVictory(teamsList, temp[2]);
    }
  }

  for(i = 0; i < 5; i++){
    free(temp[i]);
  }
  free(temp);
  if(isTeam(FALSE_TEAM, t1) == 1){
    freeTeam(t1);
  }
  if(isTeam(FALSE_TEAM, t2) == 1){
    freeTeam(t2);
  }
}

void changeScore(Game *game, Teams *teamsList, char *string, int commandNumber){
  int i;
  char **temp = separate(string ,3);
  if(isGame(game, temp[0]) == 1){
    while(game->nextGame != NULL){
      if(test(game->name, temp[0]) == 1){
        break;
      }
      game = game->nextGame;
    }
    if(game->teamsScores[0] < game->teamsScores[1] && atoi(temp[1]) > atoi(temp[2])){
      removeVictory(teamsList ,game->teams[0].name);
      addVictory(teamsList ,game->teams[1].name);
    }
    else if(game->teamsScores[0] > game->teamsScores[1] && atoi(temp[1]) < atoi(temp[2])){
      removeVictory(teamsList ,game->teams[1].name);
      addVictory(teamsList ,game->teams[0].name);
    }
    game->teamsScores[0] = atoi(temp[1]);
    game->teamsScores[1] = atoi(temp[2]);
  }
  else{
    fprintf(outputFile, "%d Jogo inexistente.\n", commandNumber);
  }
  for(i = 0; i < 3; i++){
    free(temp[i]);
  }
  free(temp);
}


Game *removeGame(Game *game, Teams *teamsList, char *gameName, int commandNumber){
  Game *temp, *move;
  int comp = 0;
  move = game;
  if(isGame(move, gameName) == 1){
    while (move->nextGame != NULL) {
      if(test(move->name, gameName) == 1){
        break;
      }
      temp = move;
      move = move->nextGame;
      comp ++;
    }

    if(move->teamsScores[0] < move->teamsScores[1]){
      removeVictory(teamsList, move->teams[1].name);
    }
    else if (move->teamsScores[0] > move->teamsScores[1]){
      removeVictory(teamsList, move->teams[0].name);
    }

    if(comp == 0){
      temp = game->nextGame;
      freeGame(game);
      return temp;
    }
    else if(move->nextGame == NULL){
      temp->nextGame = NULL;
      freeGame(move);
    }
    else{
      temp->nextGame = move->nextGame;
      freeGame(move);
    }
  }
  else{
    fprintf(outputFile, "%d Jogo inexistente.\n", commandNumber);
  }
  return game;
}

void printGame(Game *game, int commandNumber){
  fprintf(outputFile ,"%d ", commandNumber);
  fprintf(outputFile ,"%s ", game->name);
  fprintf(outputFile ,"%s ", game->teams[0].name);
  fprintf(outputFile ,"%s ", game->teams[1].name);
  fprintf(outputFile ,"%d ", game->teamsScores[0]);
  fprintf(outputFile ,"%d\n", game->teamsScores[1]);
}

void searchGame(Game *game, char *gameName, int commandNumber){
  int len;
  char *name;
  len = strlen(gameName);
  name = malloc(len + 1 * sizeof(char));
  strncpy(name, gameName, len);
  name[len] = '\0';
  if(isGame(game, name) == 1){
    while(game->nextGame != NULL){
      if(test(game->name, name) == 1){
        break;
      }
      game = game->nextGame;
    }
    printGame(game, commandNumber);
  }
  else{
    fprintf(outputFile, "%d Jogo inexistente.\n", commandNumber);
  }
  free (name);
}

void printGames(Game *game, int commandNumber){
  if(game != NULL){
    while (game->nextGame != NULL) {
      printGame(game, commandNumber);
      game = game->nextGame;
    }
    printGame(game, commandNumber);
  }
}

void freeGame(Game *game){
  free(game->name);
  free(game->teams);
  free(game->teamsScores);
  free(game);
}
