#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H


typedef struct _Jogo{
    struct _Jogo *drt, *esq;
    char *nome, *equipaX, *equipaY;
    int scoreX, scoreY;
} Jogo;


typedef struct _Equipa{
    struct _Equipa *drt, *esq;
    char *nome;
    int jogos_ganhos;
} Equipa;


typedef struct _Node {
    struct _Node *drt, *esq;
    void *tipo_node;
} Node;


typedef struct {
    void *cabeca, *ultimo;
} Lista;


#endif