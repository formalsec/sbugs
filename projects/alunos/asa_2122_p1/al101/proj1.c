#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ASC 48
#define LIM 421000

int inputSize(char str[]){
    int i = 0, j = 1;
    
    while (str[i] != '\n'){
        while (str[i] != ' ' && str[i] != '\n'){
            i++;
        }
        if (str[i] != '\n'){
            i++;
        }
        j++;
    }
    return j;  
}

void lis(int X[], int size){
    int lis[size], cnt[size];
    int i = 0, j = 0, max = 1, contador = 1;

    for (i = 0; i < size; i++){
        lis[i] = 1;
        cnt[i] = 1;
    }
    if (size > 2){
        for (i = 1; i < size - 1; i++){
            for (j = 0; j < i; j++){
                if (X[i] > X[j]){
                    if (lis[i] < lis[j] + 1){
                        lis[i] = lis[j] + 1;
                        cnt[i] = cnt[j];
                        if (lis[i] > max){
                            max = lis[i];
                            contador = 0;
                        }
                    }
                    else if (lis[i] == lis[j] + 1){
                        cnt[i] += cnt[j];
                    }
                }
            }
            if (lis[i] == max){
                contador += cnt[i];
            }
        }
    }
    else{
        contador = 1;
    }

    printf("%d %d\n", max, contador);
}

void lcis(int X[], int Y[], int n, int m){
    int i = 0, j = 0, max = 0, cur_len = 0;

    if (n != 0 && m != 0){
        int len_tab[m];
        for (i = 0; i < m; i++){
            len_tab[i] = 0;
        }
        for (i = 0; i < n - 1; i++){
            for (j = 0; j < m - 1; j++){
                if (X[i] == Y[j] && len_tab[j] < (cur_len + 1)){
                    len_tab[j] = cur_len + 1;
                    if (len_tab[j] > max){
                        max = len_tab[j];
                    }
                }
                if (X[i] > Y[j] && cur_len < len_tab[j]){
                    cur_len = len_tab[j];
                }
            }
            cur_len = 0;
        }
    }
    printf("%d\n", max);
}

int main(){
    
    char prob[3] = {'c'};
    char str[LIM] = {'c'};
    int *X = NULL;
    int *Y = NULL;
    int val = 0, i = 0, j = 0, v = 0, m = 0, sizeA = 0, sizeB = 0;

    if (fgets(prob, 3, stdin) == NULL){
        return -1;
    }

    if (strcmp(prob, "1\n") == 0){

        if (fgets(str, LIM, stdin) == NULL){
            return -1;
        }

        sizeA = inputSize(str);

        X = can_fail_malloc(sizeof(int) * sizeA);

        i = 0;

        while (str[i] != '\n'){

            m = i;

            while (str[i] != ' ' && str[i] != '\n'){
                if (str[i] != '-'){
                    val = val * 10 + (str[i] - ASC);
                }
                i++;
            }
            if (str[i] != '\n'){
                i++;
            }
            
            if (str[m] == '-'){
                val = -val;
            }

            X[j] = val;

            val = 0;
            j++;
        }

        lis(X, sizeA);
    }

    else if (strcmp(prob, "2\n") == 0){

        if (fgets(str, LIM, stdin) == NULL){
            return -1;
        }

        sizeA = inputSize(str);

        X = can_fail_malloc(sizeof(int) * sizeA);

        while (str[i] != '\n'){

            m = i;

            while (str[i] != ' ' && str[i] != '\n'){
                if (str[i] != '-'){
                    val = val * 10 + (str[i] - ASC);
                }
                i++;
            }
            if (str[i] != '\n'){
                i++;
            }

            if (str[m] == '-'){
                val = -val;
            }

            X[j] = val;

            val = 0;
        
            j++;
        }

        j = 0;
        i = 0;

        strcpy(str, "");

        if (fgets(str, LIM, stdin) == NULL){
            return -1;
        }

        sizeB = inputSize(str);

        Y = can_fail_malloc(sizeof(int) * sizeB);

        while (str[i] != '\n'){

            m = i;

            while (str[i] != ' ' && str[i] != '\n'){
                if (str[i] != '-'){
                    val = val * 10 + (str[i] - ASC);
                }
                i++;
            }
            if (str[i] != '\n'){
                i++;
            }

            if (str[m] == '-'){
                val = -val;
            }

            for (v = 0; v < sizeA - 1; v++){
                if (val == X[v]){
                    Y[j] = val;
                    j++;
                    break;
                }
            }

            val = 0;
        }

        lcis(X, Y, sizeA, j+1);
    }

    free(X);
    free(Y);

    return 0;
}