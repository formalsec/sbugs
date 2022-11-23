#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "AUXILIARES.h"

/*
 * Recebe dois pointers para strings, pointer para hash table de equipas e 2 pointers para equipas.
 * Retorna 0 se ambas as equipas existem, retorna 1 se uma das equipas ou ambas nao existem.
 * pTeam1 passa a apontar para a equipa com o nome name1.
 * pTeam2 passa a apontar para a equipa com o nome name2.
*/
int adicionaJogo_aux(char* name1, char* name2, tlink* HashTeams, pTeam* pTeam1, pTeam* pTeam2) {
    int aux1 = searchTeamHash(name1, HashTeams, pTeam1);
    int aux2 = searchTeamHash(name2, HashTeams, pTeam2);
    if (aux1 == 1 && aux2 == 1)
        return 0;
    return 1;
}

/*================================================================================================*/

/* 
 * Recebe 2 inteiros com o score1/2 e 2 pointers para equipas.
 * Atribui vitoria ah equipa vencedora.
*/
void atualizaVitorias_adicJogo(int score1, int score2, pTeam pEquipa1, pTeam pEquipa2) {
    if (score1 > score2)
        pEquipa1 -> vitorias++;
    else if (score2 > score1)
        pEquipa2 -> vitorias++;
}

/* 
 * Recebe 2 inteiros com o score1/2 e 2 pointers para equipas.
 * Subtrai vitoria da equipa vencedora.
*/
void atualizaVitorias_apagaJogo(int score1, int score2, pTeam pEquipa1, pTeam pEquipa2) {
    if (score1 > score2)
            pEquipa1 -> vitorias--;
    else if (score2 > score1)
        pEquipa2 -> vitorias--;
}

/*
 * Recebe 4 inteiros com o score1/2 e newscore1/2 e 2 pointers para equipas.
 * Altera o numero de vitorias das equipas conforme necessario.
*/
void alteraScore_aux(int score1, int score2, int newscore1, int newscore2, pTeam pE1, pTeam pE2) {
    if (score1 > score2) {
        if (newscore2 > newscore1) {
            pE1 -> vitorias--;
            pE2 -> vitorias++;
        }
        else if (newscore2 == newscore1)
            pE1 -> vitorias--;
        }
    else if (score1 < score2) {
        if (newscore1 > newscore2) {
            pE1 -> vitorias++;
            pE2 -> vitorias--;
        }
        else if (newscore2 == newscore1)
            pE2 -> vitorias--;
        }
    else if (score1 == score2) {
        if (newscore1 > newscore2)
            pE1 -> vitorias++;
        else if (newscore2 > newscore1)
            pE2 -> vitorias++;
    }
}

/*
 * Recebe  pointer para um jogo, inteiro que determina o caso e dois inteiros com newscore1/2.
 * caso = 0 quando adiciona um jogo.
 * caso = 1 quando apaga um jogo.
 * caso = 2 quando altera score.
 * Chama as respetivas funcoes para cada caso.
*/
void atualizaVitorias(pGame pJogo, int caso, int newscore1, int newscore2) {
    int score1 = pJogo -> score1, score2 = pJogo -> score2;
    pTeam pEquipa1 = pJogo -> pEquipa1, pEquipa2 = pJogo -> pEquipa2;
    if (caso == 0)
        atualizaVitorias_adicJogo(score1, score2, pEquipa1, pEquipa2);
    else if (caso == 1)
        atualizaVitorias_apagaJogo(score1, score2, pEquipa1, pEquipa2);
    else if (caso == 2)
        alteraScore_aux(score1, score2, newscore1, newscore2, pEquipa1, pEquipa2);
}

/*================================================================================================*/

/*
 * Recebe  pointer para string, pointer para hash table de jogos e pointer para jogo.
 * Apaga node do jogo a apagar da hash table e faz free da memoria alocada para o node.
*/
void apagaJogoHash(char* buffer, glink* HashGames, pGame hit) {
    glink c, prev;
    int indice = hash(buffer);
    for (c = HashGames[indice], prev = NULL; c != NULL; prev = c, c = c -> next) {
        if (c -> pJogo == hit) {
            if (c == HashGames[indice])
                HashGames[indice] = c -> next;
            else
                prev -> next = c -> next;
            free(c);
            break;
        }
    }
}

/*
 * Recebe  pointer para head e tail da lista de jogos e pointer para jogo.
 * Apaga node do jogo a apagar da lista e faz free da memoria alocada para o node.
*/
void apagaJogoLista(glink* pLGhead, glink* pLGtail, pGame hit) {
    glink c, prev;
    for (c = *pLGhead, prev = NULL; c != NULL; prev = c, c = c -> next) {
        if (c -> pJogo == hit) {
            if (c == *pLGhead)
                *pLGhead = c -> next;
            else if (c == *pLGtail) {
                *pLGtail = c -> prev;
                prev -> next = NULL;
            }
            else
                prev -> next = c -> next;
            free(c -> pJogo -> name);
            free(c -> pJogo);
            free(c);
            break;
        }
    }
}

/*================================================================================================*/

/* Funcao de comparacao usada no qsort, ordena array por ordem lexicografica. */
int cstring_cmp(const void *a, const void *b) {
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
}
