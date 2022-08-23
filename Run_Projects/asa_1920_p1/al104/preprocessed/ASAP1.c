/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


typedef struct node
{
  int grade;
  int color;
} Node;
typedef struct adjListNode
{
  int index;
  struct adjListNode *next;
} adjListNode;
typedef struct gradeListNode
{
  int index;
  struct gradeListNode *next;
} gradeListNode;
Node *graph;
adjListNode **adjList;
gradeListNode *gradeList[21] = {0};
int nCount;
int eCount;
int min = 20;
int max = 0;
gradeListNode *rightNode;
void initialize_nodes()
{
  int i;
  int tempGrade;
  for (i = 0; i < nCount; i++)
  {
    tempGrade = new_sym_var(sizeof(int) * 8);
    graph[i].grade = tempGrade;
    graph[i].color = 0;
    adjList[i] = 0;
    gradeListNode *temp = malloc(sizeof(gradeListNode));
    temp->index = i;
    if (gradeList[tempGrade] == 0)
    {
      temp->next = 0;
    }
    else
    {
      temp->next = gradeList[tempGrade];
    }

    gradeList[tempGrade] = temp;
    if (tempGrade > max)
    {
      max = tempGrade;
    }
    else
    {
      
    }

    if (tempGrade < min)
    {
      min = tempGrade;
    }
    else
    {
      
    }

  }

}

void connect(int node1, int node2)
{
  adjListNode *temp = malloc(sizeof(adjListNode));
  temp->index = node2;
  if (adjList[node1] == 0)
  {
    temp->next = 0;
  }
  else
  {
    temp->next = adjList[node1];
  }

  adjList[node1] = temp;
}

void initialize_connections()
{
  int i;
  int node1;
  int node2;
  for (i = 0; i < eCount; i++)
  {
    node2 = new_sym_var(sizeof(int) * 8);
    node1 = new_sym_var(sizeof(int) * 8);
    connect(node1 - 1, node2 - 1);
  }

}

void propagate(int node, int grade)
{
  adjListNode *temp = adjList[node];
  graph[node].color = 2;
  graph[node].grade = grade;
  for (; temp != 0; temp = temp->next)
  {
    if (graph[temp->index].color == 0)
    {
      propagate(temp->index, grade);
    }
    else
    {
      
    }

  }

}

void algorithm()
{
  int i;
  gradeListNode *temp;
  for (i = max; i > (min - 1); i--)
  {
    for (temp = rightNode; temp != 0; temp = temp->next)
    {
      if (graph[temp->index].color == 0)
      {
        propagate(temp->index, graph[temp->index].grade);
      }
      else
      {
        
      }

    }

    rightNode = gradeList[i - 1];
  }

}

void output()
{
  int i = 0;
  for (; i < nCount; i++)
  {
    printf("%d\n", graph[i].grade);
  }

}

int main()
{
  nCount = new_sym_var(sizeof(int) * 8);
  eCount = new_sym_var(sizeof(int) * 8);
  graph = malloc((sizeof(Node)) * nCount);
  adjList = malloc((sizeof(adjListNode *)) * nCount);
  initialize_nodes();
  initialize_connections();
  rightNode = gradeList[max];
  algorithm();
  output();
  free(adjList);
  free(graph);
  return 0;
}
