#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "listasEQ.h"


void freeNode(Link link)
{
  freeEq(link->equipa);
  free(link);
}

Link inicializaLista()
{
  return 0;
}

Link criaNode(Equipa *equipa)
{
  Link node;
  node = (Link) malloc(sizeof(Node));
  node->equipa = equipa;
  node->next = 0;
  return node;
}

Link addEqLista(Link head, Equipa *equipa)
{
  if (head == 0)
  {
    return criaNode(equipa);
  }
  else
  {
    head->next = addEqLista(head->next, equipa);
    return head;
  }

}

Link apagaNode(Link head, Equipa *equipa)
{
  Link link;
  Link _link;
  for (link = head, _link = 0; link != 0; _link = link, link = link->next)
  {
    if (link->equipa == equipa)
    {
      if (link == head)
      {
        head = link->next;
      }
      else
      {
        _link->next = link->next;
      }

      freeNode(link);
      break;
    }
    else
    {
      
    }

  }

  return head;
}

Link limpaLista(Link head)
{
  while (head != 0)
  {
    head = apagaNode(head, head->equipa);
  }

  return 0;
}

Equipa *procuraEquipa(Link head, char *nome)
{
  while (head != 0)
  {
    if (strcmp(head->equipa->nome, nome) == 0)
    {
      return head->equipa;
    }
    else
    {
      
    }

    head = head->next;
  }

  return 0;
}

