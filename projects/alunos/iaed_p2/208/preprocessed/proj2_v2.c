#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct 
{
  char *_nome_;
  char *_equipaA_;
  char *_equipaB_;
  int *_scoreA_;
  int *_scoreB_;
} Jogo;
typedef struct node
{
  struct node *next;
  Jogo *_jogo_;
} *link_lst;
typedef struct _node
{
  struct _node *next;
  char *teamName;
  int *gamesWon;
} *team_lst;
typedef struct _node_
{
  struct _node_ *next;
  char *gameName;
} *game_lst;
static link_lst *heads;
static int M;
static team_lst teamHead = 0;
static game_lst gameHead;
static int lineNumber = 1;
int numGamesWon[1024];
int teamNumber = 0;
int firstTeam = 0;
int firstGame = 0;
int hash(char *name, int M);
void hashInit(int m);
Jogo *hashSearch(char *nome);
Jogo *hashSearchTeam(char *game_name, char *team_name);
void hashInsert(Jogo *j);
int hashDelete(char *nome);
void hashDestroy();
link_lst link_list_pop(link_lst head);
link_lst link_list_push(link_lst head, Jogo *j);
Jogo *link_list_search(link_lst head, char *nm);
Jogo *link_list_searchTeam(link_lst head, char *team_name);
int link_list_delete(link_lst head, char *nm);
link_lst link_list_destroy(link_lst head);
void link_list_print(link_lst head);
void team_lst_init();
char *team_lst_search(char *team);
int *team_lst_searchGamesWon(char *team);
void team_lst_gamesWon_increment(char *team);
void team_lst_gamesWon_decrement(char *team);
void team_lst_destroy();
void game_lst_init();
void game_lst_push(char *game_name, size_t len_name);
void game_lst_destroy();
int adicionaJogo();
void listaJogos();
void adicionaEquipa();
void procuraJogo();
void apagaJogo();
void alteraScore();
void procuraEquipa();
void imprimeEquipascomMaisVitorias();
char *readStdin();
Jogo *mallocJogo();
void sortList(team_lst headT);
void swap(team_lst a, team_lst b, size_t len);
void aux_lst_destroy(team_lst head);
int aux_str_cmp(char *a, char *b);
int main()
{
  char comando;
  hashInit(10);
  game_lst_init();
  while (1)
  {
    comando = getchar();
    switch (comando)
    {
      case 'a':
        adicionaJogo();
        lineNumber++;
        break;

      case 'l':
        listaJogos();
        lineNumber++;
        break;

      case 'A':
        adicionaEquipa();
        lineNumber++;
        firstTeam = 1;
        break;

      case 'P':
        procuraEquipa();
        lineNumber++;
        break;

      case 'p':
        procuraJogo();
        lineNumber++;
        break;

      case 'r':
        apagaJogo();
        lineNumber++;
        break;

      case 's':
        alteraScore();
        lineNumber++;
        break;

      case 'g':
        imprimeEquipascomMaisVitorias();
        lineNumber++;
        break;

      case 'x':
        team_lst_destroy(teamHead);
        game_lst_destroy();
        hashDestroy();
        return 0;

    }

  }

  return 0;
}

void hashInit(int m)
{
  int i;
  M = m;
  heads = malloc(M * (sizeof(link_lst)));
  for (i = 0; i < M; i++)
  {
    heads[i] = 0;
  }

}

int hash(char *name, int M)
{
  int h = 0;
  int a = 127;
  for (; (*name) != '\0'; name++)
  {
    h = (a * h) % M;
  }

  return h;
}

void hashInsert(Jogo *j)
{
  int i = hash(j->_nome_, M);
  heads[i] = link_list_push(heads[i], j);
}

int hashDelete(char *nome)
{
  int i = hash(nome, M);
  return link_list_delete(heads[i], nome);
}

Jogo *hashSearch(char *nome)
{
  int i = hash(nome, M);
  return link_list_search(heads[i], nome);
}

