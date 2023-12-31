#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "team.h"
#include "game.h"
#include "hashTable.h"
#include "messages.h"
#include <stdio.h>
#include <string.h>


int teamExists(char *name, HashTable *teamsHashTable)
{
  link *link = hashTableSearch(teamsHashTable, name, compareTeamFunction);
  if (link == 0)
  {
    return 0;
  }
  else
  {
    
  }

  return 1;
}

int gameExists(char *name, HashTable *gameHashMap)
{
  link *link = hashTableSearch(gameHashMap, name, compareTeamFunction);
  if (link == 0)
  {
    return 0;
  }
  else
  {
    
  }

  return 1;
}

void newVictories(int *scores, Team **teams, int scoreToUpdate)
{
  if (scores[0] > scores[1])
  {
    updateVictories(teams[0], scoreToUpdate);
  }
  else
  {
    if (scores[0] < scores[1])
    {
      updateVictories(teams[1], scoreToUpdate);
    }
    else
    {
      
    }

  }

}

int canCreateGame(char *name, char *team1, char *team2, HashTable *gamesHashTable, HashTable *teamsHashTable)
{
  if (gameExists(name, gamesHashTable) == 1)
  {
    return 1;
  }
  else
  {
    
  }

  if ((teamExists(team1, teamsHashTable) == 0) || (teamExists(team2, teamsHashTable) == 0))
  {
    return 2;
  }
  else
  {
    
  }

  return 0;
}

int createNewGame(char *name, char *team1, char *team2, int *scores, HashTable *gamesHashTable, HashTable *teamsHashTable, List *orderList)
{
  Team *teams[2];
  Game *game;
  link *link;
  int value = canCreateGame(name, team1, team2, gamesHashTable, teamsHashTable);
  if ((value == 1) || (value == 2))
  {
    return value;
  }
  else
  {
    
  }

  link = hashTableSearch(teamsHashTable, team1, compareTeamFunction);
  teams[0] = link->dataPointer;
  link = hashTableSearch(teamsHashTable, team2, compareTeamFunction);
  teams[1] = link->dataPointer;
  game = createGame(name, teams, scores);
  hashTableInsert(gamesHashTable, name, game);
  listInsertEnd(orderList, game);
  newVictories(scores, game->teams, 1);
  return 0;
}

void execute_a(HashTable *gamesHashTable, HashTable *teamsHashTable, List *orderList, int *cmdCounter)
{
  char gameName[1023];
  char team1[1023];
  char team2[1023];
  int scores[2];
  int value;
  for (int gameName_index = 0; gameName_index < 10; gameName_index++)
  {
    gameName[gameName_index] = new_sym_var(sizeof(char) * 8);
  }

  gameName[10 - 1] = '\0';
  for (int team1_index = 0; team1_index < 10; team1_index++)
  {
    team1[team1_index] = new_sym_var(sizeof(char) * 8);
  }

  team1[10 - 1] = '\0';
  for (int team2_index = 0; team2_index < 10; team2_index++)
  {
    team2[team2_index] = new_sym_var(sizeof(char) * 8);
  }

  team2[10 - 1] = '\0';
  scores[0] = new_sym_var(sizeof(int) * 8);
  scores[1] = new_sym_var(sizeof(int) * 8);
  value = createNewGame(gameName, team1, team2, scores, gamesHashTable, teamsHashTable, orderList);
  if (value == 1)
  {
    printf("%d Jogo existente.\n", *cmdCounter);
  }
  else
  {
    if (value == 2)
    {
      printf("%d Equipa inexistente.\n", *cmdCounter);
    }
    else
    {
      
    }

  }

}

void execute_l(List *orderList, int *cmdCounter)
{
  listPrint(orderList, cmdCounter, printGame);
}

void execute_p(HashTable *gamesHashTable, int *cmdCounter)
{
  char gameName[1023];
  link *link;
  for (int gameName_index = 0; gameName_index < 10; gameName_index++)
  {
    gameName[gameName_index] = new_sym_var(sizeof(char) * 8);
  }

  gameName[10 - 1] = '\0';
  link = hashTableSearch(gamesHashTable, gameName, compareGameFunction);
  if (link != 0)
  {
    printGame(link->dataPointer, cmdCounter);
  }
  else
  {
    printf("%d Jogo inexistente.\n", *cmdCounter);
  }

}

