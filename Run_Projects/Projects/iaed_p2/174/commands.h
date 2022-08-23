#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdio.h>
#include "team.h"
#include "teamlist.h"
#include "btteam.h"
#include "game.h"
#include "btgame.h"

/* Tamanho maximo que o nome dos jogos e das equipas podem ter. */
#define NAME_MAXSIZE 1024

/* Funcoes que tratam da logica dos comandos. */
void createGameCmd(int, BTTeam *, BTGame **);
void listAllGamesCmd(int, BTGame *);
void searchGameCmd(int, BTGame *);
void deleteGameCmd(int, BTGame **);
void changeGameScoresCmd(int, BTGame *);
void createTeamCmd(int, BTTeam **);
void searchTeamCmd(int, BTTeam *);
void bestTeamsCmd(int, BTTeam *);

#endif