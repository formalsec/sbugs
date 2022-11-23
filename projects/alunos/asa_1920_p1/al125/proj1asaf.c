#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/*jose maria figueira janarra ist192505  grupo al125*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM 10000000

typedef struct aluno {
    int index;
    int notaprev;
    int notarec;
    int *amigos;
    int numa;
    int marca;
}*alunos;

static alunos *listalunos;

alunos* inserir(char *buffer, char *bufferaux, int na, int nam, alunos *listalunos) {
    char delim[]="\n";
    char *token= strtok(buffer, delim);
    int a;
    int b;
    int i;
    int j;
    for (i=0; i<na; i++) {
        token=strtok(NULL, delim);
        listalunos[i]=(alunos)can_fail_malloc(sizeof(struct aluno));
        listalunos[i]->notaprev=atoi(token);
        listalunos[i]->notarec=0;
        listalunos[i]->index=i;
        listalunos[i]->amigos=NULL;
        listalunos[i]->numa=0;
        listalunos[i]->marca=1;
    }
    for (j=0; j<nam; j++) {
        delim[0]=' ';
        token=strtok(NULL, delim);
        a=atoi(token);
        a-=1;
        delim[0]='\n';
        token=strtok(NULL, delim);
        b=atoi(token);
        b-=1;
        if (listalunos[a]->amigos==NULL) {
            listalunos[a]->numa+=1;
            listalunos[a]->amigos=(int*)can_fail_malloc(sizeof(int));
            listalunos[a]->amigos[0]=b;
        }
        else {
            listalunos[a]->numa+=1;
            listalunos[a]->amigos=(int*)can_fail_realloc(listalunos[a]->amigos, sizeof(int)*listalunos[a]->numa);
            listalunos[a]->amigos[listalunos[a]->numa-1]=b;
            }
        }
    return listalunos;
}

int recalcula(alunos aluno, int nota) {
    int i;
    if (aluno->notarec>nota) {
        nota=aluno->notarec;
        return nota;
    }
    if (aluno->marca) {
        if (aluno->notaprev>nota) {
            nota=aluno->notaprev;
        }
        aluno->marca=0;
        for (i=0; i<aluno->numa;i++) {
            nota=recalcula(listalunos[aluno->amigos[i]], nota);
        }
    }
    return nota;
}

int *contar (char *buf) {
    int *nl=(int*)can_fail_malloc(sizeof(int)*2);
    char delim[]=",";
    char *token=strtok(buf, delim);
    token[strlen(token)]='\0';
    nl[0]=atoi(token);
    delim[0]='\n';
    token=strtok(NULL, delim );
    token[strlen(token)]='\0';
    nl[1]=atoi(token);
    return nl;
}

int main() {
  char *bufferaux;
  int *nl;
  char *buf;
  char *buff;
  int i=0;
  int nota;
  int j;
  int l;
  int u;
  buf=(char*)can_fail_malloc(DIM);
  buff=(char*)can_fail_malloc(DIM);
  bufferaux=(char*)can_fail_malloc(DIM);
  fgets(buf,DIM,stdin);
  strcpy(buff, buf);
  nl=contar(buf);
  listalunos=(alunos*)can_fail_malloc(sizeof(alunos)*nl[0]);
  while (i<(nl[0]+nl[1])) {
    fgets(buf, DIM , stdin);
    strcat(buff, buf);
    i++;
  }
  strcpy(bufferaux, buff);
  listalunos=inserir(buff, bufferaux, nl[0], nl[1], listalunos);
  for (j=0; j<nl[0];j++) {
      nota=listalunos[j]->notaprev;
      nota=recalcula(listalunos[j], nota);
      listalunos[j]->notarec=nota;
      for (u=0;u<nl[0];u++) {
        listalunos[u]->marca=1;
      }
  }
  for (l=0; l<nl[0];l++) {
      printf("%d\n", listalunos[l]->notarec);
  }
  for (i=0; i<nl[0];i++) {
      free(listalunos[i]->amigos);
      free(listalunos[i]);
  }
  free(listalunos);
  free(nl);
  free(buf);
  free(buff);
  free(bufferaux);
  return 0;
}
