#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "hash.h"

unsigned int hash(const char * key) {
  unsigned long int value = 0;
  unsigned int i = 0;
  unsigned int key_len = strlen(key);

  for (; i < key_len; i++) {
      value = value * 37 + key[i];
  }
  value = value % TABLE_SIZE;
  return value;
}

ht * hash_init() {
  int i;
  ht * hashtable = can_fail_malloc(sizeof(ht));
  hashtable->entries = can_fail_malloc(sizeof(entry*) * TABLE_SIZE);

  i = 0;
  for(; i < TABLE_SIZE; i++) {
      hashtable->entries[i] = NULL;
  }
  return hashtable;
}

entry * ht_pair_team(unsigned int key, char * buffer) {
  entry * entrie = can_fail_malloc(sizeof(entry));
  entrie->t = can_fail_malloc(sizeof(Team));
  entrie->t->nome = can_fail_malloc(sizeof(char) * (strlen(buffer) + 1));
  entrie->t->wins = 0;
  strcpy(entrie->t->nome, buffer);
  entrie->key = key;
  entrie->next = NULL; /* linked list entries */

  return entrie;
}

entry * ht_pair_game(unsigned int key, char * buffer, Team * t1, Team * t2, int score1, int score2, int * maxWins) {
  entry * entrie = can_fail_malloc(sizeof(entry));
  entrie->game = can_fail_malloc(sizeof(Game));
  entrie->game->gameName = can_fail_malloc(sizeof(char) * (strlen(buffer) + 1));
  entrie->game->t1 = t1;
  entrie->game->t2 = t2;
  entrie->game->score1 = score1;
  entrie->game->score2 = score2;
  strcpy(entrie->game->gameName, buffer);
  entrie->key = key;
  entrie->next = NULL;

  /* see which team won the game and add a victory to the winning team */
  if (score1 > score2) {
    t1->wins++;
    if (t1->wins > (*maxWins))
      (*maxWins) = t1->wins;
  }
  else if (score2 > score1) {
    t2->wins++;
    if (t2->wins > (*maxWins))
      (*maxWins) = t2->wins;
  }

  return entrie;
}

Team * addTeam(ht * hashtable, int cmd_count) {
  char teamname[MAX_CHAR];
  entry * entrie;
  entry * prev;
  unsigned int key;
  scanf(" %[^:\n]", teamname);
  key = hash(teamname);
  entrie = hashtable->entries[key];

  /* pairs in the first entry if the entry is empty */
  if (entrie == NULL) {
    hashtable->entries[key] = ht_pair_team(key, teamname);
    return hashtable->entries[key]->t;
  }

  /* if the entry is not empty, it cycles through until reaches the "NULL" position */
  while (entrie != NULL) {
    if (strcmp(entrie->t->nome, teamname) != 0 && entrie->next == NULL) {
      entrie->next = ht_pair_team(key, teamname);
      return entrie->next->t;
    }
    else if (strcmp(entrie->t->nome, teamname) == 0) {
      printf("%d Equipa existente.\n", cmd_count);
      return NULL;
    }

    prev = entrie;
    entrie = prev->next;
  }

  prev->next = ht_pair_team(key, teamname);
  return prev->next->t;
}


Team * teamSearch(ht * hashtable, char * name) {
  entry * entrie;
  unsigned int key;
  key = hash(name);

  entrie = hashtable->entries[key];
  /* if the entry is empty */
  if (entrie == NULL) {
    return NULL;
  }
  /* if the entry is not empty, it cycles through until it reaches the end of the linked list entry trying to find the team */
  while (entrie != NULL) {
    if (strcmp(entrie->t->nome, name) == 0) {
      return entrie->t; /* if the game is found */
    }
    entrie = entrie->next;
  }
  return NULL;
}

void getTeam(ht * hashtable, int cmd_count) {
  char name[MAX_CHAR];
  Team * team;
  scanf(" %[^:\n]", name);
  team = teamSearch(hashtable, name); /* aux function that searches if a team exists, returning NULL otherwise*/

  if (team == NULL) {
    printf("%d Equipa inexistente.\n", cmd_count);
  }
  else {
    printf("%d %s %d\n", cmd_count, team->nome, team->wins);
  }
}

int searchGame(entry * entrie, char * buffer) {
  entry * aux = entrie;
  /* if the entry is empty returns 0, which means the game does not exists */
  if (aux == NULL) {
    return 0;
  }

  if (aux->game != NULL) {
    while (strcmp(aux->game->gameName, buffer) != 0) {
      if (aux->next == NULL) { /* reached the end of the entry and the game was not found */
        return 0;
      }
      aux = aux->next;
    }
    return 1; /* game found */
  }
  else
    return 0;
}


