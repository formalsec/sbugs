#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Hash.h"
#include "structs.h"
#include "LinkedList.h"


node append(char game[], node Head)
{
  struct nodes *temp;
  struct nodes *p;
  temp = (struct nodes *) malloc(sizeof(struct nodes));
  temp->link = 0;
  temp->nome_jogo = malloc((sizeof(char)) * (strlen(game) + 1));
  strcpy(temp->nome_jogo, game);
  if (Head == 0)
  {
    return temp;
  }
  else
  {
    p = Head;
    while (p->link != 0)
    {
      p = p->link;
    }

    p->link = temp;
  }

  return Head;
}

void display(int contalinhas, int tblsz_jogo, node Head, jogo *st)
{
  struct nodes *temp;
  struct jogos *display_jogo;
  temp = Head;
  if (temp == 0)
  {
    return;
  }
  else
  {
    while (temp != 0)
    {
      display_jogo = search_jogo(temp->nome_jogo, tblsz_jogo, st);
      printf("%d %s %s %s %d %d\n", contalinhas, display_jogo->nome, display_jogo->equipa1, display_jogo->equipa2, display_jogo->score1, display_jogo->score2);
      temp = temp->link;
    }

  }

}

void display2(int contalinhas, int tblsz_jogo, node Head, equipa *eq)
{
  struct nodes *temp;
  struct equipas *display_jogo;
  temp = Head;
  if (temp == 0)
  {
    return;
  }
  else
  {
    while (temp != 0)
    {
      display_jogo = search_equipa(temp->nome_jogo, tblsz_jogo, eq);
      printf("%d %s %d\n", contalinhas, display_jogo->nome_equipa, display_jogo->vitorias);
      temp = temp->link;
    }

  }

}

tuplio get_max_vit(node Head, int tblsz, equipa *eq, tuplio tuplo)
{
  int m;
  int conta_eq_c_max_vit = 0;
  int max_vit = 0;
  struct nodes *temp;
  temp = Head;
  tuplo->max_vitorias = 0;
  tuplo->conta_eq_c_max_vit = 0;
  if (temp == 0)
  {
    return tuplo;
  }
  else
  {
    while (temp != 0)
    {
      m = get_vitorias(temp->nome_jogo, tblsz, eq);
      if (max_vit < m)
      {
        max_vit = m;
        conta_eq_c_max_vit = 1;
      }
      else
      {
        if (max_vit == m)
        {
          conta_eq_c_max_vit += 1;
        }
        else
        {
          
        }

      }

      temp = temp->link;
    }

    tuplo->max_vitorias = max_vit;
    tuplo->conta_eq_c_max_vit = conta_eq_c_max_vit;
    return tuplo;
  }

}

node delete_node(char *nome, node Head)
{
  struct nodes *temp;
  struct nodes *p;
  struct nodes *q;
  if (strcmp(nome, Head->nome_jogo) == 0)
  {
    temp = Head;
    Head = temp->link;
    temp->link = 0;
    free(temp->nome_jogo);
    free(temp);
  }
  else
  {
    q = Head;
    while (strcmp(q->nome_jogo, nome) != 0)
    {
      p = q;
      q = q->link;
    }

    p->link = q->link;
    q->link = 0;
    free(q->nome_jogo);
    free(q);
  }

  return Head;
}

void obtem_equipas_com_max_vit(node Head, int max_vitorias, char **equipa_c_vitorias, int tblsz, equipa *eq)
{
  struct nodes *temp;
  int i;
  int cont = 1;
  temp = Head;
  while (temp != 0)
  {
    if (get_vitorias(temp->nome_jogo, tblsz, eq) == max_vitorias)
    {
      *equipa_c_vitorias = malloc((sizeof(char)) * (strlen(temp->nome_jogo) + 1));
      strcpy(*equipa_c_vitorias, temp->nome_jogo);
      equipa_c_vitorias++;
      cont++;
    }
    else
    {
      
    }

    temp = temp->link;
  }

  for (i = 0; i < cont; i++)
  {
    equipa_c_vitorias--;
  }

}
