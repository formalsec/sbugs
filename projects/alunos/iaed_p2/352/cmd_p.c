#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "header.h"

/*Comando 'p'*/
/*Comando para procurar um jogo no sistema com o nome dado*/

void cmd_p()
{	
	Jogo *aux;
	char nome_jogo[MAX_CHAR];
	int indice_jogo;
	scanf(" %1024[^:\n]", nome_jogo);
	indice_jogo = hash(nome_jogo);

	/*verificar se o jogo ja existe como head de uma linked list dentro da hashtable*/
	if(HashGames[indice_jogo] == NULL)
	{
		printf("%d Jogo inexistente.\n", nl);
		return;
	}

	/*se o jogo nao for head da linked list dentro da hashtable*/
	if(HashGames[indice_jogo]->nome != nome_jogo)
	{	
		aux = HashGames[indice_jogo];
		while(aux->next != NULL && strcmp(aux->nome, nome_jogo) != 0)
			aux = aux->next;
		if(strcmp(aux->nome, nome_jogo) == 0)
		{
			printf("%d %s %s %s %d %d\n", nl, aux->nome, aux->equipa_1, aux->equipa_2, aux->score_1, aux->score_2);
			return;
		}
		printf("%d Jogo inexistente.\n", nl);
	}
}