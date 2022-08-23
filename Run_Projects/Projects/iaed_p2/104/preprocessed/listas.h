#ifndef LISTAS_H
#define LISTAS_H

/* Definicao das Estruturas */

/* Equipas */

typedef struct no_equipa {
    ptrEquipa equipa;
    struct no_equipa *ant;
    struct no_equipa *prox;
} *linkEquipa; /* linkEquipa e' um ponteiro para um no' de uma lista de equipas */

typedef struct lst_equipas {
    linkEquipa primeiro;
    linkEquipa ultimo;
} *lstEquipas; /* lstEquipas e' um ponteiro para uma lista de equipas */

/* Jogos */

typedef struct no_jogo {
    ptrJogo jogo;
    struct no_jogo *ant;
    struct no_jogo *prox;
} *linkJogo; /* linkJogo e' um ponteiro para um no' de uma lista de jogos */

typedef struct lst_jogos {
    linkJogo primeiro;
    linkJogo ultimo;
} *lstJogos; /* lstJogos e' um ponteiro para uma lista de jogos */

/* Prototipos das Funcoes */

/* Equipas */

/* Cria uma lista duplamente ligada de equipas e devolve um ponteiro para a mesma */
lstEquipas criar_lst_equipas();
/* Adiciona a equipa ao final da lista */
void adicionar_equipa_lst(lstEquipas lista, ptrEquipa equipa);
/* Procura na lista a equipa com o nome dado, devolvendo o no' onde esta se encontra */
linkEquipa procurar_equipa_lst(lstEquipas lista, char *nome);
/* Remove da lista a equipa que se encontra no no' dado */
void remover_equipa_lst(lstEquipas lista, linkEquipa equipa);
/* Recebe uma lista de equipas e devolve o comprimento da mesma */
int comp_lst_equipas(lstEquipas lista);
/* Remove todas as equipas da lista, ficando esta vazia */
void limpar_lst_equipas(lstEquipas lista);
/* Recebe uma lista de equipas e liberta a memoria a ela associada */
void apagar_lst_equipas(lstEquipas lista);
/* Recebe uma lista de equipas e liberta a memoria associada 'a mesma e 'as suas equipas */
void apagar_lst_mais_equipas(lstEquipas lista);

/* Jogos */

/* Cria uma lista duplamente ligada de jogos e devolve um ponteiro para a mesma */
lstJogos criar_lst_jogos();
/* Adiciona o jogo ao final da lista */
void adicionar_jogo_lst(lstJogos lista, ptrJogo jogo);
/* Procura na lista o jogo com o nome dado, devolvendo o no' onde este se encontra */
linkJogo procurar_jogo_lst(lstJogos lista, char *nome);
/* Remove da lista o jogo que se encontra no no' dado */
void remover_jogo_lst(lstJogos lista, linkJogo jogo);
/* Recebe uma lista de jogos e liberta a memoria a ela associada */
void apagar_lst_jogos(lstJogos lista);
/* Recebe uma lista de jogos e liberta a memoria associada 'a mesma e aos seus jogos */
void apagar_lst_mais_jogos(lstJogos lista);

#endif