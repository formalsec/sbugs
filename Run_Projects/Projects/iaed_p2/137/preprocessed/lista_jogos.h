#include "jogo.h"

typedef struct str_NodeJogo{
	struct str_NodeJogo* seguinte;
	Jogo jogo;
} NodeJogo;

typedef struct str_LstJogos{
	NodeJogo* head;
	int n_jogos;
} LstJogos;

/* Devolve um ponteiro para uma nova lista de jogos */
LstJogos* novaListaJogos();

/* Devolve um ponteiro para um no que contem o Jogo j */
NodeJogo* novoNodeJogo(Jogo j);

/* Adiciona o Jogo dado ao inicio da lista dada */
void pushJogo(Jogo j, LstJogos* lst);

/* Retira o primeiro jogo da lista lst */
void popJogo(LstJogos* lst);

/* Retira o Jogo da lista dada que tem o nome dado */
void removeJogo(LstJogos* lst, char* nome);

/* Devolve um ponteiro para o Jogo com o nome dado na lista dada, caso nao exista devolve NULL */
Jogo* procuraLstJogos(LstJogos* lst, char* nome);

/* Copia os elementos da lista dada para um array, e devolve esse array */
Jogo* copiaLstJogos(LstJogos* lst);

/* Liberta a memoria reservada pela lista toda */
void destroiLstJogos(LstJogos* lst);
