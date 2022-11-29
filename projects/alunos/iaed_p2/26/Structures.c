#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structures.h"

/*This is my hash_function*/
unsigned int hash (char* name, int size) {
  unsigned long int value = 0;
  unsigned int i = 0;
  unsigned int name_len = strlen(name);
  for (; i < name_len; ++i) {
      value = value * 37 + name[i];
  }
  value = value % size;
  return value;
}

/*this function initializes my teams_hash_table with NULL in the name and 0 in the games_won*/
void teams_initialize (team* hash_table, int size) {
  int i = 0;
  for (; i < size; i++) {
    hash_table[i].name = NULL;
    hash_table[i].games_won = 0;
  }
}

/*This function adds a team to my teams_hash_table, recognizes the errors associated with teams*/
void create_team (char *name, team *hash_table, int size, int counter, int *teams_number, int max_games_won, int *teams_with_max_games_won) {
  int key = hash(name,size);
  int name_size = strlen(name)+1;
  int i;
  if (hash_table[key].name == NULL) { /*The slot is empty*/
    hash_table[key].name = can_fail_malloc(sizeof(char)*name_size);
    strcpy(hash_table[key].name,name);
    (*teams_number)++;
    if (max_games_won == 0) {
      (*teams_with_max_games_won)++;
    }
  }
  else {
    if (strcmp(hash_table[key].name,name) == 0) { /*The team already exists*/
      printf("%d Equipa existente.\n",counter);
    }
    else { /*Find the first empty slot - linear probing*/
      for (i = key+1; i < size; i++) {
        if (hash_table[i].name != NULL && strcmp(hash_table[i].name,name) == 0) { /*The team already exists*/
          printf("%d Equipa existente.\n",counter);
          break;
        }
        else if (hash_table[i].name == NULL) {
          hash_table[i].name = can_fail_malloc(sizeof(char)*name_size);
          strcpy(hash_table[i].name,name);
          (*teams_number)++;
          if (max_games_won == 0) {
            (*teams_with_max_games_won)++;
          }
          break;
        }
      }
    }
  }
}

/*This function searchs in my teams_hash_table for a particular name that is given as an argument - it returns the slot where the team is, -1 otherwise*/
int teams_search (char *name, team *hash_table, int size) {
  int key = hash(name,size);
  int i = key;
  if (hash_table[key].name != NULL && strcmp(hash_table[key].name,name) == 0) { /*I found the team*/
    return key;
  }
  else if (hash_table[key].name != NULL && strcmp(hash_table[key].name,name) != 0) {
    for (i = key+1; i < size; i++) {
      if (hash_table[i].name != NULL && strcmp(hash_table[i].name,name) == 0) { /*I found the team - out of the slot indicated by the hash*/
        return i;
      }
    }
  }
  return -1;
}

/*This functions calls teams_search and check for error with teams*/
void team_errors (int found, team *hash_table, int counter) {
  if (found != -1) {
    printf("%d %s %d\n",counter, hash_table[found].name, hash_table[found].games_won);
  }
  else {
    printf("%d Equipa inexistente.\n",counter);
  }
}

/*This function will increase the games_won of a team*/
void team_increase_games_won (char *name, team *hash_table, int size,int* max_games_won, int* teams_with_max_games_won, int *second_max_games_won,int* teams_with_second_max_games_won) {
  int key = teams_search(name,hash_table,size);
  hash_table[key].games_won++;
  if (hash_table[key].games_won == *max_games_won) {
    (*teams_with_max_games_won)++;
  }
  else if (hash_table[key].games_won == *second_max_games_won) {
    (*teams_with_second_max_games_won)++;
  }
  else if (hash_table[key].games_won > *max_games_won) { /*We have a new max_games_won*/
    (*second_max_games_won) = (*max_games_won);
    (*teams_with_second_max_games_won) = (*teams_with_max_games_won);
    (*max_games_won) = hash_table[key].games_won;
    (*teams_with_max_games_won) = 1;
  }
  else if (hash_table[key].games_won > *second_max_games_won) { /*We have a new second_max_games_won*/
    (*second_max_games_won) = hash_table[key].games_won;
    (*teams_with_second_max_games_won) = 1;
  }
}

