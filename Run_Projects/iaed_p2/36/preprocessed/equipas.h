#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

typedef struct equipa{
  char * nome;
  int vitorias;
  struct equipa * next;
}equipa;

typedef struct hashE{
    equipa ** entradas;
}hashE;

void adicionaVitoria(hashE * e, char * nome);
void retiraVitoria(hashE * e, char * nome);
int hash(char * nome);
hashE * criaHashE();
equipa * procuraEquipa(hashE * hash, char * nome);
int adicionaEquipa(hashE * hash, char * nome);
