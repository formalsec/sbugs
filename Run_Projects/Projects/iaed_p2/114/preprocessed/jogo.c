/*File generated by PreProcessor.py*/


#include "equipa.h"
#include "jogo.h"
#include <stdio.h>
#include <string.h>


void JTable_init(Link *Table)
{
  int contador;
  for (contador = 0; contador < 14149; contador++)
    Table[contador] = 0;

}

int hashJogo(char *v, int M)
{
  int h;
  int a = 31415;
  int b = 27183;
  for (h = 0; (*v) != '\0'; v++, a = (a * b) % (M - 1))
    h = ((a * h) + (*v)) % M;

  return h;
}

Link search_j_lista_Table(Link head, char *nome)
{
  while (head != 0)
  {
    if (strcmp(head->linkj->jogo->nome, nome) == 0)
    {
      return head;
    }
    else
    {
      head = head->next;
    }

  }

  return 0;
}

Link search_j_Table(Link *Table, char *nome)
{
  int index = hashJogo(nome, 14149);
  return search_j_lista_Table(Table[index], nome);
}

int jogo_invalido(Link *JHTable, LinkE *EHTable, char *jogo_nome, char *equipa0_nome, char *equipa1_nome)
{
  int indexj;
  indexj = hashJogo(jogo_nome, 14149);
  if (search_j_lista_Table(JHTable[indexj], jogo_nome) != 0)
  {
    return 1;
  }
  else
  {
    if ((search_lista_e(EHTable[hashEquipa(equipa0_nome, 12049)], equipa0_nome) == 0) || (search_lista_e(EHTable[hashEquipa(equipa1_nome, 12049)], equipa1_nome) == 0))
    {
      return 2;
    }
    else
    {
      
    }

  }

  return 0;
}

LinkJ add_j_to_main_list(LinkJ head, Jogo *jogo)
{
  LinkJ new;
  new = (LinkJ) malloc(sizeof(NodeJ));
  new->jogo = jogo;
  new->prev = 0;
  new->next = head;
  if (head != 0)
  {
    head->prev = new;
  }
  else
  {
    
  }

  return new;
}

Link add_linkj_to_list(Link head, LinkJ linkj)
{
  Link new;
  new = (Link) malloc(sizeof(Node));
  new->prev = 0;
  new->linkj = linkj;
  new->next = head;
  if (head != 0)
  {
    head->prev = new;
  }
  else
  {
    
  }

  return new;
}

void add_linkj_hash(Link *Table, LinkJ linkj, char *nome)
{
  int index = hashJogo(nome, 14149);
  Table[index] = add_linkj_to_list(Table[index], linkj);
}

Equipa *vencedor(Jogo *jogo)
{
  if (jogo->score[0] > jogo->score[1])
  {
    return jogo->equipa0;
  }
  else
  {
    if (jogo->score[0] < jogo->score[1])
    {
      return jogo->equipa1;
    }
    else
    {
      
    }

  }

  return 0;
}

int destroy(Link *Table, LinkJ *MainList, LinkJ *Tail, char *nome)
{
  Equipa *e_vencedora;
  Link link = search_j_Table(Table, nome);
  int index = hashJogo(nome, 14149);
  if (link != 0)
  {
    {
      e_vencedora = vencedor(link->linkj->jogo);
      if (e_vencedora != 0)
      {
        e_vencedora->wins -= 1;
      }
      else
      {
        
      }

      free(link->linkj->jogo->nome);
      free(link->linkj->jogo);
      if (link->linkj->prev != 0)
      {
        link->linkj->prev->next = link->linkj->next;
      }
      else
      {
        *MainList = link->linkj->next;
      }

      if (link->linkj->next != 0)
      {
        link->linkj->next->prev = link->linkj->prev;
      }
      else
      {
        *Tail = link->linkj->prev;
      }

      free(link->linkj);
      if ((link->prev == 0) && (link->next == 0))
      {
        Table[index] = 0;
      }
      else
      {
        if ((link->prev != 0) && (link->next == 0))
        {
          link->prev->next = 0;
        }
        else
        {
          if ((link->prev == 0) && (link->next != 0))
          {
            {
              Table[index] = link->next;
              link->next->prev = 0;
            }
          }
          else
          {
            {
              link->prev->next = link->next;
              link->next->prev = link->prev;
            }
          }

        }

      }

      free(link);
      return 1;
    }
  }
  else
  {
    
  }

  return 0;
}

void clear_j(Link *Table)
{
  int contador;
  Link link;
  Link next;
  for (contador = 0; contador < 14149; contador++)
  {
    link = Table[contador];
    while (link != 0)
    {
      free(link->linkj->jogo->nome);
      free(link->linkj->jogo);
      free(link->linkj);
      next = link->next;
      free(link);
      link = next;
    }

    Table[contador] = 0;
  }

}

