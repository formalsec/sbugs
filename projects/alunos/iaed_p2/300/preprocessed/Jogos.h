#ifndef Jogos
#define Jogos

typedef struct Jogo /* Estrutura dos jogos*/
{
    char *nome;
    char *equipa1;
    char *equipa2;
    int score1, score2;
} * pJogo;

#include "ListaLigada.h"

int hashJ(char *nome, int m);                         /* Funcao que identifica em que index da hastable e que o jogo esta */
node *insertBeginListJ(node *head, node *node_jogo);  /* Funcao auxiliar de STinsertJ*/
node *removeJogoListJ(node *head, char *nome);        /* Funcao auxiliar de STdeleteJ */
node *searchListJ(node *head, char *nome);            /* Funcao auxiliar de STsearchJ */
node **STinitJ(int m);                                /* Funcao que inicializa a hashtable dos jogos*/
void STinsertJ(node **heads, node *node_jogo, int m); /* Funcao que insere um node ao inicio da lista de um determinado index da hashtable*/
void STdeleteJ(node **heads, char *nome, int m);      /* Funcao que remove um node duma lista de um determinado index da hashtable */
node *STsearchJ(node **heads, char *nome, int m);     /* Funcao que procura se um node faz parte da hashtable */
void printJogo(node *a, int nl);                      /* Funcao que da print a um jogo */
#endif