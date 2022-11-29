#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <string.h>
#include "Linkedlist.h"

link newNode(Item item) {
	link new = (link)can_fail_malloc(sizeof(struct node));
  new->item = item;
	new->next = NULL;
	return new;
}

void insertBegin(link* head, Item item) {
  link new = newNode(item);
  new->next = *head;
  *head = new;
}

void insertEnd(link* head, Item item) {
  link temp;
  link new = newNode(item);
  if(*head == NULL) {
    new->next = *head;
    *head = new;
    return;
  }
  for(temp = *head; temp->next != NULL; temp = temp->next);
  temp->next = new;
}

void insertSorted(link* head, Item item) {
	link temp;
  link new = newNode(item);
  if(*head == NULL || more_wins(item, (*head)->item) || (equals_wins(item, (*head)->item) && less_abc(item, (*head)->item))) {
    new->next = *head;
    *head = new;
    return;
  }
  if((*head)->item == item) {
    free(new);
    return;
  }
  temp = *head;
  while(temp->next != NULL) {
		if(more_wins(item, temp->next->item) || (equals_wins(temp->next->item, item) && less_abc(item, temp->next->item))) {
			break;
		}

		if(temp->next->item == item) {
	    free(new);
	    return;
		}

    temp = temp->next;
  }
  new->next = temp->next;
  temp->next = new;
}

void removeNode(link* head, Item item) {
  link temp, temp2;
  if(*head == NULL) {
    return;
  }
  if(equals_abc(item, (*head)->item)) {
    temp = (*head)->next;
    free(*head);
    *head = temp;
    return;
  }
  temp = *head;
	if(temp->next == NULL) {
		return;
	}
  while(!equals_abc(temp->next->item, item)) {
    temp = temp->next;
		if(temp->next == NULL) {
			return;
		}
  }
  temp2 = temp->next;
  temp->next = temp2->next;
  free(temp2);
}

void deleteList(link* head) {
  link node = *head;
  link next;
  while (node != NULL) {
   next = node->next;
   free(node);
   node = next;
  }
  *head = NULL;
}
