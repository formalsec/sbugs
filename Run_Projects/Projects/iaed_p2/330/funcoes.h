#ifndef FUNCOES_H
#define FUNCOES_H
#include "hashtable.h"

/*Declaracao de prototipos*/
void a(Hequipas *TabEquipas, Hjogos *TabJogos,Cabeca_cauda *extremos_lista_jogos, int *NL);
void l(int *NL, Cabeca_cauda *extremos_lista_jogos);
void p(Hjogos *TabJogos, int *NL);
Equipa *A(Hequipas *TabEquipas, Equipa *cabeca_equipas, int *NL);
void P(Hequipas *TabEquipas, int *NL);
void s(Hequipas *TabEquipas, Hjogos *TabJogos, int *NL);
void g(int *NL, Equipa *cabeca_equipas);
void r(int *NL, Hjogos *TabJogos, Hequipas *TabEquipas, Cabeca_cauda *extremos_lista_jogos);
void sort(char* arr[], int n);

#endif