#ifndef _HASH_
#define _HASH_

/* CONSTANTES */

#define MAX_DIM 9973 /* dimensao da tabela de dispersao - primo */

/* ESTRUTURAS */

/* definicao da estrutura no, cujos elementos sao ponteiros */
struct str_node
{
    struct str_node * next, * prev; /* ponteiros para os elementos vizinhos */
    void * elem; /* elemento em si (ponteiro) -> void para reutilizar */
};

typedef struct str_node * node; /* ponteiro para o no */

/* NOTA: a implementacao da tabela de dispersao sera usando filas (FIFO), por
sua vez implementadas com listas. O motivo para tal e poder reutilizar as fun-
coes para o caso de termos apenas uma fila (comandos l e g). */

/* definicao da estrutura fila, cujos elementos sao nos */
struct str_list
{
    node head, tail; /* ponteiros para primeiro e ultimo nos */
};

typedef struct str_list * fila; /* ponteiro para a fila */

/* PROTOTIPOS DAS FUNCOES */

/* funcao de dispersao - a cada string (argumento) associa uma chave */
int hash(char * s); 
/* funcao de inicializacao - inicializa uma fila vazia */
void FILAinit(fila Lst); 
/* funcao de limpeza/libertacao - liberta a memoria associada a uma fila */
void FILAclear(fila Lst); 
/* funcao de adicao - adiciona um elemento ao fim de uma fila */
void FILAadd(fila Lst, void * v); 
/* funcao de procura - procura um elemento numa fila */
void * FILAfind(fila Lst, void * v);
/* funcao de remocao - remove um elemento de uma fila */
void FILAremove(fila Lst, void * v); 

#endif

