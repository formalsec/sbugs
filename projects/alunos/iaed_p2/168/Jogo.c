#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "Jogo.h"

/*Funcao que liberta da memoria uma estrutura 'Jogo' e os seus
parametros que foram alocadas.*/
void freeJogo(Jogo *jogo)
{
	free(jogo->nome);
	free(jogo->equipa1);
	free(jogo->equipa2);
	free(jogo);
}

/*Funcao que da print a uma estrutura Jogo de acordo com o enunciado.*/
void printJogo(Jogo *jogo, int conta_linhas)
{
	printf("%d %s %s %s %d %d\n",
			conta_linhas,
			jogo->nome, jogo->equipa1, jogo->equipa2, 
			jogo->score_equipa1, jogo->score_equipa2);
}

/*Funcao que altera ps parametros 'score' de uma estrutura Jogo.*/
void alteraScore(Jogo *jogo, int score1, int score2)
{
	jogo->score_equipa1 = score1;
	jogo->score_equipa2 = score2;
}

/*Funcao que cria uma nova estrutura Jogo. Aloca em memoria a nova
estrutura e os parametros que necessitam ser alocados.*/
Jogo* novoJogo(char *nome, char *equipa1, char *equipa2,
				int score1, int score2, int linha_n)
{
	Jogo* novo;
	novo =(Jogo*) can_fail_malloc(sizeof(Jogo));

	/*Nota: a funcao 'strdup' encontra-se no ficheiro "funcoes_aux.h".*/
	novo->nome = strdup(nome);
	novo->equipa1 = strdup(equipa1);
	novo->equipa2 = strdup(equipa2);
	novo->score_equipa1 = score1;
	novo->score_equipa2 = score2;
	novo->linha_n = linha_n;
	novo->next = NULL;

	return novo;
}





