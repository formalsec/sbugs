#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "game.h"

/* Cria um novo jogo com o nome, equipas e golos fornecidos. Devolve o ponteiro
   que aponta para o novo jogo. */
Game *newGame(int ct, char *name, Team *team1, Team *team2, int score1, int score2) {
    Game *game = (Game *) can_fail_malloc(sizeof(Game));

    /* Copiar nome para novo espaco com apenas o tamanho necessario. */
    game->name = (char *) can_fail_malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(game->name, name);

    game->team1 = team1;
    game->team2 = team2;
    game->score1 = 0;
    game->score2 = 0;
    game->ct = ct;

    /* Evitar repeticao de codigo, alterar pontuacao do jogo. */
    updateGameScore(game, score1, score2);

    return game;
}

/* Liberta a memoria do jogo fornecido. */
void freeGame(Game *game) {
    updateGameScore(game, 0, 0);
    free(game->name);
    free(game);
}

/* Devolve o nome do jogo. */
char *getGameName(Game *game) {
    return game->name;
}

/* Devolve um ponteiro que aponta para a primeira equipa do jogo. */
Team *getGameTeam1(Game *game) {
    return game->team1;
}

/* Devolve um ponteiro que aponta para a segunda equipa do jogo. */
Team *getGameTeam2(Game *game) {
    return game->team2;
}

/* Devolve o numero de golos que a primeira equipa marcou. */
int getGameScore1(Game *game) {
    return game->score1;
}

/* Devolve o numero de golos que a segunda equipa marcou. */
int getGameScore2(Game *game) {
    return game->score2;
}

int getGameCT(Game *game) {
    return game->ct;
}

/* Altera a pontuacao de um jogo para a nova pontuacao fornecida. O numero
   total de vitorias de cada equipa tambem eh atualizado. */
void updateGameScore(Game *game, int score1, int score2) {
    /* Remover vitoria da equipa anteriomente vencedora. */
    if (game->score1 > game->score2) {
        addTeamWins(game->team1, -1);
    } else if (game->score1 < game->score2) {
        addTeamWins(game->team2, -1);
    }

    game->score1 = score1;
    game->score2 = score2;

    /* Adicionar vitoria ah nova equipa vencedora. */
    if (game->score1 > game->score2) {
        addTeamWins(game->team1, 1);
    } else if (game->score1 < game->score2) {
        addTeamWins(game->team2, 1);
    }
}

/* Faz print do jogo fornecido com o numero de linha fornecido. */
void printGame(Game *game, int nl) {
    printf(
        "%d %s %s %s %d %d\n", nl,
        getGameName(game),
        getTeamName(game->team1),
        getTeamName(game->team2),
        game->score1,
        game->score2
    );
}

/* Devolve numero de comparacao entre o nome fornecido e o jogo fornecido.
   Negativo -> nome fornecido encontra-se ah esquerda.
   Igual -> nome fornecido eh igual.
   Positivo -> nome fornecido encontra-se ah direita. */
int gameKeyOrder(char *name, Game *game) {
    return strcmp(name, game->name);
}

/* Devolve numero de comparacao entre os jogos fornecidos.
   Negativo -> game1 fornecido encontra-se ah esquerda de game2.
   Igual -> game1 fornecido eh igual a game2.
   Positivo -> game1 fornecido encontra-se ah direita de game2. */
int gamesOrder(Game *game1, Game *game2) {
    return strcmp(game1->name, game2->name);
}
