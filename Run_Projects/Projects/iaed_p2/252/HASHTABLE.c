#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HASHTABLE.h"

/*Funcao de hashing a partir de strings*/
unsigned int string_hash(void *string)
{

	unsigned int result = 5381;
	unsigned char *p;

	p = (unsigned char *) string;

	while (*p != '\0') {
		result = (result << 5) + result + *p;
		++p;
	}

	return result;
}



void HashEquipa(team_list* l,Equipa* nova_equipa)
{
    int numHash;
    nova_equipa->next = NULL;
    nova_equipa->previous = l->last;
    nova_equipa->collision = NULL;

    numHash = string_hash(nova_equipa->nome) % HASHSIZE;

    if (*(l->hashtable + numHash) == NULL) 
    {
        *(l->hashtable + numHash) = nova_equipa;
    }
    else 
    {
        nova_equipa->collision = *(l->hashtable + numHash);
        *(l->hashtable + numHash) = nova_equipa;
    }

    if (l -> head == NULL) 
    {
        l->head = nova_equipa;
    }
    else 
    {
    	l->last->next = nova_equipa;
    }

    l->last = nova_equipa;
}


void HashJogo(game_list* l,Jogo* novo_jogo)
{
    int numHash;

    novo_jogo->next = NULL;
    novo_jogo->previous = l->last;
    novo_jogo->collision = NULL;

    numHash = string_hash(novo_jogo->nome) % HASHSIZE;

    if (*(l->hashtable + numHash) == NULL){
        *(l->hashtable + numHash) = novo_jogo;
    } 
    else{
        novo_jogo->collision = *(l->hashtable + numHash);
        *(l->hashtable + numHash) = novo_jogo;
    }

    if (l -> head == NULL){
        l->head = novo_jogo;
    } 
    else{
        l->last->next = novo_jogo;
    }

    l->last = novo_jogo;
}