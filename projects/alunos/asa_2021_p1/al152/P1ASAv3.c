#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/*************************************************************
 * Projeto 1 ASA - Dominos
 *
 * Filipe Joao Cabral Neves // Numero de aluno #87318
 *************************************************************/

#include <stdio.h>
#include <stdlib.h>

/*              Estrutura Principal do Projeto
 *
 ************************************************************/

typedef struct {
	int posicao;
	int numfilhos;
	int nivel;      /* incrementa 1 por cada nível */
	int* nodulos;
} Node;

/* estrutura do vetor extra para encontrar os "pais" do grafo
 *
 ************************************************************/

typedef struct {
	int valor;
	int numpais;
} Node_Aux;

/*                    Variaveis Globais
 *
 ************************************************************/

Node* tabela;
Node_Aux* vetor;
int numpieces, dependecia, min_interacao = 0, maior_caminho = 0;

/*                   Funcoes Auxiliares
 *
 ************************************************************/

void colocaposicao(int dependente, int pessa)
{
	if(tabela[pessa].numfilhos > 0)
	{
		tabela[pessa].numfilhos++;
		tabela[pessa].nodulos = can_fail_realloc(tabela[pessa].nodulos, sizeof(int)*tabela[pessa].numfilhos);
		tabela[pessa].nodulos[tabela[pessa].numfilhos - 1] = dependente;
	}
	else if(tabela[pessa].numfilhos == 0)
	{
		tabela[pessa].nodulos = can_fail_malloc(sizeof(int));
		tabela[pessa].nodulos[0] = dependente;
		tabela[pessa].numfilhos = 1;
	}
	else
	{
		exit (EXIT_FAILURE);
	}
}

void checkpais(int pessa)
{
	int i = 0;
	for(i = 0; i < tabela[pessa].numfilhos; i++)
	{
		vetor[tabela[pessa].nodulos[i]].numpais++;
	}
}

void interacoes()
{
	int i = 1;
	for(i = 1; i < numpieces; i++)
	{
		if(vetor[i].numpais == 0)
		{
			min_interacao++;
		}
	}
}

/* Funcao Caminho: aplicacao de DFS recursiva por niveis para 
 *                 encontrar caminho mais longo 
 *
 **************************************************************************/

void caminho(int pai)
{
	if(tabela[pai].numfilhos == 0)
	{
		if(tabela[pai].nivel > maior_caminho)
			maior_caminho = tabela[pai].nivel;
	}
	else
	{
		int i = 0;
		for(i = 0; i < tabela[pai].numfilhos; i++)
		{
			if(tabela[tabela[pai].nodulos[i]].nivel < (tabela[pai].nivel + 1))
			{
				tabela[tabela[pai].nodulos[i]].nivel = tabela[pai].nivel + 1;
				caminho(tabela[pai].nodulos[i]);
			}
		}
	}
}

/*                      Funcao Main
 *
 ************************************************************/

int main()
{
	int pessa, dependente, i = 0, j = 0, k = 0, l = 1, m = 1;

	if(scanf("%d %d", &numpieces, &dependecia) == 2)
	{
		if(numpieces == 0 && dependecia == 0)
		{
			printf("0 0\n");
			return EXIT_SUCCESS;
		}
		else if(numpieces == 1 && dependecia == 0)
		{
			printf("1 1\n");
			return EXIT_SUCCESS;
		}
		else if(numpieces < 2 || dependecia < 0)
			exit (EXIT_FAILURE);

		numpieces++;                              /* para que as posicoes da tabela tenham mesmo valor que o valor da pessa domino */
		tabela = can_fail_malloc(sizeof(Node)*numpieces);
		for(i = 0; i < numpieces; i++)			  /* posicao 0 existe na tabela, mas ignorada no resto do codigo pois nao corresponde a nenhuma pessa */
		{
			tabela[i].posicao = i;
			tabela[i].numfilhos = 0;
			tabela[i].nivel = 0;
			tabela[i].nodulos = NULL;
		}

		for(j = 0; j < dependecia; j++)
		{
			if(scanf("%d %d", &pessa, &dependente) == 2)
				colocaposicao(dependente, pessa);
		}

		vetor = can_fail_malloc(sizeof(Node_Aux)*numpieces);  /* cria vetor auxiliar para ver quantos pais tem cada pessa, valor 0 ignorado no resto do programa */
		for(k = 0; k < numpieces; k++)
		{
			vetor[k].valor = k;
			vetor[k].numpais = 0;
		}

		for(l = 1; l < numpieces; l++)               /* obtem todos os nodes pais / raizes do problema */
		{
			if(tabela[l].numfilhos > 0)
				checkpais(l);
		}

		if(dependecia == 0)
			min_interacao = numpieces;
		else if(dependecia == 1)
			min_interacao = numpieces - 1;
		else
			interacoes();

		if(dependecia == 0)
			maior_caminho = 0;
		else if(dependecia == 1)
			maior_caminho = 1;
		else
			for(m = 1; m < numpieces; m++)
			{
				if(vetor[m].numpais == 0)                 /* consideramos o inicio de cada caminho apenas a partir das pessas pais */
				{
					tabela[m].nivel = 1;
					caminho(m);
				}
			}

		printf("%d %d\n", min_interacao, maior_caminho);  /* resposta final */

		free(tabela);
		free(vetor);

		return EXIT_SUCCESS;
	}
	else
		return EXIT_FAILURE;
}