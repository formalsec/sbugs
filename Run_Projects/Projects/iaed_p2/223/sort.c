#include "sort.h"

/* troca a equipa correspondende ao no i com a equipa correspondente ao no j */
void swap(tlink i, tlink j) {
	Equipa aux;
	aux = i->equipa;
	i->equipa = j->equipa;
	j->equipa = aux;
}

/* ordena a lista fornecida por ordem lexicografica */
void sortlist(tlink head) {
	tlink i, j;
	for (i = head; i != NULL; i = i->next) {
		for (j = i->next; j != NULL; j = j->next) {
			if (strcmp((i->equipa)->nome, (j->equipa)->nome) > 0) {
				swap(i, j);
			}
		}
	}
}