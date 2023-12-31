#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "utilities.h"
#include "structs_auxiliary.h"


void new_game(games **games_ht, game_names **name_list, teams **teams_ht, int inp);
void list_games(game_names *names, int inp);
void find_game(games **games_ht, int inp);
void del_game(games **games_ht, game_names **names, int inp);
void change_score(games **games_ht, int inp);
teams **new_team(teams **teams_ht, teams **teams_contiguous, int *teamc, int *teams_sz, int inp);
void find_team(teams **teams_ht, int inp);
void best_teams(teams **team_contig, int teamc, int inp);
int main()
{
  int inp = 0;
  int teamc = 0;
  int *teamc_pt = &teamc;
  int teams_sz = 23269;
  int *teams_sz_pt = &teams_sz;
  games **games_ht = calloc(23269, sizeof(games *));
  game_names *names = 0;
  game_names **names_pt = &names;
  teams **teams_ht = calloc(23269, sizeof(teams *));
  teams **teams_contiguous = calloc(23269, sizeof(teams *));
  char command;
  while ((command = getchar()) != 'x')
  {
    switch (command)
    {
      case 'a':
        inp++;
        new_game(games_ht, names_pt, teams_ht, inp);
        break;

      case 'l':
        inp++;
        list_games(names, inp);
        break;

      case 'p':
        inp++;
        find_game(games_ht, inp);
        break;

      case 'r':
        inp++;
        del_game(games_ht, names_pt, inp);
        break;

      case 's':
        inp++;
        change_score(games_ht, inp);
        break;

      case 'A':
        inp++;
        teams_contiguous = new_team(teams_ht, teams_contiguous, teamc_pt, teams_sz_pt, inp);
        break;

      case 'P':
        inp++;
        find_team(teams_ht, inp);
        break;

      case 'g':
        inp++;
        best_teams(teams_contiguous, teamc, inp);
        break;

    }

  }

  clear_system(games_ht, names_pt, teams_ht, teams_contiguous, teamc_pt);
  return 0;
}

void new_game(games **games_ht, game_names **name_list, teams **teams_ht, int inp)
{
  int hash_id;
  int sc1;
  int sc2;
  char name[1024];
  char t1[1024];
  char t2[1024];
  games *new;
  teams *team1;
  teams *team2;
  teams *winner;
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
  sc1 = new_sym_var(sizeof(int) * 8);
  sc2 = new_sym_var(sizeof(int) * 8);
  if (search_game(name, games_ht) != 0)
  {
    printf("%d Jogo existente.\n", inp);
    return;
  }
  else
  {
    
  }

  if (((team1 = search_team(t1, teams_ht)) == 0) || ((team2 = search_team(t2, teams_ht)) == 0))
  {
    printf("%d Equipa inexistente.\n", inp);
    return;
  }
  else
  {
    
  }

  hash_id = hash(name, 23269);
  new = new_game_at_end(&games_ht[hash_id]);
  new_name(name, name_list);
  new->name = (*name_list)->last;
  new->name->game = new;
  new->team1 = team1;
  new->team2 = team2;
  new->sc[0] = sc1;
  new->sc[1] = sc2;
  winner = get_winner(new);
  if (winner != 0)
  {
    winner->wins++;
  }
  else
  {
    
  }

}

void list_games(game_names *names, int inp)
{
  for (; names != 0; names = names->next)
  {
    games *game = names->game;
    printf("%d %s %s %s %d %d\n", inp, game->name->name, game->team1->name, game->team2->name, game->sc[0], game->sc[1]);
  }

}

void find_game(games **games_ht, int inp)
{
  char name[1024];
  games *game;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  if ((game = search_game(name, games_ht)) == 0)
  {
    printf("%d Jogo inexistente.\n", inp);
    return;
  }
  else
  {
    
  }

  printf("%d %s %s %s %d %d\n", inp, game->name->name, game->team1->name, game->team2->name, game->sc[0], game->sc[1]);
}

void del_game(games **games_ht, game_names **names_pt, int inp)
{
  int hash_id;
  char name[20];
  games *game;
  games **head;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  game = search_game(name, games_ht);
  if (game == 0)
  {
    printf("%d Jogo inexistente.\n", inp);
    return;
  }
  else
  {
    
  }

  hash_id = hash(name, 23269);
  head = &games_ht[hash_id];
  elim_game(game, head, names_pt);
}

void change_score(games **games_ht, int inp)
{
  int sc1;
  int sc2;
  char name[1024];
  games *game;
  teams *winner;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  sc1 = new_sym_var(sizeof(int) * 8);
  sc2 = new_sym_var(sizeof(int) * 8);
  if ((game = search_game(name, games_ht)) == 0)
  {
    printf("%d Jogo inexistente.\n", inp);
    return;
  }
  else
  {
    
  }

  winner = get_winner(game);
  if (winner != 0)
  {
    winner->wins--;
  }
  else
  {
    
  }

  game->sc[0] = sc1;
  game->sc[1] = sc2;
  winner = get_winner(game);
  if (winner != 0)
  {
    winner->wins++;
  }
  else
  {
    
  }

}

teams **new_team(teams **teams_ht, teams **teams_contiguous, int *teamc, int *teams_sz, int inp)
{
  int hash_id;
  char name[1024];
  teams *new;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  if (search_team(name, teams_ht) != 0)
  {
    printf("%d Equipa existente.\n", inp);
    return teams_contiguous;
  }
  else
  {
    
  }

  hash_id = hash(name, 23269);
  new = new_team_at_end(&teams_ht[hash_id]);
  new->name = malloc((strlen(name) + 1) * (sizeof(char)));
  strcpy(new->name, name);
  if ((*teamc) >= (*teams_sz))
  {
    *teams_sz *= 2;
    teams_contiguous = realloc(teams_contiguous, (*teams_sz) * (sizeof(teams *)));
  }
  else
  {
    
  }

  teams_contiguous[(*teamc)++] = new;
  return teams_contiguous;
}

void find_team(teams **teams_ht, int inp)
{
  char name[1024];
  teams *team;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  if ((team = search_team(name, teams_ht)) == 0)
  {
    printf("%d Equipa inexistente.\n", inp);
    return;
  }
  else
  {
    
  }

  printf("%d %s %d\n", inp, name, count_wins(team));
}

void best_teams(teams **teams_contig, int teamc, int inp)
{
  int i;
  int k;
  int most_wins = 0;
  int bestc = 0;
  int *team_wins;
  int *best;
  if (teamc == 0)
  {
    return;
  }
  else
  {
    
  }

  team_wins = malloc(teamc * (sizeof(int)));
  for (i = 0; i < teamc; i++)
  {
    int winc;
    if ((winc = count_wins(teams_contig[i])) > most_wins)
    {
      most_wins = winc;
      bestc = 1;
    }
    else
    {
      if (winc == most_wins)
      {
        bestc++;
      }
      else
      {
        
      }

    }

    team_wins[i] = winc;
  }

  best = malloc(bestc * (sizeof(int)));
  for (i = 0, k = 0; k < bestc; i++)
  {
    if (team_wins[i] == most_wins)
    {
      best[k++] = i;
    }
    else
    {
      
    }

  }

  merge_sort(best, teams_contig, 0, bestc - 1, ab_ordered);
  printf("%d Melhores %d\n", inp, most_wins);
  for (i = 0; i < bestc; i++)
    printf("%d * %s\n", inp, teams_contig[best[i]]->name);

  free(team_wins);
  free(best);
}

