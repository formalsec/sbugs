#ifndef __COMMANDS__
#define __COMMANDS__

#include "hashtable-structs.h"
#include "commands.h"

link a(link* hashtable, int size_table
        , team_ptr team_list, link game_list, int nl);
team_ptr A(team_ptr team_list, int nl);


void p(link* hashtable, int size_table, int nl);
void P(team_ptr team_list, int nl);

void l(link* hashtable, int size_table, link game_list, int nl);

link r(link* hashtable, int size_table
        , link game_list, team_ptr team_list, int nl);

link s(link* hashtable, int size_table, link game_list
        , team_ptr team_list, int nl);

int compareStr(const void *pa, const void *pb);

void g(team_ptr team_list, int nl);


#endif