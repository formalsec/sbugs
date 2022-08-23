/*File generated by PreProcessor.py*/


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int result = 0;
long offset = 0;
typedef struct cross
{
  int tipo;
  int visited;
  int parent_avn;
  int parent_rua;
} *Cross;
typedef struct pair
{
  int avn;
  int rua;
} *Pair;
typedef struct node
{
  Pair coord;
  struct node *next;
} *link;
typedef struct queue
{
  link head;
  link tail;
  int size;
} *queue_t;
link newNode(Pair coord, link head)
{
  link x = (link) malloc(sizeof(struct node));
  x->coord = coord;
  x->next = head;
  return x;
}

void initQueue(queue_t queue)
{
  queue->head = 0;
  queue->tail = 0;
  queue->size = 0;
}

bool emptyQueue(queue_t queue)
{
  return queue->head == 0;
}

void push(queue_t queue, Pair coord)
{
  if (queue->head == 0)
  {
    queue->head = (queue->tail = newNode(coord, queue->head));
    return;
  }
  else
  {
    
  }

  queue->tail->next = newNode(coord, queue->tail->next);
  queue->tail = queue->tail->next;
  queue->size++;
}

Pair pop(queue_t queue)
{
  link x;
  Pair coord;
  coord = queue->head->coord;
  x = queue->head->next;
  free(queue->head);
  queue->head = x;
  queue->size--;
  return coord;
}

void debug(Cross **cross_table, int n_avn, int n_ruas)
{
  int i;
  int j;
  for (i = 0; i < n_ruas; i++)
  {
    puts("");
    for (j = 0; j < n_avn; j++)
    {
      printf("[ %d | %d ]  ", cross_table[j][i]->tipo, cross_table[j][i]->visited);
    }

  }

  puts("");
}

bool bfs(Cross **cross_table, int avn, int rua, int i, int n_avn, int n_ruas, int n_cid, bool verifica)
{
  int x;
  int y;
  int a;
  int r;
  int k;
  int j;
  bool found = false;
  bool ver = verifica;
  Pair coordenates = (Pair) malloc(sizeof(struct pair));
  Pair current;
  Pair child;
  Pair market;
  Pair destination;
  Pair maybe_path;
  Pair maybe_parent;
  Cross temp;
  queue_t queue = (queue_t) malloc(sizeof(struct queue));
  initQueue(queue);
  queue_t potential = (queue_t) malloc(sizeof(struct queue));
  initQueue(potential);
  Cross cid = cross_table[avn][rua];
  if (cid->visited != (-1))
  {
    cid->visited = i;
  }
  else
  {
    
  }

  coordenates->avn = avn;
  coordenates->rua = rua;
  push(queue, coordenates);
  while (!emptyQueue(queue))
  {
    current = pop(queue);
    x = current->avn;
    y = current->rua;
    if (cross_table[x][y]->visited == (-1))
    {
      break;
    }
    else
    {
      
    }

    if (cross_table[x][y]->tipo == 3)
    {
      cross_table[x][y]->visited = -1;
      result++;
      return true;
    }
    else
    {
      
    }

    int c;
    for (c = 0; c < 4; c++)
    {
      if (c == 0)
      {
        k = x + 1;
        j = y;
      }
      else
      {
        if (c == 1)
        {
          k = x - 1;
          j = y;
        }
        else
        {
          if (c == 2)
          {
            k = x;
            j = y - 1;
          }
          else
          {
            k = x;
            j = y + 1;
          }

        }

      }

      if ((k >= n_avn) || (k < 0))
      {
        k = x;
      }
      else
      {
        
      }

      if ((j >= n_ruas) || (j < 0))
      {
        j = y;
      }
      else
      {
        
      }

      if (cross_table[k][j]->tipo == 1)
      {
        if (cross_table[k][j]->visited != i)
        {
          market = (Pair) malloc(sizeof(struct pair));
          market->avn = k;
          market->rua = j;
          maybe_parent = (Pair) malloc(sizeof(struct pair));
          maybe_parent->avn = x;
          maybe_parent->rua = y;
          push(potential, market);
          push(potential, maybe_parent);
          if (cross_table[k][j]->visited != (-1))
          {
            cross_table[k][j]->parent_avn = x;
            cross_table[k][j]->parent_rua = y;
            while (true)
            {
              temp = cross_table[k][j];
              cross_table[k][j]->visited = -1;
              if (!((k == avn) && (j == rua)))
              {
                k = temp->parent_avn;
                j = temp->parent_rua;
              }
              else
              {
                break;
              }

            }

            if (!ver)
            {
              result++;
            }
            else
            {
              
            }

            while (!emptyQueue(potential))
            {
              pop(potential);
              pop(potential);
            }

            free(potential);
            return true;
          }
          else
          {
            
          }

        }
        else
        {
          
        }

      }
      else
      {
        if (((cross_table[k][j]->visited != i) && (cross_table[k][j]->tipo == 0)) && (cross_table[k][j]->visited != (-1)))
        {
          cross_table[k][j]->parent_avn = x;
          cross_table[k][j]->parent_rua = y;
          cross_table[k][j]->visited = i;
          child = (Pair) malloc(sizeof(struct pair));
          child->avn = k;
          child->rua = j;
          push(queue, child);
        }
        else
        {
          
        }

      }

    }

  }

  while (!emptyQueue(potential))
  {
    destination = pop(potential);
    maybe_path = pop(potential);
    if (!ver)
    {
      a = destination->avn;
      r = destination->rua;
      k = cross_table[a][r]->parent_avn;
      j = cross_table[a][r]->parent_rua;
      while (true)
      {
        temp = cross_table[k][j];
        cross_table[k][j]->visited = n_cid + offset;
        if (cross_table[k][j]->tipo != 2)
        {
          k = temp->parent_avn;
          j = temp->parent_rua;
        }
        else
        {
          break;
        }

      }

      found = bfs(cross_table, k, j, n_cid + offset, n_avn, n_ruas, n_cid, true);
      if (found)
      {
        k = maybe_path->avn;
        j = maybe_path->rua;
        while (true)
        {
          temp = cross_table[k][j];
          cross_table[k][j]->visited = -1;
          if (cross_table[k][j]->tipo != 2)
          {
            k = temp->parent_avn;
            j = temp->parent_rua;
          }
          else
          {
            result++;
            break;
          }

        }

      }
      else
      {
        a = destination->avn;
        r = destination->rua;
        k = cross_table[a][r]->parent_avn;
        j = cross_table[a][r]->parent_rua;
        while (true)
        {
          temp = cross_table[k][j];
          cross_table[k][j]->visited = -1;
          if (cross_table[k][j]->tipo != 2)
          {
            k = temp->parent_avn;
            j = temp->parent_rua;
          }
          else
          {
            break;
          }

        }

      }

      offset++;
    }
    else
    {
      
    }

  }

  free(potential);
  while (!emptyQueue(queue))
  {
    pop(queue);
  }

  free(queue);
  return false;
}

