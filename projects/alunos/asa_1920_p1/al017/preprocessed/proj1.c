#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


typedef struct list List;
typedef struct node Node;
typedef struct vertice Vertice;
struct node
{
  int num_vertice;
  Node *next;
  Node *prev;
};
struct list
{
  Node *head;
  Node *tail;
};
struct vertice
{
  int grade;
  int d;
  int l;
  int scc;
  List friends;
  int onStack;
  Vertice *next_t;
};
Vertice *vertices;
int tempo;
int n_scc = 0;
List stack;
List *sccs;
int *Mnotas;
Node *friend(Node *tail, Node **head, int v)
{
  Node *aux = (Node *) malloc(sizeof(Node));
  aux->num_vertice = v;
  aux->next = 0;
  if (tail == 0)
  {
    aux->prev = 0;
    *head = aux;
    return *head;
  }
  else
  {
    
  }

  tail->next = aux;
  aux->prev = tail;
  tail = tail->next;
  return tail;
}

int remover(Node **head, Node **tail)
{
  int n;
  if ((*head) == (*tail))
  {
    n = (*head)->num_vertice;
    free(*head);
    *head = 0;
    *tail = 0;
  }
  else
  {
    n = (*tail)->num_vertice;
    Node *aux = *tail;
    *tail = aux->prev;
    free(aux);
  }

  return n;
}

void eliminartudo(int nvertices)
{
  int i;
  Node *t;
  Node *aux;
  for (i = 0; i < nvertices; i++)
  {
    for (t = vertices[i].friends.head; t != 0;)
    {
      vertices[i].friends.head = t->next;
      aux = t;
      t = t->next;
      if (t != 0)
      {
        t->prev = 0;
      }
      else
      {
        
      }

      free(aux);
    }

    vertices[i].friends.tail = vertices[i].friends.head;
    for (t = sccs[i].head; t != 0;)
    {
      sccs[i].head = t->next;
      aux = t;
      t = t->next;
      if (t != 0)
      {
        t->prev = 0;
      }
      else
      {
        
      }

      free(aux);
    }

    sccs[i].tail = sccs[i].head;
  }

  free(vertices);
  free(sccs);
  free(Mnotas);
}

void maxNota(int u, int i)
{
  if (Mnotas[i] < vertices[u].grade)
  {
    Mnotas[i] = vertices[u].grade;
  }
  else
  {
    
  }

}

void tarjanVisit(int i)
{
  Node *aux;
  vertices[i].d = tempo;
  vertices[i].l = tempo;
  tempo = tempo + 1;
  stack.tail = friend(stack.tail, &stack.head, i);
  vertices[i].onStack = 1;
  for (aux = vertices[i].friends.head; aux != 0; aux = aux->next)
  {
    if (vertices[aux->num_vertice].grade > vertices[i].grade)
    {
      vertices[i].grade = vertices[aux->num_vertice].grade;
    }
    else
    {
      
    }

    if (vertices[aux->num_vertice].d == (-1))
    {
      tarjanVisit(aux->num_vertice);
      if (vertices[aux->num_vertice].grade > vertices[i].grade)
      {
        vertices[i].grade = vertices[aux->num_vertice].grade;
      }
      else
      {
        
      }

      if (vertices[i].l > vertices[aux->num_vertice].l)
      {
        vertices[i].l = vertices[aux->num_vertice].l;
      }
      else
      {
        
      }

    }
    else
    {
      if (vertices[aux->num_vertice].onStack == 1)
      {
        if (vertices[i].l > vertices[aux->num_vertice].d)
        {
          vertices[i].l = vertices[aux->num_vertice].d;
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

  if (vertices[i].d == vertices[i].l)
  {
    int w = -1;
    while (i != w)
    {
      w = remover(&stack.head, &stack.tail);
      sccs[n_scc].tail = friend(sccs[n_scc].tail, &sccs[n_scc].head, w);
      maxNota(w, n_scc);
      vertices[w].scc = n_scc;
      vertices[w].onStack = 0;
    }

    n_scc++;
  }
  else
  {
    
  }

}

void tarjan(int n)
{
  tempo = 0;
  int i;
  n_scc = 0;
  for (i = 0; i < n; i++)
  {
    vertices[i].d = -1;
    vertices[i].l = -1;
    vertices[i].scc = -1;
    vertices[i].onStack = 0;
  }

  for (i = 0; i < n; i++)
  {
    if (vertices[i].d == (-1))
    {
      tarjanVisit(i);
    }
    else
    {
      
    }

  }

}

int main()
{
  int n;
  int m;
  int i;
  int j;
  int w;
  int k;
  Node *aux;
  n = new_sym_var(sizeof(int) * 8);
  m = new_sym_var(sizeof(int) * 8);
  stack.head = 0;
  stack.tail = 0;
  vertices = (Vertice *) malloc((sizeof(Vertice)) * n);
  sccs = (List *) malloc((sizeof(List)) * n);
  Mnotas = malloc((sizeof(int)) * n);
  for (i = 0; i < n; i++)
  {
    vertices[i].grade = new_sym_var(sizeof(int) * 8);
    sccs[i].head = 0;
    sccs[i].tail = 0;
    Mnotas[i] = 0;
    vertices[i].friends.head = 0;
    vertices[i].friends.tail = 0;
  }

  for (j = 0; j < m; j++)
  {
    int u;
    int v;
    u = new_sym_var(sizeof(int) * 8);
    v = new_sym_var(sizeof(int) * 8);
    vertices[u - 1].friends.tail = friend(vertices[u - 1].friends.tail, &vertices[u - 1].friends.head, v - 1);
  }

  tarjan(n);
  tarjan(n);
  for (k = 0; k < n_scc; k++)
  {
    for (aux = sccs[k].head; aux != 0; aux = aux->next)
    {
      vertices[aux->num_vertice].grade = Mnotas[k];
    }

  }

  for (w = 0; w < n; w++)
  {
    printf("%d\n", vertices[w].grade);
  }

  eliminartudo(n);
  return 0;
}
