#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*helper function for merge_sort*/
void merge(char *arr[], int l, int m, int r){ 
    int i, j, k; 
    /*temporary arrays creation*/
    int n1 = m - l + 1; 
    int n2 =  r - m; 
    char **L = can_fail_malloc(n1*sizeof(char*));
    char **R = can_fail_malloc(n2*sizeof(char*));
    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1+ j]; 
    i = 0;
    j = 0;
    k = l;
    /*merging*/
    while (i < n1 && j < n2){ 
        if (strcmp(L[i], R[j]) < 0) { 
            arr[k] = L[i]; 
            i++; 
		} 
        else{ 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    }
    /*copying remaining elements*/
    while (i < n1){ 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < n2){ 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
    /*freeing memory*/
    free(L);
    free(R);
} 
/*merge sort*/
void merge_sort(char *arr[], int l, int r) { 
    if (l < r){ 
        int m = l+(r-l)/2; 
        /*sort halves*/
        merge_sort(arr, l, m); 
        merge_sort(arr, m+1, r); 
        /*calling helper function*/
        merge(arr, l, m, r); 
    } 
}
