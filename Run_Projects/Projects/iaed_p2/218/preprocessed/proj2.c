/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct Game
{
  char *name;
  char *team1;
  char *team2;
  int team1Score;
  int team2Score;
} Game;
struct Team
{
  char *name;
  int winCount;
} Team;
struct gNode
{
  struct Game *value;
  struct gNode *hashNext;
  struct gNode *chronoNext;
  struct gNode *chronoPrev;
} gNode;
struct tNode
{
  struct Team *value;
  struct tNode *next;
} tNode;
int NL;
struct gNode *Games[1019];
struct tNode *Teams[1019];
struct gNode *ChronoHead;
struct gNode *ChronoTail;
int hash(char *toBeHashed)
{
  int i = 0;
  while ((*toBeHashed) != '\0')
  {
    i += ((*toBeHashed) - 'a') % 26;
    toBeHashed++;
  }

  return (i >= 0) ? (i % 1019) : (((-1) * i) % 1019);
}

void initialiseHashTables()
{
  int i;
  for (i = 0; i < 1019; ++i)
  {
    Games[i] = 0;
    Teams[i] = 0;
  }

}

void addWin(char *teamName)
{
  struct tNode *tHeadCopy;
  int index = hash(teamName);
  for (tHeadCopy = Teams[index]; tHeadCopy != 0; tHeadCopy = tHeadCopy->next)
  {
    if (strcmp(tHeadCopy->value->name, teamName) == 0)
    {
      tHeadCopy->value->winCount++;
    }
    else
    {
      
    }

  }

}

void removeWin(char *teamName)
{
  struct tNode *tHeadCopy;
  int index = hash(teamName);
  for (tHeadCopy = Teams[index]; tHeadCopy != 0; tHeadCopy = tHeadCopy->next)
  {
    if (strcmp(tHeadCopy->value->name, teamName) == 0)
    {
      tHeadCopy->value->winCount--;
    }
    else
    {
      
    }

  }

}

void addGame(char command[])
{
  char delim[2] = ":";
  struct gNode *head;
  struct tNode *tHead;
  int gameExists = 0;
  int teamExists1 = 0;
  int teamExists2 = 0;
  char *token;
  int index;
  int tIndex1;
  int tIndex2;
  struct gNode *newptr = malloc(sizeof(gNode));
  struct Game *temp = malloc(sizeof(Game));
  token = strtok(command, delim);
  temp->name = malloc((sizeof(char)) * (strlen(token) + 1));
  strcpy(temp->name, token);
  token = strtok(0, delim);
  temp->team1 = malloc((sizeof(char)) * (strlen(token) + 1));
  strcpy(temp->team1, token);
  token = strtok(0, delim);
  temp->team2 = malloc((sizeof(char)) * (strlen(token) + 1));
  strcpy(temp->team2, token);
  token = strtok(0, delim);
  temp->team1Score = strtol(token, 0, 10);
  token = strtok(0, delim);
  temp->team2Score = strtol(token, 0, 10);
  newptr->value = temp;
  newptr->hashNext = 0;
  newptr->chronoNext = 0;
  newptr->chronoPrev = 0;
  index = hash(newptr->value->name);
  tIndex1 = hash(newptr->value->team1);
  tIndex2 = hash(newptr->value->team2);
  if ((Teams[tIndex1] == 0) || (Teams[tIndex2] == 0))
  {
    teamExists1 = 0;
    teamExists2 = 0;
  }
  else
  {
    for (tHead = Teams[tIndex1]; tHead != 0; tHead = tHead->next)
    {
      if (strcmp(tHead->value->name, newptr->value->team1) == 0)
      {
        teamExists1 = 1;
      }
      else
      {
        
      }

    }

    for (tHead = Teams[tIndex2]; tHead != 0; tHead = tHead->next)
    {
      if (strcmp(tHead->value->name, newptr->value->team2) == 0)
      {
        teamExists2 = 1;
      }
      else
      {
        
      }

    }

  }

  for (head = Games[index]; head != 0; head = head->hashNext)
  {
    if (strcmp(head->value->name, newptr->value->name) == 0)
    {
      gameExists = 1;
    }
    else
    {
      
    }

  }

  if (gameExists == 1)
  {
    printf("%d %s\n", NL, "Jogo existente.");
    free(newptr);
    free(temp->name);
    free(temp->team1);
    free(temp->team2);
    free(temp);
  }
  else
  {
    if ((teamExists1 == 0) || (teamExists2 == 0))
    {
      printf("%d %s\n", NL, "Equipa inexistente.");
      free(newptr);
      free(temp->name);
      free(temp->team1);
      free(temp->team2);
      free(temp);
    }
    else
    {
      if (Games[index] == 0)
      {
        Games[index] = newptr;
        if (ChronoHead == 0)
        {
          if (newptr->value->team1Score > newptr->value->team2Score)
          {
            addWin(newptr->value->team1);
          }
          else
          {
            if (newptr->value->team1Score < newptr->value->team2Score)
            {
              addWin(newptr->value->team2);
            }
            else
            {
              
            }

          }

          ChronoHead = newptr;
          ChronoTail = newptr;
        }
        else
        {
          if (newptr->value->team1Score > newptr->value->team2Score)
          {
            addWin(newptr->value->team1);
          }
          else
          {
            if (newptr->value->team1Score < newptr->value->team2Score)
            {
              addWin(newptr->value->team2);
            }
            else
            {
              
            }

          }

          newptr->chronoPrev = ChronoTail;
          ChronoTail->chronoNext = newptr;
          ChronoTail = newptr;
        }

      }
      else
      {
        if (newptr->value->team1Score > newptr->value->team2Score)
        {
          addWin(newptr->value->team1);
        }
        else
        {
          if (newptr->value->team1Score < newptr->value->team2Score)
          {
            addWin(newptr->value->team2);
          }
          else
          {
            
          }

        }

        newptr->hashNext = Games[index];
        Games[index] = newptr;
        newptr->chronoPrev = ChronoTail;
        ChronoTail->chronoNext = newptr;
        ChronoTail = newptr;
      }

    }

  }

}

