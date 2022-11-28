#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


typedef struct node *link;
struct node
{
  int student;
  link next;
};
struct graph
{
  int V;
  int E;
  int numSCCs;
  link *adj;
  int *grades;
  int *compSCC;
};
typedef struct graph *Graph;
Graph graph_friendship = 0;
link top = 0;
link insertBegin(int v, link head)
{
  link l = malloc(sizeof(struct node));
  l->student = v;
  l->next = head;
  return l;
}

int is_empty()
{
  return top == 0;
}

void push(int student)
{
  top = insertBegin(student, top);
}

int pop()
{
  int student;
  link old;
  if (!is_empty())
  {
    student = top->student;
    old = top;
    top = top->next;
    free(old);
    return student;
  }
  else
  {
    
  }

  return -1;
}

int findStudent(int student)
{
  link l;
  for (l = top; l != 0; l = l->next)
  {
    if (l->student == student)
    {
      return 1;
    }
    else
    {
      
    }

  }

  return 0;
}

Graph graphInit(int V)
{
  int i;
  Graph G = malloc(sizeof(struct graph));
  G->V = V;
  G->E = 0;
  G->numSCCs = 0;
  G->adj = malloc(V * (sizeof(link)));
  G->grades = malloc(V * (sizeof(int)));
  G->compSCC = malloc(V * (sizeof(int)));
  for (i = 0; i < V; i++)
  {
    G->adj[i] = 0;
    G->grades[i] = 0;
    G->compSCC[i] = 0;
  }

  return G;
}

void insertGrade(Graph G, int student, int grade)
{
  G->grades[student] = grade;
}

void insertEdge(Graph G, int u, int v)
{
  G->adj[u] = insertBegin(v, G->adj[u]);
  G->E++;
}

void freeGraph(Graph G)
{
  free(G->adj);
  free(G->grades);
  free(G->compSCC);
  free(G);
}

void readGradesAndFriendship(int N, int M, char *line)
{
  int num1;
  int num2;
  int i = 0;
  while ((i < N) && fgets(line, 100, stdin))
  {
    num1 = new_sym_var(sizeof(int) * 8);
    insertGrade(graph_friendship, i, num1);
    i++;
  }

  i = 0;
  while ((i < M) && fgets(line, 100, stdin))
  {
    num1 = new_sym_var(sizeof(int) * 8);
    num2 = new_sym_var(sizeof(int) * 8);
    insertEdge(graph_friendship, num1 - 1, num2 - 1);
    i++;
  }

}

void tarjanVisit(int u, int *d, int *low, int *visited, Graph G)
{
  link l;
  d[u] = (low[u] = (*visited) + 1);
  (*visited)++;
  push(u);
  for (l = G->adj[u]; l != 0; l = l->next)
  {
    if ((d[l->student] == 0) || findStudent(l->student))
    {
      if (d[l->student] == 0)
      {
        tarjanVisit(l->student, d, low, visited, G);
      }
      else
      {
        
      }

      if (low[u] > low[l->student])
      {
        low[u] = low[l->student];
      }
      else
      {
        
      }

    }
    else
    {
      
    }

  }

  if (low[u] == d[u])
  {
    int student = -1;
    while (student != u)
    {
      student = pop();
      G->compSCC[student] = G->numSCCs;
    }

    G->numSCCs++;
  }
  else
  {
    
  }

}

void SCC_Tarjan(Graph G)
{
  int u;
  int visited = 0;
  int *d = malloc((sizeof(int)) * G->V);
  int *low = malloc((sizeof(int)) * G->V);
  for (u = 0; u < G->V; u++)
    d[u] = 0;

  for (u = 0; u < G->V; u++)
    if (d[u] == 0)
  {
    tarjanVisit(u, d, low, &visited, G);
  }
  else
  {
    
  }


  free(d);
  free(low);
  free(top);
}

link *consListSCC(Graph G)
{
  int u;
  link *SCC = malloc(G->numSCCs * (sizeof(struct node)));
  for (u = 0; u < G->V; u++)
    SCC[G->compSCC[u]] = 0;

  for (u = 0; u < G->V; u++)
    SCC[G->compSCC[u]] = insertBegin(u, SCC[G->compSCC[u]]);

  return SCC;
}

