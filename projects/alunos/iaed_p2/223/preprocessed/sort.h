#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "equipas.h"
#include "jogos.h"
#include "game_lists.h"
#include "team_lists.h"
#include "game_hashtable.h"
#include "team_hashtable.h"
#include "iteam_hashtable.h"

#ifndef SORT_H
#define SORT_H
void swap(tlink i, tlink j);
void sortlist(tlink head);
#endif