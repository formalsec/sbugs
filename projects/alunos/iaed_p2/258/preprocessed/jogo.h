#ifndef JOGO
#define JOGO

#include "equipa.h"
/* Define o numero de espacos no qual os elementos contidos no vetor definido na estrutura jogo se vao dividir */
#define TODOS_JOGOS_ELEMENTOS_NUM 1000
/* JOGOS */
/* Criacao do jogo e especificacao da varias funcionalidades no programa */
/* Criacao da estrutura jogo */
struct Jogo
{
	char* nome;
	int score1;
	int score2;
	struct Equipa *equipa1;
	struct Equipa *equipa2;
	struct Jogo *next;
};

/* Criacao da estrutura que contem todos os jogos */
struct TodosJogos
{
	/* O primeiro jogo (ou vetor com espacos nulos se nao houver nenhum jogo) */
	struct Jogo *elementos[TODOS_JOGOS_ELEMENTOS_NUM];
	int num_jogos;
	/* Vetor ordenado de elementos dos jogos */
	struct Jogo** vetor;
};
/* strings presentes na hashtable do jogo so podem ter ate 1023 caracteres */
int hashjogo(char nome[1024]);
/* Funcao que adiciona um novo jogo ao sistema */
void adicionajogo(struct TodosJogos *jogos, struct TodasEquipas *equipas, int num_comandos);
/* Funcao que lista todos os jogo do sistema pela ordem em que foram introduzidos */
void listajogo(struct TodosJogos *jogos, int num_comandos);
/* Funcao que apaga um novo jogo ao sistema */
void apagajogo(struct TodosJogos *jogos, int num_comandos);
/* Funcao que procura um jogo no sistema atraves do nome */
void procurajogo(struct TodosJogos *jogos, int num_comandos);
/* Funcao que altera o resultado de um jogo */
void alterascore(struct TodosJogos *jogos, int num_comandos);

#endif
