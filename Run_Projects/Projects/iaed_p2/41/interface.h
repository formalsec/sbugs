#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hash.h"
#include "team.h"
#include "game.h"
#include "team_struct.h"
#include "game_struct.h"

void execute_command(team_node *, game_item *);

#endif