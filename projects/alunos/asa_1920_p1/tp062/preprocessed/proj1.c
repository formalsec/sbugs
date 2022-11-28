#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node
{
  int n;
  struct node *next;
} *Node;
typedef struct vertice
{
  int id;
  int grade;
  int low;
  int d;
  int CFL;
  Node first;
  Node tail;
  struct vertice *down;
} *Vertice;
typedef struct scc
{
  int id;
  int grade;
  int color;
  int f;
  int d;
  int pi;
  Node first;
  Node tail;
} *SCC;
Vertice stackHead;
int *vStack;
SCC *SCCs;
int time = 1;
int visitados = 0;
int grupos = 0;
int sccAtual = 0;
Vertice newVertex(int id, int grade)
{
  Vertice v = (Vertice) malloc(sizeof(struct vertice));
  v->id = id;
  v->grade = grade;
  v->low = -1;
  v->d = -1;
  v->first = 0;
  v->tail = 0;
  return v;
}

SCC newSCC(int id, int grade)
{
  SCC s = (SCC) malloc(sizeof(struct scc));
  s->id = id;
  s->d = -1;
  s->f = -1;
  s->color = 1;
  s->grade = grade;
  s->first = 0;
  s->tail = 0;
  return s;
}

Node newNode(int id)
{
  Node novo = (Node) malloc(sizeof(struct node));
  novo->n = id - 1;
  novo->next = 0;
  return novo;
}

Vertice *novaListaDeAmigos(int N)
{
  int i;
  int grade;
  Vertice *amigos = (Vertice *) malloc(N * (sizeof(struct vertice)));
  for (i = 0; i < N; i++)
  {
    grade = new_sym_var(sizeof(int) * 8);
    amigos[i] = newVertex(i, grade);
  }

  return amigos;
}

Vertice InsFimLista(Vertice v, int newID)
{
  Node new = newNode(newID);
  if (v->tail == 0)
  {
    v->first = new;
    v->tail = new;
    return v;
  }
  else
  {
    
  }

  v->tail->next = new;
  v->tail = new;
  return v;
}

SCC insertSCC(SCC s, int newID)
{
  Node new = newNode(newID + 1);
  if (s->tail == 0)
  {
    s->first = new;
    s->tail = new;
    return s;
  }
  else
  {
    
  }

  s->tail->next = new;
  s->tail = new;
  return s;
}

int *initvStack(int N)
{
  int i;
  int *vet = (int *) malloc((sizeof(int)) * N);
  for (i = 0; i < N; i++)
  {
    vet[i] = 0;
  }

  return vet;
}

void Push(Vertice v, int *vStack)
{
  v->down = stackHead;
  stackHead = v;
  vStack[v->id] = 1;
}

Vertice Pop(int *vStack)
{
  Vertice taken;
  if (stackHead == 0)
  {
    return 0;
  }
  else
  {
    
  }

  taken = stackHead;
  stackHead = stackHead->down;
  vStack[taken->id] = 0;
  return taken;
}

void Tarjan_Visit(Vertice *amigos, int casa, int *vStack)
{
  Vertice v = amigos[casa];
  Vertice popped;
  Node aux;
  int max;
  v->d = visitados;
  v->low = visitados;
  visitados++;
  Push(v, vStack);
  for (aux = v->first; aux != 0; aux = aux->next)
  {
    if (amigos[aux->n]->d == (-1))
    {
      Tarjan_Visit(amigos, amigos[aux->n]->id, vStack);
      if (amigos[aux->n]->low < v->low)
      {
        v->low = amigos[aux->n]->low;
      }
      else
      {
        
      }

    }
    else
    {
      if (vStack[aux->n] == 1)
      {
        if (amigos[aux->n]->d < v->low)
        {
          v->low = amigos[aux->n]->low;
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

  if (v->d == v->low)
  {
    if (sccAtual == 0)
    {
      SCCs = (SCC *) malloc((sccAtual + 1) * (sizeof(struct scc)));
    }
    else
    {
      SCCs = (SCC *) realloc(SCCs, (sccAtual + 1) * (sizeof(struct scc)));
    }

    max = 0;
    do
    {
      popped = Pop(vStack);
      popped->CFL = sccAtual;
      if (popped->grade > max)
      {
        max = popped->grade;
      }
      else
      {
        
      }

    }
    while (popped->id != v->id);
    SCCs[sccAtual] = newSCC(sccAtual, max);
    sccAtual++;
    grupos++;
  }
  else
  {
    
  }

}

void SCC_Tarjan(Vertice *amigos, int N, int *vStack)
{
  int i;
  Node aux;
  for (i = 0; i < N; i++)
  {
    if (amigos[i]->d == (-1))
    {
      Tarjan_Visit(amigos, i, vStack);
    }
    else
    {
      
    }

  }

  for (i = 0; i < N; i++)
  {
    for (aux = amigos[i]->first; aux != 0; aux = aux->next)
    {
      if (amigos[i]->CFL != amigos[aux->n]->CFL)
      {
        insertSCC(SCCs[amigos[i]->CFL], amigos[aux->n]->CFL);
      }
      else
      {
        
      }

    }

  }

}

void DFS_Visit(int u)
{
  Node aux;
  SCCs[u]->color = 0;
  SCCs[u]->d = time;
  time++;
  for (aux = SCCs[u]->first; aux != 0; aux = aux->next)
  {
    if (SCCs[u]->grade < SCCs[aux->n]->grade)
    {
      SCCs[u]->grade = SCCs[aux->n]->grade;
    }
    else
    {
      
    }

    if (SCCs[aux->n]->color == 1)
    {
      SCCs[aux->n]->pi = u;
      DFS_Visit(aux->n);
    }
    else
    {
      
    }

  }

  SCCs[u]->color = -1;
  SCCs[u]->f = time;
  time++;
}

void DFS()
{
  int i;
  for (i = 0; i < grupos; i++)
  {
    if (SCCs[i]->color == 1)
    {
      DFS_Visit(i);
    }
    else
    {
      
    }

  }

}

int main()
{
  int i;
  int students;
  int relations;
  int src;
  int dest;
  Vertice *friends;
  if (2 == 2)
  {
    students = new_sym_var(sizeof(int) * 8);
    relations = new_sym_var(sizeof(int) * 8);
  }
  else
  {
    
  }

  ;
  friends = novaListaDeAmigos(students);
  stackHead = (Vertice) malloc(sizeof(struct vertice));
  vStack = initvStack(students);
  for (i = 0; i < relations; i++)
  {
    if (2 == 2)
    {
      src = new_sym_var(sizeof(int) * 8);
      dest = new_sym_var(sizeof(int) * 8);
    }
    else
    {
      
    }

    ;
    InsFimLista(friends[src - 1], dest);
  }

  SCC_Tarjan(friends, students, vStack);
  DFS();
  for (i = 0; i < students; i++)
  {
    printf("%d\n", SCCs[friends[i]->CFL]->grade);
  }

  return 0;
}
