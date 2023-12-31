#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct connection
{
  int vertex;
  struct connection *next;
} *Connection;
typedef struct vertexs
{
  int vertex;
  int d;
  int low;
  int parent;
  bool is_articulation;
  bool visited;
  bool is_max_vertex;
  Connection head;
} *Vertexs;
typedef struct data
{
  int nr_vertexs;
  int nr_connections;
  int nr_graphs;
  int nr_vertexs_bigger_graph;
  Vertexs vertexs;
} *Data;
void printResults(Data data)
{
  printf("%d\n", data->nr_graphs);
  int i;
  int j = data->nr_graphs;
  int count_cut_vertexs = 0;
  for (i = 0; i < data->nr_vertexs; i++)
  {
    if (data->vertexs[i].is_max_vertex == true)
    {
      printf("%d", data->vertexs[i].vertex);
      j--;
      if (j > 0)
      {
        printf(" ");
      }
      else
      {
        
      }

    }
    else
    {
      
    }

    if (data->vertexs[i].is_articulation == true)
    {
      count_cut_vertexs++;
    }
    else
    {
      
    }

  }

  printf("\n%d\n%d\n", count_cut_vertexs, data->nr_vertexs_bigger_graph);
}

void dfsVisit(Data data, int u, int *variable, int mode)
{
  data->vertexs[u].visited = true;
  if (mode == 0)
  {
    static int time = 0;
    int children = 0;
    data->vertexs[u].d = (data->vertexs[u].low = ++time);
    Connection pointer;
    for (pointer = data->vertexs[u].head; pointer != 0; pointer = pointer->next)
    {
      if (data->vertexs[pointer->vertex - 1].visited == false)
      {
        *variable = ((*variable) > pointer->vertex) ? (*variable) : (pointer->vertex);
        children++;
        data->vertexs[pointer->vertex - 1].parent = u + 1;
        dfsVisit(data, pointer->vertex - 1, variable, mode);
        data->vertexs[u].low = (data->vertexs[u].low < data->vertexs[pointer->vertex - 1].low) ? (data->vertexs[u].low) : (data->vertexs[pointer->vertex - 1].low);
        if (((data->vertexs[u].parent == 0) && (children > 1)) || ((data->vertexs[u].parent != 0) && (data->vertexs[pointer->vertex - 1].low >= data->vertexs[u].d)))
        {
          data->vertexs[u].is_articulation = true;
        }
        else
        {
          
        }

      }
      else
      {
        if (pointer->vertex != data->vertexs[u].parent)
        {
          data->vertexs[u].low = (data->vertexs[u].low < data->vertexs[pointer->vertex - 1].d) ? (data->vertexs[u].low) : (data->vertexs[pointer->vertex - 1].d);
        }
        else
        {
          
        }

      }

    }

  }
  else
  {
    Connection pointer;
    for (pointer = data->vertexs[u].head; pointer != 0; pointer = pointer->next)
      if ((data->vertexs[pointer->vertex - 1].visited == false) && (data->vertexs[pointer->vertex - 1].is_articulation == false))
    {
      (*variable)++;
      dfsVisit(data, pointer->vertex - 1, variable, mode);
    }
    else
    {
      
    }


  }

}

void dfs(Data data, int mode)
{
  int u;
  for (u = 0; u < data->nr_vertexs; u++)
    data->vertexs[u].visited = false;

  if (mode == 0)
  {
    int max_vertex;
    for (u = 0; u < data->nr_vertexs; u++)
      if (data->vertexs[u].visited == false)
    {
      data->nr_graphs++;
      max_vertex = data->vertexs[u].vertex;
      dfsVisit(data, u, &max_vertex, mode);
      data->vertexs[max_vertex - 1].is_max_vertex = true;
    }
    else
    {
      
    }


  }
  else
  {
    int nr_vertexs_bigger_graph;
    for (u = 0; u < data->nr_vertexs; u++)
      if ((data->vertexs[u].visited == false) && (data->vertexs[u].is_articulation == false))
    {
      nr_vertexs_bigger_graph = 1;
      dfsVisit(data, u, &nr_vertexs_bigger_graph, mode);
      data->nr_vertexs_bigger_graph = (data->nr_vertexs_bigger_graph > nr_vertexs_bigger_graph) ? (data->nr_vertexs_bigger_graph) : (nr_vertexs_bigger_graph);
    }
    else
    {
      
    }


  }

}

void deleteData(Data data)
{
  int i;
  for (i = 0; i < data->nr_vertexs; i++)
  {
    Connection pointer;
    for (pointer = data->vertexs[i].head; pointer != 0;)
    {
      Connection pointer_delete = pointer;
      pointer = pointer->next;
      free(pointer_delete);
    }

  }

  free(data->vertexs);
  free(data);
}

void createDataAux(Data data, int vertex_1, int vertex_2)
{
  Connection current;
  if ((current = (Connection) malloc(sizeof(struct connection))) == 0)
  {
    perror("Error in malloc in createDataAux (current)");
    exit(1);
  }
  else
  {
    
  }

  current->vertex = vertex_2;
  Connection pointer_backup = data->vertexs[vertex_1 - 1].head;
  data->vertexs[vertex_1 - 1].head = current;
  data->vertexs[vertex_1 - 1].head->next = pointer_backup;
}

Data createData()
{
  Data data;
  if ((data = (Data) malloc(sizeof(struct data))) == 0)
  {
    perror("Error in malloc in createData (data)");
    exit(1);
  }
  else
  {
    
  }

  if (2 == 0)
  {
    perror("Error in scanf in createData");
    exit(1);
  }
  else
  {
    data->nr_vertexs = new_sym_var(sizeof(int) * 8);
    data->nr_connections = new_sym_var(sizeof(int) * 8);
    
  }

  data->nr_graphs = 0;
  data->nr_vertexs_bigger_graph = 0;
  if ((data->vertexs = (Vertexs) malloc(data->nr_vertexs * (sizeof(struct vertexs)))) == 0)
  {
    perror("Error in malloc in createData (data->vertexs)");
    exit(1);
  }
  else
  {
    
  }

  int i;
  for (i = 0; i < data->nr_vertexs; i++)
  {
    data->vertexs[i].vertex = i + 1;
    data->vertexs[i].parent = 0;
    data->vertexs[i].is_articulation = false;
    data->vertexs[i].is_max_vertex = false;
    data->vertexs[i].head = 0;
  }

  for (i = 0; i < data->nr_connections; i++)
  {
    int vertex_s;
    int vertex_d;
    if (2 == 0)
    {
      perror("Error in scanf in createData");
      exit(1);
    }
    else
    {
      vertex_s = new_sym_var(sizeof(int) * 8);
      vertex_d = new_sym_var(sizeof(int) * 8);
      
    }

    createDataAux(data, vertex_s, vertex_d);
    createDataAux(data, vertex_d, vertex_s);
  }

  return data;
}

int main()
{
  Data data;
  data = createData();
  dfs(data, 0);
  dfs(data, 1);
  printResults(data);
  deleteData(data);
  return 0;
}

