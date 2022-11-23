#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "commands.h"

/* Funcao resposavel pela logica de criar e adiconar um novo jogo ao sistema. */
void createGameCmd(int nl, BTTeam *teams, BTGame **games) {
    char name[NAME_MAXSIZE];      /* Buffer para guardar o nome do novo jogo. */
    char teamName1[NAME_MAXSIZE]; /* Buffer para guardar o nome da primeira equipa. */
    char teamName2[NAME_MAXSIZE]; /* Buffer para guardar o nome da segunda equipa. */
    int score1, score2;           /* Pontuacao das equipas 1 e 2. */
    Team *team1, *team2;          /* Equipas 1 e 2. */
    Game *game;                   /* Novo jogo. */

    /* Obter os argumentos do comando. */
    scanf(
        " %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",
        name, teamName1, teamName2, &score1, &score2
    );

    /* Verificar se o jogo existe. */
    if (existsBTGame(*games, name)) {
        printf("%d Jogo existente.\n", nl);
        return;
    } else {
        team1 = searchBTTeam(teams, teamName1);
        team2 = searchBTTeam(teams, teamName2);
        /* Verificar se as equipas existem. */
        if (team1 == NULL || team2 == NULL) {
            printf("%d Equipa inexistente.\n", nl);
        } else {
            /* Criar o jogo e adicionar ao sistema. */
            game = newGame(nl, name, team1, team2, score1, score2);
            insertBTGame(games, game);
        }
    }
}

/* Funcao auxiliar utilizada juntamente com o qsort para ordenar os jogos pela
   ordem de insercao. */
int sortbyNL(const void *a, const void *b) {
    return getGameCT(*(Game **) a) - getGameCT(*(Game **) b);
}

/* Funcao responsavel pela logica de listar todos os jogos por dem de
   insercao. */
void listAllGamesCmd(int nl, BTGame *games) {
    int i;
    /* Numero de jogos no sistema. */
    int count = countBTGame(games);
    /* Transformar arvore binaria para array. */
    Game **gamesArr = (Game **) can_fail_malloc(sizeof(Game *) * count);
    dumpBTGame(gamesArr, games);

    /* Ordenadar array pela data de insercao. */
    qsort(gamesArr, count, sizeof(Game *), sortbyNL);

    for (i = 0; i < count; i++) {
        printGame(gamesArr[i], nl);
    }

    free(gamesArr);
}

/* Funcao responsavel pela logica de procurar um jogo no sistema. */
void searchGameCmd(int nl, BTGame *games) {
    char name[NAME_MAXSIZE]; /* Buffer para guardar o nome do jogo. */
    Game *game;              /* O jogo encontrado. */

    /* Obter argumentos do comando. */
    scanf(" %[^:\n]", name);

    game = searchBTGame(games, name);
    if (game == NULL) { /* Verificar se o jogo existe. */
        printf("%d Jogo inexistente.\n", nl);
    } else {
        printGame(game, nl);
    }
}

/* Funcao responsavel pela logica de eliminar um jogo do sistema. */
void deleteGameCmd(int nl, BTGame **games) {
    char name[NAME_MAXSIZE]; /* Buffer para guardar o nome do jogo. */

    /* Obter argumentos do comando. */
    scanf(" %[^:\n]", name);

    if (!existsBTGame(*games, name)) { /* Verificar se o jogo existe. */
        printf("%d Jogo inexistente.\n", nl);
    } else {
        deleteBTGame(games, name);
    }
}

/* Funcao responsavel pela logica de alterar a pontuacao de um jogo. */
void changeGameScoresCmd(int nl, BTGame *games) {
    char name[NAME_MAXSIZE]; /* Buffer para guardar o nome do jogo. */
    int score1, score2;      /* Novas pontuacoes para as equipas 1 e 2. */
    Game *game;              /* Jogo ao qual vamos alterar a pontuacao. */

    /* Obter argumentos do comando. */
    scanf(" %[^:\n]:%d:%d", name, &score1, &score2);

    game = searchBTGame(games, name);

    if (game == NULL) { /* Verificar se o jogo existe. */
        printf("%d Jogo inexistente.\n", nl);
    } else {
        updateGameScore(game, score1, score2);
    }
}

/* Funcao responsavel pela logica de criar uma equipa e a inserir no sistema. */
void createTeamCmd(int nl, BTTeam **teams) {
    char name[NAME_MAXSIZE]; /* Buffer para guardar o nome da nova equipa. */
    Team *team;              /* Nova equipa. */

    /* Obter argumentos do comando. */
    scanf(" %[^:\n]", name);

    /* Verificar se uma equipa com este nome jah existe. */
    if (existsBTTeam(*teams, name)) {
        printf("%d Equipa existente.\n", nl);
    } else {
        team = newTeam(name, 0);
        insertBTTeam(teams, team);
    }
}

/* Funcao responsavel pela logica do comando que procurar uma equipa no
   sistema. */
void searchTeamCmd(int nl, BTTeam *teams) {
    char name[NAME_MAXSIZE]; /* Buffer que guarda o nome. */
    Team *team;              /* Equipa a procurar. */

    /* Obter argumentos do comando. */
    scanf(" %[^:\n]", name);

    team = searchBTTeam(teams, name);

    if (team == NULL) { /* Verificar se a equipa jah existe. */
        printf("%d Equipa inexistente.\n", nl);
    } else {
        printf("%d %s %d\n", nl, getTeamName(team), getTeamWins(team));
    }
}

/* Funcao responsavel pela logica do comando que retorna as equipas que mais
   jogos ganharam. */
void bestTeamsCmd(int nl, BTTeam *teams) {
    TeamList *best = bestBTTeam(teams);
    int wins;

    if (countTeamList(best) > 0) {
        wins = getTeamWins(best->team);

        printf("%d Melhores %d\n", nl, wins);
        printTeamList(best, nl);
    }

    clearTeamList(&best);
}