void addTeam(char command[])
{
  struct tNode *tHead;
  int index = hash(command);
  int teamExists = 0;
  struct tNode *newptr = malloc(sizeof(tNode));
  struct Team *temp = malloc(sizeof(Team));
  temp->name = malloc((sizeof(char)) * (strlen(command) + 1));
  strcpy(temp->name, command);
  temp->winCount = 0;
  newptr->value = temp;
  newptr->next = 0;
  if (Teams[index] == 0)
  {
    Teams[index] = newptr;
  }
  else
  {
    for (tHead = Teams[index]; tHead != 0; tHead = tHead->next)
    {
      if (strcmp(tHead->value->name, command) == 0)
      {
        teamExists = 1;
      }
      else
      {
        
      }

    }

    if (teamExists == 1)
    {
      printf("%d %s\n", NL, "Equipa existente.");
      free(newptr);
      free(temp->name);
      free(temp);
    }
    else
    {
      newptr->next = Teams[index];
      Teams[index] = newptr;
    }

  }

}

void listChrono()
{
  struct gNode *headCopy;
  for (headCopy = ChronoHead; headCopy != 0; headCopy = headCopy->chronoNext)
  {
    printf("%d %s %s %s %d %d\n", NL, headCopy->value->name, headCopy->value->team1, headCopy->value->team2, headCopy->value->team1Score, headCopy->value->team2Score);
  }

}

void searchGame(char command[])
{
  struct gNode *gHeadCopy;
  struct gNode *printIt;
  int gFound = 0;
  int index = hash(command);
  for (gHeadCopy = Games[index]; (gHeadCopy != 0) && (gFound == 0); gHeadCopy = gHeadCopy->hashNext)
  {
    if (strcmp(gHeadCopy->value->name, command) == 0)
    {
      printIt = gHeadCopy;
      gFound = 1;
    }
    else
    {
      
    }

  }

  if (gFound == 0)
  {
    printf("%d %s\n", NL, "Jogo inexistente.");
  }
  else
  {
    if (gFound == 1)
    {
      printf("%d %s %s %s %d %d\n", NL, printIt->value->name, printIt->value->team1, printIt->value->team2, printIt->value->team1Score, printIt->value->team2Score);
    }
    else
    {
      
    }

  }

}

void searchTeam(char command[])
{
  struct tNode *tHeadCopy;
  struct tNode *printIt;
  int tFound = 0;
  int index = hash(command);
  for (tHeadCopy = Teams[index]; tHeadCopy != 0; tHeadCopy = tHeadCopy->next)
  {
    if (strcmp(tHeadCopy->value->name, command) == 0)
    {
      printIt = tHeadCopy;
      tFound = 1;
    }
    else
    {
      
    }

  }

  if (tFound == 0)
  {
    printf("%d %s\n", NL, "Equipa inexistente.");
  }
  else
  {
    if (tFound == 1)
    {
      printf("%d %s %d\n", NL, printIt->value->name, printIt->value->winCount);
    }
    else
    {
      
    }

  }

}

void freeAll()
{
  int i;
  struct gNode *toDestroy;
  struct gNode *nextt = 0;
  struct tNode *toDestroyT;
  struct tNode *nexttT = 0;
  for (toDestroy = ChronoHead; toDestroy != 0; toDestroy = nextt)
  {
    nextt = toDestroy->chronoNext;
    free(toDestroy->value->name);
    free(toDestroy->value->team1);
    free(toDestroy->value->team2);
    free(toDestroy->value);
    free(toDestroy);
  }

  for (i = 0; i < 1019; i++)
  {
    for (toDestroyT = Teams[i]; toDestroyT != 0; toDestroyT = nexttT)
    {
      nexttT = toDestroyT->next;
      free(toDestroyT->value->name);
      free(toDestroyT->value);
      free(toDestroyT);
    }

  }

}

