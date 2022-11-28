#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


enum nodeType
{
  SHOP,
  PERSON,
  BOTH,
  NONE
};
typedef struct listNode
{
  struct listNode *next;
  void *value;
  int flag;
} listNode;
typedef struct list
{
  listNode *end;
  listNode *start;
} list;
typedef struct node
{
  int x;
  int y;
  listNode *in;
  listNode *out;
  struct node *prev;
  int full;
  int tmp;
  char type;
} node;
typedef struct corner
{
  node *left;
  node *right;
  enum nodeType type;
} corner;
void initList(list *s)
{
  s->end = 0;
  s->start = 0;
}

node *sink;
node *source;
corner **map;
int M;
int N;
int S;
int P;
int total;
void join(list *s, node *v)
{
  if (!s)
  {
    return;
  }
  else
  {
    
  }

  listNode *tmp = malloc(sizeof(listNode));
  tmp->value = v;
  tmp->next = 0;
  if (s->end)
  {
    s->end->next = tmp;
    s->end = tmp;
  }
  else
  {
    s->start = (s->end = tmp);
  }

}

node *query(list *s)
{
  if ((!s) || (!s->start))
  {
    return 0;
  }
  else
  {
    
  }

  listNode *tmp = s->start;
  node *tmpN = tmp->value;
  s->start = s->start->next;
  if (!s->start)
  {
    s->end = 0;
  }
  else
  {
    
  }

  free(tmp);
  return tmpN;
}

node *createNode(int x, int y, char t)
{
  node *tmp = malloc(sizeof(node));
  tmp->x = x;
  tmp->y = y;
  tmp->prev = 0;
  tmp->in = (tmp->out = 0);
  tmp->full = 0;
  tmp->tmp = 0;
  tmp->type = t;
  return tmp;
}

int bfs()
{
  list s;
  node *u;
  listNode *tmp;
  initList(&s);
  join(&s, source);
  while (s.start)
  {
    u = query(&s);
    if (u->tmp)
    {
      tmp = u->out;
      while (tmp)
      {
        if ((((node *) tmp->value)->prev == 0) && (((node *) tmp->value) != source))
        {
          ((node *) tmp->value)->prev = u;
          if (((node *) tmp->value) == sink)
          {
            while (query(&s))
              ;

            return 1;
          }
          else
          {
            join(&s, (node *) tmp->value);
          }

        }
        else
        {
          
        }

        tmp = tmp->next;
      }

    }
    else
    {
      
    }

    if (u->full)
    {
      tmp = u->in;
    }
    else
    {
      tmp = u->out;
    }

    while (tmp)
    {
      if ((((node *) tmp->value)->prev == 0) && (((node *) tmp->value) != source))
      {
        if ((u->in != 0) && (u->full == 0))
        {
          printf("err%d %d %p %d %c\n", map[2][2].right->x, map[2][2].right->y, map[2][2].right->in, map[2][2].right->full, map[2][2].right->type);
        }
        else
        {
          
        }

        ((node *) tmp->value)->prev = u;
        if (u->full)
        {
          ((node *) tmp->value)->tmp = 1;
        }
        else
        {
          
        }

        if (((node *) tmp->value) == sink)
        {
          while (query(&s))
            ;

          return 1;
        }
        else
        {
          join(&s, (node *) tmp->value);
        }

      }
      else
      {
        
      }

      tmp = tmp->next;
    }

  }

  return 0;
}

void connect(node *n1, node *n2)
{
  listNode *tmp = malloc(sizeof(listNode));
  tmp->value = n2;
  tmp->next = n1->out;
  n1->out = tmp;
}

int isConnected(node *n1, node *n2)
{
  listNode *tmp = n1->out;
  while (tmp)
  {
    if (((node *) tmp->value) == n2)
    {
      return 1;
    }
    else
    {
      
    }

    tmp = tmp->next;
  }

  return 0;
}

void pair(node *n1, node *n2)
{
  if ((!n1) || (!n2))
  {
    return;
  }
  else
  {
    
  }

  listNode *tmp;
  if (n1->in)
  {
    if (((node *) n1->in->value) == n2)
    {
      free((node *) n1->in);
      n1->in = 0;
      return;
    }
    else
    {
      
    }

  }
  else
  {
    
  }

  tmp = malloc(sizeof(listNode));
  tmp->value = n1;
  tmp->next = n2->in;
  n2->in = tmp;
}

