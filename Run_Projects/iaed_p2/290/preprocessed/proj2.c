/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char command;
int input_line = 0;
char team[1023];
char team1[1023];
char team2[1023];
char game[1023];
int score1;
int score2;
typedef struct Team
{
  char *name;
  struct Team *next;
} *link;
typedef struct Game
{
  char *name;
  char *team1;
  char *team2;
  int score1;
  int score2;
  struct Game *next;
} *link2;
link NEW(char *buffer)
{
  link x = malloc(sizeof(struct Team));
  x->name = malloc((sizeof(char)) * (strlen(buffer) + 1));
  strcpy(x->name, buffer);
  x->next = 0;
  return x;
}

link insertEnd(link head, char *name)
{
  link x;
  if (head == 0)
  {
    return NEW(name);
  }
  else
  {
    
  }

  for (x = head; x->next != 0; x = x->next)
    ;

  x->next = NEW(name);
  return head;
}

int add_new_team()
{
  command = new_sym_var(sizeof(char) * 8);
  for (int team_index = 0; team_index < 10; team_index++)
  {
    team[team_index] = new_sym_var(sizeof(char) * 8);
  }

  team[10 - 1] = '\0';
  link head;
  link t;
  for (t = head; t != 0; t = t->next)
    if (strcmp(t->name, team) == 0)
  {
    printf("Equipa existente\n");
  }
  else
  {
    
  }


  insertEnd(head, team);
  return 0;
}

link2 NEW2(char *buffer)
{
  link2 x = malloc(sizeof(struct Game));
  x->name = malloc((sizeof(char)) * (strlen(buffer) + 1));
  strcpy(x->name, buffer);
  x->next = 0;
  return x;
}

link2 insertEnd2(link2 head, char *name)
{
  link2 x;
  if (head == 0)
  {
    return NEW2(name);
  }
  else
  {
    
  }

  for (x = head; x->next != 0; x = x->next)
    ;

  x->next = NEW2(name);
  return head;
}

int add_new_game()
{
  command = new_sym_var(sizeof(char) * 8);
  for (int game_index = 0; game_index < 10; game_index++)
  {
    game[game_index] = new_sym_var(sizeof(char) * 8);
  }

  game[10 - 1] = '\0';
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
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  link Head;
  while (Head != 0)
  {
    if (strcmp(Head->name, team1) == 0)
    {
      printf("%d Equipa inexistente\n", input_line);
    }
    else
    {
      
    }

    if (strcmp(Head->name, team2) == 0)
    {
      printf("%d Equipa inexistente\n", input_line);
    }
    else
    {
      
    }

    Head = Head->next;
  }

  link2 head;
  link2 t;
  for (t = head; t != 0; t = t->next)
  {
    if (strcmp(t->name, game) == 0)
    {
      printf("%d Jogo existente\n", input_line);
    }
    else
    {
      
    }

    insertEnd2(head, game);
  }

  return 0;
}

int list_games()
{
  link2 head;
  link2 t;
  for (t = head; t != 0; t = t->next)
    printf("%d %s\n", input_line, t->name);

  return 0;
}

int search_game()
{
  command = new_sym_var(sizeof(char) * 8);
  for (int game_index = 0; game_index < 10; game_index++)
  {
    game[game_index] = new_sym_var(sizeof(char) * 8);
  }

  game[10 - 1] = '\0';
  link2 head;
  link2 t;
  for (t = head; t != 0; t = t->next)
    if (strcmp(t->name, game) == 0)
  {
    printf("%d %s\n", input_line, game);
  }
  else
  {
    
  }


  printf("%d Equipa inexistente\n", input_line);
  return 0;
}

int search_team()
{
  return 0;
}

int delete_game()
{
  command = new_sym_var(sizeof(char) * 8);
  for (int game_index = 0; game_index < 10; game_index++)
  {
    game[game_index] = new_sym_var(sizeof(char) * 8);
  }

  game[10 - 1] = '\0';
  link2 head;
  link2 t;
  link2 prev;
  for (t = head, prev = 0; t != 0; prev = t, t = t->next)
  {
    if (strcmp(t->name, game) == 0)
    {
      {
        if (t == head)
        {
          head = t->next;
        }
        else
        {
          prev->next = t->next;
        }

        free(t->name);
        free(t);
      }
    }
    else
    {
      
    }

  }

  printf("%d Jogo inexistente\n", input_line);
  return 0;
}

int change_score()
{
  return 0;
}

int list_best()
{
  return 0;
}

int main()
{
  char input[10000];
  do
  {
    input_line++;
    for (int input_index = 0; input_index < 10; input_index++)
    {
      input[input_index] = new_sym_var(sizeof(char) * 8);
    }

    input[10 - 1] = '\0';
    command = input[0];
    switch (command)
    {
      case 'a':
        add_new_game();
        break;

      case 'A':
        add_new_team();
        break;

      case 'l':
        list_games();
        break;

      case 'p':
        search_game();
        break;

      case 'P':
        search_team();
        break;

      case 'r':
        delete_game();
        break;

      case 's':
        change_score();
        break;

      case 'g':
        list_best();
        break;

      case 'x':
        return 0;

    }

  }
  while (strcmp(&command, "x") != 0);
  return 0;
}
