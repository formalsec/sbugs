#include <stdio.h>
#include "JOGOS.h"
#include "EQUIPAS.h"
#include "COMANDOS.h"

/* ---------------------------------------------- DEFINICAO DE CONSTANTES -------------------------------------------- */

#define TAMANHO 1024

/* ----------------------------------------------------- COMANDOS ---------------------------------------------------- */

/* comando a - adiciona um novo jogo */
void novo_jogo(int nl, linkJ headsJ[], linkE headsE[], lista *lst)
{
  char nome[TAMANHO];
  char equipa1[TAMANHO];
  char equipa2[TAMANHO];
  int score1, score2;
  ItemE eqp1, eqp2;
  ItemJ njogo, n;
  scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, equipa1, equipa2, &score1, &score2);
  eqp1 = procura_equipa(equipa1, headsE);
  eqp2 = procura_equipa(equipa2, headsE);
  n = procura_nome(nome, headsJ);
  if (n != NULL)
  {
    printf("%d Jogo existente.\n", nl);
  }
  else if (eqp1 == NULL || eqp2 == NULL)
  {
    printf("%d Equipa inexistente.\n", nl);
  }
  else 
  {
    njogo = novoJogo(nome, equipa1, equipa2, score1, score2);
    inserirJ(njogo, headsJ);
    inserir_fim(lst, njogo);
    /* falta inserir na tabela */
    if (score2>score1)
    {
      eqp2->vitorias ++;
    }
    else if (score1>score2)
    {
      eqp1->vitorias ++;
    }
  }
}

/* comando l - lista todos os jogos pela ordem em que foram introduzidos */
void lista_jogos(int nl, lista *lst)
{
	imprime_jogos(nl, lst);
}

/* comando p - procura um jogo */
void procura_jogo(int nl, linkJ headsJ[])
{
	char nome[TAMANHO];
	ItemJ jogo;
	scanf(" %[^:\n]", nome);
	jogo = procura_nome(nome, headsJ);
	if (jogo != NULL)
	{
		imprimeJogo(nl, jogo);
	}
	else
	{
		printf("%d Jogo inexistente.\n", nl);
	}
}

/* comando r - apaga um jogo */
void apagar_jogo(int nl, linkJ headsJ[], lista *lst, linkE headsE[])
{
	char nome[TAMANHO];
	ItemJ jogo;
	ItemE eqp1, eqp2;
	int scr1, scr2, i;
	scanf(" %[^:\n]", nome);
	jogo = procura_nome(nome, headsJ);
	i = chave(nome);
	if (jogo != NULL)
	{
		eqp1 = procura_equipa(jogo->equipa1, headsE);
		eqp2 = procura_equipa(jogo->equipa2, headsE);
		scr1 = jogo->score1;
		scr2 = jogo->score2;
		if (scr1 > scr2)
		{
			eqp1->vitorias --;
		}
		else if (scr2 > scr1)
		{
			eqp2->vitorias --;
		}
		apaga_jogo(headsJ, lst, nome, i); /* apagar jogo da hash table */
	}
	else 
	{
		printf("%d Jogo inexistente.\n", nl);
	}
}

/* comando s - altera a pontuacao de um jogo */
void altera_score(int nl, linkJ headsJ[], linkE headsE[])
{
	char nome[TAMANHO];
	int score1, score2, scr1, scr2;
	ItemJ jogo;
	ItemE eqp1, eqp2;
	scanf(" %[^:\n]:%d:%d", nome, &score1, &score2);
	jogo = procura_nome(nome, headsJ);
	if (jogo != NULL)
	{
		eqp1 = procura_equipa(jogo->equipa1, headsE);
		eqp2 = procura_equipa(jogo->equipa2, headsE);
		scr1 = jogo->score1;
		scr2 = jogo->score2;
		if (scr1 > scr2)
		{
			if (score1 < score2)
			{	
				eqp2->vitorias ++;
				eqp1->vitorias --;

			}
			else if (score1 == score2)
			{
				eqp1->vitorias --;

			}
		}

		else if (scr1 < scr2)
		{
			if (score1 > score2)
			{	
				eqp1->vitorias ++;
				eqp2->vitorias --;
			}
			else if (score1 == score2)
			{
				eqp2->vitorias --;
			}
		}

		else 
		{
			if (score1 < score2)
			{	
				eqp2->vitorias ++;
				
			}
			else if (score1 > score2)
			{

				eqp1->vitorias ++;

			}
		}

		jogo->score1 = score1;
		jogo->score2 = score2;
				
	}
	else
	{
		printf("%d Jogo inexistente.\n", nl);
	}

}

/* comando A - adiciona uma nova equipa */
void nova_equipa(int nl, int *contadorequipas, linkE headsE[])
{
	char equipa[TAMANHO];
	ItemE nequipa, aux;
	scanf(" %[^:\n]", equipa);
	aux = procura_equipa(equipa, headsE);
	if (aux == NULL)
	{
		nequipa = novaEquipa(equipa, 0);
		inserirE(nequipa, headsE);
		(*contadorequipas) ++;
	} /* alterar o link */
	else
	{
		printf("%d Equipa existente.\n",nl);
	}
}

/* comando P - procura uma equipa */
void procurar_equipa(int nl, linkE headsE[])
{
	char equipa[TAMANHO];
	ItemE eqp;
	scanf(" %[^:\n]", equipa);
	eqp = procura_equipa(equipa, headsE);
	if (eqp == NULL)
	{
		printf("%d Equipa inexistente.\n", nl);
	}
	else
	{
		printf("%d ", nl);
		imprimeEquipa(eqp);
	}
}

/* comando g - encontra as equipas com mais vitorias */
void lista_equipas(int nl, int *contadorequipas, linkE headsE[])
{
	int vitorias;
	vitorias = numero_vitorias(headsE);
	nome_equipas(vitorias, nl, *contadorequipas, headsE);
}

/* libertar a memoria associada as hashs e a lista */
void sair(linkE headsE[], linkJ headsJ[], lista *l)
{
	sair_hashE(headsE);
	sair_jogos(l, headsJ);
}