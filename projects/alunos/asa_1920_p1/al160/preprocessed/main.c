#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct str_node
{
  struct str_node *next;
  int grade;
  int num;
  int flag;
} student;
typedef struct 
{
  student *head;
} list;
typedef struct 
{
  int in;
  int out;
  int *list;
} queue;
list *mk_list();
list **mk_class(int size);
void destroy_list(list *l);
void destroy_class(list **class, int size);
void add_friendship(list **l, int in, int out);
student *new_student(int num, int grade, int flag);
int student_compare(const void *s1, const void *s2);
void map_positions(list **l, int *map, int n);
queue *mk_queue(int n);
void enqueue(queue *q, int id);
int dequeue(queue *q);
int bfs(list **l, int *map, int n, int start);
void print_estimate(int *estimate, int n);
int main()
{
  list **class;
  int *estimate;
  int *map;
  int num_students;
  int num_friendships;
  int grade;
  int in;
  int out;
  int i;
  num_students = new_sym_var(sizeof(int) * 8);
  num_friendships = new_sym_var(sizeof(int) * 8);
  class = mk_class(num_students);
  map = malloc((sizeof(int)) * num_students);
  estimate = malloc((sizeof(int)) * num_students);
  for (i = 0; i < num_students; i++)
  {
    grade = new_sym_var(sizeof(int) * 8);
    class[i]->head = new_student(i + 1, grade, 0);
  }

  for (i = 0; i < num_friendships; i++)
  {
    in = new_sym_var(sizeof(int) * 8);
    out = new_sym_var(sizeof(int) * 8);
    add_friendship(class, out - 1, in - 1);
  }

  qsort(class, num_students, sizeof(list *), student_compare);
  map_positions(class, map, num_students);
  for (i = 0; i < num_students; i++)
  {
    if (class[i]->head->flag == 0)
    {
      bfs(class, map, num_students, i);
    }
    else
    {
      
    }

    estimate[class[i]->head->num - 1] = class[i]->head->grade;
  }

  print_estimate(estimate, num_students);
  destroy_class(class, num_students);
  free(map);
  free(estimate);
  return 0;
}

list **mk_class(int size)
{
  int i;
  list **c = malloc((sizeof(list *)) * size);
  for (i = 0; i < size; i++)
    c[i] = mk_list();

  return c;
}

list *mk_list()
{
  list *l = malloc(sizeof(list));
  l->head = 0;
  return l;
}

void destroy_class(list **class, int size)
{
  int i;
  for (i = 0; i < size; i++)
  {
    destroy_list(class[i]);
    free(class[i]);
  }

  free(class);
}

void destroy_list(list *l)
{
  student *iter;
  while (l->head)
  {
    iter = l->head;
    l->head = l->head->next;
    free(iter);
  }

}

void add_friendship(list **l, int in, int out)
{
  student *iter = l[in]->head;
  student *new = malloc(sizeof(student));
  new->num = l[out]->head->num;
  new->grade = l[out]->head->grade;
  new->flag = 0;
  while (iter->next)
    iter = iter->next;

  iter->next = new;
  new->next = 0;
}

student *new_student(int num, int grade, int flag)
{
  student *new = malloc(sizeof(student));
  new->num = num;
  new->grade = grade;
  new->flag = flag;
  new->next = 0;
  return new;
}

int student_compare(const void *a1, const void *a2)
{
  return (*((list **) a2))->head->grade - (*((list **) a1))->head->grade;
}

void map_positions(list **l, int *map, int n)
{
  int i;
  for (i = 0; i < n; i++)
  {
    map[l[i]->head->num - 1] = i;
  }

}

queue *mk_queue(int n)
{
  queue *new_queue = malloc(sizeof(queue));
  new_queue->list = malloc((sizeof(int)) * n);
  new_queue->in = -1;
  new_queue->out = -1;
  return new_queue;
}

void enqueue(queue *q, int id)
{
  if (q->in == (-1))
  {
    q->in = 0;
  }
  else
  {
    
  }

  q->out++;
  q->list[q->out] = id;
}

int dequeue(queue *q)
{
  int ret;
  if (q->in == (-1))
  {
    return -1;
  }
  else
  {
    
  }

  ret = q->list[q->in];
  q->in++;
  if (q->in > q->out)
  {
    q->in = (q->out = -1);
  }
  else
  {
    
  }

  return ret;
}

int bfs(list **l, int *map, int n, int start)
{
  int current;
  int highest;
  student *next;
  queue *q = mk_queue(n);
  l[start]->head->flag = 1;
  highest = l[start]->head->grade;
  enqueue(q, start);
  while (q->in >= 0)
  {
    current = dequeue(q);
    next = l[current]->head->next;
    while (next != 0)
    {
      if (l[map[next->num - 1]]->head->flag == 0)
      {
        next->flag = 1;
        l[map[next->num - 1]]->head->flag = 1;
        l[map[next->num - 1]]->head->grade = highest;
        next->grade = highest;
        enqueue(q, map[next->num - 1]);
      }
      else
      {
        
      }

      next = next->next;
    }

  }

  free(q->list);
  free(q);
  return highest;
}

void print_estimate(int *estimate, int n)
{
  int i;
  for (i = 0; i < n; i++)
  {
    printf("%d\n", estimate[i]);
  }

}
