#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "header.h"

/*Comando 'l'*/
/*Comando para listar todos os jogos introduzidos no sistema*/

void cmd_l()
{	
	JogosOrd *aux;
	if(headgame == NULL)
		return;

	aux = headgame;

	while(aux->next != NULL)	
		aux = aux->next;

	while(aux != NULL)
	{
		printf("%d %s %s %s %d %d\n", nl, aux->game->nome, aux->game->equipa_1, aux->game->equipa_2, aux->game->score_1, aux->game->score_2);
		aux = aux->prev;
	}
}	
