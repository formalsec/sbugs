#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "games.h"
#include "teams.h"


list_games *makeListGames()
{
  list_games *new_list = (list_games *) malloc(sizeof(list_games));
  new_list->head = 0;
  new_list->last = 0;
  return new_list;
}

game *searchListGames(list_games *list, char *name)
{
  game_node *t = list->head;
  while (t)
  {
    if (!strcmp(t->gameptr->name, name))
    {
      return t->gameptr;
    }
    else
    {
      
    }

    t = t->next;
  }

  return 0;
}

void addLast(list_games *l, game *g)
{
  game_node *new_last = (game_node *) malloc(sizeof(game_node));
  new_last->gameptr = g;
  new_last->next = 0;
  new_last->previous = l->last;
  if (!l->head)
  {
    l->head = new_last;
    l->last = new_last;
    return;
  }
  else
  {
    
  }

  l->last->next = new_last;
  l->last = new_last;
}

void removeFromList(list_games *list, char *name)
{
  game_node *t;
  for (t = list->head; t; t = t->next)
  {
    if (!strcmp(t->gameptr->name, name))
    {
      if (t == list->head)
      {
        list->head = t->next;
        if (t->next != 0)
        {
          t->next->previous = 0;
        }
        else
        {
          
        }

      }
      else
      {
        if (t == list->last)
        {
          list->last = t->previous;
          if (t->previous != 0)
          {
            t->previous->next = 0;
          }
          else
          {
            
          }

        }
        else
        {
          t->previous->next = t->next;
          t->next->previous = t->previous;
        }

      }

      free(t);
      break;
    }
    else
    {
      
    }

  }

}

list_games **makeHashGames()
{
  list_games **hash_table = (list_games **) malloc((sizeof(list_games *)) * 1061);
  int i;
  for (i = 0; i < 1061; i++)
  {
    hash_table[i] = makeListGames();
  }

  return hash_table;
}

game *searchHashGames(list_games **hastable, char *name)
{
  int i = hash(name);
  return searchListGames(hastable[i], name);
}

void insertGame(list_games **hashtable, game *g)
{
  int i = hash(g->name);
  addLast(hashtable[i], g);
}

void freeGame(game *g)
{
  free(g->name);
  free(g->team1);
  free(g->team2);
  free(g);
}

void freeList(list_games *lgptr)
{
  game_node *t = lgptr->head;
  while (t)
  {
    game_node *old = t;
    freeGame(t->gameptr);
    t = t->next;
    free(old);
  }

  free(lgptr);
}

void freeAllMemoryGames(list_games *lgptr, list_games **hashgames)
{
  int i;
  freeList(lgptr);
  for (i = 0; i < 1061; i++)
  {
    list_games *t = hashgames[i];
    game_node *g = t->head;
    while (g)
    {
      game_node *old = g;
      g = g->next;
      free(old);
    }

    free(t);
  }

  free(hashgames);
}

void initGame(game *new_game, char *match_name, char *team1, char *team2, int score1, int score2)
{
  new_game->name = myStrdup(match_name);
  new_game->team1 = myStrdup(team1);
  new_game->team2 = myStrdup(team2);
  new_game->score_team1 = score1;
  new_game->score_team2 = score2;
}

