#include "estruturas.h"

/* Aloca a memoria necessaria para um jogo, criando-o*/
jogo* createGame(char* nome, char* equipa1, char* equipa2) {
  jogo* game = malloc(sizeof(struct jogo));
  if(game == NULL) {
    return NULL;
  }
  game->nome = malloc((strlen(nome)+1) * sizeof(char));
  if(game->nome == NULL) {
    free(game);
    return NULL;
  }
  game->equipa1 = malloc((strlen(equipa1)+1) * sizeof(char));
  if(game->equipa1 == NULL) {
    free(game->nome);
    free(game);
    return NULL;
  }
  game->equipa2 = malloc((strlen(equipa2)+1) * sizeof(char));
  if(game->equipa2 == NULL) {
    free(game->equipa1);
    free(game->nome);
    free(game);
    return NULL;
  }
  return game;
}

/* Da free de um jogo */
void freeGame(jogo* game ) {
  free(game->equipa1);
  free(game->equipa2);
  free(game->nome);
  free(game);
}

/* Aloca a memoria necessaria para uma equipa, criando-a*/
equipa* criaEquipa(char* nome) {
  equipa * team = malloc(sizeof(struct equipa));
  if(team == NULL){
    return NULL;
  }
  team->nome = malloc((strlen(nome)+1) * sizeof(char));
  if(team->nome == NULL) {
    free(team);
    return NULL;
  }
  return team;
}

void freeEquipa(equipa* team) {
  free(team->nome);
  free(team);
}

/* Da free de uma equipa */
void freeDataStructures(ListNode * headGameslist,
  ListNode * headTeamList,hashtable * jogos, hashtable * equipas) {

  free_dlistJogo(headGameslist);
  free_dlistEquipa(headTeamList);
  freeHashtable(jogos);
  freeHashtable(equipas);
}
/* Adiciono um novo jogo ao sistema */
void command_a(int inputLine, char* nome, char* equipa1,
  char* equipa2, int _score1, int _score2,
  ListNode** head_ref, hashtable * jogos, hashtable * equipas) {

  ListNode *p ;
  jogo* game;

  if(hashtableGet(jogos, nome) != NULL) {
    printf("%d Jogo existente.\n", inputLine);
    return;
  }
  if(hashtableGet(equipas, equipa1) == NULL) {
    printf("%d Equipa inexistente.\n", inputLine);
    return;
  }
  if(hashtableGet(equipas, equipa2) == NULL) {
    printf("%d Equipa inexistente.\n", inputLine);
    return;
  }

  game = createGame(nome, equipa1, equipa2);
  strcpy(game->nome, nome);
  strcpy(game->equipa1, equipa1);
  strcpy(game->equipa2, equipa2);
  game->score1 = _score1;
  game->score2 = _score2;

  p = push(head_ref, game);
  hashtableAdd(jogos, nome, p);
  if(_score1 > _score2) {
    ((equipa *)(((ListNode *)hashtableGet(equipas,
      equipa1))->structPointer))->jogosGanhos++;
    return;
  }
  if(_score1 < _score2) {
    ((equipa *)(((ListNode *)hashtableGet(equipas,
      equipa2))->structPointer))->jogosGanhos++;
  }
}

/* Lista todos os jogos por ordem de insercao */
void command_l(int inputLine, ListNode* tail) {
  printList(tail, inputLine);
}

/* Procura e imprime as informacoes relevantes sobre determinado jogo */
void command_p(int inputLine, char* nome, hashtable * jogos) {
  ListNode* p = hashtableGet(jogos, nome);
  if(p == NULL){
    printf("%d Jogo inexistente.\n",inputLine);
    return;
  }
  printNodeJogo(p, inputLine);
}

/* Remove do sistema um jogo */
void command_r(int inputLine, char* nome, hashtable * jogos,
  hashtable * equipas, ListNode ** head_ref, ListNode ** tail_ref) {

  ListNode* p = hashtableGet(jogos, nome);
  char team[MAX_SIZE];

  if(p == NULL){
    printf("%d Jogo inexistente.\n",inputLine);
    return;
  }
  if(winningTeam(p)!=NULL) {
    strcpy(team, winningTeam(p));
    ((equipa *)(((ListNode *)hashtableGet(equipas,
      team))->structPointer))->jogosGanhos--;
  }
  freeGame(((jogo*)(p->structPointer)));
  deleteListNode(head_ref, tail_ref, p);
  hashtableDel(jogos, nome);
}