void changeScore(char command[])
{
  struct gNode *gCopy;
  char delim[2] = ":";
  char theGame[1024];
  int index;
  int found;
  int newScore1;
  int newScore2;
  char *token;
  token = strtok(command, delim);
  strcpy(theGame, token);
  token = strtok(0, delim);
  newScore1 = strtol(token, 0, 10);
  token = strtok(0, delim);
  newScore2 = strtol(token, 0, 10);
  index = hash(theGame);
  found = 0;
  for (gCopy = Games[index]; (gCopy != 0) && (found == 0); gCopy = gCopy->hashNext)
  {
    if (strcmp(gCopy->value->name, theGame) == 0)
    {
      if (gCopy->value->team1Score > gCopy->value->team2Score)
      {
        removeWin(gCopy->value->team1);
      }
      else
      {
        if (gCopy->value->team1Score < gCopy->value->team2Score)
        {
          removeWin(gCopy->value->team2);
        }
        else
        {
          
        }

      }

      gCopy->value->team1Score = newScore1;
      gCopy->value->team2Score = newScore2;
      if (newScore1 > newScore2)
      {
        addWin(gCopy->value->team1);
      }
      else
      {
        if (newScore1 < newScore2)
        {
          addWin(gCopy->value->team2);
        }
        else
        {
          
        }

      }

      found = 1;
    }
    else
    {
      
    }

  }

  if (found == 0)
  {
    printf("%d %s\n", NL, "Jogo inexistente.");
  }
  else
  {
    
  }

}

void gNodeFree(struct gNode *freeThisOne)
{
  free(freeThisOne->value->name);
  free(freeThisOne->value->team1);
  free(freeThisOne->value->team2);
  free(freeThisOne->value);
  free(freeThisOne);
}

void removeFromChrono(struct gNode *removeIt)
{
  if (removeIt == ChronoHead)
  {
    if (ChronoHead->chronoNext == 0)
    {
      ChronoHead = 0;
      ChronoTail = 0;
    }
    else
    {
      ChronoHead = ChronoHead->chronoNext;
      ChronoHead->chronoPrev = 0;
    }

  }
  else
  {
    if (removeIt == ChronoTail)
    {
      ChronoTail = ChronoTail->chronoPrev;
      ChronoTail->chronoNext = 0;
    }
    else
    {
      removeIt->chronoPrev->chronoNext = removeIt->chronoNext;
      removeIt->chronoNext->chronoPrev = removeIt->chronoPrev;
    }

  }

  gNodeFree(removeIt);
}

void removeGame(char command[])
{
  struct gNode *gCopy;
  struct gNode *freeThisOne;
  int found = 0;
  int index = hash(command);
  if (Games[index] == 0)
  {
    found = 0;
  }
  else
  {
    if (strcmp(Games[index]->value->name, command) == 0)
    {
      found = 1;
      freeThisOne = Games[index];
      Games[index] = Games[index]->hashNext;
      if (freeThisOne->value->team1Score > freeThisOne->value->team2Score)
      {
        removeWin(freeThisOne->value->team1);
      }
      else
      {
        if (freeThisOne->value->team1Score < freeThisOne->value->team2Score)
        {
          removeWin(freeThisOne->value->team2);
        }
        else
        {
          
        }

      }

      removeFromChrono(freeThisOne);
    }
    else
    {
      for (gCopy = Games[index]; (gCopy != 0) && (found == 0); gCopy = gCopy->hashNext)
      {
        if (gCopy->hashNext != 0)
        {
          if (strcmp(gCopy->hashNext->value->name, command) == 0)
          {
            freeThisOne = gCopy->hashNext;
            if (gCopy->hashNext->hashNext == 0)
            {
              gCopy->hashNext = 0;
              if (freeThisOne->value->team1Score > freeThisOne->value->team2Score)
              {
                removeWin(freeThisOne->value->team1);
              }
              else
              {
                if (freeThisOne->value->team1Score < freeThisOne->value->team2Score)
                {
                  removeWin(freeThisOne->value->team2);
                }
                else
                {
                  
                }

              }

              removeFromChrono(freeThisOne);
            }
            else
            {
              gCopy->hashNext = gCopy->hashNext->hashNext;
              if (freeThisOne->value->team1Score > freeThisOne->value->team2Score)
              {
                removeWin(freeThisOne->value->team1);
              }
              else
              {
                if (freeThisOne->value->team1Score < freeThisOne->value->team2Score)
                {
                  removeWin(freeThisOne->value->team2);
                }
                else
                {
                  
                }

              }

              removeFromChrono(freeThisOne);
            }

            found = 1;
          }
          else
          {
            
          }

        }
        else
        {
          
        }

      }

    }

  }

  if (found == 0)
  {
    printf("%d %s\n", NL, "Jogo inexistente.");
  }
  else
  {
    
  }

}

