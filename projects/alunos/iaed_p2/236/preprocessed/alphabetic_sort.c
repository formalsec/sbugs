#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void merge(char *arr[], int l, int m, int r)
{
  int i;
  int j;
  int k;
  int n1 = (m - l) + 1;
  int n2 = r - m;
  char **L = malloc(n1 * (sizeof(char *)));
  char **R = malloc(n2 * (sizeof(char *)));
  for (i = 0; i < n1; i++)
    L[i] = arr[l + i];

  for (j = 0; j < n2; j++)
    R[j] = arr[(m + 1) + j];

  i = 0;
  j = 0;
  k = l;
  while ((i < n1) && (j < n2))
  {
    if (strcmp(L[i], R[j]) < 0)
    {
      arr[k] = L[i];
      i++;
    }
    else
    {
      arr[k] = R[j];
      j++;
    }

    k++;
  }

  while (i < n1)
  {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2)
  {
    arr[k] = R[j];
    j++;
    k++;
  }

  free(L);
  free(R);
}

void merge_sort(char *arr[], int l, int r)
{
  if (l < r)
  {
    int m = l + ((r - l) / 2);
    merge_sort(arr, l, m);
    merge_sort(arr, m + 1, r);
    merge(arr, l, m, r);
  }
  else
  {
    
  }

}

