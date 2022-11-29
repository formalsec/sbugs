#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct student{
  unsigned int friendNumber;
  unsigned char gradePrediction;
  unsigned char visited;
  unsigned char maxed;
  struct student **friends;
} student_t;

int studentNumber, friendshipNumber;
int i, j, k, src, dest, tmp, max = -1;
student_t *graph, *max_student = NULL;

void propaga(student_t *student);
void find_newMax();
void clear();

int main(int argc, char **argv, char **envp) {
  if(scanf("%d,%d", &studentNumber, &friendshipNumber) != 2){};
  graph = (student_t*) can_fail_calloc(studentNumber, sizeof(student_t));

  for(i = 0; i < studentNumber; i++){
    if(scanf("%hhu", &graph[i].gradePrediction) != 1){};
    if (graph[i].gradePrediction > max){
        max = graph[i].gradePrediction;
        max_student = &graph[i];
    }
    graph[i].friends = (student_t**) can_fail_calloc(32, sizeof(student_t*));
  }

  for(i = 0; i < friendshipNumber; i++){
    if(scanf("%d %d", &src, &dest) != 2){};
    tmp = graph[dest - 1].friendNumber;

    if(tmp % 32 == 0)
      graph[dest - 1].friends = can_fail_realloc(graph[dest - 1].friends, sizeof(student_t*)*(tmp + 32));

    graph[dest - 1].friends[tmp] = &graph[src - 1];
    graph[dest - 1].friendNumber++;

    if(graph[dest - 1].gradePrediction > graph[src - 1].gradePrediction)
      graph[src - 1].gradePrediction = graph[dest - 1].gradePrediction;
  }

  propaga(max_student);
  max_student -> maxed = 1;

  for(k = 0; k < 2; k++)
    for(i = studentNumber - 1; i >= 0; i--)
      for(j = 0; j < graph[i].friendNumber; j++)
        if(graph[i].friends[j] -> gradePrediction < graph[i].gradePrediction)
          graph[i].friends[j] -> gradePrediction = graph[i].gradePrediction;

  for(i = 0; i < studentNumber; i++){
      find_newMax();
      propaga(max_student);
      clear();
    }

  for(i = 0; i < studentNumber; i++)
    printf("%d\n", graph[i].gradePrediction);

  return 0;
}

void propaga(student_t *student){
  int i;
  student -> visited = 1;

  for(i = 0; i < student -> friendNumber; i++){
    if(student -> friends[i] -> visited == 0){
      if(student -> gradePrediction >= student->friends[i] -> gradePrediction){
        student->friends[i] -> gradePrediction = student -> gradePrediction;
        propaga(student->friends[i]);
      }
    }
  }
  return;
}

void find_newMax(){
    for(i = 0; i < studentNumber; i++){
        if(graph[i].maxed == 0){
            max_student = &graph[i];
            break;
        }
    }
    for(i = 0; i < studentNumber; i++){
        if(graph[i].maxed == 0){
            if(graph[i].gradePrediction >= max_student->gradePrediction)
              max_student = &graph[i];
        }
    }
    max_student -> maxed = 1;
}


void clear(){
  int i;

  for(i = 0; i < studentNumber; i++){
    graph[i].visited = 0;
  }
}
