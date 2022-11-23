#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/*
Grupo al009
Francisco Giro 92504
Rodrigo Antunes 92551
*/



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define UNVISITED -1
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))


typedef struct {
  int id;
  int low;
  bool onStack;
  int grade;
  int nfriends;
  int* friends;
} Aluno;

Aluno* table;

int nalunos;
int namizades;
int id =0;
int* stack;
int nstack = 0;


void inicialize_table();
void put_friendship(int first, int second);
void tarjan();
void tarjan_visit(int node);
void inicialize_stack();
void push_stack(int n);
int pop_stack();


int main(){
  int i;

  scanf("%d,%d", &nalunos, &namizades);

  if(nalunos<2 || namizades < 1)
    exit(1);

  table = can_fail_malloc(sizeof(Aluno)*nalunos);
  inicialize_table();
  inicialize_stack();

  for(i=0; i < nalunos; i++){
    scanf("%d", &table[i].grade);
  }

  for(i=0; i<namizades; i++){
    int first,second;
    scanf("%d %d", &first, &second);
    put_friendship(first,second);
  }

  tarjan();

  for(i=0; i < nalunos; i++){
    printf("%d\n", table[i].grade);
  }

  free(table);
  free(stack);

  return 0;
}

void put_friendship(int a, int b){
  int i;
  int* new_friends;
  if(table[a-1].nfriends == 0){
    table[a-1].friends = can_fail_malloc(sizeof(int));
    table[a-1].friends[0] = (b-1);
    table[a-1].nfriends++;
  }
  else{
    table[a-1].nfriends++;
    new_friends = can_fail_malloc(sizeof(int)*table[a-1].nfriends);
    for(i = 0; i < table[a-1].nfriends-1; i++)
      new_friends[i] = table[a-1].friends[i];
    new_friends[i] = (b-1);
    table[a-1].friends = new_friends;
  }
}


void inicialize_table(){
  int i;
  for(i=0; i< nalunos; i++){
    table[i].id = UNVISITED;
    table[i].low = -1;
    table[i].onStack = false;
    table[i].nfriends = 0;
    table[i].friends = NULL;
  }
}


void inicialize_stack(){
  int i;
  stack = can_fail_malloc(sizeof(int)*nalunos);
  for(i=0; i < nalunos; i++){
    stack[i] = -1;
  }
}

void push_stack(int n){
  stack[nstack] = n;
  nstack++;
}

int pop_stack(){
  nstack--;
  return stack[nstack];
}


void tarjan(){
	int i;
	for (i=0; i < nalunos; i++){
		if (table[i].id == UNVISITED){
			tarjan_visit(i);
		}
	}
}


void tarjan_visit(int node){
  int i, friend;


  push_stack(node);
  table[node].onStack = true;
  table[node].id = id; table[node].low = id;
  id++;


  for(i=0; i<table[node].nfriends; i++){
    friend = table[node].friends[i];
    if(table[friend].id == UNVISITED){
      tarjan_visit(table[node].friends[i]);
      table[node].grade = max(table[friend].grade, table[node].grade);
    }
    if(table[table[node].friends[i]].onStack){
      table[node].low = min(table[friend].low, table[node].low);
      table[node].grade = max(table[friend].grade, table[node].grade);
    }
    else{
      table[node].grade = max(table[friend].grade, table[node].grade);
    }
  }

  if(table[node].id == table[node].low){
    for(i = pop_stack();; i = pop_stack()){
      table[i].onStack = false;
      table[i].low = table[node].id;
      table[i].grade = max(table[node].grade, table[i].grade);
      if(i==node)break;
    }
  }

}
