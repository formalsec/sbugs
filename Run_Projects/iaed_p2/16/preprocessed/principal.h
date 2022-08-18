#ifndef _COMUM_
#define _COMUM_

#include "listaJogo.h"
#include "listaEquipa.h"

void  analisaComando(char* comando, listaJogo** headsJogos, listaEquipa** headsEquipas, listaJogo* listaDeJogos, listaEquipa* listaDeEquipas, int M_J, int M_E, int* pNL);
void  a_adicionaJogo(char* comando, listaJogo** headsJogos, listaEquipa** headsEquipas, listaJogo* Lista, int M_J, int M_E, int* pNL);
void  l_listaJogos(listaJogo* Lista, int* pNL);
void  p_procuraJogo(char* comando, listaJogo** headsJogos, int M_J, int* pNL);
void  r_apagaJogo(char* comando, listaJogo** headsJogos, listaJogo* Lista, listaEquipa** headsEquipas, int M_J, int M_E, int* pNL);
void  s_alteraScoreJogo(char* comando, listaJogo** headsJogos, listaEquipa** headsEquipas, int M_J, int M_E, int* pNL);
void  A_adicionaEquipa(char* comando, listaEquipa** headsEquipas, listaEquipa* listaDeEquipas, int M_E, int* pNL);
void  P_procuraEquipa(char* comando, listaEquipa** headsEquipas, int M_E, int* pNL);
void  g_listaEquipasComMaisVitorias(listaEquipa* listaDeEquipas, int* pNL);

int   comparaStrings(const void* string1, const void* string2);
int   obtemNumero(char* comando, int* pi);
char* obtemString(char* comando, int* pi);

#endif
