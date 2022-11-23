#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "header.h"

/*Comando 'a'*/
/*Comando que adiciona um novo jogo ao sistema*/

void cmd_a()
{
	Jogo *j;
	Jogo *atual;
	JogosOrd *temp;
	Equipa *aux1;
	int indice_equipa;
	int indice_jogo;
	char aux_n[MAX_CHAR],aux_eq1[MAX_CHAR],aux_eq2[MAX_CHAR];
	j = can_fail_malloc(sizeof(Jogo));
	temp = can_fail_malloc(sizeof(JogosOrd));
	scanf(" %1024[^:\n]:%1024[^:\n]:%1024[^:\n]:%d:%d", aux_n, aux_eq1, aux_eq2, &j->score_1, &j->score_2);

	j->nome = can_fail_malloc(sizeof(char)*(strlen(aux_n)+1));
	j->equipa_1 = can_fail_malloc(sizeof(char)*(strlen(aux_eq1)+1));
	j->equipa_2 = can_fail_malloc(sizeof(char)*(strlen(aux_eq2)+1));

	strcpy(j->nome,aux_n);
	strcpy(j->equipa_1,aux_eq1);
	strcpy(j->equipa_2,aux_eq2);

	indice_jogo = hash(j->nome);

	/*Se o jogo for a head da sua linked list dentro da hashtable*/
	if(HashGames[indice_jogo] == NULL)
	{	
		/*verificar se alguma das equipas nao existe*/
		if(equipa_nao_existe(j->equipa_1) || equipa_nao_existe(j->equipa_2))
		{
			free(j->nome);
			free(j->equipa_1);
			free(j->equipa_2);
			free(j);
			free(temp);
			printf("%d Equipa inexistente.\n", nl);
			return;
		}
		HashGames[indice_jogo] = j;
		HashGames[indice_jogo]->next = NULL;
	}
	else
	{
		atual = HashGames[indice_jogo];
		/*percorrer a linked list a procura do jogo*/
		while(atual->next != NULL && strcmp(atual->nome, j->nome) != 0)
			atual = atual->next;
		/*se o jogo ja existir*/
		if(strcmp(atual->nome, j->nome) == 0)
		{	
			free(j->nome);
			free(j->equipa_1);
			free(j->equipa_2);
			free(j);
			free(temp);
			printf("%d Jogo existente.\n", nl);
			return;
		}

		if(equipa_nao_existe(j->equipa_1) || equipa_nao_existe(j->equipa_2))
		{
			free(j->nome);
			free(j->equipa_1);
			free(j->equipa_2);
			free(j);
			free(temp);
			printf("%d Equipa inexistente.\n", nl);
			return;
		}
		atual->next = j;
		atual->next->next = NULL;
	}
	/*inicializar a head da linked list auxiliar JogosOrd*/
	if(headgame == NULL)
	{
		temp->game = j;
		temp->prev = NULL;
		temp->next = NULL;
		headgame = temp;
	}
	else
	{	
		temp->game = j;
		temp->prev = NULL;
		temp->next = headgame;
		headgame->prev = temp;
		headgame = temp;
	}
	/*aumentar o numero de vitorias da equipa que ganhou o jogo se nao for empate*/
	if(j->score_1 > j->score_2)
	{
		indice_equipa = hash(j->equipa_1);
		if(strcmp(HashTeams[indice_equipa]->nome_equipa, j->equipa_1) != 0)
		{	
			aux1 = HashTeams[indice_equipa];
			while(strcmp(aux1->nome_equipa, j->equipa_1) != 0)
			{
				aux1 = aux1->next;
			}
			aux1->vitorias++;
			return;
		}
		else
		{
			HashTeams[indice_equipa]->vitorias++;
			return;
		}
	}
	if(j->score_2 > j->score_1)
	{
		indice_equipa = hash(j->equipa_2);
		if(strcmp(HashTeams[indice_equipa]->nome_equipa, j->equipa_2) != 0)
		{	
			aux1 = HashTeams[indice_equipa];
			while(strcmp(aux1->nome_equipa, j->equipa_2) != 0)
			{
				aux1 = aux1->next;
			}
			aux1->vitorias++;
		}
		else
			HashTeams[indice_equipa]->vitorias++;
	}
}