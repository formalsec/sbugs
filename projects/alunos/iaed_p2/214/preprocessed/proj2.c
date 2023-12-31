#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Teams
{
  char *name;
  int counterw;
} *Team;
typedef struct Games
{
  char *name;
  Team team1;
  char *score1;
  Team team2;
  char *score2;
} *Game;
typedef struct node
{
  Game g;
  struct node *next;
} *link;
typedef struct node1
{
  Team t;
  struct node1 *next;
} *link1;
int counter;
link addGame();
link insert();
link lookup();
Game createGame();
link1 addTeam();
link1 insertTeam();
link1 lookupT();
Team createTeam();
void listGames();
void printGame();
void searchGame();
void searchTeam();
void printTeam();
link deleteGame();
link delete();
void editScoreTeam();
void editGameScore();
void listBestTeams();
int countWonGames();
void printTeam2();
int hash();
void sortFrees();
void freeTable();
void freeList();
void freeNode();
void freeTableT();
void freeListT();
void freeNodeT();
int main()
{
  int c;
  int i;
  link *table;
  link1 *tablet;
  link linkedList = 0;
  link1 teamsList = 0;
  table = (link *) malloc((sizeof(link)) * 1009);
  for (i = 0; i < 1009; i++)
    table[i] = 0;

  tablet = (link1 *) malloc((sizeof(link1)) * 1009);
  for (i = 0; i < 1009; i++)
    tablet[i] = 0;

  while (1)
  {
    c = getchar();
    switch (c)
    {
      case 'a':
        linkedList = addGame(linkedList, table, tablet);
        break;

      case 'A':
        teamsList = addTeam(teamsList, tablet);
        break;

      case 'l':
        listGames(linkedList);
        break;

      case 'p':
        searchGame(table);
        break;

      case 'P':
        searchTeam(tablet);
        break;

      case 'r':
        linkedList = deleteGame(linkedList, table);
        break;

      case 's':
        editGameScore(table);
        break;

      case 'g':
        listBestTeams(teamsList);
        break;

      case 'x':
        sortFrees(linkedList, table, teamsList, tablet);
        return 0;

      default:
        break;

    }

    while (c != '\n')
      c = getchar();

  }

  return 1;
}

link addGame(link linkedList, link *table, link1 *tablet)
{
  char name[1024];
  char name1[1024];
  char name2[1024];
  char score1[3];
  char score2[3];
  char *nameg;
  char *team1;
  char *team2;
  char *scoret1;
  char *scoret2;
  int index;
  int index1;
  int index2;
  Game game;
  counter += 1;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  for (int name1_index = 0; name1_index < 10; name1_index++)
  {
    name1[name1_index] = new_sym_var(sizeof(char) * 8);
  }

  name1[10 - 1] = '\0';
  for (int name2_index = 0; name2_index < 10; name2_index++)
  {
    name2[name2_index] = new_sym_var(sizeof(char) * 8);
  }

  name2[10 - 1] = '\0';
  for (int score1_index = 0; score1_index < 3; score1_index++)
  {
    score1[score1_index] = new_sym_var(sizeof(char) * 8);
  }

  score1[3 - 1] = '\0';
  for (int score2_index = 0; score2_index < 3; score2_index++)
  {
    score2[score2_index] = new_sym_var(sizeof(char) * 8);
  }

  score2[3 - 1] = '\0';
  index = hash(name);
  index1 = hash(name1);
  index2 = hash(name2);
  if (lookup(table[index], name) != 0)
  {
    printf("%d %s\n", counter, "Jogo existente.");
    return linkedList;
  }
  else
  {
    if ((lookupT(tablet[index1], name1) == 0) || (lookupT(tablet[index2], name2) == 0))
    {
      printf("%d %s\n", counter, "Equipa inexistente.");
      return linkedList;
    }
    else
    {
      
    }

  }

  nameg = (char *) malloc(((sizeof(char)) * strlen(name)) + 1);
  strcpy(nameg, name);
  team1 = (char *) malloc(((sizeof(char)) * strlen(name1)) + 1);
  strcpy(team1, name1);
  team2 = (char *) malloc(((sizeof(char)) * strlen(name2)) + 1);
  strcpy(team2, name2);
  scoret1 = (char *) malloc(((sizeof(char)) * strlen(score1)) + 1);
  strcpy(scoret1, score1);
  scoret2 = (char *) malloc(((sizeof(char)) * strlen(score2)) + 1);
  strcpy(scoret2, score2);
  game = createGame(nameg, team1, team2, scoret1, scoret2, tablet);
  table[index] = insert(table[index], game);
  linkedList = insert(linkedList, game);
  free(team1);
  free(team2);
  return linkedList;
}

