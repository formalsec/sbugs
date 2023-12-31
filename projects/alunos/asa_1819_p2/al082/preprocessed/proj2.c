#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


typedef int color;
typedef int bool;
struct edge
{
  int o;
  int d;
};
struct node
{
  int number;
  int flow;
  int capacity;
  int residual_network_flow;
  struct node *next;
};
struct node2
{
  int number;
  struct node2 *next;
};
struct fifo
{
  struct node2 *head;
  struct node2 *tail;
};
struct list
{
  struct node *forward_head;
  struct node *backward_head;
  int excess;
  int height;
  color visitado;
};
struct Graph
{
  int N_vertices;
  struct list *lista_adj;
};
bool flag = 100;
int gap_number;
int fornecedores;
int n_estacoes;
int size_arestas_aumentadas = 1;
int contador = 0;
struct edge **arestas_aumentadas;
struct fifo FIFO;
struct Graph *graph;
struct Graph *new_graph(int vertices)
{
  struct Graph *graph = (struct Graph *) malloc(sizeof(struct Graph));
  graph->N_vertices = vertices;
  graph->lista_adj = (struct list *) malloc((vertices + 1) * (sizeof(struct list)));
  int i;
  for (i = 1; i <= vertices; i++)
  {
    graph->lista_adj[i].excess = 0;
    graph->lista_adj[i].height = 0;
    graph->lista_adj[i].forward_head = 0;
    graph->lista_adj[i].backward_head = 0;
    graph->lista_adj[i].visitado = -1;
  }

  graph->lista_adj[0].excess = 0;
  graph->lista_adj[0].height = graph->N_vertices;
  graph->lista_adj[0].backward_head = 0;
  graph->lista_adj[0].forward_head = 0;
  graph->lista_adj[0].visitado = -1;
  return graph;
}

struct node2 *new_node2(int v)
{
  struct node2 *new_node = (struct node2 *) malloc(sizeof(struct node2));
  new_node->number = v;
  new_node->next = 0;
  return new_node;
}

struct node *new_node(int v, int capacidade)
{
  struct node *new_node = (struct node *) malloc(sizeof(struct node));
  new_node->number = v;
  new_node->next = 0;
  new_node->flow = 0;
  new_node->capacity = capacidade;
  new_node->residual_network_flow = 0;
  return new_node;
}

struct edge *create_edge(int u, int v)
{
  struct edge *new_edge = (struct edge *) malloc(sizeof(struct edge));
  new_edge->o = u;
  new_edge->d = v;
  return new_edge;
}

void update_fifo2(int n)
{
  if (FIFO.tail != 0)
  {
    if (((n != 1) && (n != 0)) && (FIFO.tail->number != n))
    {
      struct node2 *aux_node = new_node2(n);
      FIFO.tail->next = aux_node;
      FIFO.tail = aux_node;
    }
    else
    {
      
    }

  }
  else
  {
    
  }

}

void printFIFO()
{
  printf("FIFO:");
  struct node2 *go = FIFO.head;
  while (go)
  {
    printf("-> %d", go->number);
    go = go->next;
  }

  printf("\n");
}

void update_fifo(int n)
{
  if (FIFO.tail != 0)
  {
    if (((n != 1) && (n != 0)) && (FIFO.tail->number != n))
    {
      struct node2 *aux_node = new_node2(n);
      if (FIFO.head->next == 0)
      {
        struct node2 *aux2;
        aux2 = FIFO.head;
        FIFO.head = aux_node;
        FIFO.tail = aux_node;
        free(aux2);
      }
      else
      {
        struct node2 *aux2;
        aux2 = FIFO.head;
        FIFO.head = FIFO.head->next;
        free(aux2);
        FIFO.tail->next = aux_node;
        FIFO.tail = aux_node;
      }

    }
    else
    {
      struct node2 *aux2;
      aux2 = FIFO.head;
      FIFO.head = FIFO.head->next;
      free(aux2);
    }

  }
  else
  {
    
  }

}

void initialize_fifo(int n)
{
  struct node2 *aux_node = new_node2(n);
  if (FIFO.head == 0)
  {
    FIFO.head = aux_node;
    FIFO.tail = aux_node;
  }
  else
  {
    FIFO.tail->next = aux_node;
    FIFO.tail = aux_node;
  }

}

