/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>


clock_t start;
clock_t end;
void problem1(int *arr, int n)
{
  unsigned long *s;
  unsigned long *c;
  unsigned long maxsize = 0;
  unsigned long maxcount = 0;
  int i;
  int j;
  s = (unsigned long *) malloc(n * (sizeof(unsigned long)));
  c = (unsigned long *) malloc(n * (sizeof(unsigned long)));
  for (i = 0; i < n; i++)
  {
    s[i] = 1;
    c[i] = 1;
  }

  for (i = 1; i < n; i++)
  {
    for (j = 0; j < i; j++)
    {
      if (arr[j] < arr[i])
      {
        if ((s[j] + 1) > s[i])
        {
          s[i] = s[j] + 1;
          c[i] = c[j];
        }
        else
        {
          if ((s[j] + 1) == s[i])
          {
            c[i] += c[j];
          }
          else
          {
            
          }

        }

      }
      else
      {
        
      }

    }

  }

  for (i = 0; i < n; i++)
  {
    if (s[i] > maxsize)
    {
      maxsize = s[i];
      maxcount = c[i];
    }
    else
    {
      if (s[i] == maxsize)
      {
        maxcount += c[i];
      }
      else
      {
        
      }

    }

  }

  free(s);
  free(c);
  printf("%lu %lu\n", maxsize, maxcount);
}

void problem2(int *arr1, int n1, int *arr2, int n2)
{
  int *vec;
  int curr;
  int result = 0;
  int i;
  int j;
  vec = (int *) malloc(n2 * (sizeof(int)));
  for (i = 0; i < n2; i++)
  {
    vec[i] = 0;
  }

  for (i = 0; i < n1; i++)
  {
    curr = 0;
    for (j = 0; j < n2; j++)
    {
      if (arr1[i] == arr2[j])
      {
        if ((curr + 1) > vec[j])
        {
          vec[j] = curr + 1;
        }
        else
        {
          
        }

      }
      else
      {
        
      }

      if (arr1[i] > arr2[j])
      {
        if (vec[j] > curr)
        {
          curr = vec[j];
        }
        else
        {
          
        }

      }
      else
      {
        
      }

    }

  }

  for (i = 0; i < n2; i++)
    if (vec[i] > result)
  {
    result = vec[i];
  }
  else
  {
    
  }


  printf("%d\n", result);
  free(vec);
}

int main(int argc, const char *argv[])
{
  int *arr1;
  int *arr2;
  int n;
  int i = 0;
  int r;
  int n1;
  char tmp = '0';
  arr1 = (int *) malloc(26845 * (sizeof(int)));
  for (i = 0; i < 26845; i++)
  {
    arr1[i] = 0;
  }

  r = 1;
  n = new_sym_var(sizeof(int) * 8);
  if (r == (-1))
  {
    exit(-1);
  }
  else
  {
    
  }

  i = 0;
  while (tmp != '\n')
  {
    r = 2;
    arr1[i] = new_sym_var(sizeof(int) * 8);
    tmp = new_sym_var(sizeof(char) * 8);
    if (r == (-1))
    {
      exit(-1);
    }
    else
    {
      
    }

    i++;
  }

  arr1 = realloc(arr1, i * (sizeof(int)));
  if (arr1 == 0)
  {
    printf("erro\n");
    exit(-1);
  }
  else
  {
    
  }

  if (n == 1)
  {
    problem1(arr1, i);
  }
  else
  {
    if (n == 2)
    {
      n1 = i;
      arr2 = (int *) malloc(26845 * (sizeof(int)));
      for (i = 0; i < 26845; i++)
      {
        arr2[i] = 0;
      }

      i = 0;
      tmp = '0';
      while (tmp != '\n')
      {
        r = 2;
        arr2[i] = new_sym_var(sizeof(int) * 8);
        tmp = new_sym_var(sizeof(char) * 8);
        i++;
      }

      arr2 = realloc(arr2, i * (sizeof(int)));
      if (arr2 == 0)
      {
        printf("erro\n");
        exit(-1);
      }
      else
      {
        
      }

      problem2(arr1, n1, arr2, i);
      free(arr2);
    }
    else
    {
      
    }

  }

  free(arr1);
  return 0;
}

