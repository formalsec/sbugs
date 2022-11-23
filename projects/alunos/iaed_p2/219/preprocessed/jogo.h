#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXINPUT 3071	/*maximo de caracteres do input*/

typedef struct jogo{
	char *nome;
	char *equipa1;
	char *equipa2;
	char *score1;
	char *score2;
	struct jogo *jogo_seguinte, *jogo_anterior;
}jogo;

typedef struct {
	struct jogo *head, *last;
	int num_jogos;	/*contador de jogos*/
}lista_jogos;

/**
 * Cria um jogo vazio
 * @return jogo *novo_jogo
 */
jogo* cria_jogo();

/**
 * Cria uma lista de jogos vazia
 * @return lista_jogos *nova_lista
 */
lista_jogos* cria_lista_jogos();

/**
 * Apaga o jogo dado como argumento
 * @param jogo *jg - jogo que queremos apagar
 */
void free_jogo(jogo *jg);

/**
 * Preenche o jogo com os argumentos dados como input
 * @param jogo *jg - jogo a preencher    
 * @param char *nome - nome do jogo 
 * @param char *equipa1 - nome da 1 equipa do jogo
 * @param char *equipa2 - nome da 2 equipa do jogo
 * @param char *score1 - pontuacao da 1 equipa
 * @param char *score2 - pontuacao da 2 equipa
 */
void preenche_jogo(jogo *jg, char *nome, char *equipa1, char *equipa2, char *score1, char *score2);

/**
 * Adiciona o jogo dado como argumento a lista de jogos
 * @param jogo *jg - jogo a adicionar a lista 
 * @param lista_jogos *l_jogos - lista a qual se vai adicionar o jogo
 */
void adiciona_jogo(jogo *jg, lista_jogos *l_jogos);

/**
 * Elimina a lista de jogos dada como argumento
 * @param lista_jogos *l_jogos - lista de jogos
 */
void free_jogos(lista_jogos *l_jogos);

/**
 * Apaga o jogo dado como argumento da lista de jogos
 * @param lista_jogos *l_jogos - lista de jogos
 * @param jogo *jg - jogo que se quer eliminar
 */
void retira_jogo(lista_jogos *l_jogos, jogo *jg);