/* Muda o score de um determinado jogo */
void command_s(int inputLine, char* nome, int _score1,
   int _score2, hashtable * jogos, hashtable * equipas) {

  ListNode* p = hashtableGet(jogos, nome);
  ListNode* equipa1;
  ListNode* equipa2;
  int result;
  if(p == NULL){
    printf("%d Jogo inexistente.\n",inputLine);
    return;
  }
  result = changeScore(p, _score1, _score2);
  equipa1 = hashtableGet(equipas,((jogo *)(p->structPointer))->equipa1);
  equipa2 = hashtableGet(equipas,((jogo *)(p->structPointer))->equipa2);
  switch (result) {
    case 1:
      ((equipa *)(equipa1->structPointer))->jogosGanhos++;
      ((equipa *)(equipa2->structPointer))->jogosGanhos--;
      break;
    case 2:
      ((equipa *)(equipa1->structPointer))->jogosGanhos--;
      ((equipa *)(equipa2->structPointer))->jogosGanhos++;
      break;
    case 3:
      ((equipa *)(equipa1->structPointer))->jogosGanhos++;
      break;
    case 4:
      ((equipa *)(equipa2->structPointer))->jogosGanhos++;
      break;
    case 5:
      ((equipa *)(equipa1->structPointer))->jogosGanhos--;
      break;
    case 6:
      ((equipa *)(equipa2->structPointer))->jogosGanhos--;
      break;
  }
}

/* Adiciona uma equipa ao sistema */
void command_A(int inputLine, char* nome,
   ListNode ** head_ref, hashtable * equipas) {

  equipa* team;
  ListNode * p;

  if(hashtableGet(equipas, nome) != NULL) {
    printf("%d Equipa existente.\n", inputLine);
    return;
  }

  team = criaEquipa(nome);

  strcpy(team->nome,nome);
  team->jogosGanhos = 0;
  p = push(head_ref, team);
  hashtableAdd(equipas,nome,p);
}

/* Procura uma equipa no sistema e imprime as informacoes relevantes */
void command_P(int inputLine, char* nome, hashtable * equipas) {
  ListNode* p = hashtableGet(equipas, nome);
  if(p == NULL){
    printf("%d Equipa inexistente.\n",inputLine);
    return;
  }
  printNodeEquipa(p, inputLine);
 }

/* Imprime as equipas com maior numero de jogos ganhos */
void command_g(int inputLine, ListNode ** head_ref) {
  ListNode * bestTeams = NULL;
  ListNode * current = NULL;
  int max = 0;
  current = *head_ref;


  while(current !=NULL){
    if(((equipa *)(current->structPointer))->jogosGanhos > max) {
      max = ((equipa *)(current->structPointer))->jogosGanhos;
    }
    current = current->next;
  }

  current = *head_ref;

  while(current !=NULL){
    if(((equipa *)(current->structPointer))->jogosGanhos == max){
      push(&bestTeams,((equipa *)(current->structPointer)));
    }
    current=current->next;
  }
  mergeSort(&bestTeams);
  printBestTeams(&bestTeams, inputLine);
  free_dlist(bestTeams);
}

int main() {
  int inputLine=0;
  char line[MAX_INPUT_SIZE];
  char token;
  char name[MAX_INPUT_SIZE];
  char nomeJogo[MAX_SIZE];
  char equipa1[MAX_SIZE];
  char equipa2[MAX_SIZE];
  int score1;
  int score2;

  ListNode *headGameslist= NULL;
  ListNode *tailGamesList = NULL;
  ListNode *headTeamList = NULL;
  hashtable *jogos = hashtableCreate();
  hashtable *equipas = hashtableCreate();
  while (fgets(line, sizeof(line) / sizeof(char), stdin)) {

    sscanf(line, "%c %[^\n]", & token, name);
    inputLine++;
    if (token == 'x') break;

    switch (token) {
    case 'a':
      sscanf( name,"%[^:\n]:%[^:\n]:%[^:\n]:%d:%d",nomeJogo,
        equipa1,equipa2,&score1,&score2);

      command_a(inputLine, nomeJogo, equipa1, equipa2,
         score1, score2, &headGameslist, jogos, equipas);

      if(tailGamesList == NULL){
        tailGamesList = headGameslist;
      }
      break;
    case 'l':
      command_l(inputLine, tailGamesList);
      break;
    case 'p':
      strcpy(nomeJogo, name);
      command_p(inputLine, nomeJogo, jogos);
      break;
    case 'r':
      strcpy(nomeJogo, name);
      command_r(inputLine, nomeJogo, jogos,
        equipas, &headGameslist, &tailGamesList);
      break;
    case 's':
      sscanf( name,"%[^:\n]:%d:%d",nomeJogo,&score1,&score2);
      command_s(inputLine, nomeJogo, score1, score2, jogos, equipas);
      break;
    case 'A':
      strcpy(equipa1, name);
      command_A(inputLine, equipa1, &headTeamList, equipas);
      break;
    case 'P':
      strcpy(equipa1, name);
      command_P(inputLine, equipa1, equipas);
      break;
    case 'g':
      command_g(inputLine, &headTeamList);
      break;
    }
  }
  freeDataStructures(headGameslist, headTeamList, jogos, equipas);
  return 0;
}
