/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct node *link;
struct node
{
  int connection;
  link next;
};
typedef struct 
{
  int degree;
  link listOfAdj;
  link lastOfAdj;
} Domino;
int hits;
int sequence;
Domino **graph;
void dominoCracker(int vertexs, int arcs)
{
  link adj = 0;
  int i = 0;
  int pointer = -1;
  int topoPointer = 0;
  int currDomi = 0;
  int *stack = (int *) malloc(((arcs > 0) ? (arcs + 1) : (1)) * (sizeof(int)));
  int *topoOrder = (int *) malloc(((arcs > 0) ? (arcs + 1) : (1)) * (sizeof(int)));
  for (i = 0; i < vertexs; i++)
  {
    if (graph[i]->degree == 0)
    {
      hits++;
      pointer++;
      stack[pointer] = i;
    }
    else
    {
      
    }

  }

  for (; pointer > (-1);)
  {
    currDomi = stack[pointer];
    topoOrder[topoPointer] = currDomi;
    topoPointer++;
    for (adj = graph[currDomi]->listOfAdj; adj != 0; adj = adj->next)
    {
      graph[adj->connection]->degree--;
      if (graph[adj->connection]->degree == 0)
      {
        stack[pointer] = adj->connection;
        pointer++;
      }
      else
      {
        
      }

    }

    pointer--;
  }

  for (i = 0; i < topoPointer; i++)
  {
    currDomi = topoOrder[i];
    adj = graph[currDomi]->listOfAdj;
    if ((adj != 0) && ((graph[currDomi]->degree + 1) > sequence))
    {
      sequence = graph[currDomi]->degree + 1;
    }
    else
    {
      
    }

    for (; adj != 0; adj = adj->next)
    {
      if ((graph[currDomi]->degree + 1) > graph[adj->connection]->degree)
      {
        graph[adj->connection]->degree = graph[currDomi]->degree + 1;
      }
      else
      {
        
      }

    }

  }

  free(stack);
  free(topoOrder);
}

void insertLink(int rela, int relb)
{
  link newAdj = malloc(sizeof(struct node));
  if (graph[rela - 1]->listOfAdj == 0)
  {
    graph[rela - 1]->listOfAdj = newAdj;
  }
  else
  {
    graph[rela - 1]->lastOfAdj->next = newAdj;
  }

  newAdj->next = 0;
  newAdj->connection = relb - 1;
  graph[rela - 1]->lastOfAdj = newAdj;
  graph[relb - 1]->degree++;
}

int main(int argc, char **argv)
{
  int N = 0;
  int M = 0;
  int rela = 0;
  int relb = 0;
  int i = 0;
  hits = 0;
  sequence = 0;
  N = new_sym_var(sizeof(int) * 8);
  M = new_sym_var(sizeof(int) * 8);
  if ((M > 0) && (N > 0))
  {
    graph = (Domino **) malloc(N * (sizeof(Domino *)));
    while (i < N)
    {
      graph[i] = (Domino *) malloc(sizeof(Domino));
      graph[i]->degree = 0;
      graph[i]->listOfAdj = 0;
      graph[i]->lastOfAdj = 0;
      i++;
    }

    i = 0;
    while (i < M)
    {
      rela = new_sym_var(sizeof(int) * 8);
      relb = new_sym_var(sizeof(int) * 8);
      if (((((rela > 0) && (relb > 0)) && (rela != relb)) && (rela <= N)) && (relb <= N))
      {
        insertLink(rela, relb);
      }
      else
      {
        
      }

      i++;
    }

    dominoCracker(N, M);
  }
  else
  {
    
  }

  printf("%d %d\n", (M == 0) ? (N) : (hits), (N == 0) ? (0) : (sequence + 1));
  return 0;
}

