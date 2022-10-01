/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int inputSize(char str[])
{
  int i = 0;
  int j = 1;
  while (str[i] != '\n')
  {
    while ((str[i] != ' ') && (str[i] != '\n'))
    {
      i++;
    }

    if (str[i] != '\n')
    {
      i++;
    }
    else
    {
      
    }

    j++;
  }

  return j;
}

void lis(int X[], int size)
{
  int lis[size];
  int cnt[size];
  int i = 0;
  int j = 0;
  int max = 1;
  int contador = 1;
  for (i = 0; i < size; i++)
  {
    lis[i] = 1;
    cnt[i] = 1;
  }

  if (size > 2)
  {
    for (i = 1; i < (size - 1); i++)
    {
      for (j = 0; j < i; j++)
      {
        if (X[i] > X[j])
        {
          if (lis[i] < (lis[j] + 1))
          {
            lis[i] = lis[j] + 1;
            cnt[i] = cnt[j];
            if (lis[i] > max)
            {
              max = lis[i];
              contador = 0;
            }
            else
            {
              
            }

          }
          else
          {
            if (lis[i] == (lis[j] + 1))
            {
              cnt[i] += cnt[j];
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

      if (lis[i] == max)
      {
        contador += cnt[i];
      }
      else
      {
        
      }

    }

  }
  else
  {
    contador = 1;
  }

  printf("%d %d\n", max, contador);
}

void lcis(int X[], int Y[], int n, int m)
{
  int i = 0;
  int j = 0;
  int max = 0;
  int cur_len = 0;
  if ((n != 0) && (m != 0))
  {
    int len_tab[m];
    for (i = 0; i < m; i++)
    {
      len_tab[i] = 0;
    }

    for (i = 0; i < (n - 1); i++)
    {
      for (j = 0; j < (m - 1); j++)
      {
        if ((X[i] == Y[j]) && (len_tab[j] < (cur_len + 1)))
        {
          len_tab[j] = cur_len + 1;
          if (len_tab[j] > max)
          {
            max = len_tab[j];
          }
          else
          {
            
          }

        }
        else
        {
          
        }

        if ((X[i] > Y[j]) && (cur_len < len_tab[j]))
        {
          cur_len = len_tab[j];
        }
        else
        {
          
        }

      }

      cur_len = 0;
    }

  }
  else
  {
    
  }

  printf("%d\n", max);
}

int main()
{
  char prob[3] = {'c'};
  char str[421000] = {'c'};
  int *X = 0;
  int *Y = 0;
  int val = 0;
  int i = 0;
  int j = 0;
  int v = 0;
  int m = 0;
  int sizeA = 0;
  int sizeB = 0;
  if (fgets(prob, 3, stdin) == 0)
  {
    return -1;
  }
  else
  {
    
  }

  if (strcmp(prob, "1\n") == 0)
  {
    if (fgets(str, 421000, stdin) == 0)
    {
      return -1;
    }
    else
    {
      
    }

    sizeA = inputSize(str);
    X = malloc((sizeof(int)) * sizeA);
    i = 0;
    while (str[i] != '\n')
    {
      m = i;
      while ((str[i] != ' ') && (str[i] != '\n'))
      {
        if (str[i] != '-')
        {
          val = (val * 10) + (str[i] - 48);
        }
        else
        {
          
        }

        i++;
      }

      if (str[i] != '\n')
      {
        i++;
      }
      else
      {
        
      }

      if (str[m] == '-')
      {
        val = -val;
      }
      else
      {
        
      }

      X[j] = val;
      val = 0;
      j++;
    }

    lis(X, sizeA);
  }
  else
  {
    if (strcmp(prob, "2\n") == 0)
    {
      if (fgets(str, 421000, stdin) == 0)
      {
        return -1;
      }
      else
      {
        
      }

      sizeA = inputSize(str);
      X = malloc((sizeof(int)) * sizeA);
      while (str[i] != '\n')
      {
        m = i;
        while ((str[i] != ' ') && (str[i] != '\n'))
        {
          if (str[i] != '-')
          {
            val = (val * 10) + (str[i] - 48);
          }
          else
          {
            
          }

          i++;
        }

        if (str[i] != '\n')
        {
          i++;
        }
        else
        {
          
        }

        if (str[m] == '-')
        {
          val = -val;
        }
        else
        {
          
        }

        X[j] = val;
        val = 0;
        j++;
      }

      j = 0;
      i = 0;
      strcpy(str, "");
      if (fgets(str, 421000, stdin) == 0)
      {
        return -1;
      }
      else
      {
        
      }

      sizeB = inputSize(str);
      Y = malloc((sizeof(int)) * sizeB);
      while (str[i] != '\n')
      {
        m = i;
        while ((str[i] != ' ') && (str[i] != '\n'))
        {
          if (str[i] != '-')
          {
            val = (val * 10) + (str[i] - 48);
          }
          else
          {
            
          }

          i++;
        }

        if (str[i] != '\n')
        {
          i++;
        }
        else
        {
          
        }

        if (str[m] == '-')
        {
          val = -val;
        }
        else
        {
          
        }

        for (v = 0; v < (sizeA - 1); v++)
        {
          if (val == X[v])
          {
            Y[j] = val;
            j++;
            break;
          }
          else
          {
            
          }

        }

        val = 0;
      }

      lcis(X, Y, sizeA, j + 1);
    }
    else
    {
      
    }

  }

  free(X);
  free(Y);
  return 0;
}
