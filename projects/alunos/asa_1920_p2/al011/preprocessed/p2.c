#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


int M;
int N;
int S;
int C;
int V;
int F;
int MAX;
typedef struct 
{
  int avenida;
  int rua;
} cruzamento;
typedef struct 
{
  int visited;
  int fluxo;
  int supermercados;
  int cidadaos;
  int cruzamentos;
  cruzamento *c;
  cruzamento in;
} vertice;
typedef struct 
{
  cruzamento c;
  int b;
} path;
typedef struct node
{
  path *p;
  int cruzamentos;
  struct node *next;
} queueN;
typedef queueN *queue;
vertice **grid;
cruzamento *cidadaos;
void initE(int ui, int uj, int vi, int vj)
{
  grid[ui][uj].c = realloc(grid[ui][uj].c, (grid[ui][uj].cruzamentos + 1) * (sizeof(cruzamento)));
  grid[ui][uj].c[grid[ui][uj].cruzamentos].avenida = vi;
  grid[ui][uj].c[grid[ui][uj].cruzamentos].rua = vj;
  grid[ui][uj].cruzamentos++;
}

void initG()
{
  int i;
  int j;
  grid = malloc(M * (sizeof(vertice *)));
  for (i = 0; i < M; i++)
  {
    grid[i] = malloc(N * (sizeof(vertice)));
    for (j = 0; j < N; j++)
    {
      grid[i][j].visited = V;
      grid[i][j].fluxo = 0;
      grid[i][j].supermercados = 0;
      grid[i][j].cidadaos = 0;
      grid[i][j].cruzamentos = 0;
      grid[i][j].c = 0;
      grid[i][j].in.avenida = -1;
      grid[i][j].in.rua = -1;
      if (j < (N - 1))
      {
        initE(i, j, i, j + 1);
      }
      else
      {
        
      }

      if (i < (M - 1))
      {
        initE(i, j, i + 1, j);
      }
      else
      {
        
      }

      if (j > 0)
      {
        initE(i, j, i, j - 1);
      }
      else
      {
        
      }

      if (i > 0)
      {
        initE(i, j, i - 1, j);
      }
      else
      {
        
      }

    }

  }

}

void initS()
{
  int i;
  int a;
  int r;
  int Sc = S;
  for (i = 0; i < S; i++)
  {
    a = new_sym_var(sizeof(int) * 8);
    r = new_sym_var(sizeof(int) * 8);
    a--;
    r--;
    if (grid[a][r].supermercados > 0)
    {
      Sc--;
    }
    else
    {
      grid[a][r].supermercados++;
    }

  }

  S = Sc;
}

void initC()
{
  int i;
  int a;
  int r;
  int Ci = 0;
  int Cc = C;
  cidadaos = malloc(C * (sizeof(cruzamento)));
  for (i = 0; i < C; i++)
  {
    a = new_sym_var(sizeof(int) * 8);
    r = new_sym_var(sizeof(int) * 8);
    a--;
    r--;
    if (grid[a][r].cidadaos > 0)
    {
      cidadaos = realloc(cidadaos, (--Cc) * (sizeof(cruzamento)));
    }
    else
    {
      grid[a][r].cidadaos++;
      if (grid[a][r].supermercados > 0)
      {
        cidadaos = realloc(cidadaos, (--Cc) * (sizeof(cruzamento)));
        grid[a][r].fluxo = 4;
        F++;
      }
      else
      {
        cidadaos[Ci].avenida = a;
        cidadaos[Ci].rua = r;
        Ci++;
      }

    }

  }

  C = Ci;
}

void freeC()
{
  free(cidadaos);
}

void freeG()
{
  int i;
  int j;
  for (i = 0; i < M; i++)
  {
    for (j = 0; j < N; j++)
      free(grid[i][j].c);

    free(grid[i]);
  }

  free(grid);
}

queue initQ(int a, int r)
{
  queue q = malloc(sizeof(queueN));
  q->p = malloc(sizeof(path));
  q->p[0].c.avenida = a;
  q->p[0].c.rua = r;
  q->p[0].b = grid[a][r].fluxo;
  q->cruzamentos = 1;
  q->next = 0;
  return q;
}

queue enQ(queue first, queue last, int a, int r, int b)
{
  int i;
  int cruzamentos;
  cruzamentos = first->cruzamentos + 1;
  queue new = malloc(sizeof(queueN));
  new->p = malloc(cruzamentos * (sizeof(path)));
  for (i = 0; i < (cruzamentos - 1); i++)
    new->p[i] = first->p[i];

  new->p[cruzamentos - 1].c.avenida = a;
  new->p[cruzamentos - 1].c.rua = r;
  new->p[cruzamentos - 1].b = b;
  new->cruzamentos = cruzamentos;
  new->next = 0;
  last->next = new;
  return new;
}

queue deQ(queue q)
{
  queue first = q->next;
  free(q->p);
  free(q);
  return first;
}

void freeQ(queue q)
{
  queue first = q;
  while (first != 0)
    first = deQ(first);

}