Game createGame(char *name, char *name1, char *name2, char *scoret1, char *scoret2, link1 *tablet)
{
  int index;
  int index2;
  Game game;
  link1 n1;
  link1 n2;
  index = hash(name1);
  index2 = hash(name2);
  n1 = lookupT(tablet[index], name1);
  n2 = lookupT(tablet[index2], name2);
  game = (Game) malloc(sizeof(struct Games));
  game->name = name;
  game->team1 = n1->t;
  game->score1 = scoret1;
  game->team2 = n2->t;
  game->score2 = scoret2;
  if ((n1 != 0) && (n2 != 0))
  {
    if (atoi(scoret1) > atoi(scoret2))
    {
      n1->t->counterw += 1;
    }
    else
    {
      if (atoi(scoret1) < atoi(scoret2))
      {
        n2->t->counterw += 1;
      }
      else
      {
        
      }

    }

  }
  else
  {
    
  }

  return game;
}

link1 addTeam(link1 teamsList, link1 *tablet)
{
  char name[1024];
  char *team1;
  int index;
  Team team;
  counter += 1;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  index = hash(name);
  if (lookup(tablet[index], name) != 0)
  {
    printf("%d %s\n", counter, "Equipa existente.");
    return teamsList;
  }
  else
  {
    
  }

  team1 = (char *) malloc(((sizeof(char)) * strlen(name)) + 1);
  strcpy(team1, name);
  team = createTeam(team1);
  tablet[index] = insertTeam(tablet[index], team);
  teamsList = insertTeam(teamsList, team);
  return teamsList;
}

Team createTeam(char *name)
{
  Team team;
  team = (Team) malloc(sizeof(struct Teams));
  team->name = name;
  team->counterw = 0;
  return team;
}

void listGames(link n)
{
  if (n == 0)
  {
    counter += 1;
    return;
  }
  else
  {
    listGames(n->next);
    printGame(n->g);
  }

}

void listBestTeams(link1 n)
{
  if (n == 0)
  {
    counter += 1;
    return;
  }
  else
  {
    int c;
    link1 t;
    counter += 1;
    c = countWonGames(n);
    printf("%d Melhores %d\n", counter, c);
    for (t = n; t != 0; t = t->next)
    {
      if (t->t->counterw == c)
      {
        printTeam2(t->t);
      }
      else
      {
        
      }

    }

  }

}

int countWonGames(link1 n)
{
  link1 t;
  int max = 0;
  int lastmax = 0;
  for (t = n; t != 0; t = t->next)
  {
    max = t->t->counterw;
    if (max > lastmax)
    {
      lastmax = max;
    }
    else
    {
      
    }

  }

  return lastmax;
}

void searchGame(link *table)
{
  char name[1024];
  link n;
  int index;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  counter += 1;
  index = hash(name);
  n = lookup(table[index], name);
  if (n == 0)
  {
    printf("%d %s\n", counter, "Jogo inexistente.");
    return;
  }
  else
  {
    
  }

  printGame(n->g);
}

void searchTeam(link1 *tablet)
{
  char name[1024];
  int index;
  link1 n;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  counter += 1;
  index = hash(name);
  n = lookupT(tablet[index], name);
  if (n == 0)
  {
    printf("%d %s\n", counter, "Equipa inexistente.");
    return;
  }
  else
  {
    
  }

  printTeam(n->t);
}

void printGame(Game g)
{
  printf("%d %s %s %s %s %s\n", counter, g->name, g->team1->name, g->team2->name, g->score1, g->score2);
}

void printTeam(Team t)
{
  printf("%d %s %d\n", counter, t->name, t->counterw);
}

void printTeam2(Team t)
{
  printf("%d * %s\n", counter, t->name);
}

link deleteGame(link linkedList, link *table)
{
  link n;
  char name[1024];
  int index;
  counter += 1;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  index = hash(name);
  n = lookup(table[index], name);
  if (n == 0)
  {
    printf("%d %s\n", counter, "Jogo inexistente.");
    return linkedList;
  }
  else
  {
    
  }

  if (atoi(n->g->score1) > atoi(n->g->score2))
  {
    n->g->team1->counterw -= 1;
  }
  else
  {
    
  }

  if (atoi(n->g->score1) < atoi(n->g->score2))
  {
    n->g->team2->counterw -= 1;
  }
  else
  {
    
  }

  linkedList = delete(linkedList, name, 0);
  table[index] = delete(table[index], name, 1);
  return linkedList;
}

link delete(link head, const char *name, int freesGame)
{
  link t;
  link prev = 0;
  for (t = head, prev = 0; t != 0; prev = t, t = t->next)
    if (strcmp(t->g->name, name) == 0)
  {
    if (t == head)
    {
      head = head->next;
    }
    else
    {
      prev->next = t->next;
    }

    if (freesGame)
    {
      freeNode(t, 1);
    }
    else
    {
      free(t);
    }

    return head;
  }
  else
  {
    
  }


  return 0;
}

