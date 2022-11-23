#ifndef HASH_TABLEJ
#define HASH_TABLEJ
#include "hashtableequipas.h"
#include <stdlib.h>

typedef struct {
    char* nome;
    equipa* equipa1;
    equipa* equipa2;
    int score1;
    int score2;
} jogo;

typedef struct nodej{
    jogo* jogo;
    struct nodej* next;
} *linkj;

linkj* STiniciaj(int M); /*inicializo a hashtable*/
void STinserej(jogo* jg, int M, linkj* heads);  /*coloco um jogo no inicio de uma lista*/
void STapagaj(jogo* jg, int M, linkj* heads); /*remove um jogo da lista*/
jogo* STprocuraj(char* nome, int M, linkj* heads); /*procura um jogo na lista*/
void STfree_htj(int m, linkj* heads); /*liberta tuda a memoria usada na hashtable*/

#endif