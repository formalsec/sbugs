#ifndef EQUIPAS_H
#define EQUIPAS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct equipas
{
    char *nome;
    int vitorias;
}*ptr_equipas;

typedef struct no_equipas
{
    ptr_equipas equipa;
    struct no_equipas *proximo;
} *link_e; /*ponteiro para no*/

/*---------- funcoes para listas ligadas ----------*/
/*cria uma nova equipa*/
ptr_equipas nova_equipa(char *nome, int vitorias);

/*insere uma equipa y numa lista por ordem alfabetica*/
link_e insere_alfabetica(link_e primeiro, link_e y);

/*insere uma equipa y no inicio da lista*/
link_e insere_inicio_e(link_e primeiro, link_e y);

/*procura uma equipa numa lista ligada com o nome passado como input*/
link_e procura_e(link_e primeiro, char* nome);

/*da free do nome da equipa*/
void FreeNome_e(link_e x);

/*da free do no_equipa*/
void FreeNode_e(link_e x);

/*---------- funcoes para a hashtable das equipas ----------*/
/*inicializa a hashtable das equipas*/
link_e* inicializa_e(link_e *primeiros);

/*insere uma euqipa na hashtable*/
void insere_equipa(link_e *primeiros, link_e y);

/*procura uma equipa na hashtable com o nome passado como input*/
link_e procura_equipa(link_e *primeiros, char* nome);

#endif

