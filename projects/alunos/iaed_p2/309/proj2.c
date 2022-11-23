#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "Structs_Jogos.h"
#include "Structs_Equipas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Le o comando do input e redirenciona cada comando para a sua funcionalidade. */
int main(){
	
	hashtable * hash = CreateHash();
	hashtable2 * hash2 = CreateHash2();
	Jogo * headJ = CreateGameList();
	Equipa * headE = NULL;
	char c;
	int NL=0;

	while((c = getchar()) != 'x'){
		if (c == 'a'){
			NL+=1;
			AddGame(NL, headJ, hash, hash2);
		}
		else if(c =='A'){
			NL+=1;
			headE = AddTeam(NL, headE, hash);
		}
		else if( c == 'l'){
			NL+=1;
			PrintGames(NL, headJ);
		}
		else if( c == 'p'){
			NL+=1;
			SearchGame(NL, hash2);
		}
		else if(c == 'P'){
			NL+=1;
			SearchTeam(NL, hash);
		}
		else if (c == 'r'){
			NL+=1;
			DeleteGame(NL, headJ, hash, hash2);
		}
		else if(c == 's'){
			NL+=1;
			ChangeScore(NL, hash, hash2);
		}
		else if( c == 'g'){
			NL+=1;
			FindTeamsWithMaxVictories(NL, headE);
		}
		else 
			continue;
	}
	DestroyH(hash);
	DestroyH2(hash2);
	DestroyE(headE);
	DestroyJ(headJ);
	return 0;
}
