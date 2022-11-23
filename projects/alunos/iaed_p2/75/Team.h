#ifndef TEAM_H
#define TEAM_H

#define WIN 1     /* FLag represents win */
#define LOSS -1   /* Flag represents loss */

/* ============================= TEAM STRUCTURE ================================= */

typedef struct team{
    char* name;
    int victories;
}Team;

/* ============================ PROTOTYPES FOR TEAM ============================== */

Team* newTeam(char* name);
void deleteTeam(Team* tm);
void change_victory(Team* pteam, int change);

#endif