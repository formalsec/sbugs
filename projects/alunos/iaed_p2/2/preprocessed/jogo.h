#ifndef JOGO_H
#define JOGO_H
#include <string.h>

#define notEqual(A, B) (strcmp(A, B))

typedef char* Itemkey;	/* as keys sao strings */

typedef struct equipa {
	
	char *nome;			/* nome da equipa */
	int	ganhos;			/* nr de jogos ganhos */
} *pEquipa;

typedef struct jogo {
	
	char *nome;			/* nome do jogo */
	pEquipa eq1, eq2;	/* ponteiros para as 2 equipas */
	int sc1, sc2;		/* scores de cada equipa no jogo*/
} *ItemDL;

typedef char* ItemkeyDL;

pEquipa NEWequipa(char* nome);

ItemDL NEWjogo(char *nome, pEquipa eq1, pEquipa eq2, int sc1, int sc2);

ItemkeyDL keyDL(ItemDL v);

void freeItemDL(ItemDL v);

int hashItem(char* s, int M);

char *strdup(const char *src);

void* keyEquipa(void* eq);

void* keyJogo(void* lk);

#endif