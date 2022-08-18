#include "lista_jogos.h"

typedef struct str_TabJogos{
	LstJogos** lst;
	int n_jogos;
} TabJogos;

/* Dimensao da tabela */
#define DIM_TAB_JOGOS 499

/* Funcao de dispersao (Hashing) da tabela no caso das strings, devolve o hash de s*/
int hashTabJogos(char* s);

/* Devolve uma nova tabela de dispersao */
TabJogos* novaTabJogos();

/* Adiciona um Jogo dado (j) a tabela dada (tab) */
void pushTabJogos(TabJogos* tab, Jogo j);

/* Devolve um ponteiro para o Jogo com o nome dado (nome) na tabela tab, devolve NULL caso nao exista */
Jogo* procuraTabJogos(TabJogos* tab, char* nome);

/* Copia todos os elementos da tabela para um array e devolve ese array */
Jogo* copiaTabJogos(TabJogos* tab);

/* Liberta toda a memoria reservada pela tabela e os seus elementos */
void destroiTabJogos(TabJogos* tab);

/* Apaga da tabela o Jogo com o nome dado */
void popTabJogos(TabJogos* tab, char* nome);

/* Funcao de comparacao para o qsort */
int comparaJogos(const void* a, const void* b);