/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "proj2.h"


char input[1024];
int i = 0;
int j = 0;
int a = 0;
int contador = 0;
void AdicionaJogo();
void AdicionaEquipa();
void ListaJogos();
int ProcuraJogo();
int ProcuraEquipa();
void ApagaJogo();
void AlteraPontuacao();
void EncontraVencedor();
Equipa lookup(Equipa equipa, char *nome);
Jogo lookup_jogo(Jogo jogo, char *nome);
Equipa verifica(Equipa equipa, char *nome);
int isEmpty(Equipa equipa);
void ListaEquipas();
Equipa troca(Equipa equipa1, Equipa equipa2);
Equipa Ordena(Equipa equipa);
Equipa libertaequipas();
Jogo libertajogos();
Jogo verifica_jogos(Jogo jogo, char *nome);
int main()
{
  char comando;
  while (1)
  {
    comando = new_sym_var(sizeof(char) * 8);
    switch (comando)
    {
      case 'a':
        contador++;
        AdicionaJogo();
        break;

      case 'A':
        contador++;
        AdicionaEquipa();
        break;

      case 'l':
        contador++;
        ListaJogos();
        break;

      case 'p':
        contador++;
        ProcuraJogo();
        break;

      case 'P':
        contador++;
        ProcuraEquipa();
        break;

      case 'r':
        contador++;
        ApagaJogo();
        break;

      case 's':
        contador++;
        AlteraPontuacao();
        break;

      case 'g':
        contador++;
        EncontraVencedor();
        break;

      case 'L':
        contador++;
        ListaEquipas();
        break;

      case 'x':
        libertajogos();
        libertaequipas();
        return 0;

    }

  }

  return 0;
}

void AdicionaJogo()
{
  char novo_nome[1024];
  char nova_equipa1[1024];
  char nova_equipa2[1024];
  char novo_score1[3];
  char novo_score2[4];
  int nscore1;
  int nscore2;
  char *token;
  getchar();
  fgets(input, 1605, stdin);
  token = strtok(input, ":");
  strcpy(novo_nome, token);
  lookup_jogo(jogo, novo_nome);
  if (i == 1)
  {
    {
      i = 0;
      return;
    }
  }
  else
  {
    
  }

  token = strtok(0, ":");
  strcpy(nova_equipa1, token);
  if (isEmpty(equipa) != 0)
  {
    {
      verifica(equipa, nova_equipa1);
      if (j != 2)
      {
        {
          printf("%d Equipa inexistente.\n", contador);
          return;
        }
      }
      else
      {
        {
          j = 0;
        }
      }

    }
  }
  else
  {
    {
      printf("%d Equipa inexistente.\n", contador);
      return;
    }
  }

  token = strtok(0, ":");
  strcpy(nova_equipa2, token);
  verifica(equipa, nova_equipa2);
  if (j != 2)
  {
    {
      printf("%d Equipa inexistente.\n", contador);
      return;
    }
  }
  else
  {
    {
      j = 0;
    }
  }

  token = strtok(0, ":");
  strcpy(novo_score1, token);
  token = strtok(0, ":");
  strcpy(novo_score2, token);
  novojogo = (Jogo) malloc(sizeof(struct node_jogos));
  if (jogo == 0)
  {
    {
      jogo = (jogoatual = novojogo);
    }
  }
  else
  {
    {
      jogoatual = jogo;
      while (jogoatual->next != 0)
      {
        jogoatual = jogoatual->next;
      }

      jogoatual->next = novojogo;
      jogoatual = novojogo;
    }
  }

  strcpy(novojogo->nome, novo_nome);
  strcpy(novojogo->equipa1, nova_equipa1);
  strcpy(novojogo->equipa2, nova_equipa2);
  strcpy(novojogo->score1, novo_score1);
  nscore1 = atoi(novojogo->score1);
  strcpy(novojogo->score2, novo_score2);
  nscore2 = atoi(novojogo->score2);
  if (nscore1 > nscore2)
  {
    {
      equipaatual = equipa;
      while (equipaatual != 0)
      {
        if (strcmp(equipaatual->nome, novojogo->equipa1) == 0)
        {
          {
            equipaatual->vitorias += 1;
            break;
          }
        }
        else
        {
          {
            equipaatual = equipaatual->next;
          }
        }

      }

    }
  }
  else
  {
    if (nscore2 > nscore1)
    {
      {
        equipaatual = equipa;
        while (equipaatual != 0)
        {
          if (strcmp(equipaatual->nome, novojogo->equipa2) == 0)
          {
            {
              equipaatual->vitorias += 1;
              break;
            }
          }
          else
          {
            {
              equipaatual = equipaatual->next;
            }
          }

        }

      }
    }
    else
    {
      
    }

  }

  jogoatual->next = 0;
}

