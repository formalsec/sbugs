/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct team
{
  char *team_name;
  int n_victories;
} *Teams;
typedef struct node
{
  Teams T;
  struct node *next;
  struct node *prev;
} *link;
typedef struct game
{
  char *game_name;
  link teams[2];
  int score[2];
  int ID;
} *Games;
typedef struct node_games
{
  Games G;
  struct node_games *next;
  struct node_games *prev;
} *link_games;
link *Init(int m)
{
  link *heads;
  int i;
  heads = malloc(m * (sizeof(link)));
  for (i = 0; i < m; i++)
    heads[i] = 0;

  return heads;
}

link_games *Init_Games(int m)
{
  link_games *heads;
  int i;
  heads = malloc(m * (sizeof(link_games)));
  for (i = 0; i < m; i++)
    heads[i] = 0;

  return heads;
}

int hash(char *new)
{
  char i = new[0];
  return i - 'A';
}

link NEW_T(Teams new_team)
{
  link node = malloc(sizeof(struct node));
  node->T = new_team;
  node->next = 0;
  node->prev = 0;
  node->T->n_victories = 0;
  return node;
}

link insert_midle(link node, Teams new_team)
{
  link new_node = NEW_T(new_team);
  new_node->prev = node->prev;
  node->prev->next = new_node;
  new_node->next = node;
  return new_node;
}

void print(link head)
{
  link t;
  for (t = head; t != 0; t = t->next)
    printf("%s\n", t->T->team_name);

}

link *new_node(link *head, Teams new_team)
{
  link node;
  int m;
  int flag = 0;
  m = hash(new_team->team_name);
  if (head[m] == 0)
  {
    head[m] = NEW_T(new_team);
  }
  else
  {
    {
      for (node = head[m]; node != 0; node = node->next)
      {
        if (strcmp(node->T->team_name, new_team->team_name) > 0)
        {
          {
            if (node->prev == 0)
            {
              {
                node = NEW_T(new_team);
                node->next = head[m];
                head[m]->prev = node;
                head[m] = node;
                flag = 1;
                break;
              }
            }
            else
            {
              {
                node->prev = insert_midle(node, new_team);
                flag = 1;
                break;
              }
            }

          }
        }
        else
        {
          
        }

      }

      if (flag == 0)
      {
        {
          for (node = head[m]; node->next != 0; node = node->next)
          {
          }

          node->next = NEW_T(new_team);
        }
      }
      else
      {
        
      }

    }
  }

  return head;
}

