#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

typedef struct {
  int colour;
  int grade;
  int nFriends;
  int* friends;
} Person;

Person* peopleList; /*tabela de pessoas*/
int* visited;
int* low;
int* stack;
int* disc;
int max;
int nPeople, nFriendships, nStack=0;

/*Initializes each student*/
void initialize(){
  int i=0;
  for (i=0; i<nPeople; i++){
    peopleList[i].colour = WHITE;
    peopleList[i].grade = 0;
    peopleList[i].nFriends = 0;
    peopleList[i].friends = NULL;
  }
}

void addGrade(int index, int grade){
  peopleList[index].grade = grade;
}

void addFriend(int id, int friend){
  peopleList[id].nFriends ++;
  /*allocates memory in ordert to add a new friend*/
  peopleList[id].friends = (int *)can_fail_realloc(peopleList[id].friends,
  sizeof(int)*(peopleList[id].nFriends));

  peopleList[id].friends[peopleList[id].nFriends-1] = friend;

}

void Push(int i){
     stack[nStack] = i;
      nStack ++;
}

int Pop(){
    nStack--;
    return stack[nStack];
}
/*Tarjan Algorithm*/
int friendRelations(int index, int count){
  int i, n;
  int friend;

  /*put in the stack value of index*/
  Push(index);

  /*Person has already been visited*/
  peopleList[index].colour = GRAY;

  /*associate a number to each vertex using a counter*/
  low[index] = ++count;
  disc[index] = count;

  for (i=0; i<peopleList[index].nFriends; i++){
    friend = peopleList[index].friends[i];
    /*verifies if person has not been visited and, if so, checks its friends
    relations and changes low[index]*/
    if (peopleList[friend].colour == WHITE){
      friendRelations(friend, count);
      low[index] = min(low[index], low[friend]);
    }
    /*verifies if person has been visited and, if so, changes low[index]*/
    else if (peopleList[friend].colour == GRAY){
      low[index] = min(low[index], low[friend]);
    }
    /*compares person's grade with his friend's and changes it if it's smaller*/
    peopleList[index].grade = max(peopleList[friend].grade,
    peopleList[index].grade);
  }
  /*Gives max grade to all the students in the SCC*/
  if (disc[index] == low[index]){
      while ((n=Pop()) != -1){
          peopleList[n].colour = BLACK;
          peopleList[n].grade = peopleList[index].grade;
          if (n == index){
              break;
          }
      }
  }

  return peopleList[index].grade;
}

void relations(){
  int i, count=0;
  /*goes through each person*/
  for (i=0; i<nPeople; i++){
    if (peopleList[i].colour == WHITE){
      friendRelations(i, count);
    }
  }
}

void verifyInput(int nPeople, int nFriendships){
    if (nPeople < 2 || nFriendships < 1){
        exit(0);
    }
}

int main() {
  int i, grade, id, friend;

  scanf("%d,%d", &nPeople, &nFriendships);
  verifyInput(nPeople, nFriendships);

  peopleList = can_fail_malloc(sizeof(Person)*nPeople);
  disc = can_fail_malloc(sizeof(int)*nPeople);
  stack = can_fail_malloc(sizeof(int)*nPeople);
  low = can_fail_malloc(sizeof(int)*nPeople);

  initialize();

  for (i=0; i<nPeople; i++){
    scanf("%d", &grade);
    addGrade(i, grade);
  }

  for (i=0; i<nFriendships; i++){
    scanf("%d %d", &id, &friend);
    id--;
    friend--;
    addFriend(id, friend);
  }

  relations();

  for (i=0; i<nPeople; i++){
    printf("%d\n", peopleList[i].grade);
  }

  for (i=0; i<nPeople; i++){
      free(peopleList[i].friends);
  }
  free(peopleList);
  free(disc);
  free(stack);
  free(low);
  return 0;
}
