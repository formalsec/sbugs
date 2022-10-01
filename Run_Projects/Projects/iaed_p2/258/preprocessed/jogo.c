/*File generated by PreProcessor.py*/


#include "jogo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int hashjogo(char nome[1024])
{
  int hash = 893478917;
  int n = 0;
  while (nome[n] != '\0')
  {
    hash *= nome[n];
    n++;
  }

  if (hash < 0)
  {
    return -hash;
  }
  else
  {
    return hash;
  }

}

void adicionajogo(struct TodosJogos *jogos, struct TodasEquipas *equipas, int num_comandos)
{
  struct Jogo *jogo;
  struct Jogo *jogo_cur;
  struct Equipa *equipa_cur;
  struct Equipa *equipa1 = 0;
  struct Equipa *equipa2 = 0;
  char nome[1024];
  int nome_len;
  char nome_e1[1024];
  char nome_e2[1024];
  int score1;
  int score2;
  int nomehash;
  int equipa1hash;
  int equipa2hash;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  for (int nome_e1_index = 0; nome_e1_index < 10; nome_e1_index++)
  {
    nome_e1[nome_e1_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_e1[10 - 1] = '\0';
  for (int nome_e2_index = 0; nome_e2_index < 10; nome_e2_index++)
  {
    nome_e2[nome_e2_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_e2[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  nomehash = hashjogo(nome) % 1000;
  equipa1hash = hashequipa(nome_e1) % 1000;
  equipa2hash = hashequipa(nome_e2) % 1000;
  jogo_cur = jogos->elementos[nomehash];
  while (jogo_cur != 0)
  {
    if (strcmp(nome, jogo_cur->nome) == 0)
    {
      printf("%d Jogo existente.\n", num_comandos);
      return;
    }
    else
    {
      
    }

    if (jogo_cur->next == 0)
    {
      break;
    }
    else
    {
      
    }

    jogo_cur = jogo_cur->next;
  }

  equipa_cur = equipas->elementos[equipa1hash];
  while (equipa_cur != 0)
  {
    if ((equipa1 == 0) && (strncmp(nome_e1, equipa_cur->nome, 1024) == 0))
    {
      equipa1 = equipa_cur;
      break;
    }
    else
    {
      
    }

    equipa_cur = equipa_cur->next;
  }

  equipa_cur = equipas->elementos[equipa2hash];
  while (equipa_cur != 0)
  {
    if ((equipa2 == 0) && (strncmp(nome_e2, equipa_cur->nome, 1024) == 0))
    {
      equipa2 = equipa_cur;
      break;
    }
    else
    {
      
    }

    equipa_cur = equipa_cur->next;
  }

  if ((equipa1 == 0) || (equipa2 == 0))
  {
    printf("%d Equipa inexistente.\n", num_comandos);
    return;
  }
  else
  {
    
  }

  jogo = malloc(1 * (sizeof(struct Jogo)));
  jogo->equipa1 = equipa1;
  jogo->equipa2 = equipa2;
  jogo->next = 0;
  jogo->score1 = score1;
  jogo->score2 = score2;
  nome_len = strlen(nome);
  jogo->nome = malloc(nome_len + 1);
  strcpy(jogo->nome, nome);
  if (score1 > score2)
  {
    equipa1->jogos_ganhos += 1;
  }
  else
  {
    if (score2 > score1)
    {
      equipa2->jogos_ganhos += 1;
    }
    else
    {
      
    }

  }

  if (jogo_cur == 0)
  {
    jogos->elementos[nomehash] = jogo;
  }
  else
  {
    jogo_cur->next = jogo;
  }

  jogos->vetor = realloc(jogos->vetor, (jogos->num_jogos + 1) * (sizeof(struct Jogo *)));
  jogos->vetor[jogos->num_jogos] = jogo;
  jogos->num_jogos += 1;
}

void listajogo(struct TodosJogos *jogos, int num_comandos)
{
  int n;
  for (n = 0; n < jogos->num_jogos; n++)
  {
    if (jogos->vetor[n] == 0)
    {
      continue;
    }
    else
    {
      
    }

    printf("%d %s %s %s %d %d\n", num_comandos, jogos->vetor[n]->nome, jogos->vetor[n]->equipa1->nome, jogos->vetor[n]->equipa2->nome, jogos->vetor[n]->score1, jogos->vetor[n]->score2);
  }

}

void apagajogo(struct TodosJogos *jogos, int num_comandos)
{
  struct Jogo *jogo_cur;
  struct Jogo *jogo_prev = 0;
  char nome[1024];
  int nomehash;
  int n;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  nomehash = hashjogo(nome) % 1000;
  jogo_cur = jogos->elementos[nomehash];
  while (jogo_cur != 0)
  {
    if (strcmp(nome, jogo_cur->nome) == 0)
    {
      if (jogo_cur->score1 > jogo_cur->score2)
      {
        jogo_cur->equipa1->jogos_ganhos -= 1;
      }
      else
      {
        
      }

      if (jogo_cur->score1 < jogo_cur->score2)
      {
        jogo_cur->equipa2->jogos_ganhos -= 1;
      }
      else
      {
        
      }

      if (jogo_prev == 0)
      {
        jogos->elementos[nomehash] = jogo_cur->next;
      }
      else
      {
        jogo_prev->next = jogo_cur->next;
      }

      for (n = 0; n < jogos->num_jogos; n++)
      {
        if (jogos->vetor[n] == jogo_cur)
        {
          jogos->vetor[n] = 0;
          break;
        }
        else
        {
          
        }

      }

      free(jogo_cur->nome);
      free(jogo_cur);
      return;
    }
    else
    {
      
    }

    jogo_prev = jogo_cur;
    jogo_cur = jogo_cur->next;
  }

  printf("%d Jogo inexistente.\n", num_comandos);
}

void procurajogo(struct TodosJogos *jogos, int num_comandos)
{
  struct Jogo *jogo;
  char nome[1024];
  int nomehash;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  nomehash = hashjogo(nome) % 1000;
  jogo = jogos->elementos[nomehash];
  while (jogo != 0)
  {
    if (strcmp(jogo->nome, nome) == 0)
    {
      printf("%d %s %s %s %d %d\n", num_comandos, jogo->nome, jogo->equipa1->nome, jogo->equipa2->nome, jogo->score1, jogo->score2);
      return;
    }
    else
    {
      
    }

    jogo = jogo->next;
  }

  printf("%d Jogo inexistente.\n", num_comandos);
}

void alterascore(struct TodosJogos *jogos, int num_comandos)
{
  struct Jogo *jogo;
  int score1;
  int score2;
  int nomehash;
  char nome[1024];
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  nomehash = hashjogo(nome) % 1000;
  jogo = jogos->elementos[nomehash];
  while (jogo != 0)
  {
    if (strcmp(jogo->nome, nome) == 0)
    {
      if (jogo->score1 > jogo->score2)
      {
        jogo->equipa1->jogos_ganhos -= 1;
      }
      else
      {
        
      }

      if (jogo->score1 < jogo->score2)
      {
        jogo->equipa2->jogos_ganhos -= 1;
      }
      else
      {
        
      }

      if (score1 > score2)
      {
        jogo->equipa1->jogos_ganhos += 1;
      }
      else
      {
        
      }

      if (score1 < score2)
      {
        jogo->equipa2->jogos_ganhos += 1;
      }
      else
      {
        
      }

      jogo->score1 = score1;
      jogo->score2 = score2;
      return;
    }
    else
    {
      
    }

    jogo = jogo->next;
  }

  printf("%d Jogo inexistente.\n", num_comandos);
}