void update_flux(int n, int v, int flux)
{
  struct node *aux_node = graph->lista_adj[v].backward_head;
  while (aux_node)
  {
    if (aux_node->number == n)
    {
      aux_node->flow = flux;
    }
    else
    {
      
    }

    aux_node = aux_node->next;
  }

}

void add_to_graph(int v, int u, int capacidade, bool flag)
{
  struct node *aux_node = new_node(u, capacidade);
  if (v == 0)
  {
    aux_node->flow = capacidade;
  }
  else
  {
    
  }

  if (((v >= gap_number) && (v < (gap_number + n_estacoes))) && (flag == 101))
  {
    v += n_estacoes;
  }
  else
  {
    
  }

  aux_node->next = graph->lista_adj[v].forward_head;
  graph->lista_adj[v].forward_head = aux_node;
  aux_node = new_node(v, capacidade);
  if (v == 0)
  {
    aux_node->flow = capacidade;
  }
  else
  {
    
  }

  aux_node->next = graph->lista_adj[u].backward_head;
  graph->lista_adj[u].backward_head = aux_node;
}

void read_input()
{
  int arestas;
  int vertices;
  int production;
  int capacidade;
  int u;
  int v;
  int i = 0;
  fornecedores = new_sym_var(sizeof(int) * 8);
  n_estacoes = new_sym_var(sizeof(int) * 8);
  arestas = new_sym_var(sizeof(int) * 8);
  gap_number = fornecedores + 2;
  vertices = gap_number + (2 * n_estacoes);
  graph = new_graph(vertices);
  while (i < fornecedores)
  {
    production = new_sym_var(sizeof(int) * 8);
    initialize_fifo(i + 2);
    graph->lista_adj[i + 2].excess = production;
    graph->lista_adj[0].excess -= production;
    add_to_graph(0, i + 2, production, 101);
    i++;
  }

  i = 0;
  while (i < n_estacoes)
  {
    production = new_sym_var(sizeof(int) * 8);
    add_to_graph(gap_number + i, (gap_number + n_estacoes) + i, production, 100);
    i++;
  }

  i = 0;
  while (i < arestas)
  {
    v = new_sym_var(sizeof(int) * 8);
    u = new_sym_var(sizeof(int) * 8);
    capacidade = new_sym_var(sizeof(int) * 8);
    add_to_graph(v, u, capacidade, 101);
    i++;
  }

}

void DFS_visit(int vertex)
{
  int residual;
  graph->lista_adj[vertex].visitado = 0;
  struct node *aux_node = graph->lista_adj[vertex].backward_head;
  struct node *aux_node2 = graph->lista_adj[vertex].forward_head;
  while (aux_node)
  {
    residual = aux_node->capacity - aux_node->flow;
    if ((graph->lista_adj[aux_node->number].visitado == (-1)) && (residual > 0))
    {
      DFS_visit(aux_node->number);
    }
    else
    {
      
    }

    aux_node = aux_node->next;
  }

  while (aux_node2)
  {
    if ((graph->lista_adj[aux_node2->number].visitado == (-1)) && (aux_node2->flow > 0))
    {
      DFS_visit(aux_node2->number);
    }
    else
    {
      
    }

    aux_node2 = aux_node2->next;
  }

  graph->lista_adj[vertex].visitado = 1;
}

void relabel(int u)
{
  struct node *aux_node = graph->lista_adj[u].forward_head;
  int min = (2 * graph->N_vertices) + 1;
  while (aux_node != 0)
  {
    if ((min > graph->lista_adj[aux_node->number].height) && (graph->lista_adj[aux_node->number].height >= graph->lista_adj[u].height))
    {
      min = graph->lista_adj[aux_node->number].height;
    }
    else
    {
      
    }

    aux_node = aux_node->next;
  }

  aux_node = graph->lista_adj[u].backward_head;
  while (aux_node != 0)
  {
    if ((min > graph->lista_adj[aux_node->number].height) && (graph->lista_adj[aux_node->number].height >= graph->lista_adj[u].height))
    {
      min = graph->lista_adj[aux_node->number].height;
    }
    else
    {
      
    }

    aux_node = aux_node->next;
  }

  graph->lista_adj[u].height = min + 1;
}

