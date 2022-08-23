#ifndef JOGO_H
#define JOGO_H

/* 
estrutura jogo 
caracterizada por:
- nome
- nomes das equipas 1 e 2
- scores das equipas 1 e 2
 */
struct jogo {
    char *nome,*equipa1,*equipa2;
    int score1,score2;
};

/* pJogo eh um ponteiro para um jogo */
typedef struct jogo* pJogo; 

/* liberta a memoria alocada para um jogo */
void freeJogo(pJogo j);
/* imprime um jogo */
void printJogo(pJogo j);
/* cria um novo jogo */
pJogo newJogo(char*nome,char*equipa1,char*equipa2,int score1,int score2);


#endif
