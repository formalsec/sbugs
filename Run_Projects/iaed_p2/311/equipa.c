#include "jogo.h"
#include "equipa.h"
#include "hash.h"
#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*lista de equipas- funcoes (inspirado nos slides) */

int lengthE(link_E head){
	int counter = 0;
	link_E x;
	for(x = head ; x != NULL; x = x->next)
		counter++;
	return counter;
}

link_E NewE(Equipa equipa){
	link_E x = malloc(sizeof(struct lista_equipa));
	x->equipa = equipa;
	x->next = NULL;
	return x;
}

link_E insertBeginE(link_E head, Equipa equipa){
	link_E x = NewE(equipa);
	x->next = head;
	return x;
}

link_E lookupE(link_E head, char *nome){
	link_E t;
	for(t = head; t != NULL; t = t->next)
		if(strcmp(t->equipa->nome, nome) == 0)
			return t;
	return NULL;
}

/* e usado apenas para a lista de vencedores, 
apaga apenas o no, o ponteiro continua guardado na hashtable */
link_E deleteE(link_E head, char *nome){
	link_E t, prev;
	for(t = head, prev = NULL; t != NULL; prev = t, t = t->next){
		if(strcmp(t->equipa->nome, nome) == 0){
			if(t == head)
				head = t->next;
			else
				prev->next = t->next;
			free(t);
			break;
		}
	}
	return head;
}

void printNodeE(link_E head){
	printf("%s %d\n", head->equipa->nome, head->equipa->wins);
}

void free_listaE(link_E head){
	link_E x;
	while (head != NULL)
    {
       x = head;
       head = head->next;
       free(x->equipa->nome);
       free(x->equipa);
	   free(x);
    }
    return;
}

void free_nodesE(link_E head){
	link_E x;
	while (head != NULL)
    {
       x = head;
       head = head->next;
	   free(x);
    }
    return;
}

/*hashtable de equipas*/

hashE inicia_hash_equipa(int M){
	hashE hash = malloc(sizeof(link_E) * M);
	int i;

	for (i = 0; i < M; i++) 
		hash[i] = NULL;

	return hash;
}

hashE insere_hash_equipa(hashE equipas, Equipa equipa, int M) {
	int i = hash(equipa->nome, M);
	equipas[i] = insertBeginE(equipas[i], equipa);
	return equipas;
}

void free_hashE(hashE equipas, int M){
	int i;

	for (i = 0; i < M; i++)
		free_listaE(equipas[i]); 

	free(equipas);
}

link_E procura_hash_equipa(hashE equipas, char *nome, int M){
	int i;
	i =	hash(nome, M);
	return lookupE(equipas[i], nome);
}

/* compara strings (de equipas) para ficarem organizadas pelo qsort por oredm lexicografica */

int compara(const void *e1, const void *e2){
	const char **equipa1 = (const char**)e1;
	const char **equipa2 = (const char**)e2;

	return strcmp(*equipa1, *equipa2);
}

/*debug*/

void print_lista_equipa(link_E head, int contador){
	for( ; head != NULL; head = head->next){
		printf("%d ", contador);
		printNodeE(head);
	}
	return;
}