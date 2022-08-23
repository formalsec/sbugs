#include "teamlist.h"

/* Cria um novo node de uma lista de equipas. Devolve o ponteiro que aponta
   para o novo node. */
TeamList *newTeamListNode(Team *team, TeamList *next) {
    TeamList *list = (TeamList *) malloc(sizeof(TeamList));

    list->team = team;
    list->next = next;

    return list;
}

/* Liberta a memoria do node de uma lista de equipas fornecido. */
void freeTeamListNode(TeamList *node) {
    free(node);
}

/* Liberta a memoria do node de uma lista de equipas fornecido e dos seus nodes
   seguintes. */
void freeTeamListNodes(TeamList *node) {
    if (node != NULL) {
        freeTeamListNodes(node->next);
        freeTeamListNode(node);
    }
}

/* Cria uma nova lista de equipas vazia. Devolve o ponteiro que aponta para a
   lista. */
TeamList *newTeamList() {
    return NULL;
}

/* Esvazia a lista de equipas fornecida. */
void clearTeamList(TeamList **node) {
    if (*node == NULL)
        return;

    freeTeamListNodes(*node);
    *node = newTeamList();
}

/* Funcao auxilar para adicionar um novo elemento no final de uma lista de
   equipas. */
TeamList *appendTeamListAux(TeamList *node, Team *team) {
    if (node == NULL)
        return newTeamListNode(team, NULL);
    else
        node->next = appendTeamListAux(node->next, team);

    return node;
}

/* Adiciona um novo elemento no final da lista de equipas fornecida. */
void appendTeamList(TeamList **node, Team *team) {
    *node = appendTeamListAux(*node, team);
}

void shiftTeamList(TeamList **node, Team *team) {
    if (*node != NULL) {
        *node = newTeamListNode(team, *node);
    } else {
        *node = newTeamListNode(team, NULL);
    }
}

/* Devolve o numero de elementos que a lista fornecida contem. */
int countTeamList(TeamList *node) {
    if (node == NULL)
        return 0;

    return 1 + countTeamList(node->next);
}

/* Funcao auxiliar para remover um elemento da lista. */
TeamList *removeTeamListAux(TeamList *node, Team *team) {
    TeamList *aux; /* Variavel auxiliar para trocar os links da lista. */

    if (node == NULL)
        return NULL;
    else if (node->team == team) {
        aux = node->next;
        freeTeamListNode(node);
        node = aux;
    } else
        node->next = removeTeamListAux(node->next, team);

    return node;
}

/* Remove a primeira instancia da equipa fornecida da lista de equipas dada. */
void removeTeamList(TeamList **node, Team *team) {
    *node = removeTeamListAux(*node, team);
}

/* Dah print de todos os elementos da lista por ordem. */
void printTeamList(TeamList *node, int nl) {
    if (node != NULL) {
        printTeam(node->team, nl);
        printTeamList(node->next, nl);
    }
}
