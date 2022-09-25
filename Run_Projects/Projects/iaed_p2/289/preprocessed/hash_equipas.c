/*File generated by PreProcessor.py*/


#include "hash_equipas.h"


long hashUeq(char *v, int m)
{
  long h;
  long a = 31415;
  long b = 27183;
  for (h = 0; (*v) != '\0'; v++, a = (a * b) % (m - 1))
    h = ((a * h) + (*v)) % m;

  return h;
}

link_eq *HT_eq_init(int m)
{
  link_eq *heads = calloc(m, sizeof(link_eq));
  return heads;
}

link_eq insertEqBeginList(link_eq head, ptr_equipa link_team)
{
  if (head == 0)
  {
    link_eq first_node = malloc(sizeof(struct node_eq));
    first_node->link_team = link_team;
    first_node->next = 0;
    return first_node;
  }
  else
  {
    link_eq new_node = malloc(sizeof(struct node_eq));
    new_node->link_team = link_team;
    new_node->next = head;
    return new_node;
  }

}

void HT_eq_insert(ptr_equipa link_team, link_eq *heads_eq, int m)
{
  long i = hashUeq(link_team->nome, m);
  heads_eq[i] = insertEqBeginList(heads_eq[i], link_team);
}

ptr_equipa searchEqList(link_eq head, Key_equipa c)
{
  link_eq t;
  for (t = head; t != 0; t = t->next)
  {
    if (strcmp(t->link_team->nome, c) == 0)
    {
      return t->link_team;
    }
    else
    {
      
    }

  }

  return 0;
}

ptr_equipa HT_eq_search(Key_equipa c, link_eq *heads_eq, int m)
{
  long i = hashUeq(c, m);
  return searchEqList(heads_eq[i], c);
}

void HT_eq_destroy(link_eq *heads_eq, int m)
{
  long i;
  link_eq temp = 0;
  link_eq aux = 0;
  for (i = 0; i < m; i++)
  {
    temp = heads_eq[i];
    while (temp != 0)
    {
      aux = temp;
      temp = temp->next;
      freeEquipa(aux->link_team);
      free(aux);
    }

  }

  free(heads_eq);
}

