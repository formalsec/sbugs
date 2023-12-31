#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"

void freeItem(Item item) {
  if(item->type == 1) {
    Match match = item->content;
    free(match->team1);
    free(match->team2);
  }
  free(item->content);
  free(item->name);
  free(item);
}

Item newTeam(char *name) {
  Item new = (Item)can_fail_malloc(sizeof(struct Item));
  Team team = (Team)can_fail_malloc(sizeof(struct Team));
  new->name = can_fail_malloc(strlen(name) + 1);
  strcpy(new->name, name);
  new->type = 0;
  team->record = 0;
  new->content = team;
  return new;
}

Item newMatch(char *name, char *team1, char *team2, int s1, int s2) {
  Item new = (Item)can_fail_malloc(sizeof(struct Item));
  Match match = (Match)can_fail_malloc(sizeof(struct Match));
  new->type = 1;
  new->name = can_fail_malloc(strlen(name) + 1);
  strcpy(new->name, name);
  match->team1 = can_fail_malloc(strlen(team1) + 1);
  strcpy(match->team1, team1);
  match->team2 = can_fail_malloc(strlen(team2) + 1);
  strcpy(match->team2, team2);
  match->score1 = s1;
  match->score2 = s2;
  new->content = match;
  return new;
}

void printItem(Item item) {
  if(item->type == 0) {
    Team team = item->content;
    printf("%s %d\n", item->name, team->record);
  }
  else if(item->type == 1) {
    Match match = item->content;
    printf("%s %s %s %d %d\n", item->name, match->team1, match->team2, match->score1, match->score2);
  }
}

void printItemName(Item item) {
  printf("%s\n", item->name);
}

int less_abc(Item item1, Item item2) {
  return (strcmp(item1->name, item2->name) < 0) ? 1 : 0;
}

int equals_abc(Item item1, Item item2) {
  return (strcmp(item1->name, item2->name) == 0) ? 1 : 0;
}

int more_wins(Item item1, Item item2) {
  Team team1 = item1->content;
  Team team2 = item2->content;
  return (team1->record > team2->record) ? 1 : 0;
}

int equals_wins(Item item1, Item item2) {
  Team team1 = item1->content;
  Team team2 = item2->content;
  return (team1->record == team2->record) ? 1 : 0;
}
