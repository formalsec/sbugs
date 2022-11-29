#include "lista_equipas.h"

typedef struct str_TabEq{
	LstEqs** lst;
	int n_eqs;
} TabEquipas;


/* Dimensao da tabela */
#define DIM_TAB_EQ 499

/* Funcao de dispersao (Hashing) da tabela no caso das strings, devolve o hash de s */
int hashTabEq(char* s);

/* Devolve uma nova tabela de dispersao*/
TabEquipas* novaTabEq();

/* Adiciona uma equipa dada (eq) a tabela dada (tab) */
void pushTabEq(TabEquipas* tab, Equipa eq);

/* Devolve um ponteiro para a Equipa com o nome dado (nome) na tabela tab, devolve NULL caso nao exista */
Equipa* procuraTabEq(TabEquipas* tab, char* nome);

/* Copia todos os elementos da tabela tab para um array e devolve esse array */
Equipa* copiaTabEq(TabEquipas* tab);

/* Liberta toda a memoria reservada pela tabela e os seus elementos */
void destroiTabEq(TabEquipas* tab);

/* Funcao de comparacao para qsort */
int comparaEq(const void* a, const void* b);