Jogo *hashSearchTeam(char *game_name, char *team_name)
{
  int i = hash(game_name, M);
  return link_list_searchTeam(heads[i], team_name);
}

void hashDestroy()
{
  int i;
  for (i = 0; i < M; i++)
  {
    link_list_destroy(heads[i]);
  }

  free(heads);
}

link_lst link_list_pop(link_lst head)
{
  link_lst node_m;
  if (head == 0)
  {
    printf("List empty couldnt remove item");
  }
  else
  {
    node_m = head->next;
    node_m->_jogo_ = head->next->_jogo_;
    free(head);
    head = node_m;
  }

  return head;
}

link_lst link_list_push(link_lst head, Jogo *j)
{
  link_lst new_node;
  new_node = (link_lst) malloc(sizeof(struct node));
  new_node->_jogo_ = j;
  new_node->next = head;
  head = new_node;
  return head;
}

Jogo *link_list_search(link_lst head, char *nm)
{
  link_lst current = head;
  while (current != 0)
  {
    if (strcmp(current->_jogo_->_nome_, nm) == 0)
    {
      return current->_jogo_;
    }
    else
    {
      current = current->next;
    }

  }

  return 0;
}

Jogo *link_list_searchTeam(link_lst head, char *team_name)
{
  link_lst current = head;
  while (current != 0)
  {
    if ((strcmp(current->_jogo_->_equipaA_, team_name) == 0) || (strcmp(current->_jogo_->_equipaB_, team_name) == 0))
    {
      return current->_jogo_;
    }
    else
    {
      current = current->next;
    }

  }

  return 0;
}

int link_list_delete(link_lst head, char *nm)
{
  link_lst current = head;
  link_lst tempNode = 0;
  if (head != 0)
  {
    if (strcmp(head->_jogo_->_nome_, nm) == 0)
    {
      if ((*head->_jogo_->_scoreA_) > (*head->_jogo_->_scoreB_))
      {
        team_lst_gamesWon_decrement(head->_jogo_->_equipaA_);
      }
      else
      {
        
      }

      if ((*head->_jogo_->_scoreB_) > (*head->_jogo_->_scoreA_))
      {
        team_lst_gamesWon_decrement(head->_jogo_->_equipaB_);
      }
      else
      {
        
      }

      tempNode = head;
      head = head->next;
      free(tempNode->_jogo_->_nome_);
      free(tempNode->_jogo_->_equipaA_);
      free(tempNode->_jogo_->_equipaB_);
      free(tempNode->_jogo_->_scoreA_);
      free(tempNode->_jogo_->_scoreB_);
      free(tempNode->_jogo_);
      free(tempNode);
      return 1;
    }
    else
    {
      
    }

  }
  else
  {
    
  }

  while (current != 0)
  {
    if (current->next != 0)
    {
      if (strcmp(current->next->_jogo_->_nome_, nm) == 0)
      {
        if ((*current->next->_jogo_->_scoreA_) > (*current->next->_jogo_->_scoreB_))
        {
          team_lst_gamesWon_decrement(current->next->_jogo_->_equipaA_);
        }
        else
        {
          
        }

        if ((*current->next->_jogo_->_scoreB_) > (*current->next->_jogo_->_scoreA_))
        {
          team_lst_gamesWon_decrement(current->next->_jogo_->_equipaB_);
        }
        else
        {
          
        }

        tempNode = current->next;
        current->next = tempNode->next;
        free(tempNode->_jogo_->_nome_);
        free(tempNode->_jogo_->_equipaA_);
        free(tempNode->_jogo_->_equipaB_);
        free(tempNode->_jogo_->_scoreA_);
        free(tempNode->_jogo_->_scoreB_);
        free(tempNode->_jogo_);
        free(tempNode);
        return 1;
      }
      else
      {
        
      }

    }
    else
    {
      
    }

    current = current->next;
  }

  return 0;
}