void SCCToOneVertex(Graph G, Graph newG, link *SCC)
{
  int num;
  int max = -1;
  link lScc;
  link lAdj;
  int *edge = malloc(G->numSCCs * (sizeof(int)));
  for (num = 0; num < G->numSCCs; num++)
    edge[num] = 0;

  for (num = 0; num < G->numSCCs; num++)
  {
    for (lScc = SCC[num]; lScc != 0; lScc = lScc->next)
    {
      if (max < G->grades[lScc->student])
      {
        max = G->grades[lScc->student];
      }
      else
      {
        
      }

      for (lAdj = G->adj[lScc->student]; lAdj != 0; lAdj = lAdj->next)
      {
        if (edge[G->compSCC[lAdj->student]] != 1)
        {
          edge[G->compSCC[lAdj->student]] = 1;
          insertEdge(newG, num, G->compSCC[lAdj->student]);
        }
        else
        {
          
        }

      }

    }

    insertGrade(newG, num, max);
    max = -1;
    for (lScc = SCC[num]; lScc != 0; lScc = lScc->next)
    {
      for (lAdj = G->adj[lScc->student]; lAdj != 0; lAdj = lAdj->next)
        edge[G->compSCC[lAdj->student]] = 0;

    }

  }

  free(edge);
}

void serachBestSolutionVisit(Graph G, int u, int *color)
{
  link l;
  color[u] = 1;
  for (l = G->adj[u]; l != 0; l = l->next)
  {
    if (color[l->student] == 0)
    {
      serachBestSolutionVisit(G, l->student, color);
    }
    else
    {
      
    }

    if (G->grades[u] < G->grades[l->student])
    {
      G->grades[u] = G->grades[l->student];
    }
    else
    {
      
    }

  }

  color[u] = 2;
}

void serachBestSolution(Graph G)
{
  int u;
  int *color = malloc((sizeof(int)) * G->V);
  for (u = 0; u < G->V; u++)
    color[u] = 0;

  for (u = 0; u < G->V; u++)
    if (color[u] == 0)
  {
    serachBestSolutionVisit(G, u, color);
  }
  else
  {
    
  }


  free(color);
}

void changeSCCStudentsGrades(Graph G, Graph G_SCC, link *SCC)
{
  int u;
  link l;
  for (u = 0; u < G_SCC->V; u++)
  {
    for (l = SCC[u]; l != 0; l = l->next)
      G->grades[l->student] = G_SCC->grades[u];

  }

}

void freeSCC(Graph G, link *SCC)
{
  int u;
  link l;
  for (u = 0; u < G->V; u++)
  {
    while (SCC[u])
    {
      l = SCC[u];
      SCC[u] = SCC[u]->next;
      free(l);
    }

    while (G->adj[u])
    {
      l = G->adj[u];
      G->adj[u] = G->adj[u]->next;
      free(l);
    }

  }

  free(SCC);
  freeGraph(G);
}

void previsionASAGrades()
{
  if (graph_friendship->numSCCs < graph_friendship->V)
  {
    link *SCC = consListSCC(graph_friendship);
    Graph graph_SCC = graphInit(graph_friendship->numSCCs);
    SCCToOneVertex(graph_friendship, graph_SCC, SCC);
    if (graph_friendship->numSCCs > 1)
    {
      serachBestSolution(graph_SCC);
    }
    else
    {
      
    }

    changeSCCStudentsGrades(graph_friendship, graph_SCC, SCC);
    freeSCC(graph_SCC, SCC);
  }
  else
  {
    serachBestSolution(graph_friendship);
  }

}

void freeAndShow(Graph G)
{
  int i;
  link l;
  for (i = 0; i < G->V; i++)
  {
    printf("%d\n", G->grades[i]);
    while (G->adj[i])
    {
      l = G->adj[i];
      G->adj[i] = G->adj[i]->next;
      free(l);
    }

  }

  freeGraph(G);
}

int main()
{
  char line[100];
  int N;
  int M;
  if (fgets(line, 100, stdin))
  {
    N = new_sym_var(sizeof(int) * 8);
    M = new_sym_var(sizeof(int) * 8);
  }
  else
  {
    
  }

  graph_friendship = graphInit(N);
  readGradesAndFriendship(N, M, line);
  SCC_Tarjan(graph_friendship);
  previsionASAGrades();
  freeAndShow(graph_friendship);
  return 0;
}
