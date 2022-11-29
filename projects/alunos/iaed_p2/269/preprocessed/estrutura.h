#ifndef Projeto_h
#define Projeto_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1023
#define MAX_TAMANHO_TABELA 10

typedef struct jogo
{
	char *nome;
	char *equipa1;
	char *equipa2;
	int score1;
	int score2;
	int num_jogos;
	struct jogo *next;
}*jogos;

typedef struct equipa
{
	char *nome_equipa;
	int vitorias;
	struct equipa *next; 
}*equipas;

/* FUNCOES AUXILIARES*/
jogos *criar_hashtablejogos();
equipas *criar_hashtableequipas();
int hash(char *v);
jogos NEWJOGO(char* nome, char* equipa1, char* equipa2, int score1, int score2, int num_jogos);
equipas NEWEQUIPA(char* nome_equipa);
void freehashtable_jogos(jogos *hashtable_jogos);
void freehashtable_equipas(equipas *hashtable_equipas);
jogos insertBeginjogos(jogos head_jogo, char* nome, char *equipa1, char *equipa2, int score1, 
int score2, int num_jogos);
equipas insertBeginequipas(equipas head, char* nome_equipa);
jogos lookupjogo(jogos *hashtable_jogos, char *nome);
equipas lookupequipa(equipas *hashtable_equipas, char *nome_equipa);


/***********************FUNCOES PRINCIPAIS*****************************************************
|| Comando | Accao |
|:---:|:---|
| __a__ | Adiciona um novo jogo. |
| __A__ | Adiciona uma nova equipa. |
| __l__ | Lista todos os jogos pela ordem em que foram introduzidos. |
| __p__ | Procura um jogo. |
| __P__ | Procura uma equipa. |
| __r__ | Apaga um jogo. |
| __s__ | Altera a pontuacao (_score_) de um jogo. |
| __g__ | Encontra as equipas que venceram mais jogos.
| __x__ | Termina o programa. | 
***********************************************************************************************/



void adicionaequipa(equipas *hashtable_equipas, char *nome_equipa, int NL);
int adicionajogo(jogos *hashtable_jogos, equipas *hashtable_equipas, 
char *nome, char *equipa1, char *equipa2, int score1, int score2, int num_jogos, int NL);
void listaordemjogos(jogos *hashtable_jogos, int num_jogos, int NL);
void procurajogo(jogos *hashtable_jogos, char* nome, int NL);
jogos apagajogo(jogos *hashtable_jogos, equipas *hashtable_equipas, char *nome, int NL);
void procuraequipa(equipas *hashtable_equipas, char *nome_equipa, int NL);
void alterascore(jogos *hashtable_jogos, equipas *hashtable_equipas, char *nome, int score1, 
int score2, int NL); 


#endif



