/*File generated by PreProcessor.py*/


#include "struct.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


jogo *head = 0;
int a()
{
  char nome[1024];
  char equipa1[1024];
  char equipa2[1024];
  int score1;
  int score2;
  int aux1;
  int aux2;
  jogo *aux;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
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
  aux1 = procuraEquipa(equipa1);
  aux2 = procuraEquipa(equipa2);
  if (head == 0)
  {
    {
      if ((aux1 == (-1)) || (aux2 == (-1)))
      {
        {
          printf("%d Equipa inexistente.\n", NL);
          return 0;
        }
      }
      else
      {
        
      }

      head = malloc(sizeof(jogo));
      head->nome = malloc((sizeof(char)) * (strlen(nome) + 1));
      strcpy(head->nome, nome);
      head->equipa1 = hash_e[aux1];
      head->equipa2 = hash_e[aux2];
      head->score1 = score1;
      head->score2 = score2;
      head->next = 0;
      head->ant = 0;
      if (score1 > score2)
      {
        {
          hash_e[aux1]->ganhos++;
        }
      }
      else
      {
        
      }

      if (score2 > score1)
      {
        {
          hash_e[aux2]->ganhos++;
        }
      }
      else
      {
        
      }

    }
  }
  else
  {
    {
      aux = head;
      while (aux->next != 0)
      {
        if (strcmp(aux->nome, nome) == 0)
        {
          {
            printf("%d Jogo existente.\n", NL);
            return 0;
          }
        }
        else
        {
          
        }

        aux = aux->next;
      }

      if (strcmp(aux->nome, nome) == 0)
      {
        {
          printf("%d Jogo existente.\n", NL);
          return 0;
        }
      }
      else
      {
        
      }

      if ((aux1 == (-1)) || (aux2 == (-1)))
      {
        {
          printf("%d Equipa inexistente.\n", NL);
          return 0;
        }
      }
      else
      {
        
      }

      aux->next = malloc(sizeof(jogo));
      aux->next->nome = malloc((sizeof(char)) * (strlen(nome) + 1));
      strcpy(aux->next->nome, nome);
      aux->next->equipa1 = hash_e[aux1];
      aux->next->equipa2 = hash_e[aux2];
      aux->next->score1 = score1;
      aux->next->score2 = score2;
      aux->next->next = 0;
      aux->next->ant = aux;
      if (score1 > score2)
      {
        {
          hash_e[aux1]->ganhos++;
        }
      }
      else
      {
        
      }

      if (score2 > score1)
      {
        {
          hash_e[aux2]->ganhos++;
        }
      }
      else
      {
        
      }

    }
  }

  return 1;
}

void destroyJogos()
{
  jogo *aux;
  aux = head;
  while (aux != 0)
  {
    aux = aux->next;
    free(head->nome);
    free(head);
    head = aux;
  }

}

void l()
{
  jogo *aux;
  aux = head;
  while (aux != 0)
  {
    printf("%d %s %s %s %d %d\n", NL, aux->nome, aux->equipa1->nome, aux->equipa2->nome, aux->score1, aux->score2);
    aux = aux->next;
  }

}

jogo *procurarJogo(char *nome)
{
  jogo *aux = head;
  while (aux != 0)
  {
    if (strcmp(aux->nome, nome) == 0)
    {
      {
        return aux;
      }
    }
    else
    {
      
    }

    aux = aux->next;
  }

  return 0;
}

void r()
{
  char nome[1024];
  jogo *aux;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  aux = procurarJogo(nome);
  if (aux != 0)
  {
    {
      if (aux->score1 > aux->score2)
      {
        {
          aux->equipa1->ganhos--;
        }
      }
      else
      {
        
      }

      if (aux->score2 > aux->score1)
      {
        {
          aux->equipa2->ganhos--;
        }
      }
      else
      {
        
      }

      if (aux->ant == 0)
      {
        {
          head = aux->next;
          if (aux->next != 0)
          {
            {
              aux->next->ant = 0;
            }
          }
          else
          {
            
          }

          free(aux->nome);
          free(aux);
        }
      }
      else
      {
        if (aux->next == 0)
        {
          {
            aux->ant->next = 0;
            free(aux->nome);
            free(aux);
          }
        }
        else
        {
          {
            aux->ant->next = aux->next;
            aux->next->ant = aux->ant;
            free(aux->nome);
            free(aux);
          }
        }

      }

    }
  }
  else
  {
    {
      printf("%d Jogo inexistente.\n", NL);
    }
  }

}

void p()
{
  char nome[1024];
  jogo *aux;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  aux = procurarJogo(nome);
  if (aux != 0)
  {
    {
      printf("%d %s %s %s %d %d\n", NL, aux->nome, aux->equipa1->nome, aux->equipa2->nome, aux->score1, aux->score2);
    }
  }
  else
  {
    {
      printf("%d Jogo inexistente.\n", NL);
    }
  }

}

void s()
{
  char nome[1024];
  int score1;
  int score2;
  jogo *aux;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  aux = procurarJogo(nome);
  if (aux != 0)
  {
    {
      if (aux->score1 > aux->score2)
      {
        {
          if (score2 > score1)
          {
            {
              aux->equipa1->ganhos--;
              aux->equipa2->ganhos++;
            }
          }
          else
          {
            if (score1 == score2)
            {
              {
                aux->equipa1->ganhos--;
              }
            }
            else
            {
              
            }

          }

        }
      }
      else
      {
        if (aux->score1 < aux->score2)
        {
          {
            if (score1 > score2)
            {
              {
                aux->equipa1->ganhos++;
                aux->equipa2->ganhos--;
              }
            }
            else
            {
              if (score1 == score2)
              {
                {
                  aux->equipa2->ganhos--;
                }
              }
              else
              {
                
              }

            }

          }
        }
        else
        {
          {
            if (score1 > score2)
            {
              {
                aux->equipa1->ganhos++;
              }
            }
            else
            {
              
            }

            if (score2 > score1)
            {
              {
                aux->equipa2->ganhos++;
              }
            }
            else
            {
              
            }

          }
        }

      }

      aux->score1 = score1;
      aux->score2 = score2;
    }
  }
  else
  {
    {
      printf("%d Jogo inexistente.\n", NL);
    }
  }

}

