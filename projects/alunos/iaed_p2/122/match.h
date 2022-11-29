#ifndef MATCH_H
#define MATCH_H

#define MAXSIZE 1024

typedef struct {
    int score_team1;
    int score_team2;
} score;

typedef struct {
    char* team;
    int wins;
} teamwins;

typedef struct match{
    char* name;
    char* team1;
    char* team2;
    score score;
} * MATCH;

//typedef match* MATCH;

MATCH matchdup(MATCH);

#endif