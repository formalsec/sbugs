#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"


game *mk_game(char *name, team *team1, team *team2, int score1, int score2)
{
  game *new_game = malloc(sizeof(game));
  new_game->name = malloc((strlen(name) + 1) * (sizeof(char)));
  strcpy(new_game->name, name);
  new_game->team1 = team1;
  new_game->team2 = team2;
  new_game->score1 = score1;
  new_game->score2 = score2;
  if (score1 > score2)
  {
    team1->wins++;
  }
  else
  {
    
  }

  if (score2 > score1)
  {
    team2->wins++;
  }
  else
  {
    
  }

  return new_game;
}

void set_game_score(game *gm, int score1, int score2)
{
  int dif1 = 0;
  int dif2 = 0;
  if (gm->score1 > gm->score2)
  {
    dif1--;
  }
  else
  {
    
  }

  if (gm->score2 > gm->score1)
  {
    dif2--;
  }
  else
  {
    
  }

  if (score1 > score2)
  {
    dif1++;
  }
  else
  {
    
  }

  if (score2 > score1)
  {
    dif2++;
  }
  else
  {
    
  }

  gm->team1->wins += dif1;
  gm->team2->wins += dif2;
  gm->score1 = score1;
  gm->score2 = score2;
  return;
}

void print_game(int line, game *gm)
{
  printf("%d %s %s %s %d %d\n", line, gm->name, gm->team1->name, gm->team2->name, gm->score1, gm->score2);
  return;
}

void free_game(game *gm)
{
  set_game_score(gm, 0, 0);
  free(gm->name);
  free(gm);
  return;
}

