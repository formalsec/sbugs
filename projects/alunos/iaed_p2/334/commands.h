#ifndef COMMANDS_H__
#define COMMANDS_H__

#include "teams.h"

void command_a(char *command, teamList **t, gameList **g, int nl);
void command_A(char *command, teamList **t, int nl);
void command_l(gameList **g, int nl);
void command_p(char *command, gameList **g, int nl);
void command_P(char *command, teamList **t, int nl);
void command_r(char *command, gameList **g, int nl);
void command_s(char *command, gameList **g, int nl);
void command_g(teamList **t, int nl);

#endif /* COMMANDS_H__ */
