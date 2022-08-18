#ifndef TEAM_HASH_H
#define TEAM_HASH_H

#include "Team.h"

/* ========================== STRUCTURES =========================== */

typedef struct node_team{            /* Node for lists of Hash Table */
    Team* pteam;
    struct node_team* next;
}* link_team;


/* ========================= PROTOTYPES ========================== */

link_team* initTeam_Hash(int size);
void insertTeam_Hash(int size, link_team* h, Team* t);
void deleteTeam_Hash(int size, link_team* h, char* name_delete);
Team* searchTeam_Hash(int size, link_team* h, char* name);
void destroyTeam_Hash(int size, link_team* head);

#endif