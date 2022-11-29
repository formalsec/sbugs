#ifndef DLIST_H
#define DLIST_H

typedef struct node{
  int qtd;
  int prodId;
  struct node * connection;
  struct node * prev;
  struct node * next;
} node;

node * push(struct node ** head_ref, int qtd, int prodId);
void set_connection(node * sender, node * receiver);
void deleteNode(node ** head_ref,node * del);
node * find(node * head, int id);
void free_dlist(node * head);


#endif /* BST_H */
