/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


int n;
int m;
int i;
int total_visited;
void propagate(int current_grade, int current_index, int grades[], int sources[], int destinations[], int visited[])
{
  visited[current_index] = 1;
  total_visited++;
  int k;
  for (k = 0; k < m; k++)
  {
    if (sources[k] == current_index)
    {
      if ((!visited[destinations[k]]) && (grades[destinations[k]] < current_grade))
      {
        grades[destinations[k]] = current_grade;
        propagate(current_grade, destinations[k], grades, sources, destinations, visited);
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

int main()
{
  n = 0;
  m = 0;
  i = 0;
  total_visited = 0;
  if (2 != 2)
  {
    return 0;
  }
  else
  {
    n = new_sym_var(sizeof(int) * 8);
    m = new_sym_var(sizeof(int) * 8);
    
  }

  int grades[n];
  int friends[2][m];
  int highest = 0;
  int highest_index = 0;
  int found;
  int visited[n];
  for (i = 0; i < n; i++)
  {
    if (1 != 1)
    {
      return 0;
    }
    else
    {
      grades[i] = new_sym_var(sizeof(int) * 8);
      
    }

    visited[i] = 0;
  }

  int hasZero = 0;
  for (i = 0; i < m; i++)
  {
    if (2 != 2)
    {
      return 0;
    }
    else
    {
      friends[1][i] = new_sym_var(sizeof(int) * 8);
      friends[0][i] = new_sym_var(sizeof(int) * 8);
      
    }

    if ((friends[0][i] == 0) || (friends[1][i] == 0))
    {
      hasZero = 1;
    }
    else
    {
      
    }

    if (!hasZero)
    {
      friends[0][i] = friends[0][i] - 1;
      friends[1][i] = friends[1][i] - 1;
    }
    else
    {
      
    }

  }

  do
  {
    found = 0;
    for (i = 0; i < n; i++)
    {
      if ((!visited[i]) && (grades[i] >= highest))
      {
        highest = grades[i];
        highest_index = i;
        found = 1;
      }
      else
      {
        
      }

    }

    if (!found)
    {
      highest = 0;
      for (i = 0; i < n; i++)
      {
        if ((!visited[i]) && (grades[i] >= highest))
        {
          highest = grades[i];
          highest_index = i;
          found = 1;
        }
        else
        {
          
        }

      }

    }
    else
    {
      
    }

    propagate(grades[highest_index], highest_index, grades, friends[0], friends[1], visited);
  }
  while (total_visited != n);
  for (i = 0; i < n; i++)
    printf("%d\n", grades[i]);

  return 0;
}

