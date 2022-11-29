#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/*
 * File: proj1.c
 * Authors: João Vítor 99246, Rafael Maciel 100671
 * Description: ASA first project 2021/2022
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INITIAL_SIZE 200000
#define MAX_STRING 900000
#define TRUE 1
#define FALSE 0


int* getSequence(int*);
void problem1();
void problem2();
int maxCommonSize(int*, int, int*, int);
unsigned long long int numberOfLongestIncreasingSubsequences(int*, int, int*);
int binarySearch(int*, int, int, int);


/* Solves either problem 1 or problem 2*/
int main() {
    char problemNumber = getchar();
    
    if (getchar() == EOF)
        return 1;

    if (problemNumber == '1')
	problem1();
    if (problemNumber == '2')
	problem2();

    return 0;
}


/* Returns int array read from stdin. Stores size of the array in f_size*/
int* getSequence(int* f_size) {
    
    /* reads from sdin*/
    char line[MAX_STRING];
    fgets(line, MAX_STRING, stdin);

    /* allocates memory for the new array*/
    int* sequence = (int*) can_fail_malloc(sizeof(int) * INITIAL_SIZE);
    if (sequence == NULL)
        return NULL;

    /* separates the input in ints and adds them to sequence*/
    char* n = strtok(line, " ");
    int i = 0;
    int number;
    for (; n != NULL; n = strtok(NULL, " "), i++) {
        if (sscanf(n, "%d", &number) == EOF)
	    break;
        sequence[i] = number;
    }

    /* stores the size of sequence*/
    *f_size = i;

    return sequence;
}


/* Compare function for stdlib's qsort*/
int cmpfunc (const void* a, const void* b) {
   return (*(int*)a - *(int*)b);
}


/* Returns an int array read from stdin with only ints present in seq.
 * Stores size of the array in f_size*/
int* getSecondSequence(int* f_size, int* seq, int size) {
    
    /* makes a copy aux of seq*/
    int* aux = (int*) can_fail_malloc(sizeof(int) * size);
    int i = 0;
    for (; i < size; i++) 
	aux[i] = seq[i];

    /* sort aux to use binary search*/
    qsort(aux, size, sizeof(int), cmpfunc);
    
    /* reads from sdin*/
    char line[MAX_STRING];
    fgets(line, MAX_STRING, stdin);
    
    /* allocates memory for the new array*/
    int* sequence = (int*) can_fail_malloc(sizeof(int) * INITIAL_SIZE);
    if (sequence == NULL)
        return NULL;
    
    /* separates the input in ints and adds them to sequence if they are in aux*/
    char* n = strtok(line, " ");
    i = 0;
    int number;
    for (; n != NULL; n = strtok(NULL, " ")) {
        if (sscanf(n, "%d", &number) == EOF)
	    break;
	if (binarySearch(aux, 0, size -1, number)) {
	    sequence[i] = number;
	    i++;
	}
    }
    
    /* stores the size of sequence*/
    *f_size = i;

    free(aux);
    return sequence;
}


/* Returns 1 if number is present in seq, 0 otherwise*/
int binarySearch(int* seq, int left, int right, int number) {
    int mid;
    while (left <= right) {
	mid = left + (right - left) / 2;
	if (seq[mid] == number)
	    return TRUE;
	else if (seq[mid] < number)
	    left = mid + 1;
	else
	    right = mid - 1;
    }
    
    return FALSE;
}


/* Solves problem 1*/
void problem1() {
    int size;
    int maxDepth;
    int* sequence = getSequence(&size);

    unsigned long long int count = numberOfLongestIncreasingSubsequences(sequence, size, &maxDepth);
    
    printf("%d %llu\n", maxDepth, count);
    
    free(sequence);
}


/* Solves problem 2*/
void problem2() {
    int size1;
    int size2;
    int* sequence1 = getSequence(&size1);
    int* sequence2 = getSecondSequence(&size2, sequence1, size1);

    int maxSize = maxCommonSize(sequence1, size1, sequence2, size2);

    printf("%d\n", maxSize);

    free(sequence1);
    free(sequence2);
}


/* Returns the number of increasing subsequences in seq with the maximum size.
 * Stores the maximum size of subsequences in sizeOfSubSequences*/
unsigned long long int numberOfLongestIncreasingSubsequences(int* seq, int size, int* sizeOfSubSequence) {
    
    *sizeOfSubSequence = 1;
    unsigned long long int numberOfSubSequences = 0;

    /* subSize stores the size of the maximum subsequence for each index*/
    int* subSize = (int*) can_fail_malloc(sizeof(int) * size);
    /* count stores the number of sub sequences that reach the number in each index*/
    unsigned long long int* count = (unsigned long long int*) can_fail_malloc(sizeof(unsigned long long int) * size);

    /* set all entries in subSize and count to 1*/
    int i = 0;
    for (; i < size; i++) {
	count[i] = 1;
	subSize[i] = 1;
    }
    
    /* goes through each int in seq updating count and subSize*/
    i = 0;
    int j;
    for (; i < size; i++) {
	j = i - 1;
	for (; j >= 0; j--) {
	    if (seq[i] > seq[j]) {
		if (subSize[i] < subSize[j] + 1) {
		    subSize[i] = subSize[j] + 1;
		    count[i] = count[j];
		}
		else {
		    if (subSize[i] == subSize[j] + 1)
			count[i] += count[j];
		}
	    }
	}
    }

    /* searches for maximum size of subsequences*/
    i = 0;
    for (; i < size; i++) {
	if (subSize[i] > *sizeOfSubSequence)
	    *sizeOfSubSequence = subSize[i];
    }

    /* calculates the number subsequences with maximum size*/
    i = 0;
    for (; i < size; i++) {
       if (subSize[i] == *sizeOfSubSequence)
	   numberOfSubSequences += count[i];
    }

    free(subSize);
    free(count);
    return numberOfSubSequences;
}


/* Returns the size of the longest common subsequence between v1 and v2*/
int maxCommonSize(int* v1, int s1, int* v2, int s2) {
    int i = 0;
    int j;
    int maxCommonSize = 0;
    
    /* stores the size of the maximum common subsequence for each index*/
    int* sizes = (int*) can_fail_malloc(sizeof(int) * s2);

    /* set all entries in size to 0*/
    for (; i < s2; i++) 
	sizes[i] = 0;
    
    /* goes throught v2 once for each int in v1 updating sizes
     * currentSize stores the current size of subsequences in each iteration of v2*/
    int currentSize;
    i = 0;
    for (; i < s1; i++) {
	j = 0;
	currentSize = 0;
	for(; j < s2; j++) {
	    if (v1[i] == v2[j]) {
		if (sizes[j] < currentSize + 1) 
		    sizes[j] = currentSize + 1;
	    }

	    if (v1[i] > v2[j]) {
		if (sizes[j] > currentSize)
		    currentSize = sizes[j];
	    }
	}
    }

    /* searches for maximum size of subsequences in common*/
    i = 0;
    for (; i < s2; i++) {
	if (sizes[i] > maxCommonSize)
	    maxCommonSize = sizes[i];
    }

    free(sizes);
    return maxCommonSize;
} 