queue bfs(int a, int r)
{
  int i;
  int ai;
  int ri;
  int bi;
  int aq;
  int rq;
  int bq;
  int cq;
  queue first;
  queue last;
  first = initQ(a, r);
  last = first;
  V++;
  while (first != 0)
  {
    cq = first->cruzamentos - 1;
    aq = first->p[cq].c.avenida;
    rq = first->p[cq].c.rua;
    bq = first->p[cq].b;
    if ((grid[aq][rq].supermercados > 0) && (grid[aq][rq].fluxo == 0))
    {
      break;
    }
    else
    {
      
    }

    if (grid[aq][rq].fluxo == 0)
    {
      for (i = 0; i < grid[aq][rq].cruzamentos; i++)
      {
        ai = grid[aq][rq].c[i].avenida;
        ri = grid[aq][rq].c[i].rua;
        bi = grid[ai][ri].fluxo;
        if (cq > 0)
        {
          if ((ai == first->p[cq - 1].c.avenida) && (ri == first->p[cq - 1].c.rua))
          {
            continue;
          }
          else
          {
            
          }

        }
        else
        {
          
        }

        if ((grid[ai][ri].visited != V) && (bi != 2))
        {
          if (bi == 0)
          {
            grid[ai][ri].visited = V;
          }
          else
          {
            
          }

          if (grid[ai][ri].fluxo < 4)
          {
            last = enQ(first, last, ai, ri, bi);
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
    else
    {
      if ((bq > 0) && (grid[aq][rq].in.avenida != (-1)))
      {
        ai = grid[aq][rq].in.avenida;
        ri = grid[aq][rq].in.rua;
        if (grid[ai][ri].visited != V)
        {
          grid[ai][ri].visited = V;
          if (grid[ai][ri].fluxo < 4)
          {
            last = enQ(first, last, ai, ri, 0);
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
        if (bq == 0)
        {
          for (i = 0; i < grid[aq][rq].cruzamentos; i++)
          {
            ai = grid[aq][rq].c[i].avenida;
            ri = grid[aq][rq].c[i].rua;
            bi = grid[ai][ri].fluxo;
            if (cq > 0)
            {
              if ((ai == first->p[cq - 1].c.avenida) && (ri == first->p[cq - 1].c.rua))
              {
                continue;
              }
              else
              {
                
              }

            }
            else
            {
              
            }

            if ((grid[ai][ri].visited != V) && (!((bi == 2) && (!((grid[aq][rq].in.avenida == ai) && (grid[aq][rq].in.rua == ri))))))
            {
              if (bi == 0)
              {
                grid[ai][ri].visited = V;
              }
              else
              {
                
              }

              if (grid[ai][ri].fluxo < 4)
              {
                if ((grid[aq][rq].in.avenida == ai) && (grid[aq][rq].in.rua == ri))
                {
                  last = enQ(first, last, ai, ri, 0);
                }
                else
                {
                  last = enQ(first, last, ai, ri, bi);
                }

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
        else
        {
          
        }

      }

    }

    first = deQ(first);
  }

  return first;
}

void solve()
{
  int i;
  int j;
  int ai;
  int ri;
  int bi;
  int backtrack;
  queue res;
  for (i = 0; i < C; i++)
  {
    res = bfs(cidadaos[i].avenida, cidadaos[i].rua);
    if (res != 0)
    {
      backtrack = 0;
      for (j = res->cruzamentos - 1; j >= 0; j--)
      {
        ai = res->p[j].c.avenida;
        ri = res->p[j].c.rua;
        bi = res->p[j].b;
        if ((grid[ai][ri].fluxo > 0) && (backtrack == 0))
        {
          backtrack = 1;
          if (grid[ai][ri].fluxo == 2)
          {
            grid[ai][ri].in.avenida = -1;
            grid[ai][ri].in.rua = -1;
          }
          else
          {
            
          }

          continue;
        }
        else
        {
          
        }

        if ((bi == 0) && (backtrack == 1))
        {
          grid[ai][ri].fluxo = 0;
          grid[ai][ri].in.avenida = -1;
          grid[ai][ri].in.rua = -1;
          continue;
        }
        else
        {
          
        }

        if (bi > 0)
        {
          backtrack = 0;
        }
        else
        {
          
        }

        if (j == 0)
        {
          grid[ai][ri].in.avenida = -1;
          grid[ai][ri].in.rua = -1;
          if (j == (res->cruzamentos - 1))
          {
            grid[ai][ri].fluxo = 4;
          }
          else
          {
            grid[ai][ri].fluxo = 2;
          }

        }
        else
        {
          if (j > 0)
          {
            grid[ai][ri].in.avenida = res->p[j - 1].c.avenida;
            grid[ai][ri].in.rua = res->p[j - 1].c.rua;
            if (j == (res->cruzamentos - 1))
            {
              grid[ai][ri].fluxo = 3;
            }
            else
            {
              grid[ai][ri].fluxo = 1;
            }

          }
          else
          {
            
          }

        }

      }

      freeQ(res);
      F++;
    }
    else
    {
      
    }

    if (F == MAX)
    {
      return;
    }
    else
    {
      
    }

  }

}

int main()
{
  M = new_sym_var(sizeof(int) * 8);
  N = new_sym_var(sizeof(int) * 8);
  S = new_sym_var(sizeof(int) * 8);
  C = new_sym_var(sizeof(int) * 8);
  V = 0;
  F = 0;
  if (C <= S)
  {
    MAX = C;
  }
  else
  {
    MAX = S;
  }

  initG();
  initS();
  initC();
  solve();
  freeC();
  freeG();
  printf("%d\n", F);
  return 0;
}

