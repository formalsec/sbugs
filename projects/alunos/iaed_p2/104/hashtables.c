#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include "equipa.h"
#include "jogo.h"
#include "listas.h"
#include "hashtables.h"

/* Dimensao das hashtables */
#define M 1069

/* Numero primo utilizado para a funcao de dispersao */
#define P 127

/* Funcao de dispersao */
int hash(char *nome) {
    int h = 0;

    for (; *nome != '\0'; nome++)
        h = (P * h + *nome) % M;
    return h;
}

/* Equipas */

/* Cria uma hashtable de equipas */
hashEquipas criar_hash_equipas() {
    int i;
    hashEquipas hash_equipas;

    /* Reserva memoria para a hashtable, um vetor de ponteiros para listas de equipas */
    hash_equipas = (hashEquipas) can_fail_malloc(M * sizeof(lstEquipas));

    /* Inicializa cada lista da hashtable */
    for (i = 0; i < M; i++)
        hash_equipas[i] = criar_lst_equipas();

    return hash_equipas;
}

/* Adiciona a equipa 'a hashtable */
void adicionar_equipa_hash(hashEquipas hash_equipas, ptrEquipa equipa) {
    int i = hash(equipa->nome);
    adicionar_equipa_lst(hash_equipas[i], equipa);
}

/* Procura na hashtable a equipa com o nome dado */
linkEquipa procurar_equipa_hash(hashEquipas hash_equipas, char *nome) {
    int i = hash(nome);
    return procurar_equipa_lst(hash_equipas[i], nome);
}

/* Recebe uma hashtable de equipas e liberta a memoria a ela associada */
void apagar_hash_equipas(hashEquipas hash_equipas) {
    int i;

    /* Percorre cada lista da hashtable e liberta a memoria a ela associada */
    for (i = 0; i < M; i++)
        apagar_lst_equipas(hash_equipas[i]);

    /* Lberta a restante memoria associada 'a hashtable */
    free(hash_equipas);
}

/* Jogos */

/* Cria uma hashtable de jogos */
hashJogos criar_hash_jogos() {
    int i;
    hashJogos hash_jogos;

    /* Reserva memoria para a hashtable, um vetor de ponteiros para listas de jogos */
    hash_jogos = (hashJogos) can_fail_malloc(M * sizeof(lstJogos));

    /* Inicializa cada lista da hashtable */
    for (i = 0; i < M; i++)
        hash_jogos[i] = criar_lst_jogos();

    return hash_jogos;
}

/* Adiciona o jogo 'a hashtable */
void adicionar_jogo_hash(hashJogos hash_jogos, ptrJogo jogo) {
    int i = hash(jogo->nome);
    adicionar_jogo_lst(hash_jogos[i], jogo);
}

/* Procura na hashtable o jogo com o nome dado */
linkJogo procurar_jogo_hash(hashJogos hash_jogos, char *nome) {
    int i = hash(nome);
    return procurar_jogo_lst(hash_jogos[i], nome);
}

/* Remove da hashtable o jogo que se encontra no no' dado */
void remover_jogo_hash(hashJogos hash_jogos, linkJogo jogo) {
    int i = hash(jogo->jogo->nome);
    remover_jogo_lst(hash_jogos[i], jogo);
}

/* Recebe uma hashtable de jogos e liberta a memoria a ela associada */
void apagar_hash_jogos(hashJogos hash_jogos) {
    int i;

    /* Percorre cada lista da hashtable e liberta a memoria a ela associada */
    for (i = 0; i < M; i++)
        apagar_lst_jogos(hash_jogos[i]);

    /* Lberta a restante memoria associada 'a hashtable */
    free(hash_jogos);
}