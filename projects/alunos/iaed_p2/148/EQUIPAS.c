#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EQUIPAS.h"

/* ---------------------------------------------- DEFINICAO DE CONSTANTES -------------------------------------------- */

#define M 997

/* ----------------------------------------------------- EQUIPAS ----------------------------------------------------- */

ItemE novaEquipa(char *equipa, int vitorias)
/* aloca memoria e atribui o nome e o numero de vitorias, inicalmente 0 */
{
	ItemE novo = (ItemE)can_fail_malloc(sizeof(struct Equipas));
	novo->equipa = (char*)can_fail_malloc(sizeof(char)*(strlen(equipa)+1));
	strcpy(novo->equipa, equipa);
	novo->vitorias = vitorias;
	return novo;
}

void freeEquipa(ItemE a)
/* libertar memoria */
{
	free(a->equipa);
	free(a);
}

void imprimeEquipa(ItemE a)
/* imprimir uma determinada equipa */
{
	printf("%s %d\n",a->equipa, a->vitorias);
}

/* ------------------------------------------------ HASHTABLE EQUIPAS ------------------------------------------------ */

int funcao_hashE(char *v)
 /* funcao que retorna o inteiro correspondente a key para a hashtable */
{
	int h = 0, a = 127;
	for (; *v != '\0'; v++)
	h = (a*h + *v) % M;
	return h;
}

void iniciaE(linkE headsE[])
/* inicia a hash */
{
	int i;
	for (i = 0; i < M; i++)
	{
		headsE[i] = NULL;
	}
}

void inserirE(ItemE item, linkE headsE[])
/* inserir a equipa na hash */
{
	int i = funcao_hashE(item->equipa);
	headsE[i] = inserir_inicioE(headsE[i], item);
}

linkE inserir_inicioE(linkE head, ItemE a)
/* inserir a equipa no inicio da lista */
{
	linkE x = (linkE)can_fail_malloc(sizeof(struct nodeE));
	x->item = a;
	x->next = head;
	return x;
}

ItemE procura_equipa(char *nome, linkE headsE[])
/* devolve a equipa se esta estiver na hash */
{
	int i = funcao_hashE(nome);
	return procura_lista_equipa(headsE[i], nome);
}

ItemE procura_lista_equipa(linkE head, char *nome)
/* devolve a equipa se estiver na lista caso contrario devolve NULL */
{
	linkE t; 
	for (t = head; t != NULL; t = t->next)
	{
		if(strcmp(t->item->equipa, nome) == 0)
		{
			return t->item;
		}
	}
	return NULL;
}

int numero_vitorias(linkE headsE[])
/* devolve o numero maximo de equipas */
{
	int i;
	int vitorias = 0;
	linkE t;
	for (i = 0; i < M; i++)
	{
		for (t = headsE[i]; t!= NULL; t = t->next)
		{
			if(t->item->vitorias > vitorias)
			{
				vitorias = t->item->vitorias;
			}
		}
	}
	return vitorias;
}

void nome_equipas(int vitorias, int nl, int contadorequipas, linkE headsE[])
/* lista as equipas com mais vitorias */
{
	int i, x;
	int j = 0;
	char **equipas;
	linkE t;
	equipas = (char**)can_fail_malloc(sizeof(char*)*contadorequipas);
	for (i = 0; i < M; i++)
	{
		for (t = headsE[i]; t!= NULL; t = t->next)
		{
			if(t->item->vitorias == vitorias)
			{
				equipas[j] = (char*)can_fail_malloc(sizeof(char)*(strlen(t->item->equipa)+1));
				strcpy(equipas[j], t->item->equipa);
				j++;
			}
		}
	}
	if (j > 0)
	{
		qsort(equipas, j, sizeof(char *), compara);
		printf("%d Melhores %d\n",nl, vitorias);
		for(x = 0; x < j; x++)
		{
			printf("%d * %s\n",nl, equipas[x]);
			free(equipas[x]);
		}
	}
	free(equipas);
}

void sair_hashE(linkE headsE[])
/* liberta a memoria */
{
	linkE t, aux;
	int i;
	for (i = 0; i < M; i++)
	{
		for (t = headsE[i]; t != NULL;)
		{
			aux = t;
			t = t->next;
			freeEquipa(aux->item);
			free(aux);
		}
	}
}


/* ----------------------------------------------------- ORDENAR ----------------------------------------------------- */

int compara(const void *a, const void *b)
/* funcao que premite ordenar de acordo com o lexicografismo */
{
	char **aa, **bb;
	aa = (char **)a;
	bb = (char **)b;
	return strcmp(*aa, *bb);
}
