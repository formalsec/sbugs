/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


typedef struct grid *graph;
typedef struct v *vert;
typedef struct e *edge;
typedef struct slist_e *list_e;
typedef struct slist_v *list_v;
typedef struct node_adj *link_e;
typedef struct node_vert *link_v;
struct grid
{
  int nVertices;
  vert *vertex;
  list_v queue;
  link_v *heights;
};
struct v
{
  int height;
  int excess;
  int id;
  list_e adj;
};
struct e
{
  int capacity;
  int flow;
  vert out;
};
struct slist_v
{
  link_v head;
  link_v tail;
};
struct slist_e
{
  link_e head;
  link_e tail;
};
struct node_adj
{
  edge e;
  edge dual;
  link_e next;
};
struct node_vert
{
  vert v;
  link_v next;
};
typedef struct cord
{
  int in;
  int out;
} *coord;
list_v create_list_v();
void insertEndV(list_v, vert v);
void removeBeginV(list_v);
link_v insertBeginV(link_v, vert);
link_v removeV(link_v, int);
link_v h_removeBeginV(link_v);
list_e create_list_e();
void insertBeginE(list_e, edge);
void insertEndE(list_e, edge, edge);
edge create_edge(vert, int, int);
vert create_vertex(int, int);
void preflow(graph);
void addBackEdge(link_e, vert, int);
void dicharge(graph, vert);
void push(graph, link_e, vert);
void relabel(graph, vert);
void minimumCut(link_v);
int compareConnect(const void *a, const void *b);
int compareGas(const void *a, const void *b);
void free_vertex_edges_height(vert, link_v);
int main()
{
  int furn = 0;
  int comb = 0;
  int connect = 0;
  int startF = 0;
  int startComb1 = 0;
  int startComb2 = 0;
  int i = 0;
  int p = 0;
  int capacity = 0;
  int in = 0;
  int out = 0;
  vert v = 0;
  edge e = 0;
  graph grid = (graph) calloc(1, sizeof(struct grid));
  if (3 != 3)
  {
    perror("Invalid Input");
  }
  else
  {
    furn = new_sym_var(sizeof(int) * 8);
    comb = new_sym_var(sizeof(int) * 8);
    connect = new_sym_var(sizeof(int) * 8);
    
  }

  startF = 2;
  startComb1 = furn + 2;
  startComb2 = startComb1 + comb;
  grid->nVertices = (2 + (2 * comb)) + furn;
  grid->vertex = (vert *) calloc(grid->nVertices, sizeof(vert));
  grid->heights = (link_v *) calloc(grid->nVertices + 1, sizeof(link_v));
  grid->queue = create_list_v();
  grid->vertex[1] = create_vertex(1, grid->nVertices);
  grid->vertex[1]->adj = create_list_e();
  grid->heights[grid->nVertices] = insertBeginV(grid->heights[grid->nVertices], grid->vertex[1]);
  grid->vertex[0] = create_vertex(0, 0);
  grid->vertex[0]->adj = create_list_e();
  grid->heights[0] = insertBeginV(grid->heights[0], grid->vertex[0]);
  for (i = startF; i < startComb1; i++)
  {
    if (1 != 1)
    {
      perror("capacity");
    }
    else
    {
      capacity = new_sym_var(sizeof(int) * 8);
      
    }

    grid->vertex[i] = create_vertex(i, 0);
    grid->heights[0] = insertBeginV(grid->heights[0], grid->vertex[i]);
    grid->vertex[i]->adj = create_list_e();
    e = create_edge(grid->vertex[0], capacity, 0);
    insertBeginE(grid->vertex[i]->adj, e);
  }

  for (i = startComb1, p = startComb2; i < startComb2; i++, p++)
  {
    if (1 != 1)
    {
      perror("capacity");
    }
    else
    {
      capacity = new_sym_var(sizeof(int) * 8);
      
    }

    grid->vertex[i] = create_vertex(i, 0);
    grid->vertex[p] = create_vertex(-i, 0);
    grid->vertex[i]->adj = create_list_e();
    grid->vertex[p]->adj = create_list_e();
    grid->heights[0] = insertBeginV(grid->heights[0], grid->vertex[i]);
    grid->heights[0] = insertBeginV(grid->heights[0], grid->vertex[p]);
    e = create_edge(grid->vertex[p], capacity, 0);
    insertBeginE(grid->vertex[i]->adj, e);
  }

  for (i = 0; i < connect; i++)
  {
    if (3 != 3)
    {
      perror("conection");
    }
    else
    {
      out = new_sym_var(sizeof(int) * 8);
      in = new_sym_var(sizeof(int) * 8);
      capacity = new_sym_var(sizeof(int) * 8);
      
    }

    if (in >= startComb1)
    {
      e = create_edge(grid->vertex[out], capacity, 0);
      insertBeginE(grid->vertex[in + comb]->adj, e);
      continue;
    }
    else
    {
      
    }

    e = create_edge(grid->vertex[out], capacity, 0);
    insertBeginE(grid->vertex[in]->adj, e);
  }

  preflow(grid);
  while (grid->queue->head != 0)
  {
    v = grid->queue->head->v;
    removeBeginV(grid->queue);
    dicharge(grid, v);
  }

  printf("%d\n", grid->vertex[0]->excess);
  minimumCut(grid->heights[grid->nVertices]);
  for (i = 0; i < grid->nVertices; i++)
  {
    free_vertex_edges_height(grid->vertex[i], grid->heights[i]);
  }

  free_vertex_edges_height(0, grid->heights[grid->nVertices]);
  free(grid->vertex);
  free(grid->queue);
  free(grid->heights);
  free(grid);
  return 0;
}

