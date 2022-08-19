/*File generated by PreProcessor.py*/


#include "estruturas.h"


jogo *createGame(char *nome, char *equipa1, char *equipa2)
{
  jogo *game = malloc(sizeof(struct jogo));
  if (game == 0)
  {
    {
      return 0;
    }
  }
  else
  {
    
  }

  game->nome = malloc((strlen(nome) + 1) * (sizeof(char)));
  if (game->nome == 0)
  {
    {
      free(game);
      return 0;
    }
  }
  else
  {
    
  }

  game->equipa1 = malloc((strlen(equipa1) + 1) * (sizeof(char)));
  if (game->equipa1 == 0)
  {
    {
      free(game->nome);
      free(game);
      return 0;
    }
  }
  else
  {
    
  }

  game->equipa2 = malloc((strlen(equipa2) + 1) * (sizeof(char)));
  if (game->equipa2 == 0)
  {
    {
      free(game->equipa1);
      free(game->nome);
      free(game);
      return 0;
    }
  }
  else
  {
    
  }

  return game;
}

void freeGame(jogo *game)
{
  free(game->equipa1);
  free(game->equipa2);
  free(game->nome);
  free(game);
}

equipa *criaEquipa(char *nome)
{
  equipa *team = malloc(sizeof(struct equipa));
  if (team == 0)
  {
    {
      return 0;
    }
  }
  else
  {
    
  }

  team->nome = malloc((strlen(nome) + 1) * (sizeof(char)));
  if (team->nome == 0)
  {
    {
      free(team);
      return 0;
    }
  }
  else
  {
    
  }

  return team;
}

void freeEquipa(equipa *team)
{
  free(team->nome);
  free(team);
}

void freeDataStructures(ListNode *headGameslist, ListNode *headTeamList, hashtable *jogos, hashtable *equipas)
{
  free_dlistJogo(headGameslist);
  free_dlistEquipa(headTeamList);
  freeHashtable(jogos);
  freeHashtable(equipas);
}

void command_a(int inputLine, char *nome, char *equipa1, char *equipa2, int _score1, int _score2, ListNode **head_ref, hashtable *jogos, hashtable *equipas)
{
  ListNode *p;
  jogo *game;
  if (hashtableGet(jogos, nome) != 0)
  {
    {
      printf("%d Jogo existente.\n", inputLine);
      return;
    }
  }
  else
  {
    
  }

  if (hashtableGet(equipas, equipa1) == 0)
  {
    {
      printf("%d Equipa inexistente.\n", inputLine);
      return;
    }
  }
  else
  {
    
  }

  if (hashtableGet(equipas, equipa2) == 0)
  {
    {
      printf("%d Equipa inexistente.\n", inputLine);
      return;
    }
  }
  else
  {
    
  }

  game = createGame(nome, equipa1, equipa2);
  strcpy(game->nome, nome);
  strcpy(game->equipa1, equipa1);
  strcpy(game->equipa2, equipa2);
  game->score1 = _score1;
  game->score2 = _score2;
  p = push(head_ref, game);
  hashtableAdd(jogos, nome, p);
  if (_score1 > _score2)
  {
    {
      ((equipa *) ((ListNode *) hashtableGet(equipas, equipa1))->structPointer)->jogosGanhos++;
      return;
    }
  }
  else
  {
    
  }

  if (_score1 < _score2)
  {
    {
      ((equipa *) ((ListNode *) hashtableGet(equipas, equipa2))->structPointer)->jogosGanhos++;
    }
  }
  else
  {
    
  }

}

void command_l(int inputLine, ListNode *tail)
{
  printList(tail, inputLine);
}

void command_p(int inputLine, char *nome, hashtable *jogos)
{
  ListNode *p = hashtableGet(jogos, nome);
  if (p == 0)
  {
    {
      printf("%d Jogo inexistente.\n", inputLine);
      return;
    }
  }
  else
  {
    
  }

  printNodeJogo(p, inputLine);
}

void command_r(int inputLine, char *nome, hashtable *jogos, hashtable *equipas, ListNode **head_ref, ListNode **tail_ref)
{
  ListNode *p = hashtableGet(jogos, nome);
  char team[1024];
  if (p == 0)
  {
    {
      printf("%d Jogo inexistente.\n", inputLine);
      return;
    }
  }
  else
  {
    
  }

  if (winningTeam(p) != 0)
  {
    {
      strcpy(team, winningTeam(p));
      ((equipa *) ((ListNode *) hashtableGet(equipas, team))->structPointer)->jogosGanhos--;
    }
  }
  else
  {
    
  }

  freeGame((jogo *) p->structPointer);
  deleteListNode(head_ref, tail_ref, p);
  hashtableDel(jogos, nome);
}