int main(int argc, char **argv)
{
  int n_ruas;
  int n_avn;
  int n_merc;
  int n_cid;
  int i;
  int j;
  int x;
  int y;
  if (2 != 2)
  {
    perror("error reading file");
    return 1;
  }
  else
  {
    n_avn = new_sym_var(sizeof(int) * 8);
    n_ruas = new_sym_var(sizeof(int) * 8);
    
  }

  if (2 != 2)
  {
    perror("error reading file");
    return 1;
  }
  else
  {
    n_merc = new_sym_var(sizeof(int) * 8);
    n_cid = new_sym_var(sizeof(int) * 8);
    
  }

  Cross **cross_table = (Cross **) malloc(n_avn * (sizeof(Cross *)));
  for (i = 0; i < n_avn; i++)
  {
    cross_table[i] = (Cross *) malloc(n_ruas * (sizeof(Cross)));
    for (j = 0; j < n_ruas; j++)
    {
      cross_table[i][j] = (Cross) malloc(sizeof(struct cross));
      cross_table[i][j]->tipo = 0;
      cross_table[i][j]->visited = -2;
    }

  }

  Pair *citizens = (Pair *) malloc(n_cid * (sizeof(Pair)));
  for (i = 0; i < n_merc; i++)
  {
    if (2 != 2)
    {
      perror("error reading file");
      return 1;
    }
    else
    {
      x = new_sym_var(sizeof(int) * 8);
      y = new_sym_var(sizeof(int) * 8);
      
    }

    cross_table[x - 1][y - 1]->tipo = 1;
  }

  for (i = 0; i < n_cid; i++)
  {
    if (2 != 2)
    {
      perror("error reading file");
      return 1;
    }
    else
    {
      x = new_sym_var(sizeof(int) * 8);
      y = new_sym_var(sizeof(int) * 8);
      
    }

    if ((cross_table[x - 1][y - 1]->tipo == 1) || (cross_table[x - 1][y - 1]->tipo == 3))
    {
      cross_table[x - 1][y - 1]->tipo = 3;
    }
    else
    {
      cross_table[x - 1][y - 1]->tipo = 2;
    }

    citizens[i] = (Pair) malloc(sizeof(struct pair));
    citizens[i]->avn = x - 1;
    citizens[i]->rua = y - 1;
  }

  for (i = 0; i < n_cid; i++)
  {
    bfs(cross_table, citizens[i]->avn, citizens[i]->rua, i, n_avn, n_ruas, n_cid, false);
  }

  printf("%d\n", result);
  return 0;
}

