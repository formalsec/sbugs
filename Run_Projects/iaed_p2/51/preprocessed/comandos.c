/*File generated by PreProcessor.py*/


#include "comandos.h"


void processa_equipas(Bt **bt, Lp **lp, char *equipa1, char *equipa2, int score1, int score2, void operacao(Team *))
{
  Team *vencedora;
  if (score1 != score2)
  {
    {
      if (score1 > score2)
      {
        {
          vencedora = (Team *) search_item_lp(*lp, equipa1, key_team_lp, hash);
        }
      }
      else
      {
        {
          vencedora = (Team *) search_item_lp(*lp, equipa2, key_team_lp, hash);
        }
      }

      (*bt)->root = remove_item_bt(vencedora, (*bt)->root, key_team_bt, free_team);
      operacao(vencedora);
      (*bt)->root = add_item_bt(vencedora, (*bt)->root, key_team_bt);
    }
  }
  else
  {
    
  }

}

void adiciona_jogo(List **lista, Lp **lp1, Bt **bt, Lp **lp2, int linha)
{
  char buffer1[1024];
  char buffer2[1024];
  char buffer3[1024];
  int arg1;
  int arg2;
  for (int buffer1_index = 0; buffer1_index < 10; buffer1_index++)
  {
    buffer1[buffer1_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer1[10 - 1] = '\0';
  for (int buffer2_index = 0; buffer2_index < 10; buffer2_index++)
  {
    buffer2[buffer2_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer2[10 - 1] = '\0';
  for (int buffer3_index = 0; buffer3_index < 10; buffer3_index++)
  {
    buffer3[buffer3_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer3[10 - 1] = '\0';
  arg1 = new_sym_var(sizeof(int) * 8);
  arg2 = new_sym_var(sizeof(int) * 8);
  if (search_item_lp(*lp1, buffer1, key_game, hash) != 0)
  {
    {
      printf("%d Jogo existente.\n", linha);
    }
  }
  else
  {
    if ((search_item_lp(*lp2, buffer2, key_team_lp, hash) == 0) || (search_item_lp(*lp2, buffer3, key_team_lp, hash) == 0))
    {
      {
        printf("%d Equipa inexistente.\n", linha);
      }
    }
    else
    {
      {
        Game *jogo;
        Node_list *no;
        jogo = new_game(buffer1, buffer2, buffer3, arg1, arg2);
        no = add_node_list(*lista, jogo);
        *lp1 = add_item_lp(*lp1, no, key_game, hash);
        processa_equipas(bt, lp2, buffer2, buffer3, arg1, arg2, add_win);
      }
    }

  }

}

void adiciona_equipa(Bt **bt, Lp **lp, int linha)
{
  char buffer[1024];
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  if (search_item_lp(*lp, buffer, key_team_lp, hash) != 0)
  {
    {
      printf("%d Equipa existente.\n", linha);
    }
  }
  else
  {
    {
      Team *equipa;
      equipa = new_team(buffer);
      (*bt)->root = add_item_bt(equipa, (*bt)->root, key_team_bt);
      *lp = add_item_lp(*lp, equipa, key_team_lp, hash);
    }
  }

}

void lista_jogos(List **lista, int linha)
{
  print_list(*lista, linha, print_game_list);
}

void procura_jogo(Lp **lp, int linha)
{
  char buffer[1024];
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  if (search_item_lp(*lp, buffer, key_game, hash) == 0)
  {
    {
      printf("%d Jogo inexistente.\n", linha);
    }
  }
  else
  {
    {
      Game *jogo;
      Node_list *no;
      no = (Node_list *) search_item_lp(*lp, buffer, key_game, hash);
      jogo = no->item;
      printf("%d ", linha);
      print_game(jogo);
    }
  }

}

void procura_equipa(Lp **lp, int linha)
{
  char buffer[1024];
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  if (search_item_lp(*lp, buffer, key_team_lp, hash) == 0)
  {
    {
      printf("%d Equipa inexistente.\n", linha);
    }
  }
  else
  {
    {
      void *equipa;
      equipa = search_item_lp(*lp, buffer, key_team_lp, hash);
      printf("%d ", linha);
      print_team_lp(equipa);
    }
  }

}

void apaga_jogo(List **lista, Lp **lp1, Bt **bt, Lp **lp2, int linha)
{
  char buffer[1024];
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  if (search_item_lp(*lp1, buffer, key_game, hash) == 0)
  {
    {
      printf("%d Jogo inexistente.\n", linha);
    }
  }
  else
  {
    {
      Node_list *no;
      Game *jogo;
      no = (Node_list *) search_item_lp(*lp1, buffer, key_game, hash);
      jogo = no->item;
      processa_equipas(bt, lp2, jogo->team1, jogo->team2, jogo->score_team1, jogo->score_team2, remove_win);
      no = delete_item_lp(*lp1, jogo->name, key_game, hash);
      *lista = remove_node_list(*lista, no, free_game);
    }
  }

}

void altera_score(Lp **lp1, Bt **bt, Lp **lp2, int linha)
{
  char buffer[1024];
  int arg1;
  int arg2;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  arg1 = new_sym_var(sizeof(int) * 8);
  arg2 = new_sym_var(sizeof(int) * 8);
  if (search_item_lp(*lp1, buffer, key_game, hash) == 0)
  {
    {
      printf("%d Jogo inexistente.\n", linha);
    }
  }
  else
  {
    {
      Node_list *no;
      Game *jogo;
      no = (Node_list *) search_item_lp(*lp1, buffer, key_game, hash);
      jogo = no->item;
      processa_equipas(bt, lp2, jogo->team1, jogo->team2, jogo->score_team1, jogo->score_team2, remove_win);
      change_score(jogo, arg1, arg2);
      processa_equipas(bt, lp2, jogo->team1, jogo->team2, arg1, arg2, add_win);
    }
  }

}

int my_strcmp(const void *a, const void *b)
{
  Team **el1;
  Team **el2;
  char *v1;
  char *v2;
  el1 = (Team **) a;
  el2 = (Team **) b;
  v1 = (*el1)->name;
  v2 = (*el2)->name;
  return strcmp(v1, v2);
}

void encontra_equipas(Bt **bt, int linha)
{
  int contador;
  int n_equipas;
  int vitorias;
  Team **equipas;
  if (!empty_bt((*bt)->root))
  {
    {
      n_equipas = max_bt((*bt)->root)->count;
      equipas = (Team **) max_bt((*bt)->root)->items;
      qsort(equipas, n_equipas, sizeof(char *), my_strcmp);
      vitorias = equipas[0]->wins;
      printf("%d Melhores %d\n", linha, vitorias);
      for (contador = 0; contador < n_equipas; contador++)
      {
        printf("%d ", linha);
        print_team_bt(equipas[contador]);
      }

    }
  }
  else
  {
    
  }

}

void liberta_estruturas(List *lista, Lp *lp1, Bt *bt, Lp *lp2)
{
  free_lp(lp1);
  free_lp(lp2);
  free_list(lista, free_game);
  free_bt(bt, free_team);
}

