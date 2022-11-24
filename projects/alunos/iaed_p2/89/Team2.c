#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "Team2.h"

/* Adds a Team to the system */
void addTeam(char *name, BTlink* BThead, int NL){
    Team team = BTsearch(*BThead, name);
    if (!team){
        team = Tnew(name);
        *BThead = BTinsert(*BThead, team);
    }
    else
        printf("%d Equipa existente.\n", NL);

}

/* Search for a team in the system and prints it's names and wins */
void searchTeam(char* name, BTlink BThead, int NL){
    Team team = BTsearch(BThead, name);
    if (team)
        printf("%d %s %d\n", NL, Tgetname(team), Tgetwins(team));
    else
        printf("%d Equipa inexistente.\n", NL);
}

/* Prints the teams with the most wins */
void showwinners(BTlink BThead, int NL){
    LTlink List_head = LTinit();
    Ttraverse(BThead, &List_head, 0);
    LTprint(List_head, NL);
    LTclear(List_head);
}

/* Frees all memory allocations made regarding teams */
void freeAllTeams(BTlink *BThead){
    Team team;
    while(*BThead != NULL){
        team = BTgetteam(*BThead);
        *BThead = BTdelete(*BThead, team);
        Tdelete(team);
    }
}
