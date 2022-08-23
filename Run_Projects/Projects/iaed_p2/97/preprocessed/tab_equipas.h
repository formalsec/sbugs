#ifndef TAB_EQUIPAS
#define TAB_EQUIPAS

#include "LL_equipas.h"

/* Tamanho da tabela de dispersao para as equipas */
#define TAB_EQUIPA 1049

/* Cria a tabela de dispersao para as equipas */
elem_eq** incializa_tabela_equipa();

/* Corresponde a funcao encontra_equipa_lista, para a tabela de dispersao */
elem_eq* encontra_equipa_tabela(elem_eq **tab_eqs, char *nome);

/* Insere o Item_j e na tabela de dispersao */
elem_eq** insere_equipa_tabela(elem_eq **tab_eqs, Item_eq *e);

/* Apaga toda a tabela de dispersao e memoria associada */
void apaga_tabela_equipas(elem_eq **tab_eqs);

/* Retorna uma lista das equipas da tabela com mais pontos */
elem_eq* equipas_vencedoras(elem_eq **tab_eqs, int *maior);

#endif