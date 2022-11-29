#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "team_lists.h"

/* cria um novo no que contem um ponteiro para uma equipa */
tlink TNEW(Equipa equipa) {
	tlink x = can_fail_malloc(sizeof(struct tnode));
	x->equipa = equipa;
	x->next = NULL;
	return x;
}

/* insere no inicio da lista um novo no contendo a equipa indicada */
tlink TinsertBegin(tlink head, Equipa equipa) {
	tlink x = TNEW(equipa);
	x->next = head;
	return x;
}

/* insere no final da lista um novo no contendo a equipa indicada */
tlink TinsertEnd(tlink head, Equipa equipa) {
	tlink x;
	if (head == NULL) {
		return TNEW(equipa);
	}
	for (x = head; x->next != NULL; x = x->next);
	x->next = TNEW(equipa);
	return head;
}

/* procura na lista um no que contenha a equipa cujo nome e indicado por v */
tlink Tlookup(tlink head, char *v) {
	tlink t;
	for (t = head; t != NULL; t = t->next) {
		if (strcmp((t->equipa)->nome, v) == 0) {
			return t;
		}
	}
	return NULL;
}

/* caso n = 1, remove o no da lista e a informacao relativa a equipa do sistema, caso 
contrario apenas remove o no */
tlink TremoveItem(tlink head, Equipa equipa, int n) {
	tlink t, prev;
	for (t = head, prev = NULL; t != NULL; prev = t, t = t->next) {
		if (strcmp((t->equipa)->nome, equipa->nome) == 0) {
			if (t == head) {
				head = t->next;
			}
			else {
				prev->next = t->next;
			}
			if (n == 1) {					/* ha situacoes em que apenas se pretende remover o no e nao a equipa */
				libertaEquipa(equipa);
			}
			free(t);
			break;
		}
	}
	return head;
}