void editGameScore(link *table)
{
  char name[1024];
  char score1[3];
  char score2[3];
  char *scoret1;
  char *scoret2;
  int index;
  link n;
  counter += 1;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  for (int score1_index = 0; score1_index < 3; score1_index++)
  {
    score1[score1_index] = new_sym_var(sizeof(char) * 8);
  }

  score1[3 - 1] = '\0';
  for (int score2_index = 0; score2_index < 3; score2_index++)
  {
    score2[score2_index] = new_sym_var(sizeof(char) * 8);
  }

  score2[3 - 1] = '\0';
  index = hash(name);
  n = lookup(table[index], name);
  if (n == 0)
  {
    printf("%d %s\n", counter, "Jogo inexistente.");
    return;
  }
  else
  {
    
  }

  if (atoi(n->g->score1) > atoi(n->g->score2))
  {
    n->g->team1->counterw--;
  }
  else
  {
    
  }

  if (atoi(n->g->score2) > atoi(n->g->score1))
  {
    n->g->team2->counterw--;
  }
  else
  {
    
  }

  scoret1 = (char *) malloc(((sizeof(char)) * strlen(score1)) + 1);
  ;
  strcpy(scoret1, score1);
  scoret2 = (char *) malloc(((sizeof(char)) * strlen(score2)) + 1);
  ;
  strcpy(scoret2, score2);
  n->g->score1 = realloc(n->g->score1, ((sizeof(char)) * strlen(scoret1)) + 1);
  strcpy(n->g->score1, scoret1);
  n->g->score2 = realloc(n->g->score2, ((sizeof(char)) * strlen(scoret2)) + 1);
  strcpy(n->g->score2, scoret2);
  if (atoi(n->g->score1) > atoi(n->g->score2))
  {
    n->g->team1->counterw++;
  }
  else
  {
    if (atoi(n->g->score2) > atoi(n->g->score1))
    {
      n->g->team2->counterw++;
    }
    else
    {
      
    }

  }

  free(scoret1);
  free(scoret2);
}

int hash(const char *v)
{
  int h;
  int a = 127;
  for (h = 0; (*v) != '\0'; v++)
    h = ((a * h) + (*v)) % 1009;

  return h;
}

link insert(link head, Game g)
{
  link newNode = (link) malloc(sizeof(struct node));
  newNode->g = g;
  newNode->next = head;
  return newNode;
}

link1 insertTeam(link1 head, Team t)
{
  link1 n;
  link1 temp;
  link1 newNode1 = (link1) malloc(sizeof(struct node1));
  newNode1->t = t;
  if (head == 0)
  {
    newNode1->next = 0;
    return newNode1;
  }
  else
  {
    if (head->next == 0)
    {
      if (strcmp(head->t->name, t->name) < 0)
      {
        head->next = newNode1;
        newNode1->next = 0;
        return head;
      }
      else
      {
        head->next = 0;
        newNode1->next = head;
        head = newNode1;
        return head;
      }

    }
    else
    {
      
    }

    for (n = head; n->next != 0; n = n->next)
    {
      if (strcmp(n->t->name, t->name) > 0)
      {
        temp = n;
        n = newNode1;
        newNode1->next = temp;
        if (n->next == head)
        {
          head = newNode1;
        }
        else
        {
          
        }

        return head;
      }
      else
      {
        if ((strcmp(n->t->name, t->name) < 0) && (strcmp(n->next->t->name, t->name) > 0))
        {
          temp = n->next;
          n->next = newNode1;
          newNode1->next = temp;
          return head;
        }
        else
        {
          
        }

      }

    }

    n->next = newNode1;
    newNode1->next = 0;
    return head;
  }

}

link lookup(link head, const char *name)
{
  link t;
  for (t = head; t != 0; t = t->next)
    if (strcmp(t->g->name, name) == 0)
  {
    return t;
  }
  else
  {
    
  }


  return 0;
}

link1 lookupT(link1 head, const char *name)
{
  link1 t;
  for (t = head; t != 0; t = t->next)
    if (strcmp(t->t->name, name) == 0)
  {
    return t;
  }
  else
  {
    
  }


  return 0;
}

void sortFrees(link linkedList, link *table, link1 teamsList, link1 *tablet)
{
  freeTable(table);
  freeList(linkedList, 1);
  freeTableT(tablet);
  freeListT(teamsList, 1);
}

void freeTable(link *table)
{
  int i;
  for (i = 0; i < 1009; i++)
    freeList(table[i], 0);

  free(table);
}

void freeTableT(link1 *tablet)
{
  int i;
  for (i = 0; i < 1009; i++)
    freeListT(tablet[i], 0);

  free(tablet);
}

void freeList(link n, int g)
{
  if (n == 0)
  {
    return;
  }
  else
  {
    
  }

  freeList(n->next, g);
  freeNode(n, g);
}

void freeListT(link1 n, int t)
{
  if (n == 0)
  {
    return;
  }
  else
  {
    
  }

  freeListT(n->next, t);
  freeNodeT(n, t);
}

void freeNode(link t, int g)
{
  if (g)
  {
    free(t->g->score2);
    free(t->g->score1);
    free(t->g->name);
    free(t->g);
  }
  else
  {
    
  }

  free(t);
}

void freeNodeT(link1 t, int t1)
{
  if (t1)
  {
    free(t->t->name);
    free(t->t);
  }
  else
  {
    
  }

  free(t);
}

