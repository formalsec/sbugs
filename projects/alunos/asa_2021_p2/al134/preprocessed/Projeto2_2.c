#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


int capacity = 0;
typedef struct edge link;
struct edge
{
  int v;
  int cr;
  link *twin;
  link *next;
};
typedef struct graph
{
  int V;
  link **adj;
} graph;
graph G;
void readInput()
{
  int i;
  int nProcesses;
  int nCosts;
  int costY;
  int costX;
  int node1;
  int node2;
  int cost12;
  if (2 != 2)
  {
    exit(1);
  }
  else
  {
    nProcesses = new_sym_var(sizeof(int) * 8);
    nCosts = new_sym_var(sizeof(int) * 8);
    
  }

  G.V = nProcesses + 2;
  G.adj = (link **) malloc((sizeof(link)) * G.V);
  for (i = 0; i < nProcesses; i++)
  {
    link *edgeXP = malloc(sizeof(link));
    link *edgeYP = malloc(sizeof(link));
    link *edgePX = malloc(sizeof(link));
    link *edgePY = malloc(sizeof(link));
    if (2 != 2)
    {
      exit(1);
    }
    else
    {
      costX = new_sym_var(sizeof(int) * 8);
      costY = new_sym_var(sizeof(int) * 8);
      
    }

    edgeXP->v = i;
    edgeXP->cr = costX;
    edgeXP->twin = edgePX;
    edgeXP->next = G.adj[G.V - 2];
    G.adj[G.V - 2] = edgeXP;
    edgePX->v = G.V - 2;
    edgePX->cr = costX;
    edgePX->twin = edgeXP;
    edgePX->next = G.adj[i];
    G.adj[i] = edgePX;
    edgeYP->v = i;
    edgeYP->cr = costY;
    edgeYP->twin = edgePY;
    edgeYP->next = G.adj[G.V - 1];
    G.adj[G.V - 1] = edgeYP;
    edgePY->v = G.V - 1;
    edgePY->cr = costY;
    edgePY->twin = edgeYP;
    edgePY->next = G.adj[i];
    G.adj[i] = edgePY;
  }

  for (i = 0; i < nCosts; i++)
  {
    link *edge1_2 = malloc(sizeof(link));
    link *edge2_1 = malloc(sizeof(link));
    if (3 != 3)
    {
      exit(1);
    }
    else
    {
      node1 = new_sym_var(sizeof(int) * 8);
      node2 = new_sym_var(sizeof(int) * 8);
      cost12 = new_sym_var(sizeof(int) * 8);
      
    }

    edge1_2->cr = cost12;
    edge1_2->v = node2 - 1;
    edge1_2->twin = edge2_1;
    edge1_2->next = G.adj[node1 - 1];
    G.adj[node1 - 1] = edge1_2;
    edge2_1->cr = cost12;
    edge2_1->v = node1 - 1;
    edge2_1->twin = edge1_2;
    edge2_1->next = G.adj[node2 - 1];
    G.adj[node2 - 1] = edge2_1;
  }

}

int findPath(int s, int t, int pa[], link *parc[])
{
  int v;
  int queue[G.V];
  int lenght = 0;
  int first = 0;
  int last = -1;
  int min_flow = 0x7fffffff;
  int visited[G.V];
  link *edge;
  for (v = 0; v < G.V; v++)
  {
    visited[v] = 0;
  }

  visited[s] = 1;
  queue[(++last) % G.V] = s;
  lenght++;
  while (lenght != 0)
  {
    v = queue[(first++) % G.V];
    lenght--;
    if (v == t)
    {
      break;
    }
    else
    {
      
    }

    for (edge = G.adj[v]; edge != 0; edge = edge->next)
    {
      if ((edge->cr > 0) && (visited[edge->v] != 1))
      {
        visited[edge->v] = 1;
        pa[edge->v] = v;
        parc[edge->v] = edge;
        queue[(++last) % G.V] = edge->v;
        lenght++;
      }
      else
      {
        
      }

    }

  }

  if (visited[t] != 1)
  {
    return 0;
  }
  else
  {
    
  }

  for (v = t; v != s; v = pa[v])
  {
    edge = parc[v];
    if (edge->cr < min_flow)
    {
      min_flow = edge->cr;
    }
    else
    {
      
    }

  }

  return min_flow;
}

void EdmondsKarp()
{
  int pa[G.V];
  int v;
  link *parc[G.V];
  link *edge;
  int path_flow;
  while ((path_flow = findPath(G.V - 2, G.V - 1, pa, parc)) != 0)
  {
    for (v = G.V - 1; v != (G.V - 2); v = pa[v])
    {
      edge = parc[v];
      edge->cr -= path_flow;
      edge->twin->cr += path_flow;
    }

    capacity += path_flow;
  }

}

int main()
{
  readInput();
  EdmondsKarp();
  printf("%d\n", capacity);
  return 0;
}