void AdicionaEquipa()
{
  char novo_nome[1024];
  char *token;
  getchar();
  fgets(input, 1605, stdin);
  token = strtok(input, "\n");
  strcpy(novo_nome, token);
  lookup(equipa, novo_nome);
  if (i == 3)
  {
    {
      i = 0;
      return;
    }
  }
  else
  {
    {
      novaequipa = (Equipa) malloc(sizeof(struct node_equipas));
      if (equipa == 0)
      {
        {
          equipa = (equipaatual = novaequipa);
        }
      }
      else
      {
        {
          equipaatual = equipa;
          while (equipaatual->next != 0)
          {
            equipaatual = equipaatual->next;
          }

          equipaatual->next = novaequipa;
          equipaatual = novaequipa;
        }
      }

      strcpy(novaequipa->nome, novo_nome);
      novaequipa->vitorias = 0;
      equipaatual->next = 0;
    }
  }

}

void ListaJogos()
{
  int nscore1;
  int nscore2;
  if (jogo != 0)
  {
    {
      jogoatual = jogo;
      do
      {
        nscore1 = atoi(jogoatual->score1);
        nscore2 = atoi(jogoatual->score2);
        printf("%d %s %s %s %d %d\n", contador, jogoatual->nome, jogoatual->equipa1, jogoatual->equipa2, nscore1, nscore2);
      }
      while ((jogoatual = jogoatual->next) != 0);
    }
  }
  else
  {
    
  }

}

int ProcuraJogo()
{
  char novo_nome[1024];
  char *token;
  getchar();
  fgets(input, 1605, stdin);
  token = strtok(input, "\n");
  strcpy(novo_nome, token);
  jogoatual = jogo;
  while (jogoatual != 0)
  {
    if (strcmp(jogoatual->nome, novo_nome) == 0)
    {
      {
        printf("%d %s %s %s %s %s\n", contador, jogoatual->nome, jogoatual->equipa1, jogoatual->equipa2, jogoatual->score1, jogoatual->score2);
        return 0;
      }
    }
    else
    {
      {
        jogoatual = jogoatual->next;
      }
    }

  }

  printf("%d Jogo inexistente.\n", contador);
  return 1;
}

int ProcuraEquipa()
{
  char novo_nome[1024];
  char *token;
  getchar();
  fgets(input, 1605, stdin);
  token = strtok(input, "\n");
  strcpy(novo_nome, token);
  equipaatual = equipa;
  while (equipaatual != 0)
  {
    if (strcmp(equipaatual->nome, novo_nome) == 0)
    {
      {
        printf("%d %s %d\n", contador, equipaatual->nome, equipaatual->vitorias);
        return 0;
      }
    }
    else
    {
      {
        equipaatual = equipaatual->next;
      }
    }

  }

  printf("%d Equipa inexistente.\n", contador);
  return 1;
}

