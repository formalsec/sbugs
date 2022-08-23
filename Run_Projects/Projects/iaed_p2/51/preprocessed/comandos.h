#ifndef COMANDOS_H
#define COMANDOS_H

/******************************************************************************
 * Bibliotecas:
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipos.h"
#include "estruturas.h"

/******************************************************************************
 * Constantes:
******************************************************************************/

/* O numero maximo de caracteres de um nome (mais caracter '/0'). */
#define MAX_NOME 1024

/******************************************************************************
 * Prototipos:
******************************************************************************/

/* processa_equipas: Funcao que, a seguir a adicionar/remover/alterar a 
pontuacao de um jogo, processa as equipas intervenientes (na arvore binaria).
(i.e. altera as pontuacoes de cada equipa individualmente, e remove-as e 
readiciona-as 'a arvore caso seja necessario).
 bt: parametro que representa o ponteiro do ponteiro para a arvore binaria das 
equipas.
 lp: parametro que representa o ponteiro do ponteiro para a tabela de dispersao 
(por procura linear) das equipas.
 equipa1: parametro que representa o nome da primeira equipa.
 equipa2: parametro que representa o nome da segunda equipa.
 score1: parametro que representa a pontuacao da primeira equipa.
 score2: parametro que representa a pontuacao da segunda equipa.
 operacao: parametro que representa o ponteiro para uma funcao que executa a 
operacao de processamento.  */
void processa_equipas(Bt **bt, Lp **lp, char *equipa1, char *equipa2, int score1,
 int score2, void operacao(Team *));
 
/* adiciona_jogo: Funcao que executa o comando "a". 
 lista: parametro que representa o ponteiro do o ponteiro para lista 
(duplamente ligada) dos jogos.
 lp1: parametro que representa o ponteiro do ponteiro para a tabela de dispersao 
(por procura linear) dos nos da lista dos jogos.
 bt: parametro que representa o ponteiro do ponteiro para a arvore binaria das 
equipas.
 lp2: parametro que representa o ponteiro do ponteiro para a tabela de dispersao 
(por procura linear) das equipas.
 linha: parametro que representa a linha de input que esta a ser lida. */
void adiciona_jogo(List **lista, Lp **lp1, Bt **bt, Lp **lp2, int linha);

/* adiciona_equipa: Funcao que executa o comando "A". 
 bt: parametro que representa o ponteiro do ponteiro para a arvore binaria das 
equipas.
 lp: parametro que representa o ponteiro do ponteiro para a tabela de dispersao 
(por procura linear) das equipas.
 linha: parametro que representa a linha de input que esta a ser lida. */
void adiciona_equipa(Bt **bt, Lp **lp, int linha);

/* lista_jogos: Funcao que executa o comando "l". 
 lista: parametro que representa o ponteiro do o ponteiro para lista (duplamente 
ligada) dos jogos.
 linha: parametro que representa a linha de input que esta a ser lida. */
void lista_jogos(List **lista, int linha);

/* procura_jogo: Funcao que executa o comando "p".
 lp: parametro que representa o ponteiro do ponteiro para a tabela de dispersao 
(por procura linear) dos nos da lista dos jogos.
 linha: parametro que representa a linha de input que esta a ser lida. */
void procura_jogo(Lp **lp , int linha);

/* procura_equipa: Funcao que executa o comando "P".
 lp: parametro que representa o ponteiro do ponteiro para a tabela de dispersao 
(por procura linear) das equipas.
 linha: parametro que representa a linha de input que esta a ser lida. */
void procura_equipa(Lp **lp, int linha);

/* apaga_jogo: Funcao que executa o comando "r". 
 lista: parametro que representa o ponteiro do o ponteiro para lista 
(duplamente ligada) dos jogos.
 lp1: parametro que representa o ponteiro do ponteiro para a tabela de dispersao 
(por procura linear) dos nos da lista dos jogos.
 bt: parametro que representa o ponteiro do ponteiro para a arvore binaria das 
equipas.
 lp2: parametro que representa o ponteiro do ponteiro para a tabela de dispersao 
(por procura linear) das equipas.
 linha: parametro que representa a linha de input que esta a ser lida. */
void apaga_jogo(List **lista, Lp **lp1, Bt **bt, Lp **lp2, int linha);

/* altera_score: Funcao que executa o comando "s".
 lp1: parametro que representa o ponteiro do ponteiro para a tabela de dispersao 
(por procura linear) dos nos da lista dos jogos.
 bt: parametro que representa o ponteiro do ponteiro para a arvore binaria das 
equipas.
 lp2: parametro que representa o ponteiro do ponteiro para a tabela de dispersao 
(por procura linear) das equipas.
 linha: parametro que representa a linha de input que esta a ser lida. */
void altera_score(Lp **lp1, Bt **bt, Lp **lp2, int linha);

/* my_strcmp: Funcao de comparacao usada no qsort.
 a: parametro que representa o primeiro elemento a comparar.
 b: parametro que representa o segundo elemento a comparar. */
int my_strcmp(const void *a, const void *b);

/* encontra_equipas: Funcao que executa o comando "g".
 bt: parametro que representa o ponteiro do ponteiro para a arvore binaria das 
equipas.
 linha: parametro que representa a linha de input que esta a ser lida. */
void encontra_equipas(Bt **bt, int linha);

/* adiciona_jogo: Funcao que liberta todo o espaco associado 'as estruturas. 
 lista: parametro que representa o ponteiro do o ponteiro para lista 
(duplamente ligada) dos jogos.
 lp1: parametro que representa o ponteiro do ponteiro para a tabela de dispersao 
(por procura linear) dos nos da lista dos jogos.
 bt: parametro que representa o ponteiro do ponteiro para a arvore binaria das 
equipas.
 lp2: parametro que representa o ponteiro do ponteiro para a tabela de dispersao 
(por procura linear) das equipas. */
void liberta_estruturas(List *lista, Lp *lp1, Bt *bt, Lp *lp2);

#endif
