#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/*Istituto Superior Tecnico - LEIC-A
Analise e Sintese de Algoritmos
1o Projeto
Grupo 62
83508 Marcia Marques
91110 Inara Parbato*/

#include <stdio.h>
#include <stdlib.h>

int *input1;
int *input2;
int *solutions1len; /*stores the maximum len that includes the input number in the same index*/
int *solutions1strs; /*stores the number of strings that end with the input number in the same index*/
int *solutions2;
int len=0;/*last occupied position of input1*/
int len2=0;/*last occupied position of input2*/
char c, e;
int i,j;
int max=1, nrseq=0;
int a;

/*solveProblem2
* Function that solves Problem 2*/
int solveProblem2(){
  max=0;
  if((solutions2 = (int*)can_fail_malloc((len2+1)*sizeof(int)))==NULL){
    printf("Memory not allocated\n");
    exit(0);
  }
  for (i=0;i<=len; i=i+1){
    a=0;
    for(j=0; j<=len2; j=j+1){
      if(input1[i]==input2[j] && a+1>solutions2[j]){
        solutions2[j]=a+1;
        if(solutions2[j]>max){
          max=solutions2[j];
        }
      }
      if(input1[i]>input2[j] && a<solutions2[j]){
        a=solutions2[j];
      }
    }
  }
  printf("%d\n", max);
  return 0;
}


/*solveProblem1
* Function that solves Problem 1*/
int solveProblem1(){
  if((solutions1len = (int*)can_fail_malloc((len+1)*sizeof(int)))==NULL){
    printf("Memory not allocated\n");
    exit(0);
  }
  if((solutions1strs = (int*)can_fail_malloc((len+1)*sizeof(int)))==NULL){
    printf("Memory not allocated\n");
    exit(0);
  }
  for (i=0; i<=len; i=i+1){
    solutions1len[i]=1;
    solutions1strs[i]=1;
    for (j=0; j<i;j=j+1){
      if(input1[i]>input1[j]) {
        if(solutions1len[j]+1 > solutions1len[i]){
          solutions1len[i]=solutions1len[j]+1;
          if(solutions1len[i]>max){
            max=solutions1len[i];
            nrseq=0;
          }
          solutions1strs[i]=solutions1strs[j];
        }
        else if (solutions1len[j]+1 == solutions1len[i]){
          solutions1strs[i] =solutions1strs[i]+solutions1strs[j];
        }
      }
    }
    if(solutions1len[i]==max){
      nrseq = nrseq + solutions1strs[i];
    }
  }
  printf ("%d %d\n", max, nrseq);
  return 0;
}

/*getinput
*function that receives the problem number and gets the inputs accordingly
*one line of numbers separated by space for problem 1 stored in input1
*two lines of numbers separated by space for problem 2, one stored in input1 and the other in input2*/
int getinput(char c){
  if((input1 = (int*)can_fail_malloc(sizeof(int)))==NULL){
    printf("Memory not allocated\n");
    exit(0);
  }
  if(scanf("%d", &input1[len]) !=1){
    printf("Read fail1\n");
    exit(0);
  }
  while ((e=getchar()) != '\n' && e != EOF){
    len=len+1;
    input1=(int*) can_fail_realloc(input1, (len+1)*sizeof(int));
    if(scanf("%d", &input1[len]) ==1){
    }
  }
  if(c-48==2){
    len2=0;
    if((input2 = (int*)can_fail_malloc(sizeof(int)))==NULL){
      printf("Memory not allocated\n");
      exit(0);
    }
    if(scanf("%d", &input2[len2])!= 1){
      printf("Read fail3\n");
      exit(0);
    }
    while ((e=getchar()) != '\n' && e != EOF){
      len2=len2+1;
      input2=can_fail_realloc(input2, (len2+1)*sizeof(int));
      if(scanf("%d", &input2[len2]) !=1){
        printf("Read fail4\n");
        exit(0);
      }
    }
  }
  return 0;
}


int main(int argc, char *argv[]){
  c=getchar(); /*get problem number*/
  getchar(); /*get \n*/
  switch(c){
    case '1':
      getinput(c);
      solveProblem1();
      free(input1);
      free(solutions1len);
      free(solutions1strs);
      break;
    case '2':
      getinput(c);
      solveProblem2();
      free(input2);
      free(input1);
      break;
  }
  return 0;
}
