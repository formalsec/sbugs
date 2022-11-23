#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "itemTeam.h"

ItemTeam newItem_team(char* name){
	ItemTeam x = can_fail_malloc(sizeof(Team));
	x->name = strdup(name);
   x->numGamesWon = 0;
	return x;
}

void deleteItem_team(ItemTeam i){
	free(i->name);
   free(i);
}

void showItem_team(ItemTeam i){
   printf("%s %d\n", i->name, i->numGamesWon);
}
