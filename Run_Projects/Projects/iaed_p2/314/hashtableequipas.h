#ifndef HASH_TABLEE
#define HASH_TABLEE
#include <stdlib.h>

typedef struct {
	char* nomeeq;
	int jogosg;
}equipa;

typedef struct nodee {
	equipa* equipa;
	struct nodee* next;
} *linke;

linke* STiniciae(int m); /*inicializo a hashtable*/
void STinsertee(equipa* eq, int M, linke* heads); /*coloco uma equipa no inicio de uma lista*/
equipa* STprocurae(char* nomeeq, int M, linke* heads); /*procura uma equipa na lista*/
void STfree_hte(int M, linke* heads);/*liberta tuda a memoria usada na hashtable*/
#endif