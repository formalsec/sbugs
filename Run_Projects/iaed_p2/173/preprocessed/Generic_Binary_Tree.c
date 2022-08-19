/*File generated by PreProcessor.py*/


#include "Generic_Binary_Tree.h"


BTlink btnode_create(void *data, int size)
{
  int i;
  BTlink node = (BTlink) malloc(sizeof(struct BTnode));
  node->l = 0;
  node->r = 0;
  node->height = 1;
  node->data = malloc(size);
  for (i = 0; i < size; i++)
  {
    *(((char *) node->data) + i) = *(((char *) data) + i);
  }

  free(data);
  return node;
}

BTlink bintree_create()
{
  return 0;
}

void *bintree_search(BTlink head, void *info, void *(*get_info)(void *), int (*compare)(void *, void *))
{
  int aux;
  if (head == 0)
  {
    return 0;
  }
  else
  {
    
  }

  aux = compare(info, get_info(head->data));
  if (aux == 0)
  {
    {
      return head->data;
    }
  }
  else
  {
    if ((head->l == 0) && (head->r == 0))
    {
      {
        return 0;
      }
    }
    else
    {
      {
        if (aux > 0)
        {
          {
            return bintree_search(head->l, info, get_info, compare);
          }
        }
        else
        {
          {
            return bintree_search(head->r, info, get_info, compare);
          }
        }

      }
    }

  }

}

BTlink bintree_max(BTlink head)
{
  if (head->r == 0)
  {
    {
      return head;
    }
  }
  else
  {
    {
      return bintree_max(head->r);
    }
  }

}

BTlink bintree_min(BTlink head)
{
  if (head->l == 0)
  {
    {
      return head;
    }
  }
  else
  {
    {
      return bintree_min(head->l);
    }
  }

}

void btnode_free(BTlink node, void (*free_data)(void *))
{
  free_data(node->data);
  free(node);
}

void bintree_free(BTlink head, void (*free_data)(void *))
{
  if (head == 0)
  {
    {
      return;
    }
  }
  else
  {
    
  }

  if (head->r != 0)
  {
    {
      bintree_free(head->r, free_data);
    }
  }
  else
  {
    
  }

  if (head->l != 0)
  {
    {
      bintree_free(head->l, free_data);
    }
  }
  else
  {
    
  }

  btnode_free(head, free_data);
}

int bintree_height(BTlink head)
{
  if (head == 0)
  {
    return 0;
  }
  else
  {
    
  }

  return head->height;
}

BTlink rotL(BTlink head)
{
  int hleft;
  int hright;
  int xleft;
  int xright;
  BTlink x = head->r;
  head->r = x->l;
  x->l = head;
  hleft = bintree_height(head->l);
  hright = bintree_height(head->r);
  head->height = (hleft > hright) ? (hleft + 1) : (hright + 1);
  xleft = bintree_height(x->l);
  xright = bintree_height(x->r);
  x->height = (xleft > xright) ? (xleft + 1) : (xright + 1);
  return x;
}

BTlink rotR(BTlink head)
{
  int hleft;
  int hright;
  int xleft;
  int xright;
  BTlink x = head->l;
  head->l = x->r;
  x->r = head;
  hleft = bintree_height(head->l);
  hright = bintree_height(head->r);
  head->height = (hleft > hright) ? (hleft + 1) : (hright + 1);
  xleft = bintree_height(x->l);
  xright = bintree_height(x->r);
  x->height = (xleft > xright) ? (xleft + 1) : (xright + 1);
  return x;
}

BTlink rotLR(BTlink head)
{
  if (head == 0)
  {
    return head;
  }
  else
  {
    
  }

  head->l = rotL(head->l);
  return rotR(head);
}

BTlink rotRL(BTlink head)
{
  if (head == 0)
  {
    return head;
  }
  else
  {
    
  }

  head->r = rotR(head->r);
  return rotL(head);
}

int bintree_balance(BTlink head)
{
  if (head == 0)
  {
    return 0;
  }
  else
  {
    
  }

  return bintree_height(head->l) - bintree_height(head->r);
}

