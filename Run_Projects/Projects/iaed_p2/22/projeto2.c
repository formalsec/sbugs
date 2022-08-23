#include "hash.h"
int line = 0; /*Variavel global que guarda o numero de linhas do input*/

void comando_a(struct game** hash_games,struct team** hash_teams,struct game** lastGame,struct game** firstGame){
  char* name = malloc(sizeof(char) * MAXINPUT);
  char* team1 = malloc(sizeof(char) * MAXINPUT);
  char* team2 = malloc(sizeof(char) * MAXINPUT);
  int s1,s2;
  scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", name, team1, team2, &s1, &s2);

  if(gameExists(name,hash_games)==0){
    printf("%d Jogo existente.\n",line);
    free(name);
    free(team1);
    free(team2);
    return;
  }
  if(teamExists(team1,hash_teams) == -1 || teamExists(team2,hash_teams) == -1){
    printf("%d Equipa inexistente.\n",line);
    free(name);
    free(team1);
    free(team2);
    return;
  }
  addGame(name,team1,team2,s1,s2,hash_games,hash_teams,lastGame,firstGame);
  free(name);
  free(team1);
  free(team2);
  return;
}

void comando_A(char* input,struct team** hash_teams){
  unsigned long key;
  struct team* t;
  struct team* t1;
  key = hash(input);
  for(t = hash_teams[key]; t != NULL; t = t->nextHash){
    if(strcmp(t->name,input) == 0){
      printf("%d Equipa existente.\n",line);
      return;
    }
    t1 = t;
  }
  if(hash_teams[key]== NULL){
    addTeam(input,hash_teams,hash_teams[key]);
  }
  else{
    addTeam(input,hash_teams,t1); /* a equipa t1 e a ultima nessa lista*/
  }
  return;
}

void comando_l(struct game** firstGame){
  struct game* g;
  if(firstGame == NULL){
    return;
  }
  g = *firstGame;
  while(g != NULL){
    printf("%d %s %s %s %d %d\n",line,g->name,g->team1->name,g->team2->name,g->score1,g->score2);
    g = g->nextGeral;
    }
}

void comando_s(struct game** hash_games){
  struct game* g;
  char* name = malloc(sizeof(char)*MAXINPUT);
  int s1,s2;
  scanf(" %[^:\n]:%d:%d", name,&s1, &s2);

  if(hash_games[hash(name)]==NULL){
    printf("%d Jogo inexistente.\n",line);
    free(name);
    return;
  }
  for(g=hash_games[hash(name)]; g != NULL; g = g->nextHash){
    if(strcmp(name,g->name)==0){
      changeScore(g,s1,s2);
      free(name);
      return;
    }
  }
  printf("%d Jogo inexistente.\n",line);
  free(name);
  return;
}

void comando_p(char* input,struct game** hash_games){
  struct game* g;
  if(hash_games[hash(input)]==NULL){
    printf("%d Jogo inexistente.\n",line);
    return;
  }
  for(g=hash_games[hash(input)]; g != NULL; g = g->nextHash){
    if(strcmp(input,g->name)==0){
      printf("%d %s %s %s %d %d\n",line,g->name,g->team1->name,g->team2->name,g->score1,g->score2);
      return;
    }
  }
  printf("%d Jogo inexistente.\n",line);
  return;
}

void comando_P(char* input, struct team** hash_teams){
  struct team* t;
  if(hash_teams[hash(input)]==NULL){
    printf("%d Equipa inexistente.\n",line);
    return;
  }
  for(t=hash_teams[hash(input)]; t != NULL; t = t->nextHash){
    if(strcmp(input,t->name)==0){
      printf("%d %s %d\n",line,input,t->wins);
      return;
    }
  }
  printf("%d Equipa inexistente.\n",line);
  return;
}

void comando_g(struct team** hash_teams){
  struct team* t;
  char** teams = malloc(sizeof(char*)*500);
  int i;
  int n;
  int max = findMaxWins(hash_teams);
  n = 0;
  for(i=0;i<500;i++){
    teams[i] = malloc(sizeof(char)*300);
  }
  if(max==-1){
    for(i=0;i<500;i++){
      free(teams[i]);
    }
    free(teams);
    return;
  }
  for(i=0; i < HASHSIZE; i++){
    if(hash_teams[i] != NULL){
      for(t = hash_teams[i]; t != NULL; t = t->nextHash){
        if(t->wins == max){
          strcpy(teams[n],t->name);
          n++;
        }
      }
    }
  }
  sortAlphabetic(teams,n);
  printf("%d Melhores %d\n",line,max);
  for(i=0;i<n;i++){
    printf("%d * %s\n",line,teams[i]);
  }
  for(i=0;i<500;i++){
    free(teams[i]);
  }
  free(teams);
}

void comando_r(char* input,struct game** hash_games,struct game** lastGame,struct game** firstGame){
  struct game* g;
  if(gameExists(input,hash_games)==-1){
    printf("%d Jogo inexistente.\n",line);
    return;
  }
  for(g=hash_games[hash(input)]; g != NULL; g = g->nextHash){
    if(strcmp(input,g->name)==0){
      removeGame(g,hash_games,lastGame,firstGame);
      return;
    }
  }
}

/*funcao que vai libertar o programa todo*/
void comando_x(struct game** hash_games,struct team** hash_teams,struct game* firstGame){
  struct game* g;
  struct game* g1;
  if(firstGame != NULL){
    g = firstGame;
    while(g!=NULL){
      g1 = g->nextGeral;
      freeGame(g);
      g = g1;
    }
  }
  free(hash_games);
  deleteHashTeams(hash_teams);
}


int main(){
  char* control = malloc(sizeof(char)*6);
  char* input = malloc(sizeof(char)* MAXINPUT * 3);
  int end;
  struct game** hash_games = malloc(sizeof(struct game*)*HASHSIZE);
  struct team** hash_teams = malloc(sizeof(struct team*)*HASHSIZE);
  struct game* lastGame;
  struct game* firstGame;
  lastGame = NULL;
  firstGame = NULL;
  init_hash_games(hash_games);
  init_hash_teams(hash_teams);
  end = 0;
  while(end == 0){
    scanf("%s",control);
    switch (*control) {
      case 'a':
        line++;
        comando_a(hash_games,hash_teams,&lastGame,&firstGame);
        break;
      case 'A':
        line++;
        scanf(" %[^:\n]",input);
        comando_A(input,hash_teams);
        break;
      case 'l':
        line++;
        comando_l(&firstGame);
        break;
      case 'p':
        line++;
        scanf(" %[^:\n]",input);
        comando_p(input,hash_games);
        break;
      case 's':
        line++;
        comando_s(hash_games);
        break;
      case 'P':
        line++;
        scanf(" %[^:\n]",input);
        comando_P(input,hash_teams);
        break;
      case 'g':
        line++;
        comando_g(hash_teams);
        break;
      case 'r':
        line++;
        scanf(" %[^:\n]",input);
        comando_r(input,hash_games,&lastGame,&firstGame);
        break;
      case 'x':
        comando_x(hash_games,hash_teams,firstGame);
        free(input);
        free(control);
        end = 1;
        return 0;
        break;
    }
  }
  return 0;
}
