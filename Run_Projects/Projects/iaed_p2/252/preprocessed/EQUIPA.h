#ifndef EQUIPA_H
#define EQUIPA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HASHTABLE.h" /* Ficheiro que contem as funcoes que gerem as hashtables */
		         
#define DIM_STR	1024  

Equipa* FindTeam(team_list* l, char buffer[DIM_STR]);

void comando_P(team_list* l, int NL);

void SearchTeam(team_list* l,char buffer[DIM_STR], int NL);

team_list* comando_A(team_list* l,int NL);

team_list* teamAdd(team_list* l, char* buffer);

#endif
