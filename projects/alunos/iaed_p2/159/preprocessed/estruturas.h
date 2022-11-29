#ifndef ESTRUTURAS
#define ESTRUTURAS

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX 911
/*Chave para o calculo do indice de uma hash table.
Neste caso e o nome de tanto uma Equipa ou de um Jogo*/
#define key(a) (a->nome)
/*Devolve igualdade entre strings*/
#define eq(a,b) (!strcmp(a,b))




/*ESTRUTURA "EQUIPA" */

typedef struct equipa
{
	char * nome; /* nome da equipa*/
	unsigned int jogos_ganhos; /* numero de jogos ganhos pela equipa*/

}equipa;

typedef struct equipa* Equipa;



/*ESTRUTURA "JOGO" */

typedef struct jogo
{
	char * nome; /* nome do jogo*/
	Equipa e1; /* ponteiros para as equipas*/
	Equipa e2; 
	unsigned int s1; /*pontuacoes das equipas*/
	unsigned int s2;

}jogo;


typedef struct jogo* Jogo;

typedef char* Key;

extern char * strdup(const char*);



/*prototipos de manipulacao do tipo "Equipa" */
void free_Equipa(Equipa e);
void print_Equipa(Equipa e,unsigned int num_linhas);
Equipa new_Equipa(char * nome);


/* prototipos de manipulacao do tipo "Jogo" */
void free_Jogo(Jogo j);
void print_Jogo(Jogo j, unsigned int num_linhas);
Jogo new_Jogo(char *nome, Equipa e1, Equipa e2,
	unsigned int s1, unsigned int s2);

#endif