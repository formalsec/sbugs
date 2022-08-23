/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct fila_element
{
  int value;
  struct fila_element *next;
} Fila_Element;
typedef struct fila
{
  Fila_Element *first;
  Fila_Element *last;
} Fila;
Fila *new_fila()
{
  Fila *f = malloc(sizeof(Fila));
  f->first = 0;
  f->last = 0;
  return f;
}

void free_fila_element(Fila_Element *fe)
{
  free(fe);
}

void free_fila(Fila *f)
{
  Fila_Element *fe;
  Fila_Element *aux;
  fe = f->first;
  while (fe)
  {
    aux = fe;
    fe = fe->next;
    free_fila_element(aux);
  }

  free(f);
}

int is_fila_empty(Fila *f)
{
  if (f->first)
  {
    return 0;
  }
  else
  {
    return -1;
  }

}

void enqueue_fila(Fila *f, int value)
{
  Fila_Element *fe = malloc(sizeof(Fila_Element));
  fe->value = value;
  if (!f->first)
  {
    f->first = fe;
  }
  else
  {
    f->last->next = fe;
  }

  fe->next = 0;
  f->last = fe;
}

int dequeue_fila(Fila *f)
{
  Fila_Element *fe = f->first;
  int value;
  if (!fe)
  {
    return -1;
  }
  else
  {
    
  }

  if (!fe->next)
  {
    f->last = 0;
    f->first = 0;
  }
  else
  {
    f->first = fe->next;
  }

  value = fe->value;
  free_fila_element(fe);
  return value;
}

typedef struct linked_list_destination_node
{
  int id;
  int limite;
  int fluxo;
  struct linked_list_destination_node *next;
} LinkedListDestinationNode;
typedef struct linked_list_base_node
{
  LinkedListDestinationNode *first;
} LinkedListBaseNode;
typedef struct grafo
{
  int dimension;
  LinkedListBaseNode *baseNodes;
} Grafo;
Grafo *new_grafo(int dimension)
{
  Grafo *g = malloc(sizeof(Grafo));
  LinkedListBaseNode *bn;
  int i;
  g->dimension = dimension;
  g->baseNodes = malloc(g->dimension * (sizeof(LinkedListBaseNode)));
  bn = g->baseNodes;
  for (i = 0; i < g->dimension; i++)
    (bn + i)->first = 0;

  return g;
}

void free_grafo(Grafo *g)
{
  int i;
  LinkedListBaseNode *bn;
  LinkedListDestinationNode *dn;
  LinkedListDestinationNode *tmp;
  bn = g->baseNodes;
  for (i = 0; i < g->dimension; i++)
  {
    dn = (bn + i)->first;
    while (dn)
    {
      tmp = dn;
      dn = tmp->next;
      free(tmp);
    }

  }

  free(g->baseNodes);
  free(g);
}

void add_node_grafo(Grafo *g, int from, int to, int limite)
{
  LinkedListDestinationNode *dn;
  LinkedListDestinationNode *tmp;
  LinkedListDestinationNode *prev;
  LinkedListBaseNode *bn = g->baseNodes;
  prev = 0;
  tmp = (bn + from)->first;
  while (tmp)
  {
    if (tmp->id == to)
    {
      return;
    }
    else
    {
      
    }

    prev = tmp;
    tmp = tmp->next;
  }

  dn = malloc(sizeof(LinkedListDestinationNode));
  dn->id = to;
  dn->limite = limite;
  dn->fluxo = 0;
  dn->next = 0;
  if (prev)
  {
    prev->next = dn;
  }
  else
  {
    (bn + from)->first = dn;
  }

}

int get_fluxo_residual(Grafo *g, int from, int to)
{
  LinkedListBaseNode *bn = g->baseNodes + from;
  LinkedListDestinationNode *dn = bn->first;
  while (dn)
  {
    if (dn->id == to)
    {
      return dn->limite - dn->fluxo;
    }
    else
    {
      
    }

  }

  return -1;
}

void node_increment_fluxo(Grafo *g, int from, int to, int incr)
{
  LinkedListBaseNode *bn = g->baseNodes + from;
  LinkedListDestinationNode *dn = bn->first;
  while (dn)
  {
    if (dn->id == to)
    {
      dn->fluxo += incr;
      return;
    }
    else
    {
      
    }

    dn = dn->next;
  }

}

LinkedListDestinationNode *get_first_destination_node(Grafo *g, int from)
{
  LinkedListBaseNode *bn = g->baseNodes + from;
  return bn->first;
}

void print_grafo(Grafo *g)
{
  int i;
  LinkedListBaseNode *bn = g->baseNodes;
  LinkedListDestinationNode *dn;
  printf("\n ******* PRINT GRAFO *******");
  for (i = 0; i < g->dimension; i++)
  {
    printf("\n[%d]  ", i);
    dn = (bn + i)->first;
    while (dn)
    {
      printf(" ->  {ID=%d | L= %d | F=%d} ", dn->id, dn->limite, dn->fluxo);
      dn = dn->next;
    }

  }

  printf("\n ******* FIM PRINT GRAFO *******\n");
}

typedef struct mapa
{
  int avenidas;
  int ruas;
  Grafo *representacao;
} Mapa;
Mapa *new_mapa(int avenidas, int ruas)
{
  Mapa *m = malloc(sizeof(Mapa));
  m->avenidas = avenidas;
  m->ruas = ruas;
  m->representacao = new_grafo(((2 * avenidas) * ruas) + 2);
  return m;
}

