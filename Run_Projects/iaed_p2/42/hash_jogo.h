#ifndef HASH_JOGO_H
#define HASH_JOGO_H

#include "jogo.h"

/* 
estrutura nodeJ 
no de uma lista ligada caracterizado por
- ponteiro para um jogo (jogo)
- ponteiro para o no seguinte (next)
- ponteiro para no anterior (prev)
 */
typedef struct nodeJ{
    pJogo jogo;
    struct nodeJ *next;
    struct nodeJ *prev;
}*linkJ; /* linkJ eh um ponteiro para um nodeJ */


/* inicializa uma hashtable de jogos */
linkJ* InitJogo(int M);
/* insere um jogo no inicio de uma lista */
linkJ InsertJogo(pJogo j,linkJ head);
/* apaga um jogo */
linkJ DeleteJogo(linkJ j,linkJ head); 
/* procura um jogo */
linkJ SearchJogo(char *nome,linkJ head);
/* liberta uma hashtable de jogos*/
void FreeHashJogo(int M,linkJ * heads);


#endif