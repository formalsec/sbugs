/*File generated by PreProcessor.py*/


#include "hashTeam.h"


LinkTeam push_team(LinkTeam head, ItemTeam item)
{
  LinkTeam aux = new_node_team(item, head);
  return aux;
}

ItemTeam search_list_team(LinkTeam head, char *name)
{
  LinkTeam t;
  for (t = head; t != 0; t = t->next)
  {
    if (strcmp(t->item->name, name) == 0)
    {
      return t->item;
    }
    else
    {
      
    }

  }

  return 0;
}

void destroy_list_team(LinkTeam head)
{
  LinkTeam t;
  LinkTeam aux;
  if (head == 0)
  {
    return;
  }
  else
  {
    
  }

  for (t = head, aux = head->next; t != 0; aux = t->next, delete_node_team(t), t = aux)
  {
  }

}

LinkTeam *HASHinit_team()
{
  int i;
  LinkTeam *heads = malloc(1009 * (sizeof(LinkTeam)));
  for (i = 0; i < 1009; i++)
  {
    heads[i] = 0;
  }

  return heads;
}

int hash_team(char *v)
{
  int h = 0;
  for (; (*v) != '\0'; v++)
  {
    h = ((127 * h) + (*v)) % 1009;
  }

  return h;
}

LinkTeam new_node_team(ItemTeam item, LinkTeam head)
{
  LinkTeam x = malloc(sizeof(NodeTeam));
  x->item = item;
  x->next = head;
  return x;
}

void delete_node_team(LinkTeam nodeTeam)
{
  deleteItem_team(nodeTeam->item);
  free(nodeTeam);
}

void insert_team(LinkTeam *heads, ItemTeam item)
{
  int i = hash_team(item->name);
  heads[i] = push_team(heads[i], item);
}

ItemTeam search_team(LinkTeam *heads, char *name)
{
  int i = hash_team(name);
  return search_list_team(heads[i], name);
}

void destroy_hash_team(LinkTeam *heads)
{
  int i;
  for (i = 0; i < 1009; i++)
  {
    destroy_list_team(heads[i]);
  }

  free(heads);
}