void preenche_mapa(Mapa *mapa, int s, int c)
{
  int i;
  int j;
  int av;
  int rua;
  int from;
  int to;
  int in;
  int out;
  int esc = mapa->representacao->dimension - 1;
  int fnt = 0;
  for (i = 1; i <= mapa->avenidas; i++)
  {
    for (j = 1; j <= mapa->ruas; j++)
    {
      out = (from = (i + (mapa->avenidas * (j - 1))) + (mapa->avenidas * mapa->ruas));
      ;
      in = i + (mapa->avenidas * (j - 1));
      ;
      add_node_grafo(mapa->representacao, in, out, 1);
      add_node_grafo(mapa->representacao, out, in, 0);
      if ((i - 1) > 0)
      {
        to = (i - 1) + (mapa->avenidas * (j - 1));
        ;
        add_node_grafo(mapa->representacao, from, to, 1);
        add_node_grafo(mapa->representacao, to, from, 0);
      }
      else
      {
        
      }

      if ((i + 1) <= mapa->avenidas)
      {
        to = (i + 1) + (mapa->avenidas * (j - 1));
        ;
        add_node_grafo(mapa->representacao, from, to, 1);
        add_node_grafo(mapa->representacao, to, from, 0);
      }
      else
      {
        
      }

      if ((j - 1) > 0)
      {
        to = i + (mapa->avenidas * ((j - 1) - 1));
        ;
        add_node_grafo(mapa->representacao, from, to, 1);
        add_node_grafo(mapa->representacao, to, from, 0);
      }
      else
      {
        
      }

      if ((j + 1) <= mapa->ruas)
      {
        to = i + (mapa->avenidas * ((j + 1) - 1));
        ;
        add_node_grafo(mapa->representacao, from, to, 1);
        add_node_grafo(mapa->representacao, to, from, 0);
      }
      else
      {
        
      }

    }

  }

  for (i = 0; i < s; i++)
  {
    av = new_sym_var(sizeof(int) * 8);
    rua = new_sym_var(sizeof(int) * 8);
    from = (av + (mapa->avenidas * (rua - 1))) + (mapa->avenidas * mapa->ruas);
    ;
    add_node_grafo(mapa->representacao, from, esc, 1);
    add_node_grafo(mapa->representacao, esc, from, 0);
  }

  for (i = 0; i < c; i++)
  {
    av = new_sym_var(sizeof(int) * 8);
    rua = new_sym_var(sizeof(int) * 8);
    to = av + (mapa->avenidas * (rua - 1));
    ;
    add_node_grafo(mapa->representacao, fnt, to, 1);
    add_node_grafo(mapa->representacao, to, fnt, 0);
  }

}

void free_mapa(Mapa *mapa)
{
  free_grafo(mapa->representacao);
  free(mapa);
}

Fila *fila;
int *visitados;
int bfs(Mapa *mapa, int *caminho, int from, int to)
{
  int actual_node;
  LinkedListDestinationNode *dn = 0;
  memset(visitados, 0, mapa->representacao->dimension * (sizeof(*visitados)));
  enqueue_fila(fila, from);
  caminho[from] = -1;
  visitados[from] = 1;
  while (is_fila_empty(fila) == 0)
  {
    actual_node = dequeue_fila(fila);
    visitados[actual_node] = 2;
    dn = get_first_destination_node(mapa->representacao, actual_node);
    while (dn)
    {
      if ((visitados[dn->id] == 0) && ((dn->limite - dn->fluxo) > 0))
      {
        enqueue_fila(fila, dn->id);
        visitados[dn->id] = 1;
        caminho[dn->id] = actual_node;
      }
      else
      {
        
      }

      dn = dn->next;
    }

  }

  if (visitados[to] == 2)
  {
    return 1;
  }
  else
  {
    return 0;
  }

}

int fluxo_maximo(Mapa *mapa)
{
  int *caminho = malloc(mapa->representacao->dimension * (sizeof(int)));
  int pos;
  int fluxo = 0;
  while (bfs(mapa, caminho, 0, mapa->representacao->dimension - 1))
  {
    fluxo++;
    pos = mapa->representacao->dimension - 1;
    do
    {
      node_increment_fluxo(mapa->representacao, caminho[pos], pos, 1);
      node_increment_fluxo(mapa->representacao, pos, caminho[pos], -1);
      pos = caminho[pos];
    }
    while (pos != 0);
  }

  free(caminho);
  return fluxo;
}

int main()
{
  Mapa *mapa;
  int avenidas;
  int ruas;
  int s;
  int c;
  fila = new_fila();
  avenidas = new_sym_var(sizeof(int) * 8);
  ruas = new_sym_var(sizeof(int) * 8);
  mapa = new_mapa(avenidas, ruas);
  visitados = (int *) malloc(mapa->representacao->dimension * (sizeof(int)));
  s = new_sym_var(sizeof(int) * 8);
  c = new_sym_var(sizeof(int) * 8);
  preenche_mapa(mapa, s, c);
  printf("%d\n", fluxo_maximo(mapa));
  free_fila(fila);
  free(visitados);
  free_mapa(mapa);
  return 0;
}

