/*File generated by PreProcessor.py*/


#include "hash.h"


Hash_table init_HT()
{
  Hash_table HT;
  int i;
  HT.heads = malloc((sizeof(Node_team)) * 1777);
  for (i = 0; i < 1777; i++)
  {
    HT.heads[i] = 0;
  }

  return HT;
}

int hash(char *nome)
{
  int h = 0;
  int a = 127;
  for (; (*nome) != '\0'; nome++)
  {
    h = ((a * h) + (*nome)) % 1777;
  }

  return h;
}

void HT_insert(Hash_table HT, char *nome)
{
  int i = hash(nome);
  HT.heads[i] = insert_begin(HT.heads[i], nome);
}

Node_team *search_HT(Hash_table HT, char *nome)
{
  int i = hash(nome);
  return search_team(HT.heads[i], nome);
}

void clear_ht(Hash_table HT)
{
  int i;
  for (i = 0; i < 1777; i++)
  {
    HT.heads[i] = clear_node_team(HT.heads[i]);
    free(HT.heads[i]);
  }

  free(HT.heads);
}

Hash_table_games init_HT_games()
{
  Hash_table_games HTG;
  int i;
  HTG.heads = malloc((sizeof(Node_g_ht)) * 1777);
  for (i = 0; i < 1777; i++)
  {
    HTG.heads[i] = 0;
  }

  return HTG;
}

void HT_games_insert(Hash_table_games HTG, Node_game *head, char *nome_jogo)
{
  int i = hash(nome_jogo);
  HTG.heads[i] = insert_begin_games(HTG.heads[i], head);
}

Node_g_ht *search_HTG(Hash_table_games HTG, char *nome)
{
  int i = hash(nome);
  return search_game_lst(HTG.heads[i], nome);
}

void clear_ht_games(Hash_table_games HTG)
{
  int i;
  for (i = 0; i < 1777; i++)
  {
    HTG.heads[i] = clear_lst_node_g_ht(HTG.heads[i]);
    free(HTG.heads[i]);
  }

  free(HTG.heads);
}