void addGame(list_games *lgptr, list_games **hashgames, team_node **hasteams, int line)
{
  char *match_name_buffer = (char *) malloc((sizeof(char)) * 1024);
  char *team1_buffer = (char *) malloc((sizeof(char)) * 1024);
  char *team2_buffer = (char *) malloc((sizeof(char)) * 1024);
  int score1;
  int score2;
  game *new_game;
  for (int match_name_buffer_index = 0; match_name_buffer_index < 10; match_name_buffer_index++)
  {
    match_name_buffer[match_name_buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  match_name_buffer[10 - 1] = '\0';
  for (int team1_buffer_index = 0; team1_buffer_index < 10; team1_buffer_index++)
  {
    team1_buffer[team1_buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  team1_buffer[10 - 1] = '\0';
  for (int team2_buffer_index = 0; team2_buffer_index < 10; team2_buffer_index++)
  {
    team2_buffer[team2_buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  team2_buffer[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  if (searchHashGames(hashgames, match_name_buffer))
  {
    printf("%d Jogo existente.\n", line);
    free(match_name_buffer);
    free(team1_buffer);
    free(team2_buffer);
    return;
  }
  else
  {
    if ((!searchHashTeams(hasteams, team1_buffer)) || (!searchHashTeams(hasteams, team2_buffer)))
    {
      printf("%d Equipa inexistente.\n", line);
      free(match_name_buffer);
      free(team1_buffer);
      free(team2_buffer);
      return;
    }
    else
    {
      
    }

  }

  new_game = (game *) malloc(sizeof(game));
  initGame(new_game, match_name_buffer, team1_buffer, team2_buffer, score1, score2);
  insertGame(hashgames, new_game);
  addLast(lgptr, new_game);
  if (score1 > score2)
  {
    searchHashTeams(hasteams, team1_buffer)->number_of_wins++;
  }
  else
  {
    if (score1 < score2)
    {
      searchHashTeams(hasteams, team2_buffer)->number_of_wins++;
    }
    else
    {
      
    }

  }

  free(match_name_buffer);
  free(team1_buffer);
  free(team2_buffer);
}

void listGames(list_games *lgptr, int line)
{
  game_node *t;
  for (t = lgptr->head; t; t = t->next)
  {
    printf("%d %s %s %s %d %d\n", line, t->gameptr->name, t->gameptr->team1, t->gameptr->team2, t->gameptr->score_team1, t->gameptr->score_team2);
  }

}

void searchGame(list_games **hastable, int line)
{
  char *name = (char *) malloc((sizeof(char)) * 1024);
  game *g;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  g = searchHashGames(hastable, name);
  if (!g)
  {
    printf("%d Jogo inexistente.\n", line);
    free(name);
    return;
  }
  else
  {
    
  }

  printf("%d %s %s %s %d %d\n", line, g->name, g->team1, g->team2, g->score_team1, g->score_team2);
  free(name);
}

void deleteGame(list_games *lgprt, list_games **hashgames, team_node **hashteams, int line)
{
  char *name = (char *) malloc((sizeof(char)) * 1024);
  game *g;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  g = searchHashGames(hashgames, name);
  if (!g)
  {
    printf("%d Jogo inexistente.\n", line);
    free(name);
    return;
  }
  else
  {
    
  }

  if (g->score_team1 > g->score_team2)
  {
    searchHashTeams(hashteams, g->team1)->number_of_wins--;
  }
  else
  {
    if (g->score_team1 < g->score_team2)
    {
      searchHashTeams(hashteams, g->team2)->number_of_wins--;
    }
    else
    {
      
    }

  }

  removeFromList(lgprt, name);
  removeFromList(hashgames[hash(name)], name);
  freeGame(g);
  free(name);
}

void changeScore(list_games **hashgames, team_node **hashteams, int line)
{
  char *name = (char *) malloc((sizeof(char)) * 1024);
  int old_score1;
  int old_score2;
  int new_score1;
  int new_score2;
  game *g;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  new_score1 = new_sym_var(sizeof(int) * 8);
  new_score2 = new_sym_var(sizeof(int) * 8);
  g = searchHashGames(hashgames, name);
  if (!g)
  {
    printf("%d Jogo inexistente.\n", line);
    free(name);
    return;
  }
  else
  {
    
  }

  old_score1 = g->score_team1;
  old_score2 = g->score_team2;
  if (old_score1 > old_score2)
  {
    if (new_score1 < new_score2)
    {
      searchHashTeams(hashteams, g->team1)->number_of_wins--;
      searchHashTeams(hashteams, g->team2)->number_of_wins++;
    }
    else
    {
      if (new_score1 == new_score2)
      {
        searchHashTeams(hashteams, g->team1)->number_of_wins--;
      }
      else
      {
        
      }

    }

  }
  else
  {
    if (old_score2 > old_score1)
    {
      if (new_score2 < new_score1)
      {
        searchHashTeams(hashteams, g->team2)->number_of_wins--;
        searchHashTeams(hashteams, g->team1)->number_of_wins++;
      }
      else
      {
        if (new_score2 == new_score1)
        {
          searchHashTeams(hashteams, g->team2)->number_of_wins--;
        }
        else
        {
          
        }

      }

    }
    else
    {
      if (new_score1 > new_score2)
      {
        searchHashTeams(hashteams, g->team1)->number_of_wins++;
      }
      else
      {
        if (new_score2 > new_score1)
        {
          searchHashTeams(hashteams, g->team2)->number_of_wins++;
        }
        else
        {
          
        }

      }

    }

  }

  g->score_team1 = new_score1;
  g->score_team2 = new_score2;
  free(name);
}

