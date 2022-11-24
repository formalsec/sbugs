#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <string.h>
#include "team.h"

#define SIZE 1024


/* Junta os subarrays do mergesort_n */
void merge_aux(Team * teams, int l, int m, int r) {
	int i, j, k;
	Team aux[SIZE];

	/* Constroi o vetor auxiliar */
	for (i = m+1; i > l; i--)
		aux[i-1] = teams[i-1];
	for (j = m; j < r; j++)
		aux[r+m-j] = teams[j+1];

	/* Junta arrays */
	for (k = l; k <= r; k++) {
		if (strcmp(aux[j]->name, aux[i]->name) < 0 || i > m)
			teams[k] = aux[j--];
		else
			teams[k] = aux[i++];
	}
}


/* Ordena equipas por ordem lexicografica do nome */
void sort(Team * teams, int l, int r) {
	int m = (r + l)/2;

	if (r <= l)
		return;

	/* Ordena as duas metades */
	sort(teams, l, m);
	sort(teams, m+1, r);

	/* Junta as duas metades */
	merge_aux(teams, l, m, r);
}

