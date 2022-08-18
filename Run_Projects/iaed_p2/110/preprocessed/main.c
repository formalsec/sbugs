/*File generated by PreProcessor.py*/


#include "gameslinked.h"
#include "hashteams.h"


gamelist addGame(int NL, gamelist *list, heads *hash);
heads addTeam(int NL, heads *hash);
void lookupTeam(int NL, heads hash);
void printGames(int NL, gamelist list);
void lookupGame(int NL, gamelist list);
gamelist deleteGame(int NL, gamelist *list);
gamelist changeScore(int NL, gamelist *list);
int compare(const void *a, const void *b);
void topWinners(int NL, heads hash);
int main()
{
  int NL = 1;
  char letra;
  gamelist head = game_listInit();
  heads hash = hashInit();
  while (letra != EOF)
  {
    letra = getchar();
    switch (letra)
    {
      case 'a':
        addGame(NL, &head, &hash);
        NL++;
        break;

      case 'A':
        addTeam(NL, &hash);
        NL++;
        break;

      case 'l':
        printGames(NL, head);
        NL++;
        break;

      case 'p':
        lookupGame(NL, head);
        NL++;
        break;

      case 'P':
        lookupTeam(NL, hash);
        NL++;
        break;

      case 'r':
        deleteGame(NL, &head);
        NL++;
        break;

      case 's':
        changeScore(NL, &head);
        NL++;
        break;

      case 'g':
        topWinners(NL, hash);
        NL++;
        break;

      case 'x':
        game_destroyList(head);
        hashDestroy(hash);
        return 0;

      default:
        break;

    }

  }

  return 0;
}

gamelist addGame(int NL, gamelist *list, heads *hash)
{
  char name[1023];
  char t1[1023];
  char t2[1023];
  int s1;
  int s2;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  for (int t1_index = 0; t1_index < 10; t1_index++)
  {
    t1[t1_index] = new_sym_var(sizeof(char) * 8);
  }

  t1[10 - 1] = '\0';
  for (int t2_index = 0; t2_index < 10; t2_index++)
  {
    t2[t2_index] = new_sym_var(sizeof(char) * 8);
  }

  t2[10 - 1] = '\0';
  s1 = new_sym_var(sizeof(int) * 8);
  s2 = new_sym_var(sizeof(int) * 8);
  if (game_searchList(*list, name) == 0)
  {
    {
      link team1 = hashSearch(*hash, t1);
      link team2 = hashSearch(*hash, t2);
      if ((team1 == 0) || (team2 == 0))
      {
        {
          printf("%d Equipa inexistente.\n", NL);
        }
      }
      else
      {
        {
          Game game = gameInit(name, getItem(team1), getItem(team2), s1, s2);
          *list = game_insertListEnd(*list, game);
          team1->Team->wins = game->t1->wins;
          team2->Team->wins = game->t2->wins;
        }
      }

      return *list;
    }
  }
  else
  {
    {
      printf("%d Jogo existente.\n", NL);
    }
  }

  return *list;
}

heads addTeam(int NL, heads *hash)
{
  char name[1023];
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  hashInsert(NL, *hash, teamInit(name));
  return *hash;
}

void lookupTeam(int NL, heads hash)
{
  char name[1023];
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  teamPrint(NL, getItem(hashSearch(hash, name)));
}

void printGames(int NL, gamelist list)
{
  game_showList(NL, list);
}

void lookupGame(int NL, gamelist list)
{
  char name[1023];
  gamelink game2print;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  game2print = game_searchList(list, name);
  if (!game2print)
  {
    {
      printf("%d Jogo inexistente.\n", NL);
      return;
    }
  }
  else
  {
    
  }

  gamePrint(NL, game2print->game);
}

gamelist deleteGame(int NL, gamelist *list)
{
  gamelink node;
  int score1;
  int score2;
  char name[1023];
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  node = game_searchList(*list, name);
  if (node == 0)
  {
    {
      printf("%d Jogo inexistente.\n", NL);
      return *list;
    }
  }
  else
  {
    
  }

  score1 = gameScoreT1(node->game);
  score2 = gameScoreT2(node->game);
  if (score1 == score2)
  {
    return game_removeList(*list, node);
  }
  else
  {
    
  }

  if (score1 > score2)
  {
    node->game->t1->wins--;
  }
  else
  {
    
  }

  if (score1 < score2)
  {
    node->game->t2->wins--;
  }
  else
  {
    
  }

  return game_removeList(*list, node);
}

gamelist changeScore(int NL, gamelist *list)
{
  char name[1023];
  int s1;
  int s2;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  s1 = new_sym_var(sizeof(int) * 8);
  s2 = new_sym_var(sizeof(int) * 8);
  return game_changeScore(NL, *list, name, s1, s2);
}

int compare(const void *a, const void *b)
{
  char **v1;
  char **v2;
  v1 = (char **) a;
  v2 = (char **) b;
  return strcmp(*v1, *v2);
}

void topWinners(int NL, heads hash)
{
  if (!hashEmpty(hash))
  {
    {
      int i = 0;
      maxes maxes = getHashMax(hash);
      char **strings = malloc((sizeof(char **)) * maxes.maxOcc);
      strings = getHashStrings(hash, maxes.max, strings);
      qsort(strings, maxes.maxOcc, sizeof(char **), compare);
      printf("%d Melhores %d\n", NL, maxes.max);
      while (i < maxes.maxOcc)
      {
        printf("%d * %s\n", NL, strings[i]);
        free(strings[i]);
        i++;
      }

      free(strings);
    }
  }
  else
  {
    
  }

}

