#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "jogo.h"

Jogo novoJogo(char* nome, char* eq1, char* eq2, int sc1, int sc2, int id){
	Jogo j;

	j.id = id;
	j.nome = nome;
	j.equipa1 = eq1;
	j.equipa2 = eq2;
	j.score1 = sc1;
	j.score2 = sc2;

	return j;
}

void destroiJogo(Jogo j){
	free(j.nome);
	free(j.equipa1);
	free(j.equipa2);
}