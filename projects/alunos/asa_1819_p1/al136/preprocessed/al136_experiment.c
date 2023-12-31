#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


int min(int a, int b)
{
  return (a < b) ? (a) : (b);
}

int max(int a, int b)
{
  return (a > b) ? (a) : (b);
}

int numero_subredes_R;
int numero_routers_vulneraveis_C;
int ID_sub;
int id;
int contador_numero_vertixes;
int contador_numero_vertixes_aux;
int *List_ID;
int *Lista_routers_vulneraveis;
typedef struct Node
{
  struct Node *next;
  int vertice;
} *Node;
typedef struct List
{
  Node head;
} *List;
typedef struct Graph
{
  List List;
  int num_vertices;
} *Graph;
Node createNode(int destino);
Graph createGraph(int num_vertices);
void addEdge(Graph grafo, int fonte, int destino);
int cmpfunc(const void *a, const void *b);
int *sort(int *List_ID, int numero_subredes_R);
void sort_print(int *List_ID, int numero_subredes_R);
Node createNode(int src)
{
  Node new_Node = (Node) malloc(sizeof(Node *));
  new_Node->vertice = src;
  new_Node->next = 0;
  return new_Node;
}

Graph createGraph(int num_vertices)
{
  Graph new_graph = (Graph) malloc(sizeof(Graph *));
  new_graph->num_vertices = num_vertices;
  int i;
  for (i = 0; i < num_vertices; i++)
  {
    new_graph->List = (List) malloc(num_vertices * (sizeof(List *)));
  }

  for (i = 0; i < num_vertices; i++)
  {
    new_graph->List[i].head = 0;
  }

  return new_graph;
}

void addEdge(Graph graph, int src, int dest)
{
  dest--;
  src--;
  Node new_node = createNode(dest);
  new_node->next = graph->List[src].head;
  graph->List[src].head = new_node;
  Node new_node_2 = createNode(src);
  new_node_2->next = graph->List[dest].head;
  graph->List[dest].head = new_node_2;
}

void apAUX(Graph grafo, int node, int *isVisited, int *des, int *parent, int *low, int *ap)
{
  Node current_node = 0;
  static int time = 0;
  time++;
  des[node] = (low[node] = time);
  ID_sub = max(ID_sub, node);
  int children = 0;
  isVisited[node] = 1;
  current_node = grafo->List[node].head;
  int vertice;
  while (current_node != 0)
  {
    vertice = current_node->vertice;
    if (!isVisited[vertice])
    {
      children++;
      parent[vertice] = node;
      apAUX(grafo, current_node->vertice, isVisited, des, parent, low, ap);
      low[node] = min(low[node], low[current_node->vertice]);
      if (((parent[node] == (-1)) && (children > 1)) && (ap[node] == 0))
      {
        if (ap[node] == 0)
        {
          numero_routers_vulneraveis_C++;
          ap[node] = 1;
        }
        else
        {
          
        }

      }
      else
      {
        
      }

      if ((parent[node] != (-1)) && (des[node] <= low[current_node->vertice]))
      {
        if (ap[node] == 0)
        {
          numero_routers_vulneraveis_C++;
          ap[node] = 1;
        }
        else
        {
          
        }

      }
      else
      {
        
      }

    }
    else
    {
      if (current_node->vertice != parent[node])
      {
        low[node] = min(low[node], des[current_node->vertice]);
      }
      else
      {
        
      }

    }

    current_node = current_node->next;
  }

}

