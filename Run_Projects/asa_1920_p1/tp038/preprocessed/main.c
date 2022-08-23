/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


typedef struct Node
{
  int index;
  int low;
  int in_stack;
  int id;
  int scc_id;
  int *adj;
  int grade;
  int total_childs;
  int visited;
} node;
typedef struct Scc
{
  int node_id;
  int max;
  int scc_counter;
  int visited;
} scc;
typedef struct SccAdj
{
  int scc_id;
  int scc_adj_counter;
} sccadj;
typedef struct Stack
{
  int top;
  int *items;
} stack;
node *nodes;
stack buf;
scc **sccs;
sccadj **scc_adj;
int total_students = 0;
int total_relationships = 0;
int sccs_count = 0;
int curr_index = 0;
void init_vars()
{
  buf.items = malloc((sizeof(int)) * total_students);
  buf.top = -1;
  sccs = malloc((sizeof(scc *)) * total_students);
}

void process_input()
{
  char c;
  total_students = new_sym_var(sizeof(int) * 8);
  c = new_sym_var(sizeof(char) * 8);
  total_relationships = new_sym_var(sizeof(int) * 8);
  nodes = malloc((sizeof(node)) * total_students);
  int i = 0;
  for (; i < total_students; i++)
  {
    nodes[i].grade = new_sym_var(sizeof(int) * 8);
    nodes[i].adj = 0;
    nodes[i].id = i;
    nodes[i].total_childs = 0;
    nodes[i].index = -1;
    nodes[i].low = -1;
    nodes[i].visited = -1;
    nodes[i].in_stack = 0;
    nodes[i].scc_id = -1;
  }

  int j = 0;
  int u = 0;
  int v = 0;
  for (; j < total_relationships; j++)
  {
    u = new_sym_var(sizeof(int) * 8);
    v = new_sym_var(sizeof(int) * 8);
    u--;
    v--;
    if (!nodes[u].adj)
    {
      nodes[u].adj = malloc(sizeof(int));
    }
    else
    {
      int *newAdj = realloc(nodes[u].adj, (sizeof(int)) * (nodes[u].total_childs + 1));
      nodes[u].adj = newAdj;
    }

    nodes[u].adj[nodes[u].total_childs] = v;
    nodes[u].total_childs++;
  }

}

void stack_push(int v)
{
  buf.top++;
  buf.items[buf.top] = v;
}

int stack_pop()
{
  return (buf.top < 0) ? (-1) : (buf.items[buf.top--]);
}

int min(int a, int b)
{
  return (a < b) ? (a) : (b);
}

void tarjan_visit(int v)
{
  int i;
  int c;
  int n;
  nodes[v].index = curr_index;
  nodes[v].low = curr_index;
  ++curr_index;
  stack_push(v);
  nodes[v].in_stack = 1;
  for (i = 0, c = nodes[v].total_childs; i < c; i++)
  {
    n = nodes[v].adj[i];
    if ((nodes[n].index == (-1)) || nodes[n].in_stack)
    {
      if (nodes[n].index == (-1))
      {
        tarjan_visit(n);
      }
      else
      {
        
      }

      nodes[v].low = min(nodes[v].low, nodes[n].low);
    }
    else
    {
      
    }

  }

  if (nodes[v].index == nodes[v].low)
  {
    while ((n = stack_pop()) != (-1))
    {
      nodes[n].in_stack = 0;
      if (!sccs[sccs_count])
      {
        sccs[sccs_count] = malloc((sizeof(scc)) * 2);
        sccs[sccs_count]->scc_counter = 0;
        sccs[sccs_count]->visited = -1;
      }
      else
      {
        scc *new_scc = realloc(sccs[sccs_count], (sizeof(scc)) * (sccs[sccs_count]->scc_counter + 2));
        sccs[sccs_count] = new_scc;
      }

      sccs[sccs_count][sccs[sccs_count]->scc_counter].node_id = n;
      if (sccs[sccs_count]->scc_counter == 0)
      {
        sccs[sccs_count]->max = nodes[n].grade;
      }
      else
      {
        if (nodes[n].grade > sccs[sccs_count]->max)
        {
          sccs[sccs_count]->max = nodes[n].grade;
        }
        else
        {
          
        }

      }

      nodes[n].scc_id = sccs_count;
      sccs[sccs_count]->scc_counter++;
      if (n == v)
      {
        sccs_count++;
        break;
      }
      else
      {
        
      }

    }

  }
  else
  {
    
  }

}

void find_scc_adj()
{
  int j;
  int z;
  int a;
  scc_adj = malloc((sizeof(sccadj *)) * sccs_count);
  for (j = 0; j < sccs_count; j++)
  {
    for (a = 0; a < sccs[j]->scc_counter; a++)
    {
      int c = sccs[j][a].node_id;
      for (z = 0; z < nodes[c].total_childs; z++)
        if (nodes[nodes[c].adj[z]].scc_id != j)
      {
        if (!scc_adj[j])
        {
          scc_adj[j] = malloc(sizeof(sccadj));
          scc_adj[j]->scc_adj_counter = 0;
        }
        else
        {
          sccadj *new_scc_adj = realloc(scc_adj[j], (sizeof(sccadj)) * (scc_adj[j]->scc_adj_counter + 1));
          scc_adj[j] = new_scc_adj;
        }

        scc_adj[j][scc_adj[j]->scc_adj_counter].scc_id = nodes[nodes[c].adj[z]].scc_id;
        scc_adj[j]->scc_adj_counter++;
      }
      else
      {
        
      }


    }

  }

}

void dfs_visit(int u, int pos)
{
  sccs[u]->visited = 1;
  if (scc_adj[u])
  {
    int v;
    for (v = 0; v < scc_adj[u]->scc_adj_counter; v++)
    {
      if (sccs[v]->visited == (-1))
      {
        dfs_visit(v, pos);
      }
      else
      {
        
      }

    }

  }
  else
  {
    
  }

  if ((u != pos) && (sccs[scc_adj[pos][u].scc_id]->max > sccs[pos]->max))
  {
    sccs[pos]->max = sccs[scc_adj[pos][u].scc_id]->max;
  }
  else
  {
    
  }

  sccs[u]->visited = -1;
}

void dfs_scc()
{
  int i;
  for (i = 0; i < sccs_count; i++)
  {
    if (sccs[i]->visited == (-1))
    {
      dfs_visit(i, i);
    }
    else
    {
      
    }

  }

}

void change_to_max()
{
  int i;
  for (i = 0; i < total_students; i++)
  {
    nodes[i].grade = sccs[nodes[i].scc_id]->max;
    printf("%d\n", nodes[i].grade);
  }

}

int main(void)
{
  process_input();
  init_vars();
  int i;
  for (i = 0; i < total_students; i++)
    if (nodes[i].index == (-1))
  {
    tarjan_visit(i);
  }
  else
  {
    
  }


  find_scc_adj();
  dfs_scc();
  change_to_max();
  for (i = 0; i < total_students; i++)
    free(nodes[i].adj);

  for (i = 0; i < sccs_count; i++)
  {
    free(sccs[i]);
    free(scc_adj[i]);
  }

  free(nodes);
  free(sccs);
  free(scc_adj);
  free(buf.items);
  return 0;
}

