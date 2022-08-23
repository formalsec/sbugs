#include "game_lists.h"

/* cria novo no que contem um ponteiro para um jogo */
glink GNEW(Jogo jogo) {
	glink x = malloc(sizeof(struct gnode));
	x->jogo = jogo;
	x->next = NULL;
	return x;
}

/* insere um no no inicio de uma lista de jogos */
glink GinsertBegin(glink head, Jogo jogo) {
	glink x = GNEW(jogo);
	x->next = head;
	return x;
}

/* insere um no no fim de uma lista de jogo */
glink GinsertEnd(glink head, Jogo jogo) {
	glink x;
	if (head == NULL) {
		return GNEW(jogo);
	}
	for (x = head; x->next != NULL; x = x->next);
	x->next = GNEW(jogo);
	return head;
}

/* procura numa lista de jogos, o no com o jogo de nome v */
glink Glookup(glink head, char *v) {
	glink t;
	for (t = head; t != NULL; t = t->next) {
		if (strcmp((t->jogo)->nome, v) == 0) {
			return t;
		}
	}
	return NULL;
}

/* caso n != 1 remove um no de uma lista de jogos, caso n = 1, para alem de remover apenas o no
remove o proprio jogo */
glink GremoveItem(glink head, Jogo jogo, int n) {
	glink t, prev;
	for (t = head, prev = NULL; t != NULL; prev = t, t = t->next) {
		if (strcmp((t->jogo)->nome,jogo->nome) == 0) {
			if (t == head) {
				head = t->next;
			}
			else {
				prev->next = t->next;
			}
			if (n == 1) {				/* ha situacoes em que nao e pretendido apagar o jogo do sitema, mas apenas o no da lista */
				libertaJogo(jogo);
			}
			free(t);
			break;
		}
	}
	return head;
}

