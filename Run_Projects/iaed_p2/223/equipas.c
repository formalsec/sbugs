#include "equipas.h"

/* dado um nome cria uma nova equipa com esse nome */
Equipa novaEquipa(char *nome) {
	Equipa e;
	e = malloc(sizeof(struct equipa));
	e->vitorias = 0;						/* todas as equipas comecam com zero vitorias */
	e->nome = malloc(sizeof(char)*(strlen(nome)+1));
	strcpy(e->nome, nome);
	return e;
}

/* liberta a memoria onde estava alocado o jogo e e os seus dados */
void libertaEquipa(Equipa e) {
	free(e->nome);
	free(e);
}

/* funcao que imprime as caracteristicas de uma equipa */
void imprimeEquipa(Equipa e) {
	printf("%s %d\n", e->nome, e->vitorias);
}

/*funcao que aumenta o numero de vitorias de uma equipa */
void aumentaVitorias(Equipa e) {
	(e->vitorias)++;
}

/* funcao que diminui o numero de vitorias de uma equipa */
void diminuiVitorias(Equipa e) {
	(e->vitorias)--;
}

/* funcao que devolve o numero de vitorias de uma equipa */
int obterVitorias(Equipa e) {
	return e->vitorias;
}

/* funcao que devolve o nome de uma equipa */
char * obterNomeEquipa(Equipa e) {
	return e->nome;
}