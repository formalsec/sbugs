#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct str_jogo  {
        char *nome_jogo;
        char *equipa1;
        char *equipa2;
        int sc1;
        int sc2;
        unsigned long int id;
    } *Jogo;


typedef struct str_equipa {
    char *nome;
    int vitorias;
    unsigned long int id;
} *Equipa;

typedef unsigned long Key; /* tipo da chave */
#define key(a) (a->id)


/*prototipos das funcoes referentes as estruturas das equipas e jogos */
/*cria o id que depois vai formar a  hash*/
int cria_id(char *nome1);
Jogo novo_jogo(char *nome1,char *equipa_1,char *equipa_2, int sc1 , int sc2);
Equipa nova_equipa(char *nome_equipa);
void free_jogo(Jogo a);
void free_equipa(Equipa a);
#endif