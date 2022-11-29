#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>

void problem1(int* vec, int size, int aux[]){
    int i,j;
    if (size <= 1){
        aux[0] = size;
        aux[1] = size;
    }
    int* lenght = (int*)can_fail_malloc(size*sizeof(int));
    int* count = (int*)can_fail_malloc(size*sizeof(int));
    for(i=0;i<size;i++){
        lenght[i] = 1;
        count[i] = 1;
    }

    for(j=0;j<size; j++){
        for (i=0;i<j; i++){
            if (vec[i] < vec[j]){
                if (lenght[i] >= lenght[j]){
                    lenght[j] = lenght[i] + 1;
                    count[j] = count[i];
                }
                else if (lenght[j] == lenght[i] + 1)
                    count[j] += count[i];
            }
        }
    }

    int max=0, cnt=0;
    for (i=0; i<size; i++){
        if (lenght[i] > max){
            max = lenght[i];
            cnt = count[i];
        } else if (lenght[i] == max){
            cnt += count[i];
        }  
    }
    aux[0] = max;
    aux[1] = cnt;
    free(lenght);
    free(count);
}

int problem2(int* vec1,int size1,int*vec2,int size2){
    int i,j,k;
    int* result = (int*)can_fail_malloc(size2*sizeof(int));
    for (i=0;i<size2;i++){
        result[i] = 0;
    }

    for (i=0;i<size1;i++){
        int len = 0;
        for (j=0; j<size2; j++){
            if (vec1[i] == vec2[j]){
                if (len + 1 > result[j]){
                    result[j] = len + 1;
                }
            }
            if (vec1[i] > vec2[j]){
                if (result[j] > len){
                    len = result[j];
                }
            }
        }
    }

    int value = 0;
    for (k=0;k<size2;k++){
        if(result[k] > value){
            value = result[k];
        }
    }
    return value;

}

int main(){
    int array[2] = {0,0};
    int size = 0;
    int size1 = 0;
    int d;
    char temp = ' ';
    int* vec = (int*) can_fail_malloc((size + 1)*sizeof(int));
    scanf("%d",&d);
    if (d == 1){
        while(temp != '\n'){
            scanf("%d%c",&vec[size],&temp);
            size++;
            vec = (int*) can_fail_realloc(vec,(size+1)*sizeof(int));
        }
        problem1(vec,size,array);
        printf("%d %d\n", array[0], array[1]);
    }
    if (d == 2){
        while(temp != '\n'){
            scanf("%d%c",&vec[size],&temp);
            size++;
            vec = (int*) can_fail_realloc(vec,(size+1)*sizeof(int));
        }
        int *vec1 = (int*) can_fail_malloc((size1+1)*sizeof(int));
        temp = ' ';
        while(temp != '\n'){
            scanf("%d%c",&vec1[size1],&temp);
            size1++;
            vec1 = (int*) can_fail_realloc(vec1,(size1+1)*sizeof(int));
        }
        int result = problem2(vec,size,vec1,size1);
        printf("%d\n",result);
        free(vec1);
    }
    free(vec);
    return 0;
}