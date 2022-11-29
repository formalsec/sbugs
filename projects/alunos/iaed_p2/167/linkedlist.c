#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "linkedlist.h"
/* ============================================================ */
node * ListDelete(node *head, char *string)
{
  if (head == NULL)
    { return NULL; }
  if (strcmp(head->name, string) == 0)
  {
    node *new_head;    
    new_head = head->next;    
    free(head->name);
    free(head->team1);
    free(head->team2);
    free(head);
    return new_head;
  }
  head->next = ListDelete(head->next, string);
  return head;
}
/* ============================================================ */
node * AddElement(node *head, char *name, char *team1, char *team2, int score1, int score2)
{
    node * new_head;
    new_head = (node *) can_fail_malloc(sizeof(node));
    new_head->next = head;
    new_head->name = d_strdup(name);
    new_head->team1 = d_strdup(team1);
    new_head->team2 = d_strdup(team2);
    new_head->score1 = score1;
    new_head->score2 = score2;
    head = new_head;
    return head;
}
/* ============================================================ */
node * DestroyList(node *head)
{
    node *aux_head;
    while (head != NULL)
    {
        aux_head = head;
        head = head->next;
        free(aux_head->name);
        free(aux_head->team1);
        free(aux_head->team2);
        free(aux_head);
    }
    return head;
}
/* ============================================================ */
node * SearchLL(node*head, char *name)
{
    node *new_head = head;
    while (strcmp(new_head->name, name) != 0)
    { new_head = new_head->next; }
    return new_head;
}