/*File generated by PreProcessor.py*/


#include <stdio.h>
#include "Projeto2.h"


int main()
{
  gameLink *hashGameTable = InitGameHash(5501);
  teamLink *hashTeamTable = InitTeamHash(2131);
  gameLink headGame = 0;
  gameLink tailGame = 0;
  int nrCommand = 0;
  while (scanCommand(&nrCommand, hashTeamTable, &headGame, hashGameTable, &tailGame))
    ;

  freeTeamHash(hashTeamTable);
  freeGameHash(hashGameTable);
  freeGameList(headGame);
  return 0;
}

