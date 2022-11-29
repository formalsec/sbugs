#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "commands.h"

int main(){
	char c;
	System *s = can_fail_malloc(sizeof(System));
	Start_Sytem(s);
	while((c = getchar())!= 'x'){
		switch(c){

			case 'a':
				command_add_game(s);
				break;

			case 'A':
				command_add_team(s);
				break;

			case 'l':
				command_list_game(s);
				break;

			case 'p':
				search_game(s);
				break;

			case 'P':
				command_search_team(s);
				break;

			case 'r':
				deleate_game(s);
				break;

			case 's':
				change_score(s);
				break;

			case 'g':
				command_bggst_wnnrs(s);
				break;
		}
	}
	Stop_System(s);
	return 0;
}