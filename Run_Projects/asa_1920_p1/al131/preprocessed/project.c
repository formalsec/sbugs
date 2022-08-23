/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


typedef struct node *link;
struct node
{
  int w;
  link next;
};
typedef struct graph
{
  int V;
  int A;
  link *adj;
} *Graph;
static link NEWnode(int w, link next)
{
  link a = malloc(sizeof(struct node));
  a->w = w;
  a->next = next;
  return a;
}

Graph GRAPHinit(int V)
{
  int v;
  Graph G = malloc(sizeof(G));
  G->V = V;
  G->A = 0;
  G->adj = malloc((V + 1) * (sizeof(link)));
  for (v = 1; v <= V; v++)
  {
    G->adj[v] = 0;
  }

  return G;
}

void GRAPHinsertArc(Graph G, int v, int w)
{
  link a;
  for (a = G->adj[v]; a != 0; a = a->next)
  {
    if (a->w == w)
    {
      return;
    }
    else
    {
      
    }

  }

  G->adj[v] = NEWnode(w, G->adj[v]);
  G->A++;
}

int main()
{
  int students;
  int relations;
  int i;
  students = new_sym_var(sizeof(int) * 8);
  relations = new_sym_var(sizeof(int) * 8);
  int test_grades[students + 1];
  for (i = 1; i <= students; i++)
  {
    test_grades[i] = new_sym_var(sizeof(int) * 8);
  }

  Graph G = GRAPHinit(students);
  for (i = 0; i < relations; i++)
  {
    int u;
    int v;
    u = new_sym_var(sizeof(int) * 8);
    v = new_sym_var(sizeof(int) * 8);
    GRAPHinsertArc(G, u, v);
  }

  int nochanges = 0;
  while (nochanges == 0)
  {
    int changed = 0;
    int grade = 0;
    for (i = 1; i <= G->V; ++i)
    {
      grade = test_grades[i];
      link a;
      for (a = G->adj[i]; a != 0; a = a->next)
      {
        if (grade < test_grades[a->w])
        {
          grade = test_grades[a->w];
        }
        else
        {
          
        }

      }

      if (test_grades[i] != grade)
      {
        test_grades[i] = grade;
        changed = 1;
      }
      else
      {
        
      }

    }

    if (changed == 0)
    {
      nochanges = 1;
    }
    else
    {
      
    }

  }

  for (i = 1; i <= students; i++)
  {
    printf("%d\n", test_grades[i]);
  }

  return 0;
}