void findBigWinners()
{
  int i;
  int j;
  int empates = 0;
  int maxWin = 0;
  int teamsExist = 0;
  int winnerCounter = 0;
  struct tNode *storm;
  struct tNode *tHead;
  struct tNode **bigWinners;
  for (i = 0; i < 1019; i++)
  {
    if (Teams[i] != 0)
    {
      teamsExist = 1;
      for (tHead = Teams[i]; tHead != 0; tHead = tHead->next)
      {
        if (tHead->value->winCount > maxWin)
        {
          empates = 1;
          maxWin = tHead->value->winCount;
        }
        else
        {
          if (tHead->value->winCount == maxWin)
          {
            empates += 1;
          }
          else
          {
            
          }

        }

      }

    }
    else
    {
      
    }

  }

  if (teamsExist == 1)
  {
    bigWinners = malloc((sizeof(struct tNode *)) * empates);
    for (i = 0; i < 1019; i++)
    {
      for (tHead = Teams[i]; tHead != 0; tHead = tHead->next)
      {
        if (tHead->value->winCount == maxWin)
        {
          bigWinners[winnerCounter] = tHead;
          winnerCounter += 1;
        }
        else
        {
          
        }

      }

    }

    for (i = 0; i < (winnerCounter - 1); ++i)
    {
      for (j = 0; j < ((winnerCounter - i) - 1); ++j)
      {
        if (strcmp(bigWinners[j]->value->name, bigWinners[j + 1]->value->name) > 0)
        {
          storm = bigWinners[j];
          bigWinners[j] = bigWinners[j + 1];
          bigWinners[j + 1] = storm;
        }
        else
        {
          
        }

      }

    }

    printf("%d Melhores %d\n", NL, maxWin);
    for (i = 0; i < empates; ++i)
    {
      printf("%d * %s\n", NL, bigWinners[i]->value->name);
    }

    free(bigWinners);
  }
  else
  {
    
  }

}

int main()
{
  char mander = ' ';
  char arg[(1024 * 3) + 24];
  initialiseHashTables();
  ChronoHead = 0;
  ChronoTail = 0;
  NL = 0;
  while (mander != 'x')
  {
    mander = getchar();
    if (mander == '\n')
    {
      continue;
    }
    else
    {
      
    }

    NL++;
    switch (mander)
    {
      case 'a':
        getchar();
        for (int arg_index = 0; arg_index < ((1024 * 3) + 24); arg_index++)
      {
        arg[arg_index] = new_sym_var(sizeof(char) * 8);
      }

        arg[((1024 * 3) + 24) - 1] = '\0';
        addGame(arg);
        break;

      case 'l':
        listChrono();
        break;

      case 'A':
        getchar();
        for (int arg_index = 0; arg_index < ((1024 * 3) + 24); arg_index++)
      {
        arg[arg_index] = new_sym_var(sizeof(char) * 8);
      }

        arg[((1024 * 3) + 24) - 1] = '\0';
        addTeam(arg);
        break;

      case 'p':
        getchar();
        for (int arg_index = 0; arg_index < ((1024 * 3) + 24); arg_index++)
      {
        arg[arg_index] = new_sym_var(sizeof(char) * 8);
      }

        arg[((1024 * 3) + 24) - 1] = '\0';
        searchGame(arg);
        break;

      case 'P':
        getchar();
        for (int arg_index = 0; arg_index < ((1024 * 3) + 24); arg_index++)
      {
        arg[arg_index] = new_sym_var(sizeof(char) * 8);
      }

        arg[((1024 * 3) + 24) - 1] = '\0';
        searchTeam(arg);
        break;

      case 's':
        getchar();
        for (int arg_index = 0; arg_index < ((1024 * 3) + 24); arg_index++)
      {
        arg[arg_index] = new_sym_var(sizeof(char) * 8);
      }

        arg[((1024 * 3) + 24) - 1] = '\0';
        changeScore(arg);
        break;

      case 'r':
        getchar();
        for (int arg_index = 0; arg_index < ((1024 * 3) + 24); arg_index++)
      {
        arg[arg_index] = new_sym_var(sizeof(char) * 8);
      }

        arg[((1024 * 3) + 24) - 1] = '\0';
        removeGame(arg);
        break;

      case 'g':
        findBigWinners();
        break;

    }

  }

  freeAll();
  return 0;
}

