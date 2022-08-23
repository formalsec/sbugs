/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <stdio.h>
#include<limits.h>


typedef struct List
{
  struct Link *tail;
} *list;
typedef struct Link
{
  struct Student *student;
  struct Link *prev;
} *link;
typedef struct Graph
{
  struct Student **students;
  int n_students;
  int visited;
  struct List *tarj_list;
} *graph;
typedef struct Student
{
  int id;
  int d;
  int low;
  int in_list;
  int color;
  int grade_est;
  int *new_estim;
  struct FriendLink *rel;
} *student;
typedef struct FriendLink
{
  struct Student *friend;
  struct FriendLink *next;
} *friendLink;
graph newGraph(int n_students);
list newList();
link newLink(student s);
void push(list lst, student s);
student pop(list lst);
int min(int n, int m);
student newStudent(int id, int grade);
void newFriend(student stud, student friend);
void dfs(graph studentGraph);
void dfsVisit(student stud);
void tarjan(graph studentGraph);
void tarjanVisit(graph sGraph, student s);
graph newGraph(int n_students)
{
  graph new = (graph) malloc(sizeof(struct Graph));
  new->students = (student *) malloc((sizeof(student)) * n_students);
  new->n_students = n_students;
  new->visited = 0;
  new->tarj_list = newList();
  return new;
}

list newList()
{
  list new = (list) malloc(sizeof(struct List));
  new->tail = 0;
  return new;
}

link newLink(student s)
{
  link new = (link) malloc(sizeof(struct Link));
  new->student = s;
  new->prev = 0;
  return new;
}

void push(list lst, student s)
{
  link lnk = newLink(s);
  lnk->prev = lst->tail;
  lst->tail = lnk;
}

student pop(list lst)
{
  link aux = lst->tail;
  student aux_s = aux->student;
  lst->tail = aux->prev;
  free(aux);
  return aux_s;
}

int min(int n, int m)
{
  if (n < m)
  {
    return n;
  }
  else
  {
    return m;
  }

}

student newStudent(int id, int grade)
{
  student new = (student) malloc(sizeof(struct Student));
  new->color = 0;
  new->in_list = 0;
  new->d = 32767;
  new->low = 32767;
  new->id = id;
  new->grade_est = grade;
  new->rel = 0;
  new->new_estim = 0;
  return new;
}

void newFriend(student stud, student friend)
{
  friendLink new_rel = (friendLink) malloc(sizeof(struct FriendLink));
  new_rel->friend = friend;
  new_rel->next = stud->rel;
  stud->rel = new_rel;
}

void dfs(graph studentGraph)
{
  int i;
  for (i = 0; i < studentGraph->n_students; i++)
  {
    if (studentGraph->students[i]->color == 0)
    {
      dfsVisit(studentGraph->students[i]);
    }
    else
    {
      
    }

  }

}

void dfsVisit(student stud)
{
  friendLink relationship = stud->rel;
  stud->color = 1;
  while (relationship != 0)
  {
    if (relationship->friend->color == 0)
    {
      dfsVisit(relationship->friend);
    }
    else
    {
      
    }

    if ((*stud->new_estim) < (*relationship->friend->new_estim))
    {
      *stud->new_estim = *relationship->friend->new_estim;
    }
    else
    {
      
    }

    relationship = relationship->next;
  }

}

void tarjan(graph studentGraph)
{
  int i;
  for (i = 0; i < studentGraph->n_students; i++)
  {
    if (studentGraph->students[i]->d == 32767)
    {
      tarjanVisit(studentGraph, studentGraph->students[i]);
    }
    else
    {
      
    }

  }

}

void tarjanVisit(graph sGraph, student s)
{
  student stack_s;
  int *shared_estim_ptr;
  friendLink adj = s->rel;
  sGraph->visited++;
  s->d = sGraph->visited;
  s->low = sGraph->visited;
  s->in_list = 1;
  push(sGraph->tarj_list, s);
  while (adj != 0)
  {
    if (adj->friend->d == 32767)
    {
      tarjanVisit(sGraph, adj->friend);
      s->low = min(s->low, adj->friend->low);
    }
    else
    {
      if (adj->friend->in_list == 1)
      {
        s->low = min(s->low, adj->friend->d);
      }
      else
      {
        
      }

    }

    adj = adj->next;
  }

  if (s->low == s->d)
  {
    shared_estim_ptr = (int *) malloc(sizeof(int));
    *shared_estim_ptr = INT_MIN;
    do
    {
      stack_s = pop(sGraph->tarj_list);
      if ((*shared_estim_ptr) < stack_s->grade_est)
      {
        *shared_estim_ptr = stack_s->grade_est;
      }
      else
      {
        
      }

      stack_s->new_estim = shared_estim_ptr;
      stack_s->in_list = 0;
    }
    while (s->id != stack_s->id);
  }
  else
  {
    
  }

}

int main(int argc, char *argv[])
{
  int n_rel;
  int n_students;
  int grade;
  int stud_id;
  int friend_id;
  int i;
  friendLink rel;
  friendLink aux_rel;
  graph studentGraph;
  n_students = new_sym_var(sizeof(int) * 8);
  n_rel = new_sym_var(sizeof(int) * 8);
  studentGraph = newGraph(n_students);
  for (i = 0; i < n_students; i++)
  {
    grade = new_sym_var(sizeof(int) * 8);
    studentGraph->students[i] = newStudent(i, grade);
  }

  for (i = 0; i < n_rel; i++)
  {
    stud_id = new_sym_var(sizeof(int) * 8);
    friend_id = new_sym_var(sizeof(int) * 8);
    newFriend(studentGraph->students[stud_id - 1], studentGraph->students[friend_id - 1]);
  }

  tarjan(studentGraph);
  dfs(studentGraph);
  for (i = 0; i < n_students; i++)
  {
    printf("%d\n", *studentGraph->students[i]->new_estim);
  }

  for (i = 0; i < n_students; i++)
  {
    rel = studentGraph->students[i]->rel;
    while (rel != 0)
    {
      aux_rel = rel->next;
      free(rel);
      rel = aux_rel;
    }

    if (studentGraph->students[i]->new_estim != 0)
    {
      free(studentGraph->students[i]->new_estim);
    }
    else
    {
      
    }

    free(studentGraph->students[i]);
  }

  free(studentGraph->students);
  free(studentGraph->tarj_list);
  free(studentGraph);
  return 0;
}

