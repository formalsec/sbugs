#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Funcoes.h"

int main(){
	char c;
	int* Contador_Instrucoes = malloc(sizeof(int));
	Hash_Equipa* ptr_HTE = hash_init_EQUIPAS();
	Hash_Jogo* ptr_HTJ = hash_init_JOGOS();
	Lista_Equipas* CE = cria_lista_Equipas();
	Lista_Jogos* CJ = cria_lista_Jogos();
	*Contador_Instrucoes = 0;

	while ((c = getchar()) != 'x'){
		if (c == 'a'){
			a(ptr_HTJ, ptr_HTE, CJ, Contador_Instrucoes);
		}
		if (c == 'l'){
			l(CJ, Contador_Instrucoes);
		}
		if (c == 'p'){
			p(ptr_HTJ, Contador_Instrucoes);
		}
		if (c == 'r'){
			r(ptr_HTJ, ptr_HTE, CJ, Contador_Instrucoes);
		}
		if (c == 's'){
			s(ptr_HTJ, ptr_HTE, Contador_Instrucoes);
		}
		if (c == 'A'){
			A(ptr_HTE, CE, Contador_Instrucoes);
		}
		if (c == 'P'){
			P(ptr_HTE, Contador_Instrucoes);
		}
		if (c == 'g'){
			g(CE, Contador_Instrucoes);
		}
	}
	/*Liberta a memoria alocada pela hash e lista de jogo e equipas*/
	Liberta_HTE(ptr_HTE);
	Liberta_HTJ(ptr_HTJ);
	Liberta_Lista_Equipas(CE);
	Liberta_Lista_Jogo(CJ);
	free(Contador_Instrucoes);
	return 0;
}