int delGame(char *name, HashTable *gamesHashTable, List *orderList)
{
  link *link;
  if (gameExists(name, gamesHashTable) == 0)
  {
    return 0;
  }
  else
  {
    
  }

  link = hashTableSearch(gamesHashTable, name, compareGameFunction);
  newVictories(((Game *) link->dataPointer)->scores, ((Game *) link->dataPointer)->teams, -1);
  listRemoveElement(orderList, name, compareGameFunction, 0);
  hashTableRemove(gamesHashTable, name, compareGameFunction, deleteGame);
  return 1;
}

void execute_r(HashTable *gamesHashTable, List *orderList, int *cmdCounter)
{
  char gameName[1023];
  for (int gameName_index = 0; gameName_index < 10; gameName_index++)
  {
    gameName[gameName_index] = new_sym_var(sizeof(char) * 8);
  }

  gameName[10 - 1] = '\0';
  if (delGame(gameName, gamesHashTable, orderList) == 0)
  {
    printf("%d Jogo inexistente.\n", *cmdCounter);
  }
  else
  {
    
  }

}

void evaluateScores(int *newScores, Game *game)
{
  if (newScores[0] == newScores[1])
  {
    if (game->scores[0] > game->scores[1])
    {
      updateVictories(game->teams[0], -1);
    }
    else
    {
      if (game->scores[0] < game->scores[1])
      {
        updateVictories(game->teams[1], -1);
      }
      else
      {
        
      }

    }

  }
  else
  {
    if ((game->scores[0] > game->scores[1]) && (newScores[0] < newScores[1]))
    {
      updateVictories(game->teams[0], -1);
      updateVictories(game->teams[1], 1);
    }
    else
    {
      if ((game->scores[0] < game->scores[1]) && (newScores[0] > newScores[1]))
      {
        updateVictories(game->teams[1], -1);
        updateVictories(game->teams[0], 1);
      }
      else
      {
        if (game->scores[0] == game->scores[1])
        {
          if (newScores[0] > newScores[1])
          {
            updateVictories(game->teams[0], 1);
          }
          else
          {
            if (newScores[0] < newScores[1])
            {
              updateVictories(game->teams[1], 1);
            }
            else
            {
              
            }

          }

        }
        else
        {
          
        }

      }

    }

  }

}

int changeGameScores(char *name, int *newScores, HashTable *gamesHashTable)
{
  link *gameLink;
  Game *game;
  if (gameExists(name, gamesHashTable) == 0)
  {
    return 0;
  }
  else
  {
    
  }

  gameLink = hashTableSearch(gamesHashTable, name, compareGameFunction);
  game = gameLink->dataPointer;
  evaluateScores(newScores, game);
  game->scores[0] = newScores[0];
  game->scores[1] = newScores[1];
  return 1;
}

void execute_s(HashTable *gamesHashTable, int *cmdCounter)
{
  char gameName[1023];
  int scores[2];
  for (int gameName_index = 0; gameName_index < 10; gameName_index++)
  {
    gameName[gameName_index] = new_sym_var(sizeof(char) * 8);
  }

  gameName[10 - 1] = '\0';
  scores[0] = new_sym_var(sizeof(int) * 8);
  scores[1] = new_sym_var(sizeof(int) * 8);
  if (changeGameScores(gameName, scores, gamesHashTable) == 0)
  {
    printf("%d Jogo inexistente.\n", *cmdCounter);
  }
  else
  {
    
  }

}

int createNewTeam(char *name, HashTable *teamsHashTable)
{
  Team *team;
  if (teamExists(name, teamsHashTable) == 1)
  {
    return 0;
  }
  else
  {
    
  }

  team = createTeam(name);
  hashTableInsert(teamsHashTable, name, team);
  return 1;
}

