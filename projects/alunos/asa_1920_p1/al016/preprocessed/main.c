#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct vertex
{
  int num;
  int predicted_grade;
  int d;
  int low;
  int is_in_stack;
} *vertex;
typedef struct node
{
  struct node *next;
  vertex vertex;
} *node;
int min(int i, int j);
int max(int i, int j);
vertex new_vertex(int num);
node new_node(vertex v);
void insert_ad_list_table(vertex u, vertex v);
void free_ad_list(node ad_list_head);
void push(vertex v);
vertex pop();
void Tarjan_visit(vertex v);
void SCC_Tarjan();
void inicialise_ad_list_table();
void initialise_vertexes();
void process_input();
void print_predicted_grades();
void free_vertexes();
void free_ad_list_table();
void free_sccs_ad_list_table();
int main();
int num_vertexes;
vertex *vertexes;
node *ad_list_table;
node stack_head;
int time;
int min(int i, int j)
{
  if (i < j)
  {
    return i;
  }
  else
  {
    
  }

  return j;
}

int max(int i, int j)
{
  if (i > j)
  {
    return i;
  }
  else
  {
    
  }

  return j;
}

vertex new_vertex(int num)
{
  vertex v = (vertex) malloc(sizeof(struct vertex));
  v->num = num;
  v->predicted_grade = -1;
  v->d = -1;
  v->low = -1;
  v->is_in_stack = 0;
  return v;
}

node new_node(vertex v)
{
  node new_node = (node) malloc(sizeof(struct node));
  new_node->vertex = v;
  new_node->next = 0;
  return new_node;
}

void insert_ad_list_table(vertex u, vertex v)
{
  node cur_node;
  node prev_node;
  if (ad_list_table[u->num - 1] == 0)
  {
    ad_list_table[u->num - 1] = new_node(v);
  }
  else
  {
    cur_node = ad_list_table[u->num - 1];
    while (cur_node != 0)
    {
      prev_node = cur_node;
      cur_node = prev_node->next;
    }

    prev_node->next = new_node(v);
  }

}

void free_ad_list(node ad_list_head)
{
  node cur_node;
  node next_node;
  cur_node = ad_list_head;
  while (cur_node != 0)
  {
    next_node = cur_node->next;
    free(cur_node);
    cur_node = next_node;
  }

}

void push(vertex v)
{
  node new_node = (node) malloc(sizeof(struct node));
  new_node->vertex = v;
  new_node->next = stack_head;
  stack_head = new_node;
}

vertex pop()
{
  node top_node = stack_head;
  vertex v = top_node->vertex;
  stack_head = stack_head->next;
  free(top_node);
  return v;
}

void Tarjan_visit(vertex v)
{
  node a = ad_list_table[v->num - 1];
  vertex popped_vertex = 0;
  v->d = time;
  v->low = time;
  time++;
  push(v);
  v->is_in_stack = 1;
  while (a != 0)
  {
    if (a->vertex->d == (-1))
    {
      Tarjan_visit(a->vertex);
      v->low = min(v->low, a->vertex->low);
    }
    else
    {
      if (a->vertex->is_in_stack)
      {
        v->low = min(v->low, a->vertex->low);
      }
      else
      {
        
      }

    }

    v->predicted_grade = max(v->predicted_grade, a->vertex->predicted_grade);
    a = a->next;
  }

  if (v->d == v->low)
  {
    popped_vertex = pop();
    popped_vertex->is_in_stack = 0;
    while (popped_vertex->num != v->num)
    {
      popped_vertex->predicted_grade = v->predicted_grade;
      popped_vertex = pop();
      popped_vertex->is_in_stack = 0;
    }

  }
  else
  {
    
  }

}

void SCC_Tarjan()
{
  int i;
  time = 0;
  for (i = 0; i < num_vertexes; i++)
  {
    vertexes[i]->d = -1;
    vertexes[i]->low = -1;
    vertexes[i]->is_in_stack = 0;
  }

  for (i = 0; i < num_vertexes; i++)
  {
    if (vertexes[i]->d == (-1))
    {
      Tarjan_visit(vertexes[i]);
    }
    else
    {
      
    }

  }

}

void inicialise_ad_list_table()
{
  int i;
  ad_list_table = (node *) malloc((sizeof(node)) * num_vertexes);
  for (i = 0; i < num_vertexes; i++)
  {
    ad_list_table[i] = 0;
  }

}

void initialise_vertexes()
{
  int i;
  vertexes = (vertex *) malloc((sizeof(vertex)) * num_vertexes);
  for (i = 0; i < num_vertexes; i++)
  {
    vertexes[i] = new_vertex(i + 1);
  }

}

void process_input()
{
  int num_students;
  int num_friendships;
  int predicted_grade;
  int student;
  int friend;
  int i;
  num_students = new_sym_var(sizeof(int) * 8);
  num_friendships = new_sym_var(sizeof(int) * 8);
  if (num_students < 2)
  {
    perror("Number of students must be greater than 2\n");
    exit(-1);
  }
  else
  {
    
  }

  if (num_friendships < 1)
  {
    perror("Number of friendships must be greater than 1\n");
    exit(-1);
  }
  else
  {
    
  }

  num_vertexes = num_students;
  initialise_vertexes();
  inicialise_ad_list_table();
  for (i = 0; i < num_vertexes; i++)
  {
    predicted_grade = new_sym_var(sizeof(int) * 8);
    vertexes[i]->predicted_grade = predicted_grade;
  }

  for (i = 0; i < num_friendships; i++)
  {
    student = new_sym_var(sizeof(int) * 8);
    friend = new_sym_var(sizeof(int) * 8);
    insert_ad_list_table(vertexes[student - 1], vertexes[friend - 1]);
  }

}

void print_predicted_grades()
{
  int i;
  for (i = 0; i < num_vertexes; i++)
  {
    printf("%d\n", vertexes[i]->predicted_grade);
  }

}

void free_vertexes()
{
  int i;
  for (i = 0; i < num_vertexes; i++)
  {
    free(vertexes[i]);
  }

  free(vertexes);
}

void free_ad_list_table()
{
  int i;
  for (i = 0; i < num_vertexes; i++)
  {
    free_ad_list(ad_list_table[i]);
  }

  free(ad_list_table);
}

int main()
{
  process_input();
  SCC_Tarjan();
  print_predicted_grades();
  free_vertexes();
  free_ad_list_table();
  return 0;
}

