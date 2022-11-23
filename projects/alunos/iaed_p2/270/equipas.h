#ifndef EQUIPAS_H
#define EQUIPAS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* estrutura que representa as caracteristicas de uma equipa */
struct equipa{
  char *nome;
  int jogos_ganhos;
};

/* abstracoes para a estrutura das equipas */
typedef struct equipa* pEquipa;
#define nome(a) (a->nome)
#define jogos_ganhos(a) (a->jogos_ganhos)

/*prototipos das funcoes referentes ao manuseamento das equipas */
void liberta_equipa(pEquipa a);
void imprime_equipa(pEquipa a);
pEquipa nova_equipa(char *nome);
char* strdup(const char *s);

#endif
