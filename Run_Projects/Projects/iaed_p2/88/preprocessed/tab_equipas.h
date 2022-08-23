#ifndef __HTEQUIPAS__
#define __HTEQUIPAS__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tab_disp.h"
#include "equipa.h"

/* Insere e retira equipa */
void insere_tab_equipa(tab_disp ht, equipa e);
void retira_tab_equipa(tab_disp ht, char *nome);

/* Liberta memoria da tabela */
void liberta_tab_equipas(tab_disp ht);

/* Procura equipa */
equipa procura_tab_equipa(tab_disp ht, char *nome);

/* Determina maximo de vitorias na tabela */
int max_vitorias_tab(tab_disp ht);

/* Mostra equipas mais vitoriosas */
void mostra_equipas_max(tab_disp tab_equipas, int num_linha);

#endif

