#include "btgame.h"

/* Cria um novo node de uma arvore binaria de jogos. Devolve o ponteiro que
   aponta para o novo node. */
BTGame *newBTGameNode(Game *game, BTGame *left, BTGame *right) {
    BTGame *node = (BTGame *) malloc(sizeof(BTGame));

    node->game = game;
    node->left = left;
    node->right = right;
    node->height = 1;

    return node;
}

/* Liberta a memoria de um node de uma arvore binaria de jogos. */
void freeBTGameNode(BTGame *node) {
    free(node);
}

/* Devolve um ponteiro que aponta para uma arvore binaria de jogos vazia. */
BTGame *newBTGame() {
    return NULL;
}

/* Liberta toda a memoria da arvore binaria de jogos fornecida, incluindo os
   jogos. */
void freeBTGame(BTGame *node) {
    if (node != NULL) {
        freeBTGame(node->left);
        freeBTGame(node->right);
        freeGame(node->game);
        freeBTGameNode(node);
    }
}

/* Devolve o numero de elementos que a arvore binaria de jogos fornecida
   contem. */
int countBTGame(BTGame *node) {
    if (node == NULL)
        return 0;

    return 1 + countBTGame(node->left) + countBTGame(node->right);
}

/* Devolve um ponteiro que aponta para o jogo com o nome fornecido, se este
   jogo for um elemento da arvore binaria. Devolve NULL no caso de nao
   existir uma jogo na arvore com o nome fornecido. */
Game *searchBTGame(BTGame *node, char *name) {
    int cmp; /* Variavel que guarda a comparacao do nome com o node atual. */

    if (node == NULL)
        /* Jogo nao existe na arvore binaria. */
        return NULL;

    cmp = gameKeyOrder(name, node->game);

    if (cmp == 0)
        /* Jogo encontrado. */
        return node->game;
    else if (cmp < 0)
        /* Jogo encontra-se no ramo esquerdo. */
        return searchBTGame(node->left, name);
    else
        /* Jogo encontra-se no ramo direito. */
        return searchBTGame(node->right, name);
}

/* Devolve-se se existe um jogo com o nome fornecido na arvore binaria
   dada. */
int existsBTGame(BTGame *node, char *name) {
    return searchBTGame(node, name) != NULL;
}

/* Devolve a altura relativa do node fornecido. */
int heightBBGame(BTGame *node){
    if (node == NULL)
        return 0;

    return node->height;
}

/* Funcao auxiliar para efetuar uma rotacao para a esquerda. */
BTGame *rotLBTGame(BTGame *node) {
    int hleft, hright, xleft, xright;

    BTGame *x = node->right;
    node->right = x->left;
    x->left = node;

    hleft = heightBBGame(node->left);
    hright = heightBBGame(node->right);
    node->height = hleft > hright ? hleft + 1 : hright + 1;

    xleft = heightBBGame(x->left);
    xright = heightBBGame(x->right);
    x->height = xleft > xright ? xleft + 1 : xright + 1;

    return x;
}

/* Funcao auxiliar para efetuar uma rotacao para a direita. */
BTGame *rotRBTGame(BTGame *node) {
    int hleft, hright, xleft, xright;

    BTGame *x = node->left;
    node->left = x->right;
    x->right = node;

    hleft = heightBBGame(node->left);
    hright = heightBBGame(node->right);
    node->height = hleft > hright ? hleft + 1 : hright + 1;

    xleft = heightBBGame(x->left);
    xright = heightBBGame(x->right);
    x->height = xleft > xright ? xleft + 1 : xright + 1;

    return x;
}

/* Funcao auxiliar para efetuar uma rotacao dupla esquerda-direita. */
BTGame *rotLRBTGame(BTGame *node) {
    if (node == NULL)
        return NULL;

    node->left = rotLBTGame(node->left);
    return rotRBTGame(node);
}

/* Funcao auxiliar para efetuar uma rotacao dupla direita-esquerda. */
BTGame *rotRLBTGame(BTGame *node) {
    if (node == NULL)
        return NULL;

    node->right = rotRBTGame(node->right);
    return rotLBTGame(node);
}

