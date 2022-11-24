#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <string.h>

/* funcao merge */
void merge_alpha(char ** list_t, int l, int m, int r){
	int i, j, k, a;
	char ** list_t_aux = can_fail_malloc(sizeof(char *) * (r + 1));
	for(i = l; i <= m; i++)	list_t_aux[i] = list_t[i];
	for(i = m + 1; i <= r; i++) list_t_aux[i] = list_t[i];
	i = l;
	j = m + 1;
	k = l;
	while(i <= m && j <= r){
		for(a = 0; list_t_aux[i][a] == list_t_aux[j][a]; a++);
		if(list_t_aux[i][a] < list_t_aux[j][a]){
			list_t[k] = list_t_aux[i];
			i++;
		}
		else{
			list_t[k] = list_t_aux[j];
			j++;
		}
		k++;
	}
	if(i > m){
		for(; j <= r; j++){
			list_t[k] = list_t_aux[j];
			k++;
		}
	}
	else{
		for(; i <= m; i++){
			list_t[k] = list_t_aux[i];
			k++;
		}
	}
	free(list_t_aux);
}

/* funcao sort */
void sort_alpha(char ** list_t, int l, int r){
	int m = (r + l)/2;
	if(r <= l) return;
	sort_alpha(list_t, l, m);
	sort_alpha(list_t, m + 1, r);
	merge_alpha(list_t, l, m, r);
}