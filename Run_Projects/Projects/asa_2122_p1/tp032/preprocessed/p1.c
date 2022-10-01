/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int ceilIndex(int arr[], int l, int r, int key)
{
  int curr = 0;
  while ((r - l) > 1)
  {
    curr = l + ((r - l) / 2);
    if (arr[curr] >= key)
    {
      r = curr;
    }
    else
    {
      l = curr;
    }

  }

  return r;
}

int longestIncreasingSubsequenceLength(int v[], int len)
{
  int k;
  int length = 1;
  int tail[(int) len];
  size_t i;
  if (len == 0)
  {
    return 0;
  }
  else
  {
    
  }

  for (k = 0; k < ((int) len); k++)
    tail[k] = 0;

  tail[0] = v[0];
  for (i = 1; i < len; i++)
  {
    if (v[i] < tail[0])
    {
      tail[0] = v[i];
    }
    else
    {
      if (v[i] > tail[length - 1])
      {
        tail[length++] = v[i];
      }
      else
      {
        tail[ceilIndex(tail, -1, length - 1, v[i])] = v[i];
      }

    }

  }

  return length;
}

int numOfIncSubsequencesOfSizeK(int v[], int n, int k)
{
  int i;
  int l;
  int j;
  int depth_pool[k][n];
  int sum = 0;
  memset(depth_pool, 0, sizeof(depth_pool));
  for (i = 0; i < n; i++)
    depth_pool[0][i] = 1;

  for (l = 1; l < k; l++)
  {
    for (i = l; i < n; i++)
    {
      depth_pool[l][i] = 0;
      for (j = l - 1; j < i; j++)
      {
        if (v[j] < v[i])
        {
          depth_pool[l][i] += depth_pool[l - 1][j];
        }
        else
        {
          
        }

      }

    }

  }

  for (i = k - 1; i < n; i++)
    sum += depth_pool[k - 1][i];

  return sum;
}

int LCIS(int *seq1, int *seq2, int len1, int len2)
{
  int i;
  int j;
  int current = 0;
  int max = 0;
  int depth_array[len2];
  for (i = 0; i < len2; i++)
    depth_array[i] = 0;

  for (i = 0; i < len1; i++)
  {
    for (j = 0; j < len2; j++)
    {
      if (seq1[i] == seq2[j])
      {
        if ((current + 1) > depth_array[j])
        {
          depth_array[j] = current + 1;
        }
        else
        {
          
        }

      }
      else
      {
        
      }

      if (seq1[i] > seq2[j])
      {
        if (current < depth_array[j])
        {
          current = depth_array[j];
        }
        else
        {
          
        }

      }
      else
      {
        
      }

      if (depth_array[j] > max)
      {
        max = depth_array[j];
      }
      else
      {
        
      }

    }

  }

  return max;
}

int main()
{
  int allocd = 10000000;
  int problem;
  int *v1 = malloc((sizeof(int)) * allocd);
  int *v2 = malloc((sizeof(int)) * allocd);
  int lis;
  int lis_amount;
  int i = -1;
  int j = 0;
  int curr = 0;
  int l1;
  int l2;
  char c = ' ';
  memset(v1, 0, (sizeof(int)) * allocd);
  memset(v2, 0, (sizeof(int)) * allocd);
  if ((problem = getchar() - '0') <= 0)
  {
    return 1;
  }
  else
  {
    
  }

  getchar();
  do
  {
    if (i > ((int) allocd))
    {
      v1 = (int *) realloc(v1, 2 * allocd);
      allocd *= 2;
    }
    else
    {
      
    }

    if (c == ' ')
    {
      v1[i++] = curr;
      curr = 0;
    }
    else
    {
      curr = ((curr * 10) + c) - '0';
    }

  }
  while ((c = getchar()) != '\n');
  v1[i] = curr;
  v1 = realloc(v1, (sizeof(int)) * i);
  allocd = 100;
  if (problem == 2)
  {
    while (1 != EOF)
    {
      v2[j] = new_sym_var(sizeof(int) * 8);
      if (i > ((int) allocd))
      {
        v2 = (int *) realloc(v2, 2 * allocd);
        allocd *= 2;
      }
      else
      {
        
      }

      j++;
    }

  }
  else
  {
    
  }

  v2 = realloc(v2, (sizeof(int)) * j);
  l1 = i;
  l2 = j;
  if (problem == 1)
  {
    lis = longestIncreasingSubsequenceLength(v1, i + 1);
    lis_amount = numOfIncSubsequencesOfSizeK(v1, i + 1, lis);
    printf("%d %d\n", lis, lis_amount);
  }
  else
  {
    if (problem == 2)
    {
      printf("%d\n", LCIS(v1, v2, l1 + 1, l2));
    }
    else
    {
      return 1;
    }

  }

  return 0;
}
