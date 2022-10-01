/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum state
{
  CLEAR,
  VISITED,
  CLOSED
} State;
typedef struct student
{
  int grade;
  State state;
  int friend_amount;
  struct student **is_friends;
} Student;
Student *new_student(int grade, int total_students)
{
  Student *student = malloc(sizeof(Student));
  student->grade = grade;
  student->state = CLEAR;
  student->friend_amount = 0;
  student->is_friends = 0;
  return student;
}

void visit_friend(Student *friend)
{
  if (friend->friend_amount == 0)
  {
    return;
  }
  else
  {
    
  }

  friend->state = VISITED;
  int i;
  for (i = 0; i < friend->friend_amount; i++)
  {
    if (friend->grade > friend->is_friends[i]->grade)
    {
      friend->is_friends[i]->grade = friend->grade;
      visit_friend(friend->is_friends[i]);
    }
    else
    {
      
    }

  }

  friend->state = CLOSED;
}

int main()
{
  char *line = malloc((sizeof(char)) * 100);
  fgets(line, 100, stdin);
  int n = 0;
  int m = 0;
  n = atoi(strtok(line, ","));
  m = atoi(strtok(0, ","));
  if (n < 2)
  {
    n = 2;
  }
  else
  {
    
  }

  if (m < 1)
  {
    m = 1;
  }
  else
  {
    
  }

  int student_counter = 0;
  Student **students = malloc(n * (sizeof(Student)));
  while (student_counter < n)
  {
    fgets(line, 100, stdin);
    int grade = atoi(line);
    students[student_counter] = new_student(grade, n);
    student_counter++;
  }

  int a = 0;
  int b = 0;
  int i;
  for (i = 0; i < m; i++)
  {
    fgets(line, 100, stdin);
    a = new_sym_var(sizeof(int) * 8);
    b = new_sym_var(sizeof(int) * 8);
    students[b - 1]->friend_amount++;
    students[b - 1]->is_friends = realloc(students[b - 1]->is_friends, students[b - 1]->friend_amount * (sizeof(Student)));
    students[b - 1]->is_friends[students[b - 1]->friend_amount - 1] = students[a - 1];
  }

  free(line);
  for (i = 0; i < n; i++)
    if (students[i]->state == CLEAR)
  {
    visit_friend(students[i]);
  }
  else
  {
    
  }


  for (i = 0; i < n; i++)
  {
    printf("%d\n", students[i]->grade);
    free(students[i]->is_friends);
    free(students[i]);
  }

  free(students);
  return 0;
}