void getGame(ht * game_ht, int cmd_count) {
  char name[MAX_CHAR];
  entry * entrie;
  int key;
  scanf(" %[^\n]", name);


  key = hash(name);
  entrie = game_ht->entries[key];

  if (!searchGame(entrie, name)) {
    printf("%d Jogo inexistente.\n", cmd_count);
  }
  else {
    /* cycles through the entry searching for the game */
    while (entrie->game != NULL && strcmp(entrie->game->gameName, name) != 0) {
      entrie = entrie->next;
    }
      printf("%d %s %s %s %d %d\n", cmd_count, entrie->game->gameName, entrie->game->t1->nome, entrie->game->t2->nome, entrie->game->score1, entrie->game->score2);
  }
}

Game * addGame(ht * hashtable, ht * game_ht, int cmd_count, int * game_count, int * maxWins) {
  char gameName[MAX_CHAR];
  char t1_name[MAX_CHAR];
  char t2_name[MAX_CHAR];
  int score1, score2;
  Team * t1;
  Team * t2;
  entry * entrie;
  entry * prev;
  unsigned int key;

  scanf(" %[^:]:%[^:]:%[^:]:%d:%d", gameName, t1_name, t2_name, &score1, &score2);
  t1 = teamSearch(hashtable, t1_name);
  t2 = teamSearch(hashtable, t2_name);

  key = hash(gameName);
  entrie = game_ht->entries[key];

  if (entrie == NULL) {
    if (t1 == NULL || t2 == NULL) {
      printf("%d Equipa inexistente.\n", cmd_count);
      return NULL;
    }
    /* if the teams exists and the first entry is empty, it pairs the game in this entry */
    game_ht->entries[key] = ht_pair_game(key, gameName, t1, t2, score1, score2, maxWins);
    (*game_count)++;
    return game_ht->entries[key]->game;
  }
  /* cycle through until it finds the end of the linked list */
  while (entrie != NULL) {
    if (strcmp(entrie->game->gameName, gameName) != 0 && entrie->next == NULL && entrie->game != NULL && t1 != NULL && t2 != NULL) {
      entrie->next = ht_pair_game(key, gameName, t1, t2, score1, score2, maxWins);
      (*game_count)++;
      return entrie->next->game;
    } /* in case the game exists */
    else if (strcmp(entrie->game->gameName, gameName) == 0) {
      printf("%d Jogo existente.\n", cmd_count);
      return NULL;
    }
    prev = entrie;
    entrie = prev->next;
  }

  if (t1 == NULL || t2 == NULL) {
    printf("%d Equipa inexistente.\n", cmd_count);
    return NULL;
  }
  prev->next = ht_pair_game(key, gameName, t1, t2, score1, score2, maxWins);
  (*game_count)++;
  return prev->next->game;
}

void changeScore(ht * game_ht, int cmd_count) {
  char buffer[MAX_CHAR];
  entry * entrie;
  int key;
  int score1, score2;
  scanf(" %[^:]:%d:%d", buffer, &score1, &score2);

  key = hash(buffer);
  entrie = game_ht->entries[key];

  if (!searchGame(entrie, buffer)) {
    printf("%d Jogo inexistente.\n", cmd_count);
    return;
  }

  while (strcmp(entrie->game->gameName, buffer) != 0) {
    entrie = entrie->next;
  }

  /* adjusts the victories count */
  if (entrie->game->score1 > entrie->game->score2) {
    entrie->game->t1->wins--;
  }
  else if (entrie->game->score2 > entrie->game->score1) {
    entrie->game->t2->wins--;
  }

  if (score1 > score2) {
    entrie->game->t1->wins++;
  }
  else if (score2 > score1) {
    entrie->game->t2->wins++;
  }

  entrie->game->score1 = score1;
  entrie->game->score2 = score2;
}

entry * destroyTeamEntry(entry * head) {
  entry * new = head;
  while (new != NULL) {
    entry * aux = new->next;
    free(new->t->nome);
    free(new->t);
    free(new);
    new = aux;
  }
  return NULL;
}

entry * destroyGameEntry(entry * head) {
  entry * new = head;
  while (new != NULL) {
    entry * aux = new->next;
    free(new->game->gameName);
    free(new->game);
    free(new);
    new = aux;
  }
  return NULL;
}

void destroyTeam(ht * hashtable) {
  int i;
  for (i = 0; i < TABLE_SIZE; i++) {
    if (hashtable->entries[i] == NULL) {
      continue;
    }
    else {
      destroyTeamEntry(hashtable->entries[i]);
    }
  }
  free(hashtable->entries);
  free(hashtable);
}

void destroyGame(ht * hashtable) {
  int i;
  for (i = 0; i < TABLE_SIZE; i++) {
    if (hashtable->entries[i] == NULL) {
      continue;
    }
    else {
      destroyGameEntry(hashtable->entries[i]);
    }
  }
  free(hashtable->entries);
  free(hashtable);
}
