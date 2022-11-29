#include <string.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct equipa 
{
    char *nome;      /* nome da equipa */
    unsigned int num_vitorias;  /* numero de vitorias da equipa */

}*pEquipa; /* pEquipa eh um pointeiro para uma struct equipa */


/* prototipos ---------------------------------------------------------------------------------- */

/* cria um equipa e devolve um ponteiro para a equipa */
pEquipa cria_equipa(char*);

/* devolve o nome da equipa */
char* obtem_nome_equipa(pEquipa);

/* devolve o numero de vitorias da equipa */
int obtem_vitorias_equipa(pEquipa);

/* altera o numero de vitorias da equipa */
void altera_vitorias_equipa(pEquipa, int);

/* escreve o nome e numero de vitorias da equipa */
void print_equipa(pEquipa, unsigned int);

/* liberta a memoria alocada para a equipa */
void free_equipa(pEquipa);
