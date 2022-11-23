#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <string.h>
#include "teams.h"

char *strdup (const char *s)
{
  size_t len = strlen (s) + 1;
  void *new = can_fail_malloc (len);
  if (new == NULL)
    return NULL;
  return (char *) memcpy (new, s, len);
}


/* Adiciona nova equipa no inicio da lista (ordem nao importa) ou cria nova lista se t for NULL*/
teamList *addTeam(teamList *t, char *name)
{
    teamList *newTeam = NULL, *head = t;

    newTeam = can_fail_malloc(sizeof(teamList));
    if(!newTeam) exit(1);

    if(!head)
    {
        newTeam->next = NULL;
    } else {
        newTeam->next = head;
    }

    head = newTeam;
    newTeam->name = strdup(name);
    newTeam->won = 0;

    return head;
}

/* Adiciona novo jogo no fim da lista (importante pois queremos dar print pela ordem que foi criada) 
   ou cria nova lista se g for NULL*/
gameList *addGame(gameList *g, char *name, teamList *team1, teamList *team2, int score1, int score2)
{
    gameList *newGame = NULL, *head = g, *tail = g;

    newGame = can_fail_malloc(sizeof(gameList));
    if(!newGame) exit(1);

    if(!head)
    {
        head = newGame;
        newGame->prev = NULL;
    } else {
        while(tail->next) tail = tail->next;
        tail->next = newGame;
        newGame->prev = tail;
    }

    newGame->next = NULL;
    newGame->name = strdup(name);
    newGame->team1 = team1;
    newGame->team2 = team2;
    newGame->score1 = score1;
    newGame->score2 = score2;

    return head;
}

/* Encontra uma equipa na lista dado o nome ou retorna NULL se equipa nao existir*/
teamList *findTeam(teamList *t, char *name)
{
    teamList *cur = t;
    while(cur)
    {
        if(!strcmp(cur->name, name))
            return cur;
        cur = cur->next;
    }

    return NULL;
}

/* Encontra um jogo na lista dado o nome ou retorn NULL se jogo nao existir */
gameList *findGame(gameList *g, char *name)
{
    gameList *cur = g;
    while(cur)
    {
        if(!strcmp(cur->name, name))
            return cur;
        cur = cur->next;
    }

    return NULL;
}

/* Apaga jogo da lista */
gameList *deleteGame(gameList *g, gameList *game)
{
    gameList *prev, *next;
    if(!game || !g) return g;

    prev = game->prev;
    next = game->next;

    /* Se apagarmos o primeiro jogo da lista, se existir um segundo jogo ele ficara como primeiro jogo*/
    if(g == game)
        g = g->next;

    /* Remove o jogo da lista */
    if(prev)
        prev->next = next;
    if(next)
        next->prev = prev;

    /* Free do jogo */
    free(game->name);
    free(game);

    return g;
}

/* Free da lista de equipas */
void freeTeams(teamList *t)
{
    teamList *cur = t, *next;
    while(cur)
    {
        next = cur->next;
        free(cur->name);
        free(cur);
        cur = next;
    }
}

/* Free da lista de jogos */
void freeGames(gameList *g)
{
    gameList *cur = g, *next;
    while(cur)
    {
        next = cur->next;
        free(cur->name);
        free(cur);
        cur = next;
    }
}
