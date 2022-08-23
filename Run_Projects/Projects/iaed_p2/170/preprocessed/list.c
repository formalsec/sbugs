/*File generated by PreProcessor.py*/


#include "list.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Node NewNode(char *name)
{
  Node new = (Node) malloc(sizeof(node));
  new->name = NewString(name);
  new->next = 0;
  return new;
}

void DeleteNode(Node node)
{
  free(node->name);
  free(node);
}

List NewList()
{
  List new_list = (List) malloc(sizeof(list));
  new_list->head = 0;
  new_list->tail = 0;
  return new_list;
}

void Append_List(List list, char *name)
{
  Node new = NewNode(name);
  if (!list->head)
  {
    {
      list->head = new;
      list->tail = new;
      return;
    }
  }
  else
  {
    
  }

  list->tail->next = new;
  list->tail = new;
}

void Remove_List(List list, char *name)
{
  Node tmp_aux = 0;
  Node tmp = list->head;
  while (strcmp(tmp->name, name) != 0)
  {
    tmp_aux = tmp;
    tmp = tmp->next;
  }

  if (tmp == list->head)
  {
    {
      list->head = tmp->next;
    }
  }
  else
  {
    {
      tmp_aux->next = tmp->next;
    }
  }

  if (tmp == list->tail)
  {
    {
      list->tail = tmp_aux;
    }
  }
  else
  {
    
  }

  DeleteNode(tmp);
}

void Delete_List(List list)
{
  Node aux;
  while (list->head != 0)
  {
    aux = list->head->next;
    DeleteNode(list->head);
    list->head = aux;
  }

  free(list);
}

