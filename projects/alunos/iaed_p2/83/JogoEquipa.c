#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "JogoEquipa.h"

#define CARACTERES_MAX 1023


/* Funcao auxiliar que aloca e copia uma string para um dado espaco de memoria, 
   tendo essa string um numero limite de bytes 
*/
char *strndup(const char *s, size_t n) 
{
    char *p = memchr(s, '\0', n);
    if (p != NULL)
        n = p - s;
    p = can_fail_malloc(n + 1);
    if (p != NULL) {
        memcpy(p, s, n);
        p[n] = '\0';
    }
    return p;
}


/* Implementacao das funcoes referentes aos Jogos */

/* Funcao auxiliar que liberta a memoria que um dado Jogo "a" ocupa */
void freeJogo(Jogo a)
{
    free(a -> nome);
    free(a -> equipa1);
    free(a -> equipa2);
    free(a);
}


/* Funcao auxiliar que imprime um dado jogo */ 
void printJogo(Jogo a)
{
    printf("%s %s %s %d %d\n", a -> nome, a -> equipa1, a -> equipa2, a -> score1, a-> score2);
}


/* Funcao auxiliar que cria um novo jogo e aloca memoria para o guardar */
Jogo newJogo(char* nome, char* equipa1, char* equipa2, int score1, int score2)
{
    Jogo new = (Jogo)can_fail_malloc(sizeof(struct struct_Jogo));
    new -> nome = strndup(nome, CARACTERES_MAX);
    new -> equipa1 = strndup(equipa1, CARACTERES_MAX);
    new -> equipa2 = strndup(equipa2, CARACTERES_MAX);
    new -> score1 = score1;
    new -> score2 = score2;
    
    return new; 
}



/* Implementacao das funcoes referentes as Equipas */

/* Funcao auxiliar que liberta a memoria que uma dada equipa ocupa */
void freeEquipa(Equipa a)
{
    free(a -> nome);
    free(a);
}


/* Funcao auxiliar que imprime o nome da equipa juntamente com o numero de vitorias */
void printEquipa(Equipa a)
{
    printf("%s %d\n", a -> nome, a -> vitorias);
}


/* Funcao auxiliar que aloca memoria para ser guardada uma nova equipa */
Equipa newEquipa(char* nome, int vitorias)
{
    Equipa new = (Equipa)can_fail_malloc(sizeof(struct struct_Equipa));
    new -> nome = strndup(nome, CARACTERES_MAX);
    new -> vitorias = vitorias;

    return new;
}