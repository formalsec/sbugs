#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hashtable.h"
#include "Linkedlist.h"

/* Max number of characters in the command */
#define MAX_CMD 3076
/* Max number of matches in the system */
#define MAX_MATCHES 101
/* Max number of teams in the system */
#define MAX_TEAMS 29

/* counter for number of commands received */
int NL = 0;

/* adds match to the matches hash_table and updates record of the winning team.
   also updates the 2 linkedlists accordingly */
void addMatch(hash_table* matches, hash_table* teams, link* ordered_matches, link* ordered_teams, char* command);

/* adds team to the teams hash_table and to the tail of the ordered_teams
   linkedlist */
void addTeam(hash_table* teams, link* ordered_teams, char* command);

/* lists matches in the order they were submitted, making use of the
   ordered_matches linkedlist */
void listMatches(link ordered_matches);

/* searches for a match in the matches hash_table, printing it */
void searchMatch(hash_table* matches, char* command);

/* searches for a team in the teams hash_table, printing it */
void searchTeam(hash_table* teams, char* command);

/* removes match from the matches hash_table and from the ordered_matches
   linkedlist. also updates the respective teams' record and their position in
   the ordered_teams linkedlist */
void removeMatch(hash_table* matches, hash_table* teams, link* ordered_matches, link* ordered_teams, char* command);

/* changes the score of a match, updating the respective team's record and their
   position in the ordered_teams linkedlist accordingly */
void changeScore(hash_table* matches, hash_table* teams, link* ordered_teams, char* command);

/* grabs the teams with the most wins from the ordered_teams linkedlist */
void getTopTeams(link ordered_teams);

/* receives commands from stdin, and using the 1st character in it,
   which function to execute */
int main() {
  char command[MAX_CMD];
  hash_table *matches = hash_table_init(MAX_MATCHES);
  hash_table *teams = hash_table_init(MAX_TEAMS);
  link ordered_teams = NULL;
  link ordered_matches = NULL;

  while(1) {
    fgets(command, MAX_CMD, stdin);
    NL++;
    switch(command[0]) {
      case 'a':
        addMatch(matches, teams, &ordered_matches, &ordered_teams, command);
        break;
      case 'A':
        addTeam(teams, &ordered_teams, command);
        break;
      case 'l':
        listMatches(ordered_matches);
        break;
      case 'p':
        searchMatch(matches, command);
        break;
      case 'P':
        searchTeam(teams, command);
        break;
      case 'r':
        removeMatch(matches, teams, &ordered_matches, &ordered_teams, command);
        break;
      case 's':
        changeScore(matches, teams, &ordered_teams, command);
        break;
      case 'g':
        getTopTeams(ordered_teams);
        break;
      case 'x':
        deleteList(&ordered_teams);
        deleteList(&ordered_matches);
        hash_table_free(matches);
        hash_table_free(teams);
        return EXIT_SUCCESS;
      default:
        printf("ERROR: Unknown command\n");
    }
  }

  return EXIT_FAILURE;
}

/* Implementation of functions */

void addMatch(hash_table* matches, hash_table* teams, link* ordered_matches, link* ordered_teams, char* command) {
  char *token, *name, *team1, *team2;
  int score1, score2;
  Item item, item1, item2;
  Team team;

  token = strtok(command, " ");
  name = token = strtok(NULL, ":");
  if((hash_table_search(matches, name)) != NULL) {
    printf("%d Jogo existente.\n", NL);
    return;
  }
  team1 = token = strtok(NULL, ":");
  if((item1 = (hash_table_search(teams, team1))) == NULL) {
    printf("%d Equipa inexistente.\n", NL);
    return;
  }
  team2 = token = strtok(NULL, ":");
  if((item2 = (hash_table_search(teams, team2))) == NULL) {
    printf("%d Equipa inexistente.\n", NL);
    return;
  }
  score1 = atoi(token = strtok(NULL, ":"));
  score2 = atoi(token = strtok(NULL, "\n"));

  item = newMatch(name, team1, team2, score1, score2);

  hash_table_insert(matches, item);
  insertEnd(ordered_matches, item);

  if(score1 > score2) {
    team = item1->content;
    team->record++;
    removeNode(ordered_teams, item1);
    insertSorted(ordered_teams, item1);
  }
  else if (score2 > score1) {
    team = item2->content;
    team->record++;
    removeNode(ordered_teams, item2);
    insertSorted(ordered_teams, item2);
  }
}

