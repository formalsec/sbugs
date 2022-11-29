#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "hashtableequipas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*funcao hash que da em que slot vamos trabalhar*/
int hashe(char* v, int m) {
	int h = 0, a = 127;
	for (; *v != '\0'; v++)
		h = (a * h + *v) % m;
	return h;
}

/*inicializo a hashtable*/
linke* STiniciae(int M) {
	int i;
	linke* heads = can_fail_malloc(M * sizeof(linke));
	for (i = 0; i < M; i++) { /*coloco todas as posicoes da hashtable a NULL*/
		heads[i] = NULL;
	}
	return heads;
}

/*coloco uma equipa no inicio de uma lista (funcao auxiliar)*/
linke insereListe(linke head, equipa* eq) {
	linke e = can_fail_malloc(sizeof(struct nodee)); /*crio um novo linke*/
	e->equipa = eq;
	if (head == NULL){ /*se a lista ainda estiver vazia*/
	    e->next = NULL;
	    head = e;
	}
	else{ /*se ja existirem elementos na lista*/
    	e->next = head;
    	head = e;
	}
	return head;
}

/*coloco uma equipa no inicio de uma lista*/
void STinsertee(equipa* eq, int M, linke* heads) {
	int i = hashe(eq->nomeeq, M);
	heads[i] = insereListe(heads[i], eq);
}

/*procura uma equipa na lista (funcao auxiliar)*/
equipa* procuraListe(linke head, char* nome) {
    linke tmp = head;
	if (tmp == NULL) { /*se a lista estiver vazia*/
		return NULL;
	}
	while (tmp != NULL && strcmp(tmp->equipa->nomeeq, nome) != 0) { /*anda na lista enquanto nao encontra a equipa que quero*/
		tmp = tmp->next;
	}
	if (tmp != NULL && strcmp(tmp->equipa->nomeeq, nome) == 0) { /*quando encontra a equipa que queremos retorno essa equipa*/
		return tmp->equipa;
	}
	return NULL; /*se nao a encontrar*/
}

/*procura uma equipa na lista*/
equipa* STprocurae(char* nomeeq, int M, linke* heads) {
	int i = hashe(nomeeq, M);
	return procuraListe(heads[i], nomeeq);
}

/*liberto toda a memoria de um linke*/
void STfree_listhte(linke head) {
	linke tmp;
	while (head) {
		tmp = head->next;
		free(head->equipa->nomeeq);
		free(head->equipa);
		free(head);
		head = tmp;
	}
}

/*liberta toda a memoria usada na hashtable*/
void STfree_hte(int M, linke* heads) {
	int i;
	for (i = 0; i < M; i++) { /*liberto cada uma das listas da hashtable*/
		STfree_listhte(heads[i]);
	}
	free(heads);
}