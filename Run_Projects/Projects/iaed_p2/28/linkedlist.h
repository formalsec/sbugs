#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct ListNode{
  void * structPointer;
  struct ListNode * prev;
  struct ListNode * next;
} ListNode;

ListNode * push(ListNode ** head_ref, void * structPointer);

void deleteListNode(ListNode ** head_ref,
  ListNode ** tail_ref, ListNode * del);

int changeScore(ListNode * node, int newScore1, int newScore2);
char * winningTeam(ListNode* node);
void printNodeJogo(ListNode * node, int inputLine);
void printNodeEquipa(ListNode * node, int inputLine);
void printList(ListNode * tail, int inputLine);
void printBestTeams(ListNode ** head_ref, int inputLine);
void free_dlistJogo(ListNode * head);
void free_dlistEquipa(ListNode * head);
void free_dlist(ListNode * head);
void mergeSort(ListNode ** head_ref);
ListNode * sortedMerge(ListNode *a, ListNode *b);

void splitList(ListNode * source, ListNode ** frontRef,
  ListNode ** backRef);


#endif /* LINKEDLIST_H */
