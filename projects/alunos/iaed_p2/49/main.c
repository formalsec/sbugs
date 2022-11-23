#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

#include "_features.h"

/* Regulates the flux of data through the system*/
int main() {
	char command;
	int nl = 1;

	hash *hashT = initT(HASHSIZE);

	int id = 1;
	link head = NULL; /* Head pointer to the first node of the list*/

	hashM *hashMt = initM(HASHSIZE);

	while((command = getchar())) {
		switch(command) {
			case 'a':
				new_match(nl, id, hashMt, hashT, head);
				id++;
				break;
			case 'A':
				add_team(nl, hashT);
				break;
			case 'l':
				list_all_matches(nl, hashMt);
				getchar();
				break;
			case 'p':
				search_match(nl, hashMt);
				break;
			case 'P':
				search_team(nl, hashMt, hashT);
				break;
			case 'r':
				delete_match(nl, hashMt);
				break;
			case 's':
				change_score(nl, hashMt);
				break;
			case 'g':

			case 'x':
				eraseT(hashT);
				eraseM(hashMt);
				return EXIT_SUCCESS;
		}
		++nl;
	}
	return EXIT_FAILURE;
}