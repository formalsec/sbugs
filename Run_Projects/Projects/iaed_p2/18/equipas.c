#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipas.h"
#include "constants.h"

Team createTeam(char *name){
  Team newTeam;
  int len, i = 0;
  /*name = format(name);*/
  len = strlen(name);
  newTeam.name = malloc(len + 1 * sizeof(char));
  if(!newTeam.name){
    perror("createTeam Failed malloc");
  }
  while (name[i] != '\0' && i < len) {
    newTeam.name[i] = name[i];
    i++;
  }
  newTeam.name[i] = '\0';
  /*strcpy(newTeam.name, name);*/
  newTeam.victories = 0;
  return newTeam;
}

int isTeam(char *name, Team team){
  int len, len2, i;
  len = strlen(name);
  len2 = strlen(team.name);
  if(len == len2){
    for(i = 0; i < len; i++){
      if(name[i] != team.name[i]){
        return 0;
      }
    }
    return 1;
  }
  return 0;
}

void addVictory(Teams *teamsList, char *team){
  while (teamsList->nextTeam != NULL) {
    if(isTeam(team, teamsList->team)){
      break;
    }
    teamsList = teamsList->nextTeam;
  }
  teamsList->team.victories++;
}

void removeVictory(Teams *teamsList, char *team){
  while (teamsList->nextTeam != NULL) {
    if(isTeam(team, teamsList->team)){
      break;
    }
    teamsList = teamsList->nextTeam;
  }
  teamsList->team.victories--;
}

Teams *createTeams(char *name){
  Teams *new;
  new = malloc(sizeof(Teams));
  if(!new){
    perror("createTeams Failed malloc");
  }
  new->team = createTeam(name);
  new->nextTeam = NULL;
  return new;
}

int addTeam(char *name, Teams *teamsList){
  Team test;
  /*name = format(name);*/
  test = searchTeam(teamsList, name);
  if(isTeam(FALSE_TEAM, test) == 1){
    while(teamsList->nextTeam != NULL){
      teamsList = teamsList->nextTeam;
    }
    teamsList->nextTeam = createTeams(name);
    freeTeam(test);
    return 1;
  }
  return 0;
}

Team searchTeam(Teams *teamsList, char* name){
  if(teamsList == NULL){
    return createTeam(FALSE_TEAM);
  }
  while(teamsList->nextTeam != NULL){
    if(isTeam(name, teamsList->team) == 1){
      return teamsList->team;
    }
    teamsList = teamsList->nextTeam;
  }
  if(isTeam(name, teamsList->team) == 1){
    return teamsList->team;
  }
  return createTeam(FALSE_TEAM);
}

void freeTeams(Teams *teamsList){
  if(teamsList != NULL){
    Teams *next;
    while (teamsList->nextTeam != NULL) {
      next = teamsList->nextTeam;
      teamsList->nextTeam = next->nextTeam;
      freeTeam(next->team);
      free(next);
    }
    freeTeam(teamsList->team);
    free(teamsList);
  }
}

void printTeam(Teams *teamsList, char *name, int commandNumber){
  Team team;
  if(teamsList != NULL){
    /*name = format(name);*/
    team = searchTeam(teamsList, name);
    if(isTeam(FALSE_TEAM, team) == 0){
      fprintf(outputFile, "%d %s %d\n", commandNumber, name, team.victories);
    }
    else{
      freeTeam(team);
      fprintf(outputFile, "%d Equipa inexistente.\n", commandNumber);
    }
  }
  else{
    fprintf(outputFile, "%d Equipa inexistente.\n", commandNumber);
  }
}

int nameComp(char *c1, char *c2){
  int lenght, i;
  if(strcmp(c1, c2) < 0){
    lenght = strlen(c1);
  }
  else{
    lenght = strlen(c2);
  }
  for(i = 0; i < lenght; i++){
    if(c1[i] < c2[i]){
      return -1;
    }
    else if(c1[i] > c2[i]){
      return 1;
    }
  }
  return 0;
}

void sort(char **list, int size){
  int i, j , temp;
  char string[MAX_STRING_SIZE];
  for(i = 0; i < size - 1; i++){
    temp = i;
    for(j = i + 1; j <= size -1; j++){
      if(nameComp(list[j], list[temp]) == -1){
        temp = j;
      }
    }
    strcpy(string, list[i]);
    strcpy(list[i], list[temp]);
    strcpy(list[temp], string);
  }
}

void printBest(Teams *teamsList, int commandNumber){
  int max = 0, num = 0, i = 0, j;
  char **list;
  Teams *move;
  if(teamsList != NULL){
    move = teamsList;
    while (move->nextTeam != NULL) {
      if(move->team.victories > max){
        max = move->team.victories;
        num = 0;
      }
      else if(move->team.victories == max){
        num++;
      }
      move = move->nextTeam;
    }
    if(move->team.victories > max){
      max = move->team.victories;
    }
    else if(move->team.victories == max){
      num++;
    }
    list = malloc(num * sizeof(char*));
    while(teamsList->nextTeam != NULL){
      if(teamsList->team.victories == max){
        list[i] = malloc(MAX_STRING_SIZE * sizeof(char));
        strcpy(list[i], teamsList->team.name);
        i++;
      }
      teamsList = teamsList->nextTeam;
    }
    if(teamsList->team.victories == max){
      list[i] = malloc(MAX_STRING_SIZE * sizeof(char));
      strcpy(list[i], teamsList->team.name);
      i++;
    }
  }
  sort(list, i);
  fprintf(outputFile, "%d Melhores %d\n", commandNumber, max);
  for(j = 0; j < i; j++){
    fprintf(outputFile, "%d * %s\n", commandNumber, list[j]);
    free(list[j]);
  }
  free(list);
}

void freeTeam(Team team){
  free(team.name);
}