void ApagaJogo()
{
  char novo_nome[1024];
  char *token;
  int oldscore1;
  int oldscore2;
  getchar();
  fgets(input, 1605, stdin);
  token = strtok(input, "\n");
  strcpy(novo_nome, token);
  jogoatual = jogo;
  jogoanterior = jogo;
  equipaatual = equipa;
  verifica_jogos(jogoatual, novo_nome);
  if (a != 2)
  {
    {
      printf("%d Jogo inexistente.\n", contador);
      return;
    }
  }
  else
  {
    {
      a = 0;
    }
  }

  while (jogoatual != 0)
  {
    if (strcmp(jogoatual->nome, novo_nome) == 0)
    {
      {
        oldscore1 = atoi(jogoatual->score1);
        oldscore2 = atoi(jogoatual->score2);
        if (oldscore1 > oldscore2)
        {
          {
            while (equipaatual != 0)
            {
              if (strcmp(jogoatual->equipa1, equipaatual->nome) == 0)
              {
                {
                  equipaatual->vitorias -= 1;
                  break;
                }
              }
              else
              {
                {
                  equipaatual = equipaatual->next;
                }
              }

            }

          }
        }
        else
        {
          if (oldscore2 > oldscore1)
          {
            {
              while (equipaatual != 0)
              {
                if (strcmp(jogoatual->equipa2, equipaatual->nome) == 0)
                {
                  {
                    equipaatual->vitorias -= 1;
                    break;
                  }
                }
                else
                {
                  {
                    equipaatual = equipaatual->next;
                  }
                }

              }

            }
          }
          else
          {
            
          }

        }

        if (jogoatual != jogo)
        {
          {
            jogoanterior->next = jogoatual->next;
          }
        }
        else
        {
          {
            jogo = jogo->next;
          }
        }

        break;
      }
    }
    else
    {
      {
        jogoanterior = jogoatual;
        jogoatual = jogoatual->next;
      }
    }

  }

  if (jogoatual == 0)
  {
    {
      printf("%d Jogo inexistente.\n", contador);
    }
  }
  else
  {
    
  }

}

void AlteraPontuacao()
{
  char novo_nome[1024];
  char novo_score1[3];
  char novo_score2[4];
  char *token;
  int nscore1;
  int nscore2;
  int oldscore1;
  int oldscore2;
  getchar();
  fgets(input, 1605, stdin);
  token = strtok(input, ":");
  strcpy(novo_nome, token);
  token = strtok(0, ":");
  strcpy(novo_score1, token);
  token = strtok(0, ":");
  strcpy(novo_score2, token);
  jogoatual = jogo;
  verifica_jogos(jogoatual, novo_nome);
  if (a != 2)
  {
    {
      printf("%d Jogo inexistente.\n", contador);
      return;
    }
  }
  else
  {
    {
      a = 0;
    }
  }

  while (jogoatual != 0)
  {
    if (strcmp(jogoatual->nome, novo_nome) == 0)
    {
      {
        equipaatual = equipa;
        oldscore1 = atoi(jogoatual->score1);
        oldscore2 = atoi(jogoatual->score2);
        if (oldscore1 > oldscore2)
        {
          {
            while (equipaatual != 0)
            {
              if (strcmp(jogoatual->equipa1, equipaatual->nome) == 0)
              {
                {
                  equipaatual->vitorias -= 1;
                  break;
                }
              }
              else
              {
                {
                  equipaatual = equipaatual->next;
                }
              }

            }

          }
        }
        else
        {
          if (oldscore2 > oldscore1)
          {
            {
              while (equipaatual != 0)
              {
                if (strcmp(jogoatual->equipa2, equipaatual->nome) == 0)
                {
                  {
                    equipaatual->vitorias -= 1;
                    break;
                  }
                }
                else
                {
                  {
                    equipaatual = equipaatual->next;
                  }
                }

              }

            }
          }
          else
          {
            
          }

        }

        strcpy(jogoatual->score1, novo_score1);
        strcpy(jogoatual->score2, novo_score2);
        nscore1 = atoi(jogoatual->score1);
        nscore2 = atoi(jogoatual->score2);
        if (nscore1 > nscore2)
        {
          {
            equipaatual = equipa;
            while (equipaatual != 0)
            {
              if (strcmp(equipaatual->nome, novojogo->equipa1) == 0)
              {
                {
                  equipaatual->vitorias += 1;
                  break;
                }
              }
              else
              {
                {
                  equipaatual = equipaatual->next;
                }
              }

            }

          }
        }
        else
        {
          if (nscore2 > nscore1)
          {
            {
              equipaatual = equipa;
              while (equipaatual != 0)
              {
                if (strcmp(equipaatual->nome, novojogo->equipa2) == 0)
                {
                  {
                    equipaatual->vitorias += 1;
                    break;
                  }
                }
                else
                {
                  {
                    equipaatual = equipaatual->next;
                  }
                }

              }

            }
          }
          else
          {
            
          }

        }

        break;
      }
    }
    else
    {
      {
        jogoatual = jogoatual->next;
      }
    }

  }

  if (jogoatual == 0)
  {
    {
      printf("%d Jogo inexistente.\n", contador);
    }
  }
  else
  {
    
  }

}

