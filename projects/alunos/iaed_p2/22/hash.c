#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "hash.h"

unsigned long hash(char *s){
    unsigned long hash = 5381;
    int c;
    while((c=*s++)){
        hash = hash*33 + c;
    }
    hash = hash % HASHSIZE;
    return hash;
}

void init_hash_games(struct game** hash_games){
    int i;
    for (i= 0; i< HASHSIZE; i++)
      hash_games[i] = NULL;
}

void init_hash_teams(struct team** hash_teams){
    int i;
    for (i= 0; i< HASHSIZE; i++)
      hash_teams[i] = NULL;
}

/*funcao que cria o espaco para alocar um novo jogo e preenche com o nome*/
struct game* createGame(char* name, struct team* team1, struct team* team2, int score1, int score2){
  struct game* game = can_fail_malloc(sizeof(struct game));
  game->name = can_fail_malloc(strlen(name)*sizeof(char) + 1);
  game->team1 = team1;
  game->team2 = team2;
  game->score1 = score1;
  game->score2 = score2;
  strcpy(game->name,name);
  return game;
}

/*funcao que cria o espaco para alocar uma nova equipa*/
struct team* createTeam(char* name){
  struct team* team = can_fail_malloc(sizeof(struct team));
  team->name = can_fail_malloc(strlen(name)*sizeof(char) + 1);
  strcpy(team->name,name);
  team->wins = 0;
  return team;
}

void addTeam(char* name, struct team** hash_teams, struct team* last){
  struct team* newTeam;
  newTeam = createTeam(name);
  newTeam->nextHash = NULL;
  if(hash_teams[hash(name)] == NULL){
    newTeam->previousHash = NULL;
    hash_teams[hash(name)] = newTeam;
  }
  else{
    newTeam->previousHash = last;
    last->nextHash = newTeam;
  }
}

/*Adiciona o jogo na estrutura*/
void addGame(char* name, char* team1, char* team2, int s1, int s2, struct game** hash_games,struct team** hash_teams,struct game** lastGame,struct game** firstGame){
  struct team* teamOne = getTeam(team1,hash_teams);
  struct team* teamTwo = getTeam(team2,hash_teams);
  struct game* newGame = createGame(name,teamOne,teamTwo,s1,s2);
  struct game* g;
  if(*lastGame == NULL){
    newGame->previousGeral = NULL;
    newGame->nextGeral = NULL;
    *firstGame = newGame;
    *lastGame = newGame ;
  }
  else{
    g = *lastGame;
    g->nextGeral = newGame;
    newGame->previousGeral = *lastGame;
    newGame->nextGeral = NULL;
    *lastGame = newGame;
  }

  if(hash_games[hash(name)] == NULL){
    newGame->nextHash = NULL;
    newGame->previousHash = NULL;
    hash_games[hash(name)] = newGame;
  }
  else{
    g = hash_games[hash(name)];
    while(g->nextHash != NULL){
      g = g->nextHash;
    }
    newGame->nextHash = NULL;
    newGame->previousHash = g;
    g->nextHash = newGame;
  }
  if(s1>s2){
    teamOne->wins++;
  }
  if(s1<s2){
    teamTwo->wins++;
  }
}

void freeGame(struct game* game){
  free(game->name);
  free(game);
}

void freeTeam(struct team* team){
  free(team->name);
  free(team);
}

/*funcao que elimina todos os elementos das listas ligadas da hash de equipas*/
void deleteHashTeams(struct team** hash_teams){
  int i;
  struct team* t;
  struct team* t1;
  for(i=0; i<HASHSIZE; i++){
    if(hash_teams[i] != NULL){
      t1 = hash_teams[i];
      while(t1 != NULL){
        t = t1->nextHash;
        freeTeam(t1);
        t1 = t;
      }
    }
  }
  free(hash_teams);
}


/*funcao que verifica a existencia de uma equipa*/
int teamExists(char* name,struct team** hash_teams){
  struct team* t;
  for(t = hash_teams[hash(name)]; t != NULL; t = t->nextHash){
    if(strcmp(name,t->name)==0){
      return 0;
    }
  }
  return -1;
}

/*funcao que verifica a existencia de um jogo*/
int gameExists(char* name,struct game** hash_games){
  struct game* g;
  if(hash_games[hash(name)] == NULL){
    return -1;
  }
  else{
    for(g=hash_games[hash(name)]; g != NULL; g = g->nextHash){
      if(strcmp(name,g->name)==0){
        return 0;
      }
    }
  }
  return -1;
}

/*recebe o nome da equipa e a hash, e devolve a estrutura equipa desejada*/
struct team* getTeam(char* name,struct team** hash_teams){
  struct team* t;
  for(t = hash_teams[hash(name)]; t != NULL; t = t->nextHash){
    if(strcmp(name,t->name) == 0){
      return t;
    }
  }
  return NULL;
}

/*Altera o score*/
void changeScore(struct game* g, int s1,int s2){
  if(g->score1 > g->score2){
    if(s1 < s2){
      g->team2->wins++;
      g->team1->wins--;
    }
    if(s1 == s2){
      g->team1->wins--;
    }
  }
  else if(g->score1 < g->score2){
    if(s1 > s2){
      g->team1->wins++;
      g->team2->wins--;
    }
    if(s1 == s2){
      g->team2->wins--;
    }
  }
  else{
    if(s1>s2){
      g->team1->wins++;
    }
    if(s1<s2){
      g->team2->wins++;
    }
  }
  g->score1 = s1;
  g->score2 = s2;
}

void removeGame(struct game* g,struct game** hash_games,struct game** lastGame,struct game** firstGame){
  struct game* game;
  struct game* game1;
  changeScore(g,0,0); /*para tratar logo de corrigir as wins*/
  if(g->previousHash==NULL){
    if(g->nextHash==NULL){
      hash_games[hash(g->name)]=NULL;
    }
    else{
      game = g->nextHash;
      game->previousHash = NULL;
      hash_games[hash(g->name)] = game;
    }
  }
  else{
    game = g->previousHash;
    game->nextHash = g->nextHash;
  }

  if(g->previousGeral == NULL){
    if(g->nextGeral==NULL){
      *firstGame = NULL;
      *lastGame = NULL;
      freeGame(g);
      return;
    }
    else{
      game = g->nextGeral;
      game->previousGeral = NULL;
      *firstGame = game;
      freeGame(g);
      return;
    }
  }
  else{
    if(g->nextGeral == NULL){
      game = g->previousGeral;
      game->nextGeral = NULL;
      *lastGame = game;
      freeGame(g);
      return;
    }
    else{
      game = g->previousGeral;
      game1 = g->nextGeral;
      game1->previousGeral = game;
      game->nextGeral = game1;
      freeGame(g);
      return;
    }
  }
}

/*funcao que encontra o maximode vitorias que pelo menos uma equipa tem*/
int findMaxWins(struct team** hash_teams){
  int max,i;
  struct team* t;
  max = -1;
  for(i=0; i < HASHSIZE; i++){
    if(hash_teams[i] != NULL){
      for(t = hash_teams[i]; t != NULL; t = t->nextHash){
        if(t->wins > max){
          max = t->wins;
        }
      }
    }
  }
  return max;
}

/*sort basico para organizar um array de strings por ordem alfabetica*/
void sortAlphabetic(char** array, int max){
  int i, j;
  char* swap;
  for (i = 0; i < max; i++){
    for (j = 0; j < max; j++){
      if (strcmp(array[j],array[i]) > 0){
        swap = array[i];
        array[i] = array[j];
        array[j] = swap;
      }
    }
  }
}
