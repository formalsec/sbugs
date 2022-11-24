#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "equipa.h"

Equipa novaEquipa(char* nome){
	Equipa e;
	
	e.nome = nome;
	e.vitorias = 0;

	return e;
}

void destroiEquipa(Equipa e){
	free(e.nome);
}