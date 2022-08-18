#ifndef UTILITIES_H
#define UTILITIES_H

#include <string.h>
#include "structs.h"


void merge_sort(int *, int, int, short int crit(int, int)); 
void merge(int *, int, int, int, short int crit(int, int));


/* Determines if a product ever existed in an order
 * NOTE: does not check if it has been removed */
short int prod_in(int p_id, const order *ord) {
	int i;

	for (i=0; i<ord->num; i++) {

		if (ord->ids[i] == p_id)
			return 1;
	}

	return 0;
}


/* Basic merge sort. Takes the sort criterion as last argument */
void merge_sort(int v[], int l, int r, short int crit(int, int) ) {
	int m = (l+r)/2;

	/* Nothing to merge/sort if array size is < 2 */
	if (r-l+1<2)
		return;

	/* Split the array into 2, sorting each individually */
	merge_sort(v, l, m, crit);
	merge_sort(v, m+1, r, crit);
	merge(v, l, m, r, crit);
}


							/* Auxiliary */


/* Merges the two (sorted) halves of the given array */
void merge(int v[], int l, int m, int r, short int crit(int, int) ) {
	int i=l, j=m+1, k=0;
	int	*aux = malloc((r-l+1)*sizeof(int));
 
	/* Copy the values of v into aux, adding the smallest value between 
	 * v[i] (first half) and v[j] (second half) in each iteration */
	for (; (i<=m) && (j<=r); k++) {

		if (crit(v[i], v[j]))
			aux[k] = v[i++];
		else
			aux[k] = v[j++];
	}

	/* Insert the remaining values of the array into aux if
	 * the main cycle ended prematurely (due to i>m or j>r) */
	while (i<=m)
		aux[k++] = v[i++];

	while (j<=r)
		aux[k++] = v[j++];

	/* Copy the sorted values of aux back into the original array */
	for (i=0; i<r-l+1; i++)
		v[l+i] = aux[i];

	free(aux);
}


/* Checks if products with given IDs are ordered by price (ascending) */
short int price_ordered(int p_id1, int p_id2) {

	return sys[p_id1].price <= sys[p_id2].price;
}


/* Checks if descriptions of products with given IDs are ordered 
 * alphabetically (ascending) */
short int ab_ordered(int p1, int p2) {

	return strcmp(sys[p1].desc, sys[p2].desc) <= 0;
}


#endif /* UTILITIES_H */