void backwards_discharge(int u)
{
  struct node *backward = graph->lista_adj[u].backward_head;
  int disponivel;
  while ((graph->lista_adj[u].excess > 0) && (backward != 0))
  {
    disponivel = backward->flow;
    if ((graph->lista_adj[u].height > graph->lista_adj[backward->number].height) && (disponivel > 0))
    {
      if (disponivel < graph->lista_adj[u].excess)
      {
        backward->flow = 0;
        update_flux(u, backward->number, backward->flow);
        graph->lista_adj[u].excess -= disponivel;
        graph->lista_adj[backward->number].excess += disponivel;
        update_fifo2(backward->number);
      }
      else
      {
        backward->flow -= graph->lista_adj[u].excess;
        update_flux(u, backward->number, backward->flow);
        graph->lista_adj[backward->number].excess += graph->lista_adj[u].excess;
        graph->lista_adj[u].excess = 0;
        update_fifo(backward->number);
        break;
      }

    }
    else
    {
      
    }

    backward = backward->next;
  }

}

void forward_discharge(int u)
{
  struct node *forward = graph->lista_adj[u].forward_head;
  int disponivel;
  while ((graph->lista_adj[u].excess > 0) && (forward != 0))
  {
    disponivel = forward->capacity - forward->flow;
    if ((graph->lista_adj[u].height > graph->lista_adj[forward->number].height) && (disponivel > 0))
    {
      if (disponivel < graph->lista_adj[u].excess)
      {
        forward->flow += disponivel;
        update_flux(u, forward->number, forward->flow);
        graph->lista_adj[u].excess -= disponivel;
        graph->lista_adj[forward->number].excess += disponivel;
        update_fifo2(forward->number);
      }
      else
      {
        forward->flow += graph->lista_adj[u].excess;
        update_flux(u, forward->number, forward->flow);
        graph->lista_adj[forward->number].excess += graph->lista_adj[u].excess;
        graph->lista_adj[u].excess = 0;
        update_fifo(forward->number);
        break;
      }

    }
    else
    {
      
    }

    forward = forward->next;
  }

  backwards_discharge(u);
  if (graph->lista_adj[u].excess > 0)
  {
    relabel(u);
  }
  else
  {
    
  }

}

void save_edge(int u, int v)
{
  if (u != 0)
  {
    struct edge *new_edge = create_edge(u, v);
    if (size_arestas_aumentadas <= contador)
    {
      size_arestas_aumentadas += 10;
      arestas_aumentadas = (struct edge **) realloc((void *) arestas_aumentadas, size_arestas_aumentadas * (sizeof(struct edge *)));
    }
    else
    {
      
    }

    arestas_aumentadas[contador] = new_edge;
    contador++;
  }
  else
  {
    
  }

}

int verify(int n)
{
  if (n >= (gap_number + n_estacoes))
  {
    return n - n_estacoes;
  }
  else
  {
    return n;
  }

}

void seeBorderEdgesFornecedores()
{
  int i;
  for (i = 2; i < gap_number; i++)
  {
    if (graph->lista_adj[i].visitado == 1)
    {
      struct node *aux_node = graph->lista_adj[i].forward_head;
      while (aux_node)
      {
        if (graph->lista_adj[aux_node->number].visitado != 1)
        {
          save_edge(i, aux_node->number);
        }
        else
        {
          
        }

        aux_node = aux_node->next;
      }

    }
    else
    {
      
    }

  }

}

void print()
{
  int i;
  for (i = 0; i < contador; i++)
  {
    printf("%d %d\n", arestas_aumentadas[i]->o, arestas_aumentadas[i]->d);
  }

}

void initialize_relable_to_front()
{
  while (FIFO.head)
  {
    if (graph->lista_adj[FIFO.head->number].excess > 0)
    {
      forward_discharge(FIFO.head->number);
    }
    else
    {
      FIFO.head = FIFO.head->next;
    }

  }

}

