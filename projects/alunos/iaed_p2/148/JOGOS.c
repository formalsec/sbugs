#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "JOGOS.h"

#define M 997

/* ------------------------------------------------------ JOGOS ------------------------------------------------------ */

ItemJ novoJogo(char *nome, char *equipa1, char *equipa2, int score1, int score2)
/* aloca memoria e atribui o nome, as equipas e o resultado */
{
	ItemJ novo = (ItemJ)can_fail_malloc(sizeof(struct Jogo));
	novo->nome = (char*)can_fail_malloc(sizeof(char)*(strlen(nome)+1));
	strcpy(novo->nome, nome);
	novo->equipa1 = (char*)can_fail_malloc(sizeof(char)*(strlen(equipa1)+1));
	strcpy(novo->equipa1, equipa1);
	novo->equipa2 = (char*)can_fail_malloc(sizeof(char)*(strlen(equipa2)+1));
	strcpy(novo->equipa2, equipa2);
	novo->score1 = score1;
	novo->score2 = score2;
	return novo;
}


void freeJogo(ItemJ a)
/* libertar memoria */
{
	free(a->equipa2);
	free(a->equipa1);
	free(a->nome);
	free(a);
}

void imprimeJogo(int nl, ItemJ a)
/* imprimir um determinado jogo */
{
	printf("%d %s %s %s %d %d\n", nl, a->nome, a->equipa1, a->equipa2, a->score1, a->score2);
}

/* ------------------------------------------------- HASHTABLE JOGOS ------------------------------------------------- */

int funcao_hashJ(char *v)
/* funcao que retorna o inteiro correspondente a key para a hashtable */
{
	int h = 0, a = 127;
	for (; *v != '\0'; v++)
	h = (a*h + *v) % M;
	return h;
}

int chave(char *nome)
/* funcao que devolve o inteiro correspondente a key */
{
	return funcao_hashJ(nome);
}

void iniciaJ(linkJ headsJ[])
/* inicia a hash */
{
	int i;
	for (i = 0; i < M; i++)
	{
		headsJ[i] = NULL;
	}
}

void inserirJ(ItemJ item, linkJ headsJ[])
/* inserir o jogo na hash */
{
	int i = funcao_hashJ(item->nome);
	headsJ[i] = inserir_inicioJ(headsJ[i], item);
}

linkJ inserir_inicioJ(linkJ head, ItemJ a)
/* inserir o jogo no inicio da lista */
{
	linkJ x = (linkJ)can_fail_malloc(sizeof(struct nodeJ));
	x->item = a;
	x->next = head;
	return x;
}


ItemJ procura_nome(char *nome, linkJ headsJ[])
/* devolve o jogo se este estiver na hash */
{
	int i = funcao_hashJ(nome);
	return procura_lista_nome(headsJ[i], nome);
}

ItemJ procura_lista_nome(linkJ head, char *nome)
/* devolve o jogo se estiver na lista caso contrario devolve NULL */
{
	linkJ t; 
	for (t = head; t != NULL; t = t->next)
	{
		if(strcmp(t->item->nome, nome) == 0)
		{
			return t->item;
		}
	}
	return NULL;
}

/* -----------------------------------------------  LISTA JOGOS ---------------------------------------------- */

lista *cria_lista()
/* criar e inicalizar a lista */
{
	lista *l = can_fail_malloc(sizeof(lista));
	l -> primeiro = l -> ultimo = NULL;
	return l;
}


void inserir_fim(lista *l, ItemJ jogo)
/* inserir o jogo no fim da lista */
{
	linkL n = can_fail_malloc(sizeof(struct nodeL));
	n -> item = jogo;
	n -> next = NULL;
	n -> prev = l -> primeiro;
	if (l -> ultimo)
	{
		l -> ultimo -> next = n;
	} 
	else 
		l -> primeiro = n;

	l -> ultimo = n;
}


void imprime_jogos(int nl, lista *l)
/* imipre todos os jogos presentes na lista */
{
	linkL n;
	for (n = l -> primeiro; n; n = n -> next)
		imprimeJogo(nl, n->item);
}


/* -----------------------------------------------  APAGA JOGO ---------------------------------------------- */

void apaga_jogo(linkJ headsJ[], lista *l, char *nome, int i)
/* a paga o jogo com um determinado nome */
{
	int comp;
	linkJ t, prev;
	linkL n = l -> primeiro;
 	for(t = headsJ[i], prev = NULL; t != NULL; prev = t, t = t->next) 
 	{
 		if(strcmp(t->item->nome, nome) == 0) 
 		{
 			if(t == headsJ[i])
 				headsJ[i] = t->next;
 			else
 				prev->next = t->next;
			break;
 		}
 	}
 	for(; n && (comp = strcmp(n->item->nome, nome)) != 0; n = n->next);
	if (n && !comp)
	{
		if (n -> prev) 
			n -> prev -> next = n -> next;
		else 
			l-> primeiro = n -> next;

		if (n -> next) n -> next -> prev = n -> prev;
		else l -> ultimo = n -> prev;
	}
	freeJogo(t->item);
	free(t);
	free(n);
}

void sair_jogos(lista *l, linkJ headsJ[])
/* libertar a memoria */
{
	linkJ t, aux;
	int i;
	for(i = 0; i < M; i++)
	{
		for(t = headsJ[i]; t != NULL;)
		{
			aux = t;
			t = t->next;
			apaga_jogo(headsJ, l, aux->item->nome, i);
		}
	}
	free(l);
}
