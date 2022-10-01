/*File generated by PreProcessor.py*/


#include "Generic_Linked_List.h"


Link linkedlist_create()
{
  return 0;
}

Link create_node(void *data, int size)
{
  int i;
  Link node_link = (Link) malloc(sizeof(Node));
  node_link->next = 0;
  node_link->length = 0;
  node_link->data = malloc(size);
  for (i = 0; i < size; i++)
  {
    *(((char *) node_link->data) + i) = *(((char *) data) + i);
  }

  return node_link;
}

void free_node(Link head, void (*free_data)(void *))
{
  free_data(head->data);
  free(head);
}

void linkedlist_add_item(Link *list, void *data, int size)
{
  if ((*list) == 0)
  {
    *list = create_node(data, size);
    linkedlist_set_length(*list, 1);
    return;
  }
  else
  {
    
  }

  linkedlist_add_item(&(*list)->next, data, size);
  linkedlist_set_length(*list, linkedlist_get_length(*list) + 1);
}

void delete_item_aux(Link previous, Link item, void (*free_data)(void *))
{
  Link aux = item;
  previous->next = item->next;
  free_node(aux, free_data);
}

void linkedlist_delete_item_aux(Link *head, int i, int *count, void (*free_data)(void *))
{
  if ((*head)->next == 0)
  {
    return;
  }
  else
  {
    
  }

  if ((*count) != (i - 1))
  {
    (*count)++;
    linkedlist_delete_item_aux(&(*head)->next, i, count, free_data);
  }
  else
  {
    delete_item_aux(*head, (*head)->next, free_data);
  }

}

void linkedlist_delete_item(Link *head, int i, void (*free_data)(void *))
{
  int count = 0;
  if ((*head) == 0)
  {
    free_node(*head, free_data);
    *head = 0;
  }
  else
  {
    
  }

  linkedlist_delete_item_aux(head, i, &count, free_data);
}

void linkedlist_delete_item_cmp_aux(Link *head, void *info, void *(*get_info)(void *), void (*free_data)(void *), int (*compare)(void *, void *))
{
  if ((*head)->next == 0)
  {
    return;
  }
  else
  {
    
  }

  if (compare(info, get_info((*head)->next->data)))
  {
    delete_item_aux(*head, (*head)->next, free_data);
    return;
  }
  else
  {
    
  }

  linkedlist_delete_item_cmp_aux(&(*head)->next, info, get_info, free_data, compare);
}

void linkedlist_delete_item_cmp(Link *head, void *info, void *(*get_info)(void *), void (*free_data)(void *), int (*compare)(void *, void *))
{
  if ((*head) == 0)
  {
    return;
  }
  else
  {
    
  }

  if (compare(info, get_info((*head)->data)))
  {
    free_node(*head, free_data);
    *head = 0;
    return;
  }
  else
  {
    
  }

  linkedlist_delete_item_cmp_aux(head, info, get_info, free_data, compare);
}

void linkedlist_free(Link head, void (*free_data)(void *))
{
  if (head != 0)
  {
    linkedlist_free(head->next, free_data);
    free_node(head, free_data);
  }
  else
  {
    
  }

}

void linkedlist_traverse(Link head, void (*func)(void *))
{
  if (head != 0)
  {
    func(head->data);
    linkedlist_traverse(head->next, func);
  }
  else
  {
    
  }

}

void *linkedlist_get_item_aux(Link head, int i, int *count)
{
  if (head == 0)
  {
    return 0;
  }
  else
  {
    
  }

  if (i != (*count))
  {
    (*count)++;
    return linkedlist_get_item_aux(head->next, i, count);
  }
  else
  {
    
  }

  return head->data;
}

void *linkedlist_get_item(Link head, int i)
{
  int count = 0;
  return linkedlist_get_item_aux(head, i, &count);
}

void *linkedlist_get_item_cmp(Link head, void *info, void *(*get_info)(void *), int (*compare)(void *, void *))
{
  int cmp_aux;
  if (head == 0)
  {
    return 0;
  }
  else
  {
    
  }

  cmp_aux = compare(info, get_info(head->data));
  if (cmp_aux)
  {
    return head->data;
  }
  else
  {
    return linkedlist_get_item_cmp(head->next, info, get_info, compare);
  }

}

Link linkedlist_reset(Link head, void (*free_data)(void *))
{
  linkedlist_free(head, free_data);
  return 0;
}

void linkedlist_set_length(Link head, int n)
{
  if (head == 0)
  {
    return;
  }
  else
  {
    
  }

  head->length = n;
}

int linkedlist_get_length(Link head)
{
  if (head == 0)
  {
    return 0;
  }
  else
  {
    
  }

  return head->length;
}
