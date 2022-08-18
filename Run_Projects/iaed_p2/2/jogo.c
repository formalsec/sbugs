#include <stdlib.h>

#include "jogo.h"


/* inicializa uma equipa */
pEquipa NEWequipa(char* nome) {

	pEquipa eq = malloc(sizeof(struct equipa));
	eq->nome = strdup(nome);
	eq->ganhos = 0;
	return eq;
}


/* inicializa um jogo */
ItemDL NEWjogo(char *nome, pEquipa eq1, pEquipa eq2, int sc1, int sc2) {
	
	ItemDL p = malloc(sizeof(struct jogo));
	p->nome = strdup(nome);
	p->eq1 = eq1;
	p->eq2 = eq2;
	p->sc1 = sc1;
	p->sc2 = sc2;	
	return p;
}


/* a key de um jogo ? o nome */
ItemkeyDL keyDL(ItemDL v) {

	return v->nome;
}


/* liberta toda a mem de um jogo */
void freeItemDL(ItemDL v) {
	
	free(v->nome);
	free(v);
}


/* hash function for a string */
int hashItem(char* s, int M)
{
	int h = 0, a = 127;
	for (; *s != '\0'; s++)
		h = (a*h + *s) % M;
	return h;
}


/* string duplicate from stackoverflow */
char *strdup(const char *src) {
    char *dst = malloc(strlen (src) + 1);
    if (dst == NULL) return NULL;
    strcpy(dst, src);
    return dst;
}


/* identifies the key given the equipa pointer */
void* keyEquipa(void* eq) {		/* eq is in fact a pEquipa */
	
	return ((pEquipa) eq)->nome;
}


/* identifies the key given the jogo node pointer */
void* keyJogo(void* lk) {		/* lk is in fact a link to jogo node */
	
	return (void*) (*(ItemDL*)lk)->nome;
}

