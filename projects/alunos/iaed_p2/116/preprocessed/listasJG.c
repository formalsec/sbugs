#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "listasJG.h"


void freeNode_(Link_ link)
{
  freeJg(link->jogo);
  free(link);
}

Link_ inicializaLista_()
{
  return 0;
}

Link_ criaNode_(Jogo *jogo)
{
  Link_ node;
  node = (Link_) malloc(sizeof(Node_));
  node->jogo = jogo;
  node->next = 0;
  return node;
}

Link_ addJgLista(Link_ head, Jogo *jogo)
{
  if (head == 0)
  {
    return criaNode_(jogo);
  }
  else
  {
    head->next = addJgLista(head->next, jogo);
    return head;
  }

}

Link_ apagaNode_(Link_ head, Jogo *jogo)
{
  Link_ link;
  Link_ _link;
  for (link = head, _link = 0; link != 0; _link = link, link = link->next)
  {
    if (link->jogo == jogo)
    {
      if (link == head)
      {
        head = link->next;
      }
      else
      {
        _link->next = link->next;
      }

      freeNode_(link);
      break;
    }
    else
    {
      
    }

  }

  return head;
}

Link_ apagaNode_caso(Link_ head, Jogo *jogo)
{
  Link_ link;
  Link_ _link;
  for (link = head, _link = 0; link != 0; _link = link, link = link->next)
  {
    if (link->jogo == jogo)
    {
      if (link == head)
      {
        head = link->next;
      }
      else
      {
        _link->next = link->next;
      }

      free(link);
      break;
    }
    else
    {
      
    }

  }

  return head;
}

Link_ limpaLista_(Link_ head)
{
  while (head != 0)
  {
    head = apagaNode_(head, head->jogo);
  }

  return 0;
}

Link_ limpaLista_caso(Link_ head)
{
  while (head != 0)
  {
    head = apagaNode_caso(head, head->jogo);
  }

  return 0;
}

Jogo *procuraJogo(Link_ head, char *nome)
{
  while (head != 0)
  {
    if (strcmp(head->jogo->nome, nome) == 0)
    {
      return head->jogo;
    }
    else
    {
      
    }

    head = head->next;
  }

  return 0;
}

Jogo *obtemElem(Link_ node)
{
  return node->jogo;
}

