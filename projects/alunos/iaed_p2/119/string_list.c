#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strdup.h"
#include "string_list.h"

link newNode(const char *str, link next)
{
/* cria um link com string */
  link x = (link) can_fail_malloc(sizeof(node));
  x->str = strdup(str);
  x->next = next;
  return x;
}

void freeStr(link x) {free(x->str); free(x);}

void append(link *L, const char *str)
{
/* coloca um string no fim de uma lista ligada */
  link x, y;
  if (*L == NULL)
  {
    *L = newNode(str, NULL);
    return;
  }
  x = *L;
  y = newNode(str, NULL);
  while (x->next != NULL) x = x->next;
  x->next = y;
  return;
}

void removeStr(link *L, const char *str)
/* remove um string de uma lista ligada, independentemente da posicao */
{
  link x = *L;
  if (strcmp(x->str, str) == 0)
  {
    *L = (*L)->next;
    freeStr(x);
    return;
  }
  while (x->next != NULL)
  {
    if (strcmp(x->next->str, str) == 0)
    {
      link tmp = x->next;
      x->next = x->next->next;
      freeStr(tmp);
      return;
    }
    x = x->next;
  }
}

void insertSorted(link *L, const char *equipa)
/* insere um string numa lista ligada segundo ordem lexicografica */
{
  link x, y;
  if (*L == NULL)
  {
    *L = newNode(equipa, NULL);
    return;
  }
  x = *L;
  if (strcmp(equipa, x->str) < 0)
  {
    link tmp = newNode(equipa, x);
    *L = tmp;
    return;
  }
  while (x->next != NULL)
  {
    if (strcmp(equipa, x->next->str) < 0)
    {
      y = newNode(equipa, x->next);
      x->next = y;
      return;
    }
    x = x->next;
  }
  x->next = newNode(equipa, NULL);
}

void freeList(link *L)
{
  link x;
  for (x = *L; x != NULL; x = x->next) freeStr(x);
}

void printList(link *L)
{
  link x;
  char *c;
  for (x = *L; x != NULL; x = x->next)
  {
    for (c = x->str; *c != '\0'; c++) printf("%c", *c);
    printf(" ");
  }
  printf("\n");
}	