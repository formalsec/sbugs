#ifndef __COMANDOS__
#define __COMANDOS__
#include "item.h"

/* O tamanho maximo de um nome */
#define TAM_BUFFER 1024

/* valor pelo qual substituo a pontuacao/numero de vitorias num item apagado */
#define ITEM_APAGADO -1

/* valor que coloco como a pontuacao quando estou a usar a estrutura de dados "dados" como uma equipa */
#define EQUIPA -1

/* Prototipos das funcoes dos comandos */
void a(tabela *jogos,tabela *equipas,int NL,lista *jogosL);
void A(tabela *equipas,int NL,lista *equipasL);
void l(lista *jogosL,int NL);
void p(tabela *jogos,int NL);
void r(tabela *jogos,tabela *equipas,int NL);
void s(tabela *jogos,tabela *equipas,int NL);
void P(tabela *equipas,int NL);
void g(lista *equipasL,int NL);

#endif
