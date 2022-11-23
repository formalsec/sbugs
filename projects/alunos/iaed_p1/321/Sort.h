#ifndef SORT_H
#define SORT_H


int less(int p1, int p2);
void fixDown(int arr[], int r, int k);
void heapsort(int arr[], int r);
void countsort(int* arr, int len, int mask, int* out);
void radixsort(int* arr, int len);

#endif /* SORT_H */