void preflow(graph grid)
{
  link_e i = 0;
  for (i = grid->vertex[1]->adj->head; i != 0; i = i->next)
  {
    i->e->out->excess = i->e->capacity;
    i->e->flow = i->e->capacity;
    addBackEdge(i, grid->vertex[1], i->e->capacity);
    insertEndV(grid->queue, i->e->out);
  }

}

void addBackEdge(link_e prev_edge, vert new_out, int flow)
{
  edge e = create_edge(new_out, 0, -flow);
  prev_edge->dual = e;
  insertEndE(prev_edge->e->out->adj, e, prev_edge->e);
}

void dicharge(graph grid, vert v)
{
  list_e t = v->adj;
  link_e edge = t->head;
  while (v->excess > 0)
  {
    if (edge == 0)
    {
      relabel(grid, v);
      edge = v->adj->head;
    }
    else
    {
      
    }

    if ((v->height == (edge->e->out->height + 1)) && (edge->e->flow != edge->e->capacity))
    {
      push(grid, edge, v);
    }
    else
    {
      
    }

    edge = edge->next;
  }

}

void push(graph grid, link_e edge, vert v)
{
  int flow_left = edge->e->capacity - edge->e->flow;
  int flow = (v->excess < flow_left) ? (v->excess) : (flow_left);
  v->excess -= flow;
  if (((edge->e->out->excess == 0) && (flow > 0)) && ((edge->e->out->id > 1) || (edge->e->out->id < 0)))
  {
    insertEndV(grid->queue, edge->e->out);
  }
  else
  {
    
  }

  edge->e->flow += flow;
  edge->e->out->excess += flow;
  if (edge->dual == 0)
  {
    addBackEdge(edge, v, flow);
  }
  else
  {
    edge->dual->flow -= flow;
  }

}

