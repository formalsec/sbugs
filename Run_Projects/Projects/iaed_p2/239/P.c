#include "projeto2.h"

/*
ARGUMENTOS: Um nome de uma equipa que se quer procurar
no sistema.

OBJETIVO: Procurar uma equipa dado um nome.
Se a equipa com o nome que se procura nao existir
no sistema, dar o erro "Equipa inexistente". Se a equipa
existir, mostra uma linha com o nome da equipa procurada e
o numero de jogos ganho por essa mesma equipa.
*/

void P(TEAM* hashT[], int row)
{
  TEAM* searcher_team;
  int index;
  char name[MAX_STRING];
  getchar();
  scanf("%[^\n]", name);
  index = hash_function(name);
  searcher_team = hashT[index];

  while(strcmp(searcher_team->name,name) != 0)
  {
    if(searcher_team->link == NULL)
    {
      printf("%d Equipa inexistente.", row);

      return;
    }

    searcher_team = searcher_team->link;
  }

  printf("%d %s %d", row, searcher_team->name, searcher_team->score);

  return;
}
