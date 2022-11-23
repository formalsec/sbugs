#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"
#include "commands.h"
#include "match.h"
#include "stack.h"
#include "strdup.h"
#include "list.h"

/* compares a and b*/
int compare(const void* a, const void* b) {

    int x;

    teamwins* teamA = (teamwins*)a;
    teamwins* teamB = (teamwins*)b;
    x = teamB->wins - teamA->wins;
    if(x == 0) { 
        x = strcmp(teamA->team, teamB->team);
    }    
    return x;
}

/* adds a new match*/
link a(link matches, tSTACK teams, int lineCounter) {
    MATCH newMatch; /*a new match*/

    newMatch = can_fail_malloc(sizeof(struct match));
    newMatch->name = can_fail_malloc(sizeof(char) * 1024);
    newMatch->team1 = can_fail_malloc(sizeof(char) * 1024);
    newMatch->team2 = can_fail_malloc(sizeof(char) * 1024);

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",
        newMatch->name, newMatch->team1, newMatch->team2, &newMatch->score.score_team1, &newMatch->score.score_team2);
    if(STsearch(newMatch->name) == NULL) {
        if(tSTACKteamsearch(teams, newMatch->team1) != NULL) {
            if(tSTACKteamsearch(teams, newMatch->team2) != NULL) {
                matches = insertEnd(matches, _strdup(newMatch->name));
                STinsert(matchdup(newMatch));       
            }
            else
                printf("%d Equipa inexistente.\n", lineCounter);
        }
        else
            printf("%d Equipa inexistente.\n", lineCounter);
    }
    else {
        printf("%d Jogo existente.\n", lineCounter);
    }
    free(newMatch->name);   
    free(newMatch->team1);
    free(newMatch->team2);
    free(newMatch);
    return matches;
}

/* lists all matches by the order they were added*/
void l(link matches, int lineCounter) {
    MATCH match;    /* a match*/
    link t;
    if(!isEmpty(matches))
        for(t = matches; t != NULL; t = t->next) {
            match = STsearch(t->name);
            if(match != NULL)
                printf("%d %s %s %s %d %d\n",
                    lineCounter, match->name, match->team1, match->team2,
                    match->score.score_team1, match->score.score_team2);
        }
}

/* searches for a match with a given name*/
void p(int lineCounter) {
    MATCH match;    /* a match*/
    char* name;     /* a match's name*/
    name = can_fail_malloc(sizeof(char) * MAXSIZE);
    scanf(" %[^:\n]", name);
    match = STsearch(name);
    if (match != NULL)
        printf("%d %s %s %s %d %d\n",
            lineCounter, match->name, match->team1, match->team2, match->score.score_team1, match->score.score_team2);
    else
        printf("%d Jogo inexistente.\n", lineCounter);
    free(name);
}

/* removes a match with a given name*/
link r(link matches, int lineCounter) {
    char* name; /* a match's name*/

    name = can_fail_malloc(sizeof(char) * MAXSIZE);

    scanf(" %[^:\n]", name);
    if(STsearch(name) != NULL) {
        STdelete(name);
        matches = delete(matches, name);
    }
    else
        printf("%d Jogo inexistente.\n", lineCounter);
    free(name);
    return matches;
}

/* changes a match's score*/
void s(int lineCounter) {
    MATCH match;    /* a match*/
    char* name; /* a match's name*/
    int newscore1, newscore2;

    name = can_fail_malloc(sizeof(char) * MAXSIZE);

    scanf(" %[^:\n]:%d:%d", name, &newscore1, &newscore2);
    match = STsearch(name);
    if(match != NULL) {
        match->score.score_team1 = newscore1;
        match->score.score_team2 = newscore2;
    }
    else
        printf("%d Jogo inexistente.\n", lineCounter);
    free(name);
}

/* adds a new team*/
void A(tSTACK teams, int lineCounter) {
    char* newteam;  /* a new team*/

    newteam = can_fail_malloc(sizeof(char) * MAXSIZE);

    scanf(" %[^:\n]", newteam);
    if(tSTACKteamsearch(teams, newteam) == NULL) {
        tSTACKpush(teams, newteam);
    }
    else{
        printf("%d Equipa existente.\n", lineCounter);
        free(newteam);
    }
}

/* searches for a given team*/
void P(link matches, tSTACK teams, int lineCounter) {
    char* team;     /* a team*/
    int wins = 0;   /* a team's wins*/

    team = can_fail_malloc(sizeof(char) * MAXSIZE);

    scanf(" %[^:\n]", team);
    if(tSTACKteamsearch(teams, team) != NULL) {
        link t;
        MATCH match;    /* a match*/
        for(t = matches; t != NULL; t = t->next) {
            match = STsearch(t->name);
            if(match != NULL) {
                if(strcmp(match->team1, team) == 0) {
                    if(match->score.score_team1 > match->score.score_team2)
                        wins++;
                }
                else if(strcmp(match->team2, team) == 0) {
                    if(match->score.score_team2 > match->score.score_team1)
                        wins++;
                }
            }
        }
        printf("%d %s %d\n", lineCounter, team, wins);
    }
    else
        printf("%d Equipa inexistente.\n", lineCounter);
    free(team);    
}

/* finds the teams that won the most matches and lists them sorted*/
void g(link matches, tSTACK teams, int lineCounter) {
    int wins;   /* a team's wins*/
    int mostwins = 0;   /* most wins obtained by any of the teams*/
    int i = 0;
    int j;
    int len;    /* length of the teams' stack*/
    teamwins* twArray;

    len = tSTACKlength(teams);
    twArray = (teamwins*)can_fail_malloc(sizeof(teamwins) * MAXSIZE * len);

    if(!tSTACKempty(teams)) {
        tlink t;
        link v;
        MATCH match;    /* a match*/
        for(t = teams->head; t != NULL; t = t->next) {
            wins = 0;
            for(v = matches; v != NULL; v = v->next) {
                match = STsearch(v->name);
                if(match != NULL) {
                    if(strcmp(match->team1, t->team) == 0) {
                        if(match->score.score_team1 > match->score.score_team2)
                            wins++;
                    }
                    else if(strcmp(match->team2, t->team) == 0) {
                        if(match->score.score_team2 > match->score.score_team1)
                            wins++;
                    }
                }
            }
            if(wins > mostwins) {
                mostwins = wins;
            }
            twArray[i].team = _strdup(t->team);
            twArray[i].wins = wins;
            i++;
        }
        qsort(twArray, len, sizeof(teamwins), compare);
        
        printf("%d Melhores %d\n", lineCounter, mostwins);
        i = 0;
        while(twArray[i].wins == mostwins) {
            if(twArray[i].team == NULL)
                break;
            printf("%d * %s\n", lineCounter, twArray[i].team);
            i++;
        }
    }
    for(j = 0; j < len; j++) {
        free(twArray[j].team);
    }
    free(twArray);
}

/* ends the program*/
link x(link matches, tSTACK teams) {
    STdeletetable();
    tSTACKdelete(teams);
    destroy(matches);
    return NULL;
}