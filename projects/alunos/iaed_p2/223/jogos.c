#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "jogos.h"

/* dado um nome, duas equipas e dois inteiros correspondentes ao score, cria um jogo */
Jogo novoJogo(char *nome, Equipa e1, Equipa e2, int s1, int s2) {
	Jogo j;
	j = can_fail_malloc(sizeof(struct game));
	j->nome = can_fail_malloc(sizeof(char)*(strlen(nome)+1));
	strcpy(j->nome, nome);
	j->equipa1 = e1;
	j->equipa2 = e2;
	j->score1 = s1;
	j->score2 = s2;
	return j;
}

/* liberta a memoria onde estava alocado o jogo j e os seus dados */
void libertaJogo(Jogo j) {
	free(j->nome);
	free(j);
}

/* imprime os dados de um jogo */
void imprimeJogo(Jogo j) {
	printf("%s %s %s %d %d\n", j->nome, (j->equipa1)->nome, (j->equipa2)->nome, j->score1, j->score2);
}

/* altera a pontuacao de um jogo */
void alteraPont(Jogo j, int s1, int s2) {
	j->score1 = s1;
	j->score2 = s2;
}

/* obtem a pontuacao de um jogo relativa a uma equipa. se p = 1 relativo a equipa 1,
caso contrario relativo a equipa 2 */
int obtemPont(Jogo j, int p) {
	if (p == 1) {
		return j->score1;
	}	
	return j->score2;
}

/* obtem as equipas que compoem um jogo. se e = 1 retorna a equipa 1, caso contrario
retorna a equipa 2 */
Equipa obtemEquipa(Jogo j, int e) {
	if (e == 1) {
		return j->equipa1;
	}
	return j->equipa2;
}

/* retorna o nome do jogo j */
char * obtemNomeJogo(Jogo j) {
	return j->nome;
}