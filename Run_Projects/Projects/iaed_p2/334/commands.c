#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include "teams.h"

/* Mostra mensagem de erro e da return da funcao */
#define ERR(x) { \
        printf("%d %s\n", nl, x); \
        return; \
    }

/* Analisa a linha de comandos e procura o proximo argumento */
#define PARSE_ARG(prev_arg, arg) { \
        arg = prev_arg; \
        while(*arg && *arg != ':') arg++; \
        if(!*arg) ERR("Bad command format."); \
        *arg = '\0'; \
        arg++; \
}

/* Executa o comando a */
void command_a(char *command, teamList **t, gameList **g, int nl)
{
    char *name, *t1name, *t2name, *sc1str, *sc2str;
    int score1, score2;
    teamList *team1, *team2;

    /* Analisar argumentos da linha de comandos */
    name = command;
    PARSE_ARG(name, t1name);
    PARSE_ARG(t1name, t2name);
    PARSE_ARG(t2name, sc1str);
    PARSE_ARG(sc1str, sc2str);
    /* Converte de strings para int para os scores */
    if(sscanf(sc1str, "%d", &score1) == 0) ERR("Bad command format.");
    if(sscanf(sc2str, "%d", &score2) == 0) ERR("Bad command format.");

    /* Se ja existe jogo com mesmo nome, erro */
    if(findGame(*g, name)) ERR("Jogo existente.");

    team1 = findTeam(*t, t1name);
    team2 = findTeam(*t, t2name);
    /* Se ambas equipas nao existem, erro */
    if(!team1 || !team2) ERR("Equipa inexistente.");

    /* Aumenta numero de vitorias do vencedor */
    if(score1 > score2) team1->won++;
    else if(score1 < score2) team2->won++;

    /* Adiciona novo jogo a lista */
    *g = addGame(*g, name, team1, team2, score1, score2);
}

/* Executa o comando A */
void command_A(char *command, teamList **t, int nl)
{
    char *name = command;
    /* Truncagem do ultimo caractere para remover '\n' */
    name[strlen(name) - 1] = '\0';

    /* Se uma equipa com o mesmo nome ja existe, erro */
    if(findTeam(*t, name)) ERR("Equipa existente.");

    /* Adiciona nova equipa a lista */
    *t = addTeam(*t, name);
}

/* Executa comando l */
void command_l(gameList **g, int nl)
{
    gameList *cur = *g;

    /* Por cada jogo na lista, print */
    while(cur)
    {
        printf("%d %s %s %s %d %d\n",
                nl,
                cur->name,
                cur->team1->name,
                cur->team2->name,
                cur->score1,
                cur->score2
        );
        cur = cur->next;
    }
}

/* Executa comando p */
void command_p(char *command, gameList **g, int nl)
{
    char *name = command;
    gameList *game;

    /* Truncagem do ultimo caractere para remover '\n' */
    name[strlen(name) - 1] = '\0';
    game = findGame(*g, name);

    /* Se o jogo nao existe, erro */
    if(!game) ERR("Jogo inexistente.");

    /* Print da info do jogo */
    printf("%d %s %s %s %d %d\n",
            nl,
            game->name,
            game->team1->name,
            game->team2->name,
            game->score1,
            game->score2
    );
}

/* Executa comando P */
void command_P(char *command, teamList **t, int nl)
{
    char *name = command;
    teamList *team;
    
    /* Truncagem do ultimo caractere para remover '\n' */
    name[strlen(name) - 1] = '\0';
    team = findTeam(*t, name);

    /* Se a equipa nao existir, erro */
    if(!team) ERR("Equipa inexistente.");

    /* Print da info da equipa */
    printf("%d %s %d\n",
            nl,
            team->name,
            team->won
    );
}

/* Executa o comando r */
void command_r(char *command, gameList **g, int nl)
{
    char *name = command;
    gameList *game;

    /* Truncagem do ultimo caractere para remover '\n' */
    name[strlen(name) - 1] = '\0';
    game = findGame(*g, name);

    /* Se o jogo nao existir, erro */
    if(!game) ERR("Jogo inexistente.");

    /* Remove o jogo do contador de vitorias do vencedor */
    if(game->score1 > game->score2) game->team1->won--;
    else if(game->score1 < game->score2) game->team2->won--;

    /* Apaga jogo da lista */
    *g = deleteGame(*g, game);
}

/* Executa o comando s */
void command_s(char *command, gameList **g, int nl)
{
    char *name, *sc1str, *sc2str;
    int score1, score2;
    gameList *game;

    /* Analisa argumentos da command line */
    name = command;
    PARSE_ARG(name, sc1str);
    PARSE_ARG(sc1str, sc2str);
    /* Converte string para int para os scores*/
    if(sscanf(sc1str, "%d", &score1) == 0) ERR("Bad command format.");
    if(sscanf(sc2str, "%d", &score2) == 0) ERR("Bad command format.");

    /* Se o jogo nao existe, erro */
    game = findGame(*g, name);
    if(!game) ERR("Jogo inexistente.");

    /* Atualiza contador de vitorias das equipas */
    if(game->score1 > game->score2) game->team1->won--;
    else if(game->score1 < game->score2) game->team2->won--;

    if(score1 > score2) game->team1->won++;
    else if(score1 < score2) game->team2->won++;

    /* Poe os scores */
    game->score1 = score1;
    game->score2 = score2;
}

/* Partition function para o quicksort */
int partition(char **names, int lo, int hi)
{
    char *pi = names[(hi + lo) / 2];
    char *swap;
    int i = lo;
    int j = hi;

    while(1)
    {
        while(strcmp(names[i], pi) < 0) i++;
        while(strcmp(names[j], pi) > 0) j--;
        if(i >= j) return j;
        swap = names[i];
        names[i] = names[j];
        names[j] = swap;
        i++;
        j--;
    }

    return -1;
}

/* Quicksort para nomes das equipas */
void quickSort(char **names, int lo, int hi)
{
    int pi;
    if (lo < hi)
    {
        pi = partition(names, lo, hi);
        quickSort(names, lo, pi);
        quickSort(names, pi + 1, hi);
    }
}

/* Executa o comando g */
void command_g(teamList **t, int nl)
{
    int maxWon = 0, sizeWon = 0, i = 0;
    char **listNames = NULL;
    teamList *cur = *t;

    /* Se a lista estiver vazia, nao faz nada */
    if(!*t) return;

    /* Encontra o maior numero de vitorias e quantas equipas ganharam esse numero de jogos */
    while(cur)
    {
        if(cur->won == maxWon)
            sizeWon++;
        if(cur->won > maxWon)
        {
            maxWon = cur->won;
            sizeWon = 1;
        }
        cur = cur->next;
    }

    /* Alocacao da lista dos nomes */
    listNames = malloc(sizeWon * sizeof(char *));
    if(!listNames) exit(1);
    /* Copia os nomes das equipas com mais vitorias para a lista de nomes*/
    cur = *t;
    while(cur)
    {
        if(cur->won == maxWon)
        {
            listNames[i] = cur->name;
            i++;
        }
        cur = cur->next;
    }

    /* Sort dos nomes */
    quickSort(listNames, 0, sizeWon - 1);

    /* Print da lista dos nomes */
    printf("%d Melhores %d\n", nl, maxWon);
    for(i = 0; i < sizeWon; i++)
    {
        printf("%d * %s\n", nl, listNames[i]);
    }

    /* Free da lista de nomes */
    free(listNames);
}
