#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "btteam.h"

/* Cria um novo node de uma arvore binaria de equipas. Devolve o ponteiro que
   aponta para o novo node. */
BTTeam *newBTTeamNode(Team *team, BTTeam *left, BTTeam *right) {
    BTTeam *node = (BTTeam *) can_fail_malloc(sizeof(BTTeam));

    node->team = team;
    node->left = left;
    node->right = right;
    node->height = 1;

    return node;
}

/* Liberta a memoria de um node de uma arvore binaria de equipas. */
void freeBTTeamNode(BTTeam *node) {
    free(node);
}

/* Devolve um ponteiro que aponta para uma arvore binaria de equipas vazia. */
BTTeam *newBTTeam() {
    return NULL;
}

/* Liberta toda a memoria da arvore binaria de equipas fornecida, incluido as
   equipas. */
void freeBTTeam(BTTeam *node) {
    if (node != NULL) {
        freeBTTeam(node->left);
        freeBTTeam(node->right);
        freeTeam(node->team);
        freeBTTeamNode(node);
    }
}

/* Devolve o numero de elementos que a arvore binaria de equipas fornecida
   contem. */
int countBTTeam(BTTeam *node) {
    if (node == NULL)
        return 0;

    return 1 + countBTTeam(node->left) + countBTTeam(node->right);
}

/* Devolve um ponteiro que aponta para a equipa com o nome fornecido, se esta
   equipa for um elemento da arvore binaria. Devolve NULL no caso de nao
   existir uma equipa na arvore com o nome fornecido. */
Team *searchBTTeam(BTTeam *node, char *name) {
    int cmp; /* Variavel que guarda a comparacao entre o node e o nome. */

    if (node == NULL)
        /* Equipa nao existe na arvore. */
        return NULL;

    cmp = teamKeyOrder(name, node->team);

    if (cmp == 0)
        /* Encontramos a equipa. */
        return node->team;
    else if (cmp < 0)
        return searchBTTeam(node->left, name);
    else
        return searchBTTeam(node->right, name);
}

/* Devolve-se se existe uma equipa com o nome fornecido na arvore binaria
   dada. */
int existsBTTeam(BTTeam *node, char *name) {
    return searchBTTeam(node, name) != NULL;
}

/* Devolve a altura relativa do node fornecido. */
int heightBBTeam(BTTeam *node){
    if (node == NULL)
        return 0;

    return node->height;
}

/* Funcao auxiliar para efetuar uma rotacao para a esquerda. */
BTTeam *rotLBTTeam(BTTeam *node) {
    int hleft, hright, xleft, xright;

    BTTeam *x = node->right;
    node->right = x->left;
    x->left = node;

    hleft = heightBBTeam(node->left);
    hright = heightBBTeam(node->right);
    node->height = hleft > hright ? hleft + 1 : hright + 1;

    xleft = heightBBTeam(x->left);
    xright = heightBBTeam(x->right);
    x->height = xleft > xright ? xleft + 1 : xright + 1;

    return x;
}

/* Funcao auxiliar para efetuar uma rotacao para a direita. */
BTTeam *rotRBTTeam(BTTeam *node) {
    int hleft, hright, xleft, xright;

    BTTeam *x = node->left;
    node->left = x->right;
    x->right = node;

    hleft = heightBBTeam(node->left);
    hright = heightBBTeam(node->right);
    node->height = hleft > hright ? hleft + 1 : hright + 1;

    xleft = heightBBTeam(x->left);
    xright = heightBBTeam(x->right);
    x->height = xleft > xright ? xleft + 1 : xright + 1;

    return x;
}

/* Funcao auxiliar para efetuar uma rotacao dupla esquerda-direita. */
BTTeam *rotLRBTTeam(BTTeam *node) {
    if (node == NULL)
        return NULL;

    node->left = rotLBTTeam(node->left);
    return rotRBTTeam(node);
}

/* Funcao auxiliar para efetuar uma rotacao dupla direita-esquerda. */
BTTeam *rotRLBTTeam(BTTeam *node) {
    if (node == NULL)
        return NULL;

    node->right = rotRBTTeam(node->right);
    return rotLBTTeam(node);
}

