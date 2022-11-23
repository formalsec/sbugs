#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/*Projeto de ASA*/
/*Tiago Prata N86516*/
/*Joao Goncalves N93918*/
/*Grupo 82*/

#include <stdio.h>
#include <stdlib.h>

int numberofStudents;
int *departure;
int *discovered;
int time;

int dfs(int graph[numberofStudents][numberofStudents], int v, int discovered[numberofStudents], int departure[2*numberofStudents], int time){
  discovered[v] = 1;
  time++;
  int i;
  for(i = 0; i < numberofStudents; i++){
    if(graph[v][i] == 1){
      if(discovered[i] != 1){
        time = dfs(graph, i, discovered, departure, time);
      }
    }
  }
  departure[time] = v;
  time++;
  return time;
}

void doTopologicalSort(int graph[numberofStudents][numberofStudents]){
  int i;
  for(i = 0; i < 2*numberofStudents; i++){
    departure[i] = -1;
  }

  for(i=0; i < numberofStudents; i++){
    discovered[i] = 0;
  }

  time = 0;
  for(i = 0; i < numberofStudents; i++){
    if(discovered[i] != 1){
      time = dfs(graph, i, discovered, departure, time);
    }
  }
}

int main(){

  int numberofRelations;
  int source;
  int dest;
  int i;
  int j;

  scanf("%d,%d", &numberofStudents, &numberofRelations);

/*Initialize graph in matrix format*/
  int matrixGraph[numberofStudents][numberofStudents];
  for(i = 0; i < numberofStudents; i++){
    for(j = 0; j < numberofStudents; j++){
      matrixGraph[i][j] = 0;
    }
  }

  int studentGrades[numberofStudents];
  for (i = 0; i < numberofStudents; i++){
    scanf("%d", &studentGrades[i]);
  }

  /*Updating the matrix*/
  for(i=0; i < numberofRelations; i++){
    scanf("%d %d", &source, &dest);
    matrixGraph[source-1][dest-1] = 1;
  }


  departure = (int*)can_fail_malloc((numberofStudents * 2) * sizeof(int));
  discovered = (int*)can_fail_malloc(numberofStudents * sizeof(int));

  doTopologicalSort(matrixGraph);

  for(i = 0; i < 2*numberofStudents; i++){
    if (departure[i] != -1){
      for(j = 0; j < numberofStudents; j++){
        if (matrixGraph[departure[i]][j] == 1){
          if(studentGrades[j] > studentGrades[departure[i]]){
            studentGrades[departure[i]] = studentGrades[j];
          }
        }
      }
    }
  }

  for(j = 0; j < numberofStudents; j++){
    printf("%d\n", studentGrades[j]);
  }

  free(discovered);
  free(departure);
  return 0;
}
