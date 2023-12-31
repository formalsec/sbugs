#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node
{
  long id;
  long cap;
  int type;
  struct node *next;
} *node_t;
typedef struct pair
{
  int u;
  int v;
} pair;
void insertNode(int u, int v, int c, int type);
void printAdjacenciesList();
void initPreflow();
void Push(int u, int v);
void Relabel(int u);
int Discharge(int u);
int withExcess();
int PushRelabel();
void DFS();
void DFSvisit(int u);
void getResults();
int cmpfunc(const void *p1, const void *p2);
int numManuf;
int numStora;
int numNodes;
int numLinks;
int DFS_iTree = 0;
int DFS_time = 1;
int *DFS_tree;
int *DFS_color;
int *DFS_d;
int *DFS_pi;
int *PR_h;
int *PR_e;
int *storaUp;
int **PR_f;
int **PR_c;
node_t *linkList;
int main(int argc, char *argv[])
{
  int i;
  int u;
  int v;
  int c;
  char buffer[1048576];
  char *token;
  if (fgets(buffer, 1048576 - 1, stdin) == 0)
  {
    exit(1);
  }
  else
  {
    
  }

  token = strtok(buffer, " ");
  numManuf = atoi(token);
  token = strtok(0, " ");
  numStora = atoi(token);
  token = strtok(0, " ");
  numLinks = atoi(token);
  numNodes = (numManuf + (2 * numStora)) + 2;
  DFS_color = (int *) malloc(numNodes * (sizeof(int)));
  DFS_d = (int *) malloc(numNodes * (sizeof(int)));
  DFS_pi = (int *) malloc(numNodes * (sizeof(int)));
  DFS_tree = (int *) malloc(numNodes * (sizeof(int)));
  PR_h = (int *) calloc(numNodes, sizeof(int));
  PR_e = (int *) calloc(numNodes, sizeof(int));
  storaUp = (int *) calloc(numNodes, sizeof(int));
  linkList = (node_t *) malloc(numNodes * (sizeof(struct node)));
  PR_f = (int **) malloc(numNodes * (sizeof(int *)));
  PR_f[0] = (int *) calloc(numNodes * numNodes, sizeof(int));
  for (i = 1; i < numNodes; i++)
    PR_f[i] = PR_f[0] + (i * numNodes);

  PR_c = (int **) malloc(numNodes * (sizeof(int *)));
  PR_c[0] = (int *) calloc(numNodes * numNodes, sizeof(int));
  for (i = 1; i < numNodes; i++)
    PR_c[i] = PR_c[0] + (i * numNodes);

  for (i = 0; i <= numNodes; i++)
  {
    linkList[i] = 0;
  }

  if (fgets(buffer, 1048576 - 1, stdin) == 0)
  {
    exit(1);
  }
  else
  {
    
  }

  token = strtok(buffer, " ");
  for (i = 2; i <= (numManuf + 1); i++)
  {
    insertNode(0, i, atoi(token), 2);
    insertNode(i, 0, 0, 5);
    PR_c[0][i] = atoi(token);
    token = strtok(0, " ");
  }

  if (fgets(buffer, 1048576 - 1, stdin) == 0)
  {
    exit(1);
  }
  else
  {
    
  }

  token = strtok(buffer, " ");
  for (; i < (numNodes - numStora); i++)
  {
    insertNode(i, i + numStora, atoi(token), 1);
    insertNode(i + numStora, i, 0, 4);
    PR_c[i][i + numStora] = atoi(token);
    token = strtok(0, " ");
  }

  for (i = 0; i < numLinks; i++)
  {
    if (fgets(buffer, 1048576 - 1, stdin) == 0)
    {
      exit(1);
    }
    else
    {
      
    }

    token = strtok(buffer, " ");
    u = atoi(token);
    u = (u > (numManuf + 1)) ? (u + numStora) : (u);
    token = strtok(0, " ");
    v = atoi(token);
    token = strtok(0, " ");
    c = atoi(token);
    insertNode(u, v, c, 0);
    insertNode(v, u, 0, 3);
    PR_c[u][v] = c;
    PR_c[v][u] = 0;
  }

  printf("%d\n", PushRelabel());
  DFS();
  getResults();
  return 0;
}

void insertNode(int u, int v, int c, int type)
{
  node_t new = (node_t) malloc(sizeof(struct node));
  new->id = v;
  new->cap = c;
  new->type = type;
  new->next = linkList[u];
  linkList[u] = new;
}

void printAdjacenciesList()
{
  int i;
  node_t node_i;
  for (i = 0; i < numNodes; i++)
  {
    printf("%d: ", i);
    node_i = linkList[i];
    while (node_i != 0)
    {
      printf("%ld:%ld - ", node_i->id, node_i->cap);
      node_i = node_i->next;
    }

    printf("\n");
  }

}

void initPreflow()
{
  int c;
  int u;
  node_t node_i = linkList[0];
  PR_h[0] = numNodes;
  while (node_i != 0)
  {
    c = node_i->cap;
    u = node_i->id;
    PR_c[u][0] = c;
    PR_f[0][u] = c;
    PR_f[u][0] = c * (-1);
    PR_e[u] = c;
    node_i = node_i->next;
  }

}

