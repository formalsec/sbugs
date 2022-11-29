#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "team.h"

orderedTeams * pushTeam(orderedTeams * head, Team * team) {
  /* if the game returned from the addGame function is NULL i.e wrong addGame() input, it doesn't add to the ordered list and return the unchanged list */
  if (team == NULL) {
    return head;
  }
  /* if it is a valid game, adds to the end of the list */
  else {
    orderedTeams * novo;
    orderedTeams * aux;
    orderedTeams * last;
    novo = can_fail_malloc(sizeof(orderedTeams));
    aux = last = head;
    /* if the list is not empty */
    if (aux == NULL) {
      novo->team = team;
      novo->next = NULL;
      return novo;
    }

    else {
      while (aux != NULL && (strcmp(aux->team->nome, team->nome)) < 0)  {
        last = aux;
        aux = aux->next;
      }
      if (aux == last) {
        novo->team = team;
        novo->next = aux;
        return novo;
      }
      else {
        last->next = novo;
        novo->team = team;
        novo->next = aux;
        return head;
      }
    }
  }
}

void printTeams(orderedTeams * head, int cmd_count, int maxWins) {
  orderedTeams * aux;
  if (head == NULL) {
    return;
  }
  printf("%d Melhores %d\n", cmd_count, maxWins);
  for (aux = head; aux != NULL; aux = aux->next) {  /* prints every team in the list */
    if (aux->team->wins == maxWins)
      printf("%d * %s\n", cmd_count, aux->team->nome);
  }
}

orderedTeams * destroyTeams(orderedTeams * head) {
  orderedTeams * novo = head;
  /* cycle until it reaches the end of the list */
  while (novo != NULL) {
    orderedTeams * aux = novo->next;
    free(novo);
    novo = aux;
  }
  return NULL;
}

void updateMaxWins(orderedTeams * head, int * maxWins) {
  orderedTeams * aux = head;
  (*maxWins) = 0;
  
  while (aux != NULL) {
    if (aux->team->wins > (*maxWins)) {
      (*maxWins) = aux->team->wins;
    }
    aux = aux->next;
  }
}