/* Devolve a diferenca de alturas entre os ramos esquerdo e direito. */
int balanceBBGame(BTGame *node) {
    if (node == NULL)
        return 0;

    return heightBBGame(node->left) - heightBBGame(node->right);
}

/* Funcao auxiliar para balanciar a arvore binaria. */
BTGame *AVLbalanceBBGame(BTGame *node) {
    int balanceFactor, hleft, hright;

    if (node == NULL)
        return NULL;

    balanceFactor = balanceBBGame(node);
    if (balanceFactor > 1) { /* mais peso para a esquerda */
        if (balanceBBGame(node->left) >= 0)
            node = rotRBTGame(node);
        else
            node = rotLRBTGame(node);
    } else if(balanceFactor < -1){ /* mais peso para a direita*/
        if (balanceBBGame(node->right) <= 0)
            node = rotLBTGame(node);
        else
            node = rotRLBTGame(node);
    } else {
        hleft = heightBBGame(node->left);
        hright = heightBBGame(node->right);
        node->height = hleft > hright ? hleft + 1 : hright + 1;
    }

    return node;
}

/* Funcao auxiliar para inserir um novo elemento ah arvore. */
BTGame *insertBTGameAux(BTGame *node, Game *game) {
    int cmp; /* Variavel que guarda a comparacao do nome do jogo com o node atual. */

    if (node == NULL)
        return newBTGameNode(game, NULL, NULL);

    cmp = gamesOrder(game, node->game);

    if (cmp < 0)
        node->left = insertBTGameAux(node->left, game);
    else
        node->right = insertBTGameAux(node->right, game);

    return AVLbalanceBBGame(node);
}

/* Insere a jogo forncida ah arvore binaria dada. */
void insertBTGame(BTGame **node, Game *game) {
    *node = insertBTGameAux(*node, game);
}

/* Funcao auxiliar para achar o node com o maior elemento da arvore binaria. */
BTGame *maxBBGame(BTGame *node) {
    if (node==NULL || node->right==NULL)
        return node;

    return maxBBGame(node->right);
}

/* Funcao auxiliar para remover uma jogo com o dado nome da arvore binaria. */
BTGame *deleteRBTGame(BTGame *node, char *name) {
    BTGame *aux;
    Game *x;
    int cmp;

    if (node == NULL)
        return NULL;

    cmp = gameKeyOrder(name, node->game);

    if (cmp < 0)
        node->left = deleteRBTGame(node->left, name);
    else if (cmp > 0)
        node->right = deleteRBTGame(node->right, name);
    else if (node->left != NULL && node->right != NULL) {
        aux = maxBBGame(node->left);
        x = node->game;
        node->game = aux->game;
        aux->game = x;
        node->left = deleteRBTGame(node->left, name);
    } else {
        aux = node;

        if (node->left == NULL && node->right == NULL)
            node = NULL;
        else if (node->left == NULL)
            node = node->right;
        else
            node = node->left;

        freeGame(aux->game);
        freeBTGameNode(aux);
    }

    return AVLbalanceBBGame(node);
}

/* Remove a jogo com o nome fornecido da arvore binaria fornecida. */
void deleteBTGame(BTGame **node, char *name) {
    *node = deleteRBTGame(*node, name);
}

/* Funcao auxiliar para transformar a arvore binaria numa array. */
void dumpGame(Game *array[], BTGame *node, int index) {
    array[index] = node->game;
    index++;

    if (node->right != NULL) {
        dumpGame(array, node->right, index);
        index = index + countBTGame(node->right);
    }

    if (node->left != NULL) {
        dumpGame(array, node->left, index);
    }
}

/* Coloca todos os jogos da arvore binaria fornecida na array fornecida numa
   ordem nao definida/arbitraria. */
void dumpBTGame(Game *array[], BTGame *node) {
    if (node != NULL) {
        dumpGame(array, node, 0);
    }
}
