#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "hash_jogos.h"
#include "equipa.h"
#include "hash_equipas.h"
#include "jogo.h"
#include "lista_jogos.h"


long hashU(char *v, int M)
{
  long h;
  long a = 31415;
  long b = 27183;
  for (h = 0; (*v) != '\0'; v++, a = (a * b) % (M - 1))
    h = ((a * h) + (*v)) % M;

  return h;
}

link_jg *HT_jg_init(int M)
{
  link_jg *heads = calloc(M, sizeof(link_jg));
  return heads;
}

link_jg insertJgBeginList(link_jg head, link_jogo ptr_link_jogo)
{
  if (head == 0)
  {
    link_jg first_node = (link_jg) malloc(sizeof(struct node_jg));
    first_node->ptr_link_jogo = ptr_link_jogo;
    first_node->next = 0;
    return first_node;
  }
  else
  {
    link_jg new_node = (link_jg) malloc(sizeof(struct node_jg));
    new_node->ptr_link_jogo = ptr_link_jogo;
    new_node->next = head;
    head = new_node;
    return new_node;
  }

}

void HT_jg_insert(link_jogo ptr_link_jogo, link_jg *heads_jg, int M)
{
  long i = hashU(ptr_link_jogo->jogo->nome, M);
  heads_jg[i] = insertJgBeginList(heads_jg[i], ptr_link_jogo);
}

link_jg removeJgList(link_jg head, link_jogo ptr_link_jogo)
{
  link_jg t;
  link_jg prev;
  for (t = head, prev = 0; t != 0; prev = t, t = t->next)
  {
    if (strcmp(t->ptr_link_jogo->jogo->nome, ptr_link_jogo->jogo->nome) == 0)
    {
      if (t == head)
      {
        head = t->next;
      }
      else
      {
        prev->next = t->next;
      }

      free(t);
      break;
    }
    else
    {
      
    }

  }

  return head;
}

void HT_jg_delete(link_jogo ptr_link_jogo, link_jg *heads_jg, int M)
{
  long i = hashU(ptr_link_jogo->jogo->nome, M);
  heads_jg[i] = removeJgList(heads_jg[i], ptr_link_jogo);
}

link_jogo searchJgList(link_jg head, Key_jogo c)
{
  link_jg t;
  for (t = head; t != 0; t = t->next)
  {
    if (strcmp(t->ptr_link_jogo->jogo->nome, c) == 0)
    {
      return t->ptr_link_jogo;
    }
    else
    {
      
    }

  }

  return 0;
}

link_jogo HT_jg_search(Key_jogo c, link_jg *heads_jg, int M)
{
  long i = hashU(c, M);
  return searchJgList(heads_jg[i], c);
}

void HT_jg_destroy(link_jg *heads_jg, int M)
{
  long i;
  link_jg temp = 0;
  link_jg aux = 0;
  for (i = 0; i < M; i++)
  {
    temp = heads_jg[i];
    while (temp != 0)
    {
      aux = temp;
      temp = temp->next;
      free(aux);
    }

  }

  free(heads_jg);
}
