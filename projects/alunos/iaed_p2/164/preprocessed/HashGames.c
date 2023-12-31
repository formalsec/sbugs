#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "HashGames.h"


int hash(char *v, int *M)
{
  int h = 0;
  int a = 127;
  for (; (*v) != '\0'; v++)
    h = ((a * h) + (*v)) % (*M);

  return h;
}

Node *HashGamesInit(int *m)
{
  int i;
  Node *hash_table;
  hash_table = (Node *) malloc((sizeof(Node)) * (*m));
  for (i = 0; i < (*m); i++)
    hash_table[i] = 0;

  return hash_table;
}

void HashGamesInsert(Node *hash_table, Node node, int *m)
{
  int i = hash(GameName(NodeGame(node)), m);
  while (hash_table[i] != 0)
    i = (i + 1) % (*m);

  hash_table[i] = node;
}

int GameSearch(char *name, int *m, Node *hash_table)
{
  int i = hash(name, m);
  while (hash_table[i] != 0)
  {
    if (!strcmp(GameName(NodeGame(hash_table[i])), name))
    {
      return i;
    }
    else
    {
      i = (i + 1) % (*m);
    }

  }

  return -1;
}

Node HashRemoveGame(char *name, int *m, Node *hash_table)
{
  int j;
  int i = GameSearch(name, m, hash_table);
  Node aux;
  Node node;
  if (i == (-1))
  {
    return 0;
  }
  else
  {
    
  }

  node = hash_table[i];
  hash_table[i] = 0;
  for (j = (i + 1) % (*m); hash_table[j] != 0; j = (j + 1) % (*m))
  {
    aux = hash_table[j];
    hash_table[j] = 0;
    HashGamesInsert(hash_table, aux, m);
  }

  return node;
}

void DestroyHashGames(Node *hash_games)
{
  free(hash_games);
}

Node *ExpandGames(Node *hash_game, int *n_games, int *m)
{
  int i = 0;
  int count = 0;
  Node *new_hash_game;
  *m *= 2;
  new_hash_game = HashGamesInit(m);
  for (; count < (*n_games); i++)
    if (hash_game[i] != 0)
  {
    HashGamesInsert(new_hash_game, hash_game[i], m);
    count++;
  }
  else
  {
    
  }


  free(hash_game);
  return new_hash_game;
}

