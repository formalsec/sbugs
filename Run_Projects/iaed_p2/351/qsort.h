#include <stdlib.h>
#include <string.h>
#ifndef QSORT_CHARARR_H
#define QSORT_CHARARR_H

/* info_struct allows for parallel operations related to the sort */
typedef void (*swap_elem)(int idx_1,int idx_2,char **chr_arr,void * info_struct);

void quicksort(char **chr_arr,int left, int right,void * info_struct, swap_elem f_swap);
int part(char **chr_arr,int left, int right, void * info_struct, swap_elem f_swap);
#endif

