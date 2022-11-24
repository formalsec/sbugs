#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "header.h"

/*Comando 'A'*/
/*Comando para adicionar uma nova equipa ao sistema*/
void cmd_A()
{
	Equipa *t;
	Equipa *temp;
	EquipasOrd *aux;
	EquipasOrd *temp1;
	char aux_ler[MAX_CHAR];
	int indice_equipa;
	scanf(" %1024[^:\n]", aux_ler);
	t = can_fail_malloc(sizeof(Equipa));
	aux = can_fail_malloc(sizeof(EquipasOrd));
	t->nome_equipa = can_fail_malloc(sizeof(char)*(strlen(aux_ler)+1));
	strcpy(t->nome_equipa, aux_ler);
	t->vitorias = 0;
	t->next = NULL;

	/*verificar se a equipa ja existe*/
	if(!(equipa_nao_existe(t->nome_equipa)))
	{
		free(t->nome_equipa);
		free(t);
		free(aux);
		printf("%d Equipa existente.\n", nl);
		return;
	}
	indice_equipa = hash(t->nome_equipa);
	/*se a equipa nao for a head da linked list dentro da hashtable*/
	if(HashTeams[indice_equipa] != NULL)
	{	
		temp = HashTeams[indice_equipa];
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = t;
	}
	else
		HashTeams[indice_equipa] = t;
	/*inicializar a head da linked list auxiliar Equipas*/
	if(headteam == NULL)
	{
		aux->team = t;
		aux->next = NULL;
		headteam = aux;
	}
	else
	{	
		temp1 = headteam;
		while(temp1->next != NULL)
			temp1 = temp1->next;
		aux->team = t;
		aux->next = NULL;
		temp1->next = aux;
	}
}