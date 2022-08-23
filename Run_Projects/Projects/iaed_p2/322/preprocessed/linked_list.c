/*File generated by PreProcessor.py*/


#include "main.h"


Node_ptr init()
{
  Node_ptr top;
  top = 0;
  return top;
}

Node_ptr push(char *value, Node_ptr top)
{
  Node_ptr new;
  int size;
  new = malloc(sizeof(struct node));
  if (top == 0)
  {
    {
      new->value = value;
      new->next = 0;
      new->prev = 0;
      top = new;
      top->size = 0;
      top->first = top;
      return top;
    }
  }
  else
  {
    
  }

  new->value = value;
  new->next = top;
  new->first = top->first;
  new->prev = 0;
  top->prev = new;
  size = top->size;
  top = new;
  new->size = size + 1;
  return top;
}

int is_empty(Node_ptr top)
{
  return top == 0;
}

Node_ptr delete_index(int index, Node_ptr top)
{
  int amount;
  int counter;
  Node_ptr aux;
  amount = top->size - index;
  aux = top;
  for (counter = 0; counter < amount; counter++)
  {
    top->size = top->size - 1;
    top = top->next;
  }

  if ((top->prev == 0) && (top->next == 0))
  {
    {
      free(top);
      top = 0;
      return top;
    }
  }
  else
  {
    
  }

  if ((top->prev != 0) && (top->next != 0))
  {
    {
      top->prev->next = top->next;
      top->next->prev = top->prev;
    }
  }
  else
  {
    
  }

  if ((top->next == 0) && (top->prev != 0))
  {
    {
      top->prev->next = 0;
      aux->first = top->prev;
    }
  }
  else
  {
    
  }

  if ((top->prev == 0) && (top->next != 0))
  {
    {
      aux = top->next;
      aux->first = top->first;
      top->next->prev = 0;
    }
  }
  else
  {
    
  }

  free(top);
  return aux;
}

void clear_all(Node_ptr top)
{
  Node_ptr aux;
  while (top != 0)
  {
    aux = top->next;
    free(top);
    top = aux;
  }

  return;
}

void print_all(int side_flag, Node_ptr top)
{
  Node_ptr aux;
  aux = top;
  while (aux != 0)
  {
    printf("%d %s\n", aux->size, aux->value);
    if (side_flag == 1)
    {
      aux = aux->next;
    }
    else
    {
      aux = aux->prev;
    }

  }

  return;
}

Node_ptr get_index(int index, Node_ptr top)
{
  int amount;
  int counter;
  amount = top->size - index;
  for (counter = 0; counter < amount; counter++)
  {
    top = top->next;
  }

  return top;
}

