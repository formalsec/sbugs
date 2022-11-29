#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "jogo.h"
#include "equipa.h"
#include "hash.h"
#include "funcoes.h"

int hash(char *nome, int M){
	int h, a = 29478, b = 36178;
	for (h = 0; *nome != '\0'; nome++, a = a*b % (M-1))
		h = (a*h + *nome) % M;
	return h;
}