BTlink bintree_AVLbalance(BTlink head)
{
  int balanceFactor;
  int hleft;
  int hright;
  if (head == 0)
  {
    return head;
  }
  else
  {
    
  }

  balanceFactor = bintree_balance(head);
  if (balanceFactor > 1)
  {
    {
      if (bintree_balance(head->l) >= 0)
      {
        {
          head = rotR(head);
        }
      }
      else
      {
        {
          head = rotLR(head);
        }
      }

    }
  }
  else
  {
    if (balanceFactor < (-1))
    {
      {
        if (bintree_balance(head->r) <= 0)
        {
          {
            head = rotL(head);
          }
        }
        else
        {
          {
            head = rotRL(head);
          }
        }

      }
    }
    else
    {
      {
        hleft = bintree_height(head->l);
        hright = bintree_height(head->r);
        head->height = (hleft > hright) ? (hleft + 1) : (hright + 1);
      }
    }

  }

  return head;
}

int bintree_add_item_aux(BTlink *head, BTlink node, void *(*get_info)(void *), int (*compare)(void *, void *))
{
  int aux = compare(get_info((*head)->data), get_info(node->data));
  int res = 0;
  if (aux == 0)
  {
    return 1;
  }
  else
  {
    
  }

  if (aux > 0)
  {
    {
      if ((*head)->r == 0)
      {
        {
          (*head)->r = node;
        }
      }
      else
      {
        {
          res = bintree_add_item_aux(&(*head)->r, node, get_info, compare);
        }
      }

    }
  }
  else
  {
    {
      if ((*head)->l == 0)
      {
        {
          (*head)->l = node;
        }
      }
      else
      {
        {
          res = bintree_add_item_aux(&(*head)->l, node, get_info, compare);
        }
      }

    }
  }

  *head = bintree_AVLbalance(*head);
  return res;
}

int bintree_add_item(BTlink *head, void *data, int size, void (*free_data)(void *), void *(*get_info)(void *), int (*compare)(void *, void *))
{
  BTlink node = btnode_create(data, size);
  if ((*head) != 0)
  {
    {
      if (bintree_add_item_aux(head, node, get_info, compare))
      {
        {
          btnode_free(node, free_data);
          return 1;
        }
      }
      else
      {
        
      }

      return 0;
    }
  }
  else
  {
    {
      *head = node;
      return 0;
    }
  }

}

void bintree_delete_item(BTlink *head, void *info, void *(*get_info)(void *), void (*free_data)(void *), int (*compare)(void *, void *))
{
  int cmp_aux = compare(info, get_info((*head)->data));
  BTlink aux;
  void *data_aux;
  if (cmp_aux != 0)
  {
    {
      if (cmp_aux > 0)
      {
        {
          if ((*head)->l == 0)
          {
            return;
          }
          else
          {
            
          }

          bintree_delete_item(&(*head)->l, info, get_info, free_data, compare);
        }
      }
      else
      {
        {
          if ((*head)->r == 0)
          {
            return;
          }
          else
          {
            
          }

          bintree_delete_item(&(*head)->r, info, get_info, free_data, compare);
        }
      }

    }
  }
  else
  {
    {
      if (((*head)->r != 0) && ((*head)->l != 0))
      {
        {
          aux = bintree_max((*head)->l);
          data_aux = (*head)->data;
          (*head)->data = aux->data;
          aux->data = data_aux;
          bintree_delete_item(&(*head)->l, get_info(aux->data), get_info, free_data, compare);
        }
      }
      else
      {
        {
          aux = *head;
          if (((*head)->l == 0) && ((*head)->r == 0))
          {
            {
              *head = 0;
            }
          }
          else
          {
            if ((*head)->l == 0)
            {
              {
                *head = (*head)->r;
              }
            }
            else
            {
              {
                *head = (*head)->l;
              }
            }

          }

          btnode_free(aux, free_data);
        }
      }

    }
  }

  *head = bintree_AVLbalance(*head);
}

void bintree_array_aux(BTlink head, void **array, int *i, int size)
{
  if (head == 0)
  {
    return;
  }
  else
  {
    
  }

  bintree_array_aux(head->l, array, i, size);
  array[(*i)++] = head->data;
  bintree_array_aux(head->r, array, i, size);
}

void bintree_array(BTlink head, void **array, int size)
{
  int i = 0;
  bintree_array_aux(head, array, &i, size);
}

void bintree_to_list_condition_aux(BTlink head, Link *lista, void (*condition)(void *, Link *))
{
  if (head == 0)
  {
    return;
  }
  else
  {
    
  }

  bintree_to_list_condition_aux(head->l, lista, condition);
  condition(head->data, lista);
  bintree_to_list_condition_aux(head->r, lista, condition);
}

Link bintree_to_list_condition(BTlink head, void (*condition)(void *, Link *))
{
  Link lista = linkedlist_create();
  bintree_to_list_condition_aux(head, &lista, condition);
  return lista;
}
