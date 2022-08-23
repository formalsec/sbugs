#include "jogo.h"
#include "equipa.h"

#define M 2003		/*tamanho da hashtable*/

typedef struct node_jogo{
	jogo *j;
	struct node_jogo *next;
}*link_jogo;

typedef struct node_equipa{
	equipa *e;
	struct node_equipa *next;
}*link_equipa;

/**
  * Calcula o indice de um nome para a hashtable
  * @param  char *nome - nome cujo indice queremos encontrar
  * @return int h - indice referente ao nome dado
  */
int hash(char *nome);

/**
 * Inicializa a hashtable dos jogos
 */
void Initjogo();

/**
 * Procura um jogo na hashtable com o nome dado como argumento
 * @param  int hashID - indice do jogo na hashtable
 * @param  char *nome - nome do jogo que procuramos
 * @return jogo *auxjogo - jogo com o nome dado ou NULL se nao existir
 */
jogo *searchListJogo(int hashID, char *nome);

/**
 * Procura um jogo na hashtable dado um nome
 * @param  char *nome - nome do jogo que procuramos
 * @return equipa *auxjogo - jogo com o nome dado ou NULL se nao existir
 */
jogo *STsearchJogo(char *nome);

/**
 * Adiciona um jogo dado como argumento a hashtable
 * @param int hashID - indice do jogo na hashtable
 * @param jogo *jg - jogo que queremos adicionar
 * @return 0 se for adicionado, -1 caso contrario
 */
int insertBeginListJogo(int hashID, jogo *jg);

/**
 * Adiciona um jogo dado como argumento na hashtable
 * @param jogo *jg - jogo que queremos adicionar
 */
void STinsertJogo(jogo *jg);

/**
 * Apaga um jogo da hashtable dado um nome
 * @param int hashID - indice do jogo na hashtable
 * @param char *nome - nome do jogo que queremos apagar
 */
int removeItemJogo(int hashID, char *nome);

/**
 * Apaga um jogo da hashtable dado um nome
 * @param char *nome
 */
void STdelete(char *nome);

/**
 * Apaga toda a informacao da hashtable
 */
void ApagaHashJogo();

/**
 * Inicializa a hashtable das equipas
 */
void Initequipa();

/**
 * Procura uma equipa na hashtable com o nome dado como argumento
 * @param  int hashID - indice da equipa na hashtable
 * @param  char *nome - nome da equipa que procuramos
 * @return equipa *auxequipa - equipa com o nome dado ou NULL se nao existir
 */
equipa  *searchListEquipa(int hashID, char *nome);

/**
 * Procura uma equipa na hashtable dado um nome
 * @param  char *nome - nome da equipa que procuramos
 * @return equipa *auxequipa - equipa com o nome dado ou NULL se nao existir
 */
equipa *STsearchEquipa(char *nome);

/**
 * Adiciona uma equipa dado como argumento a hashtable
 * @param int hashID - indice da equipa na hashtable
 * @param equipa *eq - equipa que queremos adicionar
 * @return 0 se for adicionado, -1 caso contrario
 */
int insertBeginListEquipa(int hashID, equipa *eq);

/**
 * Adiciona uma equipa dada como argumento na hashtable
 * @param equipa *eq - equipa que queremos adicionar
 */
void STinsertEquipa(equipa *eq);

/**
 * Apaga toda a informacao da hashtable
 */
void ApagaHashEquipa();