void Push(int u, int v)
{
  int c = PR_c[u][v] - PR_f[u][v];
  int d = (PR_e[u] < c) ? (PR_e[u]) : (c);
  PR_f[u][v] += d;
  PR_f[v][u] = PR_f[u][v] * (-1);
  PR_e[u] -= d;
  PR_e[v] += d;
}

void Relabel(int u)
{
  int v;
  int minH = 2 * numNodes;
  node_t node_i = linkList[u];
  while (node_i != 0)
  {
    v = node_i->id;
    if ((PR_h[v] < minH) && (PR_h[u] <= PR_h[v]))
    {
      minH = PR_h[v];
    }
    else
    {
      
    }

    node_i = node_i->next;
  }

  PR_h[u] = minH + 1;
}

int Discharge(int u)
{
  int v;
  node_t node_i = linkList[u];
  while (PR_e[u] > 0)
  {
    if (node_i == 0)
    {
      return -1;
    }
    else
    {
      
    }

    v = node_i->id;
    if ((PR_h[u] > PR_h[v]) && ((PR_c[u][v] - PR_f[u][v]) > 0))
    {
      Push(u, v);
    }
    else
    {
      
    }

    node_i = node_i->next;
  }

  return 0;
}

int withExcess()
{
  int i;
  for (i = 2; i < numNodes; i++)
  {
    if (PR_e[i] > 0)
    {
      return i;
    }
    else
    {
      
    }

  }

  return -1;
}

int PushRelabel()
{
  int u;
  initPreflow();
  while ((u = withExcess()) != (-1))
  {
    while (Discharge(u) == (-1))
    {
      Relabel(u);
    }

  }

  return PR_e[1];
}

void DFS()
{
  int i;
  for (i = 0; i < numNodes; i++)
  {
    DFS_color[i] = (DFS_d[i] = 0);
    DFS_pi[i] = -1;
  }

  DFSvisit(1);
  DFS_iTree++;
  for (i = numNodes - 1; i >= 0; i--)
  {
    if (DFS_color[i] == 0)
    {
      DFSvisit(i);
    }
    else
    {
      
    }

    if ((DFS_pi[i] == (-1)) && (i != 1))
    {
      DFS_iTree++;
    }
    else
    {
      
    }

  }

}

void DFSvisit(int u)
{
  int v;
  node_t node_i = linkList[u];
  DFS_tree[u] = DFS_iTree;
  DFS_color[u] = 1;
  DFS_d[u] = DFS_time++;
  while (node_i != 0)
  {
    v = node_i->id;
    if (DFS_color[v] == 0)
    {
      if ((PR_c[v][u] - PR_f[v][u]) != 0)
      {
        DFS_pi[v] = u;
        DFSvisit(v);
      }
      else
      {
        
      }

    }
    else
    {
      
    }

    node_i = node_i->next;
  }

  DFS_color[u] = 2;
}

void getResults()
{
  int i = 2 + numManuf;
  int iPair = 0;
  node_t node_i;
  pair *pairs = (pair *) malloc(numLinks * (sizeof(pair)));
  for (i = 2 + numManuf; i < ((2 + numManuf) + numStora); i++)
  {
    if ((DFS_tree[i + numStora] == 0) && (DFS_tree[i] != 0))
    {
      storaUp[i] = 1;
    }
    else
    {
      
    }

  }

  for (i = 0; i < numNodes; i++)
  {
    if (!DFS_tree[i])
    {
      node_i = linkList[i];
      while (node_i != 0)
      {
        if ((((((DFS_tree[node_i->id] && (storaUp[i] != 1)) && (storaUp[node_i->id] != 1)) && (node_i->type != 2)) && (node_i->type != 1)) && (node_i->type != 5)) && (node_i->type != 4))
        {
          pairs[iPair].u = (((int) node_i->id) > ((1 + numManuf) + numStora)) ? (node_i->id - numStora) : (node_i->id);
          pairs[iPair].v = i;
          iPair++;
        }
        else
        {
          
        }

        node_i = node_i->next;
      }

    }
    else
    {
      
    }

  }

  for (i = 1; i < numNodes; i++)
  {
    if (storaUp[i] == 1)
    {
      printf("%d", i);
      break;
    }
    else
    {
      
    }

  }

  for (i++; i < numNodes; i++)
  {
    if (storaUp[i] == 1)
    {
      printf(" %d", i);
    }
    else
    {
      
    }

  }

  printf("\n");
  qsort(pairs, numLinks, sizeof(pair), cmpfunc);
  for (i = numLinks - iPair; i < numLinks; i++)
    printf("%d %d\n", pairs[i].u, pairs[i].v);

}

int cmpfunc(const void *p1, const void *p2)
{
  pair a = *((pair *) p1);
  pair b = *((pair *) p2);
  if (a.u != b.u)
  {
    return a.u - b.u;
  }
  else
  {
    
  }

  return a.v - b.v;
}

