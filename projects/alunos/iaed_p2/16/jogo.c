#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "codigoAux.h"
#include "jogo.h"
#include "hashtableJogo.h"
#include "hashtableEquipa.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Aloca memoria para um jogo e inicializa-o */
jogo* criaJogo(char* nome, char* equipa1, char* equipa2, int score1, int score2, listaEquipa** headsEquipas, int M_E) {
    jogo*   novoJogo;
    equipa* equipaVencedora;
    novoJogo = (jogo*)can_fail_malloc(sizeof(jogo));

    /* Aloca memoria para as strings e copia-as */
    novoJogo->nome = duplicaString(nome);
    novoJogo->equipa1 = duplicaString(equipa1);
    novoJogo->equipa2 = duplicaString(equipa2);
    novoJogo->score1 = score1;
    novoJogo->score2 = score2;

    /* Se os scores forem iguais retorna o jogo */
    if (novoJogo->score1 == novoJogo->score2) {
        return novoJogo;
    }
    /* Se score1 > score2 a vitoria vai para a equipa1 */
    else if (novoJogo->score1 > novoJogo->score2) {
        equipaVencedora = procuraHashTableEquipa(headsEquipas, equipa1, M_E);
        equipaVencedora->numeroVitorias += 1;
    }
    /* Se score1 < score2 a vitoria vai para a equipa2 */
    else {
        equipaVencedora = procuraHashTableEquipa(headsEquipas, equipa2, M_E);
        equipaVencedora->numeroVitorias += 1;
    }
    /* Se for empate nenhuma equipa acrescenta uma vitoria */

    return novoJogo;
}

/* Liberta um jogo e toda a memoria associada */
void freeJogo(jogo* Jogo) {
    free(Jogo->nome);
    free(Jogo->equipa1);
    free(Jogo->equipa2);
    free(Jogo);
}

/* Imprime os parametros de um jogo */
void printJogo(jogo* Jogo, int* pNL) {
    printf("%d %s %s %s %d %d\n", *pNL, 
                                  Jogo->nome, 
                                  Jogo->equipa1, 
                                  Jogo->equipa2, 
                                  Jogo->score1, 
                                  Jogo->score2);
}
