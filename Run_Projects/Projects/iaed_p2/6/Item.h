#ifndef _ITEMH_
#define _ITEMH_

struct Item {
  char* name;
  void* content;
  int type;
};

typedef struct Item* Item;

struct Team {
  int record;
};

typedef struct Team* Team;

struct Match {
  char* team1;
  char* team2;
  int score1;
  int score2;
};

typedef struct Match* Match;

typedef char* Key;
#define key(a) (a->name)

void freeItem(Item item);
void freeMatch(Match match);
Item newTeam(char *name);
Item newMatch(char *name, char *team1, char *team2, int s1, int s2);
void printItem(Item item);
void printItemName(Item item);
int less_abc(Item item1, Item item2);
int equals_abc(Item item1, Item item2);
int more_wins(Item item1, Item item2);
int equals_wins(Item item1, Item item2);

#endif
