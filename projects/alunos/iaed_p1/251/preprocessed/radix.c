#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <string.h>
#include "radix.h"


int getMax(int arr[][2], int n)
{
  int max = arr[0][1];
  int i;
  for (i = 1; i < n; i++)
    if (arr[i][1] > max)
  {
    max = arr[i][1];
  }
  else
  {
    
  }


  return max;
}

void countingSort(int arr[][2], int n, int bDez)
{
  int output[10000][2];
  int i;
  int count[500] = {0};
  for (i = 0; i < n; i++)
    count[(arr[i][1] / bDez) % 10]++;

  for (i = 1; i < 10; i++)
    count[i] += count[i - 1];

  for (i = n - 1; i >= 0; i--)
  {
    output[count[(arr[i][1] / bDez) % 10] - 1][1] = arr[i][1];
    output[count[(arr[i][1] / bDez) % 10] - 1][0] = arr[i][0];
    count[(arr[i][1] / bDez) % 10]--;
  }

  for (i = 0; i < n; i++)
  {
    arr[i][0] = output[i][0];
    arr[i][1] = output[i][1];
  }

}

void radixSort(int arr[][2], int n)
{
  int m = getMax(arr, n);
  int bDez;
  for (bDez = 1; (m / bDez) > 0; bDez *= 10)
    countingSort(arr, n, bDez);

}
