#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "all.h"
#include <string.h>
#include <stdio.h> 
#include <stdlib.h>


extern prod prod_list[];
int less(int i1, int i2)
{
  prod *p1 = &prod_list[i1];
  prod *p2 = &prod_list[i2];
  return (strcmp(p1->desc, p2->desc) < 0) ? (1) : (0);
}

void fixDown(int arr[], int r, int k)
{
  int ileft;
  int iright;
  int largest = k;
  ileft = (2 * k) + 1;
  iright = 2 * (k + 1);
  if ((ileft <= r) && less(arr[largest], arr[ileft]))
  {
    largest = ileft;
  }
  else
  {
    
  }

  if ((iright <= r) && less(arr[largest], arr[iright]))
  {
    largest = iright;
  }
  else
  {
    
  }

  if (largest != k)
  {
    {
      int t = *(&arr[k]);
      *(&arr[k]) = *(&arr[largest]);
      *(&arr[largest]) = t;
    }
    ;
    fixDown(arr, r, largest);
  }
  else
  {
    
  }

}

void heapsort(int arr[], int r)
{
  int i;
  int heapsize = r + 1;
  for (i = (heapsize / 2) - 1; i >= 0; i--)
    fixDown(arr, r, i);

  while (r > 0)
  {
    {
      int t = *(&arr[0]);
      *(&arr[0]) = *(&arr[r]);
      *(&arr[r]) = t;
    }
    ;
    fixDown(arr, --r, 0);
  }

}

void countsort(int *arr, int len, int mask, int *out)
{
  int i0 = 0;
  int i1 = 0;
  int i;
  for (i = 0; i < len; i++)
    if (!(prod_list[*(arr + i)].price & mask))
  {
    i1++;
  }
  else
  {
    
  }


  for (i = 0; i < len; i++)
    if (prod_list[*(arr + i)].price & mask)
  {
    *(out + (i1++)) = *(arr + i);
  }
  else
  {
    *(out + (i0++)) = *(arr + i);
  }


}

void radixsort(int *arr, int len)
{
  int *out = malloc(10000 * (sizeof(int)));
  int *a[2];
  int i;
  a[0] = arr;
  a[1] = out;
  for (i = 0; i < 31; i++)
  {
    countsort(a[i & 1], len, 1 << i, a[1 - (i & 1)]);
  }

  free(out);
}

