/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node
{
  long last;
  int amount;
  struct node *next;
} *Node;
typedef struct head
{
  Node node;
  Node tail;
} *Head;
Head create_head(long last, int amount)
{
  Head head = (Head) malloc(sizeof(struct head));
  head->node = (Node) malloc(sizeof(struct node));
  head->node->last = last;
  head->node->next = 0;
  head->node->amount = amount;
  head->tail = 0;
  return head;
}

Head insert(Head head, long last, int amount)
{
  Node child = (Node) malloc(sizeof(struct node));
  child->last = last;
  child->next = 0;
  child->amount = amount;
  if (head == 0)
  {
    free(child);
    return create_head(last, amount);
  }
  else
  {
    
  }

  if (head->node->last > last)
  {
    child->next = head->node;
    head->tail = head->node;
    head->node = child;
    return head;
  }
  else
  {
    
  }

  if (head->node->next == 0)
  {
    head->node->next = child;
    head->tail = child;
    return head;
  }
  else
  {
    
  }

  Node n;
  Node prev = head->node;
  for (n = head->node->next; n != 0; prev = n, n = n->next)
  {
    if (last < n->last)
    {
      prev->next = child;
      child->next = n;
      break;
    }
    else
    {
      
    }

    if (n->next == 0)
    {
      n->next = child;
      head->tail = child;
      break;
    }
    else
    {
      
    }

  }

  return head;
}

Head insert_tail(Head head, long last, int amount)
{
  if (head == 0)
  {
    return create_head(last, amount);
  }
  else
  {
    
  }

  Node new = (Node) malloc(sizeof(struct node));
  new->last = last;
  new->next = 0;
  new->amount = amount;
  if (head->tail == 0)
  {
    head->node->next = new;
  }
  else
  {
    head->tail->next = new;
  }

  head->tail = new;
  return head;
}

Node destroy(Node node)
{
  if (node->next != 0)
  {
    destroy(node->next);
  }
  else
  {
    
  }

  free(node);
  return 0;
}

void merge(long *a, int l, int m, int r, long *aux)
{
  int i;
  int j;
  int k;
  for (i = m + 1; i > l; i--)
    aux[i - 1] = a[i - 1];

  for (j = m; j < r; j++)
    aux[(r + m) - j] = a[j + 1];

  for (k = l; k <= r; k++)
  {
    if ((aux[j] < aux[i]) || (i > m))
    {
      a[k] = aux[j--];
    }
    else
    {
      a[k] = aux[i++];
    }

  }

}

void merge_sort(long *a, int l, int r, long *aux)
{
  int m = (r + l) / 2;
  if (r <= l)
  {
    return;
  }
  else
  {
    
  }

  merge_sort(a, l, m, aux);
  merge_sort(a, m + 1, r, aux);
  merge(a, l, m, r, aux);
}

int number_exists(long *a, int l, int r, long number)
{
  while (l <= r)
  {
    int m = (l + r) / 2;
    if (a[m] == number)
    {
      return 1;
    }
    else
    {
      
    }

    if (a[m] > number)
    {
      r = m - 1;
    }
    else
    {
      l = m + 1;
    }

  }

  return 0;
}

char *read_input()
{
  int i;
  int size = 500;
  char *input = (char *) malloc(size * (sizeof(int)));
  int c = getchar();
  for (i = 0; (c != '\n') && (c != EOF); i++)
  {
    input[i] = (char) c;
    if (size <= (i - 1))
    {
      size = size * 2;
      input = (char *) realloc(input, size * (sizeof(int)));
    }
    else
    {
      
    }

    c = getchar();
  }

  input[i] = '\0';
  return input;
}

long *read_sequence(char *input, int *length, int problem)
{
  int counter = 0;
  int size = 500;
  long *sequence = (long *) malloc(size * (sizeof(long)));
  char *number = strtok(input, " ");
  long number_converted;
  long smallest;
  sequence[counter] = atol(number);
  smallest = sequence[counter];
  counter++;
  while ((number = strtok(0, " ")) != 0)
  {
    if (size < (counter + 1))
    {
      size = size * 2;
      sequence = (long *) realloc(sequence, size * (sizeof(long)));
    }
    else
    {
      
    }

    number_converted = atol(number);
    if (((number_converted != sequence[counter - 1]) && (smallest != number_converted)) || (problem == 1))
    {
      sequence[counter] = number_converted;
      if (smallest > number_converted)
      {
        smallest = number_converted;
      }
      else
      {
        
      }

      counter++;
    }
    else
    {
      
    }

  }

  *length = counter;
  return sequence;
}