link search(char *name, link *head)
{
  link node;
  int m;
  m = hash(name);
  if (head[m] != 0)
  {
    {
      for (node = head[m]; node != 0; node = node->next)
      {
        if (strcmp(node->T->team_name, name) == 0)
        {
          {
            return node;
          }
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

  return 0;
}

link_games search_game(char *name, link_games *head)
{
  link_games node;
  int m;
  m = hash(name);
  if (head[m] != 0)
  {
    {
      for (node = head[m]; node != 0; node = node->next)
      {
        if (strcmp(node->G->game_name, name) == 0)
        {
          {
            return node;
          }
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

  return 0;
}

void print_games(link_games head)
{
  link_games t;
  for (t = head; t != 0; t = t->next)
    printf("%s\n", t->G->game_name);

}

link *add_team(int NL, link *heads)
{
  Teams new_team = malloc(sizeof(struct team));
  char e_temp[1024];
  int flag = 0;
  for (int e_temp_index = 0; e_temp_index < 10; e_temp_index++)
  {
    e_temp[e_temp_index] = new_sym_var(sizeof(char) * 8);
  }

  e_temp[10 - 1] = '\0';
  new_team->n_victories = 0;
  new_team->team_name = malloc((strlen(e_temp) + 1) * (sizeof(char)));
  strcpy(new_team->team_name, e_temp);
  if (search(new_team->team_name, heads) != 0)
  {
    {
      printf("%d Equipa existente.\n", NL);
      free(new_team->team_name);
      free(new_team);
      flag = 1;
    }
  }
  else
  {
    
  }

  if (flag == 0)
  {
    heads = new_node(heads, new_team);
  }
  else
  {
    
  }

  return heads;
}

void free_node(link_games node)
{
  free(node->G->game_name);
  free(node->G);
  free(node);
}

link_games *delete_game(int NL, link_games *heads)
{
  char g_temp[1024];
  int m;
  int flag = 0;
  link_games node;
  for (int g_temp_index = 0; g_temp_index < 10; g_temp_index++)
  {
    g_temp[g_temp_index] = new_sym_var(sizeof(char) * 8);
  }

  g_temp[10 - 1] = '\0';
  m = hash(g_temp);
  for (node = heads[m]; node != 0; node = node->next)
  {
    if (strcmp(node->G->game_name, g_temp) == 0)
    {
      {
        if (node->prev == 0)
        {
          {
            free_node(heads[m]);
            heads[m] = 0;
          }
        }
        else
        {
          if (node->next == 0)
          {
            {
              node->prev->next = 0;
              free_node(node);
              break;
            }
          }
          else
          {
            {
              node->prev->next = node->next;
              node->next->prev = node->prev;
              free_node(node);
            }
          }

        }

        flag = 1;
      }
    }
    else
    {
      
    }

  }

  if (flag == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
  }
  else
  {
    
  }

  if (flag == 1)
  {
    printf("%d Jogo existente.\n", NL);
  }
  else
  {
    
  }

  return heads;
}

void search_team(int NL, link *heads)
{
  char e_temp[1024];
  link node;
  for (int e_temp_index = 0; e_temp_index < 10; e_temp_index++)
  {
    e_temp[e_temp_index] = new_sym_var(sizeof(char) * 8);
  }

  e_temp[10 - 1] = '\0';
  if ((node = search(e_temp, heads)) == 0)
  {
    printf("%d Equipa inexistente.\n", NL);
  }
  else
  {
    printf("%d %s %d\n", NL, node->T->team_name, node->T->n_victories);
  }

}

link_games NEW_G(Games new_game)
{
  link_games node = malloc(sizeof(struct node_games));
  node->G = new_game;
  node->next = 0;
  node->prev = 0;
  return node;
}

link_games insert_midle_games(link_games node, Games new_game)
{
  link_games new_node = NEW_G(new_game);
  new_node->prev = node->prev;
  node->prev->next = new_node;
  new_node->next = node;
  return new_node;
}

link_games *new_node_game(link_games *head, Games new_game)
{
  link_games node;
  link_games last_node;
  int m;
  int flag = 0;
  m = hash(new_game->game_name);
  if (head[m] == 0)
  {
    {
      head[m] = NEW_G(new_game);
    }
  }
  else
  {
    {
      last_node = 0;
      for (node = head[m]; node != 0; node = node->next)
      {
        last_node = node;
        if (strcmp(node->G->game_name, new_game->game_name) > 0)
        {
          {
            if (node->prev == 0)
            {
              {
                node = NEW_G(new_game);
                node->next = head[m];
                head[m]->prev = node;
                head[m] = node;
                flag = 1;
                break;
              }
            }
            else
            {
              {
                node->prev = insert_midle_games(node, new_game);
                flag = 1;
                break;
              }
            }

          }
        }
        else
        {
          
        }

      }

      if (flag == 0)
      {
        {
          last_node->next = NEW_G(new_game);
          last_node->next->prev = last_node;
        }
      }
      else
      {
        
      }

    }
  }

  return head;
}

void victories(Games new_game)
{
  if (new_game->score[0] > new_game->score[1])
  {
    new_game->teams[0]->T->n_victories++;
  }
  else
  {
    
  }

  if (new_game->score[0] < new_game->score[1])
  {
    new_game->teams[1]->T->n_victories++;
  }
  else
  {
    
  }

}

link_games *add_games(int NL, link_games *heads_games, link *heads_teams, int id)
{
  char e_temp1[1024];
  char e_temp2[1024];
  char g_temp[1024];
  int score1;
  int score2;
  int flag = 0;
  Games new;
  for (int g_temp_index = 0; g_temp_index < 10; g_temp_index++)
  {
    g_temp[g_temp_index] = new_sym_var(sizeof(char) * 8);
  }

  g_temp[10 - 1] = '\0';
  for (int e_temp1_index = 0; e_temp1_index < 10; e_temp1_index++)
  {
    e_temp1[e_temp1_index] = new_sym_var(sizeof(char) * 8);
  }

  e_temp1[10 - 1] = '\0';
  for (int e_temp2_index = 0; e_temp2_index < 10; e_temp2_index++)
  {
    e_temp2[e_temp2_index] = new_sym_var(sizeof(char) * 8);
  }

  e_temp2[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  if (search(e_temp1, heads_teams) != 0)
  {
    {
      if (search(e_temp2, heads_teams) != 0)
      {
        {
          flag = 1;
          if (search_game(g_temp, heads_games) == 0)
          {
            {
              new = malloc(sizeof(struct game));
              new->score[0] = score1;
              new->score[1] = score2;
              new->game_name = malloc((strlen(g_temp) + 1) * (sizeof(char)));
              strcpy(new->game_name, g_temp);
              new->teams[0] = search(e_temp1, heads_teams);
              new->teams[1] = search(e_temp2, heads_teams);
              new->ID = id;
              victories(new);
              heads_games = new_node_game(heads_games, new);
              flag = 2;
            }
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
  else
  {
    
  }

  if (flag == 0)
  {
    printf("%d Equipa inexistente.\n", NL);
  }
  else
  {
    
  }

  if (flag == 1)
  {
    printf("%d Jogo existente.\n", NL);
  }
  else
  {
    
  }

  return heads_games;
}

void search_games(int NL, link_games *heads_games)
{
  char g_temp[1024];
  link_games node;
  for (int g_temp_index = 0; g_temp_index < 10; g_temp_index++)
  {
    g_temp[g_temp_index] = new_sym_var(sizeof(char) * 8);
  }

  g_temp[10 - 1] = '\0';
  if ((node = search_game(g_temp, heads_games)) == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
  }
  else
  {
    printf("%d %s %s %s %d %d\n", NL, node->G->game_name, node->G->teams[0]->T->team_name, node->G->teams[1]->T->team_name, node->G->score[0], node->G->score[1]);
  }

}

link_games *change_score(int NL, link_games *heads_games)
{
  char g_temp[1024];
  int score1;
  int score2;
  link_games game;
  for (int g_temp_index = 0; g_temp_index < 10; g_temp_index++)
  {
    g_temp[g_temp_index] = new_sym_var(sizeof(char) * 8);
  }

  g_temp[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  game = search_game(g_temp, heads_games);
  if (game == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
  }
  else
  {
    {
      if (((game->G->score[0] - game->G->score[1]) > 0) && ((score1 - score2) > 0))
      {
        {
          game->G->score[0] = score1;
          game->G->score[1] = score2;
        }
      }
      else
      {
        
      }

      if (((game->G->score[0] - game->G->score[1]) < 0) && ((score1 - score2) < 0))
      {
        {
          game->G->score[0] = score1;
          game->G->score[1] = score2;
        }
      }
      else
      {
        
      }

      if (((game->G->score[0] - game->G->score[1]) > 0) && ((score1 - score2) < 0))
      {
        {
          game->G->score[0] = score1;
          game->G->score[1] = score2;
          game->G->teams[0]->T->n_victories--;
          game->G->teams[1]->T->n_victories++;
        }
      }
      else
      {
        
      }

      if (((game->G->score[0] - game->G->score[1]) < 0) && ((score1 - score2) > 0))
      {
        {
          game->G->score[0] = score1;
          game->G->score[1] = score2;
          game->G->teams[0]->T->n_victories++;
          game->G->teams[1]->T->n_victories--;
        }
      }
      else
      {
        {
          game->G->score[0] = score1;
          game->G->score[1] = score2;
        }
      }

    }
  }

  return heads_games;
}

void list_teams(link *heads_teams)
{
  link node;
  link temp;
  link temp1;
  link begin_node;
  Teams begin;
  int i;
  int count = -1;
  begin = malloc(sizeof(struct game));
  begin_node = NEW_T(begin);
  for (i = 0; i < 58; i++)
  {
    for (temp1 = heads_teams[i]; temp1 != 0; temp1 = temp1->next)
    {
      if (temp1->T->n_victories > count)
      {
        {
          count = temp1->T->n_victories;
          node = NEW_T(temp1->T);
          begin_node->next = node;
          node->prev = begin_node;
        }
      }
      else
      {
        if (temp1->T->n_victories == count)
        {
          {
            for (temp = begin_node; temp->next != 0; temp = temp->next)
            {
            }

            node = NEW_T(temp1->T);
            node->prev = temp;
            temp->next = node;
          }
        }
        else
        {
          
        }

      }

    }

  }

  print(begin_node->next);
  for (temp = begin_node; temp->next != 0; temp = temp->next)
  {
  }

  while (temp->prev != 0)
  {
    temp = temp->prev;
    free(temp->next);
  }

  free(temp);
}

void list_games(int NL, link_games *heads)
{
  int i;
  int j;
  int max_array_size = 10;
  int array_size = 0;
  link_games *array = malloc(max_array_size * (sizeof(link_games)));
  link_games temp;
  for (i = 0; i < 58; i++)
  {
    for (temp = heads[i]; temp != 0; temp = temp->next)
    {
      if (array_size == max_array_size)
      {
        {
          max_array_size *= 2;
          array = realloc(array, max_array_size * (sizeof(link_games)));
        }
      }
      else
      {
        
      }

      for (j = array_size; (j > 0) && (array[j - 1]->G->ID > temp->G->ID); j--)
        array[j] = array[j - 1];

      array[j] = temp;
      array_size++;
    }

  }

  for (i = 0; i < array_size; i++)
    printf("%d %s %s %s %d %d\n", NL, array[i]->G->game_name, array[i]->G->teams[0]->T->team_name, array[i]->G->teams[1]->T->team_name, array[i]->G->score[0], array[i]->G->score[1]);

  free(array);
}

void free_teams(link *heads)
{
  int i;
  link temp;
  for (i = 0; i < 58; i++)
    while (heads[i] != 0)
  {
    temp = heads[i]->next;
    free(heads[i]->T->team_name);
    free(heads[i]->T);
    free(heads[i]);
    heads[i] = temp;
  }


  free(heads);
}

void free_games(link_games *heads)
{
  int i;
  link_games temp;
  for (i = 0; i < 58; i++)
    while (heads[i] != 0)
  {
    temp = heads[i]->next;
    free(heads[i]->G->game_name);
    free(heads[i]->G);
    free(heads[i]);
    heads[i] = temp;
  }


  free(heads);
}

int main()
{
  int NL = 0;
  int id_jogo = -1;
  char comando = '\0';
  link *heads_teams;
  link_games *heads_games;
  heads_teams = Init(58);
  heads_games = Init_Games(58);
  while (comando != 'x')
  {
    comando = new_sym_var(sizeof(char) * 8);
    switch (comando)
    {
      case 'a':
        NL++;
        id_jogo++;
        heads_games = add_games(NL, heads_games, heads_teams, id_jogo);
        break;

      case 'A':
        NL++;
        heads_teams = add_team(NL, heads_teams);
        break;

      case 'l':
        NL++;
        list_games(NL, heads_games);
        break;

      case 'p':
        NL++;
        search_games(NL, heads_games);
        break;

      case 'P':
        NL++;
        search_team(NL, heads_teams);
        break;

      case 'r':
        NL++;
        heads_games = delete_game(NL, heads_games);
        break;

      case 's':
        NL++;
        heads_games = change_score(NL, heads_games);
        break;

      case 'g':
        NL++;
        list_teams(heads_teams);
        break;

    }

  }

  free_teams(heads_teams);
  free_games(heads_games);
  return 0;
}

