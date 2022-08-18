#include "header.h"

/*Funcao main*/

int main()
{	
	char c;
	nl = 0;
	headgame = NULL;
	headteam = NULL;
	iniciar_HashGames();
	iniciar_HashTeams();
	while(1)
	{
		switch (c = getchar())
		{

			case 'a':
				nl++;
				cmd_a();
				break;
			case 'A':
				nl++;
				cmd_A();
				break;

			case 'l':
				nl++;
				cmd_l();
				break;

			case 'p':
				nl++;
				cmd_p();
				break;

			case 'P':
				nl++;
				cmd_P();
				break;

			case 'r':
				nl++;
				cmd_r();
				break;

			case 's':
				nl++;
				cmd_s();
				break;

			case 'g':
				nl++;
				cmd_g();
				break;

			case 'x':
				FreeMemory();
				exit(0);
				break;
		}
	}
	return 0;
}