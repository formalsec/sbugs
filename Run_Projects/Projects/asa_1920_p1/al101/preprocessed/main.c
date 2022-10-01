/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct 
{
  int id;
  int grade;
  int graded;
  int grading;
} student;
struct node;
typedef struct node *link;
typedef struct node
{
  student *student;
  struct node *next;
} node;
typedef struct 
{
  node *head;
  node *tail;
} list;
list **adj;
void insert(int src, int dest)
{
  link new = (link) malloc(sizeof(node));
  new->next = 0;
  new->student = adj[dest]->head->student;
  list *l = adj[src];
  l->tail->next = new;
  l->tail = new;
}

void split(int *n, int *m, char arg)
{
  char mStr[100];
  char nStr[100];
  char c = getchar();
  int j = 0;
  while (c != arg)
  {
    if (c != ' ')
    {
      nStr[j] = c;
    }
    else
    {
      
    }

    j++;
    c = getchar();
  }

  nStr[j] = '\0';
  c = getchar();
  j = 0;
  while (((c != '\n') && (c != '\0')) && (c != EOF))
  {
    if (c != ' ')
    {
      mStr[j] = c;
    }
    else
    {
      
    }

    j++;
    c = getchar();
  }

  mStr[j] = '\0';
  *n = atoi(nStr);
  *m = atoi(mStr);
}

void processStudents(int n)
{
  int i;
  for (i = 0; i < n; i++)
  {
    student *new = (student *) malloc(sizeof(student));
    new->grade = new_sym_var(sizeof(int) * 8);
    new->graded = 0;
    new->id = i;
    new->grading = 0;
    list *newList = (list *) malloc(sizeof(list));
    link newNode = (link) malloc(sizeof(node));
    newNode->student = new;
    newNode->next = 0;
    adj[i] = newList;
    adj[i]->head = newNode;
    adj[i]->tail = newNode;
  }

}

void processRelationships(int m)
{
  int i;
  int u;
  int v;
  for (i = 0; i < m; i++)
  {
    u = new_sym_var(sizeof(int) * 8);
    v = new_sym_var(sizeof(int) * 8);
    insert(u - 1, v - 1);
  }

}

void grade(int id)
{
  list *l = adj[id];
  l->head->student->grading = !0;
  link current = l->head->next;
  int finished = !0;
  while (current != 0)
  {
    if (!current->student->grading)
    {
      if (!adj[current->student->id]->head->student->graded)
      {
        grade(current->student->id);
        if (!current->student->graded)
        {
          finished = 0;
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
      finished = 0;
    }

    if (current->student->grade > l->head->student->grade)
    {
      l->head->student->grade = current->student->grade;
    }
    else
    {
      
    }

    current = current->next;
  }

  l->head->student->graded = finished;
  l->head->student->grading = 0;
}

void compute(int n)
{
  int i = 0;
  for (i = 0; i < n; i++)
  {
    if (!adj[i]->head->student->graded)
    {
      grade(i);
      adj[i]->head->student->graded = !0;
    }
    else
    {
      
    }

  }

}

int main()
{
  int n;
  int m;
  int i;
  split(&n, &m, ',');
  if ((n < 2) || (m < 1))
  {
    printf("Invalid input.");
  }
  else
  {
    
  }

  adj = (list **) malloc((sizeof(list *)) * n);
  processStudents(n);
  processRelationships(m);
  compute(n);
  for (i = 0; i < n; i++)
  {
    printf("%d\n", adj[i]->head->student->grade);
  }

  for (i = 0; i < n; i++)
  {
    list *l = adj[i];
    link head = l->head;
    link next;
    link current = head->next;
    ;
    free(head->student);
    free(head);
    if (current != 0)
    {
      while (current->next != 0)
      {
        next = current->next;
        free(current);
        current = next;
      }

      free(current);
    }
    else
    {
      
    }

    free(l);
  }

  free(adj);
  return 0;
}
