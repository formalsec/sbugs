#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "dlist.h"
/* Cria uma node nova*/
node * new_node(int qtd, int prodId) {
  node * p = malloc(sizeof(node));
  if (!p) {
    perror("new_node: no memory for a new node");
    exit(EXIT_FAILURE);
  }
  p -> qtd = qtd;
  p -> prodId = prodId;
  p -> connection = NULL;
  p -> prev = NULL;
  p -> next = NULL;
  return p;
}
/* Adiciona uma nova node ao principio da lista */
node * push(struct node ** head_ref, int qtd, int prodId) {
  node * p = new_node(qtd, prodId);
  p -> next = ( * head_ref);
  if (( * head_ref) != NULL)
    ( * head_ref) -> prev = p;
  ( * head_ref) = p;
  return p;
}
/* Estabelece uma ligacao entre duas nodes de listas diferentes */
void set_connection(node * sender, node * receiver) {
  sender -> connection = receiver;
  receiver -> connection = sender;
}
/* Encontra na lista a node com o id */
node * find(node * head, int id) {
  node * current = head;
  while (current != NULL) {
    if (current -> prodId == id)
      return current;
    current = current -> next;
  }
  return NULL;
}
/* Elemina a node da lista */
void deleteNode(node ** head_ref, node * del) {
  if ( * head_ref == NULL || del == NULL)
    return;
  if ( * head_ref == del)
    * head_ref = del -> next;
  if (del -> next != NULL)
    del -> next -> prev = del -> prev;
  if (del -> prev != NULL)
    del -> prev -> next = del -> next;

  free(del);
  return;
}
/* Da free a todos os elementos da lista */
void free_dlist(node * head){
  if(!head)
    return;

  free_dlist(head->next);
  free(head);
}
