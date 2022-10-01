/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef enum color
{
  white,
  gray,
  black
} Color;
typedef struct node
{
  bool is_source;
  int depth;
  int max_depth;
  struct node *source;
  struct node *parent;
  struct node **link;
  int link_size;
} Node;
void addNode(Node *node_p, Node *node_c)
{
  node_p->link = (Node **) realloc(node_p->link, (sizeof(Node *)) * (++node_p->link_size));
  node_p->link[node_p->link_size - 1] = node_c;
}

int visit(Node *node)
{
  int i;
  int diff;
  int n = node->link_size;
  if (n == 0)
  {
    node->max_depth = node->depth;
    return -1;
  }
  else
  {
    
  }

  for (i = 0; i < n; i++)
  {
    if (node->link[i]->source == node->source)
    {
      if ((node->depth + 1) > node->link[i]->depth)
      {
        diff = (node->depth + 1) - node->link[i]->depth;
        if ((node->link[i]->max_depth + diff) > node->max_depth)
        {
          node->max_depth = node->link[i]->max_depth + diff;
        }
        else
        {
          
        }

      }
      else
      {
        if ((node->depth + 1) < node->link[i]->depth)
        {
          diff = node->link[i]->depth - (node->depth + 1);
          if (node->max_depth < (node->link[i]->max_depth - diff))
          {
            node->max_depth = node->link[i]->max_depth - diff;
          }
          else
          {
            
          }

        }
        else
        {
          if (node->max_depth < node->link[i]->max_depth)
          {
            node->max_depth = node->link[i]->max_depth;
          }
          else
          {
            
          }

        }

      }

    }
    else
    {
      node->link[i]->source = node->source;
      node->link[i]->depth = node->depth + 1;
      node->link[i]->max_depth = -1;
      return i;
    }

  }

  return -1;
}

int longestPath(Node *src)
{
  int depth = 1;
  Node *current = src;
  while (depth > 0)
  {
    int next = visit(current);
    if (next == (-1))
    {
      depth--;
      current = current->parent;
      continue;
    }
    else
    {
      
    }

    depth++;
    current->link[next]->parent = current;
    current = current->link[next];
  }

  return src->max_depth;
}

int main()
{
  int n;
  int l;
  int u;
  int v;
  int i;
  int max_depth = 0;
  int min_src = 0;
  if (2 == 0)
  {
    exit(1);
  }
  else
  {
    n = new_sym_var(sizeof(int) * 8);
    l = new_sym_var(sizeof(int) * 8);
    
  }

  Node *graph = (Node *) malloc((sizeof(Node)) * n);
  for (i = 0; i < n; i++)
  {
    graph[i].is_source = true;
    graph[i].depth = 1;
    graph[i].max_depth = -1;
    graph[i].source = &graph[i];
    graph[i].parent = &graph[i];
    graph[i].link = 0;
    graph[i].link_size = 0;
  }

  for (i = 0; i < l; i++)
  {
    if (2 == 0)
    {
      exit(1);
    }
    else
    {
      u = new_sym_var(sizeof(int) * 8);
      v = new_sym_var(sizeof(int) * 8);
      
    }

    addNode(&graph[u - 1], &graph[v - 1]);
    graph[v - 1].is_source = false;
  }

  for (i = 0; i < n; i++)
  {
    if (graph[i].is_source)
    {
      min_src++;
      int max = longestPath(&graph[i]);
      if (max > max_depth)
      {
        max_depth = max;
      }
      else
      {
        
      }

    }
    else
    {
      
    }

  }

  printf("%d %d\n", min_src, max_depth);
  exit(0);
}
