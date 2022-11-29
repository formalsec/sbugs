#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <string.h>
#include "jogos.h"



Jogo *cria_jogo(char *nome_j, char *eq1, char *eq2, int score1, int score2){

	/*----------------------------------------------
	CRIA UM JOGO DADOS OS NOMES E SCORES NECESSARIOS
	----------------------------------------------*/

	Jogo *x = can_fail_malloc(sizeof(Jogo));

	/* Nome de jogo. */
	nome_jogo(x) = can_fail_malloc(sizeof(char)*(strlen(nome_j)+1));
	strcpy(nome_jogo(x), nome_j);
	/* Nome equipa 1. */
	equipa1_j(x) = can_fail_malloc(sizeof(char)*(strlen(eq1)+1));
	strcpy(equipa1_j(x), eq1);
	/*	 Nome equipa 2. */
	equipa2_j(x) = can_fail_malloc(sizeof(char)*(strlen(eq2)+1));
	strcpy(equipa2_j(x), eq2);
	/* Score equipa 1. */
	score1_j(x) = score1;
	/* Score equipa 2.*/
	score2_j(x) = score2;
	proximo_j(x) = NULL;

	return x;
}





void free_jogo(Jogo *head){

	/*------------------------------------------------
	LIBERTA TODA A MEMORIA ALOCADA REFERENTE A UM JOGO
	------------------------------------------------*/
	
	free(nome_jogo(head));
	free(equipa1_j(head));
	free(equipa2_j(head));
	free(head);
}