void execute_A(HashTable *teamsHashTable, int *cmdCounter)
{
  char name[1023];
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  if (createNewTeam(name, teamsHashTable) == 0)
  {
    printf("%d Equipa existente.\n", *cmdCounter);
  }
  else
  {
    
  }

}

void execute_P(HashTable *teamsHashTable, int *cmdCounter)
{
  char name[1023];
  link *link;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  link = hashTableSearch(teamsHashTable, name, compareTeamFunction);
  if (link != 0)
  {
    printTeam(link->dataPointer, cmdCounter);
  }
  else
  {
    printf("%d Equipa inexistente.\n", *cmdCounter);
  }

}

List *createBestTeamsList(HashTable *teamsHashTable, int *mostVictories)
{
  link *listNode;
  link *node;
  List *list = creatList();
  int i;
  for (i = 0; i < teamsHashTable->buckets; i++)
  {
    for (node = teamsHashTable->lists[i]->head; node != 0; node = node->next)
    {
      if (((Team *) node->dataPointer)->victories == (*mostVictories))
      {
        if (isListEmpty(list))
        {
          listInsertEnd(list, node->dataPointer);
          continue;
        }
        else
        {
          
        }

        for (listNode = list->head; listNode != 0; listNode = listNode->next)
        {
          if (strcmp(((Team *) node->dataPointer)->name, ((Team *) listNode->dataPointer)->name) < 0)
          {
            listInsertBefore(list, listNode, node->dataPointer);
            break;
          }
          else
          {
            if (listNode == list->tail)
            {
              listInsertEnd(list, node->dataPointer);
              break;
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

  }

  return list;
}

List *buildListByGames(HashTable *teamsHashTable, int *victories)
{
  int i;
  link *node;
  int mostVictories = 0;
  for (i = 0; i < teamsHashTable->buckets; i++)
  {
    for (node = teamsHashTable->lists[i]->head; node != 0; node = node->next)
    {
      if (mostVictories < ((Team *) node->dataPointer)->victories)
      {
        mostVictories = ((Team *) node->dataPointer)->victories;
      }
      else
      {
        
      }

    }

  }

  *victories = mostVictories;
  return createBestTeamsList(teamsHashTable, &mostVictories);
}

void execute_g(HashTable *teamsHashTable, int *counter)
{
  int victories = 0;
  List *teams = buildListByGames(teamsHashTable, &victories);
  if (isListEmpty(teams) == 0)
  {
    printf("%d Melhores %d\n", *counter, victories);
    listPrint(teams, counter, bestTeamsFunction);
  }
  else
  {
    
  }

  deleteList(teams, 0);
}

int readCommands(char command, HashTable *gamesHashTable, HashTable *teamsHashTable, List *orderList, int *counter)
{
  switch (command)
  {
    case 'a':
      execute_a(gamesHashTable, teamsHashTable, orderList, counter);
      break;

    case 'l':
      execute_l(orderList, counter);
      break;

    case 'p':
      execute_p(gamesHashTable, counter);
      break;

    case 'r':
      execute_r(gamesHashTable, orderList, counter);
      break;

    case 's':
      execute_s(gamesHashTable, counter);
      break;

    case 'A':
      execute_A(teamsHashTable, counter);
      break;

    case 'P':
      execute_P(teamsHashTable, counter);
      break;

    case 'g':
      execute_g(teamsHashTable, counter);
      break;

    case 'x':
      return 0;

    default:
      break;

  }

  return 1;
}

int main()
{
  int running = 1;
  int counter = 10;
  char command;
  HashTable *teamsHashTable = createHashTable(10000);
  HashTable *gamesHashTable = createHashTable(10000);
  List *orderList = creatList();
  for (counter = 1; running == 1; counter++)
  {
    command = new_sym_var(sizeof(char) * 8);
    running = readCommands(command, gamesHashTable, teamsHashTable, orderList, &counter);
  }

  deleteHashTable(teamsHashTable, deleteTeam);
  deleteHashTable(gamesHashTable, deleteGame);
  deleteList(orderList, 0);
  return 0;
}

