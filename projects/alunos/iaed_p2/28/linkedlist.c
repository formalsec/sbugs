#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "linkedlist.h"

#include "estruturas.h"

/* Cria uma node nova*/
ListNode * new_node(void * structPointer) {
  ListNode * p = can_fail_malloc(sizeof(ListNode));
  if (!p) {
    perror("new_node: no memory for a new node");
    exit(EXIT_FAILURE);
  }
  p -> structPointer = structPointer;
  p -> prev = NULL;
  p -> next = NULL;
  return p;
}

/* Adiciona uma nova node ao principio da lista */
ListNode * push(ListNode ** head_ref, void * structPointer) {
  ListNode * p = new_node(structPointer);
  p -> next = ( * head_ref);
  if (( * head_ref) != NULL)
    ( * head_ref) -> prev = p;
  ( * head_ref) = p;
  return p;
}

/* Imprime o conteudo da lista por ordem de insercao */
void printList(ListNode *tail, int inputLine){
  while (tail != NULL) {
    printNodeJogo(tail, inputLine);
    tail= tail->prev;
  }
}

/* Retorna uma flag de modo a alterar o numero de
 * jogos ganhos das equipas com base nos novos scores */
int changeScore(ListNode * node, int newScore1, int newScore2) {
  int prevScore1 = ((struct jogo*)(node->structPointer))->score1;
  int prevScore2 = ((struct jogo*)(node->structPointer))->score2;
  ((struct jogo*)(node->structPointer))->score1 = newScore1;
  ((struct jogo*)(node->structPointer))->score2 = newScore2;
  if(prevScore1-prevScore2 > 0 && newScore1-newScore2 < 0) return 2;
  if(prevScore1-prevScore2 < 0 && newScore1-newScore2 >0) return 1;
  if(prevScore1-prevScore2 == 0 && newScore1-newScore2 >0) return 3;
  if(prevScore1-prevScore2 == 0 && newScore1-newScore2 <0) return 4;
  if(prevScore1-prevScore2 > 0 && newScore1-newScore2 == 0) return 5;
  if(prevScore1-prevScore2 < 0 && newScore1-newScore2 == 0) return 6;
  return 0;
}

/* Compara duas equipas e retorna o nome da equipa que ganhou o jogo */
char * winningTeam(ListNode* node){
  int Score1 = ((struct jogo*)(node->structPointer))->score1;
  int Score2 = ((struct jogo*)(node->structPointer))->score2;
  if(Score1>Score2)
    return ((struct jogo*)(node->structPointer))->equipa1;
  if(Score1<Score2)
    return ((struct jogo*)(node->structPointer))->equipa2;
  return NULL;
}

/* Imprime para o stdin as informacoes relevantes de um jogo */
void printNodeJogo(ListNode * node, int inputLine){
  printf("%d %s %s %s %d %d\n", inputLine,
  ((struct jogo*)(node->structPointer))->nome,
  ((struct jogo*)(node->structPointer))->equipa1,
  ((struct jogo*)(node->structPointer))->equipa2,
  ((struct jogo*)(node->structPointer))->score1,
  ((struct jogo*)(node->structPointer))->score2);
}

/* Imprime para o stdin as informacoes relevantes de uma equipa */
void printNodeEquipa(ListNode *node, int inputLine) {
  printf("%d %s %d\n", inputLine,
  ((struct equipa*)(node->structPointer))->nome,
  ((struct equipa*)(node->structPointer))->jogosGanhos);
}

/* Dada uma lista de equipas imprime as equipas com mais jogos ganhos */
void printBestTeams(ListNode ** head_ref, int inputLine) {
  int max;
  ListNode * current= *head_ref;
  if(*head_ref == NULL) return;
  max = ((struct equipa*)current->structPointer)->jogosGanhos;
  printf("%d Melhores %d\n",inputLine,max);
  while(((struct equipa*)current->structPointer)->jogosGanhos == max) {
    printf("%d * %s\n",inputLine,
    ((struct equipa*)current->structPointer)->nome);
    current = current->next;
    if(current == NULL) return;
  }
}


/* Elemina a node da lista */
void deleteListNode(ListNode ** head_ref,
  ListNode ** tail_ref, ListNode * del) {

  if ( * head_ref == NULL || del == NULL)
    return;
  if (*tail_ref == del)
    * tail_ref = del ->prev;
  if ( * head_ref == del)
    * head_ref = del -> next;
  if (del -> next != NULL)
    del -> next -> prev = del -> prev;
  if (del -> prev != NULL)
    del -> prev -> next = del -> next;

  free(del);
  return;
}

/* Da free a todos os elementos da lista de jogos */
void free_dlistJogo(ListNode * head){
  if(!head)
    return;

  free_dlistJogo(head->next);
  freeGame((jogo*)(head->structPointer));
  free(head);
}

/* Da free a todos os elemntos da lista de jogos */
void free_dlistEquipa(ListNode * head){
  if(!head)
    return;

  free_dlistEquipa(head->next);
  freeEquipa((equipa*)(head->structPointer));
  free(head);
}

/* Das nodes de qualquer lista
 * Utilizado em listas auxiliares */
void free_dlist(ListNode * head){
  if(!head)
    return;

  free_dlist(head->next);
  free(head);
}

/* FUNCOES AUXILIARES */

/*Divide a lista em duas sublistas usando "fast/slow pointer strategy" */
void splitList(ListNode * source,
  ListNode ** frontRef, ListNode ** backRef) {

  ListNode * fast;
  ListNode * slow;
  slow = source;
  fast = source->next;

  while (fast != NULL) {
    fast = fast->next;
    if(fast !=NULL) {
      slow = slow->next;
      fast = fast->next;
    }
  }
  *frontRef = source;
  *backRef = slow->next;
  slow->next = NULL;
}

/* Funcao auxiliar do merge sort */
ListNode * sortedMerge(ListNode *a, ListNode *b) {
  ListNode * result = NULL;

  if (a == NULL) {
    return(b);
  }
  else if(b == NULL) {
    return(a);
  }

  if(strcmp(((struct equipa*)(a->structPointer))->nome,
    ((struct equipa*)(b->structPointer))->nome) <= 0) {

    result = a;
    result->next = sortedMerge(a->next,b);
  }
  else {
    result = b;
    result->next = sortedMerge(a, b->next);
  }

  return(result);
}

/* Realiza um mergeSort sobre a lista ligada */
void mergeSort(ListNode ** head_ref) {
  ListNode* head = * head_ref;
  ListNode* a;
  ListNode* b;

  if((head == NULL) || (head->next == NULL )) {
    return;
  }
  splitList(head, &a, &b);

  mergeSort(&a);
  mergeSort(&b);

  *head_ref = sortedMerge(a, b);

}
