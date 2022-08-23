#include "Jogo.h"

struct lista{
    Jogo jogo;
    struct lista* next;
};
typedef struct lista* Lista;

void Lista_Produtos(Lista lista);