void AP(Graph grafo)
{
  int i;
  int auxiliar_index = 0;
  int *des = (int *) malloc((sizeof(int)) * grafo->num_vertices);
  int *isVisited = (int *) malloc((sizeof(int)) * grafo->num_vertices);
  int *parent = (int *) malloc((sizeof(int)) * grafo->num_vertices);
  int *low = (int *) malloc((sizeof(int)) * grafo->num_vertices);
  int *ap = (int *) malloc((sizeof(int)) * grafo->num_vertices);
  List_ID = (int *) malloc((sizeof(int)) * grafo->num_vertices);
  for (i = 0; i < (grafo->num_vertices - 1); i++)
  {
    isVisited[i] = 0;
    parent[i] = -1;
    ap[i] = 0;
  }

  for (i = 0; i < grafo->num_vertices; i++)
  {
    if (isVisited[i] == 0)
    {
      apAUX(grafo, i, isVisited, des, parent, low, ap);
      List_ID[numero_subredes_R] = ID_sub + 1;
      ID_sub = 0;
      numero_subredes_R++;
    }
    else
    {
      
    }

  }

  for (i = 0; i < grafo->num_vertices; i++)
  {
    if (ap[i] == 1)
    {
      Lista_routers_vulneraveis[auxiliar_index] = i;
      auxiliar_index++;
    }
    else
    {
      
    }

  }

  for (i = 0; i < 35; i++)
  {
  }

}

void apAUX2(Graph grafo, int node, int *isVisited)
{
  contador_numero_vertixes_aux++;
  Node current_node = 0;
  isVisited[node] = 1;
  int vertice;
  current_node = grafo->List[node].head;
  while (current_node != 0)
  {
    vertice = current_node->vertice;
    if (!isVisited[vertice])
    {
      apAUX2(grafo, vertice, isVisited);
    }
    else
    {
      
    }

    current_node = current_node->next;
  }

  contador_numero_vertixes = max(contador_numero_vertixes, contador_numero_vertixes_aux);
}

void AP2(Graph grafo)
{
  contador_numero_vertixes = 0;
  int i;
  int counter = 0;
  int *isVisited = (int *) malloc((sizeof(int)) * grafo->num_vertices);
  for (i = 0; i < grafo->num_vertices; i++)
  {
    if (Lista_routers_vulneraveis[counter] == i)
    {
      isVisited[i] = 1;
      counter++;
    }
    else
    {
      isVisited[i] = 0;
    }

  }

  for (i = 0; i < grafo->num_vertices; i++)
  {
    if (isVisited[i] == 0)
    {
      apAUX2(grafo, i, isVisited);
      contador_numero_vertixes_aux = 0;
    }
    else
    {
      
    }

  }

}

int cmpfunc(const void *a, const void *b)
{
  return (*((int *) a)) - (*((int *) b));
}

int *sort(int *Lista_sort, int numero_subredes_R)
{
  qsort(Lista_sort, numero_subredes_R, sizeof(int), cmpfunc);
  return Lista_sort;
}

void sort_print(int *Lista_sort, int numero_subredes_R)
{
  int i;
  qsort(Lista_sort, numero_subredes_R, sizeof(int), cmpfunc);
  for (i = 0; i < (numero_subredes_R - 1); i++)
  {
    printf("%d ", Lista_sort[i]);
  }

  printf("%d\n", Lista_sort[i]);
}

int main(int argc, const char *argv[])
{
  int vertices;
  int arestas;
  int ign = 1;
  vertices = new_sym_var(sizeof(int) * 8);
  ign = 1;
  arestas = new_sym_var(sizeof(int) * 8);
  numero_subredes_R = 0 * ign;
  numero_routers_vulneraveis_C = 0;
  ID_sub = 0;
  Lista_routers_vulneraveis = (int *) malloc((sizeof(int)) * vertices);
  Graph grafo = createGraph(vertices);
  int ligacoes[arestas][2];
  int i;
  for (i = 0; i < arestas; i++)
  {
    ign = 2;
    ligacoes[i][0] = new_sym_var(sizeof(int) * 8);
    ligacoes[i][1] = new_sym_var(sizeof(int) * 8);
    addEdge(grafo, ligacoes[i][0], ligacoes[i][1]);
  }

  AP(grafo);
  printf("%d\n", numero_subredes_R);
  sort_print(List_ID, numero_subredes_R);
  printf("%d\n", numero_routers_vulneraveis_C);
  sort(Lista_routers_vulneraveis, numero_routers_vulneraveis_C);
  AP2(grafo);
  printf("%d\n", contador_numero_vertixes);
  free(grafo);
  return 0;
}

