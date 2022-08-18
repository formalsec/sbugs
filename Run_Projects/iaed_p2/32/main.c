#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GAME.h"



int main(){
  int line = 0;
	int option;
  TeamInit(); /* inicializacao das hashtables das equipas e jogos*/
  GameInit();
	do {option = getchar();
     line++;
	   if (option == 'A') NewTeam(line);
	   else if (option == 'P') SearchTeam(line);
     else if (option == 'a') NewGame(line);
     else if (option == 'p') SearchGame(line);
     else if (option == 'r') DeleteGame(line);
     else if (option == 'l') ListAllGames(line);
     else if (option == 's') Change_Score(line);
	   else if (option == 'g') MaxWins(line);
     else if (option == 'x') break;

  } while (option != 'x');

	freeTeamHash(); /*free das hashtables das equipas e jogos*/
  freeGameHash();

	return 0;
}
