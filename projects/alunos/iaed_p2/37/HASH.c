#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "HASH.h"

/* Hash function, recebe pointer para string e devolve um inteiro que eh o indice. */
int hash(char* v) {
    int h, a = 31415, b = 27183;
    for (h = 0; *v != '\0'; v++, a = a*b % (M-1))
        h = (a*h + *v) % M;
    return h;
}

/* Inicializa a hash table das equipas, devolve pointer para a hash table. */
tlink* initTeams() {
    int i;
    tlink* HashTeams = can_fail_malloc(M*sizeof(tlink));
    for (i = 0; i < M; i++)
        HashTeams[i] = NULL;
    return HashTeams;
}

/* Auxiliar a Tinsert, recebe pointer para equipa e next e devolve pointer para o novo node. */
tlink Tinsert_aux(pTeam pEquipa, tlink next) {
    tlink x = can_fail_malloc(sizeof(struct TeamNODE));
    x -> pEquipa = pEquipa;
    x -> next = next;
    return x;
}

/* Recebe pointer para a head duma fila e um pointer para equipa e adiciona equipa a hash table. */
void Tinsert(tlink* HeadFila, pTeam pEquipa) {
    if (*HeadFila == NULL)
        *HeadFila = Tinsert_aux(pEquipa, NULL);
	else
        *HeadFila = Tinsert_aux(pEquipa, *HeadFila);
}

/*
 * Recebe pointer para string, pointer para a hash table e pointer para um pTeam.
 * Retorna 1 se encontra equipa, retorna 0 se nao encontra equipa.
 * hit passa a ser um pointer para a equipa encontrada.
*/ 
int searchTeamHash(char* buffer, tlink* HashTeams, pTeam* hit) {
    char *compare;
    int indice;
    tlink c;
    indice = hash(buffer);
    for (c = HashTeams[indice]; c != NULL; c = c -> next) {
        compare = c -> pEquipa -> name;
        if (strcmp(compare, buffer) == 0) {
            *hit = c  -> pEquipa;
            return 1;
        }
    }
    return 0;
}

/* Recebe pointer para a hash table e liberta toda a memoria alocada para a hash table. */
void limpaHashTeams(tlink* HashTeams) {
    int i;
    tlink aux;
    for (i = 0; i < M; i++) {
        if (HashTeams[i] != NULL) {
            while (HashTeams[i]) {
                aux = HashTeams[i];
	            HashTeams[i] = HashTeams[i] -> next;
                free(aux);
            }
            free(HashTeams[i]);
        }
    }
    free(HashTeams);
}

/*================================================================================================*/

/* Inicializa a hash table dos jogos, devolve pointer para a hash table. */
glink* initGames() {
    int i;
    glink* HashGames = can_fail_malloc(M*sizeof(glink));
    for (i = 0; i < M; i++)
        HashGames[i] = NULL;
    return HashGames;
}

/* Auxiliar a Ginsert, recebe pointer para jogo e next e devolve pointer para o novo node. */
glink Ginsert_aux(pGame pJogo, glink next) {
    glink x = can_fail_malloc(sizeof(struct GameNODE));
    x -> pJogo = pJogo;
    x -> next = next;
    x -> prev = NULL;
    return x;
}

/* Recebe pointer para a head duma fila e um pointer para jogo e adiciona o jogo a hash table. */
void Ginsert(glink* HeadFila, pGame pJogo) {
    glink aux = *HeadFila;
    if (*HeadFila == NULL)
        *HeadFila = Ginsert_aux(pJogo, NULL);
	else {
        *HeadFila = Ginsert_aux(pJogo, *HeadFila);
        aux -> prev = *HeadFila;
    }
}

/*
 * Recebe pointer para string, pointer para a hash table e pointer para um pGame.
 * Retorna 1 se encontra jogo, retorna 0 se nao encontra jogo.
 * hit passa a ser um pointer para o jogo encontrado.
*/ 
int searchGameHash(char* buffer, glink* HashGames, pGame* hit) {
    char *compare;
    int indice;
    glink c;
    indice = hash(buffer);
    for (c = HashGames[indice]; c != NULL; c = c -> next) {
        compare = c -> pJogo -> name;
        if (strcmp(compare, buffer) == 0) {
            *hit = c  -> pJogo;
            return 1;
        }
    }
    return 0;
}

/* Recebe pointer para a hash table e liberta toda a memoria alocada para a hash table. */
void limpaHashGames(glink* HashGames) {
    int i;
    glink aux;
    for (i = 0; i < M; i++) {
        if (HashGames[i] != NULL) {
            while (HashGames[i]) {
                aux = HashGames[i];
	            HashGames[i] = HashGames[i] -> next;
                free(aux);
            }
            free(HashGames[i]);
        }
    }
    free(HashGames);
}
