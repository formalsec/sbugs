#ifndef JOGO
#define JOGO


#include "equipa.h"

/* Definicao das variaveis para o numero de gavetas na hash table dos jogos,
e o numero de maximo de caracteres*/
#define JOGO_GAVETAS 1024
#define MAX_JOGO_NOME 1024

/* Deifinimos a estrutura de um jogo */
struct Jogo {
    /* Ponteiro para o nome */
    char* nome;
    
    /* Definicao das estrutras das duas equipas */
    struct Equipa* equipa1;
    struct Equipa* equipa2;
    
    /* Golos de cada equipa */
    int golos1;
    int golos2;
    
    /* Proximo jogo na gaveta do jogo */
    struct Jogo *next_jogo;
};

/* Estrutura para definir os jogos todos */
struct Jogos {
    /* Definicao das gavetas da hash table */
    struct Jogo *gavetas[JOGO_GAVETAS];
    /* Numero total de jogos */
    int njogos;
    
    /* Vetor de ponteiros onde colocamos os jogos por ordme de entrada */
    struct Jogo **ordem;
};

/* Funcoes que pretendemos utilizar */
void adiciona_jogo(struct Jogos*jogos, struct Equipas*equipas, int comandos_total);
void procura_jogo(struct Jogos*jogos, int comandos_total);
void lista_jogos(struct Jogos*jogos, int comandos_total);
void apaga_jogos(struct Jogos*jogos, int comandos_total);
void muda_jogos(struct Jogos*jogos, int comandos_total);

#endif
