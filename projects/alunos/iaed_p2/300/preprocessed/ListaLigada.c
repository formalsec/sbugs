#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaLigada.h"
#include "Jogos.h"


list *mk_list()
{
  list *l = calloc(1, sizeof(list));
  return l;
}

void free_node(node *n)
{
  free(n->jogo->nome);
  free(n->jogo->equipa1);
  free(n->jogo->equipa2);
  free(n->jogo);
  free(n);
}

void free_list(list *l)
{
  while (l->head != 0)
  {
    node *tmp = l->head->next;
    free_node(l->head);
    l->head = tmp;
  }

  free(l);
}

void rm_node(list *l, node *n)
{
  if (n->previous == 0)
  {
    l->head = n->next;
  }
  else
  {
    n->previous->next = n->next;
  }

  if (n->next == 0)
  {
    l->last = n->previous;
  }
  else
  {
    n->next->previous = n->previous;
  }

  free_node(n);
}

node *add_last(list *l, char *n, char *equipa1, char *equipa2, int score1, int score2)
{
  node *nn = malloc(sizeof(node));
  nn->previous = l->last;
  nn->jogo = malloc(sizeof(struct Jogo));
  nn->jogo->nome = malloc((sizeof(char)) * (strlen(n) + 1));
  nn->jogo->equipa1 = malloc((sizeof(char)) * (strlen(equipa1) + 1));
  nn->jogo->equipa2 = malloc((sizeof(char)) * (strlen(equipa2) + 1));
  strcpy(nn->jogo->nome, n);
  strcpy(nn->jogo->equipa1, equipa1);
  strcpy(nn->jogo->equipa2, equipa2);
  nn->jogo->score1 = score1;
  nn->jogo->score2 = score2;
  nn->next = 0;
  if (l->last != 0)
  {
    l->last->next = nn;
  }
  else
  {
    l->head = nn;
  }

  ;
  l->last = nn;
  return nn;
}

void printList(node *head, int nl)
{
  node *temporario = head;
  while (temporario != 0)
  {
    printf("%d %s %s %s %d %d\n", nl, temporario->jogo->nome, temporario->jogo->equipa1, temporario->jogo->equipa2, temporario->jogo->score1, temporario->jogo->score2);
    temporario = temporario->next;
  }

}

