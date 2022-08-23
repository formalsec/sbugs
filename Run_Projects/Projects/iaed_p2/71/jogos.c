#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jog_ligados.h"
#include "jogos.h"

jlink *init_jogos()
{
    int i;
    jlink *hash_jogos = (jlink *)malloc(sizeof(jlink) * MAXHASH);
    for (i = 0; i < MAXHASH; i++)
    {
        hash_jogos[i] = NULL;
    }
    return hash_jogos;
}

jlink novo_jlink(Jogo jogo, jlink cabeca)
{
	jlink link = malloc(sizeof(struct node_jogos));

	link->jogo = jogo;
	link->proximo = cabeca;
	return link;
}

jlink push_jogo(jlink cabeca, Jogo jogo)
{
    /* acrescenta um jlink novo a lista da cabeca */
	jlink nova_cabeca = novo_jlink(jogo, cabeca);
	return nova_cabeca;
}

void adiciona_jogo(jlink* hash_jogos, Lista_Jogos lista, Jogo jogo)
{
	int chave = hash(jogo->nome);
    acrescenta_jogo(lista, jogo);
	hash_jogos[chave] = push_jogo(hash_jogos[chave], jogo);
}

jlink rem_aux2(jlink cabeca, Jogo jogo)
{
	jlink atual, anterior = NULL;
	for (atual = cabeca; atual != NULL; atual = atual->proximo)
    {
        /* nao podemos fazer free(atual) porque perderiamos o resto da pilha */
		if (atual->jogo == jogo)
        {
            /* se atual for igual a cabeca nao podemos fazer 
            anterior->proximo, pois anterior e igual a NULL*/
			if (atual == cabeca)
                cabeca = atual->proximo;
			else
                anterior->proximo = atual->proximo;
			FREEjlink(atual);
			return cabeca;
		}
        else
            anterior = atual;
	}
	return cabeca;
}

void remove_jogo(jlink* hash_jogos, Lista_Jogos lista, Jogo jogo)
{
	int chave = hash(jogo->nome);
    rem_aux1(lista, jogo);
	hash_jogos[chave] = rem_aux2(hash_jogos[chave], jogo);
}

int existe_jogo_aux(jlink cabeca, char* nome)
{
	jlink x;
	for (x = cabeca; x != NULL; x = x->proximo)
    {
		if (strcmp(x->jogo->nome, nome) == 0)
        {
            return 1;
        }
	}
	return 0;
}

int existe_jogo(jlink *hash_jogos, char * nome)
{
    int chave = hash(nome);
    return existe_jogo_aux(hash_jogos[chave], nome);
}

Jogo procura_jogo_aux(jlink cabeca, char* nome)
{
	jlink x;
	for (x = cabeca; x != NULL; x = x->proximo)
    {
		if (strcmp(x->jogo->nome, nome) == 0)
            return x->jogo;
	}
	return NULL;
}

Jogo procura_jogo(jlink* hash_jogos, char* nome)
{
	int chave = hash(nome);
	return procura_jogo_aux(hash_jogos[chave], nome);
}

jlink limpa_lista_jogos(jlink cabeca)
{
    jlink atual, aux;
    /* Esta vazia */
	if (cabeca == NULL)
    {
        free(cabeca);
        return cabeca;
    }
    /* So tem um elemento */
    else if (cabeca->proximo == NULL)
    {
        FREEjlink(cabeca);
        return NULL;
    }
    /* Tem mais do que um elemento */
    else 
    {
        atual = cabeca->proximo;
        while (atual != NULL)
        {
            aux = cabeca->proximo;
            cabeca->proximo = aux->proximo;
            FREEjlink(aux);
            atual = cabeca->proximo;
        }
        FREEjlink(cabeca);
        return NULL;
    }
}

void limpa_hash_jogos(jlink *hash_jogos)
{
    int i;
    /* Limpamos a listas das cabecas uma a uma */
    for (i = 0; i < MAXHASH; i++)
    {
        hash_jogos[i] = limpa_lista_jogos(hash_jogos[i]);
    }
	free(hash_jogos);
}
