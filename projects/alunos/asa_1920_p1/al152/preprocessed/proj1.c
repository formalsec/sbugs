#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int nStudents;
int nFriendships;
enum color
{
  White,
  Gray,
  Black
};
typedef struct Friend
{
  struct Friend *next;
  int studentIndex;
} Friend;
typedef struct Student
{
  Friend *friend;
  enum color color;
  int grade;
} Student;
typedef struct Grade
{
  struct Grade *next;
  int studentIndex;
} Grade;
typedef struct StudentGrade
{
  Grade *similarGrade;
} StudentGrade;
void add_grade(StudentGrade *studentGrade, int grade, int studentIndex)
{
  Grade *value = malloc(sizeof(Grade));
  value->studentIndex = studentIndex;
  value->next = studentGrade[grade].similarGrade;
  studentGrade[grade].similarGrade = value;
}

void add_edge(Student *students, int student, int friend)
{
  Friend *connection = malloc(sizeof(Friend));
  connection->studentIndex = friend;
  connection->next = students[student].friend;
  students[student].friend = connection;
}

void dfs_visit(Student *students, int student, int grade)
{
  students[student].color = Gray;
  students[student].grade = grade;
  Friend *temp = students[student].friend;
  while (temp != 0)
  {
    if (students[temp->studentIndex].color == White)
    {
      dfs_visit(students, temp->studentIndex, grade);
    }
    else
    {
      
    }

    temp = temp->next;
  }

  students[student].color = Black;
}

void dfs(Student *students, StudentGrade *studentGrade)
{
  int i;
  Grade *temp;
  for (i = 20; i >= 0; i--)
  {
    temp = studentGrade[i].similarGrade;
    while (temp != 0)
    {
      if (students[temp->studentIndex].color == White)
      {
        dfs_visit(students, temp->studentIndex, students[temp->studentIndex].grade);
      }
      else
      {
        
      }

      temp = temp->next;
    }

  }

}

int main()
{
  int i;
  int link1;
  int link2;
  nStudents = new_sym_var(sizeof(int) * 8);
  nFriendships = new_sym_var(sizeof(int) * 8);
  Student *students = malloc((sizeof(Student)) * nStudents);
  StudentGrade *studentGrade = malloc((sizeof(StudentGrade)) * 21);
  for (i = 0; i < 21; i++)
  {
    studentGrade[i].similarGrade = 0;
  }

  for (i = 0; i < nStudents; i++)
  {
    students[i].grade = new_sym_var(sizeof(int) * 8);
    add_grade(studentGrade, students[i].grade, i);
    students[i].friend = 0;
    students[i].color = White;
  }

  for (i = 0; i < nFriendships; i++)
  {
    link1 = new_sym_var(sizeof(int) * 8);
    link2 = new_sym_var(sizeof(int) * 8);
    add_edge(students, link2 - 1, link1 - 1);
  }

  dfs(students, studentGrade);
  for (i = 0; i < nStudents; i++)
  {
    printf("%d\n", students[i].grade);
  }

  free(students);
  free(studentGrade);
  return 0;
}