void scanMap()
{
  int x;
  int y;
  int m;
  int n;
  M = new_sym_var(sizeof(int) * 8);
  N = new_sym_var(sizeof(int) * 8);
  map = malloc((sizeof(corner *)) * M);
  for (x = 0; x < M; x++)
  {
    map[x] = malloc((sizeof(corner)) * N);
    for (y = 0; y < N; y++)
    {
      map[x][y].left = createNode(x, y, 'l');
      map[x][y].right = createNode(x, y, 'r');
      map[x][y].type = NONE;
      connect(map[x][y].right, map[x][y].left);
    }

  }

  for (x = 0; x < M; x++)
  {
    for (y = 0; y < N; y++)
    {
      if (x > 0)
      {
        connect(map[x][y].left, map[x - 1][y].right);
      }
      else
      {
        
      }

      if (x < (M - 1))
      {
        connect(map[x][y].left, map[x + 1][y].right);
      }
      else
      {
        
      }

      if (y > 0)
      {
        connect(map[x][y].left, map[x][y - 1].right);
      }
      else
      {
        
      }

      if (y < (N - 1))
      {
        connect(map[x][y].left, map[x][y + 1].right);
      }
      else
      {
        
      }

    }

  }

  S = new_sym_var(sizeof(int) * 8);
  P = new_sym_var(sizeof(int) * 8);
  for (x = 0; x < S; x++)
  {
    m = new_sym_var(sizeof(int) * 8);
    n = new_sym_var(sizeof(int) * 8);
    if (map[m - 1][n - 1].type != SHOP)
    {
      connect(map[m - 1][n - 1].left, sink);
    }
    else
    {
      
    }

    map[m - 1][n - 1].type = SHOP;
  }

  for (x = 0; x < P; x++)
  {
    m = new_sym_var(sizeof(int) * 8);
    n = new_sym_var(sizeof(int) * 8);
    if ((map[m - 1][n - 1].type == PERSON) || (map[m - 1][n - 1].type == BOTH))
    {
      continue;
    }
    else
    {
      
    }

    if (map[m - 1][n - 1].type == NONE)
    {
      map[m - 1][n - 1].type = PERSON;
    }
    else
    {
      map[m - 1][n - 1].type = BOTH;
    }

    connect(source, map[m - 1][n - 1].right);
  }

}

void freeAdj(node *n)
{
  listNode *tmp = n->in;
  listNode *tmpN;
  while (tmp)
  {
    tmpN = tmp->next;
    free(tmp);
    tmp = tmpN;
  }

  tmp = n->out;
  while (tmp)
  {
    tmpN = tmp->next;
    free(tmp);
    tmp = tmpN;
  }

}

void freeMap()
{
  int x;
  int y;
  for (x = 0; x < M; x++)
  {
    for (y = 0; y < N; y++)
    {
      freeAdj(map[x][y].right);
      freeAdj(map[x][y].left);
      free(map[x][y].right);
      free(map[x][y].left);
    }

    free(map[x]);
  }

  free(map);
}

int main()
{
  total = 0;
  int x;
  int y;
  sink = createNode(-1, -1, 't');
  source = createNode(-2, -2, 's');
  scanMap();
  node *tmp;
  node *tmpN;
  while (bfs())
  {
    total++;
    tmp = sink->prev;
    tmpN = sink;
    while (tmp)
    {
      pair(tmp, tmpN);
      tmpN = tmp;
      tmp = tmp->prev;
    }

    for (x = 0; x < M; x++)
    {
      for (y = 0; y < N; y++)
      {
        map[x][y].left->prev = 0;
        map[x][y].right->prev = 0;
        map[x][y].right->tmp = 0;
        map[x][y].left->tmp = 0;
        if (map[x][y].left->in)
        {
          map[x][y].left->full = 1;
        }
        else
        {
          map[x][y].left->full = 0;
        }

        if (map[x][y].right->in)
        {
          map[x][y].right->full = 1;
        }
        else
        {
          map[x][y].right->full = 0;
        }

      }

    }

    sink->full = 0;
    source->full = 0;
    sink->prev = 0;
    source->prev = 0;
  }

  printf("%d\n", total);
  freeMap();
  freeAdj(sink);
  freeAdj(source);
  free(sink);
  free(source);
  return 0;
}
