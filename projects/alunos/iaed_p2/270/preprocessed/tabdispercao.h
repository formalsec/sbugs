#ifndef TABDISPERCAO_H
#define TABDISPERCAO_H
#include "equipas.h"
#include "jogos.h"

/* estruturas que representam as caracteristicas de duas tabelas de dispercao
 * contendo cada uma delas um ponteiro para ponteiros para equipas ou jogos e
 * tambem dois inteiros corresponentes ao numero de elementos inseridos nas
 * tabelas e o valor maximo de elementos.
*/
struct tab_equipas{
  pEquipa *equipas; /* entradas */
  int N, max;
};

struct tab_jogos{
  pJogo *jogos;   /* entradas */
  int N, max;
};

/* abstracoes para as estruturas das tabelas de dispercao */
typedef struct tab_equipas* pTabEquipas;
typedef struct tab_jogos* pTabJogos;
typedef char* Chave;
#define NULLitem(a) (NULL)
#define iguais(a,b) (strcmp(a,b) == 0) /* def. de igualdade entre chaves (strings) */
#define M(a) (a->max)
#define N(a) (a->N)
#define equipas(a) (a->equipas)
#define jogos(a) (a->jogos)

/* numero maximo de elementos na tabela das equipas e dos jogos respetivamente */
#define MAX_EQ 6603
#define MAX_JG 20603

/* prototipos das funcoes referentes a tabelas de dispercao das equipas*/
int hash(Chave v, int m);
pTabEquipas inicia_te(int);
void insere_eq(pEquipa equipa, pTabEquipas tab_dispercao);
pEquipa procura_eq(Chave v, pTabEquipas tab_dispercao);
void aumenta_te(pTabEquipas tab_dispercao);
void liberta_te(pTabEquipas tab_dispercao);

/* prototipos das funcoes referentes a tabelas de dispercao dos jogos */
pTabJogos inicia_tj(int);
void insere_jg(pJogo jogo, pTabJogos tab_dispercao);
void apaga_jg(Chave v, pTabJogos tab_dispercao);
pJogo procura_jg(Chave v, pTabJogos tab_dispercao);
void aumenta_tj(pTabJogos tab_dispercao);
void liberta_tj(pTabJogos tab_dispercao);

#endif