void relabel(graph grid, vert v)
{
  int oldHeight = v->height;
  int i = 0;
  vert vertex = 0;
  int nVertices = grid->nVertices;
  int min_height = grid->nVertices * 2;
  link_e adj = v->adj->head;
  if (oldHeight < nVertices)
  {
    grid->heights[oldHeight] = removeV(grid->heights[oldHeight], v->id);
  }
  else
  {
    
  }

  if ((grid->heights[oldHeight] == 0) && (oldHeight < nVertices))
  {
    grid->heights[nVertices] = insertBeginV(grid->heights[nVertices], v);
    v->height = nVertices + 1;
    for (i = oldHeight + 1; i < nVertices; i++)
    {
      while (grid->heights[i] != 0)
      {
        vertex = grid->heights[i]->v;
        grid->heights[i] = h_removeBeginV(grid->heights[i]);
        grid->heights[nVertices] = insertBeginV(grid->heights[nVertices], vertex);
        vertex->height = nVertices + 1;
      }

    }

    return;
  }
  else
  {
    
  }

  for (; adj != 0; adj = adj->next)
  {
    if ((adj->e->out->height < min_height) && (adj->e->flow != adj->e->capacity))
    {
      min_height = adj->e->out->height;
    }
    else
    {
      
    }

  }

  if (min_height < nVertices)
  {
    grid->heights[min_height + 1] = insertBeginV(grid->heights[min_height + 1], v);
  }
  else
  {
    if (oldHeight < nVertices)
    {
      grid->heights[nVertices] = insertBeginV(grid->heights[nVertices], v);
    }
    else
    {
      
    }

  }

  v->height = min_height + 1;
}

void minimumCut(link_v gapVertex)
{
  coord minCutConect = (coord) malloc(10 * (sizeof(struct cord)));
  int *minCutGas = (int *) malloc(10 * (sizeof(int)));
  int mallConections = 10;
  int mallGas = 10;
  int i = 0;
  int nConections = 0;
  int nGas = 0;
  link_v gap = gapVertex;
  link_e gapEdges = 0;
  for (; gap != 0; gap = gap->next)
  {
    gapEdges = gap->v->adj->head;
    while (gapEdges != 0)
    {
      if (((gap->v->height > (gapEdges->e->out->height + 1)) && (gapEdges->e->capacity != 0)) && (gapEdges->e->out->id != 0))
      {
        if (nConections == (mallConections - 1))
        {
          mallConections *= 2;
          minCutConect = (coord) realloc(minCutConect, (sizeof(struct cord)) * mallConections);
        }
        else
        {
          
        }

        if (nGas == (mallGas - 1))
        {
          mallGas *= 2;
          minCutGas = (int *) realloc(minCutGas, (sizeof(int)) * mallGas);
        }
        else
        {
          
        }

        if ((-gapEdges->e->out->id) == gap->v->id)
        {
          minCutGas[nGas] = gap->v->id;
          nGas++;
        }
        else
        {
          minCutConect[nConections].in = abs(gapEdges->e->out->id);
          minCutConect[nConections].out = abs(gap->v->id);
          nConections++;
        }

      }
      else
      {
        
      }

      gapEdges = gapEdges->next;
    }

  }

  qsort(minCutGas, nGas, sizeof(int), compareGas);
  qsort(minCutConect, nConections, sizeof(struct cord), compareConnect);
  if (nGas == 0)
  {
    printf("\n");
  }
  else
  {
    
  }

  while (i < (nGas - 1))
  {
    printf("%d ", minCutGas[i]);
    i++;
  }

  if (nGas != 0)
  {
    printf("%d\n", minCutGas[i]);
  }
  else
  {
    
  }

  for (i = 0; i < nConections; i++)
    printf("%d %d\n", minCutConect[i].in, minCutConect[i].out);

  free(minCutConect);
  free(minCutGas);
}

edge create_edge(vert v, int capacity, int flow)
{
  edge e = (edge) calloc(1, sizeof(struct e));
  e->capacity = capacity;
  e->out = v;
  e->flow = flow;
  return e;
}

vert create_vertex(int id, int height)
{
  vert v = (vert) calloc(1, sizeof(struct v));
  v->excess = 0;
  v->height = height;
  v->id = id;
  v->adj = 0;
  return v;
}

list_v create_list_v()
{
  list_v i = (list_v) calloc(1, sizeof(struct slist_v));
  i->head = (i->tail = 0);
  return i;
}

