#ifndef EQUIPA_H
#define EQUIPA_H


/* 
estrutura equipa 
caracterizada por:
- nome
- numero de vitorias
*/  
struct equipa{
    char *nome;
    int vitorias;
};

/* pEquipa eh um ponteiro para uma equipa */
typedef struct equipa* pEquipa;

/* liberta a memoria alocada para uma equipa */
void freeEquipa(pEquipa e);
/* imprime uma equipa */
void printEquipa(pEquipa e);
/* cria uma nova equipa */
pEquipa newEquipa(char *nome);

#endif