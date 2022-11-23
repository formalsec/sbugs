#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct pair{
    int* pointer;
    int length;
}Pair;

void LIS(int* seq1, int size);
Pair parseArray();
Pair parseArray1(int* seq2);
Pair parseArray2(int* seq2);
void LCIS(int* seq1,int* seq2, int n, int m);


int main(){
    char c;
    Pair s1;
    s1.pointer=NULL;
    int i;
    c = getchar();
    getchar();
    if(c == '1'){ /* problem 1 */
        s1 = parseArray();
        LIS(s1.pointer, s1.length);
    }
    else if(c == '2'){  /* problem 2 */ 
        Pair s2;
        int *temp = can_fail_malloc(sizeof(temp));
        temp[0]=0;
        s1 = parseArray1(temp);
        temp=can_fail_realloc(temp,temp[0]*sizeof(temp));
        for (i=0;i<s1.length;i++){
            temp[s1.pointer[i]]=1;
        }
        s2 = parseArray2(temp);
        free(temp);
        LCIS(s1.pointer, s2.pointer, s1.length, s2.length);
        free(s2.pointer);
    }
    free(s1.pointer);

    return 0;
}

/* Passes array pointer, stores characters in array, and returns size */
Pair parseArray(){
    char c;
    int stop;
    int length = 0;
    int* pointer=can_fail_malloc(sizeof(int));
    Pair pp;
    while((stop = scanf("%d", &pointer[length])) == 1){
        length++;
        if((c = getchar()) == '\n'){
            break;
        }
        pointer=can_fail_realloc(pointer, (length+1)*sizeof(int));
    } 
    pp.pointer=pointer;
    pp.length=length;
    return pp;
}

Pair parseArray1(int* maxi){
    char c;
    int stop;
    int length = 0, max = 0;
    int* pointer=can_fail_malloc(sizeof(int));
    Pair pp;

    while((stop = scanf("%d", &pointer[length])) == 1){
        if(max < pointer[length])
            max = pointer[length];
        length++;
        if((c = getchar()) == '\n'){
            break;
        }
        pointer=can_fail_realloc(pointer, (length+1)*sizeof(int));
    }
    *maxi=max;
    pp.pointer=pointer;
    pp.length=length;
    return pp;
}

Pair parseArray2(int* seq1){
    char c;
    int length = 0, temp = 0;
    int stop;
    int* pointer=can_fail_malloc(sizeof(int));
    Pair pp;

    while((stop = scanf("%d", &temp)) == 1){
        if(seq1[temp] == 1){
            pointer[length] = temp;
            length++;
            if((c = getchar()) == '\n'){
                break;
            }
            pointer=can_fail_realloc(pointer, (length+1)*sizeof(int));
        }
    }
    pp.pointer=pointer;
    pp.length=length;
    return pp;
}

/* Largest Increasing Subsequence algorithm */
void LIS(int* seq1, int size){
    int sSize[size];
    int solutionsArray[size];
    int maxSize=0;
    int i,j;
    int solutions_counter=0;

    if (size!=0){

/* Initialises arrays */
        for (i = 0; i < size; i++) {
            sSize[i] = 1;
            solutionsArray[i]=1;
        }


        for(i=0;i<size;i++){
            int ssize=sSize[i];
            int solution=solutionsArray[i];
            for(j=0;j<i;j++){
                int ssizej=sSize[j];
                int solutionj=solutionsArray[j];
                if(seq1[j]<seq1[i]){
                    if(ssizej+1>ssize){
                        ssize=1+ssizej;
                        solution=solutionj;
                    }
                    else if (ssize==ssizej+1){
                        solution+=solutionj;
                    }
                }
            }
            sSize[i]=ssize;
            solutionsArray[i]=solution;

/* Determines max size of the largest increasing subsequence and 
    the number of increasing subsequences with max length */           
            if (ssize>maxSize){
                maxSize=ssize;
                solutions_counter=solution;
            }
            else if (maxSize==ssize){
                solutions_counter+=solution;
            }    
        }

    }
    printf("%d %d\n", maxSize, solutions_counter);
}


/* Largest Common Subsequence algorithm. Uses memorization */
void LCIS(int *seq1, int *seq2, int n, int m){
    int sols[m];
    memset(sols, 0, m*sizeof(int));
    int i, j;
    int result = 0;
    if(n != 0 && m != 0){
        for(i = 0; i < n; i++){
            int max = 0;
            for(j = 0; j < m; j++){
                if(seq1[i] == seq2[j]){
                    if(max + 1 > sols[j]){
                        sols[j] = max + 1;
                    }
                }
                if(seq1[i] > seq2[j]){
                    if(sols[j] > max){
                        max = sols[j];
                    }
                }
            }
        }
        for(i = 0; i < m; i++){
            if(sols[i] > result) result = sols[i];
        }  
    }
    printf("%d\n",result);
}