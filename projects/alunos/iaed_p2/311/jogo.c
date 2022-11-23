#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "jogo.h"
#include "equipa.h"
#include "hash.h"
#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* funcao que inicializa um jogo, dado os seus atributos */

Jogo inicializa_jogo(char *nome, char *equipa1, char *equipa2, int score1, int score2){
	Jogo x = can_fail_malloc(sizeof(struct jogo));

	x->nome = can_fail_malloc(sizeof(char) * (strlen(nome) + 1));
	x->equipa1 = can_fail_malloc(sizeof(char) * (strlen(equipa1) + 1));
	x->equipa2 = can_fail_malloc(sizeof(char) * (strlen(equipa2) + 1));

	strcpy(x->nome, nome);
	strcpy(x->equipa1, equipa1);
	strcpy(x->equipa2, equipa2);
	x->score1 = score1;
	x->score2 = score2;

	return x;
}

/*lista de jogos- funcoes*/

int lengthJ(link_J head){
	int counter = 0;
	link_J x;
	for(x = head ; x != NULL; x = x->next)
		counter++;
	return counter;
}

link_J NewJ(Jogo jogo){
	link_J x = can_fail_malloc(sizeof(struct lista_jogo));
	x->jogo = jogo;
	x->next = NULL;
	return x;
}

link_J insertBeginJ(link_J head, Jogo jogo){
	link_J x = NewJ(jogo);
	x->next = head;
	return x;
}

link_J lookupJ(link_J head, char *nome){
	link_J t;
	for(t = head; t != NULL; t = t->next)
		if(strcmp(t->jogo->nome, nome) == 0)
			return t;
	return NULL;
}

void free_nodeJ(link_J x){
	free(x->jogo->nome);
    free(x->jogo->equipa1);
    free(x->jogo->equipa2);
    free(x->jogo);
    free(x);
}

/* apenas apaga o no (usado para a hashtable), o resto do ponteiros sao apagados na lista */
link_J semi_deleteJ(link_J head, char *nome){
	link_J t, prev;
	for(t = head, prev = NULL; t != NULL; prev = t, t = t->next){
		if(strcmp(t->jogo->nome, nome) == 0){
			if(t == head)
				head = t->next;
			else
				prev->next = t->next;
			free(t->jogo->nome);
			t->jogo->nome = NULL;
			free(t);
			break;
		}
	}
	return head;
}

/* encontra o NULL (ver funcao anterior) e apaga todos os ponteiros associados */
link_J deleteJ(link_J head){
	link_J t, prev;
	for(t = head, prev = NULL; t != NULL; prev = t, t = t->next){
		if(t->jogo->nome == NULL){
			if(t == head)
				head = t->next;
			else
				prev->next = t->next;
			free_nodeJ(t);
			break;
		}
	}
	return head;
}

void free_listaJ(link_J head){
	link_J x;
	while (head != NULL)
    {
       x = head;
       head = head->next;
       free_nodeJ(x);
    }
    return;
}

void printNodeJ(link_J h){
	printf("%s %s %s %d %d\n", h->jogo->nome, h->jogo->equipa1,
			 h->jogo->equipa2, h->jogo->score1, h->jogo->score2);
}

void print_inverso(link_J head, int contador){
	if(head == NULL)
		return;
	print_inverso(head->next, contador);
	
	printf("%d ", contador);
	printNodeJ(head);
}

/*hashtable de jogos*/

hashJ inicia_hash_jogo(int M){
	hashJ hash = can_fail_malloc(sizeof(link_J) * M);
	int i;

	for (i = 0; i < M; i++) 
		hash[i] = NULL;

	return hash;
}

hashJ insere_hash_jogo(hashJ jogos, Jogo jogo, int M) {
	int i = hash(jogo->nome, M);
	jogos[i] = insertBeginJ(jogos[i], jogo);
	return jogos;
}

hashJ retira_hash_jogo(hashJ jogos, char *nome, int M) {
	int i = hash(nome, M);
	jogos[i] = semi_deleteJ(jogos[i], nome);
	return jogos;
}

link_J procura_hash_jogo(hashJ jogos, char *nome, int M){
	int i;
	i =	hash(nome, M);
	return lookupJ(jogos[i], nome);
}

void free_hashJ(hashJ jogos, int M){
	int i;
	link_J head, x;

	for (i = 0; i < M; i++){
		head = jogos[i];
		while(head != NULL){
			x = head;
			head = head->next;
			free(x);
		}
	}
		
	free(jogos);
}