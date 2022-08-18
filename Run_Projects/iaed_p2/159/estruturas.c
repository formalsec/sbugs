#include "estruturas.h"


/*FUNCOES DO TIPO "EQUIPA"*/


/*Cria uma nova equipa*/
Equipa new_Equipa(char * nome)
{
	/*Reserva espaco para uma Equipa*/
	Equipa new = (Equipa) malloc(sizeof(equipa));
	new->nome = strdup(nome);
	new->jogos_ganhos=0;
	return new;
}


/*Liberta o espaco reservado por uma equipa*/
void free_Equipa(Equipa e)
{
	if(e!=NULL)
	{
		free(e->nome);
		
	}
	free(e);
	
	
}


/*Imprime as equipas de acordo com o enunciado 
	do projeto, nomeadamente no comando P*/
void print_Equipa(Equipa e,unsigned int num_linha)
{
	printf("%u %s %u\n",num_linha,e->nome,e->jogos_ganhos);
}




/*Cria um novo jogo*/
Jogo new_Jogo(char *nome, Equipa e1, Equipa e2,
	unsigned int s1, unsigned int s2)
{
	/*Reserva espaco para um jogo*/
	Jogo new= (Jogo) malloc(sizeof(jogo));
	new->nome = strdup(nome);
	new->e1=e1;
	new->e2=e2;
	new->s1=s1;
	new->s2=s2;
	return new;
}


/*Liberta o espaco reservado para um jogo*/
void free_Jogo(Jogo j)
{
	if(j!=NULL)
	{
		free(j->nome);
	}
	free(j);
	
}


/*Imprime os jogos de acordo com o enunciado do projeto,
	nomeadamente nos comandos l e p*/
void print_Jogo(Jogo j,unsigned int num_linha)
{
	printf("%u %s %s %s %u %u\n",num_linha,j->nome,
		j->e1->nome,j->e2->nome,j->s1,j->s2);
}	