void EncontraVencedor()
{
  equipaatual = equipa;
  if (equipaatual == 0)
  {
    {
      return;
    }
  }
  else
  {
    
  }

  Ordena(equipaatual);
  printf("%d Melhores %d\n", contador, equipaatual->vitorias);
  while (equipaatual != 0)
  {
    printf("%d * %s\n", contador, equipaatual->nome);
    equipaatual = equipaatual->next;
  }

}

Equipa lookup(Equipa equipa, char *nome)
{
  Equipa t;
  for (t = equipa; t != 0; t = t->next)
  {
    if (strcmp(t->nome, nome) == 0)
    {
      {
        i = 3;
        printf("%d Equipa existente.\n", contador);
      }
    }
    else
    {
      
    }

  }

  return 0;
}

Jogo lookup_jogo(Jogo jogo, char *nome)
{
  Jogo t;
  for (t = jogo; t != 0; t = t->next)
  {
    if (strcmp(t->nome, nome) == 0)
    {
      {
        printf("%d Jogo existente.\n", contador);
        i = 1;
      }
    }
    else
    {
      
    }

  }

  return 0;
}

Jogo verifica_jogos(Jogo jogo, char *nome)
{
  Jogo t;
  for (t = jogo; t != 0; t = t->next)
  {
    if (strcmp(t->nome, nome) == 0)
    {
      {
        a = 2;
      }
    }
    else
    {
      
    }

  }

  return 0;
}

Equipa verifica(Equipa equipa, char *nome)
{
  Equipa t;
  for (t = equipa; t != 0; t = t->next)
  {
    if (strcmp(t->nome, nome) == 0)
    {
      {
        j = 2;
      }
    }
    else
    {
      
    }

  }

  return 0;
}

int isEmpty(Equipa equipa)
{
  if (equipa)
  {
    return 1;
  }
  else
  {
    
  }

  return 0;
}

void ListaEquipas()
{
  if (equipa != 0)
  {
    {
      equipaatual = equipa;
      do
      {
        printf("%s %d\n", equipaatual->nome, equipaatual->vitorias);
      }
      while ((equipaatual = equipaatual->next) != 0);
    }
  }
  else
  {
    
  }

}

Equipa troca(Equipa equipa1, Equipa equipa2)
{
  Equipa tmp = equipa1;
  equipa1 = equipa2;
  equipa2 = tmp;
  return 0;
}

Equipa Ordena(Equipa equipa)
{
  int swapped;
  Equipa ptr1;
  Equipa lptr = 0;
  if (equipa == 0)
  {
    return 0;
  }
  else
  {
    
  }

  do
  {
    swapped = 0;
    ptr1 = equipa;
    while (ptr1->next != lptr)
    {
      if (ptr1->vitorias < ptr1->next->vitorias)
      {
        {
          troca(ptr1, ptr1->next);
          swapped = 1;
        }
      }
      else
      {
        
      }

      ptr1 = ptr1->next;
    }

    lptr = ptr1;
  }
  while (swapped);
  return 0;
}

Equipa libertaequipas()
{
  equipaatual = equipa;
  while (equipaatual != 0)
  {
    free(equipaatual);
    equipaatual = equipaatual->next;
  }

  return 0;
}

Jogo libertajogos()
{
  jogoatual = jogo;
  while (jogoatual != 0)
  {
    free(jogoatual);
    jogoatual = jogoatual->next;
  }

  return 0;
}

