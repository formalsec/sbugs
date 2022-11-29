#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "header.h"

/*Comando 'P'*/
/*Comando para procurar uma equipa no sistema dado um nome*/

void cmd_P()
{	
	Equipa *aux;
	int indice_equipa;
	char nome_equipa[MAX_CHAR];

	scanf(" %1024[^:\n]", nome_equipa);

	indice_equipa = hash(nome_equipa);
	aux = HashTeams[indice_equipa];

	/*verificar se a equipa existe como head de uma linked list dentro da hashtable*/
	if(aux == NULL)
	{
		printf("%d Equipa inexistente.\n", nl);
		return;
	}

	/*se a equipa nao for a head de uma linked list na hashtable*/
	if(strcmp(aux->nome_equipa, nome_equipa) != 0)
	{	
		while(aux != NULL && strcmp(aux->nome_equipa, nome_equipa))
		{
			aux = aux->next;
		}
		if(aux == NULL)
		{
			printf("%d Equipa inexistente.\n", nl);
			return;
		}
		printf("%d %s %d\n", nl, aux->nome_equipa, aux->vitorias);
		return;
	}
	else	
		printf("%d %s %d\n", nl, aux->nome_equipa, aux->vitorias);
}