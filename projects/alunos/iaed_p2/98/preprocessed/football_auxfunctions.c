#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "football_auxfunctions.h"


int hash(char *v, int M)
{
  int h = 0;
  int a = 127;
  for (; (*v) != '\0'; v++)
    h = ((a * h) + (*v)) % M;

  return h;
}

Game createGame(char name[], char team1[], char team2[], int score1, int score2)
{
  Game x = malloc(sizeof(struct stru_Game));
  x->name = strdup(name);
  x->team1 = strdup(team1);
  x->team2 = strdup(team2);
  x->score1 = score1;
  x->score2 = score2;
  return x;
}

void insertGameList(Game item, List_Limits headAndTail)
{
  Game_Link x = malloc(sizeof(struct node_G));
  x->item = item;
  x->next = 0;
  if (headAndTail->head == 0)
  {
    x->prev = 0;
    headAndTail->head = x;
  }
  else
  {
    x->prev = headAndTail->tail;
    headAndTail->tail->next = x;
  }

  headAndTail->tail = x;
}

void insertGameTable(Game item, Game_Link *heads)
{
  Game_Link x;
  int i = hash(item->name, 1049);
  x = malloc(sizeof(struct node_G));
  x->item = item;
  x->prev = 0;
  if (heads[i] != 0)
  {
    heads[i]->prev = x;
    x->next = heads[i];
  }
  else
  {
    x->next = 0;
  }

  heads[i] = x;
}

void freeGameAux(Game x)
{
  free(x->name);
  free(x->team1);
  free(x->team2);
  free(x);
}

void freeGame(Game item, int i, Game_Link *headsG, List_Limits headAndTail)
{
  Game_Link t1;
  Game_Link t2;
  Game_Link s1;
  Game_Link s2;
  if (headsG[i]->item == item)
  {
    t1 = headsG[i];
    headsG[i] = t1->next;
    if (headsG[i] != 0)
    {
      headsG[i]->prev = 0;
    }
    else
    {
      
    }

  }
  else
  {
    for (t1 = headsG[i]->next; t1 != 0; t1 = t1->next)
    {
      if (t1->item == item)
      {
        s1 = t1->prev;
        s1->next = t1->next;
        if (t1->next != 0)
        {
          s1 = t1->next;
          s1->prev = t1->prev;
        }
        else
        {
          
        }

        break;
      }
      else
      {
        
      }

    }

  }

  if (headAndTail->head == headAndTail->tail)
  {
    t2 = headAndTail->head;
    headAndTail->head = 0;
    headAndTail->tail = 0;
  }
  else
  {
    if (headAndTail->head->item == item)
    {
      t2 = headAndTail->head;
      headAndTail->head = t2->next;
      headAndTail->head->prev = 0;
    }
    else
    {
      if (headAndTail->tail->item == item)
      {
        t2 = headAndTail->tail;
        headAndTail->tail = t2->prev;
        headAndTail->tail->next = 0;
      }
      else
      {
        for (t2 = headAndTail->head->next; t2 != 0; t2 = t2->next)
          if (t2->item == item)
        {
          s2 = t2->prev;
          s2->next = t2->next;
          if (t2->next != 0)
          {
            s2 = t2->next;
            s2->prev = t2->prev;
          }
          else
          {
            
          }

          break;
        }
        else
        {
          
        }


      }

    }

  }

  freeGameAux(t1->item);
  free(t1);
  free(t2);
}

Game searchGame(char name[], Game_Link *heads)
{
  Game_Link t;
  char *pname = strdup(name);
  int i = hash(pname, 1049);
  for (t = heads[i]; t != 0; t = t->next)
    if (strcmp(t->item->name, pname) == 0)
  {
    free(pname);
    return t->item;
  }
  else
  {
    
  }


  free(pname);
  return 0;
}

Team createTeam(char name[])
{
  Team x = malloc(sizeof(struct stru_Team));
  x->name = strdup(name);
  x->victories = 0;
  return x;
}

void insertTeam(Team item, Team_Link *heads)
{
  Team_Link x = malloc(sizeof(struct node_G));
  int i = hash(item->name, 1049);
  x->item = item;
  x->next = heads[i];
  heads[i] = x;
}

Team searchTeam(char name[], Team_Link *heads)
{
  Team_Link t;
  char *pname = strdup(name);
  int i = hash(pname, 1049);
  for (t = heads[i]; t != 0; t = t->next)
    if (strcmp(t->item->name, pname) == 0)
  {
    free(pname);
    return t->item;
  }
  else
  {
    
  }


  free(pname);
  return 0;
}

