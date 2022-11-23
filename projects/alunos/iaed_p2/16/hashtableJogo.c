#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "codigoAux.h"
#include "hashtableJogo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Aloca memoria para uma hash table de jogos e inicializa-a */
listaJogo** criaHashTableJogo(int M_J) {
    int i;
    listaJogo** headsJogos;
    headsJogos = (listaJogo**)can_fail_malloc(M_J*sizeof(listaJogo*));

    for (i = 0; i < M_J; i++) {
        headsJogos[i] = NULL;
    }

    return headsJogos;
}

/* Liberta a memoria associada ah hash table de jogos sem libertar os jogos */
void freeHashTableJogo(listaJogo** headsJogos, int M_J) {
    int i = 0;
    
    for (i = 0; i < M_J; i++) {
        freeListaJogo(headsJogos[i]);
    }
    free(headsJogos);
}

/* Insere um jogo na hast table de jogos na posicao dada pela funcao hash */
listaJogo** insereHashTableJogo(listaJogo** headsJogos, jogo* Jogo, int M_J) {
    int i = hash(Jogo->nome, M_J);

    headsJogos[i] = insereInicioListaJogo(headsJogos[i], Jogo);
    return headsJogos;
}

/* Remove um jogo da hash table de jogos da posicao dada pela funcao hash */
listaJogo** removeHashTableJogo(listaJogo** headsJogos, char* nome, int M_J) {
    int i = hash(nome, M_J);

    headsJogos[i] = removeListaJogo(headsJogos[i], nome);
    return headsJogos;
}

/* Procura e retorna um jogo da hash table de jogos */
jogo* procuraHashTableJogo(listaJogo** headsJogos, char* nome, int M) {
    int i = hash(nome, M);

    /* Se a hash table nao tiver sido inicializada */
    if (headsJogos == NULL) {
        return NULL;
    }
    /* Se entrada da hash table nao tiver sido inicializada */
    if (headsJogos[i] == NULL) {
        return NULL;
    }

    /* Se a lista na posicao dada por hash nao for vazia procura o jogo nessa lista */
    return procuraListaJogo(headsJogos[i], nome);
}

/* Testa a existencia de um jogo no sistema (na hash table de jogos) */
int jogoExiste(listaJogo** headsJogos, char* nome, int M_J) {
    jogo* auxJogo;

    auxJogo = procuraHashTableJogo(headsJogos, nome, M_J);

    if (auxJogo == NULL) {
        return 0;
    }
    
    return 1;
}
