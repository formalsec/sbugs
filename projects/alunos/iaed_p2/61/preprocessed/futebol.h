#ifndef _FUTEBOL_
#define _FUTEBOL_
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "arvore.h"
/*-----------funcoes para comandos e def de estruturas--------------*/
/*                                                                  */
/* Definicao de estruturas                                          */
/* Funcoes para executar os comandos                                */
/*------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
/* estrutura equipa, com nome de equipa e numero de vitorias da mesma*/
/*-------------------------------------------------------------------*/
typedef struct _equipa equipa;

/*-------------------------------------------------------------------*/
/* pointer para equipa                                               */
/*-------------------------------------------------------------------*/
typedef equipa* ptr_equipa;

/*-------------------------------------------------------------------*/
/* estrutura jogo, com nome do jogo, dois pointers para as equipas   */
/* e o scores da equipa 1 e da equipa 2                              */
/*-------------------------------------------------------------------*/
typedef struct _jogo jogo;

/*-------------------------------------------------------------------*/
/* pointer para jogo                                                 */
/*-------------------------------------------------------------------*/
typedef jogo* ptr_jogo;

/*-------------------------------------------------------------------*/
/* procura jogo chamado nome na hashtable                            */
/*                                                                   */
/* -retorna pointer para jogo                                        */
/*-------------------------------------------------------------------*/
ptr_jogo procurajogo(hashtable* jogos, char* nome);

/*-------------------------------------------------------------------*/
/* procura equipa chamada nome na hashtable                          */
/*                                                                   */
/* -retorna pointer para equipa                                      */
/*-------------------------------------------------------------------*/
ptr_equipa procuraequipa(hashtable* hequipas, char* nome);

/*-------------------------------------------------------------------*/
/* adiciona jogo                                                     */
/*                                                                   */
/* - cria um jogo e adiciona esse jogo a hashtable e a lista         */
/* - procura-se na hashtable de equipas os pointers para as equipas  */ 
/* do jogo                                                           */
/*-------------------------------------------------------------------*/
void adiciona_jogo(char *nome,char *eq1,char *eq2, int sc1, int sc2, hashtable* hequipas, hashtable* hjogos, list* ljogos,int NL);

/*-------------------------------------------------------------------*/
/* lista jogo                                                        */
/*                                                                   */
/* - retorna todos os jogos por ordem insercao                       */
/* - caso nao existam jogos retorna mensagem erro                    */
/*-------------------------------------------------------------------*/
void lista_jogos(list* ljogos,int NL);

/*-------------------------------------------------------------------*/
/* procura jogo chamado nome na hastable de jogo                     */
/*                                                                   */
/* -imprime jogo                                                     */
/* -caso nao exista o jogo, imprime erro                             */
/*-------------------------------------------------------------------*/
void procura_jogo(hashtable* hjogos, char* nome, int NL);

/*-------------------------------------------------------------------*/
/* apaga jogo chamado nome da hastable e da lista de jogos           */
/*                                                                   */
/* -caso nao exista o jogo, imprime erro                             */      
/*-------------------------------------------------------------------*/
void apaga_jogo(hashtable* hjogos, list* ljogos, char* nome, int NL);

/*-------------------------------------------------------------------*/
/* altera score jogo chamado nome                                    */
/*                                                                   */
/* -caso exista jogo, muda score do jogo e atualiza vitorias das     */
/* equipas                                                           */  
/* -caso nao exista o jogo, imprime erro                             */      
/*-------------------------------------------------------------------*/
void altera_score(hashtable* hjogos, char* nome, int newsc1, int newsc2, int NL);

/*-------------------------------------------------------------------*/
/* adiciona equipa                                                   */
/*                                                                   */
/* - cria uma equipa e adiciona a hashtable                          */
/*-------------------------------------------------------------------*/
void adiciona_equipa(char *nome, hashtable* hequipas, int NL);

/*-------------------------------------------------------------------*/
/* procura equipa chamado nome na hastable de equipa                 */
/*                                                                   */
/* -imprime equipa                                                   */
/* -caso a equipa ja exista, imprime erro                            */
/*-------------------------------------------------------------------*/
void procura_equipa(hashtable* hequipas, char* nome, int NL);

/*-------------------------------------------------------------------*/
/* free do jogo                                                      */
/*-------------------------------------------------------------------*/   
void freejogo(Item _item);

/*-------------------------------------------------------------------*/
/* free da equipa                                                    */
/*-------------------------------------------------------------------*/
void freeequipa(Item _item);

/*-------------------------------------------------------------------*/
/* percorre hashtable de equipas a procura das equipas com o max de  */
/* vitorias. ordena essas equipas e imprime.                         */   
/* -caso hajam equipa, imprime por ordem alfabetica as equipas       */
/* -caso nao hajam equipas, nao faz nada                             */
/*-------------------------------------------------------------------*/
void mais_vitorias(hashtable* hequipas, int M, int NL);

/*-------------------------------------------------------------------*/
/* imprime os items de nt (arvore) do menor para o maior             */
/*-------------------------------------------------------------------*/
void imprime_eq_vitorias(nodetree* nt, int NL);

#endif
