#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <string.h>
#include "equipas.h"


Equipa *cria_equipa(char *nome){

	/*-----------------------------------
	CRIA ESTRUTURA EQUIPA COM O NOME DADO
	-----------------------------------*/

	Equipa *x = can_fail_malloc(sizeof(Equipa));
	nome_e(x) = can_fail_malloc(sizeof(char)*(strlen(nome)+1));

	strcpy(nome_e(x), nome);
	jogos_ganhos(x) = 0;
	proxima_e(x) = NULL;

	return x;
}



/* altera o numero de jogos ganhos consoante o valor de S */
void altera_ganhos(Equipa *head, int S){

	/*-----------------------------------------------
	ALTERA O NUMERO DE JOGOS GANHOS DADO O VALOR DE S
	-----------------------------------------------*/

	/* Se S = 1 aumenta numero de jogos ganhos em 1. */
	if (S) 
		jogos_ganhos(head)+= 1;

	else if (!S && (jogos_ganhos(head)>0))
		jogos_ganhos(head)-= 1;

}


void free_equipa(Equipa *head){

	/*-------------------------------
	LIBERTA MEMORIA ALOCADA DA EQUIPA
	-------------------------------*/
	
	free(nome_e(head));
	free(head);
}