/*This function will decrease the games_won of a team*/
void team_decrease_games_won (char *name, team *hash_table, int size,int* max_games_won, int* teams_with_max_games_won, int *second_max_games_won, int *teams_with_second_max_games_won, int teams_number) {
  int key = teams_search(name,hash_table,size);
  int i, j = 0;
  if (hash_table[key].games_won == (*max_games_won)) {
    (*teams_with_max_games_won)--;
    if ((*teams_with_max_games_won) == 0) { /*Only exist one team with max_games_won and it will be deleted*/
      (*teams_with_max_games_won) = (*teams_with_second_max_games_won);
      (*max_games_won) = (*second_max_games_won);
      (*teams_with_second_max_games_won) = 0;
      (*second_max_games_won) = 0;
      for (i = 0; i < size && j < teams_number; i++) { /*Find the new second_max_games_won and teams_with_second_max_games_won*/
        if (hash_table[i].name != NULL) { /*Found a team*/
          j++;
          if (hash_table[i].games_won > (*second_max_games_won) && hash_table[i].games_won < (*max_games_won)) {
            (*teams_with_second_max_games_won) = 1;
            (*second_max_games_won) = hash_table[i].games_won;
          }
          else if (hash_table[i].games_won == (*second_max_games_won)) {
            (*teams_with_second_max_games_won)++;
          }
        }
      }
    }
  }
  else if (hash_table[key].games_won == (*second_max_games_won)) {
    (*teams_with_second_max_games_won)--;
    if ((*teams_with_second_max_games_won) == 0) { /*Only exist one team with max_games_won and it will be deleted*/
      (*second_max_games_won) = 0;
      for (i = 0; i < size && j < teams_number; i++) { /*Find the new second_max_games_won and teams_with_second_max_games_won*/
        if (hash_table[i].name != NULL) { /*Found a team*/
          j++;
          if (hash_table[i].games_won > (*second_max_games_won) && hash_table[i].games_won < (*max_games_won)) {
            (*teams_with_second_max_games_won) = 1;
            (*second_max_games_won) = hash_table[i].games_won;
          }
          else if (hash_table[i].games_won == (*second_max_games_won)) {
            (*teams_with_second_max_games_won)++;
          }
        }
      }
    }
  }
  hash_table[key].games_won--;
}

/*This function will look in the teams_hash_table for the teams that have the highest number of won games*/
void find_team_with_more_games_won (team *hash_table, int size, int teams_with_max_games_won, int max_games_won, int counter) {
  int i = 0, j = 0;
  team *teams_list = (team*) can_fail_malloc (sizeof(team)*teams_with_max_games_won); /*This will be my auxiliar array where I will sort the teams*/
  char* aux_name = can_fail_malloc(sizeof(char)*MAX_WORD_SIZE);
  int aux_games_won;
  for (; i < size && j < teams_with_max_games_won; i++) { /*Copy from the hash_table to the auxiliar array*/
    if (hash_table[i].name != NULL && hash_table[i].games_won == max_games_won) { /*Only copies the teams that have the highest number of games won*/
      teams_list[j].name = can_fail_malloc (sizeof(char)*MAX_WORD_SIZE);
      strcpy(teams_list[j].name,hash_table[i].name);
      teams_list[j].games_won = hash_table[i].games_won;
      j++;
    }
  }

  for (i = 0; i < teams_with_max_games_won-1; i++) { /*Order the auxiliar array*/
    for (j = i+1; j < teams_with_max_games_won; j++) {
      if (strcmp(teams_list[i].name,teams_list[j].name) > 0) {
        /*Passing from teams_list[i].name to aux_name*/
        strcpy(aux_name,teams_list[i].name);
        aux_games_won = teams_list[i].games_won;
        /*Passing from teams_list[j].name to teams_list[i].name*/
        strcpy(teams_list[i].name,teams_list[j].name);
        teams_list[i].games_won = teams_list[j].games_won;
        /*Passing from aux_name to teams_list[j].name*/
        strcpy(teams_list[j].name,aux_name);
        teams_list[j].games_won = aux_games_won;
      }
    }
  }

  printf("%d Melhores %d\n",counter, max_games_won);
  for (i = 0; i < teams_with_max_games_won; i++) { /*Print the ordered array*/
    printf("%d * %s\n",counter, teams_list[i].name);
  }

  free_teams(teams_list,teams_with_max_games_won);
  free(teams_list);
  free(aux_name);
}

