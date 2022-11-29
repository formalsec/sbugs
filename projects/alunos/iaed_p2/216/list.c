#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "list.h"


/*Funcao que recebe uma lista de jogos e ate encontrar um no
* que se encontre a NULL ,imprime o contador da linha, o nome do jogo,
* a equipa1, a equipa2, o resuldado1 e o resultado2. */
void listGames(list *ls){

	node *ptr = ls->head;
	while(ptr != NULL){

		printf("%d %s %s %s %d %d\n", counter, ptr->name, ptr->team1, ptr->team2, ptr->score1, ptr->score2);
		ptr = ptr->next;
	}
}