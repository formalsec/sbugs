#ifndef struct_H
#define struct_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Ficheiro que contem as estruturas utilizadas no projeto */

#define NOME      1024 /* Maximo de caracteres utilizado num nome de um jogo */
#define EQUIPAS   1024 /* Maximo de caracteres utilizado num nome de uma equipa */
#define HASHSIZE  2497 /* Tamanho da hashtable (numero primo) */


/* Estrutura de uma equipa: 
	Contem, para alem da informacao que a compoe como nome e numero de vitorias, ponteiros que 
	permitem a implementacao da lista duplamente ligada, anterior e proximo. */

typedef struct equipa {
	struct equipa *anterioreq, *proximoeq;
	char* nomeeq;
	int vitorias;
} equipa;


/* Estrutura de um jogo: 
	Contem, para alem da informacao que o compoe como nome, equipa1, equipa2, score1 e score2, 
	ponteiros que permitem a implementacao da lista duplamente ligada, anterior e proximo. */

typedef struct jogo {	
	struct jogo *anteriorj, *proximoj;
	char* nomej;
	struct equipa *equipa1;
	struct equipa *equipa2;
	int score1;
	int score2;
} jogo;


/* 	Estrutura da lista equipas:
 	Contem os ponteiros que permitem apontar para o primeiro e ultimo elemento da lista duplamente 
	ligada. Contem tambem a hashtable implementada para as equipas. */

typedef struct listaequipas {
	struct equipa *inicioeq, *fimeq, *hashequipas[HASHSIZE];
} listaequipas;


/* 	Estrutura da lista jogos:
 	Contem os ponteiros que permitem apontar para o primeiro e ultimo elemento da lista duplamente 
	ligada. Contem tambem a hashtable implementada para os jogos. */

typedef struct listajogos {	
	struct jogo *inicioj, *fimj, *hashjogos[HASHSIZE];
} listajogos;

#endif
