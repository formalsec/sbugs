#ifndef _EQUIPAS_
#define _EQUIPAS_

/* Struct equipa caracterizada por um nome e um numero de vitorias */
typedef struct equipa {
    char *name;
    int wins;
}Team;

/* Struct para um no de uma equipa caracterizado por um ponteiro para uma equipa
e um ponteiro para next */
typedef struct teamNode {
    Team * team;
    struct teamNode * next, * prev;
} TeamNode;

/* Ponteiro para um no de uma equipa */
typedef struct teamNode* teamNodeP;

/*-------------------------------------------------------------------------------------------
Funcao que cria uma nova equipa e atribui valores as variaveis
---------------------------------------------------------------------------------------------*/
teamNodeP newTeam (char* nome);

/*-------------------------------------------------------------------------------------------
Funcao que cria um ponteiro para um no de uma equipa e inicializa variaveis
---------------------------------------------------------------------------------------------*/
teamNodeP newTeamNode (Team * eq);

#endif