link_lst link_list_destroy(link_lst head)
{
  link_lst current;
  while (head != 0)
  {
    current = head;
    head = head->next;
    free(current->_jogo_->_nome_);
    free(current->_jogo_->_equipaA_);
    free(current->_jogo_->_equipaB_);
    free(current->_jogo_->_scoreA_);
    free(current->_jogo_->_scoreB_);
    free(current->_jogo_);
    free(current);
  }

  return head;
}

void link_list_print(link_lst head)
{
  int counter = 0;
  link_lst current = head;
  while (current != 0)
  {
    counter++;
    printf("%d : %s\n", counter, current->_jogo_->_nome_);
    current = current->next;
  }

}

void team_lst_init()
{
  teamHead = (team_lst) malloc(sizeof(struct _node));
  teamHead->teamName = (char *) malloc(1024 * (sizeof(char)));
  teamHead->gamesWon = (int *) malloc(sizeof(int));
  strcpy(teamHead->teamName, "?");
  *teamHead->gamesWon = 0;
  teamHead->next = 0;
}

char *team_lst_search(char *team)
{
  team_lst current = teamHead;
  while (current != 0)
  {
    if (strcmp(current->teamName, team) == 0)
    {
      return current->teamName;
    }
    else
    {
      
    }

    current = current->next;
  }

  return 0;
}

int *team_lst_searchGamesWon(char *team)
{
  team_lst current = teamHead;
  while (current != 0)
  {
    if (strcmp(current->teamName, team) == 0)
    {
      return current->gamesWon;
    }
    else
    {
      
    }

    current = current->next;
  }

  return 0;
}

void team_lst_gamesWon_increment(char *team)
{
  team_lst current = teamHead;
  while (current != 0)
  {
    if (strcmp(current->teamName, team) == 0)
    {
      (*current->gamesWon)++;
    }
    else
    {
      
    }

    current = current->next;
  }

}

void team_lst_gamesWon_decrement(char *team)
{
  team_lst current = teamHead;
  while (current != 0)
  {
    if (strcmp(current->teamName, team) == 0)
    {
      (*current->gamesWon)--;
    }
    else
    {
      
    }

    current = current->next;
  }

}

void team_lst_destroy()
{
  team_lst current = teamHead;
  while (teamHead != 0)
  {
    current = teamHead;
    teamHead = teamHead->next;
    free(current->teamName);
    free(current->gamesWon);
    free(current);
  }

}

void game_lst_init()
{
  gameHead = (game_lst) malloc(sizeof(struct _node_));
  gameHead->gameName = (char *) malloc(1024 * (sizeof(char)));
  gameHead->next = 0;
}

void game_lst_push(char *game_name, size_t len_name)
{
  game_lst current = gameHead;
  while (current->next != 0)
  {
    current = current->next;
  }

  current->next = malloc(sizeof(struct _node_));
  current->next->gameName = (char *) malloc((len_name + 1) * (sizeof(char)));
  strcpy(current->next->gameName, game_name);
  current->next->next = 0;
}

void game_lst_destroy()
{
  game_lst current = gameHead;
  while (gameHead != 0)
  {
    current = gameHead;
    gameHead = gameHead->next;
    free(current->gameName);
    free(current);
  }

}

