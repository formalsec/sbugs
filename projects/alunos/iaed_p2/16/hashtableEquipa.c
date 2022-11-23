#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "codigoAux.h"
#include "hashtableEquipa.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Aloca memoria para uma hash table de equipas e inicializa-a */
listaEquipa** criaHashTableEquipa(int M_E) {
    int i;
    listaEquipa** headsEquipas;
    headsEquipas = (listaEquipa**)can_fail_malloc(M_E*sizeof(listaEquipa*));

    for (i = 0; i < M_E; i++) {
        headsEquipas[i] = NULL;
    }

    return headsEquipas;
}

/* Liberta a memoria associada ah hash table de equipas sem libertar as equipas */
void freeHashTableEquipa(listaEquipa** headsEquipas, int M_E) {
    int i = 0;
    
    for (i = 0; i < M_E; i++) {
        freeListaEquipa(headsEquipas[i]);
    }
    free(headsEquipas);
}

/* Insere uma equipa na hast table de equipas na posicao dada pela funcao hash */
listaEquipa** insereHashTableEquipa(listaEquipa** headsEquipas, equipa* Equipa, int M_E) {
    int i = hash(Equipa->nome, M_E);

    headsEquipas[i] = insereInicioListaEquipa(headsEquipas[i], Equipa);
    return headsEquipas;
}

/* Remove uma equipa da hast table de equipas da posicao dada pela funcao hash */
listaEquipa** removeHashTableEquipa(char* nome, listaEquipa** headsEquipas, int M_E) {
    int i = hash(nome, M_E);
    
    headsEquipas[i] = removeListaEquipa(headsEquipas[i], nome);
    return headsEquipas;
}

/* Procura e retorna uma equipa da hash table de equipas */
equipa* procuraHashTableEquipa(listaEquipa** headsEquipas, char* nome, int M_E) {
    int i = hash(nome, M_E);

    /* Se a hash table nao tiver sido inicializada retorno NULL */
    if (headsEquipas == NULL) {
        return NULL;
    }
    /* Se a entrada da hash table nao tiver sido inicializada */
    if (headsEquipas[i] == NULL) {
        return NULL;
    }
    
    /* Se a lista na posicao dada por hash nao for vazia procura a equipa nessa lista */
    return procuraListaEquipa(headsEquipas[i], nome);
}

/* Testa a existencia de uma equipa no sistema (na hash table de equipas) */
int equipaExiste(listaEquipa** headsEquipas, char* nome, int M_E) {
    equipa* auxEquipa;

    auxEquipa = procuraHashTableEquipa(headsEquipas, nome, M_E);

    if (auxEquipa == NULL) {
        return 0;
    }
    
    return 1;
}