/* Devolve a diferenca de alturas entre os ramos esquerdo e direito. */
int balanceBBTeam(BTTeam *node) {
    if (node == NULL)
        return 0;

    return heightBBTeam(node->left) - heightBBTeam(node->right);
}

/* Funcao auxiliar para balanciar a arvore binaria. */
BTTeam *AVLbalanceBBTeam(BTTeam *node) {
    int balanceFactor, hleft, hright;

    if (node == NULL)
        return NULL;

    balanceFactor = balanceBBTeam(node);
    if (balanceFactor > 1) { /* mais peso para a esquerda */
        if (balanceBBTeam(node->left) >= 0)
            node = rotRBTTeam(node);
        else
            node = rotLRBTTeam(node);
    } else if(balanceFactor < -1){ /* mais peso para a direita*/
        if (balanceBBTeam(node->right) <= 0)
            node = rotLBTTeam(node);
        else
            node = rotRLBTTeam(node);
    } else {
        hleft = heightBBTeam(node->left);
        hright = heightBBTeam(node->right);
        node->height = hleft > hright ? hleft + 1 : hright + 1;
    }

    return node;
}

/* Funcao auxiliar para inserir um novo elemento ah arvore. */
BTTeam *insertBTTeamAux(BTTeam *node, Team *team) {
    int cmp; /* Variavel que guarda a comparacao entre a equipa e o node. */

    if (node == NULL)
        return newBTTeamNode(team, NULL, NULL);

    cmp = teamsOrder(team, node->team);

    if (cmp < 0)
        node->left = insertBTTeamAux(node->left, team);
    else
        node->right = insertBTTeamAux(node->right, team);

    return AVLbalanceBBTeam(node);
}

/* Insere a equipa forncida ah arvore binaria dada. */
void insertBTTeam(BTTeam **node, Team *team) {
    *node = insertBTTeamAux(*node, team);
}

/* Funcao auxiliar para achar o node com o maior elemento da arvore binaria. */
BTTeam *maxBBTeam(BTTeam *node) {
    if (node==NULL || node->right==NULL)
        return node;

    return maxBBTeam(node->right);
}

/* Funcao auxiliar para remover uma equipa com o dado nome da arvore binaria. */
BTTeam *deleteRBTTeam(BTTeam *node, char *name) {
    BTTeam *aux;
    Team *x;
    int cmp;

    if (node == NULL)
        return NULL;

    cmp = teamKeyOrder(name, node->team);

    if (cmp < 0)
        node->left = deleteRBTTeam(node->left, name);
    else if (cmp > 0)
        node->right = deleteRBTTeam(node->right, name);
    else if (node->left != NULL && node->right != NULL) {
        aux = maxBBTeam(node->left);
        x = node->team;
        node->team = aux->team;
        aux->team = x;
        node->left = deleteRBTTeam(node->left, name);
    } else {
        aux = node;

        if (node->left == NULL && node->right == NULL)
            node = NULL;
        else if (node->left == NULL)
            node = node->right;
        else
            node = node->left;

        freeTeam(aux->team);
        freeBTTeamNode(aux);
    }

    return AVLbalanceBBTeam(node);
}

/* Remove a equipa com o nome fornecido da arvore binaria fornecida. */
void deleteBTTeam(BTTeam **node, char *name) {
    *node = deleteRBTTeam(*node, name);
}

/* Funcao auxiliar para achar a lista de equipas com mais vitorias. */
void findBestTeams(TeamList **result, BTTeam *node, int *best) {
    int wins; /* Numero que vitorias que a equipa do node atual tem. */

    if (node != NULL) {
        findBestTeams(result, node->right, best);

        wins = getTeamWins(node->team);
        if (wins == *best) {
            /* Mesmo numero de vitorias que a melhor equipa, adiciona ah lista. */
            shiftTeamList(result, node->team);
        } else if (wins > *best) {
            /* Mais vitorias que o melhor previamente, limpa a lista e adiciona
               ah lista. */
            clearTeamList(result);
            shiftTeamList(result, node->team);
            *best = wins;
        }

        findBestTeams(result, node->left, best);
    }
}

/* Devolve uma lista de equipa que contem as equipas que mais ganharam. */
TeamList *bestBTTeam(BTTeam *node) {
    TeamList *result = newTeamList();
    int best = 0;
    findBestTeams(&result, node, &best);

    return result;
}