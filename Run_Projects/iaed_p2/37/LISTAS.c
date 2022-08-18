#include "LISTAS.h"

/* Recebe pointer para equipa e next e devolve pointer para o novo node. */
tlink NEWTeam(pTeam pEquipa, tlink next) {
    tlink x = malloc(sizeof(struct TeamNODE));
    x -> pEquipa = pEquipa;
    x -> next = next;
    return x;
}

/* Recebe pointer para equipa e para a head e tail da lista e adiciona a equipa ah lista. */
void put_team(pTeam pEquipa, tlink* pLThead, tlink* pLTtail) {
    tlink LTtail = *pLTtail;
    if (*pLThead == NULL)
        *pLThead = *pLTtail = NEWTeam(pEquipa, *pLThead);
	else {
        LTtail -> next = NEWTeam(pEquipa, LTtail -> next);
	    *pLTtail = LTtail -> next;
    }
}

/* Recebe pointer para a head e tail da lista e liberta toda a memoria alocada para a lista. */
void limpaFilaEquipa(tlink* pLThead, tlink* pLTtail) {
    tlink aux, LThead = *pLThead;
    while (LThead) {
        aux = LThead;
	    LThead = LThead -> next;
        free(aux -> pEquipa -> name);
        free(aux -> pEquipa);
        free(aux);
    }
	*pLThead = *pLTtail = NULL;
}

/*================================================================================================*/

/* Recebe pointer para jogo e next e devolve pointer para o novo node. */
glink NEWGame(pGame pJogo, glink next, glink prev) {
    glink x = malloc(sizeof(struct GameNODE));
    x -> pJogo = pJogo;
    x -> next = next;
    x -> prev = prev;
    return x;
}

/* Recebe pointer para jogo e para a head e tail da lista e adiciona jogo ah lista. */
void put_game(pGame pJogo, glink* pLGhead, glink* pLGtail) {
    glink LGtail = *pLGtail;
    if (*pLGhead == NULL)
	    *pLGhead = *pLGtail = NEWGame(pJogo, *pLGhead, NULL);
	else {
	    LGtail -> next = NEWGame(pJogo, LGtail -> next, LGtail);
	    *pLGtail = LGtail -> next;
    }
}

/* Recebe pointer para a head e tail da lista e liberta toda a memoria alocada para a lista. */
void limpaFilaJogo(glink* pLGhead, glink* pLGtail) {
    glink aux, LGhead = *pLGhead;
    while (LGhead) {
	    aux = LGhead;
	    LGhead = LGhead -> next;
		free(aux -> pJogo -> name);
        free(aux -> pJogo);
        free(aux);
    }
	*pLGhead = *pLGtail = NULL;
}
