#include "projeto2.h"

/*
ARGUMENTOS: Nome da equipa a adicionar, com o maximo de 1023 caracteres.

OBJETIVO: Adicionar uma nova equipa ao sistema, verificando se ja existe uma equipa com
o mesmo nome daquela que se pretende adicionar, correndo a lista existente com o nome das
equipas todas que ja se encontram no sistema verificando se ja existe uma equipa com o mesmo 
nome daquela que se pretende adicionar, se chegar o fim da lista e nao existir nenhuma equipa
com o mesmo nome, adiciona-se a nova equipa ao sistema e, se ja existir, deteta-se um erro "Equipa existente".
*/


void A(TEAM* hashT[], int row)
{
  TEAM* new_team;
  int index;
  char name[MAX_STRING];
  TEAM* searcher_team;
  getchar();
  scanf("%[^\n]", name);
  index = hash_function(name);
  searcher_team = hashT[index];

  while(strcmp(searcher_team->name,name) != 0)
  {
    if((searcher_team->link == NULL) && (strcmp(searcher_team->name,"\0") == 0))
    {
      new_team = searcher_team;
      strcpy(new_team->name,name);
      return;
    }

    if((searcher_team->link == NULL) && (strcmp(searcher_team->name,"\0") != 0))
    {
      new_team = (TEAM*)calloc(1,sizeof(TEAM*));
      strcpy(new_team->name,name);
      searcher_team->link = new_team;
      return;
    }

    searcher_team = searcher_team->link;
  }

  printf("%d Equipa existente.", row);
  
  return;
}