long *read_second_sequence(char *input, int *length, long *first_sequence, int first_length)
{
  int counter = 0;
  int size = 500;
  long *sequence = (long *) malloc(size * (sizeof(long)));
  char *number = strtok(input, " ");
  long number_converted;
  long smallest;
  sequence[counter] = atol(number);
  smallest = sequence[counter];
  counter++;
  while ((number = strtok(0, " ")) != 0)
  {
    if (size < (counter + 1))
    {
      size = size * 2;
      sequence = (long *) realloc(sequence, size * (sizeof(long)));
    }
    else
    {
      
    }

    number_converted = atol(number);
    if (((number_converted != sequence[counter - 1]) && (smallest != number_converted)) && number_exists(first_sequence, 0, first_length - 1, number_converted))
    {
      sequence[counter] = number_converted;
      if (smallest > number_converted)
      {
        smallest = number_converted;
      }
      else
      {
        
      }

      counter++;
    }
    else
    {
      
    }

  }

  *length = counter;
  return sequence;
}

int max(int *array, int length)
{
  int i;
  int result = 0;
  for (i = 0; i < length; i++)
  {
    if (array[i] > result)
    {
      result = array[i];
    }
    else
    {
      
    }

  }

  return result;
}

void execute_problem1()
{
  char *input = read_input();
  int x_length;
  long *x_sequence;
  x_sequence = read_sequence(input, &x_length, 1);
  free(input);
  int i;
  int j;
  int max_length;
  int max_last;
  int min_last;
  int number_sequences;
  Node n;
  Head lengths[x_length];
  for (i = 1; i < x_length; i++)
    lengths[i] = 0;

  lengths[0] = create_head(x_sequence[0], 1);
  max_length = 1;
  max_last = lengths[0]->node->last;
  min_last = lengths[0]->node->last;
  for (i = 1; i < x_length; i++)
  {
    if (max_last < x_sequence[i])
    {
      max_last = x_sequence[i];
      number_sequences = 0;
      for (n = lengths[max_length - 1]->node; n != 0; n = n->next)
      {
        number_sequences += n->amount;
      }

      lengths[max_length] = insert_tail(lengths[max_length], x_sequence[i], number_sequences);
      max_length++;
    }
    else
    {
      if (min_last >= x_sequence[i])
      {
        min_last = x_sequence[i];
        lengths[0] = insert(lengths[0], x_sequence[i], 1);
      }
      else
      {
        int found = 0;
        for (j = max_length - 1; j >= 0; j--)
        {
          number_sequences = 0;
          for (n = lengths[j]->node; n != 0; n = n->next)
          {
            if (n->last < x_sequence[i])
            {
              if ((j + 2) > max_length)
              {
                max_length = j + 2;
              }
              else
              {
                
              }

              number_sequences += n->amount;
              found = 1;
            }
            else
            {
              break;
            }

          }

          if (found == 1)
          {
            lengths[j + 1] = insert(lengths[j + 1], x_sequence[i], number_sequences);
            break;
          }
          else
          {
            
          }

        }

      }

    }

  }

  int number_sequences_max_length = 0;
  for (n = lengths[max_length - 1]->node; n != 0; n = n->next)
    number_sequences_max_length += n->amount;

  printf("%d %d\n", max_length, number_sequences_max_length);
  for (i = 0; i < max_length; i++)
  {
    destroy(lengths[i]->node);
    free(lengths[i]);
  }

  free(x_sequence);
}

void execute_problem2()
{
  char *input;
  int x_length;
  int y_length;
  long *x_sequence;
  long *x_sorted;
  long *x_aux;
  long *y_sequence;
  input = read_input();
  x_sequence = read_sequence(input, &x_length, 2);
  free(input);
  x_sorted = (long *) malloc(x_length * (sizeof(long)));
  x_aux = (long *) malloc(x_length * (sizeof(long)));
  memcpy(x_sorted, x_sequence, x_length * (sizeof(long)));
  merge_sort(x_sorted, 0, x_length - 1, x_aux);
  free(x_aux);
  input = read_input();
  y_sequence = read_second_sequence(input, &y_length, x_sorted, x_length);
  free(input);
  free(x_sorted);
  int longest[y_length];
  memset(longest, 0, y_length * (sizeof(int)));
  int i;
  int j;
  for (i = 0; i < x_length; i++)
  {
    int length = 0;
    for (j = 0; j < y_length; j++)
    {
      if (x_sequence[i] == y_sequence[j])
      {
        if ((length + 1) > longest[j])
        {
          longest[j] = length + 1;
        }
        else
        {
          
        }

      }
      else
      {
        if (x_sequence[i] > y_sequence[j])
        {
          if (longest[j] > length)
          {
            length = longest[j];
          }
          else
          {
            
          }

        }
        else
        {
          
        }

      }

    }

  }

  printf("%d\n", max(longest, y_length));
  free(x_sequence);
  free(y_sequence);
}

int main()
{
  char *problem = malloc((sizeof(char)) * 3);
  problem = fgets(problem, 3, stdin);
  switch (problem[0])
  {
    case '1':
    {
      execute_problem1();
      break;
    }

    case '2':
    {
      execute_problem2();
      break;
    }

    default:
      break;

  }

  free(problem);
  return 0;
}

