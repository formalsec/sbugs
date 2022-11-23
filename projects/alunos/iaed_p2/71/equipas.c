#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "eq_ligadas.h"
#include "equipas.h"

/* Alocamos um vetor com MAXHASH elinks nulos */
/* Cada posicao da tabela e o inicio de uma lista ligada*/
elink * init_equipas()
{
    int i;
    elink * hash_equipas = can_fail_malloc(sizeof(elink) * MAXHASH);
    for (i = 0; i < MAXHASH; i++)
    {
        hash_equipas[i] = NULL;
    }
    return hash_equipas;
}

elink novo_elink(Equipa equipa, elink cabeca)
{
	elink link = can_fail_malloc(sizeof(struct node_equipas));

	link->equipa = equipa;
	link->proxima = cabeca;
	return link;
}

elink push_equipa(elink cabeca, Equipa equipa)
{
    /* acrescenta um elink nova a lista da cabeca */
	elink nova_cabeca = novo_elink(equipa, cabeca);
	return nova_cabeca;
}

void adiciona_equipa(elink* hash_equipas, Equipa equipa)
{
	int chave = hash(equipa->nome);
	hash_equipas[chave] = push_equipa(hash_equipas[chave], equipa);
}

int existe_eq_aux(elink cabeca, char* nome)
{
	elink x;
	for (x = cabeca; x != NULL; x = x->proxima)
    {
		if (strcmp(x->equipa->nome, nome) == 0)
        {
            return 1;
        }
    }
	return 0;
}

int existe_equipa(elink* hash_equipa, char* nome)
{
	int chave = hash(nome);
	return existe_eq_aux(hash_equipa[chave], nome);
}

Equipa procura_eq_aux(elink cabeca, char* nome)
{
	elink x;
	for (x = cabeca; x != NULL; x = x->proxima)
    {
		if (strcmp(x->equipa->nome, nome) == 0)
            return x->equipa;
	}
	return NULL;
}

Equipa procura_equipa(elink* hash_equipa, char* nome)
{
	int chave = hash(nome);
	return procura_eq_aux(hash_equipa[chave], nome);
}

elink limpa_lista_eq(elink cabeca)
{
    elink atual, aux;
    /* Esta vazia */
	if (cabeca == NULL)
    {
        free(cabeca);
        return cabeca;
    }
    /* So tem um elemento */
    else if (cabeca->proxima == NULL)
    {
        FREEelink(cabeca);
        return NULL;
    }
    /* Tem mais do que um elemento */
    else 
    {
        atual = cabeca->proxima;
        while (atual != NULL)
        {
            aux = cabeca->proxima;
            cabeca->proxima = aux->proxima;
            FREEelink(aux);
            atual = cabeca->proxima;
        }
        FREEelink(cabeca);
        return NULL;
    }
}

void limpa_hash_eq(elink* hash_equipas)
{
	int i;
    /* Limpamos a listas das cabecas uma a uma */
	for (i = 0; i < MAXHASH; i++)
    {
        hash_equipas[i] = limpa_lista_eq(hash_equipas[i]);    
    }
	free(hash_equipas);
}

int calcula_max_ganhos(elink * hash_equipas, int max_ganhos)
{
    elink link;
    int i;
    for (i = 0; i < MAXHASH; i++)
    {
        for (link = hash_equipas[i]; link != NULL; link = link->proxima)
        {
            /* Se os jogos ganhos forem maiores do que max_ganhos,
            max_ganhos passa a ser os jogos ganhos pela equipa*/
            if (link->equipa->total_ganhos > max_ganhos)
            {
                max_ganhos = link->equipa->total_ganhos;
            }
        }
    }
    return max_ganhos;
}

void obter_equipas(elink cabeca, Lista_Equipas lista, int max_ganhos)
{
    elink atual;
    for (atual = cabeca; atual != NULL; atual = atual->proxima)
    {
        /* So acrescenta as que tiverem o numero de jogos ganhos certo */
        if (atual->equipa->total_ganhos == max_ganhos)
            acrescenta_eq(lista, atual->equipa);
    }
}
