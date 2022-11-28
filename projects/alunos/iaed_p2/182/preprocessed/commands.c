#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "commands.h"
#include "auxiliary.h"


void add_team(unsigned int NL, tlink **team_table)
{
  char name[1023];
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  getchar();
  if (!new_team(team_table, name))
  {
    printf("%u Equipa existente.\n", NL);
  }
  else
  {
    
  }

}

void add_game(unsigned int NL, game **first_game, game **last_game, glink **game_table, tlink **team_table)
{
  char name[1023];
  char team1[1023];
  char team2[1023];
  int score1;
  int score2;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  getchar();
  for (int team1_index = 0; team1_index < 10; team1_index++)
  {
    team1[team1_index] = new_sym_var(sizeof(char) * 8);
  }

  team1[10 - 1] = '\0';
  getchar();
  for (int team2_index = 0; team2_index < 10; team2_index++)
  {
    team2[team2_index] = new_sym_var(sizeof(char) * 8);
  }

  team2[10 - 1] = '\0';
  getchar();
  score1 = new_sym_var(sizeof(int) * 8);
  getchar();
  score2 = new_sym_var(sizeof(int) * 8);
  getchar();
  if (game_table_search(game_table, name) != 0)
  {
    printf("%u Jogo existente.\n", NL);
    return;
  }
  else
  {
    if ((team_table_search(team_table, team1) == 0) || (team_table_search(team_table, team2) == 0))
    {
      printf("%u Equipa inexistente.\n", NL);
      return;
    }
    else
    {
      new_game(game_table, team_table, first_game, last_game, name, team1, team2, score1, score2);
    }

  }

}

void list_games(unsigned int NL, game **first_game)
{
  game *runthrough;
  for (runthrough = *first_game; runthrough != 0; runthrough = runthrough->next)
    printf("%u %s %s %s %d %d\n", NL, runthrough->name, runthrough->team1, runthrough->team2, runthrough->score1, runthrough->score2);

}

void search_team(unsigned int NL, tlink **team_table)
{
  char name[1023];
  team *wanted;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  getchar();
  wanted = team_table_search(team_table, name);
  if (wanted == 0)
  {
    printf("%u Equipa inexistente.\n", NL);
  }
  else
  {
    printf("%u %s %d\n", NL, wanted->name, wanted->victories);
  }

}

void search_game(unsigned int NL, glink **game_table)
{
  char name[1023];
  game *wanted;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  getchar();
  wanted = game_table_search(game_table, name);
  if (wanted == 0)
  {
    printf("%u Jogo inexistente.\n", NL);
  }
  else
  {
    printf("%u %s %s %s %d %d\n", NL, wanted->name, wanted->team1, wanted->team2, wanted->score1, wanted->score2);
  }

}

void remove_game(unsigned int NL, game **first_game, game **last_game, glink **game_table, tlink **team_table)
{
  char name[1023];
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  getchar();
  if (game_table_search(game_table, name) == 0)
  {
    printf("%u Jogo inexistente.\n", NL);
  }
  else
  {
    delete_game(first_game, last_game, game_table, team_table, name);
  }

}

void change_score(unsigned int NL, glink **game_table, tlink **team_table)
{
  int new_tie = 0;
  int old_tie = 0;
  int new_scr1;
  int new_scr2;
  char new_winner[1023];
  char old_winner[1023];
  char name[1023];
  game *match;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  getchar();
  new_scr1 = new_sym_var(sizeof(int) * 8);
  getchar();
  new_scr2 = new_sym_var(sizeof(int) * 8);
  getchar();
  match = game_table_search(game_table, name);
  if (match == 0)
  {
    printf("%u Jogo inexistente.\n", NL);
    return;
  }
  else
  {
    
  }

  if (new_scr1 > new_scr2)
  {
    strcpy(new_winner, match->team1);
  }
  else
  {
    if (new_scr2 > new_scr1)
    {
      strcpy(new_winner, match->team2);
    }
    else
    {
      new_tie = 1;
    }

  }

  if (match->score1 > match->score2)
  {
    strcpy(old_winner, match->team1);
  }
  else
  {
    if (match->score2 > match->score1)
    {
      strcpy(old_winner, match->team2);
    }
    else
    {
      old_tie = 1;
    }

  }

  match->score1 = new_scr1;
  match->score2 = new_scr2;
  if (old_tie && new_tie)
  {
    return;
  }
  else
  {
    if (old_tie && (!new_tie))
    {
      give_victory(team_table, new_winner);
    }
    else
    {
      if ((!old_tie) && new_tie)
      {
        remove_victory(team_table, old_winner);
      }
      else
      {
        if (strcmp(new_winner, old_winner) == 0)
        {
          return;
        }
        else
        {
          remove_victory(team_table, old_winner);
          give_victory(team_table, new_winner);
        }

      }

    }

  }

}

void best_teams(unsigned int NL, tlink **team_table)
{
  int i;
  int total = 1;
  int most = -1;
  tlink *node;
  team *list = (team *) malloc(total * (sizeof(team)));
  team *orig_list = list;
  for (i = 0; i < 419; i++)
  {
    for (node = team_table[i]; node != 0; node = node->next)
    {
      if (node->t->victories > most)
      {
        most = node->t->victories;
        free(list);
        total = 1;
        list = (team *) malloc(total * (sizeof(team)));
        list[0] = *node->t;
      }
      else
      {
        if (node->t->victories == most)
        {
          total++;
          list = (team *) realloc(list, total * (sizeof(team)));
          list[total - 1] = *node->t;
        }
        else
        {
          
        }

      }

    }

  }

  if (most == (-1))
  {
    free(orig_list);
    return;
  }
  else
  {
    qsort(list, total, sizeof(team), compare_func);
    printf("%u Melhores %d\n", NL, most);
    for (i = 0; i < total; i++)
    {
      printf("%u * %s\n", NL, list[i].name);
    }

    free(list);
  }

}

void free_memory(glink **game_table, tlink **team_table, game **first_game, game **last_game)
{
  destroy_gtable(game_table);
  destroy_ttable(team_table);
  free(game_table);
  free(team_table);
  free(first_game);
  free(last_game);
}
