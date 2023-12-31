#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <stdio.h>


typedef struct student
{
  unsigned int friendNumber;
  unsigned char gradePrediction;
  unsigned char visited;
  unsigned char maxed;
  struct student **friends;
} student_t;
int studentNumber;
int friendshipNumber;
int i;
int j;
int k;
int src;
int dest;
int tmp;
int max = -1;
student_t *graph;
student_t *max_student = 0;
void propaga(student_t *student);
void find_newMax();
void clear();
int main(int argc, char **argv, char **envp)
{
  if (2 != 2)
  {
  }
  else
  {
    studentNumber = new_sym_var(sizeof(int) * 8);
    friendshipNumber = new_sym_var(sizeof(int) * 8);
    
  }

  ;
  graph = (student_t *) calloc(studentNumber, sizeof(student_t));
  for (i = 0; i < studentNumber; i++)
  {
    if (1 != 1)
    {
    }
    else
    {
      graph[i].gradePrediction = new_sym_var(sizeof(unsigned char) * 8);
      
    }

    ;
    if (graph[i].gradePrediction > max)
    {
      max = graph[i].gradePrediction;
      max_student = &graph[i];
    }
    else
    {
      
    }

    graph[i].friends = (student_t **) calloc(32, sizeof(student_t *));
  }

  for (i = 0; i < friendshipNumber; i++)
  {
    if (2 != 2)
    {
    }
    else
    {
      src = new_sym_var(sizeof(int) * 8);
      dest = new_sym_var(sizeof(int) * 8);
      
    }

    ;
    tmp = graph[dest - 1].friendNumber;
    if ((tmp % 32) == 0)
    {
      graph[dest - 1].friends = realloc(graph[dest - 1].friends, (sizeof(student_t *)) * (tmp + 32));
    }
    else
    {
      
    }

    graph[dest - 1].friends[tmp] = &graph[src - 1];
    graph[dest - 1].friendNumber++;
    if (graph[dest - 1].gradePrediction > graph[src - 1].gradePrediction)
    {
      graph[src - 1].gradePrediction = graph[dest - 1].gradePrediction;
    }
    else
    {
      
    }

  }

  propaga(max_student);
  max_student->maxed = 1;
  for (k = 0; k < 2; k++)
    for (i = studentNumber - 1; i >= 0; i--)
    for (j = 0; j < graph[i].friendNumber; j++)
    if (graph[i].friends[j]->gradePrediction < graph[i].gradePrediction)
  {
    graph[i].friends[j]->gradePrediction = graph[i].gradePrediction;
  }
  else
  {
    
  }




  for (i = 0; i < studentNumber; i++)
  {
    find_newMax();
    propaga(max_student);
    clear();
  }

  for (i = 0; i < studentNumber; i++)
    printf("%d\n", graph[i].gradePrediction);

  return 0;
}

void propaga(student_t *student)
{
  int i;
  student->visited = 1;
  for (i = 0; i < student->friendNumber; i++)
  {
    if (student->friends[i]->visited == 0)
    {
      if (student->gradePrediction >= student->friends[i]->gradePrediction)
      {
        student->friends[i]->gradePrediction = student->gradePrediction;
        propaga(student->friends[i]);
      }
      else
      {
        
      }

    }
    else
    {
      
    }

  }

  return;
}

void find_newMax()
{
  for (i = 0; i < studentNumber; i++)
  {
    if (graph[i].maxed == 0)
    {
      max_student = &graph[i];
      break;
    }
    else
    {
      
    }

  }

  for (i = 0; i < studentNumber; i++)
  {
    if (graph[i].maxed == 0)
    {
      if (graph[i].gradePrediction >= max_student->gradePrediction)
      {
        max_student = &graph[i];
      }
      else
      {
        
      }

    }
    else
    {
      
    }

  }

  max_student->maxed = 1;
}

void clear()
{
  int i;
  for (i = 0; i < studentNumber; i++)
  {
    graph[i].visited = 0;
  }

}

