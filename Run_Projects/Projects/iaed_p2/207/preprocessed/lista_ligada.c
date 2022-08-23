/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "funcoes.h"


NODE new_node(JOGO j)
{
  NODE new;
  new = malloc(sizeof(struct node_jogo));
  new->jogo = malloc(sizeof(struct jogo));
  new->jogo->nome = strdup(j->nome);
  new->jogo->equipa1 = strdup(j->equipa1);
  new->jogo->equipa2 = strdup(j->equipa2);
  new->jogo->score1 = j->score1;
  new->jogo->score2 = j->score2;
  new->next = 0;
  return new;
}

NODE insert_node(NODE head, JOGO j)
{
  NODE x;
  if (head == 0)
  {
    return new_node(j);
  }
  else
  {
    
  }

  for (x = head; x->next != 0; x = x->next)
    ;

  x->next = new_node(j);
  return head;
}

NODE procura_node(NODE head, JOGO j)
{
  NODE t;
  for (t = head; t != 0; t = t->next)
    if (strcmp(t->jogo->nome, j->nome) == 0)
  {
    return t;
  }
  else
  {
    
  }


  return 0;
}

NODE delete_node(NODE head, char *nome)
{
  NODE t;
  NODE prev;
  for (t = head, prev = 0; t != 0; prev = t, t = t->next)
  {
    if (strcmp(t->jogo->nome, nome) == 0)
    {
      {
        if (t == head)
        {
          head = t->next;
        }
        else
        {
          prev->next = t->next;
        }

        FREEnode(t);
        break;
      }
    }
    else
    {
      
    }

  }

  return head;
}

void FREEnode(NODE t)
{
  free(t->jogo->nome);
  free(t->jogo->equipa1);
  free(t->jogo->equipa2);
  free(t);
}

void freeList(NODE head)
{
  NODE tmp;
  while (head != 0)
  {
    tmp = head;
    head = head->next;
    free(tmp->jogo->nome);
    free(tmp->jogo->equipa1);
    free(tmp->jogo->equipa2);
    free(tmp->jogo);
    free(tmp);
  }

}

