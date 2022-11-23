#ifndef JOGO_H
#define JOGO_H

typedef struct {
    char *nome;
    char *equipas[2];
    int scores[2];
} Jogo;

Jogo *criar_jogo();
void free_jogo(Jogo *jogo);

#endif
