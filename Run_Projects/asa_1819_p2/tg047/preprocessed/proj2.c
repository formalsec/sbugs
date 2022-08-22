/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


struct node
{
  int id;
  int capa;
};
int n;
int e;
int capacity[1000][1000];
int flow[1000][1000];
int color[1000];
int pred[1000];
int min(int x, int y)
{
  return (x < y) ? (x) : (y);
}

int head;
int tail;
int q[1000 + 2];
void enqueue(int x)
{
  q[tail] = x;
  tail++;
  color[x] = 1;
}

int dequeue()
{
  int x = q[head];
  head++;
  color[x] = 2;
  return x;
}

int bfs(int start, int target)
{
  int u;
  int v;
  for (u = 0; u < n; u++)
  {
    color[u] = 0;
  }

  head = (tail = 0);
  enqueue(start);
  pred[start] = -1;
  while (head != tail)
  {
    u = dequeue();
    for (v = 0; v < n; v++)
    {
      if ((color[v] == 0) && ((capacity[u][v] - flow[u][v]) > 0))
      {
        enqueue(v);
        pred[v] = u;
      }
      else
      {
        
      }

    }

  }

  return color[target] == 2;
}

int max_flow(int source, int sink)
{
  int i;
  int j;
  int u;
  int max_flow = 0;
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < n; j++)
    {
      flow[i][j] = 0;
    }

  }

  while (bfs(source, sink))
  {
    int increment = 1000000000;
    for (u = n - 1; pred[u] >= 0; u = pred[u])
    {
      increment = min(increment, capacity[pred[u]][u] - flow[pred[u]][u]);
    }

    for (u = n - 1; pred[u] >= 0; u = pred[u])
    {
      flow[pred[u]][u] += increment;
      flow[u][pred[u]] -= increment;
    }

    max_flow += increment;
  }

  return max_flow;
}

int main()
{
  int forn;
  int abas;
  int conec;
  int v1;
  int i;
  int j;
  int l;
  int v2;
  int v3;
  int v4;
  int v5;
  int max = 0;
  forn = new_sym_var(sizeof(int) * 8);
  abas = new_sym_var(sizeof(int) * 8);
  conec = new_sym_var(sizeof(int) * 8);
  struct node forn1[forn + abas];
  int matr[forn + abas][forn + abas];
  for (i = 2; i <= (forn + 1); i++)
  {
    v1 = new_sym_var(sizeof(int) * 8);
    struct node a;
    a.id = i;
    a.capa = v1;
    forn1[i] = a;
  }

  for (j = 0; j <= abas; j++)
  {
    v2 = new_sym_var(sizeof(int) * 8);
    struct node a1;
    a1.id = i;
    a1.capa = v2;
    forn1[i] = a1;
    i++;
  }

  for (i = 0; i < (forn + abas); i++)
  {
    for (j = 0; j < (forn + abas); j++)
    {
      matr[i][j] = 0;
    }

  }

  for (l = 0; l < conec; l++)
  {
    v3 = new_sym_var(sizeof(int) * 8);
    v4 = new_sym_var(sizeof(int) * 8);
    v5 = new_sym_var(sizeof(int) * 8);
    if (forn1[v3].capa > v5)
    {
      matr[v3][v4] = v5 - forn1[v3].capa;
    }
    else
    {
      matr[v3][v4] = forn1[v3].capa;
    }

  }

  int p;
  int comp;
  for (p = 2; p < (forn + abas); p++)
  {
    comp = max_flow(p, 1);
    if (comp >= max)
    {
      max = comp;
    }
    else
    {
      
    }

  }

  printf("%d", max);
  return 0;
}

