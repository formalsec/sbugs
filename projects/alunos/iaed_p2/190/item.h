#ifndef P2_ITEM_H
#define P2_ITEM_H

typedef struct score{
    int score1;
    int score2;
}Score;

struct jogo{
    char* nome;
    char* equipa1;
    char* equipa2;
    Score pontos;
    int keyJogo;
};

typedef struct jogo* Item;

#endif
