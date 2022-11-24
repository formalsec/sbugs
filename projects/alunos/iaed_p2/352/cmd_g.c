#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "header.h"

/*Comando 'g'*/
/*Comando para listar as equipas que ganharam mais jogos por ordem lexixografica
(do nome da equipa)*/

void cmd_g()
{
	EquipasOrd *aux;
	int max_vitorias = 0;

	if(headteam == NULL)
		return;

	aux = headteam;

	/*estabelecer qual e o numero maximo de vitorias das equipas*/
	while(aux != NULL)
	{
		if(aux->team->vitorias > max_vitorias)
			max_vitorias = aux->team->vitorias;
		aux = aux->next;
	}

	if(max_vitorias == 0)
		return;

	/*ordenar as equipas por ordem lexicografica do nome de equipa*/
	MergeSort(&headteam);

	printf("%d Melhores %d\n", nl, max_vitorias);
	aux = headteam;
	while(aux != NULL)
	{
		if(aux->team->vitorias == max_vitorias)
			printf("%d * %s\n",nl, aux->team->nome_equipa);

		aux = aux->next;
	}
}	
