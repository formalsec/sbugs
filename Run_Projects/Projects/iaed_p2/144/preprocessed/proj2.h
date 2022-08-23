#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_eq.h"
#include "hash_jg.h"

void adiciona_jogo(int *ptr, lJogo* jogos,lEquipa* equipas, LDupla lst_jgs);  
void adiciona_equipa(int *ptr, lEquipa* equipas);      
void lista_jogos(int *ptr, LDupla lst_jgs);      
void procura_jogo(int *ptr, lJogo* jogos);   
void procura_equipa(int *ptr, lEquipa* equipas);   
void apaga_jogo(int *ptr, lJogo* jogos,lEquipa* equipas, LDupla lst_jgs);
void altera_pontos(int *ptr, lJogo* jogos, lEquipa* equipas, LDupla lst_jgs); 
void melhores_equipas(int *ptr, lEquipa* equipas);