int adicionaJogo()
{
  char *token;
  char *input;
  const char delim[4] = ":";
  size_t length = 0;
  int counter = 0;
  int controlTAbit = 0;
  int controlTBbit = 0;
  int controlNbit = 0;
  Jogo *novoJogo = mallocJogo();
  input = readStdin();
  token = strtok(input, delim);
  while (token != 0)
  {
    if (counter == 0)
    {
      if (hashSearch(token) == 0)
      {
        length = strlen(token);
        if (firstGame == 0)
        {
          gameHead->gameName = realloc(gameHead->gameName, (length + 1) * (sizeof(char)));
          firstGame = 1;
        }
        else
        {
          
        }

        game_lst_push(token, length);
        novoJogo->_nome_ = (char *) realloc(novoJogo->_nome_, (length + 1) * (sizeof(char)));
        strcpy(novoJogo->_nome_, token);
        controlNbit = 1;
      }
      else
      {
        printf("%d Jogo existente.\n", lineNumber);
        break;
      }

    }
    else
    {
      
    }

    if (counter == 1)
    {
      if (team_lst_search(token) != 0)
      {
        length = strlen(token);
        novoJogo->_equipaA_ = (char *) realloc(novoJogo->_equipaA_, (length + 1) * (sizeof(char)));
        strcpy(novoJogo->_equipaA_, token);
        controlTAbit = 1;
      }
      else
      {
        printf("%d Equipa inexistente.\n", lineNumber);
        break;
      }

    }
    else
    {
      
    }

    if (counter == 2)
    {
      if (team_lst_search(token) != 0)
      {
        length = strlen(token);
        novoJogo->_equipaB_ = (char *) realloc(novoJogo->_equipaB_, (length + 1) * (sizeof(char)));
        strcpy(novoJogo->_equipaB_, token);
        controlTBbit = 1;
      }
      else
      {
        printf("%d Equipa inexistente.\n", lineNumber);
        break;
      }

    }
    else
    {
      
    }

    if (counter == 3)
    {
      for (int novoJogo_index = 0; novoJogo_index < 10; novoJogo_index++)
      {
        novoJogo->_scoreA_[novoJogo_index] = new_sym_var(sizeof(int) * 8);
      }

    }
    else
    {
      
    }

    if (counter == 4)
    {
      for (int novoJogo_index = 0; novoJogo_index < 10; novoJogo_index++)
      {
        novoJogo->_scoreB_[novoJogo_index] = new_sym_var(sizeof(int) * 8);
      }

    }
    else
    {
      
    }

    counter++;
    token = strtok(0, delim);
  }

  if (((controlTAbit != 0) && (controlTBbit != 0)) && (controlNbit != 0))
  {
    if ((*novoJogo->_scoreA_) > (*novoJogo->_scoreB_))
    {
      team_lst_gamesWon_increment(novoJogo->_equipaA_);
    }
    else
    {
      
    }

    if ((*novoJogo->_scoreB_) > (*novoJogo->_scoreA_))
    {
      team_lst_gamesWon_increment(novoJogo->_equipaB_);
    }
    else
    {
      
    }

    hashInsert(novoJogo);
  }
  else
  {
    free(novoJogo->_nome_);
    free(novoJogo->_equipaA_);
    free(novoJogo->_equipaB_);
    free(novoJogo->_scoreA_);
    free(novoJogo->_scoreB_);
    free(novoJogo);
  }

  free(input);
  return 0;
}

void listaJogos()
{
  game_lst current = gameHead;
  Jogo *gameAux;
  while (current != 0)
  {
    if (firstGame == 0)
    {
      break;
    }
    else
    {
      gameAux = hashSearch(current->gameName);
      if (gameAux != 0)
      {
        printf("%d %s %s %s %d %d\n", lineNumber, gameAux->_nome_, gameAux->_equipaA_, gameAux->_equipaB_, *gameAux->_scoreA_, *gameAux->_scoreB_);
      }
      else
      {
        
      }

    }

    current = current->next;
  }

}

void adicionaEquipa()
{
  char *input;
  char *search_result;
  size_t len = 0;
  team_lst node;
  input = readStdin();
  len = strlen(input);
  search_result = team_lst_search(input);
  if (search_result != 0)
  {
    printf("%d Equipa existente.\n", lineNumber);
    free(input);
    return;
  }
  else
  {
    
  }

  node = (team_lst) malloc(sizeof(struct _node));
  node->teamName = malloc((len + 1) * (sizeof(char)));
  node->gamesWon = (int *) malloc(sizeof(int));
  strcpy(node->teamName, input);
  *node->gamesWon = 0;
  node->next = 0;
  if (teamHead == 0)
  {
    teamHead = node;
  }
  else
  {
    team_lst current = teamHead;
    while (current->next != 0)
    {
      current = current->next;
    }

    current->next = node;
  }

  free(input);
}

