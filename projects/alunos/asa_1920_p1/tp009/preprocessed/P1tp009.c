#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


typedef struct Grafo
{
  int numVertices;
  int **adjList;
  int *numArcs;
} grafo;
typedef struct Pilha
{
  int top;
  int *items;
} stack;
int N = 0;
int M = 0;
grafo graph;
int *grades;
stack st;
int time = 0;
int vSCC = 0;
int numberSCC = 0;
int *memberSCC;
int *gradesSCC;
void s_push(int v)
{
  st.items[++st.top] = v;
}

int s_pop()
{
  if (st.top < 0)
  {
    return 0;
  }
  else
  {
    
  }

  return st.items[st.top--];
}

void insert(int src, int dest)
{
  graph.adjList[src] = realloc(graph.adjList[src], ((++graph.numArcs[src]) + 1) * (sizeof(int)));
  graph.adjList[src][graph.numArcs[src]] = 0;
  graph.adjList[src][graph.numArcs[src] - 1] = dest;
}

void processInput()
{
  int i;
  int input1;
  int input2;
  N = new_sym_var(sizeof(int) * 8);
  M = new_sym_var(sizeof(int) * 8);
  grades = malloc((sizeof(int)) * N);
  graph.numVertices = N;
  graph.adjList = (int **) malloc(N * (sizeof(int *)));
  graph.numArcs = malloc((sizeof(int)) * N);
  for (i = 0; i < N; i++)
  {
    graph.adjList[i] = (int *) malloc(sizeof(int));
    graph.adjList[i][0] = 0;
    graph.numArcs[i] = 0;
    input1 = new_sym_var(sizeof(int) * 8);
    grades[i] = input1;
  }

  for (i = 0; i < M; i++)
  {
    input1 = new_sym_var(sizeof(int) * 8);
    input2 = new_sym_var(sizeof(int) * 8);
    insert(input2 - 1, input1);
  }

}

int min(int a, int b)
{
  return (a < b) ? (a) : (b);
}

int max(int a, int b)
{
  return (a > b) ? (a) : (b);
}

void spread(int sequence[])
{
  int i;
  int e;
  for (i = N - 1; i >= 0; i--)
  {
    grades[sequence[i]] = gradesSCC[memberSCC[sequence[i]]];
    for (e = 0; graph.adjList[sequence[i]][e] != 0; e++)
    {
      if ((memberSCC[sequence[i]] > memberSCC[graph.adjList[sequence[i]][e] - 1]) && (gradesSCC[memberSCC[sequence[i]]] > gradesSCC[memberSCC[graph.adjList[sequence[i]][e] - 1]]))
      {
        gradesSCC[memberSCC[graph.adjList[sequence[i]][e] - 1]] = grades[sequence[i]];
      }
      else
      {
        
      }

    }

  }

}

void SCCUtil(int u, int disc[], int low[], int inStack[], int sequence[])
{
  int i;
  int maxGrade;
  int w = 0;
  disc[u] = (low[u] = ++time);
  s_push(u);
  inStack[u] = 1;
  for (i = 0; graph.adjList[u][i] != 0; i++)
  {
    int v = graph.adjList[u][i] - 1;
    if (disc[v] == (-1))
    {
      SCCUtil(v, disc, low, inStack, sequence);
      low[u] = min(low[u], low[v]);
    }
    else
    {
      if (inStack[v] == 1)
      {
        low[u] = min(low[u], disc[v]);
      }
      else
      {
        
      }

    }

  }

  if (low[u] == disc[u])
  {
    i = 1;
    maxGrade = -1;
    gradesSCC = realloc(gradesSCC, (sizeof(int)) * (numberSCC + 1));
    while (i)
    {
      if (st.items[st.top] == u)
      {
        i = 0;
      }
      else
      {
        
      }

      w = st.items[st.top];
      inStack[w] = 0;
      s_pop();
      maxGrade = max(grades[w], maxGrade);
      sequence[vSCC++] = w;
      memberSCC[w] = numberSCC;
    }

    gradesSCC[numberSCC++] = maxGrade;
  }
  else
  {
    
  }

}

void SCC()
{
  int i;
  int *disc = malloc((sizeof(int)) * N);
  int *low = malloc((sizeof(int)) * N);
  int *inStack = malloc((sizeof(int)) * N);
  int *sequence = malloc((sizeof(int)) * N);
  memberSCC = malloc((sizeof(int)) * N);
  st.items = malloc((sizeof(int)) * N);
  st.top = -1;
  for (i = 0; i < N; i++)
  {
    disc[i] = -1;
    low[i] = -1;
    inStack[i] = 0;
  }

  for (i = 0; i < N; i++)
    if (disc[i] == (-1))
  {
    SCCUtil(i, disc, low, inStack, sequence);
  }
  else
  {
    
  }


  spread(sequence);
}

void printGrades()
{
  int i;
  for (i = 0; i < N; i++)
  {
    printf("%d\n", grades[i]);
  }

}

int main()
{
  processInput();
  SCC();
  printGrades();
  return 0;
}

