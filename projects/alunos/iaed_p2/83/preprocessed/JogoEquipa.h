#ifndef JOGOEQUIPA_H
#define JOGOEQUIPA_H

#include <string.h>

/* Definicao do ponteiro para uma estrutura Jogo */
typedef struct struct_Jogo
{
    char* nome;
    char* equipa1;
    char* equipa2;
    int score1;
    int score2;


} *Jogo;


/* Definicao do ponteiro para uma estrutura Equipa */
typedef struct struct_Equipa
{
    char* nome;
    int vitorias;

} *Equipa;


#define eq(a, b) (strcmp(a,b)) /* Significa que o jogo/equipa a eh igual ao jogo/equipa b */


/* Prototipos das funcoes referentes aos jogos */
void freeJogo(Jogo a);
void printJogo(Jogo a);
Jogo newJogo(char* nome, char* equipa1, char* equipa2, int score1, int socre2);


/* Prototipos das funcoes referentes as equipas */
void freeEquipa(Equipa a);
void printEquipa(Equipa a);
Equipa newEquipa(char* nome, int vitorias);

#endif