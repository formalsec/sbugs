#ifndef _INTERACAO_
#define _INTERACAO_
#include "equipa.h"
#define MAX_NOME 1023
#include <stdio.h>
#include "jogo.h"

/*Prototipos das funcoes que permitem a interacao com o utilizador*/
void novo_jogo(no_equipa *tabela_equipas[],lista_jogos **fila_jogos,no_jogo_tabela *tabela_jogos[],int linha);
void procura_jogo(no_jogo_tabela *tabela_jogos[],int linha);
void apaga_jogo_alvo(no_equipa *tabela_equipas[],no_jogo_tabela *tabela_jogos[], lista_jogos **fila_jogos,int linha);
void altera_score_jogo(no_jogo_tabela *tabela_jogos[],no_equipa *tabela_equipas[],int linha);
void adiciona_equipa_alvo(no_equipa *tabela_equipas[],int linha,int *numero_equipas);
void procura_equipa(no_equipa *tabela_equipas[],int linha);


#endif 

