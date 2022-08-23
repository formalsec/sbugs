#include <string.h>
#include <stdlib.h>

#include "equipas.h"


/* cria dinamicamente uma equipa */
equipa* nova_equipa(char nome_input[]) {
	equipa *nova_equipa;
	nova_equipa = malloc(sizeof(equipa));
	nova_equipa->nome = malloc(sizeof(char)*(strlen(nome_input)+1));
	strcpy(nova_equipa->nome, nome_input);
	nova_equipa->num_vitorias = 0;
	return nova_equipa;
}


/* liberta a memoria alocada por uma equipa */
void liberta_equipa(equipa *pt_equipa) {
	free(pt_equipa->nome);
	free(pt_equipa);
}
