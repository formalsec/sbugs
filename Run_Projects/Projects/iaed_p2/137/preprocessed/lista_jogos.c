/*File generated by PreProcessor.py*/


#include "lista_jogos.h"


LstJogos *novaListaJogos()
{
  LstJogos *lst = malloc(sizeof(LstJogos));
  lst->head = 0;
  lst->n_jogos = 0;
  return lst;
}

NodeJogo *novoNodeJogo(Jogo j)
{
  NodeJogo *t = malloc(sizeof(NodeJogo));
  t->jogo = j;
  t->seguinte = 0;
  return t;
}

void pushJogo(Jogo j, LstJogos *lst)
{
  NodeJogo *t = novoNodeJogo(j);
  t->seguinte = lst->head;
  lst->head = t;
  lst->n_jogos++;
}

void popJogo(LstJogos *lst)
{
  NodeJogo *t = lst->head;
  lst->head = lst->head->seguinte;
  lst->n_jogos--;
  destroiJogo(t->jogo);
  free(t);
}

void removeJogo(LstJogos *lst, char *nome)
{
  NodeJogo *t;
  NodeJogo *anterior;
  t = lst->head;
  anterior = 0;
  while (t != 0)
  {
    if (strcmp(t->jogo.nome, nome) == 0)
    {
      if (t == lst->head)
      {
        lst->head = t->seguinte;
      }
      else
      {
        anterior->seguinte = t->seguinte;
      }

      destroiJogo(t->jogo);
      free(t);
      lst->n_jogos--;
      break;
    }
    else
    {
      
    }

    anterior = t;
    t = t->seguinte;
  }

}

Jogo *procuraLstJogos(LstJogos *lst, char *nome)
{
  NodeJogo *t = lst->head;
  if (!lst)
  {
    return 0;
  }
  else
  {
    
  }

  while (t)
    if (strcmp(t->jogo.nome, nome) == 0)
  {
    return &t->jogo;
  }
  else
  {
    t = t->seguinte;
  }


  return 0;
}

Jogo *copiaLstJogos(LstJogos *lst)
{
  int i = 0;
  NodeJogo *t = lst->head;
  Jogo *arr = malloc(lst->n_jogos * (sizeof(Jogo)));
  for (i = 0; t; t = t->seguinte)
    arr[i++] = t->jogo;

  return arr;
}

void destroiLstJogos(LstJogos *lst)
{
  if (lst)
  {
    while (lst->head)
      popJogo(lst);

  }
  else
  {
    
  }

  free(lst);
}

