#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"


/* tamanho da hashtable */
#define TAMANHO_TAB 10007

/* valores booleanos*/
#define TRUE 1
#define FALSE 0


/* inicia a hashtable, atribuindo a todas as posicoes o valor NULL */
unsigned int hash(char* nome);

/* insere o item na posicao correspondente na hashtable */
void init_hashtable(Item ** hashtable);

void insere_hashtable(Item * item, Item ** hashtable);

/* procura um item na hashtable dado um nome e devolve o item caso este exista */
Item * procura_item(char* nome, Item ** hashtable);

/* recebe um jogo e retorna a equipa com a melhor pontuacao */
Item * equipa_vencedora(Item ** hashtable, Item * jogo);

/* recebe um jogo e aumneta o numero de vitorias da equipa vencedora */
void adiciona_vitoria(Item ** hashtable, Item * jogo);

/* recebe um jogo e diminui o numero de vitorias da equipa vencedora */
void retira_vitoria(Item ** hashtable, Item * jogo);

/* recebe o nome de um jogo e apaga esse jogo do sistema */
int apaga_jogo(char* nome, Item ** hashtable_jogo, Item ** hashtable_equipa, lista_jogo * lst_jogo);