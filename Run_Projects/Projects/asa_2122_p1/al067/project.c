#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100000


int seq1[SIZE];
int seq2[SIZE];


void problemOne(int *seq, int len);
void problemTwo(int *seq1, int len1, int *seq2, int len2);

int getSeq(int *seq, int *comp, int len);
int isInSeq(int *seq, int len, int n);


int main(){
    char c;
    int len1, len2;
    
    c = getchar();
    if (c == '1'){
        c = getchar();
        len1 = getSeq(&seq1[0], &seq1[0], 0);
        problemOne(&seq1[0], len1);
    }
    else if (c == '2'){
        c = getchar();
        len1 = getSeq(&seq1[0], &seq1[0], 0);
        len2 = getSeq(&seq2[0], &seq1[0], len1);
        problemTwo(&seq1[0], len1, &seq2[0], len2);
    }
    return 0;
}

void problemOne(int *seq, int len){
    int i, j, n = 0, max = 1;
    int numLis[len];
    int LIS[len];
    for (i=0; i< len; i++){
        numLis[i]=1;
        LIS[i]=1;
    }
    for (i = len-1; i >= 0; i--){
        for(j = i+1; j < len; j++){
            if (seq[i] < seq[j] && LIS[i] < (1 + LIS[j])){
                LIS[i] = 1 + LIS[j];
                numLis[i] = numLis[j];
            }
            else if (seq[i] < seq[j] && LIS[i] == (1 + LIS[j])){
                numLis[i] = numLis[i] + numLis[j];
            }
        }
        if (LIS[i] > max){
            max = LIS[i];
            n = numLis[i];
        }
        else if(LIS[i] == max){
            n += numLis[i];
        }
    }
    printf("%d %d\n", max, n);
}

void problemTwo(int *seq1, int len1, int *seq2, int len2){
    int i, j, n, max = 0;
    int LCIS[len2];
    for (i=0; i< len2; i++){
        LCIS[i]=0;
    }
    for (i = 0; i < len1 ; i++){
        n = 0;
        for(j = 0; j < len2; j++){
            if (seq1[i] == seq2[j]){
                if (n + 1 > LCIS[j]){
                    LCIS[j] = n + 1;
                    if (LCIS[j] > max){
                        max = LCIS[j];
                    }
                }
                    
            }
            if (seq1[i] > seq2[j]){
                if (LCIS[j] > n){
                    n = LCIS[j];
                }
                    
            }       
        }
    }
    printf("%d\n", max);
}

int getSeq(int *seq, int *comp, int len){
    int i = 0, n = 0;
    char c;
    c = getchar();
    while(c != '\n' && c != EOF && i < SIZE){
        if(c != ' '){
            n = (n*10) + ((int)c - '0');   
        }
        else{
            if(len == 0){
                seq[i]=n;
                i++;  
            }
            else if(isInSeq(comp, len, n)){
                seq[i]=n;
                i++;
            }
            n = 0;
        }
        c = getchar();
    }
    if(len == 0){
        seq[i]=n;
    }
    else if(isInSeq(comp, len, n)){
        seq[i]=n;
    }
    return (i+1);
}

int isInSeq(int *seq, int len, int n){
    int i;
    for (i = 0; i < len; i++){
        if(seq[i] == n){
            return 1;
        }
    }
    return 0;
}