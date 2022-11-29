#include "jogo.h"
#include "equipa.h"

#ifndef FUNCOES
#define FUNCOES

/* o tamanho da hashtable e o mesmo para jogos e equipas*/
#define TAM_HASH 1013

/* tamanho maximo dos nomes no input */
#define TAM_STR 1024

/* estados da flag usada para atualizar o estado da lista de vencedores do comando g */
#define NADA 0

#define ADD 1	/* uma nova equipa vencedora e adicionada a lista */

#define NOVO 2	/* a lista e apagada e insere-se o novo *unico* vencedor */

#define REFAZER 3	/* so existia 1 equipa na lista e as suas vitorias desceram,
					   tem de se encontrar todos os vencedores de novo, percorrendo a hashtable*/

		/* funcoes associadas a cada comando */

/* funcao atribuida ao comando a, cria um novo jogo e aumenta as vitorias de uma equipa
e insere o jogo criado na hashtable e na lista */
void addJ(hashJ hash, hashE equipas, link_J *jogos, int count, int *wins, int *flag, Equipa *new);

/* comando l: imprime os jogos na ordem inversa da lista
em que se encontram, por motivos de otimizacao */
void print_lista_jogos(link_J head, int contador);

/* comando p: procura um jogo na hashtable, dado um nome */
void procura_jogo(hashJ jogos, int contador);

/* comando r: apaga um jogo da hashtable e da lista */
void apaga_jogo(hashJ jogos, hashE equipas, link_J *lista, link_E *winners, int count, int *flag);

/* comando s: altera o score de um jogo */
void alt_score(hashJ jogos, hashE equipas, link_E *vencedores, 
				Equipa *new, int count, int *flag, int *wins);

/* comando A: adiciona uma equipa a hashtable */
void add_equipa(hashE equipas, Equipa *new_winner, int wins, int *flag, int contador);

/* comando P: procura uma equipa na hashtable */
void procura_equipa(hashE equipas, int contador);

/* comando g: organiza e imprime a lista atualizada de vencedores */
void champions(link_E equipas, int wins, int contador);

		/* funcoes auxiliares / debug */

/* atualiza a lista de vencedores de acordo com a flag definida nesse ciclo */
void atualiza_winner(hashE equipas, link_E *winners, Equipa winner, int flag, int *wins);

/* print na hashtable equipas */
void print_hash_equipas(hashE equipas, int wins);

/* print na hashtable de jogos */
void print_hash_jogos(hashJ jogos);

#endif