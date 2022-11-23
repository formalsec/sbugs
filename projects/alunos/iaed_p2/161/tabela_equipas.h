#include "equipa.h"
#include "hash.h"


typedef struct tabela_equipas
{
    unsigned int num_equipas; /* numero de equipas na tabela*/
    unsigned int tamanho; /* tamanho da tabela */
    pEquipa *equipas; /* vetor de equipas */
    
} *pTabela_equipas; /* pTabela_equipas eh um ponteiro para a struct tabela_equipas */


/* prototipos ---------------------------------------------------------------------------------- */

/* cria uma tabela de equipas vazia e devolve o seu ponteiro */
pTabela_equipas inicializa_tabela_equipas(unsigned int);

/* adiciona uma equipa 'a tabela */
void adiciona_equipa_tabela(pTabela_equipas, pEquipa);

/* devolve o ponteiro da equipa, se existir,
senao, devolve NULL */
pEquipa procura_equipa_tabela(pTabela_equipas, char*);

/* escreve as melhores equipas */
void print_melhores_equipas(pTabela_equipas, unsigned int);

/* liberta a memoria da tabela e das equipas */
void destroi_tabela_equipas(pTabela_equipas);
