/*File generated by PreProcessor.py*/


#include "hash.h"
#include "teams.h"
#include "games.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


Games *init_Glist()
{
  Games *list = malloc(sizeof(Games));
  list->head = 0;
  list->tail = 0;
  return list;
}

void destroy_Glist(Games *games)
{
  game *game_aux;
  while (games->head)
  {
    game_aux = games->head->next;
    free_game_node(games->head);
    games->head = game_aux;
  }

  free(games);
}

void free_game_node(game *game_x)
{
  free(game_x->name);
  free(game_x->t1_name);
  free(game_x->t2_name);
  free(game_x->winner);
  free(game_x);
}

void new_game(Games *games, HashGames *hashtable_games, HashTeams *hashtable_teams, int NL)
{
  char game_name[1024];
  char t1_name[1024];
  char t2_name[1024];
  int score_t1;
  int score_t2;
  for (int game_name_index = 0; game_name_index < 10; game_name_index++)
  {
    game_name[game_name_index] = new_sym_var(sizeof(char) * 8);
  }

  game_name[10 - 1] = '\0';
  for (int t1_name_index = 0; t1_name_index < 10; t1_name_index++)
  {
    t1_name[t1_name_index] = new_sym_var(sizeof(char) * 8);
  }

  t1_name[10 - 1] = '\0';
  for (int t2_name_index = 0; t2_name_index < 10; t2_name_index++)
  {
    t2_name[t2_name_index] = new_sym_var(sizeof(char) * 8);
  }

  t2_name[10 - 1] = '\0';
  score_t1 = new_sym_var(sizeof(int) * 8);
  score_t2 = new_sym_var(sizeof(int) * 8);
  if (verify_conditions_to_add_game(NL, game_name, t1_name, t2_name, hashtable_games, hashtable_teams) != 0)
  {
    {
      game *new_game = alloc_game(game_name, t1_name, t2_name, score_t1, score_t2);
      add_last_game(games, new_game);
      add_game_to_hash(new_game, hashtable_games);
      if (strcmp(new_game->winner, "NONE") != 0)
      {
        sum_win_in_team(new_game->winner, hashtable_teams);
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

int verify_conditions_to_add_game(int NL, char game_name[1024], char t1_name[1024], char t2_name[1024], HashGames *hashtable_games, HashTeams *hashtable_teams)
{
  game *game_x = hash_lookfor_game(hashtable_games, game_name);
  team *team1;
  team *team2;
  if (game_x != 0)
  {
    printf("%d Jogo existente.\n", NL);
  }
  else
  {
    
  }

  team1 = hash_lookfor_team(hashtable_teams, t1_name);
  team2 = hash_lookfor_team(hashtable_teams, t2_name);
  if ((game_x == 0) && ((team1 == 0) || (team2 == 0)))
  {
    printf("%d Equipa inexistente.\n", NL);
  }
  else
  {
    
  }

  return ((team1 != 0) && (team2 != 0)) && (game_x == 0);
}

game *alloc_game(char game_name[1024], char t1_name[1024], char t2_name[1024], int score_t1, int score_t2)
{
  game *new_game = malloc(sizeof(game));
  char winner[1024];
  new_game->next = 0;
  new_game->previous = 0;
  new_game->name = malloc((sizeof(char)) * (strlen(game_name) + 1));
  strcpy(new_game->name, game_name);
  new_game->t1_name = malloc((sizeof(char)) * (strlen(t1_name) + 1));
  strcpy(new_game->t1_name, t1_name);
  new_game->t2_name = malloc((sizeof(char)) * (strlen(t2_name) + 1));
  strcpy(new_game->t2_name, t2_name);
  new_game->score_t1 = score_t1;
  new_game->score_t2 = score_t2;
  strcpy(winner, choose_winner(score_t1, score_t2, t1_name, t2_name));
  new_game->winner = malloc((sizeof(char)) * (strlen(winner) + 1));
  strcpy(new_game->winner, winner);
  return new_game;
}

char *choose_winner(int score_t1, int score_t2, char *t1_name, char *t2_name)
{
  if (score_t1 > score_t2)
  {
    return t1_name;
  }
  else
  {
    if (score_t2 > score_t1)
    {
      return t2_name;
    }
    else
    {
      return "NONE";
    }

  }

}

void add_last_game(Games *games, game *new_game)
{
  if (games->tail)
  {
    games->tail->next = new_game;
  }
  else
  {
    games->head = new_game;
  }

  new_game->previous = games->tail;
  new_game->next = 0;
  games->tail = new_game;
}

void show_all_games(Games *games, int NL)
{
  game *game_x;
  for (game_x = games->head; game_x != 0; game_x = game_x->next)
    printf("%d %s %s %s %d %d\n", NL, game_x->name, game_x->t1_name, game_x->t2_name, game_x->score_t1, game_x->score_t2);

}

void lookfor_game(HashGames *hashtable, int NL)
{
  char game_name[1024];
  game *game_x;
  for (int game_name_index = 0; game_name_index < 10; game_name_index++)
  {
    game_name[game_name_index] = new_sym_var(sizeof(char) * 8);
  }

  game_name[10 - 1] = '\0';
  game_x = hash_lookfor_game(hashtable, game_name);
  if (game_x != 0)
  {
    printf("%d %s %s %s %d %d\n", NL, game_x->name, game_x->t1_name, game_x->t2_name, game_x->score_t1, game_x->score_t2);
  }
  else
  {
    printf("%d Jogo inexistente.\n", NL);
  }

}

void sum_win_in_team(char *team_name, HashTeams *hashtable_teams)
{
  team *team_x = hash_lookfor_team(hashtable_teams, team_name);
  team_x->wins += 1;
}

void remove_game(Games *games, HashGames *hashtable, int NL, HashTeams *hashtable_teams)
{
  char game_name[1024];
  game *game_x;
  for (int game_name_index = 0; game_name_index < 10; game_name_index++)
  {
    game_name[game_name_index] = new_sym_var(sizeof(char) * 8);
  }

  game_name[10 - 1] = '\0';
  game_x = hash_lookfor_game(hashtable, game_name);
  if (game_x != 0)
  {
    {
      int h = hash(game_x->name, hashtable->cap);
      int inc = (1 + (3 * h)) % hashtable->cap;
      if (inc == 0)
      {
        inc++;
      }
      else
      {
        
      }

      while ((hashtable->slots[h].game_slot != 0) || (hashtable->slots[h].occ == 1))
      {
        if ((hashtable->slots[h].game_slot != 0) && (strcmp(hashtable->slots[h].game_slot->name, game_name) == 0))
        {
          {
            if (strcmp(game_x->winner, "NONE") != 0)
            {
              remove_team_win(hashtable_teams, game_x->winner);
            }
            else
            {
              
            }

            erase_game_node(games, game_x, hashtable, h);
          }
        }
        else
        {
          h = (h + inc) % hashtable->cap;
        }

      }

    }
  }
  else
  {
    printf("%d Jogo inexistente.\n", NL);
  }

}

void erase_game_node(Games *games, game *game_x, HashGames *hashtable, int h)
{
  if (game_x->previous == 0)
  {
    games->head = game_x->next;
  }
  else
  {
    game_x->previous->next = game_x->next;
  }

  if (game_x->next == 0)
  {
    games->tail = game_x->previous;
  }
  else
  {
    game_x->next->previous = game_x->previous;
  }

  free_game_node(game_x);
  hashtable->slots[h].game_slot = 0;
}

void change_game_score(HashGames *hashtable_games, HashTeams *hashtable_teams, int NL)
{
  char game_name[1024];
  char new_winner[1024];
  int score_t1;
  int score_t2;
  game *game_x;
  for (int game_name_index = 0; game_name_index < 10; game_name_index++)
  {
    game_name[game_name_index] = new_sym_var(sizeof(char) * 8);
  }

  game_name[10 - 1] = '\0';
  score_t1 = new_sym_var(sizeof(int) * 8);
  score_t2 = new_sym_var(sizeof(int) * 8);
  game_x = hash_lookfor_game(hashtable_games, game_name);
  if (game_x != 0)
  {
    {
      strcpy(new_winner, choose_winner(score_t1, score_t2, game_x->t1_name, game_x->t2_name));
      if (strcmp(new_winner, game_x->winner) != 0)
      {
        change_winner(game_x, new_winner, hashtable_teams);
      }
      else
      {
        
      }

      game_x->score_t1 = score_t1;
      game_x->score_t2 = score_t2;
    }
  }
  else
  {
    printf("%d Jogo inexistente.\n", NL);
  }

}

void change_winner(game *game_x, char *new_winner, HashTeams *hashtable_teams)
{
  if (strcmp(game_x->winner, "NONE") != 0)
  {
    remove_team_win(hashtable_teams, game_x->winner);
  }
  else
  {
    
  }

  if (strcmp(new_winner, "NONE") != 0)
  {
    add_team_win(hashtable_teams, new_winner);
  }
  else
  {
    
  }

  free(game_x->winner);
  game_x->winner = malloc((sizeof(char)) * (strlen(new_winner) + 1));
  strcpy(game_x->winner, new_winner);
}

HashGames *init_HGtable(int size)
{
  int i;
  HashGames *hashtable = malloc(sizeof(HashGames));
  hashtable->slots = malloc((sizeof(Slot)) * size);
  hashtable->size = 0;
  hashtable->cap = size;
  for (i = 0; i < hashtable->cap; i++)
  {
    hashtable->slots[i].occ = 0;
    hashtable->slots[i].game_slot = 0;
  }

  return hashtable;
}

void destroy_HGtable(HashGames *hashtable)
{
  free(hashtable->slots);
  free(hashtable);
}

void add_game_to_hash(game *game_x, HashGames *hashtable)
{
  int h = hash(game_x->name, hashtable->cap);
  int inc = (1 + (3 * h)) % hashtable->cap;
  if (inc == 0)
  {
    inc++;
  }
  else
  {
    
  }

  while (hashtable->slots[h].game_slot != 0)
    h = (h + inc) % hashtable->cap;

  hashtable->slots[h].game_slot = game_x;
  hashtable->slots[h].occ = 1;
  hashtable->size++;
  if (hashtable->size > (hashtable->cap / 2))
  {
    resize_hashtable_games(hashtable);
  }
  else
  {
    
  }

}

game *hash_lookfor_game(HashGames *hashtable, char *name)
{
  int h = hash(name, hashtable->cap);
  int inc = (1 + (3 * h)) % hashtable->cap;
  if (inc == 0)
  {
    inc++;
  }
  else
  {
    
  }

  while ((hashtable->slots[h].game_slot != 0) || (hashtable->slots[h].occ == 1))
  {
    if ((hashtable->slots[h].game_slot != 0) && (strcmp(hashtable->slots[h].game_slot->name, name) == 0))
    {
      return hashtable->slots[h].game_slot;
    }
    else
    {
      h = (h + inc) % hashtable->cap;
    }

  }

  return 0;
}

void resize_hashtable_games(HashGames *hashtable)
{
  int new_cap;
  int new_size = 0;
  Slot *new_slots;
  Slot *old_slots = hashtable->slots;
  new_cap = hashtable->cap * 2;
  while (eh_primo(new_cap) != 1)
    new_cap++;

  new_slots = malloc((sizeof(Slot)) * new_cap);
  init_new_slots(new_slots, new_cap);
  rehash_games(hashtable, new_slots, old_slots, new_cap, new_size);
  hashtable->slots = new_slots;
  hashtable->cap = new_cap;
  hashtable->size = new_size;
  free(old_slots);
}

void init_new_slots(Slot *new_slots, int new_cap)
{
  int i;
  for (i = 0; i < new_cap; i++)
  {
    new_slots[i].occ = 0;
    new_slots[i].game_slot = 0;
  }

}

void rehash_games(HashGames *hashtable, Slot *new_slots, Slot *old_slots, int new_cap, int new_size)
{
  int i;
  int h;
  int inc;
  for (i = 0; i < hashtable->cap; i++)
  {
    if (old_slots[i].game_slot != 0)
    {
      {
        new_size++;
        h = hash(old_slots[i].game_slot->name, new_cap);
        inc = (1 + (3 * h)) % new_cap;
        if (inc == 0)
        {
          inc++;
        }
        else
        {
          
        }

        while (new_slots[h].game_slot != 0)
          h = (h + inc) % new_cap;

        new_slots[h].game_slot = old_slots[i].game_slot;
        new_slots[h].occ = 1;
      }
    }
    else
    {
      
    }

  }

}