void seeBorderEdges()
{
  int i;
  struct node *back_node = graph->lista_adj[1].backward_head;
  struct node *front_node;
  while (back_node)
  {
    if (graph->lista_adj[back_node->number].visitado != 1)
    {
      back_node->number = verify(back_node->number);
      save_edge(back_node->number, 1);
    }
    else
    {
      
    }

    back_node = back_node->next;
  }

  for (i = gap_number; i < (gap_number + n_estacoes); i++)
  {
    if ((graph->lista_adj[i + n_estacoes].visitado == 1) && (graph->lista_adj[i].visitado != 1))
    {
      if (flag == 100)
      {
        printf("%d", i);
        flag = 101;
      }
      else
      {
        printf(" %d", i);
      }

    }
    else
    {
      
    }

    if (graph->lista_adj[i].visitado == 1)
    {
      front_node = graph->lista_adj[i + n_estacoes].forward_head;
      back_node = graph->lista_adj[i].backward_head;
      while (front_node)
      {
        if (graph->lista_adj[front_node->number].visitado != 1)
        {
          save_edge(i, front_node->number);
        }
        else
        {
          
        }

        front_node = front_node->next;
      }

      while (back_node)
      {
        if (graph->lista_adj[back_node->number].visitado != 1)
        {
          back_node->number = verify(back_node->number);
          save_edge(back_node->number, i);
        }
        else
        {
          
        }

        back_node = back_node->next;
      }

    }
    else
    {
      
    }

  }

  printf("\n");
}

void merge(struct edge *vetor[], int comeco, int meio, int fim)
{
  int com1 = comeco;
  int com2 = meio + 1;
  int comAux = 0;
  int tam = (fim - comeco) + 1;
  struct edge **vetAux;
  vetAux = (struct edge **) malloc(tam * (sizeof(struct edge)));
  while ((com1 <= meio) && (com2 <= fim))
  {
    if (vetor[com1]->o < vetor[com2]->o)
    {
      vetAux[comAux] = vetor[com1];
      com1++;
    }
    else
    {
      if (vetor[com1]->o == vetor[com2]->o)
      {
        if (vetor[com1]->d < vetor[com2]->d)
        {
          vetAux[comAux] = vetor[com1];
          com1++;
        }
        else
        {
          vetAux[comAux] = vetor[com2];
          com2++;
        }

      }
      else
      {
        vetAux[comAux] = vetor[com2];
        com2++;
      }

    }

    comAux++;
  }

  while (com1 <= meio)
  {
    vetAux[comAux] = vetor[com1];
    comAux++;
    com1++;
  }

  while (com2 <= fim)
  {
    vetAux[comAux] = vetor[com2];
    comAux++;
    com2++;
  }

  for (comAux = comeco; comAux <= fim; comAux++)
  {
    vetor[comAux] = vetAux[comAux - comeco];
  }

  free(vetAux);
}

void mergeSort(struct edge *vetor[], int comeco, int fim)
{
  if (comeco < fim)
  {
    int meio = (fim + comeco) / 2;
    mergeSort(vetor, comeco, meio);
    mergeSort(vetor, meio + 1, fim);
    merge(vetor, comeco, meio, fim);
  }
  else
  {
    
  }

}

void reachable_from_sink()
{
  int m;
  for (m = 1; m < graph->N_vertices; m++)
  {
    if (graph->lista_adj[m].visitado == 1)
    {
      printf("%d->altura:%d\n", m, graph->lista_adj[m].height);
    }
    else
    {
      
    }

  }

  printf("\n");
}

void free_graph()
{
  int i;
  struct node *aux_node;
  for (i = 0; i <= graph->N_vertices; i++)
  {
    while (graph->lista_adj[i].forward_head)
    {
      aux_node = graph->lista_adj[i].forward_head;
      graph->lista_adj[i].forward_head = aux_node->next;
      free(aux_node);
    }

    while (graph->lista_adj[i].backward_head)
    {
      aux_node = graph->lista_adj[i].backward_head;
      graph->lista_adj[i].backward_head = aux_node->next;
      free(aux_node);
    }

  }

  free(graph->lista_adj);
  free(graph);
}

void free_arestas()
{
  int i;
  for (i = 0; i < contador; i++)
  {
    free(arestas_aumentadas[i]);
  }

  free(arestas_aumentadas);
}

int main()
{
  FIFO.head = 0;
  FIFO.tail = 0;
  arestas_aumentadas = (struct edge **) malloc(sizeof(struct edge *));
  read_input();
  initialize_relable_to_front();
  DFS_visit(1);
  printf("%d\n", graph->lista_adj[1].excess);
  seeBorderEdgesFornecedores();
  seeBorderEdges();
  mergeSort(arestas_aumentadas, 0, contador - 1);
  print();
  free_graph();
  free_arestas();
  return 0;
}

