#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main()
{
  int differences;
  int highest_grade;
  int number_of_students;
  int number_of_relations;
  int changed_grades = 0;
  int checked_relations = 0;
  int empty_spot;
  char nums[100];
  fgets(nums, 100, stdin);
  char *token = strtok(nums, ",");
  number_of_students = atoi(token);
  number_of_relations = atoi(strtok(0, ","));
  if (number_of_students < 2)
  {
    exit(1);
  }
  else
  {
    
  }

  if (number_of_relations < 1)
  {
    exit(1);
  }
  else
  {
    
  }

  char grades[number_of_students + 1][10];
  int grades_table[number_of_students + 1][2];
  int i = 0;
  grades_table[0][0] = -1;
  grades_table[0][1] = -1;
  i = 1;
  while (i < (number_of_students + 1))
  {
    grades_table[i][0] = 0;
    i++;
  }

  i = 1;
  while (i < (number_of_students + 1))
  {
    fgets(grades[i], 10, stdin);
    grades_table[i][1] = atoi(grades[i]);
    i++;
  }

  char relation[number_of_relations][10];
  int relations_table[number_of_relations][3];
  i = 0;
  while (i < number_of_relations)
  {
    relations_table[i][0] = 0;
    i++;
  }

  i = 0;
  while (i < number_of_relations)
  {
    fgets(relation[i], 100, stdin);
    char *token2 = strtok(relation[i], " ");
    relations_table[i][1] = atoi(token2);
    relations_table[i][2] = atoi(strtok(0, " "));
    i++;
  }

  int student_numbers_to_check[number_of_students];
  i = 0;
  while (i < number_of_students)
  {
    student_numbers_to_check[i] = 0;
    i++;
  }

  int j;
  int k;
  int l;
  int m;
  int n;
  int o;
  while ((changed_grades != number_of_students) && (checked_relations != number_of_relations))
  {
    empty_spot = 0;
    highest_grade = 0;
    differences = 1;
    i = 1;
    while (i < (number_of_students + 1))
    {
      if (grades_table[i][0] == 0)
      {
        if (grades_table[i][1] > highest_grade)
        {
          highest_grade = grades_table[i][1];
          student_numbers_to_check[0] = i;
          empty_spot = 1;
          j = empty_spot;
          while (j < number_of_students)
          {
            student_numbers_to_check[j] = 0;
            j++;
          }

        }
        else
        {
          if (grades_table[i][1] == highest_grade)
          {
            student_numbers_to_check[empty_spot] = i;
            empty_spot++;
          }
          else
          {
            
          }

        }

      }
      else
      {
        
      }

      i++;
    }

    k = 0;
    while ((k < number_of_students) && (student_numbers_to_check[k] != 0))
    {
      grades_table[student_numbers_to_check[k]][0] = 1;
      changed_grades++;
      k++;
    }

    while (differences == 1)
    {
      differences = 0;
      l = 0;
      while ((l < number_of_relations) && (checked_relations != number_of_relations))
      {
        if (relations_table[l][0] == 0)
        {
          m = 0;
          while ((m < number_of_students) && (student_numbers_to_check[m] != 0))
          {
            if (relations_table[l][2] == student_numbers_to_check[m])
            {
              checked_relations++;
              relations_table[l][0] = 1;
              if (grades_table[relations_table[l][1]][0] == 1)
              {
                break;
              }
              else
              {
                grades_table[relations_table[l][1]][1] = highest_grade;
                grades_table[relations_table[l][1]][0] = 1;
                changed_grades++;
                n = 0;
                while ((student_numbers_to_check[n] != 0) && (n < number_of_students))
                {
                  if (student_numbers_to_check[n] == relations_table[l][1])
                  {
                    break;
                  }
                  else
                  {
                    
                  }

                  n++;
                }

                if (n == empty_spot)
                {
                  student_numbers_to_check[empty_spot] = relations_table[l][1];
                  empty_spot++;
                  differences = 1;
                  break;
                }
                else
                {
                  
                }

              }

            }
            else
            {
              
            }

            m++;
          }

        }
        else
        {
          
        }

        l++;
      }

    }

  }

  o = 1;
  while (o < (number_of_students + 1))
  {
    printf("%d\n", grades_table[o][1]);
    o++;
  }

  return 0;
}
