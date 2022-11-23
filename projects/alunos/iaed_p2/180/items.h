#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* estrutura/node equipa */

typedef struct nodeEquipa {
    char *nome;
    unsigned int vitorias;
    struct nodeEquipa *next;
} *linkEquipa;

/* estrutura/node jogo */

typedef struct nodeJogo {
    char *nome;
    char *eq1;
    char *eq2;
    unsigned int s1;
    unsigned int s2;
    int ord;
    struct nodeJogo *next;
} *linkJogo;

/* funcoes de libertacao de memoria */
void liberta_mem_equipa(linkEquipa equipa);
void liberta_mem_jogo(linkJogo jogo);

/* funcoes sobre listas de equipas */
linkEquipa procura_equipa_item (linkEquipa head_equipas, char* nome);
linkEquipa nova_equipa (char *nome);
linkEquipa coloca_equipa (linkEquipa head_equipas, char *nome);

/* funcoes sobre listas de jogos */
linkJogo procura_jogo_item (linkJogo head_jogos, char* nome);
linkJogo novo_jogo (char *nome, char *eq1, char *eq2, int s1, int s2);
linkJogo remove_jogo (linkJogo head_jogos, char *nome);
linkJogo coloca_jogo (linkJogo head_jogos, char *nome,
                      char *eq1, char *eq2, int s1, int s2);