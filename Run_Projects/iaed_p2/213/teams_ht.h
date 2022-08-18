#ifndef SIZE_HT
#define SIZE_HT 48611
#endif


#ifndef TEAMS_HT
#define TEAMS_HT

/* Declaracoes relacionadas com a estrutura Team */
#include "team.h"

/* Funcao de hashing */
#include "hash.h"


/* Prototipos de funcoes da hashtable de equipas */
Team * T_init();
void T_insert(Team * teams, Team t);
Team T_search(Team * teams, char * name);
int find_winner(Team * teams, int * num);
void get_winners(Team * teams, Team * winners, int max);
void T_destroy(Team * teams);

#endif