void procuraJogo()
{
  char *input;
  input = readStdin();
  if (hashSearch(input) != 0)
  {
    printf("%d %s %s %s %d %d\n", lineNumber, hashSearch(input)->_nome_, hashSearch(input)->_equipaA_, hashSearch(input)->_equipaB_, *hashSearch(input)->_scoreA_, *hashSearch(input)->_scoreB_);
  }
  else
  {
    printf("%d Jogo inexistente.\n", lineNumber);
  }

  free(input);
}

void apagaJogo()
{
  char *input;
  input = readStdin();
  if (hashDelete(input) == 0)
  {
    printf("%d Jogo inexistente.\n", lineNumber);
  }
  else
  {
    
  }

  free(input);
}

void alteraScore()
{
  char *input;
  char *token;
  int *scoreA = 0;
  int *scoreB = 0;
  const char delim[2] = ":";
  int counter = 0;
  Jogo *jogo;
  input = readStdin();
  token = strtok(input, delim);
  while (token != 0)
  {
    if (counter == 0)
    {
      jogo = hashSearch(token);
      if (jogo == 0)
      {
        printf("%d Jogo inexistente.\n", lineNumber);
        return;
      }
      else
      {
        
      }

    }
    else
    {
      
    }

    if (counter == 1)
    {
      for (int scoreA_index = 0; scoreA_index < 10; scoreA_index++)
      {
        scoreA[scoreA_index] = new_sym_var(sizeof(int) * 8);
      }

    }
    else
    {
      for (int scoreB_index = 0; scoreB_index < 10; scoreB_index++)
      {
        scoreB[scoreB_index] = new_sym_var(sizeof(int) * 8);
      }

    }

    counter++;
    token = strtok(0, delim);
  }

  if ((*jogo->_scoreA_) > (*jogo->_scoreB_))
  {
    team_lst_gamesWon_decrement(jogo->_equipaA_);
  }
  else
  {
    
  }

  if ((*jogo->_scoreB_) > (*jogo->_scoreA_))
  {
    team_lst_gamesWon_decrement(jogo->_equipaB_);
  }
  else
  {
    
  }

  *jogo->_scoreA_ = *scoreA;
  *jogo->_scoreB_ = *scoreB;
  if ((*jogo->_scoreA_) > (*jogo->_scoreB_))
  {
    team_lst_gamesWon_increment(jogo->_equipaA_);
  }
  else
  {
    
  }

  if ((*jogo->_scoreB_) > (*jogo->_scoreA_))
  {
    team_lst_gamesWon_increment(jogo->_equipaB_);
  }
  else
  {
    
  }

  free(input);
}

void procuraEquipa()
{
  char *input;
  input = readStdin();
  if (team_lst_search(input) != 0)
  {
    printf("%d %s %d\n", lineNumber, team_lst_search(input), *team_lst_searchGamesWon(team_lst_search(input)));
  }
  else
  {
    printf("%d Equipa inexistente.\n", lineNumber);
  }

  free(input);
}

void imprimeEquipascomMaisVitorias()
{
  int max = 0;
  int aux_helper = 0;
  size_t len = 0;
  team_lst currentTeam = teamHead;
  team_lst currentAux;
  team_lst finalCurrentAux;
  team_lst node;
  team_lst aux_lst_head = 0;
  while (currentTeam != 0)
  {
    if (max < (*currentTeam->gamesWon))
    {
      max = *currentTeam->gamesWon;
    }
    else
    {
      
    }

    currentTeam = currentTeam->next;
  }

  currentTeam = teamHead;
  while (currentTeam != 0)
  {
    if ((*currentTeam->gamesWon) == max)
    {
      len = strlen(currentTeam->teamName);
      node = (team_lst) malloc(sizeof(struct _node));
      node->teamName = (char *) malloc((len + 1) * (sizeof(char)));
      strcpy(node->teamName, currentTeam->teamName);
      node->gamesWon = (int *) malloc((sizeof(int)) * 2);
      *node->gamesWon = max;
      currentAux = aux_lst_head;
      aux_lst_head = node;
      node->next = currentAux;
    }
    else
    {
      
    }

    currentTeam = currentTeam->next;
  }

  finalCurrentAux = aux_lst_head;
  sortList(aux_lst_head);
  while (finalCurrentAux != 0)
  {
    if (aux_helper == 0)
    {
      printf("%d Melhores %d\n", lineNumber, max);
      aux_helper = 1;
    }
    else
    {
      
    }

    printf("%d * %s\n", lineNumber, finalCurrentAux->teamName);
    finalCurrentAux = finalCurrentAux->next;
  }

  aux_lst_destroy(aux_lst_head);
}