/*This function will free every name in the teams_hash_table*/
void free_teams(team *hash_table, int size) {
  int i = 0;
  for (; i < size; i++) {
    if (hash_table[i].name != NULL) {
      free(hash_table[i].name);
    }
  }
}








/*this function initializes my games_hash_table with NULL in the names and 0 in the games_won*/
void games_initialize (game* hash_table, int size) {
  int i = 0;
  for (i = 0; i < size; i++) {
    hash_table[i].name = NULL;
    hash_table[i].team1 = NULL;
    hash_table[i].team2 = NULL;
    hash_table[i].score1 = 0;
    hash_table[i].score2 = 0;
    hash_table[i].number = 0;
  }
}

/*This function adds a game to my games_hash_table, recognizes the errors associated with games*/
void create_game (char *name, char *team1, char *team2, int score1, int score2, game *hash_table, int size, team *teams_hash_table, int teams_size,int counter, int *games_number, int *max_games_won, int*teams_with_max_games_won, int *number, int *second_max_games_won, int *teams_with_second_max_games_won) {
  int key = hash(name,size);
  int length = strlen(name)+1;
  int key_team1;
  int key_team2;
  int i,z = 0;
  if (hash_table[key].name != NULL && strcmp(hash_table[key].name,name) == 0) { /*The game already exists*/
    printf("%d Jogo existente.\n",counter);
    return;
  }
  else {
    if (hash_table[key].name != NULL) { /*The slot is not empty*/
      for (i = key+1; i < size; i++) { /*Check the rest of the table*/
        if (hash_table[i].name != NULL && strcmp(hash_table[i].name,name) == 0) { /*The game already exists*/
          printf("%d Jogo existente.\n",counter);
          return;
        }
        else if (hash_table[i].name == NULL && z == 0) {
          key = i; /*Key will keep the first empty_spot to put the game*/
          z++;
        }
      }
    }
    key_team1 = teams_search(team1,teams_hash_table,teams_size);
    key_team2 = teams_search(team2,teams_hash_table,teams_size);
    if (key_team1 == -1 || key_team2 == -1) { /*One of the teams does not exist*/
      printf("%d Equipa inexistente.\n",counter);
      return;
    }
    hash_table[key].name = can_fail_malloc(sizeof(char)*length);
    strcpy(hash_table[key].name,name);

    length = strlen(team1)+1;
    hash_table[key].team1 = can_fail_malloc(sizeof(char)*length);
    strcpy(hash_table[key].team1,team1);

    length = strlen(team2)+1;
    hash_table[key].team2 = can_fail_malloc(sizeof(char)*length);
    strcpy(hash_table[key].team2,team2);

    hash_table[key].score1 = score1;
    hash_table[key].score2 = score2;
    hash_table[key].number = (*number);
    if (score1 > score2) {
      team_increase_games_won(team1,teams_hash_table,teams_size,max_games_won,teams_with_max_games_won,second_max_games_won,teams_with_second_max_games_won);
    }
    else if (score2 > score1) {
      team_increase_games_won(team2,teams_hash_table,teams_size,max_games_won,teams_with_max_games_won,second_max_games_won,teams_with_second_max_games_won);
    }
    (*games_number)++;
    (*number)++;
  }
}

/*This function searchs in my games_hash_table for a particular name that is given as an argument - it returns the slot where the game is, -1 otherwise*/
int games_search (char *name, game *hash_table, int size) {
  int key = hash(name,size);
  int i = key;
  if (hash_table[key].name != NULL && strcmp(hash_table[key].name,name) == 0) { /*I found the game*/
    return key;
  }
  else if ((hash_table[key].name != NULL && strcmp(hash_table[key].name,name) != 0) || hash_table[key].name == NULL ) { /*The game is not in the slot given by hash - it can still be in the hash_table*/
    for (i = key+1; i < size; i++) { /*Search for the game in the rest of the table*/
      if (hash_table[i].name != NULL && strcmp(hash_table[i].name,name) == 0) { /*I found the game*/
        return i;
      }
    }
  }
  return -1;
}

