#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "header.h"

/*Comando 'r'*/
/*Comando para apagar um jogo do sistema dado um nome*/

void cmd_r()
{
	Jogo *aux;
	Jogo *aux_prev;
	Jogo *aux_seguinte;
	JogosOrd *temp;
	Equipa *aux1;
	char nome_jogo[MAX_CHAR];
	int indice_jogo;
	int indice_equipa;

	scanf(" %1024[^:\n]", nome_jogo);

	indice_jogo = hash(nome_jogo);

	aux = HashGames[indice_jogo];

	/*verificar se o jogo existe*/
	if(aux == NULL)
	{
		printf("%d Jogo inexistente.\n", nl);
		return;
	}

	/*se o jogo for a head da linked list dentro da hashtable*/
	if(strcmp(aux->nome, nome_jogo) == 0)
	{
		/*se a equipa 1 for a equipa vencedora*/
		if(aux->score_1 > aux->score_2)
		{
			indice_equipa = hash(aux->equipa_1);
			/*remover a vitoria da equipa vencedora do jogo a ser removido*/
			HashTeams[indice_equipa]->vitorias--;
		}
		/*se a equipa 2 for a equipa vencedora*/
		if(aux->score_2 > aux->score_1)
		{
			indice_equipa = hash(aux->equipa_2);
			/*remover a vitoria da equipa vencedora do jogo a ser removido*/
			HashTeams[indice_equipa]->vitorias--;
		}
	}
	else
	{	
		while(aux != NULL && strcmp(aux->nome, nome_jogo) != 0)
		{	
			aux_prev = aux;
			aux = aux->next;
		}

		if(aux == NULL)
		{
			printf("%d Jogo inexistente.\n", nl);
			return;
		}

		/*se a equipa 1 for a equipa vencedora*/
		if(aux->score_1 > aux->score_2)
		{
			indice_equipa = hash(aux->equipa_1);
			/*se a equipa for a head de uma linked list da hashtable*/
			if(strcmp(HashTeams[indice_equipa]->nome_equipa, aux->equipa_1) != 0)
			{	
				aux1 = HashTeams[indice_equipa];
				while(strcmp(aux1->nome_equipa, aux->equipa_1) != 0)
				{	
					aux1 = aux1->next;
				}
				/*remover a vitoria da equipa vencedora do jogo a ser removido*/
				aux1->vitorias--;
			}
			else
				HashTeams[indice_equipa]->vitorias--;
		}

		/*se a equipa 2 for a equipa vencedora*/
		if(aux->score_2 > aux->score_1)
		{
			indice_equipa = hash(aux->equipa_2);
			/*se a equipa for a head de uma linked list da hashtable*/
			if(strcmp(HashTeams[indice_equipa]->nome_equipa, aux->equipa_2) != 0)
			{	
				aux1 = HashTeams[indice_equipa];
				while(strcmp(aux1->nome_equipa, aux->equipa_2) != 0)
				{	
					aux1 = aux1->next;
				}
				/*remover a vitoria da equipa vencedora do jogo a ser removido*/
				aux1->vitorias--;
			}
			else
				HashTeams[indice_equipa]->vitorias--;
		}
	}	
	
	/*remover o jogo da linked lista auxiliar JogosOrd*/
	temp = headgame;
	while(strcmp(temp->game->nome, nome_jogo) != 0)
	{
		temp = temp->next;
	}
	if(temp == headgame && temp->next != NULL)
	{
		temp->next->prev = NULL;
		headgame = temp->next;
	}
	else if(temp == headgame && temp->next == NULL)
		headgame = NULL;

	else if (temp->next == NULL)
		temp->prev->next = NULL;
	else
	{
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
	}
	free(temp);

	/*desalocar a memoria usada pelo jogo eliminado*/
	if(aux == HashGames[indice_jogo])
	{
		aux = HashGames[indice_jogo]->next;
		free(HashGames[indice_jogo]->equipa_1);
		free(HashGames[indice_jogo]->equipa_2);
		free(HashGames[indice_jogo]->nome);
		free(HashGames[indice_jogo]);
		HashGames[indice_jogo] = aux;
	}
	else
	{
		aux_seguinte = aux->next;
		free(aux->equipa_1);
		free(aux->equipa_2);
		free(aux->nome);
		free(aux);
		aux_prev->next = aux_seguinte;
	}

}	