#ifndef LISTA_JOGOS
#define LISTA_JOGOS

#define STR_MAX 1023
#define TAM_HASH 1091
#define EMPATE 0
#define VITORIA_E1 1
#define VITORIA_E2 2

typedef struct game {
    char *nome;
    char *equipa1;
    char *equipa2;
    int score1;
    int score2;
} jogo;

typedef struct nodejg {
    jogo *jogo;
    struct nodejg *next, *prev;
} *linkjg;

typedef struct listajogos {
    linkjg head, last;
} *lista;

lista cria_lista_jogos();
linkjg add_lista(lista l, jogo *novo_jogo);
void remove_lista (linkjg no, lista l);


#endif