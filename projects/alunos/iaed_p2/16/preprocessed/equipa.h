#ifndef _EQUIPA_
#define _EQUIPA_

/* Estrutura equipa */
typedef struct equipa {
    char* nome;
    int   numeroVitorias;
} equipa;

equipa* criaEquipa(char* nome);
void    freeEquipa(equipa* Equipa);
void    printEquipa(equipa* Equipa, int* pNL);

#endif