void command_s(int inputLine, char *nome, int _score1, int _score2, hashtable *jogos, hashtable *equipas)
{
  ListNode *p = hashtableGet(jogos, nome);
  ListNode *equipa1;
  ListNode *equipa2;
  int result;
  if (p == 0)
  {
    {
      printf("%d Jogo inexistente.\n", inputLine);
      return;
    }
  }
  else
  {
    
  }

  result = changeScore(p, _score1, _score2);
  equipa1 = hashtableGet(equipas, ((jogo *) p->structPointer)->equipa1);
  equipa2 = hashtableGet(equipas, ((jogo *) p->structPointer)->equipa2);
  switch (result)
  {
    case 1:
      ((equipa *) equipa1->structPointer)->jogosGanhos++;
      ((equipa *) equipa2->structPointer)->jogosGanhos--;
      break;

    case 2:
      ((equipa *) equipa1->structPointer)->jogosGanhos--;
      ((equipa *) equipa2->structPointer)->jogosGanhos++;
      break;

    case 3:
      ((equipa *) equipa1->structPointer)->jogosGanhos++;
      break;

    case 4:
      ((equipa *) equipa2->structPointer)->jogosGanhos++;
      break;

    case 5:
      ((equipa *) equipa1->structPointer)->jogosGanhos--;
      break;

    case 6:
      ((equipa *) equipa2->structPointer)->jogosGanhos--;
      break;

  }

}

void command_A(int inputLine, char *nome, ListNode **head_ref, hashtable *equipas)
{
  equipa *team;
  ListNode *p;
  if (hashtableGet(equipas, nome) != 0)
  {
    {
      printf("%d Equipa existente.\n", inputLine);
      return;
    }
  }
  else
  {
    
  }

  team = criaEquipa(nome);
  strcpy(team->nome, nome);
  team->jogosGanhos = 0;
  p = push(head_ref, team);
  hashtableAdd(equipas, nome, p);
}

void command_P(int inputLine, char *nome, hashtable *equipas)
{
  ListNode *p = hashtableGet(equipas, nome);
  if (p == 0)
  {
    {
      printf("%d Equipa inexistente.\n", inputLine);
      return;
    }
  }
  else
  {
    
  }

  printNodeEquipa(p, inputLine);
}

void command_g(int inputLine, ListNode **head_ref)
{
  ListNode *bestTeams = 0;
  ListNode *current = 0;
  int max = 0;
  current = *head_ref;
  while (current != 0)
  {
    if (((equipa *) current->structPointer)->jogosGanhos > max)
    {
      {
        max = ((equipa *) current->structPointer)->jogosGanhos;
      }
    }
    else
    {
      
    }

    current = current->next;
  }

  current = *head_ref;
  while (current != 0)
  {
    if (((equipa *) current->structPointer)->jogosGanhos == max)
    {
      {
        push(&bestTeams, (equipa *) current->structPointer);
      }
    }
    else
    {
      
    }

    current = current->next;
  }

  mergeSort(&bestTeams);
  printBestTeams(&bestTeams, inputLine);
  free_dlist(bestTeams);
}

int main()
{
  int inputLine = 0;
  char line[3078];
  char token;
  char name[3078];
  char nomeJogo[1024];
  char equipa1[1024];
  char equipa2[1024];
  int score1;
  int score2;
  ListNode *headGameslist = 0;
  ListNode *tailGamesList = 0;
  ListNode *headTeamList = 0;
  hashtable *jogos = hashtableCreate();
  hashtable *equipas = hashtableCreate();
  while (fgets(line, (sizeof(line)) / (sizeof(char)), stdin))
  {
    token = new_sym_var(sizeof(char) * 8);
    for (int name_index = 0; name_index < 10; name_index++)
    {
      name[name_index] = new_sym_var(sizeof(char) * 8);
    }

    name[10 - 1] = '\0';
    inputLine++;
    if (token == 'x')
    {
      break;
    }
    else
    {
      
    }

    switch (token)
    {
      case 'a':
        for (int nomeJogo_index = 0; nomeJogo_index < 10; nomeJogo_index++)
      {
        nomeJogo[nomeJogo_index] = new_sym_var(sizeof(char) * 8);
      }

        nomeJogo[10 - 1] = '\0';
        for (int equipa1_index = 0; equipa1_index < 10; equipa1_index++)
      {
        equipa1[equipa1_index] = new_sym_var(sizeof(char) * 8);
      }

        equipa1[10 - 1] = '\0';
        for (int equipa2_index = 0; equipa2_index < 10; equipa2_index++)
      {
        equipa2[equipa2_index] = new_sym_var(sizeof(char) * 8);
      }

        equipa2[10 - 1] = '\0';
        score1 = new_sym_var(sizeof(int) * 8);
        score2 = new_sym_var(sizeof(int) * 8);
        command_a(inputLine, nomeJogo, equipa1, equipa2, score1, score2, &headGameslist, jogos, equipas);
        if (tailGamesList == 0)
      {
        {
          tailGamesList = headGameslist;
        }
      }
      else
      {
        
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
        command_r(inputLine, nomeJogo, jogos, equipas, &headGameslist, &tailGamesList);
        break;

      case 's':
        for (int nomeJogo_index = 0; nomeJogo_index < 10; nomeJogo_index++)
      {
        nomeJogo[nomeJogo_index] = new_sym_var(sizeof(char) * 8);
      }

        nomeJogo[10 - 1] = '\0';
        score1 = new_sym_var(sizeof(int) * 8);
        score2 = new_sym_var(sizeof(int) * 8);
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
