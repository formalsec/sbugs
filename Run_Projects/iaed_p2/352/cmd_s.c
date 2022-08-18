#include "header.h"

/*Comando 's'*/
/*Comando para alterar o score de um jogo dado o nome*/

void cmd_s()
{	
	Jogo *aux;
	Equipa *aux1;
	Equipa *aux2;
	char nome_jogo[MAX_CHAR];
	int indice_jogo, indice_equipa1, indice_equipa2, score_1, score_2;
	int score_antigo_1, score_antigo_2;

	scanf(" %1024[^:\n]:%d:%d", nome_jogo, &score_1, &score_2);
	indice_jogo = hash(nome_jogo);

	/*verificar se o jogo existe como head de uma linked list na hashtable*/
	if(HashGames[indice_jogo] == NULL)
	{
		printf("%d Jogo inexistente.\n", nl);
		return;
	}

	/*se o jogo nao for a head da linked list na hashtable*/
	if(strcmp(HashGames[indice_jogo]->nome, nome_jogo) != 0)
	{	
		aux = HashGames[indice_jogo];
		while(aux != NULL && strcmp(aux->nome, nome_jogo) != 0)
			aux = aux->next;

		if(aux == NULL)
		{
			printf("%d Jogo inexistente.\n", nl);
			return;
		}
		score_antigo_1 = aux->score_1;
		score_antigo_2 = aux->score_2;
		/*alterar as pontuacoes do jogo*/
		aux->score_1 = score_1;
		aux->score_2 = score_2;
	}
	else
	{	
		score_antigo_1 = HashGames[indice_jogo]->score_1;
		score_antigo_2 = HashGames[indice_jogo]->score_2;
		aux = HashGames[indice_jogo];
		/*alterar as pontuacoes do jogo*/
		HashGames[indice_jogo]->score_1 = score_1;
		HashGames[indice_jogo]->score_2 = score_2;
	}

	indice_equipa1 = hash(aux->equipa_1);
	indice_equipa2 = hash(aux->equipa_2);
	aux1 = HashTeams[indice_equipa1];
	aux2 = HashTeams[indice_equipa2];
	if(strcmp(aux1->nome_equipa, aux->equipa_1) != 0)
		{	
			while(strcmp(aux1->nome_equipa, aux->equipa_1) != 0)
				aux1 = aux1->next;
		}

	if(strcmp(aux2->nome_equipa, aux->equipa_2) != 0)
		{	
			while(strcmp(aux2->nome_equipa, aux->equipa_2) != 0)
				aux2 = aux2->next;
		}

	/*alteracao das pontuacoes do jogo*/

	/*se a equipa 1 tiver ganho o jogo antigo e perdido o novo*/
	if(score_antigo_1 > score_antigo_2 && score_1 < score_2)
	{	
		aux1->vitorias--;
		aux2->vitorias++;
		return;
	}
	/*se a equipa 2 tiver ganho o jogo antigo e ter perdido o novo*/
	if(score_antigo_1 < score_antigo_2 && score_1 > score_2)
	{	
		aux1->vitorias++;
		aux2->vitorias--;
		return;
	}
	/*se as equipas tiverem empatado o jogo antigo e agora ter ganho a equipa 2*/
	if(score_antigo_1 == score_antigo_2 && score_1 < score_2)
	{
		aux2->vitorias++;
		return;
	}
	/*se as equipas tiverem empatado o jogo antigo e agora ter ganho a equipa 1*/
	if(score_antigo_1 == score_antigo_2 && score_1 > score_2)
	{	
		aux1->vitorias++;
		return;
	}
	/*se a equipa 1 tiver ganho o jogo antigo e agora tiverem empatado*/
	if(score_antigo_1 > score_antigo_2 && score_1 == score_2)
	{
		aux1->vitorias--;
		return;
	}
	/*se a equipa 2 tiver ganho o jogo antigo e agora tiverem empatado*/
	if(score_antigo_1 < score_antigo_2 && score_1 == score_2)
		aux2->vitorias--;

}