#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void doNot()
{
}

typedef struct node
{
  int degree;
  int *adj;
  int *adjParent;
  int nEdj;
  int nEdjParent;
  bool vis;
  int maxSeq;
  int listSize;
  int listSizeParent;
  int maxLen;
  bool inQ;
} Node;
struct qNode
{
  int data;
  struct qNode *next;
};
struct qNode *first = 0;
struct qNode *last = 0;
void add(int item)
{
  struct qNode *elm = malloc(sizeof(struct qNode));
  elm->data = item;
  elm->next = 0;
  if (last == 0)
  {
    first = elm;
    last = elm;
  }
  else
  {
    last->next = elm;
    last = last->next;
  }

}

int rmv()
{
  if (first != last)
  {
    struct qNode *temp;
    temp = first;
    int temp2 = first->data;
    first = first->next;
    free(temp);
    return temp2;
  }
  else
  {
    
  }

  struct qNode *temp;
  temp = first;
  int temp2 = first->data;
  first = first->next;
  free(temp);
  first = 0;
  last = 0;
  return temp2;
}

int max(int a, int b)
{
  if (a < b)
  {
    return b;
  }
  else
  {
    
  }

  return a;
}

void dfSrcIt(Node nodeList[], int node)
{
  int s;
  int p = 0;
  int child;
  add(node);
  int stackSize = 1;
  while (stackSize > 0)
  {
    s = first->data;
    if (!nodeList[s].vis)
    {
      nodeList[s].vis = true;
      for (p = 0; p < nodeList[s].nEdj; p++)
      {
        child = nodeList[s].adj[p];
        if (!nodeList[child].vis)
        {
          if (!nodeList[child].inQ)
          {
            add(child);
            ++stackSize;
            nodeList[child].inQ = true;
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
    else
    {
      
    }

    --stackSize;
    rmv();
  }

}

int longestPath(Node nodeList[], int topSort[], int nNode)
{
  int i;
  int i2;
  int n;
  int parent;
  int maxLen;
  int x;
  maxLen = 0;
  for (i = 0; i < nNode; i++)
  {
    n = topSort[i];
    for (i2 = 0; i2 < nodeList[n].nEdjParent; i2++)
    {
      parent = nodeList[n].adjParent[i2];
      x = nodeList[parent].maxLen + 1;
      if (nodeList[n].maxLen < x)
      {
        nodeList[n].maxLen = x;
        if (maxLen < x)
        {
          maxLen = x;
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

  return maxLen;
}

int main()
{
  int nNodes;
  int nEdjes;
  int node;
  int edge;
  int i;
  int i2;
  int nTouch;
  int lSize;
  int maxSub = 0;
  if (2)
  {
    nNodes = new_sym_var(sizeof(int) * 8);
    nEdjes = new_sym_var(sizeof(int) * 8);
    doNot();
  }
  else
  {
    
  }

  int *topSort = (int *) malloc((nNodes + 1) * (sizeof(int)));
  Node *nodeList = (Node *) malloc((nNodes + 1) * (sizeof(Node)));
  for (i = 0; i <= nNodes; i++)
  {
    nodeList[i].adj = malloc((sizeof(int)) * 50);
    nodeList[i].adjParent = malloc((sizeof(int)) * 50);
    nodeList[i].listSize = 50;
    nodeList[i].listSizeParent = 50;
    nodeList[i].nEdj = 0;
    nodeList[i].nEdjParent = 0;
    nodeList[i].degree = 0;
    nodeList[i].maxSeq = 0;
    nodeList[i].maxLen = 0;
    nodeList[i].vis = false;
    nodeList[i].inQ = false;
  }

  i = 0;
  while (i < nEdjes)
  {
    if (2)
    {
      node = new_sym_var(sizeof(int) * 8);
      edge = new_sym_var(sizeof(int) * 8);
      doNot();
    }
    else
    {
      
    }

    if ((nodeList[node].listSize - 2) < nodeList[node].nEdj)
    {
      nodeList[node].adj = realloc(nodeList[node].adj, (sizeof(int)) * (nodeList[node].listSize * 1.5));
      nodeList[node].listSize = 1.5 * nodeList[node].listSize;
    }
    else
    {
      
    }

    if ((nodeList[edge].listSizeParent - 2) < nodeList[edge].nEdjParent)
    {
      nodeList[edge].adjParent = realloc(nodeList[edge].adjParent, (sizeof(int)) * (nodeList[edge].listSizeParent * 1.5));
      nodeList[edge].listSizeParent = 1.5 * (+nodeList[edge].listSizeParent);
    }
    else
    {
      
    }

    nodeList[node].adj[nodeList[node].nEdj] = edge;
    nodeList[edge].adjParent[nodeList[edge].nEdjParent] = node;
    nodeList[node].nEdj += 1;
    nodeList[edge].nEdjParent += 1;
    nodeList[edge].degree += 1;
    i++;
  }

  for (i2 = 1; i2 <= nNodes; i2++)
  {
    if (nodeList[i2].degree == 0)
    {
      add(i2);
    }
    else
    {
      
    }

  }

  i = 0;
  lSize = 0;
  i2 = 0;
  int child;
  while (lSize < nNodes)
  {
    i = rmv();
    topSort[lSize] = i;
    lSize++;
    for (i2 = 0; i2 < nodeList[i].nEdj; i2++)
    {
      child = nodeList[i].adj[i2];
      nodeList[child].degree -= 1;
      if (nodeList[child].degree == 0)
      {
        add(child);
      }
      else
      {
        
      }

    }

  }

  nTouch = 0;
  for (i = 0; i < nNodes; i++)
  {
    if (!nodeList[topSort[i]].vis)
    {
      dfSrcIt(nodeList, topSort[i]);
      nTouch++;
    }
    else
    {
      
    }

  }

  maxSub = longestPath(nodeList, topSort, nNodes);
  printf("%d %d\n", nTouch, maxSub + 1);
  free(topSort);
  for (i = 0; i <= nNodes; i++)
  {
    free(nodeList[i].adj);
    free(nodeList[i].adjParent);
  }

  free(nodeList);
  return 0;
}