void addTeam(hash_table* teams, link* ordered_teams, char* command) {
  char *token, *name;
  Item item;

  token = strtok(command, " ");
  name = token = strtok(NULL, "\n");
  if((hash_table_search(teams, name)) != NULL) {
    printf("%d Equipa existente.\n", NL);
    return;
  }
  else {
    item = newTeam(name);
    hash_table_insert(teams, item);
    insertSorted(ordered_teams, item);
  }
}

void listMatches(link ordered_matches) {
  link node = ordered_matches;
  while(node != NULL) {
    printf("%d ", NL);
    printItem(node->item);
    node = node->next;
  }
}

void searchMatch(hash_table* matches, char* command) {
  char *token, *name;
  Item item;

  token = strtok(command, " ");
  name = token = strtok(NULL, "\n");
  if((item = (hash_table_search(matches, name))) == NULL) {
    printf("%d Jogo inexistente.\n", NL);
    return;
  }
  else {
    printf("%d ", NL);
    printItem(item);
  }
}

void searchTeam(hash_table* teams, char* command) {
  char *token, *name;
  Item item;

  token = strtok(command, " ");
  name = token = strtok(NULL, "\n");

  if((item = hash_table_search(teams, name)) == NULL) {
    printf("%d Equipa inexistente.\n", NL);
  }
  else {
    printf("%d ", NL);
    printItem(item);
  }
}

void removeMatch(hash_table* matches, hash_table* teams, link* ordered_matches, link* ordered_teams, char* command) {
  char *token, *name;
  Item item, item_team;
  Match match;
  Team team;

  token = strtok(command, " ");
  name = token = strtok(NULL, "\n");
  if((item = (hash_table_search(matches, name))) == NULL) {
    printf("%d Jogo inexistente.\n", NL);
    return;
  }
  else {
    item = hash_table_remove(matches, name);
    removeNode(ordered_matches, item);
    match = item->content;
    if(match->score1 != match->score2) {
      if(match->score1 > match->score2) {
        item_team = hash_table_search(teams, match->team1);
        team = item_team->content;
      }
      else if(match->score2 > match->score1) {
        item_team = hash_table_search(teams, match->team2);
        team = item_team->content;
      }
      team->record--;
      removeNode(ordered_teams, item_team);
      insertSorted(ordered_teams, item_team);
    }
    freeItem(item);
  }
}

void changeScore(hash_table* matches, hash_table* teams, link* ordered_teams, char* command) {
  char *token, *name;
  int score1, score2;
  Item item;
  Match match;
  Team team;;

  token = strtok(command, " ");
  name = token = strtok(NULL, ":");
  if((item = (hash_table_search(matches, name))) == NULL) {
    printf("%d Jogo inexistente.\n", NL);
    return;
  }
  else {
    score1 = atoi(token = strtok(NULL, ":"));
    score2 = atoi(token = strtok(NULL, "\n"));
    match = item->content;
    if(match->score1 != match->score2) {
      if(match->score1 > match->score2) {
        item = hash_table_search(teams, match->team1);
        team = item->content;
      }
      else if(match->score2 > match->score1) {
        item = hash_table_search(teams, match->team2);
        team = item->content;
      }
      team->record--;
      removeNode(ordered_teams, item);
      insertSorted(ordered_teams, item);
    }
    match->score1 = score1;
    match->score2 = score2;

    if(score1 > score2) {
      item = hash_table_search(teams, match->team1);
      team = item->content;
      team->record++;
      removeNode(ordered_teams, item);
      insertSorted(ordered_teams, item);
    }
    else if(score2 > score1) {
      item = hash_table_search(teams, match->team2);
      team = item->content;
      team->record++;
      removeNode(ordered_teams, item);
      insertSorted(ordered_teams, item);
    }
  }
}

void getTopTeams(link ordered_teams) {
  link node = ordered_teams;
  link next;
  Item item;
  Team team;
  if(node != NULL) {
    item = node->item;
    team = item->content;
    printf("%d Melhores %d\n", NL, team->record);
  }
  while(node != NULL) {
    printf("%d * ", NL);
    printItemName(node->item);
    next = node->next;
    if(next == NULL || !(equals_wins(next->item, node->item))) {
      return;
    }
    node = next;
  }
}
