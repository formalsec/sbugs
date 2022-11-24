#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "game.h"
#include "hash.h"

orderedGames * removeGame(ht * game_ht, int cmd_count, orderedGames * head) {
  char buffer[MAX_CHAR];
  entry * entrie;
  entry * prev;
  int key, idx;
  idx = 0;

  scanf(" %[^\n]", buffer);

  key = hash(buffer);
  entrie = game_ht->entries[key];
  /* if theres nothing in the entrie the game doesn't exist */
  if (entrie == NULL) {
    printf ("%d Jogo inexistente.\n", cmd_count);
    return head;
  }

  if (searchGame(entrie, buffer)) {
    /* removes the game from the ordered games list*/
    orderedGames * aux, *prevv;
    for (aux = head, prevv = NULL; aux != NULL; prevv = aux, aux = aux->next) {
      if (strcmp(aux->game->gameName, buffer) == 0) {
        if (aux == head) {
          head = aux->next;
        }
        else {
          prevv->next = aux->next;
        }
        free(aux);
        break;
      }
    }
    /* removes the game from the hashtable */
    while (entrie != NULL) {
      /* cycle trough the entrie in case theres collision */
      if (strcmp(entrie->game->gameName, buffer) == 0) {

        if (entrie->next == NULL && idx == 0) {
          game_ht->entries[key] = NULL;
        }

        if (entrie->next != NULL && idx == 0) {
          game_ht->entries[key] = entrie->next;
        }

        if (entrie->next == NULL && idx != 0) {
          prev->next = NULL;
        }

        if (entrie->next != NULL && idx != 0) {
          prev->next = entrie->next;
        }

        if (entrie->game->score1 > entrie->game->score2) {
            entrie->game->t1->wins--;
        }

        else if (entrie->game->score2 > entrie->game->score1) {
          entrie->game->t2->wins--;
        }

        free(entrie->game->gameName);
        free(entrie->game);
        free(entrie);
        return head;
      }

      prev = entrie;
      entrie = prev->next;

      ++idx;

    }
  }
  else {
    printf("%d Jogo inexistente.\n", cmd_count);
    return head;
  }
  return head;
}


orderedGames * push(orderedGames * head, Game * game) {
  /* if the game returned from the addGame function is NULL i.e wrong addGame() input, it doesn't add to the ordered list and return the unchanged list */
  if (game == NULL) {
    return head;
  }
  /* if it is a valid game, adds to the end of the list */
  else {
    orderedGames * novo;
    orderedGames * aux;
    novo = can_fail_malloc(sizeof(orderedGames));
    aux = head;
    /* if the list is not empty */
    if (aux != NULL) {
      while (aux->next != NULL) {
        aux = aux->next;
      }
    }
    /* if the list is empty */
    else {
      novo->game = game;
      novo->next = NULL;
      return novo;
    }
    aux->next = novo;
    novo->game = game;
    novo->next = NULL;
    return head;
  }
}

/* function that frees all orderedGames nodes in the end of the program so theres no memory leak */
orderedGames * destroy(orderedGames * head) {
  orderedGames * novo = head;
  /* cycle until it reaches the end of the list */
  while (novo != NULL) {
    orderedGames * aux = novo->next;
    free(novo);
    novo = aux;
  }
  return NULL;
}

void print(orderedGames * head, int cmd_count) {
  orderedGames * aux;
  for (aux = head; aux != NULL; aux = aux->next) {
    if (aux->game != NULL && aux->game->gameName != NULL) {
        printf("%d %s %s %s %d %d\n", cmd_count, aux->game->gameName, aux->game->t1->nome, aux->game->t2->nome, aux->game->score1, aux->game->score2);
    }
  }
}
