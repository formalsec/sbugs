#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "all.h"

#include <string.h>
#include <stdio.h> 
#include <stdlib.h>

#define exch(A, B) { int t = *A; *A = *B; *B = t; }
#define BITS 31	/* bits necessarios para guardar um inteiro longo */

extern prod prod_list[];

/* funcao de comparacao do heap sort */
int less(int i1, int i2) {
	prod* p1 = &prod_list[i1];
	prod* p2 = &prod_list[i2];

	return strcmp(p1->desc, p2->desc) < 0 ? 1 : 0;
}

void fixDown(int arr[], int r, int k) {
	int ileft, iright, largest = k;

	ileft = 2 * k + 1;
	iright = 2 * (k + 1);

	if (ileft <= r && less(arr[largest], arr[ileft]))
		largest = ileft;
	if (iright <= r && less(arr[largest], arr[iright]))
		largest = iright;

	if (largest != k) {
		exch(&arr[k], &arr[largest]);
		fixDown(arr, r, largest);
	}
}

/* sort para as encomendas */
void heapsort(int arr[], int r) {
	int i, heapsize = r + 1;
	/* buildheap */

	for (i = heapsize / 2 - 1; i >= 0; i--)
		fixDown(arr, r, i);

	/* sort */
	while (r > 0) {
		exch(&arr[0], &arr[r]);
		fixDown(arr, --r, 0);
	}
}

/* auxiliar do radixsort */
void countsort(int* arr, int len, int mask, int* out) {
	int i0 = 0, i1 = 0;
	int i;

	for (i = 0; i < len; i++)
		if (!(prod_list[*(arr + i)].price & mask))
			i1++;

	for (i = 0; i < len; i++)
		if (prod_list[*(arr + i)].price & mask)
			*(out + i1++) = *(arr + i);
		else
			*(out + i0++) = *(arr + i);
}

/* sort para os produtos */
void radixsort(int* arr, int len) {
	int* out = can_fail_malloc(MAX_PROD * sizeof(int));
	int* a[2];
	int i;

	a[0] = arr; a[1] = out;

	for (i = 0; i < BITS; i++) {
		countsort(a[i & 1], len, 1 << i, a[1 - (i & 1)]);
	}

	free(out);
}