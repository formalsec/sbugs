#ifndef STRUC_H
#define STRUC_H


/* #################################################################################################### */

typedef struct node_equipas
{
	struct node_equipas *next, *previous;
	char *name;
	int Jogos_ganhos;
	/* Jogos ganhos e um inteiro que contabiliza os jgs ganhos por este node ao longo do programa*/

}node_equipas;

/* #################################################################################################### */

typedef struct node_jogos
{
	struct node_jogos *next, *previous;
	char *jogo;
	/* id das equipas 1 e 2 */
	char *equipa1;
	char *equipa2;
	int valor1;
	/* Valor da equipa 1 */
	int valor2;
	/* Valor da equipa 2 */
}node_jogos;


/* #################################################################################################### */

typedef struct lista_jogos
{
	struct node_jogos *head, *last;
	/* Primeiro e ultimo elemento de uma lista ligada */

}lista_jogos;


/* #################################################################################################### */

typedef struct Lista_equipas
{
	struct node_equipas *head, *last;

}lista_equipas;


/* #################################################################################################### */




#endif