/*This functions calls games_search and check for error with games*/
void game_errors (int found, game* hash_table, int counter) {
    if (found != -1) { /*The games already exists*/
      printf("%d %s %s %s %d %d\n",counter, hash_table[found].name,hash_table[found].team1,hash_table[found].team2,hash_table[found].score1,hash_table[found].score2);
    }
    else {
      printf("%d Jogo inexistente.\n",counter);
    }
}

/*This function will remove a game*/
void remove_game (char* game_name, game *hash_table, int games_size, team* teams_hash_table, int teams_size, int *max_games_won, int *teams_with_max_games_won, int *second_max_games_won, int *teams_with_second_max_games_won,int teams_number,int* games_number,int counter) {
  int found = games_search (game_name, hash_table, games_size);
  if (found == -1) {
    printf("%d Jogo inexistente.\n",counter);
  }
  else { /*I have to remove the game*/
    if (hash_table[found].score1 > hash_table[found].score2) {
      team_decrease_games_won(hash_table[found].team1,teams_hash_table,teams_size,max_games_won,teams_with_max_games_won,second_max_games_won,teams_with_second_max_games_won,teams_number);
    }
    else if (hash_table[found].score2 > hash_table[found].score1) {
      team_decrease_games_won(hash_table[found].team2,teams_hash_table,teams_size,max_games_won,teams_with_max_games_won,second_max_games_won,teams_with_second_max_games_won,teams_number);
    }
    free(hash_table[found].name);
    free(hash_table[found].team1);
    free(hash_table[found].team2);
    hash_table[found].name = NULL;
    hash_table[found].team1 = NULL;
    hash_table[found].team2 = NULL;
    hash_table[found].score1 = 0;
    hash_table[found].score2 = 0;
    hash_table[found].number = 0;
    (*games_number)--;
  }
}

/*This function will change the score of a game*/
void change_score(char* game_name, int team1_score, int team2_score, game *hash_table, int games_size, team* teams_hash_table, int teams_size, int *max_games_won, int *teams_with_max_games_won, int *second_max_games_won, int *teams_with_second_max_games_won,int teams_number,int counter) {
  int found = games_search (game_name, hash_table, games_size);
  if (found == -1) {
    printf("%d Jogo inexistente.\n",counter);
  }
  else { /*I have to remove the game*/
    if (hash_table[found].score1 > hash_table[found].score2) {
      if (team1_score < team2_score) { /*The new_score changes the winner*/
        team_decrease_games_won(hash_table[found].team1,teams_hash_table,teams_size,max_games_won,teams_with_max_games_won,second_max_games_won,teams_with_second_max_games_won,teams_number);
        team_increase_games_won(hash_table[found].team2,teams_hash_table,teams_size,max_games_won,teams_with_max_games_won,second_max_games_won,teams_with_second_max_games_won);
      }
      else if (team1_score == team2_score) {
        team_decrease_games_won(hash_table[found].team1,teams_hash_table,teams_size,max_games_won,teams_with_max_games_won,second_max_games_won,teams_with_second_max_games_won,teams_number);
      }
    }
    else if (hash_table[found].score2 > hash_table[found].score1) {
      if (team2_score < team1_score) { /*The new_score changes the winner*/
        team_decrease_games_won(hash_table[found].team2,teams_hash_table,teams_size,max_games_won,teams_with_max_games_won,second_max_games_won,teams_with_second_max_games_won,teams_number);
        team_increase_games_won(hash_table[found].team1,teams_hash_table,teams_size,max_games_won,teams_with_max_games_won,second_max_games_won,teams_with_second_max_games_won);
      }
      else if (team1_score == team2_score) {
        team_decrease_games_won(hash_table[found].team2,teams_hash_table,teams_size,max_games_won,teams_with_max_games_won,second_max_games_won,teams_with_second_max_games_won,teams_number);
      }
    }
    else if (hash_table[found].score2 == hash_table[found].score1) {
      if (team1_score > team2_score) {
        team_increase_games_won(hash_table[found].team1,teams_hash_table,teams_size,max_games_won,teams_with_max_games_won,second_max_games_won,teams_with_second_max_games_won);
      }
      else if (team2_score > team1_score) {
        team_increase_games_won(hash_table[found].team2,teams_hash_table,teams_size,max_games_won,teams_with_max_games_won,second_max_games_won,teams_with_second_max_games_won);
      }
    }
    hash_table[found].score1 = team1_score;
    hash_table[found].score2 = team2_score;
  }
}

/*This function will copy all the games to an auxiliar array, order them by number and print all the games*/
void list_all_the_games(game *hash_table, int size, int games_number, int counter) {
  int i = 0, j = 0, length;
  game *games_list = (game*) can_fail_malloc (sizeof(game) *games_number);
  char* aux_name, *aux_team1, *aux_team2;
  int aux_number, aux_score1, aux_score2;

  for (; i < size && j < games_number; i++) { /*Copy from the hash_table to the auxiliar array*/
    if (hash_table[i].name != NULL) {
      length = strlen(hash_table[i].name)+1;
      games_list[j].name = can_fail_malloc (sizeof(char)*length);
      strcpy(games_list[j].name,hash_table[i].name);
      length = strlen(hash_table[i].team1)+1;
      games_list[j].team1 = can_fail_malloc (sizeof(char)*length);
      strcpy(games_list[j].team1,hash_table[i].team1);
      length = strlen(hash_table[i].team2)+1;
      games_list[j].team2 = can_fail_malloc (sizeof(char)*length);
      strcpy(games_list[j].team2,hash_table[i].team2);
      games_list[j].score1 = hash_table[i].score1;
      games_list[j].score2 = hash_table[i].score2;
      games_list[j].number = hash_table[i].number;
      j++;
    }
  }

  for (i = 0; i < games_number-1; i++) { /*Order the auxiliar array*/
    for (j = i+1; j < games_number; j++) {
      if (games_list[i].number > games_list[j].number) {
        /*Passing from teams_list[i].name to aux variables*/
        length = strlen(games_list[i].name)+1;
        aux_name = can_fail_malloc (sizeof(char)*length);
        strcpy(aux_name,games_list[i].name);
        length = strlen(games_list[i].team1)+1;
        aux_team1 = can_fail_malloc (sizeof(char)*length);
        strcpy(aux_team1,games_list[i].team1);
        length = strlen(games_list[i].team2)+1;
        aux_team2 = can_fail_malloc (sizeof(char)*length);
        strcpy(aux_team2,games_list[i].team2);
        aux_score1 = games_list[i].score1;
        aux_score2 = games_list[i].score2;
        aux_number = games_list[i].number;

        /*Passing from games_list[j].name to games_list[i].name*/
        length = strlen(games_list[j].name)+1;
        games_list[i].name = can_fail_malloc (sizeof(char)*length);
        strcpy(games_list[i].name,games_list[j].name);
        length = strlen(games_list[j].team1)+1;
        games_list[i].team1 = can_fail_malloc (sizeof(char)*length);
        strcpy(games_list[i].team1,games_list[j].team1);
        length = strlen(games_list[j].team2)+1;
        games_list[i].team2 = can_fail_malloc (sizeof(char)*length);
        strcpy(games_list[i].team2,games_list[j].team2);
        games_list[i].score1 = games_list[j].score1;
        games_list[i].score2 = games_list[j].score2;
        games_list[i].number = games_list[j].number;


        /*Passing from aux variables to games_list[j].name*/
        length = strlen(aux_name)+1;
        games_list[j].name = can_fail_malloc (sizeof(char)*length);
        strcpy(games_list[j].name,aux_name);
        length = strlen(aux_team1)+1;
        games_list[j].team1 = can_fail_malloc (sizeof(char)*length);
        strcpy(games_list[j].team1,aux_team1);
        length = strlen(aux_team2)+1;
        games_list[j].team2 = can_fail_malloc (sizeof(char)*length);
        strcpy(games_list[j].team2,aux_team2);
        games_list[j].score1 = aux_score1;
        games_list[j].score2  = aux_score2;
        games_list[j].number = aux_number;
      }
    }
  }

  for (i = 0; i < games_number; i++) { /*Print the ordered array*/
    printf("%d %s %s %s %d %d\n",counter, games_list[i].name,games_list[i].team1,games_list[i].team2,games_list[i].score1,games_list[i].score2);
  }

  free_games(games_list,games_number);
  free(games_list);
}

/*This function will free every name in the games_hash_table*/
void free_games(game *hash_table, int size) {
  int i = 0;
  for (; i < size; i++) {
    if (hash_table[i].name != NULL) {
      free(hash_table[i].name);
      free(hash_table[i].team1);
      free(hash_table[i].team2);
    }
  }
}