char *readStdin()
{
  size_t capacity = 4096;
  size_t length = 0;
  char *buffer = (char *) malloc(capacity * (sizeof(char)));
  int c;
  int ack = 0;
  while (((c = fgetc(stdin)) != '\n') && (!feof(stdin)))
  {
    if ((c == ' ') && (ack == 0))
    {
      ack = 1;
      continue;
    }
    else
    {
      
    }

    buffer[length] = c;
    if ((++length) == capacity)
    {
      buffer = realloc(buffer, (capacity * 2) * (sizeof(char)));
    }
    else
    {
      
    }

  }

  buffer = realloc(buffer, (length + 1) * (sizeof(char)));
  buffer[length] = '\0';
  return buffer;
}

Jogo *mallocJogo()
{
  Jogo *novoJogo = (Jogo *) malloc(sizeof(Jogo));
  novoJogo->_nome_ = (char *) malloc(1024 * (sizeof(char)));
  novoJogo->_equipaA_ = (char *) malloc(1024 * (sizeof(char)));
  novoJogo->_equipaB_ = (char *) malloc(1024 * (sizeof(char)));
  novoJogo->_scoreA_ = (int *) malloc((sizeof(int)) * 2);
  novoJogo->_scoreB_ = (int *) malloc((sizeof(int)) * 2);
  return novoJogo;
}

void sortList(team_lst headT)
{
  int swapped = 0;
  team_lst ptr1;
  team_lst lptr = 0;
  size_t len = 0;
  size_t len_next = 0;
  if ((headT == 0) || (headT->next == 0))
  {
    return;
  }
  else
  {
    
  }

  do
  {
    swapped = 0;
    ptr1 = headT->next;
    while ((ptr1->next != lptr) && (ptr1->next != 0))
    {
      if (aux_str_cmp(ptr1->teamName, ptr1->next->teamName) > 0)
      {
        len = strlen(ptr1->teamName);
        len_next = strlen(ptr1->next->teamName);
        if (len > len_next)
        {
          swap(ptr1, ptr1->next, len);
        }
        else
        {
          swap(ptr1, ptr1->next, len_next);
        }

        swapped = 1;
      }
      else
      {
        
      }

      ptr1 = ptr1->next;
    }

    lptr = ptr1;
  }
  while (swapped);
}

void swap(team_lst a, team_lst b, size_t len)
{
  char *team_name = malloc((len + 1) * (sizeof(char)));
  strcpy(team_name, a->teamName);
  strcpy(a->teamName, b->teamName);
  strcpy(b->teamName, team_name);
  free(team_name);
}

void aux_lst_destroy(team_lst head)
{
  team_lst current = head;
  while (head != 0)
  {
    current = head;
    head = head->next;
    free(current->teamName);
    free(current->gamesWon);
    free(current);
  }

}

int aux_str_cmp(char *a, char *b)
{
  int i;
  int n;
  size_t len = 0;
  len = strlen(a);
  if (len > strlen(b))
  {
    len = strlen(b);
  }
  else
  {
    
  }

  n = len;
  for (i = 0; i < n; i++)
  {
    if (tolower(a[i]) == tolower(b[i]))
    {
      continue;
    }
    else
    {
      
    }

    if (tolower(a[i]) > tolower(b[i]))
    {
      return 1;
    }
    else
    {
      
    }

  }

  return 0;
}