void insertEndV(list_v lis, vert v)
{
  link_v newEl = (link_v) calloc(1, sizeof(struct node_vert));
  newEl->v = v;
  newEl->next = 0;
  if (lis->head == 0)
  {
    lis->head = (lis->tail = newEl);
    return;
  }
  else
  {
    
  }

  lis->tail->next = newEl;
  lis->tail = lis->tail->next;
}

void removeBeginV(list_v lis)
{
  link_v newEl = 0;
  if (lis->head == 0)
  {
    return;
  }
  else
  {
    
  }

  if (lis->head->v->id == lis->tail->v->id)
  {
    newEl = lis->head;
    free(newEl);
    lis->head = 0;
    return;
  }
  else
  {
    
  }

  newEl = lis->head;
  lis->head = lis->head->next;
  free(newEl);
}

link_v insertBeginV(link_v head, vert v)
{
  link_v newEl = calloc(1, sizeof(struct node_vert));
  newEl->v = v;
  newEl->next = head;
  head = newEl;
  return head;
}

link_v h_removeBeginV(link_v head)
{
  link_v newEl = 0;
  if (head == 0)
  {
    return head;
  }
  else
  {
    
  }

  newEl = head->next;
  free(head);
  return newEl;
}

link_v removeV(link_v head, int id)
{
  link_v ele = head;
  link_v prev_ele = 0;
  if ((head != 0) && (head->v->id == id))
  {
    ele = head->next;
    free(head);
    return ele;
  }
  else
  {
    
  }

  while ((ele != 0) && (ele->v->id != id))
  {
    prev_ele = ele;
    ele = ele->next;
  }

  if ((ele == 0) || (prev_ele == 0))
  {
    return head;
  }
  else
  {
    
  }

  prev_ele->next = ele->next;
  free(ele);
  return head;
}

list_e create_list_e()
{
  list_e i = (list_e) calloc(1, sizeof(struct slist_e));
  i->head = (i->tail = 0);
  return i;
}

void insertBeginE(list_e lis, edge e)
{
  link_e newEl = (link_e) calloc(1, sizeof(struct node_adj));
  newEl->e = e;
  if (lis->head == 0)
  {
    lis->head = (lis->tail = newEl);
    return;
  }
  else
  {
    
  }

  newEl->next = lis->head;
  lis->head = newEl;
}

void insertEndE(list_e lis, edge e, edge dual)
{
  link_e newEl = (link_e) calloc(1, sizeof(struct node_adj));
  newEl->e = e;
  newEl->next = 0;
  newEl->dual = dual;
  if (lis->head == 0)
  {
    lis->head = (lis->tail = newEl);
    return;
  }
  else
  {
    
  }

  lis->tail->next = newEl;
  lis->tail = lis->tail->next;
}

void free_vertex_edges_height(vert vertex, link_v height)
{
  link_e aux = 0;
  link_e aux2 = 0;
  link_v height_aux = height;
  link_v height_aux2 = 0;
  if (vertex != 0)
  {
    aux = vertex->adj->head;
  }
  else
  {
    
  }

  while ((aux != 0) || (height_aux != 0))
  {
    if (aux != 0)
    {
      aux2 = aux;
      free(aux->e);
      aux = aux->next;
      free(aux2);
    }
    else
    {
      
    }

    if (height_aux != 0)
    {
      height_aux2 = height_aux;
      height_aux = height_aux->next;
      free(height_aux2);
    }
    else
    {
      
    }

  }

  if (vertex != 0)
  {
    free(vertex->adj);
    free(vertex);
  }
  else
  {
    
  }

}

int compareConnect(const void *a, const void *b)
{
  coord first = (coord) a;
  coord second = (coord) b;
  int compare = first->in - second->in;
  if (compare < 0)
  {
    return -1;
  }
  else
  {
    
  }

  if (compare > 0)
  {
    return 1;
  }
  else
  {
    
  }

  return first->out - second->out;
}

int compareGas(const void *a, const void *b)
{
  return (*((int *) a)) - (*((int *) b));
}

