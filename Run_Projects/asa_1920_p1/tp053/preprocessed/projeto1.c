/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


typedef struct student
{
  int grade;
  int *friends;
  int numb_of_friends;
  int state;
} student;
void dfs_visit(int student);
void dfs();
student *class;
int students;
int relations;
int control = 1;
int main()
{
  int i;
  int aux;
  int aux2;
  char first_line[5];
  for (int first_line_index = 0; first_line_index < 5; first_line_index++)
  {
    first_line[first_line_index] = new_sym_var(sizeof(char) * 8);
  }

  first_line[5 - 1] = '\0';
  students = atoi(&first_line[0]);
  relations = atoi(&first_line[2]);
  class = (student *) malloc((sizeof(student)) * (students + 1));
  for (i = 1; i <= students; i++)
  {
    class[i].grade = new_sym_var(sizeof(int) * 8);
  }

  for (i = 1; i <= students; i++)
  {
    class[i].numb_of_friends = 0;
    class[i].state = 0;
  }

  for (i = 0; i < relations; i++)
  {
    aux = new_sym_var(sizeof(int) * 8);
    aux2 = new_sym_var(sizeof(int) * 8);
    if (class[aux].numb_of_friends != 0)
    {
      class[aux].friends = (int *) realloc(class[aux].friends, (sizeof(int)) * (class[aux].numb_of_friends + 1));
      class[aux].friends[class[aux].numb_of_friends] = aux2;
      class[aux].numb_of_friends++;
    }
    else
    {
      class[aux].friends = (int *) malloc(sizeof(int));
      class[aux].friends[class[aux].numb_of_friends] = aux2;
      class[aux].numb_of_friends++;
    }

  }

  while (control == 1)
    dfs();

  for (i = 1; i <= students; i++)
    printf("%d\n", class[i].grade);

  return 0;
}

void dfs()
{
  int i;
  control = 0;
  for (i = 1; i <= students; i++)
  {
    if ((class[i].state == 0) || (class[i].state == 2))
    {
      dfs_visit(i);
    }
    else
    {
      
    }

  }

}

void dfs_visit(int student)
{
  int i;
  class[student].state = 1;
  for (i = 0; i < class[student].numb_of_friends; i++)
  {
    if (class[class[student].friends[i]].state == 0)
    {
      dfs_visit(class[student].friends[i]);
    }
    else
    {
      
    }

    if (class[class[student].friends[i]].grade > class[student].grade)
    {
      class[student].grade = class[class[student].friends[i]].grade;
      control = 1;
    }
    else
    {
      
    }

  }

  class[student].state = 2;
}

