#include "tabela_equipa.h"
#include "tabela_jogo.h"
#include <stdbool.h>
#include <stdlib.h>

#define CALCULA_RES(A, B)	A == B? EMPATE: (A > B? VITORIA : DERROTA)
#define VITORIA 1
#define EMPATE 0 
#define DERROTA -1

/* Recebe uma string e devolve outra string, so que com o tamanho adequado */
char* novastring(char* s);