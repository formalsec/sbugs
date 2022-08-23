#ifndef _EQUIPAS_H_
#define _EQUIPAS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Definicao da estrutura que representa uma equipa. */

typedef struct
{
    char* nome;
    int vitorias;
} equipa;

/* Definicao dos prototipos das funcoes existentes no ficheiro Equipas.c. */

equipa* cria_equipa(char* nome);

equipa** insere_equipa_h(equipa** h_equipas, equipa* nova_equipa, int* cont_equipas, int* tam_h_equipas);

equipa** expande_h_equipas(equipa** h_equipas, int* cont_equipas, int* tam_h_equipas);

equipa* procura_equipa_h(char* nome, equipa** h_equipas, int tam_h_equipas);

void destroi_h_equipas(equipa** h_equipas, int tam_h_equipas